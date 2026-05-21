#include "obscurebanner0x5ec.h"

DECOMP_SIZE_ASSERT(ObscureBanner0x5ec, 0x5ec)
DECOMP_SIZE_ASSERT(ObscureBanner0x9f4, 0x9f4)

// FUNCTION: LEGORACERS 0x00466f60
ObscureBanner0x5ec::ObscureBanner0x5ec()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00466ff0
ObscureBanner0x5ec::~ObscureBanner0x5ec()
{
}

// FUNCTION: LEGORACERS 0x00467060
void ObscureBanner0x5ec::Reset()
{
	m_unk0x1ac.VTable0x08();
	m_unk0x3c8.VTable0x08();
	m_unk0x1a8 = 0;
	m_unk0x5e4 = 0;
	ObscureIcon0x1a8::Reset();
}

// STUB: LEGORACERS 0x00467240
void ObscureBanner0x5ec::VTable0x44(undefined4)
{
	STUB(0x00467240);
}

// STUB: LEGORACERS 0x00467290
void ObscureBanner0x5ec::VTable0x48(undefined4)
{
	STUB(0x00467290);
}

// STUB: LEGORACERS 0x004672e0
void ObscureBanner0x5ec::VTable0x4c(undefined4)
{
	STUB(0x004672e0);
}

// STUB: LEGORACERS 0x00467320
void ObscureBanner0x5ec::VTable0x50(undefined4)
{
	STUB(0x00467320);
}

// STUB: LEGORACERS 0x00467360
void ObscureBanner0x5ec::VTable0x58(undefined4)
{
	STUB(0x00467360);
}

// STUB: LEGORACERS 0x004673a0
undefined4 ObscureBanner0x5ec::VTable0x70(undefined4, undefined4, undefined4)
{
	STUB(0x004673a0);
	return 0;
}

// STUB: LEGORACERS 0x00467450
LegoBool32 ObscureBanner0x5ec::VTable0x20(CopperCrest0x40::Helper0x44*, undefined4, undefined4)
{
	STUB(0x00467450);
	return FALSE;
}

// STUB: LEGORACERS 0x004674c0
ObscureVantageEventResult ObscureBanner0x5ec::VTable0x24(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x004674c0);
	return FALSE;
}

// STUB: LEGORACERS 0x00467510
ObscureVantageEventResult ObscureBanner0x5ec::VTable0x28(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00467510);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004676d0
ObscureBanner0x9f4::ObscureBanner0x9f4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00467750
ObscureBanner0x9f4::~ObscureBanner0x9f4()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004677b0
void ObscureBanner0x9f4::Reset()
{
	m_unk0x5ec.VTable0x08();
	m_unk0x9e8 = 0;
	m_unk0x9f0 = 0;
	m_unk0x9ec = 0;
	ObscureBanner0x5ec::Reset();
}

// STUB: LEGORACERS 0x00467880
LegoBool32 ObscureBanner0x9f4::VTable0x08()
{
	STUB(0x00467880);
	return ObscureIcon0x1a8::VTable0x08();
}

// STUB: LEGORACERS 0x004678b0
void ObscureBanner0x9f4::VTable0x14(VisualState0x4*)
{
	STUB(0x004678b0);
}

// STUB: LEGORACERS 0x004678e0
ObscureVantageEventResult ObscureBanner0x9f4::VTable0x24(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x004678e0);
	return FALSE;
}

// STUB: LEGORACERS 0x00467960
void ObscureBanner0x9f4::VTable0x78()
{
	STUB(0x00467960);
}

// STUB: LEGORACERS 0x004679b0
void ObscureBanner0x9f4::VTable0x7c()
{
	STUB(0x004679b0);
}

// STUB: LEGORACERS 0x00467a00
undefined4 ObscureBanner0x9f4::VTable0x3c(undefined4)
{
	STUB(0x00467a00);
	return 0;
}

// STUB: LEGORACERS 0x00467ae0
undefined4 ObscureBanner0x9f4::VTable0x74(undefined4)
{
	STUB(0x00467ae0);
	return 0;
}

// STUB: LEGORACERS 0x00467b50
ObscureVantage0x58* ObscureBanner0x9f4::VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00467b50);
	return NULL;
}

// STUB: LEGORACERS 0x00467be0
ObscureVantage0x58* ObscureBanner0x9f4::VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4)
{
	STUB(0x00467be0);
	return NULL;
}
