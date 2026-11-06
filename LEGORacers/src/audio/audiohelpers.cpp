#include "audio/audiohelpers.h"

#include "compat.h"

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

#ifdef COMPAT_MODE

void DecodeMonoPcmToMono(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 index = p_state[1];
	LegoS32 sample = p_state[0];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 nibble = *p_source;
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
			nibble = *p_source;
			delta = 7;
			if (sample > 32767) {
				sample = 32767;
			}
		}
		else {
			sample -= delta;
			nibble = *p_source;
			delta = 7;
			if (sample < -32768) {
				sample = -32768;
			}
		}

		*p_destination = sample;
		p_source++;
		p_destination++;
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
		*p_destination = sample;
		p_destination++;
	} while (--p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

#else

// FUNCTION: LEGORACERS 0x00418100
__declspec(naked) void DecodeMonoPcmToMono(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	__asm {
		push ebp
		push esi
		push edi
		push ebx
		mov edx, dword ptr [esp + 0x20]
		mov esi, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x18]
		mov ebp, dword ptr [edx + 4]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
	L_DecodeMonoPcmToMono_8:
		mov dl, byte ptr [esi]
		mov eax, 7
		shr edx, 4
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToMono_0
		xor ebp, ebp
		jmp L_DecodeMonoPcmToMono_1
	L_DecodeMonoPcmToMono_0:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToMono_1
		mov ebp, 0x58
	L_DecodeMonoPcmToMono_1:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToMono_2
		add ecx, eax
		mov dl, byte ptr [esi]
		cmp ecx, 0x7fff
		mov eax, 7
		jle L_DecodeMonoPcmToMono_3
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToMono_3
	L_DecodeMonoPcmToMono_2:
		sub ecx, eax
		mov dl, byte ptr [esi]
		cmp ecx, 0xffff8000
		mov eax, 7
		jge L_DecodeMonoPcmToMono_3
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToMono_3:
		mov word ptr [edi], cx
		add esi, 1
		add edi, 2
		and eax, edx
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToMono_4
		xor ebp, ebp
		jmp L_DecodeMonoPcmToMono_5
	L_DecodeMonoPcmToMono_4:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToMono_5
		mov ebp, 0x58
	L_DecodeMonoPcmToMono_5:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToMono_6
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeMonoPcmToMono_7
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToMono_7
	L_DecodeMonoPcmToMono_6:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeMonoPcmToMono_7
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToMono_7:
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		mov word ptr [edi], cx
		dec eax
		lea edi, [edi + 2]
		mov dword ptr [esp + 0x1c], eax
		jne L_DecodeMonoPcmToMono_8
		mov edx, dword ptr [esp + 0x20]
		mov dword ptr [edx + 4], ebp
		mov dword ptr [edx], ecx
		pop ebx
		pop edi
		pop esi
		pop ebp
		ret
	}
}

#endif

#ifdef COMPAT_MODE

