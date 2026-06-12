#ifndef MAINMENUMODELSLOT_H
#define MAINMENUMODELSLOT_H

#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golmath.h"
#include "menu/widgets/menusceneelement.h"
#include "racer/drivercosmetics.h"

class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class MenuSceneView;
class DriverModelBuilder;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b33c8
// SIZE 0x15c
class MainMenuModelSlot : public MenuSceneElement {
public:
	// SIZE 0x1c
	struct CreateParams : public MenuSceneElement::CreateParams {
		DriverModelBuilder* m_unk0x0c; // 0x0c
		GolVec3 m_position;            // 0x10
	};

	MainMenuModelSlot();
	void Reset() override;                      // vtable+0x00
	~MainMenuModelSlot() override;              // vtable+0x04
	LegoBool32 VTable0x08() override;           // vtable+0x08
	LegoBool32 VTable0x0c() override;           // vtable+0x0c
	LegoBool32 VTable0x10(undefined4) override; // vtable+0x10

	GolAnimatedEntity* GetUnk0x1c() { return &m_unk0x1c; }
	CmbModelPart0x34* GetUnk0x118() { return &m_unk0x118; }
	LegoBool32 FUN_0047e0a0(CreateParams* p_createParams);
	void FUN_0047e130(LegoU32 p_unk0x04);
	void FUN_0047e160(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
	void FUN_0047e1b0(LegoU32 p_unk0x04);
	void FUN_0047e1e0(LegoU32 p_unk0x04);
	void FUN_0047e210(DriverCosmetics* p_cosmetics);

	// SYNTHETIC: LEGORACERS 0x0047dee0
	// MainMenuModelSlot::`scalar deleting destructor'

private:
	void FUN_0047df90();

	GolAnimatedEntity m_unk0x1c;         // 0x01c
	GolModelBase* m_unk0x110;            // 0x110
	GolSceneNode* m_unk0x114;            // 0x114
	CmbModelPart0x34 m_unk0x118;         // 0x118
	undefined4 m_unk0x14c;               // 0x14c
	DriverModelBuilder* m_unk0x150;      // 0x150
	DriverCosmetics m_cosmetics;         // 0x154
	undefined m_unk0x159[0x15c - 0x159]; // 0x159
};

#endif // MAINMENUMODELSLOT_H
