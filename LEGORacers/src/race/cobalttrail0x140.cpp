#include "race/cobalttrail0x140.h"

#include "decomp.h"
#include "golfontbase.h"
#include "golmath.h"
#include "golnametable.h"
#include "image/utopianpan0xa4.h"
#include "race/racecameracontroller.h"
#include "race/timeracemanager.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

DECOMP_SIZE_ASSERT(CobaltTrail0x140, 0x140)
DECOMP_SIZE_ASSERT(CobaltTrail0x140::TimeText, 0x09)

// GLOBAL: LEGORACERS 0x004c4814
undefined2 g_unk0x004c4814[42];

// GLOBAL: LEGORACERS 0x004afde0
extern const LegoFloat g_unk0x004afde0 = 10.0f;

// GLOBAL: LEGORACERS 0x004b02ac
extern const LegoFloat g_unk0x004b02ac = 128.0f;

// GLOBAL: LEGORACERS 0x004b02b0
extern const LegoFloat g_unk0x004b02b0 = 0.03125f;

// GLOBAL: LEGORACERS 0x004b02b4
extern const LegoFloat g_unk0x004b02b4 = 16.0f;

// GLOBAL: LEGORACERS 0x004b02d4
extern const LegoFloat g_unk0x004b02d4 = -7.0f;

// GLOBAL: LEGORACERS 0x004b02d8
extern const LegoFloat g_unk0x004b02d8 = 0.0020833334f;

// GLOBAL: LEGORACERS 0x004be8a8
extern const LegoChar* g_unk0x004be8a8 = "font_ths";

// GLOBAL: LEGORACERS 0x004be8ac
extern const LegoChar* g_unk0x004be8ac = "ignum";

