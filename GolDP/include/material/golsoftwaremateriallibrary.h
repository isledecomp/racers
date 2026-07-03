#ifndef GOLSOFTWAREMATERIALLIBRARY_H
#define GOLSOFTWAREMATERIALLIBRARY_H

#include "golmateriallibrary.h"

class GolSoftwareMaterial;

// VTABLE: GOLDP 0x100563d0
// SIZE 0x20
class GolSoftwareMaterialLibrary : public GolMaterialLibrary {
public:
	GolSoftwareMaterialLibrary();
	~GolSoftwareMaterialLibrary() override; // vtable+0x00

	void Clear() override;                                // vtable+0x08
	void ReleaseMaterials() override;                     // vtable+0x0c
	void RestoreMaterials() override;                     // vtable+0x10
	void AllocateItems() override;                        // vtable+0x14
	void CreateMaterial(LegoU32 p_index) override;        // vtable+0x18
	GolMaterial* GetItem(LegoU32 p_index) const override; // vtable+0x28

	// SYNTHETIC: GOLDP 0x10017820
	// GolSoftwareMaterialLibrary::`vector deleting destructor'

private:
	GolSoftwareMaterial* m_items; // 0x1c
};

#endif // GOLSOFTWAREMATERIALLIBRARY_H
