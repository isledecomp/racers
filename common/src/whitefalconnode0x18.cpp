#include "whitefalconnode0x18.h"

#include "golbinparser.h"
#include "golerror.h"
#include "jadeorbitbase0x10.h"

#include <string.h>

DECOMP_SIZE_ASSERT(WhiteFalconNode0x18, 0x18)

// FUNCTION: GOLDP 0x10029980
WhiteFalconNode0x18::WhiteFalconNode0x18()
{
	m_capacity = 0;
	m_unk0x14 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x100299c0
WhiteFalconNode0x18::~WhiteFalconNode0x18()
{
	GolNameTable::Clear();
	m_capacity = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x10029a20
void WhiteFalconNode0x18::VTable0x14(const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_capacity != 0) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".sdb");
	}
	else {
		parser = new DdfTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		if (token != GolFileParser::e_unknown0x27) {
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		FUN_10029c60(parser);
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// STUB: GOLDP 0x10029b50
void WhiteFalconNode0x18::VTable0x10(WhiteFalconNode0x18*)
{
	STUB(0x10029b50);
}

// FUNCTION: GOLDP 0x10029c10
void WhiteFalconNode0x18::Allocate(LegoU32 p_capacity)
{
	if (m_capacity != 0) {
		Clear();
	}

	m_capacity = p_capacity;
	GolNameTable::Allocate(m_capacity);
	VTable0x0c();
}

// FUNCTION: GOLDP 0x10029c40
void WhiteFalconNode0x18::Clear()
{
	GolNameTable::Clear();
	m_capacity = 0;
	m_unk0x0c = 0;
}

// FUNCTION: GOLDP 0x10029c60
void WhiteFalconNode0x18::FUN_10029c60(GolFileParser* p_parser)
{
	m_capacity = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_capacity == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_capacity);
	VTable0x0c();

	for (LegoU32 i = 0; i < m_capacity; i++) {
		JadeOrbitBase0x10* orbit = VTable0x18(i);
		GolName name;

		p_parser->AssertNextTokenIs(GolFileParser::e_unknown0x27);
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));
		GolNameTable::AddName(name, orbit);
		p_parser->ReadLeftCurly();

		GolFileParser::ParserTokenType token;
		while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case GolFileParser::e_unknown0x2a: {
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));

				JadeOrbitBase0x10* parent = static_cast<JadeOrbitBase0x10*>(GetName(name));
				if (parent == NULL) {
					p_parser->HandleUnexpectedToken(GolFileParser::e_invalidString);
				}

				parent->FUN_1001ceb0(orbit);
				break;
			}
			case GolFileParser::e_unknown0x29: {
				LegoFloat values[4];
				values[0] = p_parser->ReadFloat();
				values[1] = p_parser->ReadFloat();
				values[2] = p_parser->ReadFloat();
				values[3] = p_parser->ReadFloat();
				orbit->VTable0x2c(values);
				break;
			}
			case GolFileParser::e_unknown0x28: {
				GolVec3 position;
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				orbit->SetPosition(&position);
				break;
			}
			}
		}
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
// FUNCTION: LEGORACERS 0x004113b0 FOLDED
LegoU32 WhiteFalconNode0x18::VTable0x1c(const JadeOrbitBase0x10&) const
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x20(const GolMatrix4&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void WhiteFalconNode0x18::VTable0x24(const GolMatrix34* p_m)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x28(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void WhiteFalconNode0x18::VTable0x2c(LegoU32 p_index, GolMatrix34* p_dest) const
{
	// empty
}

// FUNCTION: LEGORACERS 0x004132a0
void WhiteFalconNode0x18::FUN_004132a0(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	*p_param3 = *p_param2;

	GolVec3 vec;
	for (JadeOrbitBase0x10* current = VTable0x18(p_param1); current != NULL; current = current->m_unk0x04) {
		vec = *p_param3;
		current->VTable0x0c(&vec, p_param3);
	}
}
