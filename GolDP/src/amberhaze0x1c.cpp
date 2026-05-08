#include "amberhaze0x1c.h"

#include "duskwindbananarelic0x24.h"
#include "golbinparser.h"
#include "golerror.h"
#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(AmberHaze0x1c, 0x1c)

// FUNCTION: GOLDP 0x100261b0
AmberHaze0x1c::AmberHaze0x1c()
{
	m_renderer = NULL;
	m_next = NULL;
	m_unk0x14 = NULL;
	m_numItems = 0;
}

// FUNCTION: GOLDP 0x100261f0
AmberHaze0x1c::~AmberHaze0x1c()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026270
void AmberHaze0x1c::VTable0x24(WhiteFalcon0x140* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_unk0x14 = NULL;
	GolFileParser* parser;

	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".mdb");
	}
	else {
		parser = new MdbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);
	parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
	m_numItems = parser->FUN_100327e0();

	if (m_numItems == 0) {
		parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_numItems);
	VTable0x14();
	LegoU32 i;
	LegoU32 j;
	LegoChar textureName[8];
	LegoU8 fullIntensity = 0xff;

	for (i = 0; i < m_numItems; i++) {
		parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		DuskWindName0x8 name;
		::strncpy(
			name.m_unk0x0,
			parser->ReadStringWithMaxLength(sizeOfArray(name.m_unk0x0)),
			sizeOfArray(name.m_unk0x0)
		);
		DuskwindBananaRelic0x24* material = VTable0x28(i);
		AddName(name.m_unk0x0, material);
		parser->ReadLeftCurly();
		DuskWindBananaRelicParams params(fullIntensity);

		GolFileParser::ParserTokenType token = parser->GetNextToken();
		while (token != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x28:
				params.m_unk0x08.m_unk0x0 = parser->ReadInteger();
				params.m_unk0x08.m_unk0x1 = parser->ReadInteger();
				params.m_unk0x08.m_unk0x2 = parser->ReadInteger();
				params.m_unk0x08.m_unk0x3 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x29:
				params.m_unk0x0c.m_unk0x0 = parser->ReadInteger();
				params.m_unk0x0c.m_unk0x1 = parser->ReadInteger();
				params.m_unk0x0c.m_unk0x2 = parser->ReadInteger();
				params.m_unk0x0c.m_unk0x3 = parser->ReadInteger();
				break;
			case GolFileParser::e_unknown0x2a:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit2;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit1;
				break;
			case GolFileParser::e_unknown0x2b:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit1;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit2;
				break;
			case GolFileParser::e_unknown0x2c:
				::strncpy(textureName, parser->ReadStringWithMaxLength(8), 8);
				params.m_unk0x04 = p_renderer->FindTextureByName(textureName);
				if (params.m_unk0x04 == NULL) {
					char message[128];
					::strcpy(message, "Mat def file references unknown texture: ");
					::strcat(message, textureName);
					GOL_FATALERROR_MESSAGE(message);
				}
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit3;
				break;
			case GolFileParser::e_unknown0x2d:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit4;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit5;
				break;
			case GolFileParser::e_unknown0x2e:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit5;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit4;
				break;
			case GolFileParser::e_unknown0x2f:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit7;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit6;
				switch (parser->GetNextToken()) {
				case GolFileParser::e_unknown0x30:
					params.m_unk0x10 = 0;
					break;
				case GolFileParser::e_unknown0x31:
					params.m_unk0x10 = 1;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x32:
					params.m_unk0x10 = 2;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x33:
					params.m_unk0x10 = 3;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x34:
					params.m_unk0x10 = 4;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x35:
					params.m_unk0x10 = 5;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				case GolFileParser::e_unknown0x36:
					params.m_unk0x10 = 6;
					break;
				case GolFileParser::e_unknown0x37:
					params.m_unk0x10 = 7;
					params.m_unk0x11 = parser->ReadInteger();
					break;
				default:
					if (params.m_unk0x10 != 0 && params.m_unk0x10 != 6) {
						params.m_unk0x11 = parser->ReadInteger();
					}
					break;
				}
				break;
			case GolFileParser::e_unknown0x38: {
				undefined* ptr = &params.m_unk0x12;
				params.m_unk0x00 &=
					~(DuskwindBananaRelic0x24::c_flag0x08Bit12 | DuskwindBananaRelic0x24::c_flag0x08Bit9);
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit13;
				for (j = 0; j < 2; j++) {
					switch (parser->GetNextToken()) {
					case GolFileParser::e_unknown0x39:
						*ptr = 0;
						break;
					case GolFileParser::e_unknown0x3a:
						*ptr = 1;
						break;
					case GolFileParser::e_unknown0x3b:
						*ptr = 2;
						break;
					case GolFileParser::e_unknown0x3c:
						*ptr = 3;
						break;
					case GolFileParser::e_unknown0x3d:
						*ptr = 4;
						break;
					case GolFileParser::e_unknown0x3e:
						*ptr = 5;
						break;
					case GolFileParser::e_unknown0x3f:
						*ptr = 6;
						break;
					case GolFileParser::e_unknown0x40:
						*ptr = 7;
						break;
					case GolFileParser::e_unknown0x41:
						*ptr = 8;
						break;
					case GolFileParser::e_unknown0x42:
						*ptr = 9;
						break;
					case GolFileParser::e_unknown0x43:
						*ptr = 10;
						break;
					default:
						parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
						break;
					}
					ptr = &params.m_unk0x13;
				}
			} break;
			case GolFileParser::e_unknown0x44:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit11;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit10;
				break;
			case GolFileParser::e_unknown0x45:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit10;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit11;
				break;
			case GolFileParser::e_unknown0x47:
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit14;
				break;
			case GolFileParser::e_unknown0x48:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit16;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit15;
				break;
			case GolFileParser::e_unknown0x49:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit15;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit16;
				break;
			case GolFileParser::e_unknown0x4a:
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit17;
				break;
			case GolFileParser::e_unknown0x4b:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit20;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit19;
				break;
			case GolFileParser::e_unknown0x4c:
				params.m_unk0x00 &= ~DuskwindBananaRelic0x24::c_flag0x08Bit22;
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit21;
				break;
			case GolFileParser::e_unknown0x46:
			case GolFileParser::e_unknown0x4e:
				params.m_unk0x13 = parser->ReadInteger();
				params.m_unk0x00 &=
					~(DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit13);
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit12;
				break;
			case GolFileParser::e_unknown0x4f:
				params.m_unk0x13 = parser->ReadInteger();
				params.m_unk0x00 = (params.m_unk0x00 & ~(DuskwindBananaRelic0x24::c_flag0x08Bit8 |
														 DuskwindBananaRelic0x24::c_flag0x08Bit13)) |
								   (DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit12);
				break;
			case GolFileParser::e_unknown0x4d:
			case GolFileParser::e_unknown0x50:
				params.m_unk0x13 = parser->ReadInteger();
				params.m_unk0x00 &=
					~(DuskwindBananaRelic0x24::c_flag0x08Bit8 | DuskwindBananaRelic0x24::c_flag0x08Bit13);
				params.m_unk0x00 |= DuskwindBananaRelic0x24::c_flag0x08Bit9 | DuskwindBananaRelic0x24::c_flag0x08Bit12;
				break;
			default:
				parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}
			token = parser->GetNextToken();
		}
		material->m_unk0x18 = name;
		material->FUN_100257e0(m_renderer, params);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	FUN_10026970();
	delete parser;
}

