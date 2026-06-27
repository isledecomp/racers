#include "core/gol.h"
#include "golbinparser.h"
#include "golbmpfile.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golfontbase.h"
#include "material/awakekite0x20.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/slatepeak0x58.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceSession::Field0x280c, 0x30)
DECOMP_SIZE_ASSERT(RaceSession::Field0x280c::LsbTxtParser, 0x1fc)

// GLOBAL: LEGORACERS 0x004bed40
const LegoChar* g_loadScreenName = "loadscrn";

// FUNCTION: LEGORACERS 0x0042f3b0
RaceSession::Field0x280c::Field0x280c()
{
	m_renderer = NULL;
	m_unk0x04 = NULL;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0.0f;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
}

// FUNCTION: LEGORACERS 0x0042f3e0
RaceSession::Field0x280c::~Field0x280c()
{
	FUN_0042f430();
}

// FUNCTION: LEGORACERS 0x0042f430
void RaceSession::Field0x280c::FUN_0042f430()
{
	m_unk0x1c.Reset();
	AwakeKite0x20* field0x08 = m_unk0x08;
	m_renderer = NULL;
	m_unk0x28 = 0;

	if (field0x08) {
		m_unk0x04->VTable0x68(field0x08);
		m_unk0x08 = NULL;
	}

	LegoS32* field0x18 = m_unk0x18;
	m_unk0x04 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;

	if (field0x18) {
		delete[] field0x18;
		m_unk0x18 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x0042f480
void RaceSession::Field0x280c::FUN_0042f480(
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
	m_unk0x04 = p_golExport;
	m_unk0x10 = 0.0f;

	LegoU32 stringIndex = 0;
	SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
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
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2a:
			stringIndex = parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x29: {
			m_unk0x14 = parser->ReadBracketedCountAndLeftCurly();
			if (m_unk0x14) {
				m_unk0x18 = new LegoS32[m_unk0x14 << 1];
				if (m_unk0x18 == NULL) {
					GOL_FATALERROR(c_golErrorOutOfMemory);
				}
			}

			for (LegoS32 i = 0; i < m_unk0x14; i++) {
				m_unk0x18[i * 2] = static_cast<LegoS32>(parser->ReadFloat() * renderTargetWidth);
				m_unk0x18[i * 2 + 1] = static_cast<LegoS32>(parser->ReadFloat() * renderTargetHeight);
			}
			parser->ReadRightCurly();
			break;
		}
		case GolFileParser::e_unknown0x28:
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

	bmpFile.VTable0x08(imageName);
	bmpFile.VTable0x20(renderTargetInfo, 0, NULL);
	renderTargetInfo->VTable0x14(TRUE);
	renderTargetInfo->VTable0x2c();

	m_unk0x1c.CopyFromBufSelection(p_stringTable->GetStringBuffer(static_cast<LegoU16>(stringIndex)), 0);
	m_unk0x28 = p_font;

	LegoS32 textWidth;
	LegoS32 textHeight;
	p_font->MeasureString(&m_unk0x1c, &textWidth, &textHeight);
	m_unk0x2c = (static_cast<LegoU32>(static_cast<LegoS32>(renderTargetWidth)) - textWidth) >> 1;

	m_unk0x08 = m_unk0x04->VTable0x34();
	m_unk0x08->LoadImageDefinitions(m_renderer, g_loadScreenName, p_binary);

	UtopianPan0xa4* image = NULL;
	GolNameTable::Entry* nameEntries = m_unk0x08->GetNameEntries();
	if (nameEntries) {
		image = static_cast<UtopianPan0xa4*>(m_unk0x08->GetName("tick"));
	}
	m_unk0x0c = image;
}

// FUNCTION: LEGORACERS 0x0042f790
void RaceSession::Field0x280c::FUN_0042f790(LegoFloat p_unk0x04)
{
	m_unk0x10 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0042f7a0
void RaceSession::Field0x280c::FUN_0042f7a0()
{
	m_renderer->VTable0x64(&m_unk0x1c, m_unk0x28, m_unk0x2c, 25, 1.0f, 1.0f, NULL, 0);

	LegoU32 count = static_cast<LegoU32>(static_cast<LegoFloat>(m_unk0x14) * m_unk0x10);
	for (LegoU32 i = 0; i < count; i++) {
		Rect destRect;
		destRect.m_top = m_unk0x18[i * 2 + 1] - 8;
		destRect.m_bottom = m_unk0x18[i * 2 + 1] + 8;
		destRect.m_left = m_unk0x18[i * 2] - 8;
		destRect.m_right = m_unk0x18[i * 2] + 8;

		m_renderer->VTable0x78(m_unk0x0c, 0, &destRect, NULL);
	}
}
