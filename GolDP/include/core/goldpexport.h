#ifndef GOLDPEXPORT_H
#define GOLDPEXPORT_H

#include "compat.h"
#include "core/gol.h"
#include "decomp.h"
#include "render/goldrawdpstate.h"

// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class GolDPExport : public GolExport {
public:
	~GolDPExport() override; // vtable+0x00

	// SYNTHETIC: GOLDP 0x10007040
	// GolDPExport::`scalar deleting destructor'

	GolCommonDrawState* GetDrawState() override;               // vtable+0x04
	GolWorldDatabase* VTable0x08() override;                   // vtable+0x08
	GolTextureList* CreateTextureList() override;              // vtable+0x0c
	GolMaterialLibrary* CreateMaterialList() override;         // vtable+0x10
	GolModelBase* VTable0x14() override;                       // vtable+0x14
	GolSceneNode* VTable0x18() override;                       // vtable+0x18
	GolBoundingShape* CreateBoundingShape() override;          // vtable+0x1c
	GolCamera* VTable0x20() override;                          // vtable+0x20
	undefined4 VTable0x24() override;                          // vtable+0x24
	WhiteBaffoon0x50* VTable0x28() override;                   // vtable+0x28
	GolFontBase* CreateFont() override;                        // vtable+0x2c
	GolWorldEntity* VTable0x30() override;                     // vtable+0x30
	AwakeKite0x20* VTable0x34() override;                      // vtable+0x34
	GolFontTable* CreateFontTable() override;                  // vtable+0x38
	void VTable0x3c(GolWorldDatabase*) override;               // vtable+0x3c
	void DestroyTextureList(GolTextureList*) override;         // vtable+0x40
	void DestroyMaterialList(GolMaterialLibrary*) override;    // vtable+0x44
	void VTable0x48(GolModelBase*) override;                   // vtable+0x48
	void VTable0x4c(GolSceneNode*) override;                   // vtable+0x4c
	void DestroyBoundingShape(GolBoundingShape*) override;     // vtable+0x50
	void VTable0x54(GolCamera*) override;                      // vtable+0x54
	void VTable0x58(undefined4*) override;                     // vtable+0x58
	void VTable0x5c(WhiteBaffoon0x50*) override;               // vtable+0x5c
	void DestroyFont(GolFontBase*) override;                   // vtable+0x60
	void VTable0x64(undefined4*) override;                     // vtable+0x64
	void VTable0x68(AwakeKite0x20*) override;                  // vtable+0x68
	void DestroyFontTable(GolNameTable* p_fontTable) override; // vtable+0x6c

private:
	GolDrawDPState m_state; // 0x04
};

#endif // GOLDPEXPORT_H
