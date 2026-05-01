#ifndef BRONZEFALCONSURFACE0X5C_H
#define BRONZEFALCONSURFACE0X5C_H

#include "decomp.h"
#include "slatepeak0x58.h"

class BronzeFalcon0xc8770;

// VTABLE: GOLDP 0x100566d0
// SIZE 0x5c
class BronzeFalconSurface0x5c : public SlatePeak0x58 {
public:
	BronzeFalconSurface0x5c();
	~BronzeFalconSurface0x5c() override;   // vtable+0x00
	void VTable0x14(undefined4*) override; // vtable+0x14
	void VTable0x34() override;            // vtable+0x34

	void FUN_10013600(BronzeFalcon0xc8770*, undefined2, undefined2);

	friend class BronzeFalcon0xc8770;

	// SYNTHETIC: GOLDP 0x10013560
	// BronzeFalconSurface0x5c::`scalar deleting destructor'

private:
	void FUN_100136a0(BronzeFalcon0xc8770*);

	BronzeFalconSurface0x5c* m_next; // 0x58
};

#endif // BRONZEFALCONSURFACE0X5C_H
