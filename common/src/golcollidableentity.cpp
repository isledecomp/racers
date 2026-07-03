#include "golcollidableentity.h"

#include "golboundingshape.h"
#include "render/golrenderdevice.h"

DECOMP_SIZE_ASSERT(GolCollidableEntity, 0x9c)

// FUNCTION: GOLDP 0x1001ac70
GolCollidableEntity::GolCollidableEntity()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
}

// FUNCTION: GOLDP 0x1001aca0
void GolCollidableEntity::SetPrimaryModelAndShape(
	GolModelBase* p_model,
	GolBoundingShape* p_shape,
	LegoFloat p_modelDistance
)
{
	GolModelEntity::SetPrimaryModel(p_model, p_modelDistance);
	m_boundingShapes[0] = p_shape;
}

// FUNCTION: GOLDP 0x1001acd0
void GolCollidableEntity::ResetModelState()
{
	m_boundingShapes[0] = NULL;
	m_boundingShapes[1] = NULL;
	m_boundingShapes[2] = NULL;
	GolModelEntity::ResetModelState();
}

// FUNCTION: GOLDP 0x1001acf0
void GolCollidableEntity::AddModel(GolModelBase* p_model, GolBoundingShape* p_shape, LegoFloat p_modelDistance)
{
	LegoU32 i;

	for (i = 0; i < 2; i++) {
		if (m_models[i] == NULL) {
			break;
		}
		if (p_modelDistance < m_modelDistances[i]) {
			LegoU32 j;
			for (j = 2; j > i; j--) {
				m_models[j] = m_models[j - 1];
				m_boundingShapes[j] = m_boundingShapes[j - 1];
				m_modelDistances[j] = m_modelDistances[j - 1];
			}
			break;
		}
	}
	m_models[i] = p_model;
	m_boundingShapes[i] = p_shape;
	m_modelDistances[i] = p_modelDistance;
}

// FUNCTION: GOLDP 0x1001ad70
void GolCollidableEntity::Draw(GolRenderDevice& p_renderer)
{
	p_renderer.DrawCollidableEntity(this);
}

// FUNCTION: LEGORACERS 0x00403c60
void GolCollidableEntity::MirrorY()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_boundingShapes); i++) {
		if (m_boundingShapes[i] != NULL) {
			m_boundingShapes[i]->MirrorY();
		}
	}
	GolOrientedEntity::MirrorY();
}
