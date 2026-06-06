#ifndef CARBUILDSCREEN_H
#define CARBUILDSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstringtable.h"
#include "menu/screens/imaginaryshape0x2b20.h"
#include "menu/widgets/obscureglyph0x21c.h"
#include "menu/widgets/obscurelattice0x228.h"

// VTABLE: LEGORACERS 0x004b2a38
// SIZE 0x3c34
class CarBuildScreen : public ImaginaryShape0x2b20 {
public:
	CarBuildScreen();

	LegoBool32 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x20(ObscureVantage0x58*) override;                                                        // vtable+0x20
	void VTable0x24(ObscureVantage0x58*) override;                                                        // vtable+0x24
	undefined4 VTable0x28(ObscureVantage0x58*, void*, undefined4, undefined4) override;                   // vtable+0x28
	void VTable0x34(ObscureIcon0x1a8*) override;                                                          // vtable+0x34
	void VTable0x38(ObscureVantage0x58*) override;                                                        // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                                        // vtable+0x44
	void VTable0x4c() override;                                                                           // vtable+0x4c
	void Reset() override;                                                                                // vtable+0x54
	~CarBuildScreen() override;                                                                           // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                                           // vtable+0x78
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override;                    // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00473790
	// CarBuildScreen::`scalar deleting destructor'

protected:
	enum {
		c_carBuildRegionSource = 0x50000000,
		c_carBuildDragThreshold = 5,
		c_carBuildDragDelay = 100,
		c_carBuildClickDelay = 500,
		c_carBuildKeyboardPageUp = InputDevice::c_sourceKeyboard | 0xc9,
		c_carBuildKeyboardPageDown = InputDevice::c_sourceKeyboard | 0xd1,
		c_carBuildKeyboardInsert = InputDevice::c_sourceKeyboard | 0xd2,
		c_carBuildKeyboardDelete = InputDevice::c_sourceKeyboard | 0xd3,
		c_carBuildMouseButton0 = InputDevice::c_sourceMouse,
		c_carBuildMouseButton1 = InputDevice::c_sourceMouse | 1
	};

	LegoBool32 FUN_00473a50(InputEventQueue::Event* p_event, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	void FUN_00473b80(LegoS32 p_deltaX, LegoS32 p_deltaY);
	LegoBool32 FUN_00473ee0(
		ObscureVantage0x58* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10
	);
	LegoBool32 FUN_00474330(
		ObscureVantage0x58* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10
	);
	LegoBool32 FUN_004743f0(InputEventQueue::Event* p_event, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	LegoBool32 FUN_00474470(
		ObscureVantage0x58* p_source,
		InputEventQueue::Event* p_event,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10
	);
	void FUN_00474940();
	void FUN_004774e0(LegoS32 p_deltaX, LegoS32 p_deltaY);
	LegoBool32 FUN_00477540();

	ObscureLattice0x228 m_unk0x2b20; // 0x2b20
	ObscureLattice0x228 m_unk0x2d48; // 0x2d48
	ObscureGlyph0x21c m_unk0x2f70;   // 0x2f70
	ObscureGlyph0x21c m_unk0x318c;   // 0x318c
	ObscureGlyph0x21c m_unk0x33a8;   // 0x33a8
	ObscureGlyph0x21c m_unk0x35c4;   // 0x35c4
	ObscureGlyph0x21c m_unk0x37e0;   // 0x37e0
	ObscureGlyph0x21c m_unk0x39fc;   // 0x39fc
	LegoU32 m_unk0x3c18;             // 0x3c18
	LegoU32 m_unk0x3c1c;             // 0x3c1c
	GolStringTable m_unk0x3c20;      // 0x3c20
};

#endif // CARBUILDSCREEN_H
