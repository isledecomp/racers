#ifndef FLOATYBOAT0x28_H
#define FLOATYBOAT0x28_H

#include "decomp.h"
#include "golmath.h"

class WhiteFalcon0x140;

// VTABLE: GOLDP 0x100572e4
// SIZE 0x28
class FloatyBoat0x28 {
public:
	FloatyBoat0x28();

	virtual void VTable0x00();                                            // vtable+0x00
	virtual void VTable0x04(GolVec3* p_v) const;                          // vtable+0x04
	virtual void VTable0x08(const GolVec3& p_v);                          // vtable+0x08
	virtual void VTable0x0c(LegoFloat p_v);                               // vtable+0x0c
	virtual void VTable0x10(LegoS32);                                     // vtable+0x10
	virtual void VTable0x14(GolVec3* p_arg1, undefined4*);                // vtable+0x14
	virtual LegoS32 VTable0x18();                                         // vtable+0x18
	virtual void VTable0x1c(WhiteFalcon0x140*);                           // vtable+0x1c
	virtual undefined4 VTable0x20();                                      // vtable+0x20
	virtual void VTable0x24(undefined4*);                                 // vtable+0x24
	virtual void VTable0x28();                                            // vtable+0x28
	virtual void VTable0x2c(const GolVec3& p_add, GolVec3* p_dest) const; // vtable+0x2c
	virtual void VTable0x30(const GolVec3& p_src, GolVec3* p_dest) const; // vtable+0x30
	virtual void VTable0x34(const GolVec3& p_src, GolVec3* p_dest);       // vtable+0x34
	virtual void VTable0x38(const GolVec3& p_src, GolVec3* p_dest) const; // vtable+0x38
	virtual void VTable0x3c(undefined4*);                                 // vtable+0x3c
	virtual void VTable0x40(undefined4, undefined4);                      // vtable+0x40
	virtual void VTable0x44(undefined4*) const;                           // vtable+0x44
	virtual void VTable0x48(GolVec3* p_v1, GolVec3* p_v2) const;          // vtable+0x48

	void FUN_100286d0(GolVec3* p_v);
	LegoFloat FUN_10028710();

private:
	GolVec3 m_v0; // 0x04
	GolVec3 m_v1; // 0x10
	GolVec3 m_v2; // 0x1c
};

#endif // FLOATYBOAT0x28_H
