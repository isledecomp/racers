#include "golfilesource.h"

#include "golstream.h"

DECOMP_SIZE_ASSERT(GolFileSource, 0x34)

// FUNCTION: LEGORACERS 0x44d820
GolFileSource::GolFileSource()
{
	m_stream = NULL;
	m_state = 0;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x44d860
GolFileSource::~GolFileSource()
{
	Reset();
}

// STUB: LEGORACERS 0x44d8e0
void GolFileSource::Reset()
{
	// TODO: AzureClip0x24 cleanup at m_unk0x0c
	STUB(0x44d8e0);
	m_stream = NULL;
	m_state = 0;
}

// STUB: LEGORACERS 0x44d900
LegoS32 GolFileSource::Open(LegoChar*, LegoS32*, LegoS32*)
{
	// TODO
	STUB(0x44d900);
	return 0;
}

// STUB: LEGORACERS 0x44d9c0
LegoS32 GolFileSource::Find(LegoChar*)
{
	// TODO
	STUB(0x44d9c0);
	return 0;
}

// FUNCTION: LEGORACERS 0x44da60
LegoS32 GolFileSource::Close()
{
	m_state = 0;
	return 0;
}

// STUB: LEGORACERS 0x44da70
LegoS32 GolFileSource::Read(LegoU32, void*, LegoU32, LegoU32, LegoS32*)
{
	// TODO
	STUB(0x44da70);
	return 0;
}

// FUNCTION: LEGORACERS 0x44dbb0
LegoS32 GolFileSource::ForwardRead(LegoU32 p_offset, void* p_buf, LegoU32 p_size, LegoS32* p_lenRead)
{
	return m_stream->BufferedRead(p_offset, p_buf, p_size, p_lenRead);
}
