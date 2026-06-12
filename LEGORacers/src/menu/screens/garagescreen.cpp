#include "menu/screens/garagescreen.h"

#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreenid.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GarageScreen, 0x6410)

// FUNCTION: LEGORACERS 0x0047e2b0
GarageScreen::GarageScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047e400
GarageScreen::~GarageScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047e530
void GarageScreen::Reset()
{
	m_unk0x640c = 0;
	m_unk0x6408 = 0;
	RacerPickScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x0047e550
void GarageScreen::FUN_0047e550()
{
	FUN_0047fdc0(&m_unk0x40c8, 0x90, 0x42, 0x28);
	FUN_0047fdc0(&m_unk0x43b8, 0x91, 0x42, 0x29);
	FUN_0047fdc0(&m_unk0x46a8, 0x92, 0x42, 0x2a);
	FUN_0047fdc0(&m_unk0x4998, 0x93, 0x42, 0x2c);
	FUN_0047fdc0(&m_unk0x4c88, 0x94, 0x42, 0x2d);
	FUN_0047fdc0(&m_unk0x5848, 0x3f, 0x43, 3);
	CreateTextLabel(&m_unk0x4050, 0x3a, 0x3a, 3);
	m_unk0x4050.FUN_0046f6b0(0x14);
}

// FUNCTION: LEGORACERS 0x0047e600
void GarageScreen::FUN_0047e600()
{
	FUN_0047fdc0(&m_unk0x5268, 0x0f, 0x42, 9);
	FUN_0047fdc0(&m_unk0x5558, 0x98, 0x42, 0x0a);
	FUN_0047fdc0(&m_unk0x4f78, 0x11, 0x42, 0x0b);
	FUN_0047e9c0();
}

// FUNCTION: LEGORACERS 0x0047e650
void GarageScreen::VTable0x4c()
{
	CreateImage(&m_unk0x3ff4, 0x49, 0x49);
	RacerPickScreenBase::VTable0x4c();
	FUN_0047e550();
	FUN_0047e600();
}

// FUNCTION: LEGORACERS 0x0047e680
LegoBool32 GarageScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (!FUN_00480440(p_context)) {
		FUN_00480470(p_context, TRUE, TRUE);
	}

	if (p_context->m_menuStack.GetSize() == 1) {
		p_context->m_menuStack.ResetSize();
		p_context->m_menuStack.Push(c_menuMainMenu);
		p_context->m_menuStack.Push(c_menuGarage);
	}

	p_context->m_modelBuilder.SetUnk0x78(p_context->m_modelBuilder.GetUnk0x78() & ~9);
	p_context->m_context->m_unk0x1e &= ~2;
	p_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(0);

	undefined4 params[3];
	params[0] = 1;
	params[1] = 1;
	params[2] = 0xffff2;

	if (!RacerPickScreenBase::VTable0xa0(p_context, p_createParams, params)) {
		return FALSE;
	}

	VTable0x80();
	FUN_0047e740();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047e740
void GarageScreen::FUN_0047e740()
{
	m_unk0x40c8.SetFlags(2);
	m_unk0x43b8.SetFlags(2);
	m_unk0x46a8.SetFlags(2);
	m_unk0x4998.SetFlags(2);
	m_unk0x4c88.SetFlags(2);
	FUN_004891f0(0);
	m_unk0x5848.FUN_00482790(2);
	m_unk0x4050.VTable0x44(3, TRUE);
	m_unk0x4050.FUN_0046f6b0(0x14);

	if (m_unk0x2704[0]) {
		m_unk0x43b8.VTable0x44(5);
		m_unk0x4998.VTable0x44(5);
		m_unk0x4c88.VTable0x44(5);

		if (m_unk0x2704[0] == 0xd1) {
			m_unk0x40c8.VTable0x48(5);
			m_unk0x46a8.VTable0x48(5);
			m_unk0x43b8.VTable0x4c(4);
		}
		else {
			m_unk0x40c8.VTable0x44(5);
			m_unk0x46a8.VTable0x44(5);
			m_unk0x40c8.VTable0x4c(4);
		}

		if (static_cast<LegoS32>(m_unk0x2704[0]) > 1) {
			FUN_00489250(0);
			FUN_00486400(0);
			FUN_004890c0(0);
		}
		else {
			FUN_00489320(0);
			FUN_00486400(0);
			FUN_004890c0(0);
		}
	}
	else {
		m_unk0x40c8.VTable0x44(5);
		m_unk0x43b8.VTable0x48(5);
		m_unk0x46a8.VTable0x48(5);
		m_unk0x4998.VTable0x48(5);
		m_unk0x4c88.VTable0x48(5);
		m_unk0x40c8.VTable0x4c(5);
		FUN_00489320(0);
		FUN_004866e0(0);
		FUN_004890c0(0);
	}
}

// FUNCTION: LEGORACERS 0x0047e900
void GarageScreen::FUN_0047e900()
{
	m_unk0x40c8.ClearFlags(2);
	m_unk0x43b8.ClearFlags(2);
	m_unk0x46a8.ClearFlags(2);
	m_unk0x4998.ClearFlags(2);
	m_unk0x4c88.ClearFlags(2);
	FUN_00489320(0);
}

// FUNCTION: LEGORACERS 0x0047e950
void GarageScreen::FUN_0047e950()
{
	m_unk0x4f78.SetFlags(2);
	m_unk0x5268.SetFlags(2);
	m_unk0x5558.SetFlags(2);
	m_unk0x5268.VTable0x4c(5);
	m_unk0x5848.FUN_00482790(3);
	m_unk0x4050.VTable0x44(4, TRUE);
	m_unk0x4050.FUN_0046f6b0(0x14);
}

// FUNCTION: LEGORACERS 0x0047e9c0
void GarageScreen::FUN_0047e9c0()
{
	m_unk0x4f78.ClearFlags(2);
	m_unk0x5268.ClearFlags(2);
	m_unk0x5558.ClearFlags(2);
}

// FUNCTION: LEGORACERS 0x0047e9f0
void GarageScreen::FUN_0047e9f0(MenuGameContext* p_context)
{
	RacerUnlockState modelState;

	modelState.FUN_00442e60(&p_context->m_saveSystem);
	modelState.FUN_00442ef0(0xffff2);
	m_unk0x2704[0] = modelState.FUN_00442e80(0xffff2);
	modelState.FUN_00442e70();
}

// FUNCTION: LEGORACERS 0x0047ea50
void GarageScreen::FUN_0047ea50()
{
	SaveRecordList* records = NULL;
	RacerUnlockState* modelState = &m_unk0x22dc[0];
	SaveRecordList::Record* record = modelState->FUN_004430b0();
	SaveRecordList::Record* nextRecord = modelState->FUN_00442fe0();

	switch (record->m_unk0x08) {
	case 1:
		records = &m_context->m_saveSystem.GetSessionSave();
		break;
	case 2:
		records = &m_context->m_saveSystem.GetMemoryCardSaves()[record->m_unk0x0c];
		break;
	}

	records->FUN_0042b920(record);
	m_unk0x364 = TRUE;
	m_unk0x360 = c_menuGarage;
	modelState->FUN_00442ef0(modelState->GetUnk0x24());

	if (nextRecord != NULL && nextRecord != record) {
		modelState->FUN_004430e0(nextRecord);
	}

	FUN_0047e9f0(m_context);
	FUN_0047e740();

	if (m_unk0x2704[0]) {
		m_unk0x4998.VTable0x4c(5);
	}
}

// FUNCTION: LEGORACERS 0x0047eb20
void GarageScreen::FUN_0047eb20()
{
	LegoRacers::Context* context = m_context->m_context;
	GolName name;
	::strcpy(name, "test");

	GolNameTable* raceNames = &m_context->m_raceNames;
	RaceNameEntry* raceName = static_cast<RaceNameEntry*>(raceNames->GetName(name));

	context->m_unk0x2d[0] = '\0';
	context->m_unk0x24 = TRUE;
	::memcpy(context->m_raceSlots[0].m_raceName, raceName->GetUnk0x0cName(), sizeof(GolName));
	::memcpy(context->m_raceSlots[0].m_unk0x08, raceName->GetName(), sizeof(GolName));
	context->m_raceSlots[0].m_unk0x00 = TRUE;
	context->m_raceSlots[0].m_unk0x04 = raceName->GetUnk0x2c();
	context->m_unk0x100 = TRUE;
	context->m_unk0x1e |= 2;

	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecordCount(1);
	undefined4 flags = m_context->m_modelBuilder.GetUnk0x78();
	flags &= 0xfffffffd;
	m_context->m_modelBuilder.SetUnk0x78(flags);
	SaveRecordList::Record* record = m_unk0x22dc[0].FUN_004430b0();
	m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(record);
	m_unk0x360 = 0x41;
}

// FUNCTION: LEGORACERS 0x0047ec00
void GarageScreen::VTable0x84()
{
	switch (m_unk0x360) {
	case c_menuGarage:
		m_context->m_menuStack.Push(c_menuSaveAll);
		return;
	case c_menuMainMenu:
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, NULL);
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(1, NULL);
		m_context->m_menuStack.Pop();
		FUN_004804c0(m_context);
		FUN_004861b0();
		return;
	case c_menuPickMem:
		m_context->m_menuStack.Push(c_menuPickMem);
		m_context->m_saveSystem.GetActiveRecord().FUN_0042b2f0(4, 0, 0, NULL);
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() | 1);
		FUN_004861b0();
		return;
	case c_menuEditDriver:
	case c_menuDriverLicense:
	case c_menuEditCar: {
		SaveRecordList::Record* record = m_unk0x22dc[0].FUN_004430b0();
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, record);
		m_context->m_saveSystem.GetActiveRecord().CopyFrom(record);
		m_context->m_menuStack.Push(m_unk0x360);
		FUN_004861b0();
		return;
	}
	case 0x41:
		m_context->m_menuStack.ResetSize();
		FUN_004861b0();
		return;
	case c_menuNewRacer:
		m_context->m_menuStack.Push(c_menuPickMem);
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(0, m_unk0x22dc[0].FUN_004430b0());
		m_context->m_modelBuilder.SetUnk0x78(m_context->m_modelBuilder.GetUnk0x78() | 8);
		FUN_004861b0();
		return;
	}

	m_context->m_menuStack.Push(m_unk0x360);
	FUN_004861b0();
}

