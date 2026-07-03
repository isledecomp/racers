#include "render/gold3drenderdevice.h"

#include "camera/golcamera.h"
#include "camera/golscenetransformnode.h"
#include "camera/goltransform.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golboundingshape.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golfontbase.h"
#include "golmath.h"
#include "golmodelbase.h"
#include "golmodelentity.h"
#include "golsurfaceformat.h"
#include "goltexture.h"
#include "image/golimage.h"
#include "mesh/gdbnormalvertexarray.h"
#include "mesh/golmodel.h"
#include "render/gold3drendersurface.h"
#include "render/goldrawdpstate.h"
#include "render/rectangle.h"
#include "scene/golbillboard.h"
#include "surface/gold3dtexture.h"
#include "surface/gold3dtexturepalette.h"

#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(GolD3DRenderDevice, 0xc8770)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::TextureFormat, 0x18)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::RasterizerPipelineSet, 0x10)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::VertexCacheEntry, 0x20)
DECOMP_SIZE_ASSERT(GolD3DRenderDevice::CommandVertex, 0x20)
DECOMP_SIZE_ASSERT(GolD3DRenderState::DrawCommand, 0x1c)
DECOMP_SIZE_ASSERT(ColorRGBA, 0x4)
DECOMP_SIZE_ASSERT(D3DTLVERTEX, 0x20)
DECOMP_SIZE_ASSERT(Rect, 0x10)

inline static LegoS32 ClampModelColorChannel(LegoS32 p_value, LegoS32 p_minimum)
{
	if (p_value < p_minimum) {
		p_value = p_minimum;
	}
	if (p_value > 0xff) {
		p_value = 0xff;
	}

	return p_value;
}

inline static LegoU32 BuildModelClipFlags(const GolD3DRenderDevice::VertexCacheEntry& p_vertex)
{
	const LegoU32 x = *reinterpret_cast<const LegoU32*>(&p_vertex.m_x);
	const LegoU32 y = *reinterpret_cast<const LegoU32*>(&p_vertex.m_y);
	const LegoU32 z = *reinterpret_cast<const LegoU32*>(&p_vertex.m_z);
	const LegoU32 w = *reinterpret_cast<const LegoU32*>(&p_vertex.m_w);

	LegoU32 lowFlags = (x >> 31) | ((y & 0x80000000) >> 29) | ((z & 0x80000000) >> 27);
	LegoU32 highFlags =
		(((w - x) & 0x80000000) >> 30) | (((w - y) & 0x80000000) >> 28) | (((w - z) & 0x80000000) >> 26);
	return lowFlags | (highFlags & ~(lowFlags << 1));
}

inline static LegoFloat GetClipDistance(
	const GolD3DRenderDevice::VertexCacheEntry& p_vertex,
	LegoU32 p_plane,
	LegoFloat p_farClip
)
{
	if (p_plane == 0x01) {
		return p_vertex.m_x;
	}
	else if (p_plane == 0x02) {
		return p_vertex.m_w - p_vertex.m_x;
	}
	else if (p_plane == 0x04) {
		return p_vertex.m_y;
	}
	else if (p_plane == 0x08) {
		return p_vertex.m_w - p_vertex.m_y;
	}
	else if (p_plane == 0x10) {
		return p_vertex.m_z;
	}

	return p_vertex.m_z - p_farClip;
}

inline static LegoU32 InterpolateColor(LegoU32 p_from, LegoU32 p_to, LegoFloat p_amount)
{
	LegoU32 result = 0;

	for (LegoU32 shift = 0; shift < 32; shift += 8) {
		LegoS32 from = (p_from >> shift) & 0xff;
		LegoS32 to = (p_to >> shift) & 0xff;
		LegoU32 value = from + static_cast<LegoS32>(static_cast<LegoFloat>(to - from) * p_amount);
		result |= (value & 0xff) << shift;
	}

	return result;
}

inline static void InterpolateClipVertex(
	const GolD3DRenderDevice::VertexCacheEntry& p_fromCache,
	const GolD3DRenderDevice::VertexCacheEntry& p_toCache,
	const D3DTLVERTEX& p_fromVertex,
	const D3DTLVERTEX& p_toVertex,
	LegoFloat p_amount,
	GolD3DRenderDevice::VertexCacheEntry& p_outputCache,
	D3DTLVERTEX& p_outputVertex
)
{
	p_outputCache.m_x = p_fromCache.m_x + (p_toCache.m_x - p_fromCache.m_x) * p_amount;
	p_outputCache.m_y = p_fromCache.m_y + (p_toCache.m_y - p_fromCache.m_y) * p_amount;
	p_outputCache.m_z = p_fromCache.m_z + (p_toCache.m_z - p_fromCache.m_z) * p_amount;
	p_outputCache.m_w = p_fromCache.m_w + (p_toCache.m_w - p_fromCache.m_w) * p_amount;
	p_outputCache.m_u = p_fromCache.m_u + (p_toCache.m_u - p_fromCache.m_u) * p_amount;
	p_outputCache.m_v = p_fromCache.m_v + (p_toCache.m_v - p_fromCache.m_v) * p_amount;
	p_outputCache.m_clipFlags = BuildModelClipFlags(p_outputCache);

	p_outputVertex.color = InterpolateColor(p_fromVertex.color, p_toVertex.color, p_amount);
	p_outputVertex.tu = p_fromVertex.tu + (p_toVertex.tu - p_fromVertex.tu) * p_amount;
	p_outputVertex.tv = p_fromVertex.tv + (p_toVertex.tv - p_fromVertex.tv) * p_amount;
}

inline static void ProjectClipVertex(
	const GolD3DRenderDevice::VertexCacheEntry& p_cache,
	const LegoFloat* p_viewportScale,
	D3DTLVERTEX& p_vertex
)
{
	p_vertex.rhw = 1.0f / p_cache.m_w;
	p_vertex.sx = p_cache.m_x * p_vertex.rhw * p_viewportScale[0] + p_viewportScale[2];
	p_vertex.sy = p_cache.m_y * p_vertex.rhw * p_viewportScale[1] + p_viewportScale[3];
	p_vertex.sz = p_cache.m_z * p_vertex.rhw;
}

inline static void ProjectClipVertexForPlane(
	GolD3DRenderDevice::VertexCacheEntry& p_cache,
	const LegoFloat* p_viewportScale,
	D3DTLVERTEX& p_vertex,
	LegoU32 p_plane,
	LegoFloat p_nearClip,
	LegoFloat p_farClip
)
{
	if (p_plane == 0x01) {
		p_cache.m_x = 0.0f;
	}
	else if (p_plane == 0x02) {
		p_cache.m_x = p_cache.m_w;
	}
	else if (p_plane == 0x04) {
		p_cache.m_y = 0.0f;
	}
	else if (p_plane == 0x08) {
		p_cache.m_y = p_cache.m_w;
	}
	else if (p_plane == 0x10) {
		p_cache.m_z = 0.0f;
		p_cache.m_w = p_nearClip;
	}
	else if (p_plane == 0x20) {
		p_cache.m_z = p_farClip;
		p_cache.m_w = p_farClip;
	}

	p_cache.m_clipFlags = BuildModelClipFlags(p_cache);
	p_vertex.rhw = 1.0f / p_cache.m_w;

	if (p_plane == 0x01) {
		p_vertex.sx = p_viewportScale[2];
		p_vertex.sy = p_cache.m_y * p_vertex.rhw * p_viewportScale[1] + p_viewportScale[3];
		p_vertex.sz = p_cache.m_z * p_vertex.rhw;
	}
	else if (p_plane == 0x02) {
		p_vertex.sx = p_viewportScale[0] + p_viewportScale[2];
		p_vertex.sy = p_cache.m_y * p_vertex.rhw * p_viewportScale[1] + p_viewportScale[3];
		p_vertex.sz = p_cache.m_z * p_vertex.rhw;
	}
	else if (p_plane == 0x04) {
		p_vertex.sx = p_cache.m_x * p_vertex.rhw * p_viewportScale[0] + p_viewportScale[2];
		p_vertex.sy = p_viewportScale[3];
		p_vertex.sz = p_cache.m_z * p_vertex.rhw;
	}
	else if (p_plane == 0x08) {
		p_vertex.sx = p_cache.m_x * p_vertex.rhw * p_viewportScale[0] + p_viewportScale[2];
		p_vertex.sy = p_viewportScale[1] + p_viewportScale[3];
		p_vertex.sz = p_cache.m_z * p_vertex.rhw;
	}
	else if (p_plane == 0x10) {
		p_vertex.sx = p_cache.m_x * p_vertex.rhw * p_viewportScale[0] + p_viewportScale[2];
		p_vertex.sy = p_cache.m_y * p_vertex.rhw * p_viewportScale[1] + p_viewportScale[3];
		p_vertex.sz = 0.0f;
	}
	else if (p_plane == 0x20) {
		p_vertex.sx = p_cache.m_x * p_vertex.rhw * p_viewportScale[0] + p_viewportScale[2];
		p_vertex.sy = p_cache.m_y * p_vertex.rhw * p_viewportScale[1] + p_viewportScale[3];
		p_vertex.sz = 1.0f;
	}
	else {
		ProjectClipVertex(p_cache, p_viewportScale, p_vertex);
	}
}

inline static LegoU32 AddIndexedClipVertex(
	GolD3DRenderDevice::VertexCacheEntry* p_cache,
	D3DTLVERTEX* p_vertices,
	const LegoFloat* p_viewportScale,
	LegoU32 p_fromIndex,
	LegoU32 p_toIndex,
	LegoFloat p_amount,
	LegoU32 p_plane,
	LegoFloat p_nearClip,
	LegoFloat p_farClip,
	LegoU32& p_nextClipIndex,
	LegoU32& p_nextVertexIndex
)
{
	GolD3DRenderDevice::VertexCacheEntry& outputCache = p_cache[p_nextClipIndex];
	D3DTLVERTEX& outputVertex = p_vertices[p_nextVertexIndex];
	const GolD3DRenderDevice::VertexCacheEntry& fromCache = p_cache[p_fromIndex];
	const GolD3DRenderDevice::VertexCacheEntry& toCache = p_cache[p_toIndex];
	const D3DTLVERTEX& fromVertex = p_vertices[fromCache.m_unk0x10];
	const D3DTLVERTEX& toVertex = p_vertices[toCache.m_unk0x10];
	LegoU32 outputIndex = p_nextClipIndex;

	p_nextClipIndex++;
	InterpolateClipVertex(fromCache, toCache, fromVertex, toVertex, p_amount, outputCache, outputVertex);
	outputCache.m_unk0x10 = p_nextVertexIndex;
	ProjectClipVertexForPlane(outputCache, p_viewportScale, outputVertex, p_plane, p_nearClip, p_farClip);
	p_nextVertexIndex++;

	return outputIndex;
}

inline static LegoFloat ComputeScreenArea(
	const D3DTLVERTEX& p_vertex0,
	const D3DTLVERTEX& p_vertex1,
	const D3DTLVERTEX& p_vertex2
)
{
	return ((p_vertex2.sy - p_vertex1.sy) * (p_vertex0.sx - p_vertex1.sx)) -
		   ((p_vertex0.sy - p_vertex1.sy) * (p_vertex2.sx - p_vertex1.sx));
}

// GLOBAL: GOLDP 0x10056540
const D3DCMPFUNC g_d3dCmpFuncLookup[] = {
	D3DCMP_ALWAYS,
	D3DCMP_EQUAL,
	D3DCMP_GREATER,
	D3DCMP_GREATEREQUAL,
	D3DCMP_LESS,
	D3DCMP_LESSEQUAL,
	D3DCMP_NEVER,
	D3DCMP_NOTEQUAL,
};

// GLOBAL: GOLDP 0x10056560
LegoU32 g_d3dBlendOpMasks[11] = {
	D3DPBLENDCAPS_ZERO,
	D3DPBLENDCAPS_ONE,
	D3DPBLENDCAPS_SRCCOLOR,
	D3DPBLENDCAPS_DESTCOLOR,
	D3DPBLENDCAPS_INVSRCCOLOR,
	D3DPBLENDCAPS_INVDESTCOLOR,
	D3DPBLENDCAPS_SRCALPHA,
	D3DPBLENDCAPS_DESTALPHA,
	D3DPBLENDCAPS_INVSRCALPHA,
	D3DPBLENDCAPS_INVDESTALPHA,
	D3DPBLENDCAPS_SRCALPHASAT,
};

// GLOBAL: GOLDP 0x1005658c
D3DBLEND g_d3dBlendOps[11] = {
	D3DBLEND_ZERO,
	D3DBLEND_ONE,
	D3DBLEND_SRCCOLOR,
	D3DBLEND_DESTCOLOR,
	D3DBLEND_INVSRCCOLOR,
	D3DBLEND_INVDESTCOLOR,
	D3DBLEND_SRCALPHA,
	D3DBLEND_DESTALPHA,
	D3DBLEND_INVSRCALPHA,
	D3DBLEND_INVDESTALPHA,
	D3DBLEND_SRCALPHASAT,
};

// GLOBAL: GOLDP 0x1005c8a8
DrawTriangleFunction GolD3DRenderDevice::g_drawTriangleLitTable[8] = {
	&GolD3DRenderDevice::FUN_10011e60,
	&GolD3DRenderDevice::FUN_10011ed0,
	&GolD3DRenderDevice::FUN_10012030,
	&GolD3DRenderDevice::FUN_100121e0,
	&GolD3DRenderDevice::FUN_100123e0,
	&GolD3DRenderDevice::FUN_10012640,
	&GolD3DRenderDevice::FUN_100128f0,
	&GolD3DRenderDevice::FUN_10012bf0,
};

// GLOBAL: GOLDP 0x1005c8c8
DrawTriangleFunction GolD3DRenderDevice::g_drawTriangleTable[64] = {
	&GolD3DRenderDevice::FUN_1000c160, &GolD3DRenderDevice::FUN_1000c2d0, &GolD3DRenderDevice::FUN_1000bfb0,
	&GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000be20, &GolD3DRenderDevice::FUN_1000c2d0,
	&GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000caf0,
	&GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880, &GolD3DRenderDevice::FUN_1000cf90,
	&GolD3DRenderDevice::FUN_1000c630, &GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880,
	&GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000baa0, &GolD3DRenderDevice::FUN_1000bc40,
	&GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470, &GolD3DRenderDevice::FUN_1000b8e0,
	&GolD3DRenderDevice::FUN_1000c2d0, &GolD3DRenderDevice::FUN_1000bfb0, &GolD3DRenderDevice::FUN_1000c470,
	&GolD3DRenderDevice::FUN_1000caf0, &GolD3DRenderDevice::FUN_1000cd20, &GolD3DRenderDevice::FUN_1000c880,
	&GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000c630, &GolD3DRenderDevice::FUN_1000cd20,
	&GolD3DRenderDevice::FUN_1000c880, &GolD3DRenderDevice::FUN_1000cf90, &GolD3DRenderDevice::FUN_1000e010,
	&GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010,
	&GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e790,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e310, &GolD3DRenderDevice::FUN_1000e310,
	&GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e540,
	&GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e010, &GolD3DRenderDevice::FUN_1000e790,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e180, &GolD3DRenderDevice::FUN_1000e180,
	&GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e790, &GolD3DRenderDevice::FUN_1000e310,
	&GolD3DRenderDevice::FUN_1000e310, &GolD3DRenderDevice::FUN_1000e930, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e540, &GolD3DRenderDevice::FUN_1000e930,
	&GolD3DRenderDevice::FUN_1000e930,
};

// FUNCTION: GOLDP 0x100078e0
GolD3DRenderDevice::GolD3DRenderDevice()
{
	Reset();
}

// FUNCTION: GOLDP 0x10007980
GolD3DRenderDevice::~GolD3DRenderDevice()
{
	Shutdown();
}

// FUNCTION: GOLDP 0x10007a00
void GolD3DRenderDevice::Reset()
{
	LegoU32 i;

	m_drawState = NULL;
	m_d3dDevice = NULL;
	::memset(&m_d3dDeviceDesc, 0, sizeof(m_d3dDeviceDesc));
	m_d3dDeviceDesc.dwSize = sizeof(m_d3dDeviceDesc);
	m_d3dViewport = NULL;

	::memset(&m_viewportParams, 0, sizeof(m_viewportParams));
	m_viewportParams.dwSize = sizeof(m_viewportParams);
	m_viewportParams.dwX = 0;
	m_viewportParams.dwY = 0;
	m_viewportParams.dwWidth = 640;
	m_viewportParams.dwHeight = 480;
	m_viewportParams.dvClipX = -1.0f;
	m_viewportParams.dvClipY = -0.75f;
	m_viewportParams.dvClipWidth = 2.0f;
	m_viewportParams.dvClipHeight = 1.5f;
	m_viewportParams.dvMinZ = 0.0f;
	m_viewportParams.dvMaxZ = 1.0f;

	::memset(&m_materialParams, 0, sizeof(m_materialParams));
	m_materialParams.dwSize = sizeof(m_materialParams);
	m_materialParams.dwRampSize = 1;
	m_backgroundMaterial = NULL;
	m_backgroundMaterialHandle = 0;
	m_clearColor.m_alp = 0;
	m_clearColor.m_red = 0;
	m_clearColor.m_grn = 0;
	m_clearColor.m_blu = 0;
	m_clearPixelValue = 0;
	m_primaryRenderTarget = NULL;
	m_renderTargetInfo = NULL;
	m_renderSurfaces = NULL;

	::memset(m_unk0x348, 0, 0xcc8 - 0x348);
	::memset(m_unk0xc38ec, 0, sizeof(m_unk0xc38ec));
	::memset(m_unk0xc428c, 0, sizeof(m_unk0xc428c));
	m_unk0xc86f0 = NULL;
	m_unk0xc86f4 = 0;
	m_unk0xc86f8 = 0;
	m_unk0xc83ac = 0;
	m_unk0xc83b0 = 0;
	m_currentScale = 1.0f;
	::memset(&m_unk0xc83b4, 0, sizeof(m_unk0xc83b4));
	m_unk0xc83c4 = 0;
	m_flatDepth = 0.0f;
	m_unk0xc3848 = 0;
	m_unk0xc384c = 0;
	m_sourcePositions = 0;
	m_sourceTexCoords = 0;
	m_sourceColors = 0;
	m_sourceIndices = 0;
	m_unk0xc83e4 = 0;
	m_unk0xc83e8 = 0;
	m_colorKeyEnabled = 0;
	m_unk0xc83ec = 0;
	m_applyMaterialFn = &GolD3DRenderDevice::ApplyMaterialHw;
	m_uvOffsetEnabled = 0;
	m_uvOffsetU = 0;
	m_uvOffsetV = 0;
	m_currentTexture = 0;
	m_activeMaterialFlags = 0;
	m_forcedMaterialFlags = 0;
	m_alpha = 255;
	m_unk0xc8568 = 0;
	m_unk0xc83f8 = 0;
	m_unk0xc83fc = -1;
	::memset(m_viewportMetrics, 0, sizeof(m_viewportMetrics));
	m_viewProjectionMatrix = 0;
	m_viewScreenProjectionMatrix = 0;
	m_currentMatrix = 0;
	m_unk0xc851c = 0;
	m_currentSceneNode = 0;
	m_renderState = 0;
	m_stateBeginPending = 0;
	::memset(&m_drawCommand, 0, sizeof(m_drawCommand));
	::memset(&m_materialCommand, 0, 0xc8568 - 0xc854c);
	m_drawCommand.m_renderer = this;
	m_drawCommand.m_vertices = m_unk0xc428c;
	m_drawCommand.m_material = NULL;
	m_materialCommand.m_renderer = this;
	m_materialCommand.m_vertices = m_unk0xc428c;
	m_modelMatrix.m_m[0][0] = 1.0f;
	m_unk0xc8450.m_m[0][0] = 1.0f;
	m_modelMatrix.m_m[0][1] = 0.0f;
	m_unk0xc8450.m_m[0][1] = 0.0f;
	m_modelMatrix.m_m[0][2] = 0.0f;
	m_unk0xc8450.m_m[0][2] = 0.0f;
	m_modelMatrix.m_m[0][3] = 0.0f;
	m_unk0xc8450.m_m[0][3] = 0.0f;
	m_modelMatrix.m_m[1][0] = 0.0f;
	m_unk0xc8450.m_m[1][0] = 0.0f;
	m_modelMatrix.m_m[1][1] = 1.0f;
	m_unk0xc8450.m_m[1][1] = 1.0f;
	m_modelMatrix.m_m[1][2] = 0.0f;
	m_unk0xc8450.m_m[1][2] = 0.0f;
	m_modelMatrix.m_m[1][3] = 0.0f;
	m_unk0xc8450.m_m[1][3] = 0.0f;
	m_modelMatrix.m_m[2][0] = 0.0f;
	m_unk0xc8450.m_m[2][0] = 0.0f;
	m_modelMatrix.m_m[2][1] = 0.0f;
	m_unk0xc8450.m_m[2][1] = 0.0f;
	m_modelMatrix.m_m[2][2] = 1.0f;
	m_unk0xc8450.m_m[2][2] = 1.0f;
	m_modelMatrix.m_m[2][3] = 0.0f;
	m_unk0xc8450.m_m[2][3] = 0.0f;
	m_modelMatrix.m_m[3][0] = 0.0f;
	m_unk0xc8450.m_m[3][0] = 0.0f;
	m_modelMatrix.m_m[3][1] = 0.0f;
	m_unk0xc8450.m_m[3][1] = 0.0f;
	m_modelMatrix.m_m[3][2] = 0.0f;
	m_unk0xc8450.m_m[3][2] = 0.0f;
	m_modelMatrix.m_m[3][3] = 1.0f;
	m_unk0xc8450.m_m[3][3] = 1.0f;
	m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000c630;
	m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;

	for (i = 0; i < (0xcc8 - 0x348) / sizeof(*m_unk0x348); i++) {
		m_unk0x348[i].color = 0xffffffff;
		m_unk0x348[i].specular = 0xffffffff;
	}

	for (i = 0; i < sizeOfArray(m_unk0xc53a0); i++) {
		m_unk0xc53a0[i].color = 0xffffffff;
		m_unk0xc53a0[i].specular = 0xffffffff;
	}

	m_defaultMipmapCount = 0;
}

