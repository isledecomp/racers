#include "render/golsoftwarerenderer.h"

#include "golcpu.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(GolSoftwareRenderer, 0x58)
DECOMP_SIZE_ASSERT(GolSoftwareRenderer::Command0x14, 0x14)

// FUNCTION: GOLDP 0x10029920 FOLDED
void NoopSpanRasterizer()
{
	// empty
}

// FUNCTION: GOLDP 0x1003ba20
static void NoopTriangleRasterizer()
{
	// empty
}

static LegoS32 __fastcall BucketCommandArrayBySortByte0(
	GolSoftwareRenderer::Command0x14** p_buckets,
	GolSoftwareRenderer::Command0x14* p_command,
	LegoS32 p_count
);

// STUB: GOLDP 0x10041000
static LegoU8 __fastcall BucketCommandsBySortByte3(
	GolSoftwareRenderer::Command0x14** p_buckets,
	GolSoftwareRenderer::Command0x14* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::Command0x14* command;

	for (; p_command != NULL; p_buckets[bucketIndex] = command) {
		bucketIndex = p_command->m_sortKey.m_bytes[3];
		command = p_command;
		p_command = p_command->m_next;
		command->m_next = p_buckets[bucketIndex];
	}

	return static_cast<LegoU8>(bucketIndex);
}

// STUB: GOLDP 0x10041030
static LegoU8 __fastcall BucketCommandsBySortByte2(
	GolSoftwareRenderer::Command0x14** p_buckets,
	GolSoftwareRenderer::Command0x14* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::Command0x14* command;

	for (; p_command != NULL; p_buckets[bucketIndex] = command) {
		bucketIndex = p_command->m_sortKey.m_bytes[2];
		command = p_command;
		p_command = p_command->m_next;
		command->m_next = p_buckets[bucketIndex];
	}

	return static_cast<LegoU8>(bucketIndex);
}

// STUB: GOLDP 0x10041060
static LegoU8 __fastcall BucketCommandsBySortByte1(
	GolSoftwareRenderer::Command0x14** p_buckets,
	GolSoftwareRenderer::Command0x14* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::Command0x14* command;

	for (; p_command != NULL; p_buckets[bucketIndex] = command) {
		bucketIndex = p_command->m_sortKey.m_bytes[1];
		command = p_command;
		p_command = p_command->m_next;
		command->m_next = p_buckets[bucketIndex];
	}

	return static_cast<LegoU8>(bucketIndex);
}

// STUB: GOLDP 0x100411b0
void GolSoftwareRenderer::FUN_100411b0(LegoU8* p_buffer, DuskwindBananaRelic0x24* p_material, LegoU32 p_index)
{
	// TODO
	STUB(0x100411b0);
}

// FUNCTION: GOLDP 0x100416a0
GolSoftwareRenderer::GolSoftwareRenderer()
{
	DetectCPU();
	m_unk0x4c = 0;
	m_nodes = NULL;
	m_commandHead = 0;
}

// FUNCTION: GOLDP 0x100416c0
LegoBool GolSoftwareRenderer::Initialize(PixelFormat p_pixelFormat, LegoS32 p_nodeCapacity)
{
	m_commandHead = NULL;
	if (m_nodes != NULL) {
		delete[] m_nodes;
		m_nodes = NULL;
	}

	PixelFormat indexedPixelFormat = e_formatIndex8;
	m_currentTriangleRasterizer = NoopTriangleRasterizer;
	m_triangleRasterizer = NoopTriangleRasterizer;
	m_unk0x34 = 0;
	m_unk0x2c = 0;
	m_spanRasterizer = NoopSpanRasterizer;
	m_unk0x38 = 10000.0f;
	m_unk0x3c = 225.0f;

	switch (p_pixelFormat) {
	default:
		m_bitsPerPixel = 16;
		m_bytesPerPixel = indexedPixelFormat;
		m_pixelFormat = p_pixelFormat & 1;
		break;
	case e_formatIndex8:
		m_bitsPerPixel = 8;
		m_bytesPerPixel = 1;
		m_pixelFormat = indexedPixelFormat;
		break;
	}

	if (p_nodeCapacity > 0xffff) {
		p_nodeCapacity = 0xffff;
	}

	m_nodes = new Command0x14[p_nodeCapacity];
	if (m_nodes == NULL) {
		m_commandHead = NULL;
		return FALSE;
	}

	m_nodeCapacity = p_nodeCapacity;
	return TRUE;
}

