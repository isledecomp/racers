#ifndef GOLDP_AWAKEKITE0x20_H
#define GOLDP_AWAKEKITE0x20_H

#include "hypnoticnoise0x1c.h"
#include "smallcocoon0xc.h"

class BronzeFalcon0xc8770;

// SIZE 0x20
// VTABLE: GOLDP 0x10056364
class AwakeKite0x20 : public HypnoticNoise0x1c {
public:
	AwakeKite0x20();
	~AwakeKite0x20() override;

	void VTable0x08() override; // vtable+0x08

	// SYNTHETIC: GOLDP 0x10005d30
	// AwakeKite0x20::`scalar deleting destructor'

	void VTable0x0c() override;                              // vtable+0x0c
	void VTable0x10() override;                              // vtable+0x10
	void VTable0x14() override;                              // vtable+0x14
	UtopianPan0xa4* VTable0x20(undefined4 p_index) override; // vtable+0x20

private:
	UtopianPan0xa4* m_unk0x1c; // 0x1c
};

#endif // GOLDP_ AWAKEKITE0x20H
