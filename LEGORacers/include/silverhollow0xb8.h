#ifndef SILVERHOLLOW0XB8_H
#define SILVERHOLLOW0XB8_H

#include "ambermeadow0x58.h"
#include "decomp.h"
#include "types.h"

class IGdbModel0x40;
class CmbModelPart0x34;
class ShadowWolf0xc;
class WhiteFalcon0x140;
class WhiteFalconNode0x18;

// VTABLE: LEGORACERS 0x004af754
// SIZE 0xb8
class SilverHollow0xb8 : public AmberMeadow0x58 {
public:
	SilverHollow0xb8();

	void VTable0x00() override;                                           // vtable+0x00
	void VTable0x10(undefined4 p_unk0x04) override;                       // vtable+0x10
	void VTable0x14(undefined4, undefined4) override;                     // vtable+0x14
	void VTable0x1c(WhiteFalcon0x140* p_renderer) override;               // vtable+0x1c
	LegoBool32 VTable0x20() override;                                     // vtable+0x20
	void VTable0x24(TransformPayload0x20* p_transform) override;          // vtable+0x24
	void VTable0x28() override;                                           // vtable+0x28
	virtual void VTable0x4c(undefined4 p_unk0x04);                        // vtable+0x4c
	virtual void VTable0x50(IGdbModel0x40* p_model, LegoFloat p_unk0x08); // vtable+0x50
	virtual void VTable0x54();                                            // vtable+0x54

	IGdbModel0x40* GetModel(LegoU32 p_index) const { return m_models[p_index]; }
	ShadowWolf0xc* GetMaterialTable(LegoU32 p_index) const { return m_unk0x6c[p_index]; }

protected:
	LegoFloat m_unk0x58;               // 0x58
	LegoU32 m_unk0x5c;                 // 0x5c
	LegoU16 m_unk0x60;                 // 0x60
	LegoU16 m_unk0x62;                 // 0x62
	undefined4 m_unk0x64;              // 0x64
	undefined4 m_unk0x68;              // 0x68
	ShadowWolf0xc* m_unk0x6c[3];       // 0x6c
	IGdbModel0x40* m_models[3];        // 0x78
	LegoFloat m_unk0x84[3];            // 0x84
	WhiteFalconNode0x18* m_nodes[3];   // 0x90
	LegoS32 m_unk0x9c[3];              // 0x9c
	CmbModelPart0x34* m_modelParts[3]; // 0xa8
	LegoFloat m_unk0xb4;               // 0xb4
};

#endif // SILVERHOLLOW0XB8_H
