#include "opalvault0xf0.h"

DECOMP_SIZE_ASSERT(OpalVault0xf0, 0xf0)

// FUNCTION: LEGORACERS 0x450300
OpalVault0xf0::OpalVault0xf0()
{
	VTable0x00();
}

// FUNCTION: LEGORACERS 0x450370
OpalVault0xf0::~OpalVault0xf0()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x4503c0
LegoS32 OpalVault0xf0::VTable0x00()
{
	m_unk0xe4 = 0;
	m_unk0xec = 0;
	return JasperCore0xf0::VTable0x00();
}

// STUB: LEGORACERS 0x450460
LegoS32 OpalVault0xf0::VTable0x08()
{
	// TODO
	STUB(0x450460);
	return 0;
}

// FUNCTION: LEGORACERS 0x450490
LegoS32 OpalVault0xf0::VTable0x0c()
{
	VTable0x24();

	if (VTable0x18() && VTable0x1c() && VTable0x20()) {
		return 1;
	}

	VTable0x08();
	return 0;
}

// STUB: LEGORACERS 0x450510
void OpalVault0xf0::VTable0x28()
{
	// TODO
	STUB(0x450510);
}

// STUB: LEGORACERS 0x4506a0
LegoS32 OpalVault0xf0::VTable0x18()
{
	// TODO
	STUB(0x4506a0);
	return 0;
}

// STUB: LEGORACERS 0x450790
LegoS32 OpalVault0xf0::VTable0x1c()
{
	// TODO
	STUB(0x450790);
	return 0;
}

// STUB: LEGORACERS 0x450880
LegoS32 OpalVault0xf0::VTable0x20()
{
	// TODO
	STUB(0x450880);
	return 0;
}

// STUB: LEGORACERS 0x4508d0
void OpalVault0xf0::VTable0x24()
{
	// TODO
	STUB(0x4508d0);
}

// STUB: LEGORACERS 0x450990
LegoS32 OpalVault0xf0::VTable0x10()
{
	// TODO
	STUB(0x450990);
	return 0;
}

// STUB: LEGORACERS 0x450a20
LegoS32 OpalVault0xf0::VTable0x14()
{
	// TODO
	STUB(0x450a20);
	return 0;
}
