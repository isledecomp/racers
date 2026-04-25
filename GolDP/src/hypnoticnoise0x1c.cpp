#include "hypnoticnoise0x1c.h"

#include "bronzefalcon0xc8770.h"

DECOMP_SIZE_ASSERT(HypnoticNoise0x1c, 0x1c)

// FUNCTION: GOLDP 0x10022fa0
HypnoticNoise0x1c::HypnoticNoise0x1c()
{
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// FUNCTION: GOLDP 0x10022fe0
#pragma inline_depth(0)
HypnoticNoise0x1c::~HypnoticNoise0x1c()
{
	m_unk0x14 = 0;

	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
	}
}
#pragma inline_depth()

// STUB: GOLDP 0x10023060
void HypnoticNoise0x1c::VTable0x18(BronzeFalcon0xc8770* p_param1, char* p_param2, undefined4 p_param3)
{
	if (m_unk0x14) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;

	STUB(0x10023060);
}

// STUB: GOLDP 0x100233a0
void HypnoticNoise0x1c::VTable0x1c()
{
	STUB(0x100233a0);
}

// FUNCTION: GOLDP 0x100233f0
void HypnoticNoise0x1c::VTable0x08()
{
	m_unk0x14 = 0;
	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x14()
{
	// empty
}
