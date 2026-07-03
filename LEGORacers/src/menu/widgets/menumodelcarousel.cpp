#include "menu/widgets/menumodelcarousel.h"

#include "camera/golcamera.h"
#include "core/gol.h"
#include "golerror.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

#include <float.h>

DECOMP_SIZE_ASSERT(MenuModelCarousel, 0xc0)
DECOMP_SIZE_ASSERT(MenuModelCarousel::CreateParams, 0x74)
DECOMP_SIZE_ASSERT(MenuModelCarousel::Item, 0xd0)

// GLOBAL: LEGORACERS 0x004b009c
extern const LegoFloat g_violetShoalTwo = 2.0f;

// GLOBAL: LEGORACERS 0x004b244c
const LegoFloat g_violetShoalMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuModelCarousel::LayoutItem(undefined4, GolModelEntity*)
{
}

// FUNCTION: LEGORACERS 0x0046ca00
MenuModelCarousel::MenuModelCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ca80
MenuModelCarousel::~MenuModelCarousel()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x0046cad0
void MenuModelCarousel::Reset()
{
	m_unk0xa4 = 1.0f;
	m_camera = 0;
	m_savedCamera = 0;
	m_items = 0;
	m_unk0xa0 = 0;
	m_unk0x9c = 0;
	m_scrollStep = 0;
	MenuCarousel::Reset();
}

// FUNCTION: LEGORACERS 0x0046cb10
LegoBool32 MenuModelCarousel::Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	if (!MenuCarousel::Create(p_createParams, p_styleEntry)) {
		return FALSE;
	}

	m_scrollStep = p_createParams->m_scrollStep;
	m_viewportIndex = p_createParams->m_viewportIndex;
	SetupCamera(p_createParams);

	PushCamera();
	CreateItems(p_createParams);
	PopCamera();

	VisualStateColor state;
	state.m_color.m_red = 0xff;
	state.m_color.m_grn = 0xff;
	state.m_color.m_blu = 0xff;
	state.m_color.m_alp = 0xff;
	SetItemColors(&state, &state);
	SetFocusedItemColors(&state, &state);

	return TRUE;
}

// FUNCTION: LEGORACERS 0x0046cba0
LegoBool32 MenuModelCarousel::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_items) {
			for (LegoS32 i = 0; i < m_slotCount; i++) {
				if (m_items[i].m_model) {
					m_golExport->DestroyModel(m_items[i].m_model);
				}
			}

			delete[] m_items;
		}

		if (m_camera) {
			m_golExport->DestroyCamera(m_camera);
		}

		result = MenuWidget::Destroy();
	}

	return result;
}

// STUB: LEGORACERS 0x0046cc10
void MenuModelCarousel::SetupCamera(CreateParams* p_createParams)
{
	m_cameraDistance = p_createParams->m_cameraVectors[7];
	GolCamera* camera = m_golExport->CreateCamera();
	m_camera = camera;

	LegoFloat fov = p_createParams->m_cameraVectors[6];
	LegoU32 flags = camera->m_flags | GolCamera::c_flagProjectionDirty;
	camera->m_fov = fov;
	camera->m_flags = flags;

	camera = m_camera;
	LegoFloat nearClip = m_cameraDistance;
	LegoU32 nearFlags = camera->m_flags | GolCamera::c_flagProjectionDirty;
	camera->m_nearClip = nearClip;
	camera->m_flags = nearFlags;

	camera = m_camera;
	LegoFloat farClip = p_createParams->m_cameraVectors[8];
	LegoU32 farFlags = camera->m_flags | GolCamera::c_flagProjectionDirty;
	camera->m_farClip = farClip;
	camera->m_flags = farFlags;

	GolVec3 position;
	GolVec3 target;
	GolVec3 up;
	position.m_x = m_cameraDistance;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = 1.0f;
	position.m_y = 0.0f;
	position.m_z = 0.0f;
	target.m_x = 0.0f;
	target.m_y = 0.0f;
	target.m_z = 0.0f;

	m_camera->LookAt(&position, &target, &up);
	UpdateViewport();

	const Rect* viewport = m_camera->GetViewport();
	LegoS32 left = viewport->m_left;
	LegoS32 top = viewport->m_top;
	LegoS32 right = viewport->m_right;
	LegoS32 bottom = viewport->m_bottom;
	LegoS32 width = right - left;
	LegoS32 height = bottom - top;

	LegoFloat aspect = static_cast<LegoFloat>(width);
	LegoFloat divisor = static_cast<LegoFloat>(height);
	aspect /= divisor;
	aspect *= p_createParams->m_aspectScale;
	m_camera->SetAspectRatio(aspect);
}

