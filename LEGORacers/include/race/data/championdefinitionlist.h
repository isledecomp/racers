#ifndef CHAMPIONDEFINITIONLIST_H
#define CHAMPIONDEFINITIONLIST_H

#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolExport;
class GolMaterialLibrary;
class GolModelBase;
class GolTextureList;

// VTABLE: LEGORACERS 0x004afde8
// SIZE 0x34
class ChampionDefinitionList : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004afdf4
	// SIZE 0x1fc
	class CcbTxtParser : public GolTxtParser {};

	// SIZE 0x30
	struct ChampionDefinition {
		GolName m_unk0x00;   // 0x00
		GolName m_unk0x08;   // 0x08
		GolName m_unk0x10;   // 0x10
		GolName m_unk0x18;   // 0x18
		LegoFloat m_unk0x20; // 0x20
		LegoFloat m_unk0x24; // 0x24
		LegoFloat m_unk0x28; // 0x28
		LegoFloat m_unk0x2c; // 0x2c
	};

	ChampionDefinitionList();
	~ChampionDefinitionList() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x0041d1f0
	// ChampionDefinitionList::`scalar deleting destructor'

private:
	void Reset();
	void ClearDefinitions();

	GolExport* m_golExport;               // 0x0c
	undefined4 m_unk0x10;                 // 0x10
	ChampionDefinition* m_definitions;    // 0x14
	GolModelBase** m_models;              // 0x18
	GolTextureList** m_textureLists;      // 0x1c
	GolMaterialLibrary** m_materialLists; // 0x20
	undefined* m_unk0x24;                 // 0x24
	undefined4 m_unk0x28;                 // 0x28
	LegoU32 m_entryCount;                 // 0x2c
	undefined4 m_unk0x30;                 // 0x30
};

#endif // CHAMPIONDEFINITIONLIST_H
