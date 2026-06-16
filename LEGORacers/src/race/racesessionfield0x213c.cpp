#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x213c, 0x0c)
DECOMP_SIZE_ASSERT(RaceSession::Field0x213c::Resource, 0x24)

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// FUNCTION: LEGORACERS 0x00464830
void RaceSession::Field0x213c::Resource::FUN_00464830(LegoU32 p_elapsedMs)
{
	LegoU32 remaining = m_unk0x18;
	if (0 < remaining) {
		if (p_elapsedMs >= remaining) {
			LegoU32 duration = m_unk0x10;
			m_unk0x18 = 0;

			if (m_unk0x1c & c_flags0x1cBit1) {
				if (duration > c_randomTableMask) {
					g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
					duration = g_unk0x004befec[g_unk0x004c6ee4] * (duration / c_randomTableMask);
				}
				else {
					g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & c_randomTableMask;
					duration = g_unk0x004befec[g_unk0x004c6ee4] % duration;
				}
			}

			FUN_00464a40(duration);
			return;
		}

		remaining -= p_elapsedMs;
		m_unk0x18 = remaining;
	}
}

// FUNCTION: LEGORACERS 0x00464a40
LegoEventQueue::Event* RaceSession::Field0x213c::Resource::FUN_00464a40(LegoU32 p_unk0x04)
{
	LegoEventQueue::Callback* callback = this;
	LegoEventQueue::Descriptor descriptor;
	descriptor.m_unk0x00 = 1;
	descriptor.m_unk0x08 = 1;
	descriptor.m_unk0x04 = 0;
	descriptor.m_unk0x0c = 0;
	descriptor.m_unk0x10 = p_unk0x04;

	return m_unk0x04 = m_unk0x0c->FUN_0042fb50(callback, &descriptor);
}

// FUNCTION: LEGORACERS 0x00464a80
RaceSession::Field0x213c::Field0x213c()
{
	m_unk0x08 = NULL;
	m_unk0x00 = 0;
	m_unk0x04 = 0;
}

// FUNCTION: LEGORACERS 0x00464a90
RaceSession::Field0x213c::~Field0x213c()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00464dd0
LegoU32 RaceSession::Field0x213c::FUN_00464dd0(LegoU32 p_elapsedMs)
{
	LegoU32 result = m_unk0x04;

	for (LegoU32 i = 0; i < result; i++) {
		m_unk0x08[i].FUN_00464830(p_elapsedMs);
		result = m_unk0x04;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00464e10
void RaceSession::Field0x213c::Destroy()
{
	if (m_unk0x08) {
		m_unk0x08->VTable0x04(3);
		m_unk0x08 = NULL;
	}

	m_unk0x00 = 0;
	m_unk0x04 = 0;
}
