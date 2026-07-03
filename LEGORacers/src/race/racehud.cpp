#include "race/racehud.h"

#include "decomp.h"
#include "golfontbase.h"
#include "golmath.h"
#include "golnametable.h"
#include "image/golimage.h"
#include "material/golimagedefinitionlist.h"
#include "race/racecameracontroller.h"
#include "race/racer/racersoundsource.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(RaceHud, 0x140)
DECOMP_SIZE_ASSERT(RaceHud::TimeText, 0x09)

// GLOBAL: LEGORACERS 0x004c4814
undefined2 g_textConversionBuffer[42];

// GLOBAL: LEGORACERS 0x004afde0
extern const LegoFloat g_unk0x004afde0 = 10.0f;

extern const LegoFloat g_ghostAnimationRateScale;
extern const LegoFloat g_ghostSpeedScale;
extern const LegoFloat g_homingProjectileCollisionStartOffset;

// GLOBAL: LEGORACERS 0x004b02a0
extern const LegoFloat g_hudArrowBaseLength = 6.5f;

// GLOBAL: LEGORACERS 0x004b02a4
extern const LegoFloat g_hudArrowHalfWidth = 5.5f;

// GLOBAL: LEGORACERS 0x004b02a8
extern const LegoFloat g_hudArrowTipLength = 9.5f;

// GLOBAL: LEGORACERS 0x004b02ac
extern const LegoFloat g_hudMapSize = 128.0f;

// GLOBAL: LEGORACERS 0x004b02b0
extern const LegoFloat g_hudMapInsetScale = 0.03125f;

// GLOBAL: LEGORACERS 0x004b02b4
extern const LegoFloat g_hudMarkerSize = 16.0f;

// GLOBAL: LEGORACERS 0x004b02d4
extern const LegoFloat g_hudTopTextOffset = -7.0f;

// GLOBAL: LEGORACERS 0x004b02d8
extern const LegoFloat g_hudBaseScale = 0.0020833334f;

extern const LegoFloat g_unk0x004b02e0;

// GLOBAL: LEGORACERS 0x004be8a8
const LegoChar* g_hudFontName = "font_ths";

// GLOBAL: LEGORACERS 0x004be8ac
const LegoChar* g_hudNumberFontName = "ignum";

static const LegoChar* g_positionDigits[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
static const LegoS16 g_positionStringIds[8] = {0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20};

// FUNCTION: LEGORACERS 0x00423fc0
void RaceHud::ClipTriangleTop(
	const GolRenderDevice::TexturedVertex* p_v0,
	const GolRenderDevice::TexturedVertex* p_v1,
	const GolRenderDevice::TexturedVertex* p_v2
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_v1->m_y < m_clipTop) {
		if (p_v0->m_y < m_clipTop) {
			if (p_v2->m_y < m_clipTop) {
				return;
			}
		}
		else {
			temporaryVertex = p_v0;
			p_v0 = p_v1;
			p_v1 = p_v2;
			p_v2 = temporaryVertex;
		}
	}
	else if (p_v2->m_y < m_clipTop) {
		temporaryVertex = p_v2;
		p_v2 = p_v1;
		p_v1 = p_v0;
		p_v0 = temporaryVertex;
	}

	if (p_v0->m_y < m_clipTop) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_y = m_clipTop;
		intersection1.m_y = m_clipTop;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_v0->m_color;
		intersection1.m_color = p_v0->m_color;

		LegoFloat amount = (p_v2->m_y - m_clipTop) / (p_v2->m_y - p_v0->m_y);
		intersection0.m_x = (p_v0->m_x - p_v2->m_x) * amount + p_v2->m_x;
		intersection0.m_u = (p_v0->m_u - p_v2->m_u) * amount + p_v2->m_u;
		intersection0.m_v = (p_v0->m_v - p_v2->m_v) * amount + p_v2->m_v;

		if (p_v1->m_y < m_clipTop) {
			amount = (p_v2->m_y - m_clipTop) / (p_v2->m_y - p_v1->m_y);
			intersection1.m_x = (p_v1->m_x - p_v2->m_x) * amount + p_v2->m_x;
			intersection1.m_u = (p_v1->m_u - p_v2->m_u) * amount + p_v2->m_u;
			intersection1.m_v = (p_v1->m_v - p_v2->m_v) * amount + p_v2->m_v;

			ClipTriangleLeft(&intersection0, &intersection1, p_v2);
		}
		else {
			amount = (p_v1->m_y - m_clipTop) / (p_v1->m_y - p_v0->m_y);
			intersection1.m_x = (p_v0->m_x - p_v1->m_x) * amount + p_v1->m_x;
			intersection1.m_u = (p_v0->m_u - p_v1->m_u) * amount + p_v1->m_u;
			intersection1.m_v = (p_v0->m_v - p_v1->m_v) * amount + p_v1->m_v;

			ClipTriangleLeft(p_v2, &intersection1, p_v1);
			ClipTriangleLeft(&intersection0, &intersection1, p_v2);
		}

		return;
	}

	ClipTriangleLeft(p_v0, p_v1, p_v2);
}

// FUNCTION: LEGORACERS 0x00424190
void RaceHud::ClipTriangleLeft(
	const GolRenderDevice::TexturedVertex* p_v0,
	const GolRenderDevice::TexturedVertex* p_v1,
	const GolRenderDevice::TexturedVertex* p_v2
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_v1->m_x < m_clipLeft) {
		if (p_v0->m_x < m_clipLeft) {
			if (p_v2->m_x < m_clipLeft) {
				return;
			}
		}
		else {
			temporaryVertex = p_v0;
			p_v0 = p_v1;
			p_v1 = p_v2;
			p_v2 = temporaryVertex;
		}
	}
	else if (p_v2->m_x < m_clipLeft) {
		temporaryVertex = p_v2;
		p_v2 = p_v1;
		p_v1 = p_v0;
		p_v0 = temporaryVertex;
	}

	if (p_v0->m_x < m_clipLeft) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_x = m_clipLeft;
		intersection1.m_x = m_clipLeft;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_v0->m_color;
		intersection1.m_color = p_v0->m_color;

		LegoFloat amount = (p_v2->m_x - m_clipLeft) / (p_v2->m_x - p_v0->m_x);
		intersection0.m_y = (p_v0->m_y - p_v2->m_y) * amount + p_v2->m_y;
		intersection0.m_u = (p_v0->m_u - p_v2->m_u) * amount + p_v2->m_u;
		intersection0.m_v = (p_v0->m_v - p_v2->m_v) * amount + p_v2->m_v;

		if (p_v1->m_x < m_clipLeft) {
			amount = (p_v2->m_x - m_clipLeft) / (p_v2->m_x - p_v1->m_x);
			intersection1.m_y = (p_v1->m_y - p_v2->m_y) * amount + p_v2->m_y;
			intersection1.m_u = (p_v1->m_u - p_v2->m_u) * amount + p_v2->m_u;
			intersection1.m_v = (p_v1->m_v - p_v2->m_v) * amount + p_v2->m_v;

			ClipTriangleRight(&intersection0, &intersection1, p_v2);
		}
		else {
			amount = (p_v1->m_x - m_clipLeft) / (p_v1->m_x - p_v0->m_x);
			intersection1.m_y = (p_v0->m_y - p_v1->m_y) * amount + p_v1->m_y;
			intersection1.m_u = (p_v0->m_u - p_v1->m_u) * amount + p_v1->m_u;
			intersection1.m_v = (p_v0->m_v - p_v1->m_v) * amount + p_v1->m_v;

			ClipTriangleRight(p_v2, &intersection1, p_v1);
			ClipTriangleRight(&intersection0, &intersection1, p_v2);
		}

		return;
	}

	ClipTriangleRight(p_v0, p_v1, p_v2);
}

