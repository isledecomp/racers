#include "porcelainveil0x50.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"

#include <string.h>

DECOMP_SIZE_ASSERT(PorcelainVeil0x50, 0x50)
DECOMP_SIZE_ASSERT(PorcelainVeil0x50::MidTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00480550
PorcelainVeil0x50::PorcelainVeil0x50()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x004805c0
PorcelainVeil0x50::~PorcelainVeil0x50()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00480610
void PorcelainVeil0x50::VTable0x0c()
{
	m_unk0x4c = NULL;
	CeruleanEmperor0x4c::VTable0x0c();
}

// FUNCTION: LEGORACERS 0x00480620
void PorcelainVeil0x50::Clear()
{
	if (m_nameEntries) {
		if (m_unk0x4c) {
			delete[] m_unk0x4c;
		}

		CeruleanEmperor0x4c::Clear();
	}
}

// FUNCTION: LEGORACERS 0x00480650
void PorcelainVeil0x50::VTable0x10(undefined4 p_param)
{
	if (p_param) {
		m_parser = new GolBinParser();
		if (!m_parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".msb");
	}
	else {
		m_parser = new MidTxtParser();
		if (!m_parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: LEGORACERS 0x00480740
void PorcelainVeil0x50::VTable0x14(undefined4 p_arg1)
{
	switch (p_arg1) {
	default:
		CeruleanEmperor0x4c::VTable0x14(p_arg1);
		return;
	case GolFileParser::e_unknown0x3e:
		FUN_004808f0();
		return;
	}
}

// FUNCTION: LEGORACERS 0x00480760
void PorcelainVeil0x50::FUN_00480760(Entry0x104* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	::memset(p_entry->m_unk0xc0, 0xff, sizeof(p_entry->m_unk0xc0));

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x3a:
			FUN_00470020(p_entry);
			break;
		case GolFileParser::e_unknown0x29:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0x90[i] = m_unk0x14->FindFontByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x28:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0xa8[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0xd8.m_bytes);

			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0xc0[i].m_bytes);
			}

			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0x00[i].m_bytes);
			}

			p_entry->m_unk0x88 = TRUE;
			break;
		case GolFileParser::e_unknown0x2c:
			FUN_0046b1d0(&p_entry->m_unk0xdc.m_left);
			FUN_0046b1d0(&p_entry->m_unk0xec.m_left);
			break;
		case GolFileParser::e_unknown0x2e:
			p_entry->m_unk0xfc = m_parser->ReadInteger();
			p_entry->m_unk0x100 = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004808f0
void PorcelainVeil0x50::FUN_004808f0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x4c = new Entry0x104[entryCount];
	if (!m_unk0x4c) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::memset(m_unk0x4c, 0, sizeof(Entry0x104) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3e) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x4c[i]);
		FUN_00480760(&m_unk0x4c[i]);
	}
}
