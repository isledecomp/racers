#include "menu/screens/newracerscreen.h"

#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenid.h"
#include "save/savegame.h"

DECOMP_SIZE_ASSERT(NewRacerScreen, 0x770)

// FUNCTION: LEGORACERS 0x00481fe0
NewRacerScreen::NewRacerScreen()
{
	m_unk0x76c = 0;
}

// FUNCTION: LEGORACERS 0x00482090
NewRacerScreen::~NewRacerScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00482120
LegoBool32 NewRacerScreen::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x76c = p_context->m_modelBuilder.GetUnk0x84();
	p_createParams->m_cursor->SetCursorEnabled(FALSE);
	return MenuGameScreen::VTable0x8c(p_context, p_createParams) != FALSE;
}

// STUB: LEGORACERS 0x00482160
void NewRacerScreen::VTable0x4c()
{
	CreateImage(&m_unk0x368, 0x49, 0x49);

	LegoU32 memoryCardIndex = m_unk0x76c;
	MenuGameContext* context = m_context;
	LegoBool32 active = TRUE;
	SaveRecordList* records;

	if (memoryCardIndex >= 2) {
		records = &context->m_saveSystem.GetSessionSave();
		if (!records->GetAvailableRecordCount()) {
			CreateImage(&m_unk0x3c4, 0x53, 0x53);
			CreateImage(&m_unk0x420, 0x54, 0x54);
			FUN_0047fdc0(&m_unk0x47c, 0x99, 0x46, 0x72);
			FUN_0046c730(&m_unk0x47c, 0xbb);
			m_cursor->SetCursorEnabled(active);
			return;
		}
	}
	else {
		MemoryCardSaveGame* memoryCardSave = &context->m_saveSystem.GetMemoryCardSaves()[memoryCardIndex];
		records = memoryCardSave;
		if (!memoryCardSave->HasUnk0x4b4Flag0x01() || !memoryCardSave->GetAvailableRecordCount()) {
			CreateImage(&m_unk0x3c4, 0x53, 0x53);
			CreateImage(&m_unk0x420, 0x54, 0x54);
			FUN_0047fdc0(&m_unk0x47c, 0x99, 0x46, 0x72);
			FUN_0046c730(&m_unk0x47c, 0xbc);
			m_cursor->SetCursorEnabled(active);
			return;
		}
	}

	if (m_context->m_modelBuilder.GetUnk0x78() & 8) {
		SaveRecordList::Record* record =
			records->FUN_0042b8f0(m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord());
		m_unk0x360 = c_menuGarage;

		SaveRecordList::Record* oldRecord = m_context->m_saveSystem.GetActiveRecord().GetSelectedRecord();
		if (oldRecord->m_unk0x08 == active && record->m_unk0x08 != active) {
			m_context->m_saveSystem.GetSessionSave().FUN_0042b920(oldRecord);
		}

		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(record);
		m_unk0x364 = active;
	}
	else {
		m_context->m_saveSystem.GetActiveRecord().SetSelectedRecord(records->AllocateRecord());
		m_unk0x360 = c_menuEditDriver;
		m_unk0x364 = active;
	}
}

// FUNCTION: LEGORACERS 0x00482310
void NewRacerScreen::VTable0x84()
{
	m_context->m_menuStack.Pop();

	if (m_unk0x360 == c_menuGarage) {
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(c_menuGarage);
	}
}

// FUNCTION: LEGORACERS 0x00482350
void NewRacerScreen::VTable0x38(MenuWidget* p_unk0x04)
{
	if (p_unk0x04 == &m_unk0x47c) {
		m_unk0x284->FUN_00468cf0();
		m_unk0x364 = TRUE;
		m_unk0x360 = c_menuGarage;
	}
}

// FUNCTION: LEGORACERS 0x004849c0 FOLDED
LegoBool32 NewRacerScreen::Destroy()
{
	if (!m_initialized) {
		return TRUE;
	}

	m_cursor->SetCursorEnabled(TRUE);
	return MenuGameScreen::Destroy();
}
