#include "hypnoticnoise0x1c.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "goltxtparser.h"

DECOMP_SIZE_ASSERT(HypnoticNoise0x1c, 0x1c)

// FUNCTION: GOLDP 0x10022fa0
HypnoticNoise0x1c::HypnoticNoise0x1c()
{
	m_renderer = NULL;
	m_next = NULL;
	m_numItems = 0;
	m_currentHashEntry = NULL;
}

// FUNCTION: GOLDP 0x10022fe0
HypnoticNoise0x1c::~HypnoticNoise0x1c()
{
	m_numItems = 0;

	if (m_renderer) {
		m_renderer->RemoveImageList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10023060
void HypnoticNoise0x1c::LoadImageDefinitions(
	BronzeFalcon0xc8770* p_renderer,
	const LegoChar* p_fileName,
	LegoBool32 p_binary
)
{
	if (m_numItems > 0) {
		Clear();
	}

	m_renderer = p_renderer;
	m_renderer->AddImageList(this);

	GolFileParser* parser;

	if (p_binary) {
		parser = new GolBinParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}

		parser->SetSuffix(".idb");
	}
	else {
		parser = new GolTxtParser();

		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_numItems = parser->ReadBracketedCountAndLeftCurly();

	if (!m_numItems) {
		parser->Dispose();
		delete parser;
		return;
	}

	GolNameTable::Allocate(m_numItems);
	m_currentHashEntry = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	AllocateItems();

	for (LegoU32 i = 0; i < m_numItems; i++) {
		FourBytes local30;
		FourBytes local34;
		local30.m_bytes[3] = -1;
		local34.m_bytes[3] = -1;

		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		UtopianPan0xa4* item = GetItem(i);

		FourBytes name[2];
		strncpy(&name[0].m_bytes[0], parser->ReadStringWithMaxLength(sizeof(name)), sizeof(name));
		AddName(&name[0].m_bytes[0], item);

		parser->ReadLeftCurly();

		LegoU16 flags = 0;

		local30.m_bytes[0] = 0;
		local30.m_bytes[1] = 0;
		local30.m_bytes[2] = 0;

		local34.m_bytes[0] = -1;
		local34.m_bytes[1] = -1;
		local34.m_bytes[2] = -1;

		GolFileParser::ParserTokenType token = parser->GetNextToken();

		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				flags |= UtopianPan0xa4::c_flagBit2;
				break;
			case GolFileParser::e_unknown0x29:
				flags = (flags & UtopianPan0xa4::c_flagsWithoutBit4) | UtopianPan0xa4::c_flagBit3;
				break;
			case GolFileParser::e_unknown0x2a:
				flags = (flags & UtopianPan0xa4::c_flagsWithoutBit3) | UtopianPan0xa4::c_flagBit4;
				break;
			case GolFileParser::e_unknown0x2b:
				flags |= UtopianPan0xa4::c_flagBit5;
				local30.m_bytes[0] = parser->ReadInteger();
				local30.m_bytes[1] = parser->ReadInteger();
				local30.m_bytes[2] = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2c:
				local34.m_bytes[0] = parser->ReadInteger();
				local34.m_bytes[1] = parser->ReadInteger();
				local34.m_bytes[2] = parser->ReadInteger();
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			}

			token = parser->GetNextToken();
		}

		item->m_name[0] = name[0];
		item->m_name[1] = name[1];

		if (p_renderer->VTable0x110()) {
			flags = flags | UtopianPan0xa4::c_flagBit6;
		}

		if ((flags & UtopianPan0xa4::c_flagBit5) && (p_renderer->GetFlags() & BronzeFalcon0xc8770::c_flagBit9)) {
			flags = flags | UtopianPan0xa4::c_flagBit7;
		}

		item->m_flags = flags;
		item->m_unk0x4a = local34;

		if (flags & UtopianPan0xa4::c_flagBit5) {
			item->m_unk0x28 = local30;
			item->m_flags = flags | UtopianPan0xa4::c_flagBit11;
		}

		item->m_renderer = p_renderer;
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry(m_currentHashEntry);
	}

	for (LegoU32 j = 0; j < m_numItems; j++) {
		UtopianPan0xa4* entry = GetItem(j);
		if (!(entry->m_unk0x3c & UtopianPan0xa4::c_stateFlagBit0)) {
			entry->VTable0x10();
		}
	}
}

// FUNCTION: GOLDP 0x100233a0
void HypnoticNoise0x1c::VTable0x1c(BronzeFalcon0xc8770* p_renderer, LegoU32 p_numItems)
{
	if (m_numItems > 0) {
		Clear();
	}

	m_renderer = p_renderer;
	m_renderer->AddImageList(this);
	m_numItems = p_numItems;

	AllocateItems();

	for (LegoU32 i = 0; i < p_numItems; i++) {
		GetItem(i)->m_renderer = p_renderer;
	}
}

// FUNCTION: GOLDP 0x100233f0
void HypnoticNoise0x1c::Clear()
{
	m_numItems = 0;
	if (m_renderer) {
		m_renderer->RemoveImageList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x10()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void HypnoticNoise0x1c::VTable0x14()
{
	// empty
}
