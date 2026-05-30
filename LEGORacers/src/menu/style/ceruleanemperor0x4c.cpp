#include "menu/style/ceruleanemperor0x4c.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golname.h"
#include "goltxtparser.h"
#include "menu/style/porcelainveil0x50.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c, 0x4c)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x0c, 0x0c)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x14, 0x14)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x18, 0x18)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x2c, 0x2c)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x90, 0x90)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0xa8, 0xa8)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x100, 0x100)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x104, 0x104)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0x150, 0x150)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0xbc, 0xbc)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::Entry0xbcWithImages, 0xbc)
DECOMP_SIZE_ASSERT(CeruleanEmperor0x4c::ResourceLoadParams, 0x10)

// FUNCTION: LEGORACERS 0x0046fa50
CeruleanEmperor0x4c::CeruleanEmperor0x4c()
{
	VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0046fac0
CeruleanEmperor0x4c::~CeruleanEmperor0x4c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x0046fb10
void CeruleanEmperor0x4c::VTable0x0c()
{
	m_unk0x20 = 0;
	m_unk0x24 = NULL;
	m_unk0x28 = NULL;
	m_unk0x2c = NULL;
	m_unk0x30 = NULL;
	m_unk0x34 = NULL;
	m_unk0x38 = NULL;
	m_unk0x3c = NULL;
	m_unk0x40 = NULL;
	m_unk0x44 = NULL;
	m_unk0x48 = NULL;

	CeruleanKnight0x20::VTable0x0c();
}

// FUNCTION: LEGORACERS 0x0046fb40
LegoBool32 CeruleanEmperor0x4c::Load(ResourceLoadParams* p_params)
{
	Clear();
	m_unk0x14 = p_params->m_renderer;
	m_unk0x20 = p_params->m_unk0x04;

	if (FUN_0046b100()) {
		FUN_0046fd30(p_params);
	}

	return m_nameEntries != NULL;
}

// FUNCTION: LEGORACERS 0x0046fb80
void CeruleanEmperor0x4c::Clear()
{
	if (m_nameEntries == NULL) {
		return;
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
		delete[] m_unk0x40;
	}
	if (m_unk0x44) {
		delete[] m_unk0x44;
	}
	if (m_unk0x48) {
		delete[] m_unk0x48;
	}

	CeruleanKnight0x20::Clear();
}

// FUNCTION: LEGORACERS 0x0046fc40
void CeruleanEmperor0x4c::VTable0x10(undefined4 p_param)
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
void CeruleanEmperor0x4c::FUN_0046fd30(ResourceLoadParams* p_params)
{
	VTable0x10(p_params->m_binary);
	m_parser->OpenFileForRead(p_params->m_fileName);
	FUN_0046b130();
	FUN_0046b250();
	m_parser->Dispose();

	delete m_parser;
}

// FUNCTION: LEGORACERS 0x0046fd80
void CeruleanEmperor0x4c::VTable0x14(undefined4 p_arg1)
{
	switch (p_arg1) {
	case 0x32:
		FUN_004707e0();
		break;
	case 0x33:
		FUN_00470880();
		break;
	case 0x34:
		FUN_00470920();
		break;
	case 0x35:
		FUN_004709c0();
		break;
	case 0x36:
		FUN_00470a70();
		break;
	case 0x37:
		FUN_00470b10();
		break;
	case 0x38:
		FUN_00470bc0();
		break;
	case 0x39:
		FUN_00470c60();
		break;
	case 0x3a:
	default:
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		break;
	case 0x3b:
		FUN_00470d10();
		break;
	case 0x3d:
		FUN_00470dc0();
		break;
	}
}

// FUNCTION: LEGORACERS 0x0046fe20
void CeruleanEmperor0x4c::FUN_0046fe20(Entry0x0c* p_entry)
{
	p_entry->m_unk0x04.m_unk0x00 = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x28:
			p_entry->m_unk0x00 = m_unk0x14->FindImageByName(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x04.m_bytes);
			p_entry->m_unk0x08 = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046feb0
void CeruleanEmperor0x4c::FUN_0046feb0(Entry0x14* p_entry)
{
	p_entry->m_unk0x04.m_unk0x00 = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x29:
			p_entry->m_unk0x00 = m_unk0x14->FindFontByName(m_parser->ReadString());
			break;
		case GolFileParser::e_unknown0x2f:
			p_entry->m_unk0x10 = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x04.m_bytes);
			p_entry->m_unk0x0c = TRUE;
			break;
		case GolFileParser::e_unknown0x2e:
			p_entry->m_unk0x08 = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x0046ff70
void CeruleanEmperor0x4c::FUN_0046ff70(Entry0x2c* p_entry)
{
	p_entry->m_unk0x24.m_unk0x00 = -1;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x28:
			for (i = 0; i < 8; i++) {
				p_entry->m_unk0x00[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_0046b210(p_entry->m_unk0x20.m_bytes);
			FUN_0046b210(p_entry->m_unk0x24.m_bytes);
			p_entry->m_unk0x28 = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470020
void CeruleanEmperor0x4c::FUN_00470020(Entry0x90* p_entry)
{
	::memset(p_entry->m_unk0x00, 0xff, sizeof(p_entry->m_unk0x00));

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x2d:
			p_entry->m_unk0x84 = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2b:
			for (i = 0; i < 5; i++) {
				p_entry->m_unk0x18[i] = m_parser->ReadInteger();
			}
			p_entry->m_unk0x8c = TRUE;
			break;
		case GolFileParser::e_unknown0x2c:
			for (i = 0; i < 6; i++) {
				FUN_0046b1d0(&p_entry->m_unk0x24[i].m_left);
			}
			break;
		case GolFileParser::e_unknown0x2a:
			for (i = 0; i < 6; i++) {
				FUN_0046b210(p_entry->m_unk0x00[i].m_bytes);
			}
			p_entry->m_unk0x88 = TRUE;
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470110
void CeruleanEmperor0x4c::FUN_00470110(Entry0xa8* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x28:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0x90[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x3a:
			FUN_00470020(p_entry);
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004701a0
void CeruleanEmperor0x4c::FUN_004701a0(Entry0x100* p_entry)
{
	LegoS32 imageTripletCount = 0;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	if (m_parser->GetNextToken() == GolFileParser::e_rightCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		return;
	}

	UtopianPan0xa4** image = p_entry->m_utopianunk0xa8;
	do {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x3a:
			FUN_00470020(p_entry);
			break;
		case GolFileParser::e_unknown0x2c:
			FUN_0046b1d0(&p_entry->m_unk0xf0.m_left);
			break;
		case GolFileParser::e_unknown0x29:
			for (i = 0; i < 6; i++) {
				p_entry->m_unk0x90[i] = m_unk0x14->FindFontByName(m_parser->ReadString());
			}
			break;
		case GolFileParser::e_unknown0x28: {
			UtopianPan0xa4** imageCursor = image;
			for (i = 0; i < 6; i++) {
				*imageCursor = m_unk0x14->FindImageByName(m_parser->ReadString());
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
void CeruleanEmperor0x4c::FUN_004702e0(Entry0x150* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x3a:
			FUN_00470020(p_entry);
			break;
		case GolFileParser::e_unknown0x2f:
			p_entry->m_unk0xac = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x31:
			for (i = 0; i < p_entry->m_unk0xac; i++) {
				p_entry->m_unk0xb0[i] = m_parser->ReadInteger();
			}
			break;
		case GolFileParser::e_unknown0x30:
			for (i = 0; i < p_entry->m_unk0xac; i++) {
				FUN_0046b1d0(&p_entry->m_unk0xd0[i].m_left);
			}
			break;
		case GolFileParser::e_unknown0x28:
			p_entry->m_unk0xa8 = m_unk0x14->FindImageByName(m_parser->ReadString());
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x00470410
void CeruleanEmperor0x4c::FUN_00470410(Entry0x18* p_entry)
{
	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	while (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		LegoS32 i;

		switch (m_parser->GetCurrentToken()) {
		case GolFileParser::e_unknown0x2b:
			for (i = 0; i < 3; i++) {
				p_entry->m_unk0x00[i] = m_parser->ReadInteger();
			}
			break;
		case GolFileParser::e_unknown0x2d:
			p_entry->m_unk0x0c = m_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2f:
			p_entry->m_unk0x10 = m_parser->ReadInteger();
			p_entry->m_unk0x14 = m_parser->ReadInteger();
			break;
		default:
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			break;
		}
	}
}

// FUNCTION: LEGORACERS 0x004704b0
void CeruleanEmperor0x4c::FUN_004704b0(Entry0xbc* p_entry)
{
	LegoBool readBase = FALSE;
	LegoBool readSingle = FALSE;
	LegoBool readPair = FALSE;
	VisualState0x4* visualState;
	LegoS32 i;

	if (m_parser->GetNextToken() != GolFileParser::e_leftCurly) {
		m_parser->HandleUnexpectedToken(GolFileParser::e_leftCurly);
	}

	::memset(p_entry->m_unk0x9c, 0xff, sizeof(p_entry->m_unk0x9c));
	::memset(p_entry->m_unk0xac, 0xff, sizeof(p_entry->m_unk0xac));

	if (m_parser->GetNextToken() != GolFileParser::e_rightCurly) {
		do {
			switch (m_parser->GetCurrentToken()) {
			case GolFileParser::e_unknown0x3a:
				FUN_00470020(p_entry);
				readBase++;
				break;
			case GolFileParser::e_unknown0x35:
				p_entry->m_unk0x90 = static_cast<Entry0xa8*>(FUN_00470e60(m_parser->ReadString()));
				p_entry->m_unk0x94 = static_cast<Entry0xa8*>(FUN_00470e60(m_parser->ReadString()));
				readPair++;
				break;
			case GolFileParser::e_unknown0x34:
				p_entry->m_unk0x98 = static_cast<Entry0x2c*>(FUN_00470e60(m_parser->ReadString()));
				readSingle++;
				break;
			case GolFileParser::e_unknown0x2a:
				visualState = p_entry->m_unk0x9c;
				i = 4;
				do {
					FUN_0046b210(visualState->m_bytes);
					visualState++;
				} while (--i);

				visualState = p_entry->m_unk0xac;
				i = 4;
				do {
					FUN_0046b210(visualState->m_bytes);
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
void CeruleanEmperor0x4c::FUN_00470650(Entry0xbcWithImages* p_entry)
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
			case GolFileParser::e_unknown0x3a:
				FUN_00470020(p_entry);
				readBase++;
				break;
			case GolFileParser::e_unknown0x35:
				p_entry->m_unk0x90 = static_cast<Entry0x90*>(FUN_00470e60(m_parser->ReadString()));
				p_entry->m_unk0x94 = static_cast<Entry0x90*>(FUN_00470e60(m_parser->ReadString()));
				readPrimaryPair++;
				break;
			case GolFileParser::e_unknown0x32:
				p_entry->m_unk0x9c = static_cast<Entry0x90*>(FUN_00470e60(m_parser->ReadString()));
				p_entry->m_unk0x98 = static_cast<Entry0x90*>(FUN_00470e60(m_parser->ReadString()));
				readSecondaryPair++;
				break;
			case GolFileParser::e_unknown0x28:
				for (i = 0; i < 6; i++) {
					p_entry->m_unk0xa0[i] = m_unk0x14->FindImageByName(m_parser->ReadString());
				}
				break;
			case GolFileParser::e_unknown0x2b:
				p_entry->m_unk0xb8 = m_parser->ReadInteger();
				p_entry->m_unk0xba = m_parser->ReadInteger();
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
void CeruleanEmperor0x4c::FUN_004707e0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x24 = new Entry0x0c[entryCount];
	::memset(m_unk0x24, 0, sizeof(Entry0x0c) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x32) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x24[i]);
		FUN_0046fe20(&m_unk0x24[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470880
void CeruleanEmperor0x4c::FUN_00470880()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x28 = new Entry0x14[entryCount];
	::memset(m_unk0x28, 0, sizeof(Entry0x14) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x33) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x28[i]);
		FUN_0046feb0(&m_unk0x28[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470920
void CeruleanEmperor0x4c::FUN_00470920()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x2c = new Entry0x2c[entryCount];
	::memset(m_unk0x2c, 0, sizeof(Entry0x2c) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x34) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x2c[i]);
		FUN_0046ff70(&m_unk0x2c[i]);
	}
}

// FUNCTION: LEGORACERS 0x004709c0
void CeruleanEmperor0x4c::FUN_004709c0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x30 = new Entry0xa8[entryCount];
	::memset(m_unk0x30, 0, sizeof(Entry0xa8) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x35) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x30[i]);
		FUN_00470110(&m_unk0x30[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470a70
void CeruleanEmperor0x4c::FUN_00470a70()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x34 = new Entry0x100[entryCount];
	::memset(m_unk0x34, 0, sizeof(Entry0x100) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x36) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x34[i]);
		FUN_004701a0(&m_unk0x34[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470b10
void CeruleanEmperor0x4c::FUN_00470b10()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x38 = new Entry0x150[entryCount];
	::memset(m_unk0x38, 0, sizeof(Entry0x150) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x37) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x38[i]);
		FUN_004702e0(&m_unk0x38[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470bc0
void CeruleanEmperor0x4c::FUN_00470bc0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x3c = new Entry0x18[entryCount];
	::memset(m_unk0x3c, 0, sizeof(Entry0x18) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x38) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x3c[i]);
		FUN_00470410(&m_unk0x3c[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470c60
void CeruleanEmperor0x4c::FUN_00470c60()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x40 = new Entry0xbc[entryCount];
	::memset(m_unk0x40, 0, sizeof(Entry0xbc) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x39) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x40[i]);
		FUN_004704b0(&m_unk0x40[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470d10
void CeruleanEmperor0x4c::FUN_00470d10()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x44 = new Entry0xbcWithImages[entryCount];
	::memset(m_unk0x44, 0, sizeof(Entry0xbcWithImages) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3b) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x44[i]);
		FUN_00470650(&m_unk0x44[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470dc0
void CeruleanEmperor0x4c::FUN_00470dc0()
{
	LegoS32 entryCount = FUN_0046b170();
	m_unk0x48 = new Entry0x90[entryCount];
	::memset(m_unk0x48, 0, sizeof(Entry0x90) * entryCount);

	for (LegoS32 i = 0; i < entryCount; i++) {
		if (m_parser->GetNextToken() != GolFileParser::e_unknown0x3a) {
			m_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
		}

		GolName name;
		::strncpy(name, m_parser->ReadString(), sizeof(name));
		AddName(name, &m_unk0x48[i]);
		FUN_00470020(&m_unk0x48[i]);
	}
}

// FUNCTION: LEGORACERS 0x00470e60
void* CeruleanEmperor0x4c::FUN_00470e60(const LegoChar* p_name)
{
	GolName name;

	::strncpy(name, p_name, sizeof(name));

	void* result = GetName(name);
	if (!result && m_unk0x20) {
		return m_unk0x20->FUN_00470e60(p_name);
	}

	return result;
}
