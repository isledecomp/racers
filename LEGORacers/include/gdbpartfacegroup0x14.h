#ifndef GDBPARTFACEGROUP0X14_H
#define GDBPARTFACEGROUP0X14_H

#include "decomp.h"
#include "golname.h"
#include "types.h"

class GolFileParser;

// SIZE 0x14
class GdbPartFaceGroup0x14 {
public:
	GdbPartFaceGroup0x14();
	~GdbPartFaceGroup0x14();

	void Clear();
	void Read(GolFileParser& p_parser);

	LegoU16* m_indices;      // 0x00
	LegoU32 m_triangleCount; // 0x04
	GolName m_materialName;  // 0x08
	LegoU32 m_unk0x10;       // 0x10
};

#endif // GDBPARTFACEGROUP0X14_H
