#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "duskwindbananarelic0x24.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golmateriallibrary.h"
#include "material/goltexturelist.h"
#include "menu/runtime/cutsceneparticle.h"
#include "menu/runtime/cutsceneplayer.h"
#include "race/cobalttrail0x140.h"
#include "race/racecameracontroller.h"
#include "race/raceeventtable0x90.h"
#include "race/raceforcefeedback.h"
#include "race/racesession.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/purpledune0x7c.h"
#include "util/racerbillboardrenderstate0x33c.h"

#include <float.h>
#include <math.h>
#include <string.h>

extern LegoFloat g_carBuildPreviewMouseScale;
extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_fadeAlphaScale;
extern const LegoFloat g_item0x40RadiansToTableIndex;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_racerBillboardScale;
extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;
extern const LegoFloat g_shieldSoundMaxDistance;
extern const LegoFloat g_shieldSoundMinDistance;
extern const LegoFloat g_unk0x004b02e0;
extern const LegoFloat g_unk0x004b0544;
extern const LegoFloat g_unk0x004b0ac0;
extern const LegoFloat g_unk0x004b0af0;
extern const LegoFloat g_unk0x004b0af4;
extern const LegoFloat g_unk0x004b0b24;
extern const LegoFloat g_unk0x004b0b28;
extern const LegoFloat g_unk0x004b0b2c;
extern const LegoFloat g_unk0x004b0b30;
extern const LegoFloat g_unk0x004b0b34;
extern const LegoFloat g_unk0x004b0b38;
extern const LegoFloat g_unk0x004b0b3c;
extern const LegoFloat g_unk0x004b0b40;
extern const LegoFloat g_unk0x004b0b44;
extern LegoU32 g_unk0x004bef68;
extern LegoU32 g_unk0x004bef6c;
extern LegoU32 g_unk0x004bef70;
extern LegoFloat g_unk0x004c6b34;
extern const LegoFloat g_violetShoalTwo;

