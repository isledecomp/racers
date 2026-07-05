#include "core/gol.h"
#include "golbinparser.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golfontbase.h"
#include "material/golimagedefinitionlist.h"
// #include "race/racesession.h"
#include "race/loadingscreen.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/golrendertarget.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(LoadingScreen, 0x30)
DECOMP_SIZE_ASSERT(LoadingScreen::LsbTxtParser, 0x1fc)

// GLOBAL: LEGORACERS 0x004bed40
const LegoChar* g_loadScreenName = "loadscrn";

// FUNCTION: LEGORACERS 0x0042f3b0
LoadingScreen::LoadingScreen()
{
	m_renderer = NULL;
	m_golExport = NULL;
	m_images = NULL;
	m_tickImage = 0;
	m_progress = 0.0f;
	m_dotCount = 0;
	m_dotPositions = NULL;
	m_font = 0;
	m_textX = 0;
}

// FUNCTION: LEGORACERS 0x0042f3e0
LoadingScreen::~LoadingScreen()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042f430
void LoadingScreen::Destroy()
{
	m_text.Reset();
	GolImageDefinitionList* images = m_images;
	m_renderer = NULL;
	m_font = 0;

	if (images) {
		m_golExport->DestroyImageList(images);
		m_images = NULL;
	}

	LegoS32* dotPositions = m_dotPositions;
	m_golExport = NULL;
	m_tickImage = 0;
	m_progress = 0;
	m_dotCount = 0;

	if (dotPositions) {
		delete[] dotPositions;
		m_dotPositions = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042f480
void LoadingScreen::Initialize(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	GolStringTable* p_stringTable,
	GolFontBase* p_font,
	LegoBool32 p_binary
)
{
	GolBmpFile bmpFile;
	LegoChar imageName[9];
	imageName[0] = '\0';
	imageName[sizeof(imageName) - 1] = '\0';

	m_renderer = p_renderer;
	m_golExport = p_golExport;
	m_progress = 0.0f;

	LegoU32 stringIndex = 0;
	GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoU32 renderTargetWidthU32 = 0;
	LegoU32 renderTargetHeightU32 = 0;
	renderTargetWidthU32 = renderTargetInfo->GetWidthU32();
	renderTargetHeightU32 = renderTargetInfo->GetHeightU32();
	LegoFloat renderTargetWidth = static_cast<LegoFloat>(static_cast<LegoS32>(renderTargetWidthU32));
	LegoFloat renderTargetHeight = static_cast<LegoFloat>(static_cast<LegoS32>(renderTargetHeightU32));

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".lsb");
	}
	else {
		parser = new LsbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(g_loadScreenName);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(LsbTxtParser::e_loadingScreen));
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case LsbTxtParser::e_string:
			stringIndex = parser->ReadInteger();
			break;
		case LsbTxtParser::e_dots: {
			m_dotCount = parser->ReadBracketedCountAndLeftCurly();
			if (m_dotCount) {
				m_dotPositions = new LegoS32[m_dotCount << 1];
				if (m_dotPositions == NULL) {
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
			}

			for (LegoS32 i = 0; i < m_dotCount; i++) {
				m_dotPositions[i * 2] = static_cast<LegoS32>(parser->ReadFloat() * renderTargetWidth);
				m_dotPositions[i * 2 + 1] = static_cast<LegoS32>(parser->ReadFloat() * renderTargetHeight);
			}
			parser->ReadRightCurly();
			break;
		}
		case LsbTxtParser::e_image:
			::strncpy(imageName, parser->ReadStringWithMaxLength(sizeof(imageName) - 1), sizeof(imageName));
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	if (parser) {
		delete parser;
	}

	bmpFile.Open(imageName);
	bmpFile.LoadSurface(renderTargetInfo, 0, NULL);
	renderTargetInfo->Present(TRUE);
	renderTargetInfo->CopyFromDisplay();

	m_text.CopyFromBufSelection(p_stringTable->GetStringBuffer(static_cast<LegoU16>(stringIndex)), 0);
	m_font = p_font;

	LegoS32 textWidth;
	LegoS32 textHeight;
	p_font->MeasureString(&m_text, &textWidth, &textHeight);
	m_textX = (static_cast<LegoU32>(static_cast<LegoS32>(renderTargetWidth)) - textWidth) >> 1;

	m_images = m_golExport->CreateImageList();
	m_images->LoadImageDefinitions(m_renderer, g_loadScreenName, p_binary);

	GolImage* image = NULL;
	GolNameTable::Entry* nameEntries = m_images->GetNameEntries();
	if (nameEntries) {
		image = static_cast<GolImage*>(m_images->GetName("tick"));
	}
	m_tickImage = image;
}

// FUNCTION: LEGORACERS 0x0042f790
void LoadingScreen::SetProgress(LegoFloat p_progress)
{
	m_progress = p_progress;
}

// FUNCTION: LEGORACERS 0x0042f7a0
void LoadingScreen::Draw()
{
	m_renderer->DrawString(&m_text, m_font, m_textX, 25, 1.0f, 1.0f, NULL, 0);

	LegoU32 count = static_cast<LegoU32>(static_cast<LegoFloat>(m_dotCount) * m_progress);
	for (LegoU32 i = 0; i < count; i++) {
		Rect destRect;
		destRect.m_top = m_dotPositions[i * 2 + 1] - 8;
		destRect.m_bottom = m_dotPositions[i * 2 + 1] + 8;
		destRect.m_left = m_dotPositions[i * 2] - 8;
		destRect.m_right = m_dotPositions[i * 2] + 8;

		m_renderer->DrawImageRect(m_tickImage, 0, &destRect, NULL);
	}
}
