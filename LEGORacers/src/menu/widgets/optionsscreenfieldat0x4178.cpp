#include "menu/widgets/optionsscreenfieldat0x4178.h"

DECOMP_SIZE_ASSERT(OptionsScreenFieldAt0x4178Base0x6dc, 0x6dc)
DECOMP_SIZE_ASSERT(OptionsScreenFieldAt0x4178, 0x6ec)

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 OptionsScreenFieldAt0x4178Base0x6dc::VTable0x3c(undefined4)
{
	return NULL;
}

// FUNCTION: LEGORACERS 0x0046de60
OptionsScreenFieldAt0x4178Base0x6dc::OptionsScreenFieldAt0x4178Base0x6dc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046def0
OptionsScreenFieldAt0x4178Base0x6dc::~OptionsScreenFieldAt0x4178Base0x6dc()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046df60
void OptionsScreenFieldAt0x4178Base0x6dc::Reset()
{
	m_unk0x6c0 = 0;
	m_unk0x6c8 = 0;
	m_unk0x6c4 = 0;
	m_unk0x6cc = 0.0f;
	m_unk0x5e8 = NULL;
	m_unk0x648.VTable0x08();
	m_unk0x5ec.VTable0x08();
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x0046e090
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x14(VisualState0x4* p_visualState)
{
	m_unk0x648.VTable0x14(p_visualState);
	m_unk0x5ec.VTable0x14(p_visualState);
	ObscureVantage0x58::VTable0x14(p_visualState);
}

// STUB: LEGORACERS 0x0046e0d0
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x78()
{
	STUB(0x0046e0d0);
}

// STUB: LEGORACERS 0x0046e130
void OptionsScreenFieldAt0x4178Base0x6dc::VTable0x7c()
{
	STUB(0x0046e130);
}

// STUB: LEGORACERS 0x0046e190
undefined4 OptionsScreenFieldAt0x4178Base0x6dc::VTable0x74(undefined4)
{
	STUB(0x0046e190);
	return 0;
}

// STUB: LEGORACERS 0x0046e210
ObscureVantage0x58* OptionsScreenFieldAt0x4178Base0x6dc::VTable0x30(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0046e210);
	return NULL;
}

// STUB: LEGORACERS 0x0046e340
ObscureVantage0x58* OptionsScreenFieldAt0x4178Base0x6dc::VTable0x34(InputEventQueue::Event*, undefined4, undefined4)
{
	STUB(0x0046e340);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0046e3f0
OptionsScreenFieldAt0x4178::OptionsScreenFieldAt0x4178()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046e460
OptionsScreenFieldAt0x4178::~OptionsScreenFieldAt0x4178()
{
	VTable0x08();
}

// STUB: LEGORACERS 0x0046e530
void OptionsScreenFieldAt0x4178::VTable0x80()
{
	STUB(0x0046e530);
}

// STUB: LEGORACERS 0x0046e5b0
void OptionsScreenFieldAt0x4178::VTable0x84()
{
	STUB(0x0046e5b0);
}

// STUB: LEGORACERS 0x0046e630
void OptionsScreenFieldAt0x4178::VTable0x88()
{
	STUB(0x0046e630);
}

// STUB: LEGORACERS 0x0046e6b0
void OptionsScreenFieldAt0x4178::VTable0x8c()
{
	STUB(0x0046e6b0);
}

// STUB: LEGORACERS 0x0046e6f0
void OptionsScreenFieldAt0x4178::VTable0x90(LegoS32)
{
	STUB(0x0046e6f0);
}

// STUB: LEGORACERS 0x0046e780
undefined4 OptionsScreenFieldAt0x4178::VTable0x70(undefined4, undefined4, undefined4)
{
	STUB(0x0046e780);
	return 0;
}

// STUB: LEGORACERS 0x0046e810
ObscureVantage0x58* OptionsScreenFieldAt0x4178::VTable0x2c(void*, undefined4, undefined4)
{
	STUB(0x0046e810);
	return NULL;
}
