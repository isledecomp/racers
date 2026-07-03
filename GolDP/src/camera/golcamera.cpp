#include "camera/golcamera.h"

#include "render/gold3drenderdevice.h"
#include "render/rectangle.h"
#include "surface/golrendertarget.h"

DECOMP_SIZE_ASSERT(GolCamera, 0x344)

// FUNCTION: GOLDP 0x10001ea0
GolCamera::GolCamera()
{
	m_transform = &m_cameraMatrices.m_transform;
	m_renderer = NULL;
}

// FUNCTION: GOLDP 0x10001f00
GolCamera::~GolCamera()
{
	if (m_renderer) {
		m_renderer->DetachCamera();
	}
}

// FUNCTION: GOLDP 0x10001f60
void GolCamera::AttachToRenderer(GolD3DRenderDevice* p_renderer)
{
	m_renderer = p_renderer;
	if (p_renderer != NULL) {
		const GolRenderTarget* renderTargetInfo = p_renderer->GetRenderTargetInfo();
		if (m_viewport.m_bottom == 0 || m_viewport.m_right == 0) {
			m_viewport.m_left = 0;
			m_viewport.m_top = 0;
			m_viewport.m_right = renderTargetInfo->GetWidth();
			m_viewport.m_bottom = renderTargetInfo->GetHeight();
		}

		if (!(m_flags & c_flagFixedAspectRatio)) {
			LegoFloat width = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
			LegoFloat height = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
			m_aspectRatio = width / height;
		}

		m_cameraMatrices.m_viewportWidth = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
		m_cameraMatrices.m_viewportHeight = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
		m_cameraMatrices.m_viewportLeft = static_cast<LegoFloat>(m_viewport.m_left);
		m_cameraMatrices.m_viewportTop = static_cast<LegoFloat>(m_viewport.m_top);
		m_flags |= c_flagViewDirty | c_flagProjectionDirty;
	}
}

// FUNCTION: GOLDP 0x10002060
void GolCamera::UpdateMatrices()
{
	if (m_flags & (c_flagViewDirty | c_flagProjectionDirty)) {
		if (m_flags & c_flagProjectionDirty) {
			if (!(m_flags & c_flagFixedAspectRatio)) {
				LegoFloat width = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
				LegoFloat height = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
				m_aspectRatio = width / height;
			}

			m_cameraMatrices.m_viewportWidth = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
			m_cameraMatrices.m_viewportHeight = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
			m_cameraMatrices.m_viewportLeft = static_cast<LegoFloat>(m_viewport.m_left);
			m_cameraMatrices.m_viewportTop = static_cast<LegoFloat>(m_viewport.m_top);
		}

		if (m_flags & c_flagViewDirty) {
			UpdateViewMatrix();
		}

		if (m_flags & c_flagProjectionDirty) {
			UpdateProjectionMatrices();
		}

		GolMath::MultiplyMatrix4(
			m_cameraMatrices.m_view,
			m_cameraMatrices.m_projection,
			&m_cameraMatrices.m_viewProjection
		);
		GolMath::MultiplyMatrix4(
			m_cameraMatrices.m_view,
			m_cameraMatrices.m_screenProjection,
			&m_cameraMatrices.m_viewScreenProjection
		);
	}
}

// FUNCTION: GOLDP 0x10002160
void GolCamera::UpdateViewMatrix()
{
	GolVec3 position;
	GolVec3 up;
	GolVec3 forward;
	GolVec3 right;
	m_cameraMatrices.m_transform.GetBasis(&right, &forward, &up);
	m_cameraMatrices.m_transform.GetPosition(&position);

	GolMatrix4& viewMatrix = m_cameraMatrices.m_view;
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

	m_flags &= ~c_flagViewDirty;
	viewMatrix.m_m[3][2] = -(position.m_x * right.m_x + position.m_y * right.m_y + position.m_z * right.m_z);
	if (m_flags & c_flagCustomViewBounds) {
		ComputeFrustumFromBounds(&m_viewFrustum);
	}
	else {
		ComputeFrustum(&m_viewFrustum);
	}
}

