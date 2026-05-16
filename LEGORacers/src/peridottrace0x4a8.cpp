#include "golbyteorder.h"
#include "peridottrace0x4e0.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PeridotTrace0x4a8, 0x4a8)
DECOMP_SIZE_ASSERT(PeridotTrace0x4e0, 0x4e0)

// FUNCTION: LEGORACERS 0x00442660
PeridotTrace0x4a8::PeridotTrace0x4a8()
{
	::memset(m_unk0x24, 0, sizeof(m_unk0x24));
	m_unk0x4a4 = 0;
}

// FUNCTION: LEGORACERS 0x00442680
PeridotTrace0x4a8::~PeridotTrace0x4a8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004426d0
void PeridotTrace0x4a8::FUN_004426d0(undefined4 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c)
{
	if (m_unk0x04) {
		Destroy();
	}

	FUN_0042b720(p_count, p_unk0x08, p_unk0x0c);
}

// STUB: LEGORACERS 0x00442770
undefined4 PeridotTrace0x4a8::FUN_00442770(GolFile& p_file)
{
	// TODO
	STUB(0x00442770);
	return 0;
}

// STUB: LEGORACERS 0x00442a00
void PeridotTrace0x4a8::FUN_00442a00(PeridotTracePersistentState* p_state)
{
	const LegoU8* data = m_unk0x24;
	const LegoU8* source = &data[c_tracePersistentHeaderOffset];
	LegoU32 i;
	LegoU32 j;

	p_state->m_unk0x0c = source[0];
	::memcpy(&p_state->m_displayDriverGuid, &source[1], sizeof(p_state->m_displayDriverGuid));
	p_state->m_unk0x1d = source[0x11];
	p_state->m_unk0x1e = source[0x12];
	p_state->m_unk0x1f = source[0x13];
	p_state->m_unk0x20 = source[0x14];
	p_state->m_unk0x21 = source[0x15];
	p_state->m_languageIndex = source[0x16];
	p_state->m_unk0x23 = source[0x17];

	::memcpy(&p_state->m_inputBindings, &data[c_traceInputBindingHeaderOffset], c_inputBindingHeaderSize);

	source = &data[c_traceInputBindingEntryOffset];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		PeridotTraceInputBindingEntry* entry = &p_state->m_inputBindings.m_entries[i];
		entry->m_deviceType = source[0];
		entry->m_deviceSubType = source[1];
		entry->m_unk0x02 = source[2];

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			entry->m_events[j] = ReadLittleEndianU32(&source[3 + (j * sizeof(LegoU32))]);
		}

		source += c_traceInputBindingEntrySize;
	}

	p_state->m_unk0x24 = data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize)];
	p_state->m_unk0x25 = data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize) + 1];
	p_state->m_unk0x26 = static_cast<LegoU16>(
		ReadLittleEndianU32(&data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize)]) >> 16
	);

	source = &data[c_traceScoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_unk0x28); i++) {
		p_state->m_unk0x28[i] = ReadLittleEndianU32(source);
		::memcpy(p_state->m_unk0x90[i], &source[4], sizeof(p_state->m_unk0x90[i]));
		p_state->m_unk0x5c[i] = ReadLittleEndianU32(&source[0x20]);
		::memcpy(p_state->m_unk0x1fc[i], &source[0x24], sizeof(p_state->m_unk0x1fc[i]));

		source += c_traceScoreRecordSize;
	}
}

// STUB: LEGORACERS 0x00442c20
void PeridotTrace0x4a8::FUN_00442c20(PeridotTracePersistentState* p_state)
{
	LegoU8* data = m_unk0x24;
	LegoU8* dest = &data[c_tracePersistentHeaderOffset];
	LegoU32 i;
	LegoU32 j;

	dest[0] = p_state->m_unk0x0c;
	::memcpy(&dest[1], &p_state->m_displayDriverGuid, sizeof(p_state->m_displayDriverGuid));
	dest[0x11] = p_state->m_unk0x1d;
	dest[0x12] = p_state->m_unk0x1e;
	dest[0x13] = p_state->m_unk0x1f;
	dest[0x14] = p_state->m_unk0x20;
	dest[0x15] = p_state->m_unk0x21;
	dest[0x16] = p_state->m_languageIndex;
	dest[0x17] = p_state->m_unk0x23;

	::memcpy(&data[c_traceInputBindingHeaderOffset], &p_state->m_inputBindings, c_inputBindingHeaderSize);

	dest = &data[c_traceInputBindingEntryOffset];
	for (i = 0; i < sizeOfArray(p_state->m_inputBindings.m_entries); i++) {
		PeridotTraceInputBindingEntry* entry = &p_state->m_inputBindings.m_entries[i];
		dest[0] = entry->m_deviceType;
		dest[1] = entry->m_deviceSubType;
		dest[2] = entry->m_unk0x02;

		for (j = 0; j < sizeOfArray(entry->m_events); j++) {
			WriteLittleEndianU32(&dest[3 + (j * sizeof(LegoU32))], entry->m_events[j]);
		}

		dest += c_traceInputBindingEntrySize;
	}

	data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize)] = p_state->m_unk0x24;
	data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize) + 1] = p_state->m_unk0x25;
	data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize) + 2] = static_cast<LegoU8>(p_state->m_unk0x26);
	data[c_traceScoreRecordsOffset + (13 * c_traceScoreRecordSize) + 3] = static_cast<LegoU8>(p_state->m_unk0x26 >> 8);

	dest = &data[c_traceScoreRecordsOffset];
	for (i = 0; i < sizeOfArray(p_state->m_unk0x28); i++) {
		WriteLittleEndianU32(dest, p_state->m_unk0x28[i]);
		::memcpy(&dest[4], p_state->m_unk0x90[i], sizeof(p_state->m_unk0x90[i]));
		WriteLittleEndianU32(&dest[0x20], p_state->m_unk0x5c[i]);
		::memcpy(&dest[0x24], p_state->m_unk0x1fc[i], sizeof(p_state->m_unk0x1fc[i]));

		dest += c_traceScoreRecordSize;
	}
}

// STUB: LEGORACERS 0x004437e0
PeridotTrace0x4e0::PeridotTrace0x4e0()
{
	// TODO
	STUB(0x4437e0);
}

// STUB: LEGORACERS 0x00443840
PeridotTrace0x4e0::~PeridotTrace0x4e0()
{
	// TODO
	STUB(0x443840);
}

// STUB: LEGORACERS 0x004438e0
void PeridotTrace0x4e0::FUN_004438e0()
{
	// TODO
	STUB(0x4438e0);
}

// STUB: LEGORACERS 0x00443910
undefined4 PeridotTrace0x4e0::FUN_00443910()
{
	// TODO
	STUB(0x00443910);
	return 0;
}

// STUB: LEGORACERS 0x00443940
undefined4 PeridotTrace0x4e0::FUN_00443940()
{
	// TODO
	STUB(0x00443940);
	return 0;
}

// STUB: LEGORACERS 0x00443980
undefined4 PeridotTrace0x4e0::FUN_00443980()
{
	// TODO
	STUB(0x00443980);
	return 0;
}

// STUB: LEGORACERS 0x004439b0
undefined4 PeridotTrace0x4a8::FUN_004439b0()
{
	// TODO
	STUB(0x004439b0);
	return 0;
}
