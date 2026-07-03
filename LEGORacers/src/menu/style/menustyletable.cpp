#include "menu/style/menustyletable.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "goltxtparser.h"
#include "menu/style/menubindingtoken.h"
#include "menu/style/sharedmenustyletable.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(MenuStyleTable, 0x4c)
DECOMP_SIZE_ASSERT(MenuStyleTable::ImageStyle, 0x0c)
DECOMP_SIZE_ASSERT(MenuStyleTable::TextStyle, 0x14)
DECOMP_SIZE_ASSERT(MenuStyleTable::CarouselStyle, 0x18)
DECOMP_SIZE_ASSERT(MenuStyleTable::FrameStyle, 0x2c)
DECOMP_SIZE_ASSERT(MenuStyleTable::IconStyle, 0x90)
DECOMP_SIZE_ASSERT(MenuStyleTable::SelectorStyleBase, 0x98)
DECOMP_SIZE_ASSERT(MenuStyleTable::ButtonStyle, 0xa8)
DECOMP_SIZE_ASSERT(MenuStyleTable::MultiStateStyle, 0x100)
DECOMP_SIZE_ASSERT(MenuStyleTable::TextButtonStyle, 0x104)
DECOMP_SIZE_ASSERT(MenuStyleTable::HotspotStyle, 0x150)
DECOMP_SIZE_ASSERT(MenuStyleTable::SelectorStyle, 0xbc)
DECOMP_SIZE_ASSERT(MenuStyleTable::CompositeStyle, 0xbc)
DECOMP_SIZE_ASSERT(MenuStyleTable::ResourceLoadParams, 0x10)

// FUNCTION: LEGORACERS 0x0046fa50
MenuStyleTable::MenuStyleTable()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046fac0
MenuStyleTable::~MenuStyleTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0046fb10
void MenuStyleTable::Reset()
{
	m_fallback = 0;
	m_imageStyles = NULL;
	m_textStyles = NULL;
	m_frameStyles = NULL;
	m_buttonStyles = NULL;
	m_multiStateStyles = NULL;
	m_hotspotStyles = NULL;
	m_carouselStyles = NULL;
	m_selectorStyles = NULL;
	m_compositeStyles = NULL;
	m_iconStyles = NULL;

	MenuResourceTable::Reset();
}

// FUNCTION: LEGORACERS 0x0046fb40
LegoBool32 MenuStyleTable::Load(ResourceLoadParams* p_params)
{
	Clear();
	m_renderer = p_params->m_renderer;
	m_fallback = p_params->m_fallback;

	if (BeginLoad()) {
		ParseFile(p_params);
	}

	return m_nameEntries != NULL;
}

// FUNCTION: LEGORACERS 0x0046fb80
void MenuStyleTable::Clear()
{
	if (m_nameEntries == NULL) {
		return;
	}

	if (m_imageStyles) {
		delete[] m_imageStyles;
	}
	if (m_textStyles) {
		delete[] m_textStyles;
	}
	if (m_frameStyles) {
		delete[] m_frameStyles;
	}
	if (m_buttonStyles) {
		delete[] m_buttonStyles;
	}
	if (m_multiStateStyles) {
		delete[] m_multiStateStyles;
	}
	if (m_hotspotStyles) {
		delete[] m_hotspotStyles;
	}
	if (m_carouselStyles) {
		delete[] m_carouselStyles;
	}
	if (m_selectorStyles) {
		delete[] m_selectorStyles;
	}
	if (m_compositeStyles) {
		delete[] m_compositeStyles;
	}
	if (m_iconStyles) {
		delete[] m_iconStyles;
	}

	MenuResourceTable::Clear();
}

// FUNCTION: LEGORACERS 0x0046fc40
void MenuStyleTable::CreateParser(undefined4 p_param)
{
	if (p_param) {
		// TODO: Subclass of GolFileParser. GolFormatParser?
		m_parser = new GolBinParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".msb");
		return;
	}

	m_parser = new GolTxtParser();
	if (m_parser == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
}

// FUNCTION: LEGORACERS 0x0046fd30
void MenuStyleTable::ParseFile(ResourceLoadParams* p_params)
{
	CreateParser(p_params->m_binary);
	m_parser->OpenFileForRead(p_params->m_fileName);
	ReadHeader();
	ParseSections();
	m_parser->Dispose();

	delete m_parser;
}

