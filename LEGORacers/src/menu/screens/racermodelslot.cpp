#include "menu/screens/racermodelslot.h"

#include "golworldentity.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerModelSlot, 0xa0)
DECOMP_SIZE_ASSERT(RacerModelSlot::CreateParams, 0x48)

// FUNCTION: LEGORACERS 0x004874b0
RacerModelSlot::RacerModelSlot()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00487520
RacerModelSlot::~RacerModelSlot()
{
	Destroy();
}

// STUB: LEGORACERS 0x00487570
void RacerModelSlot::Reset()
{
	::memset(&m_createParams, 0, sizeof(m_createParams));

	undefined4 zero = 0;
	undefined4* values = m_unk0x88;
	m_entity = NULL;
	*values++ = zero;
	m_entityB = NULL;
	m_entityA = NULL;
	m_spinAxis.m_y = 0.0f;
	*values++ = zero;
	m_spinAxis.m_x = 0.0f;
	m_spinAxis.m_z = 1.0f;
	m_unk0x84 = 0;
	*values = zero;
	m_unk0x80 = 0;
	m_unk0x7c = 0;
	m_timerBMs = 0;
	m_timerAMs = 0;
	m_promoteA = TRUE;
}

// FUNCTION: LEGORACERS 0x004875d0
LegoBool32 RacerModelSlot::Create(CreateParams* p_createParams)
{
	Destroy();
	m_createParams = *p_createParams;
	return MenuSceneElement::Create(p_createParams);
}

// FUNCTION: LEGORACERS 0x00487600
void RacerModelSlot::SetEntity(GolWorldEntity* p_entity)
{
	m_entity = p_entity;
	if (p_entity != NULL) {
		p_entity->SetPosition(m_createParams.m_position);
		p_entity->ClearVelocity();
	}
}

// FUNCTION: LEGORACERS 0x00487630
LegoBool32 RacerModelSlot::UpdateEntityA(LegoU32 p_elapsed)
{
	if (m_entityA != NULL) {
		LegoU32 elapsed = p_elapsed;
		if (elapsed > m_timerAMs) {
			elapsed = m_timerAMs;
		}

		m_entityA->Update(elapsed);
		m_timerAMs -= elapsed;

		if (m_timerAMs == 0) {
			if (m_promoteA) {
				SetEntity(m_entityA);
			}

			m_entityA = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487690
LegoBool32 RacerModelSlot::UpdateEntityB(LegoU32 p_elapsed)
{
	if (m_entityB != NULL) {
		LegoU32 elapsed = p_elapsed;
		if (elapsed > m_timerBMs) {
			elapsed = m_timerBMs;
		}

		m_entityB->Update(elapsed);
		m_timerBMs -= elapsed;

		if (m_timerBMs == 0) {
			if (!m_promoteA) {
				SetEntity(m_entityB);
			}

			m_entityB = NULL;
		}
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x004876f0
LegoBool32 RacerModelSlot::UpdateSpin(LegoS32 p_elapsed)
{
	if (m_entity == NULL) {
		return TRUE;
	}

	if (m_createParams.m_animate) {
		m_entity->Update(p_elapsed);
	}

	if (m_createParams.m_spinSpeed == 0.0f) {
		return TRUE;
	}

	LegoFloat angle = static_cast<LegoFloat>(p_elapsed) * m_createParams.m_spinSpeed;
	GolVec3 right;
	GolVec3 forward;
	m_entity->GetAxes(&right, &forward);

	GolMath::RotateAboutAxis(&right, &forward, &m_spinAxis, angle);
	m_entity->SetDirectionUp(forward, m_spinAxis);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487790
LegoBool32 RacerModelSlot::Draw()
{
	GolVec3 center;

	if (m_entityA != NULL) {
		m_entityA->GetPosition(&center);
		m_entityA->SetPosition(center);
		m_entityA->Draw(*m_renderer);
	}

	if (m_entity != NULL) {
		m_entity->GetPosition(&center);
		m_entity->SetPosition(center);
		m_entity->Draw(*m_renderer);
	}

	if (m_entityB != NULL) {
		m_entityB->GetPosition(&center);
		m_entityB->SetPosition(center);
		m_entityB->Draw(*m_renderer);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00487820
LegoBool32 RacerModelSlot::Update(LegoU32 p_elapsed)
{
	UpdateEntityA(p_elapsed);
	UpdateSpin(p_elapsed);
	UpdateEntityB(p_elapsed);

	return TRUE;
}
