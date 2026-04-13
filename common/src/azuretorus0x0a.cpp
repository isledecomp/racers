#include "azuretorus0x0a.h"

#include "types.h"

// FUNCTION: GOLDP 0x1002f950
// FUNCTION: LEGORACERS 0x449e10
AzureTorus0x0a::AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f970
// FUNCTION: LEGORACERS 0x449e30
AzureTorus0x0a::~AzureTorus0x0a()
{
	Reset();
}

// FUNCTION: GOLDP 0x1002f990
// FUNCTION: LEGORACERS 0x449e50
undefined2* AzureTorus0x0a::FUN_00449e50(undefined4 p_param)
{
	return &m_unk0x00[m_unk0x06 + p_param];
}

// FUNCTION: GOLDP 0x1002f9b0
// FUNCTION: LEGORACERS 0x449e70
undefined4 AzureTorus0x0a::FUN_00449e70(undefined2* p_1, LegoS32 p_2)
{
	m_unk0x08 = 0;
	m_unk0x06 = 0;
	m_unk0x04 = 0;
	m_unk0x00 = p_1;
	FUN_00449f00();

	if (p_2 == 0) {
		m_unk0x04 = EightMinusSix() + 1;
		return 1;
	}

	if (p_2 < EightMinusSix()) {
		m_unk0x04 = p_2;
		return 1;
	}

	Reset();
	return 0;
}

// FUNCTION: LEGORACERS 0x449ed0
undefined4 AzureTorus0x0a::FUN_00449ed0(AzureTorus0x0a* p_torus)
{
	Reset();
	m_unk0x00 = p_torus->m_unk0x00;
	m_unk0x04 = p_torus->m_unk0x04;
	FUN_00449f00();
	return 1;
}

// FUNCTION: LEGORACERS 0x449f00
void AzureTorus0x0a::FUN_00449f00()
{
	// Seek to end?
	m_unk0x08 = 0;
	m_unk0x06 = 0;

	while (m_unk0x00[m_unk0x08]) {
		m_unk0x08++;
	}
}

// FUNCTION: LEGORACERS 0x449f30
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

// FUNCTION: LEGORACERS 0x449f70
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

// FUNCTION: LEGORACERS 0x449fc0
undefined4 AzureTorus0x0a::FUN_00449fc0(AzureTorus0x0a* p_torus)
{
	// strcmp?
	LegoS32 len = EightMinusSix();
	if (len != p_torus->EightMinusSix()) {
		return 0;
	}

	while (--len) {
		if (m_unk0x00[len] != *p_torus->FUN_00449e50(len)) {
			return 0;
		}
	}

	return 1;
}
