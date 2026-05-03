#include "goldrawdpstate.h"

#include "golerror.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(GolDrawDPState, 0xc8ac4)

// FUNCTION: GOLDP 0x10001000
GolDrawDPState::GolDrawDPState()
{
	m_hWnd = NULL;
	m_ddraw = NULL;
	m_ddraw4 = NULL;
	m_d3d3 = NULL;
	m_driverName = NULL;
	m_deviceName = NULL;
	m_validGuid = FALSE;
	::memset(&m_ddrawCaps, 0, sizeof(m_ddrawCaps));
	m_ddrawCaps.dwSize = sizeof(m_ddrawCaps);
	::memset(&m_deviceDesc, 0, sizeof(m_deviceDesc));
	m_device = NULL;
	::memset(&m_deviceGuid, 0, sizeof(m_deviceGuid));
	m_unk0x2c0 = 0;
	m_currentRenderer = &m_unk0x354;
	m_unk0x14 = &m_unk0x2fc;
}

// FUNCTION: GOLDP 0x10001110
GolDrawDPState::~GolDrawDPState()
{
	if (m_driverName != NULL) {
		delete[] m_driverName;
		m_driverName = NULL;
	}

	if (m_deviceName != NULL) {
		delete[] m_deviceName;
		m_deviceName = NULL;
	}

	GolCommonDrawState::VTable0x48();
	ReleaseDDraw();
}

// FUNCTION: GOLDP 0x100011e0
void GolDrawDPState::VTable0x08(HWND p_hWnd)
{
	m_hWnd = p_hWnd;
}

// FUNCTION: GOLDP 0x100011f0
void GolDrawDPState::VTable0x48()
{
	GolCommonDrawState::VTable0x48();
	ReleaseDDraw();
}

// FUNCTION: GOLDP 0x10001210
void GolDrawDPState::ReleaseDDraw()
{
	if (m_d3d3 != NULL) {
		m_d3d3->Release();
	}

	if (m_ddraw4 != NULL) {
		if (m_hWnd != NULL) {
			m_ddraw4->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
		}
		m_ddraw4->Release();
	}

	if (m_ddraw != NULL) {
		m_ddraw->Release();
	}

	m_deviceList.Clear();
	m_ddraw = NULL;
	m_ddraw4 = NULL;
	m_d3d3 = NULL;
	::memset(&m_ddrawCaps, 0, sizeof(m_ddrawCaps));
	m_ddrawCaps.dwSize = sizeof(m_ddrawCaps);
	::memset(&m_deviceDesc, 0, sizeof(m_deviceDesc));
	::memset(&m_deviceGuid, 0, sizeof(m_deviceGuid));
	m_unk0x2c0 = 0;
}

// FUNCTION: GOLDP 0x100012b0
void GolDrawDPState::VTable0x50()
{
	m_flags &= ~(c_flagBit12 | c_flagBit11 | c_flagBit10 | c_flagBit9);
	GolCommonDrawState::VTable0x50();
	ReleaseDDraw();
}

