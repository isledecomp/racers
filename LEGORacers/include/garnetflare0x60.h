#ifndef GARNETFLARE0X60_H
#define GARNETFLARE0X60_H

#include "decomp.h"
#include "types.h"

// SIZE 0x60
class GarnetFlare0x60 {
public:
	GarnetFlare0x60();
	~GarnetFlare0x60();
	LegoBool32 ReleaseResources();

private:
	undefined m_unk0x00[0x60 - 0x00]; // 0x00
};

#endif // GARNETFLARE0X60_H
