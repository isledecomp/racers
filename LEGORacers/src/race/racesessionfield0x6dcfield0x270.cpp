#include "decomp.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270, 0x270)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270::Field0x34, 0x5c)

// GLOBAL: LEGORACERS 0x004b015c
LegoFloat g_unk0x004b015c = 180.0f;

// FUNCTION: LEGORACERS 0x004214b0
void RaceSession::Field0x6dc::Field0x270::FUN_004214b0()
{
	FUN_004217b0();
	m_unk0x0e4.FUN_004149f0();
	m_unk0x204.Clear();
	m_unk0x034.VTable0x54();

	if (m_unk0x030 != NULL && m_unk0x0c4 != NULL) {
		m_unk0x0c4->VTable0x50();
		m_unk0x030->VTable0x64(m_unk0x0c4);
		m_unk0x0c4 = NULL;
	}

	m_unk0x0c8.Reset();
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x004217b0
void RaceSession::Field0x6dc::Field0x270::FUN_004217b0()
{
	if (m_unk0x220 != NULL) {
		m_unk0x220->ClearUnk0x24();
		m_unk0x220 = NULL;
	}

	m_unk0x04 = 1;
}

// FUNCTION: LEGORACERS 0x00421ae0
void RaceSession::Field0x6dc::Field0x270::FUN_00421ae0(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x04 == 0 || m_unk0x04 == 1) {
		return;
	}

	if (m_unk0x04 == 2) {
		if (m_unk0x214 != 0 && m_unk0x268 != 0) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(g_unk0x004b015c), 2);
			m_unk0x0e4.FUN_00415a40(p_renderer);
		}

		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x23c), 1);

		if (m_unk0x0c4 != NULL) {
			p_renderer->VTable0xb4(*m_unk0x0c4);
		}

		if (m_flags0x090 & c_flag0x090Bit0) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x240), 1);
			m_unk0x034.VTable0x1c(p_renderer);
		}

		p_renderer->ClearAlphaOverride();
		return;
	}

	if (m_unk0x04 == 3 && m_unk0x214 != 0 && m_unk0x268 != 0) {
		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x23c), 2);
		m_unk0x0e4.FUN_00415a40(p_renderer);
		p_renderer->ClearAlphaOverride();
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x6dc::Field0x270::FUN_004513d0(GolD3DRenderDevice*)
{
}
