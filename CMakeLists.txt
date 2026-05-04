cmake_minimum_required(VERSION 3.25...4.2 FATAL_ERROR)

# MSVC runtime library flags are selected by an abstraction
cmake_policy(SET CMP0091 NEW)

project(racers CXX)

if (NOT WIN32)
  message(FATAL_ERROR "Windows is the only supported platform (for now...)")
endif()

include(CheckCXXSourceCompiles)
include(CMakeDependentOption)
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

cmake_dependent_option(RACERS_USE_DX6 "Build with internal DirectX 6 SDK" ON "CMAKE_SIZEOF_VOID_P EQUAL 4" OFF)
if (RACERS_USE_DX6)
  include_directories("${PROJECT_SOURCE_DIR}/3rdparty/dx6/inc")
  link_directories("${PROJECT_SOURCE_DIR}/3rdparty/dx6/lib")
  foreach(name d3dim d3drm d3dxof ddraw ddraw16 dinput dplayx dsetup dsound dxguid)
    add_library(${name} IMPORTED UNKNOWN)
    set_property(TARGET ${name} PROPERTY IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/3rdparty/dx6/lib/${name}.lib")
  endforeach()
endif()

set(MSVC_FOR_DECOMP FALSE)
if (MSVC)
  # Visual C++ 6.0 -> cl version 12.x
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "13.0")
    set(MSVC_FOR_DECOMP TRUE)
  endif()
endif()

function(add_cxx_warning WARNING)
  if (RACERS_WERROR)
    set(compiler_option "-Werror=${WARNING}")
  else()
    set(compiler_option "-W${WARNING}")
  endif()
  string(MAKE_C_IDENTIFIER "COMPILER_SUPPORTS${compiler_option}" varname)

  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_FLAGS "${compiler_option} ")
  if (MSVC)
    string(APPEND CMAKE_REQUIRED_FLAGS "/WX")
  else()
    string(APPEND CMAKE_REQUIRED_FLAGS "-Werror")
  endif()
  check_cxx_source_compiles("int main() { return 0; }" ${varname})
  cmake_pop_check_state()

  if (${varname})
    add_compile_options(${compiler_option})
  endif()
endfunction()

message(STATUS "MSVC for decompilation: ${MSVC_FOR_DECOMP}")

option(RACERS_WERROR "Treat warnings as errors" OFF)
option(RACERS_DECOMP_ASSERT "Assert struct size" ${MSVC_FOR_DECOMP})

add_cxx_warning(parentheses)

set(COMMON_SOURCES
  common/src/golnametable.cpp
  common/src/golerror.cpp
  common/src/golfile.cpp
  common/src/golfsutil.cpp
  common/src/golcpu.cpp
  common/src/golhashtable.cpp
  common/src/golstream.cpp
  common/src/golfileparser.cpp
  common/src/golbinparser.cpp
  common/src/goltxtparser.cpp
  common/src/golfilesource.cpp
  common/src/goldirentry.cpp
  common/src/golstring.cpp
  common/src/golstringtable.cpp
)

# These GOLDP-only files currently need the same inline expansion behavior as common_goldp.
# This might represent another original static library or project grouping; keep the list
# narrow until more source units show the same codegen fingerprint.
set(GOLDP_INLINE_EXPANSION_SOURCES
  GolDP/src/amberlensbase0x120.cpp
  GolDP/src/boundingshape0x2c.cpp
  GolDP/src/golfontbase0x40.cpp
  GolDP/src/goldrawstate.cpp
  GolDP/src/silverdune0x30.cpp
  GolDP/src/whitebaffoon0x50.cpp
  GolDP/src/whitefalcon0x140.cpp
  GolDP/src/duskwindbananarelic0x24.cpp
  GolDP/src/falcontextureformat.cpp
  GolDP/src/bronzefalconsurface0x5c.cpp
  GolDP/src/falcondunebag0x10.cpp
  GolDP/src/depthbuffer0x38.cpp
  GolDP/src/golfont0xa0.cpp
  GolDP/src/bronzedune0x4c.cpp
  GolDP/src/purpleribbon0x24.cpp
)

add_library(common_goldp OBJECT ${COMMON_SOURCES})
target_compile_definitions(common_goldp PRIVATE BUILDING_GOL)
target_include_directories(common_goldp PRIVATE
  "${PROJECT_SOURCE_DIR}/GolDP/include"
  "${PROJECT_SOURCE_DIR}/GolDP"
  "${PROJECT_SOURCE_DIR}/common/include"
  "${PROJECT_SOURCE_DIR}/util"
)

