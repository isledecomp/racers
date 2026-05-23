#include "crimsonpebble0x228.h"

#include "audio/soundmanager.h"
#include "bronzefalcon0xc8770.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golfont0xa0.h"
#include "golname.h"
#include "golstream.h"
#include "goltxtparser.h"
#include "mabmaterialanimation0x14.h"
#include "menuanimationlist.h"
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
DECOMP_SIZE_ASSERT(CrimsonPebbleVisual0x58, 0x58)
DECOMP_SIZE_ASSERT(CrimsonPebbleVisual0x64, 0x64)
DECOMP_SIZE_ASSERT(CrimsonPebbleText0x70, 0x70)
DECOMP_SIZE_ASSERT(CrimsonPebbleAnimation0x33c, 0x33c)

// STUB: LEGORACERS 0x00489fa0
void CrimsonPebbleAnimation0x33c::FUN_00489fa0(LegoU32)
{
	STUB(0x00489fa0);
}

// STUB: LEGORACERS 0x00489ff0
void CrimsonPebbleAnimation0x33c::FUN_00489ff0(BronzeFalcon0xc8770*)
{
	STUB(0x00489ff0);
}

// STUB: LEGORACERS 0x0048a040
void CrimsonPebbleAnimation0x33c::FUN_0048a040(BronzeFalcon0xc8770*)
{
	STUB(0x0048a040);
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

// STUB: LEGORACERS 0x004a0ff0
void CrimsonPebble0x228::FUN_004a0ff0(GolFileParser* p_parser)
{
	// ...
	m_unk0x70 = new MabMaterialAnimation0x14[m_unk0x68];

	// TODO
	STUB(0x004a0ff0);
}

// STUB: LEGORACERS 0x004a1240
void CrimsonPebble0x228::FUN_004a1240(undefined4)
{
	STUB(0x004a1240);
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

// STUB: LEGORACERS 0x004a14e0
void CrimsonPebble0x228::FUN_004a14e0()
{
	STUB(0x004a14e0);
}

// STUB: LEGORACERS 0x004a15e0
void CrimsonPebble0x228::FUN_004a15e0(GolFileParser* p_parser)
{
	STUB(0x004a15e0);
}

// STUB: LEGORACERS 0x004a16f0
void CrimsonPebble0x228::FUN_004a16f0()
{
	STUB(0x004a16f0);
}

// STUB: LEGORACERS 0x004a1760
void CrimsonPebble0x228::FUN_004a1760(GolFileParser* p_parser)
{
	STUB(0x004a1760);
}

// STUB: LEGORACERS 0x004a1850
void CrimsonPebble0x228::FUN_004a1850(undefined4)
{
	STUB(0x004a1850);
}

// STUB: LEGORACERS 0x004a18d0
void CrimsonPebble0x228::FUN_004a18d0(GolFileParser* p_parser)
{
	STUB(0x004a18d0);
}

// STUB: LEGORACERS 0x004a19c0
void CrimsonPebble0x228::FUN_004a19c0(undefined4)
{
	STUB(0x004a19c0);
}

// STUB: LEGORACERS 0x004a1a40
void CrimsonPebble0x228::FUN_004a1a40(GolFileParser* p_parser)
{
	STUB(0x004a1a40);
}

// STUB: LEGORACERS 0x004a1c00
void CrimsonPebble0x228::FUN_004a1c00(GolFileParser* p_parser)
{
	STUB(0x004a1c00);
}

// STUB: LEGORACERS 0x004a1dc0
void CrimsonPebble0x228::FUN_004a1dc0(GolFileParser* p_parser)
{
	STUB(0x004a1dc0);
}

// STUB: LEGORACERS 0x004a1f80
void CrimsonPebble0x228::FUN_004a1f80(GolFileParser* p_parser)
{
	STUB(0x004a1f80);
}

// STUB: LEGORACERS 0x004a20f0
void CrimsonPebble0x228::FUN_004a20f0(GolFileParser* p_parser)
{
	STUB(0x004a20f0);
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

// STUB: LEGORACERS 0x004a2520
void CrimsonPebble0x228::FUN_004a2520(GolFileParser* p_parser)
{
	STUB(0x004a2520);
}

// STUB: LEGORACERS 0x004a26f0
void CrimsonPebble0x228::FUN_004a26f0()
{
	STUB(0x004a26f0);
}

// STUB: LEGORACERS 0x004a2730
void CrimsonPebble0x228::FUN_004a2730(
	GolFileParser* p_parser,
	undefined4 p_unk0x04,
	undefined4& p_unk0x08,
	CrimsonPebbleEventLink0x0c*& p_unk0x0c,
	GolNameTable& p_unk0x10
)
{
	STUB(0x004a2730);
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
void CrimsonPebble0x228::FUN_004a2f80(AmberLens0x344*)
{
	STUB(0x004a2f80);
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

// FUNCTION: LEGORACERS 0x004a3260
GolStringTable* CrimsonPebble0x228::GetStringTableByIndex(LegoU32 p_index)
{
	if (p_index == 0 && m_stringTable != NULL) {
		return m_stringTable;
	}

	return &m_unk0x7c[p_index];
}

// FUNCTION: LEGORACERS 0x004a3280
CrimsonPebbleVisual0x58::CrimsonPebbleVisual0x58()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a32f0
CrimsonPebbleVisual0x58::~CrimsonPebbleVisual0x58()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a3340
void CrimsonPebbleVisual0x58::Reset()
{
	m_color.m_alp = 0xff;
	m_unk0x14 = 0.0f;
	m_unk0x18 = 0.0f;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0.0f;
	m_unk0x28 = 0.0f;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0.0f;
	m_unk0x38 = 0.0f;
	m_unk0x3c = 0.0f;
	m_unk0x40 = 0.0f;
	m_color.m_red = 0;
	m_color.m_grn = 0;
	m_color.m_blu = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x004a3380
void CrimsonPebbleVisual0x58::ParseVisualToken(
	GolFileParser* p_parser,
	GolFileParser::ParserTokenType p_token,
	CrimsonPebble0x228*,
	WhiteFalcon0x140*
)
{
	switch (p_token) {
	case GolFileParser::e_unknown0x43:
		m_unk0x14 = p_parser->ReadFloat();
		m_flags = (m_flags & ~1) | 4;
		break;
	case GolFileParser::e_unknown0x44:
		m_unk0x18 = p_parser->ReadFloat();
		m_flags = (m_flags & ~2) | 8;
		break;
	case GolFileParser::e_unknown0x45:
		m_flags = (m_flags & ~4) | 1;
		break;
	case GolFileParser::e_unknown0x46:
		m_flags = (m_flags & ~8) | 2;
		break;
	case GolFileParser::e_unknown0x47:
		m_unk0x24 = p_parser->ReadFloat();
		m_flags |= 0x10;
		break;
	case GolFileParser::e_unknown0x48:
		m_unk0x28 = p_parser->ReadFloat();
		m_flags |= 0x20;
		break;
	case GolFileParser::e_unknown0x49:
		m_unk0x34 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4a:
		m_unk0x38 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4b:
		m_unk0x3c = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x4c:
		m_unk0x40 = p_parser->ReadFloat();
		break;
	case GolFileParser::e_unknown0x66:
		m_color.m_red = p_parser->ReadInteger();
		m_color.m_grn = p_parser->ReadInteger();
		m_color.m_blu = p_parser->ReadInteger();
		m_flags |= 0x100;
		break;
	default:
		p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
	}
}

// FUNCTION: LEGORACERS 0x004a3500
void CrimsonPebbleVisual0x58::Clear()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a3510
void CrimsonPebbleVisual0x58::VTable0x14()
{
	if (!(m_flags & 0x40) && m_unk0x10 == 0) {
		LegoU32 flags = m_flags | 0xc0;

		m_unk0x1c = m_unk0x14;
		m_unk0x20 = m_unk0x18;
		m_unk0x2c = m_unk0x24;
		m_unk0x30 = m_unk0x28;
		m_flags = flags;
	}
}

// FUNCTION: LEGORACERS 0x004a3540
void CrimsonPebbleVisual0x58::VTable0x18()
{
	m_flags &= ~0x40;
}

// FUNCTION: LEGORACERS 0x004a3550
void CrimsonPebbleVisual0x58::FUN_004a3550(LegoFloat p_elapsedSeconds)
{
	if ((m_flags & 0x40) && !(m_flags & 0x80)) {
		m_unk0x1c += m_unk0x34 * p_elapsedSeconds;
		m_unk0x20 += m_unk0x38 * p_elapsedSeconds;
		m_unk0x2c += m_unk0x3c * p_elapsedSeconds;
		m_unk0x30 += m_unk0x40 * p_elapsedSeconds;
	}
}

// STUB: LEGORACERS 0x004a35a0
void CrimsonPebbleVisual0x58::FUN_004a35a0(BronzeFalcon0xc8770*)
{
	STUB(0x004a35a0);
}

// STUB: LEGORACERS 0x004a3df0
void CrimsonPebbleEvent0x50::FUN_004a3df0(LegoU32)
{
	STUB(0x004a3df0);
}

// STUB: LEGORACERS 0x004a40f0
void CrimsonPebbleEvent0x30::FUN_004a40f0()
{
	STUB(0x004a40f0);
}

// STUB: LEGORACERS 0x004a44f0
void CrimsonPebbleEvent0x50::FUN_004a44f0()
{
	STUB(0x004a44f0);
}

// FUNCTION: LEGORACERS 0x004a45b0
CrimsonPebbleText0x70::CrimsonPebbleText0x70()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a4610
CrimsonPebbleText0x70::~CrimsonPebbleText0x70()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x004a4670
void CrimsonPebbleText0x70::Reset()
{
	m_rawString = NULL;
	m_font = NULL;
	m_fontName[0] = '\0';
	m_stringTableIndex = 0;
	m_stringIndex = 0;
	CrimsonPebbleVisual0x58::Reset();
}

// FUNCTION: LEGORACERS 0x004a4690
void CrimsonPebbleText0x70::Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, WhiteFalcon0x140* p_renderer)
{
	p_parser->ReadLeftCurly();
	m_flags = 3;

	GolFileParser::ParserTokenType token;
	while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x40:
			m_stringTableIndex = p_parser->ReadInteger();
			m_stringIndex = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x41: {
			LegoChar* text = p_parser->ReadString();
			m_rawString = new LegoChar[::strlen(text) + 1];
			if (m_rawString == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			::strcpy(m_rawString, text);
			break;
		}
		case GolFileParser::e_unknown0x42:
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
void CrimsonPebbleText0x70::RefreshString(CrimsonPebble0x228* p_owner, WhiteFalcon0x140* p_renderer)
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
void CrimsonPebbleText0x70::Clear()
{
	m_string.Reset();

	if (m_rawString != NULL) {
		delete[] m_rawString;
	}

	Reset();
	CrimsonPebbleEvent0x14::Reset();
}

// FUNCTION: LEGORACERS 0x004a4890
void CrimsonPebbleText0x70::VTable0x1c(LegoS32* p_width, LegoS32* p_height)
{
	if (m_rawString != NULL) {
		m_font->FUN_00408ca0(m_rawString, p_width, p_height);
	}
	else {
		m_font->FUN_00408be0(&m_string, p_width, p_height);
	}
}

// FUNCTION: LEGORACERS 0x004a48d0
void CrimsonPebbleText0x70::VTable0x20(
	WhiteFalcon0x140* p_renderer,
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
		p_renderer->VTable0x68(m_rawString, m_font, p_x, p_y, p_scaleX, p_scaleY, NULL, 0);
	}
	else {
		p_renderer->VTable0x64(&m_string, m_font, p_x, p_y, p_scaleX, p_scaleY, NULL, 0);
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

// STUB: LEGORACERS 0x004a4d10
void CrimsonPebbleEvent0x48::FUN_004a4d10(LegoFloat)
{
	STUB(0x004a4d10);
}
