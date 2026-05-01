#include "rosequartzshine0x14.h"

#include <memory.h>

DECOMP_SIZE_ASSERT(RoseQuartzShine0x14, 0x14)
DECOMP_SIZE_ASSERT(RoseQuartzShine0x14::Struct0x38, 0x38)

// FUNCTION: LEGORACERS 0x00436490
RoseQuartzShine0x14::Struct0x38::Struct0x38()
{
	FUN_004364b0();
}

// FUNCTION: LEGORACERS 0x004364a0
RoseQuartzShine0x14::Struct0x38::~Struct0x38()
{
	FUN_00436650();
}

// FUNCTION: LEGORACERS 0x004364b0
void RoseQuartzShine0x14::Struct0x38::FUN_004364b0()
{
	m_unk0x00 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	memset(&m_unk0x04, 0, sizeof(m_unk0x04));
	memset(&m_unk0x0c, 0, sizeof(m_unk0x0c));
	memset(&m_unk0x14, 0, sizeof(m_unk0x14));
	memset(&m_unk0x1c, 0, sizeof(m_unk0x1c));
}

// FUNCTION: LEGORACERS 0x00436650
void RoseQuartzShine0x14::Struct0x38::FUN_00436650()
{
	FUN_004364b0();
}

// FUNCTION: LEGORACERS 0x00436660
RoseQuartzShine0x14::RoseQuartzShine0x14()
{
	m_entries = NULL;
	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x004366a0
RoseQuartzShine0x14::~RoseQuartzShine0x14()
{
	Clear();
}

// STUB: LEGORACERS 0x004366f0
void RoseQuartzShine0x14::Load(GolStringTable*, RaceDefinitionList*, const LegoChar*, undefined4)
{
	// TODO
	STUB(0x4366f0);
}

// FUNCTION: LEGORACERS 0x004368f0
void RoseQuartzShine0x14::Clear()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	m_entryCount = 0;
}

// FUNCTION: LEGORACERS 0x00436930
LegoU32 RoseQuartzShine0x14::GetEntryIndexByName(LegoChar* p_name)
{
	Struct0x38* entry = static_cast<Struct0x38*>(GetName(p_name));
	return entry - m_entries;
}
