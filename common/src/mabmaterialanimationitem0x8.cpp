#include "mabmaterialanimationitem0x8.h"

#include "decomp.h"
#include "golerror.h"
#include "whitefalcon0x140.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MabMaterialAnimationItem0x8, 0x8)

// FUNCTION: GOLDP 0x10026100 FOLDED
// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
MabMaterialAnimationItem0x8::MabMaterialAnimationItem0x8()
{
	m_unk0x00 = NULL;
	m_unk0x04 = 0;
}

// FUNCTION: GOLDP 0x10026110
// FUNCTION: LEGORACERS 0x00410770
void MabMaterialAnimationItem0x8::FUN_10026110(WhiteFalcon0x140* p_renderer, const LegoChar* p_name, LegoU32 p_id)
{
	m_unk0x00 = p_renderer->FindMaterialByName(p_name);
	if (m_unk0x00 == NULL) {
		LegoChar message[40];
		::strcpy(message, "Unable to find named material: ");
		size_t lenPrefix = strlen(message);
		::strncpy(message + lenPrefix, p_name, 8);
		message[lenPrefix + 8] = '\0';
		GOL_FATALERROR_MESSAGE(message);
	}

	m_unk0x04 = p_id;
}
