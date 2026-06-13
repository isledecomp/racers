#ifndef MENUTEXTLABEL_H
#define MENUTEXTLABEL_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menustaticwidget.h"

class GolFont;
class GolStringTable;

// VTABLE: LEGORACERS 0x004b273c
// SIZE 0x78
class MenuTextLabel : public MenuStaticWidget {
public:
	// SIZE 0x48
	class CreateParams : public MenuWidget::CreateParams {
	public:
		GolStringTable* m_unk0x38; // 0x38
		GolFont* m_unk0x3c;        // 0x3c
		undefined2 m_unk0x40;      // 0x40
		undefined m_unk0x42[2];    // 0x42
		undefined4 m_unk0x44;      // 0x44
	};

	MenuTextLabel();
	void Reset() override;                           // vtable+0x00
	~MenuTextLabel() override;                       // vtable+0x04
	MenuWidget* VTable0x38(Rect*, Rect*) override;   // vtable+0x38
	virtual void VTable0x40(GolString*, LegoS32);    // vtable+0x40
	virtual void VTable0x44(undefined2, undefined4); // vtable+0x44
	LegoBool32 FUN_0046f520(CreateParams* p_createParams, MenuStyleTable::TextStyle* p_unk0x08);
	void FUN_0046f6b0(LegoS32 p_rightMargin);
	void SetUnk0x60(GolFont* p_unk0x60) { m_unk0x60 = p_unk0x60; }

	// SYNTHETIC: LEGORACERS 0x0046f470
	// MenuTextLabel::`scalar deleting destructor'

protected:
	MenuStyleTable::TextStyle* m_unk0x58; // 0x58
	GolStringTable* m_unk0x5c;            // 0x5c
	GolFont* m_unk0x60;                   // 0x60
	GolString m_unk0x64;                  // 0x64
	LegoS32 m_unk0x70;                    // 0x70
	LegoBool32 m_unk0x74;                 // 0x74
};

#endif // MENUTEXTLABEL_H
