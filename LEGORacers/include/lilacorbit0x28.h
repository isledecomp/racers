#ifndef LILACORBIT0X28_H
#define LILACORBIT0X28_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class WhiteFalcon0x140;

// VTABLE: LEGORACERS 0x004af7cc
// SIZE 0x28
class LilacOrbit0x28 {
public:
	// SIZE 0x20
	struct TransformPayload0x20 {
		LegoS32 m_baseX;   // 0x00
		LegoS32 m_baseY;   // 0x04
		LegoS32 m_baseZ;   // 0x08
		LegoS32 m_baseW;   // 0x0c
		LegoS32 m_offsetX; // 0x10
		LegoS32 m_offsetY; // 0x14
		LegoS32 m_offsetZ; // 0x18
		LegoS32 m_offsetW; // 0x1c
	};

	LilacOrbit0x28();
	virtual void VTable0x00();                                  // vtable+0x00
	virtual void VTable0x04(LegoFloat* p_unk0x04);              // vtable+0x04
	virtual void VTable0x08(LegoFloat* p_unk0x04);              // vtable+0x08
	virtual void VTable0x0c(undefined4 p_unk0x04);              // vtable+0x0c
	virtual void VTable0x10(undefined4 p_unk0x04);              // vtable+0x10
	virtual void VTable0x14(undefined4, undefined4);            // vtable+0x14
	virtual void VTable0x18(undefined4 p_unk0x04);              // vtable+0x18
	virtual void VTable0x1c(WhiteFalcon0x140* p_renderer);      // vtable+0x1c
	virtual LegoBool32 VTable0x20();                            // vtable+0x20
	virtual void VTable0x24(TransformPayload0x20* p_transform); // vtable+0x24
	virtual void VTable0x28();                                  // vtable+0x28
	virtual void VTable0x2c(LegoFloat*, LegoFloat*);            // vtable+0x2c
	virtual void VTable0x30(LegoFloat*, LegoFloat*);            // vtable+0x30
	virtual void VTable0x34(LegoFloat*, LegoFloat*);            // vtable+0x34
	virtual void VTable0x38(LegoFloat*, LegoFloat*);            // vtable+0x38
	virtual void VTable0x3c(LegoFloat* p_unk0x04);              // vtable+0x3c
	virtual void VTable0x40(LegoFloat*, LegoFloat*);            // vtable+0x40
	virtual void VTable0x44(LegoFloat* p_unk0x04);              // vtable+0x44
	virtual void VTable0x48(LegoFloat*, LegoFloat*);            // vtable+0x48

protected:
	LegoFloat m_unk0x04; // 0x04
	LegoFloat m_unk0x08; // 0x08
	LegoFloat m_unk0x0c; // 0x0c
	LegoFloat m_unk0x10; // 0x10
	LegoFloat m_unk0x14; // 0x14
	LegoFloat m_unk0x18; // 0x18
	LegoFloat m_unk0x1c; // 0x1c
	LegoFloat m_unk0x20; // 0x20
	LegoFloat m_unk0x24; // 0x24
};

#endif // LILACORBIT0X28_H
