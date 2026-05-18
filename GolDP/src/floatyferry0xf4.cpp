#include "floatyferry0xf4.h"

#include "float.h"

DECOMP_SIZE_ASSERT(FloatyFerry0xf4, 0xf4)

// GLOBAL: 0x10056fc4
static const LegoFloat g_fltMax0x10056fc4 = FLT_MAX;

// FUNCTION: GOLDP 0x10023420
FloatyFerry0xf4::FloatyFerry0xf4()
{
	LegoU32 i;

	for (i = 0; i < 3; i++) {
		m_unk0x90[i] = 0;
		m_unk0xa8[i] = NULL;
		m_unk0x9c[i] = -1;
	}
	m_unk0xbc = 0;
	m_v1.m_x = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}

// FUNCTION: GOLDP 0x10023490
void FloatyFerry0xf4::FUN_10023490(undefined4* p_arg1, undefined4 p_arg2, undefined4* p_arg3, LegoFloat p_arg4)
{
	FloatyCanoe0x90::VTable0x50(p_arg1, p_arg4);
	m_unk0x90[0] = p_arg2;
	m_unk0xa8[0] = p_arg3;
}

// FUNCTION: GOLDP 0x100234c0
void FloatyFerry0xf4::FUN_100234c0(undefined4 p_arg1, undefined4* p_arg2, LegoFloat p_arg3)
{
	m_unk0x84[0] = p_arg3;
	m_v1.m_x = 0.0f;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x58 = 1.0f;
	m_unk0x90[0] = p_arg1;
	m_unk0xa8[0] = p_arg2;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10023510
void FloatyFerry0xf4::VTable0x54()
{
	LegoU32 i;

	FloatyCanoe0x90::VTable0x54();

	for (i = 0; i < 3; i++) {
		m_unk0x90[i] = 0;
		m_unk0xa8[i] = NULL;
		m_unk0x9c[i] = -1;
	}
	m_unk0xbc = 0;
	m_v1.m_x = -1.0f;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xd8 = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xec = 0;
	m_unk0xf0 = 0;
}

// STUB: GOLDP 0x10023580
void FloatyFerry0xf4::VTable0x5c(undefined4)
{
	// TODO
	STUB(0x10023580);
}

// STUB: GOLDP 0x10023940
void FloatyFerry0xf4::FUN_10023940(undefined4*, undefined4, undefined4, LegoFloat)
{
	// TODO
	STUB(0x10023940);
}

// FUNCTION: GOLDP 0x100239e0
void FloatyFerry0xf4::FUN_100239e0(undefined4 p_arg1, undefined4* p_arg2, LegoFloat p_arg3)
{
	LegoU32 i;

	for (i = 0; i < 2; i++) {
		if (m_unk0x90[i] == 0) {
			break;
		}
		if (p_arg3 < m_unk0x84[i]) {
			LegoU32 j;
			for (j = 2; j > i; j--) {
				m_unk0x90[j] = m_unk0x90[j - 1];
				m_unk0xa8[j] = m_unk0xa8[j - 1];
				m_unk0x84[j] = m_unk0x84[j - 1];
			}
			break;
		}
	}
	m_unk0x90[i] = p_arg1;
	m_unk0x9c[i] = -1;
	m_unk0xa8[i] = p_arg2;
	m_unk0x84[i] = p_arg3;
}

// STUB: GOLDP 0x10023a70
void FloatyFerry0xf4::FUN_10023a70(undefined2)
{
	// TODO
	STUB(0x10023a70);
}

// STUB: GOLDP 0x10023b10
void FloatyFerry0xf4::VTable0x10(LegoS32 p_v)
{
	// TODO
	STUB(0x10023b10);
}

// STUB: GOLDP 0x10023ef0
void FloatyFerry0xf4::VTable0x4c(LegoU32 p_index)
{
	// TODO
	STUB(0x10023ef0);
}

// STUB: GOLDP 0x100240b0
void FloatyFerry0xf4::VTable0x14(const GolVec3& p_vector, ResultStruct* p_result)
{
#if 0
	LegoU32 i;

	GolVec3 vec3;
	FUN_100286d0(&vec3);
	if (m_unk0x84[0] != g_fltMax0x10056fc4) {
		LegoFloat d = GOLVECTOR3_DISTANCE_SQUARED(p_vector, vec3);
		while (m_unk0x84[i] < d) {
			i++;
			if (i > 2) {
				p_result->m_unk0x00 = 0;
				return;
			}
		}
	}
	p_result->m_unk0x04 = i;
	if (m_unk0x78[i] == NULL) {
		p_result->m_unk0x00 = 0;
	} else {
		if (i != 0) {
			VTable0x4c(i);
			FUN_100286d0(&vec3);
		}
		p_result->m_unk0x00 = p_vector.FUN_1002bc20(vec3, FUN_10028710());
	}
#else
	// TODO
	STUB(0x100240b0);
#endif
}

// FUNCTION: GOLDP 0x100241a0
undefined4 FloatyFerry0xf4::VTable0x58(LegoU32 p_arg1)
{
	return m_unk0x90[p_arg1];
}