// FUNCTION: LEGORACERS 0x0046cd30
void MenuModelCarousel::UpdateViewport()
{
	const GolRenderTarget* renderTarget = m_renderer->GetRenderTargetInfo();

	if (m_camera) {
		Rect rect = *GetGlobalRect();

		if (rect.m_left < 0) {
			rect.m_left = 0;
		}
		if (rect.m_right > renderTarget->GetWidth()) {
			rect.m_right = renderTarget->GetWidth();
		}
		if (rect.m_top < 0) {
			rect.m_top = 0;
		}
		if (rect.m_bottom > renderTarget->GetHeight()) {
			rect.m_bottom = renderTarget->GetHeight();
		}

		m_camera->SetViewport(&rect);
	}
}

// FUNCTION: LEGORACERS 0x0046cdc0
void MenuModelCarousel::PushCamera()
{
	m_savedCamera = m_renderer->GetCurrentCamera();
	m_renderer->SetCamera(m_camera);
	m_renderer->ApplyCamera();
}

// FUNCTION: LEGORACERS 0x0046cdf0
void MenuModelCarousel::PopCamera()
{
	if (m_savedCamera) {
		m_renderer->SetCamera(m_savedCamera);
		m_renderer->ApplyCamera();
	}
}

// FUNCTION: LEGORACERS 0x0046ce10
void MenuModelCarousel::CreateItems(CreateParams* p_createParams)
{
	m_slotCount = p_createParams->m_slotCount;
	m_focusedSlot = p_createParams->m_focusedSlot;

	m_items = new Item[m_slotCount];
	if (!m_items) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	Item* item = m_items;
	for (LegoS32 i = 0; i < m_slotCount; i++) {
		item->m_model = m_golExport->CreateModel();
		if (!item->m_model) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		item->m_rect = p_createParams->m_slotRects[i];
		item++;
	}

	DestroyItems();
}

// FUNCTION: LEGORACERS 0x0046cf20
void MenuModelCarousel::DestroyItems()
{
	LegoS32 left = m_rect.m_left;
	LegoS32 width = m_rect.m_right - left;
	LegoS32 top = m_rect.m_top;
	LegoS32 height = m_rect.m_bottom - top;
	LegoS32 halfWidth = -(width >> 1);
	Item* item = m_items;
	LegoS32 zero = 0;
	LegoS32 i = zero;

	LegoFloat widthFloat = static_cast<LegoFloat>(width);
	m_scaleX = (m_camera->m_nearHalfWidth + m_camera->m_nearHalfWidth) / widthFloat;
	LegoFloat heightNumerator = m_camera->m_nearHalfHeight;
	heightNumerator += heightNumerator;
	LegoFloat heightFloat = static_cast<LegoFloat>(height);
	m_scaleY = heightNumerator / heightFloat;

	if (m_slotCount > zero) {
		do {
			Rect* rect = &item->m_rect;

			LegoS32 rectLeft = rect->m_left;
			rectLeft += halfWidth;
			item->m_left = static_cast<LegoFloat>(rectLeft) * m_scaleX;
			item->m_right = item->m_left + static_cast<LegoFloat>(rect->m_right - rect->m_left) * m_scaleX;
			item->m_height = static_cast<LegoFloat>(rect->m_bottom - rect->m_top) * m_scaleY;
			item->m_unk0x0c = 0.0f;
			item->m_positionZ = 0.0f;

			LegoFloat center = item->m_right;
			center += item->m_left;
			item->m_centerY = center * 0.5f;

			LegoFloat range = item->m_right - item->m_left;
			if (range > item->m_height) {
				item->m_fitSize = item->m_height;
			}
			else {
				item->m_fitSize = range;
			}

			i++;
			item++;
		} while (i < m_slotCount);
	}
}

// FUNCTION: LEGORACERS 0x0046d010
void MenuModelCarousel::InitializeItem(Item* p_item)
{
	GolVec3 center;
	p_item->m_entity.GetModelBounds(0, &center, &p_item->m_modelRadius);
	p_item->m_modelRadius += p_item->m_modelRadius;
}

