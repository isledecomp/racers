#include "audio/audiohelpers.h"

// GLOBAL: LEGORACERS 0x004be640
LegoS32 g_adpcmIndexAdjust[16] = {-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};

// GLOBAL: LEGORACERS 0x004be680
LegoS32 g_adpcmStepTable[89] = {7,     8,     9,     10,    11,    12,    13,    14,    16,    17,    19,    21,
								23,    25,    28,    31,    34,    37,    41,    45,    50,    55,    60,    66,
								73,    80,    88,    97,    107,   118,   130,   143,   157,   173,   190,   209,
								230,   253,   279,   307,   337,   371,   408,   449,   494,   544,   598,   658,
								724,   796,   876,   963,   1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066,
								2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,  5894,  6484,
								7132,  7845,  8630,  9493,  10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350,
								22385, 24623, 27086, 29794, 32767};

// FUNCTION: LEGORACERS 0x00418100
void DecodeMonoPcmToMono(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoU8* source = p_source;
	LegoS16* destination = p_destination;
	LegoS32* state = p_state;
	LegoS32 index = state[1];
	LegoS32 sample = state[0];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 nibble = *source;
		LegoS32 delta = 7;
		nibble >>= 4;
		delta &= nibble;
		delta *= step;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		nibble &= 8;
		if (!nibble) {
			sample += delta;
			nibble = *source;
			delta = 7;
			if (sample > 32767) {
				sample = 32767;
			}
		}
		else {
			sample -= delta;
			nibble = *source;
			delta = 7;
			if (sample < -32768) {
				sample = -32768;
			}
		}

		*destination = sample;
		source++;
		destination++;
		delta &= nibble;
		step = g_adpcmStepTable[index];
		delta *= step;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		nibble &= 8;
		if (!nibble) {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}
		else {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}

		step = g_adpcmStepTable[index];
		*destination = sample;
		p_count--;
		destination++;
	} while (p_count);

	state[1] = index;
	state[0] = sample;
}

// FUNCTION: LEGORACERS 0x00418200
void DecodeMonoPcmToStereo(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 sample = p_state[0];
	LegoS32 index = p_state[1];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 value = *p_source;
		LegoU32 nibble = value >> 4;
		LegoS32 delta = (nibble & 7) * step;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		*p_destination = sample;
		p_source++;
		p_destination[1] = sample;
		p_destination += 2;
		nibble = value;
		delta = (nibble & 7) * g_adpcmStepTable[index];
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		step = g_adpcmStepTable[index];
		*p_destination = sample;
		p_count--;
		p_destination[1] = sample;
		p_destination += 2;
	} while (p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

// FUNCTION: LEGORACERS 0x00418310
static void DecodeStereoChannel(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 sample = p_state[0];
	LegoS32 index = p_state[1];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 value = *p_source;
		LegoU32 nibble = value >> 4;
		LegoS32 delta = (nibble & 7) * step;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		*p_destination = sample;
		p_source += 2;
		p_destination += 2;
		step = g_adpcmStepTable[index];
		nibble = value;
		delta = (step * (nibble & 7)) >> 2;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		step = g_adpcmStepTable[index];
		*p_destination = sample;
		p_count--;
		p_destination += 2;
	} while (p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

// FUNCTION: LEGORACERS 0x00418410
void DecodeStereoPcmToStereo(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoU32 p_count,
	LegoS32* p_leftState,
	LegoS32* p_rightState
)
{
	while (p_count > 0x200) {
		p_count -= 0x200;
		DecodeStereoChannel(p_source, p_destination, 0x100, p_leftState);
		p_source++;
		p_destination++;
		DecodeStereoChannel(p_source, p_destination, 0x100, p_rightState);
		p_source += 0x1ff;
		p_destination += 0x3ff;
	}

	p_count >>= 1;
	DecodeStereoChannel(p_source, p_destination, p_count, p_leftState);
	p_source++;
	p_destination++;
	DecodeStereoChannel(p_source, p_destination, p_count, p_rightState);
}

// FUNCTION: LEGORACERS 0x004184c0
void DecodeMonoPcmToStereoInterpolated(LegoChar* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 sample = p_state[0];
	LegoS32 index = p_state[1];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoS32 previous = sample;
		LegoU32 value = (LegoU8) *p_source;
		LegoU32 nibble = value >> 4;
		LegoS32 delta = (nibble & 7) * step;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		delta >>= 2;
		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		*p_destination = (sample + previous) >> 1;
		p_destination[1] = sample;
		previous = sample;
		p_source++;
		step = g_adpcmStepTable[index];
		nibble = value;
		delta = (step * (nibble & 7)) >> 2;
		index += g_adpcmIndexAdjust[nibble & 0x0f];

		if (index < 0) {
			index = 0;
		}
		else if (index > 88) {
			index = 88;
		}

		if (nibble & 8) {
			sample -= delta;
			if (sample < -32768) {
				sample = -32768;
			}
		}
		else {
			sample += delta;
			if (sample > 32767) {
				sample = 32767;
			}
		}

		step = g_adpcmStepTable[index];
		LegoS32 interpolated = (sample + previous) >> 1;
		p_destination[3] = sample;
		p_destination[2] = interpolated;
		p_destination += 4;
		p_count--;
	} while (p_count);

	p_state[1] = index;
	p_state[0] = sample;
}
