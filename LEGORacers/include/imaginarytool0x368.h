#ifndef IMAGINARYTOOL0X368_H
#define IMAGINARYTOOL0X368_H

#include "compat.h"
#include "decomp.h"
#include "imaginarynotion0x290.h"

class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class ImaginaryTool0x368 : public ImaginaryNotion0x290 {
public:
	ImaginaryTool0x368();

	class HelperAt0x354 {
	public:
		undefined m_unk0x00[32]; // 0x00
		undefined4 m_unk0x20;    // 0x20
	};

	undefined4 VTable0x18(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x34(undefined4) override;                                           // vtable+0x34
	void VTable0x3c(undefined4) override;                                           // vtable+0x3c
	void VTable0x40(undefined4) override;                                           // vtable+0x40
	void VTable0x54() override;                                                     // vtable+0x54
	void VTable0x5c() override;                                                     // vtable+0x5c
	void VTable0x64() override;                                                     // vtable+0x64
	~ImaginaryTool0x368() override;                                                 // vtable+0x68
	void VTable0x6c() override;                                                     // vtable+0x6c
	void VTable0x74() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                     // vtable+0x78
	virtual void VTable0x80();                                                      // vtable+0x80
	virtual void VTable0x84() = 0;                                                  // vtable+0x84
	virtual void VTable0x88();                                                      // vtable+0x88
	virtual void VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*);     // vtable+0x8c
	virtual void VTable0x90(undefined4);                                            // vtable+0x90
	virtual void VTable0x94(undefined4);                                            // vtable+0x94

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// ImaginaryTool0x368::`scalar deleting destructor'

protected:
	undefined m_unk0x290[0x354 - 0x290]; // 0x290
	HelperAt0x354** m_unk0x354;          // 0x354
	undefined m_unk0x3d8[0x368 - 0x358]; // 0x358
};

#endif // IMAGINARYTOOL0X368_H
