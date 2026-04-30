#include "ceruleanemperor0x4c.h"

#include "golbinparser.h"
#include "golerror.h"
#include "goltxtparser.h"

DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c, 0x4c)

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

// STUB: LEGORACERS 0x0046fd80
void CeruleanEmperor0x4c::VTable0x14(undefined4)
{
	// TODO
	STUB(0x0046fd80);
}
