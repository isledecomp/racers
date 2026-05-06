#ifndef IMAGINARYSHAPE0X2B20
#define IMAGINARYSHAPE0X2B20

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b2cf8
// SIZE 0x2b20
class ImaginaryShape0x2b20 : public ImaginaryTool0x368 {
public:
	ImaginaryShape0x2b20();

	void VTable0x10(undefined4) override;                                             // vtable+0x10
	undefined4 VTable0x14(ObscureIcon0x1a8*, void*, undefined4, undefined4) override; // vtable+0x14
	undefined4 VTable0x18(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override; // vtable+0x18
	undefined4 VTable0x1c(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override;                                                 // vtable+0x1c
	void VTable0x38(undefined4) override;                       // vtable+0x38
	void VTable0x44(undefined4) override;                       // vtable+0x44
	void VTable0x4c() override;                                 // vtable+0x4c
	void VTable0x54() override;                                 // vtable+0x54
	~ImaginaryShape0x2b20() override;                           // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                 // vtable+0x78
	LegoBool32 VTable0x7c(Rect* p_arg1, Rect* p_arg2) override; // vtable+0x7c
	void VTable0x80() override;                                 // vtable+0x80
	void VTable0x84() override;                                 // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
						  MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00476e60
	// ImaginaryShape0x2b20::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2b20 - 0x368]; // 0x368
};

#endif // IMAGINARYSHAPE0X2B20
