#ifndef IMAGINARYNOTION0X290_H
#define IMAGINARYNOTION0X290_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginaryinterface.h"
#include "menu/style/ceruleanemperor0x4c.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscureicon0x1a8.h"
#include "text/coppercrest0x40.h"
#include "types.h"

class GolD3DRenderDevice;
class CrimsonSun0xa4;
class GolExport;
class GolFontTable;
class GolString;
class GolStringTable;
class InputManager;
class IvoryTalon0x23c;
class MainMenuScreenFieldAt0x420;
class MenuToolCreateParams0x30;
class ObscureCarousel0x78;
class ObscureGlyph0x21c;
class ObscureLattice0x228;
class ObscureRune0x4d8;
class ObscureTome0x3fc;
class ObscureVantage0x58;
class ObscureSigil0xdc;
class ObscureZebra0xa4;
class OptionsScreenFieldAt0x4178Base0x6e4;
class PorcelainVeil0x50;
class SoundGroupBinding;
class AwakeKite0x20;

// VTABLE: LEGORACERS 0x004b2308
// SIZE 0x290
class ImaginaryNotion0x290 : public ImaginaryInterface {
public:
	// SIZE 0x54
	class FieldAt0x54 : public ObscureVantage0x58::CreateParams0x38 {
	public:
		LegoChar m_unk0x38[0x48 - 0x38]; // 0x38
		undefined4 m_unk0x48;            // 0x48
		LegoU32 m_unk0x4c;               // 0x4c
		LegoFloat m_unk0x50;             // 0x50
	};

	ImaginaryNotion0x290();

	void VTable0x00(ObscureVantage0x58*) override;                                      // vtable+0x00
	void VTable0x04(ObscureVantage0x58*) override;                                      // vtable+0x04
	void VTable0x08(ObscureVantage0x58*) override;                                      // vtable+0x08
	void VTable0x0c(ObscureVantage0x58*) override;                                      // vtable+0x0c
	void VTable0x10(ObscureVantage0x58*) override;                                      // vtable+0x10
	undefined4 VTable0x14(ObscureVantage0x58*, void*, undefined4, undefined4) override; // vtable+0x14
	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;                                         // vtable+0x1c
	void VTable0x20(ObscureVantage0x58*) override;                                      // vtable+0x20
	void VTable0x24(ObscureVantage0x58*) override;                                      // vtable+0x24
	undefined4 VTable0x28(ObscureVantage0x58*, void*, undefined4, undefined4) override; // vtable+0x28
	void VTable0x2c(ObscureIcon0x1a8*) override;                                        // vtable+0x2c
	void VTable0x30(ObscureIcon0x1a8*) override;                                        // vtable+0x30
	void VTable0x34(ObscureIcon0x1a8*) override;                                        // vtable+0x34
	void VTable0x38(ObscureVantage0x58*) override;                                      // vtable+0x38
	void VTable0x3c(ObscureIcon0x1a8*) override;                                        // vtable+0x3c
	void VTable0x40(ObscureIcon0x1a8*) override;                                        // vtable+0x40
	void VTable0x44(ObscureVantage0x58*) override;                                      // vtable+0x44
	void VTable0x48(ObscureVantage0x58*) override;                                      // vtable+0x48
	virtual void VTable0x4c() = 0;                                                      // vtable+0x4c
	virtual undefined4 VTable0x50();                                                    // vtable+0x50
	virtual void Reset();                                                               // vtable+0x54
	virtual LegoBool32 VTable0x58(MenuToolCreateParams0x30*);                           // vtable+0x58
	virtual CeruleanEmperor0x4c* GetMenuStyles();                                       // vtable+0x5c
	virtual CeruleanEmperor0x4c* VTable0x60();                                          // vtable+0x60
	virtual MenuInputBindingTable* GetMenuInputBindings();                              // vtable+0x64
	virtual ~ImaginaryNotion0x290();                                                    // vtable+0x68
	virtual LegoFloat VTable0x6c();                                                     // vtable+0x6c
	virtual LegoBool32 Initialize(MenuToolCreateParams0x30*);                           // vtable+0x70
	virtual LegoBool32 Destroy();                                                       // vtable+0x74
	virtual LegoBool32 VTable0x78(undefined4);                                          // vtable+0x78
	virtual LegoBool32 VTable0x7c(Rect* p_arg1, Rect* p_arg2);                          // vtable+0x7c

