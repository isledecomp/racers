#include "menu/screens/mainmenumodelslot.h"

#include "core/gol.h"
#include "golerror.h"
#include "golmodelbase.h"
#include "golscenenode.h"
#include "racer/drivermodelbuilder.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <string.h>

DECOMP_SIZE_ASSERT(MainMenuModelSlot, 0x15c)
DECOMP_SIZE_ASSERT(MainMenuModelSlot::CreateParams, 0x1c)

// GLOBAL: LEGORACERS 0x004b33c4
LegoFloat g_fltMax0x004b33c4 = FLT_MAX;

// FUNCTION: LEGORACERS 0x0047de70
MainMenuModelSlot::MainMenuModelSlot()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047df00
MainMenuModelSlot::~MainMenuModelSlot()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0047df60
void MainMenuModelSlot::Reset()
{
	::memset(&m_cosmetics, 0, sizeof(m_cosmetics));
	m_unk0x150 = NULL;
	m_unk0x114 = NULL;
	m_unk0x110 = NULL;
	m_unk0x14c = 0;
}

// FUNCTION: LEGORACERS 0x0047df90
void MainMenuModelSlot::FUN_0047df90()
{
	m_unk0x150->SetExpressionMask(TRUE);
	m_unk0x110 = m_unk0x0c->VTable0x14();

	undefined4 dimensions[5];
	m_unk0x150->GetMaxMergedCounts(dimensions);
	m_unk0x110->VTable0x18(m_unk0x10, 2, dimensions[0], dimensions[1], dimensions[2], dimensions[3]);

	undefined4 zero = 0;
	GolModelBase* nullModel = NULL;
	GolSceneNode* nullNode = NULL;
	m_cosmetics.m_legIndex = zero;
	m_cosmetics.m_torsoIndex = zero;
	m_cosmetics.m_faceIndex = zero;
	m_cosmetics.m_hatIndex = zero;
	m_unk0x110 = m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, zero);
	if (m_unk0x110 == nullModel) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x114 = m_unk0x0c->VTable0x18();
	if (m_unk0x114 == nullNode) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x114->VTable0x10(m_unk0x150->GetBodySceneNode(&m_cosmetics));
	m_unk0x1c.FUN_0040d550(m_unk0x110, m_unk0x114, &m_unk0x118, g_fltMax0x004b33c4);
}

// FUNCTION: LEGORACERS 0x0047e0a0
LegoBool32 MainMenuModelSlot::FUN_0047e0a0(CreateParams* p_createParams)
{
	VTable0x08();
	m_unk0x150 = p_createParams->m_unk0x0c;

	if (MenuSceneElement::FUN_0046b300(p_createParams)) {
		FUN_0047df90();
		m_unk0x1c.VTable0x08(p_createParams->m_position);
	}

	return m_unk0x18;
}

// FUNCTION: LEGORACERS 0x0047e0e0
LegoBool32 MainMenuModelSlot::VTable0x08()
{
	if (!m_unk0x18) {
		return TRUE;
	}

	m_unk0x1c.VTable0x54();

	if (m_unk0x110) {
		m_unk0x0c->VTable0x48(m_unk0x110);
	}

	if (m_unk0x114) {
		m_unk0x0c->VTable0x4c(m_unk0x114);
	}

	return MenuSceneElement::VTable0x08();
}

// FUNCTION: LEGORACERS 0x0047e130
void MainMenuModelSlot::FUN_0047e130(LegoU32 p_unk0x04)
{
	m_cosmetics.m_hatIndex = p_unk0x04;
	m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e160
void MainMenuModelSlot::FUN_0047e160(LegoU32 p_unk0x04, LegoU32 p_unk0x08)
{
	m_cosmetics.m_faceIndex = p_unk0x04;
	m_cosmetics.m_expressionIndex = p_unk0x08;
	GolModelBase* model = m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, 0);
	m_unk0x150->ApplyFaceExpression(model, &m_cosmetics);
}

// FUNCTION: LEGORACERS 0x0047e1b0
void MainMenuModelSlot::FUN_0047e1b0(LegoU32 p_unk0x04)
{
	m_cosmetics.m_torsoIndex = p_unk0x04;
	m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e1e0
void MainMenuModelSlot::FUN_0047e1e0(LegoU32 p_unk0x04)
{
	m_cosmetics.m_legIndex = p_unk0x04;
	m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e210
void MainMenuModelSlot::FUN_0047e210(DriverCosmetics* p_cosmetics)
{
	m_cosmetics = *p_cosmetics;
	m_unk0x150->BuildDriverModel(&m_cosmetics, m_unk0x110, 0);
}

// FUNCTION: LEGORACERS 0x0047e250
LegoBool32 MainMenuModelSlot::VTable0x0c()
{
	GolVec3 position;
	m_unk0x1c.VTable0x04(&position);
	m_unk0x1c.VTable0x08(position);
	m_unk0x10->VTable0x94(&m_unk0x1c);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047e290
LegoBool32 MainMenuModelSlot::VTable0x10(undefined4 p_unk0x04)
{
	m_unk0x1c.VTable0x10(p_unk0x04);
	return TRUE;
}
