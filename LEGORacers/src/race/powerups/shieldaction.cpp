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

extern const LegoFloat g_shieldSoundMinDistance;

extern const LegoFloat g_shieldSoundMaxDistance;

extern const LegoFloat g_fadeAlphaScale;

extern const LegoFloat g_shieldExpireSoundMinDistance;

extern const LegoFloat g_shieldExpireSoundMaxDistance;

extern const LegoFloat g_homingProjectileCollisionStartOffset;

extern const LegoFloat g_violetShoalTwo;

// FUNCTION: LEGORACERS 0x00458690 FOLDED
RacePowerupManager::PowerupAction* RacePowerupManager::ShieldAction::Destroy(undefined4 p_flags)
{
	ShieldAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~ShieldAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0045bc50
RacePowerupManager::ShieldAction::ShieldAction()
{
	m_shieldEntity = 0;
	m_innerShieldEntity = 0;
	m_racer = 0;
	m_manager = 0;
	m_sound = 0;
}

// FUNCTION: LEGORACERS 0x0045bc80
RacePowerupManager::ShieldAction::~ShieldAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045bcd0 FOLDED
void RacePowerupManager::ShieldAction::Initialize(RacePowerupManager* p_manager)
{
	if (m_state != 0) {
		Destroy();
	}

	m_state = 1;
	m_manager = p_manager;
}

// FUNCTION: LEGORACERS 0x0045bd10 FOLDED
void RacePowerupManager::ShieldAction::Destroy()
{
	Deactivate();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x0045bd30
void RacePowerupManager::ShieldAction::Activate(
	RaceState::Racer* p_racer,
	LegoU32 p_level,
	GolAnimatedEntity* p_shieldTemplate,
	GolAnimatedEntity* p_innerShieldTemplate
)
{
	LegoU32 soundId = c_soundLevel0;

	m_shieldEntity = m_manager->AllocateEffectEntity();
	if (m_shieldEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_innerShieldEntity = m_manager->AllocateEffectEntity();
	if (m_innerShieldEntity == NULL) {
		m_state = c_stateDone;
		return;
	}

	m_racer = p_racer;
	if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit0) {
		m_manager->CancelShield(m_racer);
	}

	switch (p_level) {
	case 0:
		m_stateTimerMs = c_durationLevel0Ms;
		soundId = c_soundLevel0;
		break;
	case 1:
		m_stateTimerMs = c_durationLevel1Ms;
		soundId = c_soundLevel1;
		break;
	case 2:
		m_stateTimerMs = c_durationLevel2Ms;
		soundId = c_soundLevel2;
		break;
	case 3:
		m_stateTimerMs = c_durationLevel3Ms;
		soundId = c_soundLevel3;
		break;
	}

	m_sound = m_soundSource->AcquireSoundById(soundId);
	if (m_sound != NULL) {
		m_sound->Play(TRUE);
		m_sound->SetDistanceRange(g_shieldSoundMinDistance, g_shieldSoundMaxDistance);
	}

	m_state = c_stateActive;
	m_racer->StartShield(p_level);
	if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit11) {
		m_racer->RemoveCurse();
	}
	m_level = p_level;

	m_shieldEntity->FUN_0040d550(
		p_shieldTemplate->GetModel(0),
		p_shieldTemplate->VTable0x58(0),
		p_shieldTemplate->GetModelPart(0),
		p_shieldTemplate->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_shieldTemplate->GetModel(i);
		if (model != NULL) {
			m_shieldEntity->FUN_10023940(
				model,
				p_shieldTemplate->VTable0x58(i),
				p_shieldTemplate->GetModelPart(i),
				p_shieldTemplate->GetModelDistance(i)
			);
		}
	}

	m_shieldEntity->FUN_0040dad0(0);
	m_shieldEntity->SetFlags(m_shieldEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_shieldEntity->SetUnk0xb8(p_shieldTemplate->GetUnk0xb8());
	m_shieldEntity->FUN_00411680(p_shieldTemplate->FUN_00411640());
	m_shieldEntity->FUN_004116b0(p_shieldTemplate->FUN_00411660());
	m_shieldEntity->FUN_00411700(p_shieldTemplate->FUN_004116e0());
	m_shieldEntity->FUN_00411730(p_shieldTemplate->FUN_004116f0());
	m_shieldEntity->CopyPositionFrom(*m_racer->m_unk0x018.m_unk0x044);

	m_innerShieldEntity->FUN_0040d550(
		p_innerShieldTemplate->GetModel(0),
		p_innerShieldTemplate->VTable0x58(0),
		p_innerShieldTemplate->GetModelPart(0),
		p_innerShieldTemplate->GetModelDistance(0)
	);

	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_innerShieldTemplate->GetModel(i);
		if (model != NULL) {
			m_innerShieldEntity->FUN_10023940(
				model,
				p_innerShieldTemplate->VTable0x58(i),
				p_innerShieldTemplate->GetModelPart(i),
				p_innerShieldTemplate->GetModelDistance(i)
			);
		}
	}

	m_innerShieldEntity->FUN_0040dad0(0);
	m_innerShieldEntity->SetFlags(m_innerShieldEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_innerShieldEntity->SetUnk0xb8(p_innerShieldTemplate->GetUnk0xb8());
	m_innerShieldEntity->FUN_00411680(p_innerShieldTemplate->FUN_00411640());
	m_innerShieldEntity->FUN_004116b0(p_innerShieldTemplate->FUN_00411660());
	m_innerShieldEntity->FUN_00411700(p_innerShieldTemplate->FUN_004116e0());
	m_innerShieldEntity->FUN_00411730(p_innerShieldTemplate->FUN_004116f0());
	m_innerShieldEntity->CopyPositionFrom(*m_shieldEntity);
}

// FUNCTION: LEGORACERS 0x0045c060 FOLDED
void RacePowerupManager::ShieldAction::Deactivate()
{
	if (m_innerShieldEntity) {
		m_innerShieldEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_innerShieldEntity);
		m_innerShieldEntity = NULL;
	}

	if (m_shieldEntity) {
		m_shieldEntity->VTable0x54();
		m_manager->ReleaseEffectEntity(m_shieldEntity);
		m_shieldEntity = NULL;
	}

	m_racer = NULL;
	if (m_sound) {
		m_soundSource->ReleaseSound(m_soundResource);
		m_sound = NULL;
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0045c0c0 FOLDED
void RacePowerupManager::ShieldAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == 6) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);

	GolVec3 position;
	RaceState::Racer::Field0x018* racerEntities = &m_racer->m_unk0x018;
	racerEntities->m_unk0x044->VTable0x04(&position);

	GolVec3 velocity = m_racer->m_unk0x3e8.m_unk0x008;
	if (m_sound) {
		m_sound->SetPosition(position);
		m_sound->SetVelocity(velocity);
	}

	m_shieldEntity->VTable0x10(p_elapsedMs);
	m_innerShieldEntity->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0045c160 FOLDED
void RacePowerupManager::ShieldAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 6) {
		return;
	}

	GolVec3 position;
	m_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
	LegoFloat positionZ = position.m_z;
	positionZ += g_violetShoalTwo;
	position.m_z = positionZ;
	m_shieldEntity->VTable0x08(position);

	GolVec3 direction;
	GolVec3 up;
	m_racer->m_unk0x018.m_unk0x044->VTable0x48(&direction, &up);
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_shieldEntity->VTable0x40(direction, up);

	m_shieldEntity->CopyOrientationAndPositionTo(m_innerShieldEntity);

	if (m_state == 4) {
		LegoFloat alphaValue = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
		alphaValue *= 0.001f;
		alphaValue *= g_fadeAlphaScale;
		LegoS32 alpha = static_cast<LegoS32>(alphaValue);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_innerShieldEntity->VTable0x1c(*p_renderer);
	m_shieldEntity->VTable0x1c(*p_renderer);

	if (m_state == 4) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0045c2a0 FOLDED
void RacePowerupManager::ShieldAction::AdvanceState()
{
	switch (m_state) {
	case 3:
		m_stateTimerMs = 1000;
		m_state = 4;
		break;
	case 4: {
		m_state = 6;

		SoundVector position;
		RaceState::Racer::Field0x018* racerEntities = &m_racer->m_unk0x018;
		racerEntities->m_unk0x044->VTable0x04(&position);
		LegoFloat positionZ = position.m_z;
		positionZ += g_homingProjectileCollisionStartOffset;
		position.m_z = positionZ;
		m_soundSource->PlaySpatialSoundById(
			0x3b,
			&position,
			g_shieldExpireSoundMinDistance,
			g_shieldExpireSoundMaxDistance,
			1.0f,
			1.0f
		);
		m_racer->EndShield();
		break;
	}
	}
}

// FUNCTION: LEGORACERS 0x0045c330 FOLDED
LegoS32 RacePowerupManager::ShieldAction::GetBrickColor()
{
	return c_brickColorBlue;
}