// FUNCTION: LEGORACERS 0x0047ee50
void GarageScreen::VTable0x38(MenuWidget* p_source)
{
	if (p_source == &m_unk0x5848) {
		if (!m_unk0x6408) {
			m_unk0x360 = c_menuMainMenu;
		}
		else {
			m_unk0x640c = 0;
		}
	}
	else {
		switch (m_unk0x6408) {
		case 1:
			if (p_source == &m_unk0x4f78) {
				m_unk0x360 = c_menuEditCar;
			}
			else if (p_source == &m_unk0x5268) {
				m_unk0x360 = c_menuEditDriver;
			}
			else if (p_source == &m_unk0x5558) {
				m_unk0x360 = c_menuDriverLicense;
			}
			break;
		case 0:
			if (p_source == &m_unk0x40c8) {
				m_unk0x360 = c_menuNewRacer;
			}
			else if (p_source == &m_unk0x43b8) {
				m_unk0x640c = 1;
			}
			else if (p_source == &m_unk0x46a8) {
				m_unk0x360 = c_menuPickMem;
			}
			else if (p_source == &m_unk0x4998) {
				FUN_0047fdc0(&m_unk0x5b38, 0x99, 0x46, 0x73);
				FUN_0047fdc0(&m_unk0x5e28, 0x99, 0x45, 0x74);
				FUN_0046c6f0(&m_unk0x5b38, &m_unk0x5e28, 0x76);
			}
			else if (p_source == &m_unk0x4c88) {
				FUN_0047eb20();
			}
			else if (p_source == &m_unk0x5b38) {
				FUN_0047ea50();
				m_unk0x284->FUN_00468cf0();
			}
			else if (p_source == &m_unk0x5e28) {
				m_unk0x284->FUN_00468cf0();
			}
			break;
		}
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
		m_unk0x232c[0].SetFlags(m_unk0x232c[0].GetFlags() & ~0x10000);
	}

	m_unk0x35c = p_source;
}

// STUB: LEGORACERS 0x0047efe0
void GarageScreen::FUN_0047efe0()
{
	switch (m_unk0x6408) {
	case 0:
		FUN_0047e900();
		break;
	case 1:
		FUN_0047e9c0();
		break;
	}

	m_unk0x6408 = m_unk0x640c;

	switch (m_unk0x6408) {
	case 1:
		FUN_0047e950();
		break;
	case 0:
		FUN_0047e740();
		break;
	}
}

// STUB: LEGORACERS 0x0047f030
LegoBool32 GarageScreen::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x640c != m_unk0x6408 && !(m_unk0x35c->GetUnk0x54() & 1)) {
		FUN_0047efe0();
	}

	RacerUnlockState* modelState = &m_unk0x22dc[0];
	if (modelState->FUN_004430b0() != NULL) {
		if (modelState->FUN_004430b0()->m_unk0x08 == 1) {
			m_unk0x46a8.FUN_00482790(0x2b);
		}
		else {
			m_unk0x46a8.FUN_00482790(0x2a);
		}
	}

	return RacerModelScreenBase::VTable0x78(p_elapsed);
}
