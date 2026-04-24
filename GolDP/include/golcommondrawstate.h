#ifndef GOLDP_GOLCOMMONSTATE_H
#define GOLDP_GOLCOMMONSTATE_H

#include "bronzefalcon0xc8770.h"
#include "compat.h"
#include "decomp.h"
#include "goldrawstate.h"

// VTABLE: GOLDP 0x10056994
// SIZE 0x20
class GolCommonDrawState : public GolDrawState {
protected:
	GolCommonDrawState();

public:
	~GolCommonDrawState() override; // vtable+0x04

	// SYNTHETIC: GOLDP 0x100184c0
	// GolCommonDrawState::`scalar deleting destructor'

	LegoS32 VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp,
					   LegoU32 p_flags) override;                             // vtable+0x44
	void VTable0x48() override;                                               // vtable+0x48
	void VTable0x50() override;                                               // vtable+0x50
	void VTable0x54(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x54
	virtual undefined4 VTable0x58() = 0;                                      // vtable+0x58
	virtual LegoU32 VTable0x5c() const;                                       // vtable+0x5c
	virtual undefined4 VTable0x60();                                          // vtable+0x60
	virtual LegoBool32 VTable0x64() const;                                    // vtable+0x64
	virtual LegoBool32 VTable0x68() const;                                    // vtable+0x68
	virtual LegoBool32 VTable0x6c() const;                                    // vtable+0x6c
	virtual LegoBool32 VTable0x70() const;                                    // vtable+0x70
	virtual LegoBool32 VTable0x74() const;                                    // vtable+0x74
	virtual LegoBool32 VTable0x78() const;                                    // vtable+0x78
	virtual LegoBool32 VTable0x7c() const;                                    // vtable+0x7c
	virtual LegoBool32 VTable0x80() const;                                    // vtable+0x80
	virtual LegoBool32 VTable0x84() const;                                    // vtable+0x84
	virtual LegoBool32 VTable0x88() const;                                    // vtable+0x88
	virtual LegoBool32 VTable0x8c() const;                                    // vtable+0x8c
	virtual LegoBool32 VTable0x90() const;                                    // vtable+0x90
	virtual undefined4 VTable0x94();                                          // vtable+0x94
	virtual LegoBool32 VTable0x98() const;                                    // vtable+0x98
	virtual LegoBool32 VTable0x9c() const;                                    // vtable+0x9c
	virtual LegoBool32 VTable0xa0() const;                                    // vtable+0xa0
	virtual LegoBool32 VTable0xa4() const;                                    // vtable+0xa4
	virtual LegoBool32 VTable0xa8() const;                                    // vtable+0xa8
	virtual void* VTable0xac();                                               // vtable+0xac
	virtual undefined4 VTable0xb0();                                          // vtable+0xb0
	virtual undefined4 VTable0xb4();                                          // vtable+0xb4

	undefined4 m_unk0x18;           // 0x18
	BronzeFalcon0xc8770* m_unk0x1c; // 0x1c
};

#endif // GOLDP_GOLCOMMONSTATE_H
