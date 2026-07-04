#ifndef MANAGEDMATERIALTABLE_H
#define MANAGEDMATERIALTABLE_H

#include "material/materialtable.h"

class GolRenderDevice;

// SIZE 0x0c
struct ManagedMaterialTable : public MaterialTable {
	ManagedMaterialTable();
	~ManagedMaterialTable();

	void Initialize(GolRenderDevice* p_renderer, LegoU32 p_count);
	void Clear();
};

#endif // MANAGEDMATERIALTABLE_H
