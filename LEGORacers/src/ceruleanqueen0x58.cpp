#include "ceruleanqueen0x58.h"

#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CeruleanQueen0x58, 0x5c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x38, 0x38)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x3c, 0x3c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x48, 0x48)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x60, 0x60)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x84, 0x84)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x88, 0x88)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x98, 0x98)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x9c, 0x9c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0xa0, 0xa0)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0xa0WithFont, 0xa0)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0xb8, 0xb8)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0xec, 0xec)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Entry0x54, 0x54)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::MidTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::ResourceLoadParams, 0x0c)
DECOMP_SIZE_ASSERT(CeruleanQueen0x58::Struct0x74, 0x74)

// FUNCTION: LEGORACERS 0x004695b0
CeruleanQueen0x58::CeruleanQueen0x58()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x00469620
CeruleanQueen0x58::~CeruleanQueen0x58()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00469670
void CeruleanQueen0x58::VTable0x0c()
{
	m_unk0x54 = 2;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	m_unk0x50 = 0;
	CeruleanKnight0x20::VTable0x0c();
}

// FUNCTION: LEGORACERS 0x004696b0
LegoBool32 CeruleanQueen0x58::Load(ResourceLoadParams* p_params)
{
	Clear();
	m_unk0x14 = p_params->m_renderer;

	if (FUN_0046b100()) {
		FUN_00469900(p_params);
	}

	return m_nameEntries != NULL;
}

// FUNCTION: LEGORACERS 0x004696f0
void CeruleanQueen0x58::Clear()
{
	if (m_nameEntries == NULL) {
		return;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}
	if (m_unk0x24) {
		delete[] m_unk0x24;
	}
	if (m_unk0x28) {
		delete[] m_unk0x28;
	}
	if (m_unk0x2c) {
		delete[] m_unk0x2c;
	}
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}
	if (m_unk0x34) {
		delete[] m_unk0x34;
	}
	if (m_unk0x38) {
		delete[] m_unk0x38;
	}
	if (m_unk0x3c) {
		delete[] m_unk0x3c;
	}
	if (m_unk0x40) {
		for (LegoS32 i = 0; i < m_unk0x58; i++) {
			delete[] m_unk0x40[i].m_unk0x3c;
		}

		delete[] m_unk0x40;
	}
	if (m_unk0x44) {
		delete[] m_unk0x44;
	}
	if (m_unk0x48) {
		delete[] m_unk0x48;
	}
	if (m_unk0x4c) {
		delete[] m_unk0x4c;
	}
	if (m_unk0x50) {
		delete[] m_unk0x50;
	}

	CeruleanKnight0x20::Clear();
}

// FUNCTION: LEGORACERS 0x00469810
void CeruleanQueen0x58::VTable0x10(undefined4 p_param)
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
void CeruleanQueen0x58::FUN_00469900(ResourceLoadParams* p_params)
{
	VTable0x10(p_params->m_binary);
	m_parser->OpenFileForRead(p_params->m_fileName);
	FUN_0046b130();
	FUN_0046b250();
	m_parser->Dispose();

	delete m_parser;
}

