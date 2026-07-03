#include "golbinparser.h"
#include "golerror.h"
#include "race/racesession.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SurfaceTable, 0x14)
DECOMP_SIZE_ASSERT(SurfaceTable::Entry, 0x5c)
DECOMP_SIZE_ASSERT(SurfaceTable::TmbTxtParser, 0x1fc)

// FUNCTION: LEGORACERS 0x00443c90
SurfaceTable::Entry::Entry()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00443ca0
void SurfaceTable::Entry::Reset()
{
	m_name[0] = '\0';
	m_flags = 0;
	m_enterEventId = 0;
	m_leaveEventId = 0;
	m_touchEventId = 0;
	m_projectileEventId = 0;
	m_unk0x1c.m_x = 0.0f;
	m_unk0x1c.m_y = 0.0f;
	m_unk0x1c.m_z = 0.0f;
	m_surfaceForce.m_x = 0.0f;
	m_surfaceForce.m_y = 0.0f;
	m_surfaceForce.m_z = 0.0f;
	m_surfaceSoundId = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;
	m_wheelParticleName[0] = '\0';
	m_supportThreshold = 0.0f;
	m_friction = 0.0f;
	m_lateralGrip = 0.0f;
	m_unk0x54 = 0.0f;
	m_rollingResistance = 0.0f;
}

// FUNCTION: LEGORACERS 0x00443cf0
void SurfaceTable::Entry::Load(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	if (m_flags & c_flagLoaded) {
		Unload();
	}

	p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TmbTxtParser::e_surface));
	::memcpy(m_name, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	if (token != GolFileParser::e_rightCurly) {
		do {
			switch (token) {
			case TmbTxtParser::e_enterEvent:
				m_enterEventId = p_parser->ReadInteger();
				m_flags |= c_flagEnterEventId;
				break;
			case TmbTxtParser::e_leaveEvent:
				m_leaveEventId = p_parser->ReadInteger();
				m_flags |= c_flagLeaveEventId;
				break;
			case TmbTxtParser::e_touchEvent:
				m_touchEventId = p_parser->ReadInteger();
				m_flags |= c_flagTouchEventId;
				break;
			case TmbTxtParser::e_projectileEvent:
				m_projectileEventId = p_parser->ReadInteger();
				m_flags |= c_flagProjectileEventId;
				break;
			case TmbTxtParser::e_unknown0x2c:
				m_unk0x1c.m_x = p_parser->ReadFloat();
				m_unk0x1c.m_y = p_parser->ReadFloat();
				m_unk0x1c.m_z = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x1c;
				if (p_mirror) {
					m_unk0x1c.m_y = -m_unk0x1c.m_y;
				}
				break;
			case TmbTxtParser::e_surfaceForce:
				m_surfaceForce.m_x = p_parser->ReadFloat();
				m_surfaceForce.m_y = p_parser->ReadFloat();
				m_surfaceForce.m_z = p_parser->ReadFloat();
				m_flags |= c_flagSurfaceForce;
				if (p_mirror) {
					m_surfaceForce.m_y = -m_surfaceForce.m_y;
				}
				break;
			case TmbTxtParser::e_surfaceSound:
				m_surfaceSoundId = p_parser->ReadInteger();
				m_flags |= c_flagSurfaceSoundId;
				break;
			case TmbTxtParser::e_unknown0x2f:
				m_unk0x38 = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x38;
				break;
			case TmbTxtParser::e_unknown0x30:
				m_unk0x3c = p_parser->ReadInteger();
				m_flags |= c_flagUnk0x3c;
				break;
			case TmbTxtParser::e_wheelParticle:
				::memcpy(m_wheelParticleName, p_parser->ReadStringWithMaxLength(sizeof(GolName)), sizeof(GolName));
				m_flags |= c_flagWheelParticleName;
				break;
			case TmbTxtParser::e_supportThreshold:
				m_supportThreshold = p_parser->ReadFloat();
				m_flags |= c_flagSupportThreshold;
				break;
			case TmbTxtParser::e_friction:
				m_friction = p_parser->ReadFloat();
				m_flags |= c_flagFriction;
				break;
			case TmbTxtParser::e_lateralGrip:
				m_lateralGrip = p_parser->ReadFloat();
				m_flags |= c_flagLateralGrip;
				break;
			case TmbTxtParser::e_unknown0x35:
				m_unk0x54 = p_parser->ReadFloat();
				m_flags |= c_flagUnk0x54;
				break;
			case TmbTxtParser::e_rollingResistance:
				m_rollingResistance = p_parser->ReadFloat();
				m_flags |= c_flagRollingResistance;
				break;
			case TmbTxtParser::e_nonSolid:
				m_flags |= c_flagNonSolid;
				break;
			case TmbTxtParser::e_projectilePassThrough:
				m_flags |= c_flagProjectilePassThrough;
				break;
			case TmbTxtParser::e_finish:
				m_flags |= c_flagFinish;
				break;
			default:
				p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
				break;
			}

			token = p_parser->GetNextToken();
		} while (token != GolFileParser::e_rightCurly);
	}

	m_flags |= c_flagLoaded;
}

// FUNCTION: LEGORACERS 0x00443f90
void SurfaceTable::Entry::Unload()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00443fa0
SurfaceTable::SurfaceTable()
{
	m_count = 0;
	m_entries = NULL;
}

// FUNCTION: LEGORACERS 0x00443fe0
SurfaceTable::~SurfaceTable()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00444030
void SurfaceTable::Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror)
{
	if (m_entries) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
		parser->SetSuffix(".tmb");
	}
	else {
		parser = new TmbTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);
	parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(TmbTxtParser::e_surface));
	m_count = parser->ReadBracketedCountAndLeftCurly();
	GolNameTable::Allocate(m_count);

	m_entries = new Entry[m_count];
	if (m_entries == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_count; i++) {
		m_entries[i].Load(parser, p_mirror);

		GolName name;
		::memcpy(name, m_entries[i].GetName(), sizeof(GolName));
		AddName(name, &m_entries[i]);
	}

	parser->ReadRightCurly();
	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: LEGORACERS 0x00444210
void SurfaceTable::Clear()
{
	if (m_entries) {
		delete[] m_entries;
		m_entries = NULL;
	}

	if (m_nameEntries) {
		GolNameTable::Clear();
	}

	m_count = 0;
}
