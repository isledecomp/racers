#include "crimsonpebble0x228.h"

#include "amberlens0x344.h"
#include "audio/soundgroup.h"
#include "audio/soundinstance.h"
#include "audio/soundmanager.h"
#include "audio/spatialsoundinstance.h"
#include "awakekite0x20.h"
#include "bronzefalcon0xc8770.h"
#include "floatyboat0x28.h"
#include "gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golfont0xa0.h"
#include "golfonttable.h"
#include "golname.h"
#include "golstream.h"
#include "goltxtparser.h"
#include "mabmaterialanimation0x14.h"
#include "menuanimationlist.h"
#include "rectangle.h"
#include "saffronquartz0x2c.h"
#include "utopianpan0xa4.h"
#include "whitefalcon0x140.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CrimsonPebble0x228, 0x228)
DECOMP_SIZE_ASSERT(BluebellFog0x4, 0x04)
DECOMP_SIZE_ASSERT(CrimsonPebbleEvent0x14, 0x14)
DECOMP_SIZE_ASSERT(CrimsonPebbleEventValueSource0x2c, 0x2c)
DECOMP_SIZE_ASSERT(CrimsonPebbleEventValuePayload0x24, 0x24)
DECOMP_SIZE_ASSERT(CrimsonPebbleEventSelectorPayload0x28, 0x28)
DECOMP_SIZE_ASSERT(CrimsonPebbleEventVectorPayload0x44, 0x44)
DECOMP_SIZE_ASSERT(CrimsonPebbleEventLink0x0c, 0x0c)
DECOMP_SIZE_ASSERT(CrimsonPebbleEvent0x30, 0x30)
DECOMP_SIZE_ASSERT(CrimsonPebbleEvent0x48, 0x48)
DECOMP_SIZE_ASSERT(CrimsonPebbleEvent0x50, 0x50)
DECOMP_SIZE_ASSERT(CrimsonPebbleEvent0x50Derived, 0x50)
DECOMP_SIZE_ASSERT(CrimsonPebbleMenuAnimationEvent0x2c, 0x2c)
DECOMP_SIZE_ASSERT(CrimsonPebbleVisual0x58, 0x58)
DECOMP_SIZE_ASSERT(CrimsonPebbleVisual0x64, 0x64)
DECOMP_SIZE_ASSERT(CrimsonPebbleText0x70, 0x70)
DECOMP_SIZE_ASSERT(CrimsonPebbleAnimation0x33c::Entry0x8, 0x08)
DECOMP_SIZE_ASSERT(CrimsonPebbleAnimation0x33c::Runtime0x44, 0x44)
DECOMP_SIZE_ASSERT(CrimsonPebbleAnimation0x33c::Particle0x18c, 0x18c)
DECOMP_SIZE_ASSERT(CrimsonPebbleAnimation0x33c, 0x33c)

// GLOBAL: LEGORACERS 0x004b4ab0
const LegoFloat g_crimsonPebbleEvent0x30DefaultVolume = 1.0f;

// GLOBAL: LEGORACERS 0x004b4ab4
const LegoFloat g_crimsonPebbleEvent0x30DefaultPan = 0.0f;

// GLOBAL: LEGORACERS 0x004b4ab8
const LegoFloat g_crimsonPebbleEvent0x30DefaultFrequencyScale = 1.0f;

// STUB: LEGORACERS 0x004893f0
CrimsonPebbleAnimation0x33c::Particle0x18c::Particle0x18c()
{
	STUB(0x004893f0);
}

// STUB: LEGORACERS 0x00489440
CrimsonPebbleAnimation0x33c::Particle0x18c::~Particle0x18c()
{
	STUB(0x00489440);
}

// STUB: LEGORACERS 0x004897e0
void CrimsonPebbleAnimation0x33c::Particle0x18c::FUN_004897e0(LegoU32)
{
	STUB(0x004897e0);
}

