#include "goldecompress.h"

// FUNCTION: GOLDP 0x10032840
LegoU32 GolDecompress(LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* writePtr = p_dst;

	*writePtr++ = *p_src++;
	for (;;) {
		LegoU32 ctrl = ((*p_src++) << 24) + 1;
		for (;;) {
			if (static_cast<LegoS32>(ctrl) >= 0) {
				*writePtr++ = *p_src++;
				ctrl *= 2;
				if (!(ctrl & 0xff)) {
					break;
				}
			}
			else {
				LegoU8 cntOff = *p_src++;
				LegoU32 rawCnt = cntOff & 0xf;
				LegoU8 rawBack;
				LegoU32 cnt;
				if (rawCnt == 0) {
					rawBack = *p_src++;
					cnt = -*p_src++ - 18;
				}
				else {
					rawBack = *p_src++;
					cnt = rawCnt - 18;
				}
				LegoS32 back = -(((cntOff >> 4) << 8) | rawBack);
				if (back == 0) {
					return writePtr - p_dst;
				}
				do {
					cnt++;
					*writePtr = writePtr[back];
					writePtr++;
				} while (cnt != 0);
				ctrl *= 2;
				if (!(ctrl & 0xff)) {
					break;
				}
			}
		}
	}
}
