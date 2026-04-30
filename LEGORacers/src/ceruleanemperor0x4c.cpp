#include "ceruleanemperor0x4c.h"

#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c, 0x4c)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::ResourceLoadParams, 0x10)

// FUNCTION: LEGORACERS 0x0046fa50
CeruleanEmperor0x4c::CeruleanEmperor0x4c()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0046fac0
CeruleanEmperor0x4c::~CeruleanEmperor0x4c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0046fb10
void CeruleanEmperor0x4c::VTable0x0c()
{
	m_unk0x20 = 0;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = NULL;
	m_unk0x34 = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_unk0x48 = NULL;

	CeruleanKnight0x20::VTable0x0c();
}

// STUB: LEGORACERS 0x0046fb40
LegoBool32 CeruleanEmperor0x4c::Load(ResourceLoadParams*)
{
	// TODO
	STUB(0x0046fb40);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046fb80
void CeruleanEmperor0x4c::Clear()
{
	if (m_nameEntries == NULL) {
		return;
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
		delete[] m_unk0x40;
	}
	if (m_unk0x44) {
		delete[] m_unk0x44;
	}
	if (m_unk0x48) {
		delete[] m_unk0x48;
	}

	CeruleanKnight0x20::Clear();
}

// FUNCTION: LEGORACERS 0x0046fc40
void CeruleanEmperor0x4c::VTable0x10(undefined4 p_param)
{
	if (p_param) {
		// TODO: Subclass of GolFileParser. GolFormatParser?
		m_unk0x10 = new GolBinParser();
		if (m_unk0x10 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x10->SetSuffix(".msb");
		return;
	}

	m_unk0x10 = new GolTxtParser();
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x0046fd80
void CeruleanEmperor0x4c::VTable0x14(undefined4 p_arg1)
{
	switch (p_arg1) {
	case 0x32:
		FUN_004707e0();
		break;
	case 0x33:
		FUN_00470880();
		break;
	case 0x34:
		FUN_00470920();
		break;
	case 0x35:
		FUN_004709c0();
		break;
	case 0x36:
		FUN_00470a70();
		break;
	case 0x37:
		FUN_00470b10();
		break;
	case 0x38:
		FUN_00470bc0();
		break;
	case 0x39:
		FUN_00470c60();
		break;
	case 0x3a:
	default:
		m_unk0x10->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case 0x3b:
		FUN_00470d10();
		break;
	case 0x3d:
		FUN_00470dc0();
		break;
	}
}

// STUB: LEGORACERS 0x004707e0
void CeruleanEmperor0x4c::FUN_004707e0()
{
	// TODO
	STUB(0x004707e0);
}

// STUB: LEGORACERS 0x00470880
void CeruleanEmperor0x4c::FUN_00470880()
{
	// TODO
	STUB(0x00470880);
}

// STUB: LEGORACERS 0x00470920
void CeruleanEmperor0x4c::FUN_00470920()
{
	// TODO
	STUB(0x00470920);
}

// STUB: LEGORACERS 0x004709c0
void CeruleanEmperor0x4c::FUN_004709c0()
{
	// TODO
	STUB(0x004709c0);
}

// STUB: LEGORACERS 0x00470a70
void CeruleanEmperor0x4c::FUN_00470a70()
{
	// TODO
	STUB(0x00470a70);
}

// STUB: LEGORACERS 0x00470b10
void CeruleanEmperor0x4c::FUN_00470b10()
{
	// TODO
	STUB(0x00470b10);
}

// STUB: LEGORACERS 0x00470bc0
void CeruleanEmperor0x4c::FUN_00470bc0()
{
	// TODO
	STUB(0x00470bc0);
}

// STUB: LEGORACERS 0x00470c60
void CeruleanEmperor0x4c::FUN_00470c60()
{
	// TODO
	STUB(0x00470c60);
}

// STUB: LEGORACERS 0x00470d10
void CeruleanEmperor0x4c::FUN_00470d10()
{
	// TODO
	STUB(0x00470d10);
}

// STUB: LEGORACERS 0x00470dc0
void CeruleanEmperor0x4c::FUN_00470dc0()
{
	// TODO00470dc0();
	STUB(0x00470dc0);
}