// FUNCTION: GOLDP 0x100012d0
LegoS32 GolDrawDPState::VTable0x00()
{
	DDCAPS helCaps;
	char buffer[100];
	DDSURFACEDESC displayMode;
	m_ddraw = NULL;
	if (m_flags & (c_flagBit16 | c_flagBit17)) {
		m_flags |= c_flagBit11 | c_flagBit13;
	}
	else {
		m_flags &= ~c_flagBit19;
	}
	if ((m_flags & c_flagBit16) && (m_flags & c_flagBit18)) {
		m_bpp = 8;
	}
	if (!(m_flags & c_flagBit9)) {
		if (DirectDrawCreate(NULL, &m_ddraw, NULL) != DD_OK) {
			GOL_FATALERROR_MESSAGE("Unable to create DirectDraw object");
		}

		::memset(&displayMode, 0, sizeof(displayMode));
		displayMode.dwSize = sizeof(DDSURFACEDESC);

		if (m_ddraw->GetDisplayMode(&displayMode) != DD_OK) {
			GOL_FATALERROR_MESSAGE("Unable to get current display mode");
		}

		if (displayMode.ddpfPixelFormat.dwRGBBitCount != m_bpp) {
			m_flags |= c_flagBit9;
		}

		m_ddraw->Release();
	}

	m_deviceList.DetectDevices();

	GolDeviceList::GolD3DDeviceInfo* device = m_deviceList.SelectDevice(m_hWnd, m_flags, m_driverName, m_deviceName);
	if (device == NULL) {
		GOL_FATALERROR_MESSAGE("Unable to find a 3D device that meets base requirements");
	}

	GolDeviceList::GolD3DDriverInfo* driver = device->m_driver;
	if (DirectDrawCreate(driver->m_unk0x08 ? &driver->m_guid : NULL, &m_ddraw, NULL) != DD_OK) {
		GOL_FATALERROR_MESSAGE("Unable to create DirectDraw object");
	}

	HRESULT hResult = m_ddraw->QueryInterface(IID_IDirectDraw4, (LPVOID*) &m_ddraw4);
	if (hResult != DD_OK) {
		::sprintf(buffer, "DirectDraw QueryInterface() error\nerror code = 0x%x", hResult);
		this->VTable0x48();
		GOL_FATALERROR_MESSAGE(buffer);
	}

	m_device = device;
	::memset(&m_ddrawCaps, 0, sizeof(m_ddrawCaps));
	::memset(&helCaps, 0, sizeof(helCaps));
	m_ddrawCaps.dwSize = sizeof(m_ddrawCaps);
	helCaps.dwSize = sizeof(helCaps);

	if (m_ddraw->GetCaps(&m_ddrawCaps, &helCaps) != DD_OK) {
		GOL_FATALERROR_MESSAGE("Unable to get DirectDraw capabilities");
	}

	if (driver->m_unk0x00) {
		m_flags |= c_flagBit13;
	}
	else {
		m_flags = (m_flags & ~c_flagBit13) | c_flagBit9;
	}

	if (!(m_flags & (c_flagBit11 | c_flagBit16 | c_flagBit17)) && (m_ddrawCaps.dwCaps & DDCAPS_3D) &&
		device->m_hwAccelerated) {
		m_flags &= ~c_flagBit11;
		m_unk0x2c0 = TRUE;
	}
	else {
		m_unk0x2c0 = FALSE;
		m_flags |= c_flagBit11;
		if (!(m_flags & c_flagBit17)) {
			m_flags |= c_flagBit16;
		}
	}

	if (m_flags & c_flagBit9) {
		m_flags |= c_flagBit10;
		hResult = m_ddraw4->SetCooperativeLevel(m_hWnd, DDSCL_FPUSETUP | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
	}
	else if (m_flags & c_flagBit10) {
		hResult = m_ddraw4->SetCooperativeLevel(m_hWnd, DDSCL_FPUSETUP | DDSCL_EXCLUSIVE);
	}
	else {
		hResult = m_ddraw4->SetCooperativeLevel(m_hWnd, DDSCL_FPUSETUP | DDSCL_NORMAL);
	}

	if (hResult != DD_OK) {
		return -1;
	}

	if (m_flags & c_flagBit9) {
		hResult = m_ddraw4->SetDisplayMode(m_width, m_height, m_bpp, 0, 0);
		if (hResult != DD_OK) {
			ReleaseDDraw();
			return -1;
		}
	}

	m_validGuid = device->m_validGuid;
	m_deviceGuid = device->m_guid;
	m_deviceDesc = device->m_deviceDesc;
	return 0;
}

// FUNCTION: GOLDP 0x100015d0
undefined4 GolDrawDPState::VTable0x60()
{
	return m_unk0x2c0;
}

// FUNCTION: GOLDP 0x100015e0
LegoU32 GolDrawDPState::VTable0x5c() const
{
	if (m_deviceDesc.dwDeviceZBufferBitDepth & DDBD_16) {
		return 16;
	}
	if (m_deviceDesc.dwDeviceZBufferBitDepth & DDBD_24) {
		return 24;
	}
	if (m_deviceDesc.dwDeviceZBufferBitDepth & DDBD_32) {
		return 32;
	}
	if (m_deviceDesc.dwDeviceZBufferBitDepth & DDBD_8) {
		return 8;
	}

	return 0;
}

// FUNCTION: GOLDP 0x10001610
LegoBool32 GolDrawDPState::VTable0x68() const
{
	return !!(m_deviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE);
}

// FUNCTION: GOLDP 0x10001620
LegoBool32 GolDrawDPState::VTable0x6c() const
{
	return !!(m_deviceDesc.dpcTriCaps.dwTextureAddressCaps & D3DPTADDRESSCAPS_WRAP);
}

// FUNCTION: GOLDP 0x10001630
LegoBool32 GolDrawDPState::VTable0x64() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwMiscCaps & (D3DPMISCCAPS_CULLCW | D3DPMISCCAPS_CULLCCW);
}

