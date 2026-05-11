#include "../include/gdbcommonvertexarray0x1c.h"

#include "golmath.h"

// FUNCTION: GOLDP 0x10016f20
GdbCommonVertexArray0x1c::GdbCommonVertexArray0x1c()
{
	m_unk0x0c = NULL;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
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

// STUB: GOLDP 0x10017050
void GdbCommonVertexArray0x1c::VTable0x34(undefined4)
{
	// TODO
	STUB(0x10017050);
}

// FUNCTION: GOLDP 0x10017180
void GdbCommonVertexArray0x1c::VTable0x38()
{
	m_unk0x14 = 0;
}
