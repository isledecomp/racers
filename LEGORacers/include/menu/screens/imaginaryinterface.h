#ifndef IMAGINARYINTERFACE_H
#define IMAGINARYINTERFACE_H

#include "decomp.h"
#include "input/inputeventqueue.h"
#include "surface/silverdune0x30.h"
#include "types.h"

class ObscureIcon0x1a8;
class ObscureVantage0x58;

union ObscureVantageEventResultValue {
	ObscureVantage0x58* m_widget;
	LegoBool32 m_result;

	ObscureVantageEventResultValue() {}
	ObscureVantageEventResultValue(ObscureVantage0x58* p_widget) : m_widget(p_widget) {}
	ObscureVantageEventResultValue(int p_result) : m_result(p_result) {}
	ObscureVantageEventResultValue(LegoBool32 p_result) : m_result(p_result) {}

	operator LegoBool32() const { return m_result; }
};

// VTABLE: LEGORACERS 0x004b2388
class ImaginaryInterface {
public:
	virtual void VTable0x00(ObscureVantage0x58*) = 0;                                      // vtable+0x00
	virtual void VTable0x04(ObscureVantage0x58*) = 0;                                      // vtable+0x04
	virtual void VTable0x08(ObscureVantage0x58*) = 0;                                      // vtable+0x08
	virtual void VTable0x0c(ObscureVantage0x58*) = 0;                                      // vtable+0x0c
	virtual void VTable0x10(ObscureVantage0x58*) = 0;                                      // vtable+0x10
	virtual undefined4 VTable0x14(ObscureVantage0x58*, void*, undefined4, undefined4) = 0; // vtable+0x14
	virtual LegoBool32 VTable0x18(
		ObscureVantage0x58*,
		InputEventQueue::Event*,
		undefined4,
		undefined4
	) = 0; // vtable+0x18
	virtual LegoBool32 VTable0x1c(
		ObscureVantage0x58*,
		InputEventQueue::Event*,
		undefined4,
		undefined4
	) = 0;                                                                                 // vtable+0x1c
	virtual void VTable0x20(ObscureVantage0x58*) = 0;                                      // vtable+0x20
	virtual void VTable0x24(ObscureVantage0x58*) = 0;                                      // vtable+0x24
	virtual undefined4 VTable0x28(ObscureVantage0x58*, void*, undefined4, undefined4) = 0; // vtable+0x28
	virtual void VTable0x2c(ObscureIcon0x1a8*) = 0;                                        // vtable+0x2c
	virtual void VTable0x30(ObscureIcon0x1a8*) = 0;                                        // vtable+0x30
	virtual void VTable0x34(ObscureIcon0x1a8*) = 0;                                        // vtable+0x34
	virtual void VTable0x38(ObscureVantage0x58*) = 0;                                      // vtable+0x38
	virtual void VTable0x3c(ObscureIcon0x1a8*) = 0;                                        // vtable+0x3c
	virtual void VTable0x40(ObscureIcon0x1a8*) = 0;                                        // vtable+0x40
	virtual void VTable0x44(ObscureVantage0x58*) = 0;                                      // vtable+0x44
	virtual void VTable0x48(ObscureVantage0x58*) = 0;                                      // vtable+0x48
};

#endif // IMAGINARYINTERFACE_H
