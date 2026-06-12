#include "menu/screens/optionsscreenbase.h"

#include "audio/musicinstance.h"
#include "audio/soundmanager.h"
#include "input/inputmanager.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuscreencreateparams.h"
#include "save/savegame.h"

DECOMP_SIZE_ASSERT(OptionsScreenBase, 0x51ac)

extern LegoFloat g_unk0x4b05d8;

// FUNCTION: LEGORACERS 0x004829a0
OptionsScreenBase::OptionsScreenBase()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00482be0
OptionsScreenBase::~OptionsScreenBase()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00482de0
void OptionsScreenBase::Reset()
{
	m_unk0x368 = FALSE;
	m_unk0x369 = FALSE;
	m_unk0x36c = 0;
	m_unk0x370 = NULL;
	MenuGameScreen::Reset();
}

// FUNCTION: LEGORACERS 0x00482e00
void OptionsScreenBase::FUN_00482e00()
{
	CreateImage(&m_unk0x374, 0x49, 0x49);
	CreateTextLabel(&m_unk0x3d0, 0x3a, 0x3a, 0x10);
	m_unk0x3d0.FUN_0046f6b0(20);
}

// FUNCTION: LEGORACERS 0x00482e40
void OptionsScreenBase::FUN_00482e40()
{
	FUN_0047fdc0(&m_unk0x448, 0xed, 0x42, 0x11);
	VTable0x98();
	FUN_0047fdc0(&m_unk0x738, 0xef, 0x42, 0x13);
	FUN_0047fdc0(&m_unk0xa28, 0xf0, 0x42, 0x17);
	FUN_0047fdc0(&m_unk0xd18, 0xf1, 0x42, 0x18);
	FUN_0047fdc0(&m_unk0x12f8, 0xf2, 0x42, 0x9c);
	FUN_0047fdc0(&m_unk0x1008, 0x27, 0x42, 0x58);
	FUN_0047fdc0(&m_unk0x18d8, 0x3f, 0x43, 2);
}

// FUNCTION: LEGORACERS 0x00482ef0
void OptionsScreenBase::FUN_00482ef0()
{
	CreateCarousel(&m_unk0x2fb0, 0x3d, 0x3b);
	CreateCarousel(&m_unk0x3044, 0x3d, 0x3b);
	CreateSelector(&m_unk0x1bc8, &m_unk0x2fb0, 0xf3, 0x4c);
	CreateSelector(&m_unk0x25bc, &m_unk0x3044, 0xf4, 0x4c);
	CreateTextLabel(&m_unk0x3600[0], 0x100, 0x37, 0x59);
	CreateTextLabel(&m_unk0x3600[1], 0x101, 0x37, 0x5a);

	LegoS32 i;
	for (i = 0; i < 6; i++) {
		CreateTextLabel(&m_unk0x30d8[i], 0x96, 0x37, static_cast<undefined2>(i + 0x60));
		m_unk0x2fb0.FUN_0046d9c0(&m_unk0x30d8[i]);
	}

	m_unk0x2fb0.VTable0x50(m_unk0x370->GetRacerCount());
	VTable0x44(&m_unk0x1bc8);

	for (i = 0; i < 5; i++) {
		CreateTextLabel(&m_unk0x33a8[i], 0x96, 0x37, static_cast<undefined2>(i + 0x61));
		m_unk0x3044.FUN_0046d9c0(&m_unk0x33a8[i]);
	}

	m_unk0x3044.VTable0x50(m_unk0x370->GetUnk0x23() - 1);
	VTable0x44(&m_unk0x25bc);
	FUN_00483730();
}

