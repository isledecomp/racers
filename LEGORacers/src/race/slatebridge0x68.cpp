#include "race/slatebridge0x68.h"

#include "golfontbase.h"
#include "golstringtable.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"

DECOMP_SIZE_ASSERT(SlateBridge0x68, 0x68)

// FUNCTION: LEGORACERS 0x00427160
SlateBridge0x68::SlateBridge0x68()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004271d0
SlateBridge0x68::~SlateBridge0x68()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00427240
void SlateBridge0x68::Destroy()
{
	for (LegoS32 i = 0; i < sizeOfArray(m_options); i++) {
		m_options[i].Reset();
	}

	m_prompt.Reset();
	m_extra.Reset();
	Reset();
}

// FUNCTION: LEGORACERS 0x00427290
void SlateBridge0x68::Reset()
{
	m_unk0x58 = 1;
	m_font = NULL;
	m_renderer = NULL;
	m_stringTable = NULL;
	m_unk0x48 = 0;
	m_unk0x50 = 0;
	m_unk0x54 = 0;
	m_unk0x5c = 0;
	m_unk0x60 = 0;
	m_unk0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00427310
void SlateBridge0x68::FUN_00427310(
	LegoU32 p_optionCount,
	const LegoU16* p_optionStringIds,
	LegoU16 p_promptStringId,
	LegoU16 p_extraStringId,
	LegoU32 p_selectionIndex
)
{
	LegoS32 textHeight;
	const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	LegoS32 textWidth;
	LegoU32 i;

	for (i = 0; i < p_optionCount; i++) {
		m_options[i].CopyFromBufSelection(m_stringTable->GetStringBuffer(p_optionStringIds[i]), 0);
	}

	m_prompt.CopyFromBufSelection(m_stringTable->GetStringBuffer(p_promptStringId), 0);

	if (p_extraStringId != 0xffff) {
		m_extra.CopyFromBufSelection(m_stringTable->GetStringBuffer(p_extraStringId), 0);
	}
	else {
		m_extra.Reset();
	}

	m_unk0x4c = p_optionCount;
	m_unk0x48 = 1;
	m_unk0x50 = p_selectionIndex;
	m_unk0x58 = 1;
	m_unk0x60 = 0;

	i = 0;
	if (p_optionCount > i) {
		GolString* option = m_options;
		do {
			m_font->MeasureString(option, &textWidth, &textHeight);

			if (static_cast<LegoU32>(textHeight) > static_cast<LegoU32>(m_unk0x60)) {
				m_unk0x60 = textHeight;
			}

			i++;
			option++;
		} while (i < m_unk0x4c);
	}

	m_unk0x60 += 2;
	m_unk0x5c = renderTargetInfo->GetHeight() / 2 - (m_unk0x4c * m_unk0x60) / 2;
}

// FUNCTION: LEGORACERS 0x00427420
void SlateBridge0x68::FUN_00427420(LegoU32 p_elapsedMs)
{
	m_unk0x54 += p_elapsedMs;
	if (m_unk0x54 >= 500) {
		m_unk0x54 = 0;
	}
}

// STUB: LEGORACERS 0x00427440
void SlateBridge0x68::FUN_00427440()
{
	STUB(0x00427440);
}

// FUNCTION: LEGORACERS 0x00427810
void SlateBridge0x68::FUN_00427810(LegoU32 p_keyCode)
{
	LegoU32 keyCode;
	LegoU32 selectionIndex;

	if (m_unk0x48 != 1) {
		return;
	}

	if (!m_unk0x58) {
		return;
	}

	keyCode = p_keyCode;

	switch (keyCode) {
	case c_keyboardEnter:
	case c_keyboardSpace:
	case c_joystickButton13:
	case c_joystickButton14:
	case c_joystickButton15:
		m_unk0x58 = 0;
		break;
	case c_keyboardPrevious:
	case c_joystickButton4:
	case c_joystickButton11:
	case c_joystickAxisNegative:
		selectionIndex = m_unk0x50;
		if (!selectionIndex) {
			selectionIndex = m_unk0x4c;
		}
		selectionIndex--;
		m_unk0x50 = selectionIndex;
		break;
	case c_keyboardNext:
	case c_joystickButton6:
	case c_joystickButton10:
	case c_joystickAxisPositive:
		selectionIndex = m_unk0x50;
		selectionIndex++;
		if (selectionIndex == m_unk0x4c) {
			selectionIndex = 0;
		}
		m_unk0x50 = selectionIndex;
		break;
	}

	if (keyCode == m_unk0x64) {
		m_unk0x58 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004278c0
void SlateBridge0x68::FUN_004278c0(LegoU32 p_keyCode)
{
	if (p_keyCode == c_keyboardEnter || p_keyCode == c_keyboardSpace || p_keyCode == c_joystickButton13 ||
		p_keyCode == c_joystickButton15 || p_keyCode == c_joystickButton14 || p_keyCode == m_unk0x64) {
		if (!m_unk0x58) {
			m_unk0x48 = 2;
		}
	}
}
