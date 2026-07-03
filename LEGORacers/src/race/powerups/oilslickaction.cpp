#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_homingProjectileCollisionStartOffset;

// GLOBAL: LEGORACERS 0x004b16c0
const LegoFloat g_oilSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b16c4
const LegoFloat g_oilSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b16c8
const LegoFloat g_oilSlipSoundMinDistance = 200.0f;

// GLOBAL: LEGORACERS 0x004b16cc
const LegoFloat g_oilSlipSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b1704
const LegoFloat g_oilBubbleAngleScale = 0.01f;

extern LegoU16 g_randomTable[1024];

extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00457080
OilSlickAction::OilSlickAction()
{
	m_manager = 0;
	m_sound = 0;
	m_particleAnimation = 0;
	m_bubbleParticle = 0;
	m_collidable = 0;
}

// FUNCTION: LEGORACERS 0x00457100
OilSlickAction::~OilSlickAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00457170
void OilSlickAction::Destroy()
{
	Deactivate();
	m_slickDecal.Destroy();
	m_materialTable.Clear();
	m_manager = 0;
	m_sound = 0;
	m_particleAnimation = 0;
	m_bubbleParticle = 0;
	m_collidable = 0;
}

// FUNCTION: LEGORACERS 0x004571b0
void OilSlickAction::Initialize(
	RacePowerupManager* p_manager,
	RaceState* p_raceState,
	GolCollidableEntity* p_collidable,
	TriggerWorld* p_collisionWorld,
	CutsceneAnimation* p_particleAnimation,
	GolRenderDevice* p_renderer,
	GolExport* p_export
)
{
	m_manager = p_manager;
	m_raceState = p_raceState;
	m_collisionWorld = p_collisionWorld;
	m_collidable = p_collidable;
	m_particleAnimation = p_particleAnimation;
	m_state = c_stateReady;

	m_materialTable.Initialize(p_renderer, 1);
	m_materialTable.AssignEntryByName(0, "oilslck");
	m_slickDecal.Initialize(p_export, p_renderer, 0x10);
	m_slickDecal.GetEntity().EnableFlagBit1();
}

// FUNCTION: LEGORACERS 0x00457230
void OilSlickAction::Activate(Racer* p_racer)
{
	m_state = c_stateArmed;
	m_ownerRacer = p_racer;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00457250
void OilSlickAction::Deactivate()
{
	if (m_bubbleParticle != NULL) {
		m_particleAnimation->FinishRef(m_bubbleParticle);
		m_bubbleParticle = NULL;
	}

	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x004572a0
void OilSlickAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupAction::Update(p_elapsedMs);

	if (m_bubbleParticle != NULL) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoS32 phase = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomPhaseRange;
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoS32 distance = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomBubbleOffsetRange;

		LegoFloat angle = static_cast<LegoFloat>(phase) * g_oilBubbleAngleScale;
		LegoFloat offset = static_cast<LegoFloat>(distance);
		GolVec3 position;
		m_worldEntity.GetPosition(&position);
		CutsceneParticleRef* particleRef = m_bubbleParticle;
		position.m_x += static_cast<LegoFloat>(::sin(angle)) * offset;
		position.m_y += static_cast<LegoFloat>(::cos(angle)) * offset;

		if (particleRef->m_particle != NULL) {
			particleRef->m_particle->SetPosition(&position);
		}
	}
}

// FUNCTION: LEGORACERS 0x00457380
void OilSlickAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateActive) {
		m_slickDecal.Draw(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004573a0
void OilSlickAction::AdvanceState()
{
	switch (m_state) {
	case c_stateArmed:
		break;
	case c_stateActive:
		m_state = c_stateDone;
		m_stateTimerMs = 0;
		return;
	default:
		return;
	}

	SoundVector position;
	ComputeDropPosition(m_ownerRacer, &position, NULL);
	m_worldEntity.SetPosition(position);
	m_worldEntity.SetBoundsRadius(3.0f);
	m_ownerRacer->m_physics.ApplyPitchImpulse(0.0015f, 150);
	m_soundSource
		->PlaySpatialSoundById(c_soundDrop, &position, g_oilSoundMinDistance, g_oilSoundMaxDistance, 1.0f, 1.0f);

	m_sound = m_soundSource->AcquireSoundById(c_soundLoop);
	if (m_sound != NULL) {
		m_sound->Play(TRUE);

		LegoFloat maxDistance = g_oilSoundMaxDistance;
		LegoFloat minDistance = g_oilSoundMinDistance;
		m_sound->SetDistanceRangeWithMinSquared(minDistance * g_oilSoundMinDistance, maxDistance);
		m_sound->SetPosition(position);
	}

	m_state = c_stateActive;
	m_stateTimerMs = c_activeDurationMs;

	LegoEventQueue::Callback* callback = this;
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_type = 4;
	descriptor.m_flags = 1;
	descriptor.m_maxFireCount = 0;
	descriptor.m_hitThreshold = 0;
	descriptor.m_data = &m_worldEntity;
	LegoEventQueue::Event* event = m_raceState->GetEventQueue()->AllocateEvent(callback, &descriptor);

	CutsceneAnimation* animation = m_particleAnimation;
	m_collisionEvent = event;
	m_bubbleParticle = animation->SpawnParticle("oilbub", NULL, NULL, NULL);
	if (m_bubbleParticle != NULL && m_bubbleParticle->m_particle != NULL) {
		m_bubbleParticle->m_particle->SetPosition(&position);
	}

	position.m_z += g_homingProjectileCollisionStartOffset;
	m_slickDecal.m_width = 15.0f;
	m_slickDecal.m_length = 15.0f;
	m_slickDecal.m_depth = 15.0f;
	m_slickDecal.m_center = position;
	position.m_z -= g_homingProjectileCollisionStartOffset;
	m_slickDecal.GetEntity().SetPrimaryMaterialTable(&m_materialTable);

	GolVec3 normal;
	GolVec3 tangent;
	tangent.m_x = 1.0f;
	tangent.m_y = 0.0f;
	tangent.m_z = 0.0f;

	normal.m_x = 0.0f;
	normal.m_y = 0.0f;
	normal.m_z = -1.0f;

	m_slickDecal.SetOrientation(&normal, &tangent);
	m_slickDecal.Project(m_collidable);
}

// FUNCTION: LEGORACERS 0x004575b0
void OilSlickAction::OnHitRacer(Racer* p_racer)
{
	if (m_state == c_stateExpiring || (p_racer->GetFlags() & c_flagHalted)) {
		return;
	}

	p_racer->m_physics.StartSpin(1.0f, 0.007f, 1.0f);
	p_racer->m_visuals.m_reactionFlags |= CarVisuals::c_reactionHit;
	m_state = c_stateDone;
	m_stateTimerMs = 0;

	SoundVector position;
	p_racer->m_visuals.m_carEntity->GetPosition(&position);
	m_soundSource->PlaySpatialSoundById(
		c_soundSlip,
		&position,
		g_oilSlipSoundMinDistance,
		g_oilSlipSoundMaxDistance,
		1.0f,
		1.0f
	);
}