// FUNCTION: LEGORACERS 0x0046d040
void MenuModelCarousel::GetItemPosition(Item* p_item, GolVec3* p_position)
{
	LegoFloat scale;
	LegoFloat radius;
	GolVec3 itemPosition;
	GolVec3 center;
	GolVec3 oldPosition;

	LegoFloat x = p_item->m_modelRadius - p_item->m_fitSize;

	if (x > 0.0f) {
		x = -(m_cameraDistance / p_item->m_fitSize * x);
	}

	LegoFloat minX = p_item->m_modelRadius;
	minX += g_violetShoalTwo;
	minX = -minX;
	if (x > minX) {
		x = minX;
	}

	itemPosition.m_y = p_item->m_centerY;
	itemPosition.m_z = p_item->m_positionZ;
	scale = (m_cameraDistance - x) / m_cameraDistance;
	GolModelEntity* entity = &p_item->m_entity;

	entity->GetPosition(&oldPosition);

	p_position->m_x = x;
	p_position->m_y = scale * itemPosition.m_y;
	p_position->m_z = scale * itemPosition.m_z;
	entity->SetPosition(*p_position);

	entity->GetModelBounds(0, &center, &radius);

	p_position->m_x -= center.m_x - p_position->m_x;
	p_position->m_y -= center.m_y - p_position->m_y;
	p_position->m_z -= center.m_z - p_position->m_z;
	entity->SetPosition(oldPosition);
}

// FUNCTION: LEGORACERS 0x0046d140
GolModelEntity* MenuModelCarousel::GetItemEntity(LegoS32 p_index)
{
	return &m_items[p_index].m_entity;
}

// FUNCTION: LEGORACERS 0x0046d160
GolModelBase* MenuModelCarousel::GetItemModel(LegoS32 p_index)
{
	return m_items[p_index].m_model;
}

// FUNCTION: LEGORACERS 0x0046d180
void MenuModelCarousel::RefreshItemModel(LegoS32 p_index)
{
	Item* item = &m_items[p_index];
	InitializeItem(item);

	GolVec3 position;
	GetItemPosition(item, &position);
	item->m_entity.SetPosition(position);
	item->m_model = item->m_entity.GetModel(0);
}

// FUNCTION: LEGORACERS 0x0046d1d0
void MenuModelCarousel::SetItemColors(VisualStateColor* p_primaryColor, VisualStateColor* p_secondaryColor)
{
	Item* item = m_items;
	for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
		item->m_primaryColor.m_packed = p_primaryColor->m_packed;
		item->m_secondaryColor.m_packed = p_secondaryColor->m_packed;
	}
}

// FUNCTION: LEGORACERS 0x0046d210
void MenuModelCarousel::SetFocusedItemColors(VisualStateColor* p_primaryColor, VisualStateColor* p_secondaryColor)
{
	Item* item = &m_items[m_focusedSlot];
	item->m_primaryColor.m_packed = p_primaryColor->m_packed;
	item->m_secondaryColor.m_packed = p_secondaryColor->m_packed;
}

