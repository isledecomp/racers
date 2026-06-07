#ifndef DRIVERCOSMETICTABLE_H
#define DRIVERCOSMETICTABLE_H

#include "cmbmodelpart0x34.h"
#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "racer/turquoiseglowcolor.h"
#include "types.h"

class GolMaterialLibrary;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class GolTextureList;
class OpalHaven0xf4;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b00a4
// SIZE 0x80
class DriverCosmeticTable : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004b00b0
	// SIZE 0x1fc
	class DdfTxtParser : public GolTxtParser {};

	// SIZE 0x14
	struct LoadParams {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		undefined4 m_unk0x08;           // 0x08
		LegoChar* m_filename;           // 0x0c
		undefined4 m_unk0x10;           // 0x10
	};

	// SIZE 0x30
	struct Entry0x30 {
		LegoU16 m_unk0x00;          // 0x00
		GolName m_unk0x02;          // 0x02
		GolName m_unk0x0a;          // 0x0a
		GolName m_unk0x12;          // 0x12
		GolName m_unk0x1a;          // 0x1a
		LegoU8 m_unk0x22;           // 0x22
		LegoU8 m_unk0x23;           // 0x23
		LegoU8 m_unk0x24;           // 0x24
		LegoU8 m_unk0x25;           // 0x25
		LegoU8 m_unk0x26;           // 0x26
		LegoU8 m_unk0x27;           // 0x27
		LegoU8 m_unk0x28;           // 0x28
		LegoU8 m_unk0x29;           // 0x29
		LegoU8 m_unk0x2a;           // 0x2a
		TurquoiseGlowColor m_color; // 0x2b
	};

	DriverCosmeticTable();
	~DriverCosmeticTable() override; // vtable+0x00

	void Clear() override; // vtable+0x08
	void Load(LoadParams* p_params);
	void LoadStrings();
	OpalHaven0xf4* LoadEntry(const LegoChar* p_name);
	void FUN_00421050(LegoU32 p_index, TurquoiseGlowColor* p_color);
	void FUN_00421020(const LegoChar* p_name, TurquoiseGlowColor* p_color);
	LegoBool32 HasEntries() const { return m_entries != NULL; }

	// SYNTHETIC: LEGORACERS 0x004206f0
	// DriverCosmeticTable::`scalar deleting destructor'

private:
	void Reset();
	void ClearEntries();
	OpalHaven0xf4* LoadEntry(Entry0x30* p_entry);

	GolStringTable m_strings;         // 0x0c
	GolExport* m_golExport;           // 0x20
	GolD3DRenderDevice* m_renderer;   // 0x24
	Entry0x30* m_entries;             // 0x28
	GolModelBase** m_models;          // 0x2c
	GolTextureList** m_textures;      // 0x30
	GolMaterialLibrary** m_materials; // 0x34
	OpalHaven0xf4* m_loadedEntries;   // 0x38
	GolSceneNode* m_rootNode;         // 0x3c
	CmbModelPart0x34 m_modelParts;    // 0x40
	LegoU32 m_entryCapacity;          // 0x74
	LegoU32 m_loadedEntryCount;       // 0x78
	LegoBool32 m_binary;              // 0x7c
};

#endif // DRIVERCOSMETICTABLE_H
