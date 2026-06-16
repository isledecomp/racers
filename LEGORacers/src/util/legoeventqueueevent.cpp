#include "util/legoeventqueue.h"

#include <string.h>

DECOMP_SIZE_ASSERT(LegoEventQueue::Event, 0x2c)

// FUNCTION: LEGORACERS 0x00440880
LegoEventQueue::Event::Event()
{
	m_callback = NULL;
	m_descriptor.m_unk0x00 = 0;
	m_descriptor.m_unk0x04 = 0;
	m_descriptor.m_unk0x08 = 0;
	m_descriptor.m_unk0x0c = 0;
	m_descriptor.m_unk0x10 = 0;
	m_descriptor.m_unk0x14 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_active = 0;
	m_next = NULL;
}

// FUNCTION: LEGORACERS 0x004408b0
void LegoEventQueue::Event::FUN_004408b0(Callback* p_callback, const Descriptor* p_descriptor)
{
	m_callback = p_callback;
	memcpy(&m_descriptor, p_descriptor, sizeof(m_descriptor));
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_next = NULL;
	m_active = 1;
}

// FUNCTION: LEGORACERS 0x004408e0
void LegoEventQueue::Event::FUN_004408e0(LegoEventQueue*, CallbackData* p_data)
{
	if (m_active) {
		m_unk0x20++;
		p_data->m_unk0x0c = m_unk0x20;

		if (m_descriptor.m_unk0x04 & 2) {
			if (m_unk0x20 < m_descriptor.m_unk0x0c) {
				return;
			}

			m_unk0x20 = 0;
		}

		m_unk0x1c++;
		p_data->m_unk0x08 = m_unk0x1c;
		p_data->m_unk0x04 = m_descriptor.m_unk0x04;
		m_callback->VTable0x00(p_data);

		if (!(m_descriptor.m_unk0x04 & 1)) {
			if (m_unk0x1c >= m_descriptor.m_unk0x08) {
				m_active = 0;
			}
		}
	}
}