static const LegoChar* g_unk0x004b0270[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
static const LegoS16 g_unk0x004b0290[8] = {0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20};

// FUNCTION: LEGORACERS 0x00423fc0
void CobaltTrail0x140::FUN_00423fc0(
	const GolRenderDevice::TexturedVertex* p_unk0x04,
	const GolRenderDevice::TexturedVertex* p_unk0x08,
	const GolRenderDevice::TexturedVertex* p_unk0x0c
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_unk0x08->m_y < m_unk0x12c) {
		if (p_unk0x04->m_y < m_unk0x12c) {
			if (p_unk0x0c->m_y < m_unk0x12c) {
				return;
			}
		}
		else {
			temporaryVertex = p_unk0x04;
			p_unk0x04 = p_unk0x08;
			p_unk0x08 = p_unk0x0c;
			p_unk0x0c = temporaryVertex;
		}
	}
	else if (p_unk0x0c->m_y < m_unk0x12c) {
		temporaryVertex = p_unk0x0c;
		p_unk0x0c = p_unk0x08;
		p_unk0x08 = p_unk0x04;
		p_unk0x04 = temporaryVertex;
	}

	if (p_unk0x04->m_y < m_unk0x12c) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_y = m_unk0x12c;
		intersection1.m_y = m_unk0x12c;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_unk0x04->m_color;
		intersection1.m_color = p_unk0x04->m_color;

		LegoFloat amount = (p_unk0x0c->m_y - m_unk0x12c) / (p_unk0x0c->m_y - p_unk0x04->m_y);
		intersection0.m_x = (p_unk0x04->m_x - p_unk0x0c->m_x) * amount + p_unk0x0c->m_x;
		intersection0.m_u = (p_unk0x04->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
		intersection0.m_v = (p_unk0x04->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

		if (p_unk0x08->m_y < m_unk0x12c) {
			amount = (p_unk0x0c->m_y - m_unk0x12c) / (p_unk0x0c->m_y - p_unk0x08->m_y);
			intersection1.m_x = (p_unk0x08->m_x - p_unk0x0c->m_x) * amount + p_unk0x0c->m_x;
			intersection1.m_u = (p_unk0x08->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
			intersection1.m_v = (p_unk0x08->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

			FUN_00424190(&intersection0, &intersection1, p_unk0x0c);
		}
		else {
			amount = (p_unk0x08->m_y - m_unk0x12c) / (p_unk0x08->m_y - p_unk0x04->m_y);
			intersection1.m_x = (p_unk0x04->m_x - p_unk0x08->m_x) * amount + p_unk0x08->m_x;
			intersection1.m_u = (p_unk0x04->m_u - p_unk0x08->m_u) * amount + p_unk0x08->m_u;
			intersection1.m_v = (p_unk0x04->m_v - p_unk0x08->m_v) * amount + p_unk0x08->m_v;

			FUN_00424190(p_unk0x0c, &intersection1, p_unk0x08);
			FUN_00424190(&intersection0, &intersection1, p_unk0x0c);
		}

		return;
	}

	FUN_00424190(p_unk0x04, p_unk0x08, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00424190
void CobaltTrail0x140::FUN_00424190(
	const GolRenderDevice::TexturedVertex* p_unk0x04,
	const GolRenderDevice::TexturedVertex* p_unk0x08,
	const GolRenderDevice::TexturedVertex* p_unk0x0c
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_unk0x08->m_x < m_unk0x130) {
		if (p_unk0x04->m_x < m_unk0x130) {
			if (p_unk0x0c->m_x < m_unk0x130) {
				return;
			}
		}
		else {
			temporaryVertex = p_unk0x04;
			p_unk0x04 = p_unk0x08;
			p_unk0x08 = p_unk0x0c;
			p_unk0x0c = temporaryVertex;
		}
	}
	else if (p_unk0x0c->m_x < m_unk0x130) {
		temporaryVertex = p_unk0x0c;
		p_unk0x0c = p_unk0x08;
		p_unk0x08 = p_unk0x04;
		p_unk0x04 = temporaryVertex;
	}

	if (p_unk0x04->m_x < m_unk0x130) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_x = m_unk0x130;
		intersection1.m_x = m_unk0x130;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_unk0x04->m_color;
		intersection1.m_color = p_unk0x04->m_color;

		LegoFloat amount = (p_unk0x0c->m_x - m_unk0x130) / (p_unk0x0c->m_x - p_unk0x04->m_x);
		intersection0.m_y = (p_unk0x04->m_y - p_unk0x0c->m_y) * amount + p_unk0x0c->m_y;
		intersection0.m_u = (p_unk0x04->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
		intersection0.m_v = (p_unk0x04->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

		if (p_unk0x08->m_x < m_unk0x130) {
			amount = (p_unk0x0c->m_x - m_unk0x130) / (p_unk0x0c->m_x - p_unk0x08->m_x);
			intersection1.m_y = (p_unk0x08->m_y - p_unk0x0c->m_y) * amount + p_unk0x0c->m_y;
			intersection1.m_u = (p_unk0x08->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
			intersection1.m_v = (p_unk0x08->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

			FUN_00424340(&intersection0, &intersection1, p_unk0x0c);
		}
		else {
			amount = (p_unk0x08->m_x - m_unk0x130) / (p_unk0x08->m_x - p_unk0x04->m_x);
			intersection1.m_y = (p_unk0x04->m_y - p_unk0x08->m_y) * amount + p_unk0x08->m_y;
			intersection1.m_u = (p_unk0x04->m_u - p_unk0x08->m_u) * amount + p_unk0x08->m_u;
			intersection1.m_v = (p_unk0x04->m_v - p_unk0x08->m_v) * amount + p_unk0x08->m_v;

			FUN_00424340(p_unk0x0c, &intersection1, p_unk0x08);
			FUN_00424340(&intersection0, &intersection1, p_unk0x0c);
		}

		return;
	}

	FUN_00424340(p_unk0x04, p_unk0x08, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00424340
void CobaltTrail0x140::FUN_00424340(
	const GolRenderDevice::TexturedVertex* p_unk0x04,
	const GolRenderDevice::TexturedVertex* p_unk0x08,
	const GolRenderDevice::TexturedVertex* p_unk0x0c
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_unk0x08->m_x > m_unk0x138) {
		if (p_unk0x04->m_x > m_unk0x138) {
			if (p_unk0x0c->m_x > m_unk0x138) {
				return;
			}
		}
		else {
			temporaryVertex = p_unk0x04;
			p_unk0x04 = p_unk0x08;
			p_unk0x08 = p_unk0x0c;
			p_unk0x0c = temporaryVertex;
		}
	}
	else if (p_unk0x0c->m_x > m_unk0x138) {
		temporaryVertex = p_unk0x0c;
		p_unk0x0c = p_unk0x08;
		p_unk0x08 = p_unk0x04;
		p_unk0x04 = temporaryVertex;
	}

	if (p_unk0x04->m_x > m_unk0x138) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection0.m_x = m_unk0x138;
		intersection1.m_x = m_unk0x138;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_unk0x04->m_color;
		intersection1.m_color = p_unk0x04->m_color;

		LegoFloat amount = (p_unk0x0c->m_x - m_unk0x138) / (p_unk0x0c->m_x - p_unk0x04->m_x);
		intersection0.m_y = (p_unk0x04->m_y - p_unk0x0c->m_y) * amount + p_unk0x0c->m_y;
		intersection0.m_u = (p_unk0x04->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
		intersection0.m_v = (p_unk0x04->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

		if (p_unk0x08->m_x > m_unk0x138) {
			amount = (p_unk0x0c->m_x - m_unk0x138) / (p_unk0x0c->m_x - p_unk0x08->m_x);
			intersection1.m_y = (p_unk0x08->m_y - p_unk0x0c->m_y) * amount + p_unk0x0c->m_y;
			intersection1.m_u = (p_unk0x08->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
			intersection1.m_v = (p_unk0x08->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

			FUN_004244f0(&intersection0, &intersection1, p_unk0x0c);
		}
		else {
			amount = (p_unk0x08->m_x - m_unk0x138) / (p_unk0x08->m_x - p_unk0x04->m_x);
			intersection1.m_y = (p_unk0x04->m_y - p_unk0x08->m_y) * amount + p_unk0x08->m_y;
			intersection1.m_u = (p_unk0x04->m_u - p_unk0x08->m_u) * amount + p_unk0x08->m_u;
			intersection1.m_v = (p_unk0x04->m_v - p_unk0x08->m_v) * amount + p_unk0x08->m_v;

			FUN_004244f0(p_unk0x0c, &intersection1, p_unk0x08);
			FUN_004244f0(&intersection0, &intersection1, p_unk0x0c);
		}

		return;
	}

	FUN_004244f0(p_unk0x04, p_unk0x08, p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x004244f0
void CobaltTrail0x140::FUN_004244f0(
	const GolRenderDevice::TexturedVertex* p_unk0x04,
	const GolRenderDevice::TexturedVertex* p_unk0x08,
	const GolRenderDevice::TexturedVertex* p_unk0x0c
)
{
	const GolRenderDevice::TexturedVertex* temporaryVertex;

	if (p_unk0x08->m_y > m_unk0x134) {
		if (p_unk0x04->m_y > m_unk0x134) {
			if (p_unk0x0c->m_y > m_unk0x134) {
				return;
			}
		}
		else {
			temporaryVertex = p_unk0x04;
			p_unk0x04 = p_unk0x08;
			p_unk0x08 = p_unk0x0c;
			p_unk0x0c = temporaryVertex;
		}
	}
	else if (p_unk0x0c->m_y > m_unk0x134) {
		temporaryVertex = p_unk0x0c;
		p_unk0x0c = p_unk0x08;
		p_unk0x08 = p_unk0x04;
		p_unk0x04 = temporaryVertex;
	}

	if (p_unk0x04->m_y > m_unk0x134) {
		GolRenderDevice::TexturedVertex intersection0;
		GolRenderDevice::TexturedVertex intersection1;
		intersection1.m_y = intersection0.m_y = m_unk0x134;
		intersection0.m_z = 0.0f;
		intersection1.m_z = 0.0f;
		intersection0.m_color = p_unk0x04->m_color;
		intersection1.m_color = p_unk0x04->m_color;

		LegoFloat amount = (p_unk0x0c->m_y - m_unk0x134) / (p_unk0x0c->m_y - p_unk0x04->m_y);
		intersection0.m_x = (p_unk0x04->m_x - p_unk0x0c->m_x) * amount + p_unk0x0c->m_x;
		intersection0.m_u = (p_unk0x04->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
		intersection0.m_v = (p_unk0x04->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;

		if (p_unk0x08->m_y > m_unk0x134) {
			amount = (p_unk0x0c->m_y - m_unk0x134) / (p_unk0x0c->m_y - p_unk0x08->m_y);
			intersection1.m_x = (p_unk0x08->m_x - p_unk0x0c->m_x) * amount + p_unk0x0c->m_x;
			intersection1.m_u = (p_unk0x08->m_u - p_unk0x0c->m_u) * amount + p_unk0x0c->m_u;
			intersection1.m_v = (p_unk0x08->m_v - p_unk0x0c->m_v) * amount + p_unk0x0c->m_v;
		}
		else {
			amount = (p_unk0x08->m_y - m_unk0x134) / (p_unk0x08->m_y - p_unk0x04->m_y);
			intersection1.m_x = (p_unk0x04->m_x - p_unk0x08->m_x) * amount + p_unk0x08->m_x;
			intersection1.m_u = (p_unk0x04->m_u - p_unk0x08->m_u) * amount + p_unk0x08->m_u;
			intersection1.m_v = (p_unk0x04->m_v - p_unk0x08->m_v) * amount + p_unk0x08->m_v;

			m_unk0x000->DrawTriangle(p_unk0x0c, &intersection1, p_unk0x08, m_unk0x118, 0);
		}

		m_unk0x000->DrawTriangle(&intersection0, &intersection1, p_unk0x0c, m_unk0x118, 0);
		return;
	}

	m_unk0x000->DrawTriangle(p_unk0x04, p_unk0x08, p_unk0x0c, m_unk0x118, 0);
}

// FUNCTION: LEGORACERS 0x004246d0 FOLDED
LegoU32 CobaltTrail0x140::FUN_004246d0(LegoChar* p_buffer, LegoU32 p_time)
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

// STUB: LEGORACERS 0x004247d0
void CobaltTrail0x140::FUN_004247d0(LegoS32 p_x, LegoS32 p_y, LegoFloat p_directionX, LegoFloat p_directionY)
{
	const LegoFloat tipLength = 9.5f;
	const LegoFloat baseLength = 6.5f;
	const LegoFloat baseHalfWidth = 5.5f;
	const LegoFloat tailLength = 5.0f;
	const LegoFloat tailHalfWidth = 4.0f;
	const LegoFloat tailEndLength = 8.0f;

	GolRenderDevice::TexturedVertex vertices[6];

	vertices[0].m_x = p_directionX * tipLength;
	vertices[0].m_y = p_directionY * tipLength;
	vertices[1].m_x = p_directionY * baseHalfWidth - p_directionX * baseLength;
	vertices[1].m_y = -p_directionX * baseHalfWidth - p_directionY * baseLength;
	vertices[2].m_x = -p_directionY * baseHalfWidth - p_directionX * baseLength;
	vertices[2].m_y = p_directionX * baseHalfWidth - p_directionY * baseLength;

	vertices[3].m_x = p_directionX * tailEndLength;
	vertices[3].m_y = p_directionY * tailEndLength;
	vertices[4].m_x = p_directionY * tailHalfWidth - p_directionX * tailLength;
	vertices[4].m_y = -p_directionX * tailHalfWidth - p_directionY * tailLength;
	vertices[5].m_x = -p_directionY * tailHalfWidth - p_directionX * tailLength;
	vertices[5].m_y = p_directionX * tailHalfWidth - p_directionY * tailLength;

	LegoFloat originX = static_cast<LegoFloat>(p_x);
	LegoFloat originY = static_cast<LegoFloat>(p_y);
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0;
		vertices[i].m_color.m_grn = 0;
		vertices[i].m_color.m_blu = 0;
		vertices[i].m_color.m_alp = 0xff;
		vertices[i].m_z = 0.0f;
		vertices[i].m_x = vertices[i].m_x * m_unk0x104 + originX;
		vertices[i].m_y = vertices[i].m_y * m_unk0x114 + originY;
	}

	DuskwindBananaRelic0x24* material = m_unk0x118;
	m_unk0x118 = NULL;
	FUN_00423fc0(&vertices[1], &vertices[0], &vertices[2]);
	FUN_00423fc0(&vertices[4], &vertices[3], &vertices[5]);
	m_unk0x118 = material;
}

// STUB: LEGORACERS 0x004249b0
void CobaltTrail0x140::FUN_004249b0()
{
	const LegoFloat maxTextureCoordinate = 0.9990000129f;

	LegoFloat markerWidthScale = m_unk0x104;
	markerWidthScale *= g_unk0x004b02b4;
	LegoS32 markerWidth = static_cast<LegoS32>(markerWidthScale);

	LegoFloat markerHeightScale = m_unk0x114;
	markerHeightScale *= g_unk0x004b02b4;
	LegoS32 markerHeight = static_cast<LegoS32>(markerHeightScale);

	m_unk0x12c = static_cast<LegoFloat>(m_unk0x094.m_top);
	m_unk0x130 = static_cast<LegoFloat>(m_unk0x094.m_left);
	m_unk0x134 = static_cast<LegoFloat>(m_unk0x094.m_bottom);
	m_unk0x138 = static_cast<LegoFloat>(m_unk0x094.m_right);

	GolRenderDevice::TexturedVertex vertices[4];
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0xff;
		vertices[i].m_color.m_grn = 0xff;
		vertices[i].m_color.m_blu = 0xff;
		vertices[i].m_color.m_alp = 0xc8;
		vertices[i].m_z = 0.0f;
	}

	LegoS32 verticalOffset = static_cast<LegoS32>(static_cast<LegoFloat>(m_unk0x100) * g_unk0x004b02b0 * m_unk0x114);
	LegoS32 horizontalOffset = static_cast<LegoS32>(static_cast<LegoFloat>(m_unk0x100) * g_unk0x004b02b0 * m_unk0x104);
	LegoS32 mapOriginY = m_unk0x094.m_bottom - verticalOffset;
	LegoS32 mapOriginX = m_unk0x094.m_right - horizontalOffset;

	LegoFloat referenceY;
	if (m_unk0x03b) {
		referenceY = -m_unk0x11c;
	}
	else {
		referenceY = m_unk0x124;
	}

	LegoFloat rangeX = m_unk0x128 - m_unk0x120;
	LegoFloat rangeY = m_unk0x11c - m_unk0x124;
	LegoFloat scale = rangeX > rangeY ? g_unk0x004b02ac / rangeX : g_unk0x004b02ac / rangeY;
	scale *= m_unk0x0f4;
	LegoFloat scaleX = m_unk0x104 * scale;
	LegoFloat scaleY = m_unk0x114 * scale;

	if (m_unk0x118) {
		if (m_unk0x03b) {
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

		vertices[0].m_x = static_cast<LegoFloat>(mapOriginX) + (m_unk0x120 - m_unk0x128) * scaleX;
		vertices[0].m_y = static_cast<LegoFloat>(mapOriginY) + (m_unk0x124 - m_unk0x11c) * scaleY;
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

		FUN_00423fc0(&vertices[0], &vertices[1], &vertices[2]);
		FUN_00423fc0(&vertices[3], &vertices[0], &vertices[2]);
	}

	UtopianPan0xa4* markerResource = m_unk0x008->VTable0x20(10);
	LegoS32 halfMarkerWidth = markerWidth >> 1;
	LegoS32 halfMarkerHeight = markerHeight >> 1;
	LegoS32 markerOriginX = mapOriginX - halfMarkerWidth;
	LegoS32 markerOriginY = mapOriginY - halfMarkerHeight;

	for (LegoS32 racerIndex = static_cast<LegoS32>(m_unk0x028->GetRacerCount()) - 1; racerIndex >= 0; racerIndex--) {
		RaceState::Racer* racer = &m_unk0x028->GetRacers()[racerIndex];
		if (racer != m_unk0x02c) {
			GolVec3 position;
			racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

			Rect destRect;
			destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
			destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_unk0x128) * scaleX);
			destRect.m_bottom = destRect.m_top + markerHeight;
			destRect.m_right = destRect.m_left + markerWidth;

			Rect sourceRect;
			if (racer->m_unk0xd08 == 2 && racerIndex == 1) {
				sourceRect.m_left = 0x10;
			}
			else {
				sourceRect.m_left = 0;
			}
			if (m_unk0x038 == 2 || m_unk0x038 == 3) {
				sourceRect.m_top = 0x10;
			}
			else {
				sourceRect.m_top = 0;
			}
			sourceRect.m_right = sourceRect.m_left + 0x10;
			sourceRect.m_bottom = sourceRect.m_top + 0x10;

			m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
		}
	}

	if (m_unk0x030 && m_unk0x030->HasRecordGhostMarker()) {
		GolVec3 position;
		m_unk0x030->GetRecordGhostMarkerEntity()->VTable0x04(&position);

		Rect destRect;
		destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
		destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_unk0x128) * scaleX);
		destRect.m_bottom = destRect.m_top + markerHeight;
		destRect.m_right = destRect.m_left + markerWidth;

		Rect sourceRect;
		sourceRect.m_left = 0x10;
		if (m_unk0x038 == 2 || m_unk0x038 == 3) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
	}

	if (m_unk0x030 && m_unk0x030->HasBestGhostMarker()) {
		GolVec3 position;
		m_unk0x030->GetBestGhostMarkerEntity()->VTable0x04(&position);

		Rect destRect;
		destRect.m_top = markerOriginY + static_cast<LegoS32>((referenceY - position.m_y) * scaleY);
		destRect.m_left = markerOriginX + static_cast<LegoS32>((position.m_x - m_unk0x128) * scaleX);
		destRect.m_bottom = destRect.m_top + markerHeight;
		destRect.m_right = destRect.m_left + markerWidth;

		Rect sourceRect;
		sourceRect.m_left = 0;
		if (m_unk0x038 == 2 || m_unk0x038 == 3) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
	}

	GolVec3 currentPosition;
	m_unk0x02c->m_unk0x018.m_unk0x044->VTable0x04(&currentPosition);

	GolVec3 direction;
	m_unk0x02c->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);
	LegoFloat directionScale =
		1.0f / static_cast<LegoFloat>(sqrt(direction.m_y * direction.m_y + direction.m_x * direction.m_x));
	LegoFloat directionX = direction.m_x * directionScale;
	LegoFloat directionY = -(direction.m_y * directionScale);

	LegoS32 currentX = mapOriginX + static_cast<LegoS32>((currentPosition.m_x - m_unk0x128) * scaleX);
	LegoS32 currentY = mapOriginY + static_cast<LegoS32>((referenceY - currentPosition.m_y) * scaleY);
	FUN_004247d0(currentX, currentY, directionX, directionY);
}

// STUB: LEGORACERS 0x00424fb0
void CobaltTrail0x140::FUN_00424fb0()
{
	const LegoFloat maxTextureCoordinate = 0.9990000129f;

	LegoFloat markerWidthScale = m_unk0x104;
	markerWidthScale *= g_unk0x004b02b4;
	LegoS32 markerWidth = static_cast<LegoS32>(markerWidthScale);

	LegoFloat markerHeightScale = m_unk0x114;
	markerHeightScale *= g_unk0x004b02b4;
	LegoS32 markerHeight = static_cast<LegoS32>(markerHeightScale);

	GolRenderDevice::TexturedVertex vertices[8];
	for (LegoS32 i = 0; i < sizeOfArray(vertices); i++) {
		vertices[i].m_color.m_red = 0xff;
		vertices[i].m_color.m_grn = 0xff;
		vertices[i].m_color.m_blu = 0xff;
		vertices[i].m_color.m_alp = 0xc8;
		vertices[i].m_z = 0.0f;
	}

	LegoFloat directionLengthScale = m_unk0x0f4 * 0.12f * m_unk0x114;
	LegoS32 verticalInset = static_cast<LegoS32>(static_cast<LegoFloat>(m_unk0x100) * g_unk0x004b02b0 * m_unk0x114);
	LegoS32 horizontalInset = static_cast<LegoS32>(static_cast<LegoFloat>(m_unk0x100) * g_unk0x004b02b0 * m_unk0x104);
	LegoS32 mapBottom = m_unk0x094.m_bottom - verticalInset;
	LegoS32 mapRight = m_unk0x094.m_right - horizontalInset;

	LegoFloat mapSize = m_unk0x0f4 * g_unk0x004b02ac;
	LegoS32 mapHeight = static_cast<LegoS32>(m_unk0x114 * mapSize);
	LegoS32 mapWidth = static_cast<LegoS32>(m_unk0x104 * mapSize);
	LegoS32 mapTop = mapBottom - mapHeight;
	LegoS32 mapLeft = mapRight - mapWidth;
	LegoS32 mapCenterX = (mapLeft + mapRight) >> 1;
	LegoS32 mapCenterY = (mapTop + mapBottom) >> 1;

	m_unk0x12c = static_cast<LegoFloat>(mapTop);
	m_unk0x130 = static_cast<LegoFloat>(mapLeft);
	m_unk0x134 = static_cast<LegoFloat>(mapBottom);
	m_unk0x138 = static_cast<LegoFloat>(mapRight);

	UtopianPan0xa4* markerResource = m_unk0x008->VTable0x20(10);

	GolVec3 currentPosition;
	m_unk0x02c->m_unk0x018.m_unk0x044->VTable0x04(&currentPosition);

	GolVec3 cameraDirection;
	m_unk0x02c->m_unk0xdb4->FUN_00428500(&cameraDirection);

	LegoFloat directionScale =
		directionLengthScale / static_cast<LegoFloat>(sqrt(
								   cameraDirection.m_y * cameraDirection.m_y + cameraDirection.m_x * cameraDirection.m_x
							   ));
	LegoFloat directionX = cameraDirection.m_x * directionScale;
	LegoFloat directionY = cameraDirection.m_y * directionScale;

	if (m_unk0x118) {
		LegoFloat deltaY0;
		LegoFloat deltaY1;
		if (m_unk0x03b) {
			deltaY0 = -m_unk0x124 - currentPosition.m_y;
			deltaY1 = -m_unk0x11c - currentPosition.m_y;
			vertices[0].m_v = 0.0f;
			vertices[1].m_v = 0.0f;
			vertices[2].m_v = maxTextureCoordinate;
			vertices[3].m_v = maxTextureCoordinate;
		}
		else {
			deltaY0 = m_unk0x11c - currentPosition.m_y;
			deltaY1 = m_unk0x124 - currentPosition.m_y;
			vertices[0].m_v = maxTextureCoordinate;
			vertices[1].m_v = maxTextureCoordinate;
			vertices[2].m_v = 0.0f;
			vertices[3].m_v = 0.0f;
		}

		LegoFloat deltaX0 = m_unk0x120 - currentPosition.m_x;
		LegoFloat deltaX1 = m_unk0x128 - currentPosition.m_x;
		LegoFloat scaledDirectionX = directionX * m_unk0x108;
		LegoFloat scaledDirectionY = directionY * m_unk0x108;

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

		FUN_00423fc0(&vertices[0], &vertices[1], &vertices[3]);
		FUN_00423fc0(&vertices[3], &vertices[1], &vertices[2]);
	}

	LegoS32 markerOriginX = mapCenterX - (markerWidth >> 1);
	LegoS32 markerOriginY = mapCenterY - (markerHeight >> 1);
	GolVec3 position;
	Rect destRect;
	Rect sourceRect;

	for (LegoS32 racerIndex = static_cast<LegoS32>(m_unk0x028->GetRacerCount()) - 1; racerIndex >= 0; racerIndex--) {
		RaceState::Racer* racer = &m_unk0x028->GetRacers()[racerIndex];
		if (racer != m_unk0x02c) {
			racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

			LegoFloat deltaX = position.m_x - currentPosition.m_x;
			LegoFloat deltaY = position.m_y - currentPosition.m_y;

			destRect.m_left =
				markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_unk0x108);
			destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
			destRect.m_right = destRect.m_left + markerWidth;
			destRect.m_bottom = destRect.m_top + markerHeight;

			if (racer->m_unk0xd08 == 2 && racerIndex == 1) {
				sourceRect.m_left = 0x10;
			}
			else {
				sourceRect.m_left = 0;
			}
			if (m_unk0x038 == 2 || m_unk0x038 == 3) {
				sourceRect.m_top = 0x10;
			}
			else {
				sourceRect.m_top = 0;
			}
			sourceRect.m_right = sourceRect.m_left + 0x10;
			sourceRect.m_bottom = sourceRect.m_top + 0x10;

			m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
		}
	}

	if (m_unk0x030 && m_unk0x030->HasRecordGhostMarker()) {
		m_unk0x030->GetRecordGhostMarkerEntity()->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - currentPosition.m_x;
		LegoFloat deltaY = position.m_y - currentPosition.m_y;

		destRect.m_left =
			markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_unk0x108);
		destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
		destRect.m_right = destRect.m_left + markerWidth;
		destRect.m_bottom = destRect.m_top + markerHeight;

		sourceRect.m_left = 0x10;
		if (m_unk0x038 == 2 || m_unk0x038 == 3) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
	}

	if (m_unk0x030 && m_unk0x030->HasBestGhostMarker()) {
		m_unk0x030->GetBestGhostMarkerEntity()->VTable0x04(&position);

		LegoFloat deltaX = position.m_x - currentPosition.m_x;
		LegoFloat deltaY = position.m_y - currentPosition.m_y;

		destRect.m_left =
			markerOriginX + static_cast<LegoS32>((deltaX * directionY - deltaY * directionX) * m_unk0x108);
		destRect.m_top = markerOriginY - static_cast<LegoS32>(deltaY * directionY + deltaX * directionX);
		destRect.m_right = destRect.m_left + markerWidth;
		destRect.m_bottom = destRect.m_top + markerHeight;

		sourceRect.m_left = 0;
		if (m_unk0x038 == 2 || m_unk0x038 == 3) {
			sourceRect.m_top = 0x10;
		}
		else {
			sourceRect.m_top = 0;
		}
		sourceRect.m_right = sourceRect.m_left + 0x10;
		sourceRect.m_bottom = sourceRect.m_top + 0x10;

		m_unk0x000->VTable0x7c(markerResource, 0, &destRect, &sourceRect, &m_unk0x094);
	}

	FUN_004247d0(mapCenterX, mapCenterY, 0.0f, -1.0f);

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

	m_unk0x000->DrawTriangle(&vertices[0], &vertices[1], &vertices[4], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[4], &vertices[1], &vertices[5], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[0], &vertices[4], &vertices[3], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[3], &vertices[4], &vertices[7], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[3], &vertices[7], &vertices[2], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[2], &vertices[7], &vertices[6], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[5], &vertices[1], &vertices[6], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[6], &vertices[1], &vertices[2], NULL, 0);
}

// FUNCTION: LEGORACERS 0x004258e0
void CobaltTrail0x140::FUN_004258e0()
{
	UtopianPan0xa4* resource0 = m_unk0x008->VTable0x20(0);
	LegoS32 resource0Width = resource0->GetWidth();
	LegoS32 width0 = static_cast<LegoS32>(
		static_cast<double>(resource0Width) * static_cast<double>(m_unk0x0f4) * static_cast<double>(m_unk0x10c)
	);
	LegoS32 resource0Height = resource0->GetHeight();
	double scaledHeight0 = static_cast<double>(resource0Height) * static_cast<double>(m_unk0x0f4);
	LegoS32 height0 = static_cast<LegoS32>(scaledHeight0 * static_cast<double>(m_unk0x114));
	m_unk0x000
		->VTable0x70(resource0, 0, m_unk0x094.m_right - width0 - 2, m_unk0x094.m_bottom - height0 - 2, width0, height0);

	LegoFloat centerX = static_cast<LegoFloat>(m_unk0x094.m_right - ((52 * width0) >> 7) - 2);
	LegoFloat centerY = static_cast<LegoFloat>(m_unk0x094.m_bottom - ((52 * height0) >> 7) - 2);
	LegoFloat angle = m_unk0x078 * 18.0f;
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
	GolMath::FUN_00449170(angle0, &vertices[0].m_y, &vertices[0].m_x);

	LegoFloat angle1 = angle0 + 2.0943952f;
	GolMath::FUN_00449170(angle1, &vertices[2].m_y, &vertices[2].m_x);

	LegoFloat angle2 = angle1 + 2.0943952f;
	GolMath::FUN_00449170(angle2, &vertices[1].m_y, &vertices[1].m_x);

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
		vertices[i].m_x = (vertices[i].m_x * m_unk0x0f4) * m_unk0x104 + centerX;
		vertices[i].m_y = (vertices[i].m_y * m_unk0x0f4) * m_unk0x114 + centerY;
	}
	vertices[4].m_x = vertices[0].m_x;
	vertices[4].m_y = vertices[0].m_y;

	m_unk0x000->DrawTriangle(&vertices[1], &vertices[0], &vertices[3], NULL, 0);
	m_unk0x000->DrawTriangle(&vertices[2], &vertices[3], &vertices[4], NULL, 0);

	UtopianPan0xa4* resource1 = m_unk0x008->VTable0x20(1);
	LegoS32 resource1Width = resource1->GetWidth();
	LegoS32 width1 = static_cast<LegoS32>(
		static_cast<double>(resource1Width) * static_cast<double>(m_unk0x0f4) * static_cast<double>(m_unk0x10c)
	);
	LegoS32 resource1Height = resource1->GetHeight();
	double scaledHeight1 = static_cast<double>(resource1Height) * static_cast<double>(m_unk0x0f4);
	LegoS32 height1 = static_cast<LegoS32>(scaledHeight1 * static_cast<double>(m_unk0x114));
	m_unk0x000->VTable0x70(
		resource1,
		0,
		static_cast<LegoS32>(centerX) - (width1 >> 1),
		static_cast<LegoS32>(centerY) - (height1 >> 1),
		width1,
		height1
	);
}

// FUNCTION: LEGORACERS 0x00425bf0
LegoS32 CobaltTrail0x140::FUN_00425bf0(const LegoChar* p_text, LegoS32 p_x, LegoS32 p_y)
{
	FUN_00425c70(p_text, m_unk0x010);

	LegoS32 drawX;
	if (m_unk0x010->SelectionLength() == 7) {
		drawX = m_unk0x0e8 - m_unk0x0e4;
		drawX += p_x;
	}
	else {
		drawX = p_x;
	}

	LegoFloat scaleY = m_unk0x114 * m_unk0x0ec;
	LegoFloat scaleX = m_unk0x10c * m_unk0x0ec;
	m_unk0x000->VTable0x64(m_unk0x010, m_unk0x020, drawX, p_y, scaleX, scaleY, NULL, 0);

	return drawX;
}

// FUNCTION: LEGORACERS 0x00425c70
undefined4 CobaltTrail0x140::FUN_00425c70(const LegoChar* p_text, GolString* p_string)
{
	LegoU32 length = ::strlen(p_text);
	LegoU32 i = 0;

	if (length) {
		undefined2* dest = g_unk0x004c4814;
		do {
			*dest++ = p_text[i++];
		} while (i < length);
	}

	g_unk0x004c4814[length] = 0;
	return p_string->GolStrcpy(g_unk0x004c4814);
}

// FUNCTION: LEGORACERS 0x00425cc0
void CobaltTrail0x140::Reset()
{
	m_unk0x02c = NULL;
	m_unk0x13c = 1;
	m_unk0x000 = NULL;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x010 = NULL;
	m_unk0x020 = NULL;
	m_unk0x024 = NULL;
	m_unk0x028 = 0;
	m_unk0x034 = 0;
	m_unk0x038 = 0;
	m_unk0x039 = 0;
	m_unk0x03a = 0;
	m_unk0x03b = 0;
	m_unk0x03c = 0;
	m_unk0x070 = 0;
	m_unk0x074 = 0;
	m_unk0x078 = 0;
	m_unk0x07c = 0;
	m_unk0x080 = 0;
	m_unk0x084 = 0;
	m_unk0x088 = 0;
	m_unk0x08c = 0;
	m_unk0x090 = 0;
	m_unk0x0e4 = 0;
	m_unk0x0e8 = 0;
	m_unk0x0fc = 0;
	m_unk0x100 = 0;
	m_unk0x104 = 0;
	m_unk0x118 = 0;
	m_unk0x128 = 0;
	m_unk0x124 = 0;
	m_unk0x120 = 0;
	m_unk0x11c = 0;
	m_unk0x138 = 0;
	m_unk0x134 = 0;
	m_unk0x130 = 0;
	m_unk0x12c = 0;
}

// STUB: LEGORACERS 0x00425d80
LegoS32 CobaltTrail0x140::FUN_00425d80(
	GolD3DRenderDevice* p_renderer,
	GolNameTable* p_nameTable,
	GolString* p_string,
	ResourceTable* p_resourceTable,
	RaceState::Racer::Field0x00c* p_unk0x14,
	TimeRaceManager* p_unk0x18,
	GolStringTable* p_stringTable,
	RaceState::Racer::Field0x004* p_unk0x20,
	LegoBool p_unk0x24,
	LegoBool p_unk0x28
)
{
	LegoChar name[8];

	::strncpy(name, g_unk0x004be8a8, sizeof(name));
	GolFontBase* font = NULL;
	if (p_nameTable->GetNameEntries()) {
		font = static_cast<GolFontBase*>(p_nameTable->GetName(name));
	}
	m_unk0x020 = font;

	::strncpy(name, g_unk0x004be8ac, sizeof(name));
	font = NULL;
	if (p_nameTable->GetNameEntries()) {
		font = static_cast<GolFontBase*>(p_nameTable->GetName(name));
	}
	m_unk0x024 = font;

	m_unk0x02c = NULL;
	m_unk0x034 = 0;
	m_unk0x078 = 0;
	m_unk0x03a = 0;
	m_unk0x03c = 1;
	m_unk0x118 = 0;
	FUN_004262d0(static_cast<LegoU32>(-1));
	m_unk0x008 = p_resourceTable;
	m_unk0x010 = p_string;
	m_unk0x00c = p_stringTable;
	m_unk0x028 = p_unk0x14;
	m_unk0x000 = p_renderer;
	m_unk0x030 = p_unk0x18;
	m_unk0x004 = p_unk0x20;

	const SlatePeak0x58* renderTargetHeight = p_renderer->GetRenderTargetInfo();
	const SlatePeak0x58* renderTargetWidth = m_unk0x000->GetRenderTargetInfo();
	FUN_004261f0(renderTargetWidth->GetWidth(), renderTargetHeight->GetHeight());

	m_unk0x03a = p_unk0x24;
	LegoS32 mode = m_unk0x038;
	m_unk0x039 = p_unk0x28;
	m_unk0x034 = 0;
	LegoS32 result = FUN_00425e90(mode);
	m_unk0x13c = 1;

	return result;
}

// STUB: LEGORACERS 0x00425e90
LegoS32 CobaltTrail0x140::FUN_00425e90(LegoS32 p_mode)
{
	LegoS32 v25;
	LegoS32 v26;
	LegoS32 v27;

	m_unk0x038 = static_cast<LegoU8>(p_mode);
	m_unk0x094.m_left = 0;
	LegoS32 width = m_unk0x0fc;
	m_unk0x0f4 = 0.8f;
	m_unk0x0f8 = 0.8f;
	m_unk0x094.m_right = width;
	m_unk0x0ec = 0.9f;
	m_unk0x0f0 = 1.0f;

	switch (m_unk0x038) {
	case 0:
		return m_unk0x038;
	case 1:
		m_unk0x094.m_top = 0;
		m_unk0x094.m_bottom = m_unk0x100;
		m_unk0x0f8 = 1.0f;
		m_unk0x0f4 = 1.0f;
		m_unk0x0f0 = 1.0f;
		m_unk0x0ec = 1.0f;
		break;
	case 2:
		m_unk0x094.m_top = 0;
		m_unk0x094.m_bottom = m_unk0x100 >> 1;
		break;
	case 3:
		m_unk0x094.m_bottom = m_unk0x100;
		m_unk0x094.m_top = m_unk0x100 >> 1;
		break;
	}

	LegoU32 widthRange = width - m_unk0x094.m_left;

	FUN_004246d0(m_unk0x03d.m_text, 0);
	FUN_00425c70(m_unk0x03d.m_text, m_unk0x010);
	m_unk0x020->MeasureString(m_unk0x010, &p_mode, &v25);
	p_mode = static_cast<LegoS32>(static_cast<double>(p_mode) * m_unk0x0ec);
	m_unk0x0e4 = static_cast<LegoS32>(static_cast<double>(p_mode) * m_unk0x10c);

	FUN_004246d0(m_unk0x03d.m_text, 0x36ee08);
	FUN_00425c70(m_unk0x03d.m_text, m_unk0x010);
	m_unk0x020->MeasureString(m_unk0x010, &p_mode, &v25);
	p_mode = static_cast<LegoS32>(static_cast<double>(p_mode) * m_unk0x0ec);
	v25 = static_cast<LegoS32>(static_cast<double>(v25) * m_unk0x0ec);
	m_unk0x0e8 = static_cast<LegoS32>(static_cast<double>(p_mode) * m_unk0x10c);

	v26 = m_unk0x094.m_right - ((11 * m_unk0x0e8) >> 3);
	m_unk0x0ac = v26;
	LegoS32 topTextY = m_unk0x094.m_top - static_cast<LegoS32>(static_cast<double>(m_unk0x114) * g_unk0x004b02d4);
	m_unk0x0cc = topTextY;
	m_unk0x0a8 = m_unk0x094.m_left + (widthRange / 10);
	m_unk0x0c8 = topTextY;
	m_unk0x0b0 = v26;

	v27 = (static_cast<LegoU32>(7 * v25)) >> 3;
	m_unk0x0d0 = topTextY + static_cast<LegoS32>(static_cast<double>(v27) * m_unk0x114);
	m_unk0x0bc = v26;

	v27 = (static_cast<LegoU32>(14 * v25)) >> 3;
	m_unk0x0dc = topTextY + static_cast<LegoS32>(static_cast<double>(v27) * m_unk0x114);
	m_unk0x0b4 = v26;

	v27 = (static_cast<LegoU32>(21 * v25)) >> 3;
	LegoS32 bottomTextY = static_cast<LegoS32>(static_cast<double>(v27) * m_unk0x114) + topTextY;
	m_unk0x0a4 = (m_unk0x094.m_right + m_unk0x094.m_left) >> 1;
	m_unk0x0d4 = bottomTextY;
	m_unk0x0c4 = bottomTextY;

	m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x24);
	m_unk0x020->MeasureString(&m_unk0x014, &p_mode, &v25);
	m_unk0x0b8 = m_unk0x0a4 - (static_cast<LegoS32>(static_cast<double>(p_mode) * m_unk0x10c) >> 1);
	m_unk0x0d8 = m_unk0x094.m_top + ((m_unk0x094.m_bottom - m_unk0x094.m_top) / 5);

	UtopianPan0xa4* resource = m_unk0x008->VTable0x20(11);
	m_unk0x0c0 = m_unk0x094.m_left + (widthRange >> 5);

	p_mode = static_cast<LegoS32>(
		(static_cast<double>(static_cast<LegoS32>(resource->GetHeight())) * m_unk0x0f0 + g_unk0x004afde0) * m_unk0x114
	);
	m_unk0x0e0 = m_unk0x094.m_bottom - p_mode;

	return p_mode;
}

// FUNCTION: LEGORACERS 0x004261f0
LegoS32 CobaltTrail0x140::FUN_004261f0(LegoS32 p_unk0x04, LegoS32 p_unk0x08)
{
	m_unk0x0fc = p_unk0x04;
	m_unk0x100 = p_unk0x08;

	double scaledWidth = 3 * p_unk0x04;
	LegoFloat ratio = static_cast<LegoFloat>(scaledWidth / static_cast<double>(4 * p_unk0x08));
	m_unk0x110 = ratio;

	LegoS32 scaledHeight = p_unk0x08 << 2;
	LegoFloat scale = static_cast<LegoFloat>(p_unk0x08) * g_unk0x004b02d8;
	m_unk0x114 = scale;
	m_unk0x10c = scale * ratio;

	LegoFloat aspect = static_cast<LegoFloat>(scaledWidth / static_cast<double>(scaledHeight));
	m_unk0x108 = aspect;
	LegoS32 mode = m_unk0x038;
	m_unk0x104 = aspect * scale;

	return FUN_00425e90(mode);
}

// FUNCTION: LEGORACERS 0x00426280
void CobaltTrail0x140::FUN_00426280(
	DuskwindBananaRelic0x24* p_unk0x04,
	LegoFloat p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14,
	LegoBool p_unk0x18
)
{
	m_unk0x118 = p_unk0x04;
	m_unk0x11c = p_unk0x0c;
	m_unk0x120 = p_unk0x08;
	m_unk0x124 = p_unk0x14;
	m_unk0x128 = p_unk0x10;
	m_unk0x03b = p_unk0x18;
}

// FUNCTION: LEGORACERS 0x004262c0
RaceState::Racer* CobaltTrail0x140::FUN_004262c0(RaceState::Racer* p_unk0x04)
{
	m_unk0x02c = p_unk0x04;
	p_unk0x04->m_unk0xe30 = this;

	return p_unk0x04;
}

// FUNCTION: LEGORACERS 0x004262d0
void CobaltTrail0x140::FUN_004262d0(LegoU32 p_time)
{
	m_unk0x07c = -1;
	m_unk0x08c = -1;
	m_unk0x080 = p_time;
	m_unk0x090 = 8;
	m_unk0x074 = 0;
	m_unk0x070 = 0;
	m_unk0x088 = 0;
	m_unk0x061[0] = 0;

	FUN_004246d0(m_unk0x03d.m_text, 0);
	m_unk0x046 = m_unk0x03d;
	m_unk0x04f = m_unk0x03d;
	m_unk0x058 = m_unk0x03d;
}

// FUNCTION: LEGORACERS 0x00426360
void CobaltTrail0x140::FUN_00426360()
{
	m_unk0x070 = 1;
}

// FUNCTION: LEGORACERS 0x00426370
void CobaltTrail0x140::FUN_00426370()
{
	LegoS32 value = m_unk0x02c->m_lapTimes[5];

	m_unk0x070 = -1;
	m_unk0x08c = value - 1;
}

// FUNCTION: LEGORACERS 0x00426390
void CobaltTrail0x140::FUN_00426390(LegoU32 p_elapsedMs)
{
	m_unk0x034 += p_elapsedMs;
}

// STUB: LEGORACERS 0x004263a0
void CobaltTrail0x140::FUN_004263a0()
{
	LegoU32 elapsedMs = m_unk0x034;
	m_unk0x034 = 0;

	if (m_unk0x02c == NULL || !m_unk0x038) {
		return;
	}

	if (m_unk0x070 > 0) {
		LegoS32 previousState = m_unk0x070;
		m_unk0x070 += elapsedMs;
		LegoS32 countdownState = m_unk0x070 / 1000;
		LegoFloat pulseScale = static_cast<LegoFloat>((200 * (5 * countdownState + 5) - m_unk0x070) * 1.8 * 0.001);

		if (countdownState >= 5) {
			m_unk0x070 = 0;
		}
		else if (countdownState >= 3) {
			if (countdownState < 4) {
				pulseScale = 1.8f;
			}

			m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x29);

			LegoS32 textWidth;
			LegoS32 textHeight;
			m_unk0x024->MeasureString(&m_unk0x014, &textWidth, &textHeight);

			LegoFloat scale = m_unk0x0f8 * pulseScale;
			LegoFloat scaleX = m_unk0x10c * scale;
			LegoFloat scaleY = m_unk0x114 * scale;
			textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
			textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

			m_unk0x024->SetColor(0xff00ffff);
			if (m_unk0x13c) {
				m_unk0x000->VTable0x64(
					&m_unk0x014,
					m_unk0x024,
					m_unk0x0a4 - (textWidth >> 1),
					m_unk0x0c4 - (static_cast<LegoU32>(textHeight) >> 2),
					scaleX,
					scaleY,
					NULL,
					0
				);
			}
			m_unk0x024->SetColor(0xffffffff);

			if (m_unk0x004 && countdownState == 3 && previousState / 1000 != 3) {
				m_unk0x004->FUN_00443b50(0x0f);
			}
		}
		else {
			FUN_00425c70(g_unk0x004b0270[2 - countdownState], m_unk0x010);

			LegoS32 textWidth;
			LegoS32 textHeight;
			m_unk0x024->MeasureString(m_unk0x010, &textWidth, &textHeight);

			LegoFloat scale = m_unk0x0f8 * pulseScale;
			LegoFloat scaleX = m_unk0x10c * scale;
			LegoFloat scaleY = m_unk0x114 * scale;
			textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
			textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

			m_unk0x024->SetColor(0xff00ffff);
			if (m_unk0x13c) {
				m_unk0x000->VTable0x64(
					m_unk0x010,
					m_unk0x024,
					m_unk0x0a4 - (textWidth >> 1),
					m_unk0x0c4 - (static_cast<LegoU32>(textHeight) >> 2),
					scaleX,
					scaleY,
					NULL,
					0
				);
			}
			m_unk0x024->SetColor(0xffffffff);

			if ((previousState == 1 || previousState / 1000 != countdownState) && m_unk0x004) {
				m_unk0x004->FUN_00443b50(0);
			}
		}
	}
	else if (m_unk0x070 < 0) {
		m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x28);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_unk0x024->MeasureString(&m_unk0x014, &textWidth, &textHeight);

		LegoFloat scaleX = m_unk0x10c * m_unk0x0f8;
		LegoFloat scaleY = m_unk0x114 * m_unk0x0f8;
		textWidth = static_cast<LegoS32>(static_cast<double>(textWidth) * scaleX);
		textHeight = static_cast<LegoS32>(static_cast<double>(textHeight) * scaleY);

		if (m_unk0x13c) {
			m_unk0x000->VTable0x64(
				&m_unk0x014,
				m_unk0x024,
				m_unk0x0a4 - (textWidth >> 1),
				m_unk0x0c4 - (static_cast<LegoU32>(textHeight) >> 2),
				scaleX,
				scaleY,
				NULL,
				0
			);
		}

		m_unk0x070 -= elapsedMs;
		if (m_unk0x070 < -60000) {
			m_unk0x070 = -60000;
		}
	}

	if (m_unk0x02c->m_unk0xd04 & 0x10) {
		return;
	}

	LegoS32 positionIndex;
	if (m_unk0x074) {
		positionIndex = m_unk0x090;
	}
	else {
		positionIndex = m_unk0x08c;
		if (positionIndex < 0) {
			positionIndex = m_unk0x02c->m_unk0xcd8 - 1;
		}
		if (positionIndex > 8) {
			positionIndex = 8;
		}
		if (positionIndex != m_unk0x090) {
			m_unk0x090 = positionIndex;
			m_unk0x074 = 1;
		}
	}

	LegoS32 lapIndex = m_unk0x02c->m_lapsCompleted;
	LegoS32 lapCount = m_unk0x02c->m_unk0xce0;
	LegoU32 totalTime = 0;
	LegoBool drawLapTime = TRUE;
	LegoU32* lapTimes = &m_unk0x02c->m_unk0xce8;

	if (lapIndex >= lapCount) {
		LegoS32 hiddenTime = -m_unk0x070;
		if (hiddenTime < 3000 && ((hiddenTime / 250) & 1)) {
			drawLapTime = FALSE;
		}
		else {
			m_unk0x084 = lapTimes[lapCount];
			FUN_004246d0(m_unk0x03d.m_text, m_unk0x084);
		}

		for (LegoS32 i = 0; i < lapIndex; i++) {
			totalTime += lapTimes[i];
		}
	}
	else {
		m_unk0x084 = lapTimes[lapIndex + 1];
		if (lapIndex && m_unk0x084 < 3000) {
			if ((m_unk0x084 / 250) & 1) {
				drawLapTime = FALSE;
			}
			else {
				m_unk0x084 = lapTimes[lapIndex];
				FUN_004246d0(m_unk0x03d.m_text, m_unk0x084);
			}
		}
		else {
			FUN_004246d0(m_unk0x03d.m_text, m_unk0x084);
		}

		for (LegoS32 i = 0; i <= lapIndex; i++) {
			totalTime += lapTimes[i];
		}
	}

	FUN_004246d0(m_unk0x058.m_text, totalTime);
	if (m_unk0x02c->m_unk0xd84) {
		FUN_004246d0(m_unk0x04f.m_text, m_unk0x02c->m_unk0xd88);
	}

	if (lapIndex != m_unk0x07c) {
		if (m_unk0x07c != -1 && m_unk0x07c < m_unk0x02c->m_unk0xce0) {
			LegoU32 completedLapTime = lapTimes[m_unk0x07c];
			if (completedLapTime <= m_unk0x088 || !m_unk0x088) {
				m_unk0x088 = completedLapTime;
				FUN_004246d0(m_unk0x046.m_text, completedLapTime);
			}
		}

		m_unk0x07c = lapIndex;
		LegoS32 displayLap = lapIndex + 1;
		if (m_unk0x080 <= 0) {
			if (displayLap > m_unk0x02c->m_unk0xce0) {
				displayLap = m_unk0x02c->m_unk0xce0;
			}
			::sprintf(m_unk0x061, "%d", displayLap);
		}
		else {
			if (displayLap > static_cast<LegoS32>(m_unk0x080)) {
				displayLap = m_unk0x080;
			}
			::sprintf(m_unk0x061, "%d/%d", displayLap, m_unk0x080);
		}
	}

	if (!m_unk0x039) {
		FUN_00425c70(m_unk0x061, m_unk0x010);

		LegoS32 textWidth;
		LegoS32 textHeight;
		m_unk0x020->MeasureString(m_unk0x010, &textWidth, &textHeight);

		LegoFloat labelScaleX = m_unk0x10c * m_unk0x0ec;
		LegoFloat labelScaleY = m_unk0x114 * m_unk0x0ec;
		LegoS32 labelOffset = static_cast<LegoS32>(
			(static_cast<double>(textWidth) * m_unk0x0ec - static_cast<double>(m_unk0x0ec) * -14.0) * m_unk0x10c
		);
		m_unk0x000->VTable0x64(
			m_unk0x010,
			m_unk0x020,
			m_unk0x0ac - labelOffset,
			m_unk0x0cc,
			labelScaleX,
			labelScaleY,
			NULL,
			0
		);

		m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x27);
		m_unk0x020->MeasureString(&m_unk0x014, &textWidth, &textHeight);
		labelOffset = static_cast<LegoS32>(
			(static_cast<double>(textWidth) * m_unk0x0ec - static_cast<double>(m_unk0x0ec) * -6.0) * m_unk0x10c
		);
		m_unk0x000->VTable0x64(
			&m_unk0x014,
			m_unk0x020,
			m_unk0x0ac - labelOffset,
			m_unk0x0cc,
			labelScaleX,
			labelScaleY,
			NULL,
			0
		);

		if (drawLapTime) {
			FUN_00425bf0(m_unk0x03d.m_text, m_unk0x0ac, m_unk0x0cc);
		}

		if (m_unk0x088) {
			m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x25);
			m_unk0x020->MeasureString(&m_unk0x014, &textWidth, &textHeight);
			labelOffset = static_cast<LegoS32>(
				(static_cast<double>(textWidth) * m_unk0x0ec - static_cast<double>(m_unk0x0ec) * -14.0) * m_unk0x10c
			);
			m_unk0x000->VTable0x64(
				&m_unk0x014,
				m_unk0x020,
				m_unk0x0b0 - labelOffset,
				m_unk0x0d0,
				labelScaleX,
				labelScaleY,
				NULL,
				0
			);
			FUN_00425bf0(m_unk0x046.m_text, m_unk0x0b0, m_unk0x0d0);
		}

		if (m_unk0x03a) {
			m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x26);
			m_unk0x020->MeasureString(&m_unk0x014, &textWidth, &textHeight);
			labelOffset = static_cast<LegoS32>(static_cast<double>(textWidth + 14) * m_unk0x10c);
			m_unk0x000->VTable0x64(
				&m_unk0x014,
				m_unk0x020,
				m_unk0x0bc - labelOffset,
				m_unk0x0dc,
				m_unk0x10c,
				m_unk0x114,
				NULL,
				0
			);
			FUN_00425bf0(m_unk0x058.m_text, m_unk0x0bc, m_unk0x0dc);
		}
		else if (positionIndex == 8) {
			m_unk0x074 = 0;
		}
		else {
			m_unk0x00c->CopyStringByIndex(&m_unk0x014, g_unk0x004b0290[positionIndex]);
			m_unk0x000->VTable0x64(
				&m_unk0x014,
				m_unk0x020,
				m_unk0x0a8 + static_cast<LegoS32>(m_unk0x10c * 5.0f),
				m_unk0x0c8,
				labelScaleX,
				labelScaleY,
				NULL,
				0
			);

			FUN_00425c70(g_unk0x004b0270[positionIndex], m_unk0x010);
			m_unk0x024->MeasureString(m_unk0x010, &textWidth, &textHeight);
			LegoS32 numberOffset = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(static_cast<double>(textWidth) * m_unk0x10c)) * m_unk0x0ec
			);

			LegoFloat positionScale = m_unk0x0ec;
			if (m_unk0x074) {
				m_unk0x074 += elapsedMs;
				if (m_unk0x074 <= 350) {
					if (m_unk0x074 <= 175) {
						positionScale = static_cast<LegoFloat>(static_cast<double>(m_unk0x074) * 0.0057142857 + 1.0);
					}
					else {
						LegoU32 timer = m_unk0x074 - 175;
						positionScale = static_cast<LegoFloat>(
							2.0 - static_cast<double>(static_cast<LegoS32>(timer)) * 0.0057142857
						);
					}
				}
				else {
					if (m_unk0x074 > 1050) {
						m_unk0x074 = 0;
					}
					positionScale = 1.0f;
				}
				positionScale *= m_unk0x0ec;
			}

			m_unk0x000->VTable0x64(
				m_unk0x010,
				m_unk0x024,
				m_unk0x0a8 - numberOffset,
				m_unk0x0c8,
				m_unk0x10c * positionScale,
				m_unk0x114 * positionScale,
				NULL,
				0
			);
		}

		if (m_unk0x02c->m_unk0xd84) {
			LegoS32 medalX = FUN_00425bf0(m_unk0x04f.m_text, m_unk0x0b4, m_unk0x0dc);
			m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x21);
			m_unk0x020->MeasureString(&m_unk0x014, &textWidth, &textHeight);
			if (m_unk0x13c) {
				m_unk0x000->VTable0x64(
					&m_unk0x014,
					m_unk0x020,
					medalX - static_cast<LegoS32>(static_cast<double>(textWidth + 4) * m_unk0x10c),
					m_unk0x0dc,
					m_unk0x10c,
					m_unk0x114,
					NULL,
					0
				);
			}
		}

		if (m_unk0x02c->m_unk0xd04 & 0x4000) {
			m_unk0x00c->CopyStringByIndex(&m_unk0x014, 0x24);
			if (m_unk0x13c) {
				m_unk0x000
					->VTable0x64(&m_unk0x014, m_unk0x020, m_unk0x0b8, m_unk0x0d8, m_unk0x10c, m_unk0x114, NULL, 0);
			}
		}
	}

	LegoS32 itemLevel = m_unk0x02c->m_unk0xd58;
	LegoS32 itemType = m_unk0x02c->m_unk0xccc - 1;
	UtopianPan0xa4* itemResource = NULL;
	LegoU32 itemColor = 0xffffffff;
	switch (itemType) {
	case 0:
		itemColor = 0xff00ff;
		itemResource = m_unk0x008->VTable0x20(itemLevel + 2);
		break;
	case 1:
		itemColor = 0xffff5050;
		itemResource = m_unk0x008->VTable0x20(itemLevel + 16);
		break;
	case 2:
		itemColor = 0xff00ff00;
		itemResource = m_unk0x008->VTable0x20(itemLevel + 20);
		break;
	case 3:
		itemColor = 0xff0000ff;
		itemResource = m_unk0x008->VTable0x20(itemLevel + 6);
		break;
	}

	if (itemResource || itemLevel) {
		UtopianPan0xa4* background = m_unk0x008->VTable0x20(11);
		LegoS32 width = static_cast<LegoS32>(
			static_cast<double>(static_cast<LegoS32>(background->GetWidth())) * m_unk0x0f0 * m_unk0x10c
		);
		LegoS32 height = static_cast<LegoS32>(
			static_cast<double>(static_cast<LegoS32>(background->GetHeight())) * m_unk0x0f0 * m_unk0x114
		);
		m_unk0x000->VTable0x70(background, 0, m_unk0x0c0, m_unk0x0e0, width, height);

		UtopianPan0xa4* colorResource = m_unk0x008->VTable0x20(12);
		colorResource->m_unk0x4a.m_u32 = itemColor;
		m_unk0x000->VTable0x70(colorResource, 0, m_unk0x0c0, m_unk0x0e0, width, height);

		if (itemResource) {
			LegoS32 itemWidth = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(itemResource->GetWidth())) * m_unk0x0f0 * m_unk0x10c
			);
			LegoS32 itemHeight = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(itemResource->GetHeight())) * m_unk0x0f0 * m_unk0x114
			);
			m_unk0x000->VTable0x70(
				itemResource,
				0,
				m_unk0x0c0 + ((31 * width) >> 6) - (itemWidth >> 1),
				m_unk0x0e0 + ((38 * height) >> 6) - (itemHeight >> 1),
				itemWidth,
				itemHeight
			);
		}

		if (itemLevel) {
			UtopianPan0xa4* levelResource = m_unk0x008->VTable0x20(itemLevel + 12);
			LegoS32 levelWidth = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(levelResource->GetWidth())) * m_unk0x0f0 * m_unk0x10c
			);
			LegoS32 levelHeight = static_cast<LegoS32>(
				static_cast<double>(static_cast<LegoS32>(levelResource->GetHeight())) * m_unk0x0f0 * m_unk0x114
			);
			m_unk0x000->VTable0x70(
				levelResource,
				0,
				m_unk0x0c0 + ((24 * (3 * width)) >> 6),
				m_unk0x0e0,
				levelWidth,
				levelHeight
			);
		}
	}

	m_unk0x078 = m_unk0x02c->m_unk0x3e8.m_unk0x618 * 0.2f + m_unk0x078 * 0.80000001f;

	switch (m_unk0x03c) {
	case 1:
		FUN_004249b0();
		break;
	case 2:
		FUN_004258e0();
		break;
	case 3:
		FUN_00424fb0();
		break;
	}
}

// FUNCTION: LEGORACERS 0x00427140
CobaltTrail0x140::CobaltTrail0x140()
{
	Reset();
}
