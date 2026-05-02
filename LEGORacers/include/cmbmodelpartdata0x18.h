#ifndef CMBMODELPARTDATA0X18_H
#define CMBMODELPARTDATA0X18_H

#include "decomp.h"
#include "types.h"

// SIZE 0x18
class CmbModelPartData0x18 {
public:
	CmbModelPartData0x18();
	~CmbModelPartData0x18();
	void Clear();

private:
	LegoU32 m_vertexCount;      // 0x00
	LegoU32 m_frameCount;       // 0x04
	LegoU32 m_keyCount;         // 0x08
	LegoFloat (*m_vertices)[3]; // 0x0c
	LegoFloat (*m_frames)[4];   // 0x10
	LegoU16* m_keys;            // 0x14
};

#endif // CMBMODELPARTDATA0X18_H
