#ifndef OBSCURELATTICE0X228_H
#define OBSCURELATTICE0X228_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/widgets/obscureglyph0x21c.h"

class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b1ef0
// SIZE 0x228
class ObscureLattice0x228 : public ObscureGlyph0x21c {
public:
	// SIZE 0xa0
	class CreateParams0xa0 : public ObscureGlyph0x21c::CreateParams0x9c {
	public:
		UtopianPan0xa4* m_unk0x9c; // 0x9c
	};

	ObscureLattice0x228();

	void Reset() override;                                                                    // vtable+0x00
	~ObscureLattice0x228() override;                                                          // vtable+0x04
	LegoBool32 VTable0x08() override;                                                         // vtable+0x08
	ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	void VTable0x58(undefined4) override;                                                     // vtable+0x58

	LegoBool32 FUN_004665f0(CreateParams0xa0* p_createParams, CeruleanEmperor0x4c::Entry0x150* p_styleEntry);
	LegoU32 GetUnk0x224() const { return m_unk0x224; }

	// SYNTHETIC: LEGORACERS 0x00466560
	// ObscureLattice0x228::`scalar deleting destructor'

protected:
	enum {
		// Synthetic keyCode source occupying the high nibble alongside InputDevice::c_source*
		// (keyboard/mouse/joystick). It tags hotspot-region selection messages with the region
		// id in the low 16 bits so they flow through the same keyCode path as real input. Only
		// ever produced and consumed inside this widget; no real input device emits it.
		c_sourceRegion = 0x50000000,
	};

	Rect* FUN_00466640(Rect* p_rect1, Rect* p_rect2, Rect* p_out);
	void FUN_00466690(LegoU32 p_code);
	ObscureVantage0x58* FUN_00466800(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y);

	CeruleanEmperor0x4c::Entry0x150* m_unk0x21c; // 0x21c
	UtopianPan0xa4* m_unk0x220;                  // 0x220
	undefined4 m_unk0x224;                       // 0x224
};

#endif // OBSCURELATTICE0X228_H
