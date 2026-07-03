#include "menu/screens/menuscreen.h"

#include "core/gol.h"
#include "font/golfonttable.h"
#include "golerror.h"
#include "golname.h"
#include "golstream.h"
#include "golstring.h"
#include "golstringtable.h"
#include "input/inputmanager.h"
#include "material/golimagedefinitionlist.h"
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
DECOMP_SIZE_ASSERT(SceneRefBinding, 0x54)

// GLOBAL: LEGORACERS 0x004b2240
const undefined4 g_rootIconParams[14] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};

// GLOBAL: LEGORACERS 0x004b2278
const MenuIcon::CreateState g_rootIconState = {{0}};

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
undefined4 MenuScreen::ShouldLoadResources()
{
	return 1;
}

// Keep the empty menu callbacks in the original input-device empty-void fold group.
#pragma code_seg(".text$fold_44f590")
// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetCreated(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetDestroyed(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetMoved(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetResized(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnCarouselSettled(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetFocused(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetUnfocused(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconEnabled(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconDisabled(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconFocused(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconUnfocused(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconSelected(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnIconDeselected(MenuIcon*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnWidgetValueChanged(MenuWidget*)
{
}

// FUNCTION: LEGORACERS 0x0044f590 FOLDED
void MenuScreen::OnSelectorSettled(MenuWidget*)
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
	m_imageList = NULL;
	m_fontTable = NULL;
	m_soundGroupBinding = NULL;
	m_inputManager = NULL;
	m_dialog = NULL;
	m_cursor = NULL;
	m_menuStyles = NULL;
	m_resourceMenuId = 0;
	m_styleTable.Clear();
	m_bindingTable.Clear();
	m_rootIcon.Destroy();
	m_initialized = FALSE;
}

