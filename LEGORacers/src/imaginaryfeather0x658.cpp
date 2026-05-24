#include "imaginaryfeather0x658.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "golerror.h"
#include "golhashtable.h"
#include "menutoolcontext0x4bc8.h"
#include "menutoolcreateparams0x30.h"

DECOMP_SIZE_ASSERT(ImaginaryFeather0x658, 0x658)

// FUNCTION: LEGORACERS 0x004809b0
ImaginaryFeather0x658::ImaginaryFeather0x658()
{
}

// FUNCTION: LEGORACERS 0x004809f0
ImaginaryFeather0x658::~ImaginaryFeather0x658()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00480a40
LegoBool32 ImaginaryFeather0x658::VTable0x8c(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams)
{
	if (m_initialized) {
		Destroy();
	}

	if (!ImaginaryChisel0x658::VTable0x8c(p_context, p_createParams)) {
		return FALSE;
	}

	if (p_context->m_unk0x4b40.GetMusicInstance()) {
		p_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(p_context->m_unk0x4b40.GetMusicInstance());
		p_context->m_unk0x4b40.SetMusicInstance(NULL);
	}

	p_context->m_unk0x4b40.SetMusicInstance(p_context->m_unk0x4b40.GetMusicGroup()->CreateMusicInstance(19));
	if (!p_context->m_unk0x4b40.GetMusicInstance()) {
		GOL_FATALERROR(c_golErrorGeneral);
	}

	p_context->m_unk0x4b40.GetMusicInstance()->Play(TRUE);
	m_unk0x368.m_unk0x2cc = FALSE;
	return TRUE;
}

// FUNCTION: LEGORACERS 0x00480ad0
void ImaginaryFeather0x658::VTable0x4c()
{
	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA\\MAININTR");
	}

	FUN_0046c5b0(&m_unk0x368, m_unk0x28c);

	if (g_hashTable) {
		g_hashTable->SetCurrentEntryFromString("MENUDATA");
	}
}

// FUNCTION: LEGORACERS 0x00480b20
void ImaginaryFeather0x658::VTable0x84()
{
	m_context->m_menuStack.Pop();
	m_context->m_menuStack.Push(40);
}

// FUNCTION: LEGORACERS 0x00480b50 FOLDED
LegoBool32 ImaginaryFeather0x658::VTable0x78(undefined4 p_unk0x04)
{
	m_unk0x368.m_unk0x2cc = TRUE;
	return ImaginaryChisel0x658::VTable0x78(p_unk0x04);
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 ImaginaryFeather0x658::Destroy()
{
	if (m_context) {
		if (m_context->m_unk0x4b40.GetMusicGroup()) {
			if (m_context->m_unk0x4b40.GetMusicInstance()) {
				m_context->m_unk0x4b40.GetMusicInstance()->Stop();
				m_context->m_unk0x4b40.GetMusicGroup()->DestroyMusicInstance(m_context->m_unk0x4b40.GetMusicInstance());
				m_context->m_unk0x4b40.SetMusicInstance(NULL);
			}
		}
	}

	return ImaginaryChisel0x658::Destroy();
}