	LegoBool32 FUN_0046b630();
	LegoBool32 FUN_0046b6e0(MenuToolCreateParams0x30*);
	void FUN_0046ba60(ObscureVantage0x58::CreateParams0x38*);
	void FUN_0046bb10(ObscureIcon0x1a8::CreateParams0x84*);
	void FUN_0046bb90(
		ObscureBanner0x5ec::CreateParams0x90* p_createParams,
		CeruleanEmperor0x4c::Entry0xbc* p_styleEntry
	);
	void FUN_0046bc90(
		MenuInputBindingTable::Entry0xb8* p_createParams,
		CeruleanEmperor0x4c::Entry0xbcWithImages* p_styleEntry
	);
	void* FUN_0046bd80(undefined2);
	void* FUN_0046be10(undefined2);
	void FUN_0046bea0(ObscureZebra0xa4*, undefined2);
	LegoBool32 FUN_0046bef0(ObscureAnchor0x5c*, undefined2, undefined2);
	LegoBool32 FUN_0046bf80(MainMenuScreenFieldAt0x420*, undefined2, undefined2, undefined2);
	LegoBool32 FUN_0046c050(ObscureTome0x3fc*, undefined2, undefined2);
	LegoBool32 FUN_0046c110(ObscureGlyph0x21c* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c);
	LegoBool32 FUN_0046c1b0(ObscureLattice0x228*, undefined2, undefined2);
	LegoBool32 FUN_0046c240(ObscureCarousel0x78*, undefined2, undefined2);
	LegoBool32 FUN_0046c2b0(
		ObscureBanner0x9f4* p_widget,
		ObscureCarousel0x94* p_carousel,
		undefined2 p_cpId,
		undefined2 p_styleId
	);
	LegoBool32 FUN_0046c400(OptionsScreenFieldAt0x4178Base0x6e4*, undefined2, undefined2);
	LegoBool32 FUN_0046c480(ObscureSigil0xdc* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c);
	LegoBool32 FUN_0046c510(ObscureRune0x4d8* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c);
	undefined4 FUN_0046c5b0(ObscureVantage0x58*, undefined2);
	LegoBool32 FUN_0046c610(IvoryTalon0x23c*, undefined2, undefined2, undefined2, GolString*);
	undefined4 FUN_0046c6f0(ObscureIcon0x1a8*, ObscureIcon0x1a8*, undefined2);
	undefined4 FUN_0046c730(ObscureIcon0x1a8*, undefined2);
	void FUN_0046c760();
	ObscureIcon0x1a8* GetUnk0xd8() { return &m_unk0xd8; }

	CeruleanEmperor0x4c::Entry0x0c* GetStyleEntry0x0c(undefined2 p_id)
	{
		return static_cast<CeruleanEmperor0x4c::Entry0x0c*>(FUN_0046bd80(p_id));
	}

	CeruleanEmperor0x4c::Entry0x104* GetStyleEntry0x104(undefined2 p_id)
	{
		return static_cast<CeruleanEmperor0x4c::Entry0x104*>(FUN_0046bd80(p_id));
	}

	CeruleanEmperor0x4c::Entry0x150* GetStyleEntry0x150(undefined2 p_id)
	{
		return static_cast<CeruleanEmperor0x4c::Entry0x150*>(FUN_0046bd80(p_id));
	}

	MenuInputBindingTable::Entry0x3c* GetInputBindingEntry0x3c(undefined2 p_id)
	{
		return static_cast<MenuInputBindingTable::Entry0x3c*>(FUN_0046be10(p_id));
	}

	MenuInputBindingTable::Entry0x84* GetInputBindingEntry0x84(undefined2 p_id)
	{
		return static_cast<MenuInputBindingTable::Entry0x84*>(FUN_0046be10(p_id));
	}

	FieldAt0x54* GetInputBindingEntry0x54(undefined2 p_id) { return static_cast<FieldAt0x54*>(FUN_0046be10(p_id)); }

	// SYNTHETIC: LEGORACERS 0x0046b3f0
	// ImaginaryNotion0x290::`scalar deleting destructor'

protected:
	LegoBool32 m_initialized;                    // 0x004
	CeruleanEmperor0x4c m_unk0x08;               // 0x008
	PorcelainVeil0x50* m_menuStyles;             // 0x054
	MenuInputBindingTable m_unk0x58;             // 0x058
	GolExport* m_golExport;                      // 0x0b4
	GolD3DRenderDevice* m_renderer;              // 0x0b8
	AwakeKite0x20* m_unk0xbc;                    // 0x0bc
	GolFontTable* m_fontTable;                   // 0x0c0
	CopperCrest0x40::Helper0x44* m_cursorHelper; // 0x0c4
	InputEventQueue* m_inputEvents;              // 0x0c8
	InputManager* m_inputManager;                // 0x0cc
	GolStringTable* m_menuNameStrings;           // 0x0d0
	GolStringTable* m_menuTextStrings;           // 0x0d4
	ObscureIcon0x1a8 m_unk0xd8;                  // 0x0d8
	SoundGroupBinding* m_soundGroupBinding;      // 0x280
	CrimsonSun0xa4* m_unk0x284;                  // 0x284
	undefined4 m_unk0x288;                       // 0x288
	undefined2 m_unk0x28c;                       // 0x28c
};

#endif // IMAGINARYNOTION0X290_H
