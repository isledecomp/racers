#include "race/powerups/lightningaction.h"

#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "camera/golcamera.h"
#include "decomp.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/powerups/racepowerupmanager.h"
#include "race/racesoundsource.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "world/golworlddatabase.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_lightningRange;

// GLOBAL: LEGORACERS 0x004c7600
LegoFloat g_lightningReach = g_lightningRange * 4.0f;

extern const LegoFloat g_carBuildModelTextureCoordinateScale;

// GLOBAL: LEGORACERS 0x004b02fc
extern const LegoFloat g_unk0x004b02fc = 0.002f;

// GLOBAL: LEGORACERS 0x004b1544
const LegoFloat g_lightningSourceHeightOffset = 3.0f;

// GLOBAL: LEGORACERS 0x004b1548
const LegoFloat g_lightningSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b154c
const LegoFloat g_lightningSoundMaxDistanceSquared = 300.0f;

// GLOBAL: LEGORACERS 0x004b1550
const LegoFloat g_lightningFlashDrawDistance = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b1558
const LegoFloat g_lightningBeamThickness = 0.85f;

// GLOBAL: LEGORACERS 0x004b155c
const LegoFloat g_lightningBoltAmplitude = 9.0f;

// GLOBAL: LEGORACERS 0x004b1568
const ColorRGBA g_lightningBaseColor = {0x19, 0x41, 0xf5, 0xff};

// GLOBAL: LEGORACERS 0x004b156c
const ColorRGBA g_lightningSecondaryColor = {0x19, 0x41, 0xff, 0xff};

// GLOBAL: LEGORACERS 0x004b1570
const ColorRGBA g_lightningTertiaryColor = {0x19, 0x41, 0xeb, 0xff};

// GLOBAL: LEGORACERS 0x004b1574
const ColorRGBA g_lightningHitColor = {0xff, 0xff, 0xff, 0xff};

// GLOBAL: LEGORACERS 0x004b1578
extern const LegoFloat g_lightningRange = 50.0f;

// GLOBAL: LEGORACERS 0x004b157c
const LegoFloat g_lightningChainMinDistanceSquared = 9.0f;

// GLOBAL: LEGORACERS 0x004b1580
const LegoFloat g_lightningChainConeCosine = 0.5f;

// GLOBAL: LEGORACERS 0x004b1584
const LegoFloat g_lightningFrequencyRampScale = 0.1f;

// GLOBAL: LEGORACERS 0x004b1588
const LegoFloat g_lightningImpulseScale = 80.0f;

// GLOBAL: LEGORACERS 0x004b158c
const LegoFloat g_lightningLaunchImpulse = 200.0f;

// GLOBAL: LEGORACERS 0x004b15a0
const LegoFloat g_lightningFlashWidth = 8.0f;

// GLOBAL: LEGORACERS 0x004b15a4
const LegoFloat g_lightningFlashHeight = 8.0f;

// GLOBAL: LEGORACERS 0x004b15d4
const LegoFloat g_lightningRandomScale = 0.00097751711f;

// GLOBAL: LEGORACERS 0x004c7604
LegoFloat g_lightningReachSquared = g_lightningReach * g_lightningReach;

// GLOBAL: LEGORACERS 0x004c7608
GolVec3 g_beamSegmentOffsets[5];

extern LegoU16 g_randomTable[1024];

extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x00454800
LightningAction::LightningAction()
{
	m_jitterCursor = 0;
	m_unk0x228 = 3;
	m_boltLength = g_lightningRange;
	m_crackleTimerMs = 0;
	m_sound = NULL;
	m_hitParticle = 0;
	m_unk0x234 = 0;
	m_shockTimerMs = 0;
	m_source = 0;
	m_flashBillboard = NULL;
}

