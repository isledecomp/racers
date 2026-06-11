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

	~MenuTextEntry() override;                                                        // vtable+0x04
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	LegoBool32 VTable0x70(CreateParams*, const MenuIcon::CreateState*) override;      // vtable+0x70

	undefined2* GetUnk0x300() { return m_unk0x300; }
	DriverCosmetics* GetUnk0x328() { return &m_unk0x328; }

	// SYNTHETIC: LEGORACERS 0x004718b0
	// MenuTextEntry::`scalar deleting destructor'

protected:
	void FUN_00471930(CreateParams* p_createParams);
	void FUN_00471a30();
	LegoBool32 FUN_00471aa0(CreateParams* p_createParams);

	MenuColorBox m_unk0x23c;             // 0x23c
	undefined m_unk0x2fc[0x300 - 0x2fc]; // 0x2fc
	undefined2 m_unk0x300[15];           // 0x300
	undefined m_unk0x31e[0x328 - 0x31e]; // 0x31e
	DriverCosmetics m_unk0x328;          // 0x328
	undefined m_unk0x32d[0x330 - 0x32d]; // 0x32d
};

#endif // MENUTEXTENTRY_H
