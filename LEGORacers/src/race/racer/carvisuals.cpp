#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
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
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/gold3dtexture.h"
#include "util/carshadowrenderstate.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoFloat g_carBuildPreviewMouseScale;
extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_fadeAlphaScale;
extern const LegoFloat g_sweepCannonRadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_carShadowScale;
extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern const LegoFloat g_shieldSoundMaxDistance;
extern const LegoFloat g_shieldSoundMinDistance;
extern const LegoFloat g_unk0x004b02e0;
extern const LegoFloat g_unk0x004b0544;
extern const LegoFloat g_hiddenModelDistance;
extern const LegoFloat g_unk0x004b0af0;
extern const LegoFloat g_shadowProbeHeight;
extern const LegoFloat g_lookTargetRangeSquared;
extern const LegoFloat g_pitchLeanRate;
extern const LegoFloat g_rollLeanRate;
extern const LegoFloat g_pitchLeanDamping;
extern const LegoFloat g_rollLeanDamping;
extern const LegoFloat g_shadowFadeNearSquared;
extern const LegoFloat g_shadowFadeFarSquared;
extern const LegoFloat g_lookAtDotBehind;
extern const LegoFloat g_lookAtDotBeside;
extern LegoU32 g_silhouetteClearFlag;
extern LegoU32 g_silhouetteFlattenFlag;
extern LegoU32 g_raceLapCount;
extern LegoFloat g_cursePhaseScale;
extern const LegoFloat g_violetShoalTwo;

// FUNCTION: LEGORACERS 0x0043d5a0
CarVisuals::CarVisuals()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d620
CarVisuals::~CarVisuals()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d6a0
void CarVisuals::Reset()
{
	m_bodyModelEntity = NULL;
	m_secondaryEntity = NULL;
	m_carEntity = NULL;
	m_driverEntity = NULL;
	m_racer = NULL;
	m_shadowDirection.m_x = 0.0f;
	m_shadowDirection.m_y = 0.0f;
	m_shadowDirection.m_z = -1.0f;
	m_trackCollidable = NULL;
	m_racerPhysics = NULL;
	m_flags = 0;
	m_driverMountOffset.m_x = 0.0f;
	m_driverMountOffset.m_y = 0.0f;
	m_driverMountOffset.m_z = 0.0f;

	for (LegoU32 i = 0; i < sizeOfArray(m_skidMarks); i++) {
		m_wheelSkidFlags[i] = 0;
		m_wheelAirTimers[i] = 0;
		m_skidFadeTimers[i] = 0;
		m_wheelOffsets[i].m_x = 0.0f;
		m_wheelOffsets[i].m_y = 0.0f;
		m_wheelOffsets[i].m_z = 0.0f;
		m_skidMarks[i] = NULL;
		m_wheelParticles[i] = NULL;
		m_wheelParticleFromRace[i] = 0;
		m_wheelParticleNames[i][0] = 0;
	}

	m_dustParticle = NULL;
	m_carSmokeParticle = NULL;
	m_tireSmokeParticle = NULL;
	m_particleAnimation = NULL;
	m_sharedParticleAnimation = NULL;
	m_skidMarkManager = NULL;
	m_cursePhaseMs = 0;
	m_curseBlendMs = 0;
	m_nearbyRacer = NULL;
	m_unk0x390 = 0;
	m_unk0x394 = 0;
	m_pitchLean = 0;
	m_rollLean = 0;
	m_lastSpeed = 0;
	m_reactionFlags = 0;
	m_lookCooldownMs = 0;
	m_hasColorTransform = 0;
	m_isFlashing = 0;
	m_flashTimerMs = 0;
	m_lastGroundedWheelCount = 4;
}