// FUNCTION: LEGORACERS 0x0043d5a0
RaceState::Racer::CarVisuals::CarVisuals()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d620
RaceState::Racer::CarVisuals::~CarVisuals()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0043d6a0
void RaceState::Racer::CarVisuals::Reset()
{
	m_bodyModelEntity = NULL;
	m_unk0x040 = NULL;
	m_carEntity = NULL;
	m_driverEntity = NULL;
	m_racer = NULL;
	m_shadowDirection.m_x = 0.0f;
	m_shadowDirection.m_y = 0.0f;
	m_shadowDirection.m_z = -1.0f;
	m_trackCollidable = NULL;
	m_unk0x1dc = NULL;
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
void RaceState::Racer::CarVisuals::Initialize(InitParams* p_params, RaceState::Field0x3b190Params0x08* p_context)
{
	if (m_flags & c_alphaOverrideFlag) {
		Destroy();
	}

	m_bodyModelEntity = p_params->m_bodyModel;
	m_unk0x040 = p_params->m_unk0x04;
	m_carEntity = p_params->m_carEntity;
	m_driverEntity = p_params->m_driverEntity;
	m_driverMountOffset = p_params->m_driverMountOffset;
	m_trackCollidable = p_context->m_unk0x08;
	Racer* racer = p_params->m_racer;
	m_racer = racer;
	m_racerPhysics = &racer->m_unk0x3e8;
	m_particleAnimation = p_context->m_unk0x1c;
	m_sharedParticleAnimation = p_context->m_unk0x20;
	m_skidMarkManager = p_context->m_unk0x24;
	m_flags = c_alphaOverrideFlag | c_flagVisible;
	if (p_context->m_unk0x30) {
		m_flags = c_alphaOverrideFlag | c_flagVisible | c_flagShadowEnabled;
	}

	m_shadowWidth = p_params->m_shadowWidth;
	m_shadowLength = p_params->m_shadowLength;
	m_frontSkidWidth = p_params->m_frontSkidWidth;
	m_rearSkidWidth = p_params->m_rearSkidWidth;
	::strncpy(m_carMaterialName, p_params->m_materialName, sizeof(m_carMaterialName));

	m_carMaterialTable.Initialize(p_context->m_renderer, 1);
	m_carMaterialTable.AssignEntryByName(0, m_carMaterialName);
	m_skidMaterialTable.Initialize(p_context->m_renderer, 1);
	m_skidMaterialTable.AssignEntryByName(0, "skid");

	g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
	m_lookCooldownMs = g_randomTable[g_randomTableIndex] % 2000;

	for (LegoU32 i = 0; i < sizeOfArray(m_wheelOffsets); i++) {
		m_wheelOffsets[i] = p_params->m_wheelOffsets[i];
	}

	m_carEntity->FUN_0040dad0(0);
	m_carEntity->SetFlags(m_carEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (m_unk0x040) {
		m_unk0x040->FUN_0040dad0(0);
		m_unk0x040->SetFlags(m_unk0x040->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	}

	m_driverEntity->FUN_0040dad0(9);
	m_driverEntity->SetFlags(m_driverEntity->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);

	if (p_context->m_flags0x3c & 0x200) {
		m_flags |= c_flagVisible0;
	}
	if (p_context->m_flags0x3c & 0x400) {
		m_flags |= c_flagVisible1;
	}
	if (p_context->m_flags0x3c & 0x800) {
		m_flags |= c_flagVisible2;
	}

	RebuildEntityGroup();
}

// FUNCTION: LEGORACERS 0x0043d990
void RaceState::Racer::CarVisuals::InitializeVisuals(GolD3DRenderDevice* p_renderer, GolExport* p_golExport)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_modelDistances[i] = m_bodyModelEntity->GetModelDistance(i);
	}

	SnapVisuals();
	RenderImpostor(p_renderer);
	m_shadowDecal.FUN_00414950(p_golExport, p_renderer, 0x10);
	m_shadowDecal.GetUnk0x010().EnableFlagBit1();
}

// FUNCTION: LEGORACERS 0x0043d9f0
void RaceState::Racer::CarVisuals::RefreshCarMaterial()
{
	m_carMaterialTable.AssignEntryByName(0, m_carMaterialName);
}

// FUNCTION: LEGORACERS 0x0043da10
void RaceState::Racer::CarVisuals::UseTurboSkidMaterial()
{
	m_skidMaterialTable.AssignEntryByName(0, "trbskid");
}

// FUNCTION: LEGORACERS 0x0043da30
void RaceState::Racer::CarVisuals::UseNormalSkidMaterial()
{
	m_skidMaterialTable.AssignEntryByName(0, "skid");
}

// FUNCTION: LEGORACERS 0x0043da50
void RaceState::Racer::CarVisuals::Destroy()
{
	m_curseEntity.VTable0x54();
	m_shadowDecal.FUN_004149f0();
	m_skidMaterialTable.Clear();
	m_carMaterialTable.Clear();

	if (m_tireSmokeParticle) {
		m_particleAnimation->FUN_00489f00(m_tireSmokeParticle);
		m_tireSmokeParticle = NULL;
	}

	if (m_carSmokeParticle) {
		m_particleAnimation->FUN_00489f00(m_carSmokeParticle);
		m_carSmokeParticle = NULL;
	}

	if (m_dustParticle) {
		m_particleAnimation->FUN_00489f00(m_dustParticle);
		m_dustParticle = NULL;
	}

	for (LegoU32 i = 0; i < sizeOfArray(m_wheelParticles); i++) {
		CutsceneParticleRef* particleRef = m_wheelParticles[i];
		if (particleRef) {
			if (m_wheelParticleFromRace[i]) {
				m_particleAnimation->FUN_00489f00(particleRef);
			}
			else {
				m_sharedParticleAnimation->FUN_00489f00(particleRef);
			}

			m_wheelParticles[i] = NULL;
			m_wheelParticleNames[i][0] = 0;
		}
	}

	m_particleAnimation = NULL;
	m_shadowDecal.FUN_004149f0();
	m_skidMaterialTable.Clear();
	m_carMaterialTable.Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x0043db60
void RaceState::Racer::CarVisuals::ShowModels()
{
	m_flags |= c_flagVisible;

	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_bodyModelEntity->SetModelDistance(i, m_modelDistances[i]);
		m_carEntity->SetModelDistance(i, m_modelDistances[i]);
		m_driverEntity->SetModelDistance(i, m_modelDistances[i]);

		if (m_unk0x040) {
			m_unk0x040->SetModelDistance(i, m_modelDistances[i]);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dbb0
void RaceState::Racer::CarVisuals::HideModels()
{
	m_flags &= ~c_flagVisible;

	for (LegoU32 i = 0; i < sizeOfArray(m_modelDistances); i++) {
		m_bodyModelEntity->SetModelDistance(i, g_unk0x004b0ac0);
		m_carEntity->SetModelDistance(i, g_unk0x004b0ac0);
		m_driverEntity->SetModelDistance(i, g_unk0x004b0ac0);

		if (m_unk0x040) {
			m_unk0x040->SetModelDistance(i, g_unk0x004b0ac0);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043dc00
void RaceState::Racer::CarVisuals::StartSkidEffects()
{
	if (!(m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3)) {
		for (LegoU32 i = 0; i < sizeOfArray(m_wheelSkidFlags); i++) {
			if ((m_unk0x1dc->m_flags0x6c0 & PhysicsView::c_flagAllWheelSlide) || i >= 2) {
				m_wheelSkidFlags[i] = TRUE;
			}
			else {
				m_wheelSkidFlags[i] &= ~(c_wheelSkidActive | c_wheelSkidGrounded);
			}
		}

		if (!m_tireSmokeParticle) {
			m_tireSmokeParticle = m_particleAnimation->FUN_00489d70("tiresmk", NULL, NULL, NULL);

			if (m_tireSmokeParticle) {
				GolVec3 position = m_unk0x1dc->m_wheels[3].m_contactPosition;
				GolAnimatedEntity* entity = m_carEntity;
				if (m_tireSmokeParticle->m_particle) {
					entity->VTable0x44(m_tireSmokeParticle->m_particle->GetUnk0x160());
				}

				if (m_tireSmokeParticle->m_particle) {
					m_tireSmokeParticle->m_particle->FUN_00489660(&position);
				}
			}
		}

		m_flags |= c_flagSkidding;
	}
}

// FUNCTION: LEGORACERS 0x0043dcd0
void RaceState::Racer::CarVisuals::StopSkidEffects()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_skidMarks); i++) {
		if (m_skidMarks[i]) {
			m_skidMarkManager->FUN_00492820(m_skidMarks[i], 1000);
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
		m_particleAnimation->FUN_00489f30(m_tireSmokeParticle);
		m_tireSmokeParticle = NULL;
	}

	m_flags &= ~c_flagSkidding;
}

// FUNCTION: LEGORACERS 0x0043dd50
void RaceState::Racer::CarVisuals::SetWheelParticle(LegoU32 p_unk0x04, const LegoChar* p_unk0x08)
{
	if (m_wheelParticles[p_unk0x04]) {
		if (::strncmp(m_wheelParticleNames[p_unk0x04], p_unk0x08, sizeof(GolName)) == 0) {
			return;
		}

		m_particleAnimation->FUN_00489f00(m_wheelParticles[p_unk0x04]);
		m_wheelParticles[p_unk0x04] = NULL;
	}

	::memcpy(m_wheelParticleNames[p_unk0x04], p_unk0x08, sizeof(GolName));
	if (m_particleAnimation->FUN_00489d50(p_unk0x08)) {
		m_wheelParticles[p_unk0x04] = m_particleAnimation->FUN_00489d70(p_unk0x08, NULL, NULL, NULL);
		m_wheelParticleFromRace[p_unk0x04] = TRUE;
	}
	else if (m_sharedParticleAnimation->FUN_00489d50(p_unk0x08)) {
		m_wheelParticles[p_unk0x04] = m_sharedParticleAnimation->FUN_00489d70(p_unk0x08, NULL, NULL, NULL);
		m_wheelParticleFromRace[p_unk0x04] = FALSE;
	}

	CutsceneParticleRef* ref = m_wheelParticles[p_unk0x04];
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_wheels[p_unk0x04].m_contactPosition;
	CutsceneParticle* particle = ref->m_particle;
	GolWorldEntity* entity = m_carEntity;

	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_wheelParticles[p_unk0x04]->m_particle) {
		m_wheelParticles[p_unk0x04]->m_particle->FUN_00489660(&position);
	}
}

// FUNCTION: LEGORACERS 0x0043de90
void RaceState::Racer::CarVisuals::ClearWheelParticle(LegoU32 p_unk0x04)
{
	if (m_wheelParticles[p_unk0x04]) {
		m_wheelParticleNames[p_unk0x04][0] = 0;
		if (m_wheelParticleFromRace[p_unk0x04]) {
			m_particleAnimation->FUN_00489f00(m_wheelParticles[p_unk0x04]);
		}
		else {
			m_sharedParticleAnimation->FUN_00489f00(m_wheelParticles[p_unk0x04]);
		}
		m_wheelParticles[p_unk0x04] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0043def0
void RaceState::Racer::CarVisuals::StartDust()
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

	ref = m_particleAnimation->FUN_00489d70("dust", NULL, NULL, NULL);
	m_dustParticle = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_wheels[3].m_contactPosition;
	CutsceneParticle* particle = ref->m_particle;
	GolWorldEntity* entity = m_carEntity;

	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_dustParticle->m_particle) {
		m_dustParticle->m_particle->FUN_00489660(&position);
	}
}

// FUNCTION: LEGORACERS 0x0043df90
void RaceState::Racer::CarVisuals::StartCarSmoke()
{
	CutsceneParticleRef* ref = m_carSmokeParticle;
	if (ref) {
		return;
	}

	ref = m_particleAnimation->FUN_00489d70("carsmke", NULL, NULL, NULL);
	m_carSmokeParticle = ref;
	if (!ref) {
		return;
	}

	GolVec3 position = m_unk0x1dc->m_wheels[3].m_contactPosition;
	GolVec3 other = m_unk0x1dc->m_wheels[2].m_contactPosition;
	GolWorldEntity* entity = m_carEntity;

	position.m_x = (position.m_x + other.m_x) * 0.5f;
	position.m_y = (position.m_y + other.m_y) * 0.5f;
	position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

	CutsceneParticle* particle = ref->m_particle;
	if (particle) {
		entity->VTable0x44(particle->GetUnk0x160());
	}

	if (m_carSmokeParticle->m_particle) {
		m_carSmokeParticle->m_particle->FUN_00489660(&position);
	}
}

// STUB: LEGORACERS 0x0043e070
void RaceState::Racer::CarVisuals::Update(LegoU32 p_elapsedMs)
{
	UpdateBodyLean(p_elapsedMs);
	UpdateDriver(p_elapsedMs);
	m_entityGroup.VTable0x00();

	if (m_isFlashing) {
		if (p_elapsedMs >= m_flashTimerMs) {
			EndFlash();
		}
		else {
			m_flashTimerMs -= p_elapsedMs;
		}
	}

	if (!(m_racer->m_unk0xd04 & c_racerFlags0xd04Bit4)) {
		if (m_unk0x1dc->m_flags0x6c0 & PhysicsView::c_flagAllWheelSlide) {
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

		if ((m_racer->m_unk0xd04 & c_racerFlags0xd04Bit3) && (m_flags & c_flagSkidding)) {
			StopSkidEffects();
		}

		UpdateSkidMarks(p_elapsedMs);

		if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit11) {
			UpdateCurseEntity(p_elapsedMs);
		}
		else {
			m_curseBlendMs = 1000;
		}

		GolVec3 velocity = m_unk0x1dc->m_velocity * 0.5f;

		for (LegoU32 particleIndex = 0; particleIndex < sizeOfArray(m_wheelParticles); particleIndex++) {
			CutsceneParticleRef* ref = m_wheelParticles[particleIndex];
			if (ref) {
				GolVec3 position = m_unk0x1dc->m_wheels[particleIndex].m_contactPosition;
				CutsceneParticle* particle = ref->m_particle;

				if (particle) {
					m_carEntity->VTable0x44(particle->GetUnk0x160());
				}

				if (ref->m_particle) {
					ref->m_particle->FUN_00489660(&position);
				}

				if (ref->m_particle) {
					ref->m_particle->FUN_00489690(&velocity);
				}
			}
		}

		if (m_racer->m_unk0x3e8.m_unk0x6dc > 400) {
			m_flags |= c_flagAirborne;
		}

		if (m_flags & c_flagAirborne) {
			LegoU32 state = m_racer->m_unk0x3e8.m_unk0x36c;
			if (m_lastGroundedWheelCount < state) {
				m_flags &= ~c_flagAirborne;

				SoundVector position;
				m_carEntity->VTable0x04(&position);

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

				m_particleAnimation->FUN_00489d70("carland", &position, NULL, NULL);
			}

			m_lastGroundedWheelCount = state;
		}

		if (m_dustParticle) {
			CutsceneParticle* particle = m_dustParticle->m_particle;
			if (particle && particle->GetSpawnedCount() >= 10) {
				m_particleAnimation->FUN_00489f30(m_dustParticle);
				m_dustParticle = NULL;
			}
			else {
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				GolVec3 position = (g_randomTable[g_randomTableIndex] & 2) ? m_unk0x1dc->m_wheels[3].m_contactPosition
																		   : m_unk0x1dc->m_wheels[2].m_contactPosition;

				particle = m_dustParticle->m_particle;
				if (particle) {
					m_carEntity->VTable0x44(particle->GetUnk0x160());
				}

				if (m_dustParticle->m_particle) {
					m_dustParticle->m_particle->FUN_00489660(&position);
				}

				if (m_dustParticle->m_particle) {
					m_dustParticle->m_particle->FUN_00489690(&velocity);
				}
			}
		}

		if (m_carSmokeParticle) {
			CutsceneParticle* particle = m_carSmokeParticle->m_particle;
			if (particle && particle->GetSpawnedCount() >= 4) {
				m_particleAnimation->FUN_00489f30(m_carSmokeParticle);
				m_carSmokeParticle = NULL;
			}
			else {
				GolVec3 position = m_unk0x1dc->m_wheels[3].m_contactPosition;
				GolVec3 other = m_unk0x1dc->m_wheels[2].m_contactPosition;
				position.m_x = (position.m_x + other.m_x) * 0.5f;
				position.m_y = (position.m_y + other.m_y) * 0.5f;
				position.m_z = (position.m_z + other.m_z) * 0.5f + g_violetShoalTwo;

				particle = m_carSmokeParticle->m_particle;
				if (particle) {
					m_carEntity->VTable0x44(particle->GetUnk0x160());
				}

				if (m_carSmokeParticle->m_particle) {
					m_carSmokeParticle->m_particle->FUN_00489660(&position);
				}

				if (m_carSmokeParticle->m_particle) {
					m_carSmokeParticle->m_particle->FUN_00489690(&velocity);
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
						position = m_unk0x1dc->m_wheels[tireIndex].m_contactPosition;
						found = TRUE;
					}
					else {
						break;
					}
				}
			}

			CutsceneParticle* particle = m_tireSmokeParticle->m_particle;
			if (particle) {
				m_carEntity->VTable0x44(particle->GetUnk0x160());
			}

			if (m_tireSmokeParticle->m_particle) {
				m_tireSmokeParticle->m_particle->FUN_00489660(&position);
			}

			if (m_tireSmokeParticle->m_particle) {
				m_tireSmokeParticle->m_particle->FUN_00489690(&velocity);
			}
		}
	}

	m_flags &= ~c_flagShadowVisible;
}

// FUNCTION: LEGORACERS 0x0043e620
void RaceState::Racer::CarVisuals::SnapVisuals()
{
	m_carEntity->CopyOrientationAndPositionTo(m_bodyModelEntity);

	GolVec3 position;
	m_bodyModelEntity->VTable0x2c(m_driverMountOffset, &position);
	m_driverEntity->VTable0x08(position);
	m_driverEntity->CopyOrientationFrom(*m_bodyModelEntity);

	if (m_unk0x040 != NULL) {
		m_carEntity->CopyOrientationAndPositionTo(m_unk0x040);
	}
}

// FUNCTION: LEGORACERS 0x0043e740
void RaceState::Racer::CarVisuals::UpdateBodyLean(LegoS32 p_elapsedMs)
{
	GolVec3 position;
	m_carEntity->VTable0x04(&position);

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
	m_carEntity->VTable0x10(p_elapsedMs);

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
	LegoFloat scale = g_unk0x004b0b28;
	scale = -scale;
	m_pitchLean += (scale * length) * elapsed / m_racerPhysics->m_unk0x0c8;
	LegoFloat decay = elapsed;
	decay *= g_unk0x004b0b30;
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

	scale = g_unk0x004b0b2c;
	scale = -scale;
	m_rollLean += (scale * length) * elapsed / m_racerPhysics->m_unk0x0c8;
	decay = elapsed;
	decay *= g_unk0x004b0b34;
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
		GolCameraBase::FUN_00404550(&targetRow0, &oldRow0, &row0);
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
		GolCameraBase::FUN_00404550(&targetRow1, &oldRow1, &row1);
	}

	m_bodyModelEntity->VTable0x08(position);
	m_bodyModelEntity->FUN_00410a00(row0, row1);

	if (m_unk0x040 != NULL) {
		m_bodyModelEntity->CopyOrientationAndPositionTo(m_unk0x040);
		m_unk0x040->VTable0x10(p_elapsedMs);
	}

	m_bodyModelEntity->VTable0x2c(m_driverMountOffset, &position);
	m_driverEntity->VTable0x08(position);
	m_driverEntity->FUN_0043ebd0(*m_bodyModelEntity);
}

// FUNCTION: LEGORACERS 0x0043ebd0
void GolOrientedEntity::FUN_0043ebd0(const GolOrientedEntity& p_other)
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
void RaceState::Racer::CarVisuals::UpdateDriver(LegoU32 p_elapsedMs)
{
	DriveController* field0xc70 = &m_racer->m_unk0xc70;
	LegoFloat activeValue = field0xc70->m_unk0x00c;
	LegoFloat speed = m_unk0x1dc->m_forwardSpeed;
	LegoU32 activePart = m_driverEntity->GetActiveState();
	LegoU32 eventFlags = m_reactionFlags;

	m_driverEntity->VTable0x10(p_elapsedMs);
	m_reactionFlags = 0;

	if (p_elapsedMs < m_lookCooldownMs) {
		m_lookCooldownMs -= p_elapsedMs;
	}
	else {
		m_lookCooldownMs = 0;
	}

	if (m_racer->m_lapsCompleted >= g_unk0x004bef70) {
		if (m_racer->m_lapTimes[5] == 1) {
			if (activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart14) {
				return;
			}

			g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
			if (g_randomTable[g_randomTableIndex] % 2 != 0) {
				m_driverEntity->FUN_0040dad0(c_animationPart14);
				m_driverEntity->QueuePartTransition(c_animationPart15);
			}
			else {
				m_driverEntity->FUN_0040dad0(c_animationPart13);
			}
			return;
		}

		if (activePart == c_animationPart12 || activePart == c_animationPart11) {
			return;
		}

		m_driverEntity->FUN_0040dad0(c_animationPart11);
		m_driverEntity->QueuePartTransition(c_animationPart12);
		return;
	}

	if (m_lastSpeed > g_unk0x004b0544 && speed < g_carBuildPreviewMouseScale && activePart != c_animationPart0) {
		m_racer->PlayReaction(FALSE);
		m_driverEntity->FUN_0040dad0(c_animationPart0);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		m_lastSpeed = 0.0f;

		if (m_racer->m_unk0x014 != NULL) {
			m_racer->m_unk0x014->FUN_004220c0();
		}
		return;
	}

	m_lastSpeed = speed;

	if (eventFlags & c_flags0x384Bit0) {
		m_driverEntity->FUN_0040dad0(c_animationPart1);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		return;
	}

	if (eventFlags & c_flags0x384Bit1) {
		m_driverEntity->FUN_0040dad0(c_animationPart10);
		m_driverEntity->QueuePartTransition(c_animationPart9);

		if (m_racer->m_unk0x014 != NULL) {
			m_racer->m_unk0x014->FUN_004220c0();
		}
		return;
	}

	if (activePart == c_animationPart0 || activePart == c_animationPart1 || activePart == c_animationPart10 ||
		activePart == c_animationPart13 || activePart == c_animationPart15 || activePart == c_animationPart12) {
		return;
	}

	if (field0xc70->m_unk0x010 < 0.0f && speed < 0.0f) {
		if (activePart == c_animationPart2 || activePart == c_animationPart3) {
			return;
		}

		m_driverEntity->FUN_0040dad0(c_animationPart2);
		m_driverEntity->QueuePartTransition(c_animationPart3);
		return;
	}

	if (activePart == c_animationPart3) {
		m_driverEntity->FUN_0040dad0(c_animationPart4);
		m_driverEntity->QueuePartTransition(c_animationPart9);
		return;
	}

	if (activePart == c_animationPart7 || activePart == c_animationPart16 || activePart == c_animationPart8 ||
		activePart == c_animationPart17) {
		return;
	}

	if (m_lookCooldownMs == 0) {
		GolVec3 position;
		m_carEntity->VTable0x04(&position);

		Racer* racer = m_racer;
		RaceState* raceState = racer->m_raceState;
		Racer* nearbyRacer = raceState->FindNearestRacerInRange(&position, 2.0f, g_unk0x004b0b24);
		m_nearbyRacer = nearbyRacer;

		if (nearbyRacer != NULL) {
			GolAnimatedEntity* nearbyEntity = nearbyRacer->m_unk0x018.m_carEntity;
			GolVec3 row0 = m_carEntity->GetOrientation().m_rows[0];
			GolVec3 row1 = m_carEntity->GetOrientation().m_rows[1];

			GolVec3 nearbyPosition;
			nearbyEntity->VTable0x04(&nearbyPosition);

			GolVec3 direction;
			direction.m_x = nearbyPosition.m_x - position.m_x;
			direction.m_y = nearbyPosition.m_y - position.m_y;
			direction.m_z = nearbyPosition.m_z - position.m_z;
			GolMath::NormalizeVector3(direction, &direction);

			LegoFloat forwardDot = row0.m_z * direction.m_z + row0.m_y * direction.m_y + row0.m_x * direction.m_x;
			LegoU32 animationPart = 0;
			if (forwardDot < g_unk0x004b02e0 && forwardDot > g_unk0x004b0b44) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart7 : c_animationPart16;
			}
			else if (forwardDot < g_unk0x004b02e0 && forwardDot > g_unk0x004b0b40) {
				LegoFloat sideDot = row1.m_z * direction.m_z + row1.m_y * direction.m_y + row1.m_x * direction.m_x;
				animationPart = sideDot < 0.0f ? c_animationPart8 : c_animationPart17;
			}

			if (animationPart) {
				g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
				m_lookCooldownMs =
					(g_randomTable[g_randomTableIndex] % c_avoidanceCooldownRangeMs) + c_avoidanceCooldownBaseMs;
				m_driverEntity->FUN_0040dad0(animationPart);
				m_driverEntity->QueuePartTransition(c_animationPart9);
				return;
			}
		}
	}

	if (activeValue < 0.0f) {
		if (activePart != c_animationPart5) {
			m_driverEntity->FUN_0040db80(c_animationPart5, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue > 0.0f) {
		if (activePart != c_animationPart6) {
			m_driverEntity->FUN_0040db80(c_animationPart6, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
		}
		return;
	}

	if (activeValue == 0.0f && activePart != c_animationPart9) {
		m_driverEntity->FUN_0040db80(c_animationPart9, c_animationTransitionMs, 0.0f, TRUE, TRUE, TRUE);
	}
}

// FUNCTION: LEGORACERS 0x0043f1e0
void RaceState::Racer::CarVisuals::UpdateSkidMarks(LegoU32 p_elapsedMs)
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
					(m_unk0x1dc->m_wheels[i].m_flags0x03c & PhysicsView::WheelContact::c_flagOnGround)) {
					flags |= c_wheelSkidGrounded;
					m_wheelSkidFlags[i] = flags;
				}
				else if (m_unk0x1dc->m_wheels[i].m_flags0x03c & PhysicsView::WheelContact::c_flagOnGround) {
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
				m_carEntity->VTable0x2c(m_wheelOffsets[i], &position);
				m_skidMarks[i]->FUN_00491fa0(p_elapsedMs, position);
			}
		}
	}

	if (m_unk0x1dc->m_flags0x6c0 & PhysicsView::c_flagAllWheelSlide) {
		m_wheelSkidFlags[0] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[1] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[2] |= c_wheelSkidAllButActive;
		m_wheelSkidFlags[3] |= c_wheelSkidAllButActive;
	}
	else if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit6) {
		m_wheelSkidFlags[0] &= ~c_wheelSkidActive;
		m_wheelSkidFlags[2] |= c_wheelSkidActive;
		m_wheelSkidFlags[1] &= ~c_wheelSkidActive;
		m_wheelSkidFlags[3] |= c_wheelSkidActive;
	}
	else {
		GolVec3 slipDirection = m_unk0x1dc->m_slipDirection;
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
		RaceSessionField0x27d4::Item** itemSlot = m_skidMarks;
		LegoU32 i = 0;
		LegoU8 colorByte = 0xff;
		do {
			LegoU32 flags0x000Bit8 = m_flags & c_flagSliding;
			if (flags0x000Bit8) {
				RaceSessionField0x27d4::Item* item = *itemSlot;
				if (item && item->GetUnk0x314() == 1000) {
					m_skidMarkManager->FUN_00492820(item, 0);
					*itemSlot = NULL;
				}
			}
			else {
				RaceSessionField0x27d4::Item* item = *itemSlot;
				if (item && item->GetUnk0x314() == 250) {
					m_skidMarkManager->FUN_00492820(item, 0);
					*itemSlot = NULL;
				}
			}

			if (m_wheelSkidFlags[i] & c_wheelSkidActive) {
				if (!*itemSlot) {
					if (m_flags & c_flagSliding) {
						*itemSlot = m_skidMarkManager->FUN_004927c0(250);
					}
					else {
						*itemSlot = m_skidMarkManager->FUN_004927c0(1000);
					}

					if (*itemSlot) {
						ColorRGBA color;
						color.m_red = colorByte;
						color.m_grn = colorByte;
						color.m_blu = colorByte;
						color.m_alp = colorByte;
						(*itemSlot)->FUN_00491d80(&color);
						(*itemSlot)->FUN_00491d20(&m_skidMaterialTable);

						if (i == 0 || i == 1) {
							(*itemSlot)->SetUnk0x324(m_frontSkidWidth);
						}
						else {
							(*itemSlot)->SetUnk0x324(m_rearSkidWidth);
						}
					}
				}
			}
			else if (*itemSlot) {
				m_skidMarkManager->FUN_00492820(*itemSlot, 0);
				*itemSlot = NULL;
			}
			i++;
			itemSlot++;
		} while (i < sizeOfArray(m_skidMarks));
	}
}

