cmake_minimum_required(VERSION 3.25...4.2 FATAL_ERROR)

#MSVC runtime library flags are selected by an abstraction
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
#Visual C++ 6.0->cl version 12.x
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
  common/src/golcollidableentity.cpp
  common/src/golboundingshape.cpp
  common/src/golboundedentity.cpp
  common/src/golcamerabase.cpp
  common/src/golboundingvolume.cpp
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
  common/src/golrenderdevicelight.cpp
  common/src/golsurface.cpp
  common/src/goltexture.cpp
  common/src/goltexturepalette.cpp
  common/src/golpalettedtexture.cpp
  common/src/golrenderdevicematerialcolor.cpp
  common/src/cmbmodelpart.cpp
  common/src/cmbmodelparttrackdata.cpp
  common/src/cmbmodelpartdata.cpp
  common/src/mabmaterialanimation.cpp
  common/src/materialtable.cpp
  common/src/golbillboardmaterialtable.cpp
  common/src/golworldentity.cpp
  common/src/golworldentitygroup.cpp
  common/src/golorientedentity.cpp
  common/src/golviewfrustum.cpp
  common/src/golmodelmaterialtable.cpp
  common/src/golmodelbase.cpp
  common/src/gdbvertexarray.cpp
  common/src/gdbmodelindexarraybase.cpp
  common/src/gdbmodelindexarray.cpp
  common/src/golmodelentity.cpp
  common/src/golanimatedentity.cpp
  common/src/mabmaterialframe.cpp
  common/src/mabmaterialtrack.cpp
  common/src/golmaterial.cpp
  common/src/golmodelrenderstate.cpp
  common/src/golmateriallibrary.cpp
)

