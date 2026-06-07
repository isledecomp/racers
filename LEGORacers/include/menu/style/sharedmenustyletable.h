#ifndef SHAREDMENUSTYLETABLE_H
#define SHAREDMENUSTYLETABLE_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"

// VTABLE: LEGORACERS 0x004b35b0
// SIZE 0x50
class SharedMenuStyleTable : public MenuStyleTable {
public:
	// VTABLE: LEGORACERS 0x004b35c8
	// SIZE 0x1fc
	class MidTxtParser : public GolTxtParser {};

	SharedMenuStyleTable();
	~SharedMenuStyleTable() override;     // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x004805a0
	// SharedMenuStyleTable::`scalar deleting destructor'

private:
	void FUN_00480760(TextButtonStyle* p_entry);
	void FUN_004808f0();

	TextButtonStyle* m_unk0x4c; // 0x4c
};

#endif // SHAREDMENUSTYLETABLE_H