// FUNCTION: GOLDP 0x10007d80
GolCommonDrawState* GolD3DRenderDevice::GetDrawState()
{
	return m_drawState;
}

// FUNCTION: GOLDP 0x10007d90
LegoS32 GolD3DRenderDevice::Initialize(GolDrawDPState* p_drawState, GolRenderTarget* p_parg2, LegoU32 p_flags)
{
	if (m_flags & c_flagCreated) {
		Shutdown();
	}

	m_drawState = p_drawState;
	m_primaryRenderTarget = p_parg2;
	m_renderTargetInfo = p_parg2;
	m_currentCamera = NULL;
	p_drawState->AddRenderer(this);
	m_flags |= c_flagCreated | c_flagZBufferActive;
	m_viewportParams.dwX = 0;
	m_viewportParams.dwY = 0;
	m_viewportParams.dwWidth = m_renderTargetInfo->m_width;
	m_viewportParams.dwHeight = m_renderTargetInfo->m_height;

	LegoS32 result = CreateRenderer(p_flags);
	if (result != 0) {
		return result;
	}

	ClearLights();
	return 0;
}

// FUNCTION: GOLDP 0x10007e20
LegoS32 GolD3DRenderDevice::CreateRenderer(LegoU32 p_flags)
{
	GolSurfaceFormat swTextureFormat;
	LegoU32 forceSoftware;
	LegoChar errorMessage[64];
	D3DDEVICEDESC helCaps;

	m_flags = c_flagCreated | c_flagZBufferActive;
	if (p_flags & GolDrawState::c_flagPreferAlphaTest) {
		m_flags |= c_flagBit20;
	}
	if (p_flags & GolDrawState::c_flagZBuffer) {
		m_flags |= c_flagZBuffer;
	}

	forceSoftware = p_flags & GolDrawState::c_flagForceSoftware;
	if (!forceSoftware) {
		m_unk0xc384c = 0;
		m_unk0xc83c4 = 0;
		m_applyMaterialFn = &GolD3DRenderDevice::ApplyMaterialHw;

		if (m_flags & c_flagZBuffer && !m_drawState->SupportsZBufferlessHsr()) {
			LegoS32 r = m_depthBuffer.Create(m_drawState, m_primaryRenderTarget);
			if (r != 0) {
				return r;
			}
		}

		HRESULT hresult =
			m_drawState->m_d3d3
				->CreateDevice(m_drawState->m_deviceGuid, m_primaryRenderTarget->m_renderSurface, &m_d3dDevice, NULL);
		if (hresult != D3D_OK) {
			sprintf(errorMessage, "Unable to create Direct3D device\nerror %x", hresult);
			GOL_FATALERROR_MESSAGE(errorMessage);
		}

		m_countTextureFormats = 0;
		m_d3dDevice->EnumTextureFormats(CountTextureFormatsCallback, &m_countTextureFormats);
		if (m_countTextureFormats != 0) {
			LegoU32 i;

			::memset(&helCaps, 0, sizeof(helCaps));
			helCaps.dwSize = sizeof(helCaps);
			if (m_d3dDevice->GetCaps(&m_d3dDeviceDesc, &helCaps) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to query device capabilities");
			}

			if (!(m_d3dDeviceDesc.dwFlags & D3DDD_TRICAPS)) {
				::memcpy(&m_d3dDeviceDesc, &helCaps, sizeof(helCaps));
			}

			for (i = 0; i < sizeOfArray(m_srcBlendOps); i++) {
				if (m_d3dDeviceDesc.dpcTriCaps.dwSrcBlendCaps & g_d3dBlendOpMasks[i]) {
					m_srcBlendOps[i] = g_d3dBlendOps[i];
				}
				else {
					m_srcBlendOps[i] = D3DBLEND_SRCALPHA;
				}
			}

			for (i = 0; i < sizeOfArray(m_srcBlendOps); i++) {
				if (m_d3dDeviceDesc.dpcTriCaps.dwDestBlendCaps & g_d3dBlendOpMasks[i]) {
					m_destBlendOps[i] = g_d3dBlendOps[i];
				}
				else {
					m_destBlendOps[i] = D3DBLEND_INVSRCALPHA;
				}
			}

			if ((m_flags & c_flagBit20) && (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER)) {
				m_flags &= ~c_flagColorKeyAlphaBlend;
				m_flags |= c_flagColorKeyAlphaTest;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_TRANSPARENCY) {
				m_flags &= ~(c_flagColorKeyAlphaBlend | c_flagColorKeyAlphaTest);
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwAlphaCmpCaps & D3DPCMPCAPS_GREATER) {
				m_flags &= ~c_flagColorKeyAlphaBlend;
				m_flags |= c_flagColorKeyAlphaTest;
			}
			else {
				m_flags &= ~c_flagColorKeyAlphaTest;
				m_flags |= c_flagColorKeyAlphaBlend;
			}

			if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATBLEND) {
				m_flags &= ~c_flagBit12;
				m_flags |= c_flagBit11;
			}
			else if (m_d3dDeviceDesc.dpcTriCaps.dwShadeCaps & D3DPSHADECAPS_ALPHAFLATSTIPPLED) {
				m_flags |= c_flagBit11 | c_flagBit12;
			}
			else {
				m_flags &= ~c_flagBit12;
			}

			if (m_drawState->m_d3d3->CreateViewport(&m_d3dViewport, NULL) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to create viewport");
			}

			if (m_d3dDevice->AddViewport(m_d3dViewport) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to add viewport");
			}

			if (m_d3dViewport->SetViewport2(&m_viewportParams) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to configure viewport");
			}

			if (m_d3dDevice->SetCurrentViewport(m_d3dViewport) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to set viewport");
			}

			if (m_drawState->m_d3d3->CreateMaterial(&m_backgroundMaterial, NULL) != D3D_OK) {
				GOL_FATALERROR_MESSAGE("Unable to create background material");
			}

			m_textureFormats = new GolSurfaceFormat[m_countTextureFormats];
			if (m_textureFormats == NULL) {
				GOL_FATALERROR(c_golErrorOutOfMemory);
			}

			m_unk0x2c = 0;
			m_d3dDevice->EnumTextureFormats(EnumerateTextureFormatsCallback, this);
			m_paletteMode = 2;
			goto rendererCreated;
		}

		m_d3dDevice->Release();
		m_d3dDevice = NULL;
	}

	m_flags &= ~c_flagZBuffer;
	m_flags |= c_flagBlackColorKey | c_flagSoftwareRenderer;
	m_unk0xc384c = -1;
	m_unk0xc83c4 = 1;
	m_applyMaterialFn = &GolD3DRenderDevice::ApplyMaterialSw;
	::memcpy(&swTextureFormat, &m_primaryRenderTarget->m_textureFormat, sizeof(swTextureFormat));

	GolSoftwareRenderer::PixelFormat swPixelFormat;
	if (swTextureFormat.m_bitsPerPixel == 8) {
		swPixelFormat = GolSoftwareRenderer::PixelFormat::e_formatIndex8;
		if (m_drawState->m_flags & GolDrawState::c_flagTexturePalettes) {
			m_paletteMode = 1;
		}
		else {
			m_paletteMode = 0;
		}
	}
	else {
		swPixelFormat = swTextureFormat.GetGreenBitCount() == 6 ? GolSoftwareRenderer::PixelFormat::e_format565
																: GolSoftwareRenderer::PixelFormat::e_format555;
		m_paletteMode = 2;
	}

	GolD3DTexturePalette::SetTextureFormat(swTextureFormat);
	if (!m_softwareRenderer.Initialize(swPixelFormat, 16000)) {
		GOL_FATALERROR_MESSAGE("Unable to initialize software renderer");
	}

	m_softwareRenderer.SetTlVertices(m_unk0x348);
	FUN_1000b4a0();
	::memset(&m_unk0xc83b4, 0, sizeof(m_unk0xc83b4));

rendererCreated:
	SetClearColor(m_clearColor);
	FUN_100082e0();
	if (m_currentCamera != NULL) {
		SetCamera(m_currentCamera);
	}

	m_unk0x2d4.Create(*this);
	for (GolD3DRenderSurface* surface = m_renderSurfaces; surface != NULL; surface = surface->m_next) {
		surface->FUN_100136a0(this);
	}

	GolRenderDevice::RestoreResources();
	return 0;
}

// FUNCTION: GOLDP 0x100082e0
void GolD3DRenderDevice::FUN_100082e0()
{
	m_colorKeyEnabled = FALSE;
	m_unk0xc83ec = 0;
	m_unk0xc83e8 = FALSE;
	if (m_flags & c_flagColorOverride) {
		m_unk0xc83fc = ARGBU32(m_alpha, m_colorOverride.m_red, m_colorOverride.m_grn, m_colorOverride.m_blu);
	}
	else {
		m_unk0xc83f8 = FALSE;
	}

	m_activeAlphaFunc = 0;
	m_activeAlphaRef = 0;
	m_activeSrcBlend = 6;
	m_activeDestBlend = 8;
	m_activeMaterialFlags = GolMaterial::c_flagGouraudShading | GolMaterial::c_flagDecal |
							GolMaterial::c_flagNoAlphaTest | GolMaterial::c_flagNoAlphaBlend |
							GolMaterial::c_flagLinearFilter | GolMaterial::c_flagNoTransparency |
							GolMaterial::c_flagWrap | GolMaterial::c_flagBit20 | GolMaterial::c_flagBit22;
	FUN_10012f50();

	if (m_flags & c_flagSoftwareRenderer) {
		return;
	}

	m_d3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_TEXTUREPERSPECTIVE,
		m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_SUBPIXEL,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_SUBPIXEL) && m_drawState->IsHwAccelerated()
	);

	m_d3dDevice->SetRenderState(
		D3DRENDERSTATE_DITHERENABLE,
		(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->IsHwAccelerated()
	);

	m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
	if ((m_drawState->m_flags & GolDrawState::c_flagAntialias) && m_drawState->IsHwAccelerated()) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_SORTINDEPENDENT);
	}
	else {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ANTIALIAS, D3DANTIALIAS_NONE);
	}

	if ((m_d3dDeviceDesc.dpcTriCaps.dwTextureFilterCaps & D3DPTFILTERCAPS_LINEAR) && m_drawState->IsHwAccelerated()) {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	}
	else {
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
	}

	if (m_flags & c_flagZBuffer) {
		if (m_drawState->SupportsWBuffer()) {
			m_flags |= c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_flags &= ~c_flagBit13;
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
		m_flags |= c_flagZBufferActive;
	}
	else {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	}

	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
	m_d3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, g_d3dCmpFuncLookup[0]);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 0);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, m_srcBlendOps[m_activeSrcBlend]);
	m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, m_destBlendOps[m_activeDestBlend]);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

// FUNCTION: GOLDP 0x10008680
void GolD3DRenderDevice::ReleaseResources()
{
	GolRenderDevice::ReleaseResources();

	for (GolD3DRenderSurface* surface = m_renderSurfaces; surface != NULL; surface = surface->m_next) {
		surface->ReleaseResources();
	}

	m_unk0x2d4.Destroy();

	if (m_flags & c_flagSoftwareRenderer) {
		m_softwareRenderer.~GolSoftwareRenderer();
	}

	if (m_depthBuffer.GetPixelFlags() & GolSurface::c_lockRequestRead) {
		m_depthBuffer.Release();
	}

	if (m_d3dViewport != NULL) {
		m_d3dViewport->Release();
		m_d3dViewport = NULL;
	}

	if (m_d3dDevice != NULL) {
		if (m_backgroundMaterial != NULL) {
			m_backgroundMaterial->Release();
			m_backgroundMaterial = NULL;
			m_backgroundMaterialHandle = 0;
		}

		m_d3dDevice->Release();
		m_d3dDevice = NULL;
	}

	::memset(&m_d3dDeviceDesc, 0, sizeof(m_d3dDeviceDesc));
	m_d3dDeviceDesc.dwSize = sizeof(m_d3dDeviceDesc);
}

// FUNCTION: GOLDP 0x10008740
void GolD3DRenderDevice::Shutdown()
{
	if (m_currentCamera != NULL) {
		m_currentCamera->AttachToRenderer(NULL);
		m_currentCamera = NULL;
	}

	GolRenderDevice::Destroy();
	ReleaseResources();

	GolD3DRenderSurface* surface = m_renderSurfaces;
	while (surface != NULL) {
		GolD3DRenderSurface* next = surface->m_next;
		surface->Destroy();
		delete surface;
		surface = next;
	}

	if (m_drawState != NULL) {
		m_drawState->RemoveRenderer(this);
	}

	Reset();
	m_flags = 0;
}

// FUNCTION: GOLDP 0x100087b0
void GolD3DRenderDevice::SetCamera(GolCamera* p_lens)
{
	if (m_currentCamera != NULL) {
		m_currentCamera->AttachToRenderer(NULL);
	}

	m_currentCamera = p_lens;
	p_lens->AttachToRenderer(this);
}

// FUNCTION: GOLDP 0x100087e0
void GolD3DRenderDevice::ApplyCamera()
{
	GolCamera* lens = m_currentCamera;
	lens->UpdateMatrices();
	lens->BuildD3DViewport(&m_viewportParams);

	if (!(m_flags & c_flagSoftwareRenderer) && m_d3dViewport->SetViewport2(&m_viewportParams) != D3D_OK) {
		GOL_FATALERROR_MESSAGE("Unable to set viewport");
	}

	m_viewProjectionMatrix = &lens->m_cameraMatrices.m_viewProjection;
	m_viewScreenProjectionMatrix = &lens->m_cameraMatrices.m_viewScreenProjection;
	::memcpy(&m_viewFrustum, &lens->m_viewFrustum, sizeof(m_viewFrustum));
	::memcpy(m_viewportMetrics, &lens->m_cameraMatrices.m_viewportWidth, sizeof(m_viewportMetrics));
}

// FUNCTION: GOLDP 0x10008880
void GolD3DRenderDevice::FUN_10008880(GolWorldEntity* p_model, LegoU32 p_lodIndex)
{
	GolModelEntity* canoe = static_cast<GolModelEntity*>(p_model);
	m_currentSceneNode = canoe->GetSceneNode(p_lodIndex);
	if (m_currentSceneNode != NULL) {
		canoe->ApplyPartAnimation(p_lodIndex);
		if (m_unk0xc83e4) {
			static_cast<GolSceneTransformNode*>(m_currentSceneNode)
				->UpdateWorldViewMatrices(m_unk0xc8498[0], m_modelMatrix, *m_viewProjectionMatrix);
		}
		else {
			static_cast<GolSceneTransformNode*>(m_currentSceneNode)
				->UpdateWorldViewMatrices(m_unk0xc84d8, m_modelMatrix, *m_viewScreenProjectionMatrix);
		}

		if (m_unk0xc8568) {
			m_currentSceneNode->UpdateWorldMatrices(m_unk0xc8450);
		}
	}
}

// FUNCTION: GOLDP 0x10008910
void GolD3DRenderDevice::DrawModelEntity(GolWorldEntity* p_model)
{
	GolWorldEntity::ResultStruct result;
	p_model->ComputeVisibility(m_viewFrustum, &result);
	if (!result.m_visibility) {
		return;
	}

	GolMatrix4* modelMatrix = &m_modelMatrix;
	GolModelEntity* canoe = static_cast<GolModelEntity*>(p_model);
	canoe->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = canoe->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	if (result.m_visibility == 1) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
	}
	else {
		m_unk0xc83e4 = FALSE;
		m_currentMatrix = &m_unk0xc84d8;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewScreenProjectionMatrix, &m_unk0xc84d8);
	}

	GolModel* model = static_cast<GolModel*>(canoe->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	if (m_unk0xc8568 != (vertexType == 2 || vertexType == 3)) {
		m_unk0xc8568 = (vertexType == 2 || vertexType == 3);
		FUN_10012f50();
	}

	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = canoe->GetMaterialTable(result.m_lodIndex);
	FUN_10008880(p_model, result.m_lodIndex);
	model->Draw(this, materialTable);
}

// FUNCTION: GOLDP 0x10008a50
void GolD3DRenderDevice::DrawModelEntityLodMirrored(GolModelEntity* p_model, undefined4 p_lodIndex)
{
	GolWorldEntity::ResultStruct result;
	GolMatrix4* modelMatrix;

	if (p_lodIndex == static_cast<undefined4>(-1)) {
		p_model->SelectLod(m_viewFrustum.m_position, &result);
		if (!result.m_visibility) {
			return;
		}
	}
	else {
		result.m_lodIndex = p_lodIndex;
	}

	GolVec3 center;
	LegoFloat radius;
	p_model->GetModelBounds(result.m_lodIndex, &center, &radius);
	center.m_z = -center.m_z;
	result.m_visibility = m_viewFrustum.ClassifySphere(center, radius);
	if (!result.m_visibility) {
		return;
	}

	modelMatrix = &m_modelMatrix;
	p_model->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = p_model->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	m_modelMatrix.m_m[0][2] = -m_modelMatrix.m_m[0][2];
	m_modelMatrix.m_m[1][2] = -m_modelMatrix.m_m[1][2];
	m_modelMatrix.m_m[2][2] = -m_modelMatrix.m_m[2][2];
	m_modelMatrix.m_m[3][2] = -m_modelMatrix.m_m[3][2];
	m_forcedMaterialFlags = GolMaterial::c_flagRotateVertices;
	FUN_10012f50();

	if (result.m_visibility == 1) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
	}
	else {
		m_unk0xc83e4 = FALSE;
		m_currentMatrix = &m_unk0xc84d8;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewScreenProjectionMatrix, &m_unk0xc84d8);
	}

	GolModel* model = static_cast<GolModel*>(p_model->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	if (m_unk0xc8568 != (vertexType == 2 || vertexType == 3)) {
		m_unk0xc8568 = (vertexType == 2 || vertexType == 3);
		FUN_10012f50();
	}

	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = p_model->GetMaterialTable(result.m_lodIndex);
	FUN_10008880(p_model, result.m_lodIndex);
	model->Draw(this, materialTable);

	m_forcedMaterialFlags = 0;
	FUN_10012f50();
}

// FUNCTION: GOLDP 0x10008c30
void GolD3DRenderDevice::DrawModelEntityLod(GolModelEntity* p_model, undefined4 p_lodIndex)
{
	GolWorldEntity::ResultStruct result;
	GolMatrix4* modelMatrix;

	if (p_lodIndex == static_cast<undefined4>(-1)) {
		p_model->SelectLod(m_viewFrustum.m_position, &result);
		if (!result.m_visibility) {
			return;
		}
	}
	else {
		result.m_lodIndex = p_lodIndex;
	}

	GolVec3 center;
	LegoFloat radius;
	p_model->GetModelBounds(result.m_lodIndex, &center, &radius);
	center.m_z = 0.0f;
	result.m_visibility = m_viewFrustum.ClassifySphere(center, radius);
	if (!result.m_visibility) {
		return;
	}

	modelMatrix = &m_modelMatrix;
	p_model->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = p_model->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	m_modelMatrix.m_m[0][2] = 0.0f;
	m_modelMatrix.m_m[1][2] = 0.0f;
	m_modelMatrix.m_m[2][2] = 0.0f;
	m_modelMatrix.m_m[3][2] = 0.0f;

	if (result.m_visibility == 1) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
	}
	else {
		m_unk0xc83e4 = FALSE;
		m_currentMatrix = &m_unk0xc84d8;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewScreenProjectionMatrix, &m_unk0xc84d8);
	}

	GolModel* model = static_cast<GolModel*>(p_model->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	if (m_unk0xc8568 != (vertexType == 2 || vertexType == 3)) {
		m_unk0xc8568 = (vertexType == 2 || vertexType == 3);
		FUN_10012f50();
	}

	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = p_model->GetMaterialTable(result.m_lodIndex);
	FUN_10008880(p_model, result.m_lodIndex);
	model->Draw(this, materialTable);
}

// FUNCTION: GOLDP 0x10008dd0
void GolD3DRenderDevice::DrawModelEntityWithState(
	GolModelEntity* p_model,
	GolD3DRenderState* p_renderState,
	undefined4 p_lodIndex
)
{
	GolWorldEntity::ResultStruct result;
	if (p_lodIndex == static_cast<undefined4>(-1)) {
		p_model->ComputeVisibility(m_viewFrustum, &result);
		if (!result.m_visibility) {
			return;
		}
	}
	else {
		result.m_lodIndex = p_lodIndex;
	}

	GolMatrix4* modelMatrix = &m_modelMatrix;
	m_renderState = p_renderState;
	m_drawCommand.m_model = p_model;
	m_materialCommand.m_model = p_model;
	p_model->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = p_model->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	if (!m_stateBeginPending) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
	}
	else {
		p_renderState->Begin(this, p_model, result.m_lodIndex);
	}

	m_currentMatrix = modelMatrix;
	GolModel* model = static_cast<GolModel*>(p_model->GetModel(result.m_lodIndex));
	LegoU16 vertexType = model->GetVertexArray()->GetVertexType();
	m_unk0xc8568 = vertexType == GolModel::e_vertexType2 || vertexType == GolModel::e_vertexType3;
	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
		m_currentMatrix = &m_unk0xc8450;
		m_currentScale = p_model->GetModel(result.m_lodIndex)->GetScale() * p_model->GetScale();
	}

	MaterialTable* materialTable = p_model->GetMaterialTable(result.m_lodIndex);
	m_currentSceneNode = p_model->GetSceneNode(result.m_lodIndex);
	if (m_currentSceneNode != NULL) {
		p_model->ApplyPartAnimation(result.m_lodIndex);
		if (m_unk0xc8568) {
			m_currentSceneNode->UpdateWorldMatrices(m_unk0xc8450);
		}
		else {
			m_currentSceneNode->UpdateWorldMatrices(*modelMatrix);
		}
	}

	FUN_10012f50();
	model->Draw(this, materialTable);

	m_renderState = NULL;
	m_stateBeginPending = FALSE;
	FUN_10012f50();

	if (m_stateBeginPending) {
		p_renderState->End(this, p_model, result.m_lodIndex);
	}
}

