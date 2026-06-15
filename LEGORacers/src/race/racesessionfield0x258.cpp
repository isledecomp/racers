#include "decomp.h"
#include "race/racesession.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x258, 0x74)
DECOMP_SIZE_ASSERT(RaceSession::Field0x258::Field0x04, 0x70)

// FUNCTION: LEGORACERS 0x00430020
RaceSession::Field0x258::Field0x258()
{
	m_unk0x000 = NULL;
	m_unk0x004.m_unk0x058 = 0;
	m_unk0x004.m_unk0x068 = 0;
	m_unk0x004.m_unk0x05c = 0;
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x06c = 0;
}

// FUNCTION: LEGORACERS 0x00430050
RaceSession::Field0x258::~Field0x258()
{
	FUN_004300a0();
}

// FUNCTION: LEGORACERS 0x004300a0
void RaceSession::Field0x258::FUN_004300a0()
{
	m_unk0x004.FUN_004308a0();

	m_unk0x000 = NULL;
	m_unk0x004.m_unk0x058 = 0;
	m_unk0x004.m_unk0x068 = 0;
	m_unk0x004.m_unk0x05c = 0;
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x06c = 0;
}

// FUNCTION: LEGORACERS 0x00430100
void RaceSession::Field0x258::FUN_00430100()
{
	m_unk0x004.m_unk0x060 = 0;
	m_unk0x004.m_unk0x064 = 0;
	m_unk0x004.m_unk0x05c = (m_unk0x004.m_unk0x05c & ~2) | 1;
}

// STUB: LEGORACERS 0x00430530
void RaceSession::Field0x258::FUN_00430530(LegoU32)
{
	STUB(0x00430530);
}

// FUNCTION: LEGORACERS 0x00430570
void RaceSession::Field0x258::FUN_00430570(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 1;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~1;
	}
}

// FUNCTION: LEGORACERS 0x00430590
void RaceSession::Field0x258::FUN_00430590(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 2;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~2;
	}
}

// FUNCTION: LEGORACERS 0x004305b0
void RaceSession::Field0x258::FUN_004305b0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 4;
		FUN_00430790();
	}
	else {
		m_unk0x004.m_unk0x058 &= ~4;
		m_unk0x004.m_unk0x064 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004305e0
void RaceSession::Field0x258::FUN_004305e0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		RaceState::Racer* racer = m_unk0x000;
		if (racer->m_unk0xaa8 & 2) {
			racer->m_unk0x3e8.VTable0x28();
		}

		m_unk0x004.m_unk0x058 |= 8;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~8;
	}
}

// FUNCTION: LEGORACERS 0x00430620
void RaceSession::Field0x258::FUN_00430620(LegoBool32 p_enabled)
{
	if (!(m_unk0x004.m_unk0x05c & 3)) {
		if (p_enabled) {
			m_unk0x004.m_unk0x058 |= 0x10;
			m_unk0x000->FUN_00439100();
		}
		else {
			m_unk0x004.m_unk0x058 &= ~0x10;
		}
	}
}

// FUNCTION: LEGORACERS 0x00430650
void RaceSession::Field0x258::FUN_00430650(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a390();
		m_unk0x004.m_unk0x058 |= 0x20;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x20;
	}
}

// FUNCTION: LEGORACERS 0x00430680
void RaceSession::Field0x258::FUN_00430680(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a0c0();
		m_unk0x004.m_unk0x058 |= 0x40;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x40;
	}
}

// FUNCTION: LEGORACERS 0x004306b0
void RaceSession::Field0x258::FUN_004306b0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x004.m_unk0x058 |= 0x80;
	}
	else {
		m_unk0x004.m_unk0x058 &= ~0x80;
	}
}

// FUNCTION: LEGORACERS 0x004306d0
void RaceSession::Field0x258::FUN_004306d0(LegoBool32 p_enabled)
{
	if (p_enabled) {
		m_unk0x000->FUN_0043a3f0();
		m_unk0x004.m_unk0x058 |= 0x100;
	}
	else {
		m_unk0x000->FUN_0043a400();
		m_unk0x004.m_unk0x058 &= ~0x100;
	}
}

// FUNCTION: LEGORACERS 0x00430710
void RaceSession::Field0x258::FUN_00430710()
{
	LegoU32 flags = m_unk0x004.m_unk0x05c;
	flags &= ~1;
	m_unk0x004.m_unk0x05c = flags;

	if (m_unk0x004.m_unk0x060 > 0) {
		LegoU32 duration = m_unk0x004.m_unk0x060;
		RaceState::Racer* racer = m_unk0x000;
		if (duration >= 60) {
			racer->m_unk0x008->FUN_0045b1e0(racer, TRUE);
		}
		else {
			racer->m_unk0x008->FUN_0045b1e0(racer, FALSE);
		}
		m_unk0x004.m_unk0x060 = 0;
	}
	else if (!(flags & 8)) {
		m_unk0x004.m_unk0x060 = 100;
	}
}

// FUNCTION: LEGORACERS 0x00430760
void RaceSession::Field0x258::FUN_00430760()
{
	m_unk0x004.m_unk0x05c |= 2;
	m_unk0x000->FUN_0043a0e0();

	RaceState::Racer* racer = m_unk0x000;
	if (racer->m_unk0xd04 & 0x80) {
		racer->FUN_00439870();
	}
}

