#include "decomp.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"

DECOMP_SIZE_ASSERT(RacePowerupManager::TetherProjectile, 0x238)

extern const LegoFloat g_unk0x004b02e0;

// GLOBAL: LEGORACERS 0x004b0c8c
extern const LegoFloat g_unk0x004b0c8c = 300.0f;

// GLOBAL: LEGORACERS 0x004b0c90
extern const LegoFloat g_unk0x004b0c90 = 2.0f;

// GLOBAL: LEGORACERS 0x004b0c94
extern const LegoFloat g_unk0x004b0c94 = 2.0f;

// GLOBAL: LEGORACERS 0x004b0c98
extern const LegoFloat g_unk0x004b0c98 = 36.0f;

// GLOBAL: LEGORACERS 0x004b0c9c
extern const LegoFloat g_unk0x004b0c9c = 1.0f;

// GLOBAL: LEGORACERS 0x004b0ca0
extern const LegoFloat g_unk0x004b0ca0 = 250.0f;

// GLOBAL: LEGORACERS 0x004b0ca4
extern const LegoFloat g_unk0x004b0ca4 = 10.0f;

// FUNCTION: LEGORACERS 0x00444250
RacePowerupManager::TetherProjectile::TetherProjectile()
{
	m_unk0x218 = 0;
	m_unk0x21c = 0;
	m_unk0x220 = 0;
	m_unk0x224 = 0;
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x004442c0
PowerupProjectile* RacePowerupManager::TetherProjectile::Destroy(undefined4 p_flags)
{
	TetherProjectile* result = this;
	this->~TetherProjectile();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004442e0
RacePowerupManager::TetherProjectile::~TetherProjectile()
{
	Deactivate();
}

// FUNCTION: LEGORACERS 0x00444340
void RacePowerupManager::TetherProjectile::VTable0x20(const SetupParams* p_params)
{
	m_unk0x218 = p_params->m_unk0x04;
	m_unk0x21c = p_params->m_unk0x0c;
	m_unk0x220 = 0;
	m_hitRacer = 0;

	GolD3DRenderDevice* renderer = p_params->m_golExport->GetDrawState()->m_currentRenderer;

	BeamMesh::SetupParams params;
	params.m_golExport = p_params->m_golExport;
	params.m_renderer = renderer;
	params.m_material = p_params->m_material;
	params.m_unk0x0c = 5;
	params.m_unk0x10 = p_params->m_unk0x0c == 0.0f ? 1 : 5;
	params.m_unk0x14 = 2;
	params.m_unk0x18[0].m_x = 0.0f;
	params.m_unk0x18[0].m_y = p_params->m_unk0x08 * 0.5f;
	params.m_unk0x18[0].m_z = -p_params->m_unk0x08;
	params.m_unk0x18[1].m_x = 0.0f;
	params.m_unk0x18[1].m_y = 0.0f;
	params.m_unk0x18[1].m_z = 0.0f;
	params.m_unk0x18[2].m_x = 0.0f;
	params.m_unk0x18[2].m_y = 0.0f;
	params.m_unk0x18[2].m_z = 0.0f;
	params.m_unk0x54[0] = 0.0f;
	params.m_unk0x54[1] = 0.5f;
	params.m_unk0x54[2] = 1.0f;
	params.m_unk0x68 = 3;
	params.m_modelDistance = 360000.0f;
	params.m_unk0x70 = 0;

	m_beam.FUN_00493c90(&params);
	m_beam.FUN_00494820(&p_params->m_unk0x10, &p_params->m_unk0x14, &p_params->m_unk0x18);
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00444470
void RacePowerupManager::TetherProjectile::Deactivate()
{
	PowerupProjectile::Deactivate();
	m_beam.FUN_00493e60();
}

// FUNCTION: LEGORACERS 0x00444490
LegoS32 RacePowerupManager::TetherProjectile::Update(LegoU32 p_elapsedMs)
{
	if (m_unk0x234 & c_flags0x234Bit1) {
		return FUN_00444690(p_elapsedMs);
	}

	if (m_state == 2) {
		return FUN_00444820(p_elapsedMs);
	}

	PowerupProjectile::Update(p_elapsedMs);
	LegoS32 result = m_state;
	if (result == 1) {
		LegoFloat elapsedMs = static_cast<LegoFloat>(m_ageMs);
		LegoFloat elapsed = elapsedMs / static_cast<LegoFloat>(static_cast<LegoS32>(m_flightTimeMs));
		m_unk0x220 = (1.0f - elapsed) * m_unk0x21c;

		GolVec3 position;
		m_worldEntity->VTable0x04(&position);
		FUN_00444540(&position, elapsedMs, m_unk0x220);

		result = 1;
	}

	return result;
}

// STUB: LEGORACERS 0x00444540
void RacePowerupManager::TetherProjectile::FUN_00444540(
	const GolVec3* p_position,
	LegoFloat p_elapsedMs,
	LegoFloat p_amount
)
{
	LegoFloat elapsedStep = p_elapsedMs;
	elapsedStep *= g_unk0x004b02e0;
	elapsedStep *= 0.001f;

	GolVec3 origin;
	m_ownerRacer->m_unk0x018.m_unk0x044->VTable0x04(&origin);
	origin.m_z += m_unk0x218;

	LegoFloat deltaX = p_position->m_x - origin.m_x;
	LegoFloat deltaY = p_position->m_y - origin.m_y;

	GolVec3 step;
	step.m_x = deltaX * g_unk0x004b02e0;
	step.m_y = deltaY * g_unk0x004b02e0;
	step.m_z = p_position->m_z - origin.m_z;
	m_beam.FUN_00493ea0(&origin, &step);

	LegoFloat elapsed = 0.0f;
	GolVec3 position = origin;
	for (LegoU32 i = 0; i < 4; i++) {
		elapsed += elapsedStep;
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z = (m_gravity * 0.5f * elapsed * elapsed) + (m_velocityZ * elapsed) + m_startPosition.m_z;
		m_beam.FUN_00494870(&position, p_amount);
		p_amount = -p_amount;
	}

	m_beam.FUN_00494870(p_position, p_amount);
	m_beam.FUN_00494230();
}

// FUNCTION: LEGORACERS 0x00444670
void RacePowerupManager::TetherProjectile::VTable0x24(GolD3DRenderDevice* p_renderer)
{
	m_beam.FUN_00494850(p_renderer);
}

// STUB: LEGORACERS 0x00444690
LegoS32 RacePowerupManager::TetherProjectile::FUN_00444690(LegoU32 p_elapsedMs)
{
	GolVec3 position;
	m_ownerRacer->m_unk0x018.m_unk0x044->VTable0x04(&position);
	position.m_z += m_unk0x218;

	GolVec3* target = &m_unk0x228;
	if (GolMath::FUN_00449a90(
			target,
			&position,
			g_unk0x004b0c98,
			g_unk0x004b0ca0,
			static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs))
		)) {
		m_unk0x234 = 0;
		return c_stateExpired;
	}

	m_unk0x224 -= g_unk0x004b0c9c * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_unk0x224 < 0.0f) {
		m_unk0x224 = 0.0f;
	}

	LegoFloat amount = m_unk0x224 * g_unk0x004b0ca4;
	GolVec3 delta;
	delta.m_x = target->m_x - position.m_x;
	delta.m_y = target->m_y - position.m_y;
	delta.m_z = target->m_z - position.m_z;

	GolVec3 step;
	step.m_x = delta.m_x * g_unk0x004b02e0;
	step.m_y = delta.m_y * g_unk0x004b02e0;
	step.m_z = delta.m_z * g_unk0x004b02e0;
	m_beam.FUN_00493ea0(&position, &step);

	for (LegoU32 i = 0; i < 4; i++) {
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z += step.m_z;
		m_beam.FUN_00494870(&position, amount);
		amount = -amount;
	}

	m_beam.FUN_00494870(target, amount);
	m_beam.FUN_00494230();

	return c_stateFlying;
}

