#include "crimsonpebble0x228.h"

#include "audio/soundmanager.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "golname.h"
#include "goltxtparser.h"
#include "mabmaterialanimation0x14.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CrimsonPebble0x228, 0x228)
DECOMP_SIZE_ASSERT(BluebellFog0x4, 0x04)

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

// STUB: LEGORACERS 0x004a0680
LegoBool32 CrimsonPebble0x228::FUN_004a0680(const LegoChar* p_fileName, const LegoChar* p_suffix)
{
	STUB(0x004a0680);
	return FALSE;
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
		if (!FUN_004a0680(p_fileName, ".ceb")) {
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
		if (!FUN_004a0680(p_fileName, parser->GetSuffix())) {
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
			FUN_004a2310(parser);
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

// STUB: LEGORACERS 0x004a12e0
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

// STUB: LEGORACERS 0x004a2310
void CrimsonPebble0x228::FUN_004a2310(GolFileParser* p_parser)
{
	STUB(0x004a2310);
}

// FUNCTION: LEGORACERS 0x004a24e0
void CrimsonPebble0x228::FUN_004a24e0()
{
	for (LegoU32 i = 0; i < this->m_unk0x118; i++) {
		m_unk0x11c[i].FUN_004a4790(this, m_unk0x08);
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
	undefined4*& p_unk0x0c,
	GolNameTable& p_unk0x10
)
{
	STUB(0x004a2730);
}

// STUB: LEGORACERS 0x004a2ac0
void CrimsonPebble0x228::VTable0x00(void*, void*, void*)
{
	STUB(0x4a2ac0);
}

// STUB: LEGORACERS 0x004a2b00
void CrimsonPebble0x228::VTable0x04(void*, void*, void*)
{
	STUB(0x4a2b00);
}

// STUB: LEGORACERS 0x004a2b40
void CrimsonPebble0x228::VTable0x08(void*, void*, void*)
{
	STUB(0x4a2b40);
}

// STUB: LEGORACERS 0x004a2b80
void CrimsonPebble0x228::VTable0x0c(void*, void*, void*)
{
	STUB(0x4a2b80);
}

// STUB: LEGORACERS 0x004a2bc0
void CrimsonPebble0x228::VTable0x10(void*, void*, void*)
{
	STUB(0x4a2bc0);
}

// STUB: LEGORACERS 0x004a2c00
void CrimsonPebble0x228::VTable0x14(void*, void*, void*)
{
	STUB(0x4a2c00);
}

// STUB: LEGORACERS 0x004a2c40
void CrimsonPebble0x228::VTable0x18(void*, void*, void*)
{
	STUB(0x4a2c40);
}

// STUB: LEGORACERS 0x004a2c80
void CrimsonPebble0x228::VTable0x1c(void*, void*, void*)
{
	STUB(0x4a2c80);
}

// STUB: LEGORACERS 0x004a2cc0
void CrimsonPebble0x228::VTable0x20(void*, void*, void*)
{
	STUB(0x4a2cc0);
}

// STUB: LEGORACERS 0x004a2d00
void CrimsonPebble0x228::VTable0x24(void*, void*, void*)
{
	STUB(0x4a2d00);
}

// STUB: LEGORACERS 0x004a2d40
void CrimsonPebble0x228::VTable0x28(void*, void*, void*)
{
	STUB(0x4a2d40);
}

// STUB: LEGORACERS 0x004a2d80
void CrimsonPebble0x228::VTable0x2c(void*, void*, void*)
{
	STUB(0x4a2d80);
}

// STUB: LEGORACERS 0x004a2dc0
void CrimsonPebble0x228::FUN_004a2dc0(undefined4)
{
	STUB(0x004a2dc0);
}

// STUB: LEGORACERS 0x004a2f30
void CrimsonPebble0x228::FUN_004a2f30(BronzeFalcon0xc8770*)
{
	STUB(0x004a2f30);
}

// STUB: LEGORACERS 0x004a3070
void CrimsonPebble0x228::FUN_004a3070(BronzeFalcon0xc8770*)
{
	STUB(0x004a3070);
}

// STUB: LEGORACERS 0x004a30b0
void CrimsonPebble0x228::FUN_004a30b0(BronzeFalcon0xc8770*)
{
	STUB(0x004a30b0);
}

// STUB: LEGORACERS 0x004a3150
void CrimsonPebble0x228::FUN_004a3150()
{
	STUB(0x004a3150);
}
