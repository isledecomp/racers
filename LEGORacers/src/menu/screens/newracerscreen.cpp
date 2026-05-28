#include "menu/screens/newracerscreen.h"

#include "menu/crimsonsun0xa4.h"
#include "menu/menuscreenid.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"
#include "save/peridottrace0x4e0.h"

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
LegoBool32 NewRacerScreen::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	m_unk0x76c = p_context->m_unk0x4b40.GetUnk0x84();
	p_createParams->m_cursorHelper->SetCursorEnabled(FALSE);
	return ImaginaryTool0x368::VTable0x8c(p_context, p_createParams) != FALSE;
}

// STUB: LEGORACERS 0x00482160
void NewRacerScreen::VTable0x4c()
{
	FUN_0046bef0(&m_unk0x368, 0x49, 0x49);

	LegoU32 memoryCardIndex = m_unk0x76c;
	MenuToolContext0x4bc8* context = m_context;
	LegoBool32 active = TRUE;
	PeridotTraceBase0x24* trace;

	if (memoryCardIndex >= 2) {
		trace = &context->m_unk0x258.GetUnk0x108();
		if (!trace->GetAvailableRecordCount()) {
			FUN_0046bef0(&m_unk0x3c4, 0x53, 0x53);
			FUN_0046bef0(&m_unk0x420, 0x54, 0x54);
			FUN_0047fdc0(&m_unk0x47c, 0x99, 0x46, 0x72);
			FUN_0046c730(&m_unk0x47c, 0xbb);
			m_cursorHelper->SetCursorEnabled(active);
			return;
		}
	}
	else {
		PeridotTrace0x4e0* memoryCardTrace = &context->m_unk0x258.GetUnk0xa58()[memoryCardIndex];
		trace = memoryCardTrace;
		if (!memoryCardTrace->HasUnk0x4b4Flag0x01() || !memoryCardTrace->GetAvailableRecordCount()) {
			FUN_0046bef0(&m_unk0x3c4, 0x53, 0x53);
			FUN_0046bef0(&m_unk0x420, 0x54, 0x54);
			FUN_0047fdc0(&m_unk0x47c, 0x99, 0x46, 0x72);
			FUN_0046c730(&m_unk0x47c, 0xbc);
			m_cursorHelper->SetCursorEnabled(active);
			return;
		}
	}

	if (m_context->m_unk0x4b40.GetUnk0x78() & 8) {
		PeridotTraceBase0x24::Record* record = trace->FUN_0042b8f0(m_context->m_unk0x258.GetUnk0x1cfc().GetUnk0x248());
		m_unk0x360 = c_menuGarage;

		PeridotTraceBase0x24::Record* oldRecord = m_context->m_unk0x258.GetUnk0x1cfc().GetUnk0x248();
		if (oldRecord->m_unk0x08 == active && record->m_unk0x08 != active) {
			m_context->m_unk0x258.GetUnk0x108().FUN_0042b920(oldRecord);
		}

		m_context->m_unk0x258.GetUnk0x1cfc().SetUnk0x248(record);
		m_unk0x364 = active;
	}
	else {
		m_context->m_unk0x258.GetUnk0x1cfc().SetUnk0x248(trace->FUN_0042b880());
		m_unk0x360 = c_menuEditDriver;
		m_unk0x364 = active;
	}

	STUB(0x00482160);
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
void NewRacerScreen::VTable0x38(ObscureVantage0x58* p_unk0x04)
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

	m_cursorHelper->SetCursorEnabled(TRUE);
	return ImaginaryTool0x368::Destroy();
}
