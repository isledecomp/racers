#ifndef GOLMODELMATERIALTABLE_H
#define GOLMODELMATERIALTABLE_H

#include "decomp.h"
#include "material/materialtable0x0c.h"
#include "types.h"

class GolFileParser;
class DuskwindBananaRelic0x24;
class GolRenderDevice;

// SIZE 0x0c
class GolModelMaterialTable : public MaterialTable0x0c {
public:
	GolModelMaterialTable();
	~GolModelMaterialTable();

	void Destroy();

	void FUN_10025df0(GolRenderDevice* p_renderer, undefined4);
	void FUN_10025e60(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void FUN_10025f90(GolRenderDevice* p_renderer, GolFileParser& p_parser);

	GolRenderDevice* GetRenderer() const { return m_renderer; }
	LegoU32 GetCount() const { return m_count; }
	DuskwindBananaRelic0x24* GetMaterial(LegoU32 p_index) const
	{
		return static_cast<DuskwindBananaRelic0x24*>(m_entries[p_index]);
	}
};

#endif // GOLMODELMATERIALTABLE_H
