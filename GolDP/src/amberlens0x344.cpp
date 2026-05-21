#include "amberlens0x344.h"

#include "bronzefalcon0xc8770.h"
#include "rectangle.h"
#include "slatepeak0x58.h"

DECOMP_SIZE_ASSERT(AmberLens0x344, 0x344)

// FUNCTION: GOLDP 0x10001ea0
AmberLens0x344::AmberLens0x344()
{
	m_unk0x04 = &m_unk0x120.m_unk0x00;
	m_renderer = NULL;
}

// FUNCTION: GOLDP 0x10001f00
AmberLens0x344::~AmberLens0x344()
{
	if (m_renderer) {
		m_renderer->VTable0x24();
	}
}

// FUNCTION: GOLDP 0x10001f60
void AmberLens0x344::FUN_10001f60(BronzeFalcon0xc8770* p_renderer)
{
	m_renderer = p_renderer;
	if (p_renderer != NULL) {
		const SlatePeak0x58* renderTargetInfo = p_renderer->GetRenderTargetInfo();
		if (m_viewportMaxY == 0 || m_viewportMaxX == 0) {
			m_viewportMinX = 0;
			m_viewportMinY = 0;
			m_viewportMaxX = renderTargetInfo->GetWidth();
			m_viewportMaxY = renderTargetInfo->GetHeight();
		}

		if (!(m_flags & c_flagBit3)) {
			LegoFloat width = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
			LegoFloat height = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
			m_unk0x0c = width / height;
		}

		m_unk0x120.m_unk0x210 = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
		m_unk0x120.m_unk0x214 = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
		m_unk0x120.m_unk0x218 = static_cast<LegoFloat>(m_viewportMinX);
		m_unk0x120.m_unk0x21c = static_cast<LegoFloat>(m_viewportMinY);
		m_flags |= c_flagBit0 | c_flagBit1;
	}
}

// FUNCTION: GOLDP 0x10002060
void AmberLens0x344::VTable0x28()
{
	if (m_flags & (c_flagBit0 | c_flagBit1)) {
		if (m_flags & c_flagBit1) {
			if (!(m_flags & c_flagBit3)) {
				LegoFloat width = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
				LegoFloat height = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
				m_unk0x0c = width / height;
			}

			m_unk0x120.m_unk0x210 = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
			m_unk0x120.m_unk0x214 = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
			m_unk0x120.m_unk0x218 = static_cast<LegoFloat>(m_viewportMinX);
			m_unk0x120.m_unk0x21c = static_cast<LegoFloat>(m_viewportMinY);
		}

		if (m_flags & c_flagBit0) {
			VTable0x00();
		}

		if (m_flags & c_flagBit1) {
			VTable0x04();
		}

		GolMath::FUN_1002f3a0(m_unk0x120.m_unk0xd0, m_unk0x120.m_unk0x110, &m_unk0x120.m_unk0x190);
		GolMath::FUN_1002f3a0(m_unk0x120.m_unk0xd0, m_unk0x120.m_unk0x150, &m_unk0x120.m_unk0x1d0);
	}
}

// FUNCTION: GOLDP 0x10002160
void AmberLens0x344::VTable0x00()
{
	GolVec3 position;
	GolVec3 up;
	GolVec3 forward;
	GolVec3 right;
	m_unk0x120.m_unk0x00.GetBasis(&right, &forward, &up);
	m_unk0x120.m_unk0x00.GetPosition(&position);

	GolMatrix4& viewMatrix = m_unk0x120.m_unk0xd0;
	viewMatrix.m_m[0][0] = up.m_x;
	viewMatrix.m_m[0][1] = forward.m_x;
	viewMatrix.m_m[0][2] = right.m_x;
	viewMatrix.m_m[0][3] = 0.0f;
	viewMatrix.m_m[1][0] = up.m_y;
	viewMatrix.m_m[1][1] = forward.m_y;
	viewMatrix.m_m[1][2] = right.m_y;
	viewMatrix.m_m[1][3] = 0.0f;
	viewMatrix.m_m[2][0] = up.m_z;
	viewMatrix.m_m[2][1] = forward.m_z;
	viewMatrix.m_m[2][2] = right.m_z;
	viewMatrix.m_m[2][3] = 0.0f;
	viewMatrix.m_m[3][0] = -(position.m_x * up.m_x + position.m_y * up.m_y + position.m_z * up.m_z);
	viewMatrix.m_m[3][1] = -(position.m_x * forward.m_x + position.m_y * forward.m_y + position.m_z * forward.m_z);
	viewMatrix.m_m[3][3] = 1.0f;

	m_flags &= ~c_flagBit0;
	viewMatrix.m_m[3][2] = -(position.m_x * right.m_x + position.m_y * right.m_y + position.m_z * right.m_z);
	if (m_flags & c_flagBit2) {
		FUN_1001c450(m_unk0x34);
	}
	else {
		FUN_1001bfc0(m_unk0x34);
	}
}

