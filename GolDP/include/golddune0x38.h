#ifndef GOLDDUNE0x38_H
#define GOLDDUNE0x38_H

#include "silverdune0x30.h"

// VTABLE: GOLDP 0x1005766c
// SIZE 0x38
class GoldDune0x38 : public SilverDune0x30 {
public:
	GoldDune0x38();

	virtual void VTable0x30(undefined4*, undefined4*); // vtable+0x30
	virtual void VTable0x34() = 0;                     // vtable+0x34
	virtual void VTable0x38() = 0;                     // vtable+0x38

	// SYNTHETIC: GOLDP 0x10004470 FOLDED
	// GoldDune0x38::~GoldDune0x38

	// SYNTHETIC: GOLDP 0x1002f380 FOLDED
	// GoldDune0x38::`scalar deleting destructor'

protected:
	undefined m_unk0x30[0x34 - 0x30]; // 0x30
	undefined2 m_unk0x34;             // 0x34
	LegoU16 m_unk0x36;                // 0x36
};

#endif //  GOLDDUNE0x38_H
