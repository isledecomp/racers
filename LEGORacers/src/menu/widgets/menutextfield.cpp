#include "menu/widgets/menutextfield.h"

#include "audio/soundgroupbinding.h"
#include "golstringtable.h"
#include "input/inputeventqueue.h"
#include "menu/screens/menuscreeninterface.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuTextField, 0x23c)
DECOMP_SIZE_ASSERT(MenuTextField::CreateParams, 0xa0)
DECOMP_SIZE_ASSERT(MenuTextField::SoundIdSet, 0x8)

// FUNCTION: LEGORACERS 0x00470eb0
MenuTextField::MenuTextField()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00470f40
MenuTextField::~MenuTextField()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00470fb0
void MenuTextField::Reset()
{
	m_text.Reset();
	m_charset.Reset();
	memset(m_buffer, 0, sizeof(m_buffer));
	memset(&m_editSoundIds, 0, sizeof(m_editSoundIds));
	m_font = NULL;
	m_inputMode = 3;
	m_maxLength = 0x1f;
	m_length = 0;
	m_charsetIndex = 0;
	MenuIcon::Reset();
}

// FUNCTION: LEGORACERS 0x00471040
LegoBool32 MenuTextField::CreateField(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState)
{
	Destroy();

	m_editSoundIds.m_idPairs[0] = p_createParams->m_editSoundIds.m_idPairs[0];
	m_editSoundIds.m_idPairs[1] = p_createParams->m_editSoundIds.m_idPairs[1];
	m_font = p_createParams->m_font;
	m_stringTable = p_createParams->m_stringTable;
	m_maxLength = p_createParams->m_maxLength;

	m_text.CopyFromBufSelection(m_buffer, m_maxLength + 1);
	m_charset.CopyFromBufSelection(m_stringTable->GetStringBuffer(p_createParams->m_charsetStringId), 0);

	if (p_createParams->m_initialText) {
		m_text.GolStrcpy(p_createParams->m_initialText);
		m_length = m_text.SelectionLength();
	}

	return Create(p_createParams, p_createState);
}

// FUNCTION: LEGORACERS 0x00471100
void MenuTextField::HandleEditAction(undefined4 p_action)
{
	m_inputMode = p_action;

	if (p_action == 4) {
		if (m_length) {
			m_length--;
			m_charsetIndex = 0;

			while (m_charsetIndex < m_charset.SelectionLength()) {
				if (*m_text.FromCursor(m_length) == *m_charset.FromCursor(m_charsetIndex)) {
					m_text.FirstLine();
					return;
				}

				m_charsetIndex++;
			}
		}

		*m_text.FromCursor(m_length) = *m_charset.FromCursor(0);
		m_charsetIndex = 0;
		m_text.FirstLine();
	}
}

// FUNCTION: LEGORACERS 0x004711f0
void MenuTextField::SetText(GolString* p_string)
{
	m_text.GolStrcpy(p_string);
	m_length = m_text.SelectionLength();
}

// FUNCTION: LEGORACERS 0x00471220
void MenuTextField::Select(undefined4 p_flags)
{
	SetFocus();
	MenuIcon::Select(p_flags);
}

// FUNCTION: LEGORACERS 0x00471240
void MenuTextField::Deselect(undefined4 p_flags)
{
	ClearFocus();
	MenuIcon::Deselect(p_flags);
}

