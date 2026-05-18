#ifndef GARNETFLARE0X60_H
#define GARNETFLARE0X60_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class LavenderVault0x764;

// SIZE 0x60
class GarnetFlare0x60 {
public:
	// SIZE 0x18
	struct LoadParams {
		undefined4 m_unk0x00;            // 0x00
		GolExport* m_golExport;          // 0x04
		BronzeFalcon0xc8770* m_renderer; // 0x08
		LavenderVault0x764* m_unk0x0c;   // 0x0c
		undefined4 m_binary;             // 0x10
		undefined4 m_unk0x14;            // 0x14
	};

	GarnetFlare0x60();
	~GarnetFlare0x60();
	LegoBool32 FUN_00497f10(const LoadParams* p_params, undefined4 p_unk0x08);
	LegoBool32 ReleaseResources();

private:
	undefined m_unk0x00[0x60 - 0x00]; // 0x00
};

#endif // GARNETFLARE0X60_H
