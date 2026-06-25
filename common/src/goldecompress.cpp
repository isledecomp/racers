#include "goldecompress.h"

// FUNCTION: GOLDP 0x10032840
// STUB: LEGORACERS 0x0044e9a0
LegoU32 GolDecompress(LegoU8* p_src, LegoU8* p_dst)
{
#ifdef BUILDING_LEGORACERS
	LegoU8* src = p_src;
	LegoU8* dst = p_dst;
	LegoS32 value = 0;

	value = *src++;
	*dst++ = static_cast<LegoU8>(value);

	for (;;) {
		LegoS32 flags = *src;
		flags <<= 24;
		src++;
		flags++;
		for (;;) {
			if (flags >= 0) {
				flags += flags;
				value = *src++;
				*dst++ = static_cast<LegoU8>(value);
				if (!(flags & 0xff)) {
					break;
				}
			}
			else {
				value = *src++;
				LegoS32 offset = value;
				value &= 0x0f;
				offset &= 0xf0;
				offset <<= 4;
				offset |= *src;

				if (value == 0) {
					value = -src[1] - 18;
					src++;
				}
				else {
					value -= 18;
				}

				src++;
				offset = -offset;
				if (offset == 0) {
					return dst - p_dst;
				}

				do {
					value++;
					*dst = dst[offset];
					dst++;
				} while (value != 0);

				flags += flags;
				if (!(flags & 0xff)) {
					break;
				}
			}
		}
	}
#else
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
#endif
}
