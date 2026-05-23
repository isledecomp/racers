#ifndef FLUFFYGLOOMKINS0X118_H
#define FLUFFYGLOOMKINS0X118_H

#include "compat.h"
#include "decomp.h"
#include "zoweeblubberworth0xf0.h"

class AmberHaze0x20;
class AmberLens0x344;
class AmberLensBase0x120;
class BoundingShape0x2c;
class CmbModelPart0x34;
class FloatyBarge0x4c;
class FloatyBoat0x28;
class GdbModel0x48;
class GreyFalconNode0x1c;
class MabMaterialAnimation0x14;
class PurpleRibbon0x24;
class ShadowWolf0xc;
class WhiteFalconNode0x18;

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class FluffyGloomkins0x118 : public ZoweeBlubberworth0xf0 {
public:
	FluffyGloomkins0x118();
	~FluffyGloomkins0x118() override;
	void VTable0x08() override;                                           // vtable+0x08
	undefined4* VTable0x0c() override;                                    // vtable+0x0c
	void VTable0x18() override;                                           // vtable+0x18
	void VTable0x1c(WhiteFalcon0x140*) override;                          // vtable+0x1c
	void VTable0x20(WhiteFalcon0x140*) override;                          // vtable+0x20
	void VTable0x24(WhiteFalcon0x140*) override;                          // vtable+0x24
	void VTable0x28(WhiteFalcon0x140*) override;                          // vtable+0x28
	MagentaRibbon0x20* VTable0x2c(LegoU32 p_index) const override;        // vtable+0x2c
	AmberHaze0x1c* VTable0x30(LegoU32 p_index) const override;            // vtable+0x30
	CmbModelPart0x34* VTable0x34(LegoU32 p_index) const override;         // vtable+0x34
	IGdbModel0x40* VTable0x38(LegoU32 p_index) const override;            // vtable+0x38
	ShadowWolf0xc* VTable0x3c(LegoU32 p_index) const override;            // vtable+0x3c
	WhiteFalconNode0x18* VTable0x40(LegoU32 p_index) const override;      // vtable+0x40
	BoundingShape0x2c* VTable0x44(LegoU32 p_index) const override;        // vtable+0x44
	FloatyBoat0x28* VTable0x48(LegoU32 p_index) const override;           // vtable+0x48
	MabMaterialAnimation0x14* VTable0x4c(LegoU32 p_index) const override; // vtable+0x4c
	AmberLensBase0x120* VTable0x50(LegoU32 p_index) const override;       // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// FluffyGloomkins0x118::`scalar deleting destructor'

private:
	void FUN_10017390();

	PurpleRibbon0x24* m_unk0xf0;          // 0xf0
	AmberHaze0x20* m_unk0xf4;             // 0xf4
	GdbModel0x48* m_unk0xf8;              // 0xf8
	GreyFalconNode0x1c* m_unk0xfc;        // 0xfc
	FloatyBarge0x4c* m_unk0x100;          // 0x100
	ShadowWolf0xc* m_unk0x104;            // 0x104
	MabMaterialAnimation0x14* m_unk0x108; // 0x108
	CmbModelPart0x34* m_unk0x10c;         // 0x10c
	BoundingShape0x2c* m_unk0x110;        // 0x110
	AmberLens0x344* m_unk0x114;           // 0x114
};

#endif // FLUFFYGLOOMKINS0X118_H