void DecodeMonoPcmToStereo(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 index = p_state[1];
	LegoS32 sample = p_state[0];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 nibble = *p_source;
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
			nibble = *p_source;
			delta = 7;
			if (sample > 32767) {
				sample = 32767;
			}
		}
		else {
			sample -= delta;
			nibble = *p_source;
			delta = 7;
			if (sample < -32768) {
				sample = -32768;
			}
		}

		*p_destination = sample;
		p_source++;
		p_destination[1] = sample;
		p_destination += 2;
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
		*p_destination = sample;
		p_destination[1] = sample;
		p_destination += 2;
	} while (--p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

#else

// FUNCTION: LEGORACERS 0x00418200
__declspec(naked) void DecodeMonoPcmToStereo(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoS32 p_count,
	LegoS32* p_state
)
{
	__asm {
		push ebp
		push esi
		push edi
		push ebx
		mov edx, dword ptr [esp + 0x20]
		mov esi, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x18]
		mov ebp, dword ptr [edx + 4]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
	L_DecodeMonoPcmToStereoTag_8:
		mov dl, byte ptr [esi]
		mov eax, 7
		shr edx, 4
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToStereoTag_0
		xor ebp, ebp
		jmp L_DecodeMonoPcmToStereoTag_1
	L_DecodeMonoPcmToStereoTag_0:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToStereoTag_1
		mov ebp, 0x58
	L_DecodeMonoPcmToStereoTag_1:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToStereoTag_2
		add ecx, eax
		mov dl, byte ptr [esi]
		cmp ecx, 0x7fff
		mov eax, 7
		jle L_DecodeMonoPcmToStereoTag_3
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToStereoTag_3
	L_DecodeMonoPcmToStereoTag_2:
		sub ecx, eax
		mov dl, byte ptr [esi]
		cmp ecx, 0xffff8000
		mov eax, 7
		jge L_DecodeMonoPcmToStereoTag_3
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToStereoTag_3:
		mov word ptr [edi], cx
		add esi, 1
		mov word ptr [edi + 2], cx
		add edi, 4
		and eax, edx
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToStereoTag_4
		xor ebp, ebp
		jmp L_DecodeMonoPcmToStereoTag_5
	L_DecodeMonoPcmToStereoTag_4:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToStereoTag_5
		mov ebp, 0x58
	L_DecodeMonoPcmToStereoTag_5:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToStereoTag_6
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeMonoPcmToStereoTag_7
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToStereoTag_7
	L_DecodeMonoPcmToStereoTag_6:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeMonoPcmToStereoTag_7
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToStereoTag_7:
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		mov word ptr [edi], cx
		dec eax
		mov word ptr [edi + 2], cx
		lea edi, [edi + 4]
		mov dword ptr [esp + 0x1c], eax
		jne L_DecodeMonoPcmToStereoTag_8
		mov edx, dword ptr [esp + 0x20]
		mov dword ptr [edx + 4], ebp
		mov dword ptr [edx], ecx
		pop ebx
		pop edi
		pop esi
		pop ebp
		ret
	}
}

#endif

#ifdef COMPAT_MODE

static void DecodeStereoChannel(LegoU8* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 sample = p_state[0];
	LegoS32 index = p_state[1];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoU32 nibble = *p_source;
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
		*p_destination = sample;
		nibble = *p_source;
		delta = 7;
		p_source += 2;
		p_destination += 2;
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
		*p_destination = sample;
		p_destination += 2;
	} while (--p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

#else

// FUNCTION: LEGORACERS 0x00418310
__declspec(naked) static void DecodeStereoChannel(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoS32 p_count,
	LegoS32* p_state
)
{
	__asm {
		push ebp
		push esi
		push edi
		push ebx
		mov edx, dword ptr [esp + 0x20]
		mov esi, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x18]
		mov ebp, dword ptr [edx + 4]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
	L_DecodeStereoChannel_8:
		mov dl, byte ptr [esi]
		mov eax, 7
		shr edx, 4
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeStereoChannel_0
		xor ebp, ebp
		jmp L_DecodeStereoChannel_1
	L_DecodeStereoChannel_0:
		cmp ebp, 0x58
		jle L_DecodeStereoChannel_1
		mov ebp, 0x58
	L_DecodeStereoChannel_1:
		sar eax, 2
		and dl, 8
		jne L_DecodeStereoChannel_2
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeStereoChannel_3
		mov ecx, 0x7fff
		jmp L_DecodeStereoChannel_3
	L_DecodeStereoChannel_2:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeStereoChannel_3
		mov ecx, 0xffff8000
	L_DecodeStereoChannel_3:
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		mov word ptr [edi], cx
		mov dl, byte ptr [esi]
		mov eax, 7
		add esi, 2
		add edi, 4
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeStereoChannel_4
		xor ebp, ebp
		jmp L_DecodeStereoChannel_5
	L_DecodeStereoChannel_4:
		cmp ebp, 0x58
		jle L_DecodeStereoChannel_5
		mov ebp, 0x58
	L_DecodeStereoChannel_5:
		sar eax, 2
		and dl, 8
		jne L_DecodeStereoChannel_6
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeStereoChannel_7
		mov ecx, 0x7fff
		jmp L_DecodeStereoChannel_7
	L_DecodeStereoChannel_6:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeStereoChannel_7
		mov ecx, 0xffff8000
	L_DecodeStereoChannel_7:
		mov eax, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		mov word ptr [edi], cx
		dec eax
		lea edi, [edi + 4]
		mov dword ptr [esp + 0x1c], eax
		jne L_DecodeStereoChannel_8
		mov edx, dword ptr [esp + 0x20]
		mov dword ptr [edx + 4], ebp
		mov dword ptr [edx], ecx
		pop ebx
		pop edi
		pop esi
		pop ebp
		ret
	}
}