// STUB: LEGORACERS 0x0043f530
void RaceState::Racer::CarVisuals::UpdateCurseEntity(LegoU32 p_elapsedMs)
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

	LegoFloat phase = static_cast<LegoFloat>(m_cursePhaseMs) * g_unk0x004c6b34;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase * g_negativeRadiansToTableIndex)) & c_randomTableMask;
	LegoFloat offsetX = g_cosineTable[tableIndex];
	tableIndex = static_cast<LegoS32>(phase * g_item0x40RadiansToTableIndex) & c_randomTableMask;
	LegoFloat offsetY = g_cosineTable[tableIndex];

	GolModelEntity* entity = &m_curseEntity;
	GolVec3 position;
	entity->VTable0x04(&position);

	GolVec3 target;
	m_bodyModelEntity->VTable0x04(&target);
	target.m_x += 6.0f * offsetX;
	target.m_y += 6.0f * offsetY;
	target.m_z += 9.0f;

	LegoFloat speed = m_unk0x1dc->m_speed;
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
	entity->VTable0x08(position);

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	m_bodyModelEntity->VTable0x04(&target);
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
		entity->VTable0x44(&currentOrientation);
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
		GolMath::FUN_1002f5a0(desiredOrientation, &desiredRotation);
		GolMath::FUN_1002f5a0(currentOrientation, &currentRotation);
		GolMath::FUN_1002f890(desiredRotation, currentRotation, amount, &blendedRotation);

		GolMatrix3 orientation;
		GolMath::FUN_00449340(&blendedRotation, &orientation.m_m[0][0]);
		entity->VTable0x3c(orientation);
	}
	else {
		entity->VTable0x40(right, up);
	}

	LegoFloat scale = entity->GetUnk0x58();
	if (scale > 0.66600001f) {
		scale -= elapsed * 0.0099999998f * 0.065999999f;
		if (scale < 0.66600001f) {
			scale = 0.66600001f;
		}
		entity->SetUnk0x58ThenInvalidateRadius(scale);
	}

	entity->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0043fa50