// FUNCTION: GOLDP 0x10041770
GolSoftwareRenderer::~GolSoftwareRenderer()
{
	m_commandHead = 0;
	if (m_nodes != NULL) {
		delete[] m_nodes;
		m_nodes = NULL;
	}
}

// FUNCTION: GOLDP 0x100417a0
void GolSoftwareRenderer::FUN_100417a0(Command0x14* p_cmds, LegoU32 p_count, LegoFloat p_arg3)
{
	while (p_count) {
		p_cmds->m_sortKey.m_value = p_arg3;
		p_cmds++;
		p_count--;
	}
}

// STUB: GOLDP 0x100417c0
void GolSoftwareRenderer::FUN_100417c0(Command0x14* p_cmds, LegoU32 p_count)
{
	// TODO
	STUB(0x100417c0);
}

// FUNCTION: GOLDP 0x10041830
void GolSoftwareRenderer::FUN_10041830(LegoS32 p_count, LegoBool p_sort)
{
	Command0x14* buckets0[256];
	Command0x14* buckets1[256];

	if (p_count == 0) {
		m_commandHead = NULL;
		return;
	}

	m_commandCount = p_count;

	if (p_sort) {
		::memset(buckets0, 0, sizeof(buckets0));
		BucketCommandArrayBySortByte0(buckets0, m_nodes + p_count - 1, p_count);

		::memset(buckets1, 0, sizeof(buckets1));
		Command0x14** bucket = &buckets0[255];
		LegoS32 i = 256;
		do {
			BucketCommandsBySortByte1(buckets1, *bucket);
			bucket--;
			i--;
		} while (i != 0);

		::memset(buckets0, 0, sizeof(buckets0));
		bucket = buckets1;
		i = 256;
		do {
			BucketCommandsBySortByte2(buckets0, *bucket);
			bucket++;
			i--;
		} while (i != 0);

		::memset(buckets1, 0, sizeof(buckets1));
		bucket = &buckets0[255];
		i = 256;
		do {
			BucketCommandsBySortByte3(buckets1, *bucket);
			bucket--;
			i--;
		} while (i != 0);

		Command0x14* head = NULL;
		bucket = buckets1;
		i = 256;
		do {
			Command0x14* command = *bucket;
			if (command != NULL) {
				do {
					Command0x14* next = command->m_next;
					command->m_next = head;
					head = command;
					command = next;
				} while (command != NULL);
			}
			bucket++;
			i--;
		} while (i != 0);
		m_commandHead = head;
		return;
	}

	m_commandHead = m_nodes + p_count - 1;
	if (p_count > 1) {
		Command0x14* command = m_nodes + 1;
		LegoS32 remaining = p_count - 1;
		do {
			command->m_next = command - 1;
			command++;
			remaining--;
		} while (remaining != 0);
	}
	m_nodes->m_next = NULL;
}

// STUB: GOLDP 0x10041980
static LegoS32 __fastcall BucketCommandArrayBySortByte0(
	GolSoftwareRenderer::Command0x14** p_buckets,
	GolSoftwareRenderer::Command0x14* p_command,
	LegoS32 p_count
)
{
	LegoS32 result = p_count;
	LegoU32 bucketIndex = 0;

	do {
		bucketIndex = p_command->m_sortKey.m_bytes[0];
		GolSoftwareRenderer::Command0x14* command = p_command;
		p_command--;
		result--;
		command->m_next = p_buckets[bucketIndex];
		p_buckets[bucketIndex] = command;
	} while (result != 0);

	return result;
}

// STUB: GOLDP 0x10041a20
void GolSoftwareRenderer::FUN_10041a20(LegoBool)
{
	STUB(0x10041a20);
}
