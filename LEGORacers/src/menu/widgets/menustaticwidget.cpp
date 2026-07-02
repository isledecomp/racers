#include "menu/widgets/menustaticwidget.h"

#include "input/inputdevice.h"

DECOMP_SIZE_ASSERT(MenuStaticWidget, 0x58)

// FUNCTION: LEGORACERS 0x0046e9e0
MenuStaticWidget::MenuStaticWidget()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ea50
MenuStaticWidget::~MenuStaticWidget()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046eaa0
MenuWidget* MenuStaticWidget::OnCursorEvent(void* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_flags & 8) {
		if (m_eventHandler) {
			m_eventHandler->VTable0x28(this, p_item, p_x, p_y);
		}

		return this;
	}

	if (m_eventHandler) {
		m_eventHandler->VTable0x14(this, p_item, p_x, p_y);
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046eaf0
MenuWidget* MenuStaticWidget::OnKeyDown(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if ((p_item->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse && !HitTest(p_x, p_y)) {
		return NULL;
	}

	if (m_eventHandler && m_eventHandler->VTable0x18(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046eb50
MenuWidget* MenuStaticWidget::OnKeyUp(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if ((p_item->m_keyCode & InputDevice::c_sourceMask) == InputDevice::c_sourceMouse && !HitTest(p_x, p_y)) {
		return NULL;
	}

	if (m_eventHandler && m_eventHandler->VTable0x1c(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}
