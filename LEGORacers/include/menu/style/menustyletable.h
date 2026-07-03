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
class GolImage;

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class MenuStyleTable : public MenuResourceTable {
public:
	// SIZE 0x0c
	class ImageStyle {
	public:
		GolImage* m_image;        // 0x00
		VisualStateColor m_color; // 0x04
		LegoBool32 m_hasColor;    // 0x08
	};

	// SIZE 0x14
	class TextStyle {
	public:
		// .msb text-style field tokens
		enum {
			e_wrapWidth = 0x2e,
			e_centered = 0x2f,
		};

		GolFont* m_font;          // 0x00
		VisualStateColor m_color; // 0x04
		LegoS32 m_wrapWidth;      // 0x08
		LegoBool32 m_hasColor;    // 0x0c
		LegoS32 m_centered;       // 0x10
	};

	// SIZE 0x18
	class CarouselStyle {
	public:
		enum {
			e_scrollDurationMs = 0x2d,
			e_pageMode = 0x2f,
		};

		undefined4 m_soundIds[3];   // 0x00
		LegoS32 m_scrollDurationMs; // 0x0c
		LegoS32 m_pageMode;         // 0x10
		LegoS32 m_wrap;             // 0x14
	};

	// SIZE 0x2c
	class FrameStyle {
	public:
		GolImage* m_images[8];     // 0x00
		VisualStateColor m_color0; // 0x20
		VisualStateColor m_color1; // 0x24
		LegoBool32 m_hasColors;    // 0x28
	};

	// SIZE 0x90
	class IconStyle : public MenuIcon::CreateState {
	public:
		// .msb icon-style field tokens
		enum {
			e_stateRects = 0x2c,
			e_transitionDurationMs = 0x2d,
		};
	};

	// SIZE 0x98
	class SelectorStyleBase : public IconStyle {
	public:
		IconStyle* m_prevButtonStyle; // 0x90
		IconStyle* m_nextButtonStyle; // 0x94
	};

	// SIZE 0xa8
	class ButtonStyle : public IconStyle {
	public:
		GolImage* m_stateImages[6]; // 0x90
	};

	// SIZE 0x104
	class TextButtonStyle : public IconStyle {
	public:
		enum {
			e_rects = 0x2c,
			e_maxTextWidth = 0x2e,
		};

		GolFont* m_stateFonts[6];          // 0x90
		GolImage* m_stateImages[6];        // 0xa8
		VisualStateColor m_stateColors[6]; // 0xc0
		VisualStateColor m_unk0xd8;        // 0xd8
		Rect m_unk0xdc;                    // 0xdc
		Rect m_unk0xec;                    // 0xec
		LegoU32 m_maxTextWidth;            // 0xfc
		LegoBool32 m_hasMaxTextWidth;      // 0x100
	};

	// SIZE 0x100
	class MultiStateStyle : public IconStyle {
	public:
		enum {
			e_rect = 0x2c,
		};

		GolFont* m_stateFonts[6];      // 0x90
		GolImage* m_stateImages[6][3]; // 0xa8
		Rect m_rect;                   // 0xf0
	};

	// SIZE 0x150
	class HotspotStyle : public IconStyle {
	public:
		enum {
			e_hotspotCount = 0x2f,
			e_hotspotRects = 0x30,
			e_hotspotIds = 0x31,
		};

		undefined m_unk0x90[0xa8 - 0x90]; // 0x90
		GolImage* m_image;                // 0xa8
		LegoS32 m_hotspotCount;           // 0xac
		undefined4 m_hotspotIds[8];       // 0xb0
		Rect m_hotspotRects[8];           // 0xd0
	};

	// SIZE 0xbc
	class SelectorStyle : public SelectorStyleBase {
	public:
		FrameStyle* m_frameStyle;                // 0x98
		VisualStateColor m_itemColors[4];        // 0x9c
		VisualStateColor m_focusedItemColors[4]; // 0xac

		ButtonStyle* GetPrevButtonStyle() const { return static_cast<ButtonStyle*>(m_prevButtonStyle); }
		ButtonStyle* GetNextButtonStyle() const { return static_cast<ButtonStyle*>(m_nextButtonStyle); }
	};

	// SIZE 0xbc
	class CompositeStyle : public SelectorStyleBase {
	public:
		ImageStyle* m_thumbStyle;             // 0x98
		ImageStyle* m_trackStyle;             // 0x9c
		GolImage* m_stateImages[6];           // 0xa0
		MenuIcon::SoundIdPair m_stepSoundIds; // 0xb8

		ButtonStyle* GetPrevButtonStyle() const { return static_cast<ButtonStyle*>(m_prevButtonStyle); }
		ButtonStyle* GetNextButtonStyle() const { return static_cast<ButtonStyle*>(m_nextButtonStyle); }
	};

	// SIZE 0x10
	struct ResourceLoadParams {
		GolD3DRenderDevice* m_renderer;   // 0x00
		SharedMenuStyleTable* m_fallback; // 0x04
		const LegoChar* m_fileName;       // 0x08
		LegoBool32 m_binary;              // 0x0c
	};

	MenuStyleTable();
	~MenuStyleTable() override;                      // vtable+0x00
	void Clear() override;                           // vtable+0x08
	void Reset() override;                           // vtable+0x0c
	void CreateParser(undefined4 p_binary) override; // vtable+0x10
	void ParseSection(undefined4 p_token) override;  // vtable+0x14
	LegoBool32 Load(ResourceLoadParams* p_params);
	void* FindStyle(const LegoChar* p_name);
	ImageStyle* GetImageStyle(const LegoChar* p_name) { return static_cast<ImageStyle*>(FindStyle(p_name)); }
	TextStyle* GetTextStyle(const LegoChar* p_name) { return static_cast<TextStyle*>(FindStyle(p_name)); }
	IconStyle* GetIconStyle(const LegoChar* p_name) { return static_cast<IconStyle*>(FindStyle(p_name)); }
	TextButtonStyle* GetTextButtonStyle(const LegoChar* p_name)
	{
		return static_cast<TextButtonStyle*>(FindStyle(p_name));
	}

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// MenuStyleTable::`scalar deleting destructor'

protected:
	void ParseFile(ResourceLoadParams* p_params);
	void ParseImageStyle(ImageStyle* p_entry);
	void ParseTextStyle(TextStyle* p_entry);
	void ParseFrameStyle(FrameStyle* p_entry);
	void ParseIconStyle(IconStyle* p_entry);
	void ParseButtonStyle(ButtonStyle* p_entry);
	void ParseMultiStateStyle(MultiStateStyle* p_entry);
	void ParseHotspotStyle(HotspotStyle* p_entry);
	void ParseCarouselStyle(CarouselStyle* p_entry);
	void ParseSelectorStyle(SelectorStyle* p_entry);
	void ParseCompositeStyle(CompositeStyle* p_entry);

private:
	void LoadImageStyles();
	void LoadTextStyles();
	void LoadFrameStyles();
	void LoadButtonStyles();
	void LoadMultiStateStyles();
	void LoadHotspotStyles();
	void LoadCarouselStyles();
	void LoadSelectorStyles();
	void LoadCompositeStyles();
	void LoadIconStyles();

protected:
	MenuStyleTable* m_fallback;          // 0x20
	ImageStyle* m_imageStyles;           // 0x24
	TextStyle* m_textStyles;             // 0x28
	FrameStyle* m_frameStyles;           // 0x2c
	ButtonStyle* m_buttonStyles;         // 0x30
	MultiStateStyle* m_multiStateStyles; // 0x34
	HotspotStyle* m_hotspotStyles;       // 0x38
	CarouselStyle* m_carouselStyles;     // 0x3c
	SelectorStyle* m_selectorStyles;     // 0x40
	CompositeStyle* m_compositeStyles;   // 0x44
	IconStyle* m_iconStyles;             // 0x48
};

#endif // MENUSTYLETABLE_H
