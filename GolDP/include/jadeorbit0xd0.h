#ifndef JADEORBIT0XD0_H
#define JADEORBIT0XD0_H

#include "compat.h"
#include "jadeorbitbase0x10.h"
#include "types.h"

// VTABLE: GOLDP 0x1005622c
// SIZE 0xd0
class JadeOrbit0xd0 : public JadeOrbitBase0x10 {
public:
	JadeOrbit0xd0();
	void VTable0x00() override;                                      // vtable+0x00
	void VTable0x04(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x04
	void VTable0x08(undefined4, undefined4) override;                // vtable+0x08
	void VTable0x0c(const GolVec3* p_src, GolVec3* p_dest) override; // vtable+0x0c
	void VTable0x10() override;                                      // vtable+0x10
	void VTable0x14() override;                                      // vtable+0x14
	void GetBasis(GolVec3* p_right, GolVec3* p_forward,
				  GolVec3* p_up) override;                            // vtable+0x18
	void VTable0x1c(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x1c
	void VTable0x20(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x20
	void VTable0x24(GolVec3* p_unk0x04, GolVec3* p_unk0x08) override; // vtable+0x24
	void VTable0x28() override;                                       // vtable+0x28
	void VTable0x2c(LegoFloat* p_unk0x04) override;                   // vtable+0x2c
	void GetUp(GolVec3* p_up) override;                               // vtable+0x30
	void GetForward(GolVec3* p_forward) override;                     // vtable+0x34
	void GetRight(GolVec3* p_right) override;                         // vtable+0x38
	void VTable0x3c() override;                                       // vtable+0x3c
	void GetPosition(GolVec3* p_position) override;                   // vtable+0x40
	void SetPosition(GolVec3* p_position) override;                   // vtable+0x44
	void VTable0x48() override;                                       // vtable+0x48

	GolMatrix4 m_unk0x10; // 0x10
	// GolVec3 m_up;        // 0x10
	// LegoFloat m_unk0x1c; // 0x1c
	// GolVec3 m_forward;   // 0x20
	// LegoFloat m_unk0x2c; // 0x2c
	// GolVec3 m_right;     // 0x30
	// LegoFloat m_unk0x3c; // 0x3c
	// GolVec3 m_position;  // 0x40
	// LegoFloat m_unk0x4c; // 0x4c
	GolMatrix4 m_unk0x50; // 0x50
	GolMatrix4 m_unk0x90; // 0x90
};

#endif // JADEORBIT0XD0_H