add_library(common_legoracers OBJECT ${COMMON_SOURCES})
target_compile_definitions(common_legoracers PRIVATE BUILDING_LEGORACERS)
target_include_directories(common_legoracers PRIVATE
  "${PROJECT_SOURCE_DIR}/LEGORacers/include"
  "${PROJECT_SOURCE_DIR}/LEGORacers"
  "${PROJECT_SOURCE_DIR}/common/include"
  "${PROJECT_SOURCE_DIR}/util"
  "${PROJECT_SOURCE_DIR}/GolDP/include"
)

# --- GolDP.dll target ---
add_library(goldp SHARED
  GolDP/src/bronzedunebag0xc.cpp
  GolDP/src/golcommondrawstate.cpp
  GolDP/src/goldrawstate.cpp
  GolDP/src/goldrawdpstate.cpp
  GolDP/src/goldpexport.cpp
  GolDP/src/fluffygloomkins0x118.cpp
  GolDP/src/pearldew0x0c.cpp
  GolDP/src/goldevicelist.cpp
  GolDP/src/main.cpp
  GolDP/src/zoweeblubberworth0xf0.cpp
  GolDP/src/silverdune0x30.cpp
  GolDP/src/floatyboat0x28.cpp
  GolDP/src/floatypontoon0x4c.cpp
  GolDP/src/floatybarge0x4c.cpp
  GolDP/src/slatepeak0x58.cpp
  GolDP/src/azureridge0x38.cpp
  GolDP/src/amberlensbase0x120.cpp
  GolDP/src/amberlens0x344.cpp
  GolDP/src/falcontextureformat.cpp
  GolDP/src/jadeorbit0x220.cpp
  GolDP/src/ddrawutil.cpp
  GolDP/src/jadeorbitbase0x10.cpp
  GolDP/src/amberhaze0x1c.cpp
  GolDP/src/cinderbasin0x28.cpp
  GolDP/src/golfontbase0x40.cpp
  GolDP/src/magentaribbon0x20.cpp
  GolDP/src/purpleribbon0x24.cpp
  GolDP/src/purpledune0x7c.cpp
  GolDP/src/whitefalcon0x140.cpp
  GolDP/src/whitefalconnode0x18.cpp
  GolDP/src/bronzefalcon0xc8770.cpp
  GolDP/src/bronzefalconsurface0x5c.cpp
  GolDP/src/awakekite0x20.cpp
  GolDP/src/hypnoticnoise0x1c.cpp
  GolDP/src/golfonttable.cpp
  GolDP/src/golfont0xa0.cpp
  GolDP/src/moltenquillphantom0x34.cpp
  GolDP/src/golddune0x38.cpp
  GolDP/src/bronzedune0x4c.cpp
  GolDP/src/whitebaffoon0x50.cpp
  GolDP/src/utopianpan0xa4.cpp
  GolDP/src/duskwindbananarelic0x24.cpp
  GolDP/src/duskwindbananarelic0x30.cpp
  GolDP/src/depthbuffer0x38.cpp
  GolDP/src/softwarerenderer0x58.cpp
  GolDP/src/falcondunebag0x10.cpp
  GolDP/src/boundingshape0x2c.cpp
  util/decomp.cpp
  $<TARGET_OBJECTS:common_goldp>
)
target_compile_definitions(goldp PRIVATE BUILDING_GOL)
reccmp_add_target(goldp ID GOLDP)

if (MSVC)
  target_sources(goldp PRIVATE GolDP/GolDP.def)
endif()

target_include_directories(goldp PRIVATE
  "${PROJECT_SOURCE_DIR}/GolDP/include"
  "${PROJECT_SOURCE_DIR}/GolDP"
  "${PROJECT_SOURCE_DIR}/common/include"
  "${PROJECT_SOURCE_DIR}/util"
)
target_link_libraries(goldp PRIVATE
  ddraw
  dxguid
)

set_property(TARGET goldp PROPERTY OUTPUT_NAME "GolDP")
set_property(TARGET goldp PROPERTY PREFIX "")
set_property(TARGET goldp PROPERTY SUFFIX ".dll")