// FUNCTION: LEGORACERS 0x00454890
LightningAction::~LightningAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004548f0
void LightningAction::Initialize(GolExport* p_export, RacePowerupManager* p_manager)
{
	if (m_state != c_stateUnloaded) {
		Destroy();
	}

	m_owner = p_manager;
	m_collisionWorld = p_manager->m_collisionWorld;
	m_jitterTimerMs = 0;
	m_shockTimerMs = 0;
	m_source = 0;

	GolD3DRenderDevice* renderer = p_export->GetDrawState()->m_currentRenderer;

	BeamMesh::SetupParams params;
	params.m_material = renderer->FindMaterialByName("lightng");
	params.m_ringVertices[1].m_y = g_lightningBeamThickness * 0.5f;
	params.m_ringVertices[2].m_x = -g_lightningBeamThickness;
	params.m_golExport = p_export;
	params.m_renderer = renderer;
	params.m_sectionCount = 4;
	params.m_segmentCount = 5;
	params.m_ringQuadCount = 2;
	params.m_ringVertices[0].m_x = 0.0f;
	params.m_ringVertices[0].m_y = g_lightningBeamThickness;
	params.m_ringVertices[0].m_z = -0.25f;
	params.m_ringVertices[1].m_x = 0.0f;
	params.m_ringVertices[1].m_z = 0.0f;
	params.m_ringVertices[2].m_y = -0.25f;
	params.m_ringVertices[2].m_z = 0.0f;
	params.m_ringTextureXs[0] = 0.0f;
	params.m_ringTextureXs[1] = 0.5f;
	params.m_ringTextureXs[2] = 1.0f;
	params.m_textureColumnCount = 3;
	params.m_modelDistance = 360000.0f;
	params.m_faceCamera = 1;
	m_beam.Initialize(&params);
	m_beam.SetColors(&g_lightningBaseColor, &g_lightningSecondaryColor, &g_lightningTertiaryColor);

	m_flashBillboard = static_cast<GolBillboard*>(p_export->CreateBillboard());
	GolMaterial* material = renderer->FindMaterialByName("ltflash");
	m_flashBillboard->Configure(material, g_lightningFlashWidth, g_lightningFlashHeight, g_lightningFlashDrawDistance);

	m_state = c_stateReady;
	FillJitterTable();
}

// FUNCTION: LEGORACERS 0x00454a70
void LightningAction::AcquireSound()
{
	m_sound = m_soundSource->AcquireSoundById(c_soundLoop);
	if (m_sound != NULL) {
		m_sound->SetDistanceRangeWithMinSquared(
			g_lightningSoundMinDistance * g_lightningSoundMinDistance,
			g_lightningSoundMaxDistanceSquared
		);
	}
}

// FUNCTION: LEGORACERS 0x00454ab0
void LightningAction::Destroy()
{
	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_sound);
		m_sound = NULL;
	}

	Deactivate();

	if (m_flashBillboard != NULL) {
		m_flashBillboard->SetPrimaryModel();
		m_owner->m_golExport->DestroyBillboard(m_flashBillboard);
		m_flashBillboard = NULL;
	}

	m_beam.Destroy();
	m_state = c_stateUnloaded;
	m_hitParticle = 0;
	m_source = 0;
}

// FUNCTION: LEGORACERS 0x00454b20
void LightningAction::AdvanceJitter()
{
	g_randomTableIndex = (g_randomTableIndex + 1) & 0x3ff;
	m_jitterTable[m_jitterCursor] =
		((LegoS32) g_randomTable[g_randomTableIndex] * g_lightningRandomScale - 0.5f) * 5.0f;

	m_jitterCursor++;
	if (m_jitterCursor >= 20) {
		m_jitterCursor = 0;
	}
}

// FUNCTION: LEGORACERS 0x00454b90
void LightningAction::FillJitterTable()
{
	for (LegoU32 i = 0; i < 20; i++) {
		AdvanceJitter();
	}
}

// FUNCTION: LEGORACERS 0x00454bb0
void LightningAction::RebuildBolt()
{
	LegoS32 index = static_cast<LegoS32>(m_jitterCursor) - 1;
	GolVec3* modelPosition = m_boltPoints;
	BeamMesh* field = &m_beam;
	RaceActionSource* source = m_source;

	GolVec3 position;
	LegoFloat amount;
	position = *source;
	amount = g_lightningBoltAmplitude;
	position.m_z += g_lightningSourceHeightOffset;

	GolVec3 direction;
	direction.m_x = modelPosition[0].m_x - position.m_x;
	direction.m_y = modelPosition[0].m_y - position.m_y;
	direction.m_z = modelPosition[0].m_z - position.m_z;
	field->Begin(&position, &direction);

	for (LegoS32 i = 0; i < 4; i++) {
		GolVec3* offset = g_beamSegmentOffsets;
		while (offset < &g_beamSegmentOffsets[5]) {
			if (index < 0) {
				index = 19;
			}

			offset->m_x = m_jitterTable[index--];
			offset->m_y = offset->m_x;
			offset->m_z = 0.0f;
			offset++;
		}

		field->SetSegmentOffsets(g_beamSegmentOffsets);
		field->AppendSpan(modelPosition, amount);

		modelPosition++;
		amount = -amount;
	}

	field->Finish();
}

