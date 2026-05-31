#include "menu/widgets/violetshoal0xc0.h"

#include "camera/golcamera.h"
#include "core/gol.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"

#include <float.h>

DECOMP_SIZE_ASSERT(VioletShoal0xc0, 0xc0)
DECOMP_SIZE_ASSERT(VioletShoal0xc0::Item0xd0, 0xd0)

// GLOBAL: LEGORACERS 0x004b009c
const LegoFloat g_violetShoalTwo = 2.0f;

// GLOBAL: LEGORACERS 0x004b244c
const LegoFloat g_violetShoalMaxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x0046c9f0 FOLDED
void VioletShoal0xc0::VTable0x5c(undefined4, GolModelEntity*)
{
}

// FUNCTION: LEGORACERS 0x0046ca00
VioletShoal0xc0::VioletShoal0xc0()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ca80
VioletShoal0xc0::~VioletShoal0xc0()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046cad0
void VioletShoal0xc0::Reset()
{
	m_unk0xa4 = 1.0f;
	m_unk0x80 = 0;
	m_unk0x84 = 0;
	m_unk0x7c = 0;
	m_unk0xa0 = 0;
	m_unk0x9c = 0;
	m_unk0xbc = 0;
	ObscureCarousel0x78::Reset();
}

// FUNCTION: LEGORACERS 0x0046cba0
LegoBool32 VioletShoal0xc0::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_unk0x7c) {
			for (LegoS32 i = 0; i < m_unk0x60; i++) {
				if (m_unk0x7c[i].m_model) {
					m_golExport->VTable0x48(m_unk0x7c[i].m_model);
				}
			}

			operator delete(m_unk0x7c);
		}

		if (m_unk0x80) {
			m_golExport->VTable0x54(m_unk0x80);
		}

		result = ObscureVantage0x58::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x0046cd30
void VioletShoal0xc0::FUN_0046cd30()
{
	const SlatePeak0x58* renderTarget = m_renderer->GetRenderTargetInfo();

	if (m_unk0x80) {
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

		m_unk0x80->VTable0x0c(&rect);
	}
}

// FUNCTION: LEGORACERS 0x0046d010
void VioletShoal0xc0::FUN_0046d010(Item0xd0* p_item)
{
	GolVec3 center;
	p_item->m_entity.FUN_10027fe0(0, &center, &p_item->m_modelRadius);
	p_item->m_modelRadius += p_item->m_modelRadius;
}

// STUB: LEGORACERS 0x0046d040
void VioletShoal0xc0::FUN_0046d040(Item0xd0* p_item, GolVec3* p_position)
{
	GolVec3 center;
	GolVec3 oldPosition;
	LegoFloat radius;

	LegoFloat x = p_item->m_modelRadius - p_item->m_unk0x28;

	if (x > 0.0f) {
		x = -(m_unk0xb4 / p_item->m_unk0x28 * x);
	}

	LegoFloat minX = p_item->m_modelRadius;
	minX += g_violetShoalTwo;
	minX = -minX;
	if (x > minX) {
		x = minX;
	}

	LegoFloat itemY = p_item->m_unk0x20;
	LegoFloat itemZ = p_item->m_unk0x24;
	LegoFloat scale = (m_unk0xb4 - x) / m_unk0xb4;
	GolModelEntity* entity = &p_item->m_entity;

	entity->VTable0x04(&oldPosition);

	p_position->m_x = x;
	p_position->m_y = scale * itemY;
	p_position->m_z = scale * itemZ;
	entity->VTable0x08(*p_position);

	entity->FUN_10027fe0(0, &center, &radius);

	p_position->m_x -= center.m_x - p_position->m_x;
	p_position->m_y -= center.m_y - p_position->m_y;
	p_position->m_z -= center.m_z - p_position->m_z;
	entity->VTable0x08(oldPosition);
}

// FUNCTION: LEGORACERS 0x0046d180
void VioletShoal0xc0::VTable0x60(LegoS32 p_index)
{
	Item0xd0* item = &m_unk0x7c[p_index];
	FUN_0046d010(item);

	GolVec3 position;
	FUN_0046d040(item, &position);
	item->m_entity.VTable0x08(position);
	item->m_model = item->m_entity.GetModel(0);
}

// FUNCTION: LEGORACERS 0x0046d1d0
void VioletShoal0xc0::VTable0x48(VisualState0x4* p_unk0x04, VisualState0x4* p_unk0x08)
{
	Item0xd0* item = m_unk0x7c;
	for (LegoS32 i = 0; i < m_unk0x60; i++, item++) {
		item->m_unk0xc8.m_unk0x00 = p_unk0x04->m_unk0x00;
		item->m_unk0xcc.m_unk0x00 = p_unk0x08->m_unk0x00;
	}
}

// FUNCTION: LEGORACERS 0x0046d210
void VioletShoal0xc0::VTable0x4c(VisualState0x4* p_unk0x04, VisualState0x4* p_unk0x08)
{
	Item0xd0* item = &m_unk0x7c[m_unk0x64];
	item->m_unk0xc8.m_unk0x00 = p_unk0x04->m_unk0x00;
	item->m_unk0xcc.m_unk0x00 = p_unk0x08->m_unk0x00;
}

