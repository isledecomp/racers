#ifndef FLOATYFRIGATE0X9C_H
#define FLOATYFRIGATE0X9C_H

#include "compat.h"
#include "decomp.h"
#include "floatycanoe0x90.h"

class WhiteFalcon0x140;

// VTABLE: GOLDP 0x10056b04
// SIZE 0x9c
class FloatyFrigate0x9c : public FloatyCanoe0x90 {
public:
	FloatyFrigate0x9c();

	void VTable0x1c(WhiteFalcon0x140&) override;                 // vtable+0x1c
	void VTable0x54() override;                                  // vtable+0x54
	virtual void VTable0x60(undefined4*, undefined4, LegoFloat); // vtable+0x60

	void FUN_1001acf0(undefined4* p_arg1, undefined4 p_arg2, LegoFloat p_arg3);

protected:
	undefined4 m_unk0x90[3]; // 0x90
};
#endif // FLOATYFRIGATE0X9C_H
