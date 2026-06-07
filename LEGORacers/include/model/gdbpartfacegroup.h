#ifndef GDBPARTFACEGROUP_H
#define GDBPARTFACEGROUP_H

#include "decomp.h"
#include "golname.h"
#include "types.h"

class GolFileParser;

// SIZE 0x14
class GdbPartFaceGroup {
public:
	GdbPartFaceGroup();
	~GdbPartFaceGroup();

	void Clear();
	void Read(GolFileParser& p_parser);

	LegoU16* m_indices;      // 0x00
	LegoU32 m_triangleCount; // 0x04
	GolName m_materialName;  // 0x08
	LegoU32 m_unk0x10;       // 0x10
};

#endif // GDBPARTFACEGROUP_H