// STUB: LEGORACERS 0x00430790
void RaceSession::Field0x258::FUN_00430790()
{
	if (m_unk0x004.m_unk0x05c & 1) {
		if (m_unk0x004.m_unk0x064 > 2000) {
			m_unk0x004.m_unk0x060 = 100;
			m_unk0x004.m_unk0x064 = 0;
		}
	}
	else {
		LegoU32 duration = m_unk0x004.m_unk0x060;
		LegoU32 flags = m_unk0x004.m_unk0x05c;
		if (!(0 < duration) || (flags & 3)) {
			return;
		}

		RaceState::Racer* racer = m_unk0x000;
		if (duration >= 60) {
			racer->m_unk0x008->FUN_0045b1e0(racer, TRUE);
		}
		else {
			racer->m_unk0x008->FUN_0045b1e0(racer, FALSE);
		}

		m_unk0x000->m_unk0x018.FUN_0043df90();
		m_unk0x004.m_unk0x060 = 0;
	}
}

// FUNCTION: LEGORACERS 0x00430840
RaceSession::Field0x258::Field0x04::Field0x04()
{
	m_unk0x004 = NULL;
	m_unk0x050 = NULL;

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_unk0x008[i] = 0;
		m_unk0x02c[i] = NULL;
	}

	m_unk0x054 = 1;
}

// FUNCTION: LEGORACERS 0x00430890
RaceSession::Field0x258::Field0x04::~Field0x04()
{
	FUN_004308a0();
}

// FUNCTION: LEGORACERS 0x004308a0
void RaceSession::Field0x258::Field0x04::FUN_004308a0()
{
	FUN_00430980();

	for (LegoS32 i = 0; i < c_inputSlotCount; i++) {
		m_unk0x008[i] = 0;
		m_unk0x02c[i] = NULL;
	}

	m_unk0x004 = NULL;
	m_unk0x050 = NULL;
	m_unk0x054 = 1;
}

// FUNCTION: LEGORACERS 0x00430910
undefined4 RaceSession::Field0x258::Field0x04::FUN_00430910(InputDispatchSource** p_source, LegoU32 p_index)
{
	*p_source = m_unk0x02c[p_index];
	return m_unk0x008[p_index];
}

// FUNCTION: LEGORACERS 0x00430980
void RaceSession::Field0x258::Field0x04::FUN_00430980()
{
	InputDispatchSource** current = m_unk0x02c;
	LegoS32 remaining = c_inputSlotCount;
	do {
		InputDispatchSource* source = *current;
		if (source && source->m_unk0x98 == this) {
			source->m_unk0x98 = NULL;
			(*current)->VTable0x54();
		}
		current++;
	} while (--remaining);
}

// STUB: LEGORACERS 0x004309c0
LegoS32 RaceSession::Field0x258::Field0x04::VTable0x00(
	InputDispatchSource* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_unk0x054) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (m_unk0x008[i] == p_input && m_unk0x02c[i] == p_source) {
				switch (i) {
				case 0:
					m_unk0x004->FUN_00430570(TRUE);
					break;
				case 1:
					m_unk0x004->FUN_00430590(TRUE);
					break;
				case 2:
					m_unk0x004->FUN_004305b0(TRUE);
					break;
				case 3:
					m_unk0x004->FUN_004305e0(TRUE);
					break;
				case 4:
					m_unk0x004->FUN_00430620(TRUE);
					break;
				case 5:
					m_unk0x004->FUN_00430650(TRUE);
					break;
				case 6:
					m_unk0x004->FUN_00430680(TRUE);
					break;
				case 7:
					m_unk0x004->FUN_004306b0(TRUE);
					break;
				case 8:
					m_unk0x004->FUN_004306d0(TRUE);
					break;
				}

				return TRUE;
			}
		}
	}

	if (m_unk0x050) {
		return m_unk0x050->VTable0x00(p_source, p_input, p_time);
	}

	return FALSE;
}

// STUB: LEGORACERS 0x00430af0
LegoS32 RaceSession::Field0x258::Field0x04::VTable0x04(
	InputDispatchSource* p_source,
	undefined4 p_input,
	undefined4 p_time
)
{
	if (m_unk0x054) {
		for (LegoU32 i = 0; i < c_inputSlotCount; i++) {
			if (m_unk0x008[i] == p_input && m_unk0x02c[i] == p_source) {
				switch (i) {
				case 0:
					m_unk0x004->FUN_00430570(FALSE);
					break;
				case 1:
					m_unk0x004->FUN_00430590(FALSE);
					break;
				case 2:
					m_unk0x004->FUN_004305b0(FALSE);
					break;
				case 3:
					m_unk0x004->FUN_004305e0(FALSE);
					break;
				case 4:
					m_unk0x004->FUN_00430620(FALSE);
					break;
				case 5:
					m_unk0x004->FUN_00430650(FALSE);
					break;
				case 6:
					m_unk0x004->FUN_00430680(FALSE);
					break;
				case 7:
					m_unk0x004->FUN_004306b0(FALSE);
					break;
				case 8:
					m_unk0x004->FUN_004306d0(FALSE);
					break;
				}

				return TRUE;
			}
		}
	}

	if (m_unk0x050) {
		return m_unk0x050->VTable0x04(p_source, p_input, p_time);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00430c20
void RaceSession::Field0x258::Field0x04::FUN_00430c20()
{
	m_unk0x004->FUN_00430570(FALSE);
	m_unk0x004->FUN_00430590(FALSE);
	m_unk0x004->FUN_004305b0(FALSE);
	m_unk0x004->FUN_004305e0(FALSE);
	m_unk0x004->FUN_00430620(FALSE);
	m_unk0x004->FUN_00430650(FALSE);
	m_unk0x004->FUN_00430680(FALSE);
	m_unk0x004->FUN_004306b0(FALSE);
	m_unk0x004->FUN_004306d0(FALSE);
}

// FUNCTION: LEGORACERS 0x00430c80
LegoS32 RaceSession::InputEventSink::VTable0x08(InputDispatchSource* p_source, undefined4 p_input, undefined4 p_time)
{
	return VTable0x00(p_source, p_input, p_time);
}
