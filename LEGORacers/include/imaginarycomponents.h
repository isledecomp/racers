#ifndef IMAGINARYCOMPONENTS_H
#define IMAGINARYCOMPONENTS_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af7c0
// SIZE 0x0c
class CeruleanSubject {
public:
	CeruleanSubject();
	virtual ~CeruleanSubject();
	virtual void VTable0x04(undefined4); // vtable+0x04
	virtual void VTable0x08();           // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x004117d0
	// CeruleanSubject::`scalar deleting destructor'

protected:
	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
};

// VTABLE: LEGORACERS 0x004b2210
// SIZE 0x20
class CeruleanKnight : public CeruleanSubject {
public:
	CeruleanKnight();
	~CeruleanKnight() override;
	void VTable0x08() override;              // vtable+0x08
	virtual void VTable0x0c();               // vtable+0x0c
	virtual void VTable0x10(undefined4) = 0; // vtable+0x10
	virtual void VTable0x14(undefined4) = 0; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0046b070
	// CeruleanKnight::`scalar deleting destructor'

protected:
	undefined m_unk0x0c;  // 0x0c
	undefined4 m_unk0x10; // 0x10
	undefined4 m_unk0x14; // 0x10
	undefined4 m_unk0x18; // 0x10
	undefined4 m_unk0x1c; // 0x10
};

// VTABLE: LEGORACERS 0x004b2180
// SIZE 0x58
class CeruleanQueen : public CeruleanKnight {
public:
	CeruleanQueen();
	~CeruleanQueen() override;
	void VTable0x08() override;           // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x00469600
	// CeruleanQueen::`scalar deleting destructor'

protected:
	undefined4 m_unk0x20; // 0x20
	undefined4 m_unk0x24; // 0x24
	undefined4 m_unk0x28; // 0x28
	undefined4 m_unk0x2c; // 0x2c
	undefined4 m_unk0x30; // 0x30
	undefined4 m_unk0x34; // 0x34
	undefined4 m_unk0x38; // 0x38
	undefined4 m_unk0x3c; // 0x3c
	undefined4 m_unk0x40; // 0x40
	undefined4 m_unk0x44; // 0x44
	undefined4 m_unk0x48; // 0x48
	undefined4 m_unk0x4c; // 0x4c
	undefined4 m_unk0x50; // 0x50
	undefined2 m_unk0x54; // 0x54
};

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class CeruleanEmperor : public CeruleanKnight {
public:
	CeruleanEmperor();
	~CeruleanEmperor() override;
	void VTable0x08() override;           // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// CeruleanEmperor::`scalar deleting destructor'

protected:
	undefined4 m_unk0x20;   // 0x20
	undefined4 m_unk0x24;   // 0x24
	undefined4 m_unk0x28;   // 0x28
	undefined4 m_unk0x2c;   // 0x2c
	undefined4 m_unk0x30;   // 0x30
	undefined4 m_unk0x34;   // 0x34
	undefined4 m_unk0x38;   // 0x38
	undefined4 m_unk0x3c;   // 0x3c
	undefined4 m_unk0x40;   // 0x40
	undefined4 m_unk0x44;   // 0x44
	undefined4 m_unk0x48;   // 0x48
	undefined m_unk0x4c[4]; // 0x4c ?
};

#endif // IMAGINARYCOMPONENTS_H
