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

// STUB: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x0c(const char* p_driverName, const char* p_deviceName)
{
	// TODO (empty)
	STUB(0x1002c010);
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoU32 GolDrawState::VTable0x10()
{
	STUB(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x1001d640
void GolDrawState::VTable0x50()
{
	// TODO
	STUB(0x1001d640);
}

// STUB: GOLDP 0x1001d660
void GolDrawState::VTable0x54(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x1001d660);
}

// STUB: GOLDP 0x1001d6d0
void GolDrawState::VTable0x4c()
{
	// TODO
	STUB(0x1001d6d0);
}

// STUB: GOLDP 0x1001d6e0
void GolDrawState::VTable0x48()
{
	// TODO
	STUB(0x1001d6e0);
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

// STUB: GOLDP 0x1002c010 FOLDED
void GolDrawState::VTable0x30(LegoU32 p_driverIndex, GUID* p_guid)
{
	// TODO (empty)
	STUB(0x1002c010);
}

// FUNCTION: GOLDP 0x100294f0 FOLDED
void GolDrawState::VTable0x34(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid)
{
}

// STUB: GOLDP 0x100016f0 FOLDED
GUID* GolDrawState::VTable0x38() const
{
	STUB(0x100016f0);
	return 0;
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x3c()
{
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolDrawState::VTable0x40()
{
}
