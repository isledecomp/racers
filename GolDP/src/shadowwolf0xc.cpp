#include "shadowwolf0xc.h"

#include <stddef.h>

// FUNCTION: GOLDP 0x10025de0
ShadowWolf0xc::ShadowWolf0xc()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
}

// STUB: GOLDP 0x10025df0
void ShadowWolf0xc::FUN_10025df0(undefined4, undefined4)
{
	// TODO
	STUB(0x10025df0);
}

// STUB: GOLDP 0x10025e60
void ShadowWolf0xc::FUN_10025e60(undefined4, undefined4, undefined4)
{
	// TODO
	STUB(0x10025e60);
}

// STUB: GOLDP 0x10025f90
void ShadowWolf0xc::FUN_10025f90(undefined4, undefined4)
{
	// TODO
	STUB(0x10025f90);
}

// FUNCTION: GOLDP 0x100260d0
ShadowWolf0xc::~ShadowWolf0xc()
{
	if (m_unk0x08 != NULL) {
		delete[] m_unk0x08;
		m_unk0x08 = NULL;
	}
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}