// FUNCTION: LEGORACERS 0x00454cb0
void LightningAction::Activate(Racer* p_racer, ActionTarget* p_target)
{
	m_state = c_stateRampIn;
	m_stateTimerMs = 500;
	m_ownerRacer = p_racer;
	m_targetRacer = NULL;

	if (p_racer != NULL) {
		m_source = &p_racer->m_actionSource;
	}
	else {
		m_source = p_target->m_source;
	}

	m_crackleTimerMs = 0;
	if (m_sound != NULL) {
		m_sound->Play(TRUE);
	}
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00454d10
void LightningAction::Deactivate()
{
	if (m_targetRacer != NULL) {
		m_targetRacer->EndSpinOut();
	}

	if (m_owner != NULL && m_hitParticle != NULL) {
		m_owner->m_cutsceneAnimation->FinishRef(m_hitParticle);
		m_hitParticle = NULL;
	}

	m_beam.SetColors(&g_lightningBaseColor, &g_lightningSecondaryColor, &g_lightningTertiaryColor);
	m_source = NULL;
	m_ownerRacer = NULL;
	m_targetRacer = NULL;
	m_state = c_stateReady;
}

// FUNCTION: LEGORACERS 0x00454d70
void LightningAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	if (p_elapsedMs >= m_stateTimerMs) {
		p_elapsedMs -= m_stateTimerMs;
		m_stateTimerMs = 0;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}

	m_jitterTimerMs += p_elapsedMs;
	while (m_jitterTimerMs > c_jitterIntervalMs) {
		AdvanceJitter();
		m_jitterTimerMs -= c_jitterIntervalMs;
	}

	if (m_targetRacer != NULL) {
		m_shockTimerMs += p_elapsedMs;
		if (m_shockTimerMs > c_shockDurationMs) {
			m_targetRacer->EndSpinOut();
			m_targetRacer = NULL;
			m_shockTimerMs = 0;
			m_beam.SetColors(&g_lightningBaseColor, &g_lightningSecondaryColor, &g_lightningTertiaryColor);
		}
	}

	UpdateBoltPath();
	RebuildBolt();
	UpdateHitParticle();
	FindVictim();
	UpdateSound(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00454e50
void LightningAction::UpdateSound(LegoU32 p_elapsedMs)
{
	if (m_sound != NULL) {
		m_sound->SetPosition(*m_source);
		m_sound->SetVelocity(m_source->m_velocity);

		switch (m_state) {
		case c_stateRampIn:
			m_sound->SetFrequencyScale(
				1.0f - static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs)) * g_lightningFrequencyRampScale *
						   g_unk0x004b02fc
			);
			break;
		case c_stateSustain:
			m_sound->SetFrequencyScale(1.0f);
			break;
		case c_stateFade:
			m_sound->SetFrequencyScale(
				1.0f - static_cast<LegoFloat>(static_cast<LegoS32>(c_fadeDurationMs - m_stateTimerMs)) *
						   g_lightningFrequencyRampScale * g_unk0x004b02fc
			);
			break;
		}
	}

	if (m_state != c_stateSustain) {
		return;
	}

	if (m_crackleTimerMs < p_elapsedMs) {
		SoundVector position = *m_source;

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoS32 distance = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange;
		SoundVector* right = &m_source->m_forward;
		GolVec3 offset;
		offset.m_x = static_cast<LegoFloat>(distance) * right->m_x;
		offset.m_y = right->m_y * static_cast<LegoFloat>(distance);
		offset.m_z = static_cast<LegoFloat>(distance) * right->m_z;
		position.m_x += offset.m_x;
		position.m_y += offset.m_y;
		position.m_z += offset.m_z;

		m_soundSource->PlaySpatialSoundById(
			c_soundCrackle,
			&position,
			g_lightningSoundMinDistance,
			g_lightningSoundMaxDistanceSquared,
			1.0f,
			1.0f
		);

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		m_crackleTimerMs =
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_crackleIntervalRangeMs + c_crackleMinIntervalMs;
	}
	else {
		m_crackleTimerMs -= p_elapsedMs;
	}
}

