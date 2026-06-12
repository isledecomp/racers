#include "golstream.h"
#include "save/savedirectory.h"

DECOMP_SIZE_ASSERT(SaveSlotBase, 0x08)

// FUNCTION: LEGORACERS 0x0044e040
SaveSlotBase::SaveSlotBase()
{
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x0044e070
SaveSlotBase::~SaveSlotBase()
{
}

// FUNCTION: LEGORACERS 0x0044e080 FOLDED
LegoS32 SaveSlotBase::VTable0x18(undefined4, undefined4)
{
	return GolStream::e_ioOperationNotSupported;
}

// FUNCTION: LEGORACERS 0x0044e090 FOLDED
LegoS32 SaveSlotBase::VTable0x10(undefined4)
{
	return GolStream::e_ioOperationNotSupported;
}

// FUNCTION: LEGORACERS 0x0044e090 FOLDED
LegoS32 SaveSlotBase::VTable0x1c(undefined4)
{
	return GolStream::e_ioOperationNotSupported;
}

// FUNCTION: LEGORACERS 0x0044e080 FOLDED
LegoS32 SaveSlotBase::VTable0x20(undefined4, undefined4)
{
	return GolStream::e_ioOperationNotSupported;
}