// FUNCTION: LEGORACERS 0x00471260
MenuWidget* MenuTextField::OnCursorEvent(void* p_item, undefined4 p_x, undefined4 p_y)
{
	LegoU8 flag = 8;

	if (!m_parent) {
		if (!(flag & m_flags)) {
			return NULL;
		}
	}

	if (!HitTest(p_x, p_y)) {
		return NULL;
	}

	if (flag & m_flags) {
		if (m_notifyHandler) {
			m_notifyHandler->OnWidgetKeyDown(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (!IsEnabled()) {
		return NULL;
	}

	Select(0);

	if (m_selectedChild || m_firstChild) {
		return NULL;
	}

	if (m_notifyHandler) {
		m_notifyHandler->OnWidgetKeyUp(this, p_item, p_x, p_y);
	}

	return this;
}

// STUB: LEGORACERS 0x00471300
MenuWidget* MenuTextField::DrawSelf(Rect* p_rect, Rect* p_arg)
{
	LegoS32 xOffset = p_arg->m_left - p_rect->m_left;
	LegoS32 yOffset = p_arg->m_top - p_rect->m_top;

	Rect clip;
	clip.m_left = p_arg->m_left;
	clip.m_top = p_arg->m_top;
	clip.m_right = p_arg->m_right;
	clip.m_bottom = p_arg->m_bottom - 4;

	Rect rect;
	rect.m_left = p_rect->m_left;
	rect.m_top = p_rect->m_top;
	rect.m_right = p_rect->m_right;
	rect.m_bottom = p_rect->m_bottom - 4;

	MeasureText(m_font, &m_text, &rect, &m_textRect, 0);

	m_textRect.m_right -= m_textRect.m_left;

	rect.m_left = xOffset;
	rect.m_top = m_textRect.m_top + yOffset;
	rect.m_right = m_textRect.m_right + xOffset;
	rect.m_bottom = m_textRect.m_bottom + yOffset;
	m_textRect.m_left = 0;

	DrawString(&rect, &clip, m_font, &m_text, 0, 0);

	return NULL;
}

// FUNCTION: LEGORACERS 0x004713f0
MenuWidget* MenuTextField::HandleCharacterInput(InputEventQueue::Event* p_event)
{
	if ((p_event->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceCharacter) {
		LegoU16 character = (LegoU16) p_event->m_keyCode;

		if (character == 8) {
			if (m_length != 0) {
				m_length--;
				*m_text.FromCursor(m_length) = 0;
				m_text.FirstLine();
				m_eventHandler->OnWidgetValueChanged(this);
				m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[2]);
				return this;
			}
		}
		else {
			LegoS32 charsetLength = m_charset.SelectionLength();
			LegoS32 i;
			for (i = 0; i < charsetLength; i++) {
				if (character == *m_charset.FromCursor(i)) {
					break;
				}
			}

			if (i >= charsetLength) {
				m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
				return NULL;
			}

			if (m_length != m_maxLength) {
				*m_text.FromCursor(m_length) = character;
				m_length++;
				m_text.FirstLine();
				m_eventHandler->OnWidgetValueChanged(this);
				m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[0]);
				return this;
			}
		}

		m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00471560
MenuWidget* MenuTextField::HandleJoystickInput(InputEventQueue::Event* p_event)
{
	switch (p_event->m_keyCode) {
	case InputDevice::c_sourceJoystickButton | 0x4:
		if (m_length <= m_maxLength) {
			m_length++;
			*m_text.FromCursor(m_length) = *m_charset.FromCursor(m_charsetIndex);
			m_charsetIndex = 0;
			if (m_length <= m_maxLength) {
				*m_text.FromCursor(m_length) = *m_charset.FromCursor(0);
			}
			else {
				*m_text.FromCursor(m_length) = 0;
			}

			m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[1]);
			break;
		}

		m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
		break;

	case InputDevice::c_sourceJoystickButton | 0x5:
		if (m_length != 0) {
			*m_text.FromCursor(m_length) = 0;
			m_length--;
			for (m_charsetIndex = 0; m_charsetIndex < m_charset.SelectionLength(); m_charsetIndex++) {
				if (*m_text.FromCursor(m_length) == *m_charset.FromCursor(m_charsetIndex)) {
					break;
				}
			}

			m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[2]);
			break;
		}

		m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
		return NULL;

	case InputDevice::c_sourceJoystickButton | 0x7:
	case InputDevice::c_sourceJoystickAxisButton | 0x0:
		if (m_length != m_maxLength) {
			m_charsetIndex = (m_charsetIndex + 1) % m_charset.SelectionLength();
			*m_text.FromCursor(m_length) = *m_charset.FromCursor(m_charsetIndex);
			m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[0]);
			break;
		}

		m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
		break;

	case InputDevice::c_sourceJoystickButton | 0x9:
	case InputDevice::c_sourceJoystickAxisButton | 0x1:
		if (m_length != m_maxLength) {
			LegoU16 index = m_charsetIndex;
			if (index == 0) {
				index = m_charset.SelectionLength();
			}

			index--;
			m_charsetIndex = index;
			*m_text.FromCursor(m_length) = *m_charset.FromCursor(m_charsetIndex);
			m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[0]);
			break;
		}

		m_soundGroupBinding->PlaySoundByIndex(m_editSoundIds.m_ids[3]);
		break;

	default:
		return NULL;
	}

	m_text.FirstLine();
	return this;
}

// FUNCTION: LEGORACERS 0x00471810
MenuWidget* MenuTextField::OnKeyDown(InputEventQueue::Event* p_event, undefined4, undefined4)
{
	if (m_stateFlags & c_flagSelected) {
		LegoU32 mode = m_inputMode;
		if (mode == p_event->m_device->GetDeviceType()) {
			switch (mode) {
			case 3:
				return HandleCharacterInput(p_event);
			case 4:
				return HandleJoystickInput(p_event);
			}
		}
	}

	return NULL;
}

// Keep this null-return override in the scene-widget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuTextField::OnKeyUp(InputEventQueue::Event*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()
