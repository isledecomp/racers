#include "race/hazards/cursedrophazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/actiontarget.h"
#include "race/powerups/racepowerupmanager.h"
#include "types.h"

DECOMP_SIZE_ASSERT(CurseDropHazard, 0x18)

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

static const GolVec3 g_curseDropActionDirection = {1.0f, 0.0f, 0.0f};

static const GolVec3 g_curseDropActionPositions[] = {
	{-357.582703f, 458.126984f, -11.665112f},
	{-351.203125f, 518.713013f, -94.215683f},
	{-362.258179f, 397.303925f, -94.959518f},
};

#pragma code_seg(".text$hazard_masked_update")
// FUNCTION: LEGORACERS 0x0048b060 FOLDED
void CurseDropHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);
	}
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0048b2f0
CurseDropHazard::CurseDropHazard()
{
	m_powerupManager = NULL;
	m_mirror = 0;
}

// FUNCTION: LEGORACERS 0x0048b330
CurseDropHazard::~CurseDropHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048b380
void CurseDropHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_powerupManager = p_context->GetPowerupManager();
	m_mirror = p_context->GetMirror();
	m_triggerId = 8;
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048b3c0
void CurseDropHazard::OnActivate(void*)
{
	ActionTarget target;
	target.m_direction = g_curseDropActionDirection;

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	LegoS32 positionIndex = g_randomTable[g_randomTableIndex] % c_positionCount;
	target.m_source = NULL;
	target.m_position = g_curseDropActionPositions[positionIndex];
	if (m_mirror) {
		target.m_position.m_y = -target.m_position.m_y;
	}

	m_powerupManager->SetAimTarget(&target);
	m_powerupManager->UseYellowPowerup(NULL, 3);
	m_powerupManager->SetAimTarget(NULL);
	m_state = c_stateActive;
}

LegoS32 CurseDropHazard::Reset()
{
	OnDeactivate(NULL);
	m_powerupManager = NULL;
	m_mirror = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048d470 FOLDED
void CurseDropHazard::OnDeactivate(void*)
{
	m_state = c_stateLoaded;
}
