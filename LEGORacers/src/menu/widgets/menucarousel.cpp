#include "menu/widgets/menucarousel.h"

#include "audio/soundgroupbinding.h"
#include "camera/golcamera.h"
#include "core/gol.h"
#include "golerror.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menumodelcarousel.h"
#include "menu/widgets/menuscrollcarousel.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"

#include <float.h>

DECOMP_SIZE_ASSERT(MenuCarousel, 0x78)
DECOMP_SIZE_ASSERT(MenuCarousel::CreateParams, 0x38)
DECOMP_SIZE_ASSERT(MenuModelCarousel, 0xc0)
DECOMP_SIZE_ASSERT(MenuModelCarousel::CreateParams, 0x74)
DECOMP_SIZE_ASSERT(MenuModelCarousel::Item, 0xd0)
DECOMP_SIZE_ASSERT(MenuScrollCarousel, 0x94)
DECOMP_SIZE_ASSERT(MenuCarouselNavigator, 0x94)

extern const LegoFloat g_two;

// GLOBAL: LEGORACERS 0x004b244c
const LegoFloat g_modelCarouselMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x0046c880
MenuCarousel::MenuCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c8f0
MenuCarousel::~MenuCarousel()
{
	Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046c950
void MenuCarousel::Reset()
{
	m_selectedIndex = 0;
	m_itemCount = 0;
	m_slotCount = 0;
	m_style = NULL;
	m_scrolling = 0;
	m_scrollDurationMs = 0;
	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x0046c970
LegoBool32 MenuCarousel::Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry)
{
	Destroy();
	m_style = p_styleEntry;
	m_soundGroupBinding = p_createParams->m_soundGroupBinding;

	return CreateWidget(p_createParams);
}

// FUNCTION: LEGORACERS 0x0046c9a0
LegoS32 MenuCarousel::WrapIndex(LegoS32 p_index)
{
	if (p_index >= 0) {
		return p_index % m_itemCount;
	}

	return m_itemCount + p_index;
}

// FUNCTION: LEGORACERS 0x0046c9c0
void MenuCarousel::SetColor(VisualStateColor* p_visualState)
{
	for (MenuWidget* child = m_firstChild; child; child = child->GetNextSibling()) {
		child->SetColor(p_visualState);
	}

	MenuWidget::SetColor(p_visualState);
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::SetItemColors(VisualStateColor*, VisualStateColor*)
{
}

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void MenuCarousel::SetFocusedItemColors(VisualStateColor*, VisualStateColor*)
{
}

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
	state.m_color.m_red = state.m_color.m_grn = state.m_color.m_blu = 0xff;
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

// FUNCTION: LEGORACERS 0x0046cc10
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
	LegoS32 width = m_rect.m_right - m_rect.m_left;
	LegoS32 height = m_rect.m_bottom - m_rect.m_top;
	LegoS32 halfWidth = -(width >> 1);
	Item* item = m_items;
	LegoS32 i = 0;

	LegoFloat widthFloat = static_cast<LegoFloat>(width);
	m_scaleX = (m_camera->m_nearHalfWidth + m_camera->m_nearHalfWidth) / widthFloat;
	LegoFloat heightFloat = static_cast<LegoFloat>(height);
	m_scaleY = (m_camera->m_nearHalfHeight + m_camera->m_nearHalfHeight) / heightFloat;

	if (m_slotCount > 0) {
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
	minX += g_two;
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
			entity->SetPrimaryModel(item->m_model, g_modelCarouselMaxFloat);
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
			entity->SetPrimaryModel(shiftedModel, g_modelCarouselMaxFloat);
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

		LegoS32 scrollDurationMs = m_scrollDurationMs;
		elapsed = p_elapsed;
		if (p_elapsed > static_cast<undefined4>(scrollDurationMs)) {
			elapsed = scrollDurationMs;
		}
		m_scrollDurationMs = scrollDurationMs - elapsed;
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

// FUNCTION: LEGORACERS 0x0046d820
MenuScrollCarousel::MenuScrollCarousel()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d890
MenuScrollCarousel::~MenuScrollCarousel()
{
	Destroy();
	Reset();
}

// FUNCTION: LEGORACERS 0x0046d8f0
void MenuScrollCarousel::Reset()
{
	MenuCarousel::Reset();
	m_slotCount = 1;
	m_selectedChild = NULL;
	m_scrollPosition = 0.0f;
	m_scrollSpeed = 0.0f;
}

// FUNCTION: LEGORACERS 0x0046d920
void MenuScrollCarousel::SelectChild(MenuWidget* p_child)
{
	MenuWidget* child = m_firstChild;
	MenuWidget* current = m_selectedChild;
	LegoS32 index = 0;

	if (p_child != current) {
		m_selectedChild = NULL;

		while (child) {
			if (child == p_child) {
				m_selectedChild = child;
				m_selectedIndex = index;
				break;
			}

			child = child->GetNextSibling();
			index++;
		}

		if (!m_scrolling) {
			SnapToSelection();
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d960
void MenuScrollCarousel::SetSelection(undefined4 p_index)
{
	m_selectedChild = GetChildByIndex(p_index);
	m_selectedIndex = p_index;
	if (!m_scrolling) {
		SnapToSelection();
	}
}

// FUNCTION: LEGORACERS 0x0046d990
void MenuScrollCarousel::SnapToSelection()
{
	m_offsetX = m_selectedChild->GetRect()->m_left;

	if (m_style->m_pageMode) {
		LegoS32 width = m_rect.m_right - m_rect.m_left;
		m_offsetX = (m_offsetX / width) * width;
	}
}

// FUNCTION: LEGORACERS 0x0046d9c0
void MenuScrollCarousel::AddItem(MenuWidget* p_item)
{
	p_item->SetParent(this);
	p_item->SetColor(&m_visualState);
	m_itemCount++;
	LayoutItem(p_item);

	if (m_itemCount == 1) {
		SetSelection(m_selectedIndex);
	}
}

// FUNCTION: LEGORACERS 0x0046da00
void MenuScrollCarousel::RemoveItem(MenuWidget* p_child)
{
	MenuWidget* child = p_child->GetNextSibling();
	p_child->RemoveFromParent();
	m_itemCount--;

	while (child) {
		LayoutItem(child);
		if (child == m_selectedChild) {
			SetSelection(m_selectedIndex - 1);
		}

		child = child->GetNextSibling();
	}
}

// FUNCTION: LEGORACERS 0x0046da40
MenuWidget* MenuScrollCarousel::RemoveItemByIndex(LegoS32 p_index)
{
	MenuWidget* child = GetChildByIndex(p_index);
	RemoveItem(child);

	return child;
}

// FUNCTION: LEGORACERS 0x0046da60
void MenuScrollCarousel::RemoveAllItems()
{
	while (m_itemCount) {
		RemoveItemByIndex(0);
	}
}

// FUNCTION: LEGORACERS 0x0046da80
void MenuCarouselNavigator::LayoutItem(MenuWidget* p_child)
{
	Rect rect = *p_child->GetRect();

	MenuStyleTable::CarouselStyle* style = m_style;
	LegoS32 width = rect.m_right;
	if (style->m_pageMode) {
		width = m_rect.m_right;
		width -= m_rect.m_left;
	}
	else {
		width -= rect.m_left;
	}

	Rect slot;
	MenuWidget* prev = p_child->GetPrevSibling();
	if (prev) {
		slot.m_left = prev->GetRect()->m_right;

		if (style->m_pageMode) {
			slot.m_left = ((slot.m_left + width - 1) / width) * width;
		}
	}
	else {
		slot.m_left = 0;
	}

	slot.m_top = rect.m_top;
	slot.m_bottom = rect.m_bottom;
	slot.m_right = slot.m_left + width;

	if (style->m_pageMode) {
		CenterRectIn(&slot, &rect);
	}
	else {
		rect = slot;
	}

	p_child->SetRect(&rect);
}

// FUNCTION: LEGORACERS 0x0046db40
void MenuCarouselNavigator::StartScroll(undefined4 p_distance)
{
	LegoS32 count = m_style->m_scrollDurationMs;

	m_scrollDurationMs = count;
	LegoFloat divisor = (LegoFloat) count;
	LegoFloat scrollSpeed = (LegoFloat) (LegoS32) p_distance;
	scrollSpeed /= divisor;
	m_animFlags |= 1;
	m_scrolling = 1;
	m_scrollSpeed = scrollSpeed;
	m_scrollPosition = (LegoFloat) m_offsetX;
}

// FUNCTION: LEGORACERS 0x0046db80
LegoS32 MenuCarouselNavigator::ScrollNext()
{
	if (!m_itemCount) {
		return 0;
	}

	if (!m_scrolling) {
		if (m_selectedIndex >= m_itemCount - 1 && !m_style->m_wrap) {
			m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
			return m_selectedIndex;
		}

		StartScroll(m_rect.m_right - m_rect.m_left);
		SetSelection(WrapIndex(m_selectedIndex + 1));
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[0]);
	}

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046dbf0
LegoS32 MenuCarouselNavigator::ScrollPrevious()
{
	if (!m_itemCount) {
		return 0;
	}

	if (m_scrolling) {
		return m_selectedIndex;
	}

	if (m_selectedIndex == 0 && !m_style->m_wrap) {
		m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[2]);
		return m_selectedIndex;
	}

	StartScroll(m_rect.m_left - m_rect.m_right);
	SetSelection(WrapIndex(m_selectedIndex - 1));
	m_soundGroupBinding->PlaySoundByIndex(m_style->m_soundIds[1]);

	return m_selectedIndex;
}

// FUNCTION: LEGORACERS 0x0046dc70
MenuWidget* MenuCarouselNavigator::DrawSelf(Rect* p_param1, Rect* p_param2)
{
	Rect* lastChildRect = m_lastChild->GetRect();
	MenuWidget* child = m_firstChild;

	if (!m_style->m_wrap || !child) {
		return NULL;
	}

	do {
		child->Draw(p_param1, p_param2);
		child = child->GetNextSibling();
	} while (child);

	LegoS32 width;
	if (m_style->m_pageMode) {
		width = m_rect.m_right - m_rect.m_left;
	}
	else {
		width = lastChildRect->m_right - lastChildRect->m_left;
	}

	LegoS32 savedLeft = m_offsetX;
	LegoS32 roundedExtent = ((lastChildRect->m_right + width - 1) / width) * width;

	if (width + savedLeft > roundedExtent) {
		m_offsetX = 0;

		Rect local1 = *p_param1;
		Rect local2 = *p_param2;
		local2.m_left += roundedExtent - savedLeft;

		local1.m_left = 0;
		local1.m_right = local2.m_right - local2.m_left;

		for (child = m_firstChild; child; child = child->GetNextSibling()) {
			child->Draw(&local1, &local2);
		}

		m_offsetX = savedLeft;
	}

	return this;
}

// FUNCTION: LEGORACERS 0x0046dd80
undefined4 MenuCarouselNavigator::OnEvent(undefined4 p_elapsedMs)
{
	if (m_scrolling) {
		LegoS32 remaining = m_scrollDurationMs;

		if (remaining == 0) {
			m_scrolling = 0;
			m_animFlags &= 0xfe;
			SnapToSelection();

			if (m_notifyHandler) {
				m_notifyHandler->OnCarouselSettled(this);
			}

			return 0;
		}

		if (p_elapsedMs > (undefined4) remaining) {
			p_elapsedMs = remaining;
		}

		LegoFloat step = m_scrollSpeed;
		LegoFloat scaled = (LegoFloat) (LegoS32) p_elapsedMs;
		LegoFloat delta = step * scaled;

		m_scrollDurationMs = remaining - p_elapsedMs;
		m_scrollPosition = m_scrollPosition + delta;

		if (m_scrollPosition < 0.0f) {
			LegoS32 extent;
			if (m_style->m_pageMode) {
				LegoS32 left = m_rect.m_left;
				LegoS32 width = m_rect.m_right - left;
				extent = ((m_lastChild->GetRect()->m_right - left + m_rect.m_right - 1) / width) * width;
			}
			else {
				extent = m_lastChild->GetRect()->m_right;
			}

			m_scrollPosition = m_scrollPosition + (LegoFloat) extent;
		}

		m_offsetX = (LegoS32) m_scrollPosition;
	}

	return 0;
}
