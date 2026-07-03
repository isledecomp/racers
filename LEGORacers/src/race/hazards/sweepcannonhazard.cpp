#include "race/hazards/sweepcannonhazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazardmanager.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/actiontarget.h"
#include "race/powerups/racepowerupmanager.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SweepCannonHazard, 0x58)

extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_twoPi;

// GLOBAL: LEGORACERS 0x004b0b48
extern const LegoFloat g_sweepCannonRadiansToTableIndex = 162.974655f;

// GLOBAL: LEGORACERS 0x004b03f0
extern const LegoFloat g_hazardPi = 3.1415927f;

// GLOBAL: LEGORACERS 0x004b4270
extern const LegoFloat g_sweepCannonTrackedEntityZOffset = 17.0f;

// FUNCTION: LEGORACERS 0x0048b480
SweepCannonHazard::SweepCannonHazard()
{
	ClearFields();
}

// FUNCTION: LEGORACERS 0x0048b4f0
SweepCannonHazard::~SweepCannonHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b540
void SweepCannonHazard::ClearFields()
{
	m_trackedEntity = NULL;
	m_powerupManager = NULL;
	m_sweepMs = 0;
	m_cooldownMs = 0;
	m_periodMs = 0;
	m_sweepAngle = 0.0f;
	m_verticalRange = 0.0f;
	m_verticalBase = 0.0f;
	m_source.m_x = 0.0f;
	m_source.m_y = 0.0f;
	m_source.m_z = 0.0f;
	m_source.m_velocity.m_x = 0.0f;
	m_source.m_velocity.m_y = 0.0f;
	m_source.m_velocity.m_z = 0.0f;
	m_source.m_forward.m_x = 0.0f;
	m_source.m_forward.m_y = 0.0f;
	m_source.m_forward.m_z = 0.0f;
	m_mirror = 0;
}

// FUNCTION: LEGORACERS 0x0048b580
void SweepCannonHazard::Load(HazardContext* p_context, GolFileParser* p_parser)
{
	if (m_state) {
		Reset();
	}

	GolName name;
	name[0] = '\0';

	m_mirror = p_context->GetMirror();
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case HazardManager::HzbTxtParser::e_entity:
			::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
			break;
		case HazardManager::HzbTxtParser::e_source:
			m_source.m_x = p_parser->ReadFloat();
			m_source.m_y = p_parser->ReadFloat();
			m_source.m_z = p_parser->ReadFloat();
			if (m_mirror) {
				m_source.m_y = -m_source.m_y;
			}
			break;
		case HazardManager::HzbTxtParser::e_period:
			m_periodMs = p_parser->ReadInteger();
			break;
		case HazardManager::HzbTxtParser::e_trigger:
			m_triggerId = p_parser->ReadInteger();
			break;
		case HazardManager::HzbTxtParser::e_sweep:
			m_sweepAngle = p_parser->ReadFloat();
			m_verticalRange = p_parser->ReadFloat();
			m_verticalBase = p_parser->ReadFloat();
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
	}

	m_powerupManager = p_context->GetPowerupManager();
	if (name[0]) {
		m_trackedEntity = p_context->GetTrackDatabase()->FindAnimatedEntity(name);
	}
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048b700
LegoS32 SweepCannonHazard::Reset()
{
	OnDeactivate(NULL);
	ClearFields();
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048b720
void SweepCannonHazard::OnActivate(void*)
{
	m_cooldownMs = c_actionCooldownMs;
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048b740
void SweepCannonHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		ActionTarget target;
		Hazard::Update(p_elapsedMs);

		LegoU32 elapsedMs = static_cast<LegoU32>(p_elapsedMs);
		m_sweepMs += elapsedMs;
		if (m_sweepMs >= m_periodMs) {
			m_sweepMs = 0;
		}

		LegoU32 currentTime = m_sweepMs;
		LegoU32 halfPeriod = m_periodMs >> 1;
		LegoFloat lateralAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								 static_cast<LegoFloat>(static_cast<LegoS32>(halfPeriod));
		lateralAngle *= m_sweepAngle;
		if (currentTime > halfPeriod) {
			lateralAngle = g_hazardPi - lateralAngle;
		}

		LegoS32 index = static_cast<LegoS32>(lateralAngle * g_sweepCannonRadiansToTableIndex) & 0x3ff;
		m_source.m_forward.m_x = g_cosineTable[index];

		index = (0xffffff00 - static_cast<LegoS32>(lateralAngle * g_negativeRadiansToTableIndex)) & 0x3ff;
		m_source.m_forward.m_y = g_cosineTable[index];
		if (m_mirror) {
			m_source.m_forward.m_y = -m_source.m_forward.m_y;
		}

		LegoU32 quarterPeriod = m_periodMs >> 2;
		LegoFloat verticalAngle = static_cast<LegoFloat>(static_cast<LegoS32>(currentTime)) /
								  static_cast<LegoFloat>(static_cast<LegoS32>(quarterPeriod));
		verticalAngle *= g_twoPi;
		verticalAngle *= g_sweepCannonRadiansToTableIndex;
		index = static_cast<LegoS32>(verticalAngle) & 0x3ff;
		m_source.m_forward.m_z = g_cosineTable[index] * m_verticalRange + m_verticalBase;

		GolMath::NormalizeVector3(m_source.m_forward, &m_source.m_forward);

		if (m_trackedEntity) {
			m_trackedEntity->GetPosition(&m_source);
			m_source.m_z -= g_sweepCannonTrackedEntityZOffset;
		}

		m_cooldownMs += elapsedMs;
		if (m_cooldownMs >= c_actionCooldownMs) {
			target.m_source = &m_source;
			m_powerupManager->SetAimTarget(&target);
			m_powerupManager->UseRedPowerup(NULL, 2);
			m_powerupManager->SetAimTarget(NULL);
			m_cooldownMs = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void SweepCannonHazard::OnDeactivate(void*)
{
	m_state = c_stateLoaded;
}
