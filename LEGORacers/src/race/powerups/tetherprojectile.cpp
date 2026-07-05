#include "race/powerups/tetherprojectile.h"

#include "decomp.h"
#include "race/triggerworld.h"
#include "render/golcommondrawstate.h"

DECOMP_SIZE_ASSERT(TetherProjectile, 0x238)

extern const LegoFloat g_unk0x004b02e0;

// GLOBAL: LEGORACERS 0x004b0c8c
extern const LegoFloat g_tetherChaseSpeed = 300.0f;

// GLOBAL: LEGORACERS 0x004b0c90
extern const LegoFloat g_tetherTargetHeightOffset = 2.0f;

// GLOBAL: LEGORACERS 0x004b0c94
extern const LegoFloat g_tetherSnapRadius = 2.0f;

// GLOBAL: LEGORACERS 0x004b0c98
extern const LegoFloat g_tetherRetractRadius = 36.0f;

// GLOBAL: LEGORACERS 0x004b0c9c
extern const LegoFloat g_tetherTautnessRate = 1.0f;

// GLOBAL: LEGORACERS 0x004b0ca0
extern const LegoFloat g_tetherRetractSpeed = 250.0f;

// GLOBAL: LEGORACERS 0x004b0ca4
extern const LegoFloat g_tetherWaveScale = 10.0f;

