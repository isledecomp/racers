#include "render/goldrawstate.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(GolDrawState, 0x18)

// FUNCTION: GOLDP 0x1001d570
GolDrawState::GolDrawState()
{
	m_width = 0;
	m_height = 0;
	m_bpp = 0;
	m_flags = 0;
	m_displaySurface = NULL;
}

// FUNCTION: GOLDP 0x1001d5b0
GolDrawState::~GolDrawState()
{
}

// FUNCTION: GOLDP 0x1001d5c0
LegoS32 GolDrawState::RecreateDisplay(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	if (m_flags & c_flagCreated) {
		DestroyDisplay();
	}

	LegoU32 flags = m_flags | c_flagRecreating;
	LegoU32 bpp = p_bpp;
	LegoU32 height = p_height;
	m_flags = flags;

	LegoU32 width = p_width;

	if (!width) {
		width = 640;
	}

	if (!height) {
		height = 480;
	}

	if (!bpp) {
		bpp = 16;
	}

	m_bpp = bpp;
	m_height = height;
	m_flags = p_flags;
	m_width = width;

	LegoS32 result = CreateDevice();
	if (result) {
		return result;
	}

	m_displaySurface->Create(this, m_width, m_height, m_bpp);

	m_flags &= ~c_flagRecreating;
	m_flags |= c_flagCreated;

	return 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::SelectDevice(const char* p_driverName, const char* p_deviceName)
{
	// empty
}

// FUNCTION: GOLDP 0x1001d640
void GolDrawState::ReleaseDisplay()
{
	m_flags |= c_flagRecreating;
	if (m_displaySurface != NULL && (m_displaySurface->GetPixelFlags() & GolSurface::c_lockRequestRead)) {
		m_displaySurface->Destroy();
	}
}

// FUNCTION: GOLDP 0x1001d660
LegoS32 GolDrawState::CreateDisplay(LegoS32 p_width, LegoS32 p_height, undefined4 p_bpp, LegoU32 p_flags)
{
	if (p_width == 0) {
		p_width = 640;
	}

	if (p_height == 0) {
		p_height = 480;
	}

	if (p_bpp == 0) {
		p_bpp = 16;
	}

	m_width = p_width;
	m_bpp = p_bpp;
	m_height = p_height;
	m_flags = p_flags;

	LegoS32 result = CreateDevice();
	if (result != 0) {
		return result;
	}

	m_displaySurface->Create(this, m_width, m_height, m_bpp);
	m_flags &= ~c_flagRecreating;
	m_flags |= c_flagCreated;

	return 0;
}

// FUNCTION: GOLDP 0x1001d6d0
void GolDrawState::Present()
{
	m_displaySurface->Present(0);
}

// FUNCTION: GOLDP 0x1001d6e0
void GolDrawState::DestroyDisplay()
{
	m_flags &= ~c_flagCreated;
	if (m_displaySurface != NULL && (m_displaySurface->GetPixelFlags() & GolSurface::c_lockRequestRead)) {
		m_displaySurface->Destroy();
	}
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
const LegoChar* GolDrawState::GetDriverDescription(LegoU32 p_index)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
const LegoChar* GolDrawState::GetDriverName(LegoU32 p_index)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
LegoU32 GolDrawState::GetDeviceCount(LegoU32 p_index)
{
	return 0;
}

// FUNCTION: GOLDP 0x1001d710
void GolDrawState::FindDevice(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex)
{
	*p_driverIndex = 0;
	*p_deviceIndex = 0;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
const LegoChar* GolDrawState::GetDeviceName(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return NULL;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
const LegoChar* GolDrawState::GetDeviceDescription(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return NULL;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
LegoBool32 GolDrawState::IsDeviceHwAccelerated(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return FALSE;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::GetDriverGuid(LegoU32 p_driverIndex, GUID* p_guid)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void GolDrawState::GetDeviceGuid(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x3c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x40()
{
	// empty
}
