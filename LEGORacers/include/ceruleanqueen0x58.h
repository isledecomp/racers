#ifndef CERULEANQUEEN0X58_H
#define CERULEANQUEEN0X58_H

#include "ceruleanknight0x20.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b2180
// SIZE 0x58
class CeruleanQueen0x58 : public CeruleanKnight0x20 {
public:
	CeruleanQueen0x58();
	~CeruleanQueen0x58() override;        // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x00469600
	// CeruleanQueen0x58::`scalar deleting destructor'

private:
	void FUN_0046a750();
	void FUN_0046a800();
	void FUN_0046a8a0();
	void FUN_0046a940();
	void FUN_0046a9e0();
	void FUN_0046aa90();
	void FUN_0046ab40();
	void FUN_0046abe0();
	void FUN_0046ac90();
	void FUN_0046ad40();
	void FUN_0046adf0();
	void FUN_0046af50();
	void FUN_0046aea0();

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

#endif // CERULEANQUEEN0X58_H