// FUNCTION: LEGORACERS 0x0046d240
void VioletShoal0xc0::VTable0x40()
{
	Item0xd0* item = m_unk0x7c;
	for (LegoS32 i = 0; i < m_unk0x60; i++, item++) {
		if (item->m_entity.HasModel()) {
			GolVec3 position;
			FUN_0046d040(item, &position);
			item->m_entity.VTable0x08(position);
			item->m_entity.ClearVelocity();
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d2a0
void VioletShoal0xc0::VTable0x44(undefined4)
{
	m_unk0x74 = m_unk0x58->m_unk0x0c;
	m_unk0x70 = 1;

	Item0xd0* item = m_unk0x7c;
	for (LegoS32 i = 0; i < m_unk0x60; i++, item++) {
		if (item->m_entity.HasModel()) {
			GolVec3 currentPosition;
			item->m_entity.VTable0x04(&currentPosition);

			GolVec3 targetPosition;
			FUN_0046d040(item, &targetPosition);

			LegoFloat duration = static_cast<LegoFloat>(m_unk0x74);
			GolVec3 velocity;
			velocity.m_x = (targetPosition.m_x - currentPosition.m_x) / duration;
			velocity.m_y = (targetPosition.m_y - currentPosition.m_y) / duration;
			velocity.m_z = (targetPosition.m_z - currentPosition.m_z) / duration;
			item->m_entity.SetVelocity(velocity);
		}
	}
}

// FUNCTION: LEGORACERS 0x0046d350
LegoS32 VioletShoal0xc0::VTable0x54()
{
	GolModelBase* model = m_unk0x7c[0].m_model;
	Item0xd0* item = m_unk0x7c;

	for (LegoS32 i = 0; i < m_unk0x60 - 1; i++, item++) {
		GolModelEntity* entity = &item->m_entity;

		item->m_model = item[1].m_model;
		if (item[1].m_entity.HasModel()) {
			entity->VTable0x50(item->m_model, g_violetShoalMaxFloat);
			entity->CopyOrientationAndPositionFrom(item[1].m_entity);
			entity->InvalidateRadius();
			entity->SetPrimaryMaterialTable(item[1].m_entity.GetPrimaryMaterialTable());
			item->m_modelRadius = item[1].m_modelRadius;
			FUN_0046d010(item);
		}
		else {
			entity->VTable0x54();
		}
	}

	item->m_entity.VTable0x54();
	item->m_model = model;
	VTable0x44(0);
	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046d470
LegoS32 VioletShoal0xc0::VTable0x58()
{
	Item0xd0* item = &m_unk0x7c[m_unk0x60 - 1];
	GolModelBase* model = item->m_model;

	for (LegoS32 i = m_unk0x60 - 1; i > 0; i--, item--) {
		GolModelEntity* entity = &item->m_entity;
		GolModelBase* shiftedModel = item[-1].m_model;

		item->m_model = shiftedModel;
		if (item[-1].m_entity.HasModel()) {
			entity->VTable0x50(shiftedModel, g_violetShoalMaxFloat);
			entity->CopyOrientationAndPositionFrom(item[-1].m_entity);
			entity->InvalidateRadius();
			entity->SetPrimaryMaterialTable(item[-1].m_entity.GetPrimaryMaterialTable());
			item->m_modelRadius = item[-1].m_modelRadius;
			FUN_0046d010(item);
		}
		else {
			entity->VTable0x54();
		}
	}

	item->m_entity.VTable0x54();
	item->m_model = model;
	VTable0x44(0);
	return m_unk0x6c;
}

// FUNCTION: LEGORACERS 0x0046d5a0
void VioletShoal0xc0::SetParent(ObscureVantage0x58* p_parent)
{
	ObscureVantage0x58::SetParent(p_parent);
	FUN_0046cd30();
}

// FUNCTION: LEGORACERS 0x0046d5c0
ObscureVantage0x58* VioletShoal0xc0::VTable0x30(InputEventQueue::Event* p_event, undefined4 p_x, undefined4 p_y)
{
	if (!FUN_00472c40(p_x, p_y)) {
		return NULL;
	}

	if ((p_event->m_keyCode & InputDevice::c_sourceMask) != InputDevice::c_sourceMouse) {
		return NULL;
	}

	for (LegoS32 i = 0; i < m_unk0x60; i++) {
		if (FUN_00473a20(&m_unk0x7c[i].m_rect, p_x, p_y)) {
			LegoS32 index = FUN_0046c9a0(i + m_unk0x6c - m_unk0x64);
			VTable0x50(index);

			if (m_unk0x28) {
				m_unk0x28->VTable0x18(this, p_event, p_x, p_y);
			}

			return this;
		}
	}

	return NULL;
}

// STUB: LEGORACERS 0x0046d670
ObscureVantage0x58* VioletShoal0xc0::VTable0x38(Rect*, Rect*)
{
	STUB(0x0046d670);
	return NULL;
}

// FUNCTION: LEGORACERS 0x0046d780
undefined4 VioletShoal0xc0::VTable0x3c(undefined4 p_elapsed)
{
	undefined4 elapsed;

	if (m_unk0x70) {
		if (!m_unk0x74) {
			Item0xd0* item = m_unk0x7c;
			for (LegoS32 i = 0; i < m_unk0x60; i++, item++) {
				if (item->m_entity.HasModel()) {
					item->m_entity.ClearVelocity();
				}
			}

			m_unk0x70 = 0;
			VTable0x40();
		}

		elapsed = p_elapsed;
		if (p_elapsed > static_cast<undefined4>(m_unk0x74)) {
			elapsed = m_unk0x74;
		}
		m_unk0x74 -= elapsed;
	}
	else {
		elapsed = p_elapsed;
	}

	Item0xd0* item = m_unk0x7c;
	for (LegoS32 i = 0; i < m_unk0x60; i++, item++) {
		VTable0x5c(elapsed, &item->m_entity);
		item->m_entity.VTable0x10(elapsed);
	}

	return 0;
}
