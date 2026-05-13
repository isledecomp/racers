#include "peridottrace0x4e0.h"

#include "golstring.h"

DECOMP_SIZE_ASSERT(PeridotTraceBase0x24, 0x24)
DECOMP_SIZE_ASSERT(PeridotTraceBase0x24::Record, 0x241)
DECOMP_SIZE_ASSERT(PeridotTraceBuffer0x250, 0x250)

// STUB: LEGORACERS 0x0042b290
PeridotTraceBuffer0x250::PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b290);
}

// STUB: LEGORACERS 0x0042b2b0
PeridotTraceBuffer0x250::~PeridotTraceBuffer0x250()
{
	// TODO
	STUB(0x42b2b0);
}

// STUB: LEGORACERS 0x0042b2f0
void PeridotTraceBuffer0x250::FUN_0042b2f0(undefined4, undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x0042b2f0);
}

// FUNCTION: LEGORACERS 0x0042b560
void PeridotTraceBuffer0x250::CopyStringToBuffer(GolString* p_string, undefined2* p_dest, LegoU32 p_count)
{
	LegoU32 length = p_string->SelectionLength();
	if (length > p_count) {
		length = p_count;
	}

	LegoU8* dest = reinterpret_cast<LegoU8*>(p_dest);
	LegoU32 i = 0;
	for (; i < length; i++) {
		undefined2 c = *p_string->FromCursor(i);

		dest[0] = static_cast<LegoU8>(c);
		dest[1] = static_cast<LegoU8>(c >> 8);
		dest += 2;
	}

	for (; i < p_count; i++) {
		*dest++ = 0;
		*dest++ = 0;
	}
}

// FUNCTION: LEGORACERS 0x0042b6e0
PeridotTraceBase0x24::PeridotTraceBase0x24()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b700
void PeridotTraceBase0x24::Initialize()
{
	m_unk0x20 = 0;
	m_unk0x00 = 0;
	m_unk0x1c = 0;
	m_unk0x04 = 0;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// STUB: LEGORACERS 0x0042b880
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b880()
{
	// TODO
	STUB(0x0042b880);
	return NULL;
}
