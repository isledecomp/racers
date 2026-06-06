#include "menu/screens/racerpickscreenbase0x3ff4.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickScreenBase0x3ff4, 0x3ff4)

// FUNCTION: LEGORACERS 0x00488ce0
RacerPickScreenBase0x3ff4::RacerPickScreenBase0x3ff4()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00488df0
RacerPickScreenBase0x3ff4::~RacerPickScreenBase0x3ff4()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00488eb0
void RacerPickScreenBase0x3ff4::Reset()
{
	::memset(m_unk0x2b4c, 0, sizeof(m_unk0x2b4c));
	RacerPickScreenBase0x270c::Reset();
}

// FUNCTION: LEGORACERS 0x00488ed0
void RacerPickScreenBase0x3ff4::VTable0x4c()
{
	RacerPickScreenBase0x270c::VTable0x4c();

	LegoS32 i;

	for (i = 0; i < m_unk0x26fc; i++) {
		FUN_0046c240(&m_unk0x270c[i], 0x3d, 0x3b);
		FUN_0046c2b0(&m_unk0x2c0c[i], &m_unk0x270c[i], i + 0x70, 0x4c);
	}

	for (i = 0; i < m_unk0x26fc; i++) {
		LegoS32 j;

		for (j = 0; j < 3; j++) {
			FUN_0046bf80(&m_unk0x2834[i * 3 + j], 0x96, 0x37, i + 2);
		}
	}
}

// STUB: LEGORACERS 0x00488f80
LegoBool32 RacerPickScreenBase0x3ff4::VTable0xa0(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*, undefined4*)
{
	STUB(0x00488f80);
	return FALSE;
}

// STUB: LEGORACERS 0x004890c0
void RacerPickScreenBase0x3ff4::FUN_004890c0(undefined4)
{
	STUB(0x004890c0);
}

// FUNCTION: LEGORACERS 0x00489130
void RacerPickScreenBase0x3ff4::VTable0x44(ObscureVantage0x58* p_source)
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (&m_unk0x2c0c[i] == p_source) {
			undefined4 state = m_unk0x2c0c[i].GetUnk0x5e4();

			if (state != -1) {
				if (state != 1) {
					FUN_00486400(i);
				}
				else {
					FUN_004864a0(i);
				}
			}
			else {
				FUN_004864f0(i);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004891a0
void RacerPickScreenBase0x3ff4::VTable0x10(ObscureVantage0x58* p_source)
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (&m_unk0x270c[i] == p_source) {
			FUN_004890c0(0);
		}
	}
}
