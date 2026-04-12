cmake_minimum_required(VERSION 3.15...4.2 FATAL_ERROR)

# MSVC runtime library flags are selected by an abstraction
cmake_policy(SET CMP0091 NEW)

project(racers CXX)

include(CheckCXXSourceCompiles)
include(CMakePushCheckState)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/reccmp.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
option(ENABLE_CLANG_TIDY "Enable clang-tidy")
if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_BIN NAMES "clang-tidy")
  set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_BIN}")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_BIN}")
endif()

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit LEGO Racers")
if (NOT bits EQUAL 32)
  message(WARNING "Only 32-bit executables are supported")
endif()

set(MSVC_FOR_DECOMP FALSE)
if (MSVC)
  # Visual C++ 6.0 -> cl version 12.x
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "13.0")
    set(MSVC_FOR_DECOMP TRUE)
  endif()
endif()

function(add_cxx_warning WARNING)
  if(RACERS_WERROR)
    set(compiler_option "-Werror=${WARNING}")
  else()
    set(compiler_option "-W${WARNING}")
  endif()
  string(MAKE_C_IDENTIFIER "COMPILER_SUPPORTS${compiler_option}" varname)

  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_FLAGS "${compiler_option} ")
  if(MSVC)
    string(APPEND CMAKE_REQUIRED_FLAGS "/WX")
  else()
    string(APPEND CMAKE_REQUIRED_FLAGS "-Werror")
  endif()
  check_cxx_source_compiles("int main() { return 0; }" ${varname})
  cmake_pop_check_state()

  if(${varname})
    add_compile_options(${compiler_option})
  endif()
endfunction()

message(STATUS "MSVC for decompilation: ${MSVC_FOR_DECOMP}")

option(RACERS_WERROR "Treat warnings as errors" OFF)
option(RACERS_DECOMP_ASSERT "Assert struct size" ${MSVC_FOR_DECOMP})

add_cxx_warning(parentheses)

# --- GolDP.dll target ---
add_library(goldp SHARED
  util/decomp.cpp
  GolDP/src/adapter.cpp
  GolDP/src/goldpexport.cpp
  GolDP/src/main.cpp
)
reccmp_add_target(goldp ID GOLDP)

if (MSVC)
  target_sources(goldp PRIVATE GolDP/GolDP.def)
endif()

target_include_directories(goldp PRIVATE
  "${PROJECT_SOURCE_DIR}/GolDP/include"
  "${PROJECT_SOURCE_DIR}/GolDP"
  "${PROJECT_SOURCE_DIR}/util"
)

set_property(TARGET goldp PROPERTY OUTPUT_NAME "GolDP")
set_property(TARGET goldp PROPERTY PREFIX "")
set_property(TARGET goldp PROPERTY SUFFIX ".dll")

# --- LEGORacers.exe target ---
add_executable(legoracers WIN32
  util/decomp.cpp
  LEGORacers/src/main.cpp
  LEGORacers/src/cactusinterface0x4.cpp
  LEGORacers/src/neoncactus0x1d6c.cpp
  LEGORacers/src/ironflame0x944.cpp
  LEGORacers/src/indigostar0x18.cpp
  LEGORacers/src/amberwolf0x98.cpp
  LEGORacers/src/jadestorm0x0c.cpp
  LEGORacers/src/amberleaf0x10.cpp
  LEGORacers/src/rubyhaze0x08.cpp
  LEGORacers/src/crimsonray0x20.cpp
  LEGORacers/src/goldenoak0x128.cpp
  LEGORacers/src/frostpetal0x34.cpp
  LEGORacers/src/emberdust0x28.cpp
  LEGORacers/src/cobaltmist0x30.cpp
  LEGORacers/src/tealpulse0x24.cpp
  LEGORacers/src/crimsonforge0x800.cpp
  LEGORacers/src/coralbeam0x30.cpp
  LEGORacers/src/mossglow0x30.cpp
  LEGORacers/src/violetshard0x34.cpp
  LEGORacers/src/azureclip0x24.cpp
  LEGORacers/src/jaspercore0xf0.cpp
  LEGORacers/src/opalvault0xf0.cpp
  LEGORacers/src/silvernode0x50.cpp
  LEGORacers/src/imaginarynotion0x280.cpp
  LEGORacers/src/imaginarytool0x368.cpp
  LEGORacers/src/imaginarywrench0x23bc.cpp
  LEGORacers/racers.rc
)
reccmp_add_target(legoracers ID LEGORACERS)

