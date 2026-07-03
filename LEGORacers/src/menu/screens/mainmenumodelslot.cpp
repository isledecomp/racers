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
LegoFloat g_unlimitedModelDistance = FLT_MAX;

// FUNCTION: LEGORACERS 0x0047de70
MainMenuModelSlot::MainMenuModelSlot()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0047df00
MainMenuModelSlot::~MainMenuModelSlot()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0047df60
void MainMenuModelSlot::Reset()
{
	::memset(&m_cosmetics, 0, sizeof(m_cosmetics));
	m_modelBuilder = NULL;
	m_bodySceneNode = NULL;
	m_driverModel = NULL;
	m_unk0x14c = 0;
}

// FUNCTION: LEGORACERS 0x0047df90
void MainMenuModelSlot::CreateDriverModel()
{
	m_modelBuilder->SetExpressionMask(TRUE);
	m_driverModel = m_golExport->CreateModel();

	undefined4 dimensions[5];
	m_modelBuilder->GetMaxMergedCounts(dimensions);
	m_driverModel->Allocate(m_renderer, 2, dimensions[0], dimensions[1], dimensions[2], dimensions[3]);

	undefined4 zero = 0;
	GolModelBase* nullModel = NULL;
	GolSceneNode* nullNode = NULL;
	m_cosmetics.m_legIndex = zero;
	m_cosmetics.m_torsoIndex = zero;
	m_cosmetics.m_faceIndex = zero;
	m_cosmetics.m_hatIndex = zero;
	m_driverModel = m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, zero);
	if (m_driverModel == nullModel) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_bodySceneNode = m_golExport->CreateSceneNode();
	if (m_bodySceneNode == nullNode) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_bodySceneNode->CopyFrom(m_modelBuilder->GetBodySceneNode(&m_cosmetics));
	m_driverEntity.SetModel(m_driverModel, m_bodySceneNode, &m_bodyModelPart, g_unlimitedModelDistance);
}

// FUNCTION: LEGORACERS 0x0047e0a0
LegoBool32 MainMenuModelSlot::Create(CreateParams* p_createParams)
{
	Destroy();
	m_modelBuilder = p_createParams->m_modelBuilder;

	if (MenuSceneElement::Create(p_createParams)) {
		CreateDriverModel();
		m_driverEntity.SetPosition(p_createParams->m_position);
	}

	return m_created;
}

// FUNCTION: LEGORACERS 0x0047e0e0
LegoBool32 MainMenuModelSlot::Destroy()
{
	if (!m_created) {
		return TRUE;
	}

	m_driverEntity.ResetModelState();

	if (m_driverModel) {
		m_golExport->DestroyModel(m_driverModel);
	}

	if (m_bodySceneNode) {
		m_golExport->DestroySceneNode(m_bodySceneNode);
	}

	return MenuSceneElement::Destroy();
}

// FUNCTION: LEGORACERS 0x0047e130
void MainMenuModelSlot::SetHat(LegoU32 p_hatIndex)
{
	m_cosmetics.m_hatIndex = p_hatIndex;
	m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, 0);
}

// FUNCTION: LEGORACERS 0x0047e160
void MainMenuModelSlot::SetFace(LegoU32 p_faceIndex, LegoU32 p_expressionIndex)
{
	m_cosmetics.m_faceIndex = p_faceIndex;
	m_cosmetics.m_expressionIndex = p_expressionIndex;
	GolModelBase* model = m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, 0);
	m_modelBuilder->ApplyFaceExpression(model, &m_cosmetics);
}

// FUNCTION: LEGORACERS 0x0047e1b0
void MainMenuModelSlot::SetTorso(LegoU32 p_torsoIndex)
{
	m_cosmetics.m_torsoIndex = p_torsoIndex;
	m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, 0);
}

// FUNCTION: LEGORACERS 0x0047e1e0
void MainMenuModelSlot::SetLegs(LegoU32 p_legIndex)
{
	m_cosmetics.m_legIndex = p_legIndex;
	m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, 0);
}

// FUNCTION: LEGORACERS 0x0047e210
void MainMenuModelSlot::SetCosmetics(DriverCosmetics* p_cosmetics)
{
	m_cosmetics = *p_cosmetics;
	m_modelBuilder->BuildDriverModel(&m_cosmetics, m_driverModel, 0);
}

// FUNCTION: LEGORACERS 0x0047e250
LegoBool32 MainMenuModelSlot::Draw()
{
	GolVec3 position;
	m_driverEntity.GetPosition(&position);
	m_driverEntity.SetPosition(position);
	m_renderer->DrawModelEntity(&m_driverEntity);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047e290
LegoBool32 MainMenuModelSlot::Update(undefined4 p_elapsedMs)
{
	m_driverEntity.Update(p_elapsedMs);
	return TRUE;
}
