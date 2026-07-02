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
	~SharedMenuStyleTable() override;                // vtable+0x00
	void Clear() override;                           // vtable+0x08
	void Reset() override;                           // vtable+0x0c
	void CreateParser(undefined4 p_binary) override; // vtable+0x10
	void ParseSection(undefined4 p_token) override;  // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x004805a0
	// SharedMenuStyleTable::`scalar deleting destructor'

private:
	void ParseTextButtonStyle(TextButtonStyle* p_entry);
	void LoadTextButtonStyles();

	TextButtonStyle* m_textButtonStyles; // 0x4c
};

#endif // SHAREDMENUSTYLETABLE_H
