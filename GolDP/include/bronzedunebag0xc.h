#ifndef BRONZEDUNEBAG0XC_H
#define BRONZEDUNEBAG0XC_H

#include "compat.h"
#include "golddune0x38.h"

// SIZE 0xc
// VTABLE: GOLDP 0x10057554
class BronzeDuneBag0xc {
public:
	BronzeDuneBag0xc();

	virtual void VTable0x00(undefined4*, undefined4, undefined4); // vtable+0x
	virtual void VTable0x04(undefined4*);                         // vtable+0x
	virtual void VTable0x08(undefined4*, undefined4, undefined4); // vtable+0x
	virtual void VTable0x0c(undefined4*, undefined4);             // vtable+0x
	virtual void VTable0x10(undefined4*);                         // vtable+0x
	virtual undefined4 VTable0x14();                              // vtable+0x
	virtual undefined4 VTable0x18();                              // vtable+0x
	virtual undefined4 VTable0x1c();                              // vtable+0x

	// FUNCTION: GOLDP 0x1002a0f0
	virtual ~BronzeDuneBag0xc() // vtable+0x00
	{
		// FUN_1002a1b0();
		m_unk0x8 = 0;
		if (m_unk0x4 != NULL) {
			delete[] m_unk0x4;
			m_unk0x4 = NULL;
		}
	}
	void FUN_1002a120(undefined4*);
	void FUN_1002a1b0();

	// SYNTHETIC: GOLDP 0x1002a0b0
	// BronzeDuneBag0xc::`scalar deleting destructor'

protected:
	undefined4* m_unk0x4; // 0x4
	undefined4 m_unk0x8;  // 0x8
};

#endif // BRONZEDUNEBAG0XC_H
