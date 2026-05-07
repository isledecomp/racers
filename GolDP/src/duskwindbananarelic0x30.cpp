#include "duskwindbananarelic0x30.h"

#include "golcommondrawstate.h"
#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(DuskwindBananaRelic0x30, 0x30)

// FUNCTION: GOLDP 0x10006280
DuskwindBananaRelic0x30::DuskwindBananaRelic0x30()
{
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
}

// FUNCTION: GOLDP 0x100062a0
DuskwindBananaRelic0x30::~DuskwindBananaRelic0x30()
{
	Destroy();
}

// STUB: GOLDP 0x10006320
void DuskwindBananaRelic0x30::FUN_10006320(WhiteFalcon0x140& p_renderer)
{
	// TODO
	STUB(0x10006320);
}

// FUNCTION: GOLDP 0x10006490
void DuskwindBananaRelic0x30::Destroy()
{
	if (m_unk0x2c != NULL) {
		delete m_unk0x2c;
		m_unk0x2c = NULL;
	}
	if (m_unk0x24 != NULL) {
		m_unk0x24->Release();
		m_unk0x24 = NULL;
	}
	m_unk0x28 = 0;
	m_unk0x08 &= ~c_flagBit0;
}
