#include "menu/screens/pickracerscreen.h"

#include "menu/menutoolcontext0x4bc8.h"

DECOMP_SIZE_ASSERT(PickRacerScreen, 0x4c8c)

// FUNCTION: LEGORACERS 0x00484c10
PickRacerScreen::PickRacerScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00484ce0
PickRacerScreen::~PickRacerScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00484d90
void PickRacerScreen::VTable0x4c()
{
	undefined2 textId = 0x14;

	FUN_0046bef0(&m_unk0x3ff4, 0x49, 0x49);
	RacerPickScreenBase0x3ff4::VTable0x4c();

	if (m_context->m_unk0x4b40.GetUnk0x78() & 2) {
		textId = static_cast<undefined2>(m_context->m_unk0x258.GetUnk0x1cfc().GetUnk0x244() + 0x15);
	}

	FUN_0046bf80(&m_unk0x4050, 0x3a, 0x3a, textId);
	m_unk0x4050.FUN_0046f6b0(0x14);
	FUN_0047fdc0(&m_unk0x46a8, 9, 0x42, 0xb9);
	FUN_0047fdc0(&m_unk0x40c8, 0x41, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x43b8, 0x40, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x4998, 0x3f, 0x45, 0x1f);
}

// STUB: LEGORACERS 0x00484e40
LegoBool32 PickRacerScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00484e40);
	return FALSE;
}

// STUB: LEGORACERS 0x00484f40
void PickRacerScreen::VTable0x38(ObscureVantage0x58*)
{
	STUB(0x00484f40);
}

// FUNCTION: LEGORACERS 0x00485090
void PickRacerScreen::VTable0x44(ObscureVantage0x58* p_source)
{
	RacerPickScreenBase0x3ff4::VTable0x44(p_source);
}

// STUB: LEGORACERS 0x004850a0
void PickRacerScreen::VTable0x84()
{
	STUB(0x004850a0);
}
