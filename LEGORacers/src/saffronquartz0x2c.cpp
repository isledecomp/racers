#include "saffronquartz0x2c.h"

#include "amberlens0x344.h"
#include "amberlensbase0x120.h"
#include "bluebellfog0x4.h"
#include "bronzefalcon0xc8770.h"
#include "floatyboat0x28.h"
#include "gol.h"
#include "golbinparser.h"
#include "golerror.h"
#include "golfileparser.h"
#include "mabmaterialanimation0x14.h"
#include "mabmaterialanimationitem0x18.h"
#include "opalhaven0xf4.h"
#include "zoweeblubberworth0xf0.h"

#include <stdlib.h>
#include <string.h>

DECOMP_SIZE_ASSERT(SaffronQuartz0x2c, 0x2c)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::CdbTxtParser, 0x1fc)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8, 0xb8)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Event0x20, 0x20)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Model0x68, 0x68)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Model0x68::Animation0x1c, 0x1c)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Camera0x34, 0x34)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38, 0x38)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44, 0x44)
DECOMP_SIZE_ASSERT(SaffronQuartz0x2c::Frame0xb8::Event0x44, 0x44)

// FUNCTION: LEGORACERS 0x00404920
SaffronQuartz0x2c::Frame0xb8::Model0x68::Model0x68()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00404970
SaffronQuartz0x2c::Frame0xb8::Model0x68::~Model0x68()
{
	FUN_00404e80();
}

// FUNCTION: LEGORACERS 0x004049c0
LegoU32 SaffronQuartz0x2c::Frame0xb8::Model0x68::Reset()
{
	LegoU32 result = 0;

	m_unk0x2c[0] = '\0';
	m_unk0x20 = 0;
	((LegoU32*) m_unk0x2c)[0] = 0;
	((LegoU32*) m_unk0x2c)[1] = 0;
	m_unk0x28 = NULL;
	m_unk0x24 = NULL;
	m_unk0x34.m_x = 0.0f;
	m_unk0x34.m_y = 0.0f;
	m_unk0x34.m_z = 0.0f;
	m_unk0x40.m_x = 1.0f;
	m_unk0x40.m_y = 0.0f;
	m_unk0x40.m_z = 0.0f;
	m_unk0x4c.m_x = 0.0f;
	m_unk0x4c.m_y = 0.0f;
	m_unk0x4c.m_z = 1.0f;
	m_unk0x58 = -1;
	m_unk0x5c = 0;
	m_unk0x60 = NULL;
	m_unk0x64 = 0;

	return result;
}

// STUB: LEGORACERS 0x00404a10
LegoU32 SaffronQuartz0x2c::Frame0xb8::Model0x68::FUN_00404a10(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser)
{
	STUB(0x00404a10);

	LegoU32 duration = 0;
	m_unk0x28 = p_parent;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x2e);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2c:
			duration = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x58 = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2f:
			::strncpy(m_unk0x2c, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c));
			m_unk0x20 = 1;
			break;
		case GolFileParser::e_unknown0x30:
			::strncpy(m_unk0x2c, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c));
			m_unk0x20 = 2;
			break;
		case GolFileParser::e_unknown0x31:
			::strncpy(m_unk0x2c, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x2c));
			m_unk0x20 = 3;
			break;
		case GolFileParser::e_unknown0x32:
			((LegoU32*) m_unk0x2c)[0] = p_parser->ReadInteger();
			((LegoU32*) m_unk0x2c)[1] = p_parser->ReadInteger();
			m_unk0x20 = 4;
			break;
		case GolFileParser::e_unknown0x33:
			m_unk0x34.m_x = p_parser->ReadFloat();
			m_unk0x34.m_y = p_parser->ReadFloat();
			m_unk0x34.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x34:
			m_unk0x40.m_x = p_parser->ReadFloat();
			m_unk0x40.m_y = p_parser->ReadFloat();
			m_unk0x40.m_z = p_parser->ReadFloat();
			m_unk0x4c.m_x = p_parser->ReadFloat();
			m_unk0x4c.m_y = p_parser->ReadFloat();
			m_unk0x4c.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x36: {
			m_unk0x5c = p_parser->ReadBracketedCountAndLeftCurly();
			if (!m_unk0x5c) {
				p_parser->HandleUnexpectedToken(GolFileParser::e_int);
			}

			m_unk0x60 = new Animation0x1c[m_unk0x5c];
			if (!m_unk0x60) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			for (LegoU32 i = 0; i < m_unk0x5c; i++) {
				m_unk0x60[i].m_unk0x08 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x0c = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x10 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x14 = p_parser->ReadInteger();
				m_unk0x60[i].m_unk0x18 = p_parser->ReadInteger();
			}

			p_parser->ReadRightCurly();
			break;
		}
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	duration += m_unk0x0c;
	m_unk0x10 = duration;
	return duration;
}

