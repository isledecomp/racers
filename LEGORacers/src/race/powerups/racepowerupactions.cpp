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
extern const LegoFloat g_unk0x004b03f4;
extern const LegoFloat g_unk0x004b0958;
extern const LegoFloat g_unk0x004b095c;
extern const LegoFloat g_unlimitedDrawDistance;
extern const LegoFloat g_unk0x004b14dc;
extern const LegoFloat g_unk0x004b1508;
extern const LegoFloat g_unk0x004b0b4c;
extern const LegoFloat g_unk0x004b165c;
extern const LegoFloat g_unk0x004b1660;
extern const LegoFloat g_unk0x004b1930;
extern const LegoFloat g_unk0x004b1934;
extern const LegoFloat g_unk0x004b1a6c;
extern const LegoFloat g_carBuildModelTextureCoordinateScale;
extern LegoFloat g_cosineTable[1024];
extern const LegoFloat g_ghostSpeedScale;
extern const LegoFloat g_ghostSampleFractionScale;
extern const LegoFloat g_item0x40RadiansToTableIndex;
extern const LegoFloat g_item0x40Pi;
extern const LegoFloat g_negativeRadiansToTableIndex;
extern const LegoFloat g_homingProjectileCollisionProbeDepth;
extern const LegoFloat g_homingProjectileCollisionStartOffset;
extern const LegoFloat g_violetShoalTwo;

// GLOBAL: LEGORACERS 0x004b02fc
const LegoFloat g_unk0x004b02fc = 0.002f;

// GLOBAL: LEGORACERS 0x004b0400
const LegoFloat g_unk0x004b0400 = 0.002f;

// GLOBAL: LEGORACERS 0x004b1370
const LegoFloat g_cannonballTargetHeightOffset = 5.0f;

// GLOBAL: LEGORACERS 0x004b1384
const LegoFloat g_powerupSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b1388
const LegoFloat g_powerupSoundMaxDistance = 300.0f;

const LegoFloat g_powerupHitSoundMinDistance = 200.0f;

const LegoFloat g_powerupHitSoundMaxDistance = 600.0f;

// GLOBAL: LEGORACERS 0x004b1394
const LegoFloat g_cannonballGravity = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1398
const LegoFloat g_cannonballSpeed = 180.0f;

// GLOBAL: LEGORACERS 0x004b139c
const LegoFloat g_cannonballDefaultRange = 500.0f;

// GLOBAL: LEGORACERS 0x004b13a4
const LegoFloat g_cannonballTrailSize = 3.0f;

// GLOBAL: LEGORACERS 0x004b13b0
const LegoFloat g_cannonballSmokeHeightOffset = 4.0f;

// GLOBAL: LEGORACERS 0x004b13b4
const LegoFloat g_cannonballLaunchHeight = 5.0f;

// GLOBAL: LEGORACERS 0x004b13e4
const LegoFloat g_scarNormalThreshold = 0.70709997f;

// GLOBAL: LEGORACERS 0x004b13e8
const LegoFloat g_emplacementGravityScale = 3.0f;

const LegoFloat g_unk0x004b13f0 = 30.0f;

const LegoFloat g_unk0x004b13f4 = 300.0f;

const LegoFloat g_unk0x004b13f8 = 10.0f;

const LegoFloat g_unk0x004b1420 = 13.0f;

const LegoFloat g_unk0x004b1424 = 5.0f;

// GLOBAL: LEGORACERS 0x004b1428
const LegoFloat g_unk0x004b1428 = 3.0f;

const LegoFloat g_unk0x004b1434 = 30.0f;

const LegoFloat g_unk0x004b1438 = 300.0f;

const LegoFloat g_unk0x004b143c = 200.0f;

const LegoFloat g_unk0x004b1440 = 600.0f;

const LegoFloat g_unk0x004b1444 = 0.012f;

const LegoFloat g_unk0x004b146c = 5.17852306f;

const LegoFloat g_unk0x004b1470 = 0.155761003f;

const LegoFloat g_unk0x004b1474 = -0.727681994f;

const LegoFloat g_unk0x004b1478 = 0.727681994f;

const LegoFloat g_unk0x004b147c = -90.0f;

// GLOBAL: LEGORACERS 0x004b1484
const LegoFloat g_unk0x004b1484 = 3.0f;

// GLOBAL: LEGORACERS 0x004b14a8
const LegoFloat g_unk0x004b14a8 = 100.0f;

// GLOBAL: LEGORACERS 0x004b14ac
const LegoFloat g_unk0x004b14ac = 0.8f;

// GLOBAL: LEGORACERS 0x004b170c
const LegoFloat g_unk0x004b170c = 30.0f;

// GLOBAL: LEGORACERS 0x004b14e0
const LegoFloat g_unk0x004b14e0 = 30.0f;

// GLOBAL: LEGORACERS 0x004b14e4
const LegoFloat g_unk0x004b14e4 = 300.0f;

// GLOBAL: LEGORACERS 0x004b14e8
const LegoFloat g_unk0x004b14e8 = 4.0f;

// GLOBAL: LEGORACERS 0x004b14ec
const LegoFloat g_unk0x004b14ec = 180.0f;

// GLOBAL: LEGORACERS 0x004b14f0
const LegoFloat g_unk0x004b14f0 = -90.1760025f;

// GLOBAL: LEGORACERS 0x004b14f4
const LegoFloat g_unk0x004b14f4 = 320.0f;

// GLOBAL: LEGORACERS 0x004b150c
const LegoFloat g_unk0x004b150c = 5.0f;

// GLOBAL: LEGORACERS 0x004b1510
const LegoFloat g_unk0x004b1510 = 144.0f;

// GLOBAL: LEGORACERS 0x004b1514
const LegoFloat g_unk0x004b1514 = 0.6f;

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
const LegoFloat g_lightningRange = 50.0f;

// GLOBAL: LEGORACERS 0x004b157c
const LegoFloat g_unk0x004b157c = 9.0f;

// GLOBAL: LEGORACERS 0x004b1580
const LegoFloat g_unk0x004b1580 = 0.5f;

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

const LegoFloat g_unk0x004b15dc = 30.0f;

const LegoFloat g_unk0x004b15e0 = 300.0f;

const LegoFloat g_unk0x004b15e4 = 10.0f;

const LegoFloat g_unk0x004b15e8 = 100.0f;

const LegoFloat g_unk0x004b15ec = 81.0f;

const LegoFloat g_unk0x004b15f0 = 30.0f;

const LegoFloat g_unk0x004b15f4 = 1.0f;

const LegoFloat g_unk0x004b15f8 = 1.0f;

// GLOBAL: LEGORACERS 0x004c75f4
LegoFloat g_unk0x004c75f4 = 1.0f / g_unk0x004b14a8;

// GLOBAL: LEGORACERS 0x004c75f8
LegoFloat g_unk0x004c75f8 = g_ghostSampleFractionScale * g_unk0x004b14a8;

// GLOBAL: LEGORACERS 0x004c7600
LegoFloat g_unk0x004c7600 = g_ghostSpeedScale * g_lightningRange;

// GLOBAL: LEGORACERS 0x004c7604
LegoFloat g_unk0x004c7604 = g_unk0x004c7600 * g_unk0x004c7600;

// GLOBAL: LEGORACERS 0x004c7608
GolVec3 g_beamSegmentOffsets[5];

// GLOBAL: LEGORACERS 0x004b1620
const LegoFloat g_unk0x004b1620 = 127.0f;

// GLOBAL: LEGORACERS 0x004b1628
const LegoFloat g_unk0x004b1628 = 1.0f;

// GLOBAL: LEGORACERS 0x004b162c
const LegoFloat g_unk0x004b162c = 50.0f;

// GLOBAL: LEGORACERS 0x004b1664
const LegoFloat g_unk0x004b1664 = 200.0f;

// GLOBAL: LEGORACERS 0x004b1668
const LegoFloat g_unk0x004b1668 = 600.0f;

// GLOBAL: LEGORACERS 0x004b166c
const LegoFloat g_unk0x004b166c = 170.0f;

// GLOBAL: LEGORACERS 0x004b1670
const LegoFloat g_unk0x004b1670 = -32.1759987f;

// GLOBAL: LEGORACERS 0x004b1674
const LegoFloat g_unk0x004b1674 = 500.0f;

// GLOBAL: LEGORACERS 0x004b1678
const LegoFloat g_unk0x004b1678 = 4.0f;

const LegoFloat g_unk0x004b1684 = 100.0f;

const LegoFloat g_unk0x004b1688 = 160000.0f;

// GLOBAL: LEGORACERS 0x004b168c
const LegoFloat g_unk0x004b168c = 0.70709997f;

// GLOBAL: LEGORACERS 0x004b16c0
const LegoFloat g_unk0x004b16c0 = 30.0f;

// GLOBAL: LEGORACERS 0x004b16c4
const LegoFloat g_unk0x004b16c4 = 300.0f;

// GLOBAL: LEGORACERS 0x004b16c8
const LegoFloat g_unk0x004b16c8 = 200.0f;

// GLOBAL: LEGORACERS 0x004b16cc
const LegoFloat g_unk0x004b16cc = 600.0f;

// GLOBAL: LEGORACERS 0x004b1704
const LegoFloat g_unk0x004b1704 = 0.01f;

// GLOBAL: LEGORACERS 0x004b19d4
const LegoFloat g_unk0x004b19d4 = 30.0f;

// GLOBAL: LEGORACERS 0x004b19d8
const LegoFloat g_unk0x004b19d8 = 300.0f;

// GLOBAL: LEGORACERS 0x004b19e4
const LegoFloat g_unk0x004b19e4 = 0.7f;

// GLOBAL: LEGORACERS 0x004b1a50
const LegoFloat g_unk0x004b1a50 = -2.0f;

// GLOBAL: LEGORACERS 0x004b1a54
const LegoFloat g_unk0x004b1a54 = 0.0028571428f;

// GLOBAL: LEGORACERS 0x004b1a58
const LegoFloat g_unk0x004b1a58 = 0.6f;

// GLOBAL: LEGORACERS 0x004b1a60
const LegoFloat g_unk0x004b1a60 = 200.0f;

// GLOBAL: LEGORACERS 0x004b1a64
const LegoFloat g_unk0x004b1a64 = 600.0f;

// GLOBAL: LEGORACERS 0x004b1a68
const LegoFloat g_unk0x004b1a68 = 45.0f;

// GLOBAL: LEGORACERS 0x004b1a70
const LegoFloat g_unk0x004b1a70 = 0.6f;

// GLOBAL: LEGORACERS 0x004b1a74
const LegoFloat g_unk0x004b1a74 = 700.0f;

// GLOBAL: LEGORACERS 0x004b1aa8
const LegoFloat g_unk0x004b1aa8 = 0.00066666666f;

// GLOBAL: LEGORACERS 0x004c1c4c
ColorRGBA g_unk0x004c1c4c = {0x32, 0x32, 0x32, 0xc8};

// GLOBAL: LEGORACERS 0x004c1c50
ColorRGBA g_unk0x004c1c50 = {0x64, 0x3c, 0x0e, 0xff};

// GLOBAL: LEGORACERS 0x004c1c54
ColorRGBA g_unk0x004c1c54 = {0x8f, 0x5a, 0x1c, 0xff};

// GLOBAL: LEGORACERS 0x004c1c58
ColorRGBA g_unk0x004c1c58 = {0x14, 0x14, 0x00, 0xff};

// GLOBAL: LEGORACERS 0x004c1c64
ColorRGBA g_unk0x004c1c64 = {0xff, 0xff, 0xff, 0xc8};

extern LegoU16 g_randomTable[1024];
extern LegoU32 g_randomTableIndex;

// FUNCTION: LEGORACERS 0x004518f0
RacePowerupManager::CannonballAction::CannonballAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_billboard = NULL;
	m_smokeParticle = 0;
	m_emplacement = 0;
	m_trailParticle = 0;
}

// FUNCTION: LEGORACERS 0x00451970
RacePowerupManager::CannonballAction::~CannonballAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004519d0
void RacePowerupManager::CannonballAction::Initialize(GolExport** p_unk0x04, RaceSessionField0x32b4* p_unk0x08)
{
	if (m_state != 0) {
		Destroy();
	}

	m_golExportPtr = p_unk0x04;
	m_collisionWorld = p_unk0x08;
	m_billboard = static_cast<GolBillboard*>((*p_unk0x04)->VTable0x30());
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00451a10
void RacePowerupManager::CannonballAction::Destroy()
{
	Deactivate();

	if (m_golExportPtr != NULL && m_billboard != NULL) {
		(*m_golExportPtr)->VTable0x64(m_billboard);
		m_billboard = NULL;
		m_golExportPtr = NULL;
	}

	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00451a50
LegoU32 RacePowerupManager::CannonballAction::Activate(ActionSetup* p_unk0x04)
{
	m_state = 2;
	m_ownerRacer = p_unk0x04->m_racer;
	m_targetRacer = p_unk0x04->m_targetRacer;
	m_targetPoint = p_unk0x04->m_targetPoint;
	m_stateTimerMs = p_unk0x04->m_initialTimerMs;

	ActionTarget* target = p_unk0x04->m_aimTarget;
	if (target) {
		m_materialName = target->m_materialName;
	}

	GolD3DRenderDevice* renderDevice = m_owner0x01c->m_renderer;
	const LegoChar* materialName = m_materialName;
	DuskwindBananaRelic0x24* material;
	if (materialName && materialName[0]) {
		material = renderDevice->FindMaterialByName(materialName);
	}
	else {
		material = renderDevice->FindMaterialByName("cannon");
	}

	return m_billboard->VTable0x4c(material, 5.0f, 5.0f, g_unlimitedDrawDistance);
}

// FUNCTION: LEGORACERS 0x00451ad0
void RacePowerupManager::CannonballAction::Deactivate()
{
	m_projectile.Deactivate();

	if (m_smokeParticle != NULL) {
		m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f00(m_smokeParticle);
		m_smokeParticle = NULL;
	}

	if (m_billboard != NULL) {
		m_billboard->VTable0x50();
	}

	m_ownerRacer = NULL;
	m_targetRacer = 0;
	m_targetPoint = 0;
	m_emplacement = 0;
	m_state = 1;

	if (m_owner0x01c != NULL && m_trail != NULL) {
		m_owner0x01c->m_trailManager->FUN_00493a10(m_trail);
		m_trail = NULL;
	}
}

// STUB: LEGORACERS 0x00451b50
void RacePowerupManager::CannonballAction::Update(LegoU32 p_elapsedMs)
{
	GolVec2 perpendicular;
	GolVec3 direction;
	GolVec3 particlePosition;
	GolVec3 particleVelocity;
	GolVec3 trailVelocity;
	GolVec3 positions[4];

	if (p_elapsedMs >= m_stateTimerMs) {
		p_elapsedMs -= m_stateTimerMs;
		m_stateTimerMs = 0;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}

	if (m_state == 3) {
		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			SoundVector position;
			GolVec3& positionBase = position;
			positionBase = m_projectile.GetHitPosition();
			LegoBool32 skipBurst = FALSE;

			if (projectileState == PowerupProjectile::c_stateHitRacer) {
				RaceState::Racer* target = m_projectile.GetHitRacer();
				if ((target->m_unk0xd04 & c_racerFlags0xd04Bit0) && target->m_shieldLevel >= 2) {
					skipBurst = TRUE;
				}

				OnHitRacer(target);
				m_stateTimerMs = 3000;
			}
			else {
				m_soundSource->PlaySpatialSoundById(
					c_soundHit,
					&position,
					g_powerupHitSoundMinDistance,
					g_powerupHitSoundMaxDistance,
					1.0f,
					1.0f
				);
			}

			if (!skipBurst) {
				GolVec3 hitNormal = m_projectile.GetHitNormal();
				LegoBool32 upwardHit = FALSE;
				if (projectileState == PowerupProjectile::c_stateHitWorld && hitNormal.m_z > g_scarNormalThreshold) {
					upwardHit = TRUE;
				}

				m_owner0x01c->SpawnExplosion(&position, upwardHit, m_ownerRacer);
				if (projectileState == PowerupProjectile::c_stateHitRacer &&
					!(m_projectile.GetHitRacer()->m_unk0xd04 & c_racerFlags0xd04Bit0)) {
					m_projectile.GetVelocity(&direction);
					direction.m_x = -direction.m_x;
					direction.m_y = -direction.m_y;
					direction.m_z = 0.0f;
					GolMath::NormalizeVector3(direction, &direction);
					m_owner0x01c->FUN_0045b550(&position, &direction, m_projectile.GetHitRacer());
				}

				AdvanceState();
			}
		}
	}

	if (m_smokeParticle != NULL) {
		CutsceneParticle* particle = m_smokeParticle->m_unk0x00;
		if (particle != NULL && particle->GetSpawnedCount() < 3) {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&particlePosition);
				particlePosition.m_z += g_cannonballSmokeHeightOffset;

				particleVelocity = m_ownerRacer->m_unk0x3e8.m_unk0x008;
				if (m_smokeParticle->m_unk0x00 != NULL) {
					m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_smokeParticle->m_unk0x00->GetUnk0x160());
				}

				if (m_smokeParticle->m_unk0x00 != NULL) {
					m_smokeParticle->m_unk0x00->FUN_00489660(&particlePosition);
				}
				if (m_smokeParticle->m_unk0x00 != NULL) {
					m_smokeParticle->m_unk0x00->FUN_00489690(&particleVelocity);
				}
			}
		}
		else {
			m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f30(m_smokeParticle);
			m_smokeParticle = NULL;
		}
	}

	if (m_state == 3) {
		GolVec3 position;
		m_projectile.GetWorldEntity()->FUN_100286d0(&position);

		if (m_trail != NULL) {
			m_projectile.GetVelocity(&trailVelocity);

			perpendicular.m_x = trailVelocity.m_y;
			perpendicular.m_y = -trailVelocity.m_x;
			if (perpendicular.m_y != 0.0f || perpendicular.m_x != 0.0f) {
				GolMath::NormalizeVector2(perpendicular, &perpendicular);
				perpendicular.m_x *= g_cannonballTrailSize;
				perpendicular.m_y *= g_cannonballTrailSize;

				positions[0].m_x = position.m_x - perpendicular.m_x * 0.5f;
				positions[0].m_y = position.m_y - perpendicular.m_y * 0.5f;
				positions[0].m_z = position.m_z + g_cannonballTrailSize * 0.5f;
				positions[1].m_x = positions[0].m_x;
				positions[1].m_y = positions[0].m_y;
				positions[1].m_z = positions[0].m_z - g_cannonballTrailSize;
				positions[2].m_x = positions[0].m_x + perpendicular.m_x;
				positions[2].m_y = positions[0].m_y + perpendicular.m_y;
				positions[2].m_z = positions[1].m_z;
				positions[3].m_x = positions[2].m_x;
				positions[3].m_y = positions[2].m_y;
				positions[3].m_z = positions[1].m_z + g_cannonballTrailSize;

				m_trail->FUN_00492ee0(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00451f30
void RacePowerupManager::CannonballAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 3) {
		p_renderer->VTable0xb4(*m_billboard);
	}
}

// STUB: LEGORACERS 0x00451f50
void RacePowerupManager::CannonballAction::AdvanceState()
{
	switch (m_state) {
	case 2:
		break;
	case 3:
		m_state = 6;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_trail != NULL) {
			m_owner0x01c->m_trailManager->FUN_00493a10(m_trail);
			m_trail = NULL;
		}

		return;
	default:
		m_state = 6;
		m_stateTimerMs = 0;
		return;
	}

	m_state = 3;
	LegoU32 durationMs = 3000;
	SoundVector position;
	GolVec3 direction;
	GolVec3 target;
	GolVec3 velocity;
	GolVec3 right;
	GolVec3 forward;
	PowerupProjectile::Params projectileParams;
	RaceTrailManager::Trail::Params trailParams;

	m_stateTimerMs = durationMs;

	if (m_emplacement == NULL) {
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_unk0x044->VTable0x04(&position);
		m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);
	}
	else {
		GolVec3& positionBase = position;
		positionBase = m_emplacement->m_position;
		direction.m_x = 0.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;
	}

	projectileParams.m_worldEntity = m_billboard;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_cannonballGravity;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_cannonballSpeed;
	projectileParams.m_lifetimeMs = durationMs;
	projectileParams.m_launchHeight = g_cannonballLaunchHeight;

	if (m_targetRacer != NULL) {
		m_projectile.LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, TRUE, FALSE);
	}
	else if (m_emplacement != NULL) {
		projectileParams.m_lifetimeMs = m_emplacement->m_lifetimeMs;
		m_billboard->VTable0x08(m_emplacement->m_position);
		projectileParams.m_gravity = g_cannonballGravity * g_emplacementGravityScale;
		m_projectile.LaunchAtPosition(&projectileParams, &m_emplacement->m_targetPosition);
	}
	else {
		if (m_targetPoint != NULL) {
			target = m_targetPoint->m_unk0x00;
		}
		else {
			target.m_x = position.m_x + direction.m_x * g_cannonballDefaultRange;
			target.m_y = position.m_y + direction.m_y * g_cannonballDefaultRange;
			target.m_z = position.m_z + direction.m_z * g_cannonballDefaultRange + g_cannonballTargetHeightOffset;
		}

		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;
		m_projectile.LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &velocity, TRUE);
	}

	m_smokeParticle = m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489d70("cannsmk", NULL, NULL, NULL);
	if (m_smokeParticle != NULL) {
		if (m_emplacement == NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x48(&right, &forward);
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		}
		else {
			GolVec3& positionBase = position;
			positionBase = m_emplacement->m_position;
			right.m_x = 1.0f;
			right.m_y = 0.0f;
			right.m_z = 0.0f;
			forward.m_x = 0.0f;
			forward.m_y = 0.0f;
			forward.m_z = 1.0f;
		}

		position.m_z += g_cannonballSmokeHeightOffset;
		if (m_smokeParticle->m_unk0x00 != NULL) {
			m_smokeParticle->m_unk0x00->FUN_00489540(&right, &forward);
		}
		if (m_smokeParticle->m_unk0x00 != NULL) {
			m_smokeParticle->m_unk0x00->FUN_00489660(&position);
		}
	}

	trailParams.m_unk0x00 = 300;
	trailParams.m_unk0x04 = 4;
	trailParams.m_unk0x08 = 4;
	trailParams.m_unk0x0c = 1;
	trailParams.m_unk0x10 = 0;
	trailParams.m_unk0x14 = 0.1f;
	trailParams.m_unk0x18 = 0.0f;
	m_trail = m_owner0x01c->m_trailManager->FUN_004939b0(&trailParams);
	if (m_trail != NULL) {
		m_trail->FUN_00492ab0(&g_unk0x004c1c4c);

		DuskwindBananaRelic0x24* material = m_owner0x01c->m_renderer->FindMaterialByName("canstrk");
		if (material != NULL) {
			m_trail->FUN_00492a90(m_owner0x01c->m_renderer, material);
		}
	}

	if (m_emplacement != NULL) {
		GolVec3& positionBase = position;
		positionBase = m_emplacement->m_position;
	}
	else {
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_unk0x044->VTable0x04(&position);
	}

	m_soundSource->PlaySpatialSoundById(
		c_soundFire,
		&position,
		g_powerupSoundMinDistance,
		g_powerupSoundMaxDistance,
		1.0f,
		1.0f
	);
}