// FUNCTION: LEGORACERS 0x00424340
void RaceHud::ClipTriangleRight(
	const GolRenderDevice::TexturedVertex* p_v0,
	const GolRenderDevice::TexturedVertex* p_v1,
	const GolRenderDevice::TexturedVertex* p_v2
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_v1->m_x > m_clipRight) {
		if (p_v0->m_x > m_clipRight) {
			if (p_v2->m_x > m_clipRight) {
				return;
			}
		}
		else {
			temporaryVertex = p_v0;
			p_v0 = p_v1;
			p_v1 = p_v2;
			p_v2 = temporaryVertex;
		}
	}
	else if (p_v2->m_x > m_clipRight) {
		temporaryVertex = p_v2;
		p_v2 = p_v1;
		p_v1 = p_v0;
		p_v0 = temporaryVertex;
	}

	if (p_v0->m_x > m_clipRight) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_x = m_clipRight;
		intersection1.m_x = m_clipRight;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_v0->m_color;
		intersection1.m_color = p_v0->m_color;

		LegoFloat amount = (p_v2->m_x - m_clipRight) / (p_v2->m_x - p_v0->m_x);
		intersection0.m_y = (p_v0->m_y - p_v2->m_y) * amount + p_v2->m_y;
		intersection0.m_u = (p_v0->m_u - p_v2->m_u) * amount + p_v2->m_u;
		intersection0.m_v = (p_v0->m_v - p_v2->m_v) * amount + p_v2->m_v;

		if (p_v1->m_x > m_clipRight) {
			amount = (p_v2->m_x - m_clipRight) / (p_v2->m_x - p_v1->m_x);
			intersection1.m_y = (p_v1->m_y - p_v2->m_y) * amount + p_v2->m_y;
			intersection1.m_u = (p_v1->m_u - p_v2->m_u) * amount + p_v2->m_u;
			intersection1.m_v = (p_v1->m_v - p_v2->m_v) * amount + p_v2->m_v;

			ClipTriangleBottom(&intersection0, &intersection1, p_v2);
		}
		else {
			amount = (p_v1->m_x - m_clipRight) / (p_v1->m_x - p_v0->m_x);
			intersection1.m_y = (p_v0->m_y - p_v1->m_y) * amount + p_v1->m_y;
			intersection1.m_u = (p_v0->m_u - p_v1->m_u) * amount + p_v1->m_u;
			intersection1.m_v = (p_v0->m_v - p_v1->m_v) * amount + p_v1->m_v;

			ClipTriangleBottom(p_v2, &intersection1, p_v1);
			ClipTriangleBottom(&intersection0, &intersection1, p_v2);
		}

		return;
	}

	ClipTriangleBottom(p_v0, p_v1, p_v2);
}

// FUNCTION: LEGORACERS 0x004244f0
void RaceHud::ClipTriangleBottom(
	const GolRenderDevice::TexturedVertex* p_v0,
	const GolRenderDevice::TexturedVertex* p_v1,
	const GolRenderDevice::TexturedVertex* p_v2
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_v1->m_y > m_clipBottom) {
		if (p_v0->m_y > m_clipBottom) {
			if (p_v2->m_y > m_clipBottom) {
				return;
			}
		}
		else {
			temporaryVertex = p_v0;
			p_v0 = p_v1;
			p_v1 = p_v2;
			p_v2 = temporaryVertex;
		}
	}
	else if (p_v2->m_y > m_clipBottom) {
		temporaryVertex = p_v2;
		p_v2 = p_v1;
		p_v1 = p_v0;
		p_v0 = temporaryVertex;
	}

	if (p_v0->m_y > m_clipBottom) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection1.m_y = intersection0.m_y = m_clipBottom;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_v0->m_color;
		intersection1.m_color = p_v0->m_color;

		LegoFloat amount = (p_v2->m_y - m_clipBottom) / (p_v2->m_y - p_v0->m_y);
		intersection0.m_x = (p_v0->m_x - p_v2->m_x) * amount + p_v2->m_x;
		intersection0.m_u = (p_v0->m_u - p_v2->m_u) * amount + p_v2->m_u;
		intersection0.m_v = (p_v0->m_v - p_v2->m_v) * amount + p_v2->m_v;

		if (p_v1->m_y > m_clipBottom) {
			amount = (p_v2->m_y - m_clipBottom) / (p_v2->m_y - p_v1->m_y);
			intersection1.m_x = (p_v1->m_x - p_v2->m_x) * amount + p_v2->m_x;
			intersection1.m_u = (p_v1->m_u - p_v2->m_u) * amount + p_v2->m_u;
			intersection1.m_v = (p_v1->m_v - p_v2->m_v) * amount + p_v2->m_v;
		}
		else {
			amount = (p_v1->m_y - m_clipBottom) / (p_v1->m_y - p_v0->m_y);
			intersection1.m_x = (p_v0->m_x - p_v1->m_x) * amount + p_v1->m_x;
			intersection1.m_u = (p_v0->m_u - p_v1->m_u) * amount + p_v1->m_u;
			intersection1.m_v = (p_v0->m_v - p_v1->m_v) * amount + p_v1->m_v;

			m_renderer->DrawTriangle(p_v2, &intersection1, p_v1, m_mapMaterial, 0);
		}

		m_renderer->DrawTriangle(&intersection0, &intersection1, p_v2, m_mapMaterial, 0);
		return;
	}

	m_renderer->DrawTriangle(p_v0, p_v1, p_v2, m_mapMaterial, 0);
}

// FUNCTION: LEGORACERS 0x004246d0 FOLDED
LegoU32 RaceHud::FormatTime(LegoChar* p_buffer, LegoU32 p_time)
{
	LegoU32 millisecondsPerHour = 3600000;
	LegoS32 divisor = 10;
	LegoU32 time = p_time % millisecondsPerHour;
	LegoS32 digitOffset;

	p_buffer[8] = '\0';
	if (time >= 600000) {
		digitOffset = 7;
		p_buffer[5] = ':';
		p_buffer[2] = ':';
	}
	else {
		digitOffset = 6;
		p_buffer[4] = ':';
		p_buffer[1] = ':';
		p_buffer[7] = '\0';
	}

	LegoU32 centiseconds = time / 10;
	p_buffer[digitOffset] = static_cast<LegoChar>(centiseconds % 10 + '0');
	centiseconds /= 10;
	p_buffer[digitOffset - 1] = static_cast<LegoChar>(centiseconds % 10 + '0');

	LegoU32 seconds = centiseconds / divisor;
	LegoS32 secondsWithinMinute = static_cast<LegoS32>(seconds % 60);
	LegoU32 minutes = seconds / 60;
	p_buffer[digitOffset - 3] = static_cast<LegoChar>(secondsWithinMinute % divisor + '0');
	p_buffer[digitOffset - 4] = static_cast<LegoChar>((secondsWithinMinute / divisor) % divisor + '0');

	p_buffer[digitOffset - 6] = static_cast<LegoChar>(minutes % divisor + '0');
	LegoU32 extraMinutes = minutes / divisor;
	if (extraMinutes) {
		p_buffer[digitOffset - 7] = static_cast<LegoChar>(extraMinutes % divisor + '0');
		extraMinutes /= divisor;
	}

	return extraMinutes;
}

// FUNCTION: LEGORACERS 0x004247d0
void RaceHud::DrawMapArrow(LegoS32 p_x, LegoS32 p_y, LegoFloat p_directionX, LegoFloat p_directionY)
{
	const LegoFloat tailEndLength = 8.0f;

	LegoU8 colorAlpha = 0xff;
	GolRenderDevice::TexturedVertex vertices[6];

	LegoFloat tipX = p_directionX;
	tipX *= g_hudArrowTipLength;
	vertices[0].m_x = tipX;
	LegoFloat tipY = p_directionY;
	tipY *= g_hudArrowTipLength;
	vertices[0].m_y = tipY;

	LegoFloat baseSide = p_directionY;
	baseSide *= g_hudArrowHalfWidth;
	LegoFloat baseForward = p_directionX;
	baseForward *= g_hudArrowBaseLength;
	vertices[1].m_x = baseSide - baseForward;

	LegoFloat baseForwardY = p_directionY;
	baseForwardY *= g_hudArrowBaseLength;
	LegoFloat baseSideX = p_directionX;
	baseSideX *= g_hudArrowHalfWidth;
	vertices[1].m_y = -baseForwardY - baseSideX;
	vertices[2].m_x = -baseForward - baseSide;
	vertices[2].m_y = baseSideX - baseForwardY;

	vertices[3].m_x = p_directionX * tailEndLength;
	vertices[3].m_y = p_directionY * tailEndLength;
	LegoFloat tailSide = p_directionY;
	tailSide *= g_ghostSpeedScale;
	LegoFloat tailForward = p_directionX;
	tailForward *= g_homingProjectileCollisionStartOffset;
	vertices[4].m_x = tailSide - tailForward;

	LegoFloat tailForwardY = p_directionY;
	tailForwardY *= g_homingProjectileCollisionStartOffset;
	LegoFloat tailSideX = p_directionX;
	tailSideX *= g_ghostSpeedScale;
	vertices[4].m_y = -tailForwardY - tailSideX;
	vertices[5].m_x = -tailForward - tailSide;
	vertices[5].m_y = tailSideX - tailForwardY;

	LegoFloat originX = static_cast<LegoFloat>(p_x);
	LegoFloat originY = static_cast<LegoFloat>(p_y);
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0;
		vertices[i].m_color.m_grn = 0;
		vertices[i].m_color.m_blu = 0;
		vertices[i].m_color.m_alp = colorAlpha;
		vertices[i].m_z = 0.0f;
		LegoFloat scaledX = vertices[i].m_x;
		scaledX *= m_scaleX;
		vertices[i].m_x = scaledX + originX;
		vertices[i].m_y = m_scaleY * vertices[i].m_y + originY;
	}

	GolMaterial* material = m_mapMaterial;
	m_mapMaterial = NULL;
	vertices[3].m_color.m_grn = colorAlpha;
	vertices[4].m_color.m_grn = colorAlpha;
	vertices[5].m_color.m_grn = colorAlpha;
	ClipTriangleTop(&vertices[1], &vertices[0], &vertices[2]);
	ClipTriangleTop(&vertices[4], &vertices[3], &vertices[5]);
	m_mapMaterial = material;
}

