#define INITGUID

// Forward declarations for DirectDraw7 types referenced by modern strmif.h
// (MSVC 6.0's strmif.h doesn't require these)
struct IDirectDraw7;
struct IDirectDrawSurface7;
typedef struct IDirectDraw7* LPDIRECTDRAW7;
typedef struct IDirectDrawSurface7* LPDIRECTDRAWSURFACE7;

#include <windows.h>
// <windows.h> must be defined first for MSVC6

#include <control.h>
#include <dinput.h>
#include <strmif.h>
#include <uuids.h>
#ifndef __MINGW32__
// mingw32's headers define this variable. MSVC's headers do not.
DEFINE_GUID(IID_IGraphBuilder, 0x56a868a9L, 0x0ad4, 0x11ce, 0xb0, 0x3a, 0x00, 0x20, 0xaf, 0x0b, 0xa7, 0x70);
#endif
