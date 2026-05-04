#ifndef IMAGINARYNOTION0X290_H
#define IMAGINARYNOTION0X290_H

#include "ceruleanemperor0x4c.h"
#include "ceruleanqueen0x58.h"
#include "compat.h"
#include "decomp.h"
#include "imaginaryinterface.h"
#include "obscureicon0x1a8.h"
#include "types.h"

class ObscureVantage0x58;

// VTABLE: LEGORACERS 0x004b2308
// SIZE 0x290
class ImaginaryNotion0x290 : public ImaginaryInterface {
public:
	// SIZE unknown
	class FieldAt0xc4 {
	public:
		void SetUnk0x41(undefined p_unk0x41) { m_unk0x41 = p_unk0x41; }

	private:
		undefined m_unk0x00[0x41 - 0x00]; // 0x00
		undefined m_unk0x41;              // 0x41
	};

	ImaginaryNotion0x290();

	void VTable0x00(undefined4) override;                                             // vtable+0x00
	void VTable0x04(ObscureVantage0x58*) override;                                    // vtable+0x04
	void VTable0x08(undefined4) override;                                             // vtable+0x08
	void VTable0x0c(undefined4) override;                                             // vtable+0x0c
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
	) override;                                                                                // vtable+0x1c
	void VTable0x20(undefined4) override;                                                      // vtable+0x20
	void VTable0x24(undefined4) override;                                                      // vtable+0x24
	undefined4 VTable0x28(ObscureIcon0x1a8*, void*, undefined4, undefined4) override;          // vtable+0x28
	void VTable0x2c(undefined4) override;                                                      // vtable+0x2c
	void VTable0x30(undefined4) override;                                                      // vtable+0x30
	void VTable0x34(undefined4) override;                                                      // vtable+0x34
	void VTable0x38(undefined4) override;                                                      // vtable+0x38
	void VTable0x3c(undefined4) override;                                                      // vtable+0x3c
	void VTable0x40(undefined4) override;                                                      // vtable+0x40
	void VTable0x44(undefined4) override;                                                      // vtable+0x44
	void VTable0x48(undefined4) override;                                                      // vtable+0x48
	virtual void VTable0x4c() = 0;                                                             // vtable+0x4c
	virtual undefined4 VTable0x50();                                                           // vtable+0x50
	virtual void VTable0x54();                                                                 // vtable+0x54
	virtual void VTable0x58(undefined4*);                                                      // vtable+0x58
	virtual void VTable0x5c();                                                                 // vtable+0x5c
	virtual void VTable0x60();                                                                 // vtable+0x60
	virtual void VTable0x64();                                                                 // vtable+0x64
	virtual ~ImaginaryNotion0x290();                                                           // vtable+0x68
	virtual void VTable0x6c();                                                                 // vtable+0x6c
	virtual void VTable0x70(undefined4*);                                                      // vtable+0x70
	virtual void VTable0x74();                                                                 // vtable+0x74
	virtual LegoBool32 VTable0x78(undefined4);                                                 // vtable+0x78
	virtual LegoBool32 VTable0x7c(SilverDune0x30::Rect* p_arg1, SilverDune0x30::Rect* p_arg2); // vtable+0x7c

	undefined4 FUN_0046b630();
	void FUN_0046b6e0();
	void FUN_0046ba60(undefined4*);
	void FUN_0046bb10(undefined4*);
	void FUN_0046bb90(undefined4*, undefined4);
	void FUN_0046bc90(undefined4*, undefined4);
	void FUN_0046bd80(undefined4*, undefined4);
	void FUN_0046be10(undefined4*, undefined2);
	void FUN_0046bea0(undefined4*, undefined2);
	undefined4 FUN_0046bef0(undefined4*, undefined2, undefined2);
	undefined4 FUN_0046bf80(undefined4*, undefined2, undefined2, undefined2);
	undefined4 FUN_0046c050(undefined4*, undefined2, undefined2);
	undefined4 FUN_0046c110(undefined4*, undefined2, undefined2);
	undefined4 FUN_0046c1b0(undefined4*, undefined2, undefined2);
	undefined4 FUN_0046c240(undefined4*, undefined2, undefined2);
	void FUN_0046c2b0(undefined4*, undefined4, undefined2, undefined2);
	undefined4 FUN_0046c400(undefined4*, undefined2, undefined2);
	void FUN_0046c480(undefined4*, undefined4, undefined2);
	void FUN_0046c510(undefined4*, undefined4, undefined2);
	void FUN_0046c5b0(ObscureVantage0x58*, undefined2);
	undefined4 FUN_0046c610(undefined4*, undefined2, undefined2, undefined2, undefined4);
	undefined4 FUN_0046c6f0(undefined4, undefined4, undefined2);
	undefined4 FUN_0046c730(undefined4, undefined2);
	void FUN_0046c760();
	ObscureIcon0x1a8* GetUnk0xd8() { return &m_unk0xd8; }

	// SYNTHETIC: LEGORACERS 0x0046b3f0
	// ImaginaryNotion0x290::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04;          // 0x004
	CeruleanEmperor0x4c m_unk0x08; // 0x008
	undefined4 m_unk0x54;          // 0x054
	CeruleanQueen0x58 m_unk0x58;   // 0x058
	undefined4 m_unk0xb0;          // 0x0b0
	undefined4 m_unk0xb4;          // 0x0b4
	undefined4 m_unk0xb8;          // 0x0b8
	undefined4* m_unk0xbc;         // 0x0bc
	undefined4 m_unk0xc0;          // 0x0c0
	FieldAt0xc4* m_unk0xc4;        // 0x0c4
	undefined4 m_unk0xc8;          // 0x0c8
	undefined4* m_unk0xcc;         // 0x0cc
	undefined4* m_unk0xd0;         // 0x0d0
	undefined4 m_unk0xd4;          // 0x0d4
	ObscureIcon0x1a8 m_unk0xd8;    // 0x0d8
	undefined4 m_unk0x280;         // 0x280
	undefined4 m_unk0x284;         // 0x284
	undefined4 m_unk0x288;         // 0x288
	undefined2 m_unk0x28c;         // 0x28c
};

#endif // IMAGINARYNOTION0X290_H
