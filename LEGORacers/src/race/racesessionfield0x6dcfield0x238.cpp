#include "decomp.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x238, 0x238)

// FUNCTION: LEGORACERS 0x00444250
RaceSession::Field0x6dc::Field0x238::Field0x238()
{
	m_unk0x218 = 0;
	m_unk0x21c = 0;
	m_unk0x220 = 0;
	m_unk0x224 = 0;
	m_unk0x234 = 0;
}

// STUB: LEGORACERS 0x004442c0
RaceSession::Field0x6dc::Field0xa8* RaceSession::Field0x6dc::Field0x238::VTable0x10(undefined4 p_flags)
{
	Field0x238* result = this;
	this->~Field0x238();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004442e0
RaceSession::Field0x6dc::Field0x238::~Field0x238()
{
	VTable0x14();
}

// FUNCTION: LEGORACERS 0x00444340
void RaceSession::Field0x6dc::Field0x238::VTable0x20(const SetupParams* p_params)
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
	params.m_unk0x54 = 0;
	params.m_unk0x58 = 0x3f000000;
	params.m_unk0x5c = 0x3f800000;
	params.m_unk0x68 = 3;
	params.m_modelDistance = 360000.0f;
	params.m_unk0x70 = 0;

	m_unk0x0a8.FUN_00493c90(&params);
	m_unk0x0a8.FUN_00494820(&p_params->m_unk0x10, &p_params->m_unk0x14, &p_params->m_unk0x18);
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00444470
void RaceSession::Field0x6dc::Field0x238::VTable0x14()
{
	Field0xa8::VTable0x14();
	m_unk0x0a8.FUN_00493e60();
}