// STUB: LEGORACERS 0x004249b0
void RaceHud::DrawFixedMap()
{
	const LegoFloat maxTextureCoordinate = 0.9990000129f;

	LegoFloat markerWidthScale = m_scaleX;
	markerWidthScale *= g_hudMarkerSize;
	LegoS32 markerWidth = static_cast<LegoS32>(markerWidthScale);

	LegoFloat markerHeightScale = m_scaleY;
	markerHeightScale *= g_hudMarkerSize;
	LegoS32 markerHeight = static_cast<LegoS32>(markerHeightScale);

	m_clipTop = static_cast<LegoFloat>(m_viewport.m_top);
	m_clipLeft = static_cast<LegoFloat>(m_viewport.m_left);
	m_clipBottom = static_cast<LegoFloat>(m_viewport.m_bottom);
	m_clipRight = static_cast<LegoFloat>(m_viewport.m_right);

	GolRenderDevice::TexturedVertex vertices[4];
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0xff;
		vertices[i].m_color.m_grn = 0xff;
		vertices[i].m_color.m_blu = 0xff;
		vertices[i].m_color.m_alp = 0xc8;
		vertices[i].m_z = 0.0f;
	}

	LegoS32 verticalOffset =
		static_cast<LegoS32>(static_cast<LegoFloat>(m_screenHeight) * g_hudMapInsetScale * m_scaleY);
	LegoS32 horizontalOffset =
		static_cast<LegoS32>(static_cast<LegoFloat>(m_screenHeight) * g_hudMapInsetScale * m_scaleX);
	LegoS32 mapOriginY = m_viewport.m_bottom - verticalOffset;
	LegoS32 mapOriginX = m_viewport.m_right - horizontalOffset;

	LegoFloat referenceY;
	if (m_mirror) {
		referenceY = -m_mapMaxY;
	}
	else {
		referenceY = m_mapMinY;
	}

	LegoFloat rangeX = m_mapMaxX - m_mapMinX;
	LegoFloat rangeY = m_mapMaxY - m_mapMinY;
	LegoFloat scale = rangeX > rangeY ? g_hudMapSize / rangeX : g_hudMapSize / rangeY;
	scale *= m_mapScale;
	LegoFloat scaleX = m_scaleX * scale;
	LegoFloat scaleY = m_scaleY * scale;

	if (m_mapMaterial) {
		if (m_mirror) {
			vertices[0].m_v = 0.0f;
			vertices[1].m_v = 0.0f;
			vertices[2].m_v = maxTextureCoordinate;
			vertices[3].m_v = maxTextureCoordinate;
		}
		else {
			vertices[0].m_v = maxTextureCoordinate;
			vertices[1].m_v = maxTextureCoordinate;
			vertices[2].m_v = 0.0f;
			vertices[3].m_v = 0.0f;
		}

		vertices[0].m_x = static_cast<LegoFloat>(mapOriginX) + (m_mapMinX - m_mapMaxX) * scaleX;
		vertices[0].m_y = static_cast<LegoFloat>(mapOriginY) + (m_mapMinY - m_mapMaxY) * scaleY;
		vertices[0].m_u = 0.0f;

		vertices[1].m_x = static_cast<LegoFloat>(mapOriginX);
		vertices[1].m_y = vertices[0].m_y;
		vertices[1].m_u = maxTextureCoordinate;

		vertices[2].m_x = static_cast<LegoFloat>(mapOriginX);
		vertices[2].m_y = static_cast<LegoFloat>(mapOriginY);
		vertices[2].m_u = maxTextureCoordinate;

		vertices[3].m_x = vertices[0].m_x;
		vertices[3].m_y = static_cast<LegoFloat>(mapOriginY);
		vertices[3].m_u = 0.0f;

		ClipTriangleTop(&vertices[0], &vertices[1], &vertices[2]);
		ClipTriangleTop(&vertices[3], &vertices[0], &vertices[2]);
	}

	GolImage* markerResource = m_images->GetItem(10);
	LegoS32 halfMarkerWidth = markerWidth >> 1;
	LegoS32 halfMarkerHeight = markerHeight >> 1;
	LegoS32 markerOriginX = mapOriginX - halfMarkerWidth;
	LegoS32 markerOriginY = mapOriginY - halfMarkerHeight;

	for (LegoS32 racerIndex = static_cast<LegoS32>(m_raceState->GetRacerCount()) - 1; racerIndex >= 0; racerIndex--) {
		Racer* racer = &m_raceState->GetRacers()[racerIndex];
		if (racer != m_racer) {
			GolVec3 position;
			racer->m_visuals.m_carEntity->GetPosition(&position);

			Rect destRect;
			destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
			destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_mapMaxX) * scaleX);
			destRect.m_bottom = destRect.m_top + markerHeight;
			destRect.m_right = destRect.m_left + markerWidth;

			Rect sourceRect;
			if (racer->m_controlMode == Racer::c_controlAi && racerIndex == 1) {
				sourceRect.m_left = 0x10;
			}
			else {
				sourceRect.m_left = 0;
			}
			if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
				sourceRect.m_top = 0x10;
			}
			else {
				sourceRect.m_top = 0;
			}
			sourceRect.m_right = sourceRect.m_left + 0x10;
			sourceRect.m_bottom = sourceRect.m_top + 0x10;

			m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
		}
	}

	if (m_timeRaceManager && m_timeRaceManager->HasRecordGhostMarker()) {
		GolVec3 position;
		m_timeRaceManager->GetRecordGhostMarkerEntity()->GetPosition(&position);

		Rect destRect;
		destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
		destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_mapMaxX) * scaleX);
		destRect.m_bottom = destRect.m_top + markerHeight;
		destRect.m_right = destRect.m_left + markerWidth;

		Rect sourceRect;
		sourceRect.m_left = 0x10;
		if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
	}

	if (m_timeRaceManager && m_timeRaceManager->HasBestGhostMarker()) {
		GolVec3 position;
		m_timeRaceManager->GetBestGhostMarkerEntity()->GetPosition(&position);

		Rect destRect;
		destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
		destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_mapMaxX) * scaleX);
		destRect.m_bottom = destRect.m_top + markerHeight;
		destRect.m_right = destRect.m_left + markerWidth;

		Rect sourceRect;
		sourceRect.m_left = 0;
		if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
	}

	GolVec3 currentPosition;
	m_racer->m_visuals.m_carEntity->GetPosition(&currentPosition);

	GolVec3 direction;
	m_racer->m_visuals.m_carEntity->GetOrientationRow0(&direction);
	LegoFloat directionScale =
		1.0f / static_cast<LegoFloat>(sqrt(direction.m_y * direction.m_y + direction.m_x * direction.m_x));
	LegoFloat directionX = direction.m_x * directionScale;
	LegoFloat directionY = -(direction.m_y * directionScale);

	LegoS32 currentX = mapOriginX + static_cast<LegoS32>((currentPosition.m_x - m_mapMaxX) * scaleX);
	LegoS32 currentY = mapOriginY + static_cast<LegoS32>((referenceY - currentPosition.m_y) * scaleY);
	DrawMapArrow(currentX, currentY, directionX, directionY);
}

