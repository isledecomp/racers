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
	m_unk0x0c = NULL;
	m_unk0x10 = 0;
	m_numItems = 0;
	m_unk0x18 = NULL;
}

// TODO: Temporary workaround until we figure out how the original code was written.
// FUNCTION: GOLDP 0x10022fe0
#pragma inline_depth(0)
HypnoticNoise0x1c::~HypnoticNoise0x1c()
{
	m_numItems = 0;

	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
	}
}
#pragma inline_depth()

// FUNCTION: GOLDP 0x10023060
void HypnoticNoise0x1c::VTable0x18(BronzeFalcon0xc8770* p_param1, char* p_param2, undefined4 p_param3)
{
	if (m_numItems > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);

	GolFileParser* parser;

	if (p_param3) {
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

	parser->VTable0x38((undefined4) p_param2);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_numItems = parser->FUN_100327e0();

	if (!m_numItems) {
		parser->Dispose();
		delete parser;
		return;
	}

	SmallCocoon0xc::VTable0x04(m_numItems);
	m_unk0x18 = g_hashTable ? g_hashTable->GetCurrentEntry() : NULL;
	VTable0x0c();

	for (LegoU32 i = 0; i < m_numItems; i++) {
		FourBytes local30;
		FourBytes local34;
		local30.m_bytes[3] = -1;
		local34.m_bytes[3] = -1;

		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		UtopianPan0xa4* item = VTable0x20(i);

		FourBytes name[2];
		strncpy(&name[0].m_bytes[0], parser->ReadStringWithMaxLength(8), 8);
		AddName(&name[0].m_bytes[0], item);

		parser->ReadLeftCurly();

		LegoU32 flags = 0;

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
				flags |= 4;
				break;
			case GolFileParser::e_unknown0x29:
				flags &= 0xffef;
				flags |= 0x08;
				break;
			case GolFileParser::e_unknown0x2a:
				flags &= 0xfff7;
				flags |= 0x10;
				break;
			case GolFileParser::e_unknown0x2b:
				flags |= 0x20;
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

		if (p_param1->VTable0x110()) {
			flags = flags | 0x40;
		}

		if ((flags & 0x20) && (p_param1->GetUnk0x04() & 0x200)) {
			flags = flags | 0x80;
		}

		item->m_unk0x40 = flags;
		item->m_unk0x4a = local34;

		if (flags & 0x20) {
			item->m_unk0x28 = local30;
			item->m_unk0x40 = flags | 0x800;
		}

		item->m_unk0x24 = p_param1;
	}

	parser->ReadRightCurly();
	parser->Dispose();
	delete parser;

	if (g_hashTable) {
		g_hashTable->SetCurrentEntry(m_unk0x18);
	}

	for (LegoU32 j = 0; j < m_numItems; j++) {
		UtopianPan0xa4* entry = VTable0x20(j);
		if ((entry->m_unk0x3c & 1) == 0) {
			entry->VTable0x10();
		}
	}
}

// FUNCTION: GOLDP 0x100233a0
void HypnoticNoise0x1c::VTable0x1c(BronzeFalcon0xc8770* p_param1, LegoU32 p_param2)
{
	if (m_numItems > 0) {
		VTable0x08();
	}

	m_unk0x0c = p_param1;
	m_unk0x0c->FUN_10028ad0(this);
	m_numItems = p_param2;

	VTable0x0c();

	for (LegoU32 i = 0; i < p_param2; i++) {
		VTable0x20(i)->m_unk0x24 = p_param1;
	}
}

// FUNCTION: GOLDP 0x100233f0
void HypnoticNoise0x1c::VTable0x08()
{
	m_numItems = 0;
	if (m_unk0x0c) {
		m_unk0x0c->FUN_10028ae0(this);
		m_unk0x0c = 0;
	}

	if (m_data) {
		SmallCocoon0xc::VTable0x08();
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
