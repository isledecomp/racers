#ifndef CHAMPIONDEFINITIONLIST_H
#define CHAMPIONDEFINITIONLIST_H

#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolExport;
class GolD3DRenderDevice;
class GolMaterialLibrary;
class GolModelEntity;
class GolModelBase;
class GolTextureList;
class RaceState;

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

	// SIZE 0x14
	struct LoadParams {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		LegoS32 m_entryCapacity;        // 0x08
		const LegoChar* m_fileName;     // 0x0c
		LegoBool32 m_binary;            // 0x10
	};

	ChampionDefinitionList();
	~ChampionDefinitionList() override; // vtable+0x00

	void Clear() override; // vtable+0x08
	void FUN_0041d370(const LoadParams* p_params);

	// SYNTHETIC: LEGORACERS 0x0041d1f0
	// ChampionDefinitionList::`scalar deleting destructor'

private:
	friend class RaceState;

	void Reset();
	void ClearDefinitions();
	GolModelEntity* FUN_0041d780(const LegoChar* p_name);
	GolModelEntity* FUN_0041d7a0(ChampionDefinition* p_definition);

	GolExport* m_golExport;               // 0x0c
	GolD3DRenderDevice* m_renderer;       // 0x10
	ChampionDefinition* m_definitions;    // 0x14
	GolModelBase** m_models;              // 0x18
	GolTextureList** m_textureLists;      // 0x1c
	GolMaterialLibrary** m_materialLists; // 0x20
	GolModelEntity* m_modelEntities;      // 0x24
	LegoU32 m_entryCapacity;              // 0x28
	LegoU32 m_entryCount;                 // 0x2c
	LegoBool32 m_binary;                  // 0x30
};

#endif // CHAMPIONDEFINITIONLIST_H