// FUNCTION: GOLDP 0x10008f70
void GolD3DRenderDevice::DrawModelEntityWithUvOffset(
	GolWorldEntity* p_model,
	LegoFloat p_uvOffsetU,
	LegoFloat p_uvOffsetV
)
{
	GolWorldEntity::ResultStruct result;
	GolModelEntity* modelEntity = static_cast<GolModelEntity*>(p_model);
	p_model->ComputeVisibility(m_viewFrustum, &result);
	if (!result.m_visibility) {
		return;
	}

	GolMatrix4* modelMatrix = &m_modelMatrix;
	m_uvOffsetU = p_uvOffsetU;
	m_uvOffsetEnabled = 1;
	m_uvOffsetV = p_uvOffsetV;
	modelEntity->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = modelEntity->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	if (result.m_visibility == 1) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
	}
	else {
		m_unk0xc83e4 = FALSE;
		m_currentMatrix = &m_unk0xc84d8;
		FUN_10012f50();
		GolMath::MultiplyMatrix4(*modelMatrix, *m_viewScreenProjectionMatrix, &m_unk0xc84d8);
	}

	GolModel* model = static_cast<GolModel*>(modelEntity->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	m_unk0xc8568 = vertexType == GolModel::e_vertexType2 || vertexType == GolModel::e_vertexType3;
	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = modelEntity->GetMaterialTable(result.m_lodIndex);
	FUN_10008880(p_model, result.m_lodIndex);
	FUN_10012f50();
	model->Draw(this, materialTable);

	m_uvOffsetEnabled = 0;
	FUN_10012f50();
}

// FUNCTION: GOLDP 0x100090b0
void GolD3DRenderDevice::DrawCollidableEntityWithState(
	GolModelEntity* p_model,
	GolD3DRenderState* p_renderState,
	undefined4 p_lodIndex
)
{
	GolWorldEntity::ResultStruct result;
	if (p_lodIndex == static_cast<undefined4>(-1)) {
		p_model->ComputeVisibility(m_viewFrustum, &result);
		if (!result.m_visibility) {
			return;
		}
	}
	else {
		result.m_lodIndex = p_lodIndex;
	}

	m_renderState = p_renderState;

	GolBoundingShape::TreeNode::Node* firstNode;
	GolBoundingShape::TreeNode::Node* lastNode;
	static_cast<GolCollidableEntity*>(p_model)
		->GetBoundingShape(result.m_lodIndex)
		->CollectVisibleLeaves(&m_viewFrustum, &firstNode, &lastNode);

	GolMatrix4* modelMatrix = &m_modelMatrix;
	p_model->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = p_model->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	if (!m_stateBeginPending) {
		m_unk0xc83e4 = TRUE;
		m_currentMatrix = m_unk0xc8498;
		FUN_10012f50();
	}
	else {
		p_renderState->Begin(this, p_model, result.m_lodIndex);
	}

	m_currentMatrix = modelMatrix;
	GolModel* model = static_cast<GolModel*>(p_model->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	m_unk0xc8568 = vertexType == GolModel::e_vertexType2 || vertexType == GolModel::e_vertexType3;
	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = p_model->GetMaterialTable(result.m_lodIndex);
	GolBoundingShape::TreeNode::Node* node;
	LegoU32 nextOffset;
	if (m_flags & c_flagZBufferActive) {
		node = firstNode;
		nextOffset = 0;
	}
	else {
		node = lastNode;
		nextOffset = 1;
	}

	FUN_10012f50();
	while (node != NULL) {
		model->DrawNode(this, materialTable, node);
		node = (&node->m_next)[nextOffset];
	}

	m_renderState = NULL;
	m_stateBeginPending = FALSE;
	FUN_10012f50();

	if (m_stateBeginPending) {
		p_renderState->End(this, p_model, result.m_lodIndex);
	}
}

// FUNCTION: GOLDP 0x10009240
void GolD3DRenderDevice::DrawModelEntityWithScopedState(
	GolModelEntity* p_arg1,
	GolD3DRenderState* p_arg2,
	undefined4 p_arg3
)
{
	m_stateBeginPending = TRUE;
	DrawModelEntityWithState(p_arg1, p_arg2, p_arg3);
}

// FUNCTION: GOLDP 0x10009270
void GolD3DRenderDevice::DrawCollidableEntityWithScopedState(
	GolModelEntity* p_arg1,
	GolD3DRenderState* p_arg2,
	undefined4 p_arg3
)
{
	m_stateBeginPending = TRUE;
	DrawCollidableEntityWithState(p_arg1, p_arg2, p_arg3);
}

// FUNCTION: GOLDP 0x100092a0
void GolD3DRenderDevice::DrawCollidableEntity(GolWorldEntity* p_model)
{
	GolWorldEntity::ResultStruct result;
	GolModelEntity* modelEntity = static_cast<GolModelEntity*>(p_model);
	p_model->ComputeVisibility(m_viewFrustum, &result);
	if (!result.m_visibility) {
		return;
	}

	GolBoundingShape::TreeNode::Node* firstNode;
	GolBoundingShape::TreeNode::Node* lastNode;
	static_cast<GolCollidableEntity*>(p_model)
		->GetBoundingShape(result.m_lodIndex)
		->CollectVisibleLeaves(&m_viewFrustum, &firstNode, &lastNode);

	GolMatrix4* modelMatrix = &m_modelMatrix;
	modelEntity->BuildModelMatrix(modelMatrix, result.m_lodIndex);

	const GolVec3& position = modelEntity->GetPosition();
	modelMatrix->m_m[3][0] = position.m_x;
	modelMatrix->m_m[3][1] = position.m_y;
	modelMatrix->m_m[3][2] = position.m_z;

	GolMath::MultiplyMatrix4(*modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
	GolMath::MultiplyMatrix4(*modelMatrix, *m_viewScreenProjectionMatrix, &m_unk0xc84d8);

	GolModel* model = static_cast<GolModel*>(modelEntity->GetModel(result.m_lodIndex));
	GdbVertexArray* vertexArray = model->GetVertexArray();
	LegoU16 vertexType = vertexArray->GetVertexType();
	if (m_unk0xc8568 != (vertexType == GolModel::e_vertexType2 || vertexType == GolModel::e_vertexType3)) {
		m_unk0xc8568 = vertexType == GolModel::e_vertexType2 || vertexType == GolModel::e_vertexType3;
		FUN_10012f50();
	}

	if (m_unk0xc8568) {
		FUN_1000add0(p_model, model);
	}

	MaterialTable* materialTable = modelEntity->GetMaterialTable(result.m_lodIndex);
	GolBoundingShape::TreeNode::Node* node;
	LegoU32 nextOffset;
	if (m_flags & c_flagZBufferActive) {
		node = firstNode;
		nextOffset = 0;
	}
	else {
		node = lastNode;
		nextOffset = 1;
	}

	while (node != NULL) {
		if (node->m_linked == 0) {
			m_unk0xc83e4 = FALSE;
			m_currentMatrix = &m_unk0xc84d8;
		}
		else {
			m_unk0xc83e4 = TRUE;
			m_currentMatrix = m_unk0xc8498;
		}
		FUN_10012f50();

		model->DrawNode(this, materialTable, node);
		node = (&node->m_next)[nextOffset];
	}
}

// FUNCTION: GOLDP 0x10009420
void GolD3DRenderDevice::BeginFrame(undefined4 p_flags)
{
	ApplyCamera();
	ApplyLights();

	m_unk0xc3848 = 0;

	if (m_renderTargetInfo->m_pixelFlags & GolSurface::c_lockFlagFlipPending) {
		m_renderTargetInfo->FinishPendingFlip();
	}

	if (p_flags & 0x05) {
		if (m_unk0xc83c4 == 0) {
			D3DRECT rect;
			rect.x1 = 0;
			rect.y1 = 0;

			rect.x2 = m_renderTargetInfo->m_width;
			rect.y2 = m_renderTargetInfo->m_height;

			LegoU32 clearFlags = ((~p_flags & 0xff) >> 2) & 1;
			if (m_flags & c_flagZBuffer) {
				clearFlags |= 2;
			}

			m_d3dViewport->Clear(1, &rect, clearFlags);
		}
		else if (p_flags & 0x01) {
			m_renderTargetInfo->Fill(m_clearPixelValue);
		}
	}

	if (m_unk0xc83c4 == 0) {
		HRESULT result = m_d3dDevice->BeginScene();
		if (result) {
			GOL_FATALERROR_MESSAGE("Unable to begin scene");
		}
	}
	else {
		m_unk0xc86f4 = 0;
		m_softwareRenderer.SetDimensions(m_renderTargetInfo->m_width, m_renderTargetInfo->m_height);
		m_unk0xc86f0 = m_softwareRenderer.GetCommands();
		m_unk0xc86f8 = m_softwareRenderer.GetNodeCapacity();
	}
}

// FUNCTION: GOLDP 0x10009540
void GolD3DRenderDevice::EndFrame()
{
	if (m_unk0xc83c4 == 0) {
		HRESULT result = m_d3dDevice->EndScene();
		if (result && result != DDERR_SURFACELOST) {
			GOL_FATALERROR_MESSAGE("Unable to end scene");
		}
	}
	else {
		m_softwareRenderer.FUN_10041830(m_unk0xc86f4, TRUE);
		if (m_unk0xc86f4 != 0) {
			m_softwareRenderer.SetTlVertexCount(m_unk0xc3848);

			LegoU8* pixels;
			LegoU32 pitch;
			m_renderTargetInfo
				->LockPixels(&pixels, &pitch, GolSurface::c_lockRequestRead | GolSurface::c_lockRequestWrite);
			if (pixels != NULL) {
				m_softwareRenderer.SetRenderTarget(pixels, pitch);
				m_softwareRenderer.FUN_10041a20(FALSE);
				m_renderTargetInfo->UnlockPixels();
			}
		}
	}

	if (m_renderTargetInfo != m_primaryRenderTarget) {
		GolRenderTarget* renderTargetInfo = m_primaryRenderTarget;
		m_renderTargetInfo = renderTargetInfo;

		Rect rect;
		rect.m_left = 0;
		rect.m_top = 0;
		rect.m_right = renderTargetInfo->m_width;
		rect.m_bottom = renderTargetInfo->m_height;

		SetCamera(m_currentCamera);
		m_currentCamera->SetViewport(&rect);
	}

	m_drawCommand.m_material = NULL;
}

// FUNCTION: GOLDP 0x10009640
void GolD3DRenderDevice::SetClearColor(const ColorRGBA& p_color)
{
	GolSurfaceFormat textureFormat;

	m_clearColor = p_color;
	if (m_flags & c_flagSoftwareRenderer) {
		textureFormat = m_renderTargetInfo->m_textureFormat;
		if (textureFormat.m_paletteMask != 0) {
			m_clearPixelValue = m_renderTargetInfo->GetPalette()->FindEntry(m_clearColor);
		}
		else {
			m_clearPixelValue = textureFormat.MapRGBA(m_clearColor);
		}
	}
	else {
		LegoFloat c = static_cast<LegoFloat>(static_cast<double>(p_color.m_red) / 255.0);
		m_materialParams.ambient.r = c;
		m_materialParams.diffuse.r = c;
		c = static_cast<LegoFloat>(static_cast<double>(p_color.m_grn) / 255.0);
		m_materialParams.ambient.g = c;
		m_materialParams.diffuse.g = c;
		c = static_cast<LegoFloat>(static_cast<double>(p_color.m_blu) / 255.0);
		m_materialParams.ambient.b = c;
		m_materialParams.diffuse.b = c;
		m_backgroundMaterial->SetMaterial(&m_materialParams);
		m_backgroundMaterial->GetHandle(m_d3dDevice, &m_backgroundMaterialHandle);
		m_d3dViewport->SetBackground(m_backgroundMaterialHandle);
	}
}

// FUNCTION: GOLDP 0x10009780
void GolD3DRenderDevice::EnablePerspectiveCorrection()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetRenderState(
				D3DRENDERSTATE_TEXTUREPERSPECTIVE,
				(m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps & D3DPTEXTURECAPS_PERSPECTIVE) ? TRUE : FALSE
			);
		}
	}
}

// FUNCTION: GOLDP 0x100097c0
void GolD3DRenderDevice::DisablePerspectiveCorrection()
{
	if (!m_unk0xc83c4) {
		if (!m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);
		}
	}
}

// FUNCTION: GOLDP 0x100097f0
void GolD3DRenderDevice::EnableDither()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(
			D3DRENDERSTATE_DITHERENABLE,
			(m_d3dDeviceDesc.dpcTriCaps.dwRasterCaps & D3DPRASTERCAPS_DITHER) && m_drawState->IsHwAccelerated() ? TRUE
																												: FALSE
		);
	}
}

// FUNCTION: GOLDP 0x10009840
void GolD3DRenderDevice::DisableDither()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, FALSE);
	}
}

// FUNCTION: GOLDP 0x10009860
void GolD3DRenderDevice::EnableZBuffer()
{
	if (!m_unk0xc83c4 && (m_flags & c_flagZBuffer)) {
		if (m_drawState->SupportsWBuffer()) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_USEW);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		}

		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	}

	m_flags |= c_flagZBufferActive;
}

// FUNCTION: GOLDP 0x100098d0
void GolD3DRenderDevice::DisableZBuffer(LegoBool32 p_arg)
{
	m_flags &= ~c_flagZBufferActive;

	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	}
	else {
		if (p_arg == 0) {
			m_flatDepth = 0.0f;
		}
		else {
			m_flatDepth = 1.0f;
		}
	}
}

// FUNCTION: GOLDP 0x10009930
LPDIRECT3D3 GolD3DRenderDevice::GetDirect3D3() const
{
	return m_drawState->m_d3d3;
}

// FUNCTION: GOLDP 0x10009940
LPDIRECTDRAW4 GolD3DRenderDevice::GetDirectDraw4() const
{
	return m_drawState->m_ddraw4;
}

// FUNCTION: GOLDP 0x10009950
GolRenderTarget* GolD3DRenderDevice::GetRenderTargetInfo()
{
	return m_renderTargetInfo;
}

// FUNCTION: GOLDP 0x10009960
void GolD3DRenderDevice::DrawImageClipped(
	GolImage* p_image,
	undefined4 p_unk0x08,
	Rect* p_destRect,
	Rect* p_sourceRect,
	Rect* p_clipRect
)
{
	p_image->DrawStretched(this, p_unk0x08, p_destRect, p_sourceRect, p_clipRect);
}

// FUNCTION: GOLDP 0x10009990
void GolD3DRenderDevice::DrawImageRect(GolImage* p_image, undefined4 p_unk0x08, Rect* p_destRect, Rect* p_clipRect)
{
	p_image->Draw(this, p_unk0x08, p_destRect, p_clipRect);
}

// FUNCTION: GOLDP 0x100099b0
void GolD3DRenderDevice::DrawImageStretched(
	GolImage* p_image,
	undefined4 p_unk0x08,
	LegoS32 p_destLeft,
	LegoS32 p_destTop,
	LegoS32 p_destWidth,
	LegoS32 p_destHeight,
	LegoS32 p_sourceLeft,
	LegoS32 p_sourceTop,
	LegoS32 p_sourceWidth,
	LegoS32 p_sourceHeight
)
{
	Rect destRect;
	destRect.m_left = p_destLeft;
	destRect.m_top = p_destTop;
	destRect.m_right = p_destLeft + p_destWidth;
	destRect.m_bottom = p_destTop + p_destHeight;

	Rect sourceRect;
	sourceRect.m_left = p_sourceLeft;
	sourceRect.m_top = p_sourceTop;
	sourceRect.m_right = p_sourceLeft + p_sourceWidth;
	sourceRect.m_bottom = p_sourceTop + p_sourceHeight;

	p_image->DrawStretched(this, p_unk0x08, &destRect, &sourceRect, 0);
}

// FUNCTION: GOLDP 0x10009a20
void GolD3DRenderDevice::DrawImage(
	GolImage* p_image,
	undefined4 p_unk0x08,
	LegoS32 p_destLeft,
	LegoS32 p_destTop,
	LegoS32 p_destWidth,
	LegoS32 p_destHeight
)
{
	Rect destRect;
	destRect.m_left = p_destLeft;
	destRect.m_top = p_destTop;
	destRect.m_right = p_destLeft + p_destWidth;
	destRect.m_bottom = p_destTop + p_destHeight;

	p_image->Draw(this, p_unk0x08, &destRect, 0);
}

// FUNCTION: GOLDP 0x10009a70
void GolD3DRenderDevice::DrawBillboard(GolBillboard& p_param)
{
	LegoBool32 visibility[2];
	p_param.TestVisibility(m_viewFrustum.m_position, visibility);
	if (visibility[0]) {
		GolVec3 forward;
		GolVec3 right;
		GolCamera* camera = m_currentCamera;
		camera->m_transform->VTable0x1c(&right, &forward);

		forward.m_x = -forward.m_x;
		forward.m_y = -forward.m_y;
		forward.m_z = -forward.m_z;

		LegoBool32 builtMatrix = p_param.BuildModelMatrix(&right, &forward, &m_modelMatrix);
		if (builtMatrix) {
			GolMath::MultiplyMatrix4(m_modelMatrix, *m_viewProjectionMatrix, m_unk0xc8498);
			m_unk0xc8568 = 0;
			m_unk0xc83e4 = 1;
			m_currentMatrix = m_unk0xc8498;
			FUN_10012f50();
			p_param.DrawQuad(this);
		}
	}
}