// FUNCTION: GOLDP 0x100022b0
void GolCamera::BuildProjection(
	GolMatrix4* p_matrix,
	LegoFloat p_scaleX,
	LegoFloat p_scaleY,
	LegoFloat p_offsetX,
	LegoFloat p_offsetY
)
{
	LegoFloat xScale = 1.0f / (m_viewBounds.m_z - m_viewBounds.m_x);
	xScale *= p_scaleX;
	LegoFloat yScale = 1.0f / (m_viewBounds.m_u - m_viewBounds.m_y);
	yScale *= p_scaleY;
	LegoFloat zScale = m_farClip;
	LegoFloat zDenominator = m_farClip - m_nearClip;
	zScale /= zDenominator;
	LegoFloat nearTwice = m_nearClip + m_nearClip;

	p_matrix->m_m[0][0] = nearTwice * xScale;
	p_matrix->m_m[0][1] = 0.0f;
	p_matrix->m_m[0][2] = 0.0f;
	p_matrix->m_m[0][3] = 0.0f;
	p_matrix->m_m[1][0] = 0.0f;
	p_matrix->m_m[1][1] = nearTwice * yScale;
	p_matrix->m_m[1][2] = 0.0f;
	p_matrix->m_m[1][3] = 0.0f;
	p_matrix->m_m[2][0] = p_offsetX - ((m_viewBounds.m_x + m_viewBounds.m_z) * xScale);
	p_matrix->m_m[2][1] = p_offsetY - ((m_viewBounds.m_y + m_viewBounds.m_u) * yScale);
	p_matrix->m_m[2][2] = zScale;
	p_matrix->m_m[2][3] = 1.0f;
	p_matrix->m_m[3][0] = 0.0f;
	p_matrix->m_m[3][1] = 0.0f;
	p_matrix->m_m[3][2] = -(m_nearClip * zScale);
	p_matrix->m_m[3][3] = 0.0f;
}

// FUNCTION: GOLDP 0x10002370
void GolCamera::UpdateProjectionMatrices()
{
	if (!(m_flags & c_flagCustomViewBounds)) {
		m_viewBounds.m_x = -m_nearHalfWidth;
		m_viewBounds.m_y = -m_nearHalfHeight;
		m_viewBounds.m_z = m_nearHalfWidth;
		m_viewBounds.m_u = m_nearHalfHeight;
	}

	BuildProjection(&m_cameraMatrices.m_projection, 0.5f, 0.5f, 0.5f, 0.5f);

	LegoFloat halfWidth = m_cameraMatrices.m_viewportWidth * 0.5f;
	LegoFloat halfHeight = m_cameraMatrices.m_viewportHeight * 0.5f;
	BuildProjection(
		&m_cameraMatrices.m_screenProjection,
		halfWidth,
		halfHeight,
		halfWidth + m_cameraMatrices.m_viewportLeft,
		halfHeight + m_cameraMatrices.m_viewportTop
	);

	m_flags &= ~c_flagProjectionDirty;
}

// FUNCTION: GOLDP 0x10002430
void GolCamera::GetViewMatrix(GolMatrix4* p_dest)
{
	p_dest->m_m[0][0] = m_cameraMatrices.m_view.m_m[0][0];
	p_dest->m_m[0][1] = m_cameraMatrices.m_view.m_m[0][1];
	p_dest->m_m[0][2] = m_cameraMatrices.m_view.m_m[0][2];
	p_dest->m_m[0][3] = m_cameraMatrices.m_view.m_m[0][3];
	p_dest->m_m[1][0] = m_cameraMatrices.m_view.m_m[1][0];
	p_dest->m_m[1][1] = m_cameraMatrices.m_view.m_m[1][1];
	p_dest->m_m[1][2] = m_cameraMatrices.m_view.m_m[1][2];
	p_dest->m_m[1][3] = m_cameraMatrices.m_view.m_m[1][3];
	p_dest->m_m[2][0] = m_cameraMatrices.m_view.m_m[2][0];
	p_dest->m_m[2][1] = m_cameraMatrices.m_view.m_m[2][1];
	p_dest->m_m[2][2] = m_cameraMatrices.m_view.m_m[2][2];
	p_dest->m_m[2][3] = m_cameraMatrices.m_view.m_m[2][3];
	p_dest->m_m[3][0] = m_cameraMatrices.m_view.m_m[3][0];
	p_dest->m_m[3][1] = m_cameraMatrices.m_view.m_m[3][1];
	p_dest->m_m[3][2] = m_cameraMatrices.m_view.m_m[3][2];
	p_dest->m_m[3][3] = m_cameraMatrices.m_view.m_m[3][3];
}

