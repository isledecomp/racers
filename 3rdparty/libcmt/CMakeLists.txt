add_library(patched-libcmt INTERFACE)

set(MSVC_CRT_SRC_PATH "" CACHE PATH "Path of MSVC6 CRT/SRC")
# Locate the LIBCMT.LIB picked up from the LIB env var
set(libs "$ENV{LIB}")
if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  string(REPLACE ":" ";" libs "${libs}")
endif()
find_library(LIBCMT_MSVC6_RTM_LIB NAMES LIBCMT.LIB libcmt.lib HINTS ${libs})

set(patch_libcmd TRUE)
if(NOT EXISTS "${MSVC_CRT_SRC_PATH}/calloc.c")
  message(STATUS "Missing path of MSVC6 SP3 CRT sources (MSVC_CRT_SRC_PATH)")
  set(patch_libcmd FALSE)
endif()
if(NOT EXISTS "${LIBCMT_MSVC6_RTM_LIB}")
  message(STATUS "Missing path of MSVC6 RTM LIBCMT library (LIBCMT_MSVC6_RTM_LIB)")
  set(patch_libcmd FALSE)
endif()
if(patch_libcmd)
  enable_language(C)
  set(CMAKE_CXX_FLAGS "/W3 /GX /DWIN32 /D_WINDOWS")
  set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Od /D_DEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/O1 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O1 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /DNDEBUG")

  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")

  # Compile our SP3 heap overlay as an OBJECT library so we can patch the
  # resulting .obj files into a copy of RTM's LIBCMT.LIB.
  add_library(goldp_libcmt_objs OBJECT
    "${MSVC_CRT_SRC_PATH}/free.c"
    "${MSVC_CRT_SRC_PATH}/calloc.c"
    "${MSVC_CRT_SRC_PATH}/malloc.c"
    "${MSVC_CRT_SRC_PATH}/realloc.c"
    "${MSVC_CRT_SRC_PATH}/expand.c"
    "${MSVC_CRT_SRC_PATH}/msize.c"
    "${MSVC_CRT_SRC_PATH}/sbheap.c"
    "${MSVC_CRT_SRC_PATH}/heapinit.c"
    "${MSVC_CRT_SRC_PATH}/heapchk.c"
    "${MSVC_CRT_SRC_PATH}/heapmin.c"
    "${MSVC_CRT_SRC_PATH}/new.cpp"
    "${MSVC_CRT_SRC_PATH}/delete.cpp"
  )
  target_include_directories(goldp_libcmt_objs PRIVATE "${MSVC_CRT_SRC_PATH}")
  target_compile_definitions(goldp_libcmt_objs PRIVATE WIN32_LEAN_AND_MEAN NOSERVICE)
  target_compile_definitions(goldp_libcmt_objs PRIVATE _MBCS _MB_MAP_DIRECT)
  target_compile_definitions(goldp_libcmt_objs PRIVATE _CRTBLD)
  target_compile_definitions(goldp_libcmt_objs PRIVATE WINHEAP)
  target_compile_options(goldp_libcmt_objs PRIVATE -Zp8 -GFy -GB -Gi- -Zl)
  set_property(TARGET goldp_libcmt_objs PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  # Suppress source-level debug info so the PDB doesn't emit S_GPROC32 entries with C-source
  # names for CRT internals — this would shadow PUBLIC symbol names and break reccmp's symbol
  # resolution for call targets that LR's PDB only knows by linker-decorated name.
  set_property(TARGET goldp_libcmt_objs PROPERTY MSVC_DEBUG_INFORMATION_FORMAT "")

  # Build a patched LIBCMT.LIB: copy lib, strip heap .obj members, add ours.
  set(PATCHED_LIBCMT "${CMAKE_CURRENT_BINARY_DIR}/GOLDP_LIBCMT.lib")
  set(PRUNED_LIBCMT "${CMAKE_CURRENT_BINARY_DIR}/PRUNED_LIBCMT.lib")

  add_custom_command(
    OUTPUT "${PATCHED_LIBCMT}"
    BYPRODUCTS "${PRUNED_LIBCMT}"
    DEPENDS goldp_libcmt_objs "${LIBCMT_MSVC6_RTM_LIB}"
    COMMAND "${CMAKE_COMMAND}" -E rm -f "${PATCHED_LIBCMT}" "${PRUNED_LIBCMT}"
    COMMAND "${CMAKE_COMMAND}" -E copy "${LIBCMT_MSVC6_RTM_LIB}" "${PRUNED_LIBCMT}"
    COMMAND "${CMAKE_AR}" /nologo
      /REMOVE:build\\intel\\mt_obj\\free.obj
      /REMOVE:build\\intel\\mt_obj\\calloc.obj
      /REMOVE:build\\intel\\mt_obj\\malloc.obj
      /REMOVE:build\\intel\\mt_obj\\realloc.obj
      /REMOVE:build\\intel\\mt_obj\\expand.obj
      /REMOVE:build\\intel\\mt_obj\\msize.obj
      /REMOVE:build\\intel\\mt_obj\\sbheap.obj
      /REMOVE:build\\intel\\mt_obj\\heapinit.obj
      /REMOVE:build\\intel\\mt_obj\\heapchk.obj
      /REMOVE:build\\intel\\mt_obj\\heapmin.obj
      /REMOVE:build\\intel\\mt_obj\\new.obj
      /REMOVE:build\\intel\\mt_obj\\delete.obj
      "${PRUNED_LIBCMT}"
    COMMAND "${CMAKE_AR}" /nologo /NODEFAULTLIB:LIBCMT.LIB "/OUT:${PATCHED_LIBCMT}" "${PRUNED_LIBCMT}" $<TARGET_OBJECTS:goldp_libcmt_objs>
    COMMAND_EXPAND_LISTS
    VERBATIM
  )
  add_custom_target(goldp_libcmt_target DEPENDS "${PATCHED_LIBCMT}")
  add_dependencies(goldp goldp_libcmt_target)

  message(STATUS "Original LIBCMT.LIB: ${LIBCMT_MSVC6_RTM_LIB}")
  message(STATUS "Patched LIBCMT.LIB: ${PATCHED_LIBCMT}")

  # Tell the linker to use our patched LIBCMT instead of RTM's
  target_link_options(patched-libcmt INTERFACE "-NODEFAULTLIB:LIBCMT.LIB" "${PATCHED_LIBCMT}")
else()
  message(STATUS "CRT will not be 100% matching")
endif()