// FUNCTION: GOLDP 0x10009b40
void GolD3DRenderDevice::DrawCString(
	const LegoChar* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	p_font->DrawString(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009b70
void GolD3DRenderDevice::DrawString(
	GolString* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	p_font->DrawString(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009ba0
void GolD3DRenderDevice::DrawStringFitted(
	GolString* p_unk0x04,
	GolFontBase* p_font,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoFloat p_unk0x14,
	LegoFloat p_unk0x18,
	Rect* p_unk0x1c,
	undefined4 p_unk0x20
)
{
	p_font->DrawStringFitted(p_unk0x04, this, p_unk0x0c, p_unk0x10, p_unk0x14, p_unk0x18, p_unk0x1c, p_unk0x20);
}

// FUNCTION: GOLDP 0x10009bd0
void GolD3DRenderDevice::DrawRectangle(
	const Rect& p_rect,
	LegoFloat p_z,
	const ColorRGBA& p_color1,
	const ColorRGBA& p_color2,
	const ColorRGBA& p_color3,
	const ColorRGBA& p_color4,
	undefined4 p_arg7
)
{
	TexturedVertex topLeft;
	TexturedVertex bottomRight;
	TexturedVertex bottomLeft;
	TexturedVertex topRight;

	LegoFloat left = static_cast<LegoFloat>(p_rect.m_left);
	topLeft.m_z = p_z;
	topLeft.m_color = p_color1;
	topLeft.m_x = left;

	LegoFloat top = static_cast<LegoFloat>(p_rect.m_top);
	bottomLeft.m_z = p_z;
	topLeft.m_y = top;
	bottomLeft.m_color = p_color2;
	bottomLeft.m_x = left;

	LegoFloat bottom = static_cast<LegoFloat>(p_rect.m_bottom);
	bottomLeft.m_y = bottom;

	LegoFloat right = static_cast<LegoFloat>(p_rect.m_right);
	topRight.m_z = p_z;
	topRight.m_y = top;
	topRight.m_color = p_color3;
	topRight.m_x = right;

	bottomRight.m_x = right;
	bottomRight.m_color = p_color4;
	bottomRight.m_y = bottom;
	bottomRight.m_z = p_z;

	topLeft.m_u = 0.0f;
	topLeft.m_v = 0.0f;
	bottomLeft.m_u = 0.0f;
	bottomLeft.m_v = 0.0f;
	topRight.m_u = 0.0f;
	topRight.m_v = 0.0f;
	bottomRight.m_u = 0.0f;
	bottomRight.m_v = 0.0f;

	DrawTriangle(&bottomLeft, &topLeft, &bottomRight, NULL, p_arg7);
	DrawTriangle(&bottomRight, &topLeft, &topRight, NULL, p_arg7);
}

// FUNCTION: GOLDP 0x10009ce0
void GolD3DRenderDevice::DrawTriangle(
	const TexturedVertex* p_vertex0,
	const TexturedVertex* p_vertex1,
	const TexturedVertex* p_vertex2,
	GolMaterial* p_material,
	undefined4
)
{
	if (p_material == NULL) {
		p_material = &m_unk0x2d4;
	}

	(this->*m_applyMaterialFn)(p_material);
	SetCurrentTexture(p_material->GetTexture());

	const TexturedVertex* v0;
	const TexturedVertex* v1;
	const TexturedVertex* v2;
	if (p_material->GetFlags() & GolMaterial::c_flagRotateVertices) {
		v2 = p_vertex0;
		v0 = p_vertex1;
		v1 = p_vertex2;
	}
	else {
		v2 = p_vertex2;
		v1 = p_vertex1;
		v0 = p_vertex0;
	}

	LegoU32 vertexIndexMask = m_unk0xc384c;
	LegoU32 vertexIndex = m_unk0xc3848 & vertexIndexMask;
	vertexIndexMask = ~vertexIndexMask;
	vertexIndexMask &= 0x40;
	D3DTLVERTEX* vertices = &m_unk0x348[vertexIndexMask + vertexIndex];

	vertices[0].sx = v0->m_x;
	vertices[0].sy = v0->m_y;
	vertices[0].sz = v0->m_z;
	if (vertices[0].sz > 0.0f) {
		LegoFloat z = v0->m_z;
		vertices[0].rhw = 1.0f / z;
	}
	else {
		vertices[0].rhw = 1.0f;
	}
	vertices[0].tu = v0->m_u;
	vertices[0].tv = v0->m_v;
	vertices[0].specular = 0;

	vertices[1].sx = v1->m_x;
	vertices[1].sy = v1->m_y;
	vertices[1].sz = v1->m_z;
	if (vertices[1].sz > 0.0f) {
		LegoFloat z = v1->m_z;
		vertices[1].rhw = 1.0f / z;
	}
	else {
		vertices[1].rhw = 1.0f;
	}
	vertices[1].tu = v1->m_u;
	vertices[1].tv = v1->m_v;
	vertices[1].specular = 0;

	vertices[2].sx = v2->m_x;
	vertices[2].sy = v2->m_y;
	vertices[2].sz = v2->m_z;
	if (vertices[2].sz > 0.0f) {
		LegoFloat z = v2->m_z;
		vertices[2].rhw = 1.0f / z;
	}
	else {
		vertices[2].rhw = 1.0f;
	}
	vertices[2].tu = v2->m_u;
	vertices[2].tv = v2->m_v;
	vertices[2].specular = 0;

	switch (m_paletteMode) {
	case 1: {
		LegoU32 color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[0].color = color;

		color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[1].color = color;

		color = v0->m_color.m_grn;
		color &= 0xe0;
		color |= v0->m_color.m_blu >> 3;
		color >>= 3;
		color |= v0->m_color.m_red & 0xe0;
		vertices[2].color = color;
		break;
	}
	case 2:
		vertices[0].color =
			(v0->m_color.m_alp << 24) | (v0->m_color.m_red << 16) | (v0->m_color.m_grn << 8) | v0->m_color.m_blu;
		vertices[1].color =
			(v1->m_color.m_alp << 24) | (v1->m_color.m_red << 16) | (v1->m_color.m_grn << 8) | v1->m_color.m_blu;
		vertices[2].color =
			(v2->m_color.m_alp << 24) | (v2->m_color.m_red << 16) | (v2->m_color.m_grn << 8) | v2->m_color.m_blu;
		break;
	}

	if (m_unk0xc83c4) {
		LegoS32 commandIndex = m_unk0xc86f4;
		LegoS32 nextCommandIndex = commandIndex + 1;
		if (nextCommandIndex < m_unk0xc86f8) {
			GolSoftwareRenderer::TriangleCommand* cmd = m_unk0xc86f0 + commandIndex;
			m_unk0xc86f4 = nextCommandIndex;
			cmd->m_vertexIndex0 = m_unk0xc3848++;
			cmd->m_vertexIndex1 = m_unk0xc3848++;
			cmd->m_vertexIndex2 = m_unk0xc3848++;
			cmd->m_rasterizer = m_unk0xc83b4.m_unk0x00[0];
			if (m_flags & c_flagZBufferActive) {
				m_softwareRenderer.FUN_100417c0(cmd, 1);
			}
			else {
				m_softwareRenderer.FUN_100417a0(cmd, 1, m_flatDepth);
			}
		}
	}
	else {
		m_d3dDevice->DrawPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			vertices,
			3,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x10009fd0
void GolD3DRenderDevice::DrawTriangleStrip(D3DTLVERTEX* p_vertices, LegoU32 p_count)
{
	if (m_unk0xc83c4) {
		D3DTLVERTEX* vertices = &m_unk0x348[m_unk0xc3848];

		LegoU32 copyCount = p_count;
		D3DTLVERTEX* dest = vertices;
		for (; copyCount > 0; copyCount--) {
			*dest = *p_vertices;
			dest++;
			p_vertices++;
		}

		LegoS32 triangleCount = p_count - 2;
		if (triangleCount >= 0) {
			LegoS32 commandIndex = m_unk0xc86f4;
			LegoS32 nextCommandIndex = commandIndex + triangleCount;
			if (nextCommandIndex < m_unk0xc86f8) {
				GolSoftwareRenderer::TriangleCommand* cmd = m_unk0xc86f0 + commandIndex;
				m_unk0xc86f4 = nextCommandIndex;

				LegoS32 winding = 1;
				GolSoftwareRenderer::TriangleCommand* command = cmd;
				for (LegoS32 i = 0; i < triangleCount;) {
					i++;
					command->m_vertexIndex0 = static_cast<LegoU16>(m_unk0xc3848 + i + winding);
					command->m_vertexIndex1 = static_cast<LegoU16>(m_unk0xc3848 + i);
					command->m_vertexIndex2 = static_cast<LegoU16>(m_unk0xc3848 + i - winding);
					command->m_rasterizer = m_unk0xc83b4.m_unk0x00[0];
					winding = -winding;
					command++;
				}

				m_unk0xc3848 += p_count;
				if (m_flags & c_flagZBufferActive) {
					m_softwareRenderer.FUN_100417c0(cmd, triangleCount);
				}
				else {
					m_softwareRenderer.FUN_100417a0(cmd, triangleCount, m_flatDepth);
				}
			}
		}
	}
	else {
		m_d3dDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,
			D3DFVF_TLVERTEX,
			p_vertices,
			p_count,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x1000a110
void GolD3DRenderDevice::SelectTextureFormat(
	const GolSurfaceFormat& p_requestedTextureFormat,
	GolSurfaceFormat* p_actualTextureFormat,
	LegoBool32 p_arg3
)
{
	GolSurfaceFormat reqTextureFormat;
	if (p_arg3 && (m_flags & (c_flagColorKeyAlphaBlend | c_flagColorKeyAlphaTest)) &&
		p_requestedTextureFormat.GetAlphaBitCount() == 0) {
		reqTextureFormat.m_redBitMask = 0xf800;
		reqTextureFormat.m_grnBitMask = 0x07c0;
		reqTextureFormat.m_bluBitMask = 0x003e;
		reqTextureFormat.m_alpBitMask = 0x0001;
		reqTextureFormat.m_intensityMask = 0;
		reqTextureFormat.m_paletteMask = 0;
		reqTextureFormat.m_bitsPerPixel = 16;
		GolRenderDevice::SelectTextureFormat(reqTextureFormat, p_actualTextureFormat, TRUE);
	}
	else {
		GolRenderDevice::SelectTextureFormat(p_requestedTextureFormat, p_actualTextureFormat, FALSE);
	}
}

// FUNCTION: GOLDP 0x1000a1c0
LegoU32 GolD3DRenderDevice::GetMinimumTextureWidth(undefined4) const
{
	if (m_unk0xc83c4) {
		return 8;
	}
	if (m_d3dDeviceDesc.dwMinTextureWidth != 0) {
		return m_d3dDeviceDesc.dwMinTextureWidth;
	}
	return 32;
}

// FUNCTION: GOLDP 0x1000a1f0
LegoU32 GolD3DRenderDevice::GetMaximumTextureWidth(undefined4) const
{
	if (m_unk0xc83c4) {
		return 256;
	}
	if (m_d3dDeviceDesc.dwMaxTextureWidth != 0) {
		return m_d3dDeviceDesc.dwMaxTextureWidth;
	}
	return 256;
}

// FUNCTION: GOLDP 0x1000a210
LegoU32 GolD3DRenderDevice::GetMinimumTextureHeight(undefined4) const
{
	if (m_unk0xc83c4) {
		return 8;
	}
	if (m_d3dDeviceDesc.dwMinTextureHeight != 0) {
		return m_d3dDeviceDesc.dwMinTextureHeight;
	}
	return 32;
}

// FUNCTION: GOLDP 0x1000a240
LegoU32 GolD3DRenderDevice::GetMaximumTextureHeight(undefined4) const
{
	if (m_unk0xc83c4) {
		return 256;
	}
	if (m_d3dDeviceDesc.dwMaxTextureHeight != 0) {
		return m_d3dDeviceDesc.dwMaxTextureHeight;
	}
	return 256;
}

// FUNCTION: GOLDP 0x1000a260
LegoBool32 GolD3DRenderDevice::TexturesMustBeSquare() const
{
	if (m_unk0xc83c4) {
		return FALSE;
	}
	else {
		LegoU32 textureCaps = m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps;
		LegoU32 result = static_cast<LegoU8>(~textureCaps);
		result &= 0xff;
		return (result >> 5) & 1;
	}
}

// FUNCTION: GOLDP 0x1000a290
LegoBool32 GolD3DRenderDevice::TextureSizesMustBePowersOfTwo() const
{
	if (m_unk0xc83c4) {
		return TRUE;
	}
	else {
		LegoU32 textureCaps = m_d3dDeviceDesc.dpcTriCaps.dwTextureCaps;
		LegoU32 result = textureCaps & 0xff;
		return (result >> 1) & 1;
	}
}

// FUNCTION: GOLDP 0x1000a2c0
void GolD3DRenderDevice::ApplyMaterialHw(GolMaterial* p_material)
{
	LegoU32 newFlags = p_material->GetFlags();

	m_drawCommand.m_material = p_material;
	if (m_unk0xc8568 != 0) {
		GolMaterialColor c = p_material->GetAmbient();
		m_unk0xc8570 = static_cast<LegoU32>(m_unk0xc856c.m_red * c.m_red) >> 8;
		m_unk0xc8574 = static_cast<LegoU32>(m_unk0xc856c.m_grn * c.m_grn) >> 8;
		m_unk0xc8578 = static_cast<LegoU32>(m_unk0xc856c.m_blu * c.m_blu) >> 8;
		m_unk0xc857c = c.m_alp & 0xff;
		c = p_material->GetDiffuse();
		for (LegoU32 i = 0; i < m_lightCount; i++) {
			m_unk0xc859c[i].m_red =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_red) * static_cast<LegoFloat>(c.m_red & 0xff) / 256.0f;
			m_unk0xc859c[i].m_grn =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_grn) * static_cast<LegoFloat>(c.m_grn & 0xff) / 256.0f;
			m_unk0xc859c[i].m_blu =
				static_cast<LegoFloat>(m_unk0xc8580[i].m_blu) * static_cast<LegoFloat>(c.m_blu & 0xff) / 256.0f;
		}
	}

	if (m_flags & c_flagAlphaOverride) {
		newFlags &= ~(GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency);
		newFlags |= GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagTransparent;
	}
	else {
		if (newFlags &
			(GolMaterial::c_flagAlphaTest | GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagTransparent)) {
			if (newFlags & GolMaterial::c_flagAlphaTest) {
				LegoU32 alphaFunc = p_material->GetAlphaFunc();
				if (m_activeAlphaFunc != alphaFunc) {
					m_activeAlphaFunc = alphaFunc;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, g_d3dCmpFuncLookup[alphaFunc]);
				}

				LegoU32 alphaRef = p_material->GetAlphaRef();
				if (m_activeAlphaRef != alphaRef) {
					m_activeAlphaRef = alphaRef;
					// BUG? documentation specifies range from 0x00000000 to 0x000000FF.
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, alphaRef << 16);
				}
			}

			if (newFlags & GolMaterial::c_flagTransparent) {
				LegoU32 destBlend = p_material->GetDestBlend();
				m_alpha = destBlend;
				newFlags &= ~GolMaterial::c_flagDecal;
				newFlags |= GolMaterial::c_flagModulate;
				m_unk0xc83fc = (destBlend << 24) | (m_unk0xc83fc & 0x00ffffff);
			}
			else if (newFlags & GolMaterial::c_flagAlphaBlend) {
				LegoU32 srcBlend = p_material->GetSrcBlend();
				if (m_activeSrcBlend != srcBlend) {
					m_activeSrcBlend = srcBlend;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, m_srcBlendOps[srcBlend]);
				}

				LegoU32 destBlend = p_material->GetDestBlend();
				if (m_activeDestBlend != destBlend) {
					m_activeDestBlend = destBlend;
					m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, m_destBlendOps[destBlend]);
				}
			}
		}
	}

	if (newFlags == m_activeMaterialFlags) {
		return;
	}

	if ((newFlags ^ m_activeMaterialFlags) & (GolMaterial::c_flagLinearFilter | GolMaterial::c_flagPointFilter)) {
		if (!(newFlags & GolMaterial::c_flagPointFilter) && m_drawState->IsHwAccelerated()) {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTSS_COLORARG1);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTSS_COLOROP);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		}
	}

	if ((newFlags ^ m_activeMaterialFlags) & (GolMaterial::c_flagWrap | GolMaterial::c_flagClamp)) {
		if (newFlags & GolMaterial::c_flagClamp) {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP);
		}
	}

	if ((newFlags ^ m_activeMaterialFlags) & (GolMaterial::c_flagFlatShading | GolMaterial::c_flagGouraudShading)) {
		if (newFlags & GolMaterial::c_flagGouraudShading) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT);
		}
	}

	if ((newFlags ^ m_activeMaterialFlags) &
		(GolMaterial::c_flagTextured | GolMaterial::c_flagDecal | GolMaterial::c_flagModulate)) {
		if (newFlags & GolMaterial::c_flagTextured) {
			if (newFlags & GolMaterial::c_flagModulate) {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
				if (m_flags & c_flagColorOverride) {
					m_unk0xc83fc =
						ARGBU32(m_alpha, m_colorOverride.m_red, m_colorOverride.m_grn, m_colorOverride.m_blu);
				}
				else {
					m_unk0xc83f8 = FALSE;
				}
			}
			else {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
				m_unk0xc83f8 = TRUE;
				m_unk0xc83fc = ARGBU32(m_alpha, 0xff, 0xff, 0xff);
			}
			if (newFlags & (GolMaterial::c_flagTransparent | GolMaterial::c_flagModulate)) {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				m_unk0xc83e8 = TRUE;
			}
			else {
				m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
				m_unk0xc83e8 = TRUE;
			}
		}
		else {
			m_d3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
			m_unk0xc83e8 = FALSE;
			if (m_flags & c_flagColorOverride) {
				m_unk0xc83fc = ARGBU32(m_alpha, m_colorOverride.m_red, m_colorOverride.m_grn, m_colorOverride.m_blu);
			}
			else {
				m_unk0xc83f8 = FALSE;
			}
		}
		FUN_10012f50();
	}

	if ((newFlags ^ m_activeMaterialFlags) & (GolMaterial::c_flagAlphaTest | GolMaterial::c_flagNoAlphaTest)) {
		if (newFlags & GolMaterial::c_flagAlphaTest) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
		}
		else {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, FALSE);
		}
	}

	if ((newFlags ^ m_activeMaterialFlags) & (GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoAlphaBlend |
											  GolMaterial::c_flagTransparent | GolMaterial::c_flagNoTransparency)) {
		if (newFlags & (GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagTransparent)) {
			m_unk0xc83ec = 0;
			if (newFlags & GolMaterial::c_flagTransparent) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
				m_activeSrcBlend = 6;
				m_activeDestBlend = 8;
				m_unk0xc83ec = 1;
				if (newFlags & GolMaterial::c_flagTextured) {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
			}
			else {
				if (newFlags & GolMaterial::c_flagTextured) {
					if (newFlags & GolMaterial::c_flagModulate) {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
					}
					else {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
						m_unk0xc83fc = ARGBU32(0xff, 0xff, 0xff, 0xff);
					}
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
				m_alpha = 0xff;
			}
			if (m_flags & c_flagBit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, TRUE);
			}
			else {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			}
			m_activeMaterialFlags = newFlags;
			FUN_10012f50();
		}
		else {
			if (m_activeMaterialFlags & GolMaterial::c_flagTransparent) {
				if (newFlags & GolMaterial::c_flagTextured) {
					if (newFlags & GolMaterial::c_flagModulate) {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
					}
					else {
						m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
						m_unk0xc83fc = ARGBU32(0xff, 0xff, 0xff, 0xff);
					}
				}
				else {
					m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				}
				m_alpha = 0xff;
			}
			if (m_flags & c_flagBit12) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_STIPPLEDALPHA, FALSE);
			}
			else {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
			}
			m_unk0xc83ec = 0;
			m_activeMaterialFlags = newFlags;
			FUN_10012f50();
		}
	}
	else {
		if ((m_activeMaterialFlags ^ newFlags) & GolMaterial::c_flagRotateVertices) {
			m_activeMaterialFlags = newFlags;
			FUN_10012f50();
		}
		else {
			m_activeMaterialFlags = newFlags;
		}
	}
}

// FUNCTION: GOLDP 0x1000a950
void GolD3DRenderDevice::ApplyMaterialSw(GolMaterial* p_material)
{
	LegoU32 newFlags = p_material->GetFlags();
	m_drawCommand.m_material = p_material;

	LegoU32 textureCount;
	if (p_material->GetTexture() == NULL) {
		textureCount = 1;
	}
	else {
		textureCount = p_material->GetTexture()->GetMipmapCount();
	}
	m_unk0xc83ac = textureCount - 1;

	if (textureCount > 0) {
		for (LegoU32 i = 0; i < textureCount; i++) {
			m_unk0xc83b4.m_unk0x00[i] = static_cast<GolSoftwareMaterial*>(p_material)->GetPipelines() + i;
		}
	}

	if (m_unk0xc8568 != 0) {
		GolMaterialColor color = p_material->GetAmbient();
		m_unk0xc8570 = (static_cast<LegoU32>(m_unk0xc856c.m_red) * static_cast<LegoU32>(color.m_red & 0xff)) >> 8;
		m_unk0xc8574 = (static_cast<LegoU32>(m_unk0xc856c.m_grn) * static_cast<LegoU32>(color.m_grn & 0xff)) >> 8;
		m_unk0xc8578 = (static_cast<LegoU32>(m_unk0xc856c.m_blu) * static_cast<LegoU32>(color.m_blu & 0xff)) >> 8;
		m_unk0xc857c = color.m_alp & 0xff;

		color = p_material->GetDiffuse();
		for (LegoU32 i = 0; i < m_lightCount; i++) {
			m_unk0xc859c[i].m_red = ScaleColorChannel(m_unk0xc8580[i].m_red, color.m_red & 0xff);
			m_unk0xc859c[i].m_grn = ScaleColorChannel(m_unk0xc8580[i].m_grn, color.m_grn & 0xff);
			m_unk0xc859c[i].m_blu = ScaleColorChannel(m_unk0xc8580[i].m_blu, color.m_blu & 0xff);
		}
	}

	if (m_flags & c_flagAlphaOverride) {
		newFlags &= ~(GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoTransparency);
		newFlags |= GolMaterial::c_flagNoAlphaBlend | GolMaterial::c_flagTransparent;
	}
	else if (
		newFlags & (GolMaterial::c_flagAlphaTest | GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagTransparent)
	) {
		if (newFlags & GolMaterial::c_flagAlphaTest) {
			m_activeAlphaFunc = p_material->GetAlphaFunc();
			m_activeAlphaRef = p_material->GetAlphaRef();
		}

		if (newFlags & GolMaterial::c_flagTransparent) {
			LegoU32 destBlend = p_material->GetDestBlend();
			m_alpha = destBlend;
			newFlags &= ~GolMaterial::c_flagDecal;
			newFlags |= GolMaterial::c_flagModulate;
			m_unk0xc83fc = (destBlend << 24) | (m_unk0xc83fc & 0x00ffffff);
		}
		else if (newFlags & GolMaterial::c_flagAlphaBlend) {
			m_activeSrcBlend = p_material->GetSrcBlend();
			m_activeDestBlend = p_material->GetDestBlend();
		}
	}

	if (newFlags == m_activeMaterialFlags) {
		return;
	}

	LegoU32 changedFlags = newFlags ^ m_activeMaterialFlags;
	if (changedFlags & (GolMaterial::c_flagTextured | GolMaterial::c_flagDecal | GolMaterial::c_flagModulate)) {
		m_unk0xc83e8 = (newFlags >> 3) & 1;
		FUN_10012f50();
	}

	changedFlags = newFlags ^ m_activeMaterialFlags;
	if (changedFlags & (GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagNoAlphaBlend |
						GolMaterial::c_flagTransparent | GolMaterial::c_flagNoTransparency)) {
		m_unk0xc83ec = 0;
		if (newFlags & (GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagTransparent)) {
			if (newFlags & GolMaterial::c_flagTransparent) {
				m_activeSrcBlend = 6;
				m_activeDestBlend = 8;
				m_unk0xc83ec = 1;
				m_activeMaterialFlags = newFlags;
				FUN_10012f50();
				return;
			}
			m_alpha = 0xff;
		}

		m_activeMaterialFlags = newFlags;
		FUN_10012f50();
	}
	else {
		m_activeMaterialFlags = newFlags;
		if (changedFlags & GolMaterial::c_flagRotateVertices) {
			FUN_10012f50();
		}
	}
}

// FUNCTION: GOLDP 0x1000ac00
void GolD3DRenderDevice::SetCurrentTexture(GolTexture* p_texture)
{
	if (m_currentTexture == p_texture) {
		return;
	}

	m_currentTexture = p_texture;
	if (m_unk0xc83c4) {
		if (p_texture != NULL) {
			m_unk0xc83b0 = ~((p_texture->GetHeight() * p_texture->GetWidth() * 2) - 1);
		}
		return;
	}

	if (p_texture != NULL) {
		if (p_texture->GetTextureFlags() & GolTexture::c_textureFlagColorKeyed) {
			if (m_colorKeyEnabled == 0) {
				m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
				m_colorKeyEnabled = TRUE;
			}
		}
		else if (m_colorKeyEnabled != 0) {
			m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
			m_colorKeyEnabled = FALSE;
		}

		m_d3dDevice->SetTexture(0, static_cast<GolD3DTexture*>(m_currentTexture)->GetDirect3DTexture());
	}
	else if (m_colorKeyEnabled != 0) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);
		m_colorKeyEnabled = FALSE;
	}
}

