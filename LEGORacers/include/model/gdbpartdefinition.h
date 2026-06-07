#ifndef GDBPARTDEFINITION_H
#define GDBPARTDEFINITION_H

#include "decomp.h"
#include "model/gdbpartfacegroup.h"
#include "types.h"

class GolFileParser;

// SIZE 0x0c
class GdbPartDefinition {
public:
	GdbPartDefinition();
	~GdbPartDefinition();

	void Clear();
	void Read(GolFileParser& p_parser);

	LegoU32 m_groupCount;       // 0x00
	GdbPartFaceGroup* m_groups; // 0x04
	LegoFloat m_scale;          // 0x08
};

#endif // GDBPARTDEFINITION_H
