#include "util/legoeventqueue.h"

#include "golerror.h"

DECOMP_SIZE_ASSERT(LegoEventQueue, 0x28)
DECOMP_SIZE_ASSERT(LegoEventQueue::Descriptor, 0x18)
DECOMP_SIZE_ASSERT(LegoEventQueue::CallbackData, 0x18)
DECOMP_SIZE_ASSERT(LegoEventQueue::Field0x2c, 0x2c)

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

// STUB: LEGORACERS 0x0042fa40
void LegoEventQueue::VTable0x08(LegoU32 p_count)
{
	m_events = new Event[p_count];
	if (m_events == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_freeList = m_events;
	p_count--;

	if (p_count > 0) {
		for (LegoU32 i = 0; i < p_count; i++) {
			m_events[i].m_next = &m_events[i + 1];
		}
	}

	m_events[p_count].m_next = NULL;
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
LegoEventQueue::Event* LegoEventQueue::FUN_0042fb50(Callback* p_callback, const Descriptor* p_descriptor)
{
	Event* result = m_freeList;
	if (result == NULL) {
		return NULL;
	}

	m_freeList = result->m_next;
	result->FUN_004408b0(p_callback, p_descriptor);
	VTable0x00(result);

	return result;
}

// FUNCTION: LEGORACERS 0x0042fb90
LegoS32 LegoEventQueue::VTable0x00(Event* p_event)
{
	if (p_event->m_descriptor.m_unk0x00 == 1) {
		p_event->m_next = m_activeList;
		m_activeList = p_event;
		p_event->m_descriptor.m_unk0x14 = 0;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042fbc0
void LegoEventQueue::FUN_0042fbc0()
{
	Event* previous = NULL;
	Event* event = m_activeList;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_activeList == event) {
					m_activeList = next;
					FUN_0042fc70(event);
				}
				else {
					previous->m_next = next;
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

// FUNCTION: LEGORACERS 0x0042fc10
void LegoEventQueue::VTable0x10(LegoU32 p_elapsedMs)
{
	Event* event = m_activeList;
	m_callbackData.m_unk0x00 = 1;

	if (event) {
		do {
			Descriptor* descriptor = &event->m_descriptor;
			LegoU32 elapsedMs = descriptor->m_unk0x14;
			elapsedMs += p_elapsedMs;
			descriptor->m_unk0x14 = elapsedMs;
			LegoU32 durationMs = descriptor->m_unk0x10;

			if (elapsedMs >= durationMs) {
				m_callbackData.m_unk0x10 = durationMs;
				m_callbackData.m_unk0x14 = elapsedMs;
				event->FUN_004408e0(this, &m_callbackData);
				event->m_descriptor.m_unk0x14 = 0;
			}

			event = event->m_next;
		} while (event);
	}

	FUN_0042fbc0();
}

// FUNCTION: LEGORACERS 0x0042fc70
LegoEventQueue::Event* LegoEventQueue::FUN_0042fc70(Event* p_event)
{
	p_event->m_next = m_freeList;
	m_freeList = p_event;

	return p_event;
}

// FUNCTION: LEGORACERS 0x0042fc80
LegoEventQueue::Field0x2c::Field0x2c()
{
	m_unk0x28 = NULL;
}

// FUNCTION: LEGORACERS 0x0042fcd0
void LegoEventQueue::Field0x2c::Destroy()
{
	m_unk0x28 = NULL;
	LegoEventQueue::Destroy();
}

// FUNCTION: LEGORACERS 0x0042fce0
void LegoEventQueue::Field0x2c::VTable0x10(LegoU32 p_elapsedMs)
{
	LegoEventQueue::VTable0x10(p_elapsedMs);
	FUN_0042fe10();
	FUN_0042fd10();
	FUN_0042ffc0();
}

// STUB: LEGORACERS 0x0042fd10
void LegoEventQueue::Field0x2c::FUN_0042fd10()
{
	Event* event = m_unk0x28;
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
						model->VTable0x00();
					}

					maxX = model->GetMaxX();
					if (otherModel->GetRadius() < 0.0f) {
						otherModel->VTable0x00();
					}

					if (otherModel->GetMinX() <= maxX) {
						if (other->m_active && model->VTable0x18(otherModel)) {
							m_callbackData.m_unk0x00 = 2;
							m_callbackData.m_worldEntity0 = model;
							m_callbackData.m_worldEntity1 = otherModel;
							event->FUN_004408e0(this, &m_callbackData);

							if (!(event->m_descriptor.m_unk0x04 & 4)) {
								m_callbackData.m_unk0x00 = 2;
								m_callbackData.m_worldEntity0 = otherModel;
								m_callbackData.m_worldEntity1 = model;
								other->FUN_004408e0(this, &m_callbackData);
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
void LegoEventQueue::Field0x2c::FUN_0042fe10()
{
	LegoFloat eventMinX;

	if (m_unk0x28 == NULL) {
		return;
	}

	GolWorldEntity* model = VTable0x14(m_unk0x28);
	if (model->GetRadius() < 0.0f) {
		model->VTable0x00();
	}

	LegoFloat previousMinX = model->GetMinX();
	Event* previous = m_unk0x28;
	Event* event = m_unk0x28->m_next;

	if (event == NULL) {
		return;
	}

	do {
		Event* next = event->m_next;
		GolWorldEntity* eventModel = VTable0x14(event);

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
					GolWorldEntity* insertModel = VTable0x14(insertAfter);

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
				event->m_next = m_unk0x28;
				m_unk0x28->m_descriptor.m_previous = event;
				m_unk0x28 = event;
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

// FUNCTION: LEGORACERS 0x0042ff70
LegoS32 LegoEventQueue::Field0x2c::VTable0x00(Event* p_event)
{
	if (LegoEventQueue::VTable0x00(p_event)) {
		return 1;
	}

	if (p_event->m_descriptor.m_unk0x00 == 2) {
		if (m_unk0x28) {
			m_unk0x28->m_descriptor.m_previous = p_event;
		}

		p_event->m_descriptor.m_previous = NULL;
		p_event->m_next = m_unk0x28;
		m_unk0x28 = p_event;

		return 1;
	}

	return 0;
}

// FUNCTION: LEGORACERS 0x0042ffc0
void LegoEventQueue::Field0x2c::FUN_0042ffc0()
{
	Event* previous = NULL;
	Event* event = m_unk0x28;

	if (event) {
		do {
			Event* next = event->m_next;

			if (!event->m_active) {
				if (m_unk0x28 == event) {
					m_unk0x28 = next;
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