// FUNCTION: GOLDP 0x1000acf0
void GolD3DRenderDevice::FUN_1000acf0(LegoU32 p_index)
{
	GolD3DRenderState* useMatrix = m_renderState;
	GolTransform** orbits = &static_cast<GolSceneTransformNode*>(m_currentSceneNode)->m_transforms;
	GolMatrix4* matrix;
	if (useMatrix != NULL) {
		matrix = &(*orbits)[p_index].m_worldMatrix;
	}
	else {
		matrix = &(*orbits)[p_index].m_worldViewMatrix;
	}
	m_currentMatrix = matrix;

	if (m_unk0xc8568 != 0) {
		GolMatrix4* lightMatrix = &(*orbits)[p_index].m_worldMatrix;
		for (LegoU32 i = 0; i < m_lightCount; i++) {
			m_unk0xc8644[i].m_x = m_unk0xc85f0[i].m_x * lightMatrix->m_m[0][0];
			m_unk0xc8644[i].m_y = m_unk0xc85f0[i].m_x * lightMatrix->m_m[1][0];
			m_unk0xc8644[i].m_z = m_unk0xc85f0[i].m_x * lightMatrix->m_m[2][0];

			m_unk0xc8644[i].m_x += lightMatrix->m_m[0][1] * m_unk0xc85f0[i].m_y;
			m_unk0xc8644[i].m_y += lightMatrix->m_m[1][1] * m_unk0xc85f0[i].m_y;
			m_unk0xc8644[i].m_z += lightMatrix->m_m[2][1] * m_unk0xc85f0[i].m_y;

			m_unk0xc8644[i].m_x += m_unk0xc85f0[i].m_z * lightMatrix->m_m[0][2];
			m_unk0xc8644[i].m_y += m_unk0xc85f0[i].m_z * lightMatrix->m_m[1][2];
			m_unk0xc8644[i].m_z += m_unk0xc85f0[i].m_z * lightMatrix->m_m[2][2];
		}
	}
}

// STUB: GOLDP 0x1000add0
void GolD3DRenderDevice::FUN_1000add0(GolWorldEntity* p_model, GolModel* p_modelData)
{
	GolOrientedEntity* model = static_cast<GolOrientedEntity*>(p_model);
	model->CopyOrientationToMatrix4(&m_unk0xc8450);

	const GolVec3& position = model->GetPosition();
	m_unk0xc8450.m_m[3][0] = position.m_x;
	m_unk0xc8450.m_m[3][1] = position.m_y;
	m_unk0xc8450.m_m[3][2] = position.m_z;

	GdbNormalVertexArray* vertexArray = static_cast<GdbNormalVertexArray*>(p_modelData->GetModelVertexArray());
	m_sourceNormals = vertexArray->GetNormals();

	for (LegoU32 i = 0; i < m_lightCount; i++) {
		m_unk0xc8644[i].m_x = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[0][0];
		m_unk0xc8644[i].m_y = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[1][0];
		m_unk0xc8644[i].m_z = m_unk0xc85f0[i].m_x * m_unk0xc8450.m_m[2][0];

		m_unk0xc8644[i].m_x += m_unk0xc8450.m_m[0][1] * m_unk0xc85f0[i].m_y;
		m_unk0xc8644[i].m_y += m_unk0xc8450.m_m[1][1] * m_unk0xc85f0[i].m_y;
		m_unk0xc8644[i].m_z += m_unk0xc8450.m_m[2][1] * m_unk0xc85f0[i].m_y;

		m_unk0xc8644[i].m_x += m_unk0xc85f0[i].m_z * m_unk0xc8450.m_m[0][2];
		m_unk0xc8644[i].m_y += m_unk0xc85f0[i].m_z * m_unk0xc8450.m_m[1][2];
		m_unk0xc8644[i].m_z += m_unk0xc8450.m_m[2][2] * m_unk0xc85f0[i].m_z;
	}
}

// FUNCTION: GOLDP 0x1000aeb0
void GolD3DRenderDevice::SetAlphaOverride(undefined4 p_alpha, undefined4 p_flags)
{
	GolRenderDevice::SetAlphaOverride(p_alpha, p_flags);
	m_alpha = p_alpha;
	m_unk0xc83fc = (m_unk0xc83fc & 0x00ffffff) | (p_alpha << 24);
}

// FUNCTION: GOLDP 0x1000aef0
void GolD3DRenderDevice::ClearAlphaOverride()
{
	GolRenderDevice::ClearAlphaOverride();
	m_alpha = 0xff;
	m_unk0xc83fc |= 0xff000000;
}

// FUNCTION: GOLDP 0x1000af20
void GolD3DRenderDevice::SetColorOverride(const ColorRGBA& p_color)
{
	GolRenderDevice::SetColorOverride(p_color);
	m_unk0xc83f8 = TRUE;
	m_unk0xc83fc = ARGBU32(m_alpha, p_color.m_red, p_color.m_grn, p_color.m_blu);
}

// FUNCTION: GOLDP 0x1000af70
void GolD3DRenderDevice::ClearColorOverride()
{
	GolRenderDevice::ClearColorOverride();
	m_unk0xc83f8 = FALSE;
}

// FUNCTION: GOLDP 0x1000af90
void GolD3DRenderDevice::ClearLights()
{
	GolRenderDevice::ClearLights();
	m_unk0xc856c.m_red = 0xff;
	m_unk0xc856c.m_grn = 0xff;
	m_unk0xc856c.m_blu = 0xff;
	m_unk0xc856c.m_alp = 0xff;

	if (m_drawCommand.m_material != NULL) {
		GolMaterialColor color = m_drawCommand.m_material->GetAmbient();
		m_unk0xc8570 = color.m_red & 0xff;
		m_unk0xc8574 = color.m_grn & 0xff;
		m_unk0xc8578 = color.m_blu & 0xff;
		m_unk0xc857c = color.m_alp & 0xff;
	}
}

// FUNCTION: GOLDP 0x1000b000
void GolD3DRenderDevice::SetAmbient(const MaterialColor* p_param)
{
	GolRenderDevice::SetAmbient(p_param);
	m_unk0xc856c = p_param->m_color;

	if (m_drawCommand.m_material != NULL) {
		GolMaterialColor color = m_drawCommand.m_material->GetAmbient();
		m_unk0xc8570 = (static_cast<LegoU32>(m_unk0xc856c.m_red) * static_cast<LegoU32>(color.m_red & 0xff)) >> 8;
		m_unk0xc8574 = (static_cast<LegoU32>(m_unk0xc856c.m_grn) * static_cast<LegoU32>(color.m_grn & 0xff)) >> 8;
		m_unk0xc8578 = (static_cast<LegoU32>(m_unk0xc856c.m_blu) * static_cast<LegoU32>(color.m_blu & 0xff)) >> 8;
		m_unk0xc857c = color.m_alp & 0xff;
	}
	else {
		m_unk0xc8570 = 0;
		m_unk0xc8574 = 0;
		m_unk0xc8578 = 0;
		m_unk0xc857c = 0xff;
	}
}

// FUNCTION: GOLDP 0x1000b0c0
void GolD3DRenderDevice::AddLight(const Light* p_param)
{
	LegoU32 index = m_lightCount;
	if (index < 7) {
		SetLight(index, p_param);
		GolRenderDevice::AddLight(p_param);
	}
}

// FUNCTION: GOLDP 0x1000b0f0
void GolD3DRenderDevice::SetLight(LegoU32 p_index, const Light* p_param)
{
	m_unk0xc8580[p_index] = p_param->m_color;
	m_unk0xc85f0[p_index] = p_param->m_direction;

	GolMaterialColor color;
	if (m_drawCommand.m_material != NULL) {
		color = m_drawCommand.m_material->GetDiffuse();
	}
	else {
		color.m_red = 0;
		color.m_grn = 0;
		color.m_blu = 0;
	}

	m_unk0xc859c[p_index].m_red = ScaleColorChannel(color.m_red & 0xff, m_unk0xc8580[p_index].m_red);
	m_unk0xc859c[p_index].m_grn = ScaleColorChannel(m_unk0xc8580[p_index].m_grn, color.m_grn & 0xff);
	m_unk0xc859c[p_index].m_blu = ScaleColorChannel(m_unk0xc8580[p_index].m_blu, color.m_blu & 0xff);
}

// FUNCTION: GOLDP 0x1000b1f0
void GolD3DRenderDevice::ApplyLights()
{
	if (m_flags & c_flagLightingEnabled) {
		if (m_ambientColor != NULL) {
			SetAmbient(m_ambientColor);
		}

		for (LegoU32 i = 0; i < m_lightCount; i++) {
			SetLight(i, m_lights[i]);
		}
	}
}

// FUNCTION: GOLDP 0x1000b240
void GolD3DRenderDevice::EnableWireframe()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
	}
}