target_include_directories(legoracers PRIVATE
  "${PROJECT_SOURCE_DIR}/LEGORacers/include"
  "${PROJECT_SOURCE_DIR}/LEGORacers"
  "${PROJECT_SOURCE_DIR}/util"
)

target_link_libraries(legoracers PRIVATE
  ole32
  winmm
)
add_dependencies(legoracers goldp)

set_property(TARGET legoracers PROPERTY OUTPUT_NAME "LEGORacers")
set_property(TARGET legoracers PROPERTY SUFFIX ".exe")

set_property(SOURCE LEGORacers/racers.rc APPEND PROPERTY OBJECT_DEPENDS "${PROJECT_SOURCE_DIR}/LEGORacers/resources/racers.ico")

# --- Modern compiler compatibility ---
if (MSVC)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "15")
    set_property(TARGET goldp legoracers APPEND PROPERTY COMPILE_DEFINITIONS "_CRT_SECURE_NO_WARNINGS")
  endif()
  # Visual Studio 2017 version 15.7 needs "/Zc:__cplusplus" for __cplusplus
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.14.26428")
    set_property(TARGET goldp legoracers APPEND PROPERTY COMPILE_OPTIONS "-Zc:__cplusplus")
  endif()
endif()

if (RACERS_DECOMP_ASSERT)
  message(STATUS "Decomp asserts enabled")
  set_property(TARGET goldp legoracers APPEND PROPERTY COMPILE_DEFINITIONS "ENABLE_DECOMP_ASSERTS")
endif()

if (MSVC_FOR_DECOMP)
  # These flags have been taken from the defaults for a Visual C++ 6.0 project (the compiler the
  # game was originally built with) and tweaked slightly to produce more debugging info for reccmp.
  # They ensure a recompilation that can be byte/instruction accurate to the original binaries.
  if (TARGET legoracers)
    target_link_options(legoracers PRIVATE "/OPT:NOREF,ICF")
  endif()
  if (TARGET goldp)
    target_link_options(goldp PRIVATE "/OPT:NOREF,ICF")
  endif()

  set_property(TARGET legoracers goldp PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

  set(CMAKE_CXX_FLAGS "/W3 /GX /D \"WIN32\" /D \"_WINDOWS\"")
  set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Zi /Od /D \"_DEBUG\"")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /D \"NDEBUG\"")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Zi /O2 /D \"NDEBUG\"")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /D \"NDEBUG\"")

  set(CMAKE_EXE_LINKER_FLAGS "/machine:I386")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/incremental:no")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/incremental:no")

  set(CMAKE_STATIC_LINKER_FLAGS "/machine:I386")

  set(CMAKE_SHARED_LINKER_FLAGS "/machine:I386")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/incremental:yes /debug")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/incremental:no")
  set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug")
  set(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL "/incremental:no")
endif()

find_program(CLANGFORMAT_BIN NAMES clang-format)
if(EXISTS "${CLANGFORMAT_BIN}")
  execute_process(COMMAND "${CLANGFORMAT_BIN}" --version
    OUTPUT_VARIABLE "CLANGFORMAT_VERSION_OUTPUT"
    RESULT_VARIABLE "CLANGFORMAT_RESULT"
  )
  if(CLANGFORMAT_RESULT EQUAL 0 AND CLANGFORMAT_VERSION_OUTPUT MATCHES "version ([0-9\\.]+)")
    set(CLANGFORMAT_VERSION "${CMAKE_MATCH_1}")
    set(CLANGFORMAT_VERSION_REQUIRED "17.0")
    message(DEBUG "Found clang-format version ${CLANGFORMAT_VERSION} (needs ${CLANGFORMAT_VERSION_REQUIRED}")
    if(CLANGFORMAT_VERSION VERSION_GREATER_EQUAL "${CLANGFORMAT_VERSION_REQUIRED}")
      file(GLOB_RECURSE racers_sources
        "${PROJECT_SOURCE_DIR}/LEGORacers/*.cpp"
        "${PROJECT_SOURCE_DIR}/LEGORacers/*.h"
        "${PROJECT_SOURCE_DIR}/GolDP/*.cpp"
        "${PROJECT_SOURCE_DIR}/GolDP/*.h"
      )
      string(REPLACE ";" "\n" racers_sources_lines "${racers_sources}")
      file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/racers_sources.txt" "${racers_sources_lines}\n")
      add_custom_target(clang-format ${CLANGFORMAT_BIN} -i "--files=${CMAKE_CURRENT_BINARY_DIR}/racers_sources.txt")
    endif()
  endif()
endif()

reccmp_configure()