#endif

#ifdef COMPAT_MODE

void DecodeStereoPcmToStereo(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoS32 p_count,
	LegoS32* p_leftState,
	LegoS32* p_rightState
)
{
	LegoU32 remaining = static_cast<LegoU32>(p_count);
	for (;;) {
		LegoU32 previous = remaining;
		remaining -= 0x200;
		if (previous <= 0x200) {
			break;
		}

		DecodeStereoChannel(p_source, p_destination, 0x100, p_leftState);
		p_source++;
		p_destination++;
		DecodeStereoChannel(p_source, p_destination, 0x100, p_rightState);
		p_source += 0x1ff;
		p_destination += 0x3ff;
	}

	remaining += 0x200;
	remaining >>= 1;
	DecodeStereoChannel(p_source, p_destination, remaining, p_leftState);
	p_source++;
	p_destination++;
	DecodeStereoChannel(p_source, p_destination, remaining, p_rightState);
}

#else

// FUNCTION: LEGORACERS 0x00418410
__declspec(naked) void DecodeStereoPcmToStereo(
	LegoU8* p_source,
	LegoS16* p_destination,
	LegoS32 p_count,
	LegoS32* p_leftState,
	LegoS32* p_rightState
)
{
	__asm {
		push esi
		push edi
		push ebx
		mov edx, dword ptr [esp + 0x1c]
		mov ebx, dword ptr [esp + 0x18]
		mov edi, dword ptr [esp + 0x14]
		mov esi, dword ptr [esp + 0x10]
		push edx
		push 0x100
		push edi
		push esi
		jmp L_DecodeStereoPcmToStereo_1
	L_DecodeStereoPcmToStereo_0:
		call DecodeStereoChannel
		inc esi
		add edi, 2
		mov eax, 0x100
		mov edx, dword ptr [esp + 0x30]
		mov dword ptr [esp], esi
		mov dword ptr [esp + 4], edi
		mov dword ptr [esp + 8], eax
		mov dword ptr [esp + 0xc], edx
		call DecodeStereoChannel
		add esi, 0x1ff
		add edi, 0x7fe
		mov eax, 0x100
		mov edx, dword ptr [esp + 0x2c]
		mov dword ptr [esp], esi
		mov dword ptr [esp + 4], edi
		mov dword ptr [esp + 8], eax
		mov dword ptr [esp + 0xc], edx
	L_DecodeStereoPcmToStereo_1:
		sub ebx, 0x200
		ja L_DecodeStereoPcmToStereo_0
		add ebx, 0x200
		shr ebx, 1
		mov dword ptr [esp + 8], ebx
		call DecodeStereoChannel
		inc esi
		add edi, 2
		mov edx, dword ptr [esp + 0x30]
		mov dword ptr [esp], esi
		mov dword ptr [esp + 4], edi
		mov dword ptr [esp + 8], ebx
		mov dword ptr [esp + 0xc], edx
		call DecodeStereoChannel
		add esp, 0x10
		pop ebx
		pop edi
		pop esi
		ret
	}
}

#endif

#ifdef COMPAT_MODE