// FUNCTION: LEGORACERS 0x0046d240
void MenuModelCarousel::SnapToSelection()
{
	Item* item = m_items;
	for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
		if (item->m_entity.HasModel()) {
			GolVec3 position;
			GetItemPosition(item, &position);
			item->m_entity.SetPosition(position);
			item->m_entity.ClearVelocity();
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d2a0
void MenuModelCarousel::StartScroll(undefined4)
{
	m_scrollDurationMs = m_style->m_scrollDurationMs;
	m_scrolling = 1;

	Item* item = m_items;
	for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
		if (item->m_entity.HasModel()) {
			GolVec3 currentPosition;
			item->m_entity.GetPosition(&currentPosition);

			GolVec3 targetPosition;
			GetItemPosition(item, &targetPosition);

			LegoFloat duration = static_cast<LegoFloat>(m_scrollDurationMs);
			GolVec3 velocity;
			velocity.m_x = (targetPosition.m_x - currentPosition.m_x) / duration;
			velocity.m_y = (targetPosition.m_y - currentPosition.m_y) / duration;
			velocity.m_z = (targetPosition.m_z - currentPosition.m_z) / duration;
			item->m_entity.SetVelocity(velocity);
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d350
LegoS32 MenuModelCarousel::ScrollNext()
{
	GolModelBase* model = m_items[0].m_model;
	Item* item = m_items;

	for (LegoS32 i = 0; i < m_slotCount - 1; i++, item++) {
		GolModelEntity* entity = &item->m_entity;

		item->m_model = item[1].m_model;
		if (item[1].m_entity.HasModel()) {
			entity->SetPrimaryModel(item->m_model, g_violetShoalMaxFloat);
			entity->CopyOrientationAndPositionFrom(item[1].m_entity);
			entity->InvalidateRadius();
			entity->SetPrimaryMaterialTable(item[1].m_entity.GetPrimaryMaterialTable());
			item->m_modelRadius = item[1].m_modelRadius;
			InitializeItem(item);
		}
		else {
			entity->ResetModelState();
		}
	}

	item->m_entity.ResetModelState();
	item->m_model = model;
	StartScroll(0);
	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046d470
LegoS32 MenuModelCarousel::ScrollPrevious()
{
	Item* item = &m_items[m_slotCount - 1];
	GolModelBase* model = item->m_model;

	for (LegoS32 i = m_slotCount - 1; i > 0; i--, item--) {
		GolModelEntity* entity = &item->m_entity;
		GolModelBase* shiftedModel = item[-1].m_model;

		item->m_model = shiftedModel;
		if (item[-1].m_entity.HasModel()) {
			entity->SetPrimaryModel(shiftedModel, g_violetShoalMaxFloat);
			entity->CopyOrientationAndPositionFrom(item[-1].m_entity);
			entity->InvalidateRadius();
			entity->SetPrimaryMaterialTable(item[-1].m_entity.GetPrimaryMaterialTable());
			item->m_modelRadius = item[-1].m_modelRadius;
			InitializeItem(item);
		}
		else {
			entity->ResetModelState();
		}
	}

	item->m_entity.ResetModelState();
	item->m_model = model;
	StartScroll(0);
	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046d5a0
void MenuModelCarousel::SetParent(MenuWidget* p_parent)
{
	MenuWidget::SetParent(p_parent);
	UpdateViewport();
}

// FUNCTION: LEGORACERS 0x0046d5c0
MenuWidget* MenuModelCarousel::OnKeyDown(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	if (!HitTest(p_x, p_y)) {
		return NULL;
	}

	if ((p_event->m_keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceMouse) {
		return NULL;
	}

	for (LegoS32 i = 0; i < m_slotCount; i++) {
		if (PointInRect(&m_items[i].m_rect, p_x, p_y)) {
			LegoS32 index = WrapIndex(i + m_selectedIndex - m_focusedSlot);
			SetSelection(index);

			if (m_notifyHandler) {
				m_notifyHandler->HandleKeyDown(this, p_event, p_x, p_y);
			}

			return this;
		}
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046d670
MenuWidget* MenuModelCarousel::DrawSelf(Rect*, Rect*)
{
	Item* item = m_items;

	m_renderer->EnableZBuffer();
	PushCamera();
	m_renderer->SelectViewport(m_viewportIndex);

	GolVec3 direction = m_renderer->GetCurrentLight(0)->m_direction;
	m_light.SetDirection(direction);

	m_renderer->ClearLights();
	m_renderer->SetAmbient(&m_materialColor);
	m_renderer->AddLight(&m_light);

	LegoU8 hasModelFlag = 1;
	for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
		if (item->m_entity.HasModel() & hasModelFlag) {
			m_renderer->GetCurrentMaterialColor()->SetColor(item->m_primaryColor.m_color);
			m_renderer->GetCurrentLight(0)->SetColor(item->m_secondaryColor.m_color);
			m_renderer->ApplyLights();
			m_renderer->DrawModelEntity(&item->m_entity);
		}
	}

	PopCamera();
	m_renderer->SelectViewport(6);
	m_renderer->DisableZBuffer(FALSE);

	return NULL;
}

// FUNCTION: LEGORACERS 0x0046d780
undefined4 MenuModelCarousel::OnEvent(undefined4 p_elapsed)
{
	undefined4 elapsed;

	if (m_scrolling) {
		if (!m_scrollDurationMs) {
			Item* item = m_items;
			for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
				if (item->m_entity.HasModel()) {
					item->m_entity.ClearVelocity();
				}
			}

			m_scrolling = 0;
			SnapToSelection();
		}

		elapsed = p_elapsed;
		if (p_elapsed > static_cast<undefined4>(m_scrollDurationMs)) {
			elapsed = m_scrollDurationMs;
		}
		m_scrollDurationMs -= elapsed;
	}
	else {
		elapsed = p_elapsed;
	}

	Item* item = m_items;
	for (LegoS32 i = 0; i < m_slotCount; i++, item++) {
		LayoutItem(elapsed, &item->m_entity);
		item->m_entity.Update(elapsed);
	}

	return 0;
}
