#include "save/peridottrace0x4e0.h"

#include "golerror.h"
#include "golstring.h"
#include "racer/turquoiseglowcolor.h"

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

// FUNCTION: LEGORACERS 0x0042b330
void PeridotTraceBase0x24::Record::FUN_0042b330(TurquoiseGlowColor* p_color) const
{
	p_color->m_unk0x01 = m_data[0x1c];
	p_color->m_unk0x00 = m_data[0x1d];
	p_color->m_unk0x03 = m_data[0x1e];
	p_color->m_unk0x02 = m_data[0x1f];
	p_color->m_unk0x04 = m_data[0x20] & 0x7f;
}

// FUNCTION: LEGORACERS 0x0042b360
void PeridotTraceBase0x24::Record::FUN_0042b360(LegoU8* p_dest) const
{
	::memcpy(p_dest, &m_data[0x29], 0x202);
}

// FUNCTION: LEGORACERS 0x0042b380
void PeridotTraceBase0x24::Record::FUN_0042b380(GolName p_dest) const
{
	::memcpy(p_dest, &m_data[0x21], 8);
}

// FUNCTION: LEGORACERS 0x0042b3a0
void PeridotTraceBase0x24::Record::FUN_0042b3a0(GolString* p_string) const
{
	PeridotTraceBuffer0x250::CopyBufferToString(p_string, m_data, 0x0e);
}

// FUNCTION: LEGORACERS 0x0042b400
void PeridotTraceBuffer0x250::CopyBufferToString(GolString* p_string, const LegoU8* p_source, LegoU32 p_count)
{
	LegoU32 i = 0;
	while (i < p_count) {
		undefined2 c = static_cast<undefined2>((p_source[1] << 8) + p_source[0]);
		if (!c) {
			break;
		}

		*p_string->FromCursor(i) = c;
		p_source += 2;
		i++;
	}

	*p_string->FromCursor(i) = 0;
	p_string->SetCursorEnd(static_cast<undefined2>(i));
	p_string->SetCursorStart(0);
}

// FUNCTION: LEGORACERS 0x0042b460
LegoBool32 PeridotTraceBase0x24::Record::FUN_0042b460() const
{
	return m_data[0x20] & 0x80;
}

// FUNCTION: LEGORACERS 0x0042b470
void PeridotTraceBase0x24::Record::FUN_0042b470()
{
	FUN_0042b6d0();
	m_data[0x20] |= 0x80;
}

// FUNCTION: LEGORACERS 0x0042b490
void PeridotTraceBase0x24::Record::FUN_0042b490()
{
	FUN_0042b6d0();
	m_data[0x20] &= 0x7f;
}

// FUNCTION: LEGORACERS 0x0042b4b0
void PeridotTraceBase0x24::Record::FUN_0042b4b0(const TurquoiseGlowColor* p_color)
{
	m_data[0x1c] = p_color->m_unk0x01;
	m_data[0x1d] = p_color->m_unk0x00;
	m_data[0x1e] = p_color->m_unk0x03;
	m_data[0x1f] = p_color->m_unk0x02;
	m_data[0x20] = (m_data[0x20] & 0x80) | p_color->m_unk0x04;
	FUN_0042b6d0();
}

// FUNCTION: LEGORACERS 0x0042b4f0
void PeridotTraceBuffer0x250::FUN_0042b4f0(const LegoU8* p_source)
{
	memcpy(&m_data[0x29], p_source, 0x202);
	FUN_0042b6d0();
}

// FUNCTION: LEGORACERS 0x0042b510
void PeridotTraceBase0x24::Record::FUN_0042b510(const GolName p_source)
{
	::memcpy(&m_data[0x21], p_source, 8);
	FUN_0042b6d0();
}

// FUNCTION: LEGORACERS 0x0042b530
void PeridotTraceBase0x24::Record::FUN_0042b530(GolString* p_string)
{
	PeridotTraceBuffer0x250::CopyStringToBuffer(p_string, m_data, 0x0e);
	FUN_0042b6d0();
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

// FUNCTION: LEGORACERS 0x0042b5c0
void PeridotTraceBase0x24::Record::FUN_0042b5c0(const Record* p_source)
{
	if (m_unk0x08 == 0) {
		FUN_0042b2f0(p_source->m_unk0x08, p_source->m_unk0x0c, 0, NULL);
	}

	::memcpy(m_data, p_source->m_data, sizeof(m_data));
	FUN_0042b6d0();
}

// FUNCTION: LEGORACERS 0x0042b610
LegoU32 PeridotTraceBase0x24::Record::FUN_0042b610(undefined4 p_index) const
{
	LegoU16 value = m_data[0x22c];
	LegoU16 low = m_data[0x22b];
	value <<= 8;
	value += low;

	LegoU8 shift = static_cast<LegoU8>(p_index);
	shift <<= 1;
	return (value >> shift) & 3;
}

// STUB: LEGORACERS 0x0042b640
LegoBool32 PeridotTraceBase0x24::Record::FUN_0042b640(LegoU32 p_index, LegoU32 p_value)
{
	Record* record = this;

	if (p_value > 3) {
		return FALSE;
	}

	LegoU16 value = static_cast<LegoU16>((record->m_data[0x22c] << 8) + record->m_data[0x22b]);
	LegoU16 updated = value;

	LegoU16 existing = value;
	existing >>= static_cast<LegoU16>(p_index << 1);
	existing &= 3;
	if (existing && static_cast<LegoU16>(p_value) >= existing) {
		return FALSE;
	}

	LegoU32 shift = p_index + p_index;
	existing = 3;
	existing <<= shift;
	p_value <<= shift;
	updated &= ~existing;
	updated |= static_cast<LegoU16>(p_value);
	record->m_data[0x22b] = static_cast<LegoU8>(updated);
	record->m_data[0x22c] = static_cast<LegoU8>(updated >> 8);
	record->FUN_0042b6d0();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0042b6d0
void PeridotTraceBase0x24::Record::FUN_0042b6d0()
{
	if (m_owner) {
		m_owner->m_unk0x20 = 1;
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

// FUNCTION: LEGORACERS 0x0042b990
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b990(LegoU32 p_index)
{
	Record* record = m_unk0x18;

	while (p_index-- != 0) {
		record = record->m_next;
	}

	return record;
}

// FUNCTION: LEGORACERS 0x0042b9b0
PeridotTraceBase0x24::Record* PeridotTraceBase0x24::FUN_0042b9b0(undefined4 p_unk0x04)
{
	Record* record = m_unk0x18;

	while (record != NULL) {
		if (record->m_unk0x10 == p_unk0x04) {
			return record;
		}

		record = record->m_next;
	}

	return NULL;
}