// STUB: LEGORACERS 0x00444820
LegoS32 RacePowerupManager::TetherProjectile::FUN_00444820(LegoU32 p_elapsedMs)
{
	GolVec3 targetPosition;
	m_hitRacer->m_unk0x018.m_unk0x044->VTable0x04(&targetPosition);
	targetPosition.m_z += g_unk0x004b0c90;

	GolVec3 currentPosition;
	m_worldEntity->VTable0x04(&currentPosition);

	if (!(m_unk0x234 & c_flags0x234Bit0)) {
		if (GolMath::FUN_00449a90(
				&targetPosition,
				&currentPosition,
				g_unk0x004b0c94,
				g_unk0x004b0c8c,
				static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs))
			)) {
			m_unk0x234 |= c_flags0x234Bit0;
		}
	}

	if (m_unk0x234 & c_flags0x234Bit0) {
		currentPosition = targetPosition;
	}

	m_worldEntity->VTable0x08(currentPosition);

	GolVec3 origin;
	m_ownerRacer->m_unk0x018.m_unk0x044->VTable0x04(&origin);
	origin.m_z += m_unk0x218;

	GolVec3 delta;
	delta.m_x = currentPosition.m_x - origin.m_x;
	delta.m_y = currentPosition.m_y - origin.m_y;
	delta.m_z = currentPosition.m_z - origin.m_z;

	m_unk0x224 += g_unk0x004b0c9c * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_unk0x224 >= 1.0f) {
		GolBoundingVolume::Field0x0c record;
		m_unk0x224 = 1.0f;
		if (m_collisionWorld->FUN_0041f730(&origin, &currentPosition, &record, &m_hitPosition)) {
			m_hitNormal = record.m_unk0x24;
			return c_stateHitWorld;
		}
	}

	LegoFloat remainingAmount = 1.0f - m_unk0x224;
	GolVec3 step;
	step.m_x = delta.m_x * 0.2f;
	step.m_y = delta.m_y * 0.2f;
	step.m_z = delta.m_z * 0.2f;
	m_beam.FUN_00493ea0(&origin, &step);

	LegoFloat elapsedStep = static_cast<LegoFloat>(m_flightTimeMs) * 0.2f * 0.001f;
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
					  (m_unk0x224 * position.m_z);
		m_beam.FUN_00494870(&blended, 0.0f);
	}

	m_beam.FUN_00494870(&currentPosition, 0.0f);
	m_beam.FUN_00494230();

	return 2;
}

// FUNCTION: LEGORACERS 0x00444ac0
void RacePowerupManager::TetherProjectile::FUN_00444ac0(GolVec3* p_unk0x04)
{
	m_unk0x228.m_x = p_unk0x04->m_x;
	m_unk0x228.m_y = p_unk0x04->m_y;
	m_unk0x228.m_z = p_unk0x04->m_z;

	if (m_hitRacer == NULL) {
		m_unk0x224 = m_unk0x220 / g_unk0x004b0ca4;
	}

	m_unk0x234 |= c_flags0x234Bit1;
}