void RaceState::Racer::CarVisuals::UpdateShadow(GolCamera* p_camera)
{
	LegoU32 flags = m_flags;
	if ((flags & c_flagShadowVisible) || !(flags & c_flagShadowEnabled)) {
		return;
	}

	GolVec3 entityPosition;
	m_carEntity->VTable0x04(&entityPosition);

	GolVec3 cameraPosition;
	p_camera->GetTransform()->GetPosition(&cameraPosition);

	LegoFloat deltaX = entityPosition.m_x - cameraPosition.m_x;
	LegoFloat deltaY = entityPosition.m_y - cameraPosition.m_y;
	LegoFloat deltaZ = entityPosition.m_z - cameraPosition.m_z;
	LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;
	if (distanceSquared < m_carEntity->GetModelDistance(0)) {
		m_flags |= c_flagShadowVisible;

		GolVec3 up;
		m_carEntity->GetUnk0x34(&up);

		GolVec3 center;
		m_carEntity->FUN_100286d0(&center);

		LegoFloat scale = m_carEntity->GetUnk0x58();
		if (scale != 1.0f) {
			m_shadowDecal.m_unk0x104 = m_shadowWidth * scale;
			m_shadowDecal.m_unk0x108 = scale * m_shadowLength;
		}
		else {
			m_shadowDecal.m_unk0x104 = m_shadowWidth * 1.0f;
			m_shadowDecal.m_unk0x108 = m_shadowLength * 1.0f;
		}

		m_shadowDecal.m_unk0x10c = g_unk0x004b0af0;
		center.m_z += g_unk0x004b0af4;

		RaceSessionField0x27d4::Item::Decal* field = &m_shadowDecal;
		field->m_unk0x0e8.m_x = center.m_x;
		field->m_unk0x0e8.m_y = center.m_y;
		field->m_unk0x0e8.m_z = center.m_z;

		up.m_x = -up.m_x;
		up.m_y = -up.m_y;
		MaterialTable0x0c* materialTable = &m_carMaterialTable;
		GolVec3* upVector = &up;
		GolVec3* vector = &m_shadowDirection;
		m_shadowDecal.GetUnk0x010().SetPrimaryMaterialTable(materialTable);
		up.m_z = -up.m_z;
		field->FUN_00414c90(vector, upVector);
		field->FUN_00414a30(m_trackCollidable);
	}
}

