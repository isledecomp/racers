#include "app/cheatflags.h"
#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "goltransformbase.h"
#include "material/materialtable0x0c.h"
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

// FUNCTION: LEGORACERS 0x004586f0
RacePowerupManager::PowerupAction* RacePowerupManager::TurboAction::Destroy(undefined4 p_flags)
{
	TurboAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~TurboAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0045c7e0
RacePowerupManager::TurboAction::TurboAction()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0045c830
RacePowerupManager::TurboAction::~TurboAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045c880
void RacePowerupManager::TurboAction::Initialize(RacePowerupManager* p_manager, CutsceneAnimation* p_particleAnimation)
{
	if (m_state != 0) {
		Destroy();
	}

	m_manager = p_manager;
	m_particleAnimation = p_particleAnimation;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0045c8b0
void RacePowerupManager::TurboAction::Destroy()
{
	Deactivate();
	Reset();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x0045c8d0
void RacePowerupManager::TurboAction::Reset()
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
void RacePowerupManager::TurboAction::Activate(RaceState::Racer* p_racer, LegoU32 p_level)
{
	GolAnimatedEntity* model = NULL;
	GolAnimatedEntity* effect0 = NULL;
	GolAnimatedEntity* effect1 = NULL;

	m_turboEntity = m_manager->AllocateEffectEntity();
	if (m_turboEntity == NULL) {
		m_state = 6;
		return;
	}

	m_flameEntity = m_manager->AllocateEffectEntity();
	if (m_flameEntity == NULL) {
		m_state = 6;
		return;
	}

	m_flame2Entity = m_manager->AllocateEffectEntity();
	if (m_flame2Entity == NULL) {
		m_state = 6;
		return;
	}

	m_racer = p_racer;
	if (m_racer->m_unk0xc70.m_unk0x014 & RaceState::Racer::Field0xc70::c_flags0x014Bit0) {
		m_manager->CancelTurbo(m_racer);
		m_racer->ClearActiveAction();
		if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3) {
			m_racer->EndTurbo();
		}
	}

	m_stateTimerMs = 400;
	m_level = p_level;
	switch (p_level) {
	case 2:
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			model = m_manager->m_worldDatabase->GetUnk0xc0Name("TurboL2");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect0 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb2f1");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect1 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb2f2");
		}
		break;
	case 1:
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			model = m_manager->m_worldDatabase->GetUnk0xc0Name("TurboL1");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect0 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb1f1");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect1 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb1f2");
		}
		break;
	case 0:
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			model = m_manager->m_worldDatabase->GetUnk0xc0Name("TurboL0");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect0 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb0f1");
		}
		if (m_manager->m_worldDatabase->GetUnk0xc0NameEntries()) {
			effect1 = m_manager->m_worldDatabase->GetUnk0xc0Name("turb0f2");
		}
		break;
	}

	m_turboEntity
		->FUN_0040d550(model->GetModel(0), model->VTable0x58(0), model->GetModelPart(0), model->GetModelDistance(0));
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = model->GetModel(i);
		if (lodModel != NULL) {
			m_turboEntity
				->FUN_10023940(lodModel, model->VTable0x58(i), model->GetModelPart(i), model->GetModelDistance(i));
		}
	}

	m_flameEntity->FUN_0040d550(
		effect0->GetModel(0),
		effect0->VTable0x58(0),
		effect0->GetModelPart(0),
		effect0->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect0->GetModel(i);
		if (lodModel != NULL) {
			m_flameEntity->FUN_10023940(
				lodModel,
				effect0->VTable0x58(i),
				effect0->GetModelPart(i),
				effect0->GetModelDistance(i)
			);
		}
	}
	m_flameEntity->FUN_00411680(effect0->FUN_00411640());
	m_flameEntity->FUN_004116b0(effect0->FUN_00411660());
	m_flameEntity->FUN_00411700(effect0->FUN_004116e0());
	m_flameEntity->FUN_00411730(effect0->FUN_004116f0());

	m_flame2Entity->FUN_0040d550(
		effect1->GetModel(0),
		effect1->VTable0x58(0),
		effect1->GetModelPart(0),
		effect1->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect1->GetModel(i);
		if (lodModel != NULL) {
			m_flame2Entity->FUN_10023940(
				lodModel,
				effect1->VTable0x58(i),
				effect1->GetModelPart(i),
				effect1->GetModelDistance(i)
			);
		}
	}
	m_flame2Entity->FUN_00411680(effect1->FUN_00411640());
	m_flame2Entity->FUN_004116b0(effect1->FUN_00411660());
	m_flame2Entity->FUN_00411700(effect1->FUN_004116e0());
	m_flame2Entity->FUN_00411730(effect1->FUN_004116f0());

	AnchorToRacer();
	m_turboEntity->SetFlags(m_turboEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_turboEntity->FUN_0040dad0(0);
	m_flameEntity->SetFlags(m_flameEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_flameEntity->FUN_0040dad0(0);
	m_flame2Entity->SetFlags(m_flame2Entity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_flame2Entity->FUN_0040dad0(0);
	StartBoost();
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0045cd70
void RacePowerupManager::TurboAction::StartBoost()
{
	if (!m_level) {
		m_racer->m_unk0x3e8.ApplySpeedModifier(-0.0025f, c_speedModDurationL0Ms);
	}
	else {
		m_racer->m_unk0x3e8.ApplySpeedModifier(-0.0025f, c_speedModDurationMs);
	}

	m_racer->StartTurbo(m_level);

	SoundVector position;
	RaceState::Racer::Field0x018* racerField = &m_racer->m_unk0x018;
	GolAnimatedEntity** racerEntity = &racerField->m_unk0x044;
	(*racerEntity)->VTable0x04(&position);

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
		m_racer->FUN_00439570();
	}
}

// FUNCTION: LEGORACERS 0x0045ce20
void RacePowerupManager::TurboAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);
	m_turboEntity->VTable0x10(p_elapsedMs);
	m_flameEntity->VTable0x10(p_elapsedMs);
	m_flame2Entity->VTable0x10(p_elapsedMs);

	if (m_level == 2 && m_state == c_stateBoosting && m_smokeParticle == NULL && m_stateTimerMs < c_smokeWindowMs &&
		!(m_manager->m_cheatFlags & c_flyskyhgh)) {
		m_smokeParticle = m_particleAnimation->FUN_00489d70("trbsmke", NULL, NULL, NULL);
	}

	if (m_smokeParticle != NULL) {
		GolAnimatedEntity* racerEntity = m_racer->m_unk0x018.m_unk0x044;
		GolVec3 velocity;
		GolVec3 offset;
		GolVec3 position;

		offset.m_x = -2.0f;
		offset.m_y = 0.0f;
		offset.m_z = 3.0f;
		racerEntity->VTable0x2c(offset, &position);

		if (m_smokeParticle->m_particle != NULL) {
			racerEntity->VTable0x44(m_smokeParticle->m_particle->GetUnk0x160());
		}

		if (m_smokeParticle->m_particle != NULL) {
			m_smokeParticle->m_particle->FUN_00489660(&position);
		}

		RaceState::Racer::Field0x3e8* racerPhysics = &m_racer->m_unk0x3e8;
		velocity = racerPhysics->m_unk0x008;
		CutsceneParticleRef* particleRef = m_smokeParticle;
		velocity *= g_turboSmokeVelocityScale;

		if (particleRef->m_particle != NULL) {
			particleRef->m_particle->FUN_00489690(&velocity);
		}
	}

	if ((m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3) && m_state == c_stateBoosting &&
		m_stateTimerMs < c_earlyEndWindowMs && !m_racer->m_unk0x3e8.FUN_0042a7f0()) {
		AdvanceState();
	}
}

