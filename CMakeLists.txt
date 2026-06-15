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
  common/src/golsurfaceformat.cpp
  common/src/golnametable.cpp
  common/src/golerror.cpp
  common/src/golfile.cpp
  common/src/golfsutil.cpp
  common/src/golimgfile.cpp
  common/src/goltgafile.cpp
  common/src/golbmpfile.cpp
  common/src/golimgfilewriter.cpp
  common/src/golbmpwriterfile.cpp
  common/src/goldecompress.cpp
  common/src/golcpu.cpp
  common/src/golhashtable.cpp
  common/src/golstream.cpp
  common/src/golfileparser.cpp
  common/src/golbinparser.cpp
  common/src/golconstants.cpp
  common/src/goltxtparser.cpp
  common/src/golfilesource.cpp
  common/src/goldirentry.cpp
  common/src/golmath.cpp
  common/src/golstring.cpp
  common/src/golstringtable.cpp
  common/src/golfontbase.cpp
  common/src/goltransformbase.cpp
  common/src/golscenenode.cpp
  common/src/whitefalcon0x140light.cpp
  common/src/whitefalcon0x140materialcolor.cpp
  common/src/cmbmodelpart0x34.cpp
  common/src/cmbmodelpartdata0x18.cpp
  common/src/cmbmodelpartdata0x28.cpp
  common/src/mabmaterialanimation0x14.cpp
  common/src/materialtable0x0c.cpp
  common/src/golbillboardfield0x2c.cpp
  common/src/golworldentity.cpp
  common/src/golworldentitygroup0x38.cpp
  common/src/golorientedentity.cpp
  common/src/golmodelentity.cpp
  common/src/golanimatedentity.cpp
  common/src/mabmaterialanimationitem0x8.cpp
  common/src/mabmaterialanimationitem0x18.cpp
  common/src/duskwindbananarelic0x24.cpp
)

