#ifndef GOLWORLDDATABASEEX_H
#define GOLWORLDDATABASEEX_H

#include "compat.h"
#include "decomp.h"
#include "world/golworlddatabase.h"

class AmberHaze0x20;
class GolCamera;
class GolCameraBase;
class GolBoundingShape;
class CmbModelPart0x34;
class GolBillboardEx;
class GolWorldEntity;
class GolModel;
class GolSceneTransformNode;
class MabMaterialAnimation0x14;
class PurpleRibbon0x24;
class GolModelMaterialTable;
class GolSceneNode;

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class GolWorldDatabaseEx : public GolWorldDatabase {
public:
	GolWorldDatabaseEx();
	~GolWorldDatabaseEx() override;
	void VTable0x08() override;                                           // vtable+0x08
	undefined4* VTable0x0c() override;                                    // vtable+0x0c
	void VTable0x18() override;                                           // vtable+0x18
	void VTable0x1c(GolRenderDevice*) override;                           // vtable+0x1c
	void VTable0x20(GolRenderDevice*) override;                           // vtable+0x20
	void VTable0x24(GolRenderDevice*) override;                           // vtable+0x24
	void VTable0x28(GolRenderDevice*) override;                           // vtable+0x28
	GolTextureList* VTable0x2c(LegoU32 p_index) const override;           // vtable+0x2c
	GolMaterialLibrary* VTable0x30(LegoU32 p_index) const override;       // vtable+0x30
	CmbModelPart0x34* VTable0x34(LegoU32 p_index) const override;         // vtable+0x34
	GolModelBase* VTable0x38(LegoU32 p_index) const override;             // vtable+0x38
	GolModelMaterialTable* VTable0x3c(LegoU32 p_index) const override;    // vtable+0x3c
	GolSceneNode* VTable0x40(LegoU32 p_index) const override;             // vtable+0x40
	GolBoundingShape* VTable0x44(LegoU32 p_index) const override;         // vtable+0x44
	GolWorldEntity* VTable0x48(LegoU32 p_index) const override;           // vtable+0x48
	MabMaterialAnimation0x14* VTable0x4c(LegoU32 p_index) const override; // vtable+0x4c
	GolCameraBase* VTable0x50(LegoU32 p_index) const override;            // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// GolWorldDatabaseEx::`scalar deleting destructor'

private:
	void FUN_10017390();

	PurpleRibbon0x24* m_unk0xf0;          // 0xf0
	AmberHaze0x20* m_unk0xf4;             // 0xf4
	GolModel* m_unk0xf8;                  // 0xf8
	GolSceneTransformNode* m_unk0xfc;     // 0xfc
	GolBillboardEx* m_unk0x100;           // 0x100
	GolModelMaterialTable* m_unk0x104;    // 0x104
	MabMaterialAnimation0x14* m_unk0x108; // 0x108
	CmbModelPart0x34* m_unk0x10c;         // 0x10c
	GolBoundingShape* m_unk0x110;         // 0x110
	GolCamera* m_unk0x114;                // 0x114
};

#endif // GOLWORLDDATABASEEX_H
