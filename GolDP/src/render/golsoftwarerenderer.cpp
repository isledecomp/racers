#include "render/golsoftwarerenderer.h"

#include "golcpu.h"
#include "golmaterial.h"
#include "render/golrasterizers1.h"
#include "render/golrasterizers2.h"
#include "surface/gold3dtexture.h"

#include <stdlib.h>

DECOMP_SIZE_ASSERT(GolSoftwareRenderer, 0x58)
DECOMP_SIZE_ASSERT(GolSoftwareRenderer::RasterizerPipeline, 0x10)
DECOMP_SIZE_ASSERT(GolSoftwareRenderer::TriangleCommand, 0x14)
DECOMP_SIZE_ASSERT(GolSoftwareRenderer::TriangleCommand::SortKey, 0x04)

// FUNCTION: GOLDP 0x10029920 FOLDED
void NoopSpanRasterizer()
{
	// empty
}

static void NoopTriangleRasterizer(GolSoftwareRenderer*, D3DTLVERTEX*, D3DTLVERTEX*, D3DTLVERTEX*);

static LegoS32 __fastcall BucketCommandArrayBySortByte0(
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command,
	LegoS32 p_count
);

static LegoU8 __fastcall BucketCommandsBySortByte0(
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command
);

static LegoU8 GetSoftwareTextureSizeCode(const MipmapLevel* p_level)
{
	if (p_level == NULL || p_level->m_width != p_level->m_height) {
		return 0;
	}

	switch (p_level->m_width) {
	case 8:
		return 3;
	case 16:
		return 4;
	case 32:
		return 5;
	case 64:
		return 6;
	case 128:
		return 7;
	case 256:
		return 8;
	default:
		return 0;
	}
}

// STUB: GOLDP 0x10041000
static LegoU8 __fastcall BucketCommandsBySortByte3(
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::TriangleCommand* command;

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
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::TriangleCommand* command;

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
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::TriangleCommand* command;

	for (; p_command != NULL; p_buckets[bucketIndex] = command) {
		bucketIndex = p_command->m_sortKey.m_bytes[1];
		command = p_command;
		p_command = p_command->m_next;
		command->m_next = p_buckets[bucketIndex];
	}

	return static_cast<LegoU8>(bucketIndex);
}

// STUB: GOLDP 0x10041090
static LegoU8 __fastcall BucketCommandsBySortByte0(
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command
)
{
	LegoU32 bucketIndex = 0;
	GolSoftwareRenderer::TriangleCommand* command;

	for (; p_command != NULL; p_buckets[bucketIndex] = command) {
		bucketIndex = p_command->m_sortKey.m_bytes[0];
		command = p_command;
		p_command = p_command->m_next;
		command->m_next = p_buckets[bucketIndex];
	}

	return static_cast<LegoU8>(bucketIndex);
}

// FUNCTION: GOLDP 0x100410c0
static void SortCommandListBySortKey(GolSoftwareRenderer::TriangleCommand** p_head)
{
	GolSoftwareRenderer::TriangleCommand* buckets0[256];
	GolSoftwareRenderer::TriangleCommand* buckets1[256];

	::memset(buckets0, 0, sizeof(buckets0));
	BucketCommandsBySortByte0(buckets0, *p_head);

	::memset(buckets1, 0, sizeof(buckets1));
	GolSoftwareRenderer::TriangleCommand** bucket = &buckets0[255];
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

	*p_head = NULL;
	bucket = buckets1;
	i = 256;
	do {
		GolSoftwareRenderer::TriangleCommand* command = *bucket;
		if (command != NULL) {
			do {
				GolSoftwareRenderer::TriangleCommand* next = command->m_next;
				command->m_next = *p_head;
				*p_head = command;
				command = next;
			} while (command != NULL);
		}
		bucket++;
		i--;
	} while (i != 0);
}