// FUNCTION: LEGORACERS 0x00469950
void CeruleanQueen0x58::VTable0x14(undefined4 p_arg1)
{
	switch (p_arg1) {
	case 0x37:
		FUN_0046a750();
		break;
	case 0x38:
		FUN_0046a800();
		break;
	case 0x39:
		FUN_0046a8a0();
		break;
	case 0x3a:
		FUN_0046a940();
		break;
	case 0x3b:
		FUN_0046a9e0();
		break;
	case 0x3c:
		FUN_0046aa90();
		break;
	case 0x3d:
		FUN_0046ab40();
		break;
	case 0x3e:
		FUN_0046abe0();
		break;
	case 0x3f:
		FUN_0046ac90();
		break;
	case 0x40:
		FUN_0046ad40();
		break;
	case 0x41:
	case 0x44:
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case 0x42:
		FUN_0046adf0();
		break;
	case 0x43:
		FUN_0046af50();
		break;
	case 0x45:
		FUN_0046aea0();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00469a20
void CeruleanQueen0x58::FUN_00469a20(ObscureVantage0x58::CreateParams0x30* p_entry)
{
	VisualState0x4* visualState = &p_entry->m_unk0x22;
	visualState->m_unk0x00 = -1;

	LegoU8 flags = p_entry->m_flagsAndName.m_flagsByte;
	flags |= 1;
	p_entry->m_flagsAndName.m_flagsByte = flags;
	p_entry->m_unk0x20 = m_unk0x54++;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x2f:
			FUN_0046b1d0(&p_entry->m_rect.m_left);
			break;
		case GolFileParser::e_unknown0x30: {
			LegoS32 value = m_parser->ReadInteger();
			p_entry->m_unk0x20 = value;
			m_unk0x54 = value + 1;
			break;
		}
		case GolFileParser::e_unknown0x32: {
			LegoU8 value = m_parser->ReadInteger();
			LegoU8 flags = p_entry->m_flagsAndName.m_flagsByte;
			LegoU8 newFlags = flags;
			newFlags ^= value;
			newFlags &= 1;
			newFlags ^= flags;
			p_entry->m_flagsAndName.m_flagsByte = newFlags;
			break;
		}
		case GolFileParser::e_unknown0x31:
			::strncpy(p_entry->m_flagsAndName.m_unk0x2d, m_parser->ReadString(), 8);
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(visualState->m_bytes);
			p_entry->m_flagsAndName.m_flagsByte |= 2;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469b20
void CeruleanQueen0x58::FUN_00469b20(Entry0x84* p_entry)
{
	p_entry->m_unk0x38 = TRUE;
	p_entry->m_unk0x74 = TRUE;
	::memset(p_entry->m_unk0x52, 0xff, sizeof(p_entry->m_unk0x52));
}

// FUNCTION: LEGORACERS 0x00469b50
void CeruleanQueen0x58::FUN_00469b50(Entry0x84* p_entry)
{
	switch (m_parser->GetCurrentToken()) {
	case GolFileParser::e_unknown0x36:
		FUN_00469a20(p_entry);
		return;
	case GolFileParser::e_unknown0x33:
		p_entry->m_unk0x38 = m_parser->ReadInteger();
		return;
	case GolFileParser::e_unknown0x32:
		p_entry->m_unk0x74 = m_parser->ReadInteger();
		return;
	case GolFileParser::e_unknown0x31:
		::strncpy(p_entry->m_flagsAndName.m_unk0x2d, m_parser->ReadString(), 8);
		return;
	case GolFileParser::e_unknown0x34:
		p_entry->m_unk0x3c = m_parser->ReadInteger();
		return;
	case GolFileParser::e_unknown0x2c:
		p_entry->m_unk0x40 = m_parser->ReadInteger();
		return;
	case GolFileParser::e_unknown0x2a: {
		for (LegoS32 i = 0; i < 6; i++) {
			FUN_0046b210(p_entry->m_unk0x52[i].m_bytes);
		}
		p_entry->m_unk0x78 = TRUE;
		return;
	}
	case GolFileParser::e_unknown0x2b: {
		for (LegoS32 i = 0; i < 5; i++) {
			p_entry->m_soundIds[i] = m_parser->ReadInteger();
		}
		p_entry->m_unk0x7c = TRUE;
		return;
	}
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00469c90
void CeruleanQueen0x58::FUN_00469c90(Entry0x98* p_entry)
{
	switch (m_parser->GetCurrentToken()) {
	case GolFileParser::e_unknown0x3b:
		p_entry->m_unk0x84 = FUN_0046aff0(m_parser->ReadString());
		p_entry->m_unk0x88 = FUN_0046aff0(m_parser->ReadString());
		return;
	case GolFileParser::e_unknown0x3a:
		p_entry->m_unk0x8c = FUN_0046aff0(m_parser->ReadString());
		return;
	case GolFileParser::e_unknown0x33:
		p_entry->m_unk0x94 = m_parser->ReadInteger();
		return;
	default:
		FUN_00469b50(p_entry);
		return;
	}
}

// FUNCTION: LEGORACERS 0x00469d20
void CeruleanQueen0x58::FUN_00469d20(LegoFloat* p_floats)
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
void CeruleanQueen0x58::FUN_00469d90(Entry0x3c* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x28:
			p_entry->m_unk0x38 = m_unk0x14->FindImageByName(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x22.m_bytes);
			p_entry->m_flagsAndName.m_flagsByte |= 2;
			break;
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469e20
void CeruleanQueen0x58::FUN_00469e20(Entry0x48* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x29:
			p_entry->m_unk0x3c = m_unk0x14->FindFontByName(m_parser->ReadString());
			// Fall through.
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x22.m_bytes);
			p_entry->m_flagsAndName.m_flagsByte |= 2;
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x44 = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469ee0
void CeruleanQueen0x58::FUN_00469ee0(Entry0x60* p_entry)
{
	p_entry->m_unk0x5c = TRUE;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x5c = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x28: {
			for (LegoS32 i = 0; i < 8; i++) {
				p_entry->m_images[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x22.m_bytes);
			FUN_0046b210(p_entry->m_unk0x58.m_bytes);
			p_entry->m_flagsAndName.m_flagsByte |= 2;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00469fd0
void CeruleanQueen0x58::FUN_00469fd0(Entry0x9c* p_entry)
{
	FUN_00469b20(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		if (m_parser->GetCurrentToken() != GolFileParser::e_unknown0x28) {
			FUN_00469b50(p_entry);
		}
		else {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x84[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a050
void CeruleanQueen0x58::FUN_0046a050(Entry0xec* p_entry)
{
	FUN_00469b20(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	if (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		UtopianPan0xa4** image = p_entry->m_utopianunk0xa0;
		do {
			switch (m_parser->GetCurrentToken()) {
			case GolFileParser::e_unknown0x28: {
				UtopianPan0xa4** imageCursor = image;
				for (LegoS32 i = 0; i < 6; i++) {
					*imageCursor = m_unk0x14->FindImageByName(m_parser->ReadString());
					imageCursor += 3;
				}
				image++;
				break;
			}
			case GolFileParser::e_unknown0x29: {
				for (LegoS32 i = 0; i < 6; i++) {
					p_entry->m_unk0x88[i] = m_unk0x14->FindFontByName(m_parser->ReadString());
				}
				break;
			}
			default:
				FUN_00469b50(p_entry);
				break;
			}
		} while (m_parser->GetNextToken() != GolFileParser::e_rightCurly);
	}
}

// FUNCTION: LEGORACERS 0x0046a110
void CeruleanQueen0x58::FUN_0046a110(Entry0xa0* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	FUN_00469b20(p_entry);
	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x28:
			p_entry->m_unk0x9c = m_unk0x14->FindImageByName(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x3b:
			FUN_00469fd0(p_entry);
			break;
		default:
			FUN_00469b50(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a190
void CeruleanQueen0x58::FUN_0046a190(Entry0x98* p_entry)
{
	p_entry->m_unk0x38 = TRUE;
	p_entry->m_unk0x74 = TRUE;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		FUN_00469c90(p_entry);
	}
}

// FUNCTION: LEGORACERS 0x0046a1f0
void CeruleanQueen0x58::FUN_0046a1f0(Struct0x74* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x38 = m_parser->ReadInteger();
			p_entry->m_unk0x44 = m_parser->ReadInteger();
			p_entry->m_unk0x40 = m_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x2f: {
			if (!p_entry->m_unk0x38) {
				m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			}

			p_entry->m_unk0x3c = new Rect[p_entry->m_unk0x38];
			if (p_entry->m_unk0x3c == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoS32 i = 0; i < p_entry->m_unk0x38; i++) {
				FUN_0046b1d0(&p_entry->m_unk0x3c[i].m_left);
			}
			break;
		}
		case GolFileParser::e_unknown0x2e:
			FUN_00469d20(p_entry->m_unk0x48);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_invalidKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a310
void CeruleanQueen0x58::FUN_0046a310(Entry0xb8* p_entry)
{
	FUN_00469b20(p_entry);

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0xb4 = m_parser->ReadInteger();
			p_entry->m_unk0xb0 = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x3b:
			p_entry->m_unk0x84 = FUN_0046aff0(m_parser->ReadString());
			p_entry->m_unk0x88 = FUN_0046aff0(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x38:
			p_entry->m_unk0x90 = FUN_0046aff0(m_parser->ReadString());
			p_entry->m_unk0x8c = FUN_0046aff0(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x28: {
			for (LegoS32 i = 0; i < 6; i++) {
				p_entry->m_unk0x94[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		}
		case GolFileParser::e_unknown0x2b:
			FUN_00469b50(p_entry);
			p_entry->m_unk0xac = m_parser->ReadInteger();
			p_entry->m_unk0xae = m_parser->ReadInteger();
			break;
		default:
			FUN_00469b50(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a490
void CeruleanQueen0x58::FUN_0046a490(Entry0x88* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x2d:
			::strncpy(p_entry->m_unk0x60, m_parser->ReadString(), 8);
			break;
		case GolFileParser::e_unknown0x3a:
			p_entry->m_unk0x84 = FUN_0046aff0(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x2e:
			FUN_00469d20(p_entry->m_unk0x38);
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x70 = m_parser->ReadInteger();
			p_entry->m_unk0x74 = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x35:
			p_entry->m_unk0x78 = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a590
void CeruleanQueen0x58::FUN_0046a590(Entry0x54* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	p_entry->m_unk0x48 = 0;
	p_entry->m_unk0x4c = 0;
	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x48 = m_parser->ReadInteger();
			p_entry->m_unk0x4c = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			::strncpy(p_entry->m_unk0x38, m_parser->ReadStringWithMaxLength(8), 8);
			p_entry->m_unk0x38[8] = 0;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a640
void CeruleanQueen0x58::FUN_0046a640(Entry0xa0WithFont* p_entry)
{
	FUN_00469b20(p_entry);
	p_entry->m_unk0x94 = 31;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x36:
			FUN_00469a20(p_entry);
			break;
		case GolFileParser::e_unknown0x29:
			p_entry->m_unk0x8c = m_unk0x14->FindFontByName(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x33:
			p_entry->m_unk0x94 = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2b: {
			LegoS32 i;
			for (i = 0; i < 5; i++) {
				p_entry->m_soundIds[i] = m_parser->ReadInteger();
			}
			for (i = 0; i < 4; i++) {
				p_entry->m_unk0x96[i] = m_parser->ReadInteger();
			}
			p_entry->m_unk0x7c = TRUE;
			break;
		}
		default:
			FUN_00469b50(p_entry);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046a750
void CeruleanQueen0x58::FUN_0046a750()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x20 = new Entry0x38[entryCount];
	::memset(m_unk0x20, 0, sizeof(Entry0x38) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x37) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x20[i]);
		FUN_00469a20(&m_unk0x20[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a800
void CeruleanQueen0x58::FUN_0046a800()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x24 = new Entry0x3c[entryCount];
	::memset(m_unk0x24, 0, sizeof(Entry0x3c) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x38) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x24[i]);
		FUN_00469d90(&m_unk0x24[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a8a0
void CeruleanQueen0x58::FUN_0046a8a0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x28 = new Entry0x48[entryCount];
	::memset(m_unk0x28, 0, sizeof(Entry0x48) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x39) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x28[i]);
		FUN_00469e20(&m_unk0x28[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a940
void CeruleanQueen0x58::FUN_0046a940()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x2c = new Entry0x60[entryCount];
	::memset(m_unk0x2c, 0, sizeof(Entry0x60) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3a) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x2c[i]);
		FUN_00469ee0(&m_unk0x2c[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046a9e0
void CeruleanQueen0x58::FUN_0046a9e0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x30 = new Entry0x9c[entryCount];
	::memset(m_unk0x30, 0, sizeof(Entry0x9c) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3b) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x30[i]);
		FUN_00469fd0(&m_unk0x30[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046aa90
void CeruleanQueen0x58::FUN_0046aa90()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x34 = new Entry0xec[entryCount];
	::memset(m_unk0x34, 0, sizeof(Entry0xec) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3c) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x34[i]);
		FUN_0046a050(&m_unk0x34[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ab40
void CeruleanQueen0x58::FUN_0046ab40()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x38 = new Entry0xa0[entryCount];
	::memset(m_unk0x38, 0, sizeof(Entry0xa0) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3d) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x38[i]);
		FUN_0046a110(&m_unk0x38[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046abe0
void CeruleanQueen0x58::FUN_0046abe0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x3c = new Entry0x98[entryCount];
	::memset(m_unk0x3c, 0, sizeof(Entry0x98) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3e) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x3c[i]);
		FUN_0046a190(&m_unk0x3c[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ac90
void CeruleanQueen0x58::FUN_0046ac90()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x58 = entryCount;
	m_unk0x40 = new Struct0x74[entryCount];
	::memset(m_unk0x40, 0, sizeof(Struct0x74) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3f) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x40[i]);
		FUN_0046a1f0(&m_unk0x40[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046ad40
void CeruleanQueen0x58::FUN_0046ad40()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x44 = new Entry0xb8[entryCount];
	::memset(m_unk0x44, 0, sizeof(Entry0xb8) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x40) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x44[i]);
		FUN_0046a310(&m_unk0x44[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046adf0
void CeruleanQueen0x58::FUN_0046adf0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x48 = new Entry0x88[entryCount];
	::memset(m_unk0x48, 0, sizeof(Entry0x88) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x42) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x48[i]);
		FUN_0046a490(&m_unk0x48[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046aea0
void CeruleanQueen0x58::FUN_0046aea0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x50 = new Entry0x54[entryCount];
	::memset(m_unk0x50, 0, sizeof(Entry0x54) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x45) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x50[i]);
		FUN_0046a590(&m_unk0x50[i]);
	}
}

// FUNCTION: LEGORACERS 0x0046af50
void CeruleanQueen0x58::FUN_0046af50()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x4c = new Entry0xa0WithFont[entryCount];
	::memset(m_unk0x4c, 0, sizeof(Entry0xa0WithFont) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x43) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x4c[i]);
		FUN_0046a640(&m_unk0x4c[i]);
	}
}