// STUB: LEGORACERS 0x00424fb0
void RaceHud::DrawRotatingMap()
{
	const LegoFloat maxTextureCoordinate = 0.9990000129f;

	LegoFloat markerWidthScale = m_scaleX;
	markerWidthScale *= g_hudMarkerSize;
	LegoS32 markerWidth = static_cast<LegoS32>(markerWidthScale);

	LegoFloat markerHeightScale = m_scaleY;
	markerHeightScale *= g_hudMarkerSize;
	LegoS32 markerHeight = static_cast<LegoS32>(markerHeightScale);

	GolRenderDevice::TexturedVertex vertices[8];
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0xff;
		vertices[i].m_color.m_grn = 0xff;
		vertices[i].m_color.m_blu = 0xff;
		vertices[i].m_color.m_alp = 0xc8;
		vertices[i].m_z = 0.0f;
	}

	LegoFloat directionLengthScale = m_mapScale * 0.12f * m_scaleY;
	LegoS32 verticalInset =
		static_cast<LegoS32>(static_cast<LegoFloat>(m_screenHeight) * g_hudMapInsetScale * m_scaleY);
	LegoS32 horizontalInset =
		static_cast<LegoS32>(static_cast<LegoFloat>(m_screenHeight) * g_hudMapInsetScale * m_scaleX);
	LegoS32 mapBottom = m_viewport.m_bottom - verticalInset;
	LegoS32 mapRight = m_viewport.m_right - horizontalInset;

	LegoFloat mapSize = m_mapScale * g_hudMapSize;
	LegoS32 mapHeight = static_cast<LegoS32>(m_scaleY * mapSize);
	LegoS32 mapWidth = static_cast<LegoS32>(m_scaleX * mapSize);
	LegoS32 mapTop = mapBottom - mapHeight;
	LegoS32 mapLeft = mapRight - mapWidth;
	LegoS32 mapCenterX = (mapLeft + mapRight) >> 1;
	LegoS32 mapCenterY = (mapTop + mapBottom) >> 1;

	m_clipTop = static_cast<LegoFloat>(mapTop);
	m_clipLeft = static_cast<LegoFloat>(mapLeft);
	m_clipBottom = static_cast<LegoFloat>(mapBottom);
	m_clipRight = static_cast<LegoFloat>(mapRight);

	GolImage* markerResource = m_images->GetItem(10);

	GolVec3 currentPosition;
	m_racer->m_visuals.m_carEntity->GetPosition(&currentPosition);

	GolVec3 cameraDirection;
	m_racer->m_cameraController->GetViewDirection(&cameraDirection);

	LegoFloat directionScale =
		directionLengthScale / static_cast<LegoFloat>(sqrt(
								   cameraDirection.m_y * cameraDirection.m_y + cameraDirection.m_x * cameraDirection.m_x
							   ));
	LegoFloat directionX = cameraDirection.m_x * directionScale;
	LegoFloat directionY = cameraDirection.m_y * directionScale;

	if (m_mapMaterial) {
		LegoFloat deltaY0;
		LegoFloat deltaY1;
		if (m_mirror) {
			deltaY0 = -m_mapMinY - currentPosition.m_y;
			deltaY1 = -m_mapMaxY - currentPosition.m_y;
			vertices[0].m_v = 0.0f;
			vertices[1].m_v = 0.0f;
			vertices[2].m_v = maxTextureCoordinate;
			vertices[3].m_v = maxTextureCoordinate;
		}
		else {
			deltaY0 = m_mapMaxY - currentPosition.m_y;
			deltaY1 = m_mapMinY - currentPosition.m_y;
			vertices[0].m_v = maxTextureCoordinate;
			vertices[1].m_v = maxTextureCoordinate;
			vertices[2].m_v = 0.0f;
			vertices[3].m_v = 0.0f;
		}

		LegoFloat deltaX0 = m_mapMinX - currentPosition.m_x;
		LegoFloat deltaX1 = m_mapMaxX - currentPosition.m_x;
		LegoFloat scaledDirectionX = directionX * m_aspectScale;
		LegoFloat scaledDirectionY = directionY * m_aspectScale;

		vertices[0].m_x = static_cast<LegoFloat>(mapCenterX) + deltaX0 * scaledDirectionY - deltaY0 * scaledDirectionX;
		vertices[0].m_y = static_cast<LegoFloat>(mapCenterY) - deltaX0 * directionX - deltaY0 * directionY;
		vertices[0].m_u = 0.0f;

		vertices[1].m_x = static_cast<LegoFloat>(mapCenterX) + deltaX1 * scaledDirectionY - deltaY0 * scaledDirectionX;
		vertices[1].m_y = static_cast<LegoFloat>(mapCenterY) - deltaX1 * directionX - deltaY0 * directionY;
		vertices[1].m_u = maxTextureCoordinate;

		vertices[2].m_x = static_cast<LegoFloat>(mapCenterX) + deltaX1 * scaledDirectionY - deltaY1 * scaledDirectionX;
		vertices[2].m_y = static_cast<LegoFloat>(mapCenterY) - deltaX1 * directionX - deltaY1 * directionY;
		vertices[2].m_u = maxTextureCoordinate;

		vertices[3].m_x = static_cast<LegoFloat>(mapCenterX) + deltaX0 * scaledDirectionY - deltaY1 * scaledDirectionX;
		vertices[3].m_y = static_cast<LegoFloat>(mapCenterY) - deltaX0 * directionX - deltaY1 * directionY;
		vertices[3].m_u = 0.0f;

		ClipTriangleTop(&vertices[0], &vertices[1], &vertices[3]);
		ClipTriangleTop(&vertices[3], &vertices[1], &vertices[2]);
	}

	LegoS32 markerOriginX = mapCenterX - (markerWidth >> 1);
	LegoS32 markerOriginY = mapCenterY - (markerHeight >> 1);
	GolVec3 position;
	Rect destRect;
	Rect sourceRect;

	for (LegoS32 racerIndex = static_cast<LegoS32>(m_raceState->GetRacerCount()) - 1; racerIndex >= 0; racerIndex--) {
		Racer* racer = &m_raceState->GetRacers()[racerIndex];
		if (racer != m_racer) {
			racer->m_visuals.m_carEntity->GetPosition(&position);

			LegoFloat deltaX = position.m_x - currentPosition.m_x;
			LegoFloat deltaY = position.m_y - currentPosition.m_y;

			destRect.m_left =
				markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_aspectScale);
			destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
			destRect.m_right = destRect.m_left + markerWidth;
			destRect.m_bottom = destRect.m_top + markerHeight;

			if (racer->m_controlMode == Racer::c_controlAi && racerIndex == 1) {
				sourceRect.m_left = 0x10;
			}
			else {
				sourceRect.m_left = 0;
			}
			if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
				sourceRect.m_top = 0x10;
			}
			else {
				sourceRect.m_top = 0;
			}
			sourceRect.m_right = sourceRect.m_left + 0x10;
			sourceRect.m_bottom = sourceRect.m_top + 0x10;

			m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
		}
	}

	if (m_timeRaceManager && m_timeRaceManager->HasRecordGhostMarker()) {
		m_timeRaceManager->GetRecordGhostMarkerEntity()->GetPosition(&position);

		LegoFloat deltaX = position.m_x - currentPosition.m_x;
		LegoFloat deltaY = position.m_y - currentPosition.m_y;

		destRect.m_left =
			markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_aspectScale);
		destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
		destRect.m_right = destRect.m_left + markerWidth;
		destRect.m_bottom = destRect.m_top + markerHeight;

		sourceRect.m_left = 0x10;
		if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
	}

	if (m_timeRaceManager && m_timeRaceManager->HasBestGhostMarker()) {
		m_timeRaceManager->GetBestGhostMarkerEntity()->GetPosition(&position);

		LegoFloat deltaX = position.m_x - currentPosition.m_x;
		LegoFloat deltaY = position.m_y - currentPosition.m_y;

		destRect.m_left =
			markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_aspectScale);
		destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
		destRect.m_right = destRect.m_left + markerWidth;
		destRect.m_bottom = destRect.m_top + markerHeight;

		sourceRect.m_left = 0;
		if (m_layout == c_layoutSplitTop || m_layout == c_layoutSplitBottom) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_renderer->DrawImageClipped(markerResource, 0, &destRect, &sourceRect, &m_viewport);
	}

	DrawMapArrow(mapCenterX, mapCenterY, 0.0f, -1.0f);

	for (LegoS32 j = 0; j < sizeOfArray(vertices); j++) {
		vertices[j].m_color.m_alp = 0xff;
	}

	vertices[0].m_x = static_cast<LegoFloat>(mapLeft);
	vertices[0].m_y = static_cast<LegoFloat>(mapTop);
	vertices[1].m_x = static_cast<LegoFloat>(mapRight);
	vertices[1].m_y = vertices[0].m_y;
	vertices[2].m_x = vertices[1].m_x;
	vertices[2].m_y = static_cast<LegoFloat>(mapBottom);
	vertices[3].m_x = vertices[0].m_x;
	vertices[3].m_y = vertices[2].m_y;
	vertices[4].m_x = vertices[0].m_x + 1.0f;
	vertices[4].m_y = vertices[0].m_y + 1.0f;
	vertices[5].m_x = vertices[1].m_x - 1.0f;
	vertices[5].m_y = vertices[4].m_y;
	vertices[6].m_x = vertices[2].m_x - 1.0f;
	vertices[6].m_y = vertices[2].m_y - 1.0f;
	vertices[7].m_x = vertices[4].m_x;
	vertices[7].m_y = vertices[6].m_y;

	m_renderer->DrawTriangle(&vertices[0], &vertices[1], &vertices[4], NULL, 0);
	m_renderer->DrawTriangle(&vertices[4], &vertices[1], &vertices[5], NULL, 0);
	m_renderer->DrawTriangle(&vertices[0], &vertices[4], &vertices[3], NULL, 0);
	m_renderer->DrawTriangle(&vertices[3], &vertices[4], &vertices[7], NULL, 0);
	m_renderer->DrawTriangle(&vertices[3], &vertices[7], &vertices[2], NULL, 0);
	m_renderer->DrawTriangle(&vertices[2], &vertices[7], &vertices[6], NULL, 0);
	m_renderer->DrawTriangle(&vertices[5], &vertices[1], &vertices[6], NULL, 0);
	m_renderer->DrawTriangle(&vertices[6], &vertices[1], &vertices[2], NULL, 0);
}

