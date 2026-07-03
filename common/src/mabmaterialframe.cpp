#include "mabmaterialframe.h"

#include "decomp.h"
#include "golerror.h"
#include "golname.h"
#include "render/golrenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MabMaterialFrame, 0x8)

// FUNCTION: GOLDP 0x10026100 FOLDED
// FUNCTION: LEGORACERS 0x0045c3b0 FOLDED
MabMaterialFrame::MabMaterialFrame()
{
	m_material = NULL;
	m_frame = 0;
}

// FUNCTION: GOLDP 0x10026110
// FUNCTION: LEGORACERS 0x00410770
void MabMaterialFrame::Initialize(GolRenderDevice* p_renderer, const LegoChar* p_name, LegoU32 p_id)
{
	m_material = p_renderer->FindMaterialByName(p_name);
	if (m_material == NULL) {
		LegoChar message[40];
		::strcpy(message, "Unable to find named material: ");
		size_t lenPrefix = strlen(message);
		::strncpy(message + lenPrefix, p_name, sizeof(GolName));
		message[lenPrefix + sizeof(GolName)] = '\0';
		GOL_FATALERROR_MESSAGE(message);
	}

	m_frame = p_id;
}
