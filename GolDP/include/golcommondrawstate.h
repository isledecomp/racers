#ifndef GOLDP_GOLCOMMONSTATE_H
#define GOLDP_GOLCOMMONSTATE_H

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

	undefined4 VTable0x44(
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp,
		undefined4 p_flags
	) override;                                                               // vtable+0x44
	void VTable0x48() override;                                               // vtable+0x48
	void VTable0x50() override;                                               // vtable+0x50
	void VTable0x54(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x54
	virtual undefined4 VTable0x58() = 0;                                      // vtable+0x58
	virtual undefined4 VTable0x5c();                                          // vtable+0x5c
	virtual undefined4 VTable0x60();                                          // vtable+0x60
	virtual undefined4 VTable0x64();                                          // vtable+0x64
	virtual undefined4 VTable0x68();                                          // vtable+0x68
	virtual undefined4 VTable0x6c();                                          // vtable+0x6c
	virtual undefined4 VTable0x70();                                          // vtable+0x70
	virtual undefined4 VTable0x74();                                          // vtable+0x74
	virtual undefined4 VTable0x78();                                          // vtable+0x78
	virtual undefined4 VTable0x7c();                                          // vtable+0x7c
	virtual undefined4 VTable0x80();                                          // vtable+0x80
	virtual undefined4 VTable0x84();                                          // vtable+0x84
	virtual undefined4 VTable0x88();                                          // vtable+0x88
	virtual undefined4 VTable0x8c();                                          // vtable+0x8c
	virtual undefined4 VTable0x90();                                          // vtable+0x90
	virtual undefined4 VTable0x94();                                          // vtable+0x94
	virtual undefined4 VTable0x98();                                          // vtable+0x98
	virtual undefined4 VTable0x9c();                                          // vtable+0x9c
	virtual undefined4 VTable0xa0();                                          // vtable+0xa0
	virtual undefined4 VTable0xa4();                                          // vtable+0xa4
	virtual undefined4 VTable0xa8();                                          // vtable+0xa8
	virtual undefined4 VTable0xac();                                          // vtable+0xac
	virtual undefined4 VTable0xb0();                                          // vtable+0xb0
	virtual undefined4 VTable0xb4();                                          // vtable+0xb4

private:
	undefined4 m_unk0x18; // 0x18
	undefined4 m_unk0x1c; // 0x1c
};

#endif // GOLDP_GOLCOMMONSTATE_H
