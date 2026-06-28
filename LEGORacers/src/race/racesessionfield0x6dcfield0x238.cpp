#include "decomp.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"

DECOMP_SIZE_ASSERT(RacePowerupManager::Field0x238, 0x238)

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
RacePowerupManager::Field0x238::Field0x238()
{
	m_unk0x218 = 0;
	m_unk0x21c = 0;
	m_unk0x220 = 0;
	m_unk0x224 = 0;
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x004442c0
RaceSessionField0x6dcField0xa8* RacePowerupManager::Field0x238::VTable0x10(undefined4 p_flags)
{
	Field0x238* result = this;
	this->~Field0x238();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004442e0
RacePowerupManager::Field0x238::~Field0x238()
{
	VTable0x14();
}

// FUNCTION: LEGORACERS 0x00444340
void RacePowerupManager::Field0x238::VTable0x20(const SetupParams* p_params)
{
	m_unk0x218 = p_params->m_unk0x04;
	m_unk0x21c = p_params->m_unk0x0c;
	m_unk0x220 = 0;
	m_unk0x0a4 = 0;

	GolD3DRenderDevice* renderer = p_params->m_unk0x00->GetDrawState()->m_currentRenderer;

	Field0x170::SetupParams params;
	params.m_unk0x00 = p_params->m_unk0x00;
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

	m_unk0x0a8.FUN_00493c90(&params);
	m_unk0x0a8.FUN_00494820(&p_params->m_unk0x10, &p_params->m_unk0x14, &p_params->m_unk0x18);
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00444470
void RacePowerupManager::Field0x238::VTable0x14()
{
	RaceSessionField0x6dcField0xa8::VTable0x14();
	m_unk0x0a8.FUN_00493e60();
}

// STUB: LEGORACERS 0x00444490
LegoS32 RacePowerupManager::Field0x238::VTable0x18(LegoU32 p_elapsedMs)
{
	if (m_unk0x234 & c_flags0x234Bit1) {
		return FUN_00444690(p_elapsedMs);
	}

	if (m_unk0x004 == 2) {
		return FUN_00444820(p_elapsedMs);
	}

	LegoS32 result = RaceSessionField0x6dcField0xa8::VTable0x18(p_elapsedMs);
	if (m_unk0x004 == 1) {
		LegoFloat elapsedMs = static_cast<LegoFloat>(m_unk0x050);
		LegoFloat elapsed = elapsedMs / static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x054));
		m_unk0x220 = (1.0f - elapsed) * m_unk0x21c;

		GolVec3 position;
		m_unk0x008->VTable0x04(&position);
		FUN_00444540(&position, elapsedMs, m_unk0x220);

		result = 1;
	}

	return result;
}

// STUB: LEGORACERS 0x00444540
void RacePowerupManager::Field0x238::FUN_00444540(const GolVec3* p_position, LegoFloat p_elapsedMs, LegoFloat p_amount)
{
	LegoFloat elapsedStep = p_elapsedMs;
	elapsedStep *= g_unk0x004b02e0;
	elapsedStep *= 0.001f;

	GolVec3 origin;
	m_unk0x09c->m_unk0x018.m_unk0x044->VTable0x04(&origin);
	origin.m_z += m_unk0x218;

	GolVec3 delta;
	delta.m_x = p_position->m_x - origin.m_x;
	delta.m_y = p_position->m_y - origin.m_y;
	delta.m_z = p_position->m_z - origin.m_z;

	GolVec3 step;
	step.m_x = delta.m_x * g_unk0x004b02e0;
	step.m_y = delta.m_y * g_unk0x004b02e0;
	step.m_z = delta.m_z;
	m_unk0x0a8.FUN_00493ea0(&origin, &step);

	LegoFloat elapsed = 0.0f;
	GolVec3 position = origin;
	for (LegoU32 i = 0; i < 4; i++) {
		elapsed += elapsedStep;
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z = (m_unk0x040 * 0.5f * elapsed * elapsed) + (m_unk0x03c * elapsed) + m_unk0x010.m_z;
		m_unk0x0a8.FUN_00494870(&position, p_amount);
		p_amount = -p_amount;
	}

	m_unk0x0a8.FUN_00494870(p_position, p_amount);
	m_unk0x0a8.FUN_00494230();
}

// FUNCTION: LEGORACERS 0x00444670
void RacePowerupManager::Field0x238::VTable0x24(GolD3DRenderDevice* p_renderer)
{
	m_unk0x0a8.FUN_00494850(p_renderer);
}

// STUB: LEGORACERS 0x00444690
LegoS32 RacePowerupManager::Field0x238::FUN_00444690(LegoU32 p_elapsedMs)
{
	GolVec3 position;
	m_unk0x09c->m_unk0x018.m_unk0x044->VTable0x04(&position);
	position.m_z += m_unk0x218;

	if (GolMath::FUN_00449a90(
			&m_unk0x228,
			&position,
			g_unk0x004b0c98,
			g_unk0x004b0ca0,
			static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs))
		)) {
		m_unk0x234 = 0;
		return 4;
	}

	m_unk0x224 -= g_unk0x004b0c9c * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_unk0x224 < 0.0f) {
		m_unk0x224 = 0.0f;
	}

	LegoFloat amount = m_unk0x224 * g_unk0x004b0ca4;
	GolVec3 delta;
	delta.m_x = m_unk0x228.m_x - position.m_x;
	delta.m_y = m_unk0x228.m_y - position.m_y;
	delta.m_z = m_unk0x228.m_z - position.m_z;

	GolVec3 step;
	step.m_x = delta.m_x * g_unk0x004b02e0;
	step.m_y = delta.m_y * g_unk0x004b02e0;
	step.m_z = delta.m_z * g_unk0x004b02e0;
	m_unk0x0a8.FUN_00493ea0(&position, &step);

	for (LegoU32 i = 0; i < 4; i++) {
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z += step.m_z;
		m_unk0x0a8.FUN_00494870(&position, amount);
		amount = -amount;
	}

	m_unk0x0a8.FUN_00494870(&m_unk0x228, amount);
	m_unk0x0a8.FUN_00494230();

	return 1;
}

