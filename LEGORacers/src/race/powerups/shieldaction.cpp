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

extern const LegoFloat g_shieldSoundMinDistance;

extern const LegoFloat g_shieldSoundMaxDistance;

extern const LegoFloat g_fadeAlphaScale;

extern const LegoFloat g_shieldExpireSoundMinDistance;

extern const LegoFloat g_shieldExpireSoundMaxDistance;

extern const LegoFloat g_homingProjectileCollisionStartOffset;

extern const LegoFloat g_violetShoalTwo;

// FUNCTION: LEGORACERS 0x0045bc50
ShieldAction::ShieldAction()
{
	m_shieldEntity = 0;
	m_innerShieldEntity = 0;
	m_racer = 0;
	m_manager = 0;
	m_sound = 0;
}

// FUNCTION: LEGORACERS 0x0045bc80
ShieldAction::~ShieldAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0045bcd0 FOLDED
void ShieldAction::Initialize(RacePowerupManager* p_manager)
{
	if (m_state != c_stateUnloaded) {
		Destroy();
	}

	m_state = c_stateReady;
	m_manager = p_manager;
}

// FUNCTION: LEGORACERS 0x0045bd10 FOLDED
void ShieldAction::Destroy()
{
	Deactivate();
	m_state = c_stateUnloaded;
}

// FUNCTION: LEGORACERS 0x0045bd30
void ShieldAction::Activate(
	Racer* p_racer,
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
	if (m_racer->m_flags & Racer::c_flagShielded) {
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
	if (m_racer->m_flags & c_flagCursed) {
		m_racer->RemoveCurse();
	}
	m_level = p_level;

	m_shieldEntity->SetModel(
		p_shieldTemplate->GetModel(0),
		p_shieldTemplate->GetSceneNode(0),
		p_shieldTemplate->GetModelPart(0),
		p_shieldTemplate->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_shieldTemplate->GetModel(i);
		if (model != NULL) {
			m_shieldEntity->AddModel(
				model,
				p_shieldTemplate->GetSceneNode(i),
				p_shieldTemplate->GetModelPart(i),
				p_shieldTemplate->GetModelDistance(i)
			);
		}
	}

	m_shieldEntity->PlayPart(0);
	m_shieldEntity->SetFlags(m_shieldEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_shieldEntity->SetMsPerFrame(p_shieldTemplate->GetMsPerFrame());
	m_shieldEntity->SetTextureScrollU(p_shieldTemplate->GetTextureScrollU());
	m_shieldEntity->SetTextureScrollV(p_shieldTemplate->GetTextureScrollV());
	m_shieldEntity->SetTextureScrollSpeedU(p_shieldTemplate->GetTextureScrollSpeedU());
	m_shieldEntity->SetTextureScrollSpeedV(p_shieldTemplate->GetTextureScrollSpeedV());
	m_shieldEntity->CopyPositionFrom(*m_racer->m_visuals.m_carEntity);

	m_innerShieldEntity->SetModel(
		p_innerShieldTemplate->GetModel(0),
		p_innerShieldTemplate->GetSceneNode(0),
		p_innerShieldTemplate->GetModelPart(0),
		p_innerShieldTemplate->GetModelDistance(0)
	);

	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_innerShieldTemplate->GetModel(i);
		if (model != NULL) {
			m_innerShieldEntity->AddModel(
				model,
				p_innerShieldTemplate->GetSceneNode(i),
				p_innerShieldTemplate->GetModelPart(i),
				p_innerShieldTemplate->GetModelDistance(i)
			);
		}
	}

	m_innerShieldEntity->PlayPart(0);
	m_innerShieldEntity->SetFlags(m_innerShieldEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_innerShieldEntity->SetMsPerFrame(p_innerShieldTemplate->GetMsPerFrame());
	m_innerShieldEntity->SetTextureScrollU(p_innerShieldTemplate->GetTextureScrollU());
	m_innerShieldEntity->SetTextureScrollV(p_innerShieldTemplate->GetTextureScrollV());
	m_innerShieldEntity->SetTextureScrollSpeedU(p_innerShieldTemplate->GetTextureScrollSpeedU());
	m_innerShieldEntity->SetTextureScrollSpeedV(p_innerShieldTemplate->GetTextureScrollSpeedV());
	m_innerShieldEntity->CopyPositionFrom(*m_shieldEntity);
}

// FUNCTION: LEGORACERS 0x0045c060 FOLDED
void ShieldAction::Deactivate()
{
	if (m_innerShieldEntity) {
		m_innerShieldEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_innerShieldEntity);
		m_innerShieldEntity = NULL;
	}

	if (m_shieldEntity) {
		m_shieldEntity->ResetModelState();
		m_manager->ReleaseEffectEntity(m_shieldEntity);
		m_shieldEntity = NULL;
	}

	m_racer = NULL;
	if (m_sound) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x0045c0c0 FOLDED
void ShieldAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	PowerupAction::Update(p_elapsedMs);

	GolVec3 position;
	CarVisuals* racerEntities = &m_racer->m_visuals;
	racerEntities->m_carEntity->GetPosition(&position);

	GolVec3 velocity = m_racer->m_physics.m_velocity;
	if (m_sound) {
		m_sound->SetPosition(position);
		m_sound->SetVelocity(velocity);
	}

	m_shieldEntity->Update(p_elapsedMs);
	m_innerShieldEntity->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0045c160 FOLDED
void ShieldAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_stateDone) {
		return;
	}

	GolVec3 position;
	m_racer->m_visuals.m_carEntity->GetPosition(&position);
	LegoFloat positionZ = position.m_z;
	positionZ += g_violetShoalTwo;
	position.m_z = positionZ;
	m_shieldEntity->SetPosition(position);

	GolVec3 direction;
	GolVec3 up;
	m_racer->m_visuals.m_carEntity->GetAxes(&direction, &up);
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_shieldEntity->SetDirectionUp(direction, up);

	m_shieldEntity->CopyOrientationAndPositionTo(m_innerShieldEntity);

	if (m_state == c_stateFade) {
		LegoFloat alphaValue = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
		alphaValue *= 0.001f;
		alphaValue *= g_fadeAlphaScale;
		LegoS32 alpha = static_cast<LegoS32>(alphaValue);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_innerShieldEntity->Draw(*p_renderer);
	m_shieldEntity->Draw(*p_renderer);

	if (m_state == c_stateFade) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0045c2a0 FOLDED
void ShieldAction::AdvanceState()
{
	switch (m_state) {
	case 3:
		m_stateTimerMs = 1000;
		m_state = c_stateFade;
		break;
	case 4: {
		m_state = c_stateDone;

		SoundVector position;
		CarVisuals* racerEntities = &m_racer->m_visuals;
		racerEntities->m_carEntity->GetPosition(&position);
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
LegoS32 ShieldAction::GetBrickColor()
{
	return RacePowerupManager::c_brickColorBlue;
}