# --- LEGORacers.exe target ---
add_executable(legoracers WIN32
  LEGORacers/src/cmbmodelpart0x34.cpp
  LEGORacers/src/main.cpp
  LEGORacers/src/cactusinterface0x4.cpp
  LEGORacers/src/legoracers.cpp
  LEGORacers/src/win32golapp.cpp
  LEGORacers/src/audio/musicinstance.cpp
  LEGORacers/src/audio/nullmusicinstance.cpp
  LEGORacers/src/audio/nullmusicgroup.cpp
  LEGORacers/src/audio/audiohelpers.cpp
  LEGORacers/src/audio/directsoundmanager.cpp
  LEGORacers/src/audio/directsoundconversions.cpp
  LEGORacers/src/audio/directmusicinstance.cpp
  LEGORacers/src/audio/directmusicstream.cpp
  LEGORacers/src/audio/musicinstancestate.cpp
  LEGORacers/src/audio/nullstreamingsoundinstance.cpp
  LEGORacers/src/audio/nullsoundgroup.cpp
  LEGORacers/src/audio/nullsoundinstance.cpp
  LEGORacers/src/audio/directsoundgroup.cpp
  LEGORacers/src/audio/directmusicgroup.cpp
  LEGORacers/src/audio/nullsoundmanager.cpp
  LEGORacers/src/audio/musicgroupstate.cpp
  LEGORacers/src/audio/sounddata.cpp
  LEGORacers/src/audio/soundbuffer.cpp
  LEGORacers/src/audio/soundgroupbinding.cpp
  LEGORacers/src/audio/soundinstance.cpp
  LEGORacers/src/audio/spatialsoundinstance.cpp
  LEGORacers/src/audio/soundmanager.cpp
  LEGORacers/src/audio/soundnode.cpp
  LEGORacers/src/audio/streamingsoundinstance.cpp
  LEGORacers/src/input/inputmanager.cpp
  LEGORacers/src/input/directinputmanager.cpp
  LEGORacers/src/input/joystickdevice.cpp
  LEGORacers/src/input/keyboarddevice.cpp
  LEGORacers/src/input/mousedevice.cpp
  LEGORacers/src/input/directinputdevice.cpp
  LEGORacers/src/input/inputdevice.cpp
  LEGORacers/src/menumanager.cpp
  LEGORacers/src/aquacoral0x37b8.cpp
  LEGORacers/src/stackoflegou16.cpp
  LEGORacers/src/crimsonsun0xa4.cpp
  LEGORacers/src/glassblock0x3368.cpp
  LEGORacers/src/glassshard0x3b8.cpp
  LEGORacers/src/glassstream0x94.cpp
  LEGORacers/src/celestialforge0x48.cpp
  LEGORacers/src/opalhaven0xf4.cpp
  LEGORacers/src/cmbmodelpartdata0x18.cpp
  LEGORacers/src/silverhollow0xb8.cpp
  LEGORacers/src/golapp.cpp
  LEGORacers/src/whitefalcon0x140.cpp
  LEGORacers/src/ceruleanknight0x20.cpp
  LEGORacers/src/ceruleanqueen0x58.cpp
  LEGORacers/src/ceruleanemperor0x4c.cpp
  LEGORacers/src/obscurevantage0x58.cpp
  LEGORacers/src/obscureicon0x1a8.cpp
  LEGORacers/src/imaginaryaxe0x36c4.cpp
  LEGORacers/src/imaginarybandsaw0x2228.cpp
  LEGORacers/src/imaginarybelt0x2548.cpp
  LEGORacers/src/imaginarybolt0x4774.cpp
  LEGORacers/src/imaginarybrush0x6410.cpp
  LEGORacers/src/imaginarychisel0x658.cpp
  LEGORacers/src/imaginaryclaw0x15ec.cpp
  LEGORacers/src/imaginarycrowbar0x6750.cpp
  LEGORacers/src/imaginarycube0x3c34.cpp
  LEGORacers/src/imaginarydrill0x2450.cpp
  LEGORacers/src/imaginaryfeather0x658.cpp
  LEGORacers/src/imaginarygear0x4c8c.cpp
  LEGORacers/src/imaginaryhammer0x658.cpp
  LEGORacers/src/imaginarylever0x1d7c.cpp
  LEGORacers/src/imaginarynotion0x290.cpp
  LEGORacers/src/imaginaryorb0x7b0.cpp
  LEGORacers/src/imaginaryplate0x770.cpp
  LEGORacers/src/imaginaryring0x3360.cpp
  LEGORacers/src/imaginaryruler0x2e60.cpp
  LEGORacers/src/imaginaryspool0x2cc4.cpp
  LEGORacers/src/imaginaryspring0x658.cpp
  LEGORacers/src/imaginarytool0x368.cpp
  LEGORacers/src/imaginarywrench0x23bc.cpp
  LEGORacers/src/onyxbreeze0x248.cpp
  LEGORacers/src/onyxcircularbuffer0x1c.cpp
  LEGORacers/src/peridottraceroot0x108.cpp
  LEGORacers/src/peridottrace0x4e0.cpp
  LEGORacers/src/citrinegrove0x1f4c.cpp
  LEGORacers/src/topazburst0x14.cpp
  LEGORacers/src/legopiecelibrary.cpp
  LEGORacers/src/crimsonpebble0x228.cpp
  LEGORacers/src/sapphirereef0x2030.cpp
  LEGORacers/src/verdanttide0x38.cpp
  LEGORacers/src/turquoiseglow0x80.cpp
  LEGORacers/src/aquamarinespirit0x3c.cpp
  LEGORacers/src/championdefinitionlist.cpp
  LEGORacers/src/racedefinitionlist.cpp
  LEGORacers/src/racenamelist.cpp
  LEGORacers/src/menuanimationlist.cpp
  LEGORacers/src/lavendervault0x764.cpp
  LEGORacers/src/garnetflare0x60.cpp
  LEGORacers/src/tanzanitewisp0x88.cpp
  LEGORacers/src/chromespike0x4.cpp
  LEGORacers/src/coppercrest0x40.cpp
  LEGORacers/src/porcelainveil0x50.cpp
  LEGORacers/src/videoplayer.cpp
  LEGORacers/src/guids.cpp
  LEGORacers/racers.rc
  util/decomp.cpp
  $<TARGET_OBJECTS:common_legoracers>
)
target_compile_definitions(legoracers PRIVATE BUILDING_LEGORACERS)
target_compile_definitions(legoracers PRIVATE DIRECTINPUT_VERSION=0x500)
reccmp_add_target(legoracers ID LEGORACERS)

