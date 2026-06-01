#include "menu/screens/circuitracescreen.h"

#include "camera/golcamera.h"
#include "golname.h"
#include "golstring.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "race/data/racenameentry.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CircuitRaceScreen, 0x2228)

// FUNCTION: LEGORACERS 0x00479d70
CircuitRaceScreen::CircuitRaceScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00479e70
CircuitRaceScreen::~CircuitRaceScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00479f50
void CircuitRaceScreen::Reset()
{
	m_unk0x2214 = NULL;
	m_unk0x2218 = 0;
	m_unk0x2220 = 0;
	m_unk0x2224 = FALSE;
	ImaginaryTool0x368::Reset();
}

// FUNCTION: LEGORACERS 0x00479f70
void CircuitRaceScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x1908, 0x49, 0x49);
	SingleRaceSelectBase::VTable0x4c();

	FUN_0046bf80(&m_unk0x1964, 0x3a, 0x3a, 0x0d);
	m_unk0x1964.FUN_0046f6b0(0x14);
	FUN_0046bf80(&m_unk0x19dc, 0x5b, 0x37, 0x4a);
	FUN_0046bf80(&m_unk0x1a54, 0x5c, 0x37, 0x4c);
	FUN_0046bf80(&m_unk0x1acc, 0x5d, 0x37, 0x4a);
	FUN_0046bf80(&m_unk0x1b44, 0x5f, 0x37, 0x4b);
	FUN_0046bf80(&m_unk0x1bbc, 0x60, 0x37, 0x60);
	FUN_0047fdc0(&m_unk0x1f24, 0x40, 0x46, 0x72);
	FUN_0047fdc0(&m_unk0x1c34, 0x3f, 0x43, 2);
}

