#include "saffronquartz0x2c.h"

#include "gol.h"
#include "zoweeblubberworth0xf0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(SaffronQuartz0x2c, 0x2c)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8, 0xb8)

// FUNCTION: LEGORACERS 0x00405890
SaffronQuartz0x2c::Frame0xb8::Frame0xb8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004058a0
SaffronQuartz0x2c::Frame0xb8::~Frame0xb8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004058b0
void SaffronQuartz0x2c::Frame0xb8::Reset()
{
	m_unk0x00 = 0;
	m_unk0x54 = 30;
	m_unk0x58 = 30;
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = NULL;
	m_unk0x44 = 0;
	m_unk0x4c = 0;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0xa4 = 0.0f;
	m_unk0x5c = 0;
	::memset(m_unk0x60, 0, sizeof(m_unk0x60));
	m_unk0x80 = 0;
	m_unk0x84 = 0;
	::memset(m_unk0x88, 0, sizeof(m_unk0x88));
	m_unk0xa8.m_bottom = 0;
	m_unk0xa8.m_top = 0;
	m_unk0xa8.m_left = 0;
	m_unk0xa8.m_right = 0;
}

// FUNCTION: LEGORACERS 0x004062a0
void SaffronQuartz0x2c::Frame0xb8::Destroy()
{
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}

	if (m_unk0x38) {
		delete[] m_unk0x38;
	}

	if (m_unk0x08) {
		m_unk0x08->VTable0x00(3);
	}

	if (m_unk0x10) {
		m_unk0x10->VTable0x00(3);
	}

	if (m_unk0x18) {
		m_unk0x18->VTable0x00(3);
	}

	if (m_unk0x20) {
		m_unk0x20->VTable0x00(3);
	}

	if (m_unk0x28) {
		m_unk0x28->VTable0x00(3);
	}

	Reset();
}

// STUB: LEGORACERS 0x00406310
void SaffronQuartz0x2c::Frame0xb8::FUN_00406310()
{
	STUB(0x00406310);
}

// STUB: LEGORACERS 0x00406330
void SaffronQuartz0x2c::Frame0xb8::FUN_00406330()
{
	STUB(0x00406330);
}

// STUB: LEGORACERS 0x00406380
void SaffronQuartz0x2c::Frame0xb8::FUN_00406380()
{
	STUB(0x00406380);
}

// STUB: LEGORACERS 0x00406390
void SaffronQuartz0x2c::Frame0xb8::FUN_00406390(undefined4)
{
	STUB(0x00406390);
}

// STUB: LEGORACERS 0x00406490
void SaffronQuartz0x2c::Frame0xb8::FUN_00406490(Rect*)
{
	STUB(0x00406490);
}

// STUB: LEGORACERS 0x004064c0
void SaffronQuartz0x2c::Frame0xb8::FUN_004064c0(BronzeFalcon0xc8770*, undefined4)
{
	STUB(0x004064c0);
}

// STUB: LEGORACERS 0x004065a0
void SaffronQuartz0x2c::Frame0xb8::FUN_004065a0(undefined4)
{
	STUB(0x004065a0);
}

// STUB: LEGORACERS 0x004065d0
void SaffronQuartz0x2c::Frame0xb8::FUN_004065d0(LegoU32, LegoU32)
{
	STUB(0x004065d0);
}

// STUB: LEGORACERS 0x00406680
void SaffronQuartz0x2c::Frame0xb8::FUN_00406680(undefined4)
{
	STUB(0x00406680);
}

// STUB: LEGORACERS 0x004066b0
void SaffronQuartz0x2c::Frame0xb8::FUN_004066b0(undefined4)
{
	STUB(0x004066b0);
}

// STUB: LEGORACERS 0x004066d0
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_004066d0(undefined4)
{
	STUB(0x004066d0);
	return 0;
}

// STUB: LEGORACERS 0x00406710
void SaffronQuartz0x2c::Frame0xb8::FUN_00406710(undefined4)
{
	STUB(0x00406710);
}

// STUB: LEGORACERS 0x00406760
void SaffronQuartz0x2c::Frame0xb8::FUN_00406760(undefined4)
{
	STUB(0x00406760);
}

