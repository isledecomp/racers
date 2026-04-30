#include "porcelainveil0x50.h"

DECOMP_SIZE_ASSERT(PorcelainVeil0x50, 0x50)

// STUB: LEGORACERS 0x00480550
PorcelainVeil0x50::PorcelainVeil0x50()
{
	// TODO
	STUB(0x480550);
}

// STUB: LEGORACERS 0x004805c0
PorcelainVeil0x50::~PorcelainVeil0x50()
{
	// TODO
	STUB(0x4805c0);
}

// FUNCTION: LEGORACERS 0x00480610
void PorcelainVeil0x50::VTable0x0c()
{
	m_unk0x4c = NULL;
	CeruleanEmperor0x4c::VTable0x0c();
}

// FUNCTION: LEGORACERS 0x00480620
void PorcelainVeil0x50::Clear()
{
	if (m_nameEntries) {
		if (m_unk0x4c) {
			delete[] m_unk0x4c;
		}

		CeruleanEmperor0x4c::Clear();
	}
}

// STUB: LEGORACERS 0x00480650
void PorcelainVeil0x50::VTable0x10(undefined4)
{
	// TODO
	STUB(0x00480650);
}

// STUB: LEGORACERS 0x00480740
void PorcelainVeil0x50::VTable0x14(undefined4)
{
	// TODO
	STUB(0x00480740);
}
