#include "font/golfont.h"
#include "golerror.h"
#include "menu/runtime/cutsceneplayer.h"
#include "render/golrenderdevice.h"

#include <string.h>

// FUNCTION: LEGORACERS 0x004a45b0
CutsceneTextVisual::CutsceneTextVisual()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4610
CutsceneTextVisual::~CutsceneTextVisual()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a4670
void CutsceneTextVisual::Reset()
{
	m_rawString = NULL;
	m_font = NULL;
	m_fontName[0] = '\0';
	m_stringTableIndex = 0;
	m_stringIndex = 0;
	CutsceneVisual::Reset();
}

// FUNCTION: LEGORACERS 0x004a4690
void CutsceneTextVisual::Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer)
{
	p_parser->ReadLeftCurly();
	m_flags = 3;

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case CutscenePlayer::CebTxtParser::e_string:
			m_stringTableIndex = p_parser->ReadInteger();
			m_stringIndex = p_parser->ReadInteger();
			break;
		case CutscenePlayer::CebTxtParser::e_text: {
			LegoChar* text = p_parser->ReadString();
			m_rawString = new LegoChar[::strlen(text) + 1];
			if (m_rawString == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			::strcpy(m_rawString, text);
			break;
		}
		case CutscenePlayer::CebTxtParser::e_font:
			::strncpy(m_fontName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			break;
		default:
			ParseVisualToken(p_parser, token, p_owner, p_renderer);
			break;
		}
	}

	if (m_fontName[0] == '\0') {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a4790
void CutsceneTextVisual::RefreshString(CutscenePlayer* p_owner, GolRenderDevice* p_renderer)
{
	if (m_rawString == NULL) {
		if (m_stringTableIndex >= p_owner->GetStringTableCount()) {
			GOL_FATALERROR_MESSAGE("Invalid string manager offset encountered");
		}

		GolStringTable* stringTable = p_owner->GetStringTableByIndex(static_cast<LegoU16>(m_stringTableIndex));
		stringTable->CopyStringByIndex(&m_string, static_cast<LegoU16>(m_stringIndex));
	}

	m_font = p_renderer->FindFontByName(m_fontName);
	if (m_font == NULL) {
		LegoChar message[64];

		::strncpy(message, m_fontName, sizeof(m_fontName));
		message[sizeof(m_fontName)] = '\0';
		::strcat(message, ": Unable to find font");
		GOL_FATALERROR_MESSAGE(message);
	}
}

// FUNCTION: LEGORACERS 0x004a4850
void CutsceneTextVisual::Clear()
{
	m_string.Reset();

	if (m_rawString != NULL) {
		delete[] m_rawString;
	}

	Reset();
	CutsceneEvent::Reset();
}

// FUNCTION: LEGORACERS 0x004a4890
void CutsceneTextVisual::GetContentSize(LegoS32* p_width, LegoS32* p_height)
{
	if (m_rawString != NULL) {
		m_font->MeasureString(m_rawString, p_width, p_height);
	}
	else {
		m_font->MeasureString(&m_string, p_width, p_height);
	}
}

// FUNCTION: LEGORACERS 0x004a48d0
void CutsceneTextVisual::DrawContent(
	GolRenderDevice* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	undefined4,
	undefined4,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY
)
{
	if (m_flags & 0x100) {
		m_font->SetColor(m_colorPacked);
	}

	if (m_rawString != NULL) {
		p_renderer->DrawCString(m_rawString, m_font, p_x, p_y, p_scaleX, p_scaleY, NULL, 0);
	}
	else {
		p_renderer->DrawString(&m_string, m_font, p_x, p_y, p_scaleX, p_scaleY, NULL, 0);
	}

	if (m_flags & 0x100) {
		ColorRGBA color;

		color.m_red = 0xff;
		color.m_grn = 0xff;
		color.m_blu = 0xff;
		color.m_alp = 0xff;
		m_font->SetColor(color);
	}
}
