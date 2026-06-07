#ifndef GDBPARTLIBRARY_H
#define GDBPARTLIBRARY_H

#include "compat.h"
#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolD3DRenderDevice;
class GdbPartDefinition;
class GdbPartVertexPool;
class GolFileParser;
class GolModelBase;

// VTABLE: LEGORACERS 0x004af428
// SIZE 0x1c
class GdbPartLibrary : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004af434
	// SIZE 0x1fc
	class GdbTxtParser : public GolTxtParser {};

	GdbPartLibrary();
	~GdbPartLibrary() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x00407610
	// GdbPartLibrary::`scalar deleting destructor'

	void Reset();
	void Load(const LegoChar* p_filename, LegoBool32 p_binary);
	void CopyPartToModel(GolD3DRenderDevice* p_renderer, GolModelBase* p_model, const LegoChar* p_name);

private:
	void ReadParts(GolFileParser& p_parser);
	void CopyPartGroupStart(GolD3DRenderDevice* p_renderer, LegoU32 p_groupIndex, const LegoChar* p_materialName);
	void EmitCopyTriangle(LegoU32 p_index0, LegoU32 p_index1, LegoU32 p_index2);
	LegoS32 CopyBatchVertex(LegoU32 p_sourceVertex);
	void FlushCopyBatch();

	GdbPartVertexPool* m_vertexPool; // 0x0c
	LegoU32 m_partCount;             // 0x10
	GdbPartDefinition* m_parts;      // 0x14
	LegoU32 m_unk0x18;               // 0x18
};

#endif // GDBPARTLIBRARY_H
