#ifndef MUSICGROUP_H
#define MUSICGROUP_H

#include "audio/musicgroupstate.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

// SIZE 0x10
class MusicGroup : public MusicGroupState, public GolListLink {
public:
	MusicGroup() {}
};

#endif // MUSICGROUP_H
