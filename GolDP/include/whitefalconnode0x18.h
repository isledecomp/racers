#ifndef WHITEFALCONNODE0X18_H
#define WHITEFALCONNODE0X18_H

#include "golnametable.h"

// VTABLE: GOLDP 0x10057454
// SIZE 0x18
class WhiteFalconNode0x18 : public GolNameTable {
public:
	WhiteFalconNode0x18();
	~WhiteFalconNode0x18() override;             // vtable+0x00
	void Allocate(LegoU32 p_capacity) override;  // vtable+0x04
	void Clear() override;                       // vtable+0x08
	virtual void VTable0x0c() = 0;               // vtable+0x0c
	virtual void VTable0x10(undefined4 p_param); // vtable+0x10
	virtual void VTable0x14(undefined4 p_unk0x04,
							undefined4 p_unk0x08);   // vtable+0x14
	virtual void VTable0x18() = 0;                   // vtable+0x18
	virtual undefined4 VTable0x1c(undefined4);       // vtable+0x1c
	virtual void VTable0x20(undefined4);             // vtable+0x20
	virtual void VTable0x24(undefined4);             // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4); // vtable+0x28
	virtual void VTable0x2c(undefined4, undefined4); // vtable+0x2c

	// SYNTHETIC: GOLDP 0x100299a0
	// WhiteFalconNode0x18::`scalar deleting destructor'

private:
	undefined4 m_unk0x0c; // 0x0c
	undefined4 m_unk0x10; // 0x10
	undefined4 m_unk0x14; // 0x14
};

#endif // WHITEFALCONNODE0X18_H
