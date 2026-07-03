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
	class CcbTxtParser : public GolTxtParser {
	public:
		// .ccb tokens; ids proven by the field each one fills
		enum {
			e_champion = GolFileParser::e_unknown0x27,
			e_materialLibrary = GolFileParser::e_unknown0x28,
			e_textureList = GolFileParser::e_unknown0x29,
			e_model = GolFileParser::e_unknown0x2a,
			e_chassis = GolFileParser::e_unknown0x2b,
			e_mass = GolFileParser::e_unknown0x2c,
			e_centerOfMass = GolFileParser::e_unknown0x2d,
		};
	};

	// SIZE 0x30
	struct ChampionDefinition {
		GolName m_materialLibraryName; // 0x00
		GolName m_textureListName;     // 0x08
		GolName m_modelName;           // 0x10
		GolName m_chassisName;         // 0x18
		LegoFloat m_mass;              // 0x20
		LegoFloat m_centerOfMassX;     // 0x24
		LegoFloat m_centerOfMassY;     // 0x28
		LegoFloat m_centerOfMassZ;     // 0x2c
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
	void ClearDefinitions();
	void Load(const LoadParams* p_params);
	LegoBool32 HasDefinitions() const { return m_definitions != NULL; }

	// SYNTHETIC: LEGORACERS 0x0041d1f0
	// ChampionDefinitionList::`scalar deleting destructor'

private:
	friend class RaceState;

	void Reset();
	GolModelEntity* CreateChampionModel(const LegoChar* p_name);
	GolModelEntity* CreateChampionModel(ChampionDefinition* p_definition);

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
