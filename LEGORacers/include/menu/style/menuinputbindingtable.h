#ifndef MENUINPUTBINDINGTABLE_H
#define MENUINPUTBINDINGTABLE_H

#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "menu/style/menuresourcetable.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/visualstatecolor.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFont;
class GolStringTable;
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b2180
// SIZE 0x5c
class MenuInputBindingTable : public MenuResourceTable {
public:
	// VTABLE: LEGORACERS 0x004b2198
	// SIZE 0x1fc
	class MidTxtParser : public GolTxtParser {
		// SYNTHETIC: LEGORACERS 0x0041e920 FOLDED
		// MenuInputBindingTable::MidTxtParser::`scalar deleting destructor'

		// SYNTHETIC: LEGORACERS 0x00498840 FOLDED
		// MenuInputBindingTable::MidTxtParser::~MidTxtParser
	};

	// SIZE 0x38
	class RegionBinding : public MenuWidget::CreateParams {
	public:
	};

	// SIZE 0x3c
	class ImageBinding : public MenuImage::CreateParams {};

	// SIZE 0x48
	class TextLabelBinding : public MenuWidget::CreateParams {
	public:
		GolStringTable* m_unk0x38; // 0x38
		GolFont* m_unk0x3c;        // 0x3c
		undefined2 m_unk0x40;      // 0x40
		undefined m_unk0x42[2];    // 0x42
		undefined4 m_unk0x44;      // 0x44
	};

	// SIZE 0x60
	class FrameBinding : public MenuFrame::CreateParams {};

	// SIZE 0x84
	class IconBinding : public MenuIcon::CreateParams {};

	// SIZE 0x88
	class SceneBinding : public MenuWidget::CreateParams {
	public:
		LegoFloat m_unk0x38[9];          // 0x38
		LegoFloat m_unk0x5c;             // 0x5c
		LegoChar m_unk0x60[0x70 - 0x60]; // 0x60
		undefined4 m_unk0x70;            // 0x70
		LegoBool32 m_unk0x74;            // 0x74
		undefined4 m_unk0x78;            // 0x78
		undefined4 m_unk0x7c;            // 0x7c
		LegoFloat m_unk0x80;             // 0x80
		void* m_unk0x84;                 // 0x84
	};

	// SIZE 0x98
	class SelectorBinding : public IconBinding {
	public:
		void* m_unk0x84;      // 0x84
		void* m_unk0x88;      // 0x88
		void* m_unk0x8c;      // 0x8c
		undefined4 m_unk0x90; // 0x90
		undefined4 m_unk0x94; // 0x94
	};

	// SIZE 0x9c
	class ButtonBinding : public IconBinding {
	public:
		UtopianPan0xa4* m_unk0x84[6]; // 0x84
	};

	// SIZE 0xa0
	class HotspotBinding : public ButtonBinding {
	public:
		UtopianPan0xa4* m_unk0x9c; // 0x9c
	};

	// SIZE 0xa0
	class TextFieldBinding : public IconBinding {
	public:
		undefined m_unk0x84[0x8c - 0x84]; // 0x84
		GolFont* m_unk0x8c;               // 0x8c
		undefined m_unk0x90[0x94 - 0x90]; // 0x90
		undefined2 m_unk0x94;             // 0x94
		undefined2 m_unk0x96[4];          // 0x96
		undefined m_unk0x9e[0xa0 - 0x9e]; // 0x9e
	};

	// SIZE 0xb8
	class CompositeBinding : public MenuSelectorBase::CreateParams {
	public:
		MenuImage::CreateParams* m_unk0x8c; // 0x8c
		MenuImage::CreateParams* m_unk0x90; // 0x90
		UtopianPan0xa4* m_unk0x94[6];       // 0x94
		MenuIcon::SoundIdPair m_unk0xac;    // 0xac
		LegoS32 m_unk0xb0;                  // 0xb0
		LegoS32 m_unk0xb4;                  // 0xb4
	};

	// SIZE 0xec
	class MultiStateBinding : public IconBinding {
	public:
		// SIZE 0x0c
		class ImageTriplet {
		public:
			UtopianPan0xa4* m_unk0x00; // 0x00
			UtopianPan0xa4* m_unk0x04; // 0x04
			UtopianPan0xa4* m_unk0x08; // 0x08
		};

