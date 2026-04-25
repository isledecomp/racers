#include "hypnoticnoise0x1c.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

DECOMP_SIZE_ASSERT(HypnoticNoise0x1c, 0x1c)
DECOMP_SIZE_ASSERT(HypnoticNoise0x1cInner, 0xa4)

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
	if (m_unk0x14 > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);

	GolFileParser* parser;

	if (p_param3) {
		parser = new GolBinParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		parser->SetSuffix(".idb");
	}
	else {
		parser = new GolTxtParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->VTable0x38((undefined4) p_param2);
	parser->FUN_10032740(0x27);
	m_unk0x14 = parser->FUN_100327e0();

	// TODO: Incomplete
}

// FUNCTION: GOLDP 0x100233a0
void HypnoticNoise0x1c::VTable0x1c(BronzeFalcon0xc8770* p_param1, LegoU32 p_param2)
{
	if (m_unk0x14 > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);
	m_unk0x14 = p_param2;

	VTable0x0c();

	for (LegoU32 i = 0; i < p_param2; i++) {
		VTable0x20(i)->m_unk0x24 = p_param1;
	}
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
