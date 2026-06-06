#include "menu/screens/multiplayerpickscreen.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MultiplayerPickScreen, 0x2cc4)

// FUNCTION: LEGORACERS 0x004815f0
MultiplayerPickScreen::MultiplayerPickScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00481710
MultiplayerPickScreen::~MultiplayerPickScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00481800
void MultiplayerPickScreen::Reset()
{
	m_unk0x2b70 = 0;
	m_unk0x2b74 = 0;
	m_unk0x2b78 = 0;
	::memset(m_unk0x2b94, 0, sizeof(m_unk0x2b94));
	RacerPickScreenBase0x270c::Reset();
}

// FUNCTION: LEGORACERS 0x00481830
void MultiplayerPickScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x270c, 0x49, 0x49);
	RacerPickScreenBase0x270c::VTable0x4c();
	FUN_0046bf80(&m_unk0x2990, 0xf0, 0x37, 0x56);
	FUN_0046bf80(&m_unk0x2a08, 0xf1, 0x37, 0x57);
	FUN_0046bf80(&m_unk0x2bd4[0], 0x8e, 0x37, 0x56);
	FUN_0046bf80(&m_unk0x2bd4[1], 0x8f, 0x37, 0x56);
	FUN_0046bef0(&m_unk0x2768[0], 0x86, 0x4b);
	FUN_0046bef0(&m_unk0x2768[1], 0x87, 0x4b);
	FUN_0046bef0(&m_unk0x2768[2], 0x88, 0x4a);
	FUN_0046bef0(&m_unk0x2768[3], 0x89, 0x4a);
	FUN_0046bef0(&m_unk0x2768[4], 0x8c, 0x50);
	FUN_0046bef0(&m_unk0x2768[5], 0x8d, 0x51);
	FUN_0046bf80(&m_unk0x2a80, 0x8a, 0x37, 0x72);
	FUN_0046bf80(&m_unk0x2af8, 0x8b, 0x37, 0x1f);
}

// STUB: LEGORACERS 0x00481a30
LegoBool32 MultiplayerPickScreen::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00481a30);
	return FALSE;
}

// STUB: LEGORACERS 0x00481c80
LegoBool32 MultiplayerPickScreen::VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x00481c80);
	return FALSE;
}

// STUB: LEGORACERS 0x00481f50
void MultiplayerPickScreen::VTable0x84()
{
	STUB(0x00481f50);
}

// STUB: LEGORACERS 0x00481fc0
LegoBool32 MultiplayerPickScreen::VTable0x78(undefined4)
{
	STUB(0x00481fc0);
	return 0;
}