// FUNCTION: LEGORACERS 0x00452370
void RacePowerupManager::CannonballAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == 3) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();
			if (p_racer->m_shieldLevel >= 2) {
				m_projectile.Deflect(p_racer);
				m_ownerRacer = p_racer;
			}
		}
		else {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();
			SoundVector position;
			p_racer->m_unk0x018.SetFlags0x384(c_racerField0x018Flags0x384Bit1);
			p_racer->m_unk0x018.GetUnk0x044()->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(
				c_soundHit,
				&position,
				g_powerupHitSoundMinDistance,
				g_powerupHitSoundMaxDistance,
				1.0f,
				1.0f
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00452430 FOLDED
#pragma code_seg(".text$animatedpartresource_vt18")
LegoS32 RacePowerupManager::WeaponActionBase::GetBrickColor()
{
	return c_brickColorRed;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x00452440
RacePowerupManager::CurseAction::CurseAction()
{
	FUN_004524f0();
}

// FUNCTION: LEGORACERS 0x004524a0
RacePowerupManager::CurseAction::~CurseAction()
{
	FUN_00452510();
}

// FUNCTION: LEGORACERS 0x004524f0
void RacePowerupManager::CurseAction::FUN_004524f0()
{
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_raceState0x018 = NULL;
	m_collisionWorld = 0;
	m_unk0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00452510
void RacePowerupManager::CurseAction::FUN_00452510()
{
	Deactivate();
	FUN_004524f0();
}

// FUNCTION: LEGORACERS 0x00452530
void RacePowerupManager::CurseAction::Initialize(
	RaceState* p_raceState,
	RaceSessionField0x32b4* p_unk0x08,
	RacePowerupManager* p_unk0x0c
)
{
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_unk0x08;
	m_unk0x2c = p_unk0x0c;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452550
void RacePowerupManager::CurseAction::Activate(
	RaceState::Racer* p_racer,
	GolAnimatedEntity* p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10,
	ActionTarget* p_unk0x14
)
{
	m_unk0x30 = m_unk0x2c->AllocateEffectEntity();
	if (m_unk0x30 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x34 = m_unk0x2c->AllocateEffectEntity();
	if (m_unk0x34 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x38 = m_unk0x2c->AllocateEffectEntity();
	if (m_unk0x38 == NULL) {
		m_state = 6;
		return;
	}

	m_ownerRacer = p_racer;

	m_unk0x30->FUN_0040d550(
		p_unk0x08->GetModel(0),
		p_unk0x08->VTable0x58(0),
		p_unk0x08->GetModelPart(0),
		p_unk0x08->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x08->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x08->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x08->GetModelPart(i);
			m_unk0x30->FUN_10023940(model, p_unk0x08->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x30->SetFlags(m_unk0x30->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x30->FUN_0040dad0(0);

	m_unk0x34->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x0c->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x0c->GetModelPart(i);
			m_unk0x34->FUN_10023940(model, p_unk0x0c->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x34->SetFlags(m_unk0x34->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x34->FUN_0040dad0(0);
	m_unk0x34->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x34->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x34->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x34->FUN_00411730(p_unk0x0c->FUN_004116f0());

	m_unk0x38->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x10->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x10->GetModelPart(i);
			m_unk0x38->FUN_10023940(model, p_unk0x10->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x38->SetFlags(m_unk0x38->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x38->FUN_0040dad0(0);
	m_unk0x38->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x38->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x38->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x38->FUN_00411730(p_unk0x10->FUN_004116f0());

	if (m_ownerRacer == NULL) {
		GolVec3 position = p_unk0x14->m_unk0x00;
		GolVec3 direction = p_unk0x14->m_unk0x0c;

		GolWorldEntity* target = &m_unk0x3c;
		target->VTable0x08(position);
		m_unk0x3c.FUN_10026fa0(10.0f);
		m_unk0x34->VTable0x08(position);
		m_unk0x38->VTable0x08(position);

		position.m_z += 13.0f;
		m_unk0x30->VTable0x08(position);

		direction.m_x = -direction.m_x;
		direction.m_y = -direction.m_y;
		direction.m_z = -direction.m_z;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;

		GolVec3 forward;
		forward.m_x = -direction.m_y;
		forward.m_y = direction.m_x;
		forward.m_z = 0.0f;
		m_unk0x30->VTable0x40(forward, up);

		m_unk0x34->CopyOrientationFrom(*m_unk0x30);
		m_unk0x38->CopyOrientationFrom(*m_unk0x30);
	}

	m_state = 2;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00452970
void RacePowerupManager::CurseAction::Deactivate()
{
	if (m_unk0x38 != NULL) {
		m_unk0x38->VTable0x54();
		m_unk0x2c->ReleaseEffectEntity(m_unk0x38);
		m_unk0x38 = NULL;
	}

	if (m_unk0x34 != NULL) {
		m_unk0x34->VTable0x54();
		m_unk0x2c->ReleaseEffectEntity(m_unk0x34);
		m_unk0x34 = NULL;
	}

	if (m_unk0x30 != NULL) {
		m_unk0x30->VTable0x54();
		m_unk0x2c->ReleaseEffectEntity(m_unk0x30);
		m_unk0x30 = NULL;
	}

	if (m_unk0x64 != NULL) {
		m_soundSource->ReleaseSound(m_soundResource64);
		m_unk0x64 = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452a00
void RacePowerupManager::CurseAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_state0x06) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);
	m_unk0x30->VTable0x10(p_elapsedMs);
	m_unk0x34->VTable0x10(p_elapsedMs);
	m_unk0x38->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00452a40
void RacePowerupManager::CurseAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x06) {
		return;
	}

	if (m_state == c_state0x04) {
		m_unk0x30->SetUnk0x58AndInvalidateRadius(static_cast<LegoS32>(m_stateTimerMs) * 0.001f);
	}

	p_renderer->VTable0x94(m_unk0x30);
}

// FUNCTION: LEGORACERS 0x00452a80
void RacePowerupManager::CurseAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x06) {
		return;
	}

	if (m_state == c_state0x04) {
		LegoFloat scale = static_cast<LegoS32>(m_stateTimerMs) * 0.001f;
		m_unk0x34->SetUnk0x58AndInvalidateRadius(scale);
		m_unk0x38->SetUnk0x58ThenInvalidateRadius(m_unk0x34->GetUnk0x58());
	}

	m_unk0x34->VTable0x1c(*p_renderer);
	m_unk0x38->VTable0x1c(*p_renderer);
}

// FUNCTION: LEGORACERS 0x00452ae0
void RacePowerupManager::CurseAction::AdvanceState()
{
	switch (m_state) {
	case c_state0x02:
		break;
	case c_state0x03:
		m_state = c_state0x04;
		m_stateTimerMs = c_timer0x03e8;
		return;
	case c_state0x04:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		return;
	default:
		return;
	}

	GolVec3 position;
	if (m_ownerRacer != NULL) {
		GolBoundingVolume::Field0x0c record;
		FUN_00456360(m_ownerRacer, &position, &record);

		GolVec3 direction;
		if (m_ownerRacer->m_unk0xcc4 != NULL) {
			direction = m_ownerRacer->m_unk0xcc4->m_unk0x00;
		}
		else {
			direction.m_x = 1.0f;
			direction.m_y = 0.0f;
			direction.m_z = 0.0f;
		}

		m_unk0x3c.VTable0x08(position);
		m_unk0x3c.FUN_10026fa0(g_unk0x004b13f8);
		m_unk0x34->VTable0x08(position);
		m_unk0x38->VTable0x08(position);

		GolVec3 up = record.m_unk0x24;
		position.m_x += up.m_x * 13.0f;
		position.m_y += up.m_y * 13.0f;
		position.m_z += up.m_z * 13.0f;
		m_unk0x30->VTable0x08(position);

		GolVec3 cross;
		cross.m_x = up.m_y * direction.m_z - up.m_z * direction.m_y;
		cross.m_y = up.m_z * direction.m_x - direction.m_z * up.m_x;
		cross.m_z = direction.m_y * up.m_x - up.m_y * direction.m_x;
		m_unk0x30->VTable0x40(cross, up);

		m_unk0x34->CopyOrientationFrom(*m_unk0x30);
		m_unk0x38->CopyOrientationFrom(*m_unk0x30);
	}
	else {
		m_unk0x3c.VTable0x04(&position);
		position.m_z += 13.0f;
	}

	m_unk0x64 = m_soundSource->AcquireSoundById(c_sound0x09);
	if (m_unk0x64 != NULL) {
		m_unk0x64->Play(TRUE);
		m_unk0x64->SetDistanceRangeWithMinSquared(g_unk0x004b13f0 * g_unk0x004b13f0, g_unk0x004b13f4);
		m_unk0x64->SetPosition(position);
	}

	m_state = c_state0x03;
	m_stateTimerMs = c_timer0x3a98;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_worldEntity = &m_unk0x3c;
	m_collisionEvent = m_raceState0x018->GetEventQueue()->FUN_0042fb50(this, &descriptor);
}

// FUNCTION: LEGORACERS 0x00452da0
void RacePowerupManager::CurseAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state != c_state0x05 && !(p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit11)) {
		p_racer->FUN_00439900(m_unk0x30, c_timer0x2710);
	}
}

// FUNCTION: LEGORACERS 0x00452dd0
RacePowerupManager::DynamiteAction::DynamiteAction()
{
	m_unk0x164 = 0;
	m_unk0x168 = 0;
	m_unk0x16c = 0;
	m_unk0x170 = 0;
	m_unk0x174 = 0;
	m_unk0x178 = 0;
}

// FUNCTION: LEGORACERS 0x00452e50
RacePowerupManager::DynamiteAction::~DynamiteAction()
{
	FUN_00452eb0();
}

// FUNCTION: LEGORACERS 0x00452eb0
void RacePowerupManager::DynamiteAction::FUN_00452eb0()
{
	Deactivate();
	m_unk0x02c.VTable0x54();
	m_unk0x164 = 0;
	m_unk0x168 = 0;
	m_unk0x16c = 0;
	m_unk0x170 = 0;
}

// FUNCTION: LEGORACERS 0x00452ee0
void RacePowerupManager::DynamiteAction::Initialize(
	RaceState* p_raceState,
	RaceSessionField0x32b4* p_unk0x08,
	RacePowerupManager* p_unk0x0c,
	undefined4 p_unk0x10,
	GolModelEntity* p_model
)
{
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_unk0x08;
	m_unk0x164 = p_unk0x0c;
	m_unk0x168 = p_unk0x10;

	m_unk0x02c.VTable0x50(p_model->GetModel(0), p_model->GetModelDistance(0));

	for (LegoU32 i = 1; i < 3; i++) {
		GolModelBase* model = p_model->GetModel(i);
		if (model != NULL) {
			m_unk0x02c.FUN_10027c50(model, p_model->GetModelDistance(i));
		}
	}

	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452f60
LegoU32 RacePowerupManager::DynamiteAction::Activate(RaceState::Racer* p_racer, RaceState::Racer* p_unk0x08)
{
	m_ownerRacer = p_racer;
	LegoU32 result = 0;
	m_unk0x174 = p_unk0x08;
	m_state = 2;
	m_stateTimerMs = result;
	m_unk0x178 = 0.0f;
	return result;
}

// FUNCTION: LEGORACERS 0x00452f90
void RacePowerupManager::DynamiteAction::Deactivate()
{
	if (m_unk0x170 != NULL) {
		m_soundSource->ReleaseSound(m_soundResource170);
		m_unk0x170 = NULL;
	}

	m_projectile.Deactivate();

	if (m_unk0x16c != NULL) {
		m_cutsceneAnimation->FUN_00489f30(m_unk0x16c);
		m_unk0x16c = NULL;
	}

	m_unk0x174 = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00452ff0
void RacePowerupManager::DynamiteAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_state0x06) {
		return;
	}

	SoundVector position;
	m_unk0x02c.VTable0x04(&position);

	if (m_projectile.GetState() != 0) {
		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			if (projectileState == PowerupProjectile::c_stateHitWorld) {
				const GolVec3* projectilePosition = &m_projectile.GetHitPosition();
				position.m_x = projectilePosition->m_x;
				position.m_y = projectilePosition->m_y;
				position.m_z = projectilePosition->m_z;
			}

			m_unk0x164->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
			m_state = c_state0x04;
			m_stateTimerMs = c_timer0x01f4;
			m_soundSource->PlaySpatialSoundById(c_sound0x05, &position, g_unk0x004b143c, g_unk0x004b1440, 1.0f, 1.0f);

			if (m_unk0x170 != NULL) {
				m_soundSource->ReleaseSound(m_soundResource170);
				m_unk0x170 = NULL;
			}

			m_projectile.Deactivate();

			if (m_unk0x16c != NULL) {
				m_cutsceneAnimation->FUN_00489f30(m_unk0x16c);
				m_unk0x16c = NULL;
			}
		}
	}

	m_unk0x178 += static_cast<LegoFloat>(p_elapsedMs) * 0.012f;

	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(m_unk0x178 * g_negativeRadiansToTableIndex)) & 0x3ff;
	GolVec3 up;
	up.m_x = g_cosineTable[tableIndex];
	up.m_y = 0.0f;

	tableIndex = static_cast<LegoS32>(m_unk0x178 * g_item0x40RadiansToTableIndex) & 0x3ff;
	up.m_z = g_cosineTable[tableIndex];

	GolVec3 direction;
	direction.m_x = -up.m_z;
	direction.m_y = 0.0f;
	direction.m_z = up.m_x;
	m_unk0x02c.VTable0x40(direction, up);

	if (m_unk0x16c != NULL) {
		position.m_x += up.m_x * g_unk0x004b1474;
		position.m_y += up.m_y * 0.155761003f;
		position.m_z += up.m_z * 5.17852306f;

		if (m_unk0x16c->m_unk0x00 != NULL) {
			m_unk0x16c->m_unk0x00->FUN_00489660(&position);
		}
	}

	if (m_unk0x170 != NULL) {
		m_unk0x170->SetPosition(&position);
	}

	PowerupActionBase::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00453210
void RacePowerupManager::DynamiteAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_state0x06 && m_state != c_state0x04 && m_state != c_state0x05) {
		p_renderer->VTable0x94(&m_unk0x02c);
	}
}

// FUNCTION: LEGORACERS 0x00453240
void RacePowerupManager::DynamiteAction::AdvanceState()
{
	GolVec3 position;
	m_unk0x02c.VTable0x04(&position);

	switch (m_state) {
	case c_state0x02: {
		PowerupProjectile::Params projectileParams;
		projectileParams.m_worldEntity = &m_unk0x02c;
		projectileParams.m_collisionWorld = m_collisionWorld;
		projectileParams.m_gravity = -32.1759987f;
		projectileParams.m_eventQueue = m_unk0x164->GetRaceState()->GetEventQueue();
		projectileParams.m_targetOffset.m_x = 0.0f;
		projectileParams.m_targetOffset.m_y = 0.0f;
		projectileParams.m_targetOffset.m_z = 0.0f;
		projectileParams.m_speed = 40.0f;
		projectileParams.m_lifetimeMs = c_timer0x0bb8;
		projectileParams.m_launchHeight = g_unk0x004b1424;

		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		GolVec3 racerPosition;
		racerField->m_unk0x044->VTable0x04(&racerPosition);

		GolVec3 forward;
		m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&forward);

		if (m_unk0x174 != NULL) {
			m_projectile.LaunchAtRacer(&projectileParams, m_ownerRacer, m_unk0x174, TRUE, TRUE);
		}
		else {
			GolVec3 targetVelocity;
			targetVelocity.m_x = 0.0f;
			targetVelocity.m_y = 0.0f;
			targetVelocity.m_z = 0.0f;

			GolVec3 target;
			target.m_x = racerPosition.m_x + forward.m_x * g_unk0x004b147c;
			target.m_y = racerPosition.m_y + forward.m_y * g_unk0x004b147c;
			target.m_z = racerPosition.m_z + forward.m_z * g_unk0x004b147c + 5.0f;

			m_projectile.LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &targetVelocity, TRUE);
		}

		m_state = c_state0x03;
		m_stateTimerMs = c_timer0x1388;
		m_unk0x16c = m_cutsceneAnimation->FUN_00489d70("dynsprk", NULL, NULL, NULL);
		if (m_unk0x16c != NULL) {
			position.m_x -= 0.727681994f;
			position.m_y += 0.155761003f;
			position.m_z += 5.17852306f;

			if (m_unk0x16c->m_unk0x00 != NULL) {
				m_unk0x16c->m_unk0x00->FUN_00489660(&position);
			}
		}

		m_unk0x170 = m_soundSource->AcquireSoundById(c_sound0x11);
		if (m_unk0x170 != NULL) {
			m_unk0x170->SetDistanceRange(g_unk0x004b1434, g_unk0x004b1438);
			m_unk0x170->SetPosition(position);
			m_unk0x170->Play(TRUE);
		}
		break;
	}
	case c_state0x03:
		m_unk0x164->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		break;
	case c_state0x04:
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_x +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_y +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;
		m_unk0x164->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_state0x05;
		m_stateTimerMs = c_timer0x01f4;
		break;
	case c_state0x05:
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_x +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;

		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		position.m_y +=
			static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomOffsetRange - c_randomOffsetCenter;
		m_unk0x164->SpawnSpikeExplosion(&position, TRUE, m_ownerRacer);
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		break;
	}
}

// FUNCTION: LEGORACERS 0x004535a0
RacePowerupManager::WhiteBrick::WhiteBrick()
{
	m_droppedTimeMs = 0;
	m_flags0x64 = 0;
}

// FUNCTION: LEGORACERS 0x004535c0
RacePowerupManager::WhiteBrick::~WhiteBrick()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453610
void RacePowerupManager::WhiteBrick::Reset()
{
	m_droppedTimeMs = 0;
	m_flags0x64 = 0;
	FUN_00453a10();
}

// FUNCTION: LEGORACERS 0x00453620
void RacePowerupManager::WhiteBrick::CaptureHomePosition()
{
	m_worldEntity.VTable0x04(&m_homePosition);
	m_state = c_stateActive;
	m_droppedTimeMs = 0;
	m_flags0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00453650
void RacePowerupManager::WhiteBrick::Respawn()
{
	PickupBrick::Respawn();
	m_worldEntity.VTable0x08(m_homePosition);
	m_state = c_stateActive;
	m_droppedTimeMs = 0;
	m_flags0x64 = 0;
	m_stateTimerMs = 0;
	FUN_00453ad0(FALSE);
}

// FUNCTION: LEGORACERS 0x00453690
void RacePowerupManager::WhiteBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	PickupBrick::Update(p_elapsedMs);

	if (m_flags0x64 & c_flagDropped) {
		m_droppedTimeMs += p_elapsedMs;
		if (m_droppedTimeMs > 10000) {
			ReturnHome();
		}
	}

	LegoU32 state = m_state;
	if (state != c_stateActive) {
		if (state == c_stateTransition && m_stateTimerMs > 250) {
			LegoU8 flags = m_flags0x64;
			if (flags & c_flagReturnHome) {
				m_flags0x64 = flags & ~c_flagReturnHome;
				m_worldEntity.VTable0x08(m_homePosition);
				m_state = c_stateActive;
			}
			else {
				m_state = c_stateWait;
			}

			m_stateTimerMs = 0;
			FUN_00453ad0(FALSE);
		}
	}
	else if (m_stateTimerMs > 500) {
		m_state = c_stateIdle;
		m_stateTimerMs = 0;
		FUN_00453ad0(TRUE);
	}
}

// FUNCTION: LEGORACERS 0x00453750
void RacePowerupManager::WhiteBrick::OnTouched(RaceState::Racer* p_racer)
{
	if (m_state == c_stateIdle && p_racer->CollectWhiteBrick(this)) {
		m_nextState = c_stateWait;
		m_state = c_stateTransition;
		m_stateTimerMs = 0;
		m_flags0x64 &= ~c_flagDropped;
		m_droppedTimeMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x00453910
RacePowerupManager::PickupBrick::PickupBrick()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453960
RacePowerupManager::PickupBrick::~PickupBrick()
{
	FUN_00453a10();
}

// FUNCTION: LEGORACERS 0x00453970
LegoS32 RacePowerupManager::PickupBrick::Reset()
{
	m_scale = 1.0f;
	m_model = NULL;
	m_blendModel = NULL;
	m_manager = NULL;
	m_soundSource = NULL;
	m_state = c_stateInactive;
	m_nextState = c_stateWait;
	m_stateTimerMs = 0;
	m_respawnMs = 3000;
	m_flags0x50 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x004539b0
void RacePowerupManager::PickupBrick::Initialize(
	RacePowerupManager* p_owner,
	RaceState::Racer::Field0x004* p_soundResource,
	GolVec3* p_position,
	GolModelEntity* p_model0,
	GolModelEntity* p_model1
)
{
	if (m_manager != NULL) {
		FUN_00453a10();
	}

	m_manager = p_owner;
	m_soundSource = p_soundResource;
	m_blendModel = p_model1;
	m_model = p_model0;
	m_worldEntity.VTable0x08(*p_position);
	m_state = c_stateWait;
	m_stateTimerMs = 3000;
}

// FUNCTION: LEGORACERS 0x00453a00
void RacePowerupManager::PickupBrick::Respawn()
{
	m_state = c_stateWait;
	m_stateTimerMs = 3000;
}

// FUNCTION: LEGORACERS 0x00453a10
void RacePowerupManager::PickupBrick::FUN_00453a10()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453a20
void RacePowerupManager::PickupBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs + m_stateTimerMs;
	m_stateTimerMs = elapsedMs;

	LegoS32 stateOffset = m_state - c_stateActive;
	if (stateOffset != 0) {
		if (stateOffset == 1 && elapsedMs <= 250) {
			LegoFloat transition = (LegoS32) (250 - elapsedMs) * g_unk0x004c75f8;
			m_scale = transition * (g_unk0x004b14ac * g_unk0x004c75f4);
		}
	}
	else {
		if (elapsedMs < 400) {
			m_scale = (LegoS32) elapsedMs * 0.0024999999f;
		}
		else if (elapsedMs < 500) {
			m_scale = 1.0f - (LegoS32) (elapsedMs - 400) * g_unk0x004b0400;
		}
	}

	LegoU8 flags = m_flags0x50;
	if (flags & c_flags0x50Bit1) {
		m_flags0x50 = (flags & ~(c_flags0x50Bit1 | c_flags0x50Bit2)) | c_flags0x50Bit2;
	}
	else {
		m_flags0x50 = flags & ~c_flags0x50Bit2;
	}
}

// FUNCTION: LEGORACERS 0x00453ad0
void RacePowerupManager::PickupBrick::FUN_00453ad0(LegoBool32 p_unk0x04)
{
	if (p_unk0x04) {
		m_scale = g_unk0x004b14ac;
	}
	else {
		m_scale = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x00453af0
void RacePowerupManager::PickupBrick::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	m_flags0x50 |= c_flags0x50Bit1;

	if (m_state == c_stateIdle) {
		RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
		if (!(racer->GetUnk0xd04() & c_racerFlags0xd04Bit4)) {
			if (!(m_flags0x50 & c_flags0x50Bit2) || racer->GetUnk0xccc() == 0) {
				OnTouched(racer);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00453b30
void RacePowerupManager::PickupBrick::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateInactive &&
		(m_state == c_stateActive || m_state == c_stateIdle || m_state == c_stateTransition)) {
		GolVec3 position;
		m_worldEntity.VTable0x04(&position);
		m_model->VTable0x08(position);
		m_model->SetUnk0x58ThenInvalidateRadius(m_scale);
		m_model->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00453b90
void RacePowerupManager::PickupBrick::VTable0x14(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateInactive &&
		(m_state == c_stateActive || m_state == c_stateIdle || m_state == c_stateTransition)) {
		GolVec3 position;
		m_worldEntity.VTable0x04(&position);
		m_blendModel->VTable0x08(position);
		m_blendModel->SetUnk0x58ThenInvalidateRadius(m_scale);
		m_blendModel->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00453bf0
RacePowerupManager::GrapplingHookAction::GrapplingHookAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x270 = NULL;
	m_unk0x28c = 0;
}

// FUNCTION: LEGORACERS 0x00453c70
RacePowerupManager::GrapplingHookAction::~GrapplingHookAction()
{
	FUN_00453d90();
}

// FUNCTION: LEGORACERS 0x00453cd0
void RacePowerupManager::GrapplingHookAction::Initialize(
	RacePowerupManager* p_unk0x04,
	RaceSessionField0x32b4* p_unk0x08,
	undefined4 p_unk0x0c
)
{
	if (m_state != 0) {
		FUN_00453d90();
	}

	m_owner0x01c = p_unk0x04;
	m_collisionWorld = p_unk0x08;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x28c = p_unk0x0c;

	TetherProjectile::SetupParams params;
	params.m_golExport = p_unk0x04->m_golExport;
	params.m_ropeThickness = g_unk0x004b1514;
	params.m_waveAmplitude = g_unk0x004b14e8;
	params.m_baseColor = g_unk0x004c1c50;
	params.m_attachHeight = 3.0f;
	params.m_secondaryColor = g_unk0x004c1c54;
	params.m_tertiaryColor = g_unk0x004c1c58;
	params.m_material = p_unk0x04->m_renderer->FindMaterialByName("tether");
	m_projectile.Initialize(&params);

	m_state = 1;
	m_unk0x270 = static_cast<GolBillboard*>(params.m_golExport->VTable0x30());
}

// FUNCTION: LEGORACERS 0x00453d90
void RacePowerupManager::GrapplingHookAction::FUN_00453d90()
{
	Deactivate();

	if (m_owner0x01c != NULL && m_unk0x270 != NULL) {
		m_owner0x01c->m_golExport->VTable0x64(m_unk0x270);
		m_unk0x270 = NULL;
		m_owner0x01c = NULL;
	}

	m_projectile.Deactivate();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x00453de0
LegoU32 RacePowerupManager::GrapplingHookAction::Activate(
	GolModelEntity* p_unk0x04,
	RaceState::Racer* p_racer,
	RaceState::Racer* p_unk0x0c,
	Field0x050::Entry* p_unk0x10,
	MabMaterialAnimationItem0x18* p_unk0x14,
	LegoU32 p_unk0x18
)
{
	m_unk0x268 = p_unk0x04;
	m_ownerRacer = p_racer;
	m_targetRacer = p_unk0x0c;
	m_state = 2;
	m_targetPoint = p_unk0x10;
	m_stateTimerMs = p_unk0x18;

	m_unk0x274.FUN_004103c0(*p_unk0x14);
	m_unk0x274.FUN_00410470();
	m_unk0x274.FUN_00410480();
	m_unk0x274.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_unk0x28c, FALSE);
	m_unk0x274
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());

	return m_unk0x270->FUN_10029e90(
		m_owner0x01c->GetBillboardMaterialTable(),
		m_unk0x28c,
		g_unk0x004b1508,
		g_unk0x004b1508,
		g_unk0x004b14dc
	);
}

// FUNCTION: LEGORACERS 0x00453e90
void RacePowerupManager::GrapplingHookAction::Deactivate()
{
	m_projectile.CancelCollisionEvent();

	if (m_unk0x26c != NULL) {
		m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f00(m_unk0x26c);
		m_unk0x26c = NULL;
	}

	m_unk0x274.Reset();

	if (m_unk0x270 != NULL) {
		m_unk0x270->VTable0x50();
	}

	m_ownerRacer = NULL;
	m_targetRacer = 0;
	m_targetPoint = 0;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00453ef0
void RacePowerupManager::GrapplingHookAction::Update(LegoU32 p_elapsedMs)
{
	GolVec3 direction;
	SoundVector targetPosition;
	SoundVector position;
	GolVec3 forward;
	SoundVector projectilePositionCopy;
	GolVec3 up;
	GolVec3 velocity;

	if (m_state == 6) {
		return;
	}

	LegoS32 projectileState = 0;
	if (p_elapsedMs >= m_stateTimerMs) {
		p_elapsedMs -= m_stateTimerMs;
		m_stateTimerMs = projectileState;
		AdvanceState();
	}
	else {
		m_stateTimerMs -= p_elapsedMs;
	}

	if (m_state == 2) {
		return;
	}

	projectileState = m_projectile.Update(p_elapsedMs);
	if (projectileState != PowerupProjectile::c_stateFlying) {
		if (projectileState == PowerupProjectile::c_stateHitRacer) {
			OnHitRacer(m_projectile.GetHitRacer());
		}
	}

	switch (m_state) {
	case 3: {
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			FUN_00454690(&projectilePositionCopy);
		}
		else {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);

			up.m_x = 0.0f;
			up.m_y = 0.0f;
			up.m_z = 1.0f;

			const GolVec3* target = &m_projectile.GetTargetPosition();
			GolVec3& targetPositionBase = targetPosition;
			targetPositionBase = *target;
			forward.m_x = targetPosition.m_x - position.m_x;
			forward.m_y = targetPosition.m_y - position.m_y;
			forward.m_z = targetPosition.m_z - position.m_z;
			m_unk0x268->VTable0x40(forward, up);
		}

		break;
	}
	case 4:
		if (projectileState == PowerupProjectile::c_stateHitWorld) {
			GolVec3& projectilePositionCopyBase = projectilePositionCopy;
			projectilePositionCopyBase = m_projectile.GetHitPosition();
			FUN_00454690(&projectilePositionCopy);
		}
		else {
			RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
			racerField->m_unk0x044->VTable0x04(&position);

			RaceState::Racer* targetRacer = m_projectile.GetHitRacer();
			targetRacer->m_unk0x018.m_unk0x044->VTable0x04(&targetPosition);

			if (targetRacer->m_unk0xd04 & c_racerFlags0xd04Bit0) {
				FUN_00454690(&targetPosition);
				return;
			}

			direction.m_x = targetPosition.m_x - position.m_x;
			direction.m_y = targetPosition.m_y - position.m_y;
			direction.m_z = targetPosition.m_z - position.m_z;

			LegoFloat distanceSquared = direction.m_y * direction.m_y;
			distanceSquared += direction.m_z * direction.m_z;
			distanceSquared += direction.m_x * direction.m_x;
			if (distanceSquared < g_unk0x004b1510) {
				FUN_00454690(&targetPosition);
				break;
			}

			m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&forward);

			LegoFloat dot = direction.m_z;
			dot *= forward.m_z;
			dot += direction.m_y * forward.m_y;
			dot += direction.m_x * forward.m_x;
			if (dot < 0.0f) {
				FUN_00454690(&targetPosition);
				break;
			}

			GolMath::NormalizeVector3(direction, &direction);
			direction.m_x *= g_unk0x004b14ec;
			direction.m_y *= g_unk0x004b14ec;
			direction.m_z *= g_unk0x004b14ec;
			m_ownerRacer->m_unk0x3e8.VTable0x48(&direction);

			direction.m_x = -direction.m_x;
			direction.m_y = -direction.m_y;
			direction.m_z = -direction.m_z;
			targetRacer->m_unk0x3e8.VTable0x40(&direction);
		}
		break;
	case 5:
		if (m_unk0x274.IsAssigned()) {
			m_unk0x274.FUN_004104c0(
				p_elapsedMs,
				m_owner0x01c->GetMaterialAnimationItems(),
				m_owner0x01c->GetMaterialAnimationItemCount()
			);
			m_unk0x270->VTable0x10(p_elapsedMs);
		}

		if (projectileState == 4) {
			m_state = 6;
			m_stateTimerMs = 0;
		}
		break;
	}

	if (m_unk0x26c != NULL) {
		CutsceneParticle* particle = m_unk0x26c->m_unk0x00;
		if (particle == NULL || particle->GetSpawnedCount() >= 3) {
			m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f30(m_unk0x26c);
			m_unk0x26c = NULL;
			return;
		}

		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		velocity = m_ownerRacer->m_unk0x3e8.m_unk0x008;
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_unk0x26c->m_unk0x00->GetUnk0x160());
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489660(&position);
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489690(&velocity);
		}
	}
}

// FUNCTION: LEGORACERS 0x004542d0
void RacePowerupManager::GrapplingHookAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	switch (m_state) {
	case 3:
		p_renderer->VTable0x94(m_unk0x268);
		m_projectile.Draw(p_renderer);
		break;
	case 4:
		p_renderer->VTable0x94(m_unk0x268);
		m_projectile.Draw(p_renderer);
		break;
	case 5:
		m_projectile.Draw(p_renderer);
		if (m_unk0x274.IsAssigned()) {
			p_renderer->VTable0xb4(*m_unk0x270);
		}
		break;
	}
}

// STUB: LEGORACERS 0x00454360
void RacePowerupManager::GrapplingHookAction::AdvanceState()
{
	SoundVector targetPosition;

	if (m_state != 2) {
		if (m_state > 2 && m_state <= 4) {
			m_unk0x268->VTable0x04(&targetPosition);
			FUN_00454690(&targetPosition);
		}
		else {
			m_state = 6;
			m_stateTimerMs = 0;
		}

		return;
	}

	SoundVector position;
	GolVec3 direction;
	GolVec3 scaledDirection;
	GolVec3 targetVelocity;
	PowerupProjectile::Params projectileParams;
	RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
	LegoU32 durationMs = 3000;

	m_state = 3;
	m_stateTimerMs = durationMs;

	racerField->m_unk0x044->VTable0x04(&position);

	m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	projectileParams.m_worldEntity = m_unk0x268;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_unk0x004b14f0;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_unk0x004b14f4;
	projectileParams.m_lifetimeMs = durationMs;
	projectileParams.m_launchHeight = g_unk0x004b150c;

	if (m_targetRacer == NULL) {
		if (m_targetPoint != NULL) {
			targetPosition.m_x = m_targetPoint->m_unk0x00.m_x;
			targetPosition.m_y = m_targetPoint->m_unk0x00.m_y;
			targetPosition.m_z = m_targetPoint->m_unk0x00.m_z;
		}
		else {
			scaledDirection.m_x = direction.m_x * 500.0f;
			scaledDirection.m_y = direction.m_y * 500.0f;
			scaledDirection.m_z = direction.m_z * 500.0f;
			GolCameraBase::FUN_00404550(&position, &scaledDirection, &targetPosition);
			targetPosition.m_z = 5.0f + targetPosition.m_z;
		}

		targetVelocity.m_x = 0.0f;
		targetVelocity.m_y = 0.0f;
		targetVelocity.m_z = 0.0f;
		m_projectile
			.PowerupProjectile::LaunchAtPoint(&projectileParams, m_ownerRacer, &targetPosition, &targetVelocity, TRUE);
	}
	else {
		m_projectile.PowerupProjectile::LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, TRUE, FALSE);
	}

	m_projectile.ResetRope();

	m_unk0x26c = m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489d70("cannsmk", NULL, NULL, NULL);
	if (m_unk0x26c != NULL) {
		m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x04(&position);
		position.m_z += 4.0f;

		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_ownerRacer->m_unk0x3e8.m_unk0x13c->VTable0x44(m_unk0x26c->m_unk0x00->GetUnk0x160());
		}
		if (m_unk0x26c->m_unk0x00 != NULL) {
			m_unk0x26c->m_unk0x00->FUN_00489660(&position);
		}
	}

	racerField->m_unk0x044->VTable0x04(&position);
	m_soundSource->PlaySpatialSoundById(0x15, &position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x004545d0
void RacePowerupManager::GrapplingHookAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == 3) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();

			SoundVector position;
			m_unk0x268->VTable0x04(&position);
			FUN_00454690(&position);
		}
		else {
			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();

			SoundVector position;
			p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(0x12, &position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);

			m_state = 4;
			m_stateTimerMs = 4000;
		}
	}
}

// FUNCTION: LEGORACERS 0x00454690
void RacePowerupManager::GrapplingHookAction::FUN_00454690(SoundVector* p_position)
{
	RaceState::Racer* racer = m_projectile.GetHitRacer();
	if (racer != NULL) {
		racer->m_unk0x3e8.VTable0x44();
		m_ownerRacer->m_unk0x3e8.VTable0x4c();
		m_soundSource->PlaySpatialSoundById(0x14, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
	}
	else {
		m_soundSource->PlaySpatialSoundById(0x16, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
		m_soundSource->PlaySpatialSoundById(0x49, p_position, g_unk0x004b14e0, g_unk0x004b14e4, 1.0f, 1.0f);
	}

	m_state = 5;
	m_stateTimerMs = 500;
	m_unk0x274.FUN_00410470();
	m_unk0x274.FUN_00410480();
	m_unk0x274.FUN_10025da0(m_owner0x01c->GetBillboardMaterialTable(), m_unk0x28c, FALSE);
	m_unk0x274
		.FUN_004104c0(0, m_owner0x01c->GetMaterialAnimationItems(), m_owner0x01c->GetMaterialAnimationItemCount());
	m_unk0x270->VTable0x08(*p_position);
	m_projectile.Release(p_position);
	m_projectile.CancelCollisionEvent();
}

// FUNCTION: LEGORACERS 0x00454800
RacePowerupManager::LightningAction::LightningAction()
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
RacePowerupManager::LightningAction::~LightningAction()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004548f0
void RacePowerupManager::LightningAction::Initialize(GolExport* p_export, RacePowerupManager* p_unk0x08)
{
	if (m_state != 0) {
		Destroy();
	}

	m_owner0x01c = p_unk0x08;
	m_collisionWorld = p_unk0x08->m_unk0x068;
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

	m_flashBillboard = static_cast<GolBillboard*>(p_export->VTable0x30());
	DuskwindBananaRelic0x24* material = renderer->FindMaterialByName("ltflash");
	m_flashBillboard->VTable0x4c(material, g_lightningFlashWidth, g_lightningFlashHeight, g_lightningFlashDrawDistance);

	m_state = 1;
	FillJitterTable();
}

// FUNCTION: LEGORACERS 0x00454a70
void RacePowerupManager::LightningAction::AcquireSound()
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
void RacePowerupManager::LightningAction::Destroy()
{
	if (m_sound != NULL) {
		m_soundSource->ReleaseSound(m_soundResource);
		m_sound = NULL;
	}

	Deactivate();

	if (m_flashBillboard != NULL) {
		m_flashBillboard->VTable0x50();
		m_owner0x01c->m_golExport->VTable0x64(m_flashBillboard);
		m_flashBillboard = NULL;
	}

	m_beam.Destroy();
	m_state = 0;
	m_hitParticle = 0;
	m_source = 0;
}

// FUNCTION: LEGORACERS 0x00454b20
void RacePowerupManager::LightningAction::AdvanceJitter()
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
void RacePowerupManager::LightningAction::FillJitterTable()
{
	for (LegoU32 i = 0; i < 20; i++) {
		AdvanceJitter();
	}
}

// FUNCTION: LEGORACERS 0x00454bb0
void RacePowerupManager::LightningAction::RebuildBolt()
{
	LegoS32 index = static_cast<LegoS32>(m_jitterCursor) - 1;
	GolVec3* modelPosition = m_boltPoints;
	BeamMesh* field = &m_beam;
	RaceActionSource0x24* source = m_source;

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
void RacePowerupManager::LightningAction::Activate(RaceState::Racer* p_racer, ActionTarget* p_unk0x08)
{
	m_state = 2;
	m_stateTimerMs = 500;
	m_ownerRacer = p_racer;
	m_targetRacer = NULL;

	if (p_racer != NULL) {
		m_source = &p_racer->m_actionSource;
	}
	else {
		m_source = p_unk0x08->m_source;
	}

	m_crackleTimerMs = 0;
	if (m_sound != NULL) {
		m_sound->Play(TRUE);
	}
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00454d10
void RacePowerupManager::LightningAction::Deactivate()
{
	if (m_targetRacer != NULL) {
		m_targetRacer->EndSpinOut();
	}

	if (m_owner0x01c != NULL && m_hitParticle != NULL) {
		m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f30(m_hitParticle);
		m_hitParticle = NULL;
	}

	m_beam.SetColors(&g_lightningBaseColor, &g_lightningSecondaryColor, &g_lightningTertiaryColor);
	m_source = NULL;
	m_ownerRacer = NULL;
	m_targetRacer = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00454d70
void RacePowerupManager::LightningAction::Update(LegoU32 p_elapsedMs)
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
void RacePowerupManager::LightningAction::UpdateSound(LegoU32 p_elapsedMs)
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
		SoundVector* right = &m_source->m_right;
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
void RacePowerupManager::LightningAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_targetRacer != NULL) {
		m_flashBillboard->VTable0x08(m_boltPoints[3]);
		p_renderer->VTable0xb4(*m_flashBillboard);
	}

	m_beam.Draw(p_renderer);
}

// FUNCTION: LEGORACERS 0x00455060
void RacePowerupManager::LightningAction::AdvanceState()
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

		if (m_owner0x01c != NULL && m_hitParticle != NULL) {
			m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f30(m_hitParticle);
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
void RacePowerupManager::LightningAction::UpdateBoltPath()
{
	GolVec3 position = *m_source;
	position.m_z += g_lightningSourceHeightOffset;

	GolVec3 direction = m_source->m_right;
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
	GolBoundingVolume::Field0x0c record;
	LegoFloat scale = m_boltLength;
	scale *= g_ghostSpeedScale;
	scaledDirection.m_x = direction.m_x * scale;
	scaledDirection.m_y = direction.m_y * scale;
	scaledDirection.m_z = direction.m_z * scale;
	GolCameraBase::FUN_00404550(&position, &scaledDirection, &end);

	if (m_targetRacer != NULL) {
		m_targetRacer->m_unk0x018.m_unk0x044->VTable0x04(&end);

		direction.m_x = end.m_x - position.m_x;
		direction.m_y = end.m_y - position.m_y;
		direction.m_z = end.m_z - position.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		LegoFloat distance = static_cast<LegoFloat>(::sqrt(
			(position.m_z - end.m_z) * (position.m_z - end.m_z) + (position.m_y - end.m_y) * (position.m_y - end.m_y) +
			(position.m_x - end.m_x) * (position.m_x - end.m_x)
		));
		LegoFloat radius = m_targetRacer->m_unk0x018.m_unk0x004.FUN_10028710();
		if (distance > radius) {
			distance -= radius;
		}

		m_boltLength = distance * g_carBuildModelTextureCoordinateScale;
	}
	else {
		if (m_collisionWorld->FUN_0041f730(&position, &end, &record, &hit)) {
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
void RacePowerupManager::LightningAction::FindVictim()
{
	RaceState::Racer* racer;

	if (m_targetRacer != NULL) {
		return;
	}

	SoundVector position = *m_source;
	position.m_z += g_lightningSourceHeightOffset;

	RaceState* raceState = m_owner0x01c->m_raceState;
	racer = raceState->FUN_0043c6e0(&position, &m_source->m_right, g_unk0x004b157c, g_unk0x004c7604, g_unk0x004b1580);

	while (racer != NULL) {
		if (racer != m_ownerRacer) {
			GolVec3* start = &position;
			LegoS32 i = 0;
			GolVec3* segment = m_boltPoints;
			for (; i < sizeOfArray(m_boltPoints);) {
				GolVec3 hit;
				if (racer->m_unk0x018.IntersectSegment(start, segment, &hit)) {
					OnHitRacer(racer);
					break;
				}

				start = segment;
				i++;
				segment++;
			}
		}

		racer =
			raceState
				->FUN_0043c7f0(racer, &position, &m_source->m_right, g_unk0x004b157c, g_unk0x004c7604, g_unk0x004b1580);
	}
}

// FUNCTION: LEGORACERS 0x00455440
void RacePowerupManager::LightningAction::OnHitRacer(RaceState::Racer* p_racer)
{
	LegoU32 state = m_state;

	if (state == c_stateSustain) {
		RaceState::Racer* racer = p_racer;
		if (racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			racer->PlayReaction(TRUE);
			racer->AbsorbShieldHit();
			return;
		}

		if (!(racer->m_unk0x3e8.m_flags0x6c0 & c_racerFlags0xaa8Bit7)) {
			RaceState::Racer::Field0x3e8* field0x3e8 = &racer->m_unk0x3e8;
			GolVec3 direction = field0x3e8->m_unk0x168;
			racer->StartSpinOut();

			field0x3e8->m_unk0x008.m_x = 0.0f;
			field0x3e8->m_unk0x008.m_y = 0.0f;
			field0x3e8->m_unk0x008.m_z = 0.0f;

			GolVec3 impulse;
			impulse.m_x = direction.m_x * g_lightningImpulseScale;
			impulse.m_y = direction.m_y * g_lightningImpulseScale;
			impulse.m_z = direction.m_z * g_lightningImpulseScale + g_lightningLaunchImpulse;

			field0x3e8->VTable0x1c(&impulse, &impulse);

			RaceState::Racer::Field0x018* racerField0x018 = &racer->m_unk0x018;
			ColorTransform0x20 transform;
			transform.m_redOffset = c_colorOffset0xe1;
			transform.m_redShift = 0;
			transform.m_grnOffset = c_colorOffset0xe1;
			transform.m_grnShift = 0;
			transform.m_bluOffset = c_colorOffset0xff;
			transform.m_bluShift = 0;
			transform.m_alpOffset = 0;
			transform.m_alpShift = 0;
			racerField0x018->FlashColor(&transform, c_flashDurationMs);

			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			racer->PlayReaction(FALSE);
			racer->DropWhiteBrick();
			racerField0x018->m_unk0x384 |= c_racerField0x018Flags0x384Bit1;

			m_shockTimerMs = 0;
			m_targetRacer = racer;
			m_beam.SetColors(&g_lightningHitColor, &g_lightningHitColor, &g_lightningHitColor);

			CutsceneAnimation* cutsceneAnimation = m_owner0x01c->m_cutsceneAnimation0x040;
			if (m_hitParticle != NULL) {
				cutsceneAnimation->FUN_00489f30(m_hitParticle);
			}

			m_hitParticle = cutsceneAnimation->FUN_00489d70("lghthit", NULL, NULL, NULL);

			SoundVector position;
			racerField0x018->m_unk0x044->VTable0x04(&position);
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
void RacePowerupManager::LightningAction::GetProjectilePosition(GolVec3* p_position)
{
	*p_position = m_boltPoints[3];
}

// FUNCTION: LEGORACERS 0x00455640
void RacePowerupManager::LightningAction::GetProjectileVelocity(GolVec3* p_velocity)
{
	p_velocity->m_x = 0.0f;
	p_velocity->m_y = 0.0f;
	p_velocity->m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00455660
void RacePowerupManager::LightningAction::UpdateHitParticle()
{
	if (m_hitParticle == NULL) {
		return;
	}

	if (m_targetRacer == NULL) {
		m_owner0x01c->m_cutsceneAnimation0x040->FUN_00489f30(m_hitParticle);
		m_hitParticle = NULL;
		return;
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolVec3 direction;
	direction.m_x = -m_source->m_right.m_x;
	direction.m_y = -m_source->m_right.m_y;
	direction.m_z = -m_source->m_right.m_z;

	if (m_hitParticle->m_unk0x00 != NULL) {
		m_hitParticle->m_unk0x00->FUN_00489660(&m_boltPoints[3]);
	}

	if (m_hitParticle->m_unk0x00 != NULL) {
		m_hitParticle->m_unk0x00->FUN_00489540(&direction, &up);
	}
}

// FUNCTION: LEGORACERS 0x00455710
RacePowerupManager::MagnetAction::MagnetAction()
{
	FUN_004557e0();
}

// FUNCTION: LEGORACERS 0x00455770
RacePowerupManager::MagnetAction::~MagnetAction()
{
	FUN_004557c0();
}

// FUNCTION: LEGORACERS 0x004557c0
void RacePowerupManager::MagnetAction::FUN_004557c0()
{
	Deactivate();
	FUN_004557e0();
}

// FUNCTION: LEGORACERS 0x004557e0
void RacePowerupManager::MagnetAction::FUN_004557e0()
{
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x38 = 0;
	m_unk0x70 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;
	m_flags0x80 = 0;
	m_unk0x2c.m_x = 0.0f;
	m_unk0x2c.m_y = 0.0f;
	m_unk0x2c.m_z = 0.0f;
}

// FUNCTION: LEGORACERS 0x00455810
void RacePowerupManager::MagnetAction::Initialize(
	RacePowerupManager* p_unk0x04,
	RaceState* p_raceState,
	RaceSessionField0x32b4* p_unk0x0c,
	undefined4,
	GolExport*,
	GolD3DRenderDevice*,
	undefined4
)
{
	m_unk0x38 = p_unk0x04;
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_unk0x0c;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00455830
void RacePowerupManager::MagnetAction::Activate(
	RaceState::Racer* p_racer,
	GolAnimatedEntity* p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10
)
{
	m_unk0x3c = m_unk0x38->AllocateEffectEntity();
	if (m_unk0x3c == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x40 = m_unk0x38->AllocateEffectEntity();
	if (m_unk0x40 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x44 = m_unk0x38->AllocateEffectEntity();
	if (m_unk0x44 == NULL) {
		m_state = 6;
		return;
	}

	m_ownerRacer = p_racer;
	m_state = 2;
	m_stateTimerMs = c_timer0x4e20;

	m_unk0x3c->FUN_0040d550(
		p_unk0x08->GetModel(0),
		p_unk0x08->VTable0x58(0),
		p_unk0x08->GetModelPart(0),
		p_unk0x08->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x08->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x08->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x08->GetModelPart(i);
			m_unk0x3c->FUN_10023940(model, p_unk0x08->VTable0x58(i), modelPart, modelDistance);
		}
	}

	m_unk0x40->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x0c->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x0c->GetModelPart(i);
			m_unk0x40->FUN_10023940(model, p_unk0x0c->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x40->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x40->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x40->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x40->FUN_00411730(p_unk0x0c->FUN_004116f0());

	m_unk0x44->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model != NULL) {
			LegoFloat modelDistance = p_unk0x10->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x10->GetModelPart(i);
			m_unk0x44->FUN_10023940(model, p_unk0x10->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x44->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x44->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x44->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x44->FUN_00411730(p_unk0x10->FUN_004116f0());
}

// FUNCTION: LEGORACERS 0x00455a90
void RacePowerupManager::MagnetAction::Deactivate()
{
	if (m_unk0x70 != NULL) {
		m_soundSource->ReleaseSound(m_soundResource70);
		m_unk0x70 = NULL;
	}

	if (m_unk0x44 != NULL) {
		m_unk0x44->VTable0x54();
		m_unk0x38->ReleaseEffectEntity(m_unk0x44);
		m_unk0x44 = NULL;
	}

	if (m_unk0x40 != NULL) {
		m_unk0x40->VTable0x54();
		m_unk0x38->ReleaseEffectEntity(m_unk0x40);
		m_unk0x40 = NULL;
	}

	if (m_unk0x3c != NULL) {
		m_unk0x3c->VTable0x54();
		m_unk0x38->ReleaseEffectEntity(m_unk0x3c);
		m_unk0x3c = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;

	if (m_unk0x78 != NULL) {
		m_unk0x78->FUN_0043a1a0();
		m_unk0x78 = NULL;
	}

	m_unk0x7c = NULL;
	m_flags0x80 = 0;
	m_unk0x2c.m_x = 0.0f;
	m_unk0x2c.m_y = 0.0f;
	m_unk0x2c.m_z = 0.0f;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00455b40
void RacePowerupManager::MagnetAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == 6) {
		return;
	}

	if (m_state == 2 && m_stateTimerMs == c_timer0x4e20) {
		FUN_004560b0();
	}

	PowerupActionBase::Update(p_elapsedMs);

	if (m_unk0x78 == NULL && m_unk0x7c == NULL) {
		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		m_unk0x3c->VTable0x40(m_unk0x2c, up);
	}
	else {
		GolAnimatedEntity* racerEntity;
		if (m_unk0x78 != NULL) {
			racerEntity = m_unk0x78->m_unk0x018.m_unk0x044;
		}
		else {
			racerEntity = m_unk0x7c->m_unk0x018.m_unk0x044;
		}

		GolVec3 racerPosition;
		racerEntity->VTable0x04(&racerPosition);

		GolVec3 modelPosition;
		m_unk0x3c->VTable0x04(&modelPosition);

		GolVec3 direction;
		direction.m_x = modelPosition.m_x - racerPosition.m_x;
		direction.m_y = modelPosition.m_y - racerPosition.m_y;
		direction.m_z = modelPosition.m_z - racerPosition.m_z;
		GolMath::NormalizeVector3(direction, &direction);

		LegoFloat zero = 0.0f;
		GolVec3 side;
		side.m_x = zero - direction.m_y;
		side.m_y = direction.m_x - zero;
		side.m_z = zero;

		GolVec3 up;
		up.m_x = side.m_y * direction.m_z - side.m_z * direction.m_y;
		up.m_y = side.m_z * direction.m_x - side.m_x * direction.m_z;
		up.m_z = side.m_x * direction.m_y - side.m_y * direction.m_x;
		m_unk0x3c->FUN_00410b00(direction, up);

		if (m_unk0x78 != NULL) {
			if (m_unk0x78->m_unk0x3e8.m_unk0x604 <= 0.002f) {
				m_flags0x80 |= c_flags0x80Bit0;

				if (!(m_unk0x78->m_unk0xd04 & c_racerFlags0xd04Bit3)) {
					if (m_stateTimerMs > c_timer0x03e8) {
						m_stateTimerMs = c_timer0x03e8;
					}
				}

				m_unk0x78->FUN_00439570();
			}

			if (m_unk0x78->m_unk0x3e8.m_unk0x744 == 0 && (m_flags0x80 & c_flags0x80Bit0) &&
				!(m_flags0x80 & c_flags0x80Bit1)) {
				modelPosition.m_z -= 30.0f;
				direction.m_x = modelPosition.m_x - racerPosition.m_x;
				direction.m_y = modelPosition.m_y - racerPosition.m_y;
				direction.m_z = modelPosition.m_z - racerPosition.m_z;
				GolMath::NormalizeVector3(direction, &direction);

				m_unk0x78->m_unk0x3e8.VTable0x20(&direction, static_cast<LegoS32>(p_elapsedMs) * 1.0f);

				if (m_unk0x78->m_unk0x3e8.m_unk0x604 <= 0.002f) {
					direction.m_x = racerPosition.m_x - modelPosition.m_x;
					direction.m_y = racerPosition.m_y - modelPosition.m_y;
					direction.m_z = racerPosition.m_z - modelPosition.m_z;
					LegoFloat distanceSquared =
						direction.m_x * direction.m_x + direction.m_y * direction.m_y + direction.m_z * direction.m_z;

					if (distanceSquared <= 100.0f) {
						m_flags0x80 |= c_flags0x80Bit1;
					}
				}
			}

			if (m_unk0x78->m_unk0xc70.m_unk0x014 & c_racerField0xc70Flags0x014Bit0) {
				m_unk0x38->FUN_0045b690(m_unk0x78);
				m_unk0x78->FUN_00439730();
			}
		}
		else {
			modelPosition.m_z -= 30.0f;
			direction.m_x = modelPosition.m_x - racerPosition.m_x;
			direction.m_y = modelPosition.m_y - racerPosition.m_y;
			direction.m_z = modelPosition.m_z - racerPosition.m_z;
			GolMath::NormalizeVector3(direction, &direction);

			m_unk0x7c->m_unk0x3e8.VTable0x20(&direction, static_cast<LegoS32>(p_elapsedMs) * 1.0f);
			m_unk0x7c = NULL;
		}
	}

	if (m_state == 4) {
		m_unk0x3c->SetUnk0x58AndInvalidateRadius(static_cast<LegoS32>(m_stateTimerMs) * 0.001f);
	}

	m_unk0x40->CopyOrientationFrom(*m_unk0x3c);
	m_unk0x44->CopyOrientationFrom(*m_unk0x3c);
	m_unk0x3c->VTable0x10(p_elapsedMs);
	m_unk0x40->VTable0x10(p_elapsedMs);
	m_unk0x44->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x00455ed0
void RacePowerupManager::MagnetAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state != 6) {
		p_renderer->VTable0x94(m_unk0x3c);
	}
}

// FUNCTION: LEGORACERS 0x00455ef0
void RacePowerupManager::MagnetAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 6) {
		return;
	}

	if (m_state == 4) {
		LegoFloat alphaScale = static_cast<LegoS32>(m_stateTimerMs) * 0.001f;
		LegoS32 alpha = static_cast<LegoS32>(alphaScale * g_unk0x004b1620);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_unk0x44->VTable0x1c(*p_renderer);
	m_unk0x40->VTable0x1c(*p_renderer);

	if (m_state == 4) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x00455f50
void RacePowerupManager::MagnetAction::AdvanceState()
{
	if (m_state == 4) {
		m_state = 6;
		return;
	}

	m_state = 4;
	m_stateTimerMs = c_timer0x03e8;

	SoundVector position;
	m_unk0x3c->VTable0x04(&position);
	m_soundSource->PlaySpatialSoundById(c_sound0x4a, &position, g_unk0x004b15dc, g_unk0x004b15e0, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x00455fb0
void RacePowerupManager::MagnetAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == 4) {
		return;
	}

	if (m_state == 2) {
		m_state = 3;
		m_stateTimerMs = c_timer0x0fa0;
	}

	if (m_state == 3) {
		SoundVector modelPosition;
		GolVec3 racerPosition;
		m_unk0x3c->VTable0x04(&modelPosition);
		modelPosition.m_z -= g_unk0x004b15f0;
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&racerPosition);

		GolVec3 delta;
		delta.m_x = modelPosition.m_x - racerPosition.m_x;
		delta.m_y = modelPosition.m_y - racerPosition.m_y;
		delta.m_z = modelPosition.m_z - racerPosition.m_z;
		LegoFloat distanceSquared = delta.m_x * delta.m_x + delta.m_y * delta.m_y + delta.m_z * delta.m_z;

		if (distanceSquared <= g_unk0x004b15ec) {
			if (m_unk0x78 == NULL) {
				m_unk0x78 = p_racer;
				p_racer->FUN_0043a130();
				m_unk0x7c = NULL;
				m_soundSource
					->PlaySpatialSoundById(c_sound0x23, &modelPosition, g_unk0x004b15dc, g_unk0x004b15e0, 1.0f, 1.0f);
				p_racer->PlayReaction(FALSE);
			}
		}
		else if (m_unk0x7c == NULL) {
			m_unk0x7c = p_racer;
		}
	}
}

// FUNCTION: LEGORACERS 0x004560b0
void RacePowerupManager::MagnetAction::FUN_004560b0()
{
	SoundVector position;
	FUN_00456360(m_ownerRacer, &position, NULL);

	position.m_z += 30.0f;
	m_unk0x3c->VTable0x08(position);
	position.m_z -= 30.0f;
	m_unk0x40->CopyPositionFrom(*m_unk0x3c);
	m_unk0x44->CopyPositionFrom(*m_unk0x3c);

	m_unk0x3c->SetFlags(m_unk0x3c->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x3c->FUN_0040dad0(0);
	m_unk0x40->SetFlags(m_unk0x40->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x40->FUN_0040dad0(0);
	m_unk0x44->SetFlags(m_unk0x44->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x44->FUN_0040dad0(0);

	if (m_ownerRacer->m_unk0xcc4 != NULL) {
		m_unk0x2c = m_ownerRacer->m_unk0xcc4->m_unk0x00;
	}
	else {
		m_unk0x2c.m_x = 1.0f;
		m_unk0x2c.m_y = 0.0f;
		m_unk0x2c.m_z = 0.0f;
	}

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_unk0x3c->VTable0x40(m_unk0x2c, up);

	m_unk0x48.VTable0x08(position);
	m_unk0x48.FUN_10026fa0(10.0f);
	m_ownerRacer->m_unk0x3e8.FUN_00429cf0(0.0015f, 150);
	m_soundSource->PlaySpatialSoundById(c_sound0x21, &position, 30.0f, 300.0f, 1.0f, 1.0f);

	m_unk0x70 = m_soundSource->AcquireSoundById(c_sound0x22);
	m_unk0x70->Play(TRUE);
	m_unk0x70->SetDistanceRange(30.0f, 300.0f);
	m_unk0x70->SetPosition(position);
	m_unk0x70->ClearVelocity();

	m_state = 2;
	m_stateTimerMs = c_timer0x4e20;

	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &m_unk0x48;
	m_collisionEvent = m_raceState0x018->GetEventQueue()->FUN_0042fb50(this, &descriptor);
}

// FUNCTION: LEGORACERS 0x004562d0
RacePowerupManager::HazardActionBase::HazardActionBase()
{
	m_raceState0x018 = NULL;
	m_collisionEvent = 0;
	m_collisionWorld = 0;
	m_unk0x024 = 0;
	m_ownerRacer = 0;
}

// FUNCTION: LEGORACERS 0x00456320
void RacePowerupManager::HazardActionBase::VTable0x00(LegoEventQueue::CallbackData* p_param)
{
	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_param->m_data);
	if (racer != m_ownerRacer) {
		if (racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			racer->AbsorbShieldHit();
			if (m_level < 3) {
				m_state = 6;
			}
		}
		else {
			OnHitRacer(racer);
		}
	}
}

// STUB: LEGORACERS 0x00456360
void RacePowerupManager::HazardActionBase::FUN_00456360(
	RaceState::Racer* p_racer,
	GolVec3* p_position,
	GolBoundingVolume::Field0x0c* p_record
)
{
	GolVec3 start;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&start);

	GolVec3 verticalOffset;
	verticalOffset.Clear();
	verticalOffset.m_z = g_unk0x004b162c;
	GolVec3 end;
	end = start - verticalOffset;

	GolBoundingVolume::Field0x0c record;
	if (p_record == NULL) {
		p_record = &record;
	}

	if (m_collisionWorld->FUN_0041f4d0(&start, &end, p_record, p_position, NULL)) {
		verticalOffset.Clear();
		verticalOffset.m_z = g_unk0x004b1628;
		*p_position += verticalOffset;
	}
	else {
		*p_position = start;
	}
}

// FUNCTION: LEGORACERS 0x0044f570 FOLDED
LegoS32 RacePowerupManager::HazardActionBase::GetBrickColor()
{
	return c_brickColorYellow;
}

// FUNCTION: LEGORACERS 0x00456430
RacePowerupManager::HomingMissileAction::HomingMissileAction()
{
	m_activeProjectile = 0;
	m_activeProjectile = &m_projectile;
	m_unk0x21c = 0;
	m_projectile.m_unk0x0f4 = 0;
}

// FUNCTION: LEGORACERS 0x004564b0
RacePowerupManager::HomingMissileAction::~HomingMissileAction()
{
	FUN_00456540();
}

// FUNCTION: LEGORACERS 0x00456510
void RacePowerupManager::HomingMissileAction::Initialize(GolExport** p_unk0x04, RaceSessionField0x32b4* p_unk0x08)
{
	if (m_state != 0) {
		FUN_00456540();
	}

	m_golExportPtr = p_unk0x04;
	m_collisionWorld = p_unk0x08;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x00456540
void RacePowerupManager::HomingMissileAction::FUN_00456540()
{
	Deactivate();
	m_state = 0;
	m_unk0x21c = 0;
}

// FUNCTION: LEGORACERS 0x00456560
void RacePowerupManager::HomingMissileAction::Activate(
	GolAnimatedEntity* p_unk0x04,
	GolAnimatedEntity*,
	RaceState::Racer* p_racer,
	LegoU32 p_unk0x10
)
{
	m_state = 2;
	m_stateTimerMs = 3000;
	m_unk0x220 = p_unk0x10;
	m_ownerRacer = p_racer;
	m_targetRacer = NULL;

	GolAnimatedEntity* projectile = &m_unk0x128;
	projectile->FUN_0040d550(
		p_unk0x04->GetModel(0),
		p_unk0x04->VTable0x58(0),
		p_unk0x04->GetModelPart(0),
		p_unk0x04->GetModelDistance(0)
	);

	SoundVector position;
	RaceState::Racer::Field0x018* racerEntities = &m_ownerRacer->m_unk0x018;
	racerEntities->m_unk0x044->VTable0x04(&position);
	projectile->VTable0x08(position);

	m_ownerRacer->m_unk0x3e8.m_unk0x13c->CopyOrientationTo(&projectile->GetOrientation());
	projectile->SetFlags(projectile->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	projectile->FUN_0040dad0(p_unk0x10);
	projectile->SetFlags(projectile->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);

	m_soundSource->PlaySpatialSoundById(c_sound0x33, &position, g_unk0x004b165c, g_unk0x004b1660, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x00456680
void RacePowerupManager::HomingMissileAction::FUN_00456680()
{
	GolVec3 position;
	{
		RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
		racerField->m_unk0x044->VTable0x04(&position);
	}

	GolVec3 direction;
	m_ownerRacer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	RaceState* raceState = m_owner0x01c->m_raceState;
	LegoU32 i = 0;
	m_targetRacer = raceState->FUN_0043c6e0(&position, &direction, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);

	for (; i < m_unk0x220; i++) {
		if (m_targetRacer == NULL) {
			break;
		}

		m_targetRacer =
			raceState
				->FUN_0043c7f0(m_targetRacer, &position, &direction, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);
	}

	PowerupProjectile::Params projectileParams;
	projectileParams.m_worldEntity = &m_unk0x128;
	projectileParams.m_collisionWorld = m_collisionWorld;
	projectileParams.m_gravity = g_unk0x004b1670;
	projectileParams.m_eventQueue = m_owner0x01c->m_raceState->GetEventQueue();
	projectileParams.m_targetOffset.m_x = 0.0f;
	projectileParams.m_targetOffset.m_y = 0.0f;
	projectileParams.m_targetOffset.m_z = 0.0f;
	projectileParams.m_speed = g_unk0x004b166c;
	projectileParams.m_lifetimeMs = c_timer0x157c;
	projectileParams.m_launchHeight = g_unk0x004b1678;

	if (m_targetRacer == NULL) {
		GolVec3 velocity;
		velocity.m_x = 0.0f;
		velocity.m_y = 0.0f;
		velocity.m_z = 0.0f;

		GolVec3 scaledDirection;
		scaledDirection.m_x = direction.m_x * g_unk0x004b1674;
		scaledDirection.m_y = direction.m_y * g_unk0x004b1674;
		scaledDirection.m_z = direction.m_z * g_unk0x004b1674;

		GolVec3 target;
		target.m_x = position.m_x + scaledDirection.m_x;
		target.m_y = position.m_y + scaledDirection.m_y;
		target.m_z = position.m_z + scaledDirection.m_z + g_unk0x004b1678;

		if (m_unk0x220 == 0) {
			target.m_x += direction.m_y * 150.0f;
			target.m_y += (-direction.m_x) * 150.0f;
		}
		else if (m_unk0x220 == 2) {
			target.m_x += (-direction.m_y) * 150.0f;
			target.m_y += direction.m_x * 150.0f;
		}

		PowerupProjectile* projectile = &m_projectile;
		projectile->LaunchAtPoint(&projectileParams, m_ownerRacer, &target, &velocity, FALSE);
	}
	else {
		PowerupProjectile* projectile = &m_projectile;
		projectile->LaunchAtRacer(&projectileParams, m_ownerRacer, m_targetRacer, FALSE, FALSE);
	}

	m_projectile.m_maxSpiralAmplitude = 4.0f;
	m_projectile.m_spiralRate = 10.0f;
	m_projectile.StartHoming();
}

// FUNCTION: LEGORACERS 0x004568a0
void RacePowerupManager::HomingMissileAction::Deactivate()
{
	m_projectile.Deactivate();
	m_unk0x128.VTable0x54();
	m_state = 1;
	m_stateTimerMs = 0;

	if (m_owner0x01c != NULL && m_unk0x21c != NULL) {
		m_owner0x01c->m_trailManager->FUN_00493a10(m_unk0x21c);
		m_unk0x21c = NULL;
	}
}

// STUB: LEGORACERS 0x004568f0
void RacePowerupManager::HomingMissileAction::Update(LegoU32 p_elapsedMs)
{
	GolVec3 direction;
	GolVec3 up;

	if (m_state == c_state0x02) {
		m_unk0x128.VTable0x10(p_elapsedMs);
		if (m_unk0x128.FUN_0040e360()) {
			AdvanceState();
		}
		else {
			GolVec3 position;
			RaceState::Racer::Field0x018* racerField = &m_ownerRacer->m_unk0x018;
			racerField->m_unk0x044->VTable0x04(&position);
			m_unk0x128.VTable0x08(position);
			m_unk0x128.CopyOrientationFrom(*m_ownerRacer->m_unk0x3e8.m_unk0x13c);
			return;
		}
	}

	if (m_state == c_state0x03) {
		m_unk0x128.VTable0x10(p_elapsedMs);
		m_projectile
			.UpdateTargeting(p_elapsedMs, m_owner0x01c->m_raceState, g_unk0x004b1684, g_unk0x004b1688, g_unk0x004b168c);

		LegoS32 projectileState = m_projectile.Update(p_elapsedMs);
		if (projectileState != PowerupProjectile::c_stateFlying) {
			SoundVector position;
			GolVec3& positionBase = position;
			positionBase = m_projectile.GetHitPosition();

			LegoBool32 skipBurst = FALSE;
			if (projectileState == PowerupProjectile::c_stateHitRacer) {
				RaceState::Racer* target = m_projectile.GetHitRacer();
				if ((target->m_unk0xd04 & c_racerFlags0xd04Bit0) && target->m_shieldLevel >= 2) {
					skipBurst = TRUE;
				}

				OnHitRacer(target);
			}
			else {
				m_soundSource
					->PlaySpatialSoundById(c_sound0x32, &position, g_unk0x004b1664, g_unk0x004b1668, 1.0f, 1.0f);
			}

			if (!skipBurst) {
				GolVec3 hitNormal = m_projectile.GetHitNormal();
				LegoBool32 upwardHit = FALSE;
				if (projectileState == PowerupProjectile::c_stateHitWorld && hitNormal.m_z > g_scarNormalThreshold) {
					upwardHit = TRUE;
				}

				m_owner0x01c->FUN_0045b4d0(&position, upwardHit, m_ownerRacer);
				if (projectileState == PowerupProjectile::c_stateHitRacer &&
					!(m_projectile.GetHitRacer()->m_unk0xd04 & c_racerFlags0xd04Bit0)) {
					m_projectile.GetVelocity(&direction);
					direction.m_x = -direction.m_x;
					direction.m_y = -direction.m_y;
					direction.m_z = 0.0f;
					GolMath::NormalizeVector3(direction, &direction);
					m_owner0x01c->FUN_0045b550(&position, &direction, m_projectile.GetHitRacer());
				}

				AdvanceState();
			}

			return;
		}

		m_unk0x128.VTable0x48(&direction, &up);
		direction = m_projectile.m_direction;
		m_unk0x128.VTable0x40(direction, up);

		GolVec3 position;
		m_unk0x128.VTable0x04(&position);

		if (m_unk0x21c != NULL) {
			GolVec3 velocity;
			m_projectile.GetVelocity(&velocity);

			GolVec2 perpendicular;
			perpendicular.m_x = velocity.m_y;
			perpendicular.m_y = -velocity.m_x;
			if (perpendicular.m_y != 0.0f || perpendicular.m_x != 0.0f) {
				GolMath::NormalizeVector2(perpendicular, &perpendicular);
				perpendicular.m_x *= 1.0f;
				perpendicular.m_y *= 1.0f;

				GolVec3 positions[4];
				positions[0].m_x = position.m_x - perpendicular.m_x * 0.5f;
				positions[0].m_y = position.m_y - perpendicular.m_y * 0.5f;
				positions[0].m_z = position.m_z + 1.0f * 0.5f;
				positions[1].m_x = positions[0].m_x;
				positions[1].m_y = positions[0].m_y;
				positions[1].m_z = positions[0].m_z - 1.0f;
				positions[2].m_x = positions[0].m_x + perpendicular.m_x;
				positions[2].m_y = positions[0].m_y + perpendicular.m_y;
				positions[2].m_z = positions[1].m_z;
				positions[3].m_x = positions[2].m_x;
				positions[3].m_y = positions[2].m_y;
				positions[3].m_z = positions[1].m_z + 1.0f;

				m_unk0x21c->FUN_00492ee0(p_elapsedMs, positions, position);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00456ce0
void RacePowerupManager::HomingMissileAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x02) {
		p_renderer->VTable0x94(&m_unk0x128);
	}
	else if (m_state == c_state0x03) {
		GolSceneNode* node = m_unk0x128.VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(c_transformNodeIndex1);

		GolVec3 position;
		position.m_x = 0.0f;
		position.m_y = 0.0f;
		position.m_z = 0.0f;
		transform->SetPosition(&position);

		GolVec3 direction;
		direction.m_x = 1.0f;
		direction.m_y = 0.0f;
		direction.m_z = 0.0f;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;
		transform->VTable0x28(&direction, &up);

		p_renderer->VTable0x94(&m_unk0x128);
	}
}

// FUNCTION: LEGORACERS 0x00456db0
void RacePowerupManager::HomingMissileAction::AdvanceState()
{
	switch (m_state) {
	case c_state0x02: {
		m_state = c_state0x03;
		m_stateTimerMs = c_timer0x157c;
		m_unk0x128.VTable0x5c(0);

		GolAnimatedEntity* animatedEntity = &m_unk0x128;
		GolSceneNode* node = animatedEntity->VTable0x58(0);
		GolTransformBase* transform = node->VTable0x18(c_transformNodeIndex1);

		GolVec3 position;
		transform->GetPosition(&position);

		GolVec3 up;
		transform->GetUp(&up);

		GolVec3 right;
		transform->GetRight(&right);

		LegoFloat scale = animatedEntity->GetModel(0)->GetScale() * animatedEntity->GetUnk0x58();
		position.m_x *= scale;
		position.m_y *= scale;
		position.m_z *= scale;

		GolVec3 worldPosition;
		animatedEntity->VTable0x2c(position, &worldPosition);

		GolVec3 worldBasis[2];
		animatedEntity->VTable0x34(up, &worldBasis[1]);
		animatedEntity->VTable0x34(right, &worldBasis[0]);

		animatedEntity->VTable0x08(worldPosition);
		animatedEntity->VTable0x40(worldBasis[1], worldBasis[0]);
		animatedEntity->VTable0x4c(0);

		LegoU32 flags = animatedEntity->GetFlags();
		flags &= ~GolAnimatedEntity::c_flagPartAnimation;
		animatedEntity->SetFlags(flags);

		FUN_00456680();

		RaceTrailManager::Trail::Params params;
		params.m_unk0x04 = 4;
		params.m_unk0x08 = 4;
		RacePowerupManager* owner = m_owner0x01c;
		params.m_unk0x00 = 0x190;
		params.m_unk0x0c = 1;
		params.m_unk0x10 = 0;
		params.m_unk0x14 = 0.1f;
		params.m_unk0x18 = 0.0f;

		RaceTrailManager* trailManager = owner->m_trailManager;
		m_unk0x21c = trailManager->FUN_004939b0(&params);
		if (m_unk0x21c != NULL) {
			m_unk0x21c->FUN_00492ab0(&g_unk0x004c1c64);
			DuskwindBananaRelic0x24* material = m_owner0x01c->m_renderer->FindMaterialByName("mslstrk");
			if (material != NULL) {
				m_unk0x21c->FUN_00492a90(m_owner0x01c->m_renderer, material);
			}
		}
		break;
	}
	case c_state0x03:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		m_projectile.CancelCollisionEvent();
		if (m_unk0x21c != NULL) {
			m_owner0x01c->m_trailManager->FUN_00493a10(m_unk0x21c);
			m_unk0x21c = NULL;
		}
		break;
	case c_state0x04:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		break;
	}
}

// FUNCTION: LEGORACERS 0x00456fa0
void RacePowerupManager::HomingMissileAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == c_state0x03) {
		if (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit0) {
			p_racer->PlayReaction(TRUE);
			p_racer->AbsorbShieldHit();
			if (p_racer->m_shieldLevel >= 2) {
				m_projectile.Deflect(p_racer);
				m_ownerRacer = p_racer;
			}
		}
		else {
			p_racer->m_unk0x3e8.VTable0x24(2.0f, 0.007f, 0);

			if (m_ownerRacer != NULL) {
				m_ownerRacer->PlayReaction(TRUE);
			}

			p_racer->PlayReaction(FALSE);
			p_racer->DropWhiteBrick();
			p_racer->m_unk0x018.m_unk0x384 |= c_racerField0x018Flags0x384Bit1;

			SoundVector position;
			p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
			m_soundSource->PlaySpatialSoundById(c_sound0x32, &position, g_unk0x004b1664, g_unk0x004b1668, 1.0f, 1.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x00457080
RacePowerupManager::OilSlickAction::OilSlickAction()
{
	m_manager = 0;
	m_unk0x058 = 0;
	m_unk0x05c = 0;
	m_unk0x060 = 0;
	m_unk0x18c = 0;
}

// FUNCTION: LEGORACERS 0x00457100
RacePowerupManager::OilSlickAction::~OilSlickAction()
{
	FUN_00457170();
}

// FUNCTION: LEGORACERS 0x00457170
void RacePowerupManager::OilSlickAction::FUN_00457170()
{
	Deactivate();
	m_unk0x064.FUN_004149f0();
	m_unk0x180.Clear();
	m_manager = 0;
	m_unk0x058 = 0;
	m_unk0x05c = 0;
	m_unk0x060 = 0;
	m_unk0x18c = 0;
}

// FUNCTION: LEGORACERS 0x004571b0
void RacePowerupManager::OilSlickAction::Initialize(
	RacePowerupManager* p_unk0x04,
	RaceState* p_raceState,
	GolCollidableEntity* p_unk0x0c,
	RaceSessionField0x32b4* p_unk0x10,
	CutsceneAnimation* p_unk0x14,
	GolRenderDevice* p_renderer,
	GolExport* p_export
)
{
	m_manager = p_unk0x04;
	m_raceState0x018 = p_raceState;
	m_collisionWorld = p_unk0x10;
	m_unk0x18c = p_unk0x0c;
	m_unk0x05c = p_unk0x14;
	m_state = 1;

	m_unk0x180.Initialize(p_renderer, 1);
	m_unk0x180.AssignEntryByName(0, "oilslck");
	m_unk0x064.FUN_00414950(p_export, p_renderer, 0x10);
	m_unk0x064.GetUnk0x010().EnableFlagBit1();
}

// FUNCTION: LEGORACERS 0x00457230
void RacePowerupManager::OilSlickAction::Activate(RaceState::Racer* p_racer)
{
	m_state = 2;
	m_ownerRacer = p_racer;
	m_stateTimerMs = 0;
}

// FUNCTION: LEGORACERS 0x00457250
void RacePowerupManager::OilSlickAction::Deactivate()
{
	if (m_unk0x060 != NULL) {
		m_unk0x05c->FUN_00489f30(m_unk0x060);
		m_unk0x060 = NULL;
	}

	if (m_unk0x058 != NULL) {
		m_soundSource->ReleaseSound(m_sound058);
		m_unk0x058 = NULL;
	}

	if (m_collisionEvent != NULL) {
		m_collisionEvent->m_active = 0;
		m_collisionEvent = NULL;
	}

	m_ownerRacer = NULL;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x004572a0
void RacePowerupManager::OilSlickAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_state0x06) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);

	if (m_unk0x060 != NULL) {
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoS32 phase = static_cast<LegoS32>(g_randomTable[g_randomTableIndex]) % c_randomPhaseRange;
		g_randomTableIndex = (g_randomTableIndex + 1) & c_randomTableMask;
		LegoS32 distance = static_cast<LegoU32>(g_randomTable[g_randomTableIndex]) % c_randomBubbleOffsetRange;

		LegoFloat angle = static_cast<LegoFloat>(phase) * g_unk0x004b1704;
		LegoFloat offset = static_cast<LegoFloat>(distance);
		GolVec3 position;
		m_worldEntity.VTable0x04(&position);
		CutsceneParticleRef* particleRef = m_unk0x060;
		position.m_x += static_cast<LegoFloat>(::sin(angle)) * offset;
		position.m_y += static_cast<LegoFloat>(::cos(angle)) * offset;

		if (particleRef->m_unk0x00 != NULL) {
			particleRef->m_unk0x00->FUN_00489660(&position);
		}
	}
}

// FUNCTION: LEGORACERS 0x00457380
void RacePowerupManager::OilSlickAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x03) {
		m_unk0x064.FUN_00415a40(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004573a0
void RacePowerupManager::OilSlickAction::AdvanceState()
{
	switch (m_state) {
	case c_state0x02:
		break;
	case c_state0x03:
		m_state = c_state0x06;
		m_stateTimerMs = 0;
		return;
	default:
		return;
	}

	SoundVector position;
	FUN_00456360(m_ownerRacer, &position, NULL);
	m_worldEntity.VTable0x08(position);
	m_worldEntity.FUN_10026fa0(3.0f);
	m_ownerRacer->m_unk0x3e8.FUN_00429cf0(0.0015f, 150);
	m_soundSource->PlaySpatialSoundById(c_sound0x2e, &position, g_unk0x004b16c0, g_unk0x004b16c4, 1.0f, 1.0f);

	m_unk0x058 = m_soundSource->AcquireSoundById(c_sound0x30);
	if (m_unk0x058 != NULL) {
		m_unk0x058->Play(TRUE);

		LegoFloat maxDistance = g_unk0x004b16c4;
		LegoFloat minDistance = g_unk0x004b16c0;
		m_unk0x058->SetDistanceRangeWithMinSquared(minDistance * g_unk0x004b16c0, maxDistance);
		m_unk0x058->SetPosition(position);
	}

	m_state = c_state0x03;
	m_stateTimerMs = c_timer0x2710;

	LegoEventQueue::Callback* callback = this;
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 4;
	descriptor.m_unk0x04 = 1;
	descriptor.m_unk0x08 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_data = &m_worldEntity;
	LegoEventQueue::Event* event = m_raceState0x018->GetEventQueue()->FUN_0042fb50(callback, &descriptor);

	CutsceneAnimation* animation = m_unk0x05c;
	m_collisionEvent = event;
	m_unk0x060 = animation->FUN_00489d70("oilbub", NULL, NULL, NULL);
	if (m_unk0x060 != NULL && m_unk0x060->m_unk0x00 != NULL) {
		m_unk0x060->m_unk0x00->FUN_00489660(&position);
	}

	position.m_z += g_homingProjectileCollisionStartOffset;
	m_unk0x064.m_unk0x104 = 15.0f;
	m_unk0x064.m_unk0x108 = 15.0f;
	m_unk0x064.m_unk0x10c = 15.0f;
	m_unk0x064.m_unk0x0e8 = position;
	position.m_z -= g_homingProjectileCollisionStartOffset;
	m_unk0x064.GetUnk0x010().SetPrimaryMaterialTable(&m_unk0x180);

	GolVec3 normal;
	GolVec3 tangent;
	tangent.m_x = 1.0f;
	tangent.m_y = 0.0f;
	tangent.m_z = 0.0f;

	normal.m_x = 0.0f;
	normal.m_y = 0.0f;
	normal.m_z = -1.0f;

	m_unk0x064.FUN_00414c90(&normal, &tangent);
	m_unk0x064.FUN_00414a30(m_unk0x18c);
}

// FUNCTION: LEGORACERS 0x004575b0
void RacePowerupManager::OilSlickAction::OnHitRacer(RaceState::Racer* p_racer)
{
	if (m_state == c_state0x05 || (p_racer->GetUnk0xd04() & c_racerFlags0xd04Bit3)) {
		return;
	}

	p_racer->m_unk0x3e8.VTable0x24(1.0f, 0.007f, 1.0f);
	p_racer->m_unk0x018.m_unk0x384 |= c_racerField0x018Flags0x384Bit1;
	m_state = c_state0x06;
	m_stateTimerMs = 0;

	SoundVector position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);
	m_soundSource->PlaySpatialSoundById(c_sound0x2f, &position, g_unk0x004b16c8, g_unk0x004b16cc, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x00457640
RacePowerupManager::ColorBrick::ColorBrick()
{
	m_brickMaterial = NULL;
	m_trailMaterial = NULL;
	m_unk0x5c = 3;
	m_unk0x60 = 3;
	m_unk0x64 = 3;
}

// FUNCTION: LEGORACERS 0x00457670
RacePowerupManager::ColorBrick::~ColorBrick()
{
	FUN_00457700();
}

// FUNCTION: LEGORACERS 0x004576c0
void RacePowerupManager::ColorBrick::SetColor(LegoU32 p_unk0x04)
{
	m_unk0x5c = p_unk0x04;
	m_unk0x60 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x004576d0
void RacePowerupManager::ColorBrick::Respawn()
{
	PickupBrick::Respawn();
	m_unk0x64 = m_unk0x5c;
	m_unk0x60 = m_unk0x5c;
	m_brickMaterial = m_manager->GetBrickMaterial(&m_unk0x60);
	m_trailMaterial = m_manager->GetTrailMaterial(&m_unk0x60);
}

// FUNCTION: LEGORACERS 0x00457700
void RacePowerupManager::ColorBrick::FUN_00457700()
{
	FUN_00453a10();
}

// STUB: LEGORACERS 0x00457710
void RacePowerupManager::ColorBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	PickupBrick::Update(p_elapsedMs);

	LegoBool playSound = FALSE;
	switch (m_state) {
	case c_stateTransition:
		if (m_stateTimerMs > 250) {
			m_state = m_nextState;
			m_unk0x60 = m_unk0x64;
			m_stateTimerMs = 0;
			m_brickMaterial = m_manager->GetBrickMaterial(&m_unk0x60);
			m_trailMaterial = m_manager->GetTrailMaterial(&m_unk0x60);
			FUN_00453ad0(FALSE);

			if (m_state == c_stateActive && (m_flags0x50 & c_flags0x50Bit0)) {
				playSound = TRUE;
			}
		}
		break;
	case c_stateActive:
		if (m_stateTimerMs > 500) {
			m_state = c_stateIdle;
			m_stateTimerMs = 0;
			FUN_00453ad0(TRUE);
		}
		break;
	case c_stateWait: {
		LegoU32 elapsedMs = m_stateTimerMs;
		if (m_respawnMs <= elapsedMs) {
			LegoU8 flags = m_flags0x50;
			m_stateTimerMs = 0;
			m_state = c_stateActive;
			if (flags & c_flags0x50Bit0) {
				playSound = TRUE;
			}
		}
		break;
	}
	}

	if (playSound) {
		SoundVector position;
		m_worldEntity.VTable0x04(&position);
		m_soundSource->PlaySpatialSoundById(0x0e, &position, g_unk0x004b170c, 150.0f, 1.0f, 1.0f);
	}
}

// FUNCTION: LEGORACERS 0x00457820
void RacePowerupManager::ColorBrick::OnTouched(RaceState::Racer* p_racer)
{
	if (m_state == c_stateIdle) {
		LegoU32 racerState = p_racer->GetUnk0xccc();
		p_racer->FUN_00439210(m_unk0x60);

		SoundVector position;
		m_worldEntity.VTable0x04(&position);

		if (!racerState) {
			m_unk0x64 = m_unk0x5c;
			m_nextState = c_stateWait;
			if (m_flags0x50 & c_flags0x50Bit0) {
				m_soundSource->PlaySpatialSoundById(0x31, &position, g_unk0x004b170c, 150.0f, 1.0f, 1.0f);
			}
		}
		else {
			m_unk0x64 = racerState;
			m_nextState = c_stateActive;
			if (m_flags0x50 & c_flags0x50Bit0) {
				m_soundSource->PlaySpatialSoundById(0x48, &position, g_unk0x004b170c, 150.0f, 1.0f, 1.0f);
			}
		}

		m_state = c_stateTransition;
		m_stateTimerMs = 0;
	}
}

// FUNCTION: LEGORACERS 0x004578e0
void RacePowerupManager::ColorBrick::SetMaterials(
	DuskwindBananaRelic0x24* p_unk0x04,
	DuskwindBananaRelic0x24* p_unk0x08
)
{
	m_brickMaterial = p_unk0x04;
	m_trailMaterial = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x00457900
void RacePowerupManager::ColorBrick::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	MaterialTable0x0c* materialTable = m_model->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_model->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetPosition(0, m_brickMaterial);
	PickupBrick::VTable0x10(p_renderer);
}

// FUNCTION: LEGORACERS 0x00457930
void RacePowerupManager::ColorBrick::VTable0x14(GolD3DRenderDevice* p_renderer)
{
	MaterialTable0x0c* materialTable = m_blendModel->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_blendModel->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetPosition(0, m_trailMaterial);
	PickupBrick::VTable0x14(p_renderer);
}

// FUNCTION: LEGORACERS 0x00458390
RacePowerupManager::PowerupAction* RacePowerupManager::MagnetAction::Destroy(undefined4 p_flags)
{
	MagnetAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~MagnetAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004583f0
RacePowerupManager::PowerupAction* RacePowerupManager::OilSlickAction::Destroy(undefined4 p_flags)
{
	OilSlickAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~OilSlickAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00458450
RacePowerupManager::PowerupAction* RacePowerupManager::DynamiteAction::Destroy(undefined4 p_flags)
{
	DynamiteAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~DynamiteAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004584b0
RacePowerupManager::PowerupAction* RacePowerupManager::CurseAction::Destroy(undefined4 p_flags)
{
	CurseAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~CurseAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00458510
RacePowerupManager::PowerupAction* RacePowerupManager::CannonballAction::Destroy(undefined4 p_flags)
{
	CannonballAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~CannonballAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00458570
RacePowerupManager::PowerupAction* RacePowerupManager::GrapplingHookAction::Destroy(undefined4 p_flags)
{
	GrapplingHookAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~GrapplingHookAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004585d0
RacePowerupManager::PowerupAction* RacePowerupManager::LightningAction::Destroy(undefined4 p_flags)
{
	LightningAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~LightningAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00458630
RacePowerupManager::PowerupAction* RacePowerupManager::HomingMissileAction::Destroy(undefined4 p_flags)
{
	HomingMissileAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~HomingMissileAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

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

// FUNCTION: LEGORACERS 0x00458750
RacePowerupManager::PowerupAction* RacePowerupManager::WarpAction::Destroy(undefined4 p_flags)
{
	WarpAction* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~WarpAction();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0045bbe0
RacePowerupManager::WeaponActionBase::WeaponActionBase()
{
	m_activeProjectile = 0;
	m_golExportPtr = NULL;
	m_collisionWorld = 0;
	m_ownerRacer = 0;
	m_targetRacer = 0;
	m_targetPoint = 0;
}

// FUNCTION: LEGORACERS 0x0045bc10 FOLDED
void RacePowerupManager::WeaponActionBase::GetProjectilePosition(GolVec3* p_position)
{
	m_activeProjectile->GetWorldEntity()->FUN_100286d0(p_position);
}

// FUNCTION: LEGORACERS 0x0045bc30 FOLDED
void RacePowerupManager::WeaponActionBase::GetProjectileVelocity(GolVec3* p_velocity)
{
	m_activeProjectile->GetVelocity(p_velocity);
}

// FUNCTION: LEGORACERS 0x0045bc40
RaceState::Racer* RacePowerupManager::ShieldAction::FUN_0045bc40()
{
	if (m_unk0x18) {
		return m_unk0x18->m_unk0x08;
	}
	else {
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bc50
RacePowerupManager::ShieldAction::ShieldAction()
{
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
}

// FUNCTION: LEGORACERS 0x0045bc80
RacePowerupManager::ShieldAction::~ShieldAction()
{
	FUN_0045bd10();
}

// FUNCTION: LEGORACERS 0x0045bcd0 FOLDED
void RacePowerupManager::ShieldAction::Initialize(RacePowerupManager* p_unk0x04)
{
	if (m_state != 0) {
		FUN_0045bd10();
	}

	m_state = 1;
	m_unk0x24 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0045bd10 FOLDED
void RacePowerupManager::ShieldAction::FUN_0045bd10()
{
	Deactivate();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x0045bd30
void RacePowerupManager::ShieldAction::Activate(
	RaceState::Racer* p_racer,
	LegoU32 p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10
)
{
	LegoU32 soundId = c_sound0x4c;

	m_entity0x18 = m_unk0x24->AllocateEffectEntity();
	if (m_entity0x18 == NULL) {
		m_state = c_state0x06;
		return;
	}

	m_unk0x1c = m_unk0x24->AllocateEffectEntity();
	if (m_unk0x1c == NULL) {
		m_state = c_state0x06;
		return;
	}

	m_unk0x20 = p_racer;
	if (m_unk0x20->m_unk0xd04 & c_racerFlags0xd04Bit0) {
		m_unk0x24->FUN_0045b640(m_unk0x20);
	}

	switch (p_unk0x08) {
	case 0:
		m_stateTimerMs = c_duration0x0fa0;
		soundId = c_sound0x4c;
		break;
	case 1:
		m_stateTimerMs = c_duration0x1770;
		soundId = c_sound0x35;
		break;
	case 2:
		m_stateTimerMs = c_duration0x1f40;
		soundId = c_sound0x4d;
		break;
	case 3:
		m_stateTimerMs = c_duration0x2710;
		soundId = c_sound0x4e;
		break;
	}

	m_unk0x28 = m_soundSource->AcquireSoundById(soundId);
	if (m_unk0x28 != NULL) {
		m_unk0x28->Play(TRUE);
		m_unk0x28->SetDistanceRange(g_unk0x004b0958, g_unk0x004b095c);
	}

	m_state = c_state0x03;
	m_unk0x20->FUN_00439770(p_unk0x08);
	if (m_unk0x20->m_unk0xd04 & c_racerFlags0xd04Bit11) {
		m_unk0x20->FUN_00439b00();
	}
	m_level = p_unk0x08;

	m_entity0x18->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model != NULL) {
			m_entity0x18->FUN_10023940(
				model,
				p_unk0x0c->VTable0x58(i),
				p_unk0x0c->GetModelPart(i),
				p_unk0x0c->GetModelDistance(i)
			);
		}
	}

	m_entity0x18->FUN_0040dad0(0);
	m_entity0x18->SetFlags(m_entity0x18->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_entity0x18->SetUnk0xb8(p_unk0x0c->GetUnk0xb8());
	m_entity0x18->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_entity0x18->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_entity0x18->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_entity0x18->FUN_00411730(p_unk0x0c->FUN_004116f0());
	m_entity0x18->CopyPositionFrom(*m_unk0x20->m_unk0x018.m_unk0x044);

	m_unk0x1c->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);

	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model != NULL) {
			m_unk0x1c->FUN_10023940(
				model,
				p_unk0x10->VTable0x58(i),
				p_unk0x10->GetModelPart(i),
				p_unk0x10->GetModelDistance(i)
			);
		}
	}

	m_unk0x1c->FUN_0040dad0(0);
	m_unk0x1c->SetFlags(m_unk0x1c->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x1c->SetUnk0xb8(p_unk0x10->GetUnk0xb8());
	m_unk0x1c->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x1c->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x1c->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x1c->FUN_00411730(p_unk0x10->FUN_004116f0());
	m_unk0x1c->CopyPositionFrom(*m_entity0x18);
}

// FUNCTION: LEGORACERS 0x0045c060 FOLDED
void RacePowerupManager::ShieldAction::Deactivate()
{
	if (m_unk0x1c) {
		m_unk0x1c->VTable0x54();
		m_unk0x24->ReleaseEffectEntity(m_unk0x1c);
		m_unk0x1c = NULL;
	}

	if (m_entity0x18) {
		m_entity0x18->VTable0x54();
		m_unk0x24->ReleaseEffectEntity(m_entity0x18);
		m_entity0x18 = NULL;
	}

	m_unk0x20 = NULL;
	if (m_unk0x28) {
		m_soundSource->ReleaseSound(m_soundResource0x28);
		m_unk0x28 = NULL;
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
	RaceState::Racer::Field0x018* racerEntities = &m_unk0x20->m_unk0x018;
	racerEntities->m_unk0x044->VTable0x04(&position);

	GolVec3 velocity = m_unk0x20->m_unk0x3e8.m_unk0x008;
	if (m_unk0x28) {
		m_unk0x28->SetPosition(position);
		m_unk0x28->SetVelocity(velocity);
	}

	m_entity0x18->VTable0x10(p_elapsedMs);
	m_unk0x1c->VTable0x10(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0045c160 FOLDED
void RacePowerupManager::ShieldAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state == 6) {
		return;
	}

	GolVec3 position;
	m_unk0x20->m_unk0x018.m_unk0x044->VTable0x04(&position);
	LegoFloat positionZ = position.m_z;
	positionZ += g_violetShoalTwo;
	position.m_z = positionZ;
	m_entity0x18->VTable0x08(position);

	GolVec3 direction;
	GolVec3 up;
	m_unk0x20->m_unk0x018.m_unk0x044->VTable0x48(&direction, &up);
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	m_entity0x18->VTable0x40(direction, up);

	m_entity0x18->CopyOrientationAndPositionTo(m_unk0x1c);

	if (m_state == 4) {
		LegoFloat alphaValue = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
		alphaValue *= 0.001f;
		alphaValue *= g_unk0x004b0b4c;
		LegoS32 alpha = static_cast<LegoS32>(alphaValue);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_unk0x1c->VTable0x1c(*p_renderer);
	m_entity0x18->VTable0x1c(*p_renderer);

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
		RaceState::Racer::Field0x018* racerEntities = &m_unk0x20->m_unk0x018;
		racerEntities->m_unk0x044->VTable0x04(&position);
		LegoFloat positionZ = position.m_z;
		positionZ += g_homingProjectileCollisionStartOffset;
		position.m_z = positionZ;
		m_soundSource->PlaySpatialSoundById(0x3b, &position, g_unk0x004b1930, g_unk0x004b1934, 1.0f, 1.0f);
		m_unk0x20->FUN_00439790();
		break;
	}
	}
}

// FUNCTION: LEGORACERS 0x0045c330 FOLDED
LegoS32 RacePowerupManager::ShieldAction::GetBrickColor()
{
	return c_brickColorBlue;
}

// FUNCTION: LEGORACERS 0x0045c7e0
RacePowerupManager::TurboAction::TurboAction()
{
	FUN_0045c8d0();
}

// FUNCTION: LEGORACERS 0x0045c830
RacePowerupManager::TurboAction::~TurboAction()
{
	FUN_0045c8b0();
}

// FUNCTION: LEGORACERS 0x0045c880
void RacePowerupManager::TurboAction::Initialize(RacePowerupManager* p_unk0x04, CutsceneAnimation* p_unk0x08)
{
	if (m_state != 0) {
		FUN_0045c8b0();
	}

	m_unk0x1c = p_unk0x04;
	m_unk0x2c = p_unk0x08;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0045c8b0
void RacePowerupManager::TurboAction::FUN_0045c8b0()
{
	Deactivate();
	FUN_0045c8d0();
	m_state = 0;
}

// FUNCTION: LEGORACERS 0x0045c8d0
void RacePowerupManager::TurboAction::FUN_0045c8d0()
{
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x018 = 0;
	m_unk0x1c = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0045c8f0
void RacePowerupManager::TurboAction::Activate(RaceState::Racer* p_racer, LegoU32 p_unk0x08)
{
	GolAnimatedEntity* model = NULL;
	GolAnimatedEntity* effect0 = NULL;
	GolAnimatedEntity* effect1 = NULL;

	m_unk0x20 = m_unk0x1c->AllocateEffectEntity();
	if (m_unk0x20 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x24 = m_unk0x1c->AllocateEffectEntity();
	if (m_unk0x24 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x28 = m_unk0x1c->AllocateEffectEntity();
	if (m_unk0x28 == NULL) {
		m_state = 6;
		return;
	}

	m_unk0x018 = p_racer;
	if (m_unk0x018->m_unk0xc70.m_unk0x014 & RaceState::Racer::Field0xc70::c_flags0x014Bit0) {
		m_unk0x1c->FUN_0045b690(m_unk0x018);
		m_unk0x018->FUN_00439730();
		if (m_unk0x018->m_unk0xd04 & c_racerFlags0xd04Bit3) {
			m_unk0x018->FUN_004395a0();
		}
	}

	m_stateTimerMs = 400;
	m_level = p_unk0x08;
	switch (p_unk0x08) {
	case 2:
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("TurboL2");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb2f1");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb2f2");
		}
		break;
	case 1:
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("TurboL1");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb1f1");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb1f2");
		}
		break;
	case 0:
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("TurboL0");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb0f1");
		}
		if (m_unk0x1c->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_unk0x1c->m_unk0x05c->GetUnk0xc0Name("turb0f2");
		}
		break;
	}

	m_unk0x20
		->FUN_0040d550(model->GetModel(0), model->VTable0x58(0), model->GetModelPart(0), model->GetModelDistance(0));
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = model->GetModel(i);
		if (lodModel != NULL) {
			m_unk0x20->FUN_10023940(lodModel, model->VTable0x58(i), model->GetModelPart(i), model->GetModelDistance(i));
		}
	}

	m_unk0x24->FUN_0040d550(
		effect0->GetModel(0),
		effect0->VTable0x58(0),
		effect0->GetModelPart(0),
		effect0->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect0->GetModel(i);
		if (lodModel != NULL) {
			m_unk0x24->FUN_10023940(
				lodModel,
				effect0->VTable0x58(i),
				effect0->GetModelPart(i),
				effect0->GetModelDistance(i)
			);
		}
	}
	m_unk0x24->FUN_00411680(effect0->FUN_00411640());
	m_unk0x24->FUN_004116b0(effect0->FUN_00411660());
	m_unk0x24->FUN_00411700(effect0->FUN_004116e0());
	m_unk0x24->FUN_00411730(effect0->FUN_004116f0());

	m_unk0x28->FUN_0040d550(
		effect1->GetModel(0),
		effect1->VTable0x58(0),
		effect1->GetModelPart(0),
		effect1->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect1->GetModel(i);
		if (lodModel != NULL) {
			m_unk0x28->FUN_10023940(
				lodModel,
				effect1->VTable0x58(i),
				effect1->GetModelPart(i),
				effect1->GetModelDistance(i)
			);
		}
	}
	m_unk0x28->FUN_00411680(effect1->FUN_00411640());
	m_unk0x28->FUN_004116b0(effect1->FUN_00411660());
	m_unk0x28->FUN_00411700(effect1->FUN_004116e0());
	m_unk0x28->FUN_00411730(effect1->FUN_004116f0());

	FUN_0045cf90();
	m_unk0x20->SetFlags(m_unk0x20->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x20->FUN_0040dad0(0);
	m_unk0x24->SetFlags(m_unk0x24->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x24->FUN_0040dad0(0);
	m_unk0x28->SetFlags(m_unk0x28->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x28->FUN_0040dad0(0);
	FUN_0045cd70();
	m_state = 2;
}

// FUNCTION: LEGORACERS 0x0045cd70
void RacePowerupManager::TurboAction::FUN_0045cd70()
{
	if (!m_level) {
		m_unk0x018->m_unk0x3e8.FUN_00429cf0(-0.0025f, c_duration0x007d);
	}
	else {
		m_unk0x018->m_unk0x3e8.FUN_00429cf0(-0.0025f, c_duration0x00fa);
	}

	m_unk0x018->FUN_004396c0(m_level);

	SoundVector position;
	RaceState::Racer::Field0x018* racerField = &m_unk0x018->m_unk0x018;
	GolAnimatedEntity** racerEntity = &racerField->m_unk0x044;
	(*racerEntity)->VTable0x04(&position);

	m_soundSource->PlaySpatialSoundById(m_level + c_sound0x24, &position, g_unk0x004b19d4, g_unk0x004b19d8, 1.0f, 1.0f);
	m_soundSource->PlaySpatialSoundById(c_sound0x41, &position, g_unk0x004b19d4, g_unk0x004b19d8, 1.0f, 1.0f);

	if (m_level == 2) {
		m_unk0x018->FUN_00439570();
	}
}

// FUNCTION: LEGORACERS 0x0045ce20
void RacePowerupManager::TurboAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_state0x06) {
		return;
	}

	PowerupActionBase::Update(p_elapsedMs);
	m_unk0x20->VTable0x10(p_elapsedMs);
	m_unk0x24->VTable0x10(p_elapsedMs);
	m_unk0x28->VTable0x10(p_elapsedMs);

	if (m_level == 2 && m_state == c_state0x03 && m_unk0x30 == NULL && m_stateTimerMs < c_timer0x0320 &&
		!(m_unk0x1c->m_unk0x058 & c_ownerFlags0x058Bit1)) {
		m_unk0x30 = m_unk0x2c->FUN_00489d70("trbsmke", NULL, NULL, NULL);
	}

	if (m_unk0x30 != NULL) {
		GolAnimatedEntity* racerEntity = m_unk0x018->m_unk0x018.m_unk0x044;
		GolVec3 velocity;
		GolVec3 offset;
		GolVec3 position;

		offset.m_x = -2.0f;
		offset.m_y = 0.0f;
		offset.m_z = 3.0f;
		racerEntity->VTable0x2c(offset, &position);

		if (m_unk0x30->m_unk0x00 != NULL) {
			racerEntity->VTable0x44(m_unk0x30->m_unk0x00->GetUnk0x160());
		}

		if (m_unk0x30->m_unk0x00 != NULL) {
			m_unk0x30->m_unk0x00->FUN_00489660(&position);
		}

		RaceState::Racer::Field0x3e8* racerPhysics = &m_unk0x018->m_unk0x3e8;
		velocity = racerPhysics->m_unk0x008;
		CutsceneParticleRef* particleRef = m_unk0x30;
		velocity *= g_unk0x004b19e4;

		if (particleRef->m_unk0x00 != NULL) {
			particleRef->m_unk0x00->FUN_00489690(&velocity);
		}
	}

	if ((m_unk0x018->m_unk0xd04 & c_racerFlags0xd04Bit3) && m_state == c_state0x03 && m_stateTimerMs < c_timer0x1194 &&
		!m_unk0x018->m_unk0x3e8.FUN_0042a7f0()) {
		AdvanceState();
	}
}

// STUB: LEGORACERS 0x0045cf90
void RacePowerupManager::TurboAction::FUN_0045cf90()
{
	GolAnimatedEntity* racerEntity = m_unk0x018->m_unk0x018.m_unk0x044;

	GolVec3 position;
	racerEntity->VTable0x04(&position);

	const GolMatrix3& orientation = racerEntity->GetOrientation();

	GolVec3 right = orientation.m_rows[0];
	GolVec3 direction = orientation.m_rows[1];
	GolVec3 up = orientation.m_rows[2];
	position.m_x += right.m_x * g_unk0x004b1a50;
	position.m_y += right.m_y * g_unk0x004b1a50;
	position.m_z += right.m_z * g_unk0x004b1a50;
	position.m_x += up.m_x * g_emplacementGravityScale;
	position.m_y += up.m_y * g_emplacementGravityScale;
	position.m_z += up.m_z * g_emplacementGravityScale;

	m_unk0x20->VTable0x08(position);
	m_unk0x20->VTable0x40(direction, up);
	m_unk0x20->CopyOrientationAndPositionTo(m_unk0x24);
	m_unk0x20->CopyOrientationAndPositionTo(m_unk0x28);
}

// FUNCTION: LEGORACERS 0x0045d120
void RacePowerupManager::TurboAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_state0x06) {
		FUN_0045cf90();
		p_renderer->VTable0x94(m_unk0x20);
	}
}

// FUNCTION: LEGORACERS 0x0045d150
void RacePowerupManager::TurboAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state == c_state0x06) {
		return;
	}

	if (m_state == c_state0x02) {
		if (m_stateTimerMs > c_timer0x0032) {
			p_renderer->SetAlphaOverride(0, TRUE);
		}
		else {
			p_renderer->SetAlphaOverride(0xff, TRUE);
		}
	}
	else if (m_state == c_state0x04) {
		LegoS32 elapsed = m_stateTimerMs - c_timer0x015e;
		if (elapsed < 0) {
			elapsed = 0;
		}

		LegoFloat amount = static_cast<LegoFloat>(elapsed) * g_unk0x004b1a54;
		LegoS32 alpha = static_cast<LegoS32>(amount * g_unk0x004b0b4c);
		p_renderer->SetAlphaOverride(alpha, TRUE);
	}

	m_unk0x28->VTable0x1c(*p_renderer);
	m_unk0x24->VTable0x1c(*p_renderer);

	if (m_state == c_state0x02 || m_state == c_state0x04) {
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x0045d200
void RacePowerupManager::TurboAction::AdvanceState()
{
	switch (m_state) {
	case c_state0x04: {
		SoundVector position;
		RaceState::Racer::Field0x018* racerField = &m_unk0x018->m_unk0x018;
		GolAnimatedEntity* racerEntity = racerField->GetUnk0x044();
		racerEntity->VTable0x04(&position);

		LegoS32 state = m_level;
		if (state == 2) {
			m_soundSource->PlaySpatialSoundById(c_sound0x4b, &position, g_unk0x004b19d4, g_unk0x004b19d8, 1.0f, 1.0f);
		}
		else {
			LegoFloat volume = static_cast<LegoFloat>(state) * g_unk0x004b02e0 + g_unk0x004b1a58;
			m_soundSource->PlaySpatialSoundById(c_sound0x28, &position, g_unk0x004b19d4, g_unk0x004b19d8, volume, 1.0f);
		}

		m_state = c_state0x06;
		return;
	}
	case c_state0x03:
		if (m_level == 2 && (m_unk0x1c->m_unk0x058 & c_ownerFlags0x058Bit1)) {
			m_stateTimerMs = c_timer0x1388;
			m_state = c_state0x03;
			return;
		}

		m_unk0x20->FUN_0040dad0(2);
		m_unk0x24->FUN_0040dad0(2);
		m_unk0x28->FUN_0040dad0(2);

		m_stateTimerMs = 700;
		m_state = c_state0x04;
		return;
	case c_state0x02:
		m_unk0x20->FUN_0040dad0(1);
		m_unk0x24->FUN_0040dad0(1);
		m_unk0x28->FUN_0040dad0(1);

		switch (m_level) {
		case 0:
			m_stateTimerMs = c_timer0x03e8;
			break;
		case 1:
			m_stateTimerMs = c_timer0x05dc;
			break;
		case 2:
			m_stateTimerMs = c_timer0x1388;
			break;
		}

		m_unk0x018->PlayReaction(TRUE);
		m_state = c_state0x03;
		return;
	}
}

// FUNCTION: LEGORACERS 0x0045d360
void RacePowerupManager::TurboAction::Deactivate()
{
	m_state = c_state0x01;

	if (m_unk0x30 != NULL) {
		m_unk0x2c->FUN_00489f00(m_unk0x30);
		m_unk0x30 = NULL;
	}

	if (m_unk0x018 != NULL) {
		m_unk0x018->FUN_00439730();
		if (m_unk0x018->m_unk0xd04 & c_racerFlags0xd04Bit3) {
			m_unk0x018->FUN_004395a0();
		}
		m_unk0x018 = NULL;
	}

	if (m_unk0x28 != NULL) {
		m_unk0x28->VTable0x54();
		m_unk0x1c->ReleaseEffectEntity(m_unk0x28);
		m_unk0x28 = NULL;
	}

	if (m_unk0x24 != NULL) {
		m_unk0x24->VTable0x54();
		m_unk0x1c->ReleaseEffectEntity(m_unk0x24);
		m_unk0x24 = NULL;
	}

	if (m_unk0x20 != NULL) {
		m_unk0x20->VTable0x54();
		m_unk0x1c->ReleaseEffectEntity(m_unk0x20);
		m_unk0x20 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045d400
RacePowerupManager::WarpAction::WarpAction()
{
	FUN_0045d4b0();
}

// FUNCTION: LEGORACERS 0x0045d460
RacePowerupManager::WarpAction::~WarpAction()
{
	FUN_0045d540();
}

// FUNCTION: LEGORACERS 0x0045d4b0
void RacePowerupManager::WarpAction::FUN_0045d4b0()
{
	m_state = 0;
	m_unk0x0e0 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4.Clear();
	m_unk0x0c0.Clear();
	m_unk0x0cc.Clear();
	m_unk0x0d8 = 0;
	m_unk0x0dc = 0;
}

// FUNCTION: LEGORACERS 0x0045d510
void RacePowerupManager::WarpAction::Initialize(const SetupParams* p_params)
{
	if (m_state != 0) {
		FUN_0045d540();
	}

	m_unk0x0ac = p_params->m_manager;
	m_unk0x0b0 = p_params->m_cameraFov;
	m_state = 1;
}

// FUNCTION: LEGORACERS 0x0045d540
void RacePowerupManager::WarpAction::FUN_0045d540()
{
	Deactivate();
	FUN_0045d4b0();
}

// FUNCTION: LEGORACERS 0x0045d560
LegoU32 RacePowerupManager::WarpAction::Activate(
	RaceState::Racer* p_racer,
	GolModelEntity* p_model,
	ActionTarget* p_unk0x0c
)
{
	LegoU32 flags = p_racer->m_unk0xd04;
	if (!(flags & c_racerFlags0xd04Bit4)) {
		if (flags & c_racerFlags0xd04Bit21) {
			m_state = 6;
			return flags;
		}

		m_unk0x0ac->FUN_0045b6f0(p_racer);
		m_unk0x0a8 = p_racer;
		m_unk0x0e0 = p_racer->m_unk0xd08 == 2;
		p_racer->m_unk0xd04 |= c_racerFlags0xd04Bit21;

		m_unk0x018.VTable0x50(p_model->GetModel(0), p_model->GetModelDistance(0));
		for (LegoU32 i = 1; i < 3; i++) {
			GolModelBase* model = p_model->GetModel(i);
			if (model != NULL) {
				m_unk0x018.FUN_10027c50(model, p_model->GetModelDistance(i));
			}
		}

		m_unk0x018.FUN_00411680(p_model->FUN_00411640());
		m_unk0x018.FUN_004116b0(p_model->FUN_00411660());
		m_unk0x018.FUN_00411700(p_model->FUN_004116e0());
		m_unk0x018.FUN_00411730(p_model->FUN_004116f0());

		GolAnimatedEntity* racerEntity = p_racer->m_unk0x018.m_unk0x044;
		GolVec3 position;
		racerEntity->VTable0x04(&position);
		LegoFloat positionZ = position.m_z;
		position.m_z = positionZ + g_unk0x004b03f4;
		m_unk0x018.VTable0x08(position);
		position.m_z -= g_unk0x004b03f4;
		m_unk0x018.CopyOrientationFrom(*racerEntity);

		if (m_unk0x0a8->m_unk0xdb4 != NULL) {
			m_unk0x0a8->m_unk0xdb4->m_unk0x134 = m_unk0x0b0 + g_unk0x004b1a6c;
		}

		if (p_unk0x0c != NULL) {
			m_stateTimerMs = 0;
			m_unk0x0c0 = p_unk0x0c->m_unk0x00;
			m_unk0x0cc = p_unk0x0c->m_unk0x0c;
			m_unk0x0d8 = TRUE;
		}
		else {
			m_stateTimerMs = 500;
			m_unk0x0d8 = FALSE;
		}

		m_state = 2;
		return 0;
	}

	m_state = 6;
	return flags;
}

// FUNCTION: LEGORACERS 0x0045d780
void RacePowerupManager::WarpAction::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateDone) {
		return;
	}

	MenuAnimationList* animationList = m_unk0x0ac->m_unk0x04c;
	if (m_stateTimerMs < c_menuAnimationDurationMs && m_state == c_stateStarting && !m_unk0x0e0 &&
		!animationList->HasActive()) {
		MenuAnimationList::Entry* entry =
			animationList->Activate(c_menuAnimationDurationMs, FALSE, NULL, m_unk0x0a8->m_unk0xdb4->m_camera);
		if (entry != NULL) {
			ColorRGBA color;
			color.m_red = 0;
			color.m_grn = 0;
			color.m_blu = c_menuAnimationColorBlue;
			entry->SetColor(color);
		}
	}

	if (m_state == c_stateActive) {
		GolVec3 position;
		do {
			if (m_unk0x0d8) {
				LegoFloat amount = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs)) * g_unk0x004b1aa8;
				position.m_x = m_unk0x0c0.m_x - ((m_unk0x0c0.m_x - m_unk0x0b4.m_x) * amount);
				position.m_y = m_unk0x0c0.m_y - ((m_unk0x0c0.m_y - m_unk0x0b4.m_y) * amount);
				position.m_z = m_unk0x0c0.m_x - ((m_unk0x0c0.m_z - m_unk0x0b4.m_z) * amount);
			}
			else {
				if (!m_unk0x0dc || m_unk0x0a8->m_unk0x010 == NULL) {
					break;
				}

				LegoFloat distance = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * g_unk0x004b1a70;
				RaceSessionField0x27f4::Entry* pathEntry = m_unk0x0a8->m_unk0xcc4;
				if (pathEntry != NULL) {
					LegoU8 pathIndex = pathEntry->m_unk0x20.m_items[0];
					pathEntry = m_unk0x0a8->m_unk0x010->FUN_0041e940(pathIndex);
				}

				RaceState::Racer::Field0x018* racerField0x018 = &m_unk0x0a8->m_unk0x018;
				racerField0x018->m_unk0x044->VTable0x04(&position);
				m_unk0x0a8->m_unk0x010->FUN_0041eaf0(&position, distance, pathEntry);
			}

			m_unk0x0a8->m_unk0x018.m_unk0x044->VTable0x08(position);
			m_unk0x0a8->m_unk0x3e8.m_unk0x0e4.VTable0x08(position);
		} while (0);
	}

	m_unk0x018.VTable0x10(p_elapsedMs);
	PowerupActionBase::Update(p_elapsedMs);
}

// FUNCTION: LEGORACERS 0x0045d940
void RacePowerupManager::WarpAction::VTable0x0c(GolD3DRenderDevice* p_renderer)
{
	MenuAnimationList* animationList = m_unk0x0ac->m_unk0x04c;
	if (m_state == c_stateDone) {
		return;
	}

	if (m_state != c_stateActive) {
		return;
	}

	RaceCameraController* cameraController = m_unk0x0a8->m_unk0xdb4;
	if (cameraController == NULL) {
		return;
	}

	GolCamera* camera = p_renderer->GetUnk0x0c();
	if (cameraController->m_camera != camera) {
		return;
	}

	RaceState::Racer::Field0x018* racerField = &m_unk0x0a8->m_unk0x018;
	GolAnimatedEntity* entity = racerField->m_unk0x044;

	GolVec3 savedPosition;
	GolMatrix3 savedOrientation;
	entity->VTable0x04(&savedPosition);
	entity->VTable0x44(&savedOrientation);

	GolVec3 direction;
	direction.m_x = 0.0f;
	direction.m_y = -1.0f;
	direction.m_z = 0.0f;

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;

	GolVec3 position;
	position.Clear();
	entity->VTable0x08(position);
	entity->VTable0x40(direction, up);

	m_unk0x0a8->m_unk0xdb4->m_unk0x000 = TRUE;
	m_unk0x0a8->m_unk0xdb4->FUN_00428540(0.0f);

	LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
	phase *= g_item0x40Pi;
	phase *= g_unk0x004b1aa8;
	phase *= g_negativeRadiansToTableIndex;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase)) & 0x3ff;
	LegoFloat tableValue = g_cosineTable[tableIndex];
	LegoFloat fov = tableValue * g_unk0x004b1a68 + m_unk0x0b0;
	camera->m_flags |= GolCamera::c_flagBit1;
	camera->m_fov = fov;

	p_renderer->VTable0x5c();
	racerField->FUN_0043db60();

	GolAnimatedEntity* dbricks = m_unk0x0ac->m_unk0x064->FindUnk0xc0("dbricks");
	dbricks->FUN_0040d650();
	dbricks->SetActiveValue(0.0f);
	dbricks->FUN_00411680(0.0f);
	dbricks->FUN_004116b0(0.0f);

	GolAnimatedEntity* dtube = m_unk0x0ac->m_unk0x064->FindUnk0xc0("dtube");
	dtube->FUN_0040d650();
	dtube->SetActiveValue(0.0f);
	dtube->FUN_00411680(0.0f);
	dtube->FUN_004116b0(0.0f);

	m_unk0x0ac->m_unk0x064->FUN_00416090(c_transitionDurationMs - m_stateTimerMs);
	m_unk0x0ac->m_unk0x064->FUN_00416040();

	racerField->FUN_0043e620();
	if (m_unk0x0a8->m_unk0xdb8 != c_stateActive) {
		racerField->FUN_0043fbc0(p_renderer);
	}

	entity->VTable0x08(savedPosition);
	entity->VTable0x3c(savedOrientation);
	m_unk0x0a8->FUN_0043a3e0();
	animationList->Draw(p_renderer);
	racerField->FUN_0043dbb0();

	LegoFloat restoredFov = m_unk0x0b0;
	camera->m_fov = restoredFov;
	camera->m_flags |= GolCamera::c_flagBit1;
}

// FUNCTION: LEGORACERS 0x0045dbe0
void RacePowerupManager::WarpAction::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateStarting) {
		return;
	}

	GolVec3 position;
	LegoFloat phase = static_cast<LegoFloat>(static_cast<LegoS32>(m_stateTimerMs));
	phase *= g_unk0x004b02fc;
	phase *= g_item0x40Pi;
	phase *= g_negativeRadiansToTableIndex;
	LegoS32 tableIndex = (0xffffff00 - static_cast<LegoS32>(phase)) & 0x3ff;
	LegoFloat scale = g_cosineTable[tableIndex];
	m_unk0x018.SetUnk0x58AndInvalidateRadius(scale);

	if (m_stateTimerMs < 250) {
		m_unk0x0a8->m_unk0x018.FUN_00440160(scale);
	}

	RaceState::Racer::Field0x018* racerField = &m_unk0x0a8->m_unk0x018;
	GolAnimatedEntity* entity = racerField->m_unk0x044;
	entity->VTable0x04(&position);
	m_unk0x018.VTable0x08(position);
	m_unk0x018.VTable0x1c(*p_renderer);
}

// FUNCTION: LEGORACERS 0x0045dc90
void RacePowerupManager::WarpAction::AdvanceState()
{
	switch (m_state) {
	case c_stateStarting: {
		m_unk0x0a8->m_unk0xd04 &= ~RaceState::Racer::c_flags0xd04Bit21;
		m_unk0x0a8->FUN_004395d0();
		m_unk0x0a8->m_unk0x018.FUN_00440160(1.0f);
		m_unk0x0a8->m_unk0x3e8.VTable0x44();
		m_unk0x0a8->m_unk0x3e8.VTable0x4c();

		RaceCameraController* cameraController = m_unk0x0a8->m_unk0xdb4;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_unk0x0b0;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagBit1;
			fov = m_unk0x0b0;
			m_unk0x0a8->m_unk0xdb4->m_unk0x134 = fov;
		}

		RaceState::Racer::Field0x018* racerField = &m_unk0x0a8->m_unk0x018;
		GolAnimatedEntity** entitySlot = &racerField->m_unk0x044;
		GolAnimatedEntity* entity = *entitySlot;
		entity->VTable0x04(&m_unk0x0b4);

		if (!m_unk0x0e0) {
			m_soundSource->PlaySoundById(c_soundStart);
		}

		m_soundSource->PlaySpatialSoundById(c_soundSpatial, &m_unk0x0b4, g_unk0x004b1a60, g_unk0x004b1a64, 1.0f, 1.0f);

		if (!m_unk0x0e0) {
			m_unk0x0dc = TRUE;
		}

		m_stateTimerMs = c_transitionDurationMs;
		m_state = c_stateActive;
		break;
	}
	case c_stateActive: {
		RaceCameraController* cameraController = m_unk0x0a8->m_unk0xdb4;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_unk0x0b0;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagBit1;
			fov = m_unk0x0b0;
			m_unk0x0a8->m_unk0xdb4->m_unk0x134 = fov;
		}

		GolAnimatedEntity* entity = m_unk0x0a8->m_unk0x018.m_unk0x044;
		FUN_0045e080(entity);
		m_unk0x0a8->m_unk0x3e8.m_unk0x0e4.CopyPositionFrom(*entity);

		GolVec3 direction;
		if (m_unk0x0d8) {
			direction = m_unk0x0cc;
		}
		else {
			RaceSessionField0x27f4::Entry* racerPathEntry = m_unk0x0a8->m_unk0xcc4;
			if (racerPathEntry != NULL) {
				LegoU8 pathIndex = racerPathEntry->m_unk0x20.m_items[0];
				RaceSessionField0x27f4* path = m_unk0x0a8->m_unk0x010;
				RaceSessionField0x27f4::Entry* pathEntry = path->FUN_0041e940(pathIndex);
				direction.m_x = pathEntry->m_unk0x00.m_x;
				direction.m_y = pathEntry->m_unk0x00.m_y;
				LegoFloat z = pathEntry->m_unk0x00.m_z;
				direction.m_x = -direction.m_x;
				direction.m_y = -direction.m_y;
				direction.m_z = -z;
			}
			else {
				direction.m_x = 1.0f;
				direction.m_y = 0.0f;
				direction.m_z = 0.0f;
			}
		}

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;

		if (!m_unk0x0e0) {
			entity->VTable0x40(direction, up);
			m_unk0x0a8->m_unk0x3e8.m_unk0x0e4.CopyOrientationFrom(*entity);

			RaceState::Racer::Field0x3e8* racerField0x3e8 = &m_unk0x0a8->m_unk0x3e8;
			up.Clear();
			racerField0x3e8->m_unk0x008.m_x = 0.0f;
			racerField0x3e8->m_unk0x008.m_y = up.m_y;
			racerField0x3e8->m_unk0x008.m_z = up.m_z;
			m_unk0x0a8->m_unk0x3e8.VTable0x20(&direction, g_unk0x004b1a74);
			m_unk0x0a8->m_unk0x3e8.FUN_00446fa0();
			m_unk0x0a8->FUN_0043a3e0();

			if (!m_unk0x0e0) {
				m_soundSource->PlaySoundById(c_soundFinish);
			}
		}

		m_unk0x0a8->FUN_00439660();
		m_state = c_stateDone;
		break;
	}
	}
}

// FUNCTION: LEGORACERS 0x0045e000
void RacePowerupManager::WarpAction::Deactivate()
{
	m_state = c_stateInitialized;
	m_unk0x018.VTable0x54();
	if (m_unk0x0a8 != NULL) {
		RaceCameraController* cameraController = m_unk0x0a8->m_unk0xdb4;
		if (cameraController != NULL) {
			GolCamera* camera = cameraController->m_camera;
			LegoFloat fov = m_unk0x0b0;
			camera->m_fov = fov;
			camera->m_flags |= GolCamera::c_flagBit1;
			fov = m_unk0x0b0;
			m_unk0x0a8->m_unk0xdb4->m_unk0x134 = fov;
		}

		m_unk0x0a8->m_unk0x018.FUN_00440160(1.0f);
		m_unk0x0a8 = NULL;
	}

	m_unk0x0dc = FALSE;
}

// FUNCTION: LEGORACERS 0x0045e080
void RacePowerupManager::WarpAction::FUN_0045e080(GolWorldEntity* p_entity)
{
	GolVec3 position;
	if (m_unk0x0d8) {
		position = m_unk0x0c0;
	}
	else {
		p_entity->VTable0x04(&position);
	}

	GolVec3 start = position;
	GolVec3 end = position;
	end.m_z += g_homingProjectileCollisionStartOffset;
	start.m_z += g_homingProjectileCollisionStartOffset;
	start.m_z -= g_homingProjectileCollisionProbeDepth;

	GolBoundingVolume::Field0x0c record;
	m_unk0x0ac->m_unk0x068->FUN_0041f4d0(&start, &end, &record, &position, NULL);

	position.m_z += g_homingProjectileCollisionStartOffset;
	p_entity->VTable0x08(position);
}
