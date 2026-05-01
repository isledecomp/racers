#include "goldrawstate.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(GolDrawState, 0x18)

// FUNCTION: GOLDP 0x1001d570
GolDrawState::GolDrawState()
{
	m_width = 0;
	m_height = 0;
	m_bpp = 0;
	m_flags = 0;
	m_unk0x14 = NULL;
}

// FUNCTION: GOLDP 0x1001d5b0
GolDrawState::~GolDrawState()
{
}

// FUNCTION: GOLDP 0x1001d5c0
LegoS32 GolDrawState::VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp, LegoU32 p_flags)
{
	if (m_flags & c_flagBit0) {
		VTable0x48();
	}

	LegoU32 flags = m_flags | c_flagBit1;
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

	LegoS32 result = VTable0x00();
	if (result) {
		return result;
	}

	m_unk0x14->VTable0x30(this, m_width, m_height, m_bpp);

	m_flags &= ~c_flagBit1;
	m_flags |= c_flagBit0;
	return 0;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x0c(const char* p_driverName, const char* p_deviceName)
{
	// empty
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoU32 GolDrawState::VTable0x10()
{
	MATCHING(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x1001d640
void GolDrawState::VTable0x50()
{
	m_flags |= c_flagBit1;
	if (m_unk0x14 != NULL && (m_unk0x14->GetPixelFlags() & SilverDune0x30::c_lockRequestRead)) {
		m_unk0x14->VTable0x34();
	}
}

// FUNCTION: GOLDP 0x1001d660
LegoS32 GolDrawState::VTable0x54(LegoS32 p_width, LegoS32 p_height, undefined4 p_bpp, LegoU32 p_flags)
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
	LegoS32 result = VTable0x00();
	if (result != 0) {
		return result;
	}
	m_unk0x14->VTable0x30(this, m_width, m_height, m_bpp);
	m_flags &= ~c_flagBit1;
	m_flags |= c_flagBit0;
	return 0;
}

// FUNCTION: GOLDP 0x1001d6d0
void GolDrawState::VTable0x4c()
{
	m_unk0x14->VTable0x14(NULL);
}

// FUNCTION: GOLDP 0x1001d6e0
void GolDrawState::VTable0x48()
{
	m_flags &= ~c_flagBit0;
	if (m_unk0x14 != NULL && (m_unk0x14->GetPixelFlags() & SilverDune0x30::c_lockRequestRead)) {
		m_unk0x14->VTable0x34();
	}
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
const LegoChar* GolDrawState::VTable0x14(LegoU32 p_index)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
const LegoChar* GolDrawState::VTable0x18(LegoU32 p_index)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
LegoU32 GolDrawState::VTable0x1c(LegoU32 p_index)
{
	return 0;
}

// FUNCTION: GOLDP 0x1001d710
void GolDrawState::VTable0x2c(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex)
{
	*p_driverIndex = 0;
	*p_deviceIndex = 0;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
const LegoChar* GolDrawState::VTable0x20(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return NULL;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
const LegoChar* GolDrawState::VTable0x24(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return NULL;
}

// FUNCTION: GOLDP 0x10029950 FOLDED
LegoBool32 GolDrawState::VTable0x28(LegoU32 p_driverIndex, LegoU32 p_deviceIndex)
{
	return FALSE;
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x30(LegoU32 p_driverIndex, GUID* p_guid)
{
	// empty
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void GolDrawState::VTable0x34(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid)
{
	// empty
}

// STUB: GOLDP 0x100016f0 FOLDED
GUID* GolDrawState::VTable0x38() const
{
	MATCHING(0x100016f0);
	return NULL;
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
