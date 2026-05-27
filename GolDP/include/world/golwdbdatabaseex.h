#ifndef GOLWDBDATABASEEX_H
#define GOLWDBDATABASEEX_H

#include "compat.h"
#include "decomp.h"
#include "world/golwdbdatabase.h"

class AmberHaze0x20;
class GolCamera;
class GolCameraBase;
class GolBdbBoundingShape;
class CmbModelPart0x34;
class GolWdbBillboardEx;
class GolWdbEntity;
class GolGdbModel;
class GolSceneTransformNode;
class MabMaterialAnimation0x14;
class PurpleRibbon0x24;
class GolGdbMaterialList;
class GolSceneNode;

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class GolWdbDatabaseEx : public GolWdbDatabase {
public:
	GolWdbDatabaseEx();
	~GolWdbDatabaseEx() override;
	void VTable0x08() override;                                           // vtable+0x08
	undefined4* VTable0x0c() override;                                    // vtable+0x0c
	void VTable0x18() override;                                           // vtable+0x18
	void VTable0x1c(GolRenderDevice*) override;                           // vtable+0x1c
	void VTable0x20(GolRenderDevice*) override;                           // vtable+0x20
	void VTable0x24(GolRenderDevice*) override;                           // vtable+0x24
	void VTable0x28(GolRenderDevice*) override;                           // vtable+0x28
	GolTdbTextureList* VTable0x2c(LegoU32 p_index) const override;        // vtable+0x2c
	GolMdbMaterialList* VTable0x30(LegoU32 p_index) const override;       // vtable+0x30
	CmbModelPart0x34* VTable0x34(LegoU32 p_index) const override;         // vtable+0x34
	GolGdbModelBase* VTable0x38(LegoU32 p_index) const override;          // vtable+0x38
	GolGdbMaterialList* VTable0x3c(LegoU32 p_index) const override;       // vtable+0x3c
	GolSceneNode* VTable0x40(LegoU32 p_index) const override;             // vtable+0x40
	GolBdbBoundingShape* VTable0x44(LegoU32 p_index) const override;      // vtable+0x44
	GolWdbEntity* VTable0x48(LegoU32 p_index) const override;             // vtable+0x48
	MabMaterialAnimation0x14* VTable0x4c(LegoU32 p_index) const override; // vtable+0x4c
	GolCameraBase* VTable0x50(LegoU32 p_index) const override;            // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// GolWdbDatabaseEx::`scalar deleting destructor'

private:
	void FUN_10017390();

	PurpleRibbon0x24* m_unk0xf0;          // 0xf0
	AmberHaze0x20* m_unk0xf4;             // 0xf4
	GolGdbModel* m_unk0xf8;               // 0xf8
	GolSceneTransformNode* m_unk0xfc;     // 0xfc
	GolWdbBillboardEx* m_unk0x100;        // 0x100
	GolGdbMaterialList* m_unk0x104;       // 0x104
	MabMaterialAnimation0x14* m_unk0x108; // 0x108
	CmbModelPart0x34* m_unk0x10c;         // 0x10c
	GolBdbBoundingShape* m_unk0x110;      // 0x110
	GolCamera* m_unk0x114;                // 0x114
};

#endif // GOLWDBDATABASEEX_H
