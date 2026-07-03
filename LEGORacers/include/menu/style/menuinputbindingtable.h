#ifndef MENUINPUTBINDINGTABLE_H
#define MENUINPUTBINDINGTABLE_H

#include "compat.h"
#include "decomp.h"
#include "goltxtparser.h"
#include "menu/style/menuresourcetable.h"
#include "menu/style/scenerefbinding.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextfield.h"
#include "menu/widgets/visualstatecolor.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFont;
class GolString;
class GolStringTable;
class GolImage;

// VTABLE: LEGORACERS 0x004b2180
// SIZE 0x5c
class MenuInputBindingTable : public MenuResourceTable {
public:
	// VTABLE: LEGORACERS 0x004b2198
	// SIZE 0x1fc
	class MidTxtParser : public GolTxtParser {
	public:
		// .mid field tokens shared across binding blocks (0x34 stays unnamed:
		// parsed into a field with no readers)
		enum {
			e_image = 0x28,
			e_font = 0x29,
			e_colors = 0x2a,
			e_soundIds = 0x2b,
			e_helpStringId = 0x2c,
			e_sceneName = 0x2d,
			e_camera = 0x2e,
			e_rect = 0x2f,
			e_id = 0x30,
			e_name = 0x31,
			e_attachToParent = 0x32,
			e_value = 0x33,
			e_viewportClearMode = 0x35,
			e_widget = 0x36,
			e_imageRef = 0x38,
			e_bindingRef = 0x3a,
			e_button = 0x3b,
			e_unknown0x34 = 0x34,
		};
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
		GolStringTable* m_stringTable; // 0x38
		GolFont* m_font;               // 0x3c
		undefined2 m_stringId;         // 0x40
		LegoU32 m_wrapWidth;           // 0x44
	};

	// SIZE 0x60
	class FrameBinding : public MenuFrame::CreateParams {};

	// SIZE 0x84
	class IconBinding : public MenuIcon::CreateParams {};

	// SIZE 0x88
	class SceneBinding : public MenuWidget::CreateParams {
	public:
		LegoFloat m_cameraVectors[9];      // 0x38
		LegoFloat m_worldScale;            // 0x5c
		LegoChar m_worldName[0x70 - 0x60]; // 0x60
		undefined4 m_drawWorld;            // 0x70
		LegoBool32 m_hasBlendedWorld;      // 0x74
		LegoU32 m_viewportClearMode;       // 0x78
		undefined4 m_eventCode;            // 0x7c
		LegoFloat m_aspectScale;           // 0x80
		void* m_linkedBinding;             // 0x84
	};

	// SIZE 0x98
	class SelectorBinding : public MenuSelectorBase::CreateParamsWithCarousel {
	public:
		undefined4 m_carouselWidget;       // 0x90 (filled at runtime; see MenuSelector::CreateParams)
		undefined4 m_acceptUnfocusedInput; // 0x94
	};

	// SIZE 0x9c
	class ButtonBinding : public IconBinding {
	public:
		GolImage* m_stateImages[6]; // 0x84
	};

	// SIZE 0xa0
	class HotspotBinding : public ButtonBinding {
	public:
		GolImage* m_highlightImage; // 0x9c
	};

	// SIZE 0xa0
	class TextFieldBinding : public IconBinding {
	public:
		GolStringTable* m_stringTable;            // 0x84
		undefined2 m_charsetStringId;             // 0x88
		undefined m_unk0x8a[0x8c - 0x8a];         // 0x8a
		GolFont* m_font;                          // 0x8c
		GolString* m_initialText;                 // 0x90
		undefined2 m_maxLength;                   // 0x94
		MenuTextField::SoundIdSet m_editSoundIds; // 0x96
	};

