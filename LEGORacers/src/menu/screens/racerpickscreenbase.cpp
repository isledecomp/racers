#include "menu/screens/racerpickscreenbase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerPickScreenBase, 0x3ff4)

// FUNCTION: LEGORACERS 0x00488ce0
RacerPickScreenBase::RacerPickScreenBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00488df0
RacerPickScreenBase::~RacerPickScreenBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00488eb0
void RacerPickScreenBase::Reset()
{
	::memset(m_unk0x2b4c, 0, sizeof(m_unk0x2b4c));
	RacerModelScreenBase::Reset();
}

// FUNCTION: LEGORACERS 0x00488ed0
void RacerPickScreenBase::VTable0x4c()
{
	RacerModelScreenBase::VTable0x4c();

	LegoS32 i;

	for (i = 0; i < m_unk0x26fc; i++) {
		CreateCarousel(&m_unk0x270c[i], 0x3d, 0x3b);
		CreateSelector(&m_unk0x2c0c[i], &m_unk0x270c[i], i + 0x70, 0x4c);
	}

	for (i = 0; i < m_unk0x26fc; i++) {
		LegoS32 j;

		for (j = 0; j < 3; j++) {
			CreateTextLabel(&m_unk0x2834[i * 3 + j], 0x96, 0x37, i + 2);
		}
	}
}

// FUNCTION: LEGORACERS 0x00488f80
LegoBool32 RacerPickScreenBase::VTable0xa0(
	MenuGameContext* p_context,
	MenuScreenCreateParams* p_createParams,
	undefined4* p_params
)
{
	if (!RacerModelScreenBase::VTable0xa0(p_context, p_createParams, p_params)) {
		return FALSE;
	}

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		for (LegoS32 j = 0; j < 3; j++) {
			m_unk0x2b04[i * 3 + j].CopyFromBufSelection(m_unk0x2b4c[i * 3 + j], sizeOfArray(m_unk0x2b4c[i * 3 + j]));
		}

		if (m_unk0x2704[i]) {
			FUN_004890c0(i);
			VTable0x44(&m_unk0x2c0c[i]);
		}
	}

	return m_initialized;
}

// FUNCTION: LEGORACERS 0x00489050
void RacerPickScreenBase::FUN_00489050(LegoS32 p_index)
{
	RacerUnlockState* modelState = &m_unk0x22dc[p_index];
	modelState->FUN_00443050();
	modelState->FUN_00443050();

	for (LegoS32 i = 0; i < 3; i++) {
		LegoS32 widgetIndex = p_index * 3 + i;
		modelState->FUN_00442fe0()->GetName(&m_unk0x2b04[widgetIndex]);
		m_unk0x2834[widgetIndex].VTable0x40(&m_unk0x2b04[widgetIndex], 0);
	}

	modelState->FUN_00443050();
}

// FUNCTION: LEGORACERS 0x004890c0
void RacerPickScreenBase::FUN_004890c0(LegoS32 p_index)
{
	MenuCarouselNavigator* carousel = &m_unk0x270c[p_index];

	carousel->FUN_0046da60();

	if (m_unk0x2704[p_index] && m_initialized) {
		FUN_00489050(p_index);

		for (LegoS32 i = 0; i < 3; i++) {
			carousel->FUN_0046d9c0(&m_unk0x2834[p_index * 3 + i]);
		}

		carousel->VTable0x50(1);
	}
}

// FUNCTION: LEGORACERS 0x00489130
void RacerPickScreenBase::VTable0x44(MenuWidget* p_source)
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
void RacerPickScreenBase::VTable0x10(MenuWidget* p_source)
{
	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		if (&m_unk0x270c[i] == p_source) {
			FUN_004890c0(0);
		}
	}
}

// FUNCTION: LEGORACERS 0x004891f0
void RacerPickScreenBase::FUN_004891f0(LegoS32 p_index)
{
	if (p_index > 0) {
		m_unk0x2c0c[p_index].SetFlags(2);
		return;
	}

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		m_unk0x2c0c[i].SetFlags(2);
	}
}

// STUB: LEGORACERS 0x00489250
void RacerPickScreenBase::FUN_00489250(LegoS32 p_index)
{
	if (p_index > 0) {
		m_unk0x2c0c[p_index].VTable0x44(5);
		m_unk0x2c0c[p_index].SetUnk0x9ec(m_unk0x2704[p_index] != 0);
		return;
	}

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		m_unk0x2c0c[i].VTable0x44(5);
		m_unk0x2c0c[i].SetUnk0x9ec(m_unk0x2704[i] != 0);
	}
}

// STUB: LEGORACERS 0x00489320
void RacerPickScreenBase::FUN_00489320(LegoS32 p_index)
{
	if (p_index > 0) {
		m_unk0x2c0c[p_index].VTable0x48(5);
		m_unk0x2c0c[p_index].SetUnk0x9ec(m_unk0x2704[p_index] != 0);
		return;
	}

	for (LegoS32 i = 0; i < m_unk0x26fc; i++) {
		m_unk0x2c0c[i].VTable0x48(5);
		m_unk0x2c0c[i].SetUnk0x9ec(m_unk0x2704[i] != 0);
	}
}
