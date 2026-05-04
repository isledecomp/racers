#ifndef DDRAWUTIL_H
#define DDRAWUTIL_H

#include <ddraw.h>

extern HRESULT LockDirectDrawSurface(
	LPDIRECTDRAWSURFACE4 p_surface,
	LPRECT p_rect,
	DDSURFACEDESC2* p_desc,
	DWORD p_flags,
	HANDLE p_event
);

#endif // DDRAWUTIL_H