// STUB: LEGORACERS 0x0045cf90
void RacePowerupManager::TurboAction::AnchorToRacer()
{
	GolAnimatedEntity* racerEntity = m_racer->m_unk0x018.m_unk0x044;

	GolVec3 position;
	racerEntity->VTable0x04(&position);

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

	m_turboEntity->VTable0x08(position);
	m_turboEntity->VTable0x40(direction, up);
	m_turboEntity->CopyOrientationAndPositionTo(m_flameEntity);
	m_turboEntity->CopyOrientationAndPositionTo(m_flame2Entity);
}

// FUNCTION: LEGORACERS 0x0045d120
void RacePowerupManager::TurboAction::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateDone) {
		AnchorToRacer();
		p_renderer->VTable0x94(m_turboEntity);
	}
}

// FUNCTION: LEGORACERS 0x0045d150
void RacePowerupManager::TurboAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
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

	m_flame2Entity->VTable0x1c(*p_renderer);
	m_flameEntity->VTable0x1c(*p_renderer);

	if (m_state == c_stateIgnite || m_state == c_stateFade) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0045d200
void RacePowerupManager::TurboAction::AdvanceState()
{
	switch (m_state) {
	case c_stateFade: {
		SoundVector position;
		RaceState::Racer::Field0x018* racerField = &m_racer->m_unk0x018;
		GolAnimatedEntity* racerEntity = racerField->GetUnk0x044();
		racerEntity->VTable0x04(&position);

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

		m_turboEntity->FUN_0040dad0(2);
		m_flameEntity->FUN_0040dad0(2);
		m_flame2Entity->FUN_0040dad0(2);

		m_stateTimerMs = 700;
		m_state = c_stateFade;
		return;
	case c_stateIgnite:
		m_turboEntity->FUN_0040dad0(1);
		m_flameEntity->FUN_0040dad0(1);
		m_flame2Entity->FUN_0040dad0(1);

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
void RacePowerupManager::TurboAction::Deactivate()
{
	m_state = c_stateReady;

	if (m_smokeParticle != NULL) {
		m_particleAnimation->FUN_00489f00(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	if (m_racer != NULL) {
		m_racer->ClearActiveAction();
		if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3) {
			m_racer->EndTurbo();
		}
		m_racer = NULL;
	}

	if (m_flame2Entity != NULL) {
		m_flame2Entity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_flame2Entity);
		m_flame2Entity = NULL;
	}

	if (m_flameEntity != NULL) {
		m_flameEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_flameEntity);
		m_flameEntity = NULL;
	}

	if (m_turboEntity != NULL) {
		m_turboEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_turboEntity);
		m_turboEntity = NULL;
	}
}