// FUNCTION: LEGORACERS 0x00483030
void OptionsScreenBase::FUN_00483030()
{
	CreateOptionsRow(&m_unk0x4178, 0xf9, 0xec);
	CreateOptionsRow(&m_unk0x4864, 0xfa, 0xec);
	CreateCarousel(&m_unk0x40e4, 0xfb, 0x3b);
	CreateSelector(&m_unk0x36f0, &m_unk0x40e4, 0xfc, 0x4c);

	m_unk0x4178.VTable0x90(static_cast<LegoS32>(m_unk0x370->GetMusicVolume() * g_unk0x4b05d8 * 20.0f + 0.5f));
	m_unk0x4864.VTable0x90(static_cast<LegoS32>(m_unk0x370->GetSoundVolume() * g_unk0x4b05d8 * 20.0f + 0.5f));
	VTable0x44(&m_unk0x4178);
	VTable0x44(&m_unk0x4864);

	for (LegoS32 i = 0; i < 3; i++) {
		CreateTextLabel(&m_unk0x5040[i], static_cast<undefined2>(i + 0x104), 0x37, static_cast<undefined2>(i + 0x5d));
	}

	CreateTextLabel(&m_unk0x4f50, 0x107, 0x37, 0xa7);
	CreateTextLabel(&m_unk0x4fc8, 0x107, 0x37, 0xa8);
	m_unk0x40e4.FUN_0046d9c0(&m_unk0x4f50);
	m_unk0x40e4.FUN_0046d9c0(&m_unk0x4fc8);
	VTable0x44(&m_unk0x36f0);
	FUN_00483800();
}

// FUNCTION: LEGORACERS 0x004831a0
void OptionsScreenBase::VTable0x4c()
{
	FUN_00482e00();
	FUN_00482e40();
	FUN_00482ef0();
	FUN_00483030();
	VTable0x9c();
}

