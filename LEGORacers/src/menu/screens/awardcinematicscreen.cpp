#include "menu/screens/awardcinematicscreen.h"

#include "menu/menuscreenid.h"

DECOMP_SIZE_ASSERT(AwardCinematicScreen, 0x7b0)

// STUB: LEGORACERS 0x00475c30
AwardCinematicScreen::AwardCinematicScreen()
{
	STUB(0x00475c30);
}

// STUB: LEGORACERS 0x00475cd0
AwardCinematicScreen::~AwardCinematicScreen()
{
	STUB(0x00475cd0);
}

// STUB: LEGORACERS 0x00475d30
LegoBool32 AwardCinematicScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00475d30);
	return FALSE;
}

// STUB: LEGORACERS 0x00475e50
LegoBool32 AwardCinematicScreen::Destroy()
{
	STUB(0x00475e50);
	return FALSE;
}

// STUB: LEGORACERS 0x00475f40
void AwardCinematicScreen::VTable0x4c()
{
	STUB(0x00475f40);
}

// STUB: LEGORACERS 0x00476a00
void AwardCinematicScreen::VTable0x84()
{
	STUB(0x00476a00);
}

// FUNCTION: LEGORACERS 0x00476ad0
LegoBool32 AwardCinematicScreen::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x28c == c_menuCircuit7) {
		m_unk0x368.m_unk0x2cc = TRUE;
	}

	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}
