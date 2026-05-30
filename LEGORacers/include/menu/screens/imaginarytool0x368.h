#ifndef IMAGINARYTOOL0X368_H
#define IMAGINARYTOOL0X368_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarynotion0x290.h"
#include "menu/style/porcelainveil0x50.h"
#include "render/golrenderdevice.h"

class MenuToolContext0x4bc8;
class MenuToolCreateParams0x30;
class MainMenuScreenFieldAt0x498;
class ObscureVantage0x58;
class GolFont0xa0;
class UtopianPan0xa4;
class SiennaCircuit0x154;

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class ImaginaryTool0x368 : public ImaginaryNotion0x290 {
public:
	// VTABLE: LEGORACERS 0x004b3480
	// SIZE 0x60
	class FieldAt0x2e0 : public MenuInputBindingTable {
	public:
		// VTABLE: LEGORACERS 0x004b3498
		// SIZE 0x1fc
		class MidTxtParser : public GolTxtParser {};

		FieldAt0x2e0();
		~FieldAt0x2e0() override;             // vtable+0x00
		void Clear() override;                // vtable+0x08
		void VTable0x0c() override;           // vtable+0x0c
		void VTable0x10(undefined4) override; // vtable+0x10
		void VTable0x14(undefined4) override; // vtable+0x14

		// SIZE 0xe0
		class Entry0xe0 : public MenuInputBindingTable::Entry0x84 {
		public:
			GolFont0xa0* m_unk0x84[6];        // 0x84
			UtopianPan0xa4* m_unk0x9c[6];     // 0x9c
			VisualState0x4 m_unk0xb4[6];      // 0xb4
			undefined m_unk0xcc[0xd0 - 0xcc]; // 0xcc
			VisualState0x4 m_unk0xd0;         // 0xd0
			undefined m_unk0xd4[0xd8 - 0xd4]; // 0xd4
			undefined4 m_unk0xd8;             // 0xd8
			undefined4 m_unk0xdc;             // 0xdc
		};

		// SYNTHETIC: LEGORACERS 0x0047f0f0
		// ImaginaryTool0x368::FieldAt0x2e0::`scalar deleting destructor'

	private:
		void FUN_0047f2b0(Entry0xe0* p_entry);
		void FUN_0047f410();

		Entry0xe0* m_unk0x5c; // 0x5c
	};

	ImaginaryTool0x368();

	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;             // vtable+0x1c
	void VTable0x34(ObscureIcon0x1a8*) override;            // vtable+0x34
	void VTable0x3c(ObscureIcon0x1a8*) override;            // vtable+0x3c
	void VTable0x40(ObscureIcon0x1a8*) override;            // vtable+0x40
	void Reset() override;                                  // vtable+0x54
	CeruleanEmperor0x4c* GetMenuStyles() override;          // vtable+0x5c
	MenuInputBindingTable* GetMenuInputBindings() override; // vtable+0x64
	~ImaginaryTool0x368() override;                         // vtable+0x68
	LegoFloat VTable0x6c() override;                        // vtable+0x6c
	LegoBool32 Destroy() override;                          // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;             // vtable+0x78
	virtual void VTable0x80();                              // vtable+0x80
	virtual void VTable0x84() = 0;                          // vtable+0x84
	virtual LegoBool32 VTable0x88();                        // vtable+0x88
	virtual LegoBool32 VTable0x8c(MenuToolContext0x4bc8*,
								  MenuToolCreateParams0x30*); // vtable+0x8c
	virtual void VTable0x90(undefined4);                      // vtable+0x90
	virtual void VTable0x94(undefined4);                      // vtable+0x94

	void FUN_00480470(MenuToolContext0x4bc8* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c);

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// ImaginaryTool0x368::`scalar deleting destructor'

protected:
	FieldAt0x2e0::Entry0xe0* GetToolInputBindingEntry0xe0(undefined2 p_id)
	{
		return static_cast<FieldAt0x2e0::Entry0xe0*>(FUN_0046be10(p_id));
	}

	undefined4 FUN_0047fcf0(SiennaCircuit0x154* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c);
	undefined4 FUN_0047fdc0(
		MainMenuScreenFieldAt0x498* p_unk0x04,
		undefined2 p_unk0x08,
		undefined2 p_unk0x0c,
		undefined2 p_unk0x10
	);
	void FUN_0047fec0(GolRenderDevice::MaterialColor* p_unk0x04, GolRenderDevice::Light* p_unk0x08);
	void FUN_004803d0();
	LegoBool32 FUN_00480440(MenuToolContext0x4bc8* p_context);
	void FUN_004804c0(MenuToolContext0x4bc8* p_context);

	PorcelainVeil0x50 m_unk0x290;              // 0x290
	FieldAt0x2e0 m_unk0x2e0;                   // 0x2e0
	GolRenderDevice::Light m_unk0x340;         // 0x340
	GolRenderDevice::MaterialColor m_unk0x350; // 0x350
	MenuToolContext0x4bc8* m_context;          // 0x354
	ObscureIcon0x1a8* m_unk0x358;              // 0x358
	ObscureVantage0x58* m_unk0x35c;            // 0x35c
	LegoU16 m_unk0x360;                        // 0x360
	LegoU16 m_menuId;                          // 0x362
	LegoBool32 m_unk0x364;                     // 0x364
};

#endif // IMAGINARYTOOL0X368_H