target_include_directories(legoracers PRIVATE
  "${PROJECT_SOURCE_DIR}/LEGORacers/include"
  "${PROJECT_SOURCE_DIR}/LEGORacers"
  "${PROJECT_SOURCE_DIR}/common/include"
  "${PROJECT_SOURCE_DIR}/util"
  "${PROJECT_SOURCE_DIR}/GolDP/include"
)

target_link_libraries(legoracers PRIVATE
  dinput
  dsound
  ole32
  winmm
)

set_property(TARGET legoracers PROPERTY OUTPUT_NAME "LEGORacers")
set_property(TARGET legoracers PROPERTY SUFFIX ".exe")

set_property(SOURCE LEGORacers/racers.rc APPEND PROPERTY OBJECT_DEPENDS "${PROJECT_SOURCE_DIR}/LEGORacers/resources/racers.ico")

add_custom_target(game DEPENDS legoracers goldp)

# --- Modern compiler compatibility ---
if (MSVC)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "15")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  endif()
  # Visual Studio 2017 version 15.7 needs "/Zc:__cplusplus" for __cplusplus
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "19.14.26428")
    add_compile_options(-Zc:__cplusplus)
  endif()
endif()

if (RACERS_DECOMP_ASSERT)
  message(STATUS "Decomp asserts enabled")
  set_property(TARGET goldp legoracers common_goldp common_legoracers APPEND PROPERTY COMPILE_DEFINITIONS "ENABLE_DECOMP_ASSERTS")
endif()

