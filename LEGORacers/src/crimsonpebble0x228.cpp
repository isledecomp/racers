#include "crimsonpebble0x228.h"

#include "golerror.h"
#include "golfileparser.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CrimsonPebble0x228, 0x228)
DECOMP_SIZE_ASSERT(BluebellFog0x4, 0x04)

// FUNCTION: LEGORACERS 0x004a0210
CrimsonPebble0x228::CrimsonPebble0x228()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a03b0
CrimsonPebble0x228::~CrimsonPebble0x228()
{
	FUN_004a0bf0();
}

// FUNCTION: LEGORACERS 0x004a0530
void CrimsonPebble0x228::Reset()
{
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_unk0x64 = NULL;
	m_unk0x68 = 0;
	m_unk0x6c = NULL;
	m_unk0x70 = NULL;
	m_unk0x74 = NULL;
	m_unk0x78 = 0;
	m_unk0x7c = NULL;
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	m_unk0x88 = NULL;
	m_unk0x8c = NULL;
	m_unk0x90 = 0;
	m_unk0x94 = NULL;
	m_unk0x98 = NULL;
	m_unk0x9c = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xb4 = 0;
	m_unk0xb8 = NULL;
	m_unk0xc8 = 0;
	m_unk0xcc = NULL;
	m_unk0xdc = 0;
	m_unk0xe0 = NULL;
	m_unk0xf0 = 0;
	m_unk0xf4 = NULL;
	m_unk0x104 = 0;
	m_unk0x108 = NULL;
	m_unk0x118 = 0;
	m_unk0x11c = NULL;
	m_unk0x12c = 0;
	m_unk0x130 = NULL;
	m_unk0x134 = 0;
	m_unk0x138 = NULL;
	m_unk0x148 = 0;
	m_unk0x14c = NULL;
	m_unk0x15c = 0;
	m_unk0x160 = NULL;
	m_unk0x170 = 0;
	m_unk0x174 = NULL;
	m_unk0x184 = 0;
	m_unk0x188 = NULL;
	m_unk0x198 = 0;
	m_unk0x19c = NULL;
	m_unk0x1ac = 0;
	m_unk0x1b0 = NULL;
	m_unk0x1c0 = 0;
	m_unk0x1c4 = NULL;
	m_unk0x1d4 = 0;
	m_unk0x1d8 = NULL;
	m_unk0x1e8 = 0;
	m_unk0x1ec = NULL;
	m_unk0x1fc = 0;
	m_unk0x200 = NULL;
	m_unk0x210 = 0;
	m_unk0x214 = NULL;
	m_unk0x224 = 0;
}

// STUB: LEGORACERS 0x004a0bf0
void CrimsonPebble0x228::FUN_004a0bf0()
{
	STUB(0x4a0bf0);
}

// STUB: LEGORACERS 0x004a12e0
void CrimsonPebble0x228::FUN_004a12e0(GolFileParser* p_unk0x04)
{
	if (m_unk0x7c != NULL) {
		p_unk0x04->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_unk0x04->ReadLeftBracket();
	m_unk0x78 = p_unk0x04->ReadInteger();
	if (m_unk0x78 == 0) {
		p_unk0x04->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_unk0x04->ReadRightBracket();
	p_unk0x04->ReadLeftCurly();

	m_unk0x7c = new GolStringTable[m_unk0x78];
	m_unk0x80 = new LegoChar[m_unk0x78 * 13];
	if (m_unk0x7c == NULL || m_unk0x80 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;
	LegoU32 offset = 0;
	if (i < m_unk0x78) {
		LegoU32 tableOffset = offset;

		do {
			::strncpy(&m_unk0x80[offset], p_unk0x04->ReadStringWithMaxLength(8), 8);
			m_unk0x80[offset + 8] = '\0';
			::strcat(&m_unk0x80[offset], ".srf");

			((GolStringTable*) ((LegoU8*) m_unk0x7c + tableOffset))->UseOwnedBuffers();

			i++;
			offset += 13;
			tableOffset += sizeof(GolStringTable);
		} while (i < m_unk0x78);
	}

	p_unk0x04->ReadRightCurly();
}

// STUB: LEGORACERS 0x004a2ac0
void CrimsonPebble0x228::VTable0x00(undefined4, undefined4, undefined4)
{
	STUB(0x4a2ac0);
}

// STUB: LEGORACERS 0x004a2b00
void CrimsonPebble0x228::VTable0x04(undefined4, undefined4, undefined4)
{
	STUB(0x4a2b00);
}

// STUB: LEGORACERS 0x004a2b40
void CrimsonPebble0x228::VTable0x08(undefined4, undefined4, undefined4)
{
	STUB(0x4a2b40);
}

// STUB: LEGORACERS 0x004a2b80
void CrimsonPebble0x228::VTable0x0c(undefined4, undefined4, undefined4)
{
	STUB(0x4a2b80);
}

// STUB: LEGORACERS 0x004a2bc0
void CrimsonPebble0x228::VTable0x10(undefined4, undefined4, undefined4)
{
	STUB(0x4a2bc0);
}

// STUB: LEGORACERS 0x004a2c00
void CrimsonPebble0x228::VTable0x14(undefined4, undefined4, undefined4)
{
	STUB(0x4a2c00);
}

// STUB: LEGORACERS 0x004a2c40
void CrimsonPebble0x228::VTable0x18(undefined4, undefined4, undefined4)
{
	STUB(0x4a2c40);
}

// STUB: LEGORACERS 0x004a2c80
void CrimsonPebble0x228::VTable0x1c(undefined4, undefined4, undefined4)
{
	STUB(0x4a2c80);
}

// STUB: LEGORACERS 0x004a2cc0
void CrimsonPebble0x228::VTable0x20(undefined4, undefined4, undefined4)
{
	STUB(0x4a2cc0);
}

// STUB: LEGORACERS 0x004a2d00
void CrimsonPebble0x228::VTable0x24(undefined4, undefined4, undefined4)
{
	STUB(0x4a2d00);
}

// STUB: LEGORACERS 0x004a2d40
void CrimsonPebble0x228::VTable0x28(undefined4, undefined4, undefined4)
{
	STUB(0x4a2d40);
}

// STUB: LEGORACERS 0x004a2d80
void CrimsonPebble0x228::VTable0x2c(undefined4, undefined4, undefined4)
{
	STUB(0x4a2d80);
}
