#include "imaginaryfeather0x658.h"

#include "audio/musicgroup.h"
#include "audio/musicinstance.h"
#include "menutoolcontext0x4bc8.h"

DECOMP_SIZE_ASSERT(ImaginaryFeather0x658, 0x658)

// STUB: LEGORACERS 0x004809b0
ImaginaryFeather0x658::ImaginaryFeather0x658()
{
	STUB(0x004809b0);
}

// STUB: LEGORACERS 0x004809f0
ImaginaryFeather0x658::~ImaginaryFeather0x658()
{
	STUB(0x004809f0);
}

// STUB: LEGORACERS 0x00480a40
LegoBool32 ImaginaryFeather0x658::VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*)
{
	STUB(0x00480a40);
	return FALSE;
}

// STUB: LEGORACERS 0x00480ad0
void ImaginaryFeather0x658::VTable0x4c()
{
	STUB(0x00480ad0);
}

// STUB: LEGORACERS 0x00480b20
void ImaginaryFeather0x658::VTable0x84()
{
	STUB(0x00480b20);
}

// STUB: LEGORACERS 0x00480b50 FOLDED
LegoBool32 ImaginaryFeather0x658::VTable0x78(undefined4)
{
	STUB(0x00480b50);
	return FALSE;
}

// FUNCTION: LEGORACERS 0x004884f0 FOLDED
LegoBool32 ImaginaryFeather0x658::VTable0x74()
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

	return ImaginaryChisel0x658::VTable0x74();
}
