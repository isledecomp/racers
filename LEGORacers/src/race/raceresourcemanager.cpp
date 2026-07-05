#include "race/raceresourcemanager.h"

#include "audio/directsoundgroup.h"
#include "audio/spatialsoundinstance.h"
#include "audio/streamingsoundinstance.h"
#include "decomp.h"

#include <stddef.h>

DECOMP_SIZE_ASSERT(RaceResourceManager, 0x04)

// FUNCTION: LEGORACERS 0x00443c10
void RaceResourceManager::ReleaseSound(SpatialSoundInstance* p_sound)
{
	if (m_soundManager != NULL) {
		// Acquired sounds are streaming instances except the null fallback,
		// which is only handed out when no sound manager exists.
		DirectSoundGroup* group = p_sound->GetSoundGroup();
		group->DestroyStreamingSoundInstance(static_cast<StreamingSoundInstance*>(p_sound));
	}
}
