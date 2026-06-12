#include "menu/screens/pickracerscreen.h"

#include "menu/menugamecontext.h"
#include "menu/menuscreenid.h"

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

	CreateImage(&m_unk0x3ff4, 0x49, 0x49);
	RacerPickScreenBase::VTable0x4c();

	if (m_context->m_modelBuilder.GetUnk0x78() & 2) {
		textId = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCountAsU16();
		textId += 0x15;
	}

	CreateTextLabel(&m_unk0x4050, 0x3a, 0x3a, textId);
	m_unk0x4050.FUN_0046f6b0(0x14);
	FUN_0047fdc0(&m_unk0x46a8, 9, 0x42, 0xb9);
	FUN_0047fdc0(&m_unk0x40c8, 0x41, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x43b8, 0x40, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x4998, 0x3f, 0x45, 0x1f);
}

// FUNCTION: LEGORACERS 0x00484e40
LegoBool32 PickRacerScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	undefined4 params[3];
	params[0] = 1;
	params[1] = 1;
	params[2] = 0xffff3;

	if (!p_context->m_modelBuilder.HasMenuResources()) {
		FUN_00480210(p_context, FALSE);
	}

	if (!RacerPickScreenBase::VTable0xa0(p_context, p_createParams, params)) {
		return FALSE;
	}

	VTable0x80();

	if (p_context->m_modelBuilder.GetUnk0x78() & 2) {
		m_unk0x2c0c[0].SetUnk0x9ec(TRUE);

		if (p_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() == 0) {
			m_unk0x40c8.ClearFlags(2);
			m_unk0x43b8.VTable0x4c(0);
		}
		else {
			m_unk0x43b8.ClearFlags(2);
			m_unk0x40c8.VTable0x4c(0);
		}
	}
	else {
		m_unk0x43b8.ClearFlags(2);
		m_unk0x40c8.VTable0x4c(0);
	}

	return TRUE;
}

// STUB: LEGORACERS 0x00484f40
void PickRacerScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x46a8) {
		m_unk0x360 =
			static_cast<LegoU16>(m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() + c_menuControl1);
		m_unk0x232c[0].SetFlags(m_unk0x232c[0].GetFlags() & ~0x10000);
	}
	else if (p_source == &m_unk0x40c8) {
		if (m_context->m_modelBuilder.GetUnk0x78() & 2) {
			m_context->m_context->m_unk0x100 = 0;
		}

		FUN_00486810(0);

		ActiveRecordBuffer& buffer = m_context->m_saveSystem.GetActiveRecord();
		LegoU32 playerIndex = buffer.GetSelectedRecordCount();
		buffer.SetSelectedRecord(playerIndex, m_unk0x22dc[0].FUN_004430b0());
		buffer.SetSelectedRecordCount(playerIndex + 1);
		m_unk0x360 = 0x41;
	}
	else if (p_source == &m_unk0x43b8) {
		FUN_00486810(0);

		ActiveRecordBuffer& buffer = m_context->m_saveSystem.GetActiveRecord();
		LegoU32 playerIndex = buffer.GetSelectedRecordCount();
		buffer.SetSelectedRecord(playerIndex, m_unk0x22dc[0].FUN_004430b0());
		buffer.SetSelectedRecordCount(playerIndex + 1);
		m_unk0x360 = c_menuPickRacerP2;
	}
	else if (p_source == &m_unk0x4998) {
		m_unk0x360 = 0x3f;

		ActiveRecordBuffer& buffer = m_context->m_saveSystem.GetActiveRecord();
		if (buffer.GetSelectedRecordCount() != 0) {
			buffer.SetSelectedRecordCount(buffer.GetSelectedRecordCount() - 1);
		}

		m_unk0x232c[0].SetFlags(m_unk0x232c[0].GetFlags() & ~0x10000);
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_source;
}

// FUNCTION: LEGORACERS 0x00485090
void PickRacerScreen::VTable0x44(MenuWidget* p_source)
{
	RacerPickScreenBase::VTable0x44(p_source);
}

// FUNCTION: LEGORACERS 0x004850a0
void PickRacerScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case c_menuControl1:
	case c_menuControl2:
	case c_menuPickRacerP2:
		m_context->m_menuStack.Push(m_unk0x360);
		FUN_004861b0();
		return;
	case 0x3f:
		m_context->m_menuStack.Pop();
		FUN_004861b0();
		return;
	case 0x41:
		if (m_context->m_context->m_unk0x24 == 0 &&
			m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount() == 1) {
			RaceDefinitionList::RaceDefinition* raceDefinition = static_cast<RaceDefinitionList::RaceDefinition*>(
				m_context->m_raceList.GetName(m_context->m_context->m_unk0x2d)
			);
			LegoU32 raceIndex = m_context->m_raceList.GetEntryIndex(raceDefinition);
			m_context->m_menuStack.Push(static_cast<LegoU16>(raceIndex + c_menuCircuit1));
			m_context->m_context->m_unk0x100 = 5;
		}
		else {
			m_context->m_menuStack.ResetSize();
		}

		if (m_context->m_modelBuilder.GetUnk0x78() & 2) {
			m_context->m_context->m_unk0x100 = 0;
		}
		else {
			m_context->m_context->m_unk0x100 += m_context->m_saveSystem.GetActiveRecord().GetSelectedRecordCount();
		}

		m_unk0x364 = TRUE;
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() & ~2);
		break;
	}

	FUN_004861b0();
}
