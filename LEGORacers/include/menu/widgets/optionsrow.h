#ifndef OPTIONSROW_H
#define OPTIONSROW_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/optionsrowbase.h"

// VTABLE: LEGORACERS 0x004b25a8
// SIZE 0x6ec
class OptionsRow : public OptionsRowBase {
public:
	OptionsRow();
	~OptionsRow() override;                                                        // vtable+0x04
	MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;             // vtable+0x2c
	undefined4 MapCursorToNavigation(undefined4, undefined4, undefined4) override; // vtable+0x70
	void LayoutButtons() override;                                                 // vtable+0x80
	void LayoutTrack() override;                                                   // vtable+0x84
	void LayoutThumb() override;                                                   // vtable+0x88
	void SnapThumbToValue() override;                                              // vtable+0x8c
	void SetValue(LegoS32) override;                                               // vtable+0x90

	// SYNTHETIC: LEGORACERS 0x0046e440
	// OptionsRow::`scalar deleting destructor'

private:
	friend class OptionsRowBase;
	void ComputeThumbRange();

	undefined m_unk0x6e4[0x6ec - 0x6e4]; // 0x6e4
};

#endif // OPTIONSROW_H