// FUNCTION: LEGORACERS 0x00455020
void LightningAction::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_targetRacer != NULL) {
		m_flashBillboard->SetPosition(m_boltPoints[3]);
		p_renderer->DrawBillboard(*m_flashBillboard);
	}

	m_beam.Draw(p_renderer);
}

// FUNCTION: LEGORACERS 0x00455060
void LightningAction::AdvanceState()
{
	switch (m_state) {
	case c_stateRampIn:
		m_state = c_stateSustain;
		m_stateTimerMs = c_sustainDurationMs;
		break;
	case c_stateSustain:
		m_state = c_stateFade;
		m_stateTimerMs = c_fadeDurationMs;
		break;
	default:
		m_state = c_stateDone;
		m_stateTimerMs = 0;

		if (m_owner != NULL && m_hitParticle != NULL) {
			m_owner->m_cutsceneAnimation->FinishRef(m_hitParticle);
			m_hitParticle = NULL;
		}

		m_soundSource->PlaySpatialSoundById(
			c_soundThunder,
			m_source,
			g_lightningSoundMinDistance,
			g_lightningSoundMaxDistanceSquared,
			1.0f,
			1.0f
		);

		if (m_sound != NULL) {
			m_sound->Stop();
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x00455100
void LightningAction::UpdateBoltPath()
{
	GolVec3 position = *m_source;
	position.m_z += g_lightningSourceHeightOffset;

	GolVec3 direction = m_source->m_forward;
	if (m_state == c_stateRampIn) {
		m_boltLength =
			(1.0f - static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs)) * g_unk0x004b02fc) * g_lightningRange;
	}
	else if (m_state == c_stateFade) {
		LegoFloat amount = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs)) * g_unk0x004b02fc;
		m_boltLength = amount * g_lightningRange;
	}
	else {
		m_boltLength = g_lightningRange;
	}

	GolVec3 end;
	GolVec3 scaledDirection;
	GolVec3 hit;
	GolBoundingVolume::HitTriangle record;
	LegoFloat scale = m_boltLength;
	scale *= 4.0f;
	scaledDirection.m_x = direction.m_x * scale;
	scaledDirection.m_y = direction.m_y * scale;
	scaledDirection.m_z = direction.m_z * scale;
	GolCameraBase::Add(&position, &scaledDirection, &end);

	if (m_targetRacer != NULL) {
		m_targetRacer->m_visuals.m_carEntity->GetPosition(&end);

		direction.m_x = end.m_x - position.m_x;
		direction.m_y = end.m_y - position.m_y;
		direction.m_z = end.m_z - position.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		LegoFloat distance = static_cast<LegoFloat>(::sqrt(
			(position.m_z - end.m_z) * (position.m_z - end.m_z) + (position.m_y - end.m_y) * (position.m_y - end.m_y) +
			(position.m_x - end.m_x) * (position.m_x - end.m_x)
		));
		LegoFloat radius = m_targetRacer->m_visuals.m_entityGroup.GetBoundsRadius();
		if (distance > radius) {
			distance -= radius;
		}

		m_boltLength = distance * g_carBuildModelTextureCoordinateScale;
	}
	else {
		if (m_collisionWorld->IntersectSegmentAndFireEvents(&position, &end, &record, &hit)) {
			LegoFloat distance = static_cast<LegoFloat>(::sqrt(
				(position.m_z - hit.m_z) * (position.m_z - hit.m_z) +
				(position.m_y - hit.m_y) * (position.m_y - hit.m_y) +
				(position.m_x - hit.m_x) * (position.m_x - hit.m_x)
			));
			m_boltLength = distance * g_carBuildModelTextureCoordinateScale;
		}
	}

	direction *= m_boltLength;
	for (LegoS32 i = 0; i < sizeOfArray(m_boltPoints); i++) {
		position += direction;
		m_boltPoints[i] = position;
	}
}

// FUNCTION: LEGORACERS 0x00455350
void LightningAction::FindVictim()
{
	Racer* racer;

	if (m_targetRacer != NULL) {
		return;
	}

	SoundVector position = *m_source;
	position.m_z += g_lightningSourceHeightOffset;

	RaceState* raceState = m_owner->m_raceState;
	racer = raceState->FindRacerInCone(
		&position,
		&m_source->m_forward,
		g_lightningChainMinDistanceSquared,
		g_lightningReachSquared,
		g_lightningChainConeCosine
	);

	while (racer != NULL) {
		if (racer != m_ownerRacer) {
			GolVec3* start = &position;
			LegoS32 i = 0;
			GolVec3* segment = m_boltPoints;
			for (; i < sizeOfArray(m_boltPoints);) {
				GolVec3 hit;
				if (racer->m_visuals.IntersectSegment(start, segment, &hit)) {
					OnHitRacer(racer);
					break;
				}

				start = segment;
				i++;
				segment++;
			}
		}

		racer = raceState->FindNextRacerInCone(
			racer,
			&position,
			&m_source->m_forward,
			g_lightningChainMinDistanceSquared,
			g_lightningReachSquared,
			g_lightningChainConeCosine
		);
	}
}

