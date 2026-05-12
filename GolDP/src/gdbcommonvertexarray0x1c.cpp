#include "../include/gdbcommonvertexarray0x1c.h"

#include "golerror.h"
#include "golmath.h"

// FUNCTION: GOLDP 0x10016f20
GdbCommonVertexArray0x1c::GdbCommonVertexArray0x1c()
{
	m_unk0x0c = NULL;
	m_unk0x10 = NULL;
	m_unk0x14 = FALSE;
	m_unk0x18 = NULL;
}

// FUNCTION: GOLDP 0x10016f60 FOLDED
GdbCommonVertexArray0x1c::~GdbCommonVertexArray0x1c()
{
	VTable0x0c();
}

// FUNCTION: GOLDP 0x10016ff0
void GdbCommonVertexArray0x1c::VTable0x0c()
{
	if (m_unk0x0c != NULL) {
		delete[] m_unk0x0c;
		m_unk0x0c = NULL;
	}
	if (m_unk0x10 != NULL) {
		delete[] m_unk0x10;
		m_unk0x10 = NULL;
	}
	if (m_unk0x18 != NULL) {
		delete[] m_unk0x18;
		m_unk0x18 = NULL;
	}
	GdbVertexArray0xc::VTable0x0c();
}

// FUNCTION: GOLDP 0x10017050
void GdbCommonVertexArray0x1c::VTable0x34(const PixelFormatMod& p_details)
{
	LegoU32* ptrIn;
	LegoU32* ptrOut;
	LegoU32* ptrInEnd;

	if (m_unk0x18 == NULL) {
		m_unk0x18 = new LegoU32[m_unk0x04];
		if (m_unk0x18 == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
	ptrOut = m_unk0x18;
	ptrIn = m_unk0x10;
	ptrInEnd = ptrIn + m_unk0x04;
	for (; ptrIn < ptrInEnd; ptrIn++, ptrOut++) {
		LegoU32 original = *ptrIn;
		LegoS32 r = (original >> 16) & 0xff;
		LegoS32 g = (original >> 8) & 0xff;
		LegoS32 b = (original >> 0) & 0xff;
		LegoS32 a = (original >> 24) & 0xff;
		r = (r >> p_details.m_redShift) + p_details.m_redOffset;
		if (r > 0xff) {
			r = 0xff;
		}
		g = (g >> p_details.m_grnShift) + p_details.m_grnOffset;
		if (g > 0xff) {
			g = 0xff;
		}
		b = (b >> p_details.m_bluShift) + p_details.m_bluOffset;
		if (b > 0xff) {
			b = 0xff;
		}
		a = (a >> p_details.m_alpShift) + p_details.m_alpOffset;
		if (a > 0xff) {
			a = 0xff;
		}
		*ptrOut = (a << 24) | (r << 16) | (g << 8) | (b << 0);
	}
	m_unk0x14 = TRUE;
}

// FUNCTION: GOLDP 0x10017180
void GdbCommonVertexArray0x1c::VTable0x38()
{
	m_unk0x14 = FALSE;
}
