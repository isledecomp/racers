#ifndef GDBPARTLIBRARY0X1C_H
#define GDBPARTLIBRARY0X1C_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GdbPartDefinition0x0c;
class GdbPartVertexPool0x14;
class GolFileParser;
class IGdbModel0x40;

// VTABLE: LEGORACERS 0x004af428
// SIZE 0x1c
class GdbPartLibrary0x1c : public GolNameTable {
public:
	GdbPartLibrary0x1c();
	~GdbPartLibrary0x1c() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x00407610
	// GdbPartLibrary0x1c::`scalar deleting destructor'

	void Reset();
	void Load(const LegoChar* p_filename, LegoBool32 p_binary);
	void CopyPartToModel(BronzeFalcon0xc8770* p_renderer, IGdbModel0x40* p_model, const LegoChar* p_name);

private:
	void ReadParts(GolFileParser& p_parser);
	void CopyPartGroupStart(BronzeFalcon0xc8770* p_renderer, LegoU32 p_groupIndex, const LegoChar* p_materialName);
	void EmitCopyTriangle(LegoU32 p_index0, LegoU32 p_index1, LegoU32 p_index2);
	LegoS32 CopyBatchVertex(LegoU32 p_sourceVertex);
	void FlushCopyBatch();

	GdbPartVertexPool0x14* m_vertexPool; // 0x0c
	LegoU32 m_partCount;                 // 0x10
	GdbPartDefinition0x0c* m_parts;      // 0x14
	LegoU32 m_unk0x18;                   // 0x18
};

#endif // GDBPARTLIBRARY0X1C_H
