#ifndef CMBMODELPARTDATA0X18_H
#define CMBMODELPARTDATA0X18_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolFileParser;

// SIZE 0x18
class CmbModelPartData0x18 {
public:
	CmbModelPartData0x18();
	~CmbModelPartData0x18();
	void Clear();

	void FUN_100241d0(GolFileParser& p_parser);

private:
	LegoU32 m_vertexCount; // 0x00
	LegoU32 m_frameCount;  // 0x04
	LegoU32 m_keyCount;    // 0x08
	GolVec3* m_vertices;   // 0x0c
	GolVec4* m_frames;     // 0x10
	LegoU16* m_keys;       // 0x14
};

#endif // CMBMODELPARTDATA0X18_H