// FUNCTION: GOLDP 0x10001640
LegoBool32 GolDrawDPState::VTable0x70() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwMiscCaps & D3DPMISCCAPS_CULLCW;
}

// FUNCTION: GOLDP 0x10001650
LegoBool32 GolDrawDPState::VTable0x74() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwMiscCaps & D3DPMISCCAPS_CULLCCW;
}

// FUNCTION: GOLDP 0x10001660
LegoBool32 GolDrawDPState::VTable0x78() const
{
	return !!(m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER);
}

// FUNCTION: GOLDP 0x10001670
LegoBool32 GolDrawDPState::VTable0x7c() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_SUBPIXEL;
}

// FUNCTION: GOLDP 0x10001680
LegoBool32 GolDrawDPState::VTable0x80() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEAR;
}

// FUNCTION: GOLDP 0x10001690
LegoBool32 GolDrawDPState::VTable0x84() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwTextureFilterCaps &
		   (D3DPTFILTERCAPS_LINEARMIPLINEAR | D3DPTFILTERCAPS_LINEARMIPNEAREST | D3DPTFILTERCAPS_MIPLINEAR |
			D3DPTFILTERCAPS_MIPNEAREST);
}

// FUNCTION: GOLDP 0x100016a0
LegoBool32 GolDrawDPState::VTable0x88() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_FOGTABLE;
}

// FUNCTION: GOLDP 0x100016b0
LegoBool32 GolDrawDPState::VTable0x8c() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA;
}