// FUNCTION: LEGORACERS 0x0043d7a0
void CarVisuals::Initialize(InitParams* p_params, RacerContext* p_context)
{
	if (m_flags & c_alphaOverrideFlag) {
		Destroy();
	}

	m_bodyModelEntity = p_params->m_bodyModel;
	m_secondaryEntity = p_params->m_secondaryModel;
	m_carEntity = p_params->m_carEntity;
	m_driverEntity = p_params->m_driverEntity;
	m_driverMountOffset = p_params->m_driverMountOffset;
	m_trackCollidable = p_context->m_trackCollidable;
	Racer* racer = p_params->m_racer;
	m_racer = racer;
	m_racerPhysics = &racer->m_physics;
	m_particleAnimation = p_context->m_particleAnimation;
	m_sharedParticleAnimation = p_context->m_sharedParticleAnimation;
	m_skidMarkManager = p_context->m_decalManager;
	m_flags = c_alphaOverrideFlag | c_flagVisible;
	if (p_context->m_shadowsEnabled) {
		m_flags = c_alphaOverrideFlag | c_flagVisible | c_flagShadowEnabled;
	}

	m_shadowWidth = p_params->m_shadowWidth;
	m_shadowLength = p_params->m_shadowLength;
	m_frontSkidWidth = p_params->m_frontSkidWidth;
	m_rearSkidWidth = p_params->m_rearSkidWidth;
	::strncpy(m_shadowTextureName, p_params->m_materialName, sizeof(m_shadowTextureName));

	m_shadowMaterialTable.Initialize(p_context->m_renderer, 1);
	m_shadowMaterialTable.AssignEntryByName(0, m_shadowTextureName);
	m_skidMaterialTable.Initialize(p_context->m_renderer, 1);
	m_skidMaterialTable.AssignEntryByName(0, "skid");

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_lookCooldownMs = g_randomTable[g_randomTableIndex] % 2000;

	for (LegoU32 i = 0; i < sizeOfArray(m_wheelOffsets); i++) {
		m_wheelOffsets[i] = p_params->m_wheelOffsets[i];
	}

	m_carEntity->PlayPart(0);
	m_carEntity->SetFlags(m_carEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (m_secondaryEntity) {
		m_secondaryEntity->PlayPart(0);
		m_secondaryEntity->SetFlags(m_secondaryEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	}

	m_driverEntity->PlayPart(9);
	m_driverEntity->SetFlags(m_driverEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (p_context->m_cheatFlags & 0x200) {
		m_flags |= c_flagVisible0;
	}
	if (p_context->m_cheatFlags & 0x400) {
		m_flags |= c_flagVisible1;
	}
	if (p_context->m_cheatFlags & 0x800) {
		m_flags |= c_flagVisible2;
	}

	RebuildEntityGroup();
}

// FUNCTION: LEGORACERS 0x0043d990
void CarVisuals::InitializeVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_bodyModelEntity->GetModelDistance(i);
	}

	SnapVisuals();
	RenderShadowSilhouette(p_renderer);
	m_shadowDecal.Initialize(p_golExport, p_renderer, 0x10);
	m_shadowDecal.GetEntity().EnableFlagBit1();
}

// FUNCTION: LEGORACERS 0x0043d9f0
void CarVisuals::RefreshCarMaterial()
{
	m_shadowMaterialTable.AssignEntryByName(0, m_shadowTextureName);
}

// FUNCTION: LEGORACERS 0x0043da10
void CarVisuals::UseTurboSkidMaterial()
{
	m_skidMaterialTable.AssignEntryByName(0, "trbskid");
}

// FUNCTION: LEGORACERS 0x0043da30
void CarVisuals::UseNormalSkidMaterial()
{
	m_skidMaterialTable.AssignEntryByName(0, "skid");
}

// FUNCTION: LEGORACERS 0x0043da50
void CarVisuals::Destroy()
{
	m_curseEntity.ResetModelState();
	m_shadowDecal.Destroy();
	m_skidMaterialTable.Clear();
	m_shadowMaterialTable.Clear();

	if (m_tireSmokeParticle) {
		m_particleAnimation->ReleaseRef(m_tireSmokeParticle);
		m_tireSmokeParticle = NULL;
	}

	if (m_carSmokeParticle) {
		m_particleAnimation->ReleaseRef(m_carSmokeParticle);
		m_carSmokeParticle = NULL;
	}

	if (m_dustParticle) {
		m_particleAnimation->ReleaseRef(m_dustParticle);
		m_dustParticle = NULL;
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_wheelParticles); i++) {
		CutsceneParticleRef* particleRef = m_wheelParticles[i];
		if (particleRef) {
			if (m_wheelParticleFromRace[i]) {
				m_particleAnimation->ReleaseRef(particleRef);
			}
			else {
				m_sharedParticleAnimation->ReleaseRef(particleRef);
			}

			m_wheelParticles[i] = NULL;
			m_wheelParticleNames[i][0] = 0;
		}
	}

	m_particleAnimation = NULL;
	m_shadowDecal.Destroy();
	m_skidMaterialTable.Clear();
	m_shadowMaterialTable.Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x0043db60
void CarVisuals::ShowModels()
{
	m_flags |= c_flagVisible;

	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_bodyModelEntity->SetModelDistance(i, m_modelDistances[i]);
		m_carEntity->SetModelDistance(i, m_modelDistances[i]);
		m_driverEntity->SetModelDistance(i, m_modelDistances[i]);

		if (m_secondaryEntity) {
			m_secondaryEntity->SetModelDistance(i, m_modelDistances[i]);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dbb0
void CarVisuals::HideModels()
{
	m_flags &= ~c_flagVisible;

	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_bodyModelEntity->SetModelDistance(i, g_hiddenModelDistance);
		m_carEntity->SetModelDistance(i, g_hiddenModelDistance);
		m_driverEntity->SetModelDistance(i, g_hiddenModelDistance);

		if (m_secondaryEntity) {
			m_secondaryEntity->SetModelDistance(i, g_hiddenModelDistance);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dc00
void CarVisuals::StartSkidEffects()
{
	if (!(m_racer->m_flags & Racer::c_flagHalted)) {
		for (LegoU32 i = 0; i < sizeOfArray(m_wheelSkidFlags); i++) {
			if ((m_racerPhysics->m_flags & RacerPhysics::c_flagSpinning) || i >= 2) {
				m_wheelSkidFlags[i] = TRUE;
			}
			else {
				m_wheelSkidFlags[i] &= ~(c_wheelSkidActive | c_wheelSkidGrounded);
			}
		}

		if (!m_tireSmokeParticle) {
			m_tireSmokeParticle = m_particleAnimation->SpawnParticle("tiresmk", NULL, NULL, NULL);

			if (m_tireSmokeParticle) {
				GolVec3 position = m_racerPhysics->m_wheelProbes[3].m_wheelPosition;
				GolAnimatedEntity* entity = m_carEntity;
				if (m_tireSmokeParticle->m_particle) {
					entity->CopyOrientation(m_tireSmokeParticle->m_particle->GetBasis());
				}

				if (m_tireSmokeParticle->m_particle) {
					m_tireSmokeParticle->m_particle->SetPosition(&position);
				}
			}
		}

		m_flags |= c_flagSkidding;
	}
}

// FUNCTION: LEGORACERS 0x0043dcd0
void CarVisuals::StopSkidEffects()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_skidMarks); i++) {
		if (m_skidMarks[i]) {
			m_skidMarkManager->ReleaseTrail(m_skidMarks[i], 1000);
			m_skidMarks[i] = NULL;
		}

		LegoU8 flags = m_wheelSkidFlags[i];
		if (flags & c_wheelSkidGrounded) {
			flags &= ~c_wheelSkidGrounded;
			flags |= c_wheelSkidFading;
			m_wheelSkidFlags[i] = flags;
		}
		else {
			m_wheelSkidFlags[i] = 0;
		}
	}

	if (m_tireSmokeParticle) {
		m_particleAnimation->FinishRef(m_tireSmokeParticle);
		m_tireSmokeParticle = NULL;
	}

	m_flags &= ~c_flagSkidding;
}

// FUNCTION: LEGORACERS 0x0043dd50
void CarVisuals::SetWheelParticle(LegoU32 p_wheelIndex, const LegoChar* p_name)
{
	if (m_wheelParticles[p_wheelIndex]) {
		if (::strncmp(m_wheelParticleNames[p_wheelIndex], p_name, sizeof(GolName)) == 0) {
			return;
		}

		m_particleAnimation->ReleaseRef(m_wheelParticles[p_wheelIndex]);
		m_wheelParticles[p_wheelIndex] = NULL;
	}

	::memcpy(m_wheelParticleNames[p_wheelIndex], p_name, sizeof(GolName));
	if (m_particleAnimation->HasEmitter(p_name)) {
		m_wheelParticles[p_wheelIndex] = m_particleAnimation->SpawnParticle(p_name, NULL, NULL, NULL);
		m_wheelParticleFromRace[p_wheelIndex] = TRUE;
	}
	else if (m_sharedParticleAnimation->HasEmitter(p_name)) {
		m_wheelParticles[p_wheelIndex] = m_sharedParticleAnimation->SpawnParticle(p_name, NULL, NULL, NULL);
		m_wheelParticleFromRace[p_wheelIndex] = FALSE;
	}

	CutsceneParticleRef* ref = m_wheelParticles[p_wheelIndex];
	if (!ref) {
		return;
	}

	GolVec3 position = m_racerPhysics->m_wheelProbes[p_wheelIndex].m_wheelPosition;
	CutsceneParticle* particle = ref->m_particle;
	GolWorldEntity* entity = m_carEntity;

	if (particle) {
		entity->CopyOrientation(particle->GetBasis());
	}

	if (m_wheelParticles[p_wheelIndex]->m_particle) {
		m_wheelParticles[p_wheelIndex]->m_particle->SetPosition(&position);
	}
}

// FUNCTION: LEGORACERS 0x0043de90
void CarVisuals::ClearWheelParticle(LegoU32 p_wheelIndex)
{
	if (m_wheelParticles[p_wheelIndex]) {
		m_wheelParticleNames[p_wheelIndex][0] = 0;
		if (m_wheelParticleFromRace[p_wheelIndex]) {
			m_particleAnimation->ReleaseRef(m_wheelParticles[p_wheelIndex]);
		}
		else {
			m_sharedParticleAnimation->ReleaseRef(m_wheelParticles[p_wheelIndex]);
		}
		m_wheelParticles[p_wheelIndex] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0043def0
void CarVisuals::StartDust()
{
	CutsceneParticleRef* ref = m_dustParticle;
	if (ref) {
		return;
	}
	if (m_wheelParticles[3]) {
		return;
	}
	if (m_wheelParticles[2]) {
		return;
	}

	ref = m_particleAnimation->SpawnParticle("dust", NULL, NULL, NULL);
	m_dustParticle = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_racerPhysics->m_wheelProbes[3].m_wheelPosition;
	CutsceneParticle* particle = ref->m_particle;
	GolWorldEntity* entity = m_carEntity;

	if (particle) {
		entity->CopyOrientation(particle->GetBasis());
	}

	if (m_dustParticle->m_particle) {
		m_dustParticle->m_particle->SetPosition(&position);
	}
}

// FUNCTION: LEGORACERS 0x0043df90
void CarVisuals::StartCarSmoke()
{
	CutsceneParticleRef* ref = m_carSmokeParticle;
	if (ref) {
		return;
	}

	ref = m_particleAnimation->SpawnParticle("carsmke", NULL, NULL, NULL);
	m_carSmokeParticle = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_racerPhysics->m_wheelProbes[3].m_wheelPosition;
	GolVec3 other = m_racerPhysics->m_wheelProbes[2].m_wheelPosition;
	GolWorldEntity* entity = m_carEntity;

	position.m_x = (position.m_x + other.m_x) * 0.5f;
	position.m_y = (position.m_y + other.m_y) * 0.5f;
	position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

	CutsceneParticle* particle = ref->m_particle;
	if (particle) {
		entity->CopyOrientation(particle->GetBasis());
	}

	if (m_carSmokeParticle->m_particle) {
		m_carSmokeParticle->m_particle->SetPosition(&position);
	}
}

// STUB: LEGORACERS 0x0043e070
void CarVisuals::Update(LegoU32 p_elapsedMs)
{
	UpdateBodyLean(p_elapsedMs);
	UpdateDriver(p_elapsedMs);
	m_entityGroup.UpdateBounds();

	if (m_isFlashing) {
		if (p_elapsedMs >= m_flashTimerMs) {
			EndFlash();
		}
		else {
			m_flashTimerMs -= p_elapsedMs;
		}
	}

	if (!(m_racer->m_flags & Racer::c_flagGhost)) {
		if (m_racerPhysics->m_flags & RacerPhysics::c_flagSpinning) {
			if (!(m_flags & c_flagSliding)) {
				StartSlideSkid();
			}
		}
		else if (m_flags & c_flagSliding) {
			StopSlideSkid();
		}

		for (LegoU32 slotIndex = 0; slotIndex < sizeOfArray(m_wheelSkidFlags); slotIndex++) {
			if (m_wheelSkidFlags[slotIndex] & c_wheelSkidFading) {
				LegoU32 elapsed = m_skidFadeTimers[slotIndex] + p_elapsedMs;
				m_skidFadeTimers[slotIndex] = elapsed;

				if (elapsed > 1000) {
					m_wheelSkidFlags[slotIndex] &= ~c_wheelSkidFading;
					m_skidFadeTimers[slotIndex] = 0;
				}
			}
		}

		if ((m_racer->m_flags & Racer::c_flagHalted) && (m_flags & c_flagSkidding)) {
			StopSkidEffects();
		}

		UpdateSkidMarks(p_elapsedMs);

		if (m_racer->m_flags & Racer::c_flagCursed) {
			UpdateCurseEntity(p_elapsedMs);
		}
		else {
			m_curseBlendMs = 1000;
		}

		GolVec3 velocity = m_racerPhysics->m_velocity * 0.5f;

		for (LegoU32 particleIndex = 0; particleIndex < sizeOfArray(m_wheelParticles); particleIndex++) {
			CutsceneParticleRef* ref = m_wheelParticles[particleIndex];
			if (ref) {
				GolVec3 position = m_racerPhysics->m_wheelProbes[particleIndex].m_wheelPosition;
				CutsceneParticle* particle = ref->m_particle;

				if (particle) {
					m_carEntity->CopyOrientation(particle->GetBasis());
				}

				if (ref->m_particle) {
					ref->m_particle->SetPosition(&position);
				}

				if (ref->m_particle) {
					ref->m_particle->SetVelocity(&velocity);
				}
			}
		}

		if (m_racer->m_physics.m_airborneMs > 400) {
			m_flags |= c_flagAirborne;
		}

		if (m_flags & c_flagAirborne) {
			LegoU32 state = m_racer->m_physics.m_contactCount;
			if (m_lastGroundedWheelCount < state) {
				m_flags &= ~c_flagAirborne;

				SoundVector position;
				m_carEntity->GetPosition(&position);

				switch (state - m_lastGroundedWheelCount) {
				case 1:
					m_racer->m_soundSource->PlaySpatialSoundById(
						0x3f,
						&position,
						g_shieldSoundMinDistance,
						g_shieldSoundMaxDistance,
						1.0f,
						1.0f
					);
					break;
				case 2:
				case 3:
					m_racer->m_soundSource->PlaySpatialSoundById(
						0x40,
						&position,
						g_shieldSoundMinDistance,
						g_shieldSoundMaxDistance,
						1.0f,
						1.0f
					);
					break;
				case 4:
					m_racer->m_soundSource->PlaySpatialSoundById(
						4,
						&position,
						g_shieldSoundMinDistance,
						g_shieldSoundMaxDistance,
						1.0f,
						1.0f
					);
					break;
				}

				m_particleAnimation->SpawnParticle("carland", &position, NULL, NULL);
			}

			m_lastGroundedWheelCount = state;
		}

		if (m_dustParticle) {
			CutsceneParticle* particle = m_dustParticle->m_particle;
			if (particle && particle->GetSpawnedCount() >= 10) {
				m_particleAnimation->FinishRef(m_dustParticle);
				m_dustParticle = NULL;
			}
			else {
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				GolVec3 position = (g_randomTable[g_randomTableIndex] & 2)
									   ? m_racerPhysics->m_wheelProbes[3].m_wheelPosition
									   : m_racerPhysics->m_wheelProbes[2].m_wheelPosition;

				particle = m_dustParticle->m_particle;
				if (particle) {
					m_carEntity->CopyOrientation(particle->GetBasis());
				}

				if (m_dustParticle->m_particle) {
					m_dustParticle->m_particle->SetPosition(&position);
				}

				if (m_dustParticle->m_particle) {
					m_dustParticle->m_particle->SetVelocity(&velocity);
				}
			}
		}

		if (m_carSmokeParticle) {
			CutsceneParticle* particle = m_carSmokeParticle->m_particle;
			if (particle && particle->GetSpawnedCount() >= 4) {
				m_particleAnimation->FinishRef(m_carSmokeParticle);
				m_carSmokeParticle = NULL;
			}
			else {
				GolVec3 position = m_racerPhysics->m_wheelProbes[3].m_wheelPosition;
				GolVec3 other = m_racerPhysics->m_wheelProbes[2].m_wheelPosition;
				position.m_x = (position.m_x + other.m_x) * 0.5f;
				position.m_y = (position.m_y + other.m_y) * 0.5f;
				position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

				particle = m_carSmokeParticle->m_particle;
				if (particle) {
					m_carEntity->CopyOrientation(particle->GetBasis());
				}

				if (m_carSmokeParticle->m_particle) {
					m_carSmokeParticle->m_particle->SetPosition(&position);
				}

				if (m_carSmokeParticle->m_particle) {
					m_carSmokeParticle->m_particle->SetVelocity(&velocity);
				}
			}
		}

		if (m_tireSmokeParticle) {
			GolVec3 position;
			position.m_x = 0.0f;
			position.m_y = 0.0f;
			position.m_z = 0.0f;

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			LegoBool32 chooseSecond = (g_randomTable[g_randomTableIndex] >> 1) & 1;
			LegoBool32 found = FALSE;

			for (LegoU32 tireIndex = 0; tireIndex < sizeOfArray(m_wheelSkidFlags); tireIndex++) {
				if (m_wheelSkidFlags[tireIndex] & c_wheelSkidGrounded) {
					if (!chooseSecond || !found) {
						position = m_racerPhysics->m_wheelProbes[tireIndex].m_wheelPosition;
						found = TRUE;
					}
					else {
						break;
					}
				}
			}

			CutsceneParticle* particle = m_tireSmokeParticle->m_particle;
			if (particle) {
				m_carEntity->CopyOrientation(particle->GetBasis());
			}

			if (m_tireSmokeParticle->m_particle) {
				m_tireSmokeParticle->m_particle->SetPosition(&position);
			}

			if (m_tireSmokeParticle->m_particle) {
				m_tireSmokeParticle->m_particle->SetVelocity(&velocity);
			}
		}
	}

	m_flags &= ~c_flagShadowVisible;
}

// FUNCTION: LEGORACERS 0x0043e620
void CarVisuals::SnapVisuals()
{
	m_carEntity->CopyOrientationAndPositionTo(m_bodyModelEntity);

	GolVec3 position;
	m_bodyModelEntity->LocalToWorld(m_driverMountOffset, &position);
	m_driverEntity->SetPosition(position);
	m_driverEntity->CopyOrientationFrom(*m_bodyModelEntity);

	if (m_secondaryEntity != NULL) {
		m_carEntity->CopyOrientationAndPositionTo(m_secondaryEntity);
	}
}

// FUNCTION: LEGORACERS 0x0043e740
void CarVisuals::UpdateBodyLean(LegoS32 p_elapsedMs)
{
	GolVec3 position;
	m_carEntity->GetPosition(&position);

	const GolMatrix3& oldOrientation = m_carEntity->GetOrientation();
	GolVec3 oldRow0;
	GolVec3 oldRow1;
	GolVec3 oldRow2;
	oldRow0.m_x = oldOrientation.m_m[0][0];
	oldRow0.m_y = oldOrientation.m_m[0][1];
	oldRow0.m_z = oldOrientation.m_m[0][2];
	oldRow1.m_x = oldOrientation.m_m[1][0];
	oldRow1.m_y = oldOrientation.m_m[1][1];
	oldRow1.m_z = oldOrientation.m_m[1][2];
	oldRow2.m_x = oldOrientation.m_m[2][0];
	oldRow2.m_y = oldOrientation.m_m[2][1];
	oldRow2.m_z = oldOrientation.m_m[2][2];
	m_carEntity->Update(p_elapsedMs);

	const GolVec3& modelRow2 = m_bodyModelEntity->GetOrientation().m_rows[2];
	GolVec3 targetRow0;
	targetRow0.m_x = oldRow1.m_y * modelRow2.m_z - oldRow1.m_z * modelRow2.m_y;
	targetRow0.m_y = oldRow1.m_z * modelRow2.m_x - oldRow1.m_x * modelRow2.m_z;
	targetRow0.m_z = oldRow1.m_x * modelRow2.m_y - oldRow1.m_y * modelRow2.m_x;

	LegoFloat length = static_cast<LegoFloat>(sqrt(
		(oldRow0.m_z - targetRow0.m_z) * (oldRow0.m_z - targetRow0.m_z) +
		(oldRow0.m_y - targetRow0.m_y) * (oldRow0.m_y - targetRow0.m_y) +
		(oldRow0.m_x - targetRow0.m_x) * (oldRow0.m_x - targetRow0.m_x)
	));
	if (targetRow0.m_z * oldRow2.m_z + targetRow0.m_y * oldRow2.m_y + targetRow0.m_x * oldRow2.m_x < 0.0f) {
		length = -length;
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoFloat scale = g_pitchLeanRate;
	scale = -scale;
	m_pitchLean += (scale * length) * elapsed / m_racerPhysics->m_mass;
	LegoFloat decay = elapsed;
	decay *= g_pitchLeanDamping;
	decay *= m_pitchLean;
	if ((m_pitchLean > 0.0f && decay < m_pitchLean) || (m_pitchLean < 0.0f && decay > m_pitchLean)) {
		m_pitchLean -= decay;
	}
	else {
		m_pitchLean = 0.0f;
	}

	GolVec3 targetRow1;
	targetRow1.m_x = modelRow2.m_y * oldRow0.m_z - modelRow2.m_z * oldRow0.m_y;
	targetRow1.m_y = modelRow2.m_z * oldRow0.m_x - modelRow2.m_x * oldRow0.m_z;
	targetRow1.m_z = modelRow2.m_x * oldRow0.m_y - modelRow2.m_y * oldRow0.m_x;

	length = static_cast<LegoFloat>(sqrt(
		(oldRow1.m_z - targetRow1.m_z) * (oldRow1.m_z - targetRow1.m_z) +
		(oldRow1.m_y - targetRow1.m_y) * (oldRow1.m_y - targetRow1.m_y) +
		(oldRow1.m_x - targetRow1.m_x) * (oldRow1.m_x - targetRow1.m_x)
	));
	if (targetRow1.m_z * oldRow2.m_z + targetRow1.m_y * oldRow2.m_y + targetRow1.m_x * oldRow2.m_x < 0.0f) {
		length = -length;
	}

	scale = g_rollLeanRate;
	scale = -scale;
	m_rollLean += (scale * length) * elapsed / m_racerPhysics->m_mass;
	decay = elapsed;
	decay *= g_rollLeanDamping;
	decay *= m_rollLean;
	if ((m_rollLean > 0.0f && decay < m_rollLean) || (m_rollLean < 0.0f && decay > m_rollLean)) {
		m_rollLean -= decay;
	}
	else {
		m_rollLean = 0.0f;
	}

	GolVec3 row0;
	if (m_pitchLean == 0.0f) {
		row0 = oldRow0;
	}
	else {
		LegoFloat value = m_pitchLean;
		oldRow0.m_x = oldRow2.m_x * value;
		oldRow0.m_y = oldRow2.m_y * value;
		oldRow0.m_z = oldRow2.m_z * value;
		GolCameraBase::Add(&targetRow0, &oldRow0, &row0);
	}

	GolVec3 row1;
	if (m_rollLean == 0.0f) {
		row1 = oldRow1;
	}
	else {
		LegoFloat value = m_rollLean;
		oldRow1.m_x = oldRow2.m_x * value;
		oldRow1.m_y = oldRow2.m_y * value;
		oldRow1.m_z = oldRow2.m_z * value;
		GolCameraBase::Add(&targetRow1, &oldRow1, &row1);
	}

	m_bodyModelEntity->SetPosition(position);
	m_bodyModelEntity->SetDirectionSide(row0, row1);

	if (m_secondaryEntity != NULL) {
		m_bodyModelEntity->CopyOrientationAndPositionTo(m_secondaryEntity);
		m_secondaryEntity->Update(p_elapsedMs);
	}

	m_bodyModelEntity->LocalToWorld(m_driverMountOffset, &position);
	m_driverEntity->SetPosition(position);
	m_driverEntity->CopyOrientationFrom2(*m_bodyModelEntity);
}

// FUNCTION: LEGORACERS 0x0043ebd0
void GolOrientedEntity::CopyOrientationFrom2(const GolOrientedEntity& p_other)
{
	m_orientation.m_m[0][0] = p_other.m_orientation.m_m[0][0];
	m_orientation.m_m[0][1] = p_other.m_orientation.m_m[0][1];
	m_orientation.m_m[0][2] = p_other.m_orientation.m_m[0][2];
	m_orientation.m_m[1][0] = p_other.m_orientation.m_m[1][0];
	m_orientation.m_m[1][1] = p_other.m_orientation.m_m[1][1];
	m_orientation.m_m[1][2] = p_other.m_orientation.m_m[1][2];
	m_orientation.m_m[2][0] = p_other.m_orientation.m_m[2][0];
	m_orientation.m_m[2][1] = p_other.m_orientation.m_m[2][1];
	m_orientation.m_m[2][2] = p_other.m_orientation.m_m[2][2];
}

// FUNCTION: LEGORACERS 0x0043ec10
void CarVisuals::UpdateDriver(LegoU32 p_elapsedMs)
{
	DriveController* controller = &m_racer->m_driveController;
	LegoFloat activeValue = controller->m_turnRadius;
	LegoFloat speed = m_racerPhysics->m_forwardSpeed;
	LegoU32 activePart = m_driverEntity->GetActiveState();
	LegoU32 eventFlags = m_reactionFlags;

	m_driverEntity->Update(p_elapsedMs);
	m_reactionFlags = 0;

	if (p_elapsedMs < m_lookCooldownMs) {
		m_lookCooldownMs -= p_elapsedMs;
	}
	else {
		m_lookCooldownMs = 0;
	}

	if (m_racer->m_lapsCompleted >= g_raceLapCount) {
		if (m_racer->m_lapTimes[5] == 1) {
			if (activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart14) {
				return;
			}

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			if (g_randomTable[g_randomTableIndex] % 2 != 0) {
				m_driverEntity->PlayPart(c_animationPart14);
				m_driverEntity->QueuePartTransition(c_animationPart15);
			}
			else {
				m_driverEntity->PlayPart(c_animationPart13);
			}
			return;
		}

		if (activePart == c_animationPart12 || activePart == c_animationPart11) {
			return;
		}

		m_driverEntity->PlayPart(c_animationPart11);
		m_driverEntity->QueuePartTransition(c_animationPart12);
		return;
	}

	if (m_lastSpeed > g_unk0x004b0544 && speed < g_carBuildPreviewMouseScale && activePart != c_animationPart0) {
		m_racer->PlayReaction(FALSE);
		m_driverEntity->PlayPart(c_animationPart0);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		m_lastSpeed = 0.0f;

		if (m_racer->m_forceFeedback != NULL) {
			m_racer->m_forceFeedback->PlayReactionRumble();
		}
		return;
	}

	m_lastSpeed = speed;

	if (eventFlags & c_flags0x384Bit0) {
		m_driverEntity->PlayPart(c_animationPart1);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		return;
	}

	if (eventFlags & c_reactionHit) {
		m_driverEntity->PlayPart(c_animationPart10);
		m_driverEntity->QueuePartTransition(c_animationPart9);

		if (m_racer->m_forceFeedback != NULL) {
			m_racer->m_forceFeedback->PlayReactionRumble();
		}
		return;
	}

	if (activePart == c_animationPart0 || activePart == c_animationPart1 || activePart == c_animationPart10 ||
		activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart12) {
		return;
	}

	if (controller->m_thrust < 0.0f && speed < 0.0f) {
		if (activePart == c_animationPart2 || activePart == c_animationPart3) {
			return;
		}

		m_driverEntity->PlayPart(c_animationPart2);
		m_driverEntity->QueuePartTransition(c_animationPart3);
		return;
	}

	if (activePart == c_animationPart3) {
		m_driverEntity->PlayPart(c_animationPart4);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		return;
	}

	if (activePart == c_animationPart7 || activePart == c_animationPart16 || activePart == c_animationPart8 ||
		activePart == c_animationPart17) {
		return;
	}

	if (m_lookCooldownMs == 0) {
		GolVec3 position;
		m_carEntity->GetPosition(&position);

		Racer* racer = m_racer;
		RaceState* raceState = racer->m_raceState;
		Racer* nearbyRacer = raceState->FindNearestRacerInRange(&position, 2.0f, g_lookTargetRangeSquared);
		m_nearbyRacer = nearbyRacer;

		if (nearbyRacer != NULL) {
			GolAnimatedEntity* nearbyEntity = nearbyRacer->m_visuals.m_carEntity;
			GolVec3 row0 = m_carEntity->GetOrientation().m_rows[0];
			GolVec3 row1 = m_carEntity->GetOrientation().m_rows[1];

			GolVec3 nearbyPosition;
			nearbyEntity->GetPosition(&nearbyPosition);

			GolVec3 direction;
			direction.m_x = nearbyPosition.m_x - position.m_x;
			direction.m_y = nearbyPosition.m_y - position.m_y;
			direction.m_z = nearbyPosition.m_z - position.m_z;
			GolMath::NormalizeVector3(direction, &direction);

			LegoFloat forwardDot = row0.m_z * direction.m_z + row0.m_y * direction.m_y + row0.m_x * direction.m_x;
			LegoU32 animationPart = 0;
			if (forwardDot < g_unk0x004b02e0 && forwardDot > g_lookAtDotBeside) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart7 : c_animationPart16;
			}
			else if (forwardDot < g_unk0x004b02e0 && forwardDot > g_lookAtDotBehind) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart8 : c_animationPart17;
			}

			if (animationPart) {
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				m_lookCooldownMs =
					(g_randomTable[g_randomTableIndex] % c_avoidanceCooldownRangeMs) + c_avoidanceCooldownBaseMs;
				m_driverEntity->PlayPart(animationPart);
				m_driverEntity->QueuePartTransition(c_animationPart9);
				return;
			}
		}
	}

	if (activeValue < 0.0f) {
		if (activePart != c_animationPart5) {
			m_driverEntity->TransitionToPart(c_animationPart5, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue > 0.0f) {
		if (activePart != c_animationPart6) {
			m_driverEntity->TransitionToPart(c_animationPart6, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue == 0.0f && activePart != c_animationPart9) {
		m_driverEntity->TransitionToPart(c_animationPart9, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
	}
}

// FUNCTION: LEGORACERS 0x0043f1e0
void CarVisuals::UpdateSkidMarks(LegoU32 p_elapsedMs)
{
	if (!(m_flags & c_flagSkidding)) {
		return;
	}

	GolVec3 position;

	{
		for (LegoU32 i = 0; i < sizeOfArray(m_wheelSkidFlags); i++) {
			LegoU8 flags = m_wheelSkidFlags[i];
			if (flags & c_wheelSkidActive) {
				if (!(flags & c_wheelSkidGrounded) &&
					(m_racerPhysics->m_wheelProbes[i].m_flags & RacerPhysics::WheelProbe::c_flagContact)) {
					flags |= c_wheelSkidGrounded;
					m_wheelSkidFlags[i] = flags;
				}
				else if (m_racerPhysics->m_wheelProbes[i].m_flags & RacerPhysics::WheelProbe::c_flagContact) {
					flags &= ~c_wheelSkidGrounded;
					m_wheelSkidFlags[i] = flags;
				}
				else {
					LegoU32 elapsed = m_wheelAirTimers[i] + p_elapsedMs;
					m_wheelAirTimers[i] = elapsed;
					if (elapsed > 150) {
						m_wheelSkidFlags[i] &= ~c_wheelSkidGrounded;
						m_wheelAirTimers[i] = 0;
					}
				}
			}
			else {
				m_wheelSkidFlags[i] = flags & ~c_wheelSkidGrounded;
			}

			if (m_skidMarks[i]) {
				m_carEntity->LocalToWorld(m_wheelOffsets[i], &position);
				m_skidMarks[i]->AddSample(p_elapsedMs, position);
			}
		}
	}

	if (m_racerPhysics->m_flags & RacerPhysics::c_flagSpinning) {
		m_wheelSkidFlags[0] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[1] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[2] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[3] |= c_wheelSkidAllButActive;
	}
	else if (m_racer->m_flags & Racer::c_flagTurbo) {
		m_wheelSkidFlags[0] &= ~c_wheelSkidActive;
		m_wheelSkidFlags[2] |= c_wheelSkidActive;
		m_wheelSkidFlags[1] &= ~c_wheelSkidActive;
		m_wheelSkidFlags[3] |= c_wheelSkidActive;
	}
	else {
		GolVec3 slipDirection = m_racerPhysics->m_velocityDirection;
		LegoFloat dot = m_carEntity->GetOrientation().m_rows[1].m_x * slipDirection.m_x +
						m_carEntity->GetOrientation().m_rows[1].m_y * slipDirection.m_y +
						m_carEntity->GetOrientation().m_rows[1].m_z * slipDirection.m_z;
		if (dot > 0.0f) {
			m_wheelSkidFlags[0] &= ~c_wheelSkidActive;
			m_wheelSkidFlags[2] &= ~c_wheelSkidActive;
			m_wheelSkidFlags[1] |= c_wheelSkidActive;
			m_wheelSkidFlags[3] |= c_wheelSkidActive;
		}
		else {
			m_wheelSkidFlags[0] |= c_wheelSkidActive;
			m_wheelSkidFlags[2] |= c_wheelSkidActive;
			m_wheelSkidFlags[1] &= ~c_wheelSkidActive;
			m_wheelSkidFlags[3] &= ~c_wheelSkidActive;
		}
	}

	{
		RaceDecalManager::Trail** itemSlot = m_skidMarks;
		LegoU32 i = 0;
		LegoU8 colorByte = 0xff;
		do {
			LegoU32 sliding = m_flags & c_flagSliding;
			if (sliding) {
				RaceDecalManager::Trail* item = *itemSlot;
				if (item && item->GetDurationMs() == 1000) {
					m_skidMarkManager->ReleaseTrail(item, 0);
					*itemSlot = NULL;
				}
			}
			else {
				RaceDecalManager::Trail* item = *itemSlot;
				if (item && item->GetDurationMs() == 250) {
					m_skidMarkManager->ReleaseTrail(item, 0);
					*itemSlot = NULL;
				}
			}

			if (m_wheelSkidFlags[i] & c_wheelSkidActive) {
				if (!*itemSlot) {
					if (m_flags & c_flagSliding) {
						*itemSlot = m_skidMarkManager->AcquireTrail(250);
					}
					else {
						*itemSlot = m_skidMarkManager->AcquireTrail(1000);
					}

					if (*itemSlot) {
						ColorRGBA color;
						color.m_red = colorByte;
						color.m_grn = colorByte;
						color.m_blu = colorByte;
						color.m_alp = colorByte;
						(*itemSlot)->SetColor(&color);
						(*itemSlot)->SetMaterialTable(&m_skidMaterialTable);

						if (i == 0 || i == 1) {
							(*itemSlot)->SetWidth(m_frontSkidWidth);
						}
						else {
							(*itemSlot)->SetWidth(m_rearSkidWidth);
						}
					}
				}
			}
			else if (*itemSlot) {
				m_skidMarkManager->ReleaseTrail(*itemSlot, 0);
				*itemSlot = NULL;
			}
			i++;
			itemSlot++;
		} while (i < sizeOfArray(m_skidMarks));
	}
}

// STUB: LEGORACERS 0x0043f530
void CarVisuals::UpdateCurseEntity(LegoU32 p_elapsedMs)
{
	if (p_elapsedMs > m_cursePhaseMs) {
		m_cursePhaseMs = 1000;
	}
	else {
		m_cursePhaseMs -= p_elapsedMs;
	}

	if (p_elapsedMs > m_curseBlendMs) {
		m_curseBlendMs = 0;
	}
	else {
		m_curseBlendMs -= p_elapsedMs;
	}

	LegoFloat phase = static_cast<LegoFloat>(m_cursePhaseMs) * g_cursePhaseScale;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase * g_negativeRadiansToTableIndex)) & c_randomTableMask;
	LegoFloat offsetX = g_cosineTable[tableIndex];
	tableIndex = static_cast<LegoS32>(phase * g_sweepCannonRadiansToTableIndex) & c_randomTableMask;
	LegoFloat offsetY = g_cosineTable[tableIndex];

	GolModelEntity* entity = &m_curseEntity;
	GolVec3 position;
	entity->GetPosition(&position);

	GolVec3 target;
	m_bodyModelEntity->GetPosition(&target);
	target.m_x += 6.0f * offsetX;
	target.m_y += 6.0f * offsetY;
	target.m_z += 9.0f;

	LegoFloat speed = m_racerPhysics->m_speed;
	if (speed <= 0.1f) {
		speed = 0.1f;
	}

	LegoFloat elapsed = static_cast<LegoFloat>(p_elapsedMs);
	LegoFloat maxMove = elapsed * speed;
	GolVec3 delta;
	delta.m_x = target.m_x - position.m_x;
	delta.m_y = target.m_y - position.m_y;
	delta.m_z = target.m_z - position.m_z;

	if (delta.m_z * delta.m_z + delta.m_y * delta.m_y + delta.m_x * delta.m_x > maxMove * maxMove) {
		GolMath::NormalizeVector3(delta, &delta);
		position.m_x += delta.m_x * maxMove;
		position.m_y += delta.m_y * maxMove;
		position.m_z += delta.m_z * maxMove;
	}
	else {
		position = target;
	}
	entity->SetPosition(position);

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	m_bodyModelEntity->GetPosition(&target);
	delta.m_x = target.m_x - position.m_x;
	delta.m_y = target.m_y - position.m_y;
	delta.m_z = target.m_z - position.m_z;
	GolMath::NormalizeVector3(delta, &delta);

	GolVec3 right;
	right.m_x = up.m_y * delta.m_z - up.m_z * delta.m_y;
	right.m_y = up.m_z * delta.m_x - up.m_x * delta.m_z;
	right.m_z = up.m_x * delta.m_y - up.m_y * delta.m_x;
	GolMath::NormalizeVector3(right, &right);

	if (m_curseBlendMs > 0) {
		GolMatrix3 currentOrientation;
		entity->CopyOrientation(&currentOrientation);
		GolVec3 unit;
		GolMath::NormalizeVector3(right, &unit);

		LegoFloat dot = unit.m_z * up.m_z + unit.m_y * up.m_y + unit.m_x * up.m_x;
		up.m_x -= unit.m_x * dot;
		up.m_y -= unit.m_y * dot;
		up.m_z -= unit.m_z * dot;
		GolMath::NormalizeVector3(up, &up);

		GolVec3 cross;
		cross.m_x = up.m_y * unit.m_z - up.m_z * unit.m_y;
		cross.m_y = up.m_z * unit.m_x - up.m_x * unit.m_z;
		cross.m_z = up.m_x * unit.m_y - up.m_y * unit.m_x;

		GolMatrix3 desiredOrientation;
		desiredOrientation.m_m[0][0] = unit.m_x;
		desiredOrientation.m_m[0][1] = unit.m_y;
		desiredOrientation.m_m[0][2] = unit.m_z;
		desiredOrientation.m_m[1][0] = cross.m_x;
		desiredOrientation.m_m[1][1] = cross.m_y;
		desiredOrientation.m_m[1][2] = cross.m_z;
		desiredOrientation.m_m[2][0] = up.m_x;
		desiredOrientation.m_m[2][1] = up.m_y;
		desiredOrientation.m_m[2][2] = up.m_z;

		LegoFloat amount = static_cast<LegoFloat>(m_curseBlendMs) * 0.001f;
		GolQuat desiredRotation;
		GolQuat currentRotation;
		GolQuat blendedRotation;
		GolMath::Matrix3ToQuat(desiredOrientation, &desiredRotation);
		GolMath::Matrix3ToQuat(currentOrientation, &currentRotation);
		GolMath::LerpQuat(desiredRotation, currentRotation, amount, &blendedRotation);

		GolMatrix3 orientation;
		GolMath::QuatToMatrix3(&blendedRotation, &orientation.m_m[0][0]);
		entity->SetOrientationMatrix(orientation);
	}
	else {
		entity->SetDirectionUp(right, up);
	}

	LegoFloat scale = entity->GetScale();
	if (scale > 0.66600001f) {
		scale -= elapsed * 0.0099999998f * 0.065999999f;
		if (scale < 0.66600001f) {
			scale = 0.66600001f;
		}
		entity->SetScaleThenInvalidateRadius(scale);
	}

	entity->Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0043fa50
void CarVisuals::UpdateShadow(GolCamera* p_camera)
{
	LegoU32 flags = m_flags;
	if ((flags & c_flagShadowVisible) || !(flags & c_flagShadowEnabled)) {
		return;
	}

	GolVec3 entityPosition;
	m_carEntity->GetPosition(&entityPosition);

	GolVec3 cameraPosition;
	p_camera->GetTransform()->GetPosition(&cameraPosition);

	LegoFloat deltaX = entityPosition.m_x - cameraPosition.m_x;
	LegoFloat deltaY = entityPosition.m_y - cameraPosition.m_y;
	LegoFloat deltaZ = entityPosition.m_z - cameraPosition.m_z;
	LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
	if (distanceSquared < m_carEntity->GetModelDistance(0)) {
		m_flags |= c_flagShadowVisible;

		GolVec3 up;
		m_carEntity->GetOrientationRow1(&up);

		GolVec3 center;
		m_carEntity->GetBoundsCenter(&center);

		LegoFloat scale = m_carEntity->GetScale();
		if (scale != 1.0f) {
			m_shadowDecal.m_width = m_shadowWidth * scale;
			m_shadowDecal.m_length = scale * m_shadowLength;
		}
		else {
			m_shadowDecal.m_width = m_shadowWidth * 1.0f;
			m_shadowDecal.m_length = m_shadowLength * 1.0f;
		}

		m_shadowDecal.m_depth = g_unk0x004b0af0;
		center.m_z += g_shadowProbeHeight;

		RaceDecalManager::Trail::Decal* field = &m_shadowDecal;
		field->m_center.m_x = center.m_x;
		field->m_center.m_y = center.m_y;
		field->m_center.m_z = center.m_z;

		up.m_x = -up.m_x;
		up.m_y = -up.m_y;
		MaterialTable* materialTable = &m_shadowMaterialTable;
		GolVec3* upVector = &up;
		GolVec3* vector = &m_shadowDirection;
		m_shadowDecal.GetEntity().SetPrimaryMaterialTable(materialTable);
		up.m_z = -up.m_z;
		field->SetOrientation(vector, upVector);
		field->Project(m_trackCollidable);
	}
}

// FUNCTION: LEGORACERS 0x0043fbc0
void CarVisuals::Draw(GolD3DRenderDevice* p_renderer)
{
	if (!(m_flags & c_flagVisible0)) {
		p_renderer->DrawModelEntity(m_carEntity);
	}

	if (!(m_flags & c_flagVisible1)) {
		p_renderer->DrawModelEntity(m_bodyModelEntity);

		if (m_secondaryEntity) {
			p_renderer->DrawModelEntity(m_secondaryEntity);
		}
	}

	if (!(m_flags & c_flagVisible2)) {
		p_renderer->DrawModelEntity(m_driverEntity);
	}
}

// FUNCTION: LEGORACERS 0x0043fc20
void CarVisuals::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & c_flagShadowVisible) {
		RaceDecalManager::Trail::Decal* field = &m_shadowDecal;
		GolVec3 cameraPosition;
		p_renderer->GetCurrentCamera()->GetTransform()->GetPosition(&cameraPosition);

		GolVec3 position;
		LegoFloat deltaX = field->m_center.m_x;
		position.m_y = field->m_center.m_y;
		position.m_z = field->m_center.m_z;

		deltaX = cameraPosition.m_x - deltaX;
		LegoFloat deltaY = cameraPosition.m_y - position.m_y;
		LegoFloat deltaZ = cameraPosition.m_z - position.m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;

		LegoS32 alpha;
		if (distanceSquared <= g_shadowFadeNearSquared) {
			alpha = c_fadeAlphaMax;
		}
		else if (distanceSquared < g_shadowFadeFarSquared) {
			alpha =
				c_fadeAlphaMax -
				static_cast<LegoS32>(
					((distanceSquared - g_shadowFadeNearSquared) / (g_shadowFadeFarSquared - g_shadowFadeNearSquared)) *
					g_fadeAlphaScale
				);
		}
		else {
			alpha = 0;
		}

		if (alpha) {
			p_renderer->SetAlphaOverride(alpha, c_alphaOverrideFlag);
			field->Draw(p_renderer);
			p_renderer->ClearAlphaOverride();
		}
	}

	if (m_racer->m_flags & Racer::c_flagCursed) {
		p_renderer->DrawModelEntity(&m_curseEntity);
	}
}

// FUNCTION: LEGORACERS 0x0043fd30
void CarVisuals::StartTurboEffects()
{
	if (m_racer->m_controlMode != Racer::c_controlAi) {
		StartDust();
		StartCarSmoke();

		if (m_racer->m_turboLevel > 0) {
			UseTurboSkidMaterial();
			StartSkidEffects();
		}
	}
}

// FUNCTION: LEGORACERS 0x0043fd70
void CarVisuals::StopTurboEffects()
{
	StopSkidEffects();
	UseNormalSkidMaterial();
}

// FUNCTION: LEGORACERS 0x0043fd90
void CarVisuals::StartSlideSkid()
{
	m_flags |= c_flagSliding;

	if (m_racer->m_controlMode != Racer::c_controlAi) {
		StartSkidEffects();
	}
}

// FUNCTION: LEGORACERS 0x0043fdb0
void CarVisuals::StopSlideSkid()
{
	m_flags &= ~c_flagSliding;
	StopSkidEffects();
}

// FUNCTION: LEGORACERS 0x0043fdc0
LegoBool32 CarVisuals::IntersectSegment(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit)
{
	GolVec3 center;
	LegoFloat radius;
	m_bodyModelEntity->GetModelBounds(0, &center, &radius);
	LegoFloat radiusSquared = radius * radius;

	GolVec3 direction;
	direction.m_x = p_end->m_x - p_start->m_x;
	direction.m_y = p_end->m_y - p_start->m_y;
	direction.m_z = p_end->m_z - p_start->m_z;
	GolMath::NormalizeVector3(direction, &direction);

	LegoFloat centerDeltaX = center.m_x - p_start->m_x;
	LegoFloat centerDeltaY = center.m_y - p_start->m_y;
	LegoFloat centerDeltaZ = center.m_z - p_start->m_z;
	LegoFloat projection = centerDeltaZ * direction.m_z + centerDeltaY * direction.m_y + centerDeltaX * direction.m_x;
	LegoFloat discriminant =
		radiusSquared - ((centerDeltaY * centerDeltaY + centerDeltaZ * centerDeltaZ + centerDeltaX * centerDeltaX) -
						 projection * projection);
	if (discriminant <= 0.0f) {
		return FALSE;
	}

	LegoFloat distance = projection - static_cast<LegoFloat>(sqrt(discriminant));
	LegoFloat segmentDeltaX = p_start->m_x - p_end->m_x;
	LegoFloat segmentDeltaY = p_start->m_y - p_end->m_y;
	LegoFloat segmentDeltaZ = p_start->m_z - p_end->m_z;
	if (distance * distance >
		segmentDeltaZ * segmentDeltaZ + segmentDeltaY * segmentDeltaY + segmentDeltaX * segmentDeltaX) {
		return FALSE;
	}

	GolVec3 hitDelta;
	hitDelta.m_x = direction.m_x;
	hitDelta.m_x *= distance;
	hitDelta.m_y = direction.m_y;
	hitDelta.m_y *= distance;
	hitDelta.m_z = direction.m_z;
	hitDelta.m_z *= distance;
	p_hit->m_x = p_start->m_x + hitDelta.m_x;
	p_hit->m_y = p_start->m_y + hitDelta.m_y;
	p_hit->m_z = p_start->m_z + hitDelta.m_z;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0043ff20
void CarVisuals::RenderShadowSilhouette(GolD3DRenderDevice* p_renderer)
{
	GolMaterial* material = p_renderer->FindMaterialByName(m_shadowTextureName);
	g_carShadowRenderState.Initialize(p_renderer, material->GetTexture());

	GolVec3 position;
	m_carEntity->GetPosition(&position);
	LegoFloat origin[2];
	origin[0] = position.m_x;
	origin[1] = position.m_y;

	ColorRGBA color = {0, 0, 0, 0};
	g_carShadowRenderState.SetFillColor(&color);

	color.m_red = 8;
	color.m_grn = 8;
	color.m_blu = 8;
	color.m_alp = 0xff;
	g_carShadowRenderState.SetSilhouetteColor(&color);

	LegoFloat width = m_shadowWidth;
	width *= g_carShadowScale;
	LegoFloat length = m_shadowLength;
	length *= g_carShadowScale;
	g_carShadowRenderState.BeginCapture(origin, length, width, g_silhouetteClearFlag | g_silhouetteFlattenFlag);
	g_carShadowRenderState.RenderEntity(m_carEntity, 0);
	g_carShadowRenderState.RenderEntity(m_bodyModelEntity, 0);

	if (m_secondaryEntity) {
		g_carShadowRenderState.RenderEntity(m_secondaryEntity, 0);
	}

	g_carShadowRenderState.EndCapture();
}

// FUNCTION: LEGORACERS 0x00440030
void CarVisuals::RebuildEntityGroup()
{
	m_entityGroup.Allocate(4);

	if (m_bodyModelEntity && !(m_flags & c_flagVisible1)) {
		m_entityGroup.AddEntity(m_bodyModelEntity);
	}

	if (m_secondaryEntity && !(m_flags & c_flagVisible1)) {
		m_entityGroup.AddEntity(m_secondaryEntity);
	}

	if (m_carEntity && !(m_flags & c_flagVisible0)) {
		m_entityGroup.AddEntity(m_carEntity);
	}

	if (m_driverEntity && !(m_flags & c_flagVisible2)) {
		m_entityGroup.AddEntity(m_driverEntity);
	}
}

// FUNCTION: LEGORACERS 0x004400a0
void CarVisuals::SetColorTransform(ColorTransform* p_transform)
{
	m_baseColorTransform = *p_transform;

	LegoU32 wasFlashing = m_isFlashing;
	m_hasColorTransform = 1;

	if (!wasFlashing) {
		m_entityGroup.ApplyColorTransform(&m_baseColorTransform);
	}
}

// FUNCTION: LEGORACERS 0x004400e0
void CarVisuals::ClearColorTransform()
{
	LegoU32 wasFlashing = m_isFlashing;
	m_hasColorTransform = 0;

	if (!wasFlashing) {
		m_entityGroup.ClearColorTransform();
	}
}

// FUNCTION: LEGORACERS 0x00440100
void CarVisuals::FlashColor(ColorTransform* p_transform, undefined4 p_durationMs)
{
	m_isFlashing = 1;
	m_flashTimerMs = p_durationMs;
	m_entityGroup.ApplyColorTransform(p_transform);
}

// FUNCTION: LEGORACERS 0x00440130
void CarVisuals::EndFlash()
{
	LegoU32 hadColorTransform = m_hasColorTransform;
	m_isFlashing = 0;
	m_flashTimerMs = 0;

	if (hadColorTransform) {
		m_entityGroup.ApplyColorTransform(&m_baseColorTransform);
	}
	else {
		m_entityGroup.ClearColorTransform();
	}
}

// FUNCTION: LEGORACERS 0x00440160
void CarVisuals::SetScale(LegoFloat p_scale)
{
	m_carEntity->SetScaleAndInvalidateRadius(p_scale);
	m_bodyModelEntity->SetScaleAndInvalidateRadius(p_scale);

	if (m_secondaryEntity) {
		m_secondaryEntity->SetScaleAndInvalidateRadius(p_scale);
	}

	m_driverEntity->SetScaleAndInvalidateRadius(p_scale);
}

// FUNCTION: LEGORACERS 0x004401a0
void CarVisuals::ResetDriverAnimation()
{
	m_driverEntity->PlayPart(9);
}

// FUNCTION: LEGORACERS 0x004401b0
void CarVisuals::PlayForwardAnimation()
{
	if (m_carEntity->GetActiveState()) {
		m_carEntity->PlayPart(0);
	}
}

// FUNCTION: LEGORACERS 0x004401e0
void CarVisuals::PlayReverseAnimation()
{
	CmbModelPart* modelPart = m_carEntity->GetModelPart();

	if (modelPart->GetPartCount() > 1 && m_carEntity->GetActiveState() != 1) {
		m_carEntity->PlayPart(1);
	}
}