// FUNCTION: LEGORACERS 0x00455440
void LightningAction::OnHitRacer(Racer* p_racer)
{
	LegoU32 state = m_state;

	if (state == c_stateSustain) {
		Racer* racer = p_racer;
		if (racer->GetFlags() & Racer::c_flagShielded) {
			racer->PlayReaction(TRUE);
			racer->AbsorbShieldHit();
			return;
		}

		if (!(racer->m_physics.m_flags & RacerPhysics::c_flagSpinOut)) {
			RacerPhysics* physics = &racer->m_physics;
			GolVec3 direction = physics->m_facingDirection;
			racer->StartSpinOut();

			physics->m_velocity.m_x = 0.0f;
			physics->m_velocity.m_y = 0.0f;
			physics->m_velocity.m_z = 0.0f;

			GolVec3 impulse;
			impulse.m_x = direction.m_x * g_lightningImpulseScale;
			impulse.m_y = direction.m_y * g_lightningImpulseScale;
			impulse.m_z = direction.m_z * g_lightningImpulseScale + g_lightningLaunchImpulse;

			physics->ApplyImpulse(&impulse, &impulse);

			CarVisuals* racerCarVisuals = &racer->m_visuals;
			ColorTransform transform;
			transform.m_redOffset = c_flashRedGrnOffset;
			transform.m_redShift = 0;
			transform.m_grnOffset = c_flashRedGrnOffset;
			transform.m_grnShift = 0;
			transform.m_bluOffset = c_flashBluOffset;
			transform.m_bluShift = 0;
			transform.m_alpOffset = 0;
			transform.m_alpShift = 0;
			racerCarVisuals->FlashColor(&transform, c_flashDurationMs);

			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			racer->PlayReaction(FALSE);
			racer->DropWhiteBrick();
			racerCarVisuals->m_reactionFlags |= CarVisuals::c_reactionHit;

			m_shockTimerMs = 0;
			m_targetRacer = racer;
			m_beam.SetColors(&g_lightningHitColor, &g_lightningHitColor, &g_lightningHitColor);

			CutsceneAnimation* cutsceneAnimation = m_owner->m_cutsceneAnimation;
			if (m_hitParticle != NULL) {
				cutsceneAnimation->FinishRef(m_hitParticle);
			}

			m_hitParticle = cutsceneAnimation->SpawnParticle("lghthit", NULL, NULL, NULL);

			SoundVector position;
			racerCarVisuals->m_carEntity->GetPosition(&position);
			m_soundSource->PlaySpatialSoundById(
				c_soundZap,
				&position,
				g_lightningSoundMinDistance,
				g_lightningSoundMaxDistanceSquared,
				1.0f,
				1.0f
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00455620
void LightningAction::GetProjectilePosition(GolVec3* p_position)
{
	*p_position = m_boltPoints[3];
}

// FUNCTION: LEGORACERS 0x00455640
void LightningAction::GetProjectileVelocity(GolVec3* p_velocity)
{
	p_velocity->m_x = 0.0f;
	p_velocity->m_y = 0.0f;
	p_velocity->m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00455660
void LightningAction::UpdateHitParticle()
{
	if (m_hitParticle == NULL) {
		return;
	}

	if (m_targetRacer == NULL) {
		m_owner->m_cutsceneAnimation->FinishRef(m_hitParticle);
		m_hitParticle = NULL;
		return;
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolVec3 direction;
	direction.m_x = -m_source->m_forward.m_x;
	direction.m_y = -m_source->m_forward.m_y;
	direction.m_z = -m_source->m_forward.m_z;

	if (m_hitParticle->m_particle != NULL) {
		m_hitParticle->m_particle->SetPosition(&m_boltPoints[3]);
	}

	if (m_hitParticle->m_particle != NULL) {
		m_hitParticle->m_particle->SetOrientation(&direction, &up);
	}
}
