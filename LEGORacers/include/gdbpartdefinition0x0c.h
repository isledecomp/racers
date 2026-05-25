#ifndef GDBPARTDEFINITION0X0C_H
#define GDBPARTDEFINITION0X0C_H

#include "decomp.h"
#include "gdbpartfacegroup0x14.h"
#include "types.h"

class GolFileParser;

// SIZE 0x0c
class GdbPartDefinition0x0c {
public:
	GdbPartDefinition0x0c();
	~GdbPartDefinition0x0c();

	void Clear();
	void Read(GolFileParser& p_parser);

	LegoU32 m_groupCount;           // 0x00
	GdbPartFaceGroup0x14* m_groups; // 0x04
	LegoFloat m_scale;              // 0x08
};

#endif // GDBPARTDEFINITION0X0C_H