// STUB: LEGORACERS 0x00404c90
LegoU32 SaffronQuartz0x2c::Frame0xb8::Model0x68::FUN_00404c90()
{
	STUB(0x00404c90);

	if (!m_unk0x24) {
		char message[64];

		switch (m_unk0x20) {
		case 1:
			m_unk0x24 = m_unk0x28->FUN_00406e30(m_unk0x2c);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c, sizeof(m_unk0x2c));
				message[8] = '\0';
				::strcat(message, ": Unable to find model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case 2:
			m_unk0x24 = m_unk0x28->FUN_00406e80(m_unk0x2c);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c, sizeof(m_unk0x2c));
				message[8] = '\0';
				::strcat(message, ": Unable to find jointed model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case 3:
			m_unk0x24 = m_unk0x28->FUN_00406ed0(m_unk0x2c);
			if (!m_unk0x24) {
				::strncpy(message, m_unk0x2c, sizeof(m_unk0x2c));
				message[8] = '\0';
				::strcat(message, ": Unable to find bsp model");
				GOL_FATALERROR_MESSAGE(message);
			}
			break;
		case 4:
			m_unk0x24 = m_unk0x28->FUN_00406f20(((LegoU32*) m_unk0x2c)[0], ((LegoU32*) m_unk0x2c)[1]);
			break;
		default:
			return m_unk0x20 - 1;
		}
	}

	if (m_unk0x5c && (m_unk0x20 == 1 || m_unk0x20 == 2 || m_unk0x20 == 3)) {
		for (LegoU32 i = 0; i < m_unk0x5c; i++) {
			m_unk0x60[i].m_unk0x00 = m_unk0x28->FUN_00406f40(m_unk0x60[i].m_unk0x08, m_unk0x60[i].m_unk0x0c);
			m_unk0x60[i].m_unk0x04 =
				m_unk0x28->FUN_00406f60(m_unk0x60[i].m_unk0x08, m_unk0x60[i].m_unk0x0c, m_unk0x60[i].m_unk0x10);
		}
	}

	return m_unk0x5c;
}

// FUNCTION: LEGORACERS 0x00404e80
void SaffronQuartz0x2c::Frame0xb8::Model0x68::FUN_00404e80()
{
	if (m_unk0x60) {
		delete[] m_unk0x60;
	}

	Reset();
}

// STUB: LEGORACERS 0x00404ea0
void SaffronQuartz0x2c::Frame0xb8::Model0x68::VTable0x04(undefined4 p_elapsedMs)
{
	STUB(0x00404ea0);

	if (m_unk0x14 && m_unk0x24) {
		m_unk0x24->VTable0x10(p_elapsedMs);
	}
}

// FUNCTION: LEGORACERS 0x00404f00
void SaffronQuartz0x2c::Frame0xb8::Model0x68::VTable0x08(BronzeFalcon0xc8770* p_renderer)
{
	if (m_unk0x14 && !m_unk0x64) {
		m_unk0x24->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00404f20
void SaffronQuartz0x2c::Frame0xb8::Model0x68::VTable0x0c(BronzeFalcon0xc8770* p_renderer)
{
	if (m_unk0x14 && m_unk0x64) {
		m_unk0x24->VTable0x1c(*p_renderer);
	}
}

// STUB: LEGORACERS 0x00404f40
void SaffronQuartz0x2c::Frame0xb8::Model0x68::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	STUB(0x00404f40);

	if (m_unk0x24) {
		m_unk0x64 = m_unk0x24->VTable0x20();
		m_unk0x24->VTable0x08(m_unk0x34);
		m_unk0x24->VTable0x40(m_unk0x40, m_unk0x4c);

		if (m_unk0x20 == 2 && m_unk0x58 >= 0) {
			::srand(m_unk0x58);
		}

		Event0x20::VTable0x10(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x10(p_frame, m_name, this);
		}
	}
}

// STUB: LEGORACERS 0x00405020
void SaffronQuartz0x2c::Frame0xb8::Model0x68::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	STUB(0x00405020);

	if (m_unk0x24) {
		Event0x20::VTable0x14(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x14(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405070
SaffronQuartz0x2c::Frame0xb8::Camera0x34::Camera0x34()
{
	m_unk0x20 = NULL;
	m_unk0x24[0] = '\0';
	m_unk0x2c = NULL;
	m_unk0x30 = -1;
}

// FUNCTION: LEGORACERS 0x004050a0
LegoU32 SaffronQuartz0x2c::Frame0xb8::Camera0x34::FUN_004050a0(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x2c = p_parent;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x29);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2a:
			::strncpy(m_unk0x24, p_parser->ReadStringWithMaxLength(8), sizeof(m_unk0x24));
			break;
		case GolFileParser::e_unknown0x2b:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2c:
			duration = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2d:
			m_unk0x30 = p_parser->ReadInteger();
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	m_unk0x10 = duration + m_unk0x0c;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x00405160
void SaffronQuartz0x2c::Frame0xb8::Camera0x34::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x2c) {
		if (!m_unk0x20) {
			m_unk0x20 = m_unk0x2c->FUN_00406de0(m_unk0x24);
			if (!m_unk0x20) {
				char message[64];
				::strncpy(message, m_unk0x24, sizeof(m_unk0x24));
				message[8] = '\0';
				::strcat(message, ": Unable to find named camera");
				GOL_FATALERROR_MESSAGE(message);
			}
		}

		p_frame->FUN_004066d0(m_unk0x20);
		if (m_unk0x30 >= 0 && m_unk0x20->m_unk0x28) {
			((OpalHaven0xf4*) m_unk0x20->m_unk0x28)->FUN_0040dad0((undefined2) m_unk0x30);
		}

		Event0x20::VTable0x10(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x08(p_frame, m_name, this);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405230
void SaffronQuartz0x2c::Frame0xb8::Camera0x34::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	if (m_unk0x20) {
		p_frame->FUN_00406710(m_unk0x20);
		Event0x20::VTable0x14(p_frame, p_event);
		if (p_event) {
			p_event->VTable0x0c(p_frame, m_name, this);
		}
	}
}

// STUB: LEGORACERS 0x00405270
void SaffronQuartz0x2c::Frame0xb8::Camera0x34::VTable0x04(undefined4)
{
	STUB(0x00405270);
}

// FUNCTION: LEGORACERS 0x00405280
LegoU32 SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::FUN_00405280(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x40 = NULL;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x3c = 0;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x3a);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2c:
			duration = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x38: {
			ColorRGBA color;
			color.m_red = (LegoU8) p_parser->ReadInteger();
			color.m_grn = (LegoU8) p_parser->ReadInteger();
			color.m_blu = (LegoU8) p_parser->ReadInteger();
			color.m_alp = 0xff;
			m_unk0x20.SetColor(color);
			break;
		}
		case GolFileParser::e_unknown0x39: {
			GolVec3 direction;
			direction.m_x = p_parser->ReadFloat();
			direction.m_y = p_parser->ReadFloat();
			direction.m_z = p_parser->ReadFloat();
			m_unk0x20.SetDirection(direction);
			break;
		}
		case GolFileParser::e_unknown0x3c:
			m_unk0x30 = (LegoU32) ((LegoFloat) p_parser->ReadInteger() * 33.333328f);
			m_unk0x34 = (LegoU32) ((LegoFloat) p_parser->ReadInteger() * 33.333328f);
			m_unk0x3c |= 1;
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	LegoU32 end = m_unk0x0c;
	end += duration;
	m_unk0x10 = end;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x00405410
void SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x3c |= 2;
	m_unk0x38 = m_unk0x30;
	p_frame->FUN_00406790(&m_unk0x20);

	Event0x20::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x28(p_frame, m_name, this);
	}

	m_unk0x40 = p_frame;
}

// FUNCTION: LEGORACERS 0x00405460
void SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	p_frame->FUN_004067f0(&m_unk0x20);
	Event0x20::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x2c(p_frame, m_name, this);
	}

	m_unk0x40 = NULL;
}

