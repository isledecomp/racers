#include "bronzedunebag0xc.h"

#include "decomp.h"

// FUNCTION: GOLDP 0x1002a090
BronzeDuneBag0xc::BronzeDuneBag0xc()
{
	m_unk0x4 = NULL;
	m_unk0x8 = 0;
}

// FUNCTION: GOLDP 0x1002a0f0
BronzeDuneBag0xc::~BronzeDuneBag0xc()
{
	m_unk0x8 = 0;
	if (m_unk0x4 != NULL) {
		delete[] m_unk0x4;
		m_unk0x4 = NULL;
	}
}

// STUB: GOLDP 0x1002a120
void BronzeDuneBag0xc::FUN_1002a120(undefined4)
{
	// TODO
	STUB(0x1002a120);
}

// STUB: GOLDP 0x1002a1b0
void BronzeDuneBag0xc::FUN_1002a1b0()
{
	// TODO
	STUB(0x1002a1b0);
}

// STUB: GOLDP 0x1002a1e0
void BronzeDuneBag0xc::GetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	// TODO
	STUB(0x1002a1e0);
}

// STUB: GOLDP 0x1002a230
void BronzeDuneBag0xc::SetEntries(PALETTEENTRY* p_entries, LegoU32 p_start, LegoU32 p_count)
{
	// TODO
	STUB(0x1002a230);
}

// STUB: GOLDP 0x1002a290
void BronzeDuneBag0xc::GetEntry(PALETTEENTRY* p_entry, LegoU32 p_index)
{
	// TODO
	STUB(0x1002a290);
}

// STUB: GOLDP 0x1002a2d0
void BronzeDuneBag0xc::CopyEntriesFrom(IPalette0x4* p_source)
{
	// TODO
	STUB(0x1002a2d0);
}

// STUB: GOLDP 0x1002a300
LegoS32 BronzeDuneBag0xc::FindEntry(PALETTEENTRY* p_entry)
{
	// TODO
	STUB(0x1002a300);
	return 0;
}

// STUB: GOLDP 0x100016f0 FOLDED
LegoU32 BronzeDuneBag0xc::GetFirstEntry()
{
	MATCHING(0x100016f0);
	return 0;
}

// STUB: GOLDP 0x1002a350 FOLDED
LegoU32 BronzeDuneBag0xc::GetEntryCount()
{
	return m_unk0x8;
}

// STUB: GOLDP 0x1002a350 FOLDED
LegoU32 BronzeDuneBag0xc::GetPaletteSize()
{
	return m_unk0x8;
}