// STUB: LEGORACERS 0x00444820
LegoS32 RacePowerupManager::Field0x238::FUN_00444820(LegoU32 p_elapsedMs)
{
	GolVec3 targetPosition;
	m_unk0x0a4->m_unk0x018.m_unk0x044->VTable0x04(&targetPosition);
	targetPosition.m_z += g_unk0x004b0c90;

	GolVec3 currentPosition;
	m_unk0x008->VTable0x04(&currentPosition);

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

	m_unk0x008->VTable0x08(currentPosition);

	GolVec3 origin;
	m_unk0x09c->m_unk0x018.m_unk0x044->VTable0x04(&origin);
	origin.m_z += m_unk0x218;

	GolVec3 delta;
	delta.m_x = currentPosition.m_x - origin.m_x;
	delta.m_y = currentPosition.m_y - origin.m_y;
	delta.m_z = currentPosition.m_z - origin.m_z;

	m_unk0x224 += g_unk0x004b0c9c * static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	if (m_unk0x224 >= 1.0f) {
		GolBoundingVolume::Field0x0c record;
		m_unk0x224 = 1.0f;
		if (m_unk0x00c->FUN_0041f730(&origin, &currentPosition, &record, &m_unk0x028)) {
			m_unk0x05c = record.m_unk0x24;
			return 3;
		}
	}

	LegoFloat remainingAmount = 1.0f - m_unk0x224;
	GolVec3 step;
	step.m_x = delta.m_x * 0.2f;
	step.m_y = delta.m_y * 0.2f;
	step.m_z = delta.m_z * 0.2f;
	m_unk0x0a8.FUN_00493ea0(&origin, &step);

	LegoFloat elapsedStep = static_cast<LegoFloat>(m_unk0x054) * 0.2f * 0.001f;
	LegoFloat elapsed = 0.0f;
	GolVec3 position = origin;
	for (LegoU32 i = 0; i < 4; i++) {
		elapsed += elapsedStep;
		position.m_x += step.m_x;
		position.m_y += step.m_y;
		position.m_z += step.m_z;

		GolVec3 blended = position;
		blended.m_z =
			(((m_unk0x040 * 0.5f * elapsed * elapsed) + (m_unk0x03c * elapsed) + m_unk0x010.m_z) * remainingAmount) +
			(m_unk0x224 * position.m_z);
		m_unk0x0a8.FUN_00494870(&blended, 0.0f);
	}

	m_unk0x0a8.FUN_00494870(&currentPosition, 0.0f);
	m_unk0x0a8.FUN_00494230();

	return 2;
}

// FUNCTION: LEGORACERS 0x00444ac0
void RacePowerupManager::Field0x238::FUN_00444ac0(GolVec3* p_unk0x04)
{
	m_unk0x228.m_x = p_unk0x04->m_x;
	m_unk0x228.m_y = p_unk0x04->m_y;
	m_unk0x228.m_z = p_unk0x04->m_z;

	if (m_unk0x0a4 == NULL) {
		m_unk0x224 = m_unk0x220 / g_unk0x004b0ca4;
	}

	m_unk0x234 |= c_flags0x234Bit1;
}
