#include "race/powerups/hazardactionbase.h"

#include "camera/golcamera.h"
#include "decomp.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/racer/racer.h"
#include "race/triggerworld.h"

DECOMP_SIZE_ASSERT(ActionTarget, 0x1c)
DECOMP_SIZE_ASSERT(ActionSetup, 0x14)

#include <float.h>
#include <math.h>

const LegoFloat g_unk0x004b15f8 = 1.0f;

const LegoFloat g_unk0x004b15f4 = 1.0f;

const LegoFloat g_unk0x004b15e8 = 100.0f;

const LegoFloat g_unk0x004b15e4 = 10.0f;

const LegoFloat g_unk0x004b1478 = 0.727681994f;

const LegoFloat g_unk0x004b1470 = 0.155761003f;

const LegoFloat g_unk0x004b146c = 5.17852306f;

const LegoFloat g_unk0x004b1444 = 0.012f;

const LegoFloat g_unk0x004b1420 = 13.0f;

// GLOBAL: LEGORACERS 0x004b1428
const LegoFloat g_unk0x004b1428 = 3.0f;

// GLOBAL: LEGORACERS 0x004b1484
const LegoFloat g_unk0x004b1484 = 3.0f;

// GLOBAL: LEGORACERS 0x004b14a8
extern const LegoFloat g_brickScalePercentBase = 100.0f;

// GLOBAL: LEGORACERS 0x004b1628
const LegoFloat g_dropGroundOffset = 1.0f;

// GLOBAL: LEGORACERS 0x004b162c
const LegoFloat g_dropProbeDepth = 50.0f;

// FUNCTION: LEGORACERS 0x004562d0
HazardActionBase::HazardActionBase()
{
	m_raceState = NULL;
	m_collisionEvent = 0;
	m_collisionWorld = 0;
	m_unk0x024 = 0;
	m_ownerRacer = 0;
}

// FUNCTION: LEGORACERS 0x00456320
void HazardActionBase::OnEvent(LegoEventQueue::CallbackData* p_param)
{
	Racer* racer = static_cast<Racer*>(p_param->m_data);
	if (racer != m_ownerRacer) {
		if (racer->GetFlags() & Racer::c_flagShielded) {
			racer->AbsorbShieldHit();
			if (m_level < 3) {
				m_state = c_stateDone;
			}
		}
		else {
			OnHitRacer(racer);
		}
	}
}

// FUNCTION: LEGORACERS 0x00456360
void HazardActionBase::ComputeDropPosition(
	Racer* p_racer,
	GolVec3* p_position,
	GolBoundingVolume::HitTriangle* p_record
)
{
	GolVec3 start;
	p_racer->m_visuals.m_carEntity->GetPosition(&start);

	GolVec3 verticalOffset;
	verticalOffset.Clear();
	verticalOffset.m_z = g_dropProbeDepth;
	GolVec3 end;
	end = start - verticalOffset;

	GolBoundingVolume::HitTriangle record;
	if (p_record == NULL) {
		p_record = &record;
	}

	if (m_collisionWorld->IntersectSegment(&start, &end, p_record, p_position, NULL)) {
		verticalOffset.Clear();
		verticalOffset.m_z = g_dropGroundOffset;
		*p_position += verticalOffset;
	}
	else {
		*p_position = start;
	}
}

// FUNCTION: LEGORACERS 0x0044f570 FOLDED
LegoS32 HazardActionBase::GetBrickColor()
{
	return PowerupAction::c_brickColorYellow;
}
