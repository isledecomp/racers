#include "race/hazards/codepuzzlehazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "mabmaterialanimation.h"
#include "mabmaterialtrack.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "types.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(CodePuzzleHazard, 0x3c)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x0048d240
CodePuzzleHazard::CodePuzzleHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d2b0
CodePuzzleHazard::~CodePuzzleHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d300
void CodePuzzleHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = -1;
	m_eventTable = p_context->GetEventTable();

	GolWorldDatabase* worldDatabase = p_context->GetTrackDatabase();
	GolModelEntity* modelEntity;
	if (!worldDatabase->GetModelEntityEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetModelEntityByName("mmcode1");
	}
	m_codeModel1 = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetModelEntityEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetModelEntityByName("mmcode2");
	}
	m_codeModel2 = modelEntity;

	worldDatabase = p_context->GetTrackDatabase();
	if (!worldDatabase->GetModelEntityEntries()) {
		modelEntity = NULL;
	}
	else {
		modelEntity = worldDatabase->GetModelEntityByName("mmcode3");
	}
	m_codeModel3 = modelEntity;

	MabMaterialAnimation* animation = p_context->GetTrackDatabase()->GetMaterialAnimation(0);
	m_codeItem1 = &animation->GetUnk0x0c()[5];
	m_codeItem2 = &animation->GetUnk0x0c()[4];
	m_codeItem3 = &animation->GetUnk0x0c()[3];
	m_codeItem1->SetUnk0x0c(0.003f);
	m_codeItem2->SetUnk0x0c(0.004f);
	m_codeItem3->SetUnk0x0c(0.005f);
	m_materialFrames = animation->GetUnk0x04();
	m_materialFrameCount = animation->GetUnk0x08();
	m_state = 1;
	OnActivate(NULL);
}

// FUNCTION: LEGORACERS 0x0048d400
LegoS32 CodePuzzleHazard::Reset()
{
	return ClearFields();
}

// FUNCTION: LEGORACERS 0x0048d410
LegoS32 CodePuzzleHazard::ClearFields()
{
	m_codeModel1 = NULL;
	m_codeModel2 = NULL;
	m_codeModel3 = NULL;
	m_codeItem1 = NULL;
	m_codeItem2 = NULL;
	m_codeItem3 = NULL;
	m_codeEvent1 = 0;
	m_codeEvent2 = 0;
	m_codeEvent3 = 0;
	m_resetEvent1 = 0;
	m_resetEvent2 = 0;
	m_resetEvent3 = 0;
	m_codeProgress = 0;
	m_delayMs = 0;
	m_materialFrames = NULL;
	m_materialFrameCount = 0;
	return 0;
}

// FUNCTION: LEGORACERS 0x0048d450
void CodePuzzleHazard::OnActivate(void*)
{
	m_codeProgress = 0;
	ResetCodeModels();
	m_delayMs = 1;
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void CodePuzzleHazard::OnDeactivate(void*)
{
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0048d480
void CodePuzzleHazard::OnEventStart(LegoS32 p_unk0x04, void* p_unk0x08)
{
	if (p_unk0x04 == m_resetEvent1 || p_unk0x04 == m_resetEvent2 || p_unk0x04 == m_resetEvent3) {
		m_codeProgress = 0;
	}
	else if (p_unk0x04 == m_codeEvent1) {
		m_codeProgress = 1;
	}
	else if (p_unk0x04 == m_codeEvent2) {
		if (m_codeProgress == 1) {
			m_codeProgress = 3;
		}
	}
	else if (p_unk0x04 == m_codeEvent3 && m_codeProgress == 3) {
		m_eventTable->FireEventsAt(c_successFirstEvent, c_successFirstEvent, NULL);
		m_codeProgress = 0;
		m_codeItem1->FUN_10025da0(m_codeItem1->GetUnk0x00(), m_codeItem1->GetUnk0x04(), TRUE);
		m_codeItem2->FUN_10025da0(m_codeItem2->GetUnk0x00(), m_codeItem2->GetUnk0x04(), TRUE);
		m_codeItem3->FUN_10025da0(m_codeItem3->GetUnk0x00(), m_codeItem3->GetUnk0x04(), TRUE);
		m_delayMs = c_delayMs;
		ResetCodeModels();
		m_eventTable->StartEventsAt(c_successSecondEvent, NULL);
	}

	switch (p_unk0x04) {
	case 200:
	case 202:
	case 204:
		m_eventTable->FireEventsAt(c_goodInputEvent, c_goodInputEvent, static_cast<GolVec3*>(p_unk0x08));
		return;
	case 201:
	case 203:
	case 205:
		m_eventTable->FireEventsAt(c_badInputEvent, c_badInputEvent, static_cast<GolVec3*>(p_unk0x08));
		return;
	case 207:
		if (m_codeEvent1 == c_firstCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	case 208:
		if (m_codeEvent2 == c_secondCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	case 209:
		if (m_codeEvent3 == c_thirdCodeEvent) {
			m_eventTable->FireEventsAt(c_correctCodeEvent, c_correctCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		else {
			m_eventTable->FireEventsAt(c_wrongCodeEvent, c_wrongCodeEvent, static_cast<GolVec3*>(p_unk0x08));
		}
		break;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x0048d660
void CodePuzzleHazard::Update(undefined4 p_elapsedMs)
{
	LegoU32 timer = m_delayMs;
	if (timer > 0) {
		LegoU32 elapsedMs = p_elapsedMs;
		if (elapsedMs >= timer) {
			m_delayMs = 0;
			m_eventTable->EndEventsAt(c_successSecondEvent, NULL);

			if (m_codeEvent1 == c_firstCodeEvent) {
				m_codeItem1->FUN_00410480();
			}
			else {
				m_codeItem1->FUN_00410490();
			}
			m_codeItem1->FUN_004104c0(0, m_materialFrames, m_materialFrameCount);
			m_codeItem1->FUN_00410470();

			if (m_codeEvent2 == c_secondCodeEvent) {
				m_codeItem2->FUN_00410480();
			}
			else {
				m_codeItem2->FUN_00410490();
			}
			m_codeItem2->FUN_004104c0(0, m_materialFrames, m_materialFrameCount);
			m_codeItem2->FUN_00410470();

			if (m_codeEvent3 == c_thirdCodeEvent) {
				m_codeItem3->FUN_00410480();
			}
			else {
				m_codeItem3->FUN_00410490();
			}
			m_codeItem3->FUN_004104c0(0, m_materialFrames, m_materialFrameCount);
			m_codeItem3->FUN_00410470();
		}
		else {
			m_delayMs = timer - elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048d730
void CodePuzzleHazard::ResetCodeModels()
{
	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	LegoS32 random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_codeEvent1 = c_firstCodeEvent;
		m_resetEvent1 = c_firstCodeEvent + 1;
	}
	else {
		m_codeEvent1 = c_firstCodeEvent + 1;
		m_resetEvent1 = c_firstCodeEvent;
	}

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_codeEvent2 = c_secondCodeEvent;
		m_resetEvent2 = c_secondCodeEvent + 1;
	}
	else {
		m_codeEvent2 = c_secondCodeEvent + 1;
		m_resetEvent2 = c_secondCodeEvent;
	}

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex];
	if (random % 2) {
		m_codeEvent3 = c_thirdCodeEvent;
		m_resetEvent3 = c_thirdCodeEvent + 1;
	}
	else {
		m_codeEvent3 = c_thirdCodeEvent + 1;
		m_resetEvent3 = c_thirdCodeEvent;
	}
}
