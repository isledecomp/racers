#include "race/hazards/hammerhazard.h"

#include "decomp.h"
#include "golanimatedentity.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazards/hazardcontext.h"
#include "race/raceeventtable.h"
#include "types.h"
#include "world/golworlddatabase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(HammerHazard, 0x18)

// GLOBAL: LEGORACERS 0x004b4414
extern const LegoFloat g_hammerStrikeStart0 = 22.0f;

// GLOBAL: LEGORACERS 0x004b4418
extern const LegoFloat g_hammerStrikeEnd0 = 28.0f;

// GLOBAL: LEGORACERS 0x004b441c
extern const LegoFloat g_hammerStrikeStart1 = 72.0f;

// GLOBAL: LEGORACERS 0x004b4420
extern const LegoFloat g_hammerStrikeEnd1 = 78.0f;

// GLOBAL: LEGORACERS 0x004b4424
extern const LegoFloat g_hammerRaisedStart0 = 0.0f;

// GLOBAL: LEGORACERS 0x004b4428
extern const LegoFloat g_hammerRaisedEnd0 = 20.0f;

// GLOBAL: LEGORACERS 0x004b442c
extern const LegoFloat g_hammerRaisedStart1 = 40.0f;

// GLOBAL: LEGORACERS 0x004b4430
extern const LegoFloat g_hammerRaisedEnd1 = 60.0f;

// FUNCTION: LEGORACERS 0x0048cff0
HammerHazard::HammerHazard()
{
	m_entity = NULL;
}

// FUNCTION: LEGORACERS 0x0048d030
HammerHazard::~HammerHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048d080
void HammerHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0x32;
	m_eventTable = p_context->GetEventTable();

	GolName name;
	::strncpy(name, "rkhamm", sizeof(name));
	name[6] = '0';
	name[7] = '2';

	m_entity = p_context->GetTrackDatabase()->FindAnimatedEntity(name);
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048d110
LegoS32 HammerHazard::Reset()
{
	OnDeactivate(NULL);
	m_entity = NULL;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d130
void HammerHazard::OnActivate(void*)
{
	m_unk0x14 = 7;
	m_state = c_stateActive;
}

// FUNCTION: LEGORACERS 0x0048d150
void HammerHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state == c_stateLoaded) {
		return;
	}

	Hazard::Update(p_elapsedMs);
	if (!m_entity) {
		return;
	}

	LegoFloat frame = m_entity->GetPartTimeMs();
	LegoU32 state = m_unk0x14;
	LegoU32 active = state;
	active &= 1;
	if (active) {
		if ((frame > g_hammerStrikeStart0 && frame < g_hammerStrikeEnd0) ||
			(frame > g_hammerStrikeStart1 && frame < g_hammerStrikeEnd1)) {
			m_eventTable->FireEventsAt(0x2b, 0x2b, NULL);
			m_unk0x14 &= ~1;
		}
	}
	else if (
		(frame > g_hammerRaisedStart0 && frame < g_hammerRaisedEnd0) ||
		(frame > g_hammerRaisedStart1 && frame < g_hammerRaisedEnd1)
	) {
		m_unk0x14 = state | 1;
	}
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void HammerHazard::OnDeactivate(void*)
{
	m_state = c_stateLoaded;
}
