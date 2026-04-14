#ifndef GOLDP_GOLDPSTATE_H
#define GOLDP_GOLDPSTATE_H

#include "golcommondrawstate.h"

// VTABLE: GOLDP 0x10056140
// SIZE 0xc8ac4
class GolDrawDPState : public GolCommonDrawState {
public:
	GolDrawDPState();
	~GolDrawDPState() override;

	LegoS32 VTable0x00() override;
	void VTable0x08(HWND p_hWnd) override;                          // vtable+0x08
	void VTable0x0c(undefined4, undefined4) override;               // vtable+0x0c
	undefined4 VTable0x10() override;                               // vtable+0x10
	undefined4 VTable0x14(undefined4) override;                     // vtable+0x14
	undefined4 VTable0x18(undefined4) override;                     // vtable+0x18
	undefined4 VTable0x1c(undefined4) override;                     // vtable+0x1c
	undefined4 VTable0x20(undefined4, undefined4) override;         // vtable+0x20
	undefined4 VTable0x24(undefined4, undefined4) override;         // vtable+0x24
	undefined4 VTable0x28(undefined4, undefined4) override;         // vtable+0x28
	void VTable0x2c(undefined4, undefined4*, undefined4*) override; // vtable+0x2c
	void VTable0x30(undefined4, undefined4*) override;              // vtable+0x30
	void VTable0x34(undefined4, undefined4, undefined4*) override;  // vtable+0x34
	undefined4 VTable0x38() override;                               // vtable+0x38

	void VTable0x48() override;       // vtable+0x4c
	void VTable0x50() override;       // vtable+0x48
	undefined4 VTable0x58() override; // vtable+0x58
	undefined4 VTable0x5c() override; // vtable+0x5c
	undefined4 VTable0x60() override; // vtable+0x60
	undefined4 VTable0x64() override; // vtable+0x64
	undefined4 VTable0x68() override; // vtable+0x68
	undefined4 VTable0x6c() override; // vtable+0x6c
	undefined4 VTable0x70() override; // vtable+0x70
	undefined4 VTable0x74() override; // vtable+0x74
	undefined4 VTable0x78() override; // vtable+0x78
	undefined4 VTable0x7c() override; // vtable+0x7c
	undefined4 VTable0x80() override; // vtable+0x80
	undefined4 VTable0x84() override; // vtable+0x84
	undefined4 VTable0x88() override; // vtable+0x88
	undefined4 VTable0x8c() override; // vtable+0x8c
	undefined4 VTable0x90() override; // vtable+0x90
	undefined4 VTable0x94() override; // vtable+0x94
	undefined4 VTable0x98() override; // vtable+0x98
	undefined4 VTable0x9c() override; // vtable+0x9c
	undefined4 VTable0xa0() override; // vtable+0xa0
	undefined4 VTable0xa4() override; // vtable+0xa4
	undefined4 VTable0xa8() override; // vtable+0xa8
	undefined4 VTable0xac() override; // vtable+0xac
	undefined4 VTable0xb0() override; // vtable+0xb0
	undefined4 VTable0xb4() override; // vtable+0xb4

	// SYNTHETIC: GOLDP 0x100010e0
	// GolDrawDPState::`scalar deleting destructor'

private:
	undefined m_unk0x20[0x2c - 0x20];    // 0x20
	HWND m_hWnd;                         // 0x2c
	undefined m_unk0x30[0xc8ac4 - 0x30]; // 0x30
};

#endif // GOLDP_GOLDPSTATE_H
