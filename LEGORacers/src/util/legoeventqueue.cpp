#include "util/legoeventqueue.h"

#include "golerror.h"
#include "golworldentity.h"
#include "util/proximityeventqueue.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(LegoEventQueue, 0x28)
DECOMP_SIZE_ASSERT(LegoEventQueue::Descriptor, 0x18)
DECOMP_SIZE_ASSERT(LegoEventQueue::CallbackData, 0x18)
DECOMP_SIZE_ASSERT(ProximityEventQueue, 0x2c)

// FUNCTION: LEGORACERS 0x0042f9f0
LegoEventQueue::LegoEventQueue()
{
	m_events = NULL;
	m_activeList = NULL;
}

// FUNCTION: LEGORACERS 0x0042fa30
LegoEventQueue::~LegoEventQueue()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0042fa40
void LegoEventQueue::Initialize(LegoU32 p_count)
{
	m_events = new Event[p_count];
	if (m_events == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	LegoU32 linkCount = p_count;
	m_freeList = m_events;
	linkCount--;
	if (linkCount > 0) {
		for (LegoU32 i = 0; i < linkCount; i++) {
			m_events[i].m_next = &m_events[i + 1];
		}
	}

	m_events[p_count - 1].m_next = NULL;
	m_activeList = NULL;
}

// FUNCTION: LEGORACERS 0x0042fb20
void LegoEventQueue::Destroy()
{
	if (m_events) {
		delete[] m_events;
		m_events = NULL;
	}

	m_freeList = NULL;
	m_activeList = NULL;
}

// FUNCTION: LEGORACERS 0x0042fb50
LegoEventQueue::Event* LegoEventQueue::AllocateEvent(Callback* p_callback, const Descriptor* p_descriptor)
{
	Event* result = m_freeList;
	if (result == NULL) {
		return NULL;
	}

	m_freeList = result->m_next;
	result->Initialize(p_callback, p_descriptor);
	AddEvent(result);

	return result;
}

// FUNCTION: LEGORACERS 0x0042fb90
LegoS32 LegoEventQueue::AddEvent(Event* p_event)
{
	if (p_event->m_descriptor.m_type == Descriptor::c_typeTimer) {
		p_event->m_next = m_activeList;
		m_activeList = p_event;
		p_event->m_descriptor.m_elapsedMs = 0;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042fbc0
void LegoEventQueue::PruneActiveList()
{
	Event* previous = NULL;
	Event* event = m_activeList;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_activeList == event) {
					m_activeList = next;
					FreeEvent(event);
				}
				else {
					previous->m_next = next;
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

// FUNCTION: LEGORACERS 0x0042fc10
void LegoEventQueue::Update(LegoU32 p_elapsedMs)
{
	Event* event = m_activeList;
	m_callbackData.m_type = Descriptor::c_typeTimer;

	if (event) {
		do {
			Descriptor* descriptor = &event->m_descriptor;
			LegoU32 elapsedMs = descriptor->m_elapsedMs;
			elapsedMs += p_elapsedMs;
			descriptor->m_elapsedMs = elapsedMs;
			LegoU32 durationMs = descriptor->m_intervalMs;

			if (elapsedMs >= durationMs) {
				m_callbackData.m_intervalMs = durationMs;
				m_callbackData.m_elapsedMs = elapsedMs;
				event->Fire(this, &m_callbackData);
				event->m_descriptor.m_elapsedMs = 0;
			}

			event = event->m_next;
		} while (event);
	}

	PruneActiveList();
}

// FUNCTION: LEGORACERS 0x0042fc70
LegoEventQueue::Event* LegoEventQueue::FreeEvent(Event* p_event)
{
	p_event->m_next = m_freeList;
	m_freeList = p_event;

	return p_event;
}

// FUNCTION: LEGORACERS 0x0042fc80
ProximityEventQueue::ProximityEventQueue()
{
	m_sortedList = NULL;
}

// FUNCTION: LEGORACERS 0x0042fcd0
void ProximityEventQueue::Destroy()
{
	m_sortedList = NULL;
	LegoEventQueue::Destroy();
}

// FUNCTION: LEGORACERS 0x0042fce0
void ProximityEventQueue::Update(LegoU32 p_elapsedMs)
{
	LegoEventQueue::Update(p_elapsedMs);
	SortList();
	TestPairs();
	PruneSortedList();
}

// FUNCTION: LEGORACERS 0x0042fd10
void ProximityEventQueue::TestPairs()
{
	Event* event = m_sortedList;
	Event* other;
	GolWorldEntity* model;
	GolWorldEntity* otherModel;
	LegoFloat maxX;

	if (event == NULL) {
		return;
	}

	do {
		if (event->m_active) {
			other = event->m_next;
			model = event->m_descriptor.m_worldEntity;

			if (other) {
				do {
					otherModel = other->m_descriptor.m_worldEntity;

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
							m_callbackData.m_worldEntity0 = model;
							m_callbackData.m_worldEntity1 = otherModel;
							event->Fire(this, &m_callbackData);

							if (!(event->m_descriptor.m_flags & 4)) {
								m_callbackData.m_type = Descriptor::c_typeProximity;
								m_callbackData.m_worldEntity0 = otherModel;
								m_callbackData.m_worldEntity1 = model;
								event->Fire(this, &m_callbackData);
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

// FUNCTION: LEGORACERS 0x0042fe10
void ProximityEventQueue::SortList()
{
	LegoFloat eventMinX;

	if (m_sortedList == NULL) {
		return;
	}

	GolWorldEntity* model = GetEventEntity(m_sortedList);
	if (model->GetRadius() < 0.0f) {
		model->UpdateBounds();
	}

	LegoFloat previousMinX = model->GetMinX();
	Event* previous = m_sortedList;
	Event* event = m_sortedList->m_next;

	if (event == NULL) {
		return;
	}

	do {
		Event* next = event->m_next;
		GolWorldEntity* eventModel = GetEventEntity(event);

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
					GolWorldEntity* insertModel = GetEventEntity(insertAfter);

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
				event->m_next = m_sortedList;
				m_sortedList->m_descriptor.m_previous = event;
				m_sortedList = event;
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

// FUNCTION: LEGORACERS 0x0042ff70
LegoS32 ProximityEventQueue::AddEvent(Event* p_event)
{
	if (LegoEventQueue::AddEvent(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_type == Descriptor::c_typeProximity) {
		if (m_sortedList) {
			m_sortedList->m_descriptor.m_previous = p_event;
		}

		p_event->m_descriptor.m_previous = NULL;
		p_event->m_next = m_sortedList;
		m_sortedList = p_event;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042ffc0
void ProximityEventQueue::PruneSortedList()
{
	Event* previous = NULL;
	Event* event = m_sortedList;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_sortedList == event) {
					m_sortedList = next;
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
