#ifndef OBSIDIANMANTLE0X3B4_H
#define OBSIDIANMANTLE0X3B4_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/imaginarytool0x368.h"
#include "render/rectangle.h"

class ObscureVantage0x58;

// VTABLE: LEGORACERS 0x004b2dc0
// SIZE 0x3b4
class ObsidianMantle0x3b4 : public ImaginaryTool0x368 {
public:
	// FUNCTION: LEGORACERS 0x00476e80
	~ObsidianMantle0x3b4() override {} // vtable+0x68

	undefined4 VTable0x14(ObscureVantage0x58*, void*, undefined4, undefined4) override; // vtable+0x14
	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;   // vtable+0x1c
	void Reset() override;                        // vtable+0x54
	LegoBool32 VTable0x78(undefined4) override;   // vtable+0x78
	LegoBool32 VTable0x7c(Rect*, Rect*) override; // vtable+0x7c

	// SYNTHETIC: LEGORACERS 0x00476ed0
	// ObsidianMantle0x3b4::`scalar deleting destructor'

protected:
	void FUN_00474e40();
	void FUN_00474e70();
	void FUN_00474ef0();

	undefined4 m_unk0x368;               // 0x368
	undefined4 m_unk0x36c;               // 0x36c
	undefined4 m_unk0x370;               // 0x370
	undefined4 m_unk0x374;               // 0x374
	undefined m_unk0x378[0x37c - 0x378]; // 0x378
	LegoU8 m_unk0x37c;                   // 0x37c
	LegoU8 m_unk0x37d;                   // 0x37d
	LegoU16 m_unk0x37e;                  // 0x37e
	undefined4 m_unk0x380;               // 0x380
	undefined4 m_unk0x384;               // 0x384
	undefined4 m_unk0x388;               // 0x388
	undefined4 m_unk0x38c;               // 0x38c
	undefined4 m_unk0x390;               // 0x390
	undefined4 m_unk0x394;               // 0x394
	undefined4 m_unk0x398;               // 0x398
	undefined4 m_unk0x39c;               // 0x39c
	undefined4 m_unk0x3a0;               // 0x3a0
	undefined4 m_unk0x3a4;               // 0x3a4
	GolString m_unk0x3a8;                // 0x3a8
};

#endif // OBSIDIANMANTLE0X3B4_H
