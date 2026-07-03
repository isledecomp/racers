#ifndef CHASSISMODELTABLE_H
#define CHASSISMODELTABLE_H

#include "cmbmodelpart.h"
#include "decomp.h"
#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "types.h"

class GolExport;
class GolMaterialLibrary;
class GolD3DRenderDevice;
class GolModelBase;
class GolTextureList;
class GolAnimatedEntity;
class GolSceneNode;
class GolFileParser;
class RaceState;

// VTABLE: LEGORACERS 0x004afe70
// SIZE 0x3c
class ChassisModelTable : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004afe7c
	// SIZE 0x1fc
	class CmbTxtParser : public GolTxtParser {
	public:
		// chassis-table tokens for fields with proven names
		enum {
			e_chassis = 0x27,
			e_variantModels = 0x28,
			e_altVariantModels = 0x29,
			e_centerOfMass = 0x2a,
			e_driverMountOffset = 0x2b,
			e_mass = 0x2c,
			e_shadowSize = 0x2e,
			e_enginePitch = 0x2f,
			e_skidWidths = 0x30,
			e_wheelPositions = 0x31,
			e_shadow = 0x39,
			e_handlingStat = 0x3a,
			e_topSpeedStat = 0x3b,
			e_accelerationStat = 0x3c,
			e_materialLibrary = 0x34,
			e_textureList = 0x35,
			e_model = 0x36,
			e_sceneNode = 0x37,
			e_modelPart = 0x38,
			e_unknown0x2d = 0x2d,
			e_unknown0x32 = 0x32,
			e_unknown0x33 = 0x33,
		};
	};

	ChassisModelTable();
	~ChassisModelTable() override; // vtable+0x00
	void Clear() override;

	// SYNTHETIC: LEGORACERS 0x0041d910
	// ChassisModelTable::`scalar deleting destructor'

	struct Params {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		LegoS32 m_instantiateCount;     // 0x08
		const LegoChar* m_filename;     // 0x0c
		LegoBool32 m_binary;            // 0x10
	};

	LegoU32 Load(const Params* p_params);
	LegoU32 InstantiateModels(const LegoChar* p_name, GolAnimatedEntity** p_primary, GolAnimatedEntity** p_secondary);
	void InstantiateAllModels();
	GolAnimatedEntity* GetPrimaryModel(const LegoChar* p_name);
	void ReleaseInstances();
	LegoBool32 HasItems() const { return m_items != NULL; }

	// SIZE 0x104
	struct Item {
		GolName m_materialNames[2];          // 0x000
		GolName m_textureNames[2];           // 0x010
		GolName m_modelNames[2];             // 0x020
		GolName m_modelPartNames[2];         // 0x030
		GolName m_nodeNames[2];              // 0x040
		GolName m_shadowName;                // 0x050
		GolVec3 m_wheelOffsets[4];           // 0x058
		GolVec3 m_wheelPositions[4];         // 0x088
		GolVec3 m_centerOfMass;              // 0x0b8
		GolVec3 m_driverMountOffset;         // 0x0c4
		LegoFloat m_baseMass;                // 0x0d0
		GolVec2 m_unk0xd4;                   // 0x0d4
		GolVec2 m_shadowSize;                // 0x0dc
		GolVec2 m_skidWidths;                // 0x0e4
		LegoFloat m_enginePitchScale;        // 0x0ec
		LegoS32 m_unk0xf0;                   // 0x0f0
		LegoS32 m_unk0xf4;                   // 0x0f4
		GolAnimatedEntity* m_primaryModel;   // 0x0f8
		GolAnimatedEntity* m_secondaryModel; // 0x0fc
		LegoU8 m_handlingStat;               // 0x100
		LegoU8 m_accelerationStat;           // 0x101
		LegoU8 m_topSpeedStat;               // 0x102
		undefined m_unk0x103[0x104 - 0x103]; // 0x103
	};

private:
	friend class RaceState;

	void Reset();
	void ParseVariantNames(GolFileParser* p_parser, LegoU32 p_index, LegoU32 p_variant);
	LegoU32 InstantiateModels(Item* p_item, GolAnimatedEntity** p_primary, GolAnimatedEntity** p_secondary);

	GolExport* m_golExport;                // 0x0c
	GolD3DRenderDevice* m_renderer;        // 0x10
	Item* m_items;                         // 0x14
	GolModelBase** m_models;               // 0x18
	GolTextureList** m_textureLists;       // 0x1c
	GolMaterialLibrary** m_materialLists;  // 0x20
	GolSceneNode** m_sceneNodes;           // 0x24
	CmbModelPart* m_modelParts;            // 0x28
	GolAnimatedEntity* m_animatedEntities; // 0x2c
	LegoU32 m_instantiateCount;            // 0x30
	LegoU32 m_instantiatedCount;           // 0x34
	LegoBool32 m_binary;                   // 0x38
};

#endif // CHASSISMODELTABLE_H