# These GOLDP-only files currently need the same inline expansion behavior as common_goldp.
# This might represent another original static library or project grouping; keep the list
# narrow until more source units show the same codegen fingerprint.
set(GOLDP_INLINE_EXPANSION_SOURCES
  GolDP/src/camera/golcamerabase.cpp
  GolDP/src/bounds/golboundingshape.cpp
  GolDP/src/material/duskwindbananarelic0x30.cpp
  GolDP/src/render/goldrawstate.cpp
  GolDP/src/surface/silverdune0x30.cpp
  GolDP/src/image/utopianpan0xa4.cpp
  GolDP/src/image/whitebaffoon0x50.cpp
  GolDP/src/render/golrenderdevice.cpp
  GolDP/src/render/gold3drendersurface.cpp
  GolDP/src/surface/falcondunebag0x10.cpp
  GolDP/src/surface/goldepthbuffer.cpp
  GolDP/src/font/golfont.cpp
  GolDP/src/surface/bronzedune0x4c.cpp
  GolDP/src/surface/purpledune0x7c.cpp
  GolDP/src/material/purpleribbon0x24.cpp
  GolDP/src/material/amberhaze0x20.cpp
  GolDP/src/mesh/gdbvertexarray0xc.cpp
  GolDP/src/mesh/gdbcommonvertexarray0x1c.cpp
  GolDP/src/mesh/igdbmodelindexarray0x8.cpp
  GolDP/src/mesh/gdbmodelindexarray0xc.cpp
  GolDP/src/mesh/golmodelmaterialtable.cpp
  GolDP/src/mesh/golmodel.cpp
  GolDP/src/camera/golscenetransformnode.cpp
  GolDP/src/surface/bronzedunebag0xc.cpp
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
  GolDP/src/surface/bronzedunebag0xc.cpp
  GolDP/src/render/golcommondrawstate.cpp
  GolDP/src/render/goldrawstate.cpp
  GolDP/src/render/goldrawdpstate.cpp
  GolDP/src/core/goldpexport.cpp
  GolDP/src/world/golworlddatabaseex.cpp
  GolDP/src/device/goldirectdrawpalette.cpp
  GolDP/src/device/goldevicelist.cpp
  GolDP/src/core/main.cpp
  GolDP/src/world/golworlddatabase.cpp
  GolDP/src/surface/silverdune0x30.cpp
  GolDP/src/scene/golbillboard.cpp
  GolDP/src/scene/golbillboardex.cpp
  GolDP/src/surface/slatepeak0x58.cpp
  GolDP/src/surface/azureridge0x38.cpp
  GolDP/src/camera/golcamerabase.cpp
  GolDP/src/camera/golcamera.cpp
  GolDP/src/camera/goltransform.cpp
  GolDP/src/device/ddrawutil.cpp
  GolDP/src/material/golmateriallibrary.cpp
  GolDP/src/material/amberhaze0x20.cpp
  GolDP/src/font/golfontlibrary.cpp
  GolDP/src/material/goltexturelist.cpp
  GolDP/src/material/purpleribbon0x24.cpp
  GolDP/src/surface/purpledune0x7c.cpp
  GolDP/src/render/golrenderdevice.cpp
  GolDP/src/render/gold3drenderdevice.cpp
  GolDP/src/render/gold3drendersurface.cpp
  GolDP/src/material/awakekite0x20.cpp
  GolDP/src/material/golimagelist.cpp
  GolDP/src/font/golfonttable.cpp
  GolDP/src/font/golfont.cpp
  GolDP/src/surface/moltenquillphantom0x34.cpp
  GolDP/src/surface/golddune0x38.cpp
  GolDP/src/surface/bronzedune0x4c.cpp
  GolDP/src/image/whitebaffoon0x50.cpp
  GolDP/src/image/utopianpan0xa4.cpp
  GolDP/src/material/duskwindbananarelic0x30.cpp
  GolDP/src/surface/goldepthbuffer.cpp
  GolDP/src/render/golsoftwarerenderer.cpp
  GolDP/src/surface/falcondunebag0x10.cpp
  GolDP/src/bounds/golboundingshape.cpp
  GolDP/src/mesh/golmodelmaterialtable.cpp
  GolDP/src/mesh/golmodelbase.cpp
  GolDP/src/mesh/gdbvertexarray0xc.cpp
  GolDP/src/mesh/gdbcommonvertexarray0x1c.cpp
  GolDP/src/mesh/gdbvertexarraytypetwo0x20.cpp
  GolDP/src/mesh/gdbvertexarraytypeone0x1c.cpp
  GolDP/src/mesh/gdbvertexarraytypethree0x20.cpp
  GolDP/src/mesh/gdbvertexarraymistery0x1c.cpp
  GolDP/src/mesh/golmodel.cpp
  GolDP/src/mesh/igdbmodelindexarray0x8.cpp
  GolDP/src/mesh/gdbmodelindexarray0xc.cpp
  GolDP/src/camera/golscenetransformnode.cpp
  GolDP/src/bounds/golboundingvolume.cpp
  GolDP/src/scene/golboundedentity.cpp
  GolDP/src/scene/golcollidableentity.cpp
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
  LEGORacers/src/app/main.cpp
  LEGORacers/src/app/gamemain.cpp
  LEGORacers/src/app/golappeventhandler.cpp
  LEGORacers/src/app/legoracers.cpp
  LEGORacers/src/app/win32golapp.cpp
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
  LEGORacers/src/menu/menumanager.cpp
  LEGORacers/src/race/racemoderunner.cpp
  LEGORacers/src/util/stackoflegou16.cpp
  LEGORacers/src/util/marblepath0x114.cpp
  LEGORacers/src/menu/menudialogscreen.cpp
  LEGORacers/src/menu/menudialog.cpp
  LEGORacers/src/race/racesession.cpp
  LEGORacers/src/race/racesessionfield0x2080.cpp
  LEGORacers/src/race/racesessionfield0x2098.cpp
  LEGORacers/src/race/racesessionfield0x213c.cpp
  LEGORacers/src/race/racesessionfield0x2148.cpp
  LEGORacers/src/race/racesessionfield0x23c.cpp
  LEGORacers/src/race/racesessionfield0x27c8.cpp
  LEGORacers/src/race/racesessionfield0x27d4.cpp
  LEGORacers/src/race/racesessionfield0x27d4field0x004.cpp
  LEGORacers/src/race/racestatefield0xc70.cpp
  LEGORacers/src/race/racesessionfield0x2ad4.cpp
  LEGORacers/src/race/racesessionfield0x27e0.cpp
  LEGORacers/src/race/racesessionfield0x27f4.cpp
  LEGORacers/src/race/racesessionfield0x280c.cpp
  LEGORacers/src/race/racesessionfield0x2804.cpp
  LEGORacers/src/race/racesessionfield0x2f90.cpp
  LEGORacers/src/race/racesessionfield0x30c4.cpp
  LEGORacers/src/race/racesessionfield0x3104.cpp
  LEGORacers/src/race/racesessionfield0x32b4.cpp
  LEGORacers/src/race/racesessionfield0x32b4field0x004.cpp
  LEGORacers/src/race/racesessionfield0x32b4field0x058.cpp
  LEGORacers/src/race/racesessionfield0x32c4.cpp
  LEGORacers/src/race/racesessionfield0x258.cpp
  LEGORacers/src/race/racesessionfield0x3300.cpp
  LEGORacers/src/race/racesessionfield0x340.cpp
  LEGORacers/src/race/racesessionfield0x6dc.cpp
  LEGORacers/src/race/racesessionfield0x6dcfield0x170.cpp
  LEGORacers/src/race/racesessionfield0x6dcfield0x3c.cpp
  LEGORacers/src/race/racesessionfield0x6dcfield0x270.cpp
  LEGORacers/src/race/racesessionfield0x6dcresources.cpp
  LEGORacers/src/race/racestate.cpp
  LEGORacers/src/race/racestatefield0x00c.cpp
  LEGORacers/src/race/racestatefield0x004.cpp
  LEGORacers/src/race/racestatefield0x0f0.cpp
  LEGORacers/src/race/racestatefield0x2a0.cpp
  LEGORacers/src/race/racestatefield0xd5c.cpp
  LEGORacers/src/race/racestatefield0xc70field0x000.cpp
  LEGORacers/src/race/racestatefield0xc70field0x050.cpp
  LEGORacers/src/race/timeracemanager.cpp
  LEGORacers/src/race/cobalttrail0x140.cpp
  LEGORacers/src/race/slatebridge0x68.cpp
  LEGORacers/src/race/circuitracerunner.cpp
  LEGORacers/src/race/circuitstandings.cpp
  LEGORacers/src/util/amethystbreeze0x104.cpp
  LEGORacers/src/app/golapp.cpp
  LEGORacers/src/gol/golrenderdevice.cpp
  LEGORacers/src/model/golworlddatabase.cpp
  LEGORacers/src/menu/style/menuresourcetable.cpp
  LEGORacers/src/menu/style/menuinputbindingtable.cpp
  LEGORacers/src/menu/style/menustyletable.cpp
  LEGORacers/src/menu/widgets/menuimage.cpp
  LEGORacers/src/menu/widgets/menuclippedimage.cpp
  LEGORacers/src/menu/widgets/menustaticwidget.cpp
  LEGORacers/src/menu/widgets/menuselector.cpp
  LEGORacers/src/menu/widgets/menucarousel.cpp
  LEGORacers/src/menu/widgets/optionsrow.cpp
  LEGORacers/src/menu/widgets/menubutton.cpp
  LEGORacers/src/menu/widgets/menuicon.cpp
  LEGORacers/src/menu/widgets/menuhotspotbutton.cpp
  LEGORacers/src/menu/widgets/menusceneelement.cpp
  LEGORacers/src/menu/widgets/menutextentry.cpp
  LEGORacers/src/menu/widgets/menutextfield.cpp
  LEGORacers/src/menu/widgets/menuracercarousel.cpp
  LEGORacers/src/menu/widgets/menucolorbox.cpp
  LEGORacers/src/menu/widgets/menuframedsceneview.cpp
  LEGORacers/src/menu/widgets/menusceneview.cpp
  LEGORacers/src/menu/widgets/menuframe.cpp
  LEGORacers/src/menu/widgets/menuwidget.cpp
  LEGORacers/src/menu/widgets/menumodelcarousel.cpp
  LEGORacers/src/menu/widgets/menutriangle.cpp
  LEGORacers/src/menu/screens/editcarscreen.cpp
  LEGORacers/src/menu/screens/circuitracescreen.cpp
  LEGORacers/src/menu/screens/pickmemorycardscreen.cpp
  LEGORacers/src/menu/screens/editdriverscreen.cpp
  LEGORacers/src/menu/screens/garagescreen.cpp
  LEGORacers/src/menu/screens/menuscenescreen.cpp
  LEGORacers/src/menu/screens/scenewidget.cpp
  LEGORacers/src/menu/screens/racermodelslot.cpp
  LEGORacers/src/menu/screens/racerunlockstate.cpp
  LEGORacers/src/menu/screens/racermodelscreenbase.cpp
  LEGORacers/src/menu/screens/racerpickscreenbase.cpp
  LEGORacers/src/gol/golcamerabase.cpp
  LEGORacers/src/menu/runtime/cutscenedefinition.cpp
  LEGORacers/src/menu/screens/picklanguagescreen.cpp
  LEGORacers/src/menu/screens/optionsscreenbase.cpp
  LEGORacers/src/menu/screens/optionsscreen.cpp
  LEGORacers/src/menu/screens/carbuildscreen.cpp
  LEGORacers/src/menu/screens/mainmenuscreen.cpp
  LEGORacers/src/menu/screens/mainmenumodelslot.cpp
  LEGORacers/src/menu/widgets/menutextlabel.cpp
  LEGORacers/src/menu/widgets/menutextbutton.cpp
  LEGORacers/src/menu/screens/mainintroscreen.cpp
  LEGORacers/src/menu/screens/pickracerscreen.cpp
  LEGORacers/src/menu/screens/singleraceselectbase.cpp
  LEGORacers/src/menu/screens/splashcinematicscreen.cpp
  LEGORacers/src/menu/screens/saveloadscreen.cpp
  LEGORacers/src/menu/screens/menuscreen.cpp
  LEGORacers/src/menu/screens/awardcinematicscreen.cpp
  LEGORacers/src/menu/screens/sceneentitygroup.cpp
  LEGORacers/src/menu/screens/newracerscreen.cpp
  LEGORacers/src/menu/screens/controlconfigscreen.cpp
  LEGORacers/src/menu/screens/driverlicensescreen.cpp
  LEGORacers/src/menu/screens/racemodesetupscreen.cpp
  LEGORacers/src/menu/screens/carbuildscreenbase.cpp
  LEGORacers/src/menu/screens/carmodelscreenbase.cpp
  LEGORacers/src/menu/screens/carpartplacement.cpp
  LEGORacers/src/menu/screens/multiplayerpickscreen.cpp
  LEGORacers/src/menu/screens/circuitselectscreen.cpp
  LEGORacers/src/menu/screens/menugamescreen.cpp
  LEGORacers/src/menu/screens/buttonbindingtable.cpp
  LEGORacers/src/menu/menuinputhandler.cpp
  LEGORacers/src/input/inputeventqueue.cpp
  LEGORacers/src/save/saveslotbase.cpp
  LEGORacers/src/save/savedirectory.cpp
  LEGORacers/src/save/saverecordlist.cpp
  LEGORacers/src/save/savegame.cpp
  LEGORacers/src/save/savegamefile.cpp
  LEGORacers/src/save/memorycardfilebase.cpp
  LEGORacers/src/save/gamestate.cpp
  LEGORacers/src/save/savesystem.cpp
  LEGORacers/src/model/carpartset.cpp
  LEGORacers/src/model/legopiecelibrary.cpp
  LEGORacers/src/menu/runtime/cutsceneparticle.cpp
  LEGORacers/src/menu/runtime/cutsceneplayer.cpp
  LEGORacers/src/menu/runtime/cutscenetextvisual.cpp
  LEGORacers/src/menu/runtime/cutscenevisual.cpp
  LEGORacers/src/model/carbuildmodel.cpp
  LEGORacers/src/model/carbuildpiecelist.cpp
  LEGORacers/src/model/legocolortable.cpp
  LEGORacers/src/racer/drivercosmetictable.cpp
  LEGORacers/src/racer/chassismodeltable.cpp
  LEGORacers/src/racer/carpartcarousel.cpp
  LEGORacers/src/race/data/championdefinitionlist.cpp
  LEGORacers/src/race/data/circuitdefinitionlist.cpp
  LEGORacers/src/race/data/racenamelist.cpp
  LEGORacers/src/menu/menuanimationlist.cpp
  LEGORacers/src/racer/driverpartcatalog.cpp
  LEGORacers/src/model/gdbpartdefinition.cpp
  LEGORacers/src/model/gdbpartlibrary.cpp
  LEGORacers/src/model/gdbpartfacegroup.cpp
  LEGORacers/src/model/gdbpartvertexpool.cpp
  LEGORacers/src/model/gdbpositionvertexpool.cpp
  LEGORacers/src/racer/driverpartresources.cpp
  LEGORacers/src/racer/drivermodelbuilder.cpp
  LEGORacers/src/racer/driverheadbuilder.cpp
  LEGORacers/src/util/particlesystem.cpp
  LEGORacers/src/util/particle.cpp
  LEGORacers/src/menu/menuscreenfactory.cpp
  LEGORacers/src/menu/menuinputdispatcher.cpp
  LEGORacers/src/menu/style/sharedmenustyletable.cpp
  LEGORacers/src/video/videoplayer.cpp
  LEGORacers/src/app/guids.cpp
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
