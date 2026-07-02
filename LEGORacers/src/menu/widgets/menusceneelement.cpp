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
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046b2e0
void MenuSceneElement::Reset()
{
	m_golExport = 0;
	m_renderer = 0;
	m_sceneView = 0;
	m_next = 0;
	m_prev = 0;
	m_created = 0;
}

// FUNCTION: LEGORACERS 0x0046b300
LegoBool32 MenuSceneElement::Create(CreateParams* p_createParams)
{
	Destroy();
	m_golExport = p_createParams->m_golExport;
	m_renderer = p_createParams->m_renderer;
	m_sceneView = p_createParams->m_sceneView;
	m_created = TRUE;

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046b330
LegoBool32 MenuSceneElement::Destroy()
{
	if (m_created) {
		Reset();
	}

	return !m_created;
}

// FUNCTION: LEGORACERS 0x0046b350
MenuSceneElement* MenuSceneElement::Append(MenuSceneElement* p_parent)
{
	MenuSceneElement* result = p_parent;

	if (p_parent) {
		m_prev = p_parent;
		m_next = p_parent->m_next;
		p_parent->m_next = this;
		result = m_next;

		if (result) {
			result->m_prev = this;
		}
	}

	return result;
}
