#ifndef OBSCURECLASSES_H
#define OBSCURECLASSES_H

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"

// VTABLE: LEGORACERS 0x004b29f4
// SIZE 0xa4
class ObscureZebra : public ObscureVantage0x58 {
public:
	ObscureZebra();
	void VTable0x00() override;                             // vtable+0x00
	~ObscureZebra() override;                               // vtable+0x04
	void VTable0x14(undefined4) override;                   // vtable+0x14
	undefined4 VTable0x38(undefined4, undefined4) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004734f0
	// ObscureZebra::`scalar deleting destructor'

protected:
	undefined m_unk0x58[0xa4 - 0x58]; // 0x58
};

// VTABLE: LEGORACERS 0x004b263c
// SIZE 0x58
class ObscureAnthem : public ObscureVantage0x58 {
public:
	ObscureAnthem();
	~ObscureAnthem() override;                                                             // vtable+0x04
	undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
	undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x0046ea30
	// ObscureAnthem::`scalar deleting destructor'
};

// VTABLE: LEGORACERS 0x004b26bc
// SIZE 0x5c
class ObscureAnchor : public ObscureAnthem {
public:
	ObscureAnchor();

	void VTable0x00() override;                             // vtable+0x00
	~ObscureAnchor() override;                              // vtable+0x04
	undefined4 VTable0x38(undefined4, undefined4) override; // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x0046f0d0
	// ObscureAnchor::`scalar deleting destructor'

protected:
	undefined4 m_unk0x58; // 0x58
};

// VTABLE: LEGORACERS 0x004b267c
// SIZE 0x3dc
class ObscureTome : public ObscureAnthem {
public:
	ObscureTome();
	~ObscureTome() override;              // vtable+0x04
	void VTable0x10(undefined4) override; // vtable+0x10

	// SYNTHETIC: LEGORACERS 0x0046ec30
	// ObscureTome::`scalar deleting destructor'

protected:
	ObscureZebra m_unk0x58;     // 0x058
	ObscureAnchor m_unk0xfc[8]; // 0x0fc
};

// VTABLE: LEGORACERS 0x004b1dfc
// SIZE: 0xdc
class ObscureSigil : public ObscureVantage0x58 {
public:
	ObscureSigil();

	void VTable0x00() override;                                                            // vtable+0x00
	~ObscureSigil() override;                                                              // vtable+0x04
	undefined4 VTable0x08() override;                                                      // vtable+0x08
	undefined4 VTable0x2c(void*, undefined4, undefined4) override;                         // vtable+0x2c
	undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(undefined4, undefined4) override;                                // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                            // vtable+0x3c

	// SYNTHETIC: LEGORACERS 0x00465730
	// ObscureSigil::`scalar deleting destructor'

protected:
	undefined4 m_unk0x58;             // 0x58
	undefined4 m_unk0x5c;             // 0x5c
	undefined4 m_unk0x60;             // 0x60
	undefined4 m_unk0x64;             // 0x64
	undefined4 m_unk0x68;             // 0x68
	undefined4 m_unk0x6c;             // 0x6c
	undefined m_unk0x70[0x88 - 0x70]; // 0x70
	undefined4 m_unk0x88;             // 0x88
	undefined4 m_unk0x8c;             // 0x8c
	undefined4 m_unk0x90;             // 0x90
	undefined4 m_unk0x94;             // 0x94
	LegoFloat m_unk0x98;              // 0x98
	undefined m_unk0x9c[0xb4 - 0x9c]; // 0x9c
	undefined4 m_unk0xb4;             // 0xb4
	undefined4 m_unk0xb8;             // 0xb8
	undefined4 m_unk0xbc;             // 0xbc
	undefined4 m_unk0xc0;             // 0xc0
	undefined4 m_unk0xc4;             // 0xc4
	undefined4 m_unk0xc8;             // 0xc8
	undefined4 m_unk0xcc;             // 0xcc
	undefined4 m_unk0xd0;             // 0xd0
	undefined4 m_unk0xd4;             // 0xd4
	undefined4 m_unk0xd8;             // 0xd8
};

// VTABLE: LEGORACERS 0x004b1e40
// SIZE 0x4d8
class ObscureRune : public ObscureSigil {
public:
	ObscureRune();
	~ObscureRune() override; // vtable+0x04

	// SYNTHETIC: LEGORACERS 0x00466100
	// ObscureRune::`scalar deleting destructor'

protected:
	ObscureTome m_unk0xdc;               // 0x0dc
	undefined m_unk0x4b8[0x4d8 - 0x4b8]; // 0x4b8
};

#endif // OBSCURECLASSES_H
