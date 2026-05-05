#include "ddrawutil.h"

// FUNCTION: GOLDP 0x100030d0
HRESULT LockDirectDrawSurface(
	LPDIRECTDRAWSURFACE4 p_surface,
	LPRECT p_rect,
	DDSURFACEDESC2* p_desc,
	DWORD p_flags,
	HANDLE p_event
)
{
	HRESULT hresult;
	for (;;) {
		hresult = p_surface->Lock(p_rect, p_desc, p_flags, p_event);
		if (hresult != DDERR_SURFACEBUSY && hresult != DDERR_WASSTILLDRAWING) {
			break;
		}
		Sleep(1);
	}
	return hresult;
}
