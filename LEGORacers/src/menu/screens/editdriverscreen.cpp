#include "menu/screens/editdriverscreen.h"

#include "menu/menutoolcontext0x4bc8.h"

DECOMP_SIZE_ASSERT(EditDriverScreen, 0x4774)
DECOMP_SIZE_ASSERT(MaroonAtoll0x170, 0x170)
DECOMP_SIZE_ASSERT(TealCrucible0x50, 0x50)

// FUNCTION: LEGORACERS 0x0047ce30
EditDriverScreen::EditDriverScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047cf90
EditDriverScreen::~EditDriverScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047d0d0
void EditDriverScreen::Reset()
{
	m_unk0x476c = 1;
	m_unk0x4764 = 0;
	m_unk0x4768 = 0;
	m_unk0x4770 = 0;

	ImaginaryTool0x368::Reset();
}

// STUB: LEGORACERS 0x0047d100
void EditDriverScreen::FUN_0047d100(MenuToolContext0x4bc8*, undefined4)
{
	STUB(0x0047d100);
}

// STUB: LEGORACERS 0x0047d170
LegoBool32 EditDriverScreen::FUN_0047d170(MaroonAtoll0x170*, undefined2, undefined2, undefined4)
{
	STUB(0x0047d170);
	return FALSE;
}

// STUB: LEGORACERS 0x0047d230
void EditDriverScreen::FUN_0047d230()
{
	STUB(0x0047d230);
}

// STUB: LEGORACERS 0x0047d2f0
void EditDriverScreen::VTable0x4c()
{
	STUB(0x0047d2f0);
}

// STUB: LEGORACERS 0x0047d460
LegoBool32 EditDriverScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x0047d460);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0047d520
LegoBool32 EditDriverScreen::Destroy()
{
	MenuToolContext0x4bc8* context = m_context;

	if (!m_initialized) {
		return TRUE;
	}

	m_unk0x45b0.FUN_004991c0();
	context->m_unk0x21f4.FUN_00499ee0();

	return ImaginaryTool0x368::Destroy();
}

// STUB: LEGORACERS 0x0047d560
undefined4 EditDriverScreen::FUN_0047d560()
{
	STUB(0x0047d560);
	return 0;
}

// STUB: LEGORACERS 0x0047d5d0
undefined4 EditDriverScreen::FUN_0047d5d0()
{
	STUB(0x0047d5d0);
	return 0;
}

// STUB: LEGORACERS 0x0047d6f0
void EditDriverScreen::FUN_0047d6f0()
{
	STUB(0x0047d6f0);
}

// STUB: LEGORACERS 0x0047d740
void EditDriverScreen::FUN_0047d740()
{
	STUB(0x0047d740);
}

// STUB: LEGORACERS 0x0047d840
void EditDriverScreen::FUN_0047d840()
{
	STUB(0x0047d840);
}

// STUB: LEGORACERS 0x0047d8e0
void EditDriverScreen::FUN_0047d8e0()
{
	STUB(0x0047d8e0);
}

// STUB: LEGORACERS 0x0047d940
void EditDriverScreen::FUN_0047d940()
{
	STUB(0x0047d940);
}

// FUNCTION: LEGORACERS 0x0047d9a0
LegoBool32 EditDriverScreen::VTable0x88()
{
	OpalHaven0xf4* opalHaven = m_unk0x4600.GetUnk0x1c();

	return opalHaven->FUN_0040e360() || !(opalHaven->GetFlags() & 0x10000);
}

// FUNCTION: LEGORACERS 0x0047d9d0
void EditDriverScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case 0x10:
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(0x10);
		break;

	case 3:
		m_context->m_menuStack.Pop();

		if (m_unk0x4770) {
			m_context->m_menuStack.Push(0x30);
		}

		m_context->m_unk0x4b40.SetUnk0x78(m_context->m_unk0x4b40.GetUnk0x78() & ~1);
		break;
	}
}

// FUNCTION: LEGORACERS 0x0047da50
LegoBool32 EditDriverScreen::VTable0x18(ObscureVantage0x58* p_unk0x04, InputEventQueue::Event*, undefined4, undefined4)
{
	if (m_unk0x364) {
		return TRUE;
	}

	for (LegoS32 i = 0; i < 4; i++) {
		if (p_unk0x04 == &m_unk0x420[i]) {
			VTable0x44(&m_unk0x9e0[i]);
			return TRUE;
		}
	}

	return FALSE;
}

// STUB: LEGORACERS 0x0047dab0
void EditDriverScreen::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x0047dab0);
}

// STUB: LEGORACERS 0x0047dbf0
void EditDriverScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x0047dbf0);
}

// FUNCTION: LEGORACERS 0x0047de30
LegoBool32 EditDriverScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (!m_unk0x364 && m_unk0x4600.GetUnk0x1c()->FUN_0040e360()) {
		FUN_0047d6f0();
	}

	return ImaginaryTool0x368::VTable0x78(p_unk0x04);
}