// STUB: LEGORACERS 0x004054a0
void SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::VTable0x04(undefined4 p_elapsedMs)
{
	STUB(0x004054a0);

	if (m_unk0x3c & 1) {
		if ((LegoU32) p_elapsedMs <= m_unk0x38) {
			m_unk0x38 -= (LegoU32) p_elapsedMs;
		}
		else if (m_unk0x3c & 2) {
			m_unk0x3c &= ~2;
			m_unk0x38 = m_unk0x34;
			m_unk0x40->FUN_004067f0(&m_unk0x20);
		}
		else {
			m_unk0x38 = m_unk0x30;
			m_unk0x3c |= 2;
			m_unk0x40->FUN_00406790(&m_unk0x20);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405520
SaffronQuartz0x2c::Frame0xb8::Event0x20::Event0x20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405560
SaffronQuartz0x2c::Frame0xb8::Event0x20::~Event0x20()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00405570
void SaffronQuartz0x2c::Frame0xb8::Event0x20::Reset()
{
	m_name[0] = '\0';
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = NULL;
	m_unk0x14 = 0;
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x04(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x08(BronzeFalcon0xc8770*)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x0c(BronzeFalcon0xc8770*)
{
}

// FUNCTION: LEGORACERS 0x00405590
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 1;
	if (p_event) {
		p_event->VTable0x00(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004055c0
void SaffronQuartz0x2c::Frame0xb8::Event0x20::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x14 = 0;
	if (p_event) {
		p_event->VTable0x04(p_frame, m_name, this);
	}
}

typedef LegoS32(__cdecl* QSortComparator)(const void*, const void*);

// FUNCTION: LEGORACERS 0x004055f0
static LegoS32 __cdecl CompareEventStart(
	SaffronQuartz0x2c::Frame0xb8::Event0x20** p_left,
	SaffronQuartz0x2c::Frame0xb8::Event0x20** p_right
)
{
	if ((*p_left)->m_unk0x0c > (*p_right)->m_unk0x0c) {
		return 1;
	}

	if ((*p_left)->m_unk0x0c < (*p_right)->m_unk0x0c) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405610
static LegoS32 __cdecl CompareEventEnd(
	SaffronQuartz0x2c::Frame0xb8::Event0x20** p_left,
	SaffronQuartz0x2c::Frame0xb8::Event0x20** p_right
)
{
	if ((*p_left)->m_unk0x10 > (*p_right)->m_unk0x10) {
		return 1;
	}

	if ((*p_left)->m_unk0x10 < (*p_right)->m_unk0x10) {
		return -1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x00405630
void SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::FUN_00405630(GolFileParser* p_parser)
{
	LegoU32 duration = 0;
	m_unk0x34 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x35);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2c:
			duration = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x38: {
			ColorRGBA color;
			color.m_red = (LegoU8) p_parser->ReadInteger();
			color.m_grn = (LegoU8) p_parser->ReadInteger();
			color.m_blu = (LegoU8) p_parser->ReadInteger();
			color.m_alp = 0xff;
			m_unk0x20.SetColor(color);
			break;
		}
		case GolFileParser::e_unknown0x3c:
			m_unk0x24 = (LegoU32) ((LegoFloat) p_parser->ReadInteger() * 33.333328f);
			m_unk0x28 = (LegoU32) ((LegoFloat) p_parser->ReadInteger() * 33.333328f);
			m_unk0x30 |= 1;
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	LegoU32 end = m_unk0x0c;
	end += duration;
	m_unk0x10 = end;
}

// FUNCTION: LEGORACERS 0x00405780
void SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	m_unk0x30 |= 2;
	m_unk0x2c = m_unk0x24;
	p_frame->FUN_00406760(&m_unk0x20);

	Event0x20::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x20(p_frame, m_name, this);
	}

	m_unk0x34 = p_frame;
}

// FUNCTION: LEGORACERS 0x004057d0
void SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	p_frame->FUN_00406770(&m_unk0x20);
	Event0x20::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x24(p_frame, m_name, this);
	}

	m_unk0x34 = NULL;
}

// STUB: LEGORACERS 0x00405810
void SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::VTable0x04(undefined4 p_elapsedMs)
{
	STUB(0x00405810);

	if (m_unk0x30 & 1) {
		if ((LegoU32) p_elapsedMs <= m_unk0x2c) {
			m_unk0x2c -= (LegoU32) p_elapsedMs;
		}
		else if (m_unk0x30 & 2) {
			m_unk0x30 &= ~2;
			m_unk0x2c = m_unk0x28;
			m_unk0x34->FUN_00406770(&m_unk0x20);
		}
		else {
			m_unk0x2c = m_unk0x24;
			m_unk0x30 |= 2;
			m_unk0x34->FUN_00406760(&m_unk0x20);
		}
	}
}

// FUNCTION: LEGORACERS 0x00405890
SaffronQuartz0x2c::Frame0xb8::Frame0xb8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004058a0
SaffronQuartz0x2c::Frame0xb8::~Frame0xb8()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004058b0
void SaffronQuartz0x2c::Frame0xb8::Reset()
{
	m_unk0x00 = NULL;
	m_unk0x54 = 30;
	m_unk0x58 = 30;
	m_unk0x04 = 0;
	m_unk0x08 = NULL;
	m_unk0x0c = 0;
	m_unk0x10 = NULL;
	m_unk0x14 = 0;
	m_unk0x18 = NULL;
	m_unk0x1c = 0;
	m_unk0x20 = NULL;
	m_unk0x24 = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 0;
	m_unk0x30 = NULL;
	m_unk0x34 = 0;
	m_unk0x38 = NULL;
	m_unk0x3c = 0;
	m_unk0x40 = NULL;
	m_unk0x44 = 0;
	m_unk0x4c = 0;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0xa4 = 0.0f;
	m_unk0x5c = 0;
	::memset(m_unk0x60, 0, sizeof(m_unk0x60));
	m_unk0x80 = NULL;
	m_unk0x84 = 0;
	::memset(m_unk0x88, 0, sizeof(m_unk0x88));
	m_unk0xa8.m_bottom = 0;
	m_unk0xa8.m_top = 0;
	m_unk0xa8.m_left = 0;
	m_unk0xa8.m_right = 0;
}

// STUB: LEGORACERS 0x00405950
void SaffronQuartz0x2c::Frame0xb8::FUN_00405950(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser)
{
	STUB(0x00405950);

	if (m_unk0x00) {
		Destroy();
	}

	m_unk0x00 = p_parent;
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x29:
			FUN_00405bd0(p_parser);
			break;
		case GolFileParser::e_unknown0x2e:
			FUN_00405d10(p_parser);
			break;
		case GolFileParser::e_unknown0x35:
			FUN_00405f80(p_parser);
			break;
		case GolFileParser::e_unknown0x37:
			FUN_00405e50(p_parser);
			break;
		case GolFileParser::e_unknown0x3a:
			FUN_00406110(p_parser);
			break;
		case GolFileParser::e_unknown0x2c:
			m_unk0x4c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x3b:
			m_unk0x54 = p_parser->ReadInteger();
			m_unk0x58 = m_unk0x54;
			break;
		default:
			p_parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = p_parser->GetNextToken();
	}

	if (!m_unk0x4c && m_unk0x04) {
		for (LegoU32 i = 0; i < m_unk0x04; i++) {
			Camera0x34* camera = &m_unk0x08[i];
			if (camera->m_unk0x10 > m_unk0x4c) {
				m_unk0x4c = camera->m_unk0x10;
			}
		}
	}

	m_unk0x2c = m_unk0x24 + m_unk0x14 + m_unk0x0c + m_unk0x1c + m_unk0x04;
	m_unk0x30 = new Event0x20*[m_unk0x2c];
	if (!m_unk0x30) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x38 = new Event0x20*[m_unk0x2c];
	if (!m_unk0x38) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 eventIndex = 0;
	LegoU32 i;
	for (i = 0; i < m_unk0x04; i++) {
		Event0x20* event = &m_unk0x08[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x0c; i++) {
		Event0x20* event = &m_unk0x10[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x14; i++) {
		Event0x20* event = &m_unk0x18[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x1c; i++) {
		Event0x20* event = &m_unk0x20[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	for (i = 0; i < m_unk0x24; i++) {
		Event0x20* event = &m_unk0x28[i];
		m_unk0x30[eventIndex] = event;
		m_unk0x38[eventIndex] = event;
		eventIndex++;
	}

	::qsort(m_unk0x30, m_unk0x2c, sizeof(Event0x20*), (QSortComparator) CompareEventStart);
	::qsort(m_unk0x38, m_unk0x2c, sizeof(Event0x20*), (QSortComparator) CompareEventEnd);
}

// FUNCTION: LEGORACERS 0x00405bd0
void SaffronQuartz0x2c::Frame0xb8::FUN_00405bd0(GolFileParser* p_parser)
{
	m_unk0x04 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x04) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x08 = new Camera0x34[m_unk0x04];

	if (!m_unk0x08) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x04; i++) {
		m_unk0x08[i].FUN_004050a0(m_unk0x00, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405d10
void SaffronQuartz0x2c::Frame0xb8::FUN_00405d10(GolFileParser* p_parser)
{
	m_unk0x0c = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x0c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x10 = new Model0x68[m_unk0x0c];

	if (!m_unk0x10) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x0c; i++) {
		m_unk0x10[i].FUN_00404a10(m_unk0x00, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405e50
void SaffronQuartz0x2c::Frame0xb8::FUN_00405e50(GolFileParser* p_parser)
{
	m_unk0x14 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x14) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x18 = new Event0x44[m_unk0x14];

	if (!m_unk0x18) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x14; i++) {
		m_unk0x18[i].FUN_00407090(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00405f80
void SaffronQuartz0x2c::Frame0xb8::FUN_00405f80(GolFileParser* p_parser)
{
	m_unk0x1c = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x1c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x20 = new AmbientLight0x38[m_unk0x1c];

	if (!m_unk0x20) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x1c; i++) {
		m_unk0x20[i].FUN_00405630(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x004060c0
SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::AmbientLight0x38()
{
}

// FUNCTION: LEGORACERS 0x00406110
void SaffronQuartz0x2c::Frame0xb8::FUN_00406110(GolFileParser* p_parser)
{
	m_unk0x24 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x24) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x28 = new DirectionalLight0x44[m_unk0x24];

	if (!m_unk0x28) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x24; i++) {
		m_unk0x28[i].FUN_00405280(p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406240
SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::DirectionalLight0x44()
{
}

// FUNCTION: LEGORACERS 0x004062a0
void SaffronQuartz0x2c::Frame0xb8::Destroy()
{
	if (m_unk0x30) {
		delete[] m_unk0x30;
	}

	if (m_unk0x38) {
		delete[] m_unk0x38;
	}

	if (m_unk0x08) {
		delete[] m_unk0x08;
	}

	if (m_unk0x10) {
		delete[] m_unk0x10;
	}

	if (m_unk0x18) {
		delete[] m_unk0x18;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_unk0x28) {
		delete[] m_unk0x28;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00406310
void SaffronQuartz0x2c::Frame0xb8::FUN_00406310()
{
	if (m_unk0x44 & c_flagComplete) {
		FUN_00406330();
	}

	m_unk0x44 &= ~c_flagComplete;
	m_unk0x44 |= c_flagPlaying;
}

// FUNCTION: LEGORACERS 0x00406330
void SaffronQuartz0x2c::Frame0xb8::FUN_00406330()
{
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x34 = 0;
	m_unk0x3c = 0;
	m_unk0xa4 = 0.0f;

	while (m_unk0x40) {
		m_unk0x40->VTable0x14(this, m_unk0x00->GetUnk0x0c());
		FUN_004066b0(m_unk0x40);
	}

	m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406380
void SaffronQuartz0x2c::Frame0xb8::FUN_00406380()
{
	m_unk0x44 &= ~(c_flagPlaying | c_flagComplete | c_flagLooped);
}

// FUNCTION: LEGORACERS 0x00406390
void SaffronQuartz0x2c::Frame0xb8::FUN_00406390(LegoS32 p_elapsedMs)
{
	if (m_unk0x44 & c_flagPlaying) {
		LegoU32 elapsed = m_unk0x50 + p_elapsedMs * m_unk0x58;
		LegoU32 frame = elapsed / 1000;

		if (frame >= m_unk0x4c) {
			FUN_004065d0(m_unk0x48, frame);
			if (m_unk0x44 & c_flagLoop) {
				FUN_00406330();
				frame = 0;
				m_unk0x44 |= c_flagLooped;
				elapsed = 0;
				m_unk0xa4 = 0.0f;
			}
			else {
				m_unk0x44 &= ~(c_flagPlaying | c_flagLooped);
				m_unk0x44 |= c_flagComplete;
				return;
			}
		}
		else {
			m_unk0x44 &= ~(c_flagComplete | c_flagLooped);
		}

		FUN_004065d0(m_unk0x48, frame);

		if (m_unk0x58 == m_unk0x54) {
			m_unk0xa4 = (LegoFloat) ((double) p_elapsedMs + m_unk0xa4);
		}
		else {
			double frameElapsed = (double) (LegoS32) (elapsed - m_unk0x50);
			frameElapsed = frameElapsed / (double) (LegoS32) m_unk0x54;
			m_unk0xa4 = (LegoFloat) (frameElapsed + m_unk0xa4);
		}

		if (m_unk0xa4 >= 1.0f) {
			LegoS32 ticks = (LegoS32) m_unk0xa4;
			FUN_004065a0(ticks);
			m_unk0xa4 = m_unk0xa4 - (LegoFloat) ticks;
		}

		m_unk0x50 = elapsed;
		m_unk0x48 = frame;
	}
}

// FUNCTION: LEGORACERS 0x00406490
void SaffronQuartz0x2c::Frame0xb8::FUN_00406490(Rect* p_rect)
{
	m_unk0xa8 = *p_rect;
	m_unk0x44 |= c_flagHasRect;
}

// FUNCTION: LEGORACERS 0x004064c0
void SaffronQuartz0x2c::Frame0xb8::FUN_004064c0(BronzeFalcon0xc8770* p_renderer, LegoU32 p_lensIndex)
{
	if (m_unk0x5c) {
		LegoU32 lensIndex = p_lensIndex;
		if (p_lensIndex >= m_unk0x5c) {
			lensIndex = m_unk0x5c - 1;
		}

		if (m_unk0x44 & c_flagHasRect) {
			m_unk0x60[lensIndex]->VTable0x0c(&m_unk0xa8);
		}

		p_renderer->VTable0x20(m_unk0x60[lensIndex]);
		p_renderer->VTable0x5c();
		p_renderer->VTable0xec(4);
	}

	p_renderer->VTable0x28();
	if (m_unk0x80 || m_unk0x84) {
		if (m_unk0x80) {
			p_renderer->VTable0x2c(m_unk0x80);
		}

		for (LegoU32 i = 0; i < m_unk0x84; i++) {
			p_renderer->VTable0x30(m_unk0x88[i]);
		}
	}

	for (Event0x20* event3 = m_unk0x40; event3; event3 = event3->m_unk0x1c) {
		event3->VTable0x08(p_renderer);
	}

	for (Event0x20* event4 = m_unk0x40; event4; event4 = event4->m_unk0x1c) {
		event4->VTable0x0c(p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x004065a0
void SaffronQuartz0x2c::Frame0xb8::FUN_004065a0(undefined4 p_unk0x04)
{
	for (Event0x20* event = m_unk0x40; event; event = event->m_unk0x1c) {
		event->VTable0x04(p_unk0x04);
	}
}

// FUNCTION: LEGORACERS 0x004065d0
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_004065d0(LegoU32 p_startFrame, LegoU32 p_endFrame)
{
	LegoU32 result;
	LegoU32 total;

	for (;;) {
		while (TRUE) {
			result = m_unk0x34;
			total = m_unk0x2c;

			if (result >= total) {
				break;
			}

			Event0x20* event = m_unk0x30[result];
			result = event->m_unk0x0c;

			if (result > m_unk0x38[m_unk0x3c]->m_unk0x10) {
				break;
			}

			if (p_startFrame > result || p_endFrame < result) {
				return result;
			}

			if (!event->m_unk0x14) {
				event->VTable0x10(this, m_unk0x00->GetUnk0x0c());
				FUN_00406680(m_unk0x30[m_unk0x34]);
			}

			m_unk0x34++;
		}

		result = m_unk0x3c;
		if (result >= total) {
			break;
		}

		Event0x20* event = m_unk0x38[result];
		result = event->m_unk0x10;

		if (p_startFrame > result || p_endFrame < result) {
			break;
		}

		if (event->m_unk0x14) {
			event->VTable0x14(this, m_unk0x00->GetUnk0x0c());
			FUN_004066b0(m_unk0x38[m_unk0x3c]);
		}

		m_unk0x3c++;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00406680
void SaffronQuartz0x2c::Frame0xb8::FUN_00406680(Event0x20* p_event)
{
	p_event->m_unk0x18 = NULL;

	if (m_unk0x40) {
		m_unk0x40->m_unk0x18 = p_event;
		p_event->m_unk0x1c = m_unk0x40;
	}
	else {
		p_event->m_unk0x1c = NULL;
	}

	m_unk0x40 = p_event;
}

// FUNCTION: LEGORACERS 0x004066b0
void SaffronQuartz0x2c::Frame0xb8::FUN_004066b0(Event0x20* p_event)
{
	Event0x20* previous = p_event->m_unk0x18;
	Event0x20* next = p_event->m_unk0x1c;

	if (previous) {
		previous->m_unk0x1c = next;
	}
	else {
		m_unk0x40 = next;
	}

	if (next) {
		next->m_unk0x18 = previous;
	}
}

// FUNCTION: LEGORACERS 0x004066d0
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_004066d0(AmberLens0x344* p_lens)
{
	LegoU32 count = m_unk0x5c;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x60[i] == p_lens) {
			return i;
		}
	}

	m_unk0x5c = count + 1;
	m_unk0x60[count] = p_lens;

	return count;
}

// FUNCTION: LEGORACERS 0x00406710
void SaffronQuartz0x2c::Frame0xb8::FUN_00406710(AmberLens0x344* p_lens)
{
	if (m_unk0x5c) {
		LegoU32 i = 0;
		while (i < m_unk0x5c && m_unk0x60[i] != p_lens) {
			i++;
		}

		while (i < m_unk0x5c - 1) {
			m_unk0x60[i] = m_unk0x60[i + 1];
			i++;
		}

		m_unk0x5c--;
		m_unk0x60[m_unk0x5c] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406760
void SaffronQuartz0x2c::Frame0xb8::FUN_00406760(const WhiteFalcon0x140::MaterialColor* p_material)
{
	m_unk0x80 = p_material;
}

// FUNCTION: LEGORACERS 0x00406770
void SaffronQuartz0x2c::Frame0xb8::FUN_00406770(const WhiteFalcon0x140::MaterialColor* p_material)
{
	if (m_unk0x80 == p_material) {
		m_unk0x80 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406790
LegoU32 SaffronQuartz0x2c::Frame0xb8::FUN_00406790(const WhiteFalcon0x140::Light* p_light)
{
	LegoU32 count = m_unk0x84;
	for (LegoU32 i = 0; i < count; i++) {
		if (m_unk0x88[i] == p_light) {
			return i;
		}
	}

	if (count >= sizeOfArray(m_unk0x88)) {
		FUN_004067f0(m_unk0x88[0]);
	}

	m_unk0x88[m_unk0x84] = p_light;
	m_unk0x84++;

	return m_unk0x84;
}

// FUNCTION: LEGORACERS 0x004067f0
void SaffronQuartz0x2c::Frame0xb8::FUN_004067f0(const WhiteFalcon0x140::Light* p_light)
{
	if (m_unk0x84) {
		LegoU32 i = 0;
		while (i < m_unk0x84 && m_unk0x88[i] != p_light) {
			i++;
		}

		while (i < m_unk0x84 - 1) {
			m_unk0x88[i] = m_unk0x88[i + 1];
			i++;
		}

		m_unk0x84--;
		m_unk0x88[m_unk0x84] = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00406860
void SaffronQuartz0x2c::Frame0xb8::FUN_00406860()
{
	for (LegoU32 i = 0; i < m_unk0x0c; i++) {
		m_unk0x10[i].FUN_00404c90();
	}
}

// FUNCTION: LEGORACERS 0x00406890
AmberLens0x344* SaffronQuartz0x2c::Frame0xb8::FUN_00406890()
{
	if (m_unk0x5c) {
		return m_unk0x60[m_unk0x5c - 1];
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x004068a0
SaffronQuartz0x2c::SaffronQuartz0x2c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00406910
SaffronQuartz0x2c::~SaffronQuartz0x2c()
{
	Clear();
}

// FUNCTION: LEGORACERS 0x00406960
void SaffronQuartz0x2c::Reset()
{
	m_unk0x0c = NULL;
	m_golExport = NULL;
	m_renderer = NULL;
	m_unk0x18 = 0;
	m_unk0x1c = NULL;
	m_unk0x20 = NULL;
	m_frameCount = 0;
	m_frames = NULL;
}

// FUNCTION: LEGORACERS 0x00406980
void SaffronQuartz0x2c::FUN_00406980(
	GolExport* p_golExport,
	BronzeFalcon0xc8770* p_renderer,
	const LegoChar* p_fileName,
	LegoBool32 p_binary
)
{
	if (m_golExport) {
		Clear();
	}

	m_golExport = p_golExport;
	m_renderer = p_renderer;

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".cdb");
	}
	else {
		parser = new CdbTxtParser();

		if (!parser) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_fileName);

	GolFileParser::ParserTokenType token = parser->GetNextToken();
	while (token != GolFileParser::e_syntaxerror) {
		switch (token) {
		case GolFileParser::e_unknown0x27:
			FUN_00406cb0(parser);
			break;
		case GolFileParser::e_unknown0x28:
			FUN_00406b90(parser);
			break;
		default:
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
			break;
		}

		token = parser->GetNextToken();
	}

	parser->Dispose();
	delete parser;

	FUN_00406c50(p_binary);

	for (LegoU32 i = 0; i < m_frameCount; i++) {
		m_frames[i].FUN_00406860();
	}
}

// FUNCTION: LEGORACERS 0x00406af0
void SaffronQuartz0x2c::Clear()
{
	if (m_unk0x1c) {
		if (m_golExport) {
			LegoU32 i;
			for (i = 0; i < m_unk0x18; i++) {
				if (m_unk0x1c[i]) {
					m_unk0x1c[i]->VTable0x18();
					m_golExport->VTable0x3c(m_unk0x1c[i]);
				}
			}
		}

		delete[] m_unk0x1c;
	}

	if (m_unk0x20) {
		delete[] m_unk0x20;
	}

	if (m_frames) {
		delete[] m_frames;
	}

	GolNameTable::Clear();
	Reset();
}

// FUNCTION: LEGORACERS 0x00406b90
void SaffronQuartz0x2c::FUN_00406b90(GolFileParser* p_parser)
{
	if (m_unk0x1c) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x18 = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_unk0x18) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	m_unk0x1c = new ZoweeBlubberworth0xf0*[m_unk0x18];
	m_unk0x20 = new LegoChar[m_unk0x18 * 9];

	if (!m_unk0x1c || !m_unk0x20) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		::strncpy(&m_unk0x20[i * 9], p_parser->ReadStringWithMaxLength(8), 8);
		m_unk0x20[i * 9 + 8] = '\0';
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406c50
void SaffronQuartz0x2c::FUN_00406c50(LegoBool32 p_binary)
{
	if (m_unk0x20) {
		for (LegoU32 i = 0; i < m_unk0x18; i++) {
			m_unk0x1c[i] = m_golExport->VTable0x08();
			m_unk0x1c[i]->VTable0x14(m_renderer, &m_unk0x20[i * 9], p_binary, 1.0f);
		}
	}
}

// FUNCTION: LEGORACERS 0x00406cb0
void SaffronQuartz0x2c::FUN_00406cb0(GolFileParser* p_parser)
{
	if (m_frames) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_frameCount = p_parser->ReadBracketedCountAndLeftCurly();
	if (!m_frameCount) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_frameCount);
	m_frames = new Frame0xb8[m_frameCount];

	if (!m_frames) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	for (LegoU32 i = 0; i < m_frameCount; i++) {
		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);

		GolName name;
		::strncpy(name, p_parser->ReadStringWithMaxLength(8), sizeof(name));
		AddName(name, &m_frames[i]);
		m_frames[i].FUN_00405950(this, p_parser);
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: LEGORACERS 0x00406de0
AmberLens0x344* SaffronQuartz0x2c::FUN_00406de0(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		AmberLens0x344* result = m_unk0x1c[i]->FindUnk0xe4(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e30
FloatyBoat0x28* SaffronQuartz0x2c::FUN_00406e30(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		FloatyBoat0x28* result = m_unk0x1c[i]->FindUnk0xb4(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406e80
FloatyBoat0x28* SaffronQuartz0x2c::FUN_00406e80(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		FloatyBoat0x28* result = m_unk0x1c[i]->FindUnk0xc0(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406ed0
FloatyBoat0x28* SaffronQuartz0x2c::FUN_00406ed0(const LegoChar* p_name)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		FloatyBoat0x28* result = m_unk0x1c[i]->FindUnk0xcc(p_name);
		if (result) {
			return result;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00406f20
FloatyBoat0x28* SaffronQuartz0x2c::FUN_00406f20(LegoU32 p_index, LegoU32 p_modelIndex)
{
	return m_unk0x1c[p_index]->VTable0x48(p_modelIndex);
}

// FUNCTION: LEGORACERS 0x00406f40
MabMaterialAnimation0x14* SaffronQuartz0x2c::FUN_00406f40(LegoU32 p_index, LegoU32 p_animationIndex)
{
	return m_unk0x1c[p_index]->VTable0x4c(p_animationIndex);
}

// FUNCTION: LEGORACERS 0x00406f60
MabMaterialAnimationItem0x18* SaffronQuartz0x2c::FUN_00406f60(
	LegoU32 p_index,
	LegoU32 p_animationIndex,
	LegoU32 p_itemIndex
)
{
	MabMaterialAnimation0x14* materialAnimation = m_unk0x1c[p_index]->VTable0x4c(p_animationIndex);
	return &materialAnimation->GetUnk0x0c()[p_itemIndex];
}

// STUB: LEGORACERS 0x00406f90
LegoU32 SaffronQuartz0x2c::FUN_00406f90(LegoFloat p_scale)
{
	for (LegoU32 i = 0; i < m_unk0x18; i++) {
		ZoweeBlubberworth0xf0* resource = m_unk0x1c[i];

		for (LegoU32 j = 0; j < resource->GetUnk0x7c(); j++) {
			AmberLensBase0x120* lens = resource->VTable0x50(j);

			if (p_scale > 0.0f) {
				lens->m_unk0x0c = p_scale;
				lens->m_flags |= 8;
			}
			else {
				lens->m_flags &= ~8;
			}

			lens->m_flags |= 3;
		}
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x00406fc0
SaffronQuartz0x2c::Frame0xb8::Event0x44::Event0x44()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00407010
SaffronQuartz0x2c::Frame0xb8::Event0x44::~Event0x44()
{
	FUN_004071a0();
}

// FUNCTION: LEGORACERS 0x00407060
void SaffronQuartz0x2c::Frame0xb8::Event0x44::Reset()
{
	m_unk0x20.m_x = 0.0f;
	m_unk0x20.m_y = 0.0f;
	m_unk0x20.m_z = 0.0f;
	m_unk0x2c.m_x = 1.0f;
	m_unk0x2c.m_y = 0.0f;
	m_unk0x2c.m_z = 0.0f;
	m_unk0x38.m_x = 0.0f;
	m_unk0x38.m_y = 0.0f;
	m_unk0x38.m_z = 1.0f;
}

// FUNCTION: LEGORACERS 0x00407090
LegoU32 SaffronQuartz0x2c::Frame0xb8::Event0x44::FUN_00407090(GolFileParser* p_parser)
{
	LegoU32 duration = 0;

	p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x37);
	::strncpy(m_name, p_parser->ReadStringWithMaxLength(8), sizeof(m_name));
	p_parser->ReadLeftCurly();

	GolFileParser::ParserTokenType token = p_parser->GetNextToken();
	while (token != GolFileParser::e_rightCurly) {
		switch (token) {
		case GolFileParser::e_unknown0x2b:
			m_unk0x0c = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x2c:
			duration = p_parser->ReadInteger();
			break;
		case GolFileParser::e_unknown0x33:
			m_unk0x20.m_x = p_parser->ReadFloat();
			m_unk0x20.m_y = p_parser->ReadFloat();
			m_unk0x20.m_z = p_parser->ReadFloat();
			break;
		case GolFileParser::e_unknown0x34:
			m_unk0x2c.m_x = p_parser->ReadFloat();
			m_unk0x2c.m_y = p_parser->ReadFloat();
			m_unk0x2c.m_z = p_parser->ReadFloat();
			m_unk0x38.m_x = p_parser->ReadFloat();
			m_unk0x38.m_y = p_parser->ReadFloat();
			m_unk0x38.m_z = p_parser->ReadFloat();
			break;
		default:
			break;
		}

		token = p_parser->GetNextToken();
	}

	m_unk0x10 = duration + m_unk0x0c;
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x004071a0
void SaffronQuartz0x2c::Frame0xb8::Event0x44::FUN_004071a0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004071b0
void SaffronQuartz0x2c::Frame0xb8::Event0x44::VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	Event0x20::VTable0x10(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x18(p_frame, m_name, this);
	}
}

// FUNCTION: LEGORACERS 0x004071e0
void SaffronQuartz0x2c::Frame0xb8::Event0x44::VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event)
{
	Event0x20::VTable0x14(p_frame, p_event);
	if (p_event) {
		p_event->VTable0x1c(p_frame, m_name, this);
	}
}
