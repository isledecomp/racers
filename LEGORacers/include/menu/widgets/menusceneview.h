#ifndef OBSCURESIGIL0XDC
#define OBSCURESIGIL0XDC

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/menusceneelement.h"
#include "menu/widgets/menuwidget.h"
#include "types.h"

class GolCamera;
class GolWorldEntity;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b1dfc
// SIZE: 0xdc
class MenuSceneView : public MenuWidget {
public:
	// SIZE 0x84
	class CreateParams : public MenuWidget::CreateParams {
	public:
		GolVec3 m_unk0x38;               // 0x38
		GolVec3 m_unk0x44;               // 0x44
		GolVec3 m_unk0x50;               // 0x50
		LegoFloat m_unk0x5c;             // 0x5c
		LegoChar m_unk0x60[0x70 - 0x60]; // 0x60
		undefined4 m_unk0x70;            // 0x70
		LegoBool32 m_unk0x74;            // 0x74
		undefined4 m_unk0x78;            // 0x78
		undefined4 m_unk0x7c;            // 0x7c
		LegoFloat m_unk0x80;             // 0x80
	};

	MenuSceneView();

	void Reset() override;                                                            // vtable+0x00
	~MenuSceneView() override;                                                        // vtable+0x04
	LegoBool32 VTable0x08() override;                                                 // vtable+0x08
	MenuWidget* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	MenuWidget* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                                       // vtable+0x3c
	LegoBool32 FUN_00465820(CreateParams* p_createParams, undefined4 p_unk0x08);
	MenuSceneElement* FUN_00465b40(MenuSceneElement* p_unk0x04);
	void FUN_00465ab0(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
	void FUN_00465b60(GolWorldEntity* p_entity, Rect* p_rect);
	GolWorldDatabase* GetUnk0x5c() const { return m_unk0x5c; }
	GolWorldDatabase** GetUnk0x5cAddress() { return &m_unk0x5c; }
	GolWorldDatabase* GetUnk0x60() const { return m_unk0x60; }
	GolCamera* GetUnk0x64() const { return m_unk0x64; }
	void SetUnk0x6c(undefined4 p_unk0x6c) { m_unk0x6c = p_unk0x6c; }

	// SYNTHETIC: LEGORACERS 0x00465730
	// MenuSceneView::`scalar deleting destructor'

protected:
	void FUN_00465900(CreateParams* p_createParams, undefined4 p_unk0x08);
	void FUN_004659b0(CreateParams* p_createParams);
	void FUN_00465c00(undefined4 p_elapsedMs);
	void FUN_00465e40(Rect* p_rect);
	void FUN_00465ea0();

	MenuSceneElement* m_unk0x58; // 0x58
	GolWorldDatabase* m_unk0x5c; // 0x5c
	GolWorldDatabase* m_unk0x60; // 0x60
	GolCamera* m_unk0x64;        // 0x64
	GolCamera* m_unk0x68;        // 0x68
	undefined4 m_unk0x6c;        // 0x6c
	GolVec3 m_unk0x70;           // 0x70
	GolVec3 m_unk0x7c;           // 0x7c
	undefined4 m_unk0x88;        // 0x88
	LegoFloat m_unk0x8c;         // 0x8c
	GolVec3 m_unk0x90;           // 0x90
	GolVec3 m_unk0x9c;           // 0x9c
	GolVec3 m_unk0xa8;           // 0xa8
	LegoFloat m_unk0xb4;         // 0xb4
	LegoFloat m_unk0xb8;         // 0xb8
	LegoFloat m_unk0xbc;         // 0xbc
	LegoFloat m_unk0xc0;         // 0xc0
	LegoFloat m_unk0xc4;         // 0xc4
	LegoFloat m_unk0xc8;         // 0xc8
	LegoFloat m_unk0xcc;         // 0xcc
	LegoFloat m_unk0xd0;         // 0xd0
	LegoFloat m_unk0xd4;         // 0xd4
	LegoFloat m_unk0xd8;         // 0xd8
};

#endif // OBSCURESIGIL0XDC
