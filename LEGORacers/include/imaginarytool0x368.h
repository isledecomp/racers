#ifndef IMAGINARYTOOL0X368_H
#define IMAGINARYTOOL0X368_H

#include "compat.h"
#include "decomp.h"
#include "imaginarynotion0x290.h"

class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;
class ObscureVantage0x58;

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class ImaginaryTool0x368 : public ImaginaryNotion0x290 {
public:
	ImaginaryTool0x368();

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
	) override;                                 // vtable+0x1c
	void VTable0x34(undefined4) override;       // vtable+0x34
	void VTable0x3c(undefined4) override;       // vtable+0x3c
	void VTable0x40(undefined4) override;       // vtable+0x40
	void VTable0x54() override;                 // vtable+0x54
	CeruleanEmperor0x4c* VTable0x5c() override; // vtable+0x5c
	CeruleanQueen0x58* VTable0x64() override;   // vtable+0x64
	~ImaginaryTool0x368() override;             // vtable+0x68
	void VTable0x6c() override;                 // vtable+0x6c
	void VTable0x74() override;                 // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override; // vtable+0x78
	virtual void VTable0x80();                  // vtable+0x80
	virtual void VTable0x84() = 0;              // vtable+0x84
	virtual LegoBool32 VTable0x88();            // vtable+0x88
	virtual LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
								  MenuToolCreateParams0x30*); // vtable+0x8c
	virtual void VTable0x90(undefined4);                      // vtable+0x90
	virtual void VTable0x94(undefined4);                      // vtable+0x94

	void FUN_00480470(MenuToolContext0x4bc8*, undefined4, undefined4);

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// ImaginaryTool0x368::`scalar deleting destructor'

protected:
	CeruleanEmperor0x4c m_unk0x290;      // 0x290
	undefined4 m_unk0x2dc;               // 0x2dc
	CeruleanQueen0x58 m_unk0x2e0;        // 0x2e0
	undefined m_unk0x33c[0x354 - 0x33c]; // 0x33c
	MenuToolContext0x4bc8* m_unk0x354;   // 0x354
	undefined4 m_unk0x358;               // 0x358
	ObscureVantage0x58* m_unk0x35c;      // 0x35c
	LegoU16 m_unk0x360;                  // 0x360
	LegoU16 m_unk0x362;                  // 0x362
	LegoBool32 m_unk0x364;               // 0x364
};

#endif // IMAGINARYTOOL0X368_H