#These GOLDP - only files currently need the same inline expansion behavior as common_goldp.
#This might represent another original static library or project grouping; keep the list
#narrow until more source units show the same codegen fingerprint.
set(GOLDP_INLINE_EXPANSION_SOURCES
  GolDP/src/material/golsoftwarematerial.cpp
  GolDP/src/render/goldrawstate.cpp
  GolDP/src/render/golrasterizers1.cpp
  GolDP/src/render/golrasterizers2.cpp
  GolDP/src/image/golimage.cpp
  GolDP/src/image/goltiledtexture.cpp
  GolDP/src/render/golrenderdevice.cpp
  GolDP/src/render/gold3drendersurface.cpp
  GolDP/src/surface/gold3dtexturepalette.cpp
  GolDP/src/surface/goldepthbuffer.cpp
  GolDP/src/font/golfont.cpp
  GolDP/src/surface/gold3dtexture.cpp
  GolDP/src/material/gold3dtexturelist.cpp
  GolDP/src/material/golsoftwaremateriallibrary.cpp
  GolDP/src/mesh/gdbcoloredvertexarraybase.cpp
  GolDP/src/mesh/golmodel.cpp
  GolDP/src/camera/golscenetransformnode.cpp
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

#-- - GolDP.dll target -- -
add_library(goldp SHARED
  GolDP/src/render/golcommondrawstate.cpp
  GolDP/src/render/goldrawstate.cpp
  GolDP/src/render/goldrawdpstate.cpp
  GolDP/src/render/golrasterizers1.cpp
  GolDP/src/render/golrasterizers2.cpp
  GolDP/src/core/goldpexport.cpp
  GolDP/src/world/golworlddatabaseex.cpp
  GolDP/src/device/goldirectdrawpalette.cpp
  GolDP/src/device/goldevicelist.cpp
  GolDP/src/core/main.cpp
  GolDP/src/world/golworlddatabase.cpp
  GolDP/src/scene/golbillboard.cpp
  GolDP/src/scene/golbillboardex.cpp
  GolDP/src/surface/golrendertarget.cpp
  GolDP/src/surface/goldisplaysurface.cpp
  GolDP/src/camera/golcamera.cpp
  GolDP/src/camera/goltransform.cpp
  GolDP/src/device/ddrawutil.cpp
  GolDP/src/material/golsoftwaremateriallibrary.cpp
  GolDP/src/font/golfontlibrary.cpp
  GolDP/src/material/goltexturelist.cpp
  GolDP/src/material/gold3dtexturelist.cpp
  GolDP/src/surface/gold3dtexture.cpp
  GolDP/src/render/golrenderdevice.cpp
  GolDP/src/render/gold3drenderdevice.cpp
  GolDP/src/render/gold3drendersurface.cpp
  GolDP/src/material/golimagedefinitionlist.cpp
  GolDP/src/material/golimagelist.cpp
  GolDP/src/font/golfonttable.cpp
  GolDP/src/font/golfont.cpp
  GolDP/src/surface/golattachedsurface.cpp
  GolDP/src/image/goltiledtexture.cpp
  GolDP/src/image/golimage.cpp
  GolDP/src/material/golsoftwarematerial.cpp
  GolDP/src/surface/goldepthbuffer.cpp
  GolDP/src/render/golsoftwarerenderer.cpp
  GolDP/src/surface/gold3dtexturepalette.cpp
  GolDP/src/mesh/gdbcoloredvertexarraybase.cpp
  GolDP/src/mesh/gdbcoloredvertexarray.cpp
  GolDP/src/mesh/gdbnormalvertexarray.cpp
  GolDP/src/mesh/gdbprelitvertexarray.cpp
  GolDP/src/mesh/gdbuncoloredvertexarray.cpp
  GolDP/src/mesh/golmodel.cpp
  GolDP/src/camera/golscenetransformnode.cpp
  util/decomp.cpp
  $<TARGET_OBJECTS:common_goldp>
)
target_compile_definitions(goldp PRIVATE BUILDING_GOL)
reccmp_add_target(goldp ID GOLDP)

if (MSVC)
  target_sources(goldp PRIVATE GolDP/GolDP.def)
  target_link_options(goldp PRIVATE "-MAP:$<TARGET_FILE_DIR:goldp>/$<TARGET_FILE_BASE_NAME:goldp>.map")
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

#-- - LEGORacers.exe target -- -
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
  LEGORacers/src/input/directinputmanager.cpp
  LEGORacers/src/input/joystickdevice.cpp
  LEGORacers/src/input/keyboarddevice.cpp
  LEGORacers/src/input/mousedevice.cpp
  LEGORacers/src/input/directinputdevice.cpp
  LEGORacers/src/input/inputdevice.cpp
  LEGORacers/src/menu/menumanager.cpp
  LEGORacers/src/race/timeracemanager.cpp
  LEGORacers/src/util/stackoflegou16.cpp
  LEGORacers/src/util/legoeventqueue.cpp
  LEGORacers/src/util/legoeventqueuerigidbody.cpp
  LEGORacers/src/util/legoeventqueuecollision.cpp
  LEGORacers/src/util/legoeventqueueevent.cpp
  LEGORacers/src/menu/menudialogscreen.cpp
  LEGORacers/src/menu/menudialog.cpp
  LEGORacers/src/race/racesession.cpp
  LEGORacers/src/race/racertriggerlist.cpp
  LEGORacers/src/race/triggerlist.cpp
  LEGORacers/src/race/raceeventtable.cpp
  LEGORacers/src/race/events/lapzoneresource.cpp
  LEGORacers/src/race/events/externalforceresource.cpp
  LEGORacers/src/race/events/looktargetresource.cpp
  LEGORacers/src/race/events/materialanimationresource.cpp
  LEGORacers/src/race/events/modeldistanceresource.cpp
  LEGORacers/src/race/events/nodetransformresource.cpp
  LEGORacers/src/race/events/partanimationresource.cpp
  LEGORacers/src/race/events/particleresource.cpp
  LEGORacers/src/race/events/raceeventresource.cpp
  LEGORacers/src/race/events/skystateresource.cpp
  LEGORacers/src/race/events/soundresource.cpp
  LEGORacers/src/race/events/timerresource.cpp
  LEGORacers/src/race/events/colortransformresource.cpp
  LEGORacers/src/race/racetimerlist.cpp
  LEGORacers/src/race/hazardmanager.cpp
  LEGORacers/src/race/hazards/cannonballrainhazard.cpp
  LEGORacers/src/race/hazards/codepuzzlehazard.cpp
  LEGORacers/src/race/hazards/cursedrophazard.cpp
  LEGORacers/src/race/hazards/fallingpillarhazard.cpp
  LEGORacers/src/race/hazards/ghosthazard.cpp
  LEGORacers/src/race/hazards/grabberhazard.cpp
  LEGORacers/src/race/hazards/hammerhazard.cpp
  LEGORacers/src/race/hazards/hazard.cpp
  LEGORacers/src/race/hazards/launcherhazard.cpp
  LEGORacers/src/race/hazards/lavageyserhazard.cpp
  LEGORacers/src/race/hazards/movingobstaclehazard.cpp
  LEGORacers/src/race/hazards/multilauncherhazard.cpp
  LEGORacers/src/race/hazards/oscillatorhazard.cpp
  LEGORacers/src/race/hazards/rockethazard.cpp
  LEGORacers/src/race/hazards/rollingrockhazard.cpp
  LEGORacers/src/race/hazards/smokeventhazard.cpp
  LEGORacers/src/race/hazards/snowfallhazard.cpp
  LEGORacers/src/race/hazards/sphinxhazard.cpp
  LEGORacers/src/race/hazards/sweepcannonhazard.cpp
  LEGORacers/src/race/hazards/triggeredanimationhazard.cpp
  LEGORacers/src/race/hazards/warppadhazard.cpp
  LEGORacers/src/race/raceinputrouter.cpp
  LEGORacers/src/race/racetrailmanager.cpp
  LEGORacers/src/race/racedecalmanager.cpp
  LEGORacers/src/race/racedecaltrail.cpp
  LEGORacers/src/race/racer/drivecontroller.cpp
  LEGORacers/src/race/racecameracontroller.cpp
  LEGORacers/src/race/racer/racercarbody.cpp
  LEGORacers/src/race/racer/racerrigidbody.cpp
  LEGORacers/src/race/surfacetable.cpp
  LEGORacers/src/race/checkpointgraph.cpp
  LEGORacers/src/race/checkpointgraphwalk.cpp
  LEGORacers/src/race/loadingscreen.cpp
  LEGORacers/src/race/targetpointlist.cpp
  LEGORacers/src/race/racesky.cpp
  LEGORacers/src/race/racereset.cpp
  LEGORacers/src/race/racer/racerouterecord.cpp
  LEGORacers/src/race/triggerworld.cpp
  LEGORacers/src/race/racercollisionworlds.cpp
  LEGORacers/src/race/playercontrols.cpp
  LEGORacers/src/race/racesoundsource.cpp
  LEGORacers/src/race/raceforcefeedback.cpp
  LEGORacers/src/race/powerups/racepowerupmanager.cpp
  LEGORacers/src/race/powerups/racepowerupmanagerglobals.cpp
  LEGORacers/src/race/powerups/beammesh.cpp
  LEGORacers/src/race/powerups/tetherprojectile.cpp
  LEGORacers/src/util/carshadowrenderstate.cpp
  LEGORacers/src/race/powerups/powerupprojectile.cpp
  LEGORacers/src/race/powerups/homingprojectile.cpp
  LEGORacers/src/race/raceresourcemanager.cpp
  LEGORacers/src/race/powerups/powerupexplosion.cpp
  LEGORacers/src/race/powerups/powerupaction.cpp
  LEGORacers/src/race/powerups/magnetaction.cpp
  LEGORacers/src/race/powerups/oilslickaction.cpp
  LEGORacers/src/race/powerups/dynamiteaction.cpp
  LEGORacers/src/race/powerups/curseaction.cpp
  LEGORacers/src/race/powerups/cannonballaction.cpp
  LEGORacers/src/race/powerups/grapplinghookaction.cpp
  LEGORacers/src/race/powerups/lightningaction.cpp
  LEGORacers/src/race/powerups/homingmissileaction.cpp
  LEGORacers/src/race/powerups/shieldaction.cpp
  LEGORacers/src/race/powerups/turboaction.cpp
  LEGORacers/src/race/powerups/warpaction.cpp
  LEGORacers/src/race/powerups/pickupbrick.cpp
  LEGORacers/src/race/powerups/colorbrick.cpp
  LEGORacers/src/race/powerups/whitebrick.cpp
  LEGORacers/src/race/racer/carvisuals.cpp
  LEGORacers/src/race/racer/racer.cpp
  LEGORacers/src/race/racestate.cpp
  LEGORacers/src/race/racer/racersoundsource.cpp
  LEGORacers/src/race/racer/racerphysics.cpp
  LEGORacers/src/race/raceroster.cpp
  LEGORacers/src/race/racer/routecursor.cpp
  LEGORacers/src/race/powerups/droppablebrick.cpp
  LEGORacers/src/race/racehud.cpp
  LEGORacers/src/race/racedialog.cpp
  LEGORacers/src/race/circuitracerunner.cpp
  LEGORacers/src/race/circuitstandings.cpp
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
  LEGORacers/src/menu/screens/saverecordcursor.cpp
  LEGORacers/src/menu/screens/racermodelscreenbase.cpp
  LEGORacers/src/menu/screens/racerpickscreenbase.cpp
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
  LEGORacers/src/save/memorycardfile.cpp
  LEGORacers/src/save/gamestate.cpp
  LEGORacers/src/save/savesystem.cpp
  LEGORacers/src/save/memorycardsavegame.cpp
  LEGORacers/src/model/carpartset.cpp
  LEGORacers/src/model/legopiecelibrary.cpp
  LEGORacers/src/menu/runtime/cutsceneparticle.cpp
  LEGORacers/src/menu/runtime/cutsceneanimation.cpp
  LEGORacers/src/menu/runtime/cutsceneanimationevent.cpp
  LEGORacers/src/menu/runtime/cutscenecolorevent.cpp
  LEGORacers/src/menu/runtime/cutsceneimagevisual.cpp
  LEGORacers/src/menu/runtime/cutscenemenuanimationevent.cpp
  LEGORacers/src/menu/runtime/cutscenesoundevent.cpp
  LEGORacers/src/menu/runtime/cutscenestreamingsoundevent.cpp
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
  LEGORacers/src/gol/goltexturelist.cpp
)
if(MSVC)
  target_link_options(legoracers PRIVATE "-MAP:$<TARGET_FILE_DIR:legoracers>/$<TARGET_FILE_BASE_NAME:legoracers>.map")