void DecodeMonoPcmToStereoInterpolated(LegoChar* p_source, LegoS16* p_destination, LegoS32 p_count, LegoS32* p_state)
{
	LegoS32 index = p_state[1];
	LegoS32 sample = p_state[0];
	LegoS32 step = g_adpcmStepTable[index];

	do {
		LegoS32 previous = sample;
		LegoU32 nibble = (LegoU8) *p_source;
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
		p_destination[1] = sample;
		*p_destination = (sample + previous) >> 1;
		previous = sample;
		nibble = (LegoU8) *p_source;
		delta = 7;
		p_source++;
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
		LegoS32 interpolated = (sample + previous) >> 1;
		p_destination[3] = sample;
		p_destination[2] = interpolated;
		p_destination += 4;
	} while (--p_count);

	p_state[1] = index;
	p_state[0] = sample;
}

#else

// FUNCTION: LEGORACERS 0x004184c0
__declspec(naked) void DecodeMonoPcmToStereoInterpolated(
	LegoChar* p_source,
	LegoS16* p_destination,
	LegoS32 p_count,
	LegoS32* p_state
)
{
	__asm {
		push ebp
		push esi
		push edi
		push ebx
		mov edx, dword ptr [esp + 0x20]
		mov esi, dword ptr [esp + 0x14]
		mov edi, dword ptr [esp + 0x18]
		mov ebp, dword ptr [edx + 4]
		mov ecx, dword ptr [edx]
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
	L_DecodeMonoPcmToStereoInterpolated_8:
		mov dl, byte ptr [esi]
		mov eax, 7
		shr edx, 4
		push ecx
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToStereoInterpolated_0
		xor ebp, ebp
		jmp L_DecodeMonoPcmToStereoInterpolated_1
	L_DecodeMonoPcmToStereoInterpolated_0:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToStereoInterpolated_1
		mov ebp, 0x58
	L_DecodeMonoPcmToStereoInterpolated_1:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToStereoInterpolated_2
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeMonoPcmToStereoInterpolated_3
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToStereoInterpolated_3
	L_DecodeMonoPcmToStereoInterpolated_2:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeMonoPcmToStereoInterpolated_3
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToStereoInterpolated_3:
		pop eax
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		add eax, ecx
		mov word ptr [edi + 2], cx
		sar eax, 1
		push ecx
		mov word ptr [edi], ax
		mov dl, byte ptr [esi]
		mov eax, 7
		add esi, 1
		and eax, edx
		and edx, 0xf
		imul eax, ebx
		add ebp, dword ptr [edx*4 + g_adpcmIndexAdjust]
		jns L_DecodeMonoPcmToStereoInterpolated_4
		xor ebp, ebp
		jmp L_DecodeMonoPcmToStereoInterpolated_5
	L_DecodeMonoPcmToStereoInterpolated_4:
		cmp ebp, 0x58
		jle L_DecodeMonoPcmToStereoInterpolated_5
		mov ebp, 0x58
	L_DecodeMonoPcmToStereoInterpolated_5:
		sar eax, 2
		and dl, 8
		jne L_DecodeMonoPcmToStereoInterpolated_6
		add ecx, eax
		cmp ecx, 0x7fff
		jle L_DecodeMonoPcmToStereoInterpolated_7
		mov ecx, 0x7fff
		jmp L_DecodeMonoPcmToStereoInterpolated_7
	L_DecodeMonoPcmToStereoInterpolated_6:
		sub ecx, eax
		cmp ecx, 0xffff8000
		jge L_DecodeMonoPcmToStereoInterpolated_7
		mov ecx, 0xffff8000
	L_DecodeMonoPcmToStereoInterpolated_7:
		pop eax
		mov edx, dword ptr [esp + 0x1c]
		add eax, ecx
		mov ebx, dword ptr [ebp*4 + g_adpcmStepTable]
		sar eax, 1
		mov word ptr [edi + 6], cx
		dec edx
		mov word ptr [edi + 4], ax
		lea edi, [edi + 8]
		mov dword ptr [esp + 0x1c], edx
		jne L_DecodeMonoPcmToStereoInterpolated_8
		mov edx, dword ptr [esp + 0x20]
		mov dword ptr [edx + 4], ebp
		mov dword ptr [edx], ecx
		pop ebx
		pop edi
		pop esi
		pop ebp
		ret
	}
}

#endif
