#ifndef FLOATYCANOE0X90_H
#define FLOATYCANOE0X90_H

#include "compat.h"
#include "decomp.h"
#include "floatybuoy0x58.h"

// VTABLE: GOLDP 0x10057270
// SIZE 0x90
class FloatyCanoe0x90 : public FloatyBuoy0x58 {
public:
	FloatyCanoe0x90();

	void VTable0x00() override;                                                // vtable+0x00
	void VTable0x10(LegoS32 p_v) override;                                     // vtable+0x10
	void VTable0x14(const GolVec3& p_vector, ResultStruct* p_result) override; // vtable+0x14
	void VTable0x1c(WhiteFalcon0x140&) override;                               // vtable+0x1c
	undefined4 VTable0x20() override;                                          // vtable+0x20
	void VTable0x24(undefined4*) override;                                     // vtable+0x24
	void VTable0x28() override;                                                // vtable+0x28
	virtual void VTable0x4c(LegoU32 p_index);                                  // vtable+0x4c
	virtual void VTable0x50(undefined4* p_value, LegoFloat p_scalar);          // vtable+0x50
	virtual void VTable0x54();                                                 // vtable+0x54
	virtual undefined4 VTable0x58(undefined4);                                 // vtable+0x58
	virtual void VTable0x5c(undefined4);                                       // vtable+0x5c

	void FUN_10027c50(undefined4* p_value, LegoFloat p_scalar);
	void FUN_10027cc0(const GolVec3& p_vector, ResultStruct* p_result);
	void FUN_10027e70(GolMatrix4* p_dest, LegoU32 p_index);
	void FUN_10027fe0(undefined4 p_arg1, GolVec3* p_destVec, LegoFloat* p_destScalar);
	void FUN_10028110(LegoFloat p_arg);
	void FUN_10028140(LegoFloat p_arg);

protected:
	enum {
		c_flagBit0 = 0x1 << 0,
		c_flagBit2 = 0x1 << 2,
		c_flagBit3 = 0x1 << 3,
	};

	LegoFloat m_unk0x58;      // 0x58
	LegoU32 m_flags;          // 0x5c
	undefined2 m_unk0x60;     // 0x60
	undefined2 m_unk0x62;     // 0x62
	undefined4 m_unk0x64;     // 0x64
	undefined4 m_unk0x68;     // 0x68
	LegoFloat m_unk0x6c[3];   // 0x6c
	undefined4* m_unk0x78[3]; // 0x78
	LegoFloat m_unk0x84[3];   // 0x84
};
#endif // FLOATYCANOE0X90_H
