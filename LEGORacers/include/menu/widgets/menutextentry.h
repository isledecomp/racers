#ifndef MENUTEXTENTRY_H
#define MENUTEXTENTRY_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menucolorbox.h"
#include "menu/widgets/menutextfield.h"
#include "racer/drivercosmetics.h"

// VTABLE: LEGORACERS 0x004b28d0
// SIZE 0x330
class MenuTextEntry : public MenuTextField {
public:
	MenuTextEntry();

	~MenuTextEntry() override;                                                       // vtable+0x04
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	LegoBool32 CreateField(CreateParams*, const MenuIcon::CreateState*) override;    // vtable+0x70

	undefined2* GetEntryBuffer() { return m_entryBuffer; }
	DriverCosmetics* GetCosmetics() { return &m_cosmetics; }

	// SYNTHETIC: LEGORACERS 0x004718b0
	// MenuTextEntry::`scalar deleting destructor'

protected:
	void Create(CreateParams* p_createParams);
	void UpdateCaret();
	LegoBool32 CreateColorBox(CreateParams* p_createParams);

	MenuColorBox m_caret;                // 0x23c
	undefined m_unk0x2fc[0x300 - 0x2fc]; // 0x2fc
	undefined2 m_entryBuffer[15];        // 0x300
	undefined m_unk0x31e[0x328 - 0x31e]; // 0x31e
	DriverCosmetics m_cosmetics;         // 0x328
	undefined m_unk0x32d[0x330 - 0x32d]; // 0x32d
};

#endif // MENUTEXTENTRY_H
