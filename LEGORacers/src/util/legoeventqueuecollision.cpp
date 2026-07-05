#include "race/racer/racer.h"
#include "util/collisioneventqueue.h"
#include "util/legoeventqueue.h"
#include "util/proximityeventqueue.h"

DECOMP_SIZE_ASSERT(CollisionEventQueue, 0x48)

// FUNCTION: LEGORACERS 0x0043a9e0
CollisionEventQueue::CollisionEventQueue()
{
	m_bodyList = NULL;
}

// FUNCTION: LEGORACERS 0x0043aa00
void CollisionEventQueue::Destroy()
{
	m_bodyList = NULL;
	ProximityEventQueue::Destroy();
}

// FUNCTION: LEGORACERS 0x0043aa10
void CollisionEventQueue::Update(LegoU32 p_elapsedMs)
{
	ProximityEventQueue::Update(p_elapsedMs);
	SortBodyList();
	TestBodyPairs();
	PruneBodyList();
}

// FUNCTION: LEGORACERS 0x0043aa40
LegoS32 CollisionEventQueue::AddEvent(Event* p_event)
{
	if (ProximityEventQueue::AddEvent(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_type == Descriptor::c_typeCollision) {
		if (m_bodyList) {
			m_bodyList->m_descriptor.m_previous = p_event;
		}

		p_event->m_descriptor.m_previous = NULL;
		p_event->m_next = m_bodyList;
		m_bodyList = p_event;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0043aa90
void CollisionEventQueue::PruneBodyList()
{
	Event* previous = NULL;
	Event* event = m_bodyList;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_bodyList == event) {
					m_bodyList = next;
					if (next) {
						next->m_descriptor.m_previous = NULL;
					}

					FreeEvent(event);
				}
				else {
					previous->m_next = next;
					if (next) {
						next->m_descriptor.m_previous = previous;
					}

					FreeEvent(event);
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
GolWorldEntity* CollisionEventQueue::GetEventEntity(Event* p_event)
{
	return &p_event->m_descriptor.m_target->m_ownerData->m_visuals.m_entityGroup;
}

// FUNCTION: LEGORACERS 0x0043ab10
void CollisionEventQueue::DispatchContact(Event* p_event, LegoEventQueue*, CallbackData* p_data)
{
	Descriptor::RigidBody* target0 = p_data->m_target0;
	Descriptor::RigidBody* target1 = p_data->m_target1;
	CollisionCallbackData collisionData;

	m_collisionData.m_type = Descriptor::c_typeCollision;
	if (target0->CalculateBoxContact(
			target1,
			&collisionData.m_penetrationDepth,
			&collisionData.m_normal,
			&collisionData.m_contactPoint
		)) {
		if (collisionData.m_penetrationDepth != 0.0f) {
			m_collisionData.m_target0 = target0;
			collisionData.m_secondTarget = target1;
			collisionData.m_unk0x00 = 0;
			m_collisionData.m_data = &collisionData;
			p_event->Fire(this, &m_collisionData);
		}
	}
}

// FUNCTION: LEGORACERS 0x0043ab90
void CollisionEventQueue::TestBodyPairs()
{
	Event* event = m_bodyList;
	Event* other;
	GolWorldEntity* model;
	GolWorldEntity* otherModel;
	LegoFloat maxX;

	if (event == NULL) {
		return;
	}

	do {
		if (event->m_active) {
			model = event->m_descriptor.m_target->GetEntity();
			other = event->m_next;

			if (other) {
				do {
					otherModel = other->m_descriptor.m_target->GetEntity();

					if (model->GetRadius() < 0.0f) {
						model->UpdateBounds();
					}

					maxX = model->GetMaxX();
					if (otherModel->GetRadius() < 0.0f) {
						otherModel->UpdateBounds();
					}

					if (otherModel->GetMinX() <= maxX) {
						if (other->m_active && model->Intersects(otherModel)) {
							m_callbackData.m_type = Descriptor::c_typeProximity;
							m_callbackData.m_target0 = event->m_descriptor.m_target;
							m_callbackData.m_target1 = other->m_descriptor.m_target;
							DispatchContact(event, this, &m_callbackData);

							if (!(event->m_descriptor.m_flags & 4)) {
								m_callbackData.m_type = Descriptor::c_typeProximity;
								m_callbackData.m_target0 = other->m_descriptor.m_target;
								m_callbackData.m_target1 = event->m_descriptor.m_target;
								DispatchContact(other, this, &m_callbackData);
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
void CollisionEventQueue::SortBodyList()
{
	Event* previous = m_bodyList;
	LegoFloat eventMinX;

	if (previous == NULL) {
		return;
	}

	GolWorldEntity* model = previous->m_descriptor.m_target->GetEntity();
	if (model->GetRadius() < 0.0f) {
		model->UpdateBounds();
	}

	LegoFloat previousMinX = model->GetMinX();
	Event* event = previous->m_next;

	if (event == NULL) {
		return;
	}

	do {
		Event* next = event->m_next;
		GolWorldEntity* eventModel = event->m_descriptor.m_target->GetEntity();

		if (eventModel->GetRadius() < 0.0f) {
			eventModel->UpdateBounds();
		}

		if (eventModel->GetMinX() < previousMinX) {
			previous->m_next = next;
			if (next) {
				next->m_descriptor.m_previous = previous;
			}

			Event* insertAfter = previous->m_descriptor.m_previous;
			if (insertAfter) {
				do {
					GolWorldEntity* insertModel = insertAfter->m_descriptor.m_target->GetEntity();

					if (eventModel->GetRadius() < 0.0f) {
						eventModel->UpdateBounds();
					}

					eventMinX = eventModel->GetMinX();
					if (insertModel->GetRadius() < 0.0f) {
						insertModel->UpdateBounds();
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
				event->m_next = m_bodyList;
				m_bodyList->m_descriptor.m_previous = event;
				m_bodyList = event;
			}
		}
		else {
			previous = event;

			if (eventModel->GetRadius() < 0.0f) {
				eventModel->UpdateBounds();
			}

			previousMinX = eventModel->GetMinX();
		}

		event = next;
	} while (event);
}

// FUNCTION: LEGORACERS 0x0043d260 FOLDED
GolWorldEntity* ProximityEventQueue::GetEventEntity(Event* p_event)
{
	return p_event->m_descriptor.m_worldEntity;
}
