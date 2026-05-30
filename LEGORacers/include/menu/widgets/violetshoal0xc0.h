#ifndef VIOLETSHOAL0XC0_H
#define VIOLETSHOAL0XC0_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "render/golrenderdevice.h"

// VTABLE: LEGORACERS 0x004b2450
// SIZE 0xc0
class VioletShoal0xc0 : public ObscureCarousel0x78 {
public:
	VioletShoal0xc0();

	void Reset() override;                                                                    // vtable+0x00
	~VioletShoal0xc0() override;                                                              // vtable+0x04
	LegoBool32 VTable0x08() override;                                                         // vtable+0x08
	void SetParent(ObscureVantage0x58*) override;                                             // vtable+0x0c
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                               // vtable+0x3c
	void VTable0x40() override;                                                               // vtable+0x40
	void VTable0x44(undefined4) override;                                                     // vtable+0x44
	void VTable0x48(VisualState0x4*, VisualState0x4*) override;                               // vtable+0x48
	void VTable0x4c(VisualState0x4*, VisualState0x4*) override;                               // vtable+0x4c
	LegoS32 VTable0x54() override;                                                            // vtable+0x54
	LegoS32 VTable0x58() override;                                                            // vtable+0x58
	virtual void VTable0x5c(undefined4*, undefined4*);                                        // vtable+0x5c

	// SYNTHETIC: LEGORACERS 0x0046ca60
	// VioletShoal0xc0::`scalar deleting destructor'

protected:
	undefined4 m_unk0x78;                     // 0x78
	undefined4 m_unk0x7c;                     // 0x7c
	undefined4 m_unk0x80;                     // 0x80
	undefined4 m_unk0x84;                     // 0x84
	GolRenderDevice::MaterialColor m_unk0x88; // 0x88
	GolRenderDevice::Light m_unk0x8c;         // 0x8c
	undefined4 m_unk0x9c;                     // 0x9c
	undefined4 m_unk0xa0;                     // 0xa0
	LegoFloat m_unk0xa4;                      // 0xa4
	undefined m_unk0xa8[0xbc - 0xa8];         // 0xa8
	undefined4 m_unk0xbc;                     // 0xbc
};

#endif // VIOLETSHOAL0XC0_H
