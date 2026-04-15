#include "goldrawdpstate.h"

#include "golerror.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(GolDrawDPState, 0xc8ac4)

// STUB: GOLDP 0x10001000
GolDrawDPState::GolDrawDPState()
{
	// TODO
	STUB(0x10001000);
}

// STUB: GOLDP 0x10001110
GolDrawDPState::~GolDrawDPState()
{
	// TODO
	STUB(0x10001110);
}

// STUB: GOLDP 0x100011e0
void GolDrawDPState::VTable0x08(HWND p_hWnd)
{
	m_hWnd = p_hWnd;
}

// STUB: GOLDP 0x100011f0
void GolDrawDPState::VTable0x48()
{
	// TODO
	STUB(0x100011f0);
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

// STUB: GOLDP 0x100012b0
void GolDrawDPState::VTable0x50()
{
	// TODO
	STUB(0x100012b0);
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

// STUB: GOLDP 0x100015d0
undefined4 GolDrawDPState::VTable0x60()
{
	// TODO
	STUB(0x100015d0);
	return 0;
}

// STUB: GOLDP 0x100015e0
undefined4 GolDrawDPState::VTable0x5c()
{
	// TODO
	STUB(0x100015e0);
	return 0;
}

// STUB: GOLDP 0x10001610
undefined4 GolDrawDPState::VTable0x68()
{
	// TODO
	STUB(0x10001610);
	return 0;
}

// STUB: GOLDP 0x10001620
undefined4 GolDrawDPState::VTable0x6c()
{
	// TODO
	STUB(0x10001620);
	return 0;
}

// STUB: GOLDP 0x10001630
undefined4 GolDrawDPState::VTable0x64()
{
	// TODO
	STUB(0x10001630);
	return 0;
}

// STUB: GOLDP 0x10001640
undefined4 GolDrawDPState::VTable0x70()
{
	// TODO
	STUB(0x10001640);
	return 0;
}

// STUB: GOLDP 0x10001650
undefined4 GolDrawDPState::VTable0x74()
{
	// TODO
	STUB(0x10001650);
	return 0;
}

// STUB: GOLDP 0x10001660
undefined4 GolDrawDPState::VTable0x78()
{
	// TODO
	STUB(0x10001660);
	return 0;
}

// STUB: GOLDP 0x10001670
undefined4 GolDrawDPState::VTable0x7c()
{
	// TODO
	STUB(0x10001670);
	return 0;
}

// STUB: GOLDP 0x10001680
undefined4 GolDrawDPState::VTable0x80()
{
	// TODO
	STUB(0x10001680);
	return 0;
}

// STUB: GOLDP 0x10001690
undefined4 GolDrawDPState::VTable0x84()
{
	// TODO
	STUB(0x10001690);
	return 0;
}

// STUB: GOLDP 0x100016a0
undefined4 GolDrawDPState::VTable0x88()
{
	// TODO
	STUB(0x100016a0);
	return 0;
}

// STUB: GOLDP 0x100016b0
undefined4 GolDrawDPState::VTable0x8c()
{
	// TODO
	STUB(0x100016b0);
	return 0;
}

// STUB: GOLDP 0x100016c0
undefined4 GolDrawDPState::VTable0x90()
{
	// TODO
	STUB(0x100016c0);
	return 0;
}

// STUB: GOLDP 0x100016f0 FOLDED
undefined4 GolDrawDPState::VTable0x94()
{
	STUB(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x10001700
undefined4 GolDrawDPState::VTable0x9c()
{
	// TODO
	STUB(0x10001700);
	return 0;
}

// STUB: GOLDP 0x10001710
undefined4 GolDrawDPState::VTable0xa0()
{
	// TODO
	STUB(0x10001710);
	return 0;
}

// STUB: GOLDP 0x10001720
undefined4 GolDrawDPState::VTable0xa4()
{
	// TODO
	STUB(0x10001720);
	return 0;
}

// STUB: GOLDP 0x10001730
undefined4 GolDrawDPState::VTable0x98()
{
	// TODO
	STUB(0x10001730);
	return 0;
}

// STUB: GOLDP 0x10001740
undefined4 GolDrawDPState::VTable0xa8()
{
	// TODO
	STUB(0x10001740);
	return 0;
}

// STUB: GOLDP 0x10001750
undefined4 GolDrawDPState::VTable0x58()
{
	// TODO
	STUB(0x10001750);
	return 0;
}

// STUB: GOLDP 0x10001900
void GolDrawDPState::VTable0x0c(undefined4, undefined4)
{
	// TODO
	STUB(0x10001900);
}

// STUB: GOLDP 0x10001a00
undefined4 GolDrawDPState::VTable0x10()
{
	// TODO
	STUB(0x10001a00);
	return 0;
}

// STUB: GOLDP 0x10001a20
undefined4 GolDrawDPState::VTable0x14(undefined4)
{
	// TODO
	STUB(0x10001a20);
	return 0;
}

// STUB: GOLDP 0x10001a70
undefined4 GolDrawDPState::VTable0x18(undefined4)
{
	// TODO
	STUB(0x10001a70);
	return 0;
}

// STUB: GOLDP 0x10001ac0
undefined4 GolDrawDPState::VTable0x1c(undefined4)
{
	// TODO
	STUB(0x10001ac0);
	return 0;
}

// STUB: GOLDP 0x10001b10
undefined4 GolDrawDPState::VTable0x20(undefined4, undefined4)
{
	// TODO
	STUB(0x10001b10);
	return 0;
}

// STUB: GOLDP 0x10001b70
undefined4 GolDrawDPState::VTable0x24(undefined4, undefined4)
{
	// TODO
	STUB(0x10001b70);
	return 0;
}

// STUB: GOLDP 0x10001bd0
undefined4 GolDrawDPState::VTable0x38()
{
	// TODO
	STUB(0x10001bd0);
	return 0;
}

// STUB: GOLDP 0x10001bf0
void GolDrawDPState::VTable0x30(undefined4, undefined4*)
{
	// TODO
	STUB(0x10001bf0);
}

// STUB: GOLDP 0x10001c50
void GolDrawDPState::VTable0x34(undefined4, undefined4, undefined4*)
{
	// TODO
	STUB(0x10001c50);
}

// STUB: GOLDP 0x10001cc0
undefined4 GolDrawDPState::VTable0x28(undefined4, undefined4)
{
	// TODO
	STUB(0x10001cc0);
	return 0;
}

// STUB: GOLDP 0x10001d20
void GolDrawDPState::VTable0x2c(undefined4, undefined4*, undefined4*)
{
	// TODO
	STUB(0x10001d20);
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

// STUB: GOLDP 0x10001e90
undefined4 GolDrawDPState::VTable0xac()
{
	// TODO
	STUB(0x10001e90);
	return 0;
}
