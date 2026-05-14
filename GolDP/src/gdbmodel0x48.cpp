#include "gdbmodel0x48.h"

#include "gdbvertexarray0xc.h"
#include "gdbvertexarraymistery0x1c.h"
#include "gdbvertexarraytypeone0x1c.h"
#include "gdbvertexarraytypethree0x20.h"
#include "gdbvertexarraytypetwo0x20.h"
#include "golerror.h"
#include "golfileparser.h"

DECOMP_SIZE_ASSERT(GdbModel0x48, 0x48)

// FUNCTION: GOLDP 0x10006840
GdbModel0x48::GdbModel0x48()
{
	m_unk0x40 = NULL;
}

// FUNCTION: GOLDP 0x10006860
GdbModel0x48::~GdbModel0x48()
{
	VTable0x24();
}

// FUNCTION: GOLDP 0x100068e0
void GdbModel0x48::VTable0x1c(WhiteFalcon0x140* p_renderer, const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_unk0x24) {
		VTable0x24();
	}

	IGdbModel0x40::VTable0x1c(p_renderer, p_name, p_binary);

	if (m_unk0x40 != NULL) {
		VTable0x38(&m_unk0x28, &m_unk0x34, m_unk0x38);
	}

	m_unk0x3c = TRUE;
}

// FUNCTION: GOLDP 0x10006930
void GdbModel0x48::VTable0x18(
	WhiteFalcon0x140* p_renderer,
	undefined2 p_vertexType,
	undefined4 p_arg3,
	undefined4 p_arg4,
	undefined4 p_arg5,
	undefined4 p_arg6
)
{
	if (m_unk0x24) {
		VTable0x24();
	}

	if (p_arg6 > 0) {
		m_unk0x04.FUN_10025df0(p_renderer, p_arg6);
	}

	switch (p_vertexType) {
	case e_vertexType1:
		m_unk0x40 = new GdbVertexArrayTypeOne0x1c;
		break;
	case e_vertexType2:
		m_unk0x40 = new GdbVertexArrayTypeTwo0x20;
		break;
	case e_vertexType3:
		m_unk0x40 = new GdbVertexArrayTypeThree0x20;
		break;
	default:
		GOL_FATALERROR_MESSAGE("Unsupported vertex type");
		break;
	}

	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	FUN_100272e0(p_arg4, p_arg5);
	m_unk0x40->VTable0x04(p_arg3);
	m_unk0x3c = 1;
}

// FUNCTION: GOLDP 0x10006a60
void GdbModel0x48::VTable0x24()
{
	if (m_unk0x40 != NULL) {
		m_unk0x40->VTable0x0c();
		delete m_unk0x40;
		m_unk0x40 = NULL;
		m_unk0x10 = 0;
	}

	IGdbModel0x40::VTable0x24();
}

// FUNCTION: GOLDP 0x10006aa0
void GdbModel0x48::VTable0x0c(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayMistery0x1c;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}

// FUNCTION: GOLDP 0x10006b30
void GdbModel0x48::VTable0x10(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayTypeOne0x1c;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}

// FUNCTION: GOLDP 0x10006bc0
void GdbModel0x48::VTable0x14(GolFileParser& p_parser)
{
	if (m_unk0x40 != NULL) {
		p_parser.HandleUnexpectedToken(GolFileParser::e_unsuportedKeyword);
	}

	m_unk0x40 = new GdbVertexArrayTypeTwo0x20;
	m_unk0x10 = m_unk0x40;
	if (m_unk0x10 == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x40->VTable0x08(p_parser);
}
