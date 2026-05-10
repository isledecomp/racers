#include "imaginaryhammer0x658.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golhashtable.h"
#include "golstream.h"
#include "menutoolcontext0x4bc8.h"
#include "menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(ImaginaryHammer0x658, 0x658)

// FUNCTION: LEGORACERS 0x00488380
ImaginaryHammer0x658::ImaginaryHammer0x658()
{
}

// FUNCTION: LEGORACERS 0x004883c0
ImaginaryHammer0x658::~ImaginaryHammer0x658()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00488410
LegoBool32 ImaginaryHammer0x658::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	Destroy();

	m_unk0x362 = p_createParams->m_menuId;
	p_createParams->m_menuId = 1;

	if (!ImaginaryChisel0x658::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	undefined4 nextMenu = 0;
	undefined4 pushExtra = FALSE;

	switch (m_unk0x362) {
	case 43:
		nextMenu = 0x15;
		break;
	case 41:
		nextMenu = 0x14;
		break;
	case 1:
		nextMenu = 0x12;
		break;
	case 39:
		nextMenu = 0x11;
		pushExtra = TRUE;
		break;
	}

	if (nextMenu) {
		FUN_00480470(p_context, nextMenu, pushExtra);
	}

	m_unk0x368.m_unk0x2cc = 0;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 ImaginaryHammer0x658::Destroy()
{
	if (m_unk0x354) {
		if (m_unk0x354->m_unk0x4b40.GetMusicGroup()) {
			if (m_unk0x354->m_unk0x4b40.GetMusicInstance()) {
				m_unk0x354->m_unk0x4b40.GetMusicInstance()->Stop();
				m_unk0x354->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(
					m_unk0x354->m_unk0x4b40.GetMusicInstance()
				);
				m_unk0x354->m_unk0x4b40.SetMusicInstance(NULL);
			}
		}
	}

	return ImaginaryChisel0x658::Destroy();
}

// FUNCTION: LEGORACERS 0x00488550
void ImaginaryHammer0x658::VTable0x4c()
{
	switch (m_unk0x362) {
	case 43:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\N64INTR");
		}
		break;
	case 41:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\LEGOINTR");
		}
		break;
	case 1:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\HVSINTRO");
		}
		break;
	case 40:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\LEGAL");
		}
		break;
	case 39:
		if (g_hashTable) {
			g_hashTable->SetCurrentEntryFromString("MENUDATA\\CREDITS");
		}
		break;
	}

	FUN_0046c5b0(&m_unk0x368, m_unk0x362);
}

// FUNCTION: LEGORACERS 0x00488630
void ImaginaryHammer0x658::VTable0x84()
{
	m_unk0x354->m_unk0x04.Pop();
	m_unk0xc4->SetUnk0x41(TRUE);

	switch (m_unk0x362) {
	case 43:
		m_unk0x354->m_unk0x04.Push(0x29);
		return;
	case 41:
		m_unk0x354->m_unk0x04.Push(1);
		return;
	case 1:
		m_unk0x354->m_unk0x04.Push(0x26);
		return;
	case 40:
		m_unk0x354->m_unk0x04.Push(2);
		m_unk0x354->m_unk0x04.Push(0x2d);
		return;
	case 39:
		if (!m_unk0x354->m_unk0x04.GetSize()) {
			m_unk0x354->m_unk0x04.Push(2);
		}
		return;
	}
}

// FUNCTION: LEGORACERS 0x00488720
LegoBool32 ImaginaryHammer0x658::VTable0x78(undefined4 p_unk0x04)
{
	if (m_unk0x362 != 0x29) {
		m_unk0x368.m_unk0x2cc = 1;
	}

	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}
