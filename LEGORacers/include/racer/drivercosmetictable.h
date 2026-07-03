#ifndef DRIVERCOSMETICTABLE_H
#define DRIVERCOSMETICTABLE_H

#include "cmbmodelpart.h"
#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "racer/drivercosmetics.h"
#include "types.h"

class GolMaterialLibrary;
class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class GolTextureList;
class GolAnimatedEntity;
class GolSceneNode;
class RaceState;

// VTABLE: LEGORACERS 0x004b00a4
// SIZE 0x80
class DriverCosmeticTable : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004b00b0
	// SIZE 0x1fc
	class DdfTxtParser : public GolTxtParser {
	public:
		// driver-definition tokens for fields with proven names
		enum {
			e_driver = 0x27,
			e_material = 0x28,
			e_texture = 0x29,
			e_model = 0x2a,
			e_champion = 0x2b,
			e_redStat = 0x2c,
			e_yellowStat = 0x2d,
			e_greenStat = 0x2e,
			e_blueStat = 0x2f,
			e_stat4 = 0x30,
			e_stat5 = 0x31,
			e_voiceBank = 0x34,
			e_hat = 0x35,
			e_face = 0x36,
			e_torso = 0x37,
			e_legs = 0x38,
			e_expression = 0x39,
			e_aiCharge = 0x3a,
			e_unknown0x33 = 0x33,
		};
	};

	// SIZE 0x14
	struct LoadParams {
		GolExport* m_golExport;         // 0x00
		GolD3DRenderDevice* m_renderer; // 0x04
		undefined4 m_entryCapacity;     // 0x08
		const LegoChar* m_filename;     // 0x0c
		LegoBool32 m_binary;            // 0x10
	};

	// SIZE 0x30
	struct Entry {
		LegoU16 m_unk0x00;           // 0x00
		GolName m_materialName;      // 0x02
		GolName m_textureName;       // 0x0a
		GolName m_modelName;         // 0x12
		GolName m_championName;      // 0x1a
		LegoU8 m_aiChargeColor;      // 0x22
		LegoU8 m_aiChargeTarget;     // 0x23
		LegoU8 m_redStat;            // 0x24
		LegoU8 m_yellowStat;         // 0x25
		LegoU8 m_greenStat;          // 0x26
		LegoU8 m_blueStat;           // 0x27
		LegoU8 m_stat4;              // 0x28
		LegoU8 m_stat5;              // 0x29
		LegoU8 m_voiceBankIndex;     // 0x2a
		DriverCosmetics m_cosmetics; // 0x2b
	};

	DriverCosmeticTable();
	~DriverCosmeticTable() override; // vtable+0x00

	void Clear() override; // vtable+0x08
	void Load(LoadParams* p_params);
	void LoadStrings();
	GolAnimatedEntity* LoadEntry(const LegoChar* p_name);
	void CopyCosmetics(LegoU32 p_index, DriverCosmetics* p_cosmetics);
	void CopyCosmetics(const LegoChar* p_name, DriverCosmetics* p_cosmetics);
	LegoBool32 HasEntries() const { return m_entries != NULL; }

	// SYNTHETIC: LEGORACERS 0x004206f0
	// DriverCosmeticTable::`scalar deleting destructor'

private:
	friend class RaceState;

	void Reset();
	void ClearEntries();
	GolAnimatedEntity* LoadEntry(Entry* p_entry);
	undefined2* GetStringBuffer(const LegoChar* p_name);

	GolStringTable m_strings;           // 0x0c
	GolExport* m_golExport;             // 0x20
	GolD3DRenderDevice* m_renderer;     // 0x24
	Entry* m_entries;                   // 0x28
	GolModelBase** m_models;            // 0x2c
	GolTextureList** m_textures;        // 0x30
	GolMaterialLibrary** m_materials;   // 0x34
	GolAnimatedEntity* m_loadedEntries; // 0x38
	GolSceneNode* m_rootNode;           // 0x3c
	CmbModelPart m_modelParts;          // 0x40
	LegoU32 m_entryCapacity;            // 0x74
	LegoU32 m_loadedEntryCount;         // 0x78
	LegoBool32 m_binary;                // 0x7c
};

#endif // DRIVERCOSMETICTABLE_H
