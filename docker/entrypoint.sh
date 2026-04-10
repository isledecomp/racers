#!/usr/bin/env bash

# Cache the ownership status of the passed
# directories before Docker starts messing with it
SRC_DIR_OWNERSHIP="$(stat -c '%u:%g' racers)"
BUILD_DIR_OWNERSHIP="$(stat -c '%u:%g' build)"

# Silence debug warnings in wine (creates noise during compile)
export WINEDEBUG=-all

# Populate the Windows path inside of the wineprefix
# TODO: This is in here because writing to the registry seems
# to fail when performed in the Dockerfile itself; investigate
wine reg ADD 'HKCU\Environment' /v PATH /d 'C:\msvc\vc98\bin;C:\msvc\common\msdev98\bin;C:\msvc\common\tools\winnt;C:\msvc\common\tools;C:\cmake\bin;C:\windows\system32' /f
wine reg ADD 'HKCU\Environment' /v INCLUDE /d 'C:\msvc\vc98\include;C:\msvc\vc98\mfc\include;C:\msvc\vc98\atl\include' /f
wine reg ADD 'HKCU\Environment' /v LIB /d 'C:\msvc\vc98\lib;C:\msvc\vc98\mfc\lib' /f
wine reg ADD 'HKCU\Environment' /v TMP /d 'Z:\build' /f
wine reg ADD 'HKCU\Environment' /v TEMP /d 'Z:\build' /f

# Configure build with CMake
wine cmake -B build racers -G "NMake Makefiles" $CMAKE_FLAGS

# Start compiling LEGO Racers
wine cmake --build build

# Restore directory ownership
chown -R "$SRC_DIR_OWNERSHIP" racers
chown -R "$BUILD_DIR_OWNERSHIP" build