// FUNCTION: GOLDP 0x100016c0
LegoBool32 GolDrawDPState::VTable0x90() const
{
	if ((m_deviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_ALPHA) &&
		(m_deviceDesc.dpcTriCaps.dwSrcBlendCaps & D3DPBLENDCAPS_ONE) &&
		(m_deviceDesc.dpcTriCaps.dwDestBlendCaps & D3DPBLENDCAPS_ONE)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDrawDPState::VTable0x94()
{
	MATCHING(0x100016f0);
	return FALSE;
}

// FUNCTION: GOLDP 0x10001700
LegoBool32 GolDrawDPState::VTable0x9c() const
{
	// BUG: Not a bool
	return m_ddrawCaps.dwPalCaps & DDPCAPS_ALPHA;
}

// FUNCTION: GOLDP 0x10001710
LegoBool32 GolDrawDPState::VTable0xa0() const
{
	// BUG: Not a bool
	return m_deviceDesc.dwDevCaps & D3DDEVCAPS_TEXTURESYSTEMMEMORY;
}

// FUNCTION: GOLDP 0x10001720
LegoBool32 GolDrawDPState::VTable0xa4() const
{
	// BUG: Not a bool
	return m_deviceDesc.dwDevCaps & D3DDEVCAPS_TEXTUREVIDEOMEMORY;
}

// FUNCTION: GOLDP 0x10001730
LegoBool32 GolDrawDPState::VTable0x98() const
{
	// BUG: Not a bool
	return m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR;
}

// FUNCTION: GOLDP 0x10001740
LegoBool32 GolDrawDPState::VTable0xa8() const
{
	// BUG: Not a bool
	return m_ddrawCaps.dwCaps2 & DDCAPS2_CANRENDERWINDOWED;
}

// FUNCTION: GOLDP 0x10001750
undefined4 GolDrawDPState::VTable0x58()
{
	HRESULT hResult;
	LegoChar buffer[100];

	if (!(m_flags & c_flagBit16)) {
		hResult = m_ddraw->QueryInterface(IID_IDirect3D3, reinterpret_cast<LPVOID*>(&m_d3d3));
		if (hResult != DD_OK) {
			::sprintf(buffer, "DirectDraw QueryInterface(IID_IDirect3D3) error\nerror code = 0x%x", hResult);
			VTable0x48();
			GOL_FATALERROR_MESSAGE(buffer);
		}

		LegoU32 renderBitDepth = m_deviceDesc.dwDeviceRenderBitDepth;
		if ((m_bpp == 4 && !(renderBitDepth & DDBD_4)) || (m_bpp == 8 && !(renderBitDepth & DDBD_8)) ||
			(m_bpp == 16 && !(renderBitDepth & DDBD_16)) || (m_bpp == 24 && !(renderBitDepth & DDBD_24)) ||
			(m_bpp == 32 && !(renderBitDepth & DDBD_32))) {
			VTable0x48();
			GOL_FATALERROR_MESSAGE("Direct3D error\ncurrent bit depth not supported for 3D rendering");
		}

		if ((m_flags & c_flagBit3) &&
			!(m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ANTIALIASSORTINDEPENDENT)) {
			m_flags &= ~c_flagBit3;
		}

		if (!(m_deviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_ZBUFFERLESSHSR)) {
			::memset(&m_depthBufferPixelformat, 0, sizeof(m_depthBufferPixelformat));
			m_depthBufferPixelformat.dwZBufferBitDepth = 16;
			hResult = m_d3d3->EnumZBufferFormats(m_deviceGuid, FindmatchingDepthPixelformat, &m_depthBufferPixelformat);

			if (m_depthBufferPixelformat.dwSize == 0) {
				m_depthBufferPixelformat.dwZBufferBitDepth = 24;
				hResult =
					m_d3d3->EnumZBufferFormats(m_deviceGuid, FindmatchingDepthPixelformat, &m_depthBufferPixelformat);
				if (m_depthBufferPixelformat.dwSize == 0) {
					m_depthBufferPixelformat.dwZBufferBitDepth = 0;
					hResult = m_d3d3->EnumZBufferFormats(
						m_deviceGuid,
						FindmatchingDepthPixelformat,
						&m_depthBufferPixelformat
					);
				}
			}

			if ((m_flags & c_flagBit12) && (hResult != DD_OK || m_depthBufferPixelformat.dwSize == 0)) {
				GOL_FATALERROR_MESSAGE("Unable to find z-buffer format");
			}
		}
	}

	if (!(m_unk0x354.GetUnk0x04() & BronzeFalcon0xc8770::c_flagBit0)) {
		undefined4 result = m_unk0x354.FUN_10007d90(this, &m_unk0x2fc, m_flags);
		if (result != 0) {
			return result;
		}
	}
	else {
		m_unk0x354.FUN_10007e20(m_flags);
	}

	return 0;
}

// FUNCTION: GOLDP 0x10001900
void GolDrawDPState::VTable0x0c(const char* p_driverName, const char* p_deviceName)
{
	if (m_driverName != NULL) {
		delete[] m_driverName;
		m_driverName = NULL;
	}
	if (m_deviceName != NULL) {
		delete[] m_deviceName;
		m_deviceName = NULL;
	}
	if (p_driverName == NULL || p_deviceName == NULL) {
		m_flags &= ~c_flagBit14;
		return;
	}
	size_t len;

	len = ::strlen(p_driverName) + 1;
	m_driverName = new LegoChar[len];
	if (m_driverName == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memcpy(m_driverName, p_driverName, len);

	len = ::strlen(p_deviceName) + 1;
	m_deviceName = new LegoChar[len];
	if (m_deviceName == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	::memcpy(m_deviceName, p_deviceName, len);
	m_flags |= c_flagBit14;
}

// FUNCTION: GOLDP 0x10001a00
LegoU32 GolDrawDPState::VTable0x10()
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}

	return m_deviceList.m_countDrivers;
}

// FUNCTION: GOLDP 0x10001a20
const LegoChar* GolDrawDPState::VTable0x14(LegoU32 p_index)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_index > m_deviceList.m_countDrivers) {
		return NULL;
	}

	return m_deviceList.m_drivers[p_index].m_description;
}

// FUNCTION: GOLDP 0x10001a70
const LegoChar* GolDrawDPState::VTable0x18(LegoU32 p_index)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_index > m_deviceList.m_countDrivers) {
		return NULL;
	}

	return m_deviceList.m_drivers[p_index].m_name;
}

// FUNCTION: GOLDP 0x10001ac0
LegoU32 GolDrawDPState::VTable0x1c(LegoU32 p_index)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_index > m_deviceList.m_countDrivers) {
		return NULL;
	}

	return m_deviceList.m_drivers[p_index].m_countDevices;
}

