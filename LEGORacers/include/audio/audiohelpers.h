#ifndef AUDIOHELPERS_H
#define AUDIOHELPERS_H

#include "types.h"

LegoChar LowercaseString(LegoChar* p_string);
LegoChar* JoinAudioPath(LegoChar* p_destination, LegoU32 p_size, const LegoChar* p_basePath, const LegoChar* p_name);
void DecodeMonoPcmToMono(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state);
void DecodeMonoPcmToStereo(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state);
void DecodeStereoPcmToStereo(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoU32 p_count,
	LegoS32* p_leftState,
	LegoS32* p_rightState
);
void DecodeMonoPcmToStereoInterpolated(LegoChar* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state);

#endif // AUDIOHELPERS_H