// STUB: LEGORACERS 0x00489960
void CrimsonPebbleAnimation0x33c::Particle0x18c::FUN_00489960(BronzeFalcon0xc8770*)
{
	STUB(0x00489960);
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void CrimsonPebbleAnimation0x33c::Particle0x18c::FUN_004513d0(BronzeFalcon0xc8770*)
{
}

// FUNCTION: LEGORACERS 0x00489970
CrimsonPebbleAnimation0x33c::Entry0x8::Entry0x8()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00489980
CrimsonPebbleAnimation0x33c::Entry0x8::~Entry0x8()
{
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00489990
CrimsonPebbleAnimation0x33c::CrimsonPebbleAnimation0x33c()
{
	m_unk0x00c = NULL;
	m_unk0x010 = NULL;
	m_unk0x334 = 0;
	m_unk0x338 = 0;
}

// FUNCTION: LEGORACERS 0x00489a00
CrimsonPebbleAnimation0x33c::~CrimsonPebbleAnimation0x33c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00489a70
void CrimsonPebbleAnimation0x33c::Clear()
{
	if (m_nameEntries != NULL) {
		GolNameTable::Clear();
	}

	if (m_unk0x010 != NULL) {
		delete[] m_unk0x010;
		m_unk0x010 = NULL;
	}

	if (m_unk0x00c != NULL) {
		delete[] m_unk0x00c;
		m_unk0x00c = NULL;
	}

	m_unk0x334 = 0;
	m_unk0x338 = 0;
}

// STUB: LEGORACERS 0x00489af0
void CrimsonPebbleAnimation0x33c::FUN_00489af0(
	LegoU32,
	GolExport*,
	BronzeFalcon0xc8770*,
	MabMaterialAnimation0x14*,
	const LegoChar*,
	undefined4
)
{
	STUB(0x00489af0);
}

// FUNCTION: LEGORACERS 0x00489fa0
void CrimsonPebbleAnimation0x33c::FUN_00489fa0(LegoU32 p_elapsedMs)
{
	for (LegoU32 i = 0; i < m_unk0x338; i++) {
		if (m_unk0x00c[i].GetFlags() & 0x02) {
			m_unk0x00c[i].FUN_004897e0(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x00489ff0
void CrimsonPebbleAnimation0x33c::FUN_00489ff0(BronzeFalcon0xc8770* p_renderer)
{
	for (LegoU32 i = 0; i < m_unk0x338; i++) {
		if (m_unk0x00c[i].GetFlags() & 0x02) {
			m_unk0x00c[i].FUN_004513d0(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x0048a040
void CrimsonPebbleAnimation0x33c::FUN_0048a040(BronzeFalcon0xc8770* p_renderer)
{
	for (LegoU32 i = 0; i < m_unk0x338; i++) {
		if (m_unk0x00c[i].GetFlags() & 0x02) {
			m_unk0x00c[i].FUN_00489960(p_renderer);
		}
	}
}

// STUB: LEGORACERS 0x0048a090
CrimsonPebbleAnimation0x33c::Runtime0x44::Runtime0x44()
{
	STUB(0x0048a090);
}

// STUB: LEGORACERS 0x0048a0a0
CrimsonPebbleAnimation0x33c::Runtime0x44::~Runtime0x44()
{
	STUB(0x0048a0a0);
}

// FUNCTION: LEGORACERS 0x0049fd70
CrimsonPebbleEvent0x14::CrimsonPebbleEvent0x14()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0049fdb0
CrimsonPebbleEvent0x14::~CrimsonPebbleEvent0x14()
{
}

// FUNCTION: LEGORACERS 0x0049fdc0
void CrimsonPebbleEvent0x14::Reset()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x0c = 0;
	m_unk0x10 = 0;
}

// FUNCTION: LEGORACERS 0x0049fdd0
void CrimsonPebbleEvent0x14::VTable0x10(const GolVec3*, const GolVec3*, const GolVec3*)
{
	if (m_unk0x10 == 0) {
		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x0049fde0
void CrimsonPebbleEvent0x14::VTable0x0c(undefined4)
{
	if (m_unk0x10 == 0) {
		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x0049fdf0
void CrimsonPebbleEvent0x14::VTable0x08(undefined4 p_arg)
{
	if (m_unk0x10 == 0) {
		VTable0x0c(p_arg);
	}
}

// FUNCTION: LEGORACERS 0x0049fe10
void CrimsonPebbleEvent0x14::VTable0x04(undefined4 p_arg)
{
	if (m_unk0x10 == 0) {
		VTable0x08(p_arg);
	}
}

// STUB: LEGORACERS 0x0049ff70
void CrimsonPebbleEvent0x14::ParseCommonToken(
	GolFileParser* p_parser,
	GolFileParser::ParserTokenType p_token,
	CrimsonPebble0x228* p_owner
)
{
	GolName name;
	::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

	switch (p_token) {
	case GolFileParser::e_unknown0x5d:
		m_unk0x04 = p_owner->FUN_004a3240(name);
		m_unk0x08 = m_unk0x04;
		m_unk0x0c = m_unk0x04;
		if (m_unk0x04 == NULL) {
			LegoChar text[64];
			::strncpy(text, name, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": unable to find jointed model");
			GOL_FATALERROR_MESSAGE(text);
		}
		break;
	case GolFileParser::e_unknown0x5e:
		m_unk0x04 = p_owner->FUN_004a3230(name);
		m_unk0x08 = m_unk0x04;
		if (m_unk0x04 == NULL) {
			LegoChar text[64];
			::strncpy(text, name, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": unable to find model");
			GOL_FATALERROR_MESSAGE(text);
		}
		break;
	case GolFileParser::e_unknown0x5f:
		m_unk0x04 = p_owner->FUN_004a3250(name);
		m_unk0x08 = m_unk0x04;
		if (m_unk0x04 == NULL) {
			LegoChar text[64];
			::strncpy(text, name, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": unable to find bsp model");
			GOL_FATALERROR_MESSAGE(text);
		}
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CrimsonPebbleEvent0x14::VTable0x14()
{
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void CrimsonPebbleEvent0x14::VTable0x18()
{
}

// FUNCTION: LEGORACERS 0x004a00b0
CrimsonPebbleEventLink0x0c::CrimsonPebbleEventLink0x0c()
{
	m_unk0x00 = 0;
	m_event = NULL;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x004a00c0
void CrimsonPebbleEventLink0x0c::FUN_004a00c0(undefined4 p_unk0x04, CrimsonPebbleEvent0x14* p_event)
{
	m_unk0x00 = p_unk0x04;
	m_event = p_event;
}

// FUNCTION: LEGORACERS 0x004a00d0
void CrimsonPebbleEventLink0x0c::FUN_004a00d0()
{
	if (m_unk0x00) {
		m_event->VTable0x14();
	}
	else {
		m_event->VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a00f0
void CrimsonPebbleEventLink0x0c::FUN_004a00f0(CrimsonPebbleEventValuePayload0x24* p_payload)
{
	undefined4 value = p_payload->m_unk0x20->m_unk0x28;
	if (value) {
		if (m_unk0x00) {
			m_event->VTable0x04(value);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else {
		FUN_004a00d0();
	}
}

// FUNCTION: LEGORACERS 0x004a0120
void CrimsonPebbleEventLink0x0c::FUN_004a0120(CrimsonPebbleEventSelectorPayload0x28* p_payload)
{
	if (p_payload->m_unk0x20 == 2) {
		if (m_unk0x00) {
			m_event->VTable0x04(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else if (p_payload->m_unk0x20 == 3 || p_payload->m_unk0x20 == 1) {
		if (m_unk0x00) {
			m_event->VTable0x08(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
	else {
		if (m_unk0x00) {
			m_event->VTable0x0c(p_payload->m_unk0x24);
		}
		else {
			m_event->VTable0x18();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a0180
void CrimsonPebbleEventLink0x0c::FUN_004a0180(CrimsonPebbleEventVectorPayload0x44* p_payload)
{
	GolVec3 vector0 = p_payload->m_unk0x20;
	GolVec3 vector1 = p_payload->m_unk0x2c;
	GolVec3 vector2 = p_payload->m_unk0x38;

	if (m_unk0x00) {
		m_event->VTable0x10(&vector0, &vector1, &vector2);
	}
	else {
		m_event->VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a0200
void CrimsonPebbleEventLink0x0c::FUN_004a0200(void*)
{
	FUN_004a00d0();
}

// FUNCTION: LEGORACERS 0x004a0210
CrimsonPebble0x228::CrimsonPebble0x228()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a03b0
CrimsonPebble0x228::~CrimsonPebble0x228()
{
	FUN_004a0bf0();
}

// FUNCTION: LEGORACERS 0x004a0530
void CrimsonPebble0x228::Reset()
{
	m_unk0x04 = NULL;
	m_unk0x08 = 0;
	m_soundManager = NULL;
	m_unk0x10 = 0;
	m_unk0x64 = NULL;
	m_unk0x68 = 0;
	m_unk0x6c = NULL;
	m_unk0x70 = NULL;
	m_unk0x74 = NULL;
	m_unk0x78 = 0;
	m_unk0x7c = NULL;
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	m_unk0x88 = NULL;
	m_unk0x8c = NULL;
	m_unk0x90 = 0;
	m_unk0x94 = NULL;
	m_unk0x98 = NULL;
	m_unk0x9c = 0;
	m_unk0xa0 = NULL;
	m_unk0xa4 = NULL;
	m_unk0xb4 = 0;
	m_unk0xb8 = NULL;
	m_unk0xc8 = 0;
	m_unk0xcc = NULL;
	m_unk0xdc = 0;
	m_unk0xe0 = NULL;
	m_unk0xf0 = 0;
	m_unk0xf4 = NULL;
	m_unk0x104 = 0;
	m_unk0x108 = NULL;
	m_unk0x118 = 0;
	m_unk0x11c = NULL;
	m_unk0x12c = 0;
	m_unk0x130 = NULL;
	m_unk0x134 = 0;
	m_unk0x138 = NULL;
	m_unk0x148 = 0;
	m_unk0x14c = NULL;
	m_unk0x15c = 0;
	m_unk0x160 = NULL;
	m_unk0x170 = 0;
	m_unk0x174 = NULL;
	m_unk0x184 = 0;
	m_unk0x188 = NULL;
	m_unk0x198 = 0;
	m_unk0x19c = NULL;
	m_unk0x1ac = 0;
	m_unk0x1b0 = NULL;
	m_unk0x1c0 = 0;
	m_unk0x1c4 = NULL;
	m_unk0x1d4 = 0;
	m_unk0x1d8 = NULL;
	m_unk0x1e8 = 0;
	m_unk0x1ec = NULL;
	m_unk0x1fc = 0;
	m_unk0x200 = NULL;
	m_unk0x210 = 0;
	m_unk0x214 = NULL;
	m_stringTable = NULL;
}

// FUNCTION: LEGORACERS 0x004a0680
LegoBool32 CrimsonPebble0x228::HasFileWithSuffix(const LegoChar* p_fileName, const LegoChar* p_suffix)
{
	LegoU32 length = ::strlen(p_fileName) + ::strlen(p_suffix) + 1;
	LegoChar* path = new LegoChar[length];
	if (path == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	::strcpy(path, p_fileName);
	::strcat(path, p_suffix);

	LegoS32 result = GolStream::FindFile(path);
	delete[] path;

	return result == GolStream::e_ioSuccess;
}

// FUNCTION: LEGORACERS 0x004a0730
void CrimsonPebble0x228::FUN_004a0730(
	GolExport* p_golExport,
	BronzeFalcon0xc8770* p_renderer,
	SoundManager* p_soundManager,
	SaffronQuartz0x2c* p_unk0x10,
	const LegoChar* p_fileName,
	undefined4 p_binary
)
{
	GolFileParser* parser;

	if (m_unk0x04) {
		FUN_004a0bf0();
	}

	if (p_binary) {
		if (!HasFileWithSuffix(p_fileName, ".ceb")) {
			return;
		}
		parser = new GolBinParser();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		parser->SetSuffix(".ceb");
	}
	else {
		parser = new GolTxtParser2();
		if (!parser) {
			GolFatalError(c_golErrorOutOfMemory, NULL, 0);
		}
		if (!HasFileWithSuffix(p_fileName, parser->GetSuffix())) {
			delete parser;
			return;
		}
	}

	m_unk0x04 = p_golExport;
	m_unk0x08 = p_renderer;
	m_unk0x10 = p_unk0x10;
	m_soundManager = p_soundManager;

	p_soundManager->AddActiveSoundNode(&m_unk0x14);
	parser->OpenFileForRead(p_fileName);
	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_004a0ff0(parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_004a12e0(parser);
			break;
		case GolFileParser::e_unknown0x5c:
			FUN_004a15e0(parser);
			break;
		case GolFileParser::e_unknown0x29:
			FUN_004a1760(parser);
			break;
		case GolFileParser::e_unknown0x2a:
			FUN_004a18d0(parser);
			break;
		case GolFileParser::e_unknown0x2b:
			FUN_004a1a40(parser);
			break;
		case GolFileParser::e_unknown0x2f:
			FUN_004a1c00(parser);
			break;
		case GolFileParser::e_unknown0x36:
			FUN_004a1dc0(parser);
			break;
		case GolFileParser::e_unknown0x3c:
			FUN_004a1f80(parser);
			break;
		case GolFileParser::e_unknown0x60:
			FUN_004a20f0(parser);
			break;
		case GolFileParser::e_unknown0x3f:
			LoadTextEntries(parser);
			break;
		case GolFileParser::e_unknown0x4d:
			FUN_004a2520(parser);
			break;
		case GolFileParser::e_unknown0x50:
			FUN_004a2730(parser, 0x50, m_unk0x134, m_unk0x138, m_unk0x13c);
			break;
		case GolFileParser::e_unknown0x51:
			FUN_004a2730(parser, 0x51, m_unk0x148, m_unk0x14c, m_unk0x150);
			break;
		case GolFileParser::e_unknown0x52:
			FUN_004a2730(parser, 0x52, m_unk0x15c, m_unk0x160, m_unk0x164);
			break;
		case GolFileParser::e_unknown0x53:
			FUN_004a2730(parser, 0x53, m_unk0x170, m_unk0x174, m_unk0x178);
			break;
		case GolFileParser::e_unknown0x54:
			FUN_004a2730(parser, 0x54, m_unk0x184, m_unk0x188, m_unk0x18c);
			break;
		case GolFileParser::e_unknown0x55:
			FUN_004a2730(parser, 0x55, m_unk0x198, m_unk0x19c, m_unk0x1a0);
			break;
		case GolFileParser::e_unknown0x56:
			FUN_004a2730(parser, 0x56, m_unk0x1ac, m_unk0x1b0, m_unk0x1b4);
			break;
		case GolFileParser::e_unknown0x57:
			FUN_004a2730(parser, 0x57, m_unk0x1c0, m_unk0x1c4, m_unk0x1c8);
			break;
		case GolFileParser::e_unknown0x58:
			FUN_004a2730(parser, 0x58, m_unk0x1d4, m_unk0x1d8, m_unk0x1dc);
			break;
		case GolFileParser::e_unknown0x59:
			FUN_004a2730(parser, 0x59, m_unk0x1e8, m_unk0x1ec, m_unk0x1f0);
			break;
		case GolFileParser::e_unknown0x5a:
			FUN_004a2730(parser, 0x5a, m_unk0x1fc, m_unk0x200, m_unk0x204);
			break;
		case GolFileParser::e_unknown0x5b:
			FUN_004a2730(parser, 0x5b, m_unk0x210, m_unk0x214, m_unk0x218);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}
		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	FUN_004a1240(p_binary);
	FUN_004a14e0();
	FUN_004a16f0();
	FUN_004a1850(p_binary);
	FUN_004a19c0(p_binary);
	FUN_004a24e0();
	FUN_004a26f0();
}

// STUB: LEGORACERS 0x004a0bf0
void CrimsonPebble0x228::FUN_004a0bf0()
{
	STUB(0x4a0bf0);
}

// FUNCTION: LEGORACERS 0x004a0ff0
void CrimsonPebble0x228::FUN_004a0ff0(GolFileParser* p_parser)
{
	if (m_unk0x6c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x68 = p_parser->ReadInteger();
	if (m_unk0x68 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x6c = new CrimsonPebbleAnimation0x33c[m_unk0x68];
	m_unk0x70 = new MabMaterialAnimation0x14[m_unk0x68];
	m_unk0x74 = new LegoChar[m_unk0x68 * 9];
	if (m_unk0x6c == NULL || m_unk0x70 == NULL || m_unk0x74 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x68) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x74[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0x74[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x68);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1240
void CrimsonPebble0x228::FUN_004a1240(undefined4 p_binary)
{
	if (m_unk0x74 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x70[i].VTable0x04(m_unk0x08, &m_unk0x74[i * 9], p_binary);
			m_unk0x6c[i].FUN_00489af0(3, m_unk0x04, m_unk0x08, &m_unk0x70[i], &m_unk0x74[i * 9], p_binary);
		}

		delete[] m_unk0x74;
		m_unk0x74 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a12e0
void CrimsonPebble0x228::FUN_004a12e0(GolFileParser* p_parser)
{
	if (m_unk0x7c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x78 = p_parser->ReadInteger();
	if (m_unk0x78 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x7c = new GolStringTable[m_unk0x78];
	m_unk0x80 = new LegoChar[m_unk0x78 * 13];
	if (m_unk0x7c == NULL || m_unk0x80 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;
	LegoU32 offset = 0;

	if (i < m_unk0x78) {
		LegoU32 tableOffset = offset;

		do {
			::strncpy(&m_unk0x80[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			m_unk0x80[offset + sizeof(GolName)] = '\0';
			::strcat(&m_unk0x80[offset], ".srf");

			((GolStringTable*) ((LegoU8*) m_unk0x7c + tableOffset))->UseOwnedBuffers();

			i++;
			offset += 13;
			tableOffset += sizeof(GolStringTable);
		} while (i < m_unk0x78);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a14e0
void CrimsonPebble0x228::FUN_004a14e0()
{
	if (m_unk0x80 != NULL) {
		LegoU32 i = 0;

		if (i < m_unk0x78) {
			LegoU32 tableOffset = 0;
			LegoU32 fileNameOffset = 0;

			do {
				((GolStringTable*) ((LegoU8*) m_unk0x7c + tableOffset))->UseOwnedBuffers();

				if (!((GolStringTable*) ((LegoU8*) m_unk0x7c + tableOffset))->Load(&m_unk0x80[fileNameOffset])) {
					LegoChar text[48];
					::strcpy(text, "Unable to open: ");
					::strcat(text, &m_unk0x80[fileNameOffset]);
					GOL_FATALERROR_MESSAGE(text);
				}

				i++;
				tableOffset += sizeof(GolStringTable);
				fileNameOffset += 13;
			} while (i < m_unk0x78);
		}

		delete[] m_unk0x80;
		m_unk0x80 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a15e0
void CrimsonPebble0x228::FUN_004a15e0(GolFileParser* p_parser)
{
	if (m_unk0x88 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x84 = p_parser->ReadInteger();
	if (m_unk0x84 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x88 = new SoundGroup*[m_unk0x84];
	if (m_unk0x88 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x8c = new LegoChar[m_unk0x84 * 9];
	if (m_unk0x8c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x84) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x8c[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			m_unk0x8c[offset + sizeof(GolName)] = '\0';

			SoundGroup* soundGroup = m_soundManager->CreateSoundGroup();
			i++;
			offset += 9;
			m_unk0x88[i - 1] = soundGroup;
		} while (i < m_unk0x84);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a16f0
void CrimsonPebble0x228::FUN_004a16f0()
{
	if (m_unk0x8c != NULL) {
		for (LegoU32 i = 0; i < m_unk0x84; i++) {
			m_unk0x88[i]->Load(&m_unk0x8c[i * 9]);
		}

		delete[] m_unk0x8c;
		m_unk0x8c = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1760
void CrimsonPebble0x228::FUN_004a1760(GolFileParser* p_parser)
{
	if (m_unk0x94 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x90 = p_parser->ReadInteger();
	if (m_unk0x90 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x94 = new GolFontTable*[m_unk0x90];
	m_unk0x98 = new LegoChar[m_unk0x90 * 9];
	if (m_unk0x94 == NULL || m_unk0x98 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x90) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0x98[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0x98[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x90);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1850
void CrimsonPebble0x228::FUN_004a1850(undefined4 p_binary)
{
	if (m_unk0x98 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x90; i++) {
			m_unk0x94[i] = m_unk0x04->CreateFontTable();
			m_unk0x94[i]->LoadFontDefinitions(m_unk0x08, &m_unk0x98[i * 9], p_binary);
		}

		delete[] m_unk0x98;
		m_unk0x98 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a18d0
void CrimsonPebble0x228::FUN_004a18d0(GolFileParser* p_parser)
{
	if (m_unk0xa0 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x9c = p_parser->ReadInteger();
	if (m_unk0x9c == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xa0 = new AwakeKite0x20*[m_unk0x9c];
	m_unk0xa4 = new LegoChar[m_unk0x9c * 9];
	if (m_unk0xa0 == NULL || m_unk0xa4 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 i = 0;

	if (i < m_unk0x9c) {
		LegoU32 offset = 0;

		do {
			::strncpy(&m_unk0xa4[offset], p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			i++;
			m_unk0xa4[offset + sizeof(GolName)] = '\0';
			offset += 9;
		} while (i < m_unk0x9c);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a19c0
void CrimsonPebble0x228::FUN_004a19c0(undefined4 p_binary)
{
	if (m_unk0xa4 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x9c; i++) {
			m_unk0xa0[i] = m_unk0x04->VTable0x34();
			m_unk0xa0[i]->LoadImageDefinitions(m_unk0x08, &m_unk0xa4[i * 9], p_binary);
		}

		delete[] m_unk0xa4;
		m_unk0xa4 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a1a40
void CrimsonPebble0x228::FUN_004a1a40(GolFileParser* p_parser)
{
	if (m_unk0xb8 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xb4 = p_parser->ReadInteger();
	if (m_unk0xb4 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xa8.Allocate(m_unk0xb4);
	m_unk0xb8 = new CrimsonPebbleEvent0x48[m_unk0xb4];
	if (m_unk0xb8 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xb4; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2b);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xa8.AddName(name, &m_unk0xb8[i]);
		m_unk0xb8[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1c00
void CrimsonPebble0x228::FUN_004a1c00(GolFileParser* p_parser)
{
	if (m_unk0xcc != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xc8 = p_parser->ReadInteger();
	if (m_unk0xc8 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xbc.Allocate(m_unk0xc8);
	m_unk0xcc = new CrimsonPebbleEvent0x30[m_unk0xc8];
	if (m_unk0xcc == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xc8; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xbc.AddName(name, &m_unk0xcc[i]);
		m_unk0xcc[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1dc0
void CrimsonPebble0x228::FUN_004a1dc0(GolFileParser* p_parser)
{
	if (m_unk0xe0 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xdc = p_parser->ReadInteger();
	if (m_unk0xdc == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xd0.Allocate(m_unk0xdc);
	m_unk0xe0 = new CrimsonPebbleEvent0x50Derived[m_unk0xdc];
	if (m_unk0xe0 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xdc; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x36);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xd0.AddName(name, &m_unk0xe0[i]);
		m_unk0xe0[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a1f80
void CrimsonPebble0x228::FUN_004a1f80(GolFileParser* p_parser)
{
	if (m_unk0xf4 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0xf0 = p_parser->ReadInteger();
	if (m_unk0xf0 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xe4.Allocate(m_unk0xf0);
	m_unk0xf4 = new CrimsonPebbleEvent0x50[m_unk0xf0];
	if (m_unk0xf4 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0xf0; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3c);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xe4.AddName(name, &m_unk0xf4[i]);
		m_unk0xf4[i].Parse(p_parser, this);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a20f0
void CrimsonPebble0x228::FUN_004a20f0(GolFileParser* p_parser)
{
	if (m_unk0x108 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x104 = p_parser->ReadInteger();
	if (m_unk0x104 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0xf8.Allocate(m_unk0x104);
	m_unk0x108 = new CrimsonPebbleMenuAnimationEvent0x2c[m_unk0x104];
	m_unk0x64 = new MenuAnimationList();
	if (m_unk0x108 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	if (m_unk0x64 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x64->Allocate(2);

	for (LegoU32 i = 0; i < m_unk0x104; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x60);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0xf8.AddName(name, &m_unk0x108[i]);
		m_unk0x108[i].Parse(p_parser, this, m_unk0x64, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2310
void CrimsonPebble0x228::LoadTextEntries(GolFileParser* p_parser)
{
	if (m_unk0x11c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x118 = p_parser->ReadInteger();
	if (m_unk0x118 == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x10c.Allocate(m_unk0x118);
	m_unk0x11c = new CrimsonPebbleText0x70[m_unk0x118];
	if (m_unk0x11c == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x118; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3f);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0x10c.AddName(name, &m_unk0x11c[i]);
		m_unk0x11c[i].Parse(p_parser, this, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a24e0
void CrimsonPebble0x228::FUN_004a24e0()
{
	for (LegoU32 i = 0; i < m_unk0x118; i++) {
		m_unk0x11c[i].RefreshString(this, m_unk0x08);
	}
}

// FUNCTION: LEGORACERS 0x004a2520
void CrimsonPebble0x228::FUN_004a2520(GolFileParser* p_parser)
{
	if (m_unk0x130 != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	m_unk0x12c = p_parser->ReadInteger();
	if (m_unk0x12c == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	m_unk0x120.Allocate(m_unk0x12c);
	m_unk0x130 = new CrimsonPebbleVisual0x64[m_unk0x12c];
	if (m_unk0x130 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x12c; i++) {
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x4d);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
		m_unk0x120.AddName(name, &m_unk0x130[i]);
		m_unk0x130[i].Parse(p_parser, this, m_unk0x08);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a26f0
void CrimsonPebble0x228::FUN_004a26f0()
{
	for (LegoU32 i = 0; i < m_unk0x12c; i++) {
		m_unk0x130[i].FUN_004a3910(m_unk0x08);
	}
}

// STUB: LEGORACERS 0x004a2730
void CrimsonPebble0x228::FUN_004a2730(
	GolFileParser* p_parser,
	LegoU32 p_token,
	undefined4& p_unk0x08,
	CrimsonPebbleEventLink0x0c*& p_unk0x0c,
	GolNameTable& p_unk0x10
)
{
	if (p_unk0x0c != NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	p_parser->ReadLeftBracket();
	LegoU32 count = p_parser->ReadInteger();
	if (count == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	p_parser->ReadRightBracket();
	p_parser->ReadLeftCurly();

	p_unk0x08 = count;
	p_unk0x10.Allocate(count);

	CrimsonPebbleEventLink0x0c* links = new CrimsonPebbleEventLink0x0c[count];
	if (links == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}
	p_unk0x0c = links;

	CrimsonPebbleEventLink0x0c* link = links;
	CrimsonPebbleEventLink0x0c* end = links + count;
	while (link < end) {
		GolName name;

		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(p_token));
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		CrimsonPebbleEventLink0x0c* existing = static_cast<CrimsonPebbleEventLink0x0c*>(p_unk0x10.GetName(name));
		if (existing != NULL) {
			link->SetNext(existing->GetNext());
			existing->SetNext(link);
		}
		else {
			p_unk0x10.AddName(name, link);
		}

		p_parser->ReadLeftCurly();

		GolFileParser::ParserTokenType targetToken = p_parser->GetNextToken();
		GolFileParser::ParserTokenType modeToken = p_parser->GetNextToken();
		undefined4 mode;
		if (modeToken == GolFileParser::e_unknown0x4e) {
			mode = 1;
		}
		else if (modeToken == GolFileParser::e_unknown0x4f) {
			mode = 0;
		}
		else {
			p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
			mode = 0;
		}

		GolName targetName;
		::strncpy(targetName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));

		CrimsonPebbleEvent0x14* event = NULL;
		switch (targetToken) {
		case GolFileParser::e_unknown0x2b:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0xa8.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x2f:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0xbc.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x36:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0xd0.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3c:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0xe4.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x60:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0xf8.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x3f:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0x10c.GetName(targetName));
			break;
		case GolFileParser::e_unknown0x4d:
			event = static_cast<CrimsonPebbleEvent0x14*>(m_unk0x120.GetName(targetName));
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		if (event == NULL) {
			LegoChar text[64];
			::strncpy(text, targetName, sizeof(GolName));
			text[sizeof(GolName)] = '\0';
			::strcat(text, ": Unable to find effect");
			GOL_FATALERROR_MESSAGE(text);
		}

		link->FUN_004a00c0(mode, event);
		p_parser->ReadRightCurly();
		link++;
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004a2ac0
void CrimsonPebble0x228::VTable0x00(void*, void* p_name, void*)
{
	if (m_unk0x13c.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x13c.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->FUN_004a00d0();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b00
void CrimsonPebble0x228::VTable0x04(void*, void* p_name, void*)
{
	if (m_unk0x150.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x150.GetName(static_cast<const LegoChar*>(p_name)));
		while (link != NULL) {
			link->FUN_004a00d0();
			link = link->GetNext();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b40
void CrimsonPebble0x228::VTable0x08(void*, void* p_name, void* p_payload)
{
	if (m_unk0x164.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x164.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventValuePayload0x24* payload = static_cast<CrimsonPebbleEventValuePayload0x24*>(p_payload);

			while (link != NULL) {
				link->FUN_004a00f0(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2b80
void CrimsonPebble0x228::VTable0x0c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x178.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x178.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventValuePayload0x24* payload = static_cast<CrimsonPebbleEventValuePayload0x24*>(p_payload);

			while (link != NULL) {
				link->FUN_004a00f0(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2bc0
void CrimsonPebble0x228::VTable0x10(void*, void* p_name, void* p_payload)
{
	if (m_unk0x18c.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x18c.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventSelectorPayload0x28* payload =
				static_cast<CrimsonPebbleEventSelectorPayload0x28*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0120(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c00
void CrimsonPebble0x228::VTable0x14(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1a0.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x1a0.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventSelectorPayload0x28* payload =
				static_cast<CrimsonPebbleEventSelectorPayload0x28*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0120(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c40
void CrimsonPebble0x228::VTable0x18(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1b4.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x1b4.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventVectorPayload0x44* payload = static_cast<CrimsonPebbleEventVectorPayload0x44*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0180(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2c80
void CrimsonPebble0x228::VTable0x1c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1c8.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x1c8.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			CrimsonPebbleEventVectorPayload0x44* payload = static_cast<CrimsonPebbleEventVectorPayload0x44*>(p_payload);

			while (link != NULL) {
				link->FUN_004a0180(payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2cc0
void CrimsonPebble0x228::VTable0x20(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1dc.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x1dc.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d00
void CrimsonPebble0x228::VTable0x24(void*, void* p_name, void* p_payload)
{
	if (m_unk0x1f0.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x1f0.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d40
void CrimsonPebble0x228::VTable0x28(void*, void* p_name, void* p_payload)
{
	if (m_unk0x204.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x204.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2d80
void CrimsonPebble0x228::VTable0x2c(void*, void* p_name, void* p_payload)
{
	if (m_unk0x218.GetNameEntries() != NULL) {
		CrimsonPebbleEventLink0x0c* link =
			static_cast<CrimsonPebbleEventLink0x0c*>(m_unk0x218.GetName(static_cast<const LegoChar*>(p_name)));
		if (link != NULL) {
			while (link != NULL) {
				link->FUN_004a0200(p_payload);
				link = link->GetNext();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2dc0
void CrimsonPebble0x228::FUN_004a2dc0(LegoU32 p_elapsedMs)
{
	if (m_unk0x04 != NULL) {
		LegoFloat elapsedSeconds = (LegoS32) p_elapsedMs * 0.001f;
		LegoU32 i;

		for (i = 0; i < m_unk0xb4; i++) {
			CrimsonPebbleEvent0x48* entries = m_unk0xb8;
			entries[i].FUN_004a4d10(elapsedSeconds);
		}

		for (i = 0; i < m_unk0xc8; i++) {
			m_unk0xcc[i].FUN_004a40f0();
		}

		for (i = 0; i < m_unk0xdc; i++) {
			m_unk0xe0[i].FUN_004a44f0();
		}

		for (i = 0; i < m_unk0x68; i++) {
			CrimsonPebbleAnimation0x33c* entries = m_unk0x6c;
			entries[i].FUN_00489fa0(p_elapsedMs);
		}

		for (i = 0; i < m_unk0x118; i++) {
			m_unk0x11c[i].FUN_004a3550(elapsedSeconds);
		}

		for (i = 0; i < m_unk0x12c; i++) {
			m_unk0x130[i].FUN_004a3550(elapsedSeconds);
		}

		for (i = 0; i < m_unk0xf0; i++) {
			m_unk0xf4[i].FUN_004a3df0(p_elapsedMs);
		}

		if (m_unk0x64 != NULL) {
			m_unk0x64->Update(p_elapsedMs);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a2f30
void CrimsonPebble0x228::FUN_004a2f30(BronzeFalcon0xc8770* p_renderer)
{
	if (m_unk0x04 != NULL) {
		FUN_004a2f80(p_renderer->GetUnk0x0c());

		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x6c[i].FUN_00489ff0(p_renderer);
		}
	}
}

// STUB: LEGORACERS 0x004a2f80
void CrimsonPebble0x228::FUN_004a2f80(AmberLens0x344* p_lens)
{
	GolVec3 position;
	GolVec3 right;
	GolVec3 forward;

	p_lens->GetUnk0x04()->GetPosition(&position);
	p_lens->GetUnk0x04()->GetRight(&right);
	p_lens->GetUnk0x04()->GetForward(&forward);

	SoundNode* node = &m_unk0x14;

	node->m_position.m_x = position.m_x;
	node->m_position.m_y = position.m_y;
	node->m_position.m_z = position.m_z;
	node->m_unk0x44 = 1;

	forward.m_x = -forward.m_x;
	forward.m_y = -forward.m_y;
	forward.m_z = -forward.m_z;

	node->m_volume = right.m_x;
	node->m_unk0x1c = right.m_y;
	node->m_unk0x20 = right.m_z;
	node->m_unk0x24 = forward.m_x;
	node->m_unk0x28 = forward.m_y;
	node->m_frequencyScale = forward.m_z;

	node->m_orientation.m_x = (node->m_unk0x28 * node->m_unk0x20) - (node->m_frequencyScale * node->m_unk0x1c);
	node->m_orientation.m_y = (node->m_frequencyScale * node->m_volume) - (node->m_unk0x20 * node->m_unk0x24);
	node->m_orientation.m_z = (node->m_unk0x1c * node->m_unk0x24) - (node->m_unk0x28 * node->m_volume);
	GolMath::NormalizeVector3(
		reinterpret_cast<GolVec3&>(node->m_orientation),
		reinterpret_cast<GolVec3*>(&node->m_orientation)
	);

	node->m_unk0x44 = 1;
}

// FUNCTION: LEGORACERS 0x004a3070
void CrimsonPebble0x228::FUN_004a3070(BronzeFalcon0xc8770* p_renderer)
{
	if (m_unk0x04 != NULL) {
		for (LegoU32 i = 0; i < m_unk0x68; i++) {
			m_unk0x6c[i].FUN_0048a040(p_renderer);
		}
	}
}

// FUNCTION: LEGORACERS 0x004a30b0
void CrimsonPebble0x228::FUN_004a30b0(BronzeFalcon0xc8770* p_renderer)
{
	if (m_unk0x04 != NULL) {
		p_renderer->VTable0xe8(FALSE);

		LegoU32 i;
		for (i = 0; i < m_unk0x12c; i++) {
			m_unk0x130[i].FUN_004a35a0(p_renderer);
		}

		for (i = 0; i < m_unk0x118; i++) {
			m_unk0x11c[i].FUN_004a35a0(p_renderer);
		}

		if (m_unk0x64 != NULL) {
			m_unk0x64->Draw(p_renderer);
		}

		p_renderer->VTable0xe4();
	}
}

// FUNCTION: LEGORACERS 0x004a3150
void CrimsonPebble0x228::FUN_004a3150()
{
	LegoU32 i;

	for (i = 0; i < m_unk0xb4; i++) {
		m_unk0xb8[i].VTable0x18();
	}

	for (i = 0; i < m_unk0xc8; i++) {
		m_unk0xcc[i].VTable0x18();
	}

	for (i = 0; i < m_unk0xdc; i++) {
		m_unk0xe0[i].VTable0x18();
	}

	for (i = 0; i < m_unk0x118; i++) {
		m_unk0x11c[i].VTable0x18();
	}

	for (i = 0; i < m_unk0x12c; i++) {
		m_unk0x130[i].VTable0x18();
	}
}

// FUNCTION: LEGORACERS 0x004a3230
FloatyBoat0x28* CrimsonPebble0x228::FUN_004a3230(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406e30(p_name);
}

// FUNCTION: LEGORACERS 0x004a3240
FloatyBoat0x28* CrimsonPebble0x228::FUN_004a3240(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406e80(p_name);
}

// FUNCTION: LEGORACERS 0x004a3250
FloatyBoat0x28* CrimsonPebble0x228::FUN_004a3250(const LegoChar* p_name)
{
	return m_unk0x10->FUN_00406ed0(p_name);
}

// FUNCTION: LEGORACERS 0x004a3260
GolStringTable* CrimsonPebble0x228::GetStringTableByIndex(LegoU32 p_index)
{
	if (p_index == 0 && m_stringTable != NULL) {
		return m_stringTable;
	}

	return &m_unk0x7c[p_index];
}

// FUNCTION: LEGORACERS 0x004a37e0
CrimsonPebbleVisual0x64::CrimsonPebbleVisual0x64()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3830
CrimsonPebbleVisual0x64::~CrimsonPebbleVisual0x64()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a3880
void CrimsonPebbleVisual0x64::Reset()
{
	m_unk0x58 = NULL;
	m_unk0x5c[0] = '\0';
	CrimsonPebbleVisual0x58::Reset();
}

// FUNCTION: LEGORACERS 0x004a3890
void CrimsonPebbleVisual0x64::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, WhiteFalcon0x140* p_renderer)
{
	p_parser->ReadLeftCurly();
	m_flags = 3;

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		do {
			if (token != GolFileParser::e_unknown0x4d) {
				ParseVisualToken(p_parser, token, p_owner, p_renderer);
			}
			else {
				::strncpy(m_unk0x5c, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
			}

			token = p_parser->GetNextToken();
		} while (token != GolFileParser::e_rightCurly);
	}

	if (m_unk0x5c[0] == '\0') {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3910
void CrimsonPebbleVisual0x64::FUN_004a3910(BronzeFalcon0xc8770* p_renderer)
{
	m_unk0x58 = p_renderer->FindImageByName(m_unk0x5c);
	if (m_unk0x58 == NULL) {
		LegoChar text[64];
		::strncpy(text, m_unk0x5c, sizeof(GolName));
		text[sizeof(GolName)] = '\0';
		::strcat(text, ": Unable to find image");
		GOL_FATALERROR_MESSAGE(text);
	}
}

// FUNCTION: LEGORACERS 0x004a3990
void CrimsonPebbleVisual0x64::Clear()
{
	Reset();
	CrimsonPebbleEvent0x14::Reset();
}

// FUNCTION: LEGORACERS 0x004a39b0
void CrimsonPebbleVisual0x64::VTable0x1c(LegoS32* p_width, LegoS32* p_height)
{
	*p_width = m_unk0x58->GetWidth();
	*p_height = m_unk0x58->GetHeight();
}

// FUNCTION: LEGORACERS 0x004a39d0
void CrimsonPebbleVisual0x64::VTable0x20(
	WhiteFalcon0x140* p_renderer,
	LegoS32 p_x,
	LegoS32 p_y,
	undefined4 p_width,
	undefined4 p_height,
	LegoFloat,
	LegoFloat
)
{
	Rect destRect;
	destRect.m_left = p_x;
	destRect.m_right = p_x + p_width;
	destRect.m_top = p_y;
	destRect.m_bottom = p_y + p_height;

	if (m_flags & 0x100) {
		m_unk0x58->m_unk0x4a.m_u32 = m_colorPacked;
	}

	p_renderer->VTable0x78(m_unk0x58, 0, &destRect, NULL);

	if (m_flags & 0x100) {
		union {
			ColorRGBA m_color;
			LegoU32 m_colorPacked;
		} color;

		color.m_color.m_red = 0xff;
		color.m_color.m_grn = 0xff;
		color.m_color.m_blu = 0xff;
		color.m_color.m_alp = 0xff;
		m_unk0x58->m_unk0x4a.m_u32 = color.m_colorPacked;
	}
}

// FUNCTION: LEGORACERS 0x004a3a50
CrimsonPebbleEvent0x50::CrimsonPebbleEvent0x50()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3aa0
void CrimsonPebbleEvent0x50::Reset()
{
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c[0] = '\0';
	m_unk0x24.m_x = 0.0f;
	m_unk0x24.m_y = 0.0f;
	m_unk0x24.m_z = 0.0f;
	m_unk0x30.m_x = 0.0f;
	m_unk0x30.m_y = 0.0f;
	m_unk0x30.m_z = 0.0f;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
}

// FUNCTION: LEGORACERS 0x004a3ad0
void CrimsonPebbleEvent0x50::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x3d: {
			LegoU32 index = p_parser->ReadInteger();
			if (index >= p_owner->GetAnimationCount()) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
			}

			m_unk0x14 = p_owner->GetAnimationByIndex(index);
			::strncpy(m_unk0x1c, p_parser->ReadString(), sizeof(GolName));
			break;
		}
		case GolFileParser::e_unknown0x39:
			m_unk0x24.m_x = p_parser->ReadFloat();
			m_unk0x24.m_y = p_parser->ReadFloat();
			m_unk0x24.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 1;
			break;
		case GolFileParser::e_unknown0x3e:
			m_unk0x30.m_x = p_parser->ReadFloat();
			m_unk0x30.m_y = p_parser->ReadFloat();
			m_unk0x30.m_z = p_parser->ReadFloat();
			m_unk0x3c.m_x = p_parser->ReadFloat();
			m_unk0x3c.m_y = p_parser->ReadFloat();
			m_unk0x3c.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 2;
			break;
		case GolFileParser::e_unknown0x3a:
			m_unk0x48 |= 4;
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x4c = p_parser->ReadInteger();
			m_unk0x48 |= 8;
			break;
		default:
			ParseCommonToken(p_parser, token, p_owner);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// STUB: LEGORACERS 0x004a3c20
void CrimsonPebbleEvent0x50::VTable0x14()
{
	if (m_unk0x18 == NULL) {
		FUN_004a3db0();
	}
}

// STUB: LEGORACERS 0x004a3c90
void CrimsonPebbleEvent0x50::VTable0x10(const GolVec3*, const GolVec3*, const GolVec3*)
{
	if (m_unk0x18 == NULL) {
		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a3d70
void CrimsonPebbleEvent0x50::VTable0x0c(undefined4 p_arg)
{
	if (m_unk0x18 == NULL) {
		if (m_unk0x04 == NULL) {
			m_unk0x04 = reinterpret_cast<FloatyBoat0x28*>(p_arg);
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a3d90
void CrimsonPebbleEvent0x50::VTable0x04(undefined4 p_arg)
{
	if (m_unk0x18 == NULL) {
		if (m_unk0x0c == NULL) {
			m_unk0x0c = reinterpret_cast<FloatyBoat0x28*>(p_arg);
		}

		VTable0x14();
	}
}

// STUB: LEGORACERS 0x004a3db0
void CrimsonPebbleEvent0x50::FUN_004a3db0()
{
	STUB(0x004a3db0);
}

// STUB: LEGORACERS 0x004a3dd0
void CrimsonPebbleEvent0x50::VTable0x18()
{
	STUB(0x004a3dd0);
	m_unk0x18 = NULL;
}

// STUB: LEGORACERS 0x004a3df0
void CrimsonPebbleEvent0x50::FUN_004a3df0(LegoU32)
{
	STUB(0x004a3df0);
}

// FUNCTION: LEGORACERS 0x004a3e70
CrimsonPebbleEvent0x30::CrimsonPebbleEvent0x30()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3ec0
void CrimsonPebbleEvent0x30::Reset()
{
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = g_crimsonPebbleEvent0x30DefaultVolume;
	m_unk0x20 = 0;
	m_unk0x24 = g_crimsonPebbleEvent0x30DefaultFrequencyScale;
	m_unk0x28 = g_crimsonPebbleEvent0x30DefaultPan;
	m_unk0x2c = 0;
	m_unk0x2e = 0;
}

// FUNCTION: LEGORACERS 0x004a3ef0
void CrimsonPebbleEvent0x30::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner)
{
	if (m_unk0x14 != NULL) {
		Reset();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		if (!ParseToken(p_parser, p_owner, token)) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		token = p_parser->GetNextToken();
	}

	if (m_unk0x14 == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// FUNCTION: LEGORACERS 0x004a3f60
LegoBool32 CrimsonPebbleEvent0x30::ParseToken(
	GolFileParser* p_parser,
	CrimsonPebble0x228* p_owner,
	GolFileParser::ParserTokenType p_token
)
{
	switch (p_token) {
	case GolFileParser::e_unknown0x30: {
		LegoU32 index = p_parser->ReadInteger();
		if (index >= p_owner->GetSoundGroupCount()) {
			p_parser->HandleUnexpectedToken(GolFileParser::e_invalidValue);
		}

		m_unk0x14 = p_owner->GetSoundGroupByIndex(index);
		m_unk0x2e = static_cast<LegoU16>(p_parser->ReadInteger());
		return TRUE;
	}
	case GolFileParser::e_unknown0x31:
		m_unk0x20 = p_parser->ReadInteger();
		return TRUE;
	case GolFileParser::e_unknown0x32:
		m_unk0x1c = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x33:
		m_unk0x24 = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x34:
		m_unk0x28 = p_parser->ReadFloat();
		return TRUE;
	case GolFileParser::e_unknown0x35:
		m_unk0x2c = 1;
		return TRUE;
	default:
		return FALSE;
	}
}

// FUNCTION: LEGORACERS 0x004a4070
void CrimsonPebbleEvent0x30::VTable0x14()
{
	if (m_unk0x18 == NULL) {
		m_unk0x18 = m_unk0x14->CreateSoundInstance(m_unk0x2e);
		m_unk0x18->Play(m_unk0x2c);
		m_unk0x18->SetVolume(m_unk0x1c);
		m_unk0x18->SetPan(m_unk0x28);
		m_unk0x18->SetFrequencyScale(m_unk0x24);
		m_unk0x18->SetPriority(m_unk0x20);
	}
}

// FUNCTION: LEGORACERS 0x004a40d0
void CrimsonPebbleEvent0x30::VTable0x18()
{
	if (m_unk0x18 != NULL) {
		m_unk0x14->DestroySoundInstance(m_unk0x18);
		m_unk0x18 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a40f0
void CrimsonPebbleEvent0x30::FUN_004a40f0()
{
	if (m_unk0x18 != NULL) {
		if (!m_unk0x18->IsPlaying()) {
			VTable0x18();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4110
CrimsonPebbleEvent0x50Derived::CrimsonPebbleEvent0x50Derived()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4160
void CrimsonPebbleEvent0x50Derived::Reset()
{
	m_unk0x30 = NULL;
	m_unk0x34 = 100.0f;
	m_unk0x38 = 500.0f;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48 = 0;
	m_unk0x4c = 0;
	CrimsonPebbleEvent0x30::Reset();
	CrimsonPebbleEvent0x14::Reset();
}

// STUB: LEGORACERS 0x004a41a0
void CrimsonPebbleEvent0x50Derived::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner)
{
	if (m_unk0x14 != NULL) {
		VTable0x14();
	}

	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x37:
			m_unk0x34 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x38:
			m_unk0x38 = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x39:
			m_unk0x3c.m_x = p_parser->ReadFloat();
			m_unk0x3c.m_y = p_parser->ReadFloat();
			m_unk0x3c.m_z = p_parser->ReadFloat();
			m_unk0x48 |= 1;
			break;
		case GolFileParser::e_unknown0x3a:
			m_unk0x48 = (m_unk0x48 & ~4) | 2;
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x4c = p_parser->ReadInteger();
			m_unk0x48 = (m_unk0x48 & ~2) | 4;
			break;
		default:
			if (!ParseToken(p_parser, p_owner, token)) {
				ParseCommonToken(p_parser, token, p_owner);
			}
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (m_unk0x14 == NULL) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_expectedKeyword);
	}
}

// STUB: LEGORACERS 0x004a42b0
void CrimsonPebbleEvent0x50Derived::VTable0x14()
{
	STUB(0x004a42b0);
}

// STUB: LEGORACERS 0x004a43a0
void CrimsonPebbleEvent0x50Derived::FUN_004a43a0(const GolVec3*)
{
	STUB(0x004a43a0);
}

// FUNCTION: LEGORACERS 0x004a4450
void CrimsonPebbleEvent0x50Derived::VTable0x10(const GolVec3* p_a, const GolVec3*, const GolVec3*)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x04 == NULL && !(m_unk0x48 & 1)) {
			FUN_004a43a0(p_a);
		}
		else {
			VTable0x14();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4480
void CrimsonPebbleEvent0x50Derived::VTable0x0c(undefined4 p_arg)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x04 == NULL) {
			m_unk0x04 = reinterpret_cast<FloatyBoat0x28*>(p_arg);
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a44a0
void CrimsonPebbleEvent0x50Derived::VTable0x04(undefined4 p_arg)
{
	if (m_unk0x30 == NULL) {
		if (m_unk0x0c == NULL) {
			m_unk0x0c = reinterpret_cast<FloatyBoat0x28*>(p_arg);
			m_unk0x04 = reinterpret_cast<FloatyBoat0x28*>(p_arg);
		}

		VTable0x14();
	}
}

// STUB: LEGORACERS 0x004a44c0
void CrimsonPebbleEvent0x50Derived::VTable0x18()
{
	STUB(0x004a44c0);
	m_unk0x30 = NULL;
}

// STUB: LEGORACERS 0x004a44f0
void CrimsonPebbleEvent0x50Derived::FUN_004a44f0()
{
	STUB(0x004a44f0);
}

// FUNCTION: LEGORACERS 0x004a4970
CrimsonPebbleMenuAnimationEvent0x2c::CrimsonPebbleMenuAnimationEvent0x2c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a49c0
void CrimsonPebbleMenuAnimationEvent0x2c::Reset()
{
	m_unk0x14 = NULL;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x20 = 0;
	m_unk0x21 = 0;
	m_unk0x22 = 0;
	m_unk0x23 = 0;
}

// STUB: LEGORACERS 0x004a49e0
void CrimsonPebbleMenuAnimationEvent0x2c::Parse(
	GolFileParser* p_parser,
	CrimsonPebble0x228* p_owner,
	MenuAnimationList* p_animationList,
	BronzeFalcon0xc8770* p_renderer
)
{
	GolName materialName;
	LegoBool hasMaterialName = FALSE;

	m_unk0x14 = p_animationList;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x61:
			m_unk0x24 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x62: {
			GolFileParser::ParserTokenType mode = p_parser->GetNextToken();
			if (mode == GolFileParser::e_unknown0x63) {
				m_unk0x28 |= 1;
			}
			else if (mode == GolFileParser::e_unknown0x64) {
				m_unk0x28 |= 2;
			}
			else {
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			}
			break;
		}
		case GolFileParser::e_unknown0x65:
			::strncpy(materialName, p_parser->ReadString(), sizeof(GolName));
			hasMaterialName = TRUE;
			break;
		case GolFileParser::e_unknown0x66:
			m_unk0x20 = static_cast<LegoU8>(p_parser->ReadInteger());
			m_unk0x21 = static_cast<LegoU8>(p_parser->ReadInteger());
			m_unk0x22 = static_cast<LegoU8>(p_parser->ReadInteger());
			break;
		default:
			ParseCommonToken(p_parser, token, p_owner);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (hasMaterialName) {
		m_unk0x18 = reinterpret_cast<DuskwindBananaRelic0x24*>(p_renderer->FindMaterialByName(materialName));
	}
}

// FUNCTION: LEGORACERS 0x004a4af0
void CrimsonPebbleMenuAnimationEvent0x2c::VTable0x14()
{
	if (m_unk0x28 & 1) {
		m_unk0x1c = m_unk0x14->Activate(m_unk0x24, TRUE, m_unk0x18, NULL);
	}
	else if (m_unk0x28 & 2) {
		m_unk0x1c = m_unk0x14->Activate(m_unk0x24, FALSE, m_unk0x18, NULL);
	}

	if (m_unk0x1c != NULL) {
		m_unk0x1c->SetColor(m_colorPacked);
	}
}

// FUNCTION: LEGORACERS 0x004a4b40
void CrimsonPebbleMenuAnimationEvent0x2c::VTable0x18()
{
	if (m_unk0x1c != NULL) {
		m_unk0x14->Deactivate(m_unk0x1c);
		m_unk0x1c = NULL;
	}
}

// FUNCTION: LEGORACERS 0x004a4b60
CrimsonPebbleEvent0x48::CrimsonPebbleEvent0x48()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4bb0
void CrimsonPebbleEvent0x48::Reset()
{
	m_unk0x08 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0.0f;
	m_unk0x34 = 0.0f;
	m_unk0x38 = 0.0f;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_unk0x44 = 0.0f;
}

// FUNCTION: LEGORACERS 0x004a4be0
void CrimsonPebbleEvent0x48::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner)
{
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2c:
			m_unk0x18 = p_parser->ReadInteger();
			m_unk0x1c = p_parser->ReadInteger();
			m_unk0x20 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x24 = p_parser->ReadInteger();
			m_unk0x28 = p_parser->ReadInteger();
			m_unk0x2c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2e:
			m_unk0x3c = p_parser->ReadFloat();
			m_unk0x40 = p_parser->ReadFloat();
			m_unk0x44 = p_parser->ReadFloat();
			break;
		default:
			ParseCommonToken(p_parser, token, p_owner);
			break;
		}

		token = p_parser->GetNextToken();
	}
}

// FUNCTION: LEGORACERS 0x004a4ca0
void CrimsonPebbleEvent0x48::VTable0x14()
{
	if (m_unk0x14 == 0 && m_unk0x08 != NULL) {
		m_unk0x14 = 1;
		m_unk0x30 = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x24));
		m_unk0x34 = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x28));
		m_unk0x38 = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x2c));
		FUN_004a4da0();
	}
}

// FUNCTION: LEGORACERS 0x004a4cd0
void CrimsonPebbleEvent0x48::VTable0x08(undefined4 p_arg)
{
	if (m_unk0x14 == 0) {
		if (m_unk0x08 == NULL) {
			m_unk0x08 = reinterpret_cast<FloatyBoat0x28*>(p_arg);
		}

		VTable0x14();
	}
}

// FUNCTION: LEGORACERS 0x004a4cf0
void CrimsonPebbleEvent0x48::VTable0x18()
{
	if (m_unk0x14 != 0) {
		m_unk0x14 = 0;
		if (m_unk0x08 != NULL) {
			m_unk0x08->VTable0x28();
		}
	}
}

// FUNCTION: LEGORACERS 0x004a4d10
void CrimsonPebbleEvent0x48::FUN_004a4d10(LegoFloat p_elapsedSeconds)
{
	if (m_unk0x14 != 0) {
		if (m_unk0x08 != 0) {
			LegoFloat deltaX = m_unk0x3c * p_elapsedSeconds;
			LegoFloat deltaY = m_unk0x40 * p_elapsedSeconds;
			LegoFloat deltaZ = m_unk0x44 * p_elapsedSeconds;

			if (static_cast<LegoS32>(deltaX) || static_cast<LegoS32>(deltaY) || static_cast<LegoS32>(deltaZ)) {
				m_unk0x30 += deltaX;
				m_unk0x34 += deltaY;
				m_unk0x38 += deltaZ;
				FUN_004a4da0();
			}
		}
	}
}

// STUB: LEGORACERS 0x004a4da0
void CrimsonPebbleEvent0x48::FUN_004a4da0()
{
	STUB(0x004a4da0);
}