// FUNCTION: GOLDP 0x1000b260
void GolD3DRenderDevice::DisableWireframe()
{
	if (!m_unk0xc83c4) {
		m_d3dDevice->SetRenderState(D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
	}
}

// FUNCTION: GOLDP 0x1000b280
void GolD3DRenderDevice::EnableMipmaps(LegoU32 p_arg)
{
	m_flags |= c_flagMipmapsEnabled;
	m_defaultMipmapCount = p_arg;
	if (m_defaultMipmapCount > 4) {
		m_defaultMipmapCount = 4;
	}
}

// FUNCTION: GOLDP 0x1000b2b0
void GolD3DRenderDevice::DisableMipmaps()
{
	m_flags &= ~c_flagMipmapsEnabled;
}

// FUNCTION: GOLDP 0x1000b2c0
GolRenderTarget* GolD3DRenderDevice::CreateRenderTarget(undefined2 p_arg1, undefined2 p_arg2)
{
	GolD3DRenderSurface* surface = new GolD3DRenderSurface;
	if (surface == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	surface->FUN_10013600(this, p_arg1, p_arg2);
	surface->m_next = m_renderSurfaces;
	m_renderSurfaces = surface;
	return surface;
}

// FUNCTION: GOLDP 0x1000b350
void GolD3DRenderDevice::DestroyRenderTarget(GolRenderTarget* p_surface)
{
	GolD3DRenderSurface* surface = m_renderSurfaces;
	if (surface == NULL) {
		return;
	}

	GolD3DRenderSurface* target = static_cast<GolD3DRenderSurface*>(p_surface);
	if (target == surface) {
		m_renderSurfaces = surface->m_next;
		target->Destroy();
		delete target;
		return;
	}

	GolD3DRenderSurface* previous = surface;
	surface = surface->m_next;
	if (surface == NULL) {
		return;
	}

	while (surface != NULL) {
		if (surface == target) {
			previous->m_next = surface->m_next;
			surface->m_next = NULL;
			target->Destroy();
			delete target;
			return;
		}

		previous = surface;
		surface = surface->m_next;
	}
}

// FUNCTION: GOLDP 0x1000b3d0
void GolD3DRenderDevice::SetRenderTarget(GolRenderTarget* p_surface, undefined4 p_flags)
{
	m_renderTargetInfo = m_primaryRenderTarget;
	GolD3DRenderSurface* surface = m_renderSurfaces;
	if (surface != NULL) {
		GolD3DRenderSurface* target = static_cast<GolD3DRenderSurface*>(p_surface);
		while (surface != NULL) {
			if (surface == target) {
				m_renderTargetInfo = surface;
				if (!m_unk0xc83c4 && m_d3dDevice->SetRenderTarget(m_renderTargetInfo->m_renderSurface, 0) != D3D_OK) {
					GOL_FATALERROR_MESSAGE("Unable to set secondary rendering target");
				}

				Rect rect;
				rect.m_left = 0;
				rect.m_top = 0;
				rect.m_right = m_renderTargetInfo->m_width;
				rect.m_bottom = m_renderTargetInfo->m_height;

				SetCamera(m_currentCamera);
				m_currentCamera->SetViewport(&rect);
				BeginFrame(p_flags);
				return;
			}

			surface = surface->m_next;
		}

		BeginFrame(p_flags);
		return;
	}

	BeginFrame(p_flags);
}

// FUNCTION: GOLDP 0x100016f0 FOLDED
LegoBool32 GolD3DRenderDevice::VTable0x110() const
{
	return FALSE;
}

// FUNCTION: GOLDP 0x1000b4a0
void GolD3DRenderDevice::FUN_1000b4a0()
{
	switch (m_paletteMode) {
	case 0: {
		m_countTextureFormats = 1;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[0].m_redBitMask = 0;
		m_textureFormats[0].m_grnBitMask = 0;
		m_textureFormats[0].m_bluBitMask = 0;
		m_textureFormats[0].m_alpBitMask = 0;
		m_textureFormats[0].m_paletteMask = 0xff;
		m_textureFormats[0].m_intensityMask = 0;
		m_textureFormats[0].m_bitsPerPixel = 8;
		break;
	}
	case 1: {
		m_countTextureFormats = 1;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[0].m_redBitMask = 0xe0;
		m_textureFormats[0].m_grnBitMask = 0x1c;
		m_textureFormats[0].m_bluBitMask = 0x03;
		m_textureFormats[0].m_alpBitMask = 0;
		m_textureFormats[0].m_paletteMask = 0;
		m_textureFormats[0].m_intensityMask = 0;
		m_textureFormats[0].m_bitsPerPixel = 8;
		break;
	}
	case 2: {
		m_countTextureFormats = 3;

		TextureFormat* textureFormats = new TextureFormat[m_countTextureFormats];
		m_textureFormats = textureFormats;
		if (m_textureFormats == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_textureFormats[1].m_redBitMask = 0;
		m_textureFormats[1].m_grnBitMask = 0;
		m_textureFormats[1].m_bluBitMask = 0;
		m_textureFormats[1].m_alpBitMask = 0;
		m_textureFormats[1].m_paletteMask = 0xff;
		m_textureFormats[1].m_intensityMask = 0;
		m_textureFormats[1].m_bitsPerPixel = 8;

		GolSurfaceFormat& textureFormat = m_renderTargetInfo->GetTextureFormat();
		if (textureFormat.GetGreenBitCount() == 6) {
			m_textureFormats[0].m_redBitMask = 0xf800;
			m_textureFormats[0].m_grnBitMask = 0x07e0;
			m_textureFormats[0].m_bluBitMask = 0x001f;
			m_textureFormats[0].m_alpBitMask = 0;
			m_textureFormats[0].m_paletteMask = 0;
			m_textureFormats[0].m_intensityMask = 0;
			m_textureFormats[0].m_bitsPerPixel = 16;
			m_textureFormats[2].m_redBitMask = 0xf8000000;
			m_textureFormats[2].m_grnBitMask = 0x07e00000;
			m_textureFormats[2].m_bluBitMask = 0x001f0000;
			m_textureFormats[2].m_alpBitMask = 0x000003ff;
			m_textureFormats[2].m_paletteMask = 0;
			m_textureFormats[2].m_intensityMask = 0;
			m_textureFormats[2].m_bitsPerPixel = 32;
		}
		else {
			m_textureFormats[0].m_redBitMask = 0x7c00;
			m_textureFormats[0].m_grnBitMask = 0x03e0;
			m_textureFormats[0].m_bluBitMask = 0x001f;
			m_textureFormats[0].m_alpBitMask = 0;
			m_textureFormats[0].m_paletteMask = 0;
			m_textureFormats[0].m_intensityMask = 0;
			m_textureFormats[0].m_bitsPerPixel = 16;
			m_textureFormats[2].m_redBitMask = 0x7c000000;
			m_textureFormats[2].m_grnBitMask = 0x03e00000;
			m_textureFormats[2].m_bluBitMask = 0x001f0000;
			m_textureFormats[2].m_alpBitMask = 0x000003ff;
			m_textureFormats[2].m_paletteMask = 0;
			m_textureFormats[2].m_intensityMask = 0;
			m_textureFormats[2].m_bitsPerPixel = 32;
		}
		break;
	}
	}
}

// FUNCTION: GOLDP 0x1000b7c0
GolD3DRenderDevice::TextureFormat::TextureFormat()
{
}

// FUNCTION: GOLDP 0x1000b7e0
HRESULT GolD3DRenderDevice::CountTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	LegoU32* count = static_cast<LegoU32*>(p_context);
	*count += 1;
	return TRUE;
}

// FUNCTION: GOLDP 0x1000b800
HRESULT GolD3DRenderDevice::EnumerateTextureFormatsCallback(DDPIXELFORMAT* p_format, void* p_context)
{
	GolD3DRenderDevice* self = static_cast<GolD3DRenderDevice*>(p_context);
	GolSurfaceFormat* format = &self->m_textureFormats[self->m_unk0x2c];
	self->m_unk0x2c += 1;

	if (p_format->dwFlags & DDPF_PALETTEINDEXED8) {
		format->m_paletteMask = 0xff;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_intensityMask = 0;
		format->m_bitsPerPixel = 8;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED4) {
		format->m_paletteMask = 0xf;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_intensityMask = 0;
		format->m_bitsPerPixel = 4;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED2) {
		format->m_paletteMask = 0x3;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_intensityMask = 0;
		format->m_bitsPerPixel = 2;
	}
	else if (p_format->dwFlags & DDPF_PALETTEINDEXED1) {
		format->m_paletteMask = 0x1;
		format->m_redBitMask = 0;
		format->m_grnBitMask = 0;
		format->m_bluBitMask = 0;
		format->m_intensityMask = 0;
		format->m_bitsPerPixel = 1;
	}
	else {
		format->m_redBitMask = p_format->dwRBitMask;
		format->m_grnBitMask = p_format->dwGBitMask;
		format->m_bluBitMask = p_format->dwBBitMask;
		format->m_paletteMask = 0;
		format->m_intensityMask = 0;
		LegoU32 bitCount = p_format->dwRGBBitCount;
		format->m_bitsPerPixel = bitCount;
	}
	if (p_format->dwFlags & DDPF_ALPHAPIXELS) {
		format->m_alpBitMask = p_format->dwRGBAlphaBitMask;
	}
	else {
		format->m_alpBitMask = 0;
	}

	return TRUE;
}

// STUB: GOLDP 0x1000b8e0
void GolD3DRenderDevice::FUN_1000b8e0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_currentMatrix->m_m[0][0] * position->m_x;
		vertex->sy = m_currentMatrix->m_m[0][1] * position->m_x;
		vertex->rhw = m_currentMatrix->m_m[0][3] * position->m_x;

		vertex->sx += m_currentMatrix->m_m[1][0] * position->m_y;
		vertex->sy += m_currentMatrix->m_m[1][1] * position->m_y;
		vertex->rhw += m_currentMatrix->m_m[1][3] * position->m_y;

		vertex->sx += m_currentMatrix->m_m[2][0] * position->m_z;
		vertex->sy += m_currentMatrix->m_m[2][1] * position->m_z;
		vertex->rhw += m_currentMatrix->m_m[2][3] * position->m_z;

		vertex->sx += m_currentMatrix->m_m[3][0];
		vertex->sy += m_currentMatrix->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_currentMatrix->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = *color;
		color++;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		uv++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000baa0
void GolD3DRenderDevice::FUN_1000baa0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_currentMatrix->m_m[0][0] * position->m_x;
		vertex->sy = m_currentMatrix->m_m[0][1] * position->m_x;
		vertex->rhw = m_currentMatrix->m_m[0][3] * position->m_x;

		vertex->sx += m_currentMatrix->m_m[1][0] * position->m_y;
		vertex->sy += m_currentMatrix->m_m[1][1] * position->m_y;
		vertex->rhw += m_currentMatrix->m_m[1][3] * position->m_y;

		vertex->sx += m_currentMatrix->m_m[2][0] * position->m_z;
		vertex->sy += m_currentMatrix->m_m[2][1] * position->m_z;
		vertex->rhw += m_currentMatrix->m_m[2][3] * position->m_z;

		vertex->sx += m_currentMatrix->m_m[3][0];
		vertex->sy += m_currentMatrix->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_currentMatrix->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = *color;
		color++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000bc40
void GolD3DRenderDevice::FUN_1000bc40(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = m_currentMatrix->m_m[0][0] * position->m_x;
		vertex->sy = m_currentMatrix->m_m[0][1] * position->m_x;
		vertex->rhw = m_currentMatrix->m_m[0][3] * position->m_x;

		vertex->sx += m_currentMatrix->m_m[1][0] * position->m_y;
		vertex->sy += m_currentMatrix->m_m[1][1] * position->m_y;
		vertex->rhw += m_currentMatrix->m_m[1][3] * position->m_y;

		vertex->sx += m_currentMatrix->m_m[2][0] * position->m_z;
		vertex->sy += m_currentMatrix->m_m[2][1] * position->m_z;
		vertex->rhw += m_currentMatrix->m_m[2][3] * position->m_z;

		vertex->sx += m_currentMatrix->m_m[3][0];
		vertex->sy += m_currentMatrix->m_m[3][1];
		vertex->rhw = 1.0f / (vertex->rhw + m_currentMatrix->m_m[3][3]);

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = (*color & 0x00ffffff) | alpha;
		color++;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		uv++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000be20
void GolD3DRenderDevice::FUN_1000be20(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++, color++, uv++, vertex++) {
		LegoFloat x = position->m_x * m_currentMatrix->m_m[0][0] + position->m_y * m_currentMatrix->m_m[1][0] +
					  position->m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		LegoFloat y = position->m_x * m_currentMatrix->m_m[0][1] + position->m_y * m_currentMatrix->m_m[1][1] +
					  position->m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		LegoFloat z = position->m_x * m_currentMatrix->m_m[0][2] + position->m_y * m_currentMatrix->m_m[1][2] +
					  position->m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		LegoFloat w = position->m_x * m_currentMatrix->m_m[0][3] + position->m_y * m_currentMatrix->m_m[1][3] +
					  position->m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		LegoFloat rhw = 1.0f / w;

		vertex->sx = x * rhw;
		vertex->sy = y * rhw;
		vertex->sz = z * rhw;
		vertex->rhw = rhw;
		vertex->color = *color;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000bfb0
void GolD3DRenderDevice::FUN_1000bfb0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4* matrix = m_currentMatrix;
	LegoFloat textureOffsetX = m_uvOffsetU;
	LegoFloat textureOffsetY = m_uvOffsetV;
	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = matrix->m_m[0][0] * position->m_x;
		vertex->rhw = matrix->m_m[0][3] * position->m_x;
		vertex->sy = matrix->m_m[0][1] * position->m_x;
		vertex->sz = matrix->m_m[0][2] * position->m_x;

		vertex->sx += matrix->m_m[1][0] * position->m_y;
		vertex->rhw += matrix->m_m[1][3] * position->m_y;
		vertex->sy += matrix->m_m[1][1] * position->m_y;
		vertex->sz += matrix->m_m[1][2] * position->m_y;

		vertex->sx += matrix->m_m[2][0] * position->m_z;
		vertex->rhw += matrix->m_m[2][3] * position->m_z;
		vertex->sy += matrix->m_m[2][1] * position->m_z;
		vertex->sz += matrix->m_m[2][2] * position->m_z;

		vertex->sx += matrix->m_m[3][0];
		vertex->rhw = 1.0f / (vertex->rhw + matrix->m_m[3][3]);
		vertex->sy += matrix->m_m[3][1];
		vertex->sz += matrix->m_m[3][2];

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = *color;
		color++;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex->sz *= vertex->rhw;
		vertex->tu = uv->m_x + textureOffsetX;
		vertex->tv = uv->m_y + textureOffsetY;
		uv++;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000c160
void GolD3DRenderDevice::FUN_1000c160(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++, color++, vertex++) {
		LegoFloat x = position->m_x * m_currentMatrix->m_m[0][0] + position->m_y * m_currentMatrix->m_m[1][0] +
					  position->m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		LegoFloat y = position->m_x * m_currentMatrix->m_m[0][1] + position->m_y * m_currentMatrix->m_m[1][1] +
					  position->m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		LegoFloat z = position->m_x * m_currentMatrix->m_m[0][2] + position->m_y * m_currentMatrix->m_m[1][2] +
					  position->m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		LegoFloat w = position->m_x * m_currentMatrix->m_m[0][3] + position->m_y * m_currentMatrix->m_m[1][3] +
					  position->m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		LegoFloat rhw = 1.0f / w;

		vertex->sx = x * rhw;
		vertex->sy = y * rhw;
		vertex->sz = z * rhw;
		vertex->rhw = rhw;
		vertex->color = *color;
		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000c2d0
void GolD3DRenderDevice::FUN_1000c2d0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++, color++, uv++, vertex++) {
		LegoFloat x = position->m_x * m_currentMatrix->m_m[0][0] + position->m_y * m_currentMatrix->m_m[1][0] +
					  position->m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		LegoFloat y = position->m_x * m_currentMatrix->m_m[0][1] + position->m_y * m_currentMatrix->m_m[1][1] +
					  position->m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		LegoFloat z = position->m_x * m_currentMatrix->m_m[0][2] + position->m_y * m_currentMatrix->m_m[1][2] +
					  position->m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		LegoFloat w = position->m_x * m_currentMatrix->m_m[0][3] + position->m_y * m_currentMatrix->m_m[1][3] +
					  position->m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		LegoFloat rhw = 1.0f / w;

		vertex->sx = x * rhw;
		vertex->sy = y * rhw;
		vertex->sz = z * rhw;
		vertex->rhw = rhw;
		vertex->color = (*color & 0x00ffffff) | alpha;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000c470
void GolD3DRenderDevice::FUN_1000c470(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32* color = m_sourceColors + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	LegoFloat textureOffsetX = m_uvOffsetU;
	LegoFloat textureOffsetY = m_uvOffsetV;
	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++, color++, uv++, vertex++) {
		LegoFloat x = position->m_x * m_currentMatrix->m_m[0][0] + position->m_y * m_currentMatrix->m_m[1][0] +
					  position->m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		LegoFloat y = position->m_x * m_currentMatrix->m_m[0][1] + position->m_y * m_currentMatrix->m_m[1][1] +
					  position->m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		LegoFloat z = position->m_x * m_currentMatrix->m_m[0][2] + position->m_y * m_currentMatrix->m_m[1][2] +
					  position->m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		LegoFloat w = position->m_x * m_currentMatrix->m_m[0][3] + position->m_y * m_currentMatrix->m_m[1][3] +
					  position->m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		LegoFloat rhw = 1.0f / w;

		vertex->sx = x * rhw;
		vertex->sy = y * rhw;
		vertex->sz = z * rhw;
		vertex->rhw = rhw;
		vertex->color = (*color & 0x00ffffff) | alpha;
		vertex->tu = uv->m_x + textureOffsetX;
		vertex->tv = uv->m_y + textureOffsetY;
		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000c630
void GolD3DRenderDevice::FUN_1000c630(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_sourceColors[sourceIndex];
		vertex.tu = uv[i].m_x;
		vertex.tv = uv[i].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000c880
void GolD3DRenderDevice::FUN_1000c880(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_sourceColors[sourceIndex];
		vertex.tu = m_sourceTexCoords[sourceIndex].m_x + m_uvOffsetU;
		vertex.tv = m_sourceTexCoords[sourceIndex].m_y + m_uvOffsetV;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000caf0
void GolD3DRenderDevice::FUN_1000caf0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_sourceColors[sourceIndex];
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000cd20
void GolD3DRenderDevice::FUN_1000cd20(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = (m_sourceColors[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = uv[i].m_x;
		vertex.tv = uv[i].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000cf90
void GolD3DRenderDevice::FUN_1000cf90(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	LegoU32 alpha = (m_alpha & 0xff) << 24;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = (m_sourceColors[sourceIndex] & 0x00ffffff) | alpha;
		vertex.tu = m_sourceTexCoords[sourceIndex].m_x + m_uvOffsetU;
		vertex.tv = m_sourceTexCoords[sourceIndex].m_y + m_uvOffsetV;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// FUNCTION: GOLDP 0x1000d210
void GolD3DRenderDevice::FUN_1000d210(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	const GolVec3* normal = m_sourceNormals + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	for (; position < positionEnd; position++, normal++, uv++, vertex++) {
		vertex->m_x = (m_currentMatrix->m_m[0][0] * position->m_x) * m_currentScale;
		vertex->m_y = (m_currentMatrix->m_m[0][1] * position->m_x) * m_currentScale;
		vertex->m_z = (m_currentMatrix->m_m[0][2] * position->m_x) * m_currentScale;

		vertex->m_x += (m_currentMatrix->m_m[1][0] * position->m_y) * m_currentScale;
		vertex->m_y += (m_currentMatrix->m_m[1][1] * position->m_y) * m_currentScale;
		vertex->m_z += (m_currentMatrix->m_m[1][2] * position->m_y) * m_currentScale;

		vertex->m_x += (m_currentMatrix->m_m[2][0] * position->m_z) * m_currentScale;
		vertex->m_y += (m_currentMatrix->m_m[2][1] * position->m_z) * m_currentScale;
		vertex->m_z += (m_currentMatrix->m_m[2][2] * position->m_z) * m_currentScale;

		vertex->m_x += m_currentMatrix->m_m[3][0];
		vertex->m_y += m_currentMatrix->m_m[3][1];
		vertex->m_z += m_currentMatrix->m_m[3][2];

		vertex->m_nx = m_currentMatrix->m_m[0][0] * normal->m_x;
		vertex->m_ny = m_currentMatrix->m_m[0][1] * normal->m_y;
		vertex->m_nz = m_currentMatrix->m_m[0][2] * normal->m_z;

		vertex->m_nx += m_currentMatrix->m_m[1][0] * normal->m_x;
		vertex->m_ny += m_currentMatrix->m_m[1][1] * normal->m_y;
		vertex->m_nz += m_currentMatrix->m_m[1][2] * normal->m_z;

		vertex->m_nx += m_currentMatrix->m_m[2][0] * normal->m_x;
		vertex->m_ny += m_currentMatrix->m_m[2][1] * normal->m_y;
		vertex->m_nz += m_currentMatrix->m_m[2][2] * normal->m_z;

		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;
	}

	m_drawCommand.m_outputFirst = p_outputFirst;
	m_drawCommand.m_firstVertex = p_firstVertex;
	m_drawCommand.m_vertexCount = p_vertexCount;
	m_renderState->ProcessVertices(&m_drawCommand);
}

// STUB: GOLDP 0x1000d440
void GolD3DRenderDevice::FUN_1000d440(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_sourceColors + p_firstVertex;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	while (position < positionEnd) {
		vertex->m_x = m_currentMatrix->m_m[0][0] * position->m_x;
		vertex->m_y = m_currentMatrix->m_m[0][1] * position->m_x;
		vertex->m_z = m_currentMatrix->m_m[0][2] * position->m_x;

		vertex->m_x += m_currentMatrix->m_m[1][0] * position->m_y;
		vertex->m_y += m_currentMatrix->m_m[1][1] * position->m_y;
		vertex->m_z += m_currentMatrix->m_m[1][2] * position->m_y;

		vertex->m_x += m_currentMatrix->m_m[2][0] * position->m_z;
		vertex->m_y += m_currentMatrix->m_m[2][1] * position->m_z;
		vertex->m_z += m_currentMatrix->m_m[2][2] * position->m_z;

		vertex->m_x += m_currentMatrix->m_m[3][0];
		vertex->m_y += m_currentMatrix->m_m[3][1];
		vertex->m_z += m_currentMatrix->m_m[3][2];

		LegoU32 sourceColor = *color;
		LegoU8* destColor = reinterpret_cast<LegoU8*>(&vertex->m_color);
		destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
		destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
		destColor[2] = static_cast<LegoU8>(sourceColor);
		destColor[3] = static_cast<LegoU8>(sourceColor >> 24);
		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;

		position++;
		uv++;
		color++;
		vertex++;
	}

	m_drawCommand.m_outputFirst = p_outputFirst;
	m_drawCommand.m_firstVertex = p_firstVertex;
	m_drawCommand.m_vertexCount = p_vertexCount;
	m_renderState->ProcessVertices(&m_drawCommand);
}

// STUB: GOLDP 0x1000d5d0
void GolD3DRenderDevice::FUN_1000d5d0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32* color = m_sourceColors + p_firstVertex;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	CommandVertex* vertex = m_unk0xc428c + p_outputFirst;

	while (position < positionEnd) {
		vertex->m_x = m_currentMatrix->m_m[0][0] * position->m_x;
		vertex->m_y = m_currentMatrix->m_m[0][1] * position->m_x;
		vertex->m_z = m_currentMatrix->m_m[0][2] * position->m_x;

		vertex->m_x += m_currentMatrix->m_m[1][0] * position->m_y;
		vertex->m_y += m_currentMatrix->m_m[1][1] * position->m_y;
		vertex->m_z += m_currentMatrix->m_m[1][2] * position->m_y;

		vertex->m_x += m_currentMatrix->m_m[2][0] * position->m_z;
		vertex->m_y += m_currentMatrix->m_m[2][1] * position->m_z;
		vertex->m_z += m_currentMatrix->m_m[2][2] * position->m_z;

		vertex->m_x += m_currentMatrix->m_m[3][0];
		vertex->m_y += m_currentMatrix->m_m[3][1];
		vertex->m_z += m_currentMatrix->m_m[3][2];

		LegoU32 sourceColor = *color;
		LegoU8* destColor = reinterpret_cast<LegoU8*>(&vertex->m_color);
		destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
		destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
		destColor[2] = static_cast<LegoU8>(sourceColor);
		destColor[3] = static_cast<LegoU8>(m_alpha);
		vertex->m_u = uv->m_x;
		vertex->m_v = uv->m_y;

		position++;
		uv++;
		color++;
		vertex++;
	}

	m_drawCommand.m_outputFirst = p_outputFirst;
	m_drawCommand.m_firstVertex = p_firstVertex;
	m_drawCommand.m_vertexCount = p_vertexCount;
	m_renderState->ProcessVertices(&m_drawCommand);
}

// STUB: GOLDP 0x1000d760
void GolD3DRenderDevice::FUN_1000d760(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	{
		const GolVec3* position = m_sourcePositions + p_firstVertex;
		const GolVec3* positionEnd = position + p_vertexCount;
		LegoU32* color = m_sourceColors + p_firstVertex;
		const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
		CommandVertex* commandVertex = m_unk0xc428c + p_outputFirst;

		while (position < positionEnd) {
			commandVertex->m_x = m_currentMatrix->m_m[0][0] * position->m_x;
			commandVertex->m_y = m_currentMatrix->m_m[0][1] * position->m_x;
			commandVertex->m_z = m_currentMatrix->m_m[0][2] * position->m_x;

			commandVertex->m_x += m_currentMatrix->m_m[1][0] * position->m_y;
			commandVertex->m_y += m_currentMatrix->m_m[1][1] * position->m_y;
			commandVertex->m_z += m_currentMatrix->m_m[1][2] * position->m_y;

			commandVertex->m_x += m_currentMatrix->m_m[2][0] * position->m_z;
			commandVertex->m_y += m_currentMatrix->m_m[2][1] * position->m_z;
			commandVertex->m_z += m_currentMatrix->m_m[2][2] * position->m_z;

			commandVertex->m_x += m_currentMatrix->m_m[3][0];
			commandVertex->m_y += m_currentMatrix->m_m[3][1];
			commandVertex->m_z += m_currentMatrix->m_m[3][2];

			LegoU32 sourceColor = *color;
			LegoU8* destColor = reinterpret_cast<LegoU8*>(&commandVertex->m_color);
			destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
			destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
			destColor[2] = static_cast<LegoU8>(sourceColor);
			destColor[3] = static_cast<LegoU8>(sourceColor >> 24);
			commandVertex->m_u = uv->m_x;
			commandVertex->m_v = uv->m_y;

			position++;
			uv++;
			color++;
			commandVertex++;
		}
	}

	m_drawCommand.m_outputFirst = p_outputFirst;
	m_drawCommand.m_firstVertex = p_firstVertex;
	m_drawCommand.m_vertexCount = p_vertexCount;
	m_renderState->ProcessVerticesPrelit(&m_drawCommand);

	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	m_unk0xc3848 = cacheIndex + p_vertexCount;
	D3DTLVERTEX* vertex = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	CommandVertex* source = m_unk0xc428c + p_outputFirst;
	CommandVertex* sourceEnd = source + p_vertexCount;

	for (; source < sourceEnd; cache++, vertex++, cacheIndex++) {
		cache->m_x = source->m_x * m_viewProjectionMatrix->m_m[0][0] + source->m_y * m_viewProjectionMatrix->m_m[1][0] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][0] + m_viewProjectionMatrix->m_m[3][0];
		cache->m_y = source->m_x * m_viewProjectionMatrix->m_m[0][1] + source->m_y * m_viewProjectionMatrix->m_m[1][1] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][1] + m_viewProjectionMatrix->m_m[3][1];
		cache->m_z = source->m_x * m_viewProjectionMatrix->m_m[0][2] + source->m_y * m_viewProjectionMatrix->m_m[1][2] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][2] + m_viewProjectionMatrix->m_m[3][2];
		cache->m_w = source->m_x * m_viewProjectionMatrix->m_m[0][3] + source->m_y * m_viewProjectionMatrix->m_m[1][3] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][3] + m_viewProjectionMatrix->m_m[3][3];
		cache->m_unk0x10 = cacheIndex;
		cache->m_clipFlags = BuildModelClipFlags(*cache);

		vertex->rhw = 1.0f / cache->m_w;
		vertex->sx = cache->m_x * vertex->rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex->sy = cache->m_y * vertex->rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex->sz = cache->m_z * vertex->rhw;
		const LegoU8* sourceColor = reinterpret_cast<const LegoU8*>(&source->m_color);
		vertex->color = (sourceColor[3] << 24) | (sourceColor[0] << 16) | (sourceColor[1] << 8) | sourceColor[2];
		vertex->tu = source->m_u + m_uvOffsetU;
		vertex->tv = source->m_v + m_uvOffsetV;
	}
}

// STUB: GOLDP 0x1000dbb0
void GolD3DRenderDevice::FUN_1000dbb0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	{
		const GolVec3* position = m_sourcePositions + p_firstVertex;
		const GolVec3* positionEnd = position + p_vertexCount;
		LegoU32* color = m_sourceColors + p_firstVertex;
		const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
		CommandVertex* commandVertex = m_unk0xc428c + p_outputFirst;

		while (position < positionEnd) {
			commandVertex->m_x = m_currentMatrix->m_m[0][0] * position->m_x;
			commandVertex->m_y = m_currentMatrix->m_m[0][1] * position->m_x;
			commandVertex->m_z = m_currentMatrix->m_m[0][2] * position->m_x;

			commandVertex->m_x += m_currentMatrix->m_m[1][0] * position->m_y;
			commandVertex->m_y += m_currentMatrix->m_m[1][1] * position->m_y;
			commandVertex->m_z += m_currentMatrix->m_m[1][2] * position->m_y;

			commandVertex->m_x += m_currentMatrix->m_m[2][0] * position->m_z;
			commandVertex->m_y += m_currentMatrix->m_m[2][1] * position->m_z;
			commandVertex->m_z += m_currentMatrix->m_m[2][2] * position->m_z;

			commandVertex->m_x += m_currentMatrix->m_m[3][0];
			commandVertex->m_y += m_currentMatrix->m_m[3][1];
			commandVertex->m_z += m_currentMatrix->m_m[3][2];

			LegoU32 sourceColor = *color;
			LegoU8* destColor = reinterpret_cast<LegoU8*>(&commandVertex->m_color);
			destColor[0] = static_cast<LegoU8>(sourceColor >> 16);
			destColor[1] = static_cast<LegoU8>(sourceColor >> 8);
			destColor[2] = static_cast<LegoU8>(sourceColor);
			destColor[3] = static_cast<LegoU8>(m_alpha);
			commandVertex->m_u = uv->m_x;
			commandVertex->m_v = uv->m_y;

			position++;
			uv++;
			color++;
			commandVertex++;
		}
	}

	m_drawCommand.m_outputFirst = p_outputFirst;
	m_drawCommand.m_firstVertex = p_firstVertex;
	m_drawCommand.m_vertexCount = p_vertexCount;
	m_renderState->ProcessVerticesPrelit(&m_drawCommand);

	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	m_unk0xc3848 = cacheIndex + p_vertexCount;
	D3DTLVERTEX* vertex = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	CommandVertex* source = m_unk0xc428c + p_outputFirst;
	CommandVertex* sourceEnd = source + p_vertexCount;
	LegoU32 alpha = (m_alpha & 0xff) << 24;

	for (; source < sourceEnd; source++, cache++, vertex++, cacheIndex++) {
		cache->m_x = source->m_x * m_viewProjectionMatrix->m_m[0][0] + source->m_y * m_viewProjectionMatrix->m_m[1][0] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][0] + m_viewProjectionMatrix->m_m[3][0];
		cache->m_y = source->m_x * m_viewProjectionMatrix->m_m[0][1] + source->m_y * m_viewProjectionMatrix->m_m[1][1] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][1] + m_viewProjectionMatrix->m_m[3][1];
		cache->m_z = source->m_x * m_viewProjectionMatrix->m_m[0][2] + source->m_y * m_viewProjectionMatrix->m_m[1][2] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][2] + m_viewProjectionMatrix->m_m[3][2];
		cache->m_w = source->m_x * m_viewProjectionMatrix->m_m[0][3] + source->m_y * m_viewProjectionMatrix->m_m[1][3] +
					 source->m_z * m_viewProjectionMatrix->m_m[2][3] + m_viewProjectionMatrix->m_m[3][3];
		cache->m_unk0x10 = cacheIndex;
		cache->m_clipFlags = BuildModelClipFlags(*cache);

		vertex->rhw = 1.0f / cache->m_w;
		vertex->sx = cache->m_x * vertex->rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex->sy = cache->m_y * vertex->rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex->sz = cache->m_z * vertex->rhw;
		const LegoU8* sourceColor = reinterpret_cast<const LegoU8*>(&source->m_color);
		vertex->color = alpha | (sourceColor[0] << 16) | (sourceColor[1] << 8) | sourceColor[2];
		vertex->tu = source->m_u + m_uvOffsetU;
		vertex->tv = source->m_v + m_uvOffsetV;
	}
}

// STUB: GOLDP 0x1000e010
void GolD3DRenderDevice::FUN_1000e010(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4* matrix = m_currentMatrix;
	LegoU32 color = m_unk0xc83fc;
	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = matrix->m_m[0][0] * position->m_x;
		vertex->rhw = matrix->m_m[0][3] * position->m_x;
		vertex->sy = matrix->m_m[0][1] * position->m_x;
		vertex->sz = matrix->m_m[0][2] * position->m_x;

		vertex->sx += matrix->m_m[1][0] * position->m_y;
		vertex->rhw += matrix->m_m[1][3] * position->m_y;
		vertex->sy += matrix->m_m[1][1] * position->m_y;
		vertex->sz += matrix->m_m[1][2] * position->m_y;

		vertex->sx += matrix->m_m[2][0] * position->m_z;
		vertex->rhw += matrix->m_m[2][3] * position->m_z;
		vertex->sy += matrix->m_m[2][1] * position->m_z;
		vertex->sz += matrix->m_m[2][2] * position->m_z;

		vertex->sx += matrix->m_m[3][0];
		vertex->rhw = 1.0f / (vertex->rhw + matrix->m_m[3][3]);
		vertex->sy += matrix->m_m[3][1];
		vertex->sz += matrix->m_m[3][2];

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = color;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex->sz *= vertex->rhw;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000e180
void GolD3DRenderDevice::FUN_1000e180(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4* matrix = m_currentMatrix;
	LegoU32 color = m_unk0xc83fc;
	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = matrix->m_m[0][0] * position->m_x;
		vertex->rhw = matrix->m_m[0][3] * position->m_x;
		vertex->sy = matrix->m_m[0][1] * position->m_x;
		vertex->sz = matrix->m_m[0][2] * position->m_x;

		vertex->sx += matrix->m_m[1][0] * position->m_y;
		vertex->rhw += matrix->m_m[1][3] * position->m_y;
		vertex->sy += matrix->m_m[1][1] * position->m_y;
		vertex->sz += matrix->m_m[1][2] * position->m_y;

		vertex->sx += matrix->m_m[2][0] * position->m_z;
		vertex->rhw += matrix->m_m[2][3] * position->m_z;
		vertex->sy += matrix->m_m[2][1] * position->m_z;
		vertex->sz += matrix->m_m[2][2] * position->m_z;

		vertex->sx += matrix->m_m[3][0];
		vertex->rhw = 1.0f / (vertex->rhw + matrix->m_m[3][3]);
		vertex->sy += matrix->m_m[3][1];
		vertex->sz += matrix->m_m[3][2];

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = color;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex->sz *= vertex->rhw;
		vertex->tu = uv->m_x;
		vertex->tv = uv->m_y;
		uv++;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000e310
void GolD3DRenderDevice::FUN_1000e310(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000e540
void GolD3DRenderDevice::FUN_1000e540(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_sourceTexCoords[sourceIndex].m_x;
		vertex.tv = m_sourceTexCoords[sourceIndex].m_y;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// STUB: GOLDP 0x1000e790
void GolD3DRenderDevice::FUN_1000e790(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* position = m_sourcePositions + p_firstVertex;
	const GolVec3* positionEnd = position + p_vertexCount;
	const GolVec2* uv = m_sourceTexCoords + p_firstVertex;
	LegoU32 outputIndex = (m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4* matrix = m_currentMatrix;
	LegoU32 color = m_unk0xc83fc;
	LegoFloat textureOffsetX = m_uvOffsetU;
	LegoFloat textureOffsetY = m_uvOffsetV;
	D3DTLVERTEX* vertex = vertices;
	for (; position < positionEnd; position++) {
		vertex->sx = matrix->m_m[0][0] * position->m_x;
		vertex->rhw = matrix->m_m[0][3] * position->m_x;
		vertex->sy = matrix->m_m[0][1] * position->m_x;
		vertex->sz = matrix->m_m[0][2] * position->m_x;

		vertex->sx += matrix->m_m[1][0] * position->m_y;
		vertex->rhw += matrix->m_m[1][3] * position->m_y;
		vertex->sy += matrix->m_m[1][1] * position->m_y;
		vertex->sz += matrix->m_m[1][2] * position->m_y;

		vertex->sx += matrix->m_m[2][0] * position->m_z;
		vertex->rhw += matrix->m_m[2][3] * position->m_z;
		vertex->sy += matrix->m_m[2][1] * position->m_z;
		vertex->sz += matrix->m_m[2][2] * position->m_z;

		vertex->sx += matrix->m_m[3][0];
		vertex->rhw = 1.0f / (vertex->rhw + matrix->m_m[3][3]);
		vertex->sy += matrix->m_m[3][1];
		vertex->sz += matrix->m_m[3][2];

		vertexMap[1] = static_cast<LegoU16>(vertexMap[0] + 1);
		vertexMap++;
		vertex->color = color;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		vertex->sz *= vertex->rhw;
		vertex->tu = uv->m_x + textureOffsetX;
		vertex->tv = uv->m_y + textureOffsetY;
		uv++;
		vertex++;
	}

	*vertexMap = savedMapEntry;
}

// STUB: GOLDP 0x1000e930
void GolD3DRenderDevice::FUN_1000e930(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	LegoU32 cacheIndex = m_unk0xc3848;
	LegoU32 outputIndex = (cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c);
	D3DTLVERTEX* vertices = m_unk0x348 + outputIndex;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	LegoU32 savedCacheIndex = cache[p_vertexCount].m_unk0x10;
	cache[0].m_unk0x10 = cacheIndex;
	m_unk0xc3848 += p_vertexCount;

	const GolMatrix4& matrix = *m_currentMatrix;
	for (LegoU32 i = 0; i < p_vertexCount; i++, cacheIndex++) {
		LegoU32 sourceIndex = p_firstVertex + i;
		const GolVec3& source = m_sourcePositions[sourceIndex];
		VertexCacheEntry& cacheEntry = cache[i];
		D3DTLVERTEX& vertex = vertices[i];

		cacheEntry.m_x = source.m_x * m_currentMatrix->m_m[0][0] + source.m_y * m_currentMatrix->m_m[1][0] +
						 source.m_z * m_currentMatrix->m_m[2][0] + m_currentMatrix->m_m[3][0];
		cacheEntry.m_y = source.m_x * m_currentMatrix->m_m[0][1] + source.m_y * m_currentMatrix->m_m[1][1] +
						 source.m_z * m_currentMatrix->m_m[2][1] + m_currentMatrix->m_m[3][1];
		cacheEntry.m_z = source.m_x * m_currentMatrix->m_m[0][2] + source.m_y * m_currentMatrix->m_m[1][2] +
						 source.m_z * m_currentMatrix->m_m[2][2] + m_currentMatrix->m_m[3][2];
		cacheEntry.m_w = source.m_x * m_currentMatrix->m_m[0][3] + source.m_y * m_currentMatrix->m_m[1][3] +
						 source.m_z * m_currentMatrix->m_m[2][3] + m_currentMatrix->m_m[3][3];
		cacheEntry.m_unk0x10 = cacheIndex;
		cacheEntry.m_clipFlags = BuildModelClipFlags(cacheEntry);

		vertex.rhw = 1.0f / cacheEntry.m_w;
		vertex.sx = cacheEntry.m_x * vertex.rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex.sy = cacheEntry.m_y * vertex.rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex.sz = cacheEntry.m_z * vertex.rhw;
		vertex.color = m_unk0xc83fc;
		vertex.tu = m_sourceTexCoords[sourceIndex].m_x + m_uvOffsetU;
		vertex.tv = m_sourceTexCoords[sourceIndex].m_y + m_uvOffsetV;
	}

	cache[p_vertexCount].m_unk0x10 = savedCacheIndex;
}

// FUNCTION: GOLDP 0x1000eb90
void GolD3DRenderDevice::FUN_1000eb90(undefined4 p_firstTriangle, undefined4 p_triangleCount, undefined4)
{
	m_materialCommand.m_material = m_drawCommand.m_material;
	m_materialCommand.m_firstTriangle = p_firstTriangle;
	m_materialCommand.m_triangleCount = p_triangleCount;
	m_renderState->ProcessMaterial(&m_materialCommand);
}

// FUNCTION: GOLDP 0x1000ebd0
void GolD3DRenderDevice::FUN_1000ebd0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32 p_lastVertex)
{
	LegoU8* triangle = m_sourceIndices + (p_firstTriangle * 4);
	LegoU8* end = m_sourceIndices + ((p_firstTriangle + p_triangleCount) * 4);
	LegoU16* indices = m_unk0xc4c20;

	for (; triangle < end; triangle += 4) {
		LegoU32 index2 = triangle[2];
		LegoU32 index0 = triangle[0];
		LegoU32 index1 = triangle[1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[index2];
		D3DTLVERTEX* vertex1 = &m_unk0x348[index1];
		D3DTLVERTEX* vertex0 = &m_unk0x348[index0];

		if (((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx)) -
				((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) <
			0.0f) {
			*indices++ = index2;
			*indices++ = index1;
			*indices++ = index0;
		}
	}

	if (indices != m_unk0xc4c20) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0x348,
			p_lastVertex + 1,
			m_unk0xc4c20,
			indices - m_unk0xc4c20,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x1000ece0
void GolD3DRenderDevice::FUN_1000ece0(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32 p_lastVertex)
{
	LegoU8* triangle = m_sourceIndices + (p_firstTriangle * 4);
	LegoU8* end = m_sourceIndices + ((p_firstTriangle + p_triangleCount) * 4);
	LegoU16* indices = m_unk0xc4c20;

	for (; triangle < end; triangle += 4) {
		LegoU32 index2 = triangle[2];
		LegoU32 index0 = triangle[0];
		LegoU32 index1 = triangle[1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[index2];
		D3DTLVERTEX* vertex1 = &m_unk0x348[index1];
		D3DTLVERTEX* vertex0 = &m_unk0x348[index0];

		if (((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx)) -
				((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) >
			0.0f) {
			*indices++ = index2;
			*indices++ = index1;
			*indices++ = index0;
		}
	}

	if (indices != m_unk0xc4c20) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0x348,
			p_lastVertex + 1,
			m_unk0xc4c20,
			indices - m_unk0xc4c20,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// STUB: GOLDP 0x1000edf0
void GolD3DRenderDevice::FUN_1000edf0(undefined4 p_firstTriangle, undefined4 p_triangleCount, undefined4 p_lastVertex)
{
	enum {
		c_clippedIndexOffset = (0xc50a0 - 0xc4c20) / sizeof(LegoU16),
		c_clippedIndexCapacity = (0xc53a0 - 0xc50a0) / sizeof(LegoU16),
	};

	LegoU32 firstTriangle = p_firstTriangle;
	LegoU32 triangleCount = p_triangleCount;
	LegoU32 lastVertex = p_lastVertex;
	LegoFloat nearClip = m_currentCamera->m_nearClip;
	LegoFloat farClip = m_currentCamera->m_farClip;
	LegoU8* triangle = m_sourceIndices + (firstTriangle * 4);
	LegoU8* triangleEnd = m_sourceIndices + ((firstTriangle + triangleCount) * 4);
	LegoU16* directIndices = m_unk0xc4c20;
	LegoU16* clippedIndices = m_unk0xc4c20 + c_clippedIndexOffset;
	LegoU32 directIndexCount = 0;
	LegoU32 clippedIndexCount = 0;
	LegoU32 clippedVertexCount = 0;
	LegoBool32 flipped = ((m_activeMaterialFlags | m_forcedMaterialFlags) & GolMaterial::c_flagRotateVertices) != 0;
	static const LegoU32 g_clipPlanes[] = {0x10, 0x20, 0x01, 0x02, 0x04, 0x08};

	for (; triangle < triangleEnd; triangle += 4) {
		LegoU32 triangleIndex0 = triangle[0];
		LegoU32 triangleIndex1 = triangle[1];
		LegoU32 triangleIndex2 = triangle[2];
		VertexCacheEntry* cache0 = &m_unk0xc38ec[triangleIndex0];
		VertexCacheEntry* cache1 = &m_unk0xc38ec[triangleIndex1];
		VertexCacheEntry* cache2 = &m_unk0xc38ec[triangleIndex2];

		if (cache0->m_clipFlags & cache1->m_clipFlags & cache2->m_clipFlags) {
			continue;
		}

		LegoU32 unionFlags = cache0->m_clipFlags | cache1->m_clipFlags | cache2->m_clipFlags;
		if (unionFlags == 0) {
			D3DTLVERTEX* vertex0 = &m_unk0x348[triangleIndex0];
			D3DTLVERTEX* vertex1 = &m_unk0x348[triangleIndex1];
			D3DTLVERTEX* vertex2 = &m_unk0x348[triangleIndex2];
			LegoFloat area = ComputeScreenArea(*vertex0, *vertex1, *vertex2);

			if ((!flipped && area <= 0.0f) || (flipped && area >= 0.0f)) {
				continue;
			}

			if (flipped) {
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex0);
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex1);
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex2);
			}
			else {
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex2);
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex1);
				directIndices[directIndexCount++] = static_cast<LegoU16>(triangleIndex0);
			}
			continue;
		}

		VertexCacheEntry* cacheA[16];
		VertexCacheEntry* cacheB[16];
		D3DTLVERTEX* vertexA[16];
		D3DTLVERTEX* vertexB[16];
		VertexCacheEntry** inputCache = cacheA;
		VertexCacheEntry** outputCache = cacheB;
		D3DTLVERTEX** inputVertex = vertexA;
		D3DTLVERTEX** outputVertex = vertexB;
		VertexCacheEntry* nextClipCache = m_unk0xc38ec + 0x40;
		D3DTLVERTEX* nextClipVertex = m_unk0x348 + 0x40;
		LegoU32 vertexCount = 3;

		if (flipped) {
			inputCache[0] = cache2;
			inputCache[1] = cache1;
			inputCache[2] = cache0;
			inputVertex[0] = &m_unk0x348[triangleIndex2];
			inputVertex[1] = &m_unk0x348[triangleIndex1];
			inputVertex[2] = &m_unk0x348[triangleIndex0];
		}
		else {
			inputCache[0] = cache0;
			inputCache[1] = cache1;
			inputCache[2] = cache2;
			inputVertex[0] = &m_unk0x348[triangleIndex0];
			inputVertex[1] = &m_unk0x348[triangleIndex1];
			inputVertex[2] = &m_unk0x348[triangleIndex2];
		}

		for (LegoU32 planeIndex = 0; planeIndex < sizeOfArray(g_clipPlanes); planeIndex++) {
			LegoU32 plane = g_clipPlanes[planeIndex];
			if (!(unionFlags & plane)) {
				continue;
			}

			LegoU32 outputCount = 0;
			LegoU32 previousIndex = vertexCount - 1;
			LegoBool32 previousInside = (inputCache[previousIndex]->m_clipFlags & plane) == 0;
			LegoFloat previousDistance = GetClipDistance(*inputCache[previousIndex], plane, farClip);
			unionFlags = 0;

			for (LegoU32 i = 0; i < vertexCount; i++) {
				LegoBool32 currentInside = (inputCache[i]->m_clipFlags & plane) == 0;
				LegoFloat currentDistance = GetClipDistance(*inputCache[i], plane, farClip);

				if (previousInside != currentInside) {
					LegoFloat delta = previousDistance - currentDistance;
					LegoFloat amount = 0.0f;
					if (delta != 0.0f) {
						amount = previousDistance / delta;
					}

					if (outputCount >= sizeOfArray(cacheB)) {
						vertexCount = 0;
						break;
					}

					VertexCacheEntry* clipCache = nextClipCache++;
					D3DTLVERTEX* clipVertex = nextClipVertex++;
					InterpolateClipVertex(
						*inputCache[previousIndex],
						*inputCache[i],
						*inputVertex[previousIndex],
						*inputVertex[i],
						amount,
						*clipCache,
						*clipVertex
					);
					ProjectClipVertexForPlane(*clipCache, m_viewportMetrics, *clipVertex, plane, nearClip, farClip);
					outputCache[outputCount] = clipCache;
					outputVertex[outputCount] = clipVertex;
					unionFlags |= clipCache->m_clipFlags;
					outputCount++;
				}

				if (currentInside) {
					if (outputCount >= sizeOfArray(cacheB)) {
						vertexCount = 0;
						break;
					}

					outputCache[outputCount] = inputCache[i];
					outputVertex[outputCount] = inputVertex[i];
					unionFlags |= outputCache[outputCount]->m_clipFlags;
					outputCount++;
				}

				previousIndex = i;
				previousInside = currentInside;
				previousDistance = currentDistance;
			}

			if (vertexCount == 0 || outputCount < 3) {
				vertexCount = 0;
				break;
			}

			vertexCount = outputCount;
			VertexCacheEntry** tempCache = inputCache;
			inputCache = outputCache;
			outputCache = tempCache;
			D3DTLVERTEX** tempVertex = inputVertex;
			inputVertex = outputVertex;
			outputVertex = tempVertex;
		}

		if (vertexCount < 3) {
			continue;
		}

		LegoFloat area = ComputeScreenArea(*inputVertex[0], *inputVertex[1], *inputVertex[2]);
		if (area <= 0.0f) {
			continue;
		}

		LegoU32 polygonIndexCount = (vertexCount - 2) * 3;
		if (clippedVertexCount + 0x0e >= sizeOfArray(m_unk0xc53a0) ||
			clippedIndexCount + polygonIndexCount >= c_clippedIndexCapacity) {
			if (clippedIndexCount != 0) {
				m_d3dDevice->DrawIndexedPrimitive(
					D3DPT_TRIANGLELIST,
					D3DFVF_TLVERTEX,
					m_unk0xc53a0,
					clippedVertexCount,
					clippedIndices,
					clippedIndexCount,
					D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
				);
			}

			clippedVertexCount = 0;
			clippedIndexCount = 0;
		}

		LegoU32 firstClippedVertex = clippedVertexCount;
		for (LegoU32 i = 0; i < vertexCount; i++) {
			m_unk0xc53a0[clippedVertexCount++] = *inputVertex[i];
		}

		for (LegoU32 j = 1; j + 1 < vertexCount; j++) {
			clippedIndices[clippedIndexCount++] = static_cast<LegoU16>(firstClippedVertex);
			clippedIndices[clippedIndexCount++] = static_cast<LegoU16>(firstClippedVertex + j);
			clippedIndices[clippedIndexCount++] = static_cast<LegoU16>(firstClippedVertex + j + 1);
		}
	}

	if (directIndexCount != 0) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0x348,
			lastVertex + 1,
			directIndices,
			directIndexCount,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}

	if (clippedIndexCount != 0) {
		m_d3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			D3DFVF_TLVERTEX,
			m_unk0xc53a0,
			clippedVertexCount,
			clippedIndices,
			clippedIndexCount,
			D3DDP_DONOTLIGHT | D3DDP_DONOTUPDATEEXTENTS | D3DDP_DONOTCLIP
		);
	}
}

// FUNCTION: GOLDP 0x10010330
void GolD3DRenderDevice::FUN_10010330(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32)
{
	LegoU32 commandIndex = m_unk0xc86f4;
	if (commandIndex + p_triangleCount >= static_cast<LegoU32>(m_unk0xc86f8)) {
		return;
	}

	LegoU8* triangle = m_sourceIndices + (p_firstTriangle * 4);
	LegoU8* triangleEnd = m_sourceIndices + ((p_firstTriangle + p_triangleCount) * 4);
	p_triangleCount = 0;
	GolSoftwareRenderer::TriangleCommand* command = m_unk0xc86f0 + commandIndex;
	GolSoftwareRenderer::TriangleCommand* commandStart = command;
	LegoS32 maxRasterizerIndex = static_cast<LegoS32>(m_unk0xc83ac);
	LegoS32 rasterizerMaskBase = static_cast<LegoS32>(m_unk0xc83b0);

	while (triangle < triangleEnd) {
		command->m_vertexIndex0 = m_unk0xc3850[triangle[2]];
		command->m_vertexIndex1 = m_unk0xc3850[triangle[1]];
		command->m_vertexIndex2 = m_unk0xc3850[triangle[0]];

		D3DTLVERTEX* vertex0 = &m_unk0x348[command->m_vertexIndex0];
		D3DTLVERTEX* vertex1 = &m_unk0x348[command->m_vertexIndex1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[command->m_vertexIndex2];
		LegoFloat area = ((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) -
						 ((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx));

		if (area >= 0.0f) {
			triangle += 4;
			continue;
		}

		LegoS32 areaBucket = -static_cast<LegoS32>(area);
		LegoS32 rasterizerMask = rasterizerMaskBase;
		p_firstTriangle = 0;

		while (((areaBucket & rasterizerMask) == 0) & (static_cast<LegoS32>(p_firstTriangle) < maxRasterizerIndex)) {
			rasterizerMask >>= 2;
			p_firstTriangle++;
		}

		triangle += 4;
		p_triangleCount++;
		command->m_rasterizer = m_unk0xc83b4.m_unk0x00[p_firstTriangle];
		command++;
	}

	if (p_triangleCount == 0) {
		return;
	}

	if (m_flags & 0x20) {
		m_softwareRenderer.FUN_100417c0(commandStart, p_triangleCount);
	}
	else {
		m_softwareRenderer.FUN_100417a0(commandStart, p_triangleCount, m_flatDepth);
	}

	m_unk0xc86f4 += p_triangleCount;
}

// FUNCTION: GOLDP 0x10010500
void GolD3DRenderDevice::FUN_10010500(LegoU32 p_firstTriangle, LegoU32 p_triangleCount, LegoU32)
{
	LegoU32 commandIndex = m_unk0xc86f4;
	if (commandIndex + p_triangleCount >= static_cast<LegoU32>(m_unk0xc86f8)) {
		return;
	}

	LegoU8* triangle = m_sourceIndices + (p_firstTriangle * 4);
	LegoU8* triangleEnd = m_sourceIndices + ((p_firstTriangle + p_triangleCount) * 4);
	p_triangleCount = 0;
	GolSoftwareRenderer::TriangleCommand* command = m_unk0xc86f0 + commandIndex;
	GolSoftwareRenderer::TriangleCommand* commandStart = command;
	LegoS32 maxRasterizerIndex = static_cast<LegoS32>(m_unk0xc83ac);
	LegoS32 rasterizerMaskBase = static_cast<LegoS32>(m_unk0xc83b0);

	while (triangle < triangleEnd) {
		command->m_vertexIndex0 = m_unk0xc3850[triangle[0]];
		command->m_vertexIndex1 = m_unk0xc3850[triangle[1]];
		command->m_vertexIndex2 = m_unk0xc3850[triangle[2]];

		D3DTLVERTEX* vertex0 = &m_unk0x348[command->m_vertexIndex0];
		D3DTLVERTEX* vertex1 = &m_unk0x348[command->m_vertexIndex1];
		D3DTLVERTEX* vertex2 = &m_unk0x348[command->m_vertexIndex2];
		LegoFloat area = ((vertex2->sy - vertex1->sy) * (vertex0->sx - vertex1->sx)) -
						 ((vertex0->sy - vertex1->sy) * (vertex2->sx - vertex1->sx));

		if (area >= 0.0f) {
			triangle += 4;
			continue;
		}

		LegoS32 areaBucket = static_cast<LegoS32>(area);
		LegoS32 rasterizerMask = rasterizerMaskBase;
		p_firstTriangle = 0;

		while (((areaBucket & rasterizerMask) == 0) & (static_cast<LegoS32>(p_firstTriangle) < maxRasterizerIndex)) {
			rasterizerMask >>= 2;
			p_firstTriangle++;
		}

		triangle += 4;
		p_triangleCount++;
		command->m_rasterizer = m_unk0xc83b4.m_unk0x00[p_firstTriangle];
		command++;
	}

	if (p_triangleCount == 0) {
		return;
	}

	if (m_flags & 0x20) {
		m_softwareRenderer.FUN_100417c0(commandStart, p_triangleCount);
	}
	else {
		m_softwareRenderer.FUN_100417a0(commandStart, p_triangleCount, m_flatDepth);
	}

	m_unk0xc86f4 += p_triangleCount;
}

// STUB: GOLDP 0x100106d0
void GolD3DRenderDevice::FUN_100106d0(undefined4 p_firstTriangle, undefined4 p_triangleCount, undefined4)
{
	LegoU32 firstTriangle = p_firstTriangle;
	LegoU32 triangleCount = p_triangleCount;
	LegoU32 commandIndex = m_unk0xc86f4;
	LegoFloat nearClip = m_currentCamera->m_nearClip;
	LegoFloat farClip = m_currentCamera->m_farClip;
	LegoU8* triangle = m_sourceIndices + (firstTriangle * 4);
	LegoU8* triangleEnd = m_sourceIndices + ((firstTriangle + triangleCount) * 4);
	GolSoftwareRenderer::TriangleCommand* command = m_unk0xc86f0 + commandIndex;
	GolSoftwareRenderer::TriangleCommand* commandStart = command;
	LegoU32 emittedCount = 0;
	LegoS32 maxRasterizerIndex = static_cast<LegoS32>(m_unk0xc83ac);
	LegoS32 rasterizerMaskBase = static_cast<LegoS32>(m_unk0xc83b0);
	LegoBool32 flipped = ((m_activeMaterialFlags | m_forcedMaterialFlags) & GolMaterial::c_flagRotateVertices) != 0;
	static const LegoU32 g_clipPlanes[] = {0x10, 0x20, 0x01, 0x02, 0x04, 0x08};

	for (; triangle < triangleEnd; triangle += 4) {
		LegoU32 indicesA[16];
		LegoU32 indicesB[16];

		if (flipped) {
			indicesA[0] = triangle[2];
			indicesA[1] = triangle[1];
			indicesA[2] = triangle[0];
		}
		else {
			indicesA[0] = triangle[0];
			indicesA[1] = triangle[1];
			indicesA[2] = triangle[2];
		}

		if (m_unk0xc38ec[indicesA[0]].m_clipFlags & m_unk0xc38ec[indicesA[1]].m_clipFlags &
			m_unk0xc38ec[indicesA[2]].m_clipFlags) {
			continue;
		}

		LegoU32 unionFlags = m_unk0xc38ec[indicesA[0]].m_clipFlags | m_unk0xc38ec[indicesA[1]].m_clipFlags |
							 m_unk0xc38ec[indicesA[2]].m_clipFlags;

		if (unionFlags == 0) {
			const D3DTLVERTEX& vertex0 = m_unk0x348[m_unk0xc38ec[indicesA[0]].m_unk0x10];
			const D3DTLVERTEX& vertex1 = m_unk0x348[m_unk0xc38ec[indicesA[1]].m_unk0x10];
			const D3DTLVERTEX& vertex2 = m_unk0x348[m_unk0xc38ec[indicesA[2]].m_unk0x10];
			LegoFloat area = ComputeScreenArea(vertex0, vertex1, vertex2);

			if (area <= 0.0f) {
				continue;
			}

			command->m_vertexIndex0 = static_cast<LegoU16>(m_unk0xc38ec[indicesA[2]].m_unk0x10);
			command->m_vertexIndex1 = static_cast<LegoU16>(m_unk0xc38ec[indicesA[1]].m_unk0x10);
			command->m_vertexIndex2 = static_cast<LegoU16>(m_unk0xc38ec[indicesA[0]].m_unk0x10);

			LegoS32 areaBucket = static_cast<LegoS32>(area);
			LegoS32 rasterizerMask = rasterizerMaskBase;
			LegoU32 rasterizerIndex = 0;

			while (((areaBucket & rasterizerMask) == 0) &
				   (static_cast<LegoS32>(rasterizerIndex) < maxRasterizerIndex)) {
				rasterizerMask >>= 2;
				rasterizerIndex++;
			}

			emittedCount++;
			command->m_rasterizer = m_unk0xc83b4.m_unk0x00[rasterizerIndex];
			command++;
			continue;
		}

		LegoU32 vertexCount = 3;
		LegoU32 nextClipIndex = 0x40;
		LegoU32* inputIndices = indicesA;
		LegoU32* outputIndices = indicesB;

		for (LegoU32 planeIndex = 0; planeIndex < sizeOfArray(g_clipPlanes); planeIndex++) {
			LegoU32 plane = g_clipPlanes[planeIndex];
			if ((unionFlags & plane) == 0) {
				continue;
			}

			LegoU32 outputCount = 0;
			LegoU32 previousIndex = inputIndices[vertexCount - 1];
			LegoBool32 previousInside = (m_unk0xc38ec[previousIndex].m_clipFlags & plane) == 0;
			LegoFloat previousDistance = GetClipDistance(m_unk0xc38ec[previousIndex], plane, farClip);
			unionFlags = 0;

			for (LegoU32 i = 0; i < vertexCount; i++) {
				LegoU32 currentIndex = inputIndices[i];
				LegoBool32 currentInside = (m_unk0xc38ec[currentIndex].m_clipFlags & plane) == 0;
				LegoFloat currentDistance = GetClipDistance(m_unk0xc38ec[currentIndex], plane, farClip);

				if (previousInside != currentInside) {
					LegoFloat delta = previousDistance - currentDistance;
					LegoFloat amount = 0.0f;
					if (delta != 0.0f) {
						amount = previousDistance / delta;
					}

					if (outputCount >= sizeOfArray(indicesB)) {
						vertexCount = 0;
						break;
					}

					LegoU32 clipIndex = AddIndexedClipVertex(
						m_unk0xc38ec,
						m_unk0x348,
						m_viewportMetrics,
						previousIndex,
						currentIndex,
						amount,
						plane,
						nearClip,
						farClip,
						nextClipIndex,
						m_unk0xc3848
					);
					outputIndices[outputCount++] = clipIndex;
					unionFlags |= m_unk0xc38ec[clipIndex].m_clipFlags;
				}

				if (currentInside) {
					if (outputCount >= sizeOfArray(indicesB)) {
						vertexCount = 0;
						break;
					}

					outputIndices[outputCount++] = currentIndex;
					unionFlags |= m_unk0xc38ec[currentIndex].m_clipFlags;
				}

				previousIndex = currentIndex;
				previousInside = currentInside;
				previousDistance = currentDistance;
			}

			if (vertexCount == 0 || outputCount < 3) {
				vertexCount = 0;
				break;
			}

			vertexCount = outputCount;
			LegoU32* tempIndices = inputIndices;
			inputIndices = outputIndices;
			outputIndices = tempIndices;
		}

		if (vertexCount < 3) {
			continue;
		}

		const D3DTLVERTEX& vertex0 = m_unk0x348[m_unk0xc38ec[inputIndices[0]].m_unk0x10];
		const D3DTLVERTEX& vertex1 = m_unk0x348[m_unk0xc38ec[inputIndices[1]].m_unk0x10];
		const D3DTLVERTEX& vertex2 = m_unk0x348[m_unk0xc38ec[inputIndices[2]].m_unk0x10];

		if (ComputeScreenArea(vertex0, vertex1, vertex2) <= 0.0f) {
			continue;
		}

		for (LegoU32 i = 1; i + 1 < vertexCount; i++) {
			command->m_vertexIndex0 = static_cast<LegoU16>(m_unk0xc38ec[inputIndices[0]].m_unk0x10);
			command->m_vertexIndex1 = static_cast<LegoU16>(m_unk0xc38ec[inputIndices[i + 1]].m_unk0x10);
			command->m_vertexIndex2 = static_cast<LegoU16>(m_unk0xc38ec[inputIndices[i]].m_unk0x10);
			emittedCount++;
			command->m_rasterizer = m_unk0xc83b4.m_unk0x00[0];
			command++;
		}
	}

	if (emittedCount == 0) {
		return;
	}

	if (m_flags & 0x20) {
		m_softwareRenderer.FUN_100417c0(commandStart, emittedCount);
	}
	else {
		m_softwareRenderer.FUN_100417a0(commandStart, emittedCount, m_flatDepth);
	}

	m_unk0xc86f4 += emittedCount;
}

// FUNCTION: GOLDP 0x10011e60
void GolD3DRenderDevice::FUN_10011e60(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 color = m_unk0xc857c;
	LegoU32 red = m_unk0xc8570;
	color <<= 8;
	LegoU32 blue = m_unk0xc8578;
	LegoU32 firstVertex = p_firstVertex;
	color |= red;
	LegoU32 green = m_unk0xc8574;
	color <<= 8;
	color |= green;
	LegoU32 endIndex = firstVertex + vertexCount;
	color <<= 8;
	color |= blue;

	LegoU32* first = m_sourceColors + firstVertex;
	LegoU32* end = m_sourceColors + endIndex;
	for (; first < end; first++) {
		*first = color;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10011ed0
void GolD3DRenderDevice::FUN_10011ed0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		LegoS32 red = baseRed - static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		LegoS32 green = baseGreen - static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		LegoS32 blue = baseBlue - static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012030
void GolD3DRenderDevice::FUN_10012030(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100121e0
void GolD3DRenderDevice::FUN_100121e0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[2].m_z + normal->m_y * m_unk0xc8644[2].m_y + normal->m_x * m_unk0xc8644[2].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[2].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[2].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[2].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100123e0
void GolD3DRenderDevice::FUN_100123e0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[2].m_z + normal->m_y * m_unk0xc8644[2].m_y + normal->m_x * m_unk0xc8644[2].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[2].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[2].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[2].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[3].m_z + normal->m_y * m_unk0xc8644[3].m_y + normal->m_x * m_unk0xc8644[3].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[3].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[3].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[3].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012640
void GolD3DRenderDevice::FUN_10012640(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[2].m_z + normal->m_y * m_unk0xc8644[2].m_y + normal->m_x * m_unk0xc8644[2].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[2].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[2].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[2].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[3].m_z + normal->m_y * m_unk0xc8644[3].m_y + normal->m_x * m_unk0xc8644[3].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[3].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[3].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[3].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[4].m_z + normal->m_y * m_unk0xc8644[4].m_y + normal->m_x * m_unk0xc8644[4].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[4].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[4].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[4].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x100128f0
void GolD3DRenderDevice::FUN_100128f0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[2].m_z + normal->m_y * m_unk0xc8644[2].m_y + normal->m_x * m_unk0xc8644[2].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[2].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[2].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[2].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[3].m_z + normal->m_y * m_unk0xc8644[3].m_y + normal->m_x * m_unk0xc8644[3].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[3].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[3].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[3].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[4].m_z + normal->m_y * m_unk0xc8644[4].m_y + normal->m_x * m_unk0xc8644[4].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[4].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[4].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[4].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[5].m_z + normal->m_y * m_unk0xc8644[5].m_y + normal->m_x * m_unk0xc8644[5].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[5].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[5].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[5].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// STUB: GOLDP 0x10012bf0
void GolD3DRenderDevice::FUN_10012bf0(undefined4 p_outputFirst, undefined4 p_firstVertex, undefined4 p_vertexCount)
{
	LegoU32 firstVertex = p_firstVertex;
	LegoU32 vertexCount = p_vertexCount;
	LegoU32 endIndex = firstVertex + vertexCount;
	LegoU32* color = m_sourceColors + firstVertex;
	LegoU32* colorEnd = m_sourceColors + endIndex;
	const GolVec3* normal = m_sourceNormals + firstVertex;
	LegoS32 baseRed = static_cast<LegoS32>(m_unk0xc8570);
	LegoS32 baseGreen = static_cast<LegoS32>(m_unk0xc8574);
	LegoS32 baseBlue = static_cast<LegoS32>(m_unk0xc8578);
	LegoU32 alpha = m_unk0xc857c << 8;

	for (; color < colorEnd; color++, normal++) {
		LegoS32 red = baseRed;
		LegoS32 green = baseGreen;
		LegoS32 blue = baseBlue;

		LegoFloat intensity =
			normal->m_z * m_unk0xc8644[0].m_z + normal->m_y * m_unk0xc8644[0].m_y + normal->m_x * m_unk0xc8644[0].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[0].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[0].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[0].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[1].m_z + normal->m_y * m_unk0xc8644[1].m_y + normal->m_x * m_unk0xc8644[1].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[1].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[1].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[1].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[2].m_z + normal->m_y * m_unk0xc8644[2].m_y + normal->m_x * m_unk0xc8644[2].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[2].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[2].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[2].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[3].m_z + normal->m_y * m_unk0xc8644[3].m_y + normal->m_x * m_unk0xc8644[3].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[3].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[3].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[3].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[4].m_z + normal->m_y * m_unk0xc8644[4].m_y + normal->m_x * m_unk0xc8644[4].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[4].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[4].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[4].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[5].m_z + normal->m_y * m_unk0xc8644[5].m_y + normal->m_x * m_unk0xc8644[5].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[5].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[5].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[5].m_blu * intensity);

		intensity =
			normal->m_z * m_unk0xc8644[6].m_z + normal->m_y * m_unk0xc8644[6].m_y + normal->m_x * m_unk0xc8644[6].m_x;
		red -= static_cast<LegoS32>(m_unk0xc859c[6].m_red * intensity);
		green -= static_cast<LegoS32>(m_unk0xc859c[6].m_grn * intensity);
		blue -= static_cast<LegoS32>(m_unk0xc859c[6].m_blu * intensity);

		red = ClampModelColorChannel(red, baseRed);
		green = ClampModelColorChannel(green, baseGreen);
		blue = ClampModelColorChannel(blue, baseBlue);
		LegoU32 finalColor = alpha | red;
		finalColor <<= 8;
		finalColor |= green;
		finalColor <<= 8;
		finalColor |= blue;
		*color = finalColor;
	}

	(this->*m_drawTriangleFn0)(p_outputFirst, firstVertex, vertexCount);
}

// FUNCTION: GOLDP 0x10012f50
void GolD3DRenderDevice::FUN_10012f50()
{
	if (m_renderState) {
		if (m_stateBeginPending) {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000eb90;
			if (m_unk0xc8568) {
				m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d210;
				return;
			}
			if (m_unk0xc83ec) {
				m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d5d0;
				return;
			}

			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d440;
			return;
		}

		if (m_unk0xc83c4) {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_100106d0;
		}
		else {
			m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;
		}

		if (m_unk0xc83ec) {
			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000dbb0;
		}
		else {
			m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_1000d760;
		}
	}
	else {
		LegoU32 index = m_unk0xc83f8;
		index <<= 3;
		index |= m_unk0xc83e8;
		index <<= 1;
		index |= m_uvOffsetEnabled;
		index <<= 1;
		index |= (m_flags >> 9) & 0x10;
		index |= m_unk0xc83ec;

		if (m_unk0xc83e4) {
			if (m_unk0xc83c4) {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_100106d0;
				if (!m_unk0xc83e8 && m_paletteMode == 0) {
					m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_100132f0;
					return;
				}
			}
			else {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000edf0;
			}

			index |= 8;
		}
		else {
			LegoU32 flags = m_activeMaterialFlags | m_forcedMaterialFlags;
			if (flags & GolMaterial::c_flagRotateVertices) {
				if (m_unk0xc83c4) {
					m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_10010500;
				}
				else {
					m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000ece0;
				}
			}
			else if (m_unk0xc83c4) {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_10010330;
				if (!m_unk0xc83e8 && m_paletteMode == 0) {
					m_drawTriangleFn1 = &GolD3DRenderDevice::FUN_10013110;
					return;
				}
			}
			else {
				m_drawTriangleFn2 = &GolD3DRenderDevice::FUN_1000ebd0;
			}
		}

		if (m_unk0xc8568) {
			m_drawTriangleFn1 = g_drawTriangleLitTable[m_lightCount];
			m_drawTriangleFn0 = g_drawTriangleTable[index];
		}
		else {
			m_drawTriangleFn1 = g_drawTriangleTable[index];
		}
	}
}

// STUB: GOLDP 0x10013110
void GolD3DRenderDevice::FUN_10013110(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* source = m_sourcePositions + p_firstVertex;
	const GolVec3* sourceEnd = source + p_vertexCount;
	LegoU16* vertexMap = m_unk0xc3850 + p_outputFirst;
	D3DTLVERTEX* vertex = m_unk0x348 + ((m_unk0xc3848 & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c));
	LegoU16 savedMapEntry = vertexMap[p_vertexCount];
	vertexMap[0] = static_cast<LegoU16>(m_unk0xc3848);
	m_unk0xc3848 += p_vertexCount;

	for (; source < sourceEnd;) {
		vertex->sx = m_currentMatrix->m_m[0][0] * source->m_x;
		vertex->sy = m_currentMatrix->m_m[0][1] * source->m_x;
		vertex->sz = m_currentMatrix->m_m[0][2] * source->m_x;
		vertex->rhw = m_currentMatrix->m_m[0][3] * source->m_x;

		vertex->sx += m_currentMatrix->m_m[1][0] * source->m_y;
		vertex->sy += m_currentMatrix->m_m[1][1] * source->m_y;
		vertex->sz += m_currentMatrix->m_m[1][2] * source->m_y;
		vertex->rhw += m_currentMatrix->m_m[1][3] * source->m_y;

		vertex->sx += m_currentMatrix->m_m[2][0] * source->m_z;
		vertex->sy += m_currentMatrix->m_m[2][1] * source->m_z;
		vertex->sz += m_currentMatrix->m_m[2][2] * source->m_z;
		vertex->rhw += m_currentMatrix->m_m[2][3] * source->m_z;

		vertex->sx += m_currentMatrix->m_m[3][0];
		vertex->sy += m_currentMatrix->m_m[3][1];
		vertex->sz += m_currentMatrix->m_m[3][2];
		vertex->rhw = 1.0f / (m_currentMatrix->m_m[3][3] + vertex->rhw);
		vertexMap[1] = vertexMap[0] + 1;
		vertex->color = 0;
		vertex->sx *= vertex->rhw;
		vertex->sy *= vertex->rhw;
		source++;
		vertex++;
		vertexMap++;
		vertex[-1].sz = vertex[-1].rhw * vertex[-1].sz;
	}

	vertexMap[p_vertexCount] = savedMapEntry;
}

// FUNCTION: GOLDP 0x100132f0
void GolD3DRenderDevice::FUN_100132f0(LegoU32 p_outputFirst, LegoU32 p_firstVertex, LegoU32 p_vertexCount)
{
	const GolVec3* source = m_sourcePositions + p_firstVertex;
	const GolVec3* sourceEnd = source + p_vertexCount;
	LegoU32 cacheIndex = m_unk0xc3848;
	VertexCacheEntry* cache = m_unk0xc38ec + p_outputFirst;
	D3DTLVERTEX* vertex = m_unk0x348 + ((cacheIndex & m_unk0xc384c) + (p_outputFirst & ~m_unk0xc384c));
	m_unk0xc3848 = cacheIndex + p_vertexCount;

	for (; source < sourceEnd; source++, cache++, vertex++, cacheIndex++) {
		cache->m_x = m_currentMatrix->m_m[0][0] * source->m_x;
		cache->m_y = m_currentMatrix->m_m[0][1] * source->m_x;
		cache->m_z = m_currentMatrix->m_m[0][2] * source->m_x;
		cache->m_w = m_currentMatrix->m_m[0][3] * source->m_x;

		cache->m_x += m_currentMatrix->m_m[1][0] * source->m_y;
		cache->m_y += m_currentMatrix->m_m[1][1] * source->m_y;
		cache->m_z += m_currentMatrix->m_m[1][2] * source->m_y;
		cache->m_w += m_currentMatrix->m_m[1][3] * source->m_y;

		cache->m_x += m_currentMatrix->m_m[2][0] * source->m_z;
		cache->m_y += m_currentMatrix->m_m[2][1] * source->m_z;
		cache->m_z += m_currentMatrix->m_m[2][2] * source->m_z;
		cache->m_w += m_currentMatrix->m_m[2][3] * source->m_z;

		source++;
		cache->m_x += m_currentMatrix->m_m[3][0];
		cache->m_y += m_currentMatrix->m_m[3][1];
		cache->m_z += m_currentMatrix->m_m[3][2];
		cache->m_w += m_currentMatrix->m_m[3][3];
		vertex->rhw = 1.0f / cache->m_w;
		cache->m_clipFlags = BuildModelClipFlags(*cache);
		cache->m_unk0x10 = cacheIndex;

		vertex->color = 0;
		vertex->sx = cache->m_x * vertex->rhw * m_viewportMetrics[0] + m_viewportMetrics[2];
		vertex->sy = cache->m_y * vertex->rhw * m_viewportMetrics[1] + m_viewportMetrics[3];
		vertex->sz = cache->m_z * vertex->rhw;
	}
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0x38()
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0xd0()
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolD3DRenderDevice::SetViewportRect(LegoS32, const LegoFloat*)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolD3DRenderDevice::SelectViewport(undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolD3DRenderDevice::VTable0xf4()
{
	// empty
}
