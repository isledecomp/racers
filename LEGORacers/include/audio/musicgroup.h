#ifndef MUSICGROUP_H
#define MUSICGROUP_H

#include "audio/musicgroupbase.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

// SIZE 0x10
class MusicGroup : public MusicGroupBase, public GolListLink {
public:
	MusicGroup() {}
};

#endif // MUSICGROUP_H