// FUNCTION: GOLDP 0x100024d0
void GolCamera::GetViewScreenProjection(GolMatrix4* p_dest)
{
	p_dest->m_m[0][0] = m_cameraMatrices.m_viewScreenProjection.m_m[0][0];
	p_dest->m_m[0][1] = m_cameraMatrices.m_viewScreenProjection.m_m[0][1];
	p_dest->m_m[0][2] = m_cameraMatrices.m_viewScreenProjection.m_m[0][2];
	p_dest->m_m[0][3] = m_cameraMatrices.m_viewScreenProjection.m_m[0][3];
	p_dest->m_m[1][0] = m_cameraMatrices.m_viewScreenProjection.m_m[1][0];
	p_dest->m_m[1][1] = m_cameraMatrices.m_viewScreenProjection.m_m[1][1];
	p_dest->m_m[1][2] = m_cameraMatrices.m_viewScreenProjection.m_m[1][2];
	p_dest->m_m[1][3] = m_cameraMatrices.m_viewScreenProjection.m_m[1][3];
	p_dest->m_m[2][0] = m_cameraMatrices.m_viewScreenProjection.m_m[2][0];
	p_dest->m_m[2][1] = m_cameraMatrices.m_viewScreenProjection.m_m[2][1];
	p_dest->m_m[2][2] = m_cameraMatrices.m_viewScreenProjection.m_m[2][2];
	p_dest->m_m[2][3] = m_cameraMatrices.m_viewScreenProjection.m_m[2][3];
	p_dest->m_m[3][0] = m_cameraMatrices.m_viewScreenProjection.m_m[3][0];
	p_dest->m_m[3][1] = m_cameraMatrices.m_viewScreenProjection.m_m[3][1];
	p_dest->m_m[3][2] = m_cameraMatrices.m_viewScreenProjection.m_m[3][2];
	p_dest->m_m[3][3] = m_cameraMatrices.m_viewScreenProjection.m_m[3][3];
}

// FUNCTION: GOLDP 0x10002570
void GolCamera::TransformToView(const GolVec3* p_src, GolVec3* p_dest)
{
	if (m_flags & c_flagViewDirty) {
		UpdateViewMatrix();
	}

	LegoFloat x = m_cameraMatrices.m_view.m_m[0][0];
	p_dest->m_x = x * p_src->m_x;
	p_dest->m_y = m_cameraMatrices.m_view.m_m[0][1] * p_src->m_x;
	p_dest->m_z = m_cameraMatrices.m_view.m_m[0][2] * p_src->m_x;

	p_dest->m_x += m_cameraMatrices.m_view.m_m[1][0] * p_src->m_y;
	p_dest->m_y += m_cameraMatrices.m_view.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_cameraMatrices.m_view.m_m[1][2] * p_src->m_y;

	p_dest->m_x += m_cameraMatrices.m_view.m_m[2][0] * p_src->m_z;
	p_dest->m_y += m_cameraMatrices.m_view.m_m[2][1] * p_src->m_z;
	p_dest->m_z += m_cameraMatrices.m_view.m_m[2][2] * p_src->m_z;

	p_dest->m_x += m_cameraMatrices.m_view.m_m[3][0];
	p_dest->m_y += m_cameraMatrices.m_view.m_m[3][1];
	p_dest->m_z += m_cameraMatrices.m_view.m_m[3][2];
}

// FUNCTION: GOLDP 0x10002630
void GolCamera::SetViewBounds(const GolVec4* p_bounds)
{
	m_flags |= c_flagViewDirty | c_flagProjectionDirty | c_flagCustomViewBounds;
	m_viewBounds = *p_bounds;
}