// FUNCTION: LEGORACERS 0x004258e0
void RaceHud::DrawSpeedometer()
{
	GolImage* resource0 = m_images->GetItem(0);
	LegoS32 resource0Width = resource0->GetWidth();
	LegoS32 width0 = static_cast<LegoS32>(
		static_cast<double>(resource0Width) * static_cast<double>(m_mapScale) * static_cast<double>(m_textScaleX)
	);
	LegoS32 resource0Height = resource0->GetHeight();
	double scaledHeight0 = static_cast<double>(resource0Height) * static_cast<double>(m_mapScale);
	LegoS32 height0 = static_cast<LegoS32>(scaledHeight0 * static_cast<double>(m_scaleY));
	m_renderer
		->DrawImage(resource0, 0, m_viewport.m_right - width0 - 2, m_viewport.m_bottom - height0 - 2, width0, height0);

	LegoFloat centerX = static_cast<LegoFloat>(m_viewport.m_right - ((52 * width0) >> 7) - 2);
	LegoFloat centerY = static_cast<LegoFloat>(m_viewport.m_bottom - ((52 * height0) >> 7) - 2);
	LegoFloat angle = m_speedValue * 18.0f;
	if (angle < 0.0f) {
		angle = 0.0f;
	}
	else if (angle > 3.4000001f) {
		angle = 3.4000001f;
	}

	GolRenderDevice::TexturedVertex vertices[5];
	LegoS32 i;
	for (i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_z = 0.0f;
		vertices[i].m_color.m_alp = 0xff;
	}

	LegoFloat angle0 = angle + 2.25f;
	GolMath::SinCos(angle0, &vertices[0].m_y, &vertices[0].m_x);

	LegoFloat angle1 = angle0 + 2.0943952f;
	GolMath::SinCos(angle1, &vertices[2].m_y, &vertices[2].m_x);

	LegoFloat angle2 = angle1 + 2.0943952f;
	GolMath::SinCos(angle2, &vertices[1].m_y, &vertices[1].m_x);

	vertices[0].m_x *= 45.0f;
	vertices[1].m_color.m_red = 0x96;
	vertices[0].m_color.m_red = 0x96;

	vertices[0].m_y *= 45.0f;
	vertices[1].m_color.m_grn = 0x96;
	vertices[0].m_color.m_grn = 0x96;
	vertices[1].m_color.m_blu = 0x96;
	vertices[0].m_color.m_blu = 0x96;

	vertices[1].m_x *= 7.0f;
	vertices[3].m_x = 0.0f;
	vertices[3].m_color.m_red = 0xc8;
	vertices[3].m_color.m_grn = 0xc8;

	vertices[1].m_y *= 7.0f;
	vertices[3].m_color.m_blu = 0xc8;
	vertices[3].m_y = 0.0f;
	vertices[4].m_color.m_red = 0xff;
	vertices[2].m_color.m_red = 0xff;

	vertices[2].m_x *= 7.0f;
	vertices[4].m_color.m_grn = 0xff;
	vertices[2].m_color.m_grn = 0xff;
	vertices[4].m_color.m_blu = 0xff;
	vertices[2].m_color.m_blu = 0xff;

	vertices[2].m_y *= 7.0f;

	for (i = 0; i < 4; i++) {
		vertices[i].m_x = (vertices[i].m_x * m_mapScale) * m_scaleX + centerX;
		vertices[i].m_y = (vertices[i].m_y * m_mapScale) * m_scaleY + centerY;
	}
	vertices[4].m_x = vertices[0].m_x;
	vertices[4].m_y = vertices[0].m_y;

	m_renderer->DrawTriangle(&vertices[1], &vertices[0], &vertices[3], NULL, 0);
	m_renderer->DrawTriangle(&vertices[2], &vertices[3], &vertices[4], NULL, 0);

	GolImage* resource1 = m_images->GetItem(1);
	LegoS32 resource1Width = resource1->GetWidth();
	LegoS32 width1 = static_cast<LegoS32>(
		static_cast<double>(resource1Width) * static_cast<double>(m_mapScale) * static_cast<double>(m_textScaleX)
	);
	LegoS32 resource1Height = resource1->GetHeight();
	double scaledHeight1 = static_cast<double>(resource1Height) * static_cast<double>(m_mapScale);
	LegoS32 height1 = static_cast<LegoS32>(scaledHeight1 * static_cast<double>(m_scaleY));
	m_renderer->DrawImage(
		resource1,
		0,
		static_cast<LegoS32>(centerX) - (width1 >> 1),
		static_cast<LegoS32>(centerY) - (height1 >> 1),
		width1,
		height1
	);
}

// FUNCTION: LEGORACERS 0x00425bf0
LegoS32 RaceHud::DrawTime(const LegoChar* p_text, LegoS32 p_x, LegoS32 p_y)
{
	CopyToGolString(p_text, m_scratchString);

	LegoS32 drawX;
	if (m_scratchString->SelectionLength() == 7) {
		drawX = m_longTimeWidth - m_shortTimeWidth;
		drawX += p_x;
	}
	else {
		drawX = p_x;
	}

	LegoFloat scaleY = m_scaleY * m_textScale;
	LegoFloat scaleX = m_textScaleX * m_textScale;
	m_renderer->DrawString(m_scratchString, m_font, drawX, p_y, scaleX, scaleY, NULL, 0);

	return drawX;
}

// FUNCTION: LEGORACERS 0x00425c70
undefined4 RaceHud::CopyToGolString(const LegoChar* p_text, GolString* p_string)
{
	LegoU32 length = ::strlen(p_text);
	LegoU32 i = 0;

	if (length) {
		undefined2* dest = g_textConversionBuffer;
		do {
			*dest++ = p_text[i++];
		} while (i < length);
	}

	g_textConversionBuffer[length] = 0;
	return p_string->GolStrcpy(g_textConversionBuffer);
}

// FUNCTION: LEGORACERS 0x00425cc0
void RaceHud::Reset()
{
	m_racer = NULL;
	m_visible = 1;
	m_renderer = NULL;
	m_soundSource = 0;
	m_images = 0;
	m_scratchString = NULL;
	m_font = NULL;
	m_numberFont = NULL;
	m_raceState = 0;
	m_elapsedMs = 0;
	m_layout = c_layoutNone;
	m_hideRaceInfo = 0;
	m_isTimeRace = 0;
	m_mirror = 0;
	m_gadgetMode = 0;
	m_bannerMs = 0;
	m_positionPulseMs = 0;
	m_speedValue = 0;
	m_lastLapIndex = 0;
	m_displayLapCount = 0;
	m_lapTimeMs = 0;
	m_bestLapMs = 0;
	m_finalPosition = 0;
	m_position = 0;
	m_shortTimeWidth = 0;
	m_longTimeWidth = 0;
	m_screenWidth = 0;
	m_screenHeight = 0;
	m_scaleX = 0;
	m_mapMaterial = 0;
	m_mapMaxX = 0;
	m_mapMinY = 0;
	m_mapMinX = 0;
	m_mapMaxY = 0;
	m_clipRight = 0;
	m_clipBottom = 0;
	m_clipLeft = 0;
	m_clipTop = 0;
}

