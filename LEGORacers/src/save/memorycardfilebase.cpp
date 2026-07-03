#include "save/memorycardfilebase.h"

#include "golstream.h"
#include "save/savedirectory.h"

DECOMP_SIZE_ASSERT(MemoryCardFileBase, 0x34)

// FUNCTION: LEGORACERS 0x00450e30
MemoryCardFileBase::MemoryCardFileBase()
{
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x00450e80
LegoS32 MemoryCardFileBase::OpenSlotFile(SaveSlot* p_slot, const LegoChar* p_fileName, undefined4)
{
	p_slot->BuildFilePath(p_fileName, g_pathBuffer);
	return GolFile::Open(g_pathBuffer);
}
