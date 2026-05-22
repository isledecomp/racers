#include "obscurecarousel0x78.h"

DECOMP_SIZE_ASSERT(ObscureCarousel0x78, 0x78)
DECOMP_SIZE_ASSERT(ObscureCarousel0x78::CreateParams0x38, 0x38)
DECOMP_SIZE_ASSERT(ObscureCarousel0x78::StyleEntry0x18, 0x18)
DECOMP_SIZE_ASSERT(ObscureCarousel0x94, 0x94)
DECOMP_SIZE_ASSERT(ObscureCarouselNavigator0x94, 0x94)

// FUNCTION: LEGORACERS 0x0046c880
ObscureCarousel0x78::ObscureCarousel0x78()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c8f0
ObscureCarousel0x78::~ObscureCarousel0x78()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c950
void ObscureCarousel0x78::Reset()
{
	m_unk0x6c = 0;
	m_unk0x68 = 0;
	m_unk0x60 = 0;
	m_unk0x58 = NULL;
	m_unk0x70 = 0;
	m_unk0x74 = 0;
	ObscureVantage0x58::Reset();
}

// FUNCTION: LEGORACERS 0x0046c970
LegoBool32 ObscureCarousel0x78::FUN_0046c970(CreateParams0x38* p_createParams, StyleEntry0x18* p_styleEntry)
{
	VTable0x08();
	m_unk0x58 = p_styleEntry;
	m_unk0x5c = p_createParams->m_soundGroupBinding;

	return FUN_00472a60(p_createParams);
}

// STUB: LEGORACERS 0x0046c9c0
void ObscureCarousel0x78::VTable0x14(VisualState0x4*)
{
	STUB(0x0046c9c0);
}

#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
ObscureVantage0x58* ObscureCarousel0x78::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void ObscureCarousel0x78::VTable0x48(undefined4, undefined4)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void ObscureCarousel0x78::VTable0x4c(undefined4, undefined4)
{
}

// FUNCTION: LEGORACERS 0x0046d820
ObscureCarousel0x94::ObscureCarousel0x94()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d890
ObscureCarousel0x94::~ObscureCarousel0x94()
{
	VTable0x08();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d8f0
void ObscureCarousel0x94::Reset()
{
	ObscureCarousel0x78::Reset();
	m_unk0x60 = 1;
	m_unk0x78 = NULL;
	m_unk0x90 = 0.0f;
	m_unk0x8c = 0.0f;
}

// FUNCTION: LEGORACERS 0x0046d960
void ObscureCarousel0x94::VTable0x50(undefined4 p_unk0x04)
{
	m_unk0x78 = FUN_00472ef0(p_unk0x04);
	m_unk0x6c = p_unk0x04;
	if (!m_unk0x70) {
		VTable0x40();
	}
}

// FUNCTION: LEGORACERS 0x0046d990
void ObscureCarousel0x94::VTable0x40()
{
	m_unk0x4c = m_unk0x78->GetRect()->m_left;

	if (m_unk0x58->m_unk0x10) {
		LegoS32 width = m_unk0x34.m_right - m_unk0x34.m_left;
		m_unk0x4c = (m_unk0x4c / width) * width;
	}
}

// FUNCTION: LEGORACERS 0x0046d9c0
void ObscureCarousel0x94::FUN_0046d9c0(ObscureVantage0x58* p_unk0x04)
{
	p_unk0x04->SetParent(this);
	p_unk0x04->VTable0x14(&m_visualState);
	m_unk0x68++;
	VTable0x5c(p_unk0x04);

	if (m_unk0x68 == 1) {
		VTable0x50(m_unk0x6c);
	}
}

// STUB: LEGORACERS 0x0046da80
void ObscureCarouselNavigator0x94::VTable0x5c(ObscureVantage0x58*)
{
	STUB(0x0046da80);
}

// STUB: LEGORACERS 0x0046db40
void ObscureCarouselNavigator0x94::VTable0x44(undefined4)
{
	STUB(0x0046db40);
}

// STUB: LEGORACERS 0x0046db80
LegoS32 ObscureCarouselNavigator0x94::VTable0x54()
{
	STUB(0x0046db80);
	return m_unk0x6c;
}

// STUB: LEGORACERS 0x0046dbf0
LegoS32 ObscureCarouselNavigator0x94::VTable0x58()
{
	STUB(0x0046dbf0);
	return m_unk0x6c;
}

// STUB: LEGORACERS 0x0046dc70
undefined4 ObscureCarouselNavigator0x94::VTable0x38(Rect*, Rect*)
{
	STUB(0x0046dc70);
	return 0;
}

// STUB: LEGORACERS 0x0046dd80
undefined4 ObscureCarouselNavigator0x94::VTable0x3c(undefined4)
{
	STUB(0x0046dd80);
	return 0;
}
