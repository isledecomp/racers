#include "silverhollow0xb8.h"

DECOMP_SIZE_ASSERT(FloatyBuoy0x58, 0x58)
DECOMP_SIZE_ASSERT(SilverHollow0xb8, 0xb8)

// GLOBAL: LEGORACERS 0x004af750
LegoFloat g_unk0x004af750 = -1.0f;

// FUNCTION: LEGORACERS 0x00411150
SilverHollow0xb8::SilverHollow0xb8()
{
	m_unk0x58 = 1.0f;
	m_radius = -1.0f;
	m_unk0x5c = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_unk0x84[i] = g_unk0x004af750;
		m_unk0x6c[i] = 0;
	}
}

// FUNCTION: LEGORACERS 0x004111b0
void SilverHollow0xb8::VTable0x50(IGdbModel0x40* p_model, LegoFloat p_unk0x08)
{
	if (m_unk0x5c & 1) {
		VTable0x54();
	}

	m_models[0] = p_model;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x84[0] = p_unk0x08;
	m_unk0x58 = 1.0f;
	m_radius = -1.0f;
	m_unk0x5c |= 1;
}

// FUNCTION: LEGORACERS 0x00411200
void SilverHollow0xb8::VTable0x54()
{
	m_unk0x58 = 1.0f;
	m_unk0x5c = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;

	for (LegoS32 i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_unk0x84[i] = g_unk0x004af750;
		m_unk0x6c[i] = 0;
	}

	Reset();
}

// STUB: LEGORACERS 0x004112c0
void SilverHollow0xb8::VTable0x14(const WhiteFalconView0xcc&, ViewResult*)
{
	STUB(0x004112c0);
}

// STUB: LEGORACERS 0x004113c0
void SilverHollow0xb8::VTable0x00()
{
	STUB(0x004113c0);
}

// STUB: LEGORACERS 0x004113d0
void SilverHollow0xb8::VTable0x4c(undefined4)
{
	STUB(0x004113d0);
}

// STUB: LEGORACERS 0x00411470
void SilverHollow0xb8::VTable0x10(LegoS32)
{
	STUB(0x00411470);
}

// STUB: LEGORACERS 0x00411560
void SilverHollow0xb8::VTable0x1c(WhiteFalcon0x140&)
{
	STUB(0x00411560);
}

// STUB: LEGORACERS 0x004115f0
void SilverHollow0xb8::VTable0x24(TransformPayload0x20*)
{
	STUB(0x004115f0);
}

// STUB: LEGORACERS 0x00411620
void SilverHollow0xb8::VTable0x28()
{
	STUB(0x00411620);
}

// STUB: LEGORACERS 0x00411760
LegoBool32 SilverHollow0xb8::VTable0x20()
{
	STUB(0x00411760);
	return FALSE;
}