// FUNCTION: LEGORACERS 0x004831d0
LegoBool32 OptionsScreenBase::VTable0x8c(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams)
{
	m_unk0x370 = &p_context->m_saveSystem.GetGameState();

	if (!MenuGameScreen::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	if (!FUN_00480440(p_context)) {
		FUN_00480470(p_context, 0, TRUE);
	}

	return TRUE;
}

// FUNCTION: LEGORACERS 0x00483220
void OptionsScreenBase::VTable0x84()
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
void OptionsScreenBase::VTable0x38(MenuWidget* p_widget)
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

// FUNCTION: LEGORACERS 0x004833e0
void OptionsScreenBase::VTable0x44(MenuWidget* p_widget)
{
	if (p_widget == &m_unk0x4178) {
		LegoFloat volume = m_unk0x4178.GetUnk0x6c0() * 0.05f;
		m_unk0x370->SetMusicVolume(static_cast<LegoU8>(volume * 255.0f));

		if (m_context->m_context->m_soundManager) {
			m_context->m_context->m_soundManager->SetMusicVolumeScale(1.0f);

			MusicInstance* musicInstance = m_context->m_modelBuilder.GetMusicInstance();
			if (musicInstance) {
				musicInstance->SetVolume(volume);
			}

			m_context->m_context->m_soundManager->SetMusicVolumeScale(volume);
		}
	}
	else if (p_widget == &m_unk0x4864) {
		LegoFloat volume = m_unk0x4864.GetUnk0x6c0() * 0.05f;
		m_unk0x370->SetSoundVolume(static_cast<LegoU8>(volume * 255.0f));

		SoundManager* soundManager = m_context->m_context->m_soundManager;
		if (soundManager) {
			soundManager->SetVolumeScale(volume);
		}
	}
	else if (p_widget == &m_unk0x1bc8) {
		m_context->m_context->m_unk0x100 = m_unk0x2fb0.GetUnk0x6c();
		m_unk0x370->SetRacerCount(m_context->m_context->m_unk0x100);
	}
	else if (p_widget == &m_unk0x25bc) {
		m_context->m_context->m_unk0x2c = static_cast<LegoU8>(m_unk0x3044.GetUnk0x6c() + 1);
		m_unk0x370->SetUnk0x23(m_context->m_context->m_unk0x2c);
	}
	else if (p_widget == &m_unk0x36f0) {
		m_unk0x370->SetUnk0x21(m_unk0x40e4.GetUnk0x6c() == 0);

		SoundManager* soundManager = m_context->m_context->m_soundManager;
		if (soundManager) {
			if (m_unk0x370->GetUnk0x21()) {
				soundManager->ClearUnk0x04Flag0x04();
			}
			else {
				soundManager->SetUnk0x04Flag0x04();
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x004164c0 FOLDED
void OptionsScreenBase::VTable0x98()
{
}

// FUNCTION: LEGORACERS 0x004835a0
void OptionsScreenBase::VTable0x9c()
{
	m_unk0x448.SetFlags(2);
	m_unk0x738.SetFlags(2);
	m_unk0xa28.SetFlags(2);
	m_unk0xd18.SetFlags(2);
	m_unk0x12f8.SetFlags(2);
	m_unk0x1008.SetFlags(2);

	m_unk0x448.VTable0x4c(4);
	m_unk0x3d0.VTable0x44(0x10, TRUE);
	m_unk0x3d0.FUN_0046f6b0(20);
	m_unk0x18d8.FUN_00482790(2);
}

// FUNCTION: LEGORACERS 0x00483640
void OptionsScreenBase::VTable0xa0()
{
	m_unk0x448.ClearFlags(2);
	m_unk0x738.ClearFlags(2);
	m_unk0xa28.ClearFlags(2);
	m_unk0xd18.ClearFlags(2);
	m_unk0x12f8.ClearFlags(2);
	m_unk0x1008.ClearFlags(2);
}

// FUNCTION: LEGORACERS 0x004836a0
void OptionsScreenBase::FUN_004836a0()
{
	m_unk0x3d0.VTable0x44(0x11, TRUE);
	m_unk0x3d0.FUN_0046f6b0(20);
	m_unk0x18d8.FUN_00482790(0x10);

	m_unk0x1bc8.SetFlags(2);
	m_unk0x25bc.SetFlags(2);
	m_unk0x3600[0].SetFlags(2);
	m_unk0x3600[1].SetFlags(2);

	VTable0x44(&m_unk0x1bc8);
	VTable0x44(&m_unk0x25bc);
	m_unk0x1bc8.VTable0x4c(4);
}

// FUNCTION: LEGORACERS 0x00483730
void OptionsScreenBase::FUN_00483730()
{
	m_unk0x1bc8.ClearFlags(2);
	m_unk0x25bc.ClearFlags(2);
	m_unk0x3600[0].ClearFlags(2);
	m_unk0x3600[1].ClearFlags(2);
}

// FUNCTION: LEGORACERS 0x00483770
void OptionsScreenBase::FUN_00483770()
{
	m_unk0x4178.SetFlags(2);
	m_unk0x4864.SetFlags(2);

	for (LegoS32 i = 0; i < 3; i++) {
		m_unk0x5040[i].SetFlags(2);
	}

	VTable0x44(&m_unk0x36f0);
	m_unk0x4178.VTable0x4c(4);
	m_unk0x3d0.VTable0x44(0x13, TRUE);
	m_unk0x3d0.FUN_0046f6b0(20);
	m_unk0x18d8.FUN_00482790(0x10);
}

// FUNCTION: LEGORACERS 0x00483800
void OptionsScreenBase::FUN_00483800()
{
	m_unk0x4178.ClearFlags(2);
	m_unk0x4864.ClearFlags(2);
	m_unk0x36f0.ClearFlags(2);

	for (LegoS32 i = 0; i < 3; i++) {
		m_unk0x5040[i].ClearFlags(2);
	}
}

// FUNCTION: LEGORACERS 0x00483850
void OptionsScreenBase::VTable0xa4()
{
	switch (m_unk0x368) {
	case 0:
		VTable0xa0();
		break;
	case 1:
		FUN_00483730();
		break;
	case 2:
		FUN_00483800();
		break;
	}

	switch (m_unk0x369) {
	case 0:
		VTable0x9c();
		break;
	case 1:
		FUN_004836a0();
		break;
	case 2:
		FUN_00483770();
		break;
	}

	m_unk0x368 = m_unk0x369;
}

// FUNCTION: LEGORACERS 0x004838e0
LegoBool32 OptionsScreenBase::VTable0x78(undefined4 p_elapsed)
{
	if (m_unk0x369 != m_unk0x368 && !(m_unk0x35c->GetUnk0x54() & 1)) {
		VTable0xa4();
	}

	if (m_unk0x368 == 0) {
		if (m_inputManager->GetJoystickCount() <= 1 && !m_inputManager->IsKeyboardAvailable()) {
			m_unk0xd18.VTable0x48(5);
			return MenuGameScreen::VTable0x78(p_elapsed);
		}

		m_unk0xd18.VTable0x44(5);
	}

	return MenuGameScreen::VTable0x78(p_elapsed);
}
