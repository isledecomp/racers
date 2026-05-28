#ifndef MAINMENUSCREENFIELDAT0X22DC_H
#define MAINMENUSCREENFIELDAT0X22DC_H

#include "cmbmodelpart0x34.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/obscurelink0x1c.h"
#include "racer/turquoiseglowcolor.h"
#include "util/opalhaven0xf4.h"

class GolD3DRenderDevice;
class GolExport;
class GolModelBase;
class ObscureSigil0xdc;
class TanzaniteWisp0x88;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b33c8
// SIZE 0x15c
class MainMenuScreenFieldAt0x22dc : public ObscureLink0x1c {
public:
	// SIZE 0x1c
	struct CreateParams : public ObscureLink0x1c::CreateParams0x0c {
		TanzaniteWisp0x88* m_unk0x0c; // 0x0c
		GolVec3 m_position;           // 0x10
	};

	MainMenuScreenFieldAt0x22dc();
	void Reset() override;                      // vtable+0x00
	~MainMenuScreenFieldAt0x22dc() override;    // vtable+0x04
	LegoBool32 VTable0x08() override;           // vtable+0x08
	LegoBool32 VTable0x0c() override;           // vtable+0x0c
	LegoBool32 VTable0x10(undefined4) override; // vtable+0x10

	OpalHaven0xf4* GetUnk0x1c() { return &m_unk0x1c; }
	CmbModelPart0x34* GetUnk0x118() { return &m_unk0x118; }
	LegoBool32 FUN_0047e0a0(CreateParams* p_createParams);
	void FUN_0047e130(LegoU8 p_unk0x04);
	void FUN_0047e160(LegoU8 p_unk0x04, LegoU8 p_unk0x08);
	void FUN_0047e1b0(LegoU8 p_unk0x04);
	void FUN_0047e1e0(LegoU8 p_unk0x04);
	void FUN_0047e210(TurquoiseGlowColor* p_color);

	// SYNTHETIC: LEGORACERS 0x0047dee0
	// MainMenuScreenFieldAt0x22dc::`scalar deleting destructor'

private:
	void FUN_0047df90();

	OpalHaven0xf4 m_unk0x1c;             // 0x01c
	GolModelBase* m_unk0x110;            // 0x110
	GolSceneNode* m_unk0x114;            // 0x114
	CmbModelPart0x34 m_unk0x118;         // 0x118
	undefined4 m_unk0x14c;               // 0x14c
	TanzaniteWisp0x88* m_unk0x150;       // 0x150
	TurquoiseGlowColor m_unk0x154;       // 0x154
	undefined m_unk0x159[0x15c - 0x159]; // 0x159
};

#endif // MAINMENUSCREENFIELDAT0X22DC_H
