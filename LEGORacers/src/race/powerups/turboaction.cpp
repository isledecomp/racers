#include "race/powerups/turboaction.h"

#include "app/cheatflags.h"
#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_unk0x004b02e0;

extern const LegoFloat g_fadeAlphaScale;

// GLOBAL: LEGORACERS 0x004b19d4
const LegoFloat g_turboSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b19d8
const LegoFloat g_turboSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b19e4
const LegoFloat g_turboSmokeVelocityScale = 0.7f;

// GLOBAL: LEGORACERS 0x004b1a50
const LegoFloat g_turboPackOffset = -2.0f;

// GLOBAL: LEGORACERS 0x004b1a54
const LegoFloat g_turboFadeAlphaScale = 0.0028571428f;

// GLOBAL: LEGORACERS 0x004b1a58
const LegoFloat g_turboEndVolumeBase = 0.6f;

// FUNCTION: LEGORACERS 0x0044f580 FOLDED
LegoS32 TurboAction::GetBrickColor()
{
	return PowerupAction::c_brickColorGreen;
}

// FUNCTION: LEGORACERS 0x0045c7e0
TurboAction::TurboAction()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045c830
TurboAction::~TurboAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045c880
void TurboAction::Initialize(RacePowerupManager* p_manager, CutsceneAnimation* p_particleAnimation)
{
	if (m_state != c_stateUnloaded) {
		Destroy();
	}

	m_manager = p_manager;
	m_particleAnimation = p_particleAnimation;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x0045c8b0
void TurboAction::Destroy()
{
	Deactivate();
	Reset();
	m_state = c_stateUnloaded;
}

// FUNCTION: LEGORACERS 0x0045c8d0
void TurboAction::Reset()
{
	m_turboEntity = 0;
	m_flameEntity = 0;
	m_flame2Entity = 0;
	m_racer = 0;
	m_manager = 0;
	m_particleAnimation = 0;
	m_smokeParticle = 0;
}

// FUNCTION: LEGORACERS 0x0045c8f0
void TurboAction::Activate(Racer* p_racer, LegoU32 p_level)
{
	GolAnimatedEntity* model = NULL;
	GolAnimatedEntity* effect0 = NULL;
	GolAnimatedEntity* effect1 = NULL;

	m_turboEntity = m_manager->AllocateEffectEntity();
	if (m_turboEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_flameEntity = m_manager->AllocateEffectEntity();
	if (m_flameEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_flame2Entity = m_manager->AllocateEffectEntity();
	if (m_flame2Entity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_racer = p_racer;
	if (m_racer->m_driveController.m_flags & DriveController::c_flagTurbo) {
		m_manager->CancelTurbo(m_racer);
		m_racer->ClearActiveAction();
		if (m_racer->m_flags & c_flagHalted) {
			m_racer->Resume();
		}
	}

	m_stateTimerMs = 400;
	m_level = p_level;
	switch (p_level) {
	case 2:
		model = m_manager->m_worldDatabase->FindAnimatedEntity("TurboL2");
		effect0 = m_manager->m_worldDatabase->FindAnimatedEntity("turb2f1");
		effect1 = m_manager->m_worldDatabase->FindAnimatedEntity("turb2f2");
		break;
	case 1:
		model = m_manager->m_worldDatabase->FindAnimatedEntity("TurboL1");
		effect0 = m_manager->m_worldDatabase->FindAnimatedEntity("turb1f1");
		effect1 = m_manager->m_worldDatabase->FindAnimatedEntity("turb1f2");
		break;
	case 0:
		model = m_manager->m_worldDatabase->FindAnimatedEntity("TurboL0");
		effect0 = m_manager->m_worldDatabase->FindAnimatedEntity("turb0f1");
		effect1 = m_manager->m_worldDatabase->FindAnimatedEntity("turb0f2");
		break;
	}

	m_turboEntity
		->SetModel(model->GetModel(0), model->GetSceneNode(0), model->GetModelPart(0), model->GetModelDistance(0));
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		if (model->GetModel(i) != NULL) {
			m_turboEntity->AddModel(
				model->GetModel(i),
				model->GetSceneNode(i),
				model->GetModelPart(i),
				model->GetModelDistance(i)
			);
		}
	}

	m_flameEntity->SetModel(
		effect0->GetModel(0),
		effect0->GetSceneNode(0),
		effect0->GetModelPart(0),
		effect0->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		if (effect0->GetModel(i) != NULL) {
			m_flameEntity->AddModel(
				effect0->GetModel(i),
				effect0->GetSceneNode(i),
				effect0->GetModelPart(i),
				effect0->GetModelDistance(i)
			);
		}
	}
	m_flameEntity->SetTextureScrollU(effect0->GetTextureScrollU());
	m_flameEntity->SetTextureScrollV(effect0->GetTextureScrollV());
	m_flameEntity->SetTextureScrollSpeedU(effect0->GetTextureScrollSpeedU());
	m_flameEntity->SetTextureScrollSpeedV(effect0->GetTextureScrollSpeedV());

	m_flame2Entity->SetModel(
		effect1->GetModel(0),
		effect1->GetSceneNode(0),
		effect1->GetModelPart(0),
		effect1->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		if (effect1->GetModel(i) != NULL) {
			m_flame2Entity->AddModel(
				effect1->GetModel(i),
				effect1->GetSceneNode(i),
				effect1->GetModelPart(i),
				effect1->GetModelDistance(i)
			);
		}
	}
	m_flame2Entity->SetTextureScrollU(effect1->GetTextureScrollU());
	m_flame2Entity->SetTextureScrollV(effect1->GetTextureScrollV());
	m_flame2Entity->SetTextureScrollSpeedU(effect1->GetTextureScrollSpeedU());
	m_flame2Entity->SetTextureScrollSpeedV(effect1->GetTextureScrollSpeedV());

	AnchorToRacer();
	m_turboEntity->SetFlags(m_turboEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_turboEntity->PlayPart(0);
	m_flameEntity->SetFlags(m_flameEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_flameEntity->PlayPart(0);
	m_flame2Entity->SetFlags(m_flame2Entity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_flame2Entity->PlayPart(0);
	StartBoost();
	m_state = c_stateIgnite;
}

// FUNCTION: LEGORACERS 0x0045cd70
void TurboAction::StartBoost()
{
	if (!m_level) {
		m_racer->m_physics.ApplyPitchImpulse(-0.0025f, c_speedModDurationL0Ms);
	}
	else {
		m_racer->m_physics.ApplyPitchImpulse(-0.0025f, c_speedModDurationMs);
	}

	m_racer->StartTurbo(m_level);

	SoundVector position;
	CarVisuals* racerField = &m_racer->m_visuals;
	racerField->m_carEntity->GetPosition(&position);

	m_soundSource->PlaySpatialSoundById(
		m_level + c_soundBoostBase,
		&position,
		g_turboSoundMinDistance,
		g_turboSoundMaxDistance,
		1.0f,
		1.0f
	);
	m_soundSource
		->PlaySpatialSoundById(c_soundWhoosh, &position, g_turboSoundMinDistance, g_turboSoundMaxDistance, 1.0f, 1.0f);

	if (m_level == 2) {
		m_racer->Halt();
	}
}

// FUNCTION: LEGORACERS 0x0045ce20
void TurboAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupAction::Update(p_elapsedMs);
	m_turboEntity->Update(p_elapsedMs);
	m_flameEntity->Update(p_elapsedMs);
	m_flame2Entity->Update(p_elapsedMs);

	if (m_level == 2 && m_state == c_stateBoosting && m_smokeParticle == NULL && m_stateTimerMs < c_smokeWindowMs &&
		!(m_manager->m_cheatFlags & c_flyskyhgh)) {
		m_smokeParticle = m_particleAnimation->SpawnParticle("trbsmke", NULL, NULL, NULL);
	}

	if (m_smokeParticle != NULL) {
		GolAnimatedEntity* racerEntity = m_racer->m_visuals.m_carEntity;
		GolVec3 offset;
		GolVec3 position;

		offset.m_x = -2.0f;
		offset.m_y = 0.0f;
		offset.m_z = 3.0f;
		racerEntity->LocalToWorld(offset, &position);

		if (m_smokeParticle->m_particle != NULL) {
			racerEntity->CopyOrientation(m_smokeParticle->m_particle->GetBasis());
		}

		if (m_smokeParticle->m_particle != NULL) {
			m_smokeParticle->m_particle->SetPosition(&position);
		}

		CutsceneParticleRef* particleRef = m_smokeParticle;
		GolVec3 velocity = m_racer->m_physics.m_velocity;
		velocity *= g_turboSmokeVelocityScale;

		if (particleRef->m_particle != NULL) {
			particleRef->m_particle->SetVelocity(&velocity);
		}
	}

	if ((m_racer->m_flags & c_flagHalted) && m_state == c_stateBoosting && m_stateTimerMs < c_earlyEndWindowMs &&
		!m_racer->m_physics.IsMoving()) {
		AdvanceState();
	}
}

// FUNCTION: LEGORACERS 0x0045cf90
void TurboAction::AnchorToRacer()
{
	GolVec3 position;
	GolVec3 right;
	GolVec3 direction;
	GolVec3 up;
	GolAnimatedEntity* racerEntity = m_racer->m_visuals.m_carEntity;

	racerEntity->GetPosition(&position);

	right.m_x = racerEntity->GetOrientation().m_rows[0].m_x;
	right.m_y = racerEntity->GetOrientation().m_rows[0].m_y;
	right.m_z = racerEntity->GetOrientation().m_rows[0].m_z;
	direction.m_x = racerEntity->GetOrientation().m_rows[1].m_x;
	direction.m_y = racerEntity->GetOrientation().m_rows[1].m_y;
	direction.m_z = racerEntity->GetOrientation().m_rows[1].m_z;
	up.m_x = racerEntity->GetOrientation().m_rows[2].m_x;
	up.m_y = racerEntity->GetOrientation().m_rows[2].m_y;
	up.m_z = racerEntity->GetOrientation().m_rows[2].m_z;
	LegoFloat rightX = right.m_x;
	rightX *= g_turboPackOffset;
	rightX += position.m_x;
	position.m_x = rightX;
	LegoFloat rightY = right.m_y;
	rightY *= g_turboPackOffset;
	rightY += position.m_y;
	position.m_y = rightY;
	LegoFloat rightZ = right.m_z;
	rightZ *= g_turboPackOffset;
	rightZ += position.m_z;
	position.m_z = rightZ;
	LegoFloat upX = up.m_x;
	upX *= 3.0f;
	upX += position.m_x;
	position.m_x = upX;
	LegoFloat upY = up.m_y;
	upY *= 3.0f;
	upY += position.m_y;
	position.m_y = upY;
	LegoFloat upZ = up.m_z;
	upZ *= 3.0f;
	upZ += position.m_z;
	position.m_z = upZ;

	m_turboEntity->SetPosition(position);
	m_turboEntity->SetDirectionUp(direction, up);
	GolAnimatedEntity* turbo = m_turboEntity;
	turbo->CopyOrientationAndPositionTo(m_flameEntity);
	m_turboEntity->CopyOrientationAndPositionTo(m_flame2Entity);
}

// FUNCTION: LEGORACERS 0x0045d120
void TurboAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateDone) {
		AnchorToRacer();
		p_renderer->DrawModelEntity(m_turboEntity);
	}
}

// FUNCTION: LEGORACERS 0x0045d150
void TurboAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state == c_stateIgnite) {
		if (m_stateTimerMs > c_igniteFlashMs) {
			p_renderer->SetAlphaOverride(0, TRUE);
		}
		else {
			p_renderer->SetAlphaOverride(0xff, TRUE);
		}
	}
	else if (m_state == c_stateFade) {
		LegoS32 elapsed = m_stateTimerMs - c_fadeBaseMs;
		if (elapsed < 0) {
			elapsed = 0;
		}

		LegoFloat amount = static_cast<LegoFloat>(elapsed) * g_turboFadeAlphaScale;
		LegoS32 alpha = static_cast<LegoS32>(amount * g_fadeAlphaScale);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_flame2Entity->Draw(*p_renderer);
	m_flameEntity->Draw(*p_renderer);

	if (m_state == c_stateIgnite || m_state == c_stateFade) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0045d200
void TurboAction::AdvanceState()
{
	switch (m_state) {
	case c_stateFade: {
		SoundVector position;
		CarVisuals* racerField = &m_racer->m_visuals;
		racerField->m_carEntity->GetPosition(&position);

		LegoS32 state = m_level;
		if (state == 2) {
			m_soundSource->PlaySpatialSoundById(
				c_soundEndL2,
				&position,
				g_turboSoundMinDistance,
				g_turboSoundMaxDistance,
				1.0f,
				1.0f
			);
		}
		else {
			LegoFloat volume = static_cast<LegoFloat>(state) * g_unk0x004b02e0 + g_turboEndVolumeBase;
			m_soundSource->PlaySpatialSoundById(
				c_soundEnd,
				&position,
				g_turboSoundMinDistance,
				g_turboSoundMaxDistance,
				volume,
				1.0f
			);
		}

		m_state = c_stateDone;
		return;
	}
	case c_stateBoosting:
		if (m_level == 2 && (m_manager->m_cheatFlags & c_flyskyhgh)) {
			m_stateTimerMs = c_boostDurationL2Ms;
			m_state = c_stateBoosting;
			return;
		}

		m_turboEntity->PlayPart(2);
		m_flameEntity->PlayPart(2);
		m_flame2Entity->PlayPart(2);

		m_stateTimerMs = 700;
		m_state = c_stateFade;
		return;
	case c_stateIgnite:
		m_turboEntity->PlayPart(1);
		m_flameEntity->PlayPart(1);
		m_flame2Entity->PlayPart(1);

		switch (m_level) {
		case 0:
			m_stateTimerMs = c_boostDurationL0Ms;
			break;
		case 1:
			m_stateTimerMs = c_boostDurationL1Ms;
			break;
		case 2:
			m_stateTimerMs = c_boostDurationL2Ms;
			break;
		}

		m_racer->PlayReaction(TRUE);
		m_state = c_stateBoosting;
		return;
	}
}

// FUNCTION: LEGORACERS 0x0045d360
void TurboAction::Deactivate()
{
	m_state = c_stateReady;

	if (m_smokeParticle != NULL) {
		m_particleAnimation->ReleaseRef(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	if (m_racer != NULL) {
		m_racer->ClearActiveAction();
		if (m_racer->m_flags & c_flagHalted) {
			m_racer->Resume();
		}
		m_racer = NULL;
	}

	if (m_flame2Entity != NULL) {
		m_flame2Entity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_flame2Entity);
		m_flame2Entity = NULL;
	}

	if (m_flameEntity != NULL) {
		m_flameEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_flameEntity);
		m_flameEntity = NULL;
	}

	if (m_turboEntity != NULL) {
		m_turboEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_turboEntity);
		m_turboEntity = NULL;
	}
}
