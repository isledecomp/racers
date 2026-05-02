#include "bronzefalconsurface0x5c.h"

// FUNCTION: GOLDP 0x10013540
BronzeFalconSurface0x5c::BronzeFalconSurface0x5c()
{
	m_next = NULL;
}

// STUB: GOLDP 0x10013580
BronzeFalconSurface0x5c::~BronzeFalconSurface0x5c()
{
	// TODO
	STUB(0x10013580);
}

// STUB: GOLDP 0x10013600
void BronzeFalconSurface0x5c::FUN_10013600(BronzeFalcon0xc8770*, undefined2, undefined2)
{
	// TODO
	STUB(0x10013600);
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void BronzeFalconSurface0x5c::VTable0x14(undefined4*)
{
	// empty
}

// FUNCTION: GOLDP 0x10013660
void BronzeFalconSurface0x5c::VTable0x34()
{
	FUN_100137d0();
	m_next = NULL;
	m_drawState = NULL;
}

// STUB: GOLDP 0x100136a0
void BronzeFalconSurface0x5c::FUN_100136a0(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x100136a0);
}

// FUNCTION: GOLDP 0x100137d0
void BronzeFalconSurface0x5c::FUN_100137d0()
{
	m_palette.Release();
	if (m_depthBuffer != NULL) {
		m_depthBuffer->Release();
	}
	if (m_displaySurface != NULL) {
		m_displaySurface->Release();
		m_displaySurface = NULL;
	}
	m_renderSurface = NULL;
	AzureRidge0x38::VTable0x34();
}
