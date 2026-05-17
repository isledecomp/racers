#include "floatyfrigate0x9c.h"

#include "whitefalcon0x140.h"

DECOMP_SIZE_ASSERT(FloatyFrigate0x9c, 0x9c)

// FUNCTION: GOLDP 0x1001ac70
FloatyFrigate0x9c::FloatyFrigate0x9c()
{
	m_unk0x90[0] = 0;
	m_unk0x90[1] = 0;
	m_unk0x90[2] = 0;
}

// FUNCTION: GOLDP 0x1001aca0
void FloatyFrigate0x9c::VTable0x60(undefined4* p_arg1, undefined4 p_arg2, LegoFloat p_arg3)
{
	FloatyCanoe0x90::VTable0x50(p_arg1, p_arg3);
	m_unk0x90[0] = p_arg2;
}

// FUNCTION: GOLDP 0x1001acd0
void FloatyFrigate0x9c::VTable0x54()
{
	m_unk0x90[0] = 0;
	m_unk0x90[1] = 0;
	m_unk0x90[2] = 0;
	FloatyCanoe0x90::VTable0x54();
}

// FUNCTION: GOLDP 0x1001acf0
void FloatyFrigate0x9c::FUN_1001acf0(undefined4* p_arg1, undefined4 p_arg2, LegoFloat p_arg3)
{
	LegoU32 i;

	for (i = 0; i < 2; i++) {
		if (m_unk0x78[i] == 0) {
			break;
		}
		if (p_arg3 < m_unk0x84[i]) {
			LegoU32 j;
			for (j = 2; j > i; j--) {
				m_unk0x78[j] = m_unk0x78[j - 1];
				m_unk0x90[j] = m_unk0x90[j - 1];
				m_unk0x84[j] = m_unk0x84[j - 1];
			}
			break;
		}
	}
	m_unk0x78[i] = p_arg1;
	m_unk0x90[i] = p_arg2;
	m_unk0x84[i] = p_arg3;
}

// FUNCTION: GOLDP 0x1001ad70
void FloatyFrigate0x9c::VTable0x1c(WhiteFalcon0x140& p_renderer)
{
	p_renderer.VTable0x90(this);
}
