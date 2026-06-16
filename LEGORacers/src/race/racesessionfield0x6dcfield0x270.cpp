#include "decomp.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270, 0x270)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270::Field0x34, 0x5c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270::Field0x224, 0x20)

// GLOBAL: LEGORACERS 0x004b015c
LegoFloat g_unk0x004b015c = 180.0f;

extern const LegoFloat g_violetShoalTwo;

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

// FUNCTION: LEGORACERS 0x004217d0
void RaceSession::Field0x6dc::Field0x270::FUN_004217d0(LegoU32 p_elapsedMs)
{
	if (m_unk0x04 == 2) {
		FUN_00421850(p_elapsedMs);
	}

	if (m_unk0x04 == 3) {
		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		m_unk0x23c += elapsedSeconds * m_unk0x244;
		if (m_unk0x23c < 0.0f) {
			m_unk0x23c = 0.0f;
		}

		LegoU32 duration = m_unk0x238;
		if (p_elapsedMs >= duration) {
			m_unk0x238 = 0;
			FUN_004217b0();
		}
		else {
			m_unk0x238 = duration - p_elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x00421850
void RaceSession::Field0x6dc::Field0x270::FUN_00421850(LegoU32 p_elapsedMs)
{
	LegoS32 zero = 0;
	if (m_unk0x04 != zero && m_unk0x04 != 1) {
		LegoU32 duration = m_unk0x238;
		if (p_elapsedMs >= duration) {
			if (m_unk0x214 != NULL && m_unk0x268 != zero) {
				if (m_unk0x220 != NULL) {
					m_unk0x220->ClearUnk0x24();
					m_unk0x220 = NULL;
				}

				LegoU32 finishDuration = m_unk0x234;
				m_unk0x04 = 3;
				LegoFloat width = m_unk0x25c;
				LegoFloat width2 = m_unk0x25c;
				m_unk0x238 = finishDuration;
				m_unk0x23c = g_unk0x004b015c;
				m_unk0x0e4.m_unk0x104 = width;
				m_unk0x0e4.m_unk0x108 = width2;
				m_unk0x0e4.m_unk0x10c = 15.0f;
				m_unk0x0e4.FUN_00414a30(m_unk0x200);
			}
			else {
				FUN_004217b0();
			}

			return;
		}

		m_unk0x238 = duration - p_elapsedMs;

		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		LegoFloat acceleration = m_unk0x254;
		m_unk0x24c = acceleration * elapsedSeconds + m_unk0x24c;
		m_unk0x248 = elapsedSeconds * m_unk0x24c + m_unk0x248;

		LegoFloat radius = (m_unk0x264 - 0.1f) * m_unk0x248 + 0.1f;
		m_unk0x008.FUN_10026fa0(radius);

		LegoFloat width = (m_unk0x25c - 0.1f) * m_unk0x248 + 0.1f;
		if (m_unk0x214 != NULL && m_unk0x268 != zero) {
			m_unk0x204.SetPosition(0, m_unk0x214);
			m_unk0x0e4.m_unk0x104 = width;
			m_unk0x0e4.m_unk0x108 = width;
			m_unk0x0e4.m_unk0x10c = 15.0f;
			m_unk0x0e4.FUN_00414a30(m_unk0x200);
		}

		if (m_unk0x0c4 != NULL) {
			m_unk0x0c4->SetWidth(width);
			m_unk0x0c4->SetHeight((m_unk0x260 - 0.2f) * m_unk0x248 + 0.2f);
		}

		LegoFloat value = (m_unk0x258 - 0.050000001f) * m_unk0x248 + 0.050000001f;
		if (value > 1.0f) {
			value = 1.0f;
		}

		if (m_flags0x090 & c_flag0x090Bit0) {
			m_unk0x034.SetUnk0x58(value);
			m_unk0x034.SetUnk0x10(-1.0f);
		}

		m_unk0x23c = (g_violetShoalTwo - (m_unk0x248 + m_unk0x248)) * 255.0f;
		if (m_unk0x23c < 0.0f) {
			m_unk0x23c = 0.0f;
		}
		else if (m_unk0x23c > 255.0f) {
			m_unk0x23c = 255.0f;
		}

		m_unk0x240 = (1.0f - m_unk0x248) * 255.0f;
		if (m_unk0x240 < 0.0f) {
			m_unk0x240 = 0.0f;
		}

		if (m_unk0x0c8.IsConfigured()) {
			m_unk0x0c8.FUN_004104c0(p_elapsedMs, m_unk0x224->GetUnk0x18(), m_unk0x224->GetUnk0x1c());
		}
	}
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