// FUNCTION: LEGORACERS 0x0046fd80
void MenuStyleTable::ParseSection(undefined4 p_arg1)
{
	switch (p_arg1) {
	case 0x32:
		LoadImageStyles();
		break;
	case 0x33:
		LoadTextStyles();
		break;
	case 0x34:
		LoadFrameStyles();
		break;
	case 0x35:
		LoadButtonStyles();
		break;
	case 0x36:
		LoadMultiStateStyles();
		break;
	case 0x37:
		LoadHotspotStyles();
		break;
	case 0x38:
		LoadCarouselStyles();
		break;
	case 0x39:
		LoadSelectorStyles();
		break;
	case 0x3a:
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case 0x3b:
		LoadCompositeStyles();
		break;
	case 0x3d:
		LoadIconStyles();
		break;
	}
}

// FUNCTION: LEGORACERS 0x0046fe20
void MenuStyleTable::ParseImageStyle(ImageStyle* p_entry)
{
	p_entry->m_color.m_packed = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case c_styleImage:
			p_entry->m_image = m_renderer->FindImageByName(m_parser->ReadString());
			break;
		case c_styleColors:
			ReadVisualState(p_entry->m_color.m_bytes);
			p_entry->m_hasColor = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046feb0
void MenuStyleTable::ParseTextStyle(TextStyle* p_entry)
{
	p_entry->m_color.m_packed = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case c_styleFont:
			p_entry->m_font = m_renderer->FindFontByName(m_parser->ReadString());
			break;
		case TextStyle::e_centered:
			p_entry->m_centered = m_parser->ReadInteger();
			break;
		case c_styleColors:
			ReadVisualState(p_entry->m_color.m_bytes);
			p_entry->m_hasColor = TRUE;
			break;
		case TextStyle::e_wrapWidth:
			p_entry->m_wrapWidth = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046ff70
void MenuStyleTable::ParseFrameStyle(FrameStyle* p_entry)
{
	p_entry->m_color1.m_packed = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleImage:
			for (i = 0; i < 8; i++) {
				p_entry->m_images[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		case c_styleColors:
			ReadVisualState(p_entry->m_color0.m_bytes);
			ReadVisualState(p_entry->m_color1.m_bytes);
			p_entry->m_hasColors = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470020
void MenuStyleTable::ParseIconStyle(IconStyle* p_entry)
{
	::memset(p_entry->m_iconStateColors, 0xff, sizeof(p_entry->m_iconStateColors));

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case IconStyle::e_transitionDurationMs:
			p_entry->m_transitionDurationMs = m_parser->ReadInteger();
			break;
		case c_styleSounds:
			for (i = 0; i < 5; i++) {
				p_entry->m_iconSoundIds[i] = m_parser->ReadInteger();
			}
			p_entry->m_hasSoundIds = TRUE;
			break;
		case IconStyle::e_stateRects:
			for (i = 0; i < 6; i++) {
				ReadRect(&p_entry->m_stateRects[i].m_left);
			}
			break;
		case c_styleColors:
			for (i = 0; i < 6; i++) {
				ReadVisualState(p_entry->m_iconStateColors[i].m_bytes);
			}
			p_entry->m_hasStateColors = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470110
void MenuStyleTable::ParseButtonStyle(ButtonStyle* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleImage:
			for (i = 0; i < 6; i++) {
				p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
			}
			break;
		case c_styleIcon:
			ParseIconStyle(p_entry);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004701a0
void MenuStyleTable::ParseMultiStateStyle(MultiStateStyle* p_entry)
{
	LegoS32 imageTripletCount = 0;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	if (m_parser->GetNextToken() == GolFileParser::e_rightCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		return;
	}

	GolImage** image = &p_entry->m_stateImages[0][0];
	do {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleIcon:
			ParseIconStyle(p_entry);
			break;
		case MultiStateStyle::e_rect:
			ReadRect(&p_entry->m_rect.m_left);
			break;
		case c_styleFont:
			for (i = 0; i < 6; i++) {
				p_entry->m_stateFonts[i] = m_renderer->FindFontByName(m_parser->ReadString());
			}
			break;
		case c_styleImage: {
			GolImage** imageCursor = image;
			for (i = 0; i < 6; i++) {
				*imageCursor = m_renderer->FindImageByName(m_parser->ReadString());
				imageCursor += 3;
			}
			imageTripletCount++;
			image++;
			break;
		}
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	} while (m_parser->GetNextToken() != GolFileParser::e_rightCurly);

	if (imageTripletCount != 3) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004702e0
void MenuStyleTable::ParseHotspotStyle(HotspotStyle* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleIcon:
			ParseIconStyle(p_entry);
			break;
		case HotspotStyle::e_hotspotCount:
			p_entry->m_hotspotCount = m_parser->ReadInteger();
			break;
		case HotspotStyle::e_hotspotIds:
			for (i = 0; i < p_entry->m_hotspotCount; i++) {
				p_entry->m_hotspotIds[i] = m_parser->ReadInteger();
			}
			break;
		case HotspotStyle::e_hotspotRects:
			for (i = 0; i < p_entry->m_hotspotCount; i++) {
				ReadRect(&p_entry->m_hotspotRects[i].m_left);
			}
			break;
		case c_styleImage:
			p_entry->m_image = m_renderer->FindImageByName(m_parser->ReadString());
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470410
void MenuStyleTable::ParseCarouselStyle(CarouselStyle* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case c_styleSounds:
			for (i = 0; i < 3; i++) {
				p_entry->m_soundIds[i] = m_parser->ReadInteger();
			}
			break;
		case CarouselStyle::e_scrollDurationMs:
			p_entry->m_scrollDurationMs = m_parser->ReadInteger();
			break;
		case CarouselStyle::e_pageMode:
			p_entry->m_pageMode = m_parser->ReadInteger();
			p_entry->m_wrap = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004704b0
void MenuStyleTable::ParseSelectorStyle(SelectorStyle* p_entry)
{
	LegoBool readBase = FALSE;
	LegoBool readSingle = FALSE;
	LegoBool readPair = FALSE;
	VisualStateColor* visualState;
	LegoS32 i;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	::memset(p_entry->m_itemColors, 0xff, sizeof(p_entry->m_itemColors));
	::memset(p_entry->m_focusedItemColors, 0xff, sizeof(p_entry->m_focusedItemColors));

	if (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		do {
			switch (m_parser->GetCurrentToken()) {
			case c_styleIcon:
				ParseIconStyle(p_entry);
				readBase++;
				break;
			case c_styleBlockButton:
				p_entry->m_prevButtonStyle = static_cast<ButtonStyle*>(FindStyle(m_parser->ReadString()));
				p_entry->m_nextButtonStyle = static_cast<ButtonStyle*>(FindStyle(m_parser->ReadString()));
				readPair++;
				break;
			case c_styleBlockFrame:
				p_entry->m_frameStyle = static_cast<FrameStyle*>(FindStyle(m_parser->ReadString()));
				readSingle++;
				break;
			case c_styleColors:
				visualState = p_entry->m_itemColors;
				i = 4;
				do {
					ReadVisualState(visualState->m_bytes);
					visualState++;
				} while (--i);

				visualState = p_entry->m_focusedItemColors;
				i = 4;
				do {
					ReadVisualState(visualState->m_bytes);
					visualState++;
				} while (--i);
				break;
			default:
				m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
				break;
			}
		} while (m_parser->GetNextToken() != GolFileParser::e_rightCurly);
	}

	if (!readSingle || !readBase || !readPair) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x00470650
void MenuStyleTable::ParseCompositeStyle(CompositeStyle* p_entry)
{
	LegoBool readBase = FALSE;
	LegoBool readSecondaryPair = FALSE;
	LegoBool readPrimaryPair = FALSE;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	if (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		do {
			LegoS32 i;

			switch (m_parser->GetCurrentToken()) {
			case c_styleIcon:
				ParseIconStyle(p_entry);
				readBase++;
				break;
			case c_styleBlockButton:
				p_entry->m_prevButtonStyle = static_cast<IconStyle*>(FindStyle(m_parser->ReadString()));
				p_entry->m_nextButtonStyle = static_cast<IconStyle*>(FindStyle(m_parser->ReadString()));
				readPrimaryPair++;
				break;
			case c_styleBlockImage:
				p_entry->m_trackStyle = static_cast<ImageStyle*>(FindStyle(m_parser->ReadString()));
				p_entry->m_thumbStyle = static_cast<ImageStyle*>(FindStyle(m_parser->ReadString()));
				readSecondaryPair++;
				break;
			case c_styleImage:
				for (i = 0; i < 6; i++) {
					p_entry->m_stateImages[i] = m_renderer->FindImageByName(m_parser->ReadString());
				}
				break;
			case c_styleSounds:
				p_entry->m_stepSoundIds.m_first = m_parser->ReadInteger();
				p_entry->m_stepSoundIds.m_second = m_parser->ReadInteger();
				break;
			default:
				m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
				break;
			}
		} while (m_parser->GetNextToken() != GolFileParser::e_rightCurly);
	}

	if (!readSecondaryPair || !readBase || !readPrimaryPair) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004707e0
void MenuStyleTable::LoadImageStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_imageStyles = new ImageStyle[entryCount];
	::memset(m_imageStyles, 0, sizeof(ImageStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockImage) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_imageStyles[i]);
		ParseImageStyle(&m_imageStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470880
void MenuStyleTable::LoadTextStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_textStyles = new TextStyle[entryCount];
	::memset(m_textStyles, 0, sizeof(TextStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockText) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_textStyles[i]);
		ParseTextStyle(&m_textStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470920
void MenuStyleTable::LoadFrameStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_frameStyles = new FrameStyle[entryCount];
	::memset(m_frameStyles, 0, sizeof(FrameStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockFrame) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_frameStyles[i]);
		ParseFrameStyle(&m_frameStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x004709c0
void MenuStyleTable::LoadButtonStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_buttonStyles = new ButtonStyle[entryCount];
	::memset(m_buttonStyles, 0, sizeof(ButtonStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockButton) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_buttonStyles[i]);
		ParseButtonStyle(&m_buttonStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470a70
void MenuStyleTable::LoadMultiStateStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_multiStateStyles = new MultiStateStyle[entryCount];
	::memset(m_multiStateStyles, 0, sizeof(MultiStateStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockMultiState) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_multiStateStyles[i]);
		ParseMultiStateStyle(&m_multiStateStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470b10
void MenuStyleTable::LoadHotspotStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_hotspotStyles = new HotspotStyle[entryCount];
	::memset(m_hotspotStyles, 0, sizeof(HotspotStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockHotspot) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_hotspotStyles[i]);
		ParseHotspotStyle(&m_hotspotStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470bc0
void MenuStyleTable::LoadCarouselStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_carouselStyles = new CarouselStyle[entryCount];
	::memset(m_carouselStyles, 0, sizeof(CarouselStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockCarousel) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_carouselStyles[i]);
		ParseCarouselStyle(&m_carouselStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470c60
void MenuStyleTable::LoadSelectorStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_selectorStyles = new SelectorStyle[entryCount];
	::memset(m_selectorStyles, 0, sizeof(SelectorStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockSelector) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_selectorStyles[i]);
		ParseSelectorStyle(&m_selectorStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470d10
void MenuStyleTable::LoadCompositeStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_compositeStyles = new CompositeStyle[entryCount];
	::memset(m_compositeStyles, 0, sizeof(CompositeStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleBlockComposite) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_compositeStyles[i]);
		ParseCompositeStyle(&m_compositeStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470dc0
void MenuStyleTable::LoadIconStyles()
{
	LegoS32 entryCount = ReadSectionCount();
	m_iconStyles = new IconStyle[entryCount];
	::memset(m_iconStyles, 0, sizeof(IconStyle) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != c_styleIcon) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_iconStyles[i]);
		ParseIconStyle(&m_iconStyles[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470e60
void* MenuStyleTable::FindStyle(const LegoChar* p_name)
{
	GolName name;

	::strncpy(name, p_name, sizeof(name));

	void* result = GetName(name);
	if (!result && m_fallback) {
		return m_fallback->FindStyle(p_name);
	}

	return result;
}
