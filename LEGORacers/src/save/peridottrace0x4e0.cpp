#include "save/peridottrace0x4e0.h"

#include "golerror.h"
#include "golstring.h"

DECOMP_SIZE_ASSERT(PeridotTraceBase0x24, 0x24)
DECOMP_SIZE_ASSERT(PeridotTraceBase0x24::Record, 0x244)
DECOMP_SIZE_ASSERT(PeridotTraceBase0x24::SerializedRecord, 0x241)
DECOMP_SIZE_ASSERT(PeridotTraceBuffer0x250, 0x250)

// FUNCTION: LEGORACERS 0x0042b290
PeridotTraceBase0x24::Record::Record()
{
	m_next = NULL;
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b2b0
PeridotTraceBase0x24::Record::~Record()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042b2c0
void PeridotTraceBase0x24::Record::Initialize()
{
	m_owner = NULL;
	::memset(m_data, 0, sizeof(m_data));
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0042b2f0
void PeridotTraceBase0x24::Record::FUN_0042b2f0(
	undefined4 p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4 p_unk0x10,
	PeridotTraceBase0x24* p_owner
)
{
	if (m_unk0x08) {
		Destroy();
	}

	m_owner = p_owner;
	m_unk0x08 = p_unk0x08;
	m_unk0x0c = p_unk0x0c;
	m_unk0x10 = p_unk0x10;
}

// FUNCTION: LEGORACERS 0x0042b320
void PeridotTraceBase0x24::Record::Destroy()
{
	Initialize();
}

// FUNCTION: LEGORACERS 0x0042b560
void PeridotTraceBuffer0x250::CopyStringToBuffer(GolString* p_string, LegoU8* p_dest, LegoU32 p_count)
{
	LegoU32 length = p_string->SelectionLength();
	if (length > p_count) {
		length = p_count;
	}

	LegoU32 i = 0;
	LegoU8* dest = p_dest;
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

// FUNCTION: LEGORACERS 0x0042b6f0 FOLDED
PeridotTraceBase0x24::~PeridotTraceBase0x24()
{
	FUN_0042b7f0();
}

// FUNCTION: LEGORACERS 0x0042b6f0 FOLDED
void PeridotTraceBase0x24::Destroy()
{
	FUN_0042b7f0();
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

// FUNCTION: LEGORACERS 0x0042b720
void PeridotTraceBase0x24::FUN_0042b720(LegoU32 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	if (m_unk0x04) {
		FUN_0042b7f0();
	}

	m_unk0x20 = 0;
	m_unk0x1c = p_count;
	m_unk0x04 = new Record[p_count];
	if (!m_unk0x04) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x08 = p_unk0x08;
	m_unk0x0c = p_unk0x0c;
	FUN_0042b830();
}

// FUNCTION: LEGORACERS 0x0042b7f0
void PeridotTraceBase0x24::FUN_0042b7f0()
{
	if (m_unk0x04) {
		delete[] m_unk0x04;
		m_unk0x04 = NULL;
	}

	Initialize();
}

// STUB: LEGORACERS 0x0042b830
void PeridotTraceBase0x24::FUN_0042b830()
{
	m_unk0x14 = m_unk0x04;

	for (LegoU32 i = 1; i < m_unk0x1c; i++) {
		m_unk0x04[i - 1].m_next = &m_unk0x04[i];
	}

	m_unk0x18 = NULL;
}

// FUNCTION: LEGORACERS 0x0042b880
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b880()
{
	Record* record = m_unk0x14;
	if (!record) {
		return NULL;
	}

	m_unk0x00++;
	m_unk0x20 = 1;
	m_unk0x14 = record->m_next;
	record->FUN_0042b2f0(m_unk0x08, m_unk0x0c, m_unk0x00, this);
	record->m_next = NULL;

	if (m_unk0x18) {
		Record* tail = m_unk0x18;
		while (tail->m_next) {
			tail = tail->m_next;
		}

		tail->m_next = record;
	}
	else {
		m_unk0x18 = record;
	}

	return record;
}

// STUB: LEGORACERS 0x0042b8f0
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b8f0(Record*)
{
	STUB(0x0042b8f0);
	return NULL;
}

// STUB: LEGORACERS 0x0042b920
void PeridotTraceBase0x24::FUN_0042b920(Record*)
{
	STUB(0x0042b920);
}
