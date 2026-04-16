#ifndef GOLDP_SILVERDUNE0X30_H
#define GOLDP_SILVERDUNE0X30_H

#include "decomp.h"
#include "types.h"

// VTABLE: GOLDP 0x10056d3c
// SIZE 0x30
class SilverDune0x30 {
public:
	SilverDune0x30();

	// FUNCTION: GOLDP 0x1001cf60
	virtual ~SilverDune0x30() {} // vtable+0x00

	virtual void VTable0x04(undefined4*, undefined4*, undefined4);                        // vtable+0x04
	virtual void VTable0x08();                                                            // vtable+0x08
	virtual void VTable0x0c(undefined4*, undefined4*, undefined4);                        // vtable+0x0c
	virtual void VTable0x10();                                                            // vtable+0x10
	virtual void VTable0x14(undefined4*);                                                 // vtable+0x14
	virtual void VTable0x18();                                                            // vtable+0x18
	virtual undefined4 VTable0x1c();                                                      // vtable+0x1c
	virtual void VTable0x20(undefined4, undefined4, undefined4);                          // vtable+0x20
	virtual void VTable0x24(undefined4, undefined4, undefined4, undefined4, undefined4*); // vtable+0x24
	virtual void VTable0x28(undefined4, undefined4, undefined4*);                         // vtable+0x28
	virtual void VTable0x2c();                                                            // vtable+0x2c

	// SYNTHETIC: GOLDP 0x1001cf40
	// SilverDune0x30::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
	undefined4 m_unk0x0c; // 0x0c
	undefined4 m_unk0x10; // 0x10
	undefined4 m_unk0x14; // 0x14
	undefined2 m_unk0x18; // 0x18
	undefined2 m_unk0x1a; // 0x1a
	undefined4 m_unk0x1c; // 0x1c
	undefined4 m_unk0x20; // 0x20
	undefined2 m_unk0x24; // 0x24
	undefined2 m_unk0x26; // 0x26
	undefined2 m_unk0x28; // 0x28
	undefined2 m_unk0x2a; // 0x2a
	undefined2 m_unk0x2c; // 0x2c
};

#endif // GOLDP_SILVERDUNE0X30_H
