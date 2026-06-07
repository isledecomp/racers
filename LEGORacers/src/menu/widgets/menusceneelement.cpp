#include "menu/widgets/menusceneelement.h"

DECOMP_SIZE_ASSERT(MenuSceneElement, 0x1c)

// FUNCTION: LEGORACERS 0x0046b290
MenuSceneElement::MenuSceneElement()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046b2d0
MenuSceneElement::~MenuSceneElement()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046b2e0
void MenuSceneElement::Reset()
{
	m_unk0x0c = 0;
	m_unk0x10 = 0;
	m_unk0x14 = 0;
	m_unk0x08 = 0;
	m_unk0x04 = 0;
	m_unk0x18 = 0;
}

// FUNCTION: LEGORACERS 0x0046b300
LegoBool32 MenuSceneElement::FUN_0046b300(CreateParams* p_createParams)
{
	VTable0x08();
	m_unk0x0c = p_createParams->m_golExport;
	m_unk0x10 = p_createParams->m_renderer;
	m_unk0x14 = p_createParams->m_unk0x08;
	m_unk0x18 = TRUE;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b330
LegoBool32 MenuSceneElement::VTable0x08()
{
	if (m_unk0x18) {
		Reset();
	}

	return !m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0046b350
MenuSceneElement* MenuSceneElement::FUN_0046b350(MenuSceneElement* p_parent)
{
	MenuSceneElement* result = p_parent;

	if (p_parent) {
		m_unk0x04 = p_parent;
		m_unk0x08 = p_parent->m_unk0x08;
		p_parent->m_unk0x08 = this;
		result = m_unk0x08;

		if (result) {
			result->m_unk0x04 = this;
		}
	}

	return result;
}
