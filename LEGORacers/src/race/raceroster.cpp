#include "race/racestate.h"

// FUNCTION: LEGORACERS 0x0043d150
RaceState::RaceRoster::RaceRoster()
{
	m_bodyEvents = NULL;
	m_raceState = NULL;
}

// FUNCTION: LEGORACERS 0x0043d170
void RaceState::RaceRoster::Destroy()
{
	m_bodyEvents = NULL;
	m_raceState = NULL;
	LegoEventQueue::Field0x30::Destroy();
}

// FUNCTION: LEGORACERS 0x0043d180
void RaceState::RaceRoster::VTable0x10(LegoU32 p_elapsedMs)
{
	PruneBodyEvents();
	LegoEventQueue::Field0x30::VTable0x10(p_elapsedMs);
	SortBodyEvents();
	TestRacerCollisions();
	PruneBodyEvents();
}

// FUNCTION: LEGORACERS 0x0043d1b0
LegoS32 RaceState::RaceRoster::VTable0x00(LegoEventQueue::Event* p_event)
{
	if (LegoEventQueue::Field0x30::VTable0x00(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_unk0x00 == 4) {
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
void RaceState::RaceRoster::PruneBodyEvents()
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

// FUNCTION: LEGORACERS 0x0043d260 FOLDED
GolWorldEntity* RaceState::RaceRoster::VTable0x14(LegoEventQueue::Event* p_event)
{
	return p_event->m_descriptor.m_worldEntity;
}

// FUNCTION: LEGORACERS 0x0043d270
void RaceState::RaceRoster::TestRacerCollisions()
{
	LegoEventQueue::Event* other;
	LegoEventQueue::Descriptor::Field0x10::Field0x0e0* target;
	GolWorldEntity* model;
	GolWorldEntity* otherModel;
	LegoFloat modelMinX;
	LegoFloat modelMaxX;
	LegoU32 flags;
	LegoEventQueue::Event* event;

	event = m_unk0x2c;
	for (; event; event = event->m_next) {
		if (event->m_active) {
			target = event->m_descriptor.m_target->m_ownerData;

			if (target) {
				model = LegoEventQueue::Field0x30::VTable0x14(event);
				other = m_bodyEvents;

				while (other) {
					if (other->m_active) {
						otherModel = other->m_descriptor.m_worldEntity;
						if (model->GetRadius() < 0.0f) {
							model->VTable0x00();
						}

						modelMinX = model->GetMinX();
						if (otherModel->GetRadius() < 0.0f) {
							otherModel->VTable0x00();
						}

						if (otherModel->GetMaxX() >= modelMinX) {
							break;
						}
					}

					other = other->m_next;
				}

				while (other) {
					if (other->m_active) {
						flags = other->m_descriptor.m_unk0x04;
						otherModel = other->m_descriptor.m_worldEntity;

						if (flags & 8) {
							if (target->m_unk0xd08 == 2) {
								other = other->m_next;
								continue;
							}
						}

						if (flags & 0x10) {
							if (target->m_unk0xd08 != 2) {
								other = other->m_next;
								continue;
							}
						}

						if (model->GetRadius() < 0.0f) {
							model->VTable0x00();
						}

						modelMaxX = model->GetMaxX();
						if (otherModel->GetRadius() < 0.0f) {
							otherModel->VTable0x00();
						}

						if (otherModel->GetMinX() > modelMaxX) {
							break;
						}

						if (model->VTable0x18(otherModel)) {
							m_callbackData.m_unk0x00 = 4;
							m_callbackData.m_worldEntity0 = otherModel;
							m_callbackData.m_field0x0e0 = target;
							other->FUN_004408e0(this, &m_callbackData);
						}
					}

					other = other->m_next;
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x0043d3f0
void RaceState::RaceRoster::SortBodyEvents()
{
	LegoFloat eventMinX;
	LegoEventQueue::Event* next;

	if (m_bodyEvents == NULL) {
		return;
	}

	LegoEventQueue::Event* previous = m_bodyEvents;
	GolWorldEntity* model = previous->m_descriptor.m_worldEntity;
	if (model->GetRadius() < 0.0f) {
		model->VTable0x00();
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
			eventModel->VTable0x00();
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
				eventModel->VTable0x00();
			}

			previousMinX = eventModel->GetMinX();
		}

		event = next;
	} while (event);
}