// FUNCTION: LEGORACERS 0x00425d80
LegoS32 RaceHud::Initialize(
	GolD3DRenderDevice* p_renderer,
	GolNameTable* p_nameTable,
	GolString* p_string,
	GolImageDefinitionList* p_resourceTable,
	RaceState* p_raceState,
	TimeRaceManager* p_timeRaceManager,
	GolStringTable* p_stringTable,
	RacerSoundSource* p_soundSource,
	LegoBool p_isTimeRace,
	undefined4 p_hideRaceInfo
)
{
	LegoChar name[8];

	::strncpy(name, g_hudFontName, sizeof(name));
	GolFontBase* font;
	if (!p_nameTable->GetNameEntries()) {
		font = NULL;
	}
	else {
		font = static_cast<GolFontBase*>(p_nameTable->GetName(name));
	}
	m_font = font;

	::strncpy(name, g_hudNumberFontName, sizeof(name));
	if (!p_nameTable->GetNameEntries()) {
		font = NULL;
	}
	else {
		font = static_cast<GolFontBase*>(p_nameTable->GetName(name));
	}
	m_numberFont = font;

	m_racer = NULL;
	m_elapsedMs = 0;
	m_speedValue = 0;
	m_isTimeRace = 0;
	m_gadgetMode = 1;
	m_mapMaterial = 0;
	ResetDisplay(-1);
	m_images = p_resourceTable;
	m_scratchString = p_string;
	m_raceState = p_raceState;
	m_stringTable = p_stringTable;
	m_renderer = p_renderer;
	m_soundSource = p_soundSource;
	m_timeRaceManager = p_timeRaceManager;

	const GolRenderTarget* renderTargetHeight = p_renderer->GetRenderTargetInfo();
	const GolRenderTarget* renderTargetWidth = m_renderer->GetRenderTargetInfo();
	SetResolution(renderTargetWidth->GetWidth(), renderTargetHeight->GetHeight());

	m_hideRaceInfo = p_hideRaceInfo;
	m_isTimeRace = p_isTimeRace;
	m_elapsedMs = 0;
	LegoS32 result = SetLayout(m_layout);
	m_visible = 1;

	return result;
}

// FUNCTION: LEGORACERS 0x00425e90
LegoS32 RaceHud::SetLayout(LegoS32 p_mode)
{
	m_layout = static_cast<LegoU8>(p_mode);
	m_viewport.m_left = 0;
	LegoS32 width = m_screenWidth;
	m_mapScale = 0.8f;
	m_bannerScale = 0.8f;
	m_viewport.m_right = width;
	m_textScale = 0.9f;
	m_imageScale = 1.0f;
	p_mode = m_layout;

	switch (m_layout) {
	case 2:
		m_viewport.m_top = 0;
		m_viewport.m_bottom = m_screenHeight >> 1;
		break;
	case 3:
		m_viewport.m_bottom = m_screenHeight;
		m_viewport.m_top = m_screenHeight >> 1;
		break;
	case 1:
		m_viewport.m_top = 0;
		m_viewport.m_bottom = m_screenHeight;
		m_bannerScale = 1.0f;
		m_mapScale = 1.0f;
		m_imageScale = 1.0f;
		m_textScale = 1.0f;
		break;
	case 0:
		return p_mode;
	}

	width -= m_viewport.m_left;

	FormatTime(m_lapTimeText.m_text, 0);
	CopyToGolString(m_lapTimeText.m_text, m_scratchString);
	LegoS32 v25;
	m_font->MeasureString(m_scratchString, &p_mode, &v25);
	p_mode = static_cast<LegoS32>(static_cast<LegoFloat>(p_mode) * m_textScale);
	m_shortTimeWidth = static_cast<LegoS32>(static_cast<LegoFloat>(p_mode) * m_textScaleX);

	FormatTime(m_lapTimeText.m_text, 0x36ee08);
	CopyToGolString(m_lapTimeText.m_text, m_scratchString);
	m_font->MeasureString(m_scratchString, &p_mode, &v25);
	p_mode = static_cast<LegoS32>(static_cast<LegoFloat>(p_mode) * m_textScale);
	v25 = static_cast<LegoS32>(static_cast<LegoFloat>(v25) * m_textScale);
	m_longTimeWidth = static_cast<LegoS32>(static_cast<LegoFloat>(p_mode) * m_textScaleX);

	LegoS32 v26 = m_viewport.m_right - ((11 * m_longTimeWidth) >> 3);
	m_lapTimeX = v26;
	LegoS32 topTextY = m_viewport.m_top - static_cast<LegoS32>(m_scaleY * g_hudTopTextOffset);
	LegoS32 v27 = (static_cast<LegoU32>(7 * v25)) >> 3;
	m_lapTimeY = topTextY;
	m_positionX = m_viewport.m_left + (static_cast<LegoU32>(width) / 10);
	m_positionY = topTextY;
	m_bestLapX = v26;

	m_bestLapY = topTextY + static_cast<LegoS32>(static_cast<double>(v27) * m_scaleY);
	m_totalTimeX = v26;

	v27 = (static_cast<LegoU32>(14 * v25)) >> 3;
	m_totalTimeY = topTextY + static_cast<LegoS32>(static_cast<double>(v27) * m_scaleY);
	m_timeBehindX = v26;

	v27 = (static_cast<LegoU32>(21 * v25)) >> 3;
	LegoS32 bottomTextY = static_cast<LegoS32>(static_cast<double>(v27) * m_scaleY) + topTextY;
	m_centerX = (m_viewport.m_right + m_viewport.m_left) >> 1;
	m_timeBehindY = bottomTextY;
	m_bannerY = bottomTextY;

	m_stringTable->CopyStringByIndex(&m_labelString, 0x24);
	m_font->MeasureString(&m_labelString, &p_mode, &v25);
	m_wrongWayX = m_centerX - (static_cast<LegoS32>(static_cast<LegoFloat>(p_mode) * m_textScaleX) >> 1);
	m_wrongWayY = m_viewport.m_top + ((m_viewport.m_bottom - m_viewport.m_top) / 5);

	GolImage* resource = m_images->GetItem(11);
	m_powerupX = m_viewport.m_left + (static_cast<LegoU32>(width) >> 5);

	p_mode = static_cast<LegoS32>(
		(static_cast<double>(static_cast<LegoS32>(resource->GetHeight())) * m_imageScale + g_unk0x004afde0) * m_scaleY
	);
	m_powerupY = m_viewport.m_bottom - p_mode;

	return p_mode;
}

// FUNCTION: LEGORACERS 0x004261f0
LegoS32 RaceHud::SetResolution(LegoS32 p_width, LegoS32 p_height)
{
	m_screenWidth = p_width;
	m_screenHeight = p_height;

	double scaledWidth = 3 * p_width;
	LegoFloat ratio = static_cast<LegoFloat>(scaledWidth / static_cast<double>(4 * p_height));
	m_aspectRatio = ratio;

	LegoS32 scaledHeight = p_height << 2;
	LegoFloat scale = static_cast<LegoFloat>(p_height) * g_hudBaseScale;
	m_scaleY = scale;
	m_textScaleX = scale * ratio;

	LegoFloat aspect = static_cast<LegoFloat>(scaledWidth / static_cast<double>(scaledHeight));
	m_aspectScale = aspect;
	LegoS32 mode = m_layout;
	m_scaleX = aspect * scale;

	return SetLayout(mode);
}

// FUNCTION: LEGORACERS 0x00426280
void RaceHud::SetMapInfo(
	GolMaterial* p_material,
	LegoFloat p_minX,
	LegoFloat p_maxY,
	LegoFloat p_maxX,
	LegoFloat p_minY,
	LegoBool p_mirror
)
{
	m_mapMaterial = p_material;
	m_mapMaxY = p_maxY;
	m_mapMinX = p_minX;
	m_mapMinY = p_minY;
	m_mapMaxX = p_maxX;
	m_mirror = p_mirror;
}

// FUNCTION: LEGORACERS 0x004262c0
Racer* RaceHud::SetRacer(Racer* p_racer)
{
	m_racer = p_racer;
	p_racer->m_hud = this;

	return p_racer;
}

// FUNCTION: LEGORACERS 0x004262d0
void RaceHud::ResetDisplay(LegoS32 p_lapCount)
{
	m_lastLapIndex = -1;
	m_finalPosition = -1;
	m_displayLapCount = p_lapCount;
	m_position = 8;
	m_positionPulseMs = 0;
	m_bannerMs = 0;
	m_bestLapMs = 0;
	m_lapText[0] = 0;

	FormatTime(m_lapTimeText.m_text, 0);
	m_bestLapText = m_lapTimeText;
	m_timeBehindText = m_lapTimeText;
	m_totalTimeText = m_lapTimeText;
}

// FUNCTION: LEGORACERS 0x00426360
void RaceHud::StartCountdown()
{
	m_bannerMs = 1;
}

