#ifndef SILVERHOLLOW0XB8_H
#define SILVERHOLLOW0XB8_H

#include "decomp.h"
#include "floatybuoy0x58.h"
#include "types.h"

class IGdbModel0x40;
class CmbModelPart0x34;
class ShadowWolf0xc;
class WhiteFalcon0x140;
class WhiteFalconNode0x18;

// Shares its vtable shape and core 0x00..0x8f layout with GOLDP FloatyCanoe0x90.
// LEGORACERS promotes the first FloatyFerry tail block, 0x90..0xb8, into this
// complete class; GlassShard0x3b8 construction proves the 0xb8-byte size.
// VTABLE: LEGORACERS 0x004af754
// SIZE 0xb8
class SilverHollow0xb8 : public FloatyBuoy0x58 {
public:
	SilverHollow0xb8();

	void VTable0x00() override;                                                        // vtable+0x00
	void VTable0x10(LegoS32 p_elapsed) override;                                       // vtable+0x10
	void VTable0x14(const WhiteFalconView0xcc& p_view, ViewResult* p_result) override; // vtable+0x14
	void VTable0x1c(WhiteFalcon0x140& p_renderer) override;                            // vtable+0x1c
	LegoBool32 VTable0x20() override;                                                  // vtable+0x20
	void VTable0x24(TransformPayload0x20* p_transform) override;                       // vtable+0x24
	void VTable0x28() override;                                                        // vtable+0x28
	virtual void VTable0x4c(LegoU32 p_index);                                          // vtable+0x4c
	virtual void VTable0x50(IGdbModel0x40* p_model, LegoFloat p_modelDistance);        // vtable+0x50
	virtual void VTable0x54();                                                         // vtable+0x54
	virtual WhiteFalconNode0x18* VTable0x58(undefined4);                               // vtable+0x58
	virtual void VTable0x5c(undefined4);                                               // vtable+0x5c

	void FUN_00411250(IGdbModel0x40* p_model, LegoFloat p_modelDistance);
	void FUN_00411510(LegoU32 p_index, GolVec3* p_destVec, LegoFloat* p_destScalar);
	LegoFloat FUN_00411640() const;
	LegoFloat FUN_00411660() const;
	void FUN_00411680(LegoFloat p_arg);
	void FUN_004116b0(LegoFloat p_arg);
	LegoFloat FUN_004116e0() const;
	LegoFloat FUN_004116f0() const;
	void FUN_00411700(LegoFloat p_arg);
	void FUN_00411730(LegoFloat p_arg);
	IGdbModel0x40* GetModel(LegoU32 p_index) const { return m_models[p_index]; }
	ShadowWolf0xc* GetMaterialTable(LegoU32 p_index) const { return m_materialTables[p_index]; }

protected:
	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
	};

	LegoFloat m_unk0x58;                // 0x58
	LegoU32 m_flags;                    // 0x5c
	LegoU16 m_unk0x60;                  // 0x60
	LegoU16 m_unk0x62;                  // 0x62
	LegoS32 m_unk0x64;                  // 0x64
	LegoS32 m_unk0x68;                  // 0x68
	ShadowWolf0xc* m_materialTables[3]; // 0x6c
	IGdbModel0x40* m_models[3];         // 0x78
	LegoFloat m_modelDistances[3];      // 0x84
	WhiteFalconNode0x18* m_nodes[3];    // 0x90
	LegoS32 m_partIndices[3];           // 0x9c
	CmbModelPart0x34* m_modelParts[3];  // 0xa8
	LegoFloat m_unk0xb4;                // 0xb4
};

#endif // SILVERHOLLOW0XB8_H