// FUNCTION: GOLDP 0x100022b0
void AmberLens0x344::FUN_100022b0(
	GolMatrix4* p_matrix,
	LegoFloat p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat xScale = 1.0f / (m_unk0x100.m_z - m_unk0x100.m_x);
	xScale *= p_unk0x08;
	LegoFloat yScale = 1.0f / (m_unk0x100.m_u - m_unk0x100.m_y);
	yScale *= p_unk0x0c;
	LegoFloat zScale = m_unk0x14;
	LegoFloat zDenominator = m_unk0x14 - m_unk0x10;
	zScale /= zDenominator;
	LegoFloat nearTwice = m_unk0x10 + m_unk0x10;

	p_matrix->m_m[0][0] = nearTwice * xScale;
	p_matrix->m_m[0][1] = 0.0f;
	p_matrix->m_m[0][2] = 0.0f;
	p_matrix->m_m[0][3] = 0.0f;
	p_matrix->m_m[1][0] = 0.0f;
	p_matrix->m_m[1][1] = nearTwice * yScale;
	p_matrix->m_m[1][2] = 0.0f;
	p_matrix->m_m[1][3] = 0.0f;
	p_matrix->m_m[2][0] = p_unk0x10 - ((m_unk0x100.m_x + m_unk0x100.m_z) * xScale);
	p_matrix->m_m[2][1] = p_unk0x14 - ((m_unk0x100.m_y + m_unk0x100.m_u) * yScale);
	p_matrix->m_m[2][2] = zScale;
	p_matrix->m_m[2][3] = 1.0f;
	p_matrix->m_m[3][0] = 0.0f;
	p_matrix->m_m[3][1] = 0.0f;
	p_matrix->m_m[3][2] = -(m_unk0x10 * zScale);
	p_matrix->m_m[3][3] = 0.0f;
}

// FUNCTION: GOLDP 0x10002370
void AmberLens0x344::VTable0x04()
{
	if (!(m_flags & c_flagBit2)) {
		m_unk0x100.m_x = -m_unk0x18;
		m_unk0x100.m_y = -m_unk0x1c;
		m_unk0x100.m_z = m_unk0x18;
		m_unk0x100.m_u = m_unk0x1c;
	}

	FUN_100022b0(&m_unk0x120.m_unk0x110, 0.5f, 0.5f, 0.5f, 0.5f);

	LegoFloat halfWidth = m_unk0x120.m_unk0x210 * 0.5f;
	LegoFloat halfHeight = m_unk0x120.m_unk0x214 * 0.5f;
	FUN_100022b0(
		&m_unk0x120.m_unk0x150,
		halfWidth,
		halfHeight,
		halfWidth + m_unk0x120.m_unk0x218,
		halfHeight + m_unk0x120.m_unk0x21c
	);

	m_flags &= ~c_flagBit1;
}

// STUB: GOLDP 0x10002430
void AmberLens0x344::VTable0x14()
{
	STUB(0x10002430);
}

// STUB: GOLDP 0x100024d0
void AmberLens0x344::VTable0x18()
{
	STUB(0x100024d0);
}

// STUB: GOLDP 0x10002570
void AmberLens0x344::VTable0x1c()
{
	STUB(0x10002570);
}

// FUNCTION: GOLDP 0x10002630
void AmberLens0x344::VTable0x10(const GolVec4* p_bounds)
{
	m_flags |= c_flagBit0 | c_flagBit1 | c_flagBit2;
	m_unk0x100 = *p_bounds;
}