// FUNCTION: LEGORACERS 0x0047a040
LegoBool32 CircuitRaceScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (!SingleRaceSelectBase::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	VTable0x44(&m_unk0xbe8);
	m_unk0x1f24.VTable0x4c(0);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047a090
void CircuitRaceScreen::VTable0x38(ObscureVantage0x58* p_source)
{
	if (p_source == &m_unk0x1f24) {
		m_unk0x360 = 0x1e;
	}
	else if (p_source == &m_unk0x1c34) {
		m_unk0x360 = 2;
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_source;
}

// FUNCTION: LEGORACERS 0x0047a0e0
void CircuitRaceScreen::VTable0x44(ObscureVantage0x58*)
{
	m_context->m_context->m_unk0x24 = 0;

	m_unk0x221c = m_unk0xb54.GetUnk0x6c();
	m_unk0x1a54.VTable0x44(static_cast<undefined2>(m_unk0x221c + 0x4c), 0);
	m_unk0x1bbc.VTable0x44(static_cast<undefined2>(m_unk0x221c + 0x61), 0);

	if (m_unk0x221c < m_context->m_raceList.GetEntryCount()) {
		m_unk0x1904 = &m_context->m_raceList.GetEntries()[m_unk0x221c];
		LegoRacers::Context* context = m_context->m_context;
		::memcpy(context->m_unk0x2d, m_unk0x1904->GetName(), sizeof(GolName));

		LegoU8 mask = static_cast<LegoU8>(1 << m_context->m_raceList.GetEntryIndex(m_unk0x1904));
		for (LegoU32 i = 0; i < sizeOfArray(context->m_raceSlots); i++) {
			LegoRacers::RaceSlot* slot = &context->m_raceSlots[i];
			RaceNameEntry* raceNameEntry = m_unk0x1904->GetRaceNameEntry(i);
			if (raceNameEntry) {
				::memcpy(slot->m_unk0x08, raceNameEntry->GetName(), sizeof(GolName));
				::memcpy(slot->m_raceName, raceNameEntry->GetUnk0x0cName(), sizeof(GolName));
				slot->m_unk0x00 = TRUE;
				slot->m_unk0x04 = raceNameEntry->GetUnk0x2c();
			}
			else {
				slot->m_unk0x08[0] = '\0';
				slot->m_raceName[0] = '\0';
				slot->m_unk0x00 = FALSE;
				slot->m_unk0x04 = 0;
			}
		}

		if (m_context->m_unk0x258.GetUnk0x18c4().FUN_0042f1f0() & mask) {
			m_unk0x1f24.VTable0x44(5);
			m_unk0x1860.ClearFlags(2);
		}
		else {
			m_unk0x1f24.VTable0x48(5);
			m_unk0x1c34.VTable0x4c(0);
			m_unk0x1860.SetFlags(2);
		}

		m_unk0x2218 = 0;
		m_unk0x2220 = 0;
		FUN_0047a2b0();
	}
}

// FUNCTION: LEGORACERS 0x0047a250
void CircuitRaceScreen::VTable0x84()
{
	if (m_unk0x2214 && m_unk0x2214->IsActive()) {
		m_context->m_menuAnimations.Deactivate(m_unk0x2214);
		m_unk0x2214 = NULL;
	}

	if (m_unk0x360 == 2) {
		m_context->m_menuStack.Pop();
		return;
	}

	m_context->m_menuStack.Push(0x13);
}

// FUNCTION: LEGORACERS 0x0047a2b0
void CircuitRaceScreen::FUN_0047a2b0()
{
	GolString string;
	GolName frameName;
	GolName driverName;
	driverName[0] = '\0';

	RaceNameEntry* raceNameEntry = m_unk0x1904->GetRaceNameEntry(m_unk0x2220);
	if (raceNameEntry) {
		::memcpy(frameName, raceNameEntry->GetUnk0x14Name(), sizeof(GolName));
		::memcpy(driverName, raceNameEntry->GetUnk0x1cName(), sizeof(GolName));

		GolNameTable* frameNames = &m_unk0x368.m_unk0x58;
		SaffronQuartz0x2c::Frame0xb8* frame;
		if (!frameNames->GetNameEntries()) {
			frame = NULL;
		}
		else {
			frame = static_cast<SaffronQuartz0x2c::Frame0xb8*>(frameNames->GetName(frameName));
		}

		if (frame && frame != m_unk0x368.m_unk0x2b0) {
			m_unk0x368.FUN_00466d00(frame);
			m_unk0x368.m_unk0x2b0->SetFlags(SaffronQuartz0x2c::Frame0xb8::c_flagLoop);
			m_unk0x2218 = 2000;
			FUN_00488cb0(m_unk0x2220 + m_unk0x221c * 4);
			raceNameEntry->CopyDisplayString(&string);
			m_unk0x1acc.VTable0x40(&string, 0);
		}
	}
	else {
		m_unk0x2218 = 2000;
	}

	if (driverName[0]) {
		FUN_00488b40(driverName);
	}

	m_unk0x2224 = TRUE;
}

// FUNCTION: LEGORACERS 0x0047a3f0
LegoBool32 CircuitRaceScreen::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x2214 && !m_unk0x2214->IsActive()) {
		m_unk0x2214 = NULL;
	}

	if (p_elapsed > m_unk0x2218 && m_unk0x221c != 6) {
		m_unk0x2220 = (m_unk0x2220 + 1) & 3;
		FUN_0047a2b0();
	}
	else {
		m_unk0x2218 -= p_elapsed;
	}

	if (m_unk0x2218 < 250 && !m_context->m_menuAnimations.HasActive() && m_unk0x221c != 6) {
		if (m_unk0x2214 && m_unk0x2214->IsActive()) {
			m_context->m_menuAnimations.Deactivate(m_unk0x2214);
			m_unk0x2214 = NULL;
		}

		GolCamera* rectSource = m_unk0x368.m_unk0x2b0->FUN_00406890();
		m_unk0x2214 = m_context->m_menuAnimations.Activate(250, FALSE, NULL, rectSource);
	}

	LegoBool32 result = ImaginaryChisel0x658::VTable0x78(p_elapsed);
	if (m_unk0x2224) {
		if (m_unk0x2214 && m_unk0x2214->IsActive()) {
			m_context->m_menuAnimations.Deactivate(m_unk0x2214);
			m_unk0x2214 = NULL;
		}

		m_unk0x368.m_unk0x2b0->FUN_00406390(0);
		GolCamera* rectSource = m_unk0x368.m_unk0x2b0->FUN_00406890();
		m_unk0x2214 = m_context->m_menuAnimations.Activate(250, TRUE, NULL, rectSource);
		m_unk0x2224 = FALSE;
	}

	return result;
}
