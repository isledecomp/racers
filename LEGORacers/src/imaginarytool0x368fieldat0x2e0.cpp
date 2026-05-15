#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "imaginarytool0x368.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0, 0x60)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0::Entry0xe0, 0xe0)
DECOMP_SIZE_ASSERT(ImaginaryTool0x368::FieldAt0x2e0::MidTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x0047f0a0
ImaginaryTool0x368::FieldAt0x2e0::FieldAt0x2e0()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0047f110
ImaginaryTool0x368::FieldAt0x2e0::~FieldAt0x2e0()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0047f160
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x0c()
{
	m_unk0x5c = NULL;
	CeruleanQueen0x58::Clear();
}

// FUNCTION: LEGORACERS 0x0047f170
void ImaginaryTool0x368::FieldAt0x2e0::Clear()
{
	if (m_nameEntries) {
		if (m_unk0x5c) {
			delete[] m_unk0x5c;
		}

		CeruleanQueen0x58::Clear();
	}
}

// FUNCTION: LEGORACERS 0x0047f1a0
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x10(undefined4 p_param)
{
	if (p_param) {
		m_parser = new GolBinParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_parser->SetSuffix(".mib");
	}
	else {
		m_parser = new MidTxtParser();
		if (m_parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}
}

// FUNCTION: LEGORACERS 0x0047f290
void ImaginaryTool0x368::FieldAt0x2e0::VTable0x14(undefined4 p_arg1)
{
	if (p_arg1 != 0x46) {
		CeruleanQueen0x58::VTable0x14(p_arg1);
		return;
	}

	FUN_0047f410();
}

// FUNCTION: LEGORACERS 0x0047f2b0
void ImaginaryTool0x368::FieldAt0x2e0::FUN_0047f2b0(Entry0xe0* p_entry)
{
	CeruleanQueen0x58::FUN_00469b20(p_entry);
	::memset(p_entry->m_unk0xb4, 0xff, sizeof(p_entry->m_unk0xb4));

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x29: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x84[i] = m_unk0x14->FindFontByName(m_parser->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x28: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x9c[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x2a: {
			FUN_0046b210(p_entry->m_unk0xd0.m_bytes);

			LegoS32 i;
			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0xb4[i].m_bytes);
			}

			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0x52[i].m_bytes);
			}

			p_entry->m_unk0x78 = TRUE;
			break;
		}
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0xd8 = m_parser->ReadInteger();
			p_entry->m_unk0xdc = TRUE;
			break;
		default:
			FUN_00469b50(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0047f410
void ImaginaryTool0x368::FieldAt0x2e0::FUN_0047f410()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x5c = new Entry0xe0[entryCount];
	::memset(m_unk0x5c, 0, sizeof(Entry0xe0) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x46) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x5c[i]);
		FUN_0047f2b0(&m_unk0x5c[i]);
	}
}
