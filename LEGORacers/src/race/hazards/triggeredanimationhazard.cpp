#include "race/hazards/triggeredanimationhazard.h"

#include "cmbmodelpart.h"
#include "cmbmodelpartdata.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golnametable.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "render/gold3drenderdevice.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(TriggeredAnimationHazard, 0x30)

// FUNCTION: LEGORACERS 0x0048ed10
TriggeredAnimationHazard::TriggeredAnimationHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048ed80
TriggeredAnimationHazard::~TriggeredAnimationHazard()
{
	Reset();
}

// STUB: LEGORACERS 0x0048edd0
void TriggeredAnimationHazard::ClearFields()
{
	m_triggerId = -1;
	m_entities[0] = NULL;
	m_entities[1] = NULL;
	m_entities[2] = NULL;
	m_entities[3] = NULL;
	m_collider = NULL;
	m_unk0x24.Clear();
}

// FUNCTION: LEGORACERS 0x0048ee00
void TriggeredAnimationHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName name;
	name[0] = '\0';

	GolName modelNames[c_entityCount];
	LegoS32 i;
	for (i = 0; i < c_entityCount; i++) {
		modelNames[i][0] = '\0';
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		GolName* modelName = modelNames;
		do {
			switch (token) {
			case HazardManager::HzbTxtParser::e_trigger:
				m_triggerId = p_parser->ReadInteger();
				break;
			case HazardManager::HzbTxtParser::e_collider:
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
				break;
			case HazardManager::HzbTxtParser::e_entity:
				::strncpy(*modelName, p_parser->ReadStringWithMaxLength(sizeof(*modelName)), sizeof(*modelName));
				modelName++;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
		} while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly);
	}

	m_eventTable = p_context->GetEventTable();
	GolNameTable* nameTable = p_context->GetColliderTable();
	m_collider = nameTable->GetNameEntries() == NULL ? NULL : static_cast<ColliderRecord*>(nameTable->GetName(name));

	GolAnimatedEntity** entity = m_entities;
	GolName* modelName = modelNames;
	LegoS32 count = c_entityCount;
	do {
		if ((*modelName)[0] != '\0') {
			*entity = p_context->GetTrackDatabase()->FindAnimatedEntity(*modelName);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
		}
		entity++;
		modelName++;
	} while (--count);

	for (i = 0; i < 3; i++) {
		(&m_unk0x24.m_x)[i] = m_entities[0]->GetModelDistance(i);
	}
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048ef50
LegoS32 TriggeredAnimationHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048ef70
void TriggeredAnimationHazard::OnActivate(void*)
{
	GolAnimatedEntity** entity = m_entities;
	LegoS32 count = c_entityCount;
	do {
		if (*entity != NULL) {
			for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
				(*entity)->SetModelDistance(i, 0.0f);
			}
			(*entity)->SetFlags((*entity)->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);
		}
		entity++;
	} while (--count);

	m_eventTable->FireEventsAt(9, 9, NULL);
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048efe0
void TriggeredAnimationHazard::OnDeactivate(void*)
{
	{
		LegoU32 i;
		for (i = 0; i < c_entityCount; i++) {
			GolAnimatedEntity* entity = m_entities[i];
			if (entity != NULL && !entity->IsPartAnimationDone()) {
				return;
			}
		}
	}

	LegoS32 i;
	for (i = 0; i < c_entityCount; i++) {
		GolAnimatedEntity* entity = m_entities[i];
		if (entity != NULL) {
			entity->SetFlags(entity->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);
		}
	}

	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048f030
void TriggeredAnimationHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);

		if (m_collider != NULL) {
			m_collider->m_flags |= ColliderRecord::c_flagBit16;
			m_collider->m_flags |= ColliderRecord::c_flagBit17;
		}

		if (m_entities[0]->IsPartAnimationDone()) {
			OnDeactivate(NULL);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048f080
void TriggeredAnimationHazard::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	for (LegoS32 i = 0; i < c_entityCount; i++) {
		GolAnimatedEntity** entity = &m_entities[i];
		if (*entity != NULL) {
			LegoS32 j;
			LegoFloat* modelDistances = &m_unk0x24.m_x;
			for (j = 0; j < c_modelDistanceCount; j++) {
				(*entity)->SetModelDistance(j, modelDistances[j]);
			}

			CmbModelPartData* partData = (*entity)->GetModelPart(0)->GetPartData();
			LegoU16 frameCount = partData[(*entity)->GetCurrentPartIndex()].GetFrameCount();
			LegoS32 alpha = static_cast<LegoS32>(
				(static_cast<LegoFloat>(frameCount) - (*entity)->GetPartTimeMs()) / static_cast<LegoFloat>(frameCount) *
				255.0f
			);

			p_renderer->SetAlphaOverride(alpha, TRUE);
			p_renderer->DrawModelEntity(*entity);
			p_renderer->ClearAlphaOverride();

			for (j = 0; j < c_modelDistanceCount; j++) {
				(*entity)->SetModelDistance(j, 0.0f);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0048f160
void TriggeredAnimationHazard::ResetState()
{
	if (m_collider != NULL) {
		m_collider->m_flags &= ~ColliderRecord::c_flagBit16;
		m_collider->m_flags &= ~ColliderRecord::c_flagBit17;
	}

	GolAnimatedEntity** entity = m_entities;
	LegoS32 count = c_entityCount;
	do {
		if (*entity != NULL) {
			(*entity)->SetFlags((*entity)->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
			(*entity)->PlayPartScaled(0, 0);
			(*entity)->ApplyPartAnimation(0);
			(*entity)->SetFlags((*entity)->GetFlags() & ~GolAnimatedEntity::c_flagPartAnimation);

			LegoFloat* modelDistances = &m_unk0x24.m_x;
			for (LegoS32 i = 0; i < c_modelDistanceCount; i++) {
				(*entity)->SetModelDistance(i, modelDistances[i]);
			}
		}
		entity++;
	} while (--count);

	m_state = c_stateLoaded;
}
