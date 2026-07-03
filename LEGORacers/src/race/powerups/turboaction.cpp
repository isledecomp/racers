#include "app/cheatflags.h"
#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
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

extern const LegoFloat g_unk0x004b02e0;

extern const LegoFloat g_fadeAlphaScale;

extern const LegoFloat g_emplacementGravityScale;

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
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			model = m_manager->m_worldDatabase->GetAnimatedEntityByName("TurboL2");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect0 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb2f1");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect1 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb2f2");
		}
		break;
	case 1:
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			model = m_manager->m_worldDatabase->GetAnimatedEntityByName("TurboL1");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect0 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb1f1");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect1 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb1f2");
		}
		break;
	case 0:
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			model = m_manager->m_worldDatabase->GetAnimatedEntityByName("TurboL0");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect0 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb0f1");
		}
		if (m_manager->m_worldDatabase->GetAnimatedEntityEntries()) {
			effect1 = m_manager->m_worldDatabase->GetAnimatedEntityByName("turb0f2");
		}
		break;
	}

	m_turboEntity
		->SetModel(model->GetModel(0), model->GetSceneNode(0), model->GetModelPart(0), model->GetModelDistance(0));
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = model->GetModel(i);
		if (lodModel != NULL) {
			m_turboEntity
				->AddModel(lodModel, model->GetSceneNode(i), model->GetModelPart(i), model->GetModelDistance(i));
		}
	}

	m_flameEntity->SetModel(
		effect0->GetModel(0),
		effect0->GetSceneNode(0),
		effect0->GetModelPart(0),
		effect0->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect0->GetModel(i);
		if (lodModel != NULL) {
			m_flameEntity
				->AddModel(lodModel, effect0->GetSceneNode(i), effect0->GetModelPart(i), effect0->GetModelDistance(i));
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
		GolModelBase* lodModel = effect1->GetModel(i);
		if (lodModel != NULL) {
			m_flame2Entity
				->AddModel(lodModel, effect1->GetSceneNode(i), effect1->GetModelPart(i), effect1->GetModelDistance(i));
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
	GolAnimatedEntity** racerEntity = &racerField->m_carEntity;
	(*racerEntity)->GetPosition(&position);

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
		GolVec3 velocity;
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

		RacerPhysics* racerPhysics = &m_racer->m_physics;
		velocity = racerPhysics->m_velocity;
		CutsceneParticleRef* particleRef = m_smokeParticle;
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

// STUB: LEGORACERS 0x0045cf90
void TurboAction::AnchorToRacer()
{
	GolAnimatedEntity* racerEntity = m_racer->m_visuals.m_carEntity;

	GolVec3 position;
	racerEntity->GetPosition(&position);

	const GolMatrix3& orientation = racerEntity->GetOrientation();

	GolVec3 right = orientation.m_rows[0];
	GolVec3 direction = orientation.m_rows[1];
	GolVec3 up = orientation.m_rows[2];
	position.m_x += right.m_x * g_turboPackOffset;
	position.m_y += right.m_y * g_turboPackOffset;
	position.m_z += right.m_z * g_turboPackOffset;
	position.m_x += up.m_x * g_emplacementGravityScale;
	position.m_y += up.m_y * g_emplacementGravityScale;
	position.m_z += up.m_z * g_emplacementGravityScale;

	m_turboEntity->SetPosition(position);
	m_turboEntity->SetDirectionUp(direction, up);
	m_turboEntity->CopyOrientationAndPositionTo(m_flameEntity);
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
		GolAnimatedEntity* racerEntity = racerField->GetCarEntity();
		racerEntity->GetPosition(&position);

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
