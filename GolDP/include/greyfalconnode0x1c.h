#ifndef GREYFALCONNODE0x1C_H
#define GREYFALCONNODE0x1C_H

#include "compat.h"
#include "decomp.h"
#include "whitefalconnode0x18.h"

class JadeOrbitBase0x10;
class JadeOrbit0xd0;
struct GolMatrix4;

// VTABLE: GOLDP 0x1005672c
// SIZE 0x1c
class GreyFalconNode0x1c : public WhiteFalconNode0x18 {
public:
	GreyFalconNode0x1c();
	~GreyFalconNode0x1c() override; // vtable+0x00

	void Clear() override;                                                // vtable+0x08
	void VTable0x0c() override;                                           // vtable+0x0c
	JadeOrbitBase0x10* VTable0x18(LegoU32 p_index) const override;        // vtable+0x18
	LegoU32 VTable0x1c(const JadeOrbitBase0x10&) const override;          // vtable+0x1c
	void VTable0x20(const GolMatrix4& p_m) override;                      // vtable+0x20
	void VTable0x24(const GolMatrix34* p_m) override;                     // vtable+0x24
	void VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const override; // vtable+0x2c

	void FUN_10014a60(const GolMatrix4& p_m1, const GolMatrix4& p_m2, const GolMatrix4& p_m3);

	// SYNTHETIC: GOLDP 0x10017940
	// GreyFalconNode0x1c::`vector deleting destructor'

private:
	JadeOrbit0xd0* m_unk0x18; // 0x18
};

#endif // GREYFALCONNODE0x1C_H
