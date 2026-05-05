#include "ceruleanqueen0x58.h"

#include "golbinparser.h"
#include "golerror.h"

DECOMP_SIZE_ASSERT(CeruleanQueen0x58, 0x5c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::MidTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::ResourceLoadParams, 0x0c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Struct0x74, 0x74)

// FUNCTION: LEGORACERS 0x004695b0
CeruleanQueen0x58::CeruleanQueen0x58()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x00469620
CeruleanQueen0x58::~CeruleanQueen0x58()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00469670
void CeruleanQueen0x58::VTable0x0c()
{
	m_unk0x54 = 2;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	CeruleanKnight0x20::VTable0x0c();
}

// FUNCTION: LEGORACERS 0x004696b0
LegoBool32 CeruleanQueen0x58::Load(ResourceLoadParams* p_params)
{
	Clear();
	m_unk0x14 = p_params->m_renderer;

	if (FUN_0046b100()) {
		FUN_00469900(p_params);
	}

	return m_nameEntries != NULL;
}

// FUNCTION: LEGORACERS 0x004696f0
void CeruleanQueen0x58::Clear()
{
	if (m_nameEntries == NULL) {
		return;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}
	if (m_unk0x24) {
		delete[] m_unk0x24;
	}
	if (m_unk0x28) {
		delete[] m_unk0x28;
	}
	if (m_unk0x2c) {
		delete[] m_unk0x2c;
	}
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}
	if (m_unk0x34) {
		delete[] m_unk0x34;
	}
	if (m_unk0x38) {
		delete[] m_unk0x38;
	}
	if (m_unk0x3c) {
		delete[] m_unk0x3c;
	}
	if (m_unk0x40) {
		for (LegoS32 i = 0; i < m_unk0x58; i++) {
			delete[] m_unk0x40[i].m_unk0x3c;
		}

		delete[] m_unk0x40;
	}
	if (m_unk0x44) {
		delete[] m_unk0x44;
	}
	if (m_unk0x48) {
		delete[] m_unk0x48;
	}
	if (m_unk0x4c) {
		delete[] m_unk0x4c;
	}
	if (m_unk0x50) {
		delete[] m_unk0x50;
	}

	CeruleanKnight0x20::Clear();
}

// FUNCTION: LEGORACERS 0x00469810
void CeruleanQueen0x58::VTable0x10(undefined4 p_param)
{
	if (p_param) {
		m_unk0x10 = new GolBinParser();
		if (m_unk0x10 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x10->SetSuffix(".mib");
		return;
	}

	m_unk0x10 = new MidTxtParser();
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x00469900
void CeruleanQueen0x58::FUN_00469900(ResourceLoadParams* p_params)
{
	VTable0x10(p_params->m_binary);
	m_unk0x10->OpenFileForRead(p_params->m_fileName);
	FUN_0046b130();
	FUN_0046b250();
	m_unk0x10->Dispose();

	delete m_unk0x10;
}

// FUNCTION: LEGORACERS 0x00469950
void CeruleanQueen0x58::VTable0x14(undefined4 p_arg1)
{
	switch (p_arg1) {
	case 0x37:
		FUN_0046a750();
		break;
	case 0x38:
		FUN_0046a800();
		break;
	case 0x39:
		FUN_0046a8a0();
		break;
	case 0x3a:
		FUN_0046a940();
		break;
	case 0x3b:
		FUN_0046a9e0();
		break;
	case 0x3c:
		FUN_0046aa90();
		break;
	case 0x3d:
		FUN_0046ab40();
		break;
	case 0x3e:
		FUN_0046abe0();
		break;
	case 0x3f:
		FUN_0046ac90();
		break;
	case 0x40:
		FUN_0046ad40();
		break;
	case 0x41:
	case 0x44:
	default:
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case 0x42:
		FUN_0046adf0();
		break;
	case 0x43:
		FUN_0046af50();
		break;
	case 0x45:
		FUN_0046aea0();
		break;
	}
}

// STUB: LEGORACERS 0x0046a750
void CeruleanQueen0x58::FUN_0046a750()
{
	// TODO
	STUB(0x0046a750);
}

// STUB: LEGORACERS 0x0046a800
void CeruleanQueen0x58::FUN_0046a800()
{
	// TODO
	STUB(0x0046a800);
}

// STUB: LEGORACERS 0x0046a8a0
void CeruleanQueen0x58::FUN_0046a8a0()
{
	// TODO
	STUB(0x0046a8a0);
}

// STUB: LEGORACERS 0x0046a940
void CeruleanQueen0x58::FUN_0046a940()
{
	// TODO
	STUB(0x0046a940);
}

// STUB: LEGORACERS 0x0046a9e0
void CeruleanQueen0x58::FUN_0046a9e0()
{
	// TODO
	STUB(0x0046a9e0);
}

// STUB: LEGORACERS 0x0046aa90
void CeruleanQueen0x58::FUN_0046aa90()
{
	// TODO
	STUB(0x0046aa90);
}

// STUB: LEGORACERS 0x0046ab40
void CeruleanQueen0x58::FUN_0046ab40()
{
	// TODO
	STUB(0x0046ab40);
}

// STUB: LEGORACERS 0x0046abe0
void CeruleanQueen0x58::FUN_0046abe0()
{
	// TODO
	STUB(0x0046abe0);
}

// STUB: LEGORACERS 0x0046ac90
void CeruleanQueen0x58::FUN_0046ac90()
{
	// TODO
	STUB(0x0046ac90);
}

// STUB: LEGORACERS 0x0046ad40
void CeruleanQueen0x58::FUN_0046ad40()
{
	// TODO
	STUB(0x0046ad40);
}

// STUB: LEGORACERS 0x0046adf0
void CeruleanQueen0x58::FUN_0046adf0()
{
	// TODO
	STUB(0x0046adf0);
}

// STUB: LEGORACERS 0x0046aea0
void CeruleanQueen0x58::FUN_0046aea0()
{
	// TODO
	STUB(0x0046aea0);
}

// STUB: LEGORACERS 0x0046af50
void CeruleanQueen0x58::FUN_0046af50()
{
	// TODO
	STUB(0x0046af50);
}
