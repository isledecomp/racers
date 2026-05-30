#include "menu/screens/obsidianmantle0x3b4.h"

#include "decomp.h"

DECOMP_SIZE_ASSERT(ObsidianMantle0x3b4, 0x3b4)

// STUB: LEGORACERS 0x00474c40
void ObsidianMantle0x3b4::Reset()
{
	STUB(0x00474c40);
}

// STUB: LEGORACERS 0x00474c70
undefined4 ObsidianMantle0x3b4::VTable0x14(ObscureVantage0x58*, void*, undefined4, undefined4)
{
	STUB(0x00474c70);
	return 0;
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
undefined4 ObsidianMantle0x3b4::VTable0x18(
	ObscureVantage0x58* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return ImaginaryTool0x368::VTable0x18(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// FUNCTION: LEGORACERS 0x00474e00 FOLDED
undefined4 ObsidianMantle0x3b4::VTable0x1c(
	ObscureVantage0x58* p_unk0x04,
	InputEventQueue::Event* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10
)
{
	if (!m_unk0x36c) {
		FUN_00474e40();
	}

	return ImaginaryTool0x368::VTable0x1c(p_unk0x04, p_unk0x08, p_unk0x0c, p_unk0x10);
}

// STUB: LEGORACERS 0x00474e40
void ObsidianMantle0x3b4::FUN_00474e40()
{
	STUB(0x00474e40);
}

// STUB: LEGORACERS 0x00474e70
void ObsidianMantle0x3b4::FUN_00474e70()
{
	STUB(0x00474e70);
}

// STUB: LEGORACERS 0x00474ef0
void ObsidianMantle0x3b4::FUN_00474ef0()
{
	STUB(0x00474ef0);
}

// STUB: LEGORACERS 0x00474f40
LegoBool32 ObsidianMantle0x3b4::VTable0x78(undefined4)
{
	STUB(0x00474f40);
	return FALSE;
}

// STUB: LEGORACERS 0x00475010
LegoBool32 ObsidianMantle0x3b4::VTable0x7c(Rect*, Rect*)
{
	STUB(0x00475010);
	return FALSE;
}
