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
	GolWorldDatabase* CreateWorldDatabase() override;          // vtable+0x08
	GolTextureList* CreateTextureList() override;              // vtable+0x0c
	GolMaterialLibrary* CreateMaterialList() override;         // vtable+0x10
	GolModelBase* CreateModel() override;                      // vtable+0x14
	GolSceneNode* CreateSceneNode() override;                  // vtable+0x18
	GolBoundingShape* CreateBoundingShape() override;          // vtable+0x1c
	GolCamera* CreateCamera() override;                        // vtable+0x20
	undefined4 VTable0x24() override;                          // vtable+0x24
	GolTiledTexture* CreateTiledTexture() override;            // vtable+0x28
	GolFontBase* CreateFont() override;                        // vtable+0x2c
	GolWorldEntity* CreateBillboard() override;                // vtable+0x30
	GolImageDefinitionList* CreateImageList() override;        // vtable+0x34
	GolFontTable* CreateFontTable() override;                  // vtable+0x38
	void DestroyWorldDatabase(GolWorldDatabase*) override;     // vtable+0x3c
	void DestroyTextureList(GolTextureList*) override;         // vtable+0x40
	void DestroyMaterialList(GolMaterialLibrary*) override;    // vtable+0x44
	void DestroyModel(GolModelBase*) override;                 // vtable+0x48
	void DestroySceneNode(GolSceneNode*) override;             // vtable+0x4c
	void DestroyBoundingShape(GolBoundingShape*) override;     // vtable+0x50
	void DestroyCamera(GolCamera*) override;                   // vtable+0x54
	void VTable0x58(undefined4*) override;                     // vtable+0x58
	void DestroyTiledTexture(GolTiledTexture*) override;       // vtable+0x5c
	void DestroyFont(GolFontBase*) override;                   // vtable+0x60
	void DestroyBillboard(GolWorldEntity*) override;           // vtable+0x64
	void DestroyImageList(GolImageDefinitionList*) override;   // vtable+0x68
	void DestroyFontTable(GolNameTable* p_fontTable) override; // vtable+0x6c

private:
	GolDrawDPState m_state; // 0x04
};

#endif // GOLDPEXPORT_H
