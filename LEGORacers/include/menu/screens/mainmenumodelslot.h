#ifndef MAINMENUMODELSLOT_H
#define MAINMENUMODELSLOT_H

#include "cmbmodelpart.h"
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
		DriverModelBuilder* m_modelBuilder; // 0x0c
		GolVec3 m_position;                 // 0x10
	};

	MainMenuModelSlot();
	void Reset() override;                  // vtable+0x00
	~MainMenuModelSlot() override;          // vtable+0x04
	LegoBool32 Destroy() override;          // vtable+0x08
	LegoBool32 Draw() override;             // vtable+0x0c
	LegoBool32 Update(undefined4) override; // vtable+0x10

	GolAnimatedEntity* GetDriverEntity() { return &m_driverEntity; }
	CmbModelPart* GetBodyModelPart() { return &m_bodyModelPart; }
	LegoBool32 Create(CreateParams* p_createParams);
	void SetHat(LegoU32 p_hatIndex);
	void SetFace(LegoU32 p_faceIndex, LegoU32 p_expressionIndex);
	void SetTorso(LegoU32 p_torsoIndex);
	void SetLegs(LegoU32 p_legIndex);
	void SetCosmetics(DriverCosmetics* p_cosmetics);

	// SYNTHETIC: LEGORACERS 0x0047dee0
	// MainMenuModelSlot::`scalar deleting destructor'

private:
	void CreateDriverModel();

	GolAnimatedEntity m_driverEntity;    // 0x01c
	GolModelBase* m_driverModel;         // 0x110
	GolSceneNode* m_bodySceneNode;       // 0x114
	CmbModelPart m_bodyModelPart;        // 0x118
	undefined4 m_unk0x14c;               // 0x14c
	DriverModelBuilder* m_modelBuilder;  // 0x150
	DriverCosmetics m_cosmetics;         // 0x154
	undefined m_unk0x159[0x15c - 0x159]; // 0x159
};

#endif // MAINMENUMODELSLOT_H