// FUNCTION: GOLDP 0x10002660
void AmberLens0x344::VTable0x0c(Rect* p_rect)
{
	m_viewportMinX = p_rect->m_left;
	m_viewportMaxX = p_rect->m_right;
	m_viewportMinY = p_rect->m_top;
	m_viewportMaxY = p_rect->m_bottom;

	if (!(m_flags & c_flagBit3)) {
		LegoFloat width = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
		LegoFloat height = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
		m_unk0x0c = width / height;
	}

	m_unk0x120.m_unk0x210 = static_cast<LegoFloat>(m_viewportMaxX - m_viewportMinX);
	m_unk0x120.m_unk0x214 = static_cast<LegoFloat>(m_viewportMaxY - m_viewportMinY);
	m_unk0x120.m_unk0x218 = static_cast<LegoFloat>(m_viewportMinX);
	m_unk0x120.m_unk0x21c = static_cast<LegoFloat>(m_viewportMinY);

	if (m_flags & c_flagBit2) {
		FUN_1001c450(m_unk0x34);
	}
	else {
		FUN_1001bfc0(m_unk0x34);
	}

	VTable0x04();
	GolMath::FUN_1002f3a0(m_unk0x120.m_unk0xd0, m_unk0x120.m_unk0x110, &m_unk0x120.m_unk0x190);
	GolMath::FUN_1002f3a0(m_unk0x120.m_unk0xd0, m_unk0x120.m_unk0x150, &m_unk0x120.m_unk0x1d0);
}

// FUNCTION: GOLDP 0x10002770
void AmberLens0x344::VTable0x20(const GolVec3* p_src, GolVec3* p_dest)
{
	VTable0x28();

	LegoFloat x = m_unk0x120.m_unk0x1d0.m_m[0][0];
	p_dest->m_x = x * p_src->m_x;
	p_dest->m_y = m_unk0x120.m_unk0x1d0.m_m[0][1] * p_src->m_x;
	p_dest->m_z = m_unk0x120.m_unk0x1d0.m_m[0][2] * p_src->m_x;
	LegoFloat w = m_unk0x120.m_unk0x1d0.m_m[0][3] * p_src->m_x;

	p_dest->m_x += m_unk0x120.m_unk0x1d0.m_m[1][0] * p_src->m_y;
	p_dest->m_y += m_unk0x120.m_unk0x1d0.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_unk0x120.m_unk0x1d0.m_m[1][2] * p_src->m_y;
	w += m_unk0x120.m_unk0x1d0.m_m[1][3] * p_src->m_y;

	p_dest->m_x += m_unk0x120.m_unk0x1d0.m_m[2][0] * p_src->m_z;
	p_dest->m_y += m_unk0x120.m_unk0x1d0.m_m[2][1] * p_src->m_z;
	p_dest->m_z += m_unk0x120.m_unk0x1d0.m_m[2][2] * p_src->m_z;
	w += m_unk0x120.m_unk0x1d0.m_m[2][3] * p_src->m_z;

	p_dest->m_x += m_unk0x120.m_unk0x1d0.m_m[3][0];
	p_dest->m_y += m_unk0x120.m_unk0x1d0.m_m[3][1];
	p_dest->m_z += m_unk0x120.m_unk0x1d0.m_m[3][2];
	w += m_unk0x120.m_unk0x1d0.m_m[3][3];

	LegoFloat inverseW = 1.0f / w;
	p_dest->m_x *= inverseW;
	LegoFloat y = p_dest->m_y;
	p_dest->m_y = y * inverseW;
	LegoFloat z = p_dest->m_z;
	p_dest->m_z = z * inverseW;
}

// FUNCTION: GOLDP 0x10002860
void AmberLens0x344::FUN_10002860(D3DVIEWPORT2* p_viewport)
{
	const SlatePeak0x58* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	p_viewport->dwX = 0;
	p_viewport->dwY = 0;
	p_viewport->dwWidth = renderTargetInfo->GetWidth();
	p_viewport->dwHeight = renderTargetInfo->GetHeight();
}
