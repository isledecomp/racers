#include "util/legoeventqueue.h"

DECOMP_SIZE_ASSERT(LegoEventQueue::Field0x30, 0x48)

// FUNCTION: LEGORACERS 0x0043a9e0
LegoEventQueue::Field0x30::Field0x30()
{
	m_unk0x2c = NULL;
}

// FUNCTION: LEGORACERS 0x0043aa00
void LegoEventQueue::Field0x30::Destroy()
{
	m_unk0x2c = NULL;
	Field0x2c::Destroy();
}

// FUNCTION: LEGORACERS 0x0043aa10
void LegoEventQueue::Field0x30::VTable0x10(LegoU32 p_elapsedMs)
{
	Field0x2c::VTable0x10(p_elapsedMs);
	FUN_0043aca0();
	FUN_0043ab90();
	FUN_0043aa90();
}

// FUNCTION: LEGORACERS 0x0043aa40
LegoS32 LegoEventQueue::Field0x30::VTable0x00(Event* p_event)
{
	if (Field0x2c::VTable0x00(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_unk0x00 == 3) {
		if (m_unk0x2c) {
			m_unk0x2c->m_descriptor.m_previous = p_event;
		}

		p_event->m_descriptor.m_previous = NULL;
		p_event->m_next = m_unk0x2c;
		m_unk0x2c = p_event;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0043aa90
void LegoEventQueue::Field0x30::FUN_0043aa90()
{
	Event* previous = NULL;
	Event* event = m_unk0x2c;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_unk0x2c == event) {
					m_unk0x2c = next;
					if (next) {
						next->m_descriptor.m_previous = NULL;
					}

					FUN_0042fc70(event);
				}
				else {
					previous->m_next = next;
					if (next) {
						next->m_descriptor.m_previous = previous;
					}

					FUN_0042fc70(event);
				}
			}
			else {
				previous = event;
			}

			event = next;
		} while (event);
	}
}

// FUNCTION: LEGORACERS 0x0043aaf0
GolWorldEntity* LegoEventQueue::Field0x30::VTable0x14(Event* p_event)
{
	return &p_event->m_descriptor.m_target->m_unk0x0e0->m_unk0x1c;
}

// FUNCTION: LEGORACERS 0x0043ab10
void LegoEventQueue::Field0x30::FUN_0043ab10(Event* p_event, LegoEventQueue*, CallbackData* p_data)
{
	Descriptor::Field0x10* target0 = p_data->m_target0;
	Descriptor::Field0x10* target1 = p_data->m_target1;
	CollisionCallbackData collisionData;

	m_unk0x30.m_unk0x00 = 3;
	if (target0->FUN_00441330(target1, &collisionData.m_unk0x1c, &collisionData.m_unk0x10, &collisionData.m_unk0x04)) {
		if (collisionData.m_unk0x1c != 0.0f) {
			m_unk0x30.m_target0 = target0;
			collisionData.m_unk0x20 = target1;
			collisionData.m_unk0x00 = 0;
			m_unk0x30.m_data = &collisionData;
			p_event->FUN_004408e0(this, &m_unk0x30);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043ab90
void LegoEventQueue::Field0x30::FUN_0043ab90()
{
	Event* event = m_unk0x2c;
	Event* other;
	GolWorldEntity* model;
	GolWorldEntity* otherModel;
	LegoFloat maxX;

	if (event == NULL) {
		return;
	}

	do {
		if (event->m_active) {
			model = event->m_descriptor.m_target->VTable0x08();
			other = event->m_next;

			if (other) {
				do {
					otherModel = other->m_descriptor.m_target->VTable0x08();

					if (model->GetRadius() < 0.0f) {
						model->VTable0x00();
					}

					maxX = model->GetMaxX();
					if (otherModel->GetRadius() < 0.0f) {
						otherModel->VTable0x00();
					}

					if (otherModel->GetMinX() <= maxX) {
						if (other->m_active && model->VTable0x18(otherModel)) {
							m_callbackData.m_unk0x00 = 2;
							m_callbackData.m_target0 = event->m_descriptor.m_target;
							m_callbackData.m_target1 = other->m_descriptor.m_target;
							FUN_0043ab10(event, this, &m_callbackData);

							if (!(event->m_descriptor.m_unk0x04 & 4)) {
								m_callbackData.m_unk0x00 = 2;
								m_callbackData.m_target0 = other->m_descriptor.m_target;
								m_callbackData.m_target1 = event->m_descriptor.m_target;
								FUN_0043ab10(other, this, &m_callbackData);
							}
						}
					}
					else {
						break;
					}

				} while ((other = other->m_next) != NULL);
			}
		}

		event = event->m_next;
	} while (event != NULL);
}

// FUNCTION: LEGORACERS 0x0043aca0
void LegoEventQueue::Field0x30::FUN_0043aca0()
{
	Event* previous = m_unk0x2c;
	LegoFloat eventMinX;

	if (previous == NULL) {
		return;
	}

	GolWorldEntity* model = previous->m_descriptor.m_target->VTable0x08();
	if (model->GetRadius() < 0.0f) {
		model->VTable0x00();
	}

	LegoFloat previousMinX = model->GetMinX();
	Event* event = previous->m_next;

	if (event == NULL) {
		return;
	}

	do {
		Event* next = event->m_next;
		GolWorldEntity* eventModel = event->m_descriptor.m_target->VTable0x08();

		if (eventModel->GetRadius() < 0.0f) {
			eventModel->VTable0x00();
		}

		if (eventModel->GetMinX() < previousMinX) {
			previous->m_next = next;
			if (next) {
				next->m_descriptor.m_previous = previous;
			}

			Event* insertAfter = previous->m_descriptor.m_previous;
			if (insertAfter) {
				do {
					GolWorldEntity* insertModel = insertAfter->m_descriptor.m_target->VTable0x08();

					if (eventModel->GetRadius() < 0.0f) {
						eventModel->VTable0x00();
					}

					eventMinX = eventModel->GetMinX();
					if (insertModel->GetRadius() < 0.0f) {
						insertModel->VTable0x00();
					}

					if (insertModel->GetMinX() <= eventMinX) {
						event->m_descriptor.m_previous = insertAfter;
						event->m_next = insertAfter->m_next;
						insertAfter->m_next->m_descriptor.m_previous = event;
						insertAfter->m_next = event;
						break;
					}

					insertAfter = insertAfter->m_descriptor.m_previous;
				} while (insertAfter);
			}

			if (insertAfter == NULL) {
				event->m_descriptor.m_previous = NULL;
				event->m_next = m_unk0x2c;
				m_unk0x2c->m_descriptor.m_previous = event;
				m_unk0x2c = event;
			}
		}
		else {
			previous = event;

			if (eventModel->GetRadius() < 0.0f) {
				eventModel->VTable0x00();
			}

			previousMinX = eventModel->GetMinX();
		}

		event = next;
	} while (event);
}

// FUNCTION: LEGORACERS 0x0043d260 FOLDED
GolWorldEntity* LegoEventQueue::Field0x2c::VTable0x14(Event* p_event)
{
	return p_event->m_descriptor.m_worldEntity;
}
