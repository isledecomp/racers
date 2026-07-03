#include "util/legoeventqueue.h"

#include <string.h>

DECOMP_SIZE_ASSERT(LegoEventQueue::Event, 0x2c)

// FUNCTION: LEGORACERS 0x00440880
LegoEventQueue::Event::Event()
{
	m_callback = NULL;
	m_descriptor.m_type = 0;
	m_descriptor.m_flags = 0;
	m_descriptor.m_maxFireCount = 0;
	m_descriptor.m_hitThreshold = 0;
	m_descriptor.m_intervalMs = 0;
	m_descriptor.m_elapsedMs = 0;
	m_fireCount = 0;
	m_hitCount = 0;
	m_active = 0;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x004408b0
void LegoEventQueue::Event::Initialize(Callback* p_callback, const Descriptor* p_descriptor)
{
	m_callback = p_callback;
	memcpy(&m_descriptor, p_descriptor, sizeof(m_descriptor));
	m_fireCount = 0;
	m_hitCount = 0;
	m_next = NULL;
	m_active = 1;
}

// FUNCTION: LEGORACERS 0x004408e0
void LegoEventQueue::Event::Fire(LegoEventQueue*, CallbackData* p_data)
{
	if (m_active) {
		m_hitCount++;
		p_data->m_hitCount = m_hitCount;

		if (m_descriptor.m_flags & 2) {
			if (m_hitCount < m_descriptor.m_hitThreshold) {
				return;
			}

			m_hitCount = 0;
		}

		m_fireCount++;
		p_data->m_fireCount = m_fireCount;
		p_data->m_flags = m_descriptor.m_flags;
		m_callback->OnEvent(p_data);

		if (!(m_descriptor.m_flags & 1)) {
			if (m_fireCount >= m_descriptor.m_maxFireCount) {
				m_active = 0;
			}
		}
	}
}