// FUNCTION: LEGORACERS 0x0043fbc0
void RaceState::Racer::CarVisuals::Draw(GolD3DRenderDevice* p_renderer)
{
	if (!(m_flags & c_flagVisible0)) {
		p_renderer->VTable0x94(m_carEntity);
	}

	if (!(m_flags & c_flagVisible1)) {
		p_renderer->VTable0x94(m_bodyModelEntity);

		if (m_unk0x040) {
			p_renderer->VTable0x94(m_unk0x040);
		}
	}

	if (!(m_flags & c_flagVisible2)) {
		p_renderer->VTable0x94(m_driverEntity);
	}
}

// FUNCTION: LEGORACERS 0x0043fc20
void RaceState::Racer::CarVisuals::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & c_flagShadowVisible) {
		RaceSessionField0x27d4::Item::Decal* field = &m_shadowDecal;
		GolVec3 cameraPosition;
		p_renderer->GetUnk0x0c()->GetTransform()->GetPosition(&cameraPosition);

		GolVec3 position;
		LegoFloat deltaX = field->m_unk0x0e8.m_x;
		position.m_y = field->m_unk0x0e8.m_y;
		position.m_z = field->m_unk0x0e8.m_z;

		deltaX = cameraPosition.m_x - deltaX;
		LegoFloat deltaY = cameraPosition.m_y - position.m_y;
		LegoFloat deltaZ = cameraPosition.m_z - position.m_z;
		LegoFloat distanceSquared = deltaZ * deltaZ + deltaY * deltaY + deltaX * deltaX;

		LegoS32 alpha;
		if (distanceSquared <= g_unk0x004b0b38) {
			alpha = c_fadeAlphaMax;
		}
		else if (distanceSquared < g_unk0x004b0b3c) {
			alpha = c_fadeAlphaMax -
					static_cast<LegoS32>(
						((distanceSquared - g_unk0x004b0b38) / (g_unk0x004b0b3c - g_unk0x004b0b38)) * g_fadeAlphaScale
					);
		}
		else {
			alpha = 0;
		}

		if (alpha) {
			p_renderer->SetAlphaOverride(alpha, c_alphaOverrideFlag);
			field->FUN_00415a40(p_renderer);
			p_renderer->ClearAlphaOverride();
		}
	}

	if (m_racer->m_unk0xd04 & c_racerFlags0xd04Bit11) {
		p_renderer->VTable0x94(&m_curseEntity);
	}
}