// FUNCTION: GOLDP 0x100411b0
void GolSoftwareRenderer::SetupPipeline(RasterizerPipeline* p_buffer, GolMaterial* p_material, LegoU32 p_index)
{
	LegoU32 flags = p_material->GetFlags();
	LegoU32 rasterizerMode;

	GolD3DTexture* texture = reinterpret_cast<GolD3DTexture*>(p_material->GetTexture());

	if (texture) {
		m_currentMipmap = NULL;
		FUN_100330d0(this, &reinterpret_cast<GolD3DTexture*>(p_material->GetTexture())->GetMipmaps()[p_index]);
		rasterizerMode = c_flag0x2cBit8;

		if (flags & GolMaterial::c_flagBit19) {
			rasterizerMode = c_flag0x2cBit8 | c_flag0x2cBit9;
		}

		if (texture->GetTextureFlags() & GolTexture::c_textureFlagColorKeyed) {
			rasterizerMode |= c_flag0x2cBit1;
		}

		if (flags & GolMaterial::c_flagTransparent) {
			rasterizerMode |= c_flag0x2cBit2;
		}
		else if (!(flags & GolMaterial::c_flagDecal)) {
			if (flags & GolMaterial::c_flagAlphaBlend) {
				if ((p_material->m_srcBlend != 1) || (p_material->m_destBlend != 1)) {
					rasterizerMode |= c_flag0x2cBit2;
				}
				else {
					rasterizerMode |= c_flag0x2cBit4; // TODO: this is folded with a wrong but equivalent line
				}
			}
			else {
				if (flags & GolMaterial::c_flagModulate) {
					rasterizerMode |= c_flag0x2cBit3 | c_flag0x2cBit0;
				}
				else {
					rasterizerMode |= c_flag0x2cBit3;
				}
			}
		}
		else if (flags & GolMaterial::c_flagAlphaBlend) {
			rasterizerMode |= c_flag0x2cBit2;
		}
	}
	else {
		FUN_100330d0(this, NULL);
		// TODO: Can't get a `& 0xff` to appear
		rasterizerMode = flags & GolMaterial::c_flagGouraudShading ? c_flag0x2cBit0 : 0;
	}

	m_rasterizerFlags = rasterizerMode;

	if (m_pixelFormat == e_formatIndex8) {
		p_buffer->m_spanRasterizer = NULL;
		if (m_currentMipmap) {
			switch (m_currentMipmap->m_sizeLog2) {
			case MipmapLevel::c_size8:
				p_buffer->m_triangleRasterizer = FUN_10045520;
				break;
			case MipmapLevel::c_size16:
				p_buffer->m_triangleRasterizer = FUN_10044ce0;
				break;
			case MipmapLevel::c_size32:
				p_buffer->m_triangleRasterizer = FUN_100444a0;
				break;
			case MipmapLevel::c_size64:
				p_buffer->m_triangleRasterizer = FUN_10043c60;
				break;
			case MipmapLevel::c_size128:
				p_buffer->m_triangleRasterizer = FUN_10043420;
				break;
			case MipmapLevel::c_size256:
				p_buffer->m_triangleRasterizer = FUN_10042bd0;
				break;
			default:
				p_buffer->m_triangleRasterizer = FUN_10041a50;
			}
		}
		else {
			if (rasterizerMode & c_flag0x2cBit0) {
				p_buffer->m_triangleRasterizer = FUN_10042020;
			}
			else {
				p_buffer->m_triangleRasterizer = FUN_10041a60;
			}
		}
	}
	else {
		FUN_10032c80(this);
		p_buffer->m_triangleRasterizer = m_triangleRasterizer;
		p_buffer->m_spanRasterizer = m_spanRasterizer;
	}

	if (m_currentMipmap) {
		if (flags & GolMaterial::c_flagBit21) {
			if (m_currentMipmap->m_paletteData) {
				if ((rasterizerMode & c_flag0x2cBit1)) {
					if (m_spanRasterizer == FUN_10034980) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_100463b0;
					}
					else if (m_spanRasterizer == FUN_10035f00) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046340;
					}
					else if (m_spanRasterizer == FUN_10037480) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_100462d0;
					}
					else if (m_spanRasterizer == FUN_10038a00) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046260;
					}
					else if (m_spanRasterizer == FUN_10039f80) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_100461f0;
					}
					else if (m_spanRasterizer == FUN_1003b500) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046180;
					}
				}
				else {
					if (m_spanRasterizer == FUN_10034b10) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046120;
					}
					else if (m_spanRasterizer == FUN_10036090) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_100460c0;
					}
					else if (m_spanRasterizer == FUN_10037610) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046060;
					}
					else if (m_spanRasterizer == FUN_10038b90) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10046000;
					}
					else if (m_spanRasterizer == FUN_1003a110) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10045fa0;
					}
					else if (m_spanRasterizer == FUN_1003b690) {
						p_buffer->m_triangleRasterizer = FUN_10046420;
						p_buffer->m_spanRasterizer = FUN_10045f40;
					}
				}
			}
			else {
				if (m_spanRasterizer == FUN_10034db0) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045ef0;
				}
				else if (m_spanRasterizer == FUN_10036330) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045ea0;
				}
				else if (m_spanRasterizer == FUN_100378b0) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045e50;
				}
				else if (m_spanRasterizer == FUN_10038e30) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045e00;
				}
				else if (m_spanRasterizer == FUN_1003a3b0) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045db0;
				}
				else if (m_spanRasterizer == FUN_1003b930) {
					p_buffer->m_triangleRasterizer = FUN_10046420;
					p_buffer->m_spanRasterizer = FUN_10045d60;
				}
			}

			m_triangleRasterizer = p_buffer->m_triangleRasterizer;
			m_spanRasterizer = p_buffer->m_spanRasterizer;
		}
		else {
			if (!(rasterizerMode & c_flag0x2cBit9)) {
				if (m_spanRasterizer == FUN_10034b10) {
					p_buffer->m_triangleRasterizer = FUN_1004a6d0;
				}
				else if (m_spanRasterizer == FUN_10036090) {
					p_buffer->m_triangleRasterizer = FUN_10049e40;
				}
				else if (m_spanRasterizer == FUN_10037610) {
					p_buffer->m_triangleRasterizer = FUN_100495b0;
				}
				else if (m_spanRasterizer == FUN_10038b90) {
					p_buffer->m_triangleRasterizer = FUN_10048d20;
				}
				else if (m_spanRasterizer == FUN_1003a110) {
					p_buffer->m_triangleRasterizer = FUN_10048490;
				}
				else if (m_spanRasterizer == FUN_10038e30) {
					p_buffer->m_triangleRasterizer = FUN_10046ba0;
				}
				else if (m_spanRasterizer == FUN_1003a3b0) {
					p_buffer->m_triangleRasterizer = FUN_100473f0;
				}
				else if (m_spanRasterizer == FUN_1003b930) {
					p_buffer->m_triangleRasterizer = FUN_10047c40;
				}
			}
		}
	}

	p_buffer->m_texture = m_currentMipmap;
	if (m_currentMipmap) {
		p_buffer->m_unk0x0c = m_currentMipmap->m_paletteData;
	}
	else {
		p_buffer->m_unk0x0c = NULL;
	}
}