// FUNCTION: LEGORACERS 0x00444250
TetherProjectile::TetherProjectile()
{
	m_attachHeight = 0;
	m_waveAmplitude = 0;
	m_currentWaveAmplitude = 0;
	m_tension = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004442c0
PowerupProjectile* TetherProjectile::Destroy(undefined4 p_flags)
{
	TetherProjectile* result = this;
	this->~TetherProjectile();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004442e0
TetherProjectile::~TetherProjectile()
{
	Deactivate();
}

// FUNCTION: LEGORACERS 0x00444340
void TetherProjectile::Initialize(const SetupParams* p_params)
{
	m_attachHeight = p_params->m_attachHeight;
	m_waveAmplitude = p_params->m_waveAmplitude;
	m_currentWaveAmplitude = 0;
	m_hitRacer = 0;

	GolD3DRenderDevice* renderer = p_params->m_golExport->GetDrawState()->m_currentRenderer;

	BeamMesh::SetupParams params;
	params.m_golExport = p_params->m_golExport;
	params.m_renderer = renderer;
	params.m_material = p_params->m_material;
	params.m_sectionCount = 5;
	params.m_segmentCount = p_params->m_waveAmplitude == 0.0f ? 1 : 5;
	params.m_ringQuadCount = 2;
	params.m_ringVertices[0].m_x = 0.0f;
	params.m_ringVertices[0].m_y = p_params->m_ropeThickness * 0.5f;
	params.m_ringVertices[0].m_z = -p_params->m_ropeThickness;
	params.m_ringVertices[1].m_x = 0.0f;
	params.m_ringVertices[1].m_y = 0.0f;
	params.m_ringVertices[1].m_z = 0.0f;
	params.m_ringVertices[2].m_x = 0.0f;
	params.m_ringVertices[2].m_y = 0.0f;
	params.m_ringVertices[2].m_z = 0.0f;
	params.m_ringTextureXs[0] = 0.0f;
	params.m_ringTextureXs[1] = 0.5f;
	params.m_ringTextureXs[2] = 1.0f;
	params.m_textureColumnCount = 3;
	params.m_modelDistance = 360000.0f;
	params.m_faceCamera = 0;

	m_beam.Initialize(&params);
	m_beam.SetColors(&p_params->m_baseColor, &p_params->m_secondaryColor, &p_params->m_tertiaryColor);
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00444470
void TetherProjectile::Deactivate()
{
	PowerupProjectile::Deactivate();
	m_beam.Destroy();
}

// FUNCTION: LEGORACERS 0x00444490
LegoS32 TetherProjectile::Update(LegoU32 p_elapsedMs)
{
	if (m_flags & c_flagReleased) {
		return UpdateReleased(p_elapsedMs);
	}

	if (m_state == c_stateHitRacer) {
		return UpdateAttached(p_elapsedMs);
	}

	PowerupProjectile::Update(p_elapsedMs);
	LegoS32 result = m_state;
	if (result == c_stateFlying) {
		LegoFloat elapsedMs = static_cast<LegoFloat>(m_ageMs);
		LegoFloat elapsed = elapsedMs / static_cast<LegoFloat>(static_cast<LegoS32>(m_flightTimeMs));
		m_currentWaveAmplitude = (1.0f - elapsed) * m_waveAmplitude;

		GolVec3 position;
		m_worldEntity->GetPosition(&position);
		RebuildBeam(&position, elapsedMs, m_currentWaveAmplitude);

		result = c_stateFlying;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00444540
void TetherProjectile::RebuildBeam(const GolVec3* p_position, LegoFloat p_elapsedMs, LegoFloat p_amount)
{
	LegoFloat elapsedStep = p_elapsedMs;
	elapsedStep *= g_unk0x004b02e0;
	elapsedStep *= 0.001f;

	GolVec3 origin;
	m_ownerRacer->m_visuals.m_carEntity->GetPosition(&origin);
	origin.m_z += m_attachHeight;

	LegoFloat deltaX = p_position->m_x - origin.m_x;
	LegoFloat deltaY = p_position->m_y - origin.m_y;

	GolVec3 step;
	step.m_x = deltaX * g_unk0x004b02e0;
	step.m_y = deltaY * g_unk0x004b02e0;
	step.m_z = p_position->m_z - origin.m_z;
	m_beam.Begin(&origin, &step);

	LegoFloat elapsed = 0.0f;
	GolVec3 position = origin;
	for (LegoU32 i = 0; i < 4; i++) {
		elapsed += elapsedStep;
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z = (m_gravity * 0.5f * elapsed * elapsed) + (m_velocityZ * elapsed) + m_startPosition.m_z;
		m_beam.AppendSpan(&position, p_amount);
		p_amount = -p_amount;
	}

	m_beam.AppendSpan(p_position, p_amount);
	m_beam.Finish();
}

// FUNCTION: LEGORACERS 0x00444670
void TetherProjectile::Draw(GolD3DRenderDevice* p_renderer)
{
	m_beam.Draw(p_renderer);
}

// FUNCTION: LEGORACERS 0x00444690
LegoS32 TetherProjectile::UpdateReleased(LegoU32 p_elapsedMs)
{
	GolVec3 position;
	m_ownerRacer->m_visuals.m_carEntity->GetPosition(&position);
	position.m_z += m_attachHeight;

	GolVec3* target = &m_endPosition;
	if (GolMath::MoveToward(
			target,
			&position,
			g_tetherRetractRadius,
			g_tetherRetractSpeed,
			static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs))
		)) {
		m_flags = 0;
		return c_stateExpired;
	}

	m_tension -= g_tetherTautnessRate * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_tension < 0.0f) {
		m_tension = 0.0f;
	}

	LegoFloat amount = m_tension * g_tetherWaveScale;
	GolVec3 delta;
	delta.m_x = target->m_x - position.m_x;
	delta.m_y = target->m_y - position.m_y;
	delta.m_z = target->m_z - position.m_z;

	GolVec3 step;
	step.m_x = delta.m_x * g_unk0x004b02e0;
	step.m_y = delta.m_y * g_unk0x004b02e0;
	step.m_z = delta.m_z * g_unk0x004b02e0;
	m_beam.Begin(&position, &step);

	for (LegoU32 i = 0; i < 4; i++) {
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z += step.m_z;
		m_beam.AppendSpan(&position, amount);
		amount = -amount;
	}

	m_beam.AppendSpan(target, amount);
	m_beam.Finish();

	return c_stateFlying;
}

// FUNCTION: LEGORACERS 0x00444820
LegoS32 TetherProjectile::UpdateAttached(LegoU32 p_elapsedMs)
{
	GolVec3 targetPosition;
	m_hitRacer->m_visuals.m_carEntity->GetPosition(&targetPosition);
	targetPosition.m_z += g_tetherTargetHeightOffset;

	GolVec3 currentPosition;
	m_worldEntity->GetPosition(&currentPosition);

	if (!(m_flags & c_flagSnapped)) {
		if (GolMath::MoveToward(
				&targetPosition,
				&currentPosition,
				g_tetherSnapRadius,
				g_tetherChaseSpeed,
				static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs))
			)) {
			m_flags |= c_flagSnapped;
		}
	}

	if (m_flags & c_flagSnapped) {
		currentPosition = targetPosition;
	}

	m_worldEntity->SetPosition(currentPosition);

	GolVec3 origin;
	m_ownerRacer->m_visuals.m_carEntity->GetPosition(&origin);
	origin.m_z += m_attachHeight;

	GolVec3 delta;
	delta.m_x = currentPosition.m_x - origin.m_x;
	delta.m_y = currentPosition.m_y - origin.m_y;
	delta.m_z = currentPosition.m_z - origin.m_z;

	m_tension += g_tetherTautnessRate * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_tension >= 1.0f) {
		GolBoundingVolume::HitTriangle record;
		m_tension = 1.0f;
		if (m_collisionWorld->IntersectSegmentAndFireEvents(&origin, &currentPosition, &record, &m_hitPosition)) {
			m_hitNormal = record.m_normal;
			return c_stateHitWorld;
		}
	}

	LegoFloat remainingAmount = 1.0f - m_tension;
	GolVec3 step;
	step.m_x = delta.m_x * g_unk0x004b02e0;
	step.m_y = delta.m_y * g_unk0x004b02e0;
	step.m_z = delta.m_z * g_unk0x004b02e0;
	m_beam.Begin(&origin, &step);

	LegoFloat elapsedStep = static_cast<LegoFloat>(m_flightTimeMs) * g_unk0x004b02e0 * 0.001f;
	LegoFloat elapsed = 0.0f;
	GolVec3 position = origin;
	for (LegoU32 i = 0; i < 4; i++) {
		elapsed += elapsedStep;
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z += step.m_z;

		GolVec3 blended = position;
		blended.m_z = (((m_gravity * 0.5f * elapsed * elapsed) + (m_velocityZ * elapsed) + m_startPosition.m_z) *
					   remainingAmount) +
					  (m_tension * position.m_z);
		m_beam.AppendSpan(&blended, 0.0f);
	}

	m_beam.AppendSpan(&currentPosition, 0.0f);
	m_beam.Finish();

	return c_stateHitRacer;
}

// FUNCTION: LEGORACERS 0x00444ac0
void TetherProjectile::Release(GolVec3* p_position)
{
	m_endPosition.m_x = p_position->m_x;
	m_endPosition.m_y = p_position->m_y;
	m_endPosition.m_z = p_position->m_z;

	if (m_hitRacer == NULL) {
		m_tension = m_currentWaveAmplitude / g_tetherWaveScale;
	}

	m_flags |= c_flagReleased;
}