// FUNCTION: LEGORACERS 0x0043fd30
void RaceState::Racer::CarVisuals::StartTurboEffects()
{
	if (m_racer->m_unk0xd08 != 2) {
		StartDust();
		StartCarSmoke();

		if (m_racer->m_unk0xd68 > 0) {
			UseTurboSkidMaterial();
			StartSkidEffects();
		}
	}
}

// FUNCTION: LEGORACERS 0x0043fd70
void RaceState::Racer::CarVisuals::StopTurboEffects()
{
	StopSkidEffects();
	UseNormalSkidMaterial();
}

// FUNCTION: LEGORACERS 0x0043fd90
void RaceState::Racer::CarVisuals::StartSlideSkid()
{
	m_flags |= c_flagSliding;

	if (m_racer->m_unk0xd08 != 2) {
		StartSkidEffects();
	}
}

// FUNCTION: LEGORACERS 0x0043fdb0
void RaceState::Racer::CarVisuals::StopSlideSkid()
{
	m_flags &= ~c_flagSliding;
	StopSkidEffects();
}

// FUNCTION: LEGORACERS 0x0043fdc0
LegoBool32 RaceState::Racer::CarVisuals::IntersectSegment(const GolVec3* p_start, const GolVec3* p_end, GolVec3* p_hit)
{
	GolVec3 center;
	LegoFloat radius;
	m_bodyModelEntity->FUN_10027fe0(0, &center, &radius);
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
void RaceState::Racer::CarVisuals::RenderImpostor(GolD3DRenderDevice* p_renderer)
{
	DuskwindBananaRelic0x24* material = p_renderer->FindMaterialByName(m_carMaterialName);
	g_racerBillboardRenderState0x33c.FUN_004097c0(p_renderer, material->GetUnk0x04());

	GolVec3 position;
	m_carEntity->VTable0x04(&position);
	LegoFloat origin[2];
	origin[0] = position.m_x;
	origin[1] = position.m_y;

	ColorRGBA color = {0, 0, 0, 0};
	g_racerBillboardRenderState0x33c.FUN_00409850(&color);

	color.m_red = 8;
	color.m_grn = 8;
	color.m_blu = 8;
	color.m_alp = 0xff;
	g_racerBillboardRenderState0x33c.FUN_004098a0(&color);

	LegoFloat unk0x0c = m_shadowWidth;
	unk0x0c *= g_racerBillboardScale;
	LegoFloat unk0x08 = m_shadowLength;
	unk0x08 *= g_racerBillboardScale;
	g_racerBillboardRenderState0x33c.FUN_004098f0(origin, unk0x08, unk0x0c, g_unk0x004bef68 | g_unk0x004bef6c);
	g_racerBillboardRenderState0x33c.FUN_00409970(m_carEntity, 0);
	g_racerBillboardRenderState0x33c.FUN_00409970(m_bodyModelEntity, 0);

	if (m_unk0x040) {
		g_racerBillboardRenderState0x33c.FUN_00409970(m_unk0x040, 0);
	}

	g_racerBillboardRenderState0x33c.FUN_004099d0();
}

// FUNCTION: LEGORACERS 0x00440030
void RaceState::Racer::CarVisuals::RebuildEntityGroup()
{
	m_entityGroup.FUN_00411e30(4);

	if (m_bodyModelEntity && !(m_flags & c_flagVisible1)) {
		m_entityGroup.FUN_00411ec0(m_bodyModelEntity);
	}

	if (m_unk0x040 && !(m_flags & c_flagVisible1)) {
		m_entityGroup.FUN_00411ec0(m_unk0x040);
	}

	if (m_carEntity && !(m_flags & c_flagVisible0)) {
		m_entityGroup.FUN_00411ec0(m_carEntity);
	}

	if (m_driverEntity && !(m_flags & c_flagVisible2)) {
		m_entityGroup.FUN_00411ec0(m_driverEntity);
	}
}

// FUNCTION: LEGORACERS 0x004400a0
void RaceState::Racer::CarVisuals::SetColorTransform(ColorTransform0x20* p_unk0x04)
{
	m_baseColorTransform = *p_unk0x04;

	LegoU32 unk0x3c4 = m_isFlashing;
	m_hasColorTransform = 1;

	if (!unk0x3c4) {
		m_entityGroup.VTable0x24(&m_baseColorTransform);
	}
}

// FUNCTION: LEGORACERS 0x004400e0
void RaceState::Racer::CarVisuals::ClearColorTransform()
{
	LegoU32 unk0x3c4 = m_isFlashing;
	m_hasColorTransform = 0;

	if (!unk0x3c4) {
		m_entityGroup.VTable0x28();
	}
}

// FUNCTION: LEGORACERS 0x00440100
void RaceState::Racer::CarVisuals::FlashColor(ColorTransform0x20* p_unk0x04, undefined4 p_unk0x08)
{
	m_isFlashing = 1;
	m_flashTimerMs = p_unk0x08;
	m_entityGroup.VTable0x24(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00440130
void RaceState::Racer::CarVisuals::EndFlash()
{
	LegoU32 unk0x3c0 = m_hasColorTransform;
	m_isFlashing = 0;
	m_flashTimerMs = 0;

	if (unk0x3c0) {
		m_entityGroup.VTable0x24(&m_baseColorTransform);
	}
	else {
		m_entityGroup.VTable0x28();
	}
}

// FUNCTION: LEGORACERS 0x00440160
void RaceState::Racer::CarVisuals::SetScale(LegoFloat p_unk0x04)
{
	m_carEntity->SetUnk0x58AndInvalidateRadius(p_unk0x04);
	m_bodyModelEntity->SetUnk0x58AndInvalidateRadius(p_unk0x04);

	if (m_unk0x040) {
		m_unk0x040->SetUnk0x58AndInvalidateRadius(p_unk0x04);
	}

	m_driverEntity->SetUnk0x58AndInvalidateRadius(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x004401a0
void RaceState::Racer::CarVisuals::ResetDriverAnimation()
{
	m_driverEntity->FUN_0040dad0(9);
}

// FUNCTION: LEGORACERS 0x004401b0
void RaceState::Racer::CarVisuals::PlayForwardAnimation()
{
	if (m_carEntity->GetActiveState()) {
		m_carEntity->FUN_0040dad0(0);
	}
}

// FUNCTION: LEGORACERS 0x004401e0
void RaceState::Racer::CarVisuals::PlayReverseAnimation()
{
	CmbModelPart0x34* modelPart = m_carEntity->GetModelPart();

	if (modelPart->GetPartCount() > 1 && m_carEntity->GetActiveState() != 1) {
		m_carEntity->FUN_0040dad0(1);
	}
}
