#include "goldecompress.h"

// FUNCTION: GOLDP 0x10032840
LegoU32 GolDecompress(LegoU8* p_src, LegoU8* p_dst)
{
	LegoU8* src = p_src;
	LegoU8* dst = p_dst;

	*dst++ = *src++;
	for (;;) {
		LegoS32 ctrl = ((*src++) << 24) + 1;
		for (;;) {
			if (ctrl >= 0) {
				ctrl *= 2;
				*dst++ = *src++;
				if (!(ctrl & 0xff)) {
					break;
				}
			}
			else {
				LegoU8 token = *src++;
				LegoS32 count = token & 0xf;
				LegoS32 back = ((token & 0xf0) << 4) | *src;

				if (count == 0) {
					count = -*++src - 18;
				}
				else {
					count -= 18;
				}
				src++;
				back = -back;
				if (back == 0) {
					return dst - p_dst;
				}
				do {
					count++;
					*dst = dst[back];
					dst++;
				} while (count != 0);
				ctrl *= 2;
				if (!(ctrl & 0xff)) {
					break;
				}
			}
		}
	}
}
