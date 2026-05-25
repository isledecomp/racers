#include "shadowwolf0xc.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golname.h"
#include "igdbmodel0x40.h"
#include "whitefalcon0x140.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(ShadowWolf0xc, 0x0c)

// FUNCTION: GOLDP 0x10025de0 FOLDED
ShadowWolf0xc::ShadowWolf0xc()
{
	m_renderer = NULL;
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: GOLDP 0x10025df0 FOLDED
void ShadowWolf0xc::FUN_10025df0(WhiteFalcon0x140* p_renderer, undefined4 p_arg2)
{
	if (m_renderer != NULL) {
		Destroy();
	}

	m_renderer = p_renderer;
	m_count = p_arg2;

	m_entries = new void*[p_arg2];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_entries, 0, sizeof(*m_entries) * m_count);
}

// FUNCTION: GOLDP 0x10025e60
void ShadowWolf0xc::FUN_10025e60(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Destroy();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".gdb");
	}
	else {
		parser = new GdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	FUN_10025f90(p_renderer, *parser);

	parser->Dispose();
	delete parser;
}

// FUNCTION: GOLDP 0x10025f90
void ShadowWolf0xc::FUN_10025f90(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser)
{
	LegoU32 i;

	if (m_renderer != NULL) {
		Destroy();
	}

	m_renderer = p_renderer;
	m_count = p_parser.ReadBracketedCountAndLeftCurly();
	if (m_count == 0) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_entries = new void*[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (i = 0; i < m_count; i++) {
		GolName materialName;
		::strncpy(materialName, p_parser.ReadString(), sizeof(materialName));
		DuskwindBananaRelic0x24* material = m_renderer->FindMaterialByName(materialName);
		m_entries[i] = material;
		if (m_entries[i] == NULL) {
			char message[64];
			::memset(message, 0, sizeof(materialName) + 1);
			::strncpy(message, materialName, sizeof(materialName));
			::strcat(message, ": Material assignment failed");
			GOL_FATALERROR_MESSAGE(message);
		}
	}

	if (p_parser.GetNextToken() != GolFileParser::e_rightCurly) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_rightCurly);
	}
}

// FUNCTION: GOLDP 0x100260d0 FOLDED
ShadowWolf0xc::~ShadowWolf0xc()
{
	Destroy();
}

// FUNCTION: GOLDP 0x100260d0 FOLDED
void ShadowWolf0xc::Destroy()
{
	if (m_entries != NULL) {
		delete[] m_entries;
		m_entries = NULL;
	}
	m_renderer = NULL;
	m_count = 0;
}