// FUNCTION: GOLDP 0x10002660
void GolCamera::SetViewport(Rect* p_rect)
{
	m_viewport.m_left = p_rect->m_left;
	m_viewport.m_right = p_rect->m_right;
	m_viewport.m_top = p_rect->m_top;
	m_viewport.m_bottom = p_rect->m_bottom;

	if (!(m_flags & c_flagFixedAspectRatio)) {
		LegoFloat width = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
		LegoFloat height = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
		m_aspectRatio = width / height;
	}

	m_cameraMatrices.m_viewportWidth = static_cast<LegoFloat>(m_viewport.m_right - m_viewport.m_left);
	m_cameraMatrices.m_viewportHeight = static_cast<LegoFloat>(m_viewport.m_bottom - m_viewport.m_top);
	m_cameraMatrices.m_viewportLeft = static_cast<LegoFloat>(m_viewport.m_left);
	m_cameraMatrices.m_viewportTop = static_cast<LegoFloat>(m_viewport.m_top);

	if (m_flags & c_flagCustomViewBounds) {
		ComputeFrustumFromBounds(&m_viewFrustum);
	}
	else {
		ComputeFrustum(&m_viewFrustum);
	}

	UpdateProjectionMatrices();
	GolMath::MultiplyMatrix4(
		m_cameraMatrices.m_view,
		m_cameraMatrices.m_projection,
		&m_cameraMatrices.m_viewProjection
	);
	GolMath::MultiplyMatrix4(
		m_cameraMatrices.m_view,
		m_cameraMatrices.m_screenProjection,
		&m_cameraMatrices.m_viewScreenProjection
	);
}

// FUNCTION: GOLDP 0x10002770
void GolCamera::ProjectToScreen(const GolVec3* p_src, GolVec3* p_dest)
{
	UpdateMatrices();

	LegoFloat x = m_cameraMatrices.m_viewScreenProjection.m_m[0][0];
	p_dest->m_x = x * p_src->m_x;
	p_dest->m_y = m_cameraMatrices.m_viewScreenProjection.m_m[0][1] * p_src->m_x;
	p_dest->m_z = m_cameraMatrices.m_viewScreenProjection.m_m[0][2] * p_src->m_x;
	LegoFloat w = m_cameraMatrices.m_viewScreenProjection.m_m[0][3] * p_src->m_x;

	p_dest->m_x += m_cameraMatrices.m_viewScreenProjection.m_m[1][0] * p_src->m_y;
	p_dest->m_y += m_cameraMatrices.m_viewScreenProjection.m_m[1][1] * p_src->m_y;
	p_dest->m_z += m_cameraMatrices.m_viewScreenProjection.m_m[1][2] * p_src->m_y;
	w += m_cameraMatrices.m_viewScreenProjection.m_m[1][3] * p_src->m_y;

	p_dest->m_x += m_cameraMatrices.m_viewScreenProjection.m_m[2][0] * p_src->m_z;
	p_dest->m_y += m_cameraMatrices.m_viewScreenProjection.m_m[2][1] * p_src->m_z;
	p_dest->m_z += m_cameraMatrices.m_viewScreenProjection.m_m[2][2] * p_src->m_z;
	w += m_cameraMatrices.m_viewScreenProjection.m_m[2][3] * p_src->m_z;

	p_dest->m_x += m_cameraMatrices.m_viewScreenProjection.m_m[3][0];
	p_dest->m_y += m_cameraMatrices.m_viewScreenProjection.m_m[3][1];
	p_dest->m_z += m_cameraMatrices.m_viewScreenProjection.m_m[3][2];
	w += m_cameraMatrices.m_viewScreenProjection.m_m[3][3];

	LegoFloat inverseW = 1.0f / w;
	p_dest->m_x *= inverseW;
	LegoFloat y = p_dest->m_y;
	p_dest->m_y = y * inverseW;
	LegoFloat z = p_dest->m_z;
	p_dest->m_z = z * inverseW;
}

// FUNCTION: GOLDP 0x10002860
void GolCamera::BuildD3DViewport(D3DVIEWPORT2* p_viewport)
{
	const GolRenderTarget* renderTargetInfo = m_renderer->GetRenderTargetInfo();
	p_viewport->dwX = 0;
	p_viewport->dwY = 0;
	p_viewport->dwWidth = renderTargetInfo->GetWidth();
	p_viewport->dwHeight = renderTargetInfo->GetHeight();
}
