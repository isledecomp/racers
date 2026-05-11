#ifndef IGDBMODEL0x40_H
#define IGDBMODEL0x40_H

#include "decomp.h"
#include "golmath.h"
#include "shadowwolf0xc.h"
#include "types.h"

class GolFileParser;
struct GolVec3;

class GdbVertexArray0xc;

// VTABLE: GOLDP 0x10057224
// SIZE 0x40
class IGdbModel0x40 {
public:
	IGdbModel0x40();

	virtual void VTable0x00(GolFileParser& p_parser);                                                    // vtable+0x00
	virtual void VTable0x04(undefined4*);                                                                // vtable+0x04
	virtual void VTable0x08(undefined4*);                                                                // vtable+0x08
	virtual void VTable0x0c(GolFileParser& p_parser) = 0;                                                // vtable+0x0c
	virtual void VTable0x10(GolFileParser& p_parser) = 0;                                                // vtable+0x10
	virtual void VTable0x14(GolFileParser& p_parser);                                                    // vtable+0x14
	virtual void VTable0x18(undefined4, undefined2, undefined4, undefined4, undefined4, undefined4) = 0; // vtable+0x18
	virtual void VTable0x1c(undefined4 p_arg1, const LegoChar* p_name, LegoBool32 p_binary);             // vtable+0x1c
	virtual ~IGdbModel0x40();                                                                            // vtable+0x20
	virtual void VTable0x24();                                                                           // vtable+0x24
	virtual void VTable0x28(undefined4*);                                                                // vtable+0x28
	virtual void VTable0x2c(undefined4, undefined4);                                                     // vtable+0x2c
	virtual void VTable0x30(undefined4*);                                                                // vtable+0x30
	virtual void VTable0x34(undefined4);                                                                 // vtable+0x34
	virtual void VTable0x38(GolVec3*, LegoFloat*, LegoFloat);                                            // vtable+0x38
	virtual void VTable0x3c(undefined4);                                                                 // vtable+0x3c
	virtual void VTable0x40(undefined4);                                                                 // vtable+0x40

	void FUN_100272e0(undefined4, undefined4);

	// SYNTHETIC: GOLDP 0x10027070
	// IGdbModel0x40::`scalar deleting destructor'

protected:
	ShadowWolf0xc m_unk0x04;
	GdbVertexArray0xc* m_unk0x10;
	undefined4 m_unk0x14;
	undefined4 m_unk0x18;
	undefined4 m_unk0x1c;
	undefined4 m_unk0x20;
	undefined4 m_unk0x24;
	GolVec3 m_unk0x28;
	LegoFloat m_unk0x34;
	LegoFloat m_unk0x38;
	LegoBool32 m_unk0x3c;
};

#endif // IGDBMODEL0x40_H
