#include "glassstream0x94.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(GlassStream0x94, 0x94)

// FUNCTION: LEGORACERS 0x0041ec10
GlassStream0x94::GlassStream0x94()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0041ec90
GlassStream0x94::~GlassStream0x94()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0041ece0
void GlassStream0x94::Reset()
{
	m_context = NULL;
	m_unk0x50 = NULL;

	for (LegoS32 i = 0; i < 2; i++) {
		for (LegoS32 j = 0; j < 4; j++) {
			m_unk0x54[i][j][0] = 0;
			m_unk0x54[i][j][1] = 0;
		}
	}
}

// FUNCTION: LEGORACERS 0x0041ed10
LegoS32 GlassStream0x94::Initialize(LegoRacers::Context* p_context, GlassBlock0x3368* p_block)
{
	if (m_context) {
		Shutdown();
	}

	m_context = p_context;
	m_unk0x50 = p_block;
	sprintf(p_context->m_gameDataDirectory, "GAMEDATA\\COMMON");
	return m_unk0x04.SetContext(m_context);
}

// FUNCTION: LEGORACERS 0x0041ed60
void GlassStream0x94::Shutdown()
{
	m_unk0x04.FUN_004402a0();
	Reset();
}