if (MSVC_FOR_DECOMP)
  target_compile_options(common_goldp PRIVATE "/Ob2")

  set_source_files_properties(
    ${GOLDP_INLINE_EXPANSION_SOURCES}
    PROPERTIES COMPILE_OPTIONS "/Ob2"
  )

  # These flags have been taken from the defaults for a Visual C++ 6.0 project (the compiler the
  # game was originally built with) and tweaked slightly to produce more debugging info for reccmp.
  # They ensure a recompilation that can be byte/instruction accurate to the original binaries.
  if (TARGET legoracers)
    target_link_options(legoracers PRIVATE "/OPT:NOREF,ICF")
  endif()
  if (TARGET goldp)
    target_link_options(goldp PRIVATE "/OPT:NOREF,ICF")
  endif()

  # LegoRacers.exe links to MSVCRT.dll (/MD), GolDP.dll has embedded its runtime library (/MT)
  set_property(TARGET legoracers common_legoracers PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  set_property(TARGET goldp common_goldp PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

  # Embed debug information (/Z7) for Debug and RelWithDebInfo configuration type
  set_property(TARGET goldp legoracers common_goldp common_legoracers PROPERTY MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")

  set(CMAKE_CXX_FLAGS "/W3 /GX /D \"WIN32\" /D \"_WINDOWS\"")
  set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Od /D \"_DEBUG\"")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /D \"NDEBUG\"")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 /D \"NDEBUG\"")
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
if (EXISTS "${CLANGFORMAT_BIN}")
  execute_process(COMMAND "${CLANGFORMAT_BIN}" --version
    OUTPUT_VARIABLE "CLANGFORMAT_VERSION_OUTPUT"
    RESULT_VARIABLE "CLANGFORMAT_RESULT"
  )
  if (CLANGFORMAT_RESULT EQUAL 0 AND CLANGFORMAT_VERSION_OUTPUT MATCHES "version ([0-9\\.]+)")
    set(CLANGFORMAT_VERSION "${CMAKE_MATCH_1}")
    set(CLANGFORMAT_VERSION_REQUIRED "17.0")
    message(DEBUG "Found clang-format version ${CLANGFORMAT_VERSION} (needs ${CLANGFORMAT_VERSION_REQUIRED}")
    if (CLANGFORMAT_VERSION VERSION_GREATER_EQUAL "${CLANGFORMAT_VERSION_REQUIRED}")
      file(GLOB_RECURSE racers_sources CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/LEGORacers/*.cpp"
        "${PROJECT_SOURCE_DIR}/LEGORacers/*.h"
        "${PROJECT_SOURCE_DIR}/GolDP/*.cpp"
        "${PROJECT_SOURCE_DIR}/GolDP/*.h"
        "${PROJECT_SOURCE_DIR}/common/*.cpp"
        "${PROJECT_SOURCE_DIR}/common/*.h"
      )
      string(REPLACE ";" "\n" racers_sources_lines "${racers_sources}")
      file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/racers_sources.txt" "${racers_sources_lines}\n")
      add_custom_target(clang-format ${CLANGFORMAT_BIN} -i "--files=${CMAKE_CURRENT_BINARY_DIR}/racers_sources.txt")
    endif()
  endif()
endif()

find_library(CLANG_LIBRARY NAMES "clang" DOC "libclang from host (NOT target) system")
find_package(Python3 COMPONENTS Interpreter QUIET)
if (CLANG_LIBRARY AND TARGET Python3::Interpreter)
  add_custom_target(ncc
    Python3::Interpreter "${PROJECT_SOURCE_DIR}/tools/ncc/ncc.py"
      --clang-lib "${CLANG_LIBRARY}"
      --recurse
      --style tools/ncc/ncc.style
      --skip tools/ncc/skip.yml
      --definition DEFINE_GUID PASCAL WINAPI FAR BOOL CALLBACK HWND__=HWND
      --include
        util
        LEGORacers/include
        LEGORacers
        GolDP/include
        GolDP
        common/include
        common
      --path LEGORacers GolDP common
    COMMENT "Verifying naming conventions (ncc)"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  )
endif()

reccmp_configure()

set(RELEASE_URL "https://github.com/isledecomp/racers/releases/download/continuous")
add_custom_target(download-master-progress)
add_custom_target(show-progress)

get_property(RECCMP_TARGETS GLOBAL PROPERTY RECCMP_TARGETS)
foreach(target ${RECCMP_TARGETS})
  get_property(reccmp_id TARGET "${target}" PROPERTY INTERFACE_RECCMP_ID)

  set(progress_local "${PROJECT_BINARY_DIR}/${reccmp_id}-progress-master.json")
  set(download_command COMMAND "${CMAKE_COMMAND}"
    "-DURL=${RELEASE_URL}"
    "-DFILENAME_ONLINE=${reccmp_id}PROGRESS.json"
    "-DFILENAME_LOCAL=${progress_local}"
    "-P" "${PROJECT_SOURCE_DIR}/cmake/download-file.cmake"
  )
  add_custom_target(download-master-progress-${reccmp_id} ${download_command})
  add_dependencies(download-master-progress download-master-progress-${reccmp_id})
  add_custom_command(OUTPUT "${progress_local}" COMMAND ${download_command})
  add_custom_target(show-progress-${reccmp_id}
    COMMENT "Compare progress of ${reccmp_id} with current git master"
    COMMAND reccmp-reccmp --target ${reccmp_id} --nolib --diff "${progress_local}"
    DEPENDS "${progress_local}"
  )
  add_dependencies(show-progress show-progress-${reccmp_id})
endforeach()
