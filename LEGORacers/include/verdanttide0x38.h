#ifndef VERDANTTIDE0X38_H
#define VERDANTTIDE0X38_H

#include "amberhaze0x1c.h"
#include "decomp.h"
#include "floatypontoon0x4c.h"
#include "types.h"

class BronzeFalcon0xc8770;
class DuskwindBananaRelic0x24;
class GolExport;
class ZoweeBlubberworth0xf0;

// SIZE 0x38
class VerdantTide0x38 {
public:
	// SIZE 0x10
	struct ColorRecord0x10 {
		LegoChar* SetName(const LegoChar* p_name);

		LegoChar m_name[10];        // 0x00
		undefined m_padding0x0a[2]; // 0x0a
		LegoS32 m_materialIndex;    // 0x0c
	};

	// SIZE 0x04
	struct MaterialUsage0x4 {
		LegoU8 m_used;           // 0x00
		undefined m_padding0x01; // 0x01
		LegoU16 m_order;         // 0x02
	};

	VerdantTide0x38();
	~VerdantTide0x38();
	void Destroy();
	void FUN_004978f0(GolExport* p_golExport, BronzeFalcon0xc8770* p_renderer);
	void FUN_00497a10(const LegoChar* p_filename, undefined4 p_binary);
	void FUN_00497c30(const LegoChar* p_filename, undefined4 p_binary, undefined4 p_unk0x0c);
	FloatyPontoon0x4c::Field0x2c* GetMaterialTable();
	void ResetMaterialUsage();
	void MarkMaterialUsed(LegoS32 p_materialIndex);
	LegoS32 FindColorRecordIndexByName(const LegoChar* p_name) const;
	LegoS32 GetMaterialIndexForColorRecord(LegoS32 p_index) const;
	LegoS32 FindColorRecordIndexByMaterialIndex(LegoS32 p_materialIndex) const;
	DuskwindBananaRelic0x24* GetMaterial(LegoU32 p_index) const
	{
		return m_materials != NULL ? m_materials->GetItem(p_index) : NULL;
	}

private:
	LegoS32 Reset();
	void RebuildColorMaterialLookup();

	GolExport* m_golExport;                       // 0x00
	BronzeFalcon0xc8770* m_renderer;              // 0x04
	ZoweeBlubberworth0xf0* m_wdf;                 // 0x08
	AmberHaze0x1c* m_materials;                   // 0x0c
	FloatyPontoon0x4c::Field0x2c m_materialTable; // 0x10
	LegoS32 m_colorRecordCount;                   // 0x1c
	ColorRecord0x10* m_colorRecords;              // 0x20
	LegoS32* m_colorMaterialIndices;              // 0x24
	MaterialUsage0x4* m_materialUsage;            // 0x28
	LegoS32 m_materialCount;                      // 0x2c
	LegoS32 m_usedMaterialCount;                  // 0x30
	LegoS32 m_transparentMaterialCount;           // 0x34
};

#endif // VERDANTTIDE0X38_H
