#include "menu/screens/optionsscreenbase0x51ac.h"

#include "input/inputmanager.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/menutoolcontext0x4bc8.h"
#include "menu/menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(OptionsScreenBase0x51ac, 0x51ac)

// FUNCTION: LEGORACERS 0x004829a0
OptionsScreenBase0x51ac::OptionsScreenBase0x51ac()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00482be0
OptionsScreenBase0x51ac::~OptionsScreenBase0x51ac()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00482de0
void OptionsScreenBase0x51ac::Reset()
{
	m_unk0x368 = FALSE;
	m_unk0x369 = FALSE;
	m_unk0x36c = 0;
	m_unk0x370 = NULL;
	ImaginaryTool0x368::Reset();
}

// STUB: LEGORACERS 0x00482e00
void OptionsScreenBase0x51ac::FUN_00482e00()
{
	STUB(0x00482e00);
}

// STUB: LEGORACERS 0x00482e40
void OptionsScreenBase0x51ac::FUN_00482e40()
{
	STUB(0x00482e40);
}

// STUB: LEGORACERS 0x00482ef0
void OptionsScreenBase0x51ac::FUN_00482ef0()
{
	STUB(0x00482ef0);
}

// STUB: LEGORACERS 0x00483030
void OptionsScreenBase0x51ac::FUN_00483030()
{
	STUB(0x00483030);
}

// FUNCTION: LEGORACERS 0x004831a0
void OptionsScreenBase0x51ac::VTable0x4c()
{
	FUN_00482e00();
	FUN_00482e40();
	FUN_00482ef0();
	FUN_00483030();
	VTable0x9c();
}

// FUNCTION: LEGORACERS 0x004831d0
LegoBool32 OptionsScreenBase0x51ac::VTable0x8c(
	MenuToolContext0x4bc8* p_context,
	MenuToolCreateParams0x30* p_createParams
)
{
	m_unk0x370 = &p_context->m_unk0x258.GetUnk0x18c4();

	if (!ImaginaryTool0x368::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	if (!FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00483220
void OptionsScreenBase0x51ac::VTable0x84()
{
	switch (m_unk0x360) {
	case 2:
		m_context->m_menuStack.Pop();
		m_context->m_menuStack.Push(0x30);
		break;
	case 0x0a:
	case 0x0b:
	case 0x27:
	case 0x2c:
		m_context->m_menuStack.Push(m_unk0x360);
		// intentional fallthrough
	default:
		m_context->m_menuStack.Push(0x30);
		break;
	}
}

// FUNCTION: LEGORACERS 0x004832d0
void OptionsScreenBase0x51ac::VTable0x38(ObscureVantage0x58* p_widget)
{
	if (p_widget == &m_unk0x448) {
		m_unk0x369 = 1;
	}
	else if (p_widget == &m_unk0x738) {
		FUN_0047fdc0(&m_unk0x15e8, 0x99, 0x46, 0x72);
		FUN_0046c730(&m_unk0x15e8, 0xbd);
	}
	else if (p_widget == &m_unk0xa28) {
		m_unk0x360 = 0x0a;
	}
	else if (p_widget == &m_unk0xd18) {
		m_unk0x360 = 0x0b;
	}
	else if (p_widget == &m_unk0x12f8) {
		m_unk0x360 = 0x2c;
	}
	else if (p_widget == &m_unk0x1008) {
		m_unk0x360 = 0x27;
	}
	else if (p_widget == &m_unk0x18d8) {
		if (m_unk0x368 == 0) {
			m_unk0x360 = 2;
		}
		else {
			m_unk0x369 = 0;
		}
	}
	else if (p_widget == &m_unk0x15e8) {
		m_unk0x369 = 2;
		m_unk0x284->FUN_00468cf0();
	}

	if (m_unk0x360 != 0xffff) {
		m_unk0x364 = TRUE;
	}

	m_unk0x35c = p_widget;
}

// STUB: LEGORACERS 0x004833e0
void OptionsScreenBase0x51ac::VTable0x44(ObscureVantage0x58*)
{
	STUB(0x004833e0);
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void OptionsScreenBase0x51ac::VTable0x98()
{
}

// STUB: LEGORACERS 0x004835a0
void OptionsScreenBase0x51ac::VTable0x9c()
{
	STUB(0x004835a0);
}

// STUB: LEGORACERS 0x00483640
void OptionsScreenBase0x51ac::VTable0xa0()
{
	STUB(0x00483640);
}

// STUB: LEGORACERS 0x00483850
void OptionsScreenBase0x51ac::VTable0xa4()
{
	STUB(0x00483850);
}

// FUNCTION: LEGORACERS 0x004838e0
LegoBool32 OptionsScreenBase0x51ac::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x369 != m_unk0x368 && !(m_unk0x35c->GetUnk0x54() & 1)) {
		VTable0xa4();
	}

	if (m_unk0x368 == 0) {
		if (m_inputManager->GetJoystickCount() <= 1 && !m_inputManager->IsKeyboardAvailable()) {
			m_unk0xd18.VTable0x48(5);
			return ImaginaryTool0x368::VTable0x78(p_elapsed);
		}

		m_unk0xd18.VTable0x44(5);
	}

	return ImaginaryTool0x368::VTable0x78(p_elapsed);
}
