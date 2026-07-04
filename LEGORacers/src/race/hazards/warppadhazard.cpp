#include "race/hazards/warppadhazard.h"

#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "race/hazards/hazardcontext.h"
#include "race/powerups/actiontarget.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racer/racer.h"
#include "types.h"

DECOMP_SIZE_ASSERT(WarpPadHazard, 0x18)

// GLOBAL: LEGORACERS 0x004b4178
static const LegoFloat g_warpPadActionPositionX = 132.673004f;

// GLOBAL: LEGORACERS 0x004b417c
static const LegoFloat g_warpPadActionPositionY = 86.304001f;

// GLOBAL: LEGORACERS 0x004b4180
static const LegoFloat g_warpPadActionPositionZ = 14.722000f;

// GLOBAL: LEGORACERS 0x004b4188
static const LegoFloat g_warpPadActionDirectionX = 1.0f;

// GLOBAL: LEGORACERS 0x004b418c
static const LegoFloat g_warpPadActionDirectionY = -0.5f;

// GLOBAL: LEGORACERS 0x004b4190
static const LegoFloat g_warpPadActionDirectionZ = 0.0f;

// FUNCTION: LEGORACERS 0x0048ae80
WarpPadHazard::WarpPadHazard()
{
	m_powerupManager = NULL;
	m_mirror = 0;
}

// FUNCTION: LEGORACERS 0x0048aec0
WarpPadHazard::~WarpPadHazard()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0048af10
void WarpPadHazard::Load(HazardContext* p_context, GolFileParser*)
{
	if (m_state) {
		Reset();
	}

	m_triggerId = 0;
	m_powerupManager = p_context->GetPowerupManager();
	m_mirror = p_context->GetMirror();
	m_state = c_stateLoaded;
}

// FUNCTION: LEGORACERS 0x0048af50 FOLDED
LegoS32 WarpPadHazard::Reset()
{
	OnDeactivate(NULL);
	m_powerupManager = NULL;
	m_mirror = 0;
	return Hazard::Reset();
}

// FUNCTION: LEGORACERS 0x0048af80
void WarpPadHazard::OnActivate(void* p_racer)
{
	Racer* racer = static_cast<Racer*>(p_racer);
	if (racer && m_state != c_stateActive && !(racer->GetFlags() & c_flagGhost)) {
		ActionTarget target;
		target.m_direction.m_x = g_warpPadActionDirectionX;
		target.m_direction.m_y = g_warpPadActionDirectionY;
		target.m_direction.m_z = g_warpPadActionDirectionZ;
		target.m_position.m_x = g_warpPadActionPositionX;
		target.m_position.m_y = g_warpPadActionPositionY;
		target.m_position.m_z = g_warpPadActionPositionZ;

		if (m_mirror) {
			target.m_direction.m_y = -g_warpPadActionDirectionY;
			target.m_position.m_y = -g_warpPadActionPositionY;
		}

		target.m_source = NULL;
		m_powerupManager->SetAimTarget(&target);
		m_powerupManager->ActivateWarp(racer, 3);
		m_powerupManager->SetAimTarget(NULL);
		m_state = c_stateActive;
	}
}

// FUNCTION: LEGORACERS 0x0048b040
void WarpPadHazard::OnDeactivate(void* p_context)
{
	if (p_context) {
		m_state = c_stateLoaded;
	}
}

// FUNCTION: LEGORACERS 0x0048b060 FOLDED
void WarpPadHazard::Update(undefined4 p_elapsedMs)
{
	if (m_state != c_stateLoaded) {
		Hazard::Update(p_elapsedMs);
	}
}