		undefined4 m_unk0x84;  // 0x84
		GolFont* m_unk0x88[6]; // 0x88
		union {
			ImageTriplet m_unk0xa0[6];            // 0xa0
			UtopianPan0xa4* m_utopianunk0xa0[18]; // 0xa0
		};
		undefined4 m_unk0xe8; // 0xe8
	};

	// SIZE 0x54
	class SceneRefBinding : public MenuWidget::CreateParams {
	public:
		LegoChar m_unk0x38[0x48 - 0x38]; // 0x38
		undefined4 m_unk0x48;            // 0x48
		LegoU32 m_unk0x4c;               // 0x4c
		LegoFloat m_unk0x50;             // 0x50
	};

	// SIZE 0x74
	class ModelCarouselBinding : public MenuWidget::CreateParams {
	public:
		LegoS32 m_unk0x38;                // 0x38
		Rect* m_unk0x3c;                  // 0x3c
		LegoFloat m_unk0x40;              // 0x40
		undefined4 m_unk0x44;             // 0x44
		LegoFloat m_unk0x48[9];           // 0x48
		undefined m_unk0x6c[0x74 - 0x6c]; // 0x6c
	};

	// SIZE 0x0c
	struct ResourceLoadParams {
		GolD3DRenderDevice* m_renderer; // 0x00
		const LegoChar* m_fileName;     // 0x04
		undefined4 m_binary;            // 0x08
	};

	MenuInputBindingTable();
	~MenuInputBindingTable() override;    // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);
	ImageBinding* GetImageBinding(const LegoChar* p_name)
	{
		return static_cast<ImageBinding*>(ResolveEntryByName(p_name));
	}
	IconBinding* GetIconBinding(const LegoChar* p_name)
	{
		return static_cast<IconBinding*>(ResolveEntryByName(p_name));
	}

	// SYNTHETIC: LEGORACERS 0x00469600
	// MenuInputBindingTable::`scalar deleting destructor'

private:
	void FUN_00469900(ResourceLoadParams* p_params);
	void ParseWidgetBase(MenuWidget::CreateParams* p_entry);
	void FUN_00469c90(SelectorBinding* p_entry);
	void ReadNineFloats(LegoFloat* p_floats);
	void FUN_00469d90(ImageBinding* p_entry);
	void FUN_00469e20(TextLabelBinding* p_entry);
	void FUN_00469ee0(FrameBinding* p_entry);
	void FUN_00469fd0(ButtonBinding* p_entry);
	void FUN_0046a050(MultiStateBinding* p_entry);
	void FUN_0046a110(HotspotBinding* p_entry);
	void FUN_0046a190(SelectorBinding* p_entry);
	void FUN_0046a1f0(ModelCarouselBinding* p_entry);
	void FUN_0046a310(CompositeBinding* p_entry);
	void FUN_0046a490(SceneBinding* p_entry);
	void FUN_0046a590(SceneRefBinding* p_entry);
	void FUN_0046a640(TextFieldBinding* p_entry);
	void ParseRegionBindings();
	void ParseImageBindings();
	void ParseTextLabelBindings();
	void ParseFrameBindings();
	void ParseButtonBindings();
	void ParseMultiStateBindings();
	void ParseHotspotBindings();
	void ParseSelectorBindings();
	void ParseModelCarouselBindings();
	void ParseCompositeBindings();
	void ParseSceneBindings();
	void ParseTextFieldBindings();
	void ParseSceneRefBindings();

protected:
	void FUN_00469b20(MenuIcon::CreateParams* p_entry);
	void FUN_00469b50(MenuIcon::CreateParams* p_entry);

	RegionBinding* m_unk0x20;        // 0x20
	ImageBinding* m_unk0x24;         // 0x24
	TextLabelBinding* m_unk0x28;     // 0x28
	FrameBinding* m_unk0x2c;         // 0x2c
	ButtonBinding* m_unk0x30;        // 0x30
	MultiStateBinding* m_unk0x34;    // 0x34
	HotspotBinding* m_unk0x38;       // 0x38
	SelectorBinding* m_unk0x3c;      // 0x3c
	ModelCarouselBinding* m_unk0x40; // 0x40
	CompositeBinding* m_unk0x44;     // 0x44
	SceneBinding* m_unk0x48;         // 0x48
	TextFieldBinding* m_unk0x4c;     // 0x4c
	SceneRefBinding* m_unk0x50;      // 0x50
	undefined2 m_unk0x54;            // 0x54
	undefined m_unk0x56[2];          // 0x56
	LegoS32 m_unk0x58;               // 0x58
};

#endif // MENUINPUTBINDINGTABLE_H
