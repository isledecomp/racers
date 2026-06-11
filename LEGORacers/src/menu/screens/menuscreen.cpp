#include "menu/screens/menuscreen.h"

#include "core/gol.h"
#include "font/golfonttable.h"
#include "golerror.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "input/inputmanager.h"
#include "material/awakekite0x20.h"
#include "menu/menudialog.h"
#include "menu/menuscreencreateparams.h"
#include "menu/screens/menuscenescreen.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuhotspotbutton.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menusceneview.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextfield.h"
#include "menu/widgets/menutextlabel.h"
#include "menu/widgets/menutriangle.h"
#include "menu/widgets/menuwidget.h"
#include "menu/widgets/optionsrow.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"
#include "render/goldrawstate.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuScreen, 0x290)
DECOMP_SIZE_ASSERT(MenuScreen::SceneRefBinding, 0x54)

// GLOBAL: LEGORACERS 0x004b2240
const undefined4 g_unk0x4b2240[14] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};

// GLOBAL: LEGORACERS 0x004b2278
const MenuIcon::CreateState g_unk0x4b2278 = {{0}};

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
undefined4 MenuScreen::VTable0x50()
{
	return 1;
}

#pragma code_seg(".text$fold_44f590")
// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x00(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x04(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x08(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x0c(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x10(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x20(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x24(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x2c(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x30(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x34(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x38(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x3c(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x40(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x44(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::VTable0x48(MenuWidget*)
{
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046b380
MenuScreen::MenuScreen()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046b410
MenuScreen::~MenuScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046b480
void MenuScreen::Reset()
{
	m_menuTextStrings = NULL;
	m_menuNameStrings = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0xbc = NULL;
	m_fontTable = NULL;
	m_soundGroupBinding = NULL;
	m_inputManager = NULL;
	m_unk0x284 = NULL;
	m_cursorHelper = NULL;
	m_menuStyles = NULL;
	m_unk0x28c = 0;
	m_unk0x08.Clear();
	m_unk0x58.Clear();
	m_unk0xd8.VTable0x08();
	m_initialized = FALSE;
}

// FUNCTION: LEGORACERS 0x0046b500
LegoBool32 MenuScreen::Initialize(MenuScreenCreateParams* p_createParams)
{
	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_inputManager = p_createParams->m_inputManager;
	m_unk0x288 = p_createParams->m_unk0x2c;
	m_unk0x284 = p_createParams->m_unk0x20;
	m_cursorHelper = p_createParams->m_cursorHelper;
	m_unk0x28c = p_createParams->m_menuId;
	m_menuStyles = p_createParams->m_menuStyles;
	m_inputEvents = p_createParams->m_inputEvents;
	m_menuTextStrings = p_createParams->m_menuTextStrings;
	m_menuNameStrings = p_createParams->m_menuNameStrings;

	if (FUN_0046b630() && FUN_0046b6e0(p_createParams) && VTable0x58(p_createParams)) {
		VTable0x4c();
		m_inputManager->PollDevices(0);
		m_inputEvents->ClearQueue();
		m_initialized = TRUE;
	}

	return m_initialized;
}

// FUNCTION: LEGORACERS 0x0046b5d0
LegoBool32 MenuScreen::Destroy()
{
	if (m_initialized) {
		if (m_unk0xbc) {
			m_unk0xbc->Clear();
			m_golExport->VTable0x68(m_unk0xbc);
		}

		if (m_fontTable) {
			m_fontTable->Clear();
			m_golExport->DestroyFontTable(m_fontTable);
		}

		Reset();
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b630
LegoBool32 MenuScreen::FUN_0046b630()
{
	GolCommonDrawState* drawState = m_renderer->GetDrawState();
	MenuIcon::CreateParams createParams;

	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, g_unk0x4b2240, sizeof(g_unk0x4b2240));

	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_unk0x38 = TRUE;
	createParams.m_soundGroupBinding = m_soundGroupBinding;
	createParams.m_rect.m_right = drawState->m_width;
	createParams.m_rect.m_bottom = drawState->m_height;
	createParams.m_eventHandler = this;

	if (m_unk0xd8.FUN_00471e30(&createParams, &g_unk0x4b2278)) {
		m_unk0xd8.VTable0x4c(0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046b6e0
LegoBool32 MenuScreen::FUN_0046b6e0(MenuScreenCreateParams* p_createParams)
{
	GolString string;

	if (!VTable0x50()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_unk0x28c);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* idSuffix = ".idb";
	if (!p_createParams->m_unk0x2c) {
		idSuffix = ".idf";
	}
	strcat(fileName, idSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_unk0xbc = m_golExport->VTable0x34();
		m_unk0xbc->LoadImageDefinitions(m_renderer, fileName, p_createParams->m_unk0x2c);
	}

	string.CopyToString(fileName);

	const LegoChar* fontSuffix = ".fdb";
	if (!p_createParams->m_unk0x2c) {
		fontSuffix = ".fdf";
	}
	strcat(fileName, fontSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_fontTable = m_golExport->CreateFontTable();
		m_fontTable->VTable0x20(m_renderer, fileName, p_createParams->m_unk0x2c);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b890
LegoBool32 MenuScreen::VTable0x58(MenuScreenCreateParams* p_createParams)
{
	GolString string;

	if (!VTable0x50()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_unk0x28c);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* styleSuffix = ".msb";
	if (!p_createParams->m_unk0x2c) {
		styleSuffix = ".msd";
	}
	strcat(fileName, styleSuffix);

	if (!GolStream::FindFile(fileName)) {
		MenuStyleTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_unk0x04 = p_createParams->m_menuStyles;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_unk0x2c;

		if (!GetMenuStyles()->Load(&params)) {
			return FALSE;
		}
	}

	string.CopyToString(fileName);

	const LegoChar* inputSuffix = ".mib";
	if (!p_createParams->m_unk0x2c) {
		inputSuffix = ".mid";
	}
	strcat(fileName, inputSuffix);

	if (!GolStream::FindFile(fileName)) {
		MenuInputBindingTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_unk0x2c;

		if (!GetMenuInputBindings()->Load(&params)) {
			return FALSE;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046ba60
void MenuScreen::ApplyWidgetDefaults(MenuWidget::CreateParams* p_createParams)
{
	if (!p_createParams->m_golExport) {
		p_createParams->m_golExport = m_golExport;
	}

	if (!p_createParams->m_renderer) {
		p_createParams->m_renderer = m_renderer;
	}

	if (!p_createParams->m_soundGroupBinding) {
		p_createParams->m_soundGroupBinding = m_soundGroupBinding;
	}

	if (!p_createParams->m_eventHandler) {
		p_createParams->m_eventHandler = this;
	}

	if (!(p_createParams->m_flags & 2)) {
		::memset(&p_createParams->m_unk0x22, 0xff, sizeof(p_createParams->m_unk0x22));
	}

	if (!p_createParams->m_parent && (p_createParams->m_flags & 1)) {
		if (p_createParams->m_name[0]) {
			MenuInputBindingTable::IconBinding* entry =
				(MenuInputBindingTable::IconBinding*) GetMenuInputBindings()->ResolveEntryByName(
					p_createParams->m_name
				);

			if (entry) {
				p_createParams->m_unk0x26 = entry->m_unk0x20;
			}
		}

		if (!p_createParams->m_unk0x26) {
			p_createParams->m_unk0x26 = 1;
		}

		p_createParams->m_parent = m_unk0xd8.FindChildById(p_createParams->m_unk0x26);
	}
}

// FUNCTION: LEGORACERS 0x0046bb10
void MenuScreen::ApplyIconDefaults(MenuIcon::CreateParams* p_createParams)
{
	if (!p_createParams->m_parent && p_createParams->m_unk0x74) {
		if (p_createParams->m_unk0x4a) {
			MenuInputBindingTable::IconBinding* entry =
				(MenuInputBindingTable::IconBinding*) GetMenuInputBindings()->ResolveEntryByName(
					p_createParams->m_name
				);
			p_createParams->m_unk0x48 = entry->m_unk0x20;
		}

		if (!p_createParams->m_unk0x48) {
			p_createParams->m_unk0x48 = 1;
		}

		p_createParams->m_parent = static_cast<MenuIcon*>(m_unk0xd8.FindChildById(p_createParams->m_unk0x48));
	}

	if (!p_createParams->m_unk0x80) {
		p_createParams->m_unk0x80 = this;
	}

	ApplyWidgetDefaults(p_createParams);
}

// STUB: LEGORACERS 0x0046bb90
void MenuScreen::ApplySelectorDefaults(
	MenuSelectorBase::CreateParamsWithCarousel* p_createParams,
	MenuStyleTable::SelectorStyle* p_styleEntry
)
{
	LegoS32 i;

	ApplyIconDefaults(p_createParams);
	ApplyIconDefaults(p_createParams->m_unk0x84);
	ApplyIconDefaults(p_createParams->m_unk0x88);
	ApplyWidgetDefaults(p_createParams->m_unk0x8c);

	p_createParams->m_unk0x84->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x88->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x84->m_unk0x80 = NULL;
	p_createParams->m_unk0x88->m_unk0x80 = NULL;

	for (i = 0; i < 6; i++) {
		if (!p_createParams->m_unk0x84->m_images[i]) {
			p_createParams->m_unk0x84->m_images[i] = p_styleEntry->GetUnk0x90()->m_unk0x90[i];
		}

		if (!p_createParams->m_unk0x88->m_images[i]) {
			p_createParams->m_unk0x88->m_images[i] = p_styleEntry->GetUnk0x94()->m_unk0x90[i];
		}
	}

	for (i = 0; i < 8; i++) {
		if (!p_createParams->m_unk0x8c->m_images[6]) {
			p_createParams->m_unk0x8c->m_images[6] = p_styleEntry->m_unk0x98->m_unk0x00[6];
		}
	}

	if (!(p_createParams->m_unk0x8c->m_flags & 2) && p_styleEntry->m_unk0x98->m_unk0x28) {
		p_createParams->m_unk0x8c->m_unk0x58 = p_styleEntry->m_unk0x98->m_unk0x24;
	}
}

// FUNCTION: LEGORACERS 0x0046bc90
void MenuScreen::ApplyCompositeDefaults(
	MenuInputBindingTable::CompositeBinding* p_createParams,
	MenuStyleTable::CompositeStyle* p_styleEntry
)
{
	ApplyIconDefaults(p_createParams);
	ApplyIconDefaults(p_createParams->m_unk0x84);
	ApplyIconDefaults(p_createParams->m_unk0x88);
	ApplyWidgetDefaults(p_createParams->m_unk0x90);
	ApplyWidgetDefaults(p_createParams->m_unk0x8c);

	p_createParams->m_unk0x84->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x84->m_unk0x80 = NULL;
	p_createParams->m_unk0x88->m_unk0x38 = p_createParams->m_unk0x38;
	p_createParams->m_unk0x88->m_unk0x80 = NULL;

	for (LegoS32 i = 0; i < 6; i++) {
		if (!p_createParams->m_unk0x84->m_images[i]) {
			p_createParams->m_unk0x84->m_images[i] = p_styleEntry->GetUnk0x90()->m_unk0x90[i];
		}

		if (!p_createParams->m_unk0x88->m_images[i]) {
			p_createParams->m_unk0x88->m_images[i] = p_styleEntry->GetUnk0x94()->m_unk0x90[i];
		}
	}

	if (!p_createParams->m_unk0x90->m_unk0x38) {
		p_createParams->m_unk0x90->m_unk0x38 = p_styleEntry->m_unk0x9c->m_unk0x00;
	}

	if (!p_createParams->m_unk0x8c->m_unk0x38) {
		p_createParams->m_unk0x8c->m_unk0x38 = p_styleEntry->m_unk0x98->m_unk0x00;
	}
}

// FUNCTION: LEGORACERS 0x0046bd80
void* MenuScreen::GetStyleEntry(undefined2 p_unk0x04)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_unk0x04);
	string.CopyToBuf8(name);
	return VTable0x60()->FUN_00470e60(name);
}

// FUNCTION: LEGORACERS 0x0046be10
void* MenuScreen::GetBindingEntry(undefined2 p_unk0x04)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_unk0x04);
	string.CopyToBuf8(name);
	return GetMenuInputBindings()->ResolveEntryByName(name);
}

// FUNCTION: LEGORACERS 0x0046bea0
LegoBool32 MenuScreen::CreateTriangle(MenuTriangle* p_unk0x04, undefined2 p_unk0x08)
{
	MenuInputBindingTable::RegionBinding* sourceParams =
		static_cast<MenuInputBindingTable::RegionBinding*>(GetBindingEntry(p_unk0x08));
	if (sourceParams == NULL) {
		return FALSE;
	}

	MenuInputBindingTable::RegionBinding createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	return p_unk0x04->FUN_004735a0(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bef0
LegoBool32 MenuScreen::CreateImage(MenuImage* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::ImageBinding* sourceParams = GetImageBinding(p_unk0x08);
	MenuStyleTable::ImageStyle* styleEntry = GetImageStyle(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuImage::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	if (!createParams.m_unk0x38) {
		createParams.m_unk0x38 = styleEntry->m_unk0x00;
	}

	if (!(createParams.m_flags & 2) && styleEntry->m_unk0x08) {
		createParams.m_unk0x38 = styleEntry->m_unk0x00;
	}

	return p_unk0x04->FUN_0046f150(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bf80
LegoBool32 MenuScreen::CreateTextLabel(
	MenuTextLabel* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10
)
{
	MenuTextLabel::CreateParams* sourceParams = static_cast<MenuTextLabel::CreateParams*>(GetBindingEntry(p_unk0x08));
	MenuStyleTable::TextStyle* styleEntry = static_cast<MenuStyleTable::TextStyle*>(GetStyleEntry(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuTextLabel::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);
	createParams.m_unk0x40 = p_unk0x10;

	if (!createParams.m_unk0x38) {
		createParams.m_unk0x38 = m_menuTextStrings;
	}

	if (!createParams.m_unk0x44 && styleEntry->m_unk0x08) {
		createParams.m_unk0x44 = styleEntry->m_unk0x08;
	}

	if (!createParams.m_unk0x3c) {
		createParams.m_unk0x3c = styleEntry->m_unk0x00;
	}

	if (styleEntry->m_unk0x0c && !(createParams.m_flags & 2)) {
		createParams.m_unk0x22 = styleEntry->m_unk0x04;
	}

	return p_unk0x04->FUN_0046f520(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c050
LegoBool32 MenuScreen::CreateFrame(MenuFrame* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuInputBindingTable::FrameBinding* sourceParams =
		static_cast<MenuInputBindingTable::FrameBinding*>(GetBindingEntry(p_unk0x08));
	MenuStyleTable::FrameStyle* styleEntry = static_cast<MenuStyleTable::FrameStyle*>(GetStyleEntry(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuFrame::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	for (LegoS32 i = 0; i < 8; i++) {
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_unk0x00[i];
		}
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_unk0x00[i];
		}
	}

	if (!(sourceParams->m_flags & 2) && styleEntry->m_unk0x28) {
		createParams.m_unk0x22 = styleEntry->m_unk0x20;
		createParams.m_unk0x58 = styleEntry->m_unk0x24;
	}

	return p_unk0x04->FUN_0046ecd0(&createParams);
}

// FUNCTION: LEGORACERS 0x0046c110
LegoBool32 MenuScreen::CreateButton(MenuButton* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuButton::CreateParams* sourceParams = static_cast<MenuButton::CreateParams*>(GetBindingEntry(p_unk0x08));
	MenuStyleTable::ButtonStyle* styleEntry = static_cast<MenuStyleTable::ButtonStyle*>(GetStyleEntry(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuButton::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	for (LegoS32 i = 0; i < 6; i++) {
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_unk0x90[i];
		}
	}

	return p_unk0x04->FUN_004663d0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c1b0
LegoBool32 MenuScreen::CreateHotspotButton(MenuHotspotButton* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuHotspotButton::CreateParams* sourceParams =
		static_cast<MenuHotspotButton::CreateParams*>(GetBindingEntry(p_unk0x08));
	MenuStyleTable::HotspotStyle* styleEntry = GetHotspotStyle(p_unk0x0c);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuHotspotButton::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	if (!createParams.m_unk0x9c) {
		createParams.m_unk0x9c = styleEntry->m_unk0xa8;
	}

	return p_unk0x04->FUN_004665f0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c240
LegoBool32 MenuScreen::CreateCarousel(MenuCarousel* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuCarousel::CreateParams* sourceParams = static_cast<MenuCarousel::CreateParams*>(GetBindingEntry(p_unk0x08));
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_unk0x0c));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuCarousel::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	return p_unk0x04->FUN_0046c970(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c2b0
LegoBool32 MenuScreen::CreateSelector(
	MenuSelector* p_widget,
	MenuCarousel* p_carousel,
	undefined2 p_cpId,
	undefined2 p_styleId
)
{
	MenuSelector::CreateParams* sourceParams = static_cast<MenuSelector::CreateParams*>(GetBindingEntry(p_cpId));
	MenuStyleTable::SelectorStyle* styleEntry = static_cast<MenuStyleTable::SelectorStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuSelector::CreateParams* bannerParams = new MenuSelector::CreateParams;
	MenuButton::CreateParams* glyph1Params = new MenuButton::CreateParams;
	MenuButton::CreateParams* glyph2Params = new MenuButton::CreateParams;
	MenuFrame::CreateParams* tomeParams = new MenuFrame::CreateParams;
	if (!bannerParams || !glyph1Params || !glyph2Params || !tomeParams) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	*bannerParams = *sourceParams;
	*glyph1Params = *sourceParams->m_unk0x84;
	*glyph2Params = *sourceParams->m_unk0x88;
	*tomeParams = *sourceParams->m_unk0x8c;

	bannerParams->m_unk0x88 = glyph2Params;
	bannerParams->m_unk0x84 = glyph1Params;
	bannerParams->m_unk0x8c = tomeParams;
	bannerParams->m_unk0x90 = p_carousel;

	ApplySelectorDefaults(bannerParams, styleEntry);

	LegoBool32 result = p_widget->FUN_00467800(bannerParams, styleEntry);

	delete bannerParams;
	delete glyph1Params;
	delete glyph2Params;
	delete tomeParams;

	return result;
}

// FUNCTION: LEGORACERS 0x0046c400
LegoBool32 MenuScreen::CreateOptionsRow(OptionsRowBase* p_widget, undefined2 p_cpId, undefined2 p_styleId)
{
	MenuInputBindingTable::CompositeBinding* sourceParams =
		static_cast<MenuInputBindingTable::CompositeBinding*>(GetBindingEntry(p_cpId));
	MenuStyleTable::CompositeStyle* styleEntry = static_cast<MenuStyleTable::CompositeStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuInputBindingTable::CompositeBinding createParams = *sourceParams;
	ApplyCompositeDefaults(&createParams, styleEntry);

	return p_widget->FUN_0046dfb0(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c480
LegoBool32 MenuScreen::CreateSceneView(MenuSceneView* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuSceneView::CreateParams* sourceParams = static_cast<MenuSceneView::CreateParams*>(GetBindingEntry(p_unk0x0c));
	if (!sourceParams) {
		return FALSE;
	}

	MenuSceneView::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);
	createParams.m_unk0x7c = p_unk0x08;
	createParams.m_unk0x5c = 1.0f;
	createParams.m_unk0x80 = VTable0x6c();
	return p_unk0x04->FUN_00465820(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c510
LegoBool32 MenuScreen::CreateFramedSceneView(MenuFramedSceneView* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c)
{
	MenuFramedSceneView::CreateParams* sourceParams =
		static_cast<MenuFramedSceneView::CreateParams*>(GetBindingEntry(p_unk0x0c));
	if (!sourceParams) {
		return FALSE;
	}

	MenuFramedSceneView::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	if (createParams.m_unk0x84) {
		ApplyWidgetDefaults(createParams.m_unk0x84);
	}

	createParams.m_unk0x7c = p_unk0x08;
	createParams.m_unk0x5c = 1.0f;
	createParams.m_unk0x80 = VTable0x6c();
	return p_unk0x04->FUN_004661f0(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c5b0
undefined4 MenuScreen::CreateRegion(MenuWidget* p_unk0x04, undefined2 p_unk0x08)
{
	SceneRefBinding* params = GetSceneRefBinding(p_unk0x08);
	if (!params) {
		return 0;
	}

	SceneRefBinding createParams = *params;
	ApplyWidgetDefaults(&createParams);
	createParams.m_unk0x50 = VTable0x6c();

	return static_cast<MenuSceneScreen::SceneWidget*>(p_unk0x04)->FUN_00466b50(&createParams, m_unk0x288);
}

// FUNCTION: LEGORACERS 0x0046c610
LegoBool32 MenuScreen::CreateTextField(
	MenuTextField* p_unk0x04,
	undefined2 p_unk0x08,
	undefined2 p_unk0x0c,
	undefined2 p_unk0x10,
	GolString* p_unk0x14
)
{
	MenuTextField::CreateParams* sourceParams = static_cast<MenuTextField::CreateParams*>(GetBindingEntry(p_unk0x08));
	MenuIcon::CreateState* styleEntry = static_cast<MenuIcon::CreateState*>(GetStyleEntry(p_unk0x0c));
	if (!sourceParams || !styleEntry || !p_unk0x10) {
		return FALSE;
	}

	MenuTextField::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	if (!createParams.m_unk0x84) {
		createParams.m_unk0x84 = m_menuTextStrings;
	}

	createParams.m_unk0x88 = p_unk0x10;
	createParams.m_unk0x90 = p_unk0x14;
	createParams.m_unk0x8c = sourceParams->m_unk0x8c;

	return p_unk0x04->VTable0x70(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c6f0
undefined4 MenuScreen::FUN_0046c6f0(MenuIcon* p_unk0x04, MenuIcon* p_unk0x08, undefined2 p_unk0x0c)
{
	MenuDialog::DialogScreen* entry = m_unk0x284->FUN_00468c50(2, p_unk0x0c, this, 0);
	entry->SetUnk0x744(p_unk0x04);
	entry->SetUnk0x748(p_unk0x08);
	entry->FUN_00468590();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c730
undefined4 MenuScreen::FUN_0046c730(MenuIcon* p_unk0x04, undefined2 p_unk0x08)
{
	MenuDialog::DialogScreen* entry = m_unk0x284->FUN_00468c50(1, p_unk0x08, this, 0);
	entry->SetUnk0x740(p_unk0x04);
	entry->FUN_00468590();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c760
void MenuScreen::FUN_0046c760()
{
	MenuIcon* icon;
	MenuWidget* node;

	while (m_unk0xd8.GetFirstChild()) {
		icon = &m_unk0xd8;

		while (icon->GetFirstChild()) {
			icon = icon->GetFirstChild();
		}

		icon->DetachFromParent();
	}

	while (static_cast<MenuWidget*>(&m_unk0xd8)->GetFirstChild()) {
		node = &m_unk0xd8;

		while (node->GetFirstChild()) {
			node = node->GetFirstChild();
		}

		node->RemoveFromParent();
	}
}

// FUNCTION: LEGORACERS 0x0046c7d0
LegoBool32 MenuScreen::VTable0x78(undefined4)
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c7e0 FOLDED
LegoBool32 MenuScreen::VTable0x7c(Rect* p_arg1, Rect* p_arg2)
{
	m_unk0xd8.VTable0x1c(p_arg1, p_arg2);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c810
MenuStyleTable* MenuScreen::GetMenuStyles()
{
	return &m_unk0x08;
}

// FUNCTION: LEGORACERS 0x0046c820 FOLDED
MenuStyleTable* MenuScreen::VTable0x60()
{
	MenuStyleTable* styles = GetMenuStyles();
	if (!styles->GetNameEntries()) {
		return m_menuStyles;
	}

	return styles;
}

// FUNCTION: LEGORACERS 0x0046c840
MenuInputBindingTable* MenuScreen::GetMenuInputBindings()
{
	return &m_unk0x58;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x0046c850
#pragma code_seg(".text$imaginarynotion_vt6c")
LegoFloat MenuScreen::VTable0x6c()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 MenuScreen::VTable0x14(MenuWidget*, void*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
LegoBool32 MenuScreen::VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
LegoBool32 MenuScreen::VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 MenuScreen::VTable0x28(MenuWidget*, void*, undefined4, undefined4)
{
	return 0;
}