// STUB: LEGORACERS 0x00406770
void SaffronQuartz0x2c::Frame0xb8::FUN_00406770(undefined4)
{
	STUB(0x00406770);
}

// STUB: LEGORACERS 0x00406790
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_00406790(undefined4)
{
	STUB(0x00406790);
	return 0;
}

// STUB: LEGORACERS 0x004067f0
void SaffronQuartz0x2c::Frame0xb8::FUN_004067f0(undefined4)
{
	STUB(0x004067f0);
}

// STUB: LEGORACERS 0x00406860
void SaffronQuartz0x2c::Frame0xb8::FUN_00406860()
{
	STUB(0x00406860);
}

// STUB: LEGORACERS 0x00406890
undefined4 SaffronQuartz0x2c::Frame0xb8::FUN_00406890()
{
	STUB(0x00406890);
	return 0;
}

// FUNCTION: LEGORACERS 0x004068a0
SaffronQuartz0x2c::SaffronQuartz0x2c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00406910
SaffronQuartz0x2c::~SaffronQuartz0x2c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00406960
void SaffronQuartz0x2c::Reset()
{
	m_unk0x0c = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x18 = 0;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_frameCount = 0;
	m_frames = NULL;
}

// STUB: LEGORACERS 0x00406980
void SaffronQuartz0x2c::FUN_00406980(GolExport*, BronzeFalcon0xc8770*, const LegoChar*, undefined4)
{
	STUB(0x00406980);
}

// FUNCTION: LEGORACERS 0x00406af0
void SaffronQuartz0x2c::Clear()
{
	if (m_unk0x1c) {
		if (m_golExport) {
			LegoU32 i;
			for (i = 0; i < m_unk0x18; i++) {
				if (m_unk0x1c[i]) {
					m_unk0x1c[i]->VTable0x18();
					m_golExport->VTable0x3c(m_unk0x1c[i]);
				}
			}
		}

		delete[] m_unk0x1c;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_frames) {
		delete[] m_frames;
	}

	GolNameTable::Clear();
	Reset();
}

// STUB: LEGORACERS 0x00406b90
void SaffronQuartz0x2c::FUN_00406b90(undefined4)
{
	STUB(0x00406b90);
}

// STUB: LEGORACERS 0x00406c50
void SaffronQuartz0x2c::FUN_00406c50(undefined4)
{
	STUB(0x00406c50);
}

// STUB: LEGORACERS 0x00406cb0
void SaffronQuartz0x2c::FUN_00406cb0(undefined4)
{
	STUB(0x00406cb0);
}

// STUB: LEGORACERS 0x00406de0
undefined4 SaffronQuartz0x2c::FUN_00406de0(const LegoChar*)
{
	STUB(0x00406de0);
	return 0;
}

// STUB: LEGORACERS 0x00406e30
undefined4 SaffronQuartz0x2c::FUN_00406e30(const LegoChar*)
{
	STUB(0x00406e30);
	return 0;
}

// STUB: LEGORACERS 0x00406e80
undefined4 SaffronQuartz0x2c::FUN_00406e80(const LegoChar*)
{
	STUB(0x00406e80);
	return 0;
}

// STUB: LEGORACERS 0x00406ed0
undefined4 SaffronQuartz0x2c::FUN_00406ed0(const LegoChar*)
{
	STUB(0x00406ed0);
	return 0;
}

// STUB: LEGORACERS 0x00406f20
undefined4 SaffronQuartz0x2c::FUN_00406f20(LegoU32, undefined4)
{
	STUB(0x00406f20);
	return 0;
}

// STUB: LEGORACERS 0x00406f40
undefined4 SaffronQuartz0x2c::FUN_00406f40(LegoU32, undefined4)
{
	STUB(0x00406f40);
	return 0;
}

// STUB: LEGORACERS 0x00406f60
undefined4 SaffronQuartz0x2c::FUN_00406f60(LegoU32, undefined4, undefined4)
{
	STUB(0x00406f60);
	return 0;
}

// STUB: LEGORACERS 0x00406f90
LegoU32 SaffronQuartz0x2c::FUN_00406f90(LegoFloat)
{
	STUB(0x00406f90);
	return 0;
}
