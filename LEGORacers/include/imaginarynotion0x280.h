#ifndef IMAGINARYNOTION0X280_H
#define IMAGINARYNOTION0X280_H

#include "ceruleanemperor0x50.h"
#include "ceruleanqueen0x58.h"
#include "compat.h"
#include "decomp.h"
#include "imaginaryinterface.h"
#include "obscureicon0x1a8.h"

// VTABLE: LEGORACERS 0x004b2308
// SIZE 0x280
class ImaginaryNotion0x280 : public ImaginaryInterface {
public:
	ImaginaryNotion0x280();

	void VTable0x00(undefined4) override;                                           // vtable+0x00
	void VTable0x04(undefined4) override;                                           // vtable+0x04
	void VTable0x08(undefined4) override;                                           // vtable+0x08
	void VTable0x0c(undefined4) override;                                           // vtable+0x0c
	void VTable0x10(undefined4) override;                                           // vtable+0x10
	undefined4 VTable0x14(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x14
	undefined4 VTable0x18(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x20(undefined4) override;                                           // vtable+0x20
	void VTable0x24(undefined4) override;                                           // vtable+0x24
	undefined4 VTable0x28(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x28
	void VTable0x2c(undefined4) override;                                           // vtable+0x2c
	void VTable0x30(undefined4) override;                                           // vtable+0x30
	void VTable0x34(undefined4) override;                                           // vtable+0x34
	void VTable0x38(undefined4) override;                                           // vtable+0x38
	void VTable0x3c(undefined4) override;                                           // vtable+0x3c
	void VTable0x40(undefined4) override;                                           // vtable+0x40
	void VTable0x44(undefined4) override;                                           // vtable+0x44
	void VTable0x48(undefined4) override;                                           // vtable+0x48
	virtual void VTable0x4c(undefined4) = 0;                                        // vtable+0x4c
	virtual undefined4 VTable0x50();                                                // vtable+0x50
	virtual void VTable0x54();                                                      // vtable+0x54
	virtual void VTable0x58();                                                      // vtable+0x58
	virtual void VTable0x5c();                                                      // vtable+0x5c
	virtual void VTable0x60();                                                      // vtable+0x60
	virtual void VTable0x64();                                                      // vtable+0x64
	virtual ~ImaginaryNotion0x280();                                                // vtable+0x68
	virtual void VTable0x6c();                                                      // vtable+0x6c
	virtual void VTable0x70();                                                      // vtable+0x70
	virtual void VTable0x74();                                                      // vtable+0x74
	virtual void VTable0x78();                                                      // vtable+0x78
	virtual void VTable0x7c();                                                      // vtable+0x7c

	// SYNTHETIC: LEGORACERS 0x0046b3f0
	// ImaginaryNotion0x280::`scalar deleting destructor'

protected:
	undefined m_unk0x04[4];           // 0x04
	CeruleanEmperor0x50 m_unk0x08;    // 0x08
	CeruleanQueen0x58 m_unk0x58;      // 0x58
	undefined m_unk0xb0[0xd8 - 0xb0]; // 0xb0
	ObscureIcon0x1a8 m_unk0xd8;       // 0xd8
};

#endif // IMAGINARYNOTION0X280_H
