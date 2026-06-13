#ifndef MENUSTYLETABLE_H
#define MENUSTYLETABLE_H

#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "menu/style/menuresourcetable.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/visualstatecolor.h"
#include "render/rectangle.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFont;
class SharedMenuStyleTable;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class MenuStyleTable : public MenuResourceTable {
public:
	// SIZE 0x0c
	class ImageStyle {
	public:
		UtopianPan0xa4* m_unk0x00;  // 0x00
		VisualStateColor m_unk0x04; // 0x04
		LegoBool32 m_unk0x08;       // 0x08
	};

	// SIZE 0x14
	class TextStyle {
	public:
		GolFont* m_unk0x00;         // 0x00
		VisualStateColor m_unk0x04; // 0x04
		LegoS32 m_unk0x08;          // 0x08
		LegoBool32 m_unk0x0c;       // 0x0c
		LegoS32 m_unk0x10;          // 0x10
	};

	// SIZE 0x18
	class CarouselStyle {
	public:
		undefined4 m_unk0x00[3]; // 0x00
		LegoS32 m_unk0x0c;       // 0x0c
		LegoS32 m_unk0x10;       // 0x10
		LegoS32 m_unk0x14;       // 0x14
	};

	// SIZE 0x2c
	class FrameStyle {
	public:
		UtopianPan0xa4* m_unk0x00[8]; // 0x00
		VisualStateColor m_unk0x20;   // 0x20
		VisualStateColor m_unk0x24;   // 0x24
		LegoBool32 m_unk0x28;         // 0x28
	};

	// SIZE 0x90
	class IconStyle : public MenuIcon::CreateState {};

	// SIZE 0x98
	class SelectorStyleBase : public IconStyle {
	public:
		IconStyle* m_unk0x90; // 0x90
		IconStyle* m_unk0x94; // 0x94
	};

	// SIZE 0xa8
	class ButtonStyle : public IconStyle {
	public:
		UtopianPan0xa4* m_unk0x90[6]; // 0x90
	};

	// SIZE 0x104
	class TextButtonStyle : public IconStyle {
	public:
		GolFont* m_unk0x90[6];         // 0x90
		UtopianPan0xa4* m_unk0xa8[6];  // 0xa8
		VisualStateColor m_unk0xc0[6]; // 0xc0
		VisualStateColor m_unk0xd8;    // 0xd8
		Rect m_unk0xdc;                // 0xdc
		Rect m_unk0xec;                // 0xec
		undefined4 m_unk0xfc;          // 0xfc
		undefined4 m_unk0x100;         // 0x100
	};

	// SIZE 0x100
	class MultiStateStyle : public IconStyle {
	public:
		// SIZE 0x0c
		class ImageTriplet {
		public:
			UtopianPan0xa4* m_unk0x00; // 0x00
			UtopianPan0xa4* m_unk0x04; // 0x04
			UtopianPan0xa4* m_unk0x08; // 0x08
		};

		GolFont* m_unk0x90[6]; // 0x90
		union {
			ImageTriplet m_unk0xa8[6];            // 0xa8
			UtopianPan0xa4* m_utopianunk0xa8[18]; // 0xa8
		};
		Rect m_unk0xf0; // 0xf0
	};

	// SIZE 0x150
	class HotspotStyle : public IconStyle {
	public:
		undefined m_unk0x90[0xa8 - 0x90]; // 0x90
		UtopianPan0xa4* m_unk0xa8;        // 0xa8
		LegoS32 m_unk0xac;                // 0xac
		undefined4 m_unk0xb0[8];          // 0xb0
		Rect m_unk0xd0[8];                // 0xd0
	};

	// SIZE 0xbc
	class SelectorStyle : public SelectorStyleBase {
	public:
		FrameStyle* m_unk0x98;         // 0x98
		VisualStateColor m_unk0x9c[4]; // 0x9c
		VisualStateColor m_unk0xac[4]; // 0xac

		ButtonStyle* GetUnk0x90() const { return static_cast<ButtonStyle*>(m_unk0x90); }
		ButtonStyle* GetUnk0x94() const { return static_cast<ButtonStyle*>(m_unk0x94); }
	};

	// SIZE 0xbc
	class CompositeStyle : public SelectorStyleBase {
	public:
		ImageStyle* m_unk0x98;           // 0x98
		ImageStyle* m_unk0x9c;           // 0x9c
		UtopianPan0xa4* m_unk0xa0[6];    // 0xa0
		MenuIcon::SoundIdPair m_unk0xb8; // 0xb8

		ButtonStyle* GetUnk0x90() const { return static_cast<ButtonStyle*>(m_unk0x90); }
		ButtonStyle* GetUnk0x94() const { return static_cast<ButtonStyle*>(m_unk0x94); }
	};

	// SIZE 0x10
	struct ResourceLoadParams {
		GolD3DRenderDevice* m_renderer;  // 0x00
		SharedMenuStyleTable* m_unk0x04; // 0x04
		const LegoChar* m_fileName;      // 0x08
		undefined4 m_binary;             // 0x0c
	};

	MenuStyleTable();
	~MenuStyleTable() override;           // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);
	void* FUN_00470e60(const LegoChar* p_name);
	ImageStyle* GetImageStyle(const LegoChar* p_name) { return static_cast<ImageStyle*>(FUN_00470e60(p_name)); }
	TextStyle* GetTextStyle(const LegoChar* p_name) { return static_cast<TextStyle*>(FUN_00470e60(p_name)); }
	IconStyle* GetIconStyle(const LegoChar* p_name) { return static_cast<IconStyle*>(FUN_00470e60(p_name)); }
	TextButtonStyle* GetTextButtonStyle(const LegoChar* p_name)
	{
		return static_cast<TextButtonStyle*>(FUN_00470e60(p_name));
	}

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// MenuStyleTable::`scalar deleting destructor'

protected:
	void FUN_0046fd30(ResourceLoadParams* p_params);
	void FUN_0046fe20(ImageStyle* p_entry);
	void FUN_0046feb0(TextStyle* p_entry);
	void FUN_0046ff70(FrameStyle* p_entry);
	void FUN_00470020(IconStyle* p_entry);
	void FUN_00470110(ButtonStyle* p_entry);
	void FUN_004701a0(MultiStateStyle* p_entry);
	void FUN_004702e0(HotspotStyle* p_entry);
	void FUN_00470410(CarouselStyle* p_entry);
	void FUN_004704b0(SelectorStyle* p_entry);
	void FUN_00470650(CompositeStyle* p_entry);

private:
	void FUN_004707e0();
	void FUN_00470880();
	void FUN_00470920();
	void FUN_004709c0();
	void FUN_00470a70();
	void FUN_00470b10();
	void FUN_00470bc0();
	void FUN_00470c60();
	void FUN_00470d10();
	void FUN_00470dc0();

protected:
	MenuStyleTable* m_unk0x20;  // 0x20
	ImageStyle* m_unk0x24;      // 0x24
	TextStyle* m_unk0x28;       // 0x28
	FrameStyle* m_unk0x2c;      // 0x2c
	ButtonStyle* m_unk0x30;     // 0x30
	MultiStateStyle* m_unk0x34; // 0x34
	HotspotStyle* m_unk0x38;    // 0x38
	CarouselStyle* m_unk0x3c;   // 0x3c
	SelectorStyle* m_unk0x40;   // 0x40
	CompositeStyle* m_unk0x44;  // 0x44
	IconStyle* m_unk0x48;       // 0x48
};

#endif // MENUSTYLETABLE_H
