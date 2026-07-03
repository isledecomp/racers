#include "race/hazards/cannonballrainhazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/actiontarget.h"
#include "race/powerups/racepowerupmanager.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CannonballRainHazard, 0x44)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b43a0
extern const LegoFloat g_cannonballRainTransformOffsetScale = 35.0f;

// FUNCTION: LEGORACERS 0x0048c440
CannonballRainHazard::CannonballRainHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048c4b0
CannonballRainHazard::~CannonballRainHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048c500
void CannonballRainHazard::ClearFields()
{
	m_emitterEntity = NULL;
	m_powerupManager = NULL;
	m_timerMs = 0;
	m_intervalMs = 0;
	m_dropPosition.m_x = 0.0f;
	m_dropPosition.m_y = 0.0f;
	m_dropPosition.m_z = 0.0f;
	m_emitterPosition.m_x = 0.0f;
	m_emitterPosition.m_y = 0.0f;
	m_emitterPosition.m_z = 0.0f;
	m_materialName[0] = '\0';
}

// FUNCTION: LEGORACERS 0x0048c530
void CannonballRainHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName entityName;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case HazardManager::HzbTxtParser::e_material:
			::strncpy(
				m_materialName,
				p_parser->ReadStringWithMaxLength(sizeof(m_materialName)),
				sizeof(m_materialName)
			);
			break;
		case HazardManager::HzbTxtParser::e_entity:
			::strncpy(entityName, p_parser->ReadStringWithMaxLength(sizeof(entityName)), sizeof(entityName));
			break;
		case HazardManager::HzbTxtParser::e_trigger:
			m_triggerId = p_parser->ReadInteger();
			break;
		case HazardManager::HzbTxtParser::e_interval:
			m_intervalMs = p_parser->ReadInteger();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_powerupManager = p_context->GetPowerupManager();
	m_emitterEntity = p_context->GetTrackDatabase()->FindAnimatedEntity(entityName);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048c650
LegoS32 CannonballRainHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048c670
void CannonballRainHazard::OnActivate(void*)
{
	m_state = c_stateActive;
	m_timerMs = m_intervalMs;
}

// FUNCTION: LEGORACERS 0x0048c680
void CannonballRainHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs;
	Hazard::Update(p_elapsedMs);

	m_timerMs += elapsedMs;
	if (m_timerMs < m_intervalMs) {
		return;
	}

	m_emitterEntity->ApplyPartAnimation(0);
	GolSceneNode* node = m_emitterEntity->GetSceneNode(0);
	GolTransformBase* transform = node->GetTransform(1);

	GolVec3 position;
	transform->GetPosition(&position);

	GolVec3 right;
	transform->GetRight(&right);

	LegoFloat scale = m_emitterEntity->GetModel(0)->GetScale();
	scale *= m_emitterEntity->GetScale();
	position.m_x *= scale;
	position.m_y *= scale;
	position.m_z *= scale;

	m_emitterEntity->LocalToWorld(position, &m_emitterPosition);

	GolVec3 transformedRight;
	m_emitterEntity->RotateToWorld(right, &transformedRight);

	LegoFloat transformedOffset = transformedRight.m_x;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_emitterPosition.m_x -= transformedOffset;
	m_unk0x30 = 30.0f;
	transformedOffset = transformedRight.m_y;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_emitterPosition.m_y -= transformedOffset;
	transformedOffset = transformedRight.m_z;
	transformedOffset *= g_cannonballRainTransformOffsetScale;
	m_emitterPosition.m_z -= transformedOffset;

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	LegoS32 random = g_randomTable[g_randomTableIndex] % 4;
	m_dropPosition.m_x = static_cast<LegoFloat>(random) + m_emitterPosition.m_x - g_violetShoalTwo;

	g_randomTableIndex++;
	g_randomTableIndex &= c_randomTableMask;
	random = g_randomTable[g_randomTableIndex] % 4;
	m_dropPosition.m_y = static_cast<LegoFloat>(random) + m_emitterPosition.m_y - g_violetShoalTwo;
	if (m_dropPosition.m_x == m_emitterPosition.m_x && m_dropPosition.m_y == m_emitterPosition.m_y) {
		LegoFloat positionX = m_dropPosition.m_x;
		positionX += g_violetShoalTwo;
		m_dropPosition.m_x = positionX;
	}

	LegoFloat positionZ = m_emitterPosition.m_z;
	positionZ += 1.0f;
	m_dropPosition.m_z = positionZ;

	ActionTarget target;
	target.m_materialName = m_materialName;
	m_powerupManager->SetAimTarget(&target);
	m_powerupManager->UseRedPowerup(NULL, 0);
	m_powerupManager->SetAimTarget(NULL);
	m_timerMs = 0;
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void CannonballRainHazard::OnDeactivate(void*)
{
	m_state = c_stateLoaded;
}
