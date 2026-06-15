#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x23c, 0x1c)

// STUB: LEGORACERS 0x00427900
RaceSession::Field0x23c::Field0x23c()
{
	m_unk0x04 = NULL;
	m_unk0x08[0] = NULL;
	m_unk0x08[1] = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = 1;
}

// FUNCTION: LEGORACERS 0x00427950
RaceSession::Field0x23c::~Field0x23c()
{
	FUN_00427960();
}

// STUB: LEGORACERS 0x00427960
void RaceSession::Field0x23c::FUN_00427960()
{
	m_unk0x04 = NULL;
	m_unk0x08[0] = NULL;
	m_unk0x08[1] = NULL;
	m_unk0x10 = 0;
	m_unk0x14 = NULL;
	m_unk0x18 = 1;
}

// FUNCTION: LEGORACERS 0x00427980
void RaceSession::Field0x23c::FUN_00427980(InputDispatchSource* p_source, InputEventSink* p_fallback)
{
	m_unk0x04 = p_source;
	m_unk0x14 = p_fallback;
	m_unk0x18 = 1;
}

// FUNCTION: LEGORACERS 0x004279a0
void RaceSession::Field0x23c::FUN_004279a0(Field0x258::Field0x04* p_sink)
{
	m_unk0x08[m_unk0x10] = p_sink;
	m_unk0x10++;
}

// FUNCTION: LEGORACERS 0x004279c0
void RaceSession::Field0x23c::FUN_004279c0()
{
	m_unk0x04->m_unk0x98 = this;
	if (!m_unk0x04->VTable0x18()) {
		m_unk0x04->VTable0x50();
	}
}

// FUNCTION: LEGORACERS 0x004279f0
void RaceSession::Field0x23c::FUN_004279f0()
{
	m_unk0x04->VTable0x54();
}

// FUNCTION: LEGORACERS 0x00427a00
LegoS32 RaceSession::Field0x23c::VTable0x00(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time)
{
	if (m_unk0x18) {
		LegoU32 i = 0;
		if (i < m_unk0x10) {
			do {
				for (LegoU32 j = 0; j < Field0x258::c_inputSlotCount; j++) {
					InputDispatchSource* source;
					if (m_unk0x08[i]->FUN_00430910(&source, j) != p_input || source != m_unk0x04) {
						continue;
					}

					return m_unk0x08[i]->VTable0x00(p_source, p_input, p_time);
				}

				i++;
			} while (i < m_unk0x10);
		}
	}

	if (m_unk0x14) {
		return m_unk0x14->VTable0x00(p_source, p_input, p_time);
	}

	return FALSE;
}

// STUB: LEGORACERS 0x00427aa0
LegoS32 RaceSession::Field0x23c::VTable0x04(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time)
{
	if (m_unk0x18) {
		LegoU32 i = 0;
		if (i < m_unk0x10) {
			do {
				for (LegoU32 j = 0; j < Field0x258::c_inputSlotCount; j++) {
					InputDispatchSource* source;
					if (m_unk0x08[i]->FUN_00430910(&source, j) != p_input || source != m_unk0x04) {
						continue;
					}

					return m_unk0x08[i]->VTable0x04(p_source, p_input, p_time);
				}

				i++;
			} while (i < m_unk0x10);
		}
	}

	if (m_unk0x14) {
		return m_unk0x14->VTable0x04(p_source, p_input, p_time);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00427b40
void RaceSession::Field0x23c::FUN_00427b40()
{
	LegoU32 i = 0;
	if (m_unk0x10 > 0) {
		Field0x258::Field0x04** current = m_unk0x08;

		do {
			(*current)->FUN_00430c20();
			i++;
			current++;
		} while (i < m_unk0x10);
	}
}
