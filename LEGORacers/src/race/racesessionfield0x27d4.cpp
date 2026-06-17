#include "core/gol.h"
#include "decomp.h"
#include "golerror.h"
#include "mesh/gdbmodelindexarray0xc.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/golmodelbase.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceSessionField0x27d4, 0x0c)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item, 0x334)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::ModelEntry, 0x98)
DECOMP_SIZE_ASSERT(RaceSessionField0x27d4::Item::ModelSlot, 0x9c)

// GLOBAL: LEGORACERS 0x004b4774
const LegoFloat g_raceSessionField0x27d4MaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b4778
const LegoFloat g_raceSessionField0x27d4DefaultUnk0x10c = 15.0f;

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSessionField0x27d4::Item::FUN_004513d0(GolD3DRenderDevice*)
{
}

RaceSessionField0x27d4::Item::Item()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00491b30
RaceSessionField0x27d4::Item::~Item()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00491b80
void RaceSessionField0x27d4::Item::Destroy()
{
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_unk0x120); i++) {
		GolModelBase* model = m_unk0x120[i].m_model;
		if (model != NULL) {
			m_unk0x2f4->VTable0x48(model);
			m_unk0x120[i].m_model = NULL;
		}
	}

	m_unk0x004.FUN_004149f0();

	for (i = 0; i < sizeOfArray(m_unk0x120); i++) {
		m_unk0x120[i].m_entry.m_entity.VTable0x54();
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00491be0
void RaceSessionField0x27d4::Item::Reset()
{
	m_unk0x32c = 0xff;
	m_unk0x2f4 = NULL;
	m_unk0x314 = 0;
	m_unk0x31c = 0;
	m_unk0x318 = 0;
	m_unk0x320 = 0;
	m_flags0x328 = 0;
	m_unk0x324 = 0;
	m_unk0x2fc = 0;
	m_unk0x300 = 0;
	m_unk0x304 = 0;
	m_unk0x308 = 0;
	m_unk0x30c = 0;
	m_unk0x310 = 0;
	m_unk0x2f8 = NULL;
	m_unk0x330 = 1.0f;

	for (LegoU32 i = 0; i < sizeOfArray(m_unk0x120); i++) {
		m_unk0x120[i].m_model = NULL;
		m_unk0x120[i].m_entry.m_unk0x90 = 0;
		m_unk0x120[i].m_entry.m_unk0x94 = 0;
	}
}

void RaceSessionField0x27d4::Item::FUN_00491c70(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	Field0x004::Params* p_params
)
{
	Item* item = this;
	item->m_unk0x2f8 = p_params;
	item->m_unk0x2f4 = p_golExport;

	item->m_unk0x004.FUN_00414950(p_golExport, p_renderer, 12);
	item->m_unk0x004.GetUnk0x010().EnableFlagBit1();
	item->m_unk0x004.m_unk0x10c = g_raceSessionField0x27d4DefaultUnk0x10c;

	ModelSlot* slot = item->m_unk0x120;
	LegoU32 count = sizeOfArray(m_unk0x120);
	do {
		slot->m_model = item->m_unk0x2f4->VTable0x14();
		slot->m_model->VTable0x18(
			p_renderer,
			1,
			item->m_unk0x004.m_unk0x0a0,
			item->m_unk0x004.m_unk0x0a4,
			item->m_unk0x004.m_unk0x0a4 * 2 + 2,
			1
		);
		slot->m_entry.VTable0x50(slot->m_model, g_raceSessionField0x27d4MaxFloat);
		slot->m_entry.EnableFlagBit1();
		slot++;
		count--;
	} while (count);
}

// FUNCTION: LEGORACERS 0x00491d80
LegoU8 RaceSessionField0x27d4::Item::FUN_00491d80(const ColorRGBA* p_color)
{
	return m_unk0x004.FUN_00415bf0(p_color);
}

// FUNCTION: LEGORACERS 0x00491d90
void RaceSessionField0x27d4::Item::FUN_00491d90(LegoU32 p_unk0x04)
{
	m_flags0x328 = c_flags0x328Bit0 | c_flags0x328Bit4;
	m_unk0x314 = p_unk0x04;

	LegoU32 value = p_unk0x04 >> 2;
	m_unk0x318 = value;
	value <<= 2;
	if (value != p_unk0x04) {
		m_unk0x314 = value;
	}

	LegoU32 zero = 0;
	m_unk0x32c = 0xff;
	m_unk0x320 = zero;
	m_unk0x31c = zero;
}

// FUNCTION: LEGORACERS 0x00491de0
void RaceSessionField0x27d4::Item::FUN_00491de0(LegoU32 p_unk0x04)
{
	LegoU8 flags = m_flags0x328;
	m_unk0x31c = 0;
	flags |= c_flags0x328Bit1;
	m_flags0x328 = flags;
	m_unk0x314 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x00491e10
void RaceSessionField0x27d4::Item::FUN_00491e10()
{
	m_flags0x328 &= ~(c_flags0x328Bit0 | c_flags0x328Bit1);
}

// FUNCTION: LEGORACERS 0x00491e20
void RaceSessionField0x27d4::Item::FUN_00491e20(LegoU32 p_elapsedMs)
{
	LegoU8 flags = m_flags0x328;
	if (!(flags & c_flags0x328Bit0)) {
		return;
	}

	if (flags & c_flags0x328Bit1) {
		m_unk0x31c += p_elapsedMs;
		p_elapsedMs = m_unk0x31c;
		LegoU32 durationMs = m_unk0x314;
		if (p_elapsedMs >= durationMs) {
			m_flags0x328 = flags & ~(c_flags0x328Bit0 | c_flags0x328Bit1);
		}
		else {
			LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
			LegoFloat duration = static_cast<LegoFloat>(static_cast<LegoS32>(durationMs));
			LegoFloat value = 1.0f - (elapsed / duration);
			value *= 255.0f;
			value *= m_unk0x330;
			m_unk0x32c = static_cast<LegoU32>(value);
		}
	}

	flags = m_flags0x328;
	if (!(flags & c_flags0x328Bit0)) {
		return;
	}

	if (flags & c_flags0x328Bit1) {
		return;
	}

	flags &= ~c_flags0x328Bit3;
	m_flags0x328 = flags;
	if (flags & c_flags0x328Bit5) {
		m_unk0x004.FUN_00414a30(m_unk0x2f8);
		m_flags0x328 |= c_flags0x328Bit3;
		FUN_00492470();

		if (m_unk0x31c > m_unk0x318) {
			FUN_00492220();

			GolVec3 position;
			m_unk0x004.GetUnk0x010().VTable0x04(&position);
			m_unk0x120[m_unk0x320].m_entry.m_entity.VTable0x08(position);

			LegoU32 index = m_unk0x320;
			LegoU32 zero = 0;
			index++;
			m_unk0x320 = index;
			if (index == sizeOfArray(m_unk0x120)) {
				m_unk0x320 = zero;
				m_flags0x328 |= c_flags0x328Bit2;
			}

			m_unk0x300 = m_unk0x30c;
			m_unk0x304 = m_unk0x310;
			m_unk0x31c = zero;
			m_flags0x328 &= ~c_flags0x328Bit3;
			m_unk0x2fc = m_unk0x308;
		}
	}

	m_flags0x328 &= ~c_flags0x328Bit5;
}

// STUB: LEGORACERS 0x00492180
void RaceSessionField0x27d4::Item::FUN_00492180(GolD3DRenderDevice* p_renderer)
{
	if (m_flags0x328 & c_flags0x328Bit0) {
		LegoU32 alpha = m_unk0x32c;
		if (alpha < 0xff) {
			p_renderer->SetAlphaOverride(alpha, 2);
		}

		if (m_flags0x328 & c_flags0x328Bit3) {
			m_unk0x004.FUN_00415a40(p_renderer);
		}

		LegoU32 count;
		count = (m_flags0x328 & c_flags0x328Bit2) ? sizeOfArray(m_unk0x120) : m_unk0x320;

		if (count) {
			ModelSlot* slot = m_unk0x120;
			do {
				p_renderer->VTable0x94(&slot->m_entry.m_entity);
				slot++;
				count--;
			} while (count);
		}

		if (m_unk0x32c < 0xff) {
			p_renderer->ClearAlphaOverride();
		}
	}
}

// STUB: LEGORACERS 0x00492220
void RaceSessionField0x27d4::Item::FUN_00492220()
{
	LegoU32 i;

	LegoU32 currentIndex = m_unk0x320;
	GolModelBase* sourceModel = m_unk0x004.GetUnk0x004();
	m_unk0x120[currentIndex].m_entry.m_unk0x90 = m_unk0x004.GetUnk0x0b0();

	currentIndex = m_unk0x320;
	m_unk0x120[currentIndex].m_entry.m_unk0x94 = m_unk0x004.GetUnk0x0b4();

	GdbVertexArray0xc* sourceVertices;
	sourceModel->VTable0x28(&sourceVertices);

	GolModelBase* destModel = m_unk0x120[m_unk0x320].m_model;
	GdbVertexArray0xc* destVertices;
	destModel->VTable0x28(&destVertices);

	for (i = 0; i < m_unk0x120[m_unk0x320].m_entry.m_unk0x90; i++) {
		GolVec3 position;
		GolVec2 texCoord;
		GolVec3 normal;
		ColorRGBA color;

		sourceVertices->VTable0x14(i, &position);
		sourceVertices->VTable0x18(i, &texCoord);
		sourceVertices->VTable0x1c(i, &normal);
		sourceVertices->VTable0x20(i, &color);

		destVertices->VTable0x24(i, position);
		destVertices->VTable0x28(i, texCoord);
		destVertices->VTable0x2c(i, normal);
		destVertices->VTable0x30(i, color);
	}

	sourceModel->VTable0x2c(0, FALSE);
	m_unk0x120[m_unk0x320].m_model->VTable0x2c(1, FALSE);

	IGdbModelIndexArray0x8* sourceIndexArrayBase;
	sourceModel->VTable0x30(&sourceIndexArrayBase);

	IGdbModelIndexArray0x8* destIndexArrayBase;
	m_unk0x120[m_unk0x320].m_model->VTable0x30(&destIndexArrayBase);

	GdbModelIndexArray0xc* sourceIndexArray = static_cast<GdbModelIndexArray0xc*>(sourceIndexArrayBase);
	GdbModelIndexArray0xc* destIndexArray = static_cast<GdbModelIndexArray0xc*>(destIndexArrayBase);
	for (i = 0; i < m_unk0x120[m_unk0x320].m_entry.m_unk0x94; i++) {
		const GdbModelIndexArray0xc::Indices* sourceIndex = sourceIndexArray->GetIndex(i);
		GdbModelIndexArray0xc::Indices* destIndex = destIndexArray->GetMutableIndex(i);
		destIndex->m_a = sourceIndex->m_a;
		destIndex->m_b = sourceIndex->m_b;
		destIndex->m_c = sourceIndex->m_c;
	}

	sourceModel->VTable0x34(0);
	m_unk0x120[m_unk0x320].m_model->VTable0x34(1);

	for (i = 0; i < sourceModel->GetGroupCount(); i++) {
		m_unk0x120[m_unk0x320].m_model->GetMutableGroups()[i] = sourceModel->GetGroups()[i];
	}
}

// STUB: LEGORACERS 0x00492470
void RaceSessionField0x27d4::Item::FUN_00492470()
{
	LegoU32 currentIndex = m_unk0x320;
	if (currentIndex == 0 && !(m_flags0x328 & c_flags0x328Bit2)) {
		return;
	}

	LegoFloat distanceThreshold = m_unk0x324 * 0.25f;
	GolModelBase* sourceModel = m_unk0x004.GetUnk0x004();
	LegoU32 updatedCount = 0;

	if (currentIndex > 0) {
		currentIndex--;
	}
	else {
		currentIndex = 2;
	}

	GolModelBase* previousModel = m_unk0x120[currentIndex].m_model;
	GdbVertexArray0xc* sourceVertices;
	GdbVertexArray0xc* previousVertices;
	sourceModel->VTable0x28(&sourceVertices);
	previousModel->VTable0x28(&previousVertices);

	for (LegoU32 previousIndex = 0; previousIndex < m_unk0x120[currentIndex].m_entry.m_unk0x90; previousIndex++) {
		GolVec3 previousPosition;
		previousVertices->VTable0x14(previousIndex, &previousPosition);

		for (LegoU32 sourceIndex = 0; sourceIndex < m_unk0x004.GetUnk0x0b0(); sourceIndex++) {
			GolVec3 sourcePosition;
			sourceVertices->VTable0x14(sourceIndex, &sourcePosition);

			LegoFloat dx = sourcePosition.m_x - previousPosition.m_x;
			LegoFloat dy = sourcePosition.m_y - previousPosition.m_y;
			LegoFloat dz = sourcePosition.m_z - previousPosition.m_z;
			LegoFloat distanceSquared = dx * dx + dy * dy + dz * dz;
			if (distanceSquared < distanceThreshold) {
				sourceVertices->VTable0x24(sourceIndex, previousPosition);
				updatedCount++;
			}
		}
	}

	if (updatedCount) {
		sourceModel->VTable0x2c(1, FALSE);
		previousModel->VTable0x2c(0, FALSE);
	}
	else {
		sourceModel->VTable0x2c(0, FALSE);
		previousModel->VTable0x2c(0, FALSE);
	}
}

// FUNCTION: LEGORACERS 0x004925e0
RaceSessionField0x27d4::RaceSessionField0x27d4()
{
	m_items = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00492620
RaceSessionField0x27d4::~RaceSessionField0x27d4()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00492630
void RaceSessionField0x27d4::Destroy()
{
	if (m_items) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_items[i].Destroy();
		}

		Item* items = m_items;
		if (items) {
			delete[] items;
		}

		m_items = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00492680
void RaceSessionField0x27d4::FUN_00492680(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	Item::Field0x004::Params* p_params,
	LegoU32 p_count
)
{
	if (m_items) {
		Destroy();
	}

	m_items = new Item[p_count];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_count = p_count;
	for (LegoU32 i = 0; i < m_count; i++) {
		m_items[i].FUN_00491c70(p_renderer, p_golExport, p_params);
	}
}

// STUB: LEGORACERS 0x004927c0
RaceSessionField0x27d4::Item* RaceSessionField0x27d4::FUN_004927c0(LegoU32 p_unk0x04)
{
	LegoU32 i = 0;
	LegoU32 count = m_count;
	if (count) {
		LegoU8* flags = &m_items[0].m_flags0x328;
		do {
			if (!(*flags & Item::c_flags0x328Bit0)) {
				break;
			}

			i++;
			flags += sizeof(Item);
		} while (i < count);
	}

	if (i == count) {
		return NULL;
	}

	Item* items = m_items;
	items[i].FUN_00491d90(p_unk0x04);

	return &items[i];
}

// FUNCTION: LEGORACERS 0x00492820
void RaceSessionField0x27d4::FUN_00492820(Item* p_item, LegoU32 p_unk0x08)
{
	p_item->FUN_00491de0(p_unk0x08);
}

// FUNCTION: LEGORACERS 0x00492840
void RaceSessionField0x27d4::FUN_00492840()
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		m_items[i].FUN_00491e10();
		result = m_count;
	}
}

// FUNCTION: LEGORACERS 0x00492870
void RaceSessionField0x27d4::FUN_00492870(LegoU32 p_elapsedMs)
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].FUN_00491e20(p_elapsedMs);
		}

		result = m_count;
	}
}

// FUNCTION: LEGORACERS 0x004928b0
LegoU32 RaceSessionField0x27d4::FUN_004928b0(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_items[i].GetFlags0x328();
		if (flags & Item::c_flags0x328Bit0) {
			m_items[i].FUN_004513d0(p_renderer);
		}

		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004928f0
LegoU32 RaceSessionField0x27d4::FUN_004928f0(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].FUN_00492180(p_renderer);
		}

		result = m_count;
	}

	return result;
}
