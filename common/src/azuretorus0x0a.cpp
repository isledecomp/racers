#include "azuretorus0x0a.h"

#include "types.h"

#include <ctype.h>
#include <memory.h>

// FUNCTION: LEGORACERS 0x00449dc0
LegoS32 AzureTorus0x0a::FUN_00449dc0(undefined2* p_string)
{
	// real strlen?
	LegoS32 len = 0;

	while (*p_string++) {
		len++;
	}

	return len;
}

// FUNCTION: GOLDP 0x1002f950
// FUNCTION: LEGORACERS 0x00449e10
AzureTorus0x0a::AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f970
// FUNCTION: LEGORACERS 0x00449e30
AzureTorus0x0a::~AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f990
// FUNCTION: LEGORACERS 0x00449e50
undefined2* AzureTorus0x0a::FUN_00449e50(undefined4 p_param)
{
	return &m_unk0x00[m_unk0x06 + p_param];
}

// FUNCTION: GOLDP 0x1002f9b0
// FUNCTION: LEGORACERS 0x00449e70
undefined4 AzureTorus0x0a::FUN_00449e70(undefined2* p_buf, LegoS32 p_count)
{
	m_unk0x08 = 0;
	m_unk0x06 = 0;
	m_unk0x04 = 0;
	m_unk0x00 = p_buf;
	FUN_00449f00();

	if (p_count == 0) {
		m_unk0x04 = EightMinusSix() + 1;
		return 1;
	}

	if (p_count < EightMinusSix()) {
		m_unk0x04 = p_count;
		return 1;
	}

	Reset();
	return 0;
}

// FUNCTION: LEGORACERS 0x00449ed0
undefined4 AzureTorus0x0a::FUN_00449ed0(AzureTorus0x0a* p_torus)
{
	Reset();
	m_unk0x00 = p_torus->m_unk0x00;
	m_unk0x04 = p_torus->m_unk0x04;
	FUN_00449f00();
	return 1;
}

// FUNCTION: LEGORACERS 0x00449f00
void AzureTorus0x0a::FUN_00449f00()
{
	// Seek to end?
	m_unk0x08 = 0;
	m_unk0x06 = 0;

	while (m_unk0x00[m_unk0x08]) {
		m_unk0x08++;
	}
}

// FUNCTION: LEGORACERS 0x00449f30
void AzureTorus0x0a::FUN_00449f30()
{
	// read line?
	m_unk0x08 = 0;
	m_unk0x06 = 0;

	while (m_unk0x00[m_unk0x08]) {
		if (m_unk0x00[m_unk0x08] == '\n') {
			break;
		}

		m_unk0x08++;
	}
}

// FUNCTION: LEGORACERS 0x00449f70
void AzureTorus0x0a::FUN_00449f70()
{
	if (!m_unk0x00[m_unk0x08]) {
		return;
	}

	m_unk0x08++;
	m_unk0x06 = m_unk0x08;

	while (m_unk0x00[m_unk0x08]) {
		if (m_unk0x00[m_unk0x08] == '\n') {
			break;
		}

		m_unk0x08++;
	}
}

// FUNCTION: LEGORACERS 0x00449fc0
undefined4 AzureTorus0x0a::FUN_00449fc0(AzureTorus0x0a* p_torus)
{
	// strcmp?
	LegoS32 len = EightMinusSix();
	if (len != p_torus->EightMinusSix()) {
		return 0;
	}

	while (--len >= 0) {
		if (m_unk0x00[len] != *p_torus->FUN_00449e50(len)) {
			return 0;
		}
	}

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a020
undefined4 AzureTorus0x0a::FUN_0044a020(AzureTorus0x0a* p_torus)
{
	LegoS32 len = FUN_00449dc0(p_torus->m_unk0x00);
	if (len >= m_unk0x04) {
		return 0;
	}

	memcpy(m_unk0x00, p_torus->m_unk0x00, 2 * len);
	m_unk0x06 = p_torus->m_unk0x06;
	m_unk0x08 = p_torus->m_unk0x08;

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a080
undefined4 AzureTorus0x0a::FUN_0044a080(undefined2* p_string)
{
	LegoS32 len = FUN_00449dc0(p_string);
	if (len >= m_unk0x04) {
		return 0;
	}

	memcpy(m_unk0x00, p_string, 2 * len);
	m_unk0x00[len] = 0;
	m_unk0x08 = len;

	return 1;
}

// FUNCTION: LEGORACERS 0x0044a0d0
void AzureTorus0x0a::ToUpperCase()
{
	LegoS32 i = EightMinusSix();
	while (--i >= 0) {
		LegoU16 c = m_unk0x00[i];
		if ((c >= 0x80 && c <= 0xe0) || islower(c)) {
			m_unk0x00[i] = c + ('A' - 'a');
		}
	}
}

// FUNCTION: LEGORACERS 0x0044a130
void AzureTorus0x0a::FUN_0044a130(char* p_string)
{
	LegoS32 i = EightMinusSix();
	p_string[i] = '\0';

	while (--i >= 0) {
		p_string[i] = m_unk0x00[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a160
void AzureTorus0x0a::FUN_0044a160(char* p_buf)
{
	LegoS32 i = EightMinusSix();
	memset(p_buf, 0, 8);
	i = i > 8 ? 8 : i;

	while (--i >= 0) {
		p_buf[i] = m_unk0x00[i];
	}
}

// FUNCTION: LEGORACERS 0x0044a1a0
LegoS32 AzureTorus0x0a::FUN_0044a1a0()
{
	LegoS32 i = FUN_00449dc0(m_unk0x00);
	LegoS32 count = 1;
	while (--i >= 0) {
		if (m_unk0x00[i] == '\n') {
			count++;
		}
	}

	return count;
}
