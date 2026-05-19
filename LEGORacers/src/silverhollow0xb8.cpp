#include "silverhollow0xb8.h"

DECOMP_SIZE_ASSERT(AmberMeadow0x58, 0x58)
DECOMP_SIZE_ASSERT(SilverHollow0xb8, 0xb8)

// GLOBAL: LEGORACERS 0x004af750
LegoFloat g_unk0x004af750 = -1.0f;

// STUB: LEGORACERS 0x00403c90
void AmberMeadow0x58::VTable0x48(LegoFloat*, LegoFloat*)
{
	STUB(0x00403c90);
}

// FUNCTION: LEGORACERS 0x004108a0
AmberMeadow0x58::AmberMeadow0x58()
{
	FUN_004108c0();
}

// FUNCTION: LEGORACERS 0x004108c0
void AmberMeadow0x58::FUN_004108c0()
{
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 1.0f;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 1.0f;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 1.0f;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
}

// STUB: LEGORACERS 0x00410900
void AmberMeadow0x58::VTable0x40(LegoFloat*, LegoFloat*)
{
	STUB(0x00410900);
}

// STUB: LEGORACERS 0x00410c00
void AmberMeadow0x58::VTable0x44(LegoFloat*)
{
	STUB(0x00410c00);
}

// STUB: LEGORACERS 0x00410c40
void AmberMeadow0x58::VTable0x3c(LegoFloat*)
{
	STUB(0x00410c40);
}

// STUB: LEGORACERS 0x00410c80
void AmberMeadow0x58::VTable0x34(LegoFloat*, LegoFloat*)
{
	STUB(0x00410c80);
}

// STUB: LEGORACERS 0x00410cf0
void AmberMeadow0x58::VTable0x38(LegoFloat*, LegoFloat*)
{
	STUB(0x00410cf0);
}

// STUB: LEGORACERS 0x00410d60
void AmberMeadow0x58::VTable0x2c(LegoFloat*, LegoFloat*)
{
	STUB(0x00410d60);
}

// STUB: LEGORACERS 0x00410de0
void AmberMeadow0x58::VTable0x30(LegoFloat*, LegoFloat*)
{
	STUB(0x00410de0);
}

// STUB: LEGORACERS 0x00410ea0
void AmberMeadow0x58::VTable0x04(LegoFloat*)
{
	STUB(0x00410ea0);
}

// STUB: LEGORACERS 0x00410ec0
void AmberMeadow0x58::VTable0x08(LegoFloat*)
{
	STUB(0x00410ec0);
}

// FUNCTION: LEGORACERS 0x00411150
SilverHollow0xb8::SilverHollow0xb8()
{
	m_unk0x58 = 1.0f;
	m_unk0x10 = -1.0f;
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
	m_unk0x10 = -1.0f;
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

	FUN_004108c0();
}

// STUB: LEGORACERS 0x004112c0
void SilverHollow0xb8::VTable0x14(undefined4, undefined4)
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
void SilverHollow0xb8::VTable0x10(undefined4)
{
	STUB(0x00411470);
}

// STUB: LEGORACERS 0x00411560
void SilverHollow0xb8::VTable0x1c(undefined4)
{
	STUB(0x00411560);
}

// STUB: LEGORACERS 0x004115f0
void SilverHollow0xb8::VTable0x24(undefined4)
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