// STUB: GOLDP 0x10026970
void AmberHaze0x1c::FUN_10026970()
{
	LegoU32 i;
	if (m_unk0x14 != NULL) {
		for (i = 0; i < m_numItems; i++) {
			DuskwindBananaRelic0x24* item = VTable0x28(i);
			if (!(item->GetUnk0x08() & DuskwindBananaRelic0x24::c_flagBit0)) {
#if 0
				m_unk0x14->VTable0x00(i, buffer);
				item->FUN_100257e0(m_renderer, buffer);
#else
				// TODO
				STUB(0x10026970);
#endif
				VTable0x18(i);
			}
		}
	}
	else {
		for (i = 0; i < m_numItems; i++) {
			DuskwindBananaRelic0x24* item = VTable0x28(i);
			if (!(item->GetUnk0x08() & DuskwindBananaRelic0x24::c_flagBit0)) {
				VTable0x18(i);
			}
		}
	}
}

// FUNCTION: GOLDP 0x10026a00
void AmberHaze0x1c::VTable0x20(WhiteFalcon0x140* p_renderer, undefined4* p_arg2, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_unk0x14 = p_arg2;
	m_numItems = p_capacity;
	GolNameTable::Allocate(p_capacity);
	VTable0x14();
	FUN_10026970();
}

// FUNCTION: GOLDP 0x10026a50
void AmberHaze0x1c::Clear()
{
	m_numItems = 0;

	if (m_renderer != NULL) {
		m_renderer->RemoveMaterialList(this);
		m_renderer = NULL;
	}

	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}
}

// FUNCTION: GOLDP 0x10026a80
void AmberHaze0x1c::VTable0x1c(WhiteFalcon0x140* p_renderer, LegoU32 p_capacity)
{
	if (m_renderer != NULL) {
		Clear();
	}

	m_renderer = p_renderer;
	p_renderer->AddMaterialList(this);
	m_numItems = p_capacity;
	GolNameTable::Allocate(p_capacity);
	VTable0x14();
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void AmberHaze0x1c::VTable0x0c()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void AmberHaze0x1c::VTable0x10()
{
	// empty
}