endif()
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

#-- - Modern compiler compatibility -- -
if (MSVC)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "15")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  endif()
#Visual Studio 2017 version 15.7 needs "/Zc:__cplusplus" for __cplusplus
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
  set_source_files_properties(
    common/src/golmateriallibrary.cpp
    PROPERTIES COMPILE_OPTIONS "/Ob1"
  )

#These flags have been taken from the defaults for a Visual C++ 6.0 project(the compiler the
#game was originally built with) and tweaked slightly to produce more debugging info for reccmp.
#They ensure a recompilation that can be byte / instruction accurate to the original binaries.
  if (TARGET legoracers)
    target_link_options(legoracers PRIVATE "/OPT:NOREF,ICF")
  endif()
  if (TARGET goldp)
    target_link_options(goldp PRIVATE "/OPT:NOREF,ICF")
  endif()

#LegoRacers.exe links to MSVCRT.dll(/ MD), GolDP.dll has embedded its runtime library(/ MT)
  set_property(TARGET legoracers common_legoracers PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  set_property(TARGET goldp common_goldp PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#Embed debug information(/ Z7) for Debug and RelWithDebInfo configuration type
  set_property(TARGET goldp legoracers common_goldp common_legoracers PROPERTY MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")

  set(CMAKE_CXX_FLAGS "/W3 /GX /DWIN32 /D_WINDOWS")
  set(CMAKE_CXX_FLAGS_DEBUG "/Gm /Od /D_DEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/O2 /DNDEBUG")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /DNDEBUG")

  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")

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
    COMMAND reccmp-reccmp --target ${reccmp_id} --diff "${progress_local}"
    DEPENDS "${progress_local}"
  )
  add_dependencies(show-progress show-progress-${reccmp_id})
endforeach()

if(MSVC_FOR_DECOMP)
  add_subdirectory(3rdparty/libcmt)
  target_link_libraries(goldp PRIVATE patched-libcmt)
endif()
