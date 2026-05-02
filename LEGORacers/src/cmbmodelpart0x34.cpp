#include "cmbmodelpart0x34.h"

DECOMP_SIZE_ASSERT(CmbModelPart0x34, 0x34)

// FUNCTION: LEGORACERS 0x004011a0
CmbModelPart0x34::CmbModelPart0x34()
{
	m_unk0x24 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = NULL;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x00401200
CmbModelPart0x34::~CmbModelPart0x34()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004013b0
void CmbModelPart0x34::Clear()
{
	m_data.Clear();

	if (m_unk0x24 != NULL) {
		delete[] m_unk0x24;
		m_unk0x24 = NULL;
	}

	if (m_unk0x2c != NULL) {
		delete[] m_unk0x2c;
		m_unk0x2c = NULL;
	}

	GolNameTable::Clear();
	m_unk0x28 = 0;
	m_unk0x30 = 0;
}
