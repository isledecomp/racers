#include "tanzanitewisp0x88.h"

#include "amberhaze0x1c.h"
#include "bronzefalcon0xc8770.h"
#include "gol.h"
#include "magentaribbon0x20.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(TanzaniteWisp0x88, 0x88)

// FUNCTION: LEGORACERS 0x0049d120
TanzaniteWisp0x88::TanzaniteWisp0x88()
{
	ResetMenuState();
}

// FUNCTION: LEGORACERS 0x0049d130
TanzaniteWisp0x88::~TanzaniteWisp0x88()
{
	ReleaseMenuResources();
}

// FUNCTION: LEGORACERS 0x0049d140
void TanzaniteWisp0x88::ResetMenuState()
{
	m_unk0x10 = 1;
	m_menuId = 0;
	m_golExport = NULL;
	m_renderer = NULL;
	m_menuResource0 = NULL;
	m_menuResource1 = NULL;
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_unk0x38 = 0;
	m_unk0x0c = 0;
}

// FUNCTION: LEGORACERS 0x0049d210
LegoBool32 TanzaniteWisp0x88::ReleaseMenuResources()
{
	if (!m_menuId) {
		return TRUE;
	}

	if (m_menuResource0) {
		m_golExport->VTable0x40(m_menuResource0);
	}

	if (m_menuResource1) {
		m_golExport->VTable0x44(m_menuResource1);
	}

	ResetMenuState();
	return m_menuId == 0;
}

// FUNCTION: LEGORACERS 0x0049d260
void TanzaniteWisp0x88::RefreshMenuResources()
{
	m_unk0x04 = 0;
	m_unk0x08 = 0;
	m_menuResource0->Clear();
	m_menuResource1->Clear();
	m_menuResource0->VTable0x1c(m_renderer, m_menuId);
	m_menuResource1->VTable0x1c(m_renderer, m_menuId);
}