// FUNCTION: GOLDP 0x10001b10
const LegoChar* GolDrawDPState::VTable0x20(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_driverIndex > m_deviceList.m_countDrivers) {
		return NULL;
	}
	const GolDeviceList::GolD3DDriverInfo* driver = &m_deviceList.m_drivers[p_driverIndex];
	// BUG: should be >=
	if (p_deviceIndex > driver->m_countDevices) {
		return NULL;
	}

	return driver->m_devices[p_deviceIndex].m_name;
}

// FUNCTION: GOLDP 0x10001b70
const LegoChar* GolDrawDPState::VTable0x24(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_driverIndex > m_deviceList.m_countDrivers) {
		return NULL;
	}
	const GolDeviceList::GolD3DDriverInfo* driver = &m_deviceList.m_drivers[p_driverIndex];
	// BUG: should be >=
	if (p_deviceIndex > driver->m_countDevices) {
		return NULL;
	}

	return driver->m_devices[p_deviceIndex].m_description;
}

// FUNCTION: GOLDP 0x10001bd0
GUID* GolDrawDPState::VTable0x38() const
{
	if (m_device != NULL) {
		GolDeviceList::GolD3DDriverInfo* driver = m_device->m_driver;
		if (driver->m_unk0x08) {
			return &driver->m_guid;
		}
	}

	return NULL;
}

// FUNCTION: GOLDP 0x10001bf0
void GolDrawDPState::VTable0x30(LegoU32 p_driverIndex, GUID* p_guid)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be <
	if (p_driverIndex <= m_deviceList.m_countDrivers) {
		*p_guid = m_deviceList.m_drivers[p_driverIndex].m_guid;
	}
}

// FUNCTION: GOLDP 0x10001c50
void GolDrawDPState::VTable0x34(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be <
	if (p_driverIndex <= m_deviceList.m_countDrivers) {
		const GolDeviceList::GolD3DDriverInfo* driver = &m_deviceList.m_drivers[p_driverIndex];
		// BUG: should be <
		if (p_deviceIndex <= driver->m_countDevices) {
			*p_guid = driver->m_devices[p_deviceIndex].m_guid;
		}
	}
}

// FUNCTION: GOLDP 0x10001cc0
LegoBool32 GolDrawDPState::VTable0x28(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	// BUG: should be >=
	if (p_driverIndex > m_deviceList.m_countDrivers) {
		return FALSE;
	}
	const GolDeviceList::GolD3DDriverInfo* driver = &m_deviceList.m_drivers[p_driverIndex];
	// BUG: should be >=
	if (p_deviceIndex > driver->m_countDevices) {
		return FALSE;
	}

	return driver->m_devices[p_deviceIndex].m_hwAccelerated;
}

// FUNCTION: GOLDP 0x10001d20
void GolDrawDPState::VTable0x2c(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex)
{
	if (m_deviceList.m_countDrivers <= 0) {
		m_deviceList.DetectDevices();
	}
	m_deviceList.SelectDevice(m_hWnd, p_flags, m_driverName, m_deviceName);
	*p_driverIndex = m_deviceList.m_driverIndex;
	*p_deviceIndex = m_deviceList.m_deviceIndex;
}

// STUB: GOLDP 0x10001d80
undefined4 GolDrawDPState::VTable0xb0()
{
	// TODO
	STUB(0x10001d80);
	return 0;
}

// STUB: GOLDP 0x10001de0
undefined4 GolDrawDPState::VTable0xb4()
{
	// TODO
	STUB(0x10001de0);
	return 0;
}

// FUNCTION: GOLDP 0x10001e40
HRESULT GolDrawDPState::FindmatchingDepthPixelformat(LPDDPIXELFORMAT p_pixelformat, LPVOID p_context)
{
	if (p_pixelformat == NULL) {
		return FALSE;
	}
	LPDDPIXELFORMAT destPixelformat = static_cast<LPDDPIXELFORMAT>(p_context);
	if (p_pixelformat->dwFlags == DDPF_ZBUFFER) {
		if (destPixelformat->dwZBufferBitDepth == 0 ||
			destPixelformat->dwZBufferBitDepth == p_pixelformat->dwZBufferBitDepth) {
			memcpy(destPixelformat, p_pixelformat, sizeof(*p_pixelformat));
			destPixelformat->dwSize = sizeof(*destPixelformat);
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: GOLDP 0x10001e90
void* GolDrawDPState::VTable0xac()
{
	return m_ddraw;
}