	// SIZE 0xb8
	class CompositeBinding : public MenuSelectorBase::CreateParams {
	public:
		MenuImage::CreateParams* m_thumbParams; // 0x8c
		MenuImage::CreateParams* m_trackParams; // 0x90
		GolImage* m_stateImages[6];             // 0x94
		MenuIcon::SoundIdPair m_stepSoundIds;   // 0xac
		LegoS32 m_initialValue;                 // 0xb0
		LegoS32 m_stepCount;                    // 0xb4
	};

	// SIZE 0xec
	class MultiStateBinding : public IconBinding {
	public:
		undefined4 m_unk0x84;          // 0x84
		GolFont* m_stateFonts[6];      // 0x88
		GolImage* m_stateImages[6][3]; // 0xa0
		undefined4 m_unk0xe8;          // 0xe8
	};

	// SIZE 0x74
	class ModelCarouselBinding : public MenuWidget::CreateParams {
	public:
		LegoS32 m_slotCount;          // 0x38
		Rect* m_slotRects;            // 0x3c
		LegoFloat m_scrollStep;       // 0x40
		LegoS32 m_focusedSlot;        // 0x44
		LegoFloat m_cameraVectors[9]; // 0x48
		LegoU32 m_viewportIndex;      // 0x6c
		LegoFloat m_aspectScale;      // 0x70
	};

	// SIZE 0x0c
	struct ResourceLoadParams {
		GolD3DRenderDevice* m_renderer; // 0x00
		const LegoChar* m_fileName;     // 0x04
		LegoBool32 m_binary;            // 0x08
	};

	MenuInputBindingTable();
	~MenuInputBindingTable() override;               // vtable+0x00
	void Clear() override;                           // vtable+0x08
	void Reset() override;                           // vtable+0x0c
	void CreateParser(undefined4 p_binary) override; // vtable+0x10
	void ParseSection(undefined4 p_token) override;  // vtable+0x14
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
	void ParseFile(ResourceLoadParams* p_params);
	void ParseWidgetBase(MenuWidget::CreateParams* p_entry);
	void ParseSelectorField(SelectorBinding* p_entry);
	void ReadNineFloats(LegoFloat* p_floats);
	void ParseImageBinding(ImageBinding* p_entry);
	void ParseTextLabelBinding(TextLabelBinding* p_entry);
	void ParseFrameBinding(FrameBinding* p_entry);
	void ParseButtonBinding(ButtonBinding* p_entry);
	void ParseMultiStateBinding(MultiStateBinding* p_entry);
	void ParseHotspotBinding(HotspotBinding* p_entry);
	void ParseSelectorBinding(SelectorBinding* p_entry);
	void ParseModelCarouselBinding(ModelCarouselBinding* p_entry);
	void ParseCompositeBinding(CompositeBinding* p_entry);
	void ParseSceneBinding(SceneBinding* p_entry);
	void ParseSceneRefBinding(SceneRefBinding* p_entry);
	void ParseTextFieldBinding(TextFieldBinding* p_entry);
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
	void InitIconDefaults(MenuIcon::CreateParams* p_entry);
	void ParseIconField(MenuIcon::CreateParams* p_entry);

	RegionBinding* m_regionBindings;               // 0x20
	ImageBinding* m_imageBindings;                 // 0x24
	TextLabelBinding* m_textLabelBindings;         // 0x28
	FrameBinding* m_frameBindings;                 // 0x2c
	ButtonBinding* m_buttonBindings;               // 0x30
	MultiStateBinding* m_multiStateBindings;       // 0x34
	HotspotBinding* m_hotspotBindings;             // 0x38
	SelectorBinding* m_selectorBindings;           // 0x3c
	ModelCarouselBinding* m_modelCarouselBindings; // 0x40
	CompositeBinding* m_compositeBindings;         // 0x44
	SceneBinding* m_sceneBindings;                 // 0x48
	TextFieldBinding* m_textFieldBindings;         // 0x4c
	SceneRefBinding* m_sceneRefBindings;           // 0x50
	undefined2 m_nextWidgetId;                     // 0x54
	LegoS32 m_entryCount;                          // 0x58
};

#endif // MENUINPUTBINDINGTABLE_H
