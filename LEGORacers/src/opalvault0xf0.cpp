#include "opalvault0xf0.h"

DECOMP_SIZE_ASSERT(OpalVault0xf0, 0xf0)

// FUNCTION: LEGORACERS 0x00450300
OpalVault0xf0::OpalVault0xf0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00450370
OpalVault0xf0::~OpalVault0xf0()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x004503c0
LegoS32 OpalVault0xf0::Reset()
{
	m_directInput = 0;
	m_unk0xec = 0;
	return JasperCore0xf0::Reset();
}

// STUB: LEGORACERS 0x004503e0
void OpalVault0xf0::FUN_004503e0(HINSTANCE, HWND)
{
	// TODO
	STUB(0x004503e0);
}

// FUNCTION: LEGORACERS 0x00450460
LegoS32 OpalVault0xf0::Shutdown()
{
	if (m_unk0x8c) {
		VTable0x24();

		if (m_directInput) {
			m_directInput->Release();
		}

		Reset();
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x00450490
LegoS32 OpalVault0xf0::Init()
{
	VTable0x24();

	if (VTable0x18() && VTable0x1c() && VTable0x20()) {
		return 1;
	}

	Shutdown();
	return 0;
}

// STUB: LEGORACERS 0x00450510
void OpalVault0xf0::VTable0x28()
{
	// TODO
	STUB(0x450510);
}

// STUB: LEGORACERS 0x004506a0
LegoS32 OpalVault0xf0::VTable0x18()
{
	// TODO
	STUB(0x4506a0);
	return 0;
}

// STUB: LEGORACERS 0x00450790
LegoS32 OpalVault0xf0::VTable0x1c()
{
	// TODO
	STUB(0x450790);
	return 0;
}

// STUB: LEGORACERS 0x00450880
LegoS32 OpalVault0xf0::VTable0x20()
{
	// TODO
	STUB(0x450880);
	return 0;
}

// STUB: LEGORACERS 0x004508d0
void OpalVault0xf0::VTable0x24()
{
	// TODO
	STUB(0x4508d0);
}

// STUB: LEGORACERS 0x00450990
LegoS32 OpalVault0xf0::VTable0x10()
{
	// TODO
	STUB(0x450990);
	return 0;
}

// STUB: LEGORACERS 0x00450a20
LegoS32 OpalVault0xf0::VTable0x14()
{
	// TODO
	STUB(0x450a20);
	return 0;
}
