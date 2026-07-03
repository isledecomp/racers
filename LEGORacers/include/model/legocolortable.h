#ifndef LEGOCOLORTABLE_H
#define LEGOCOLORTABLE_H

#include "decomp.h"
#include "golmateriallibrary.h"
#include "scene/golbillboard.h"
#include "types.h"

class GolD3DRenderDevice;
class GolMaterial;
class GolExport;
class GolWorldDatabase;

// SIZE 0x38
class LegoColorTable {
public:
	enum {
		e_colors = 0x2d,
	};

	// SIZE 0x10
	struct ColorRecord {
		LegoChar* SetName(const LegoChar* p_name);

		LegoChar m_name[10];     // 0x00
		LegoS32 m_materialIndex; // 0x0c
	};

	// SIZE 0x04
	struct MaterialUsage {
		LegoU8 m_used;   // 0x00
		LegoU16 m_order; // 0x02
	};

	LegoColorTable();
	~LegoColorTable();
	void Destroy();
	void Initialize(GolExport* p_golExport, GolD3DRenderDevice* p_renderer);
	void LoadColors(const LegoChar* p_filename, undefined4 p_binary);
	void LoadMaterials(const LegoChar* p_filename, undefined4 p_binary, undefined4 p_loadTextures);
	GolBillboard::ManagedMaterialTable* GetMaterialTable();
	GolWorldDatabase* GetWorldDatabase() const { return m_wdf; }
	void ResetMaterialUsage();
	void MarkMaterialUsed(LegoS32 p_materialIndex);
	LegoS32 FindColorRecordIndexByName(const LegoChar* p_name) const;
	LegoS32 GetMaterialIndexForColorRecord(LegoS32 p_index) const;
	LegoS32 FindColorRecordIndexByMaterialIndex(LegoS32 p_materialIndex) const;
	LegoS32 GetUsedMaterialCount() const { return m_usedMaterialCount; }
	LegoS32 GetTransparentMaterialCount() const { return m_transparentMaterialCount; }
	LegoS32 GetMaterialCount() const { return m_materialCount; }
	const MaterialUsage* GetMaterialUsage() const { return m_materialUsage; }
	GolMaterial* GetMaterial(LegoU32 p_index) const
	{
		return m_materials != NULL ? m_materials->GetItem(p_index) : NULL;
	}

private:
	LegoS32 Reset();
	void RebuildColorMaterialLookup();

	GolExport* m_golExport;                             // 0x00
	GolD3DRenderDevice* m_renderer;                     // 0x04
	GolWorldDatabase* m_wdf;                            // 0x08
	GolMaterialLibrary* m_materials;                    // 0x0c
	GolBillboard::ManagedMaterialTable m_materialTable; // 0x10
	LegoS32 m_colorRecordCount;                         // 0x1c
	ColorRecord* m_colorRecords;                        // 0x20
	LegoS32* m_colorMaterialIndices;                    // 0x24
	MaterialUsage* m_materialUsage;                     // 0x28
	LegoS32 m_materialCount;                            // 0x2c
	LegoS32 m_usedMaterialCount;                        // 0x30
	LegoS32 m_transparentMaterialCount;                 // 0x34
};

#endif // LEGOCOLORTABLE_H
