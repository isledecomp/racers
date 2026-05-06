#ifndef OBSCUREICON0X1A8_H
#define OBSCUREICON0X1A8_H

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"
#include "rectangle.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b2944
// SIZE 0x1a8
class ObscureIcon0x1a8 : public ObscureVantage0x58 {
public:
	// SIZE 0x84
	class CreateParams0x84 {
	public:
		GolExport* m_golExport;                 // 0x00
		BronzeFalcon0xc8770* m_renderer;        // 0x04
		SoundGroupBinding* m_soundGroupBinding; // 0x08
		ImaginaryInterface* m_eventHandler;     // 0x0c
		undefined m_unk0x10[0x18 - 0x10];       // 0x10
		LegoS32 m_width;                        // 0x18
		LegoS32 m_height;                       // 0x1c
		undefined m_unk0x20[0x38 - 0x20];       // 0x20
		LegoBool m_unk0x38;                     // 0x38
		undefined m_unk0x39[0x84 - 0x39];       // 0x39
	};

	// SIZE 0x90
	class CreateState0x90 {
	public:
		undefined4 m_unk0x00[0x90 / sizeof(undefined4)]; // 0x00
	};

	ObscureIcon0x1a8();
	void VTable0x00() override;                                                            // vtable+0x00
	~ObscureIcon0x1a8() override;                                                          // vtable+0x04
	undefined4 VTable0x08() override;                                                      // vtable+0x08
	void VTable0x10(Rect*) override;                                                       // vtable+0x10
	undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
	undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(Rect*, Rect*) override;                                          // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                            // vtable+0x3c
	virtual void VTable0x40();
	virtual void VTable0x44(undefined4);
	virtual void VTable0x48(undefined4);
	virtual void VTable0x4c(undefined4);
	virtual void VTable0x50(undefined4);
	virtual void VTable0x54(undefined4);
	virtual void VTable0x58(undefined4);
	virtual LegoBool32 VTable0x5c();
	virtual ObscureIcon0x1a8* VTable0x60();
	virtual ObscureIcon0x1a8* VTable0x64();
	virtual ObscureIcon0x1a8* VTable0x68();
	virtual ObscureIcon0x1a8* VTable0x6c();

	LegoBool32 FUN_00471e30(CreateParams0x84* p_createParams, const CreateState0x90* p_createState);

	// SYNTHETIC: LEGORACERS 0x00471c80
	// ObscureIcon0x1a8::`scalar deleting destructor'

protected:
	undefined m_unk0x58[0x1a8 - 0x58]; // 0x58
};

#endif // OBSCUREICON0X1A8_H
