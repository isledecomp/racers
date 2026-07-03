#include "race/racestate.h"

// FUNCTION: LEGORACERS 0x0043d150
RaceRoster::RaceRoster()
{
	m_bodyEvents = NULL;
	m_raceState = NULL;
}

// FUNCTION: LEGORACERS 0x0043d170
void RaceRoster::Destroy()
{
	m_bodyEvents = NULL;
	m_raceState = NULL;
	CollisionEventQueue::Destroy();
}

// FUNCTION: LEGORACERS 0x0043d180
void RaceRoster::Update(LegoU32 p_elapsedMs)
{
	PruneBodyEvents();
	CollisionEventQueue::Update(p_elapsedMs);
	SortBodyEvents();
	TestRacerCollisions();
	PruneBodyEvents();
}

// FUNCTION: LEGORACERS 0x0043d1b0
LegoS32 RaceRoster::AddEvent(LegoEventQueue::Event* p_event)
{
	if (CollisionEventQueue::AddEvent(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_type == LegoEventQueue::Descriptor::c_typeRacerTrigger) {
		if (m_bodyEvents) {
			m_bodyEvents->m_descriptor.m_previous = p_event;
		}

		p_event->m_descriptor.m_previous = NULL;
		p_event->m_next = m_bodyEvents;
		m_bodyEvents = p_event;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0043d200
void RaceRoster::PruneBodyEvents()
{
	LegoEventQueue::Event* previous = NULL;
	LegoEventQueue::Event* event = m_bodyEvents;

	if (event) {
		do {
			LegoEventQueue::Event* next = event->m_next;

			if (!event->m_active) {
				if (m_bodyEvents == event) {
					m_bodyEvents = next;
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

// FUNCTION: LEGORACERS 0x0043d260 FOLDED
GolWorldEntity* RaceRoster::GetEventEntity(LegoEventQueue::Event* p_event)
{
	return p_event->m_descriptor.m_worldEntity;
}

// FUNCTION: LEGORACERS 0x0043d270
void RaceRoster::TestRacerCollisions()
{
	LegoEventQueue::Event* other;
	LegoEventQueue::Descriptor::RigidBody::RacerView* target;
	GolWorldEntity* model;
	GolWorldEntity* otherModel;
	LegoFloat modelMinX;
	LegoFloat modelMaxX;
	LegoU32 flags;
	LegoEventQueue::Event* event;

	event = m_bodyList;
	for (; event; event = event->m_next) {
		if (event->m_active) {
			target = event->m_descriptor.m_target->m_ownerData;

			if (target) {
				model = CollisionEventQueue::GetEventEntity(event);
				other = m_bodyEvents;

				while (other) {
					if (other->m_active) {
						otherModel = other->m_descriptor.m_worldEntity;
						if (model->GetRadius() < 0.0f) {
							model->UpdateBounds();
						}

						modelMinX = model->GetMinX();
						if (otherModel->GetRadius() < 0.0f) {
							otherModel->UpdateBounds();
						}

						if (otherModel->GetMaxX() >= modelMinX) {
							break;
						}
					}

					other = other->m_next;
				}

				while (other) {
					if (other->m_active) {
						flags = other->m_descriptor.m_flags;
						otherModel = other->m_descriptor.m_worldEntity;

						if (flags & 8) {
							if (target->m_controlMode == Racer::c_controlAi) {
								other = other->m_next;
								continue;
							}
						}

						if (flags & 0x10) {
							if (target->m_controlMode != Racer::c_controlAi) {
								other = other->m_next;
								continue;
							}
						}

						if (model->GetRadius() < 0.0f) {
							model->UpdateBounds();
						}

						modelMaxX = model->GetMaxX();
						if (otherModel->GetRadius() < 0.0f) {
							otherModel->UpdateBounds();
						}

						if (otherModel->GetMinX() > modelMaxX) {
							break;
						}

						if (model->Intersects(otherModel)) {
							m_callbackData.m_type = LegoEventQueue::Descriptor::c_typeRacerTrigger;
							m_callbackData.m_worldEntity0 = otherModel;
							m_callbackData.m_racerView1 = target;
							other->Fire(this, &m_callbackData);
						}
					}

					other = other->m_next;
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0043d3f0
void RaceRoster::SortBodyEvents()
{
	LegoFloat eventMinX;
	LegoEventQueue::Event* next;

	if (m_bodyEvents == NULL) {
		return;
	}

	LegoEventQueue::Event* previous = m_bodyEvents;
	GolWorldEntity* model = previous->m_descriptor.m_worldEntity;
	if (model->GetRadius() < 0.0f) {
		model->UpdateBounds();
	}

	LegoFloat previousMinX = model->GetMinX();
	LegoEventQueue::Event* event = m_bodyEvents->m_next;

	if (event == NULL) {
		return;
	}

	do {
		next = event->m_next;
		GolWorldEntity* eventModel = event->m_descriptor.m_worldEntity;

		if (eventModel->GetRadius() < 0.0f) {
			eventModel->UpdateBounds();
		}

		if (eventModel->GetMinX() < previousMinX) {
			previous->m_next = next;
			if (next) {
				next->m_descriptor.m_previous = previous;
			}

			LegoEventQueue::Event* insertAfter = previous->m_descriptor.m_previous;
			while (insertAfter) {
				GolWorldEntity* insertModel = insertAfter->m_descriptor.m_worldEntity;

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
			}

			if (insertAfter == NULL) {
				event->m_descriptor.m_previous = NULL;
				event->m_next = m_bodyEvents;
				m_bodyEvents->m_descriptor.m_previous = event;
				m_bodyEvents = event;
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
