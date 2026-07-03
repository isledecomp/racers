#include "menu/style/menuinputbindingtable.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "menu/style/menubindingtoken.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuInputBindingTable, 0x5c)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::RegionBinding, 0x38)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::ImageBinding, 0x3c)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::TextLabelBinding, 0x48)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::FrameBinding, 0x60)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::IconBinding, 0x84)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::SceneBinding, 0x88)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::SelectorBinding, 0x98)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::ButtonBinding, 0x9c)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::HotspotBinding, 0xa0)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::TextFieldBinding, 0xa0)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::CompositeBinding, 0xb8)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::MultiStateBinding, 0xec)
DECOMP_SIZE_ASSERT(SceneRefBinding, 0x54)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::MidTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::ResourceLoadParams, 0x0c)
DECOMP_SIZE_ASSERT(MenuInputBindingTable::ModelCarouselBinding, 0x74)

// FUNCTION: LEGORACERS 0x004695b0
MenuInputBindingTable::MenuInputBindingTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00469620
MenuInputBindingTable::~MenuInputBindingTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00469670
void MenuInputBindingTable::Reset()
{
	m_nextWidgetId = 2;
	m_regionBindings = 0;
	m_imageBindings = 0;
	m_textLabelBindings = 0;
	m_frameBindings = 0;
	m_buttonBindings = 0;
	m_multiStateBindings = 0;
	m_hotspotBindings = 0;
	m_selectorBindings = 0;
	m_modelCarouselBindings = 0;
	m_compositeBindings = 0;
	m_sceneBindings = 0;
	m_textFieldBindings = 0;
	m_sceneRefBindings = 0;
	MenuResourceTable::Reset();
}

// FUNCTION: LEGORACERS 0x004696b0
LegoBool32 MenuInputBindingTable::Load(ResourceLoadParams* p_params)
{
	Clear();
	m_renderer = p_params->m_renderer;

	if (BeginLoad()) {
		ParseFile(p_params);
	}

	return m_nameEntries != NULL;
}

// FUNCTION: LEGORACERS 0x004696f0
void MenuInputBindingTable::Clear()
{
	if (m_nameEntries == NULL) {
		return;
	}

	if (m_regionBindings) {
		delete[] m_regionBindings;
	}
	if (m_imageBindings) {
		delete[] m_imageBindings;
	}
	if (m_textLabelBindings) {
		delete[] m_textLabelBindings;
	}
	if (m_frameBindings) {
		delete[] m_frameBindings;
	}
	if (m_buttonBindings) {
		delete[] m_buttonBindings;
	}
	if (m_multiStateBindings) {
		delete[] m_multiStateBindings;
	}
	if (m_hotspotBindings) {
		delete[] m_hotspotBindings;
	}
	if (m_selectorBindings) {
		delete[] m_selectorBindings;
	}
	if (m_modelCarouselBindings) {
		for (LegoS32 i = 0; i < m_entryCount; i++) {
			delete[] m_modelCarouselBindings[i].m_slotRects;
		}

		delete[] m_modelCarouselBindings;
	}
	if (m_compositeBindings) {
		delete[] m_compositeBindings;
	}
	if (m_sceneBindings) {
		delete[] m_sceneBindings;
	}
	if (m_textFieldBindings) {
		delete[] m_textFieldBindings;
	}
	if (m_sceneRefBindings) {
		delete[] m_sceneRefBindings;
	}

	MenuResourceTable::Clear();
}