// FUNCTION: GOLDP 0x100416a0
GolSoftwareRenderer::GolSoftwareRenderer()
{
	DetectCPU();
	m_tlVertices = 0;
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
	m_currentMipmap = 0;
	m_rasterizerFlags = 0;
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

	m_nodes = new TriangleCommand[p_nodeCapacity];
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
void GolSoftwareRenderer::FUN_100417a0(TriangleCommand* p_cmds, LegoU32 p_count, LegoFloat p_arg3)
{
	while (p_count) {
		p_cmds->m_sortKey.m_value = p_arg3;
		p_cmds++;
		p_count--;
	}
}

// STUB: GOLDP 0x100417c0
void GolSoftwareRenderer::FUN_100417c0(TriangleCommand* p_cmds, LegoU32 p_count)
{
	while (p_count != 0) {
		LegoFloat sortKey = m_tlVertices[p_cmds->m_vertexIndex0].sz;

		if (sortKey < m_tlVertices[p_cmds->m_vertexIndex1].sz) {
			sortKey = m_tlVertices[p_cmds->m_vertexIndex1].sz;
		}
		if (sortKey < m_tlVertices[p_cmds->m_vertexIndex2].sz) {
			sortKey = m_tlVertices[p_cmds->m_vertexIndex2].sz;
		}

		p_cmds->m_sortKey.m_value = sortKey;
		p_cmds++;
		p_count--;
	}
}

// FUNCTION: GOLDP 0x10041830
void GolSoftwareRenderer::FUN_10041830(LegoS32 p_count, LegoBool p_sort)
{
	TriangleCommand* buckets0[256];
	TriangleCommand* buckets1[256];

	if (p_count == 0) {
		m_commandHead = NULL;
		return;
	}

	m_commandCount = p_count;

	if (p_sort) {
		::memset(buckets0, 0, sizeof(buckets0));
		BucketCommandArrayBySortByte0(buckets0, m_nodes + p_count - 1, p_count);

		::memset(buckets1, 0, sizeof(buckets1));
		TriangleCommand** bucket = &buckets0[255];
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

		TriangleCommand* head = NULL;
		bucket = buckets1;
		i = 256;
		do {
			TriangleCommand* command = *bucket;
			if (command != NULL) {
				do {
					TriangleCommand* next = command->m_next;
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
		TriangleCommand* command = m_nodes + 1;
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
	GolSoftwareRenderer::TriangleCommand** p_buckets,
	GolSoftwareRenderer::TriangleCommand* p_command,
	LegoS32 p_count
)
{
	LegoS32 result = p_count;
	LegoU32 bucketIndex = 0;

	do {
		bucketIndex = p_command->m_sortKey.m_bytes[0];
		GolSoftwareRenderer::TriangleCommand* command = p_command;
		p_command--;
		result--;
		command->m_next = p_buckets[bucketIndex];
		p_buckets[bucketIndex] = command;
	} while (result != 0);

	return result;
}

// STUB: GOLDP 0x100419b0
void GolSoftwareRenderer::DrawCommandList()
{
	TriangleCommand* command = m_commandHead;

	if (command != NULL) {
		do {
			RasterizerPipeline* rasterizer = command->m_rasterizer;
			m_spanRasterizer = rasterizer->m_spanRasterizer;
			m_currentMipmap = rasterizer->m_texture;
			rasterizer->m_triangleRasterizer(
				this,
				&m_tlVertices[command->m_vertexIndex0],
				&m_tlVertices[command->m_vertexIndex1],
				&m_tlVertices[command->m_vertexIndex2]
			);
			command = command->m_next;
		} while (command != NULL);
	}
}

// FUNCTION: GOLDP 0x10041a20
void GolSoftwareRenderer::FUN_10041a20(LegoBool p_sort)
{
	if (m_commandHead == NULL) {
		return;
	}

	if (p_sort) {
		SortCommandListBySortKey(&m_commandHead);
	}

	DrawCommandList();
}
