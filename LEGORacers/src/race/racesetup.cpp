#include "race/racesetup.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable.h"
#include "race/raceforcefeedback.h"
#include "race/racehud.h"
#include "race/racer/racerouterecord.h"
#include "race/racestate.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"
#include "util/carshadowrenderstate.h"

DECOMP_SIZE_ASSERT(RaceSetup, 0x1c)

extern LegoFloat g_minSoundPan;
extern const LegoFloat g_rubberBandScale;

// FUNCTION: LEGORACERS 0x0043a410
RaceSetup::RaceSetup()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a420
RaceSetup::~RaceSetup()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0043a430
void RaceSetup::Reset()
{
	m_racers = NULL;
	m_racerCount = 0;
	m_updateDelayMs = 0;
	m_rubberBandBoost = 0.0f;
}

// FUNCTION: LEGORACERS 0x0043a440
void RaceSetup::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043a450
void RaceSetup::Initialize(Racer* p_racers, LegoU32 p_racerCount)
{
	if (m_racers) {
		Destroy();
	}

	m_racers = p_racers;
	m_racerCount = p_racerCount;
	m_updateDelayMs = 15000;
}

// FUNCTION: LEGORACERS 0x0043a480
LegoU32 RaceSetup::Update(LegoU32 p_elapsedMs)
{
	LegoU32 delayMs = m_updateDelayMs;
	LegoFloat bestProgress = -1.0f;
	LegoU32 result;

	if (p_elapsedMs > delayMs) {
		result = m_racerCount;
		LegoU32 racerIndex = 0;
		LegoU32 ignoredState;
		m_updateDelayMs = 0;

		if (result <= 0) {
			goto ResetRacerPacing;
		}

		ignoredState = 2;
		do {
			LegoU32 state = m_racers[racerIndex].m_controlMode;
			if (state != ignoredState && m_racers[racerIndex].GetRaceProgress() > bestProgress) {
				bestProgress = m_racers[racerIndex].GetRaceProgress();
			}

			result = m_racerCount;
			racerIndex++;
		} while (racerIndex < result);

		if (bestProgress == g_minSoundPan) {
		ResetRacerPacing:
			result = m_racerCount;
			LegoU32 index = 0;
			if (result > 0) {
				LegoU32 pushedMask = RacerPhysics::c_flagRoutePushed;
				do {
					Racer* racer = &m_racers[index];
					if (!(racer->m_flags & c_rubberBandFlags)) {
						LegoU32 physicsFlags = racer->m_physics.m_flags;
						racer->m_physics.m_routeBaseSpeed = 1.0f;
						if (!(pushedMask & physicsFlags)) {
							racer->m_physics.m_routeTargetSpeed = 1.0f;
						}
					}

					result = m_racerCount;
					index++;
				} while (index < result);
			}
		}
		else {
			result = m_racerCount;
			racerIndex = 0;
			if (result > 0) {
				LegoU32 pushedMask = RacerPhysics::c_flagRoutePushed;
				do {
					if (racerIndex) {
						if (!(m_racers[racerIndex].m_flags & c_rubberBandFlags)) {
							if (m_racers[racerIndex].GetRaceProgress() > bestProgress) {
								LegoFloat adjustment = 1.0f - g_rubberBandScale;
								adjustment += m_rubberBandBoost;
								RacerPhysics* physics = &m_racers[racerIndex].m_physics;
								LegoU32 physicsFlags = physics->m_flags;
								physics->m_routeBaseSpeed = adjustment;
								if (!(pushedMask & physicsFlags)) {
									physics->m_routeTargetSpeed = adjustment;
								}
							}
							else if (m_racers[racerIndex].GetRaceProgress() < bestProgress) {
								LegoFloat adjustment = g_rubberBandScale + m_rubberBandBoost;
								adjustment += 1.0f;
								RacerPhysics* physics = &m_racers[racerIndex].m_physics;
								LegoU32 physicsFlags = physics->m_flags;
								physics->m_routeBaseSpeed = adjustment;
								if (!(pushedMask & physicsFlags)) {
									physics->m_routeTargetSpeed = adjustment;
								}
							}
						}
					}

					result = m_racerCount;
					racerIndex++;
				} while (racerIndex < result);
			}
		}
	}
	else {
		result = delayMs - p_elapsedMs;
		m_updateDelayMs = result;
	}

	return result;
}