// FUNCTION: LEGORACERS 0x00426370
void RaceHud::ShowFinish()
{
	LegoS32 value = m_racer->m_standingsPosition;

	m_bannerMs = -1;
	m_finalPosition = value - 1;
}

// FUNCTION: LEGORACERS 0x00426390
void RaceHud::Update(LegoU32 p_elapsedMs)
{
	m_elapsedMs += p_elapsedMs;
}

// STUB: LEGORACERS 0x004263a0
void RaceHud::Draw()
{
	LegoBool32 drawLapTime = TRUE;
	LegoU32 elapsedMs = m_elapsedMs;
	m_elapsedMs = 0;

	if (m_racer == NULL || !m_layout) {
		return;
	}

	if (m_bannerMs > 0) {
		LegoS32 previousState = m_bannerMs;
		m_bannerMs += elapsedMs;
		LegoS32 countdownState = m_bannerMs / 1000;
		LegoFloat pulseScale =
			static_cast<LegoFloat>(200 * (5 * countdownState + 5) - m_bannerMs) * g_ghostAnimationRateScale * 0.001f;

		if (countdownState < 3) {
			CopyToGolString(g_positionDigits[2 - countdownState], m_scratchString);

			LegoS32 textWidth;
			LegoS32 textHeight;
			m_numberFont->MeasureString(m_scratchString, &textWidth, &textHeight);

			LegoFloat scale = m_bannerScale * pulseScale;
			LegoFloat scaleX = m_textScaleX * scale;
			LegoFloat scaleY = m_scaleY * scale;
			textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
			textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

			m_numberFont->SetColor(0xff, 0xff, 0, 0xff);
			if (m_visible) {
				m_renderer->DrawString(
					m_scratchString,
					m_numberFont,
					m_centerX - (static_cast<LegoU32>(textWidth) >> 1),
					m_bannerY - (static_cast<LegoU32>(textHeight) >> 2),
					scaleX,
					scaleY,
					NULL,
					0
				);
			}
			m_numberFont->SetColor(0xff, 0xff, 0xff, 0xff);

			if ((previousState == 1 || previousState / 1000 != countdownState) && m_soundSource) {
				m_soundSource->PlaySoundById(0);
			}
		}
		else if (countdownState < 5) {
			if (countdownState < 4) {
				pulseScale = 1.8f;
			}

			m_stringTable->CopyStringByIndex(&m_labelString, 0x29);

			LegoS32 textWidth;
			LegoS32 textHeight;
			m_numberFont->MeasureString(&m_labelString, &textWidth, &textHeight);

			LegoFloat scale = m_bannerScale * pulseScale;
			LegoFloat scaleX = m_textScaleX * scale;
			LegoFloat scaleY = m_scaleY * scale;
			textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
			textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

			m_numberFont->SetColor(0xff, 0xff, 0, 0xff);
			if (m_visible) {
				m_renderer->DrawString(
					&m_labelString,
					m_numberFont,
					m_centerX - (static_cast<LegoU32>(textWidth) >> 1),
					m_bannerY - (static_cast<LegoU32>(textHeight) >> 2),
					scaleX,
					scaleY,
					NULL,
					0
				);
			}
			m_numberFont->SetColor(0xff, 0xff, 0xff, 0xff);

			if (m_soundSource && countdownState == 3 && previousState / 1000 != 3) {
				m_soundSource->PlaySoundById(c_soundCountdown);
			}
		}
		else {
			m_bannerMs = 0;
		}
	}
	else if (m_bannerMs < 0) {
		m_stringTable->CopyStringByIndex(&m_labelString, 0x28);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_numberFont->MeasureString(&m_labelString, &textWidth, &textHeight);

		LegoFloat scaleX = m_textScaleX * m_bannerScale;
		LegoFloat scaleY = m_scaleY * m_bannerScale;
		textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
		textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

		if (m_visible) {
			m_renderer->DrawString(
				&m_labelString,
				m_numberFont,
				m_centerX - (static_cast<LegoU32>(textWidth) >> 1),
				m_bannerY - (static_cast<LegoU32>(textHeight) >> 2),
				scaleX,
				scaleY,
				NULL,
				0
			);
		}

		m_bannerMs -= elapsedMs;
		if (m_bannerMs < -60000) {
			m_bannerMs = -60000;
		}
	}

	Racer* racer = m_racer;
	if (racer->m_flags & 0x10) {
		return;
	}

	LegoS32 positionIndex;
	if (!m_positionPulseMs) {
		positionIndex = m_finalPosition;
		if (positionIndex < 0) {
			positionIndex = racer->m_standingsPosition - 1;
		}
		if (positionIndex > 8) {
			positionIndex = 8;
		}
		if (positionIndex != m_position) {
			m_position = positionIndex;
			m_positionPulseMs = 1;
		}
	}
	else {
		positionIndex = m_position;
	}

	LegoS32 lapIndex = racer->m_lapsCompleted;
	LegoS32 lapCount = racer->m_lapCount;
	LegoU32 totalTime = 0;

	if (lapIndex < lapCount) {
		m_lapTimeMs = racer->m_lapTimes[lapIndex];
		if (lapIndex && m_lapTimeMs < 3000) {
			if ((m_lapTimeMs / 250) & 1) {
				drawLapTime = FALSE;
			}
			else {
				m_lapTimeMs = racer->m_lapTimes[lapIndex - 1];
				FormatTime(m_lapTimeText.m_text, m_lapTimeMs);
			}
		}
		else {
			FormatTime(m_lapTimeText.m_text, m_lapTimeMs);
		}

		for (LegoS32 i = 0; i <= lapIndex; i++) {
			totalTime += racer->m_lapTimes[i];
		}
	}
	else {
		LegoS32 hiddenTime = -m_bannerMs;
		if (hiddenTime < 3000 && ((hiddenTime / 250) & 1)) {
			drawLapTime = FALSE;
		}
		else {
			m_lapTimeMs = racer->m_lapTimes[lapCount - 1];
			FormatTime(m_lapTimeText.m_text, m_lapTimeMs);
		}

		for (LegoS32 i = 0; i < lapIndex; i++) {
			totalTime += racer->m_lapTimes[i];
		}
	}

	FormatTime(m_totalTimeText.m_text, totalTime);
	if (racer->m_timeBehindDisplayMs) {
		FormatTime(m_timeBehindText.m_text, racer->m_timeBehind);
	}

	if (lapIndex != m_lastLapIndex) {
		if (m_lastLapIndex != -1 && m_lastLapIndex < racer->m_lapCount) {
			LegoU32 completedLapTime = racer->m_lapTimes[m_lastLapIndex];
			if (completedLapTime <= m_bestLapMs || !m_bestLapMs) {
				m_bestLapMs = completedLapTime;
				FormatTime(m_bestLapText.m_text, completedLapTime);
			}
		}

		m_lastLapIndex = lapIndex;
		LegoS32 displayLap = lapIndex + 1;
		if (m_displayLapCount <= 0) {
			if (displayLap > racer->m_lapCount) {
				displayLap = racer->m_lapCount;
			}
			::sprintf(m_lapText, "%d", displayLap);
		}
		else {
			if (displayLap > static_cast<LegoS32>(m_displayLapCount)) {
				displayLap = m_displayLapCount;
			}
			::sprintf(m_lapText, "%d/%d", displayLap, m_displayLapCount);
		}
	}

	if (!m_hideRaceInfo) {
		CopyToGolString(m_lapText, m_scratchString);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_font->MeasureString(m_scratchString, &textWidth, &textHeight);

		LegoS32 scaledLabelWidth = static_cast<LegoS32>(static_cast<LegoFloat>(textWidth) * m_textScale);
		LegoS32 labelPadding = static_cast<LegoS32>(m_textScale * -14.0f);
		LegoS32 labelOffset =
			static_cast<LegoS32>(static_cast<LegoFloat>(scaledLabelWidth - labelPadding) * m_textScaleX);
		LegoS32 lapLabelX = m_lapTimeX - labelOffset;
		m_renderer->DrawString(
			m_scratchString,
			m_font,
			lapLabelX,
			m_lapTimeY,
			m_textScaleX * m_textScale,
			m_scaleY * m_textScale,
			NULL,
			0
		);

		m_stringTable->CopyStringByIndex(&m_labelString, 0x27);
		m_font->MeasureString(&m_labelString, &textWidth, &textHeight);
		scaledLabelWidth = static_cast<LegoS32>(static_cast<LegoFloat>(textWidth) * m_textScale);
		labelPadding = static_cast<LegoS32>(m_textScale * -6.0f);
		labelOffset = static_cast<LegoS32>(static_cast<LegoFloat>(scaledLabelWidth - labelPadding) * m_textScaleX);
		lapLabelX -= labelOffset;
		m_renderer->DrawString(
			&m_labelString,
			m_font,
			lapLabelX,
			m_lapTimeY,
			m_textScaleX * m_textScale,
			m_scaleY * m_textScale,
			NULL,
			0
		);

		if (drawLapTime) {
			DrawTime(m_lapTimeText.m_text, m_lapTimeX, m_lapTimeY);
		}

		if (m_bestLapMs) {
			m_stringTable->CopyStringByIndex(&m_labelString, 0x25);
			m_font->MeasureString(&m_labelString, &textWidth, &textHeight);
			scaledLabelWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * m_textScale);
			labelPadding = static_cast<LegoS32>(static_cast<double>(m_textScale) * -14.0);
			labelOffset = static_cast<LegoS32>(static_cast<double>(scaledLabelWidth - labelPadding) * m_textScaleX);
			m_renderer->DrawString(
				&m_labelString,
				m_font,
				m_bestLapX - labelOffset,
				m_bestLapY,
				m_textScaleX * m_textScale,
				m_scaleY * m_textScale,
				NULL,
				0
			);
			DrawTime(m_bestLapText.m_text, m_bestLapX, m_bestLapY);
		}

		if (m_isTimeRace) {
			m_stringTable->CopyStringByIndex(&m_labelString, 0x26);
			m_font->MeasureString(&m_labelString, &textWidth, &textHeight);
			labelOffset = static_cast<LegoS32>(static_cast<double>(textWidth + 14) * m_textScaleX);
			m_renderer->DrawString(
				&m_labelString,
				m_font,
				m_totalTimeX - labelOffset,
				m_totalTimeY,
				m_textScaleX,
				m_scaleY,
				NULL,
				0
			);
			DrawTime(m_totalTimeText.m_text, m_totalTimeX, m_totalTimeY);
		}
		else if (positionIndex != 8) {
			m_stringTable->CopyStringByIndex(&m_labelString, g_positionStringIds[positionIndex]);
			m_renderer->DrawString(
				&m_labelString,
				m_font,
				m_positionX + static_cast<LegoS32>(m_textScaleX * 5.0f),
				m_positionY,
				m_textScaleX * m_textScale,
				m_scaleY * m_textScale,
				NULL,
				0
			);

			CopyToGolString(g_positionDigits[positionIndex], m_scratchString);
			m_numberFont->MeasureString(m_scratchString, &textWidth, &textHeight);
			LegoS32 numberOffset = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(static_cast<double>(textWidth) * m_textScaleX)) * m_textScale
			);

			if (m_positionPulseMs) {
				m_positionPulseMs += elapsedMs;
				LegoFloat positionScale;
				if (m_positionPulseMs > 350) {
					if (m_positionPulseMs > 1050) {
						m_positionPulseMs = 0;
					}
					positionScale = 1.0f;
				}
				else if (m_positionPulseMs <= 175) {
					positionScale =
						static_cast<LegoFloat>(static_cast<LegoS32>(m_positionPulseMs)) * 0.0057142857f + 1.0f;
				}
				else {
					LegoU32 timer = m_positionPulseMs - 175;
					positionScale = 2.0f - static_cast<LegoFloat>(static_cast<LegoS32>(timer)) * 0.0057142857f;
				}
				positionScale *= m_textScale;

				m_renderer->DrawString(
					m_scratchString,
					m_numberFont,
					m_positionX - numberOffset,
					m_positionY,
					m_textScaleX * positionScale,
					m_scaleY * positionScale,
					NULL,
					0
				);
			}
			else {
				m_renderer->DrawString(
					m_scratchString,
					m_numberFont,
					m_positionX - numberOffset,
					m_positionY,
					m_textScaleX * m_textScale,
					m_scaleY * m_textScale,
					NULL,
					0
				);
			}
		}
		else {
			m_positionPulseMs = 0;
		}

		if (m_racer->m_timeBehindDisplayMs) {
			LegoS32 medalX = DrawTime(m_timeBehindText.m_text, m_timeBehindX, m_timeBehindY);
			m_stringTable->CopyStringByIndex(&m_labelString, 0x21);
			m_font->MeasureString(&m_labelString, &textWidth, &textHeight);
			if (m_visible) {
				m_renderer->DrawString(
					&m_labelString,
					m_font,
					medalX - static_cast<LegoS32>(static_cast<double>(textWidth + 4) * m_textScaleX),
					m_timeBehindY,
					m_textScaleX,
					m_scaleY,
					NULL,
					0
				);
			}
		}

		if (m_racer->m_flags & 0x4000) {
			m_stringTable->CopyStringByIndex(&m_labelString, 0x24);
			if (m_visible) {
				m_renderer
					->DrawString(&m_labelString, m_font, m_wrongWayX, m_wrongWayY, m_textScaleX, m_scaleY, NULL, 0);
			}
		}
	}

	LegoS32 itemLevel = m_racer->m_whiteBrickCount;
	LegoS32 itemType = m_racer->m_heldPowerupColor - 1;
	GolImage* itemResource;
	FourBytes itemColor;
	itemColor.m_uBytes[3] = 0xff;

	switch (itemType) {
	case 0:
		itemColor.m_uBytes[0] = 0xff;
		itemColor.m_uBytes[1] = 0;
		itemColor.m_uBytes[2] = 0;
		itemResource = m_images->GetItem(itemLevel + 2);
		break;
	case 1:
		itemColor.m_uBytes[0] = 0x50;
		itemColor.m_uBytes[1] = 0x50;
		itemColor.m_uBytes[2] = 0xff;
		itemResource = m_images->GetItem(itemLevel + 16);
		break;
	case 2:
		itemColor.m_uBytes[0] = 0;
		itemColor.m_uBytes[1] = 0xff;
		itemColor.m_uBytes[2] = 0;
		itemResource = m_images->GetItem(itemLevel + 20);
		break;
	case 3:
		itemColor.m_uBytes[0] = 0xff;
		itemColor.m_uBytes[1] = 0xff;
		itemColor.m_uBytes[2] = 0;
		itemResource = m_images->GetItem(itemLevel + 6);
		break;
	default:
		itemColor.m_uBytes[0] = 0xff;
		itemColor.m_uBytes[1] = 0xff;
		itemColor.m_uBytes[2] = 0xff;
		itemResource = NULL;
		break;
	}

	if (itemResource || itemLevel) {
		GolImage* background = m_images->GetItem(11);
		LegoS32 width = static_cast<LegoS32>(
			static_cast<double>(static_cast<LegoS32>(background->GetWidth())) * m_imageScale * m_textScaleX
		);
		LegoS32 height = static_cast<LegoS32>(
			static_cast<double>(static_cast<LegoS32>(background->GetHeight())) * m_imageScale * m_scaleY
		);
		m_renderer->DrawImage(background, 0, m_powerupX, m_powerupY, width, height);

		GolImage* colorResource = m_images->GetItem(12);
		colorResource->m_tintColor = itemColor;
		m_renderer->DrawImage(colorResource, 0, m_powerupX, m_powerupY, width, height);

		if (itemResource) {
			LegoS32 itemWidth = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(itemResource->GetWidth())) * m_imageScale * m_textScaleX
			);
			LegoS32 itemHeight = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(itemResource->GetHeight())) * m_imageScale * m_scaleY
			);
			m_renderer->DrawImage(
				itemResource,
				0,
				m_powerupX + (static_cast<LegoU32>(31 * width) >> 6) - (static_cast<LegoU32>(itemWidth) >> 1),
				m_powerupY + (static_cast<LegoU32>(38 * height) >> 6) - (static_cast<LegoU32>(itemHeight) >> 1),
				itemWidth,
				itemHeight
			);
		}

		if (itemLevel) {
			GolImage* levelResource = m_images->GetItem(itemLevel + 12);
			LegoS32 levelWidth = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(levelResource->GetWidth())) * m_imageScale * m_textScaleX
			);
			LegoS32 levelHeight = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(levelResource->GetHeight())) * m_imageScale * m_scaleY
			);
			m_renderer->DrawImage(
				levelResource,
				0,
				m_powerupX + (static_cast<LegoU32>(24 * width) >> 6),
				m_powerupY,
				levelWidth,
				levelHeight
			);
		}
	}

	m_speedValue = m_racer->m_physics.m_forwardSpeed * g_unk0x004b02e0 + m_speedValue * 0.80000001f;

	switch (m_gadgetMode) {
	case 1:
		DrawFixedMap();
		break;
	case 2:
		DrawSpeedometer();
		break;
	case 3:
		DrawRotatingMap();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00427140
RaceHud::RaceHud()
{
	Reset();
}