// FUNCTION: LEGORACERS 0x00469810
void MenuInputBindingTable::CreateParser(undefined4 p_param)
{
	if (p_param) {
		m_parser = new GolBinParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".mib");
		return;
	}

	m_parser = new MidTxtParser();
	if (m_parser == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x00469900
void MenuInputBindingTable::ParseFile(ResourceLoadParams* p_params)
{
	CreateParser(p_params->m_binary);
	m_parser->OpenFileForRead(p_params->m_fileName);
	ReadHeader();
	ParseSections();
	m_parser->Dispose();

	delete m_parser;
}

// FUNCTION: LEGORACERS 0x00469950
void MenuInputBindingTable::ParseSection(undefined4 p_arg1)
{
	switch (p_arg1) {
	case c_blockRegion:
		ParseRegionBindings();
		break;
	case c_blockImage:
		ParseImageBindings();
		break;
	case c_blockTextLabel:
		ParseTextLabelBindings();
		break;
	case c_blockFrame:
		ParseFrameBindings();
		break;
	case c_blockButton:
		ParseButtonBindings();
		break;
	case c_blockMultiState:
		ParseMultiStateBindings();
		break;
	case c_blockHotspot:
		ParseHotspotBindings();
		break;
	case c_blockSelector:
		ParseSelectorBindings();
		break;
	case c_blockModelCarousel:
		ParseModelCarouselBindings();
		break;
	case c_blockComposite:
		ParseCompositeBindings();
		break;
	case 0x41:
	case 0x44:
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case c_blockScene:
		ParseSceneBindings();
		break;
	case c_blockTextField:
		ParseTextFieldBindings();
		break;
	case c_blockSceneRef:
		ParseSceneRefBindings();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00469a20
void MenuInputBindingTable::ParseWidgetBase(MenuWidget::CreateParams* p_entry)
{
	VisualStateColor* visualState = &p_entry->m_color;
	visualState->m_packed = -1;

	LegoU8 flags = p_entry->m_flags;
	flags |= 1;
	p_entry->m_flags = flags;
	p_entry->m_id = m_nextWidgetId++;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_rect:
			ReadRect(&p_entry->m_rect.m_left);
			break;
		case MidTxtParser::e_id: {
			LegoS32 value = m_parser->ReadInteger();
			p_entry->m_id = value;
			m_nextWidgetId = value + 1;
			break;
		}
		case MidTxtParser::e_attachToParent: {
			LegoU8 value = m_parser->ReadInteger();
			LegoU8 flags = p_entry->m_flags;
			LegoU8 newFlags = flags;
			newFlags ^= value;
			newFlags &= 1;
			newFlags ^= flags;
			p_entry->m_flags = newFlags;
			break;
		}
		case MidTxtParser::e_name:
			::strncpy(p_entry->m_name, m_parser->ReadString(), 8);
			break;
		case MidTxtParser::e_colors:
			ReadVisualState(visualState->m_bytes);
			p_entry->m_flags |= 2;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469b20
void MenuInputBindingTable::InitIconDefaults(MenuIcon::CreateParams* p_entry)
{
	p_entry->m_startEnabled = TRUE;
	p_entry->m_attachToParent = TRUE;
	::memset(p_entry->m_iconStateColors, 0xff, sizeof(p_entry->m_iconStateColors));
}

// FUNCTION: LEGORACERS 0x00469b50
void MenuInputBindingTable::ParseIconField(MenuIcon::CreateParams* p_entry)
{
	switch (m_parser->GetCurrentToken()) {
	case MidTxtParser::e_widget:
		ParseWidgetBase(p_entry);
		return;
	case MidTxtParser::e_value:
		p_entry->m_startEnabled = m_parser->ReadInteger();
		return;
	case MidTxtParser::e_attachToParent:
		p_entry->m_attachToParent = m_parser->ReadInteger();
		return;
	case MidTxtParser::e_name:
		::strncpy(p_entry->m_name, m_parser->ReadString(), 8);
		return;
	case MidTxtParser::e_unknown0x34:
		p_entry->m_unk0x3c = m_parser->ReadInteger();
		return;
	case MidTxtParser::e_helpStringId:
		p_entry->m_helpStringId = m_parser->ReadInteger();
		return;
	case MidTxtParser::e_colors: {
		for (LegoS32 i = 0; i < 6; i++) {
			ReadVisualState(p_entry->m_iconStateColors[i].m_bytes);
		}
		p_entry->m_hasStateColors = TRUE;
		return;
	}
	case MidTxtParser::e_soundIds: {
		for (LegoS32 i = 0; i < 5; i++) {
			p_entry->m_soundIds[i] = m_parser->ReadInteger();
		}
		p_entry->m_hasSoundIds = TRUE;
		return;
	}
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00469c90
void MenuInputBindingTable::ParseSelectorField(SelectorBinding* p_entry)
{
	switch (m_parser->GetCurrentToken()) {
	case MidTxtParser::e_button:
		p_entry->m_prevButtonParams =
			static_cast<MenuButton::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
		p_entry->m_nextButtonParams =
			static_cast<MenuButton::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
		return;
	case MidTxtParser::e_bindingRef:
		p_entry->m_frameParams = static_cast<MenuFrame::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
		return;
	case MidTxtParser::e_value:
		p_entry->m_acceptUnfocusedInput = m_parser->ReadInteger();
		return;
	default:
		ParseIconField(p_entry);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00469d20
void MenuInputBindingTable::ReadNineFloats(LegoFloat* p_floats)
{
	p_floats[0] = m_parser->ReadFloat();
	p_floats[1] = m_parser->ReadFloat();
	p_floats[2] = m_parser->ReadFloat();
	p_floats[3] = m_parser->ReadFloat();
	p_floats[4] = m_parser->ReadFloat();
	p_floats[5] = m_parser->ReadFloat();
	p_floats[6] = m_parser->ReadFloat();
	p_floats[7] = m_parser->ReadFloat();
	p_floats[8] = m_parser->ReadFloat();
}

// FUNCTION: LEGORACERS 0x00469d90
void MenuInputBindingTable::ParseImageBinding(ImageBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_image:
			p_entry->m_image = m_renderer->FindImageByName(m_parser->ReadString());
			break;
		case MidTxtParser::e_colors:
			ReadVisualState(p_entry->m_color.m_bytes);
			p_entry->m_flags |= 2;
			break;
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469e20
void MenuInputBindingTable::ParseTextLabelBinding(TextLabelBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_font:
			p_entry->m_font = m_renderer->FindFontByName(m_parser->ReadString());
			// Fall through.
		case MidTxtParser::e_colors:
			ReadVisualState(p_entry->m_color.m_bytes);
			p_entry->m_flags |= 2;
			break;
		case MidTxtParser::e_value:
			p_entry->m_wrapWidth = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469ee0
void MenuInputBindingTable::ParseFrameBinding(FrameBinding* p_entry)
{
	p_entry->m_hasFillColor = TRUE;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_value:
			p_entry->m_hasFillColor = m_parser->ReadInteger();
			break;
		case MidTxtParser::e_image: {
			for (LegoS32 i = 0; i < 8; i++) {
				p_entry->m_images[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case MidTxtParser::e_colors:
			ReadVisualState(p_entry->m_color.m_bytes);
			ReadVisualState(p_entry->m_fillColor.m_bytes);
			p_entry->m_flags |= 2;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469fd0
void MenuInputBindingTable::ParseButtonBinding(ButtonBinding* p_entry)
{
	InitIconDefaults(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		if (m_parser->GetCurrentToken() != MidTxtParser::e_image) {
			ParseIconField(p_entry);
		}
		else {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a050
void MenuInputBindingTable::ParseMultiStateBinding(MultiStateBinding* p_entry)
{
	InitIconDefaults(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	if (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		GolImage** image = &p_entry->m_stateImages[0][0];
		do {
			switch (m_parser->GetCurrentToken()) {
			case MidTxtParser::e_image: {
				GolImage** imageCursor = image;
				for (LegoS32 i = 0; i < 6; i++) {
					*imageCursor = m_renderer->FindImageByName(m_parser->ReadString());
					imageCursor += 3;
				}
				image++;
				break;
			}
			case MidTxtParser::e_font: {
				for (LegoS32 i = 0; i < 6; i++) {
					p_entry->m_stateFonts[i] = m_renderer->FindFontByName(m_parser->ReadString());
				}
				break;
			}
			default:
				ParseIconField(p_entry);
				break;
			}
		} while (m_parser->GetNextToken() != GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0046a110
void MenuInputBindingTable::ParseHotspotBinding(HotspotBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	InitIconDefaults(p_entry);
	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_image:
			p_entry->m_highlightImage = m_renderer->FindImageByName(m_parser->ReadString());
			break;
		case MidTxtParser::e_button:
			ParseButtonBinding(p_entry);
			break;
		default:
			ParseIconField(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a190
void MenuInputBindingTable::ParseSelectorBinding(SelectorBinding* p_entry)
{
	p_entry->m_startEnabled = TRUE;
	p_entry->m_attachToParent = TRUE;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		ParseSelectorField(p_entry);
	}
}

// FUNCTION: LEGORACERS 0x0046a1f0
void MenuInputBindingTable::ParseModelCarouselBinding(ModelCarouselBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_value:
			p_entry->m_slotCount = m_parser->ReadInteger();
			p_entry->m_focusedSlot = m_parser->ReadInteger();
			p_entry->m_scrollStep = m_parser->ReadFloat();
			break;
		case MidTxtParser::e_rect: {
			if (!p_entry->m_slotCount) {
				m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			}

			p_entry->m_slotRects = new Rect[p_entry->m_slotCount];
			if (p_entry->m_slotRects == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoS32 i = 0; i < p_entry->m_slotCount; i++) {
				ReadRect(&p_entry->m_slotRects[i].m_left);
			}
			break;
		}
		case MidTxtParser::e_camera:
			ReadNineFloats(p_entry->m_cameraVectors);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a310
void MenuInputBindingTable::ParseCompositeBinding(CompositeBinding* p_entry)
{
	InitIconDefaults(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_value:
			p_entry->m_stepCount = m_parser->ReadInteger();
			p_entry->m_initialValue = m_parser->ReadInteger();
			break;
		case MidTxtParser::e_button:
			p_entry->m_prevButtonParams =
				static_cast<MenuButton::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
			p_entry->m_nextButtonParams =
				static_cast<MenuButton::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
			break;
		case MidTxtParser::e_imageRef:
			p_entry->m_trackParams = static_cast<MenuImage::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
			p_entry->m_thumbParams = static_cast<MenuImage::CreateParams*>(ResolveEntryByName(m_parser->ReadString()));
			break;
		case MidTxtParser::e_image: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case MidTxtParser::e_soundIds:
			ParseIconField(p_entry);
			p_entry->m_stepSoundIds.m_first = m_parser->ReadInteger();
			p_entry->m_stepSoundIds.m_second = m_parser->ReadInteger();
			break;
		default:
			ParseIconField(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a490
void MenuInputBindingTable::ParseSceneBinding(SceneBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_sceneName:
			::strncpy(p_entry->m_worldName, m_parser->ReadString(), 8);
			break;
		case MidTxtParser::e_bindingRef:
			p_entry->m_linkedBinding = ResolveEntryByName(m_parser->ReadString());
			break;
		case MidTxtParser::e_camera:
			ReadNineFloats(p_entry->m_cameraVectors);
			break;
		case MidTxtParser::e_value:
			p_entry->m_drawWorld = m_parser->ReadInteger();
			p_entry->m_hasBlendedWorld = m_parser->ReadInteger();
			break;
		case MidTxtParser::e_viewportClearMode:
			p_entry->m_viewportClearMode = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a590
void MenuInputBindingTable::ParseSceneRefBinding(SceneRefBinding* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	p_entry->m_autoAdvance = 0;
	p_entry->m_startFrameIndex = 0;
	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_value:
			p_entry->m_autoAdvance = m_parser->ReadInteger();
			p_entry->m_startFrameIndex = m_parser->ReadInteger();
			break;
		case MidTxtParser::e_sceneName:
			::strncpy(p_entry->m_cutsceneName, m_parser->ReadStringWithMaxLength(8), 8);
			p_entry->m_cutsceneName[8] = 0;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a640
void MenuInputBindingTable::ParseTextFieldBinding(TextFieldBinding* p_entry)
{
	InitIconDefaults(p_entry);
	p_entry->m_maxLength = 31;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case MidTxtParser::e_widget:
			ParseWidgetBase(p_entry);
			break;
		case MidTxtParser::e_font:
			p_entry->m_font = m_renderer->FindFontByName(m_parser->ReadString());
			break;
		case MidTxtParser::e_value:
			p_entry->m_maxLength = m_parser->ReadInteger();
			break;
		case MidTxtParser::e_soundIds: {
			LegoS32 i;
			for (i = 0; i < 5; i++) {
				p_entry->m_soundIds[i] = m_parser->ReadInteger();
			}
			for (i = 0; i < 4; i++) {
				p_entry->m_editSoundIds.m_ids[i] = m_parser->ReadInteger();
			}
			p_entry->m_hasSoundIds = TRUE;
			break;
		}
		default:
			ParseIconField(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a750
void MenuInputBindingTable::ParseRegionBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_regionBindings = new RegionBinding[entryCount];
	::memset(m_regionBindings, 0, sizeof(RegionBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockRegion) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_regionBindings[i]);
		ParseWidgetBase(&m_regionBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a800
void MenuInputBindingTable::ParseImageBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_imageBindings = new ImageBinding[entryCount];
	::memset(m_imageBindings, 0, sizeof(ImageBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != MidTxtParser::e_imageRef) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_imageBindings[i]);
		ParseImageBinding(&m_imageBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a8a0
void MenuInputBindingTable::ParseTextLabelBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_textLabelBindings = new TextLabelBinding[entryCount];
	::memset(m_textLabelBindings, 0, sizeof(TextLabelBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockTextLabel) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_textLabelBindings[i]);
		ParseTextLabelBinding(&m_textLabelBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a940
void MenuInputBindingTable::ParseFrameBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_frameBindings = new FrameBinding[entryCount];
	::memset(m_frameBindings, 0, sizeof(FrameBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockFrame) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_frameBindings[i]);
		ParseFrameBinding(&m_frameBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a9e0
void MenuInputBindingTable::ParseButtonBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_buttonBindings = new ButtonBinding[entryCount];
	::memset(m_buttonBindings, 0, sizeof(ButtonBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != MidTxtParser::e_button) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_buttonBindings[i]);
		ParseButtonBinding(&m_buttonBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046aa90
void MenuInputBindingTable::ParseMultiStateBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_multiStateBindings = new MultiStateBinding[entryCount];
	::memset(m_multiStateBindings, 0, sizeof(MultiStateBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockMultiState) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_multiStateBindings[i]);
		ParseMultiStateBinding(&m_multiStateBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ab40
void MenuInputBindingTable::ParseHotspotBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_hotspotBindings = new HotspotBinding[entryCount];
	::memset(m_hotspotBindings, 0, sizeof(HotspotBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockHotspot) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_hotspotBindings[i]);
		ParseHotspotBinding(&m_hotspotBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046abe0
void MenuInputBindingTable::ParseSelectorBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_selectorBindings = new SelectorBinding[entryCount];
	::memset(m_selectorBindings, 0, sizeof(SelectorBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockSelector) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_selectorBindings[i]);
		ParseSelectorBinding(&m_selectorBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ac90
void MenuInputBindingTable::ParseModelCarouselBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_entryCount = entryCount;
	m_modelCarouselBindings = new ModelCarouselBinding[entryCount];
	::memset(m_modelCarouselBindings, 0, sizeof(ModelCarouselBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockModelCarousel) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_modelCarouselBindings[i]);
		ParseModelCarouselBinding(&m_modelCarouselBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ad40
void MenuInputBindingTable::ParseCompositeBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_compositeBindings = new CompositeBinding[entryCount];
	::memset(m_compositeBindings, 0, sizeof(CompositeBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockComposite) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_compositeBindings[i]);
		ParseCompositeBinding(&m_compositeBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046adf0
void MenuInputBindingTable::ParseSceneBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_sceneBindings = new SceneBinding[entryCount];
	::memset(m_sceneBindings, 0, sizeof(SceneBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockScene) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_sceneBindings[i]);
		ParseSceneBinding(&m_sceneBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046aea0
void MenuInputBindingTable::ParseSceneRefBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_sceneRefBindings = new SceneRefBinding[entryCount];
	::memset(m_sceneRefBindings, 0, sizeof(SceneRefBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockSceneRef) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_sceneRefBindings[i]);
		ParseSceneRefBinding(&m_sceneRefBindings[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046af50
void MenuInputBindingTable::ParseTextFieldBindings()
{
	LegoS32 entryCount = ReadSectionCount();
	m_textFieldBindings = new TextFieldBinding[entryCount];
	::memset(m_textFieldBindings, 0, sizeof(TextFieldBinding) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_blockTextField) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_textFieldBindings[i]);
		ParseTextFieldBinding(&m_textFieldBindings[i]);
	}
}