// FUNCTION: LEGORACERS 0x0046b500
LegoBool32 MenuScreen::Initialize(MenuScreenCreateParams* p_createParams)
{
	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;
	m_inputManager = p_createParams->m_inputManager;
	m_useBinaryFiles = p_createParams->m_useBinaryFiles;
	m_dialog = p_createParams->m_dialog;
	m_cursor = p_createParams->m_cursor;
	m_resourceMenuId = p_createParams->m_menuId;
	m_menuStyles = p_createParams->m_menuStyles;
	m_inputEvents = p_createParams->m_inputEvents;
	m_menuTextStrings = p_createParams->m_menuTextStrings;
	m_menuNameStrings = p_createParams->m_menuNameStrings;

	if (CreateRootIcon() && LoadImagesAndFonts(p_createParams) && LoadStylesAndBindings(p_createParams)) {
		CreateWidgets();
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
		if (m_imageList) {
			m_imageList->Clear();
			m_golExport->DestroyImageList(m_imageList);
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
LegoBool32 MenuScreen::CreateRootIcon()
{
	GolCommonDrawState* drawState = m_renderer->GetDrawState();
	MenuIcon::CreateParams createParams;

	memset(&createParams, 0, sizeof(createParams));
	memcpy(&createParams, g_rootIconParams, sizeof(g_rootIconParams));

	createParams.m_golExport = m_golExport;
	createParams.m_renderer = m_renderer;
	createParams.m_startEnabled = TRUE;
	createParams.m_soundGroupBinding = m_soundGroupBinding;
	createParams.m_rect.m_right = drawState->m_width;
	createParams.m_rect.m_bottom = drawState->m_height;
	createParams.m_eventHandler = this;

	if (m_rootIcon.Create(&createParams, &g_rootIconState)) {
		m_rootIcon.Select(0);
		return TRUE;
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046b6e0
LegoBool32 MenuScreen::LoadImagesAndFonts(MenuScreenCreateParams* p_createParams)
{
	GolString string;

	if (!ShouldLoadResources()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_resourceMenuId);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* idSuffix = ".idb";
	if (!p_createParams->m_useBinaryFiles) {
		idSuffix = ".idf";
	}
	strcat(fileName, idSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_imageList = m_golExport->CreateImageList();
		m_imageList->LoadImageDefinitions(m_renderer, fileName, p_createParams->m_useBinaryFiles);
	}

	string.CopyToString(fileName);

	const LegoChar* fontSuffix = ".fdb";
	if (!p_createParams->m_useBinaryFiles) {
		fontSuffix = ".fdf";
	}
	strcat(fileName, fontSuffix);

	if (!GolStream::FindFile(fileName)) {
		m_fontTable = m_golExport->CreateFontTable();
		m_fontTable->LoadFontDefinitions(m_renderer, fileName, p_createParams->m_useBinaryFiles);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b890
LegoBool32 MenuScreen::LoadStylesAndBindings(MenuScreenCreateParams* p_createParams)
{
	GolString string;

	if (!ShouldLoadResources()) {
		return TRUE;
	}

	m_menuNameStrings->CopyStringByIndex(&string, m_resourceMenuId);

	LegoChar fileName[16];
	string.CopyToString(fileName);

	const LegoChar* styleSuffix = ".msb";
	if (!p_createParams->m_useBinaryFiles) {
		styleSuffix = ".msd";
	}
	strcat(fileName, styleSuffix);

	if (!GolStream::FindFile(fileName)) {
		MenuStyleTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_fallback = p_createParams->m_menuStyles;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_useBinaryFiles;

		if (!GetMenuStyles()->Load(&params)) {
			return FALSE;
		}
	}

	string.CopyToString(fileName);

	const LegoChar* inputSuffix = ".mib";
	if (!p_createParams->m_useBinaryFiles) {
		inputSuffix = ".mid";
	}
	strcat(fileName, inputSuffix);

	if (!GolStream::FindFile(fileName)) {
		MenuInputBindingTable::ResourceLoadParams params;
		params.m_renderer = m_renderer;
		params.m_fileName = fileName;
		params.m_binary = p_createParams->m_useBinaryFiles;

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
		::memset(&p_createParams->m_color, 0xff, sizeof(p_createParams->m_color));
	}

	if (!p_createParams->m_parent && (p_createParams->m_flags & 1)) {
		if (p_createParams->m_name[0]) {
			MenuInputBindingTable::IconBinding* entry =
				(MenuInputBindingTable::IconBinding*) GetMenuInputBindings()->ResolveEntryByName(
					p_createParams->m_name
				);

			if (entry) {
				p_createParams->m_parentId = entry->m_id;
			}
		}

		if (!p_createParams->m_parentId) {
			p_createParams->m_parentId = 1;
		}

		p_createParams->m_parent = m_rootIcon.FindChildById(p_createParams->m_parentId);
	}
}

// FUNCTION: LEGORACERS 0x0046bb10
void MenuScreen::ApplyIconDefaults(MenuIcon::CreateParams* p_createParams)
{
	if (!p_createParams->m_parent && p_createParams->m_attachToParent) {
		if (p_createParams->m_resolveParentByName) {
			MenuInputBindingTable::IconBinding* entry =
				(MenuInputBindingTable::IconBinding*) GetMenuInputBindings()->ResolveEntryByName(
					p_createParams->m_name
				);
			p_createParams->m_parentId = entry->m_id;
		}

		if (!p_createParams->m_parentId) {
			p_createParams->m_parentId = 1;
		}

		p_createParams->m_parent = static_cast<MenuIcon*>(m_rootIcon.FindChildById(p_createParams->m_parentId));
	}

	if (!p_createParams->m_iconEventHandler) {
		p_createParams->m_iconEventHandler = this;
	}

	ApplyWidgetDefaults(p_createParams);
}

// STUB: LEGORACERS 0x0046bb90
void MenuScreen::ApplySelectorDefaults(
	MenuSelectorBase::CreateParamsWithCarousel* p_createParams,
	MenuStyleTable::SelectorStyle* p_styleEntry
)
{
	ApplyIconDefaults(p_createParams);
	ApplyIconDefaults(p_createParams->m_prevButtonParams);
	ApplyIconDefaults(p_createParams->m_nextButtonParams);
	ApplyWidgetDefaults(p_createParams->m_frameParams);

	p_createParams->m_prevButtonParams->m_startEnabled = p_createParams->m_startEnabled;
	p_createParams->m_nextButtonParams->m_startEnabled = p_createParams->m_startEnabled;
	p_createParams->m_prevButtonParams->m_iconEventHandler = NULL;
	p_createParams->m_nextButtonParams->m_iconEventHandler = NULL;

	for (LegoS32 i = 0; i < 6; i++) {
		if (!p_createParams->m_prevButtonParams->m_stateImages[i]) {
			p_createParams->m_prevButtonParams->m_stateImages[i] = p_styleEntry->GetPrevButtonStyle()->m_stateImages[i];
		}

		if (!p_createParams->m_nextButtonParams->m_stateImages[i]) {
			p_createParams->m_nextButtonParams->m_stateImages[i] = p_styleEntry->GetNextButtonStyle()->m_stateImages[i];
		}
	}

	LegoS32 count = 8;
	do {
		if (!p_createParams->m_frameParams->m_images[6]) {
			p_createParams->m_frameParams->m_images[6] = p_styleEntry->m_frameStyle->m_images[6];
		}
	} while (--count);

	if (!(p_createParams->m_frameParams->m_flags & 2) && p_styleEntry->m_frameStyle->m_hasColors) {
		p_createParams->m_frameParams->m_fillColor = p_styleEntry->m_frameStyle->m_color1;
	}
}

// FUNCTION: LEGORACERS 0x0046bc90
void MenuScreen::ApplyCompositeDefaults(
	MenuInputBindingTable::CompositeBinding* p_createParams,
	MenuStyleTable::CompositeStyle* p_styleEntry
)
{
	ApplyIconDefaults(p_createParams);
	ApplyIconDefaults(p_createParams->m_prevButtonParams);
	ApplyIconDefaults(p_createParams->m_nextButtonParams);
	ApplyWidgetDefaults(p_createParams->m_trackParams);
	ApplyWidgetDefaults(p_createParams->m_thumbParams);

	p_createParams->m_prevButtonParams->m_startEnabled = p_createParams->m_startEnabled;
	p_createParams->m_prevButtonParams->m_iconEventHandler = NULL;
	p_createParams->m_nextButtonParams->m_startEnabled = p_createParams->m_startEnabled;
	p_createParams->m_nextButtonParams->m_iconEventHandler = NULL;

	for (LegoS32 i = 0; i < 6; i++) {
		if (!p_createParams->m_prevButtonParams->m_stateImages[i]) {
			p_createParams->m_prevButtonParams->m_stateImages[i] = p_styleEntry->GetPrevButtonStyle()->m_stateImages[i];
		}

		if (!p_createParams->m_nextButtonParams->m_stateImages[i]) {
			p_createParams->m_nextButtonParams->m_stateImages[i] = p_styleEntry->GetNextButtonStyle()->m_stateImages[i];
		}
	}

	if (!p_createParams->m_trackParams->m_image) {
		p_createParams->m_trackParams->m_image = p_styleEntry->m_trackStyle->m_image;
	}

	if (!p_createParams->m_thumbParams->m_image) {
		p_createParams->m_thumbParams->m_image = p_styleEntry->m_thumbStyle->m_image;
	}
}

// FUNCTION: LEGORACERS 0x0046bd80
void* MenuScreen::GetStyleEntry(undefined2 p_source)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_source);
	string.CopyToBuf8(name);
	return GetActiveStyles()->FindStyle(name);
}

// FUNCTION: LEGORACERS 0x0046be10
void* MenuScreen::GetBindingEntry(undefined2 p_source)
{
	GolString string;
	GolName name;

	m_menuNameStrings->CopyStringByIndex(&string, p_source);
	string.CopyToBuf8(name);
	return GetMenuInputBindings()->ResolveEntryByName(name);
}

// FUNCTION: LEGORACERS 0x0046bea0
LegoBool32 MenuScreen::CreateTriangle(MenuTriangle* p_source, undefined2 p_event)
{
	MenuInputBindingTable::RegionBinding* sourceParams =
		static_cast<MenuInputBindingTable::RegionBinding*>(GetBindingEntry(p_event));
	if (sourceParams == NULL) {
		return FALSE;
	}

	MenuInputBindingTable::RegionBinding createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	return p_source->Create(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bef0
LegoBool32 MenuScreen::CreateImage(MenuImage* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuInputBindingTable::ImageBinding* sourceParams = GetImageBinding(p_event);
	MenuStyleTable::ImageStyle* styleEntry = GetImageStyle(p_styleId);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuImage::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	if (!createParams.m_image) {
		createParams.m_image = styleEntry->m_image;
	}

	if (!(createParams.m_flags & 2) && styleEntry->m_hasColor) {
		createParams.m_image = styleEntry->m_image;
	}

	return p_source->Create(&createParams);
}

// FUNCTION: LEGORACERS 0x0046bf80
LegoBool32 MenuScreen::CreateTextLabel(
	MenuTextLabel* p_source,
	undefined2 p_event,
	undefined2 p_styleId,
	undefined2 p_stringId
)
{
	MenuTextLabel::CreateParams* sourceParams = static_cast<MenuTextLabel::CreateParams*>(GetBindingEntry(p_event));
	MenuStyleTable::TextStyle* styleEntry = static_cast<MenuStyleTable::TextStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuTextLabel::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);
	createParams.m_stringId = p_stringId;

	if (!createParams.m_stringTable) {
		createParams.m_stringTable = m_menuTextStrings;
	}

	if (!createParams.m_wrapWidth && styleEntry->m_wrapWidth) {
		createParams.m_wrapWidth = styleEntry->m_wrapWidth;
	}

	if (!createParams.m_font) {
		createParams.m_font = styleEntry->m_font;
	}

	if (styleEntry->m_hasColor && !(createParams.m_flags & 2)) {
		createParams.m_color = styleEntry->m_color;
	}

	return p_source->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c050
LegoBool32 MenuScreen::CreateFrame(MenuFrame* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuInputBindingTable::FrameBinding* sourceParams =
		static_cast<MenuInputBindingTable::FrameBinding*>(GetBindingEntry(p_event));
	MenuStyleTable::FrameStyle* styleEntry = static_cast<MenuStyleTable::FrameStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuFrame::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	for (LegoS32 i = 0; i < 8; i++) {
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_images[i];
		}
		if (!createParams.m_images[i]) {
			createParams.m_images[i] = styleEntry->m_images[i];
		}
	}

	if (!(sourceParams->m_flags & 2) && styleEntry->m_hasColors) {
		createParams.m_color = styleEntry->m_color0;
		createParams.m_fillColor = styleEntry->m_color1;
	}

	return p_source->Create(&createParams);
}

// FUNCTION: LEGORACERS 0x0046c110
LegoBool32 MenuScreen::CreateButton(MenuButton* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuButton::CreateParams* sourceParams = static_cast<MenuButton::CreateParams*>(GetBindingEntry(p_event));
	MenuStyleTable::ButtonStyle* styleEntry = static_cast<MenuStyleTable::ButtonStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuButton::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	for (LegoS32 i = 0; i < 6; i++) {
		if (!createParams.m_stateImages[i]) {
			createParams.m_stateImages[i] = styleEntry->m_stateImages[i];
		}
	}

	return p_source->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c1b0
LegoBool32 MenuScreen::CreateHotspotButton(MenuHotspotButton* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuHotspotButton::CreateParams* sourceParams =
		static_cast<MenuHotspotButton::CreateParams*>(GetBindingEntry(p_event));
	MenuStyleTable::HotspotStyle* styleEntry = GetHotspotStyle(p_styleId);
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuHotspotButton::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	if (!createParams.m_highlightImage) {
		createParams.m_highlightImage = styleEntry->m_image;
	}

	return p_source->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c240
LegoBool32 MenuScreen::CreateCarousel(MenuCarousel* p_source, undefined2 p_event, undefined2 p_styleId)
{
	MenuCarousel::CreateParams* sourceParams = static_cast<MenuCarousel::CreateParams*>(GetBindingEntry(p_event));
	MenuStyleTable::CarouselStyle* styleEntry = static_cast<MenuStyleTable::CarouselStyle*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry) {
		return FALSE;
	}

	MenuCarousel::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	return p_source->Create(&createParams, styleEntry);
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
	*glyph1Params = *sourceParams->m_prevButtonParams;
	*glyph2Params = *sourceParams->m_nextButtonParams;
	*tomeParams = *sourceParams->m_frameParams;

	bannerParams->m_nextButtonParams = glyph2Params;
	bannerParams->m_prevButtonParams = glyph1Params;
	bannerParams->m_frameParams = tomeParams;
	bannerParams->m_carouselWidget = p_carousel;

	ApplySelectorDefaults(bannerParams, styleEntry);

	LegoBool32 result = p_widget->Create(bannerParams, styleEntry);

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

	return p_widget->Create(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c480
LegoBool32 MenuScreen::CreateSceneView(MenuSceneView* p_source, undefined4 p_event, undefined2 p_styleId)
{
	MenuSceneView::CreateParams* sourceParams = static_cast<MenuSceneView::CreateParams*>(GetBindingEntry(p_styleId));
	if (!sourceParams) {
		return FALSE;
	}

	MenuSceneView::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);
	createParams.m_eventCode = p_event;
	createParams.m_worldScale = 1.0f;
	createParams.m_aspectScale = GetAspectScale();
	return p_source->Create(&createParams, m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x0046c510
LegoBool32 MenuScreen::CreateFramedSceneView(MenuFramedSceneView* p_source, undefined4 p_event, undefined2 p_styleId)
{
	MenuFramedSceneView::CreateParams* sourceParams =
		static_cast<MenuFramedSceneView::CreateParams*>(GetBindingEntry(p_styleId));
	if (!sourceParams) {
		return FALSE;
	}

	MenuFramedSceneView::CreateParams createParams = *sourceParams;
	ApplyWidgetDefaults(&createParams);

	if (createParams.m_unk0x84) {
		ApplyWidgetDefaults(createParams.m_unk0x84);
	}

	createParams.m_eventCode = p_event;
	createParams.m_worldScale = 1.0f;
	createParams.m_aspectScale = GetAspectScale();
	return p_source->Create(&createParams, m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x0046c5b0
undefined4 MenuScreen::CreateRegion(MenuWidget* p_source, undefined2 p_event)
{
	SceneRefBinding* params = GetSceneRefBinding(p_event);
	if (!params) {
		return 0;
	}

	SceneRefBinding createParams = *params;
	ApplyWidgetDefaults(&createParams);
	createParams.m_aspectScale = GetAspectScale();

	return static_cast<MenuSceneScreen::SceneWidget*>(p_source)->Create(&createParams, m_useBinaryFiles);
}

// FUNCTION: LEGORACERS 0x0046c610
LegoBool32 MenuScreen::CreateTextField(
	MenuTextField* p_source,
	undefined2 p_event,
	undefined2 p_styleId,
	undefined2 p_charsetStringId,
	GolString* p_initialText
)
{
	MenuTextField::CreateParams* sourceParams = static_cast<MenuTextField::CreateParams*>(GetBindingEntry(p_event));
	MenuIcon::CreateState* styleEntry = static_cast<MenuIcon::CreateState*>(GetStyleEntry(p_styleId));
	if (!sourceParams || !styleEntry || !p_charsetStringId) {
		return FALSE;
	}

	MenuTextField::CreateParams createParams = *sourceParams;
	ApplyIconDefaults(&createParams);

	if (!createParams.m_stringTable) {
		createParams.m_stringTable = m_menuTextStrings;
	}

	createParams.m_charsetStringId = p_charsetStringId;
	createParams.m_initialText = p_initialText;
	createParams.m_font = sourceParams->m_font;

	return p_source->CreateField(&createParams, styleEntry);
}

// FUNCTION: LEGORACERS 0x0046c6f0
undefined4 MenuScreen::ShowConfirmDialog(MenuIcon* p_yesIcon, MenuIcon* p_noIcon, undefined2 p_notifyId)
{
	MenuDialog::DialogScreen* entry = m_dialog->OpenDialog(2, p_notifyId, this, 0);
	entry->SetYesIcon(p_yesIcon);
	entry->SetNoIcon(p_noIcon);
	entry->Open();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c730
undefined4 MenuScreen::ShowPopupDialog(MenuIcon* p_icon, undefined2 p_notifyId)
{
	MenuDialog::DialogScreen* entry = m_dialog->OpenDialog(1, p_notifyId, this, 0);
	entry->SetPopupIcon(p_icon);
	entry->Open();

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c760
void MenuScreen::DetachAllWidgets()
{
	MenuIcon* icon;
	MenuWidget* node;

	while (m_rootIcon.GetFirstChild()) {
		icon = &m_rootIcon;

		while (icon->GetFirstChild()) {
			icon = icon->GetFirstChild();
		}

		icon->DetachFromParent();
	}

	while (static_cast<MenuWidget*>(&m_rootIcon)->GetFirstChild()) {
		node = &m_rootIcon;

		while (node->GetFirstChild()) {
			node = node->GetFirstChild();
		}

		node->RemoveFromParent();
	}
}

// FUNCTION: LEGORACERS 0x0046c7d0
LegoBool32 MenuScreen::Update(undefined4)
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c7e0 FOLDED
LegoBool32 MenuScreen::Draw(Rect* p_arg1, Rect* p_arg2)
{
	m_rootIcon.Draw(p_arg1, p_arg2);
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046c810
MenuStyleTable* MenuScreen::GetMenuStyles()
{
	return &m_styleTable;
}

// FUNCTION: LEGORACERS 0x0046c820 FOLDED
MenuStyleTable* MenuScreen::GetActiveStyles()
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
	return &m_bindingTable;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// The pragma code_seg prevents this trivial body from folding with identical functions elsewhere.

// FUNCTION: LEGORACERS 0x0046c850
#pragma code_seg(".text$menuscreen_vt6c")
LegoFloat MenuScreen::GetAspectScale()
{
	return 1.0f;
}
#pragma code_seg()

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 MenuScreen::OnWidgetKeyUp(MenuWidget*, void*, undefined4, undefined4)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
LegoBool32 MenuScreen::HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
LegoBool32 MenuScreen::HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4)
{
	return FALSE;
}

// FUNCTION: LEGORACERS 0x0046c860 FOLDED
undefined4 MenuScreen::OnWidgetKeyDown(MenuWidget*, void*, undefined4, undefined4)
{
	return 0;
}
