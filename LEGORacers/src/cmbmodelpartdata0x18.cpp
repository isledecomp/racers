#include "cmbmodelpartdata0x18.h"

DECOMP_SIZE_ASSERT(CmbModelPartData0x18, 0x18)

// FUNCTION: LEGORACERS 0x0040e490
CmbModelPartData0x18::CmbModelPartData0x18()
{
	m_vertexCount = 0;
	m_vertices = NULL;
	m_frameCount = 0;
	m_frames = NULL;
	m_keyCount = 0;
	m_keys = NULL;
}

// FUNCTION: LEGORACERS 0x0040e4b0
CmbModelPartData0x18::~CmbModelPartData0x18()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0040e9d0
void CmbModelPartData0x18::Clear()
{
	if (m_vertices != NULL) {
		delete[] m_vertices;
		m_vertices = NULL;
	}

	if (m_frames != NULL) {
		delete[] m_frames;
		m_frames = NULL;
	}

	if (m_keys != NULL) {
		delete[] m_keys;
		m_keys = NULL;
	}

	m_vertexCount = 0;
	m_frameCount = 0;
	m_keyCount = 0;
}
