#include "amberlens0x344.h"

#include "bronzefalcon0xc8770.h"
#include "slatepeak0x58.h"

DECOMP_SIZE_ASSERT(AmberLens0x344, 0x344)

// FUNCTION: GOLDP 0x10001ea0
AmberLens0x344::AmberLens0x344()
{
	m_unk0x04 = &m_unk0x120;
	m_unk0x340 = NULL;
}

// FUNCTION: GOLDP 0x10001f00
AmberLens0x344::~AmberLens0x344()
{
	if (m_unk0x340) {
		m_unk0x340->VTable0x24();
	}
}

// FUNCTION: GOLDP 0x10001f60
void AmberLens0x344::FUN_10001f60(BronzeFalcon0xc8770* p_renderer)
{
	m_unk0x340 = p_renderer;
	if (p_renderer != NULL) {
		const SlatePeak0x58* renderTargetInfo = p_renderer->GetRenderTargetInfo();
		if (m_unk0x11c == 0 || m_unk0x118 == 0) {
			m_unk0x110 = 0;
			m_unk0x114 = 0;
			m_unk0x118 = renderTargetInfo->GetWidth();
			m_unk0x11c = renderTargetInfo->GetHeight();
		}

		if (!(m_flags & c_flagBit3)) {
			LegoFloat width = static_cast<LegoFloat>(m_unk0x118 - m_unk0x110);
			LegoFloat height = static_cast<LegoFloat>(m_unk0x11c - m_unk0x114);
			m_unk0x0c = width / height;
		}

		m_unk0x120.m_unk0x210 = static_cast<LegoFloat>(m_unk0x118 - m_unk0x110);
		m_unk0x120.m_unk0x214 = static_cast<LegoFloat>(m_unk0x11c - m_unk0x114);
		m_unk0x120.m_unk0x218 = static_cast<LegoFloat>(m_unk0x110);
		m_unk0x120.m_unk0x21c = static_cast<LegoFloat>(m_unk0x114);
		m_flags |= c_flagBit0 | c_flagBit1;
	}
}

// STUB: GOLDP 0x10002060
void AmberLens0x344::VTable0x28()
{
	STUB(0x10002060);
}

// STUB: GOLDP 0x10002160
void AmberLens0x344::VTable0x00()
{
	STUB(0x10002160);
}

// STUB: GOLDP 0x10002370
void AmberLens0x344::VTable0x04()
{
	STUB(0x10002370);
}

// STUB: GOLDP 0x10002430
void AmberLens0x344::VTable0x14()
{
	STUB(0x10002430);
}

// STUB: GOLDP 0x100024d0
void AmberLens0x344::VTable0x18()
{
	STUB(0x100024d0);
}

// STUB: GOLDP 0x10002570
void AmberLens0x344::VTable0x1c()
{
	STUB(0x10002570);
}

// STUB: GOLDP 0x10002630
void AmberLens0x344::VTable0x10()
{
	STUB(0x10002630);
}

// STUB: GOLDP 0x10002660
void AmberLens0x344::VTable0x0c(Rect*)
{
	STUB(0x10002660);
}

// STUB: GOLDP 0x10002770
void AmberLens0x344::VTable0x20(undefined4, undefined4)
{
	STUB(0x10002770);
}
