#ifndef GOLMODELMATERIALTABLE_H
#define GOLMODELMATERIALTABLE_H

#include "decomp.h"
#include "material/materialtable.h"
#include "types.h"

class GolFileParser;
class GolMaterial;
class GolRenderDevice;

// SIZE 0x0c
class GolModelMaterialTable : public MaterialTable {
public:
	enum {
		e_materials = 0x27,
	};

	GolModelMaterialTable();
	~GolModelMaterialTable();

	void Destroy();

	void Initialize(GolRenderDevice* p_renderer, undefined4 p_count);
	void Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void Parse(GolRenderDevice* p_renderer, GolFileParser& p_parser);

	GolRenderDevice* GetRenderer() const { return m_renderer; }
	LegoU32 GetCount() const { return m_count; }
	GolMaterial* GetMaterial(LegoU32 p_index) const { return static_cast<GolMaterial*>(m_entries[p_index]); }
};

#endif // GOLMODELMATERIALTABLE_H
