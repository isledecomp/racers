#include "race/racedecalmanager.h"

#include "core/gol.h"
#include "decomp.h"
#include "gdbmodelindexarray.h"
#include "gdbvertexarray.h"
#include "golcollidableentity.h"
#include "golerror.h"
#include "golmaterial.h"
#include "golmodelbase.h"
#include "material/materialtable.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(RaceDecalManager, 0x0c)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail, 0x334)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::ModelEntry, 0x98)
DECOMP_SIZE_ASSERT(RaceDecalManager::Trail::ModelSlot, 0x9c)

// GLOBAL: LEGORACERS 0x004b4774
const LegoFloat g_raceDecalMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b4778
const LegoFloat g_raceDecalDefaultDepth = 15.0f;

extern LegoFloat g_minSoundPan;

// GLOBAL: LEGORACERS 0x004b477c
const LegoFloat g_raceDecalTrailOffsetZ = 6.0f;

// GLOBAL: LEGORACERS 0x004b4780
const LegoFloat g_raceDecalWeldThresholdScale = 0.25f;

// GLOBAL: LEGORACERS 0x004b4784
const LegoFloat g_raceDecalMinSampleDistance = 0.1f;

extern LegoFloat g_inv255;

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceDecalManager::Trail::DrawOpaque(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x00491ac0
RaceDecalManager::Trail::Trail()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00491b30
RaceDecalManager::Trail::~Trail()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00491b80
void RaceDecalManager::Trail::Destroy()
{
	LegoU32 i;

	for (i = 0; i < sizeOfArray(m_slots); i++) {
		GolModelBase* model = m_slots[i].m_model;
		if (model != NULL) {
			m_golExport->DestroyModel(model);
			m_slots[i].m_model = NULL;
		}
	}

	m_decal.Destroy();

	for (i = 0; i < sizeOfArray(m_slots); i++) {
		m_slots[i].m_entry.m_entity.ResetModelState();
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00491be0
void RaceDecalManager::Trail::Reset()
{
	m_alpha = 0xff;
	m_golExport = NULL;
	m_durationMs = 0;
	m_elapsedMs = 0;
	m_segmentMs = 0;
	m_slotIndex = 0;
	m_flags = 0;
	m_width = 0;
	m_anchorX = 0;
	m_anchorY = 0;
	m_anchorZ = 0;
	m_lastX = 0;
	m_lastY = 0;
	m_lastZ = 0;
	m_collidable = NULL;
	m_alphaScale = 1.0f;

	for (LegoU32 i = 0; i < sizeOfArray(m_slots); i++) {
		m_slots[i].m_model = NULL;
		m_slots[i].m_entry.m_vertexCount = 0;
		m_slots[i].m_entry.m_triangleCount = 0;
	}
}

// FUNCTION: LEGORACERS 0x00491c70
void RaceDecalManager::Trail::Initialize(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	GolCollidableEntity* p_params
)
{
	m_collidable = p_params;
	m_golExport = p_golExport;

	m_decal.Initialize(p_golExport, p_renderer, 12);
	m_decal.GetEntity().EnableFlagBit1();
	m_decal.m_depth = g_raceDecalDefaultDepth;

	ModelSlot* slot = m_slots;
	LegoU32 count = sizeOfArray(m_slots);
	do {
		slot->m_model = m_golExport->CreateModel();
		slot->m_model->Allocate(
			p_renderer,
			1,
			m_decal.m_vertexCapacity,
			m_decal.m_triangleCapacity,
			m_decal.m_triangleCapacity * 2 + 2,
			1
		);
		slot->m_entry.m_entity.SetPrimaryModel(slot->m_model, g_raceDecalMaxFloat);
		slot->m_entry.EnableFlagBit1();
		slot++;
		count--;
	} while (count);
}

// FUNCTION: LEGORACERS 0x00491d20
void RaceDecalManager::Trail::SetMaterialTable(MaterialTable* p_materialTable)
{
	m_decal.GetEntity().SetPrimaryMaterialTable(p_materialTable);

	for (LegoU32 i = 0; i < sizeOfArray(m_slots); i++) {
		m_slots[i].m_entry.m_entity.SetPrimaryMaterialTable(p_materialTable);
	}

	GolMaterial* material = static_cast<GolMaterial*>(p_materialTable->GetEntry(0));
	if (material->GetFlags() & GolMaterial::c_flagTransparent) {
		m_alphaScale = static_cast<LegoFloat>(material->GetDestBlend()) * g_inv255;
	}
	else {
		m_alphaScale = 1.0f;
	}
}

// FUNCTION: LEGORACERS 0x00491d80
LegoU8 RaceDecalManager::Trail::SetColor(const ColorRGBA* p_color)
{
	return m_decal.SetColor(p_color);
}

// FUNCTION: LEGORACERS 0x00491d90
void RaceDecalManager::Trail::Start(LegoU32 p_durationMs)
{
	m_flags = c_active | c_firstSample;
	m_durationMs = p_durationMs;

	LegoU32 value = p_durationMs >> 2;
	m_segmentMs = value;
	value <<= 2;
	if (value != p_durationMs) {
		m_durationMs = value;
	}

	LegoU32 zero = 0;
	m_alpha = 0xff;
	m_slotIndex = zero;
	m_elapsedMs = zero;
}

// FUNCTION: LEGORACERS 0x00491de0
void RaceDecalManager::Trail::StartFade(LegoU32 p_durationMs)
{
	LegoU8 flags = m_flags;
	m_elapsedMs = 0;
	flags |= c_fading;
	m_flags = flags;
	m_durationMs = p_durationMs;
}

// FUNCTION: LEGORACERS 0x00491e10
void RaceDecalManager::Trail::Stop()
{
	m_flags &= ~(c_active | c_fading);
}

// FUNCTION: LEGORACERS 0x00491e20
void RaceDecalManager::Trail::Update(LegoU32 p_elapsedMs)
{
	LegoU8 flags = m_flags;
	if (!(flags & c_active)) {
		return;
	}

	if (flags & c_fading) {
		m_elapsedMs += p_elapsedMs;
		p_elapsedMs = m_elapsedMs;
		LegoU32 durationMs = m_durationMs;
		if (p_elapsedMs >= durationMs) {
			m_flags = flags & ~(c_active | c_fading);
		}
		else {
			LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
			LegoFloat duration = static_cast<LegoFloat>(static_cast<LegoS32>(durationMs));
			LegoFloat value = 1.0f - (elapsed / duration);
			value *= 255.0f;
			value *= m_alphaScale;
			m_alpha = static_cast<LegoU32>(value);
		}
	}

	flags = m_flags;
	if (!(flags & c_active)) {
		return;
	}

	if (flags & c_fading) {
		return;
	}

	flags &= ~c_liveSegment;
	m_flags = flags;
	if (flags & c_samplePending) {
		m_decal.Project(m_collidable);
		m_flags |= c_liveSegment;
		WeldVertices();

		if (m_elapsedMs > m_segmentMs) {
			BakeSegment();

			GolVec3 position;
			m_decal.GetEntity().GetPosition(&position);
			m_slots[m_slotIndex].m_entry.m_entity.SetPosition(position);

			LegoU32 index = m_slotIndex;
			LegoU32 zero = 0;
			index++;
			m_slotIndex = index;
			if (index == sizeOfArray(m_slots)) {
				m_slotIndex = zero;
				m_flags |= c_slotsWrapped;
			}

			m_anchorY = m_lastY;
			m_anchorZ = m_lastZ;
			m_elapsedMs = zero;
			m_flags &= ~c_liveSegment;
			m_anchorX = m_lastX;
		}
	}

	m_flags &= ~c_samplePending;
}

// FUNCTION: LEGORACERS 0x00491fa0
void RaceDecalManager::Trail::AddSample(LegoU32 p_elapsedMs, GolVec3 p_position)
{
	m_lastX = p_position.m_x;
	m_lastY = p_position.m_y;
	m_lastZ = p_position.m_z;

	LegoU8 flags = m_flags;
	if (flags & c_firstSample) {
		m_anchorX = p_position.m_x;
		m_anchorY = p_position.m_y;
		m_anchorZ = p_position.m_z;
		m_flags = flags & ~c_firstSample;
		return;
	}

	m_elapsedMs += p_elapsedMs;

	LegoFloat distance = static_cast<LegoFloat>(sqrt(
		(p_position.m_z - m_anchorZ) * (p_position.m_z - m_anchorZ) +
		(p_position.m_y - m_anchorY) * (p_position.m_y - m_anchorY) +
		(p_position.m_x - m_anchorX) * (p_position.m_x - m_anchorX)
	));
	if (distance < g_raceDecalMinSampleDistance) {
		return;
	}

	GolVec3 direction;
	direction.m_x = (p_position.m_x - m_anchorX) / distance;
	direction.m_y = (p_position.m_y - m_anchorY) / distance;
	direction.m_z = (p_position.m_z - m_anchorZ) / distance;

	GolVec3 up;
	up.m_x = 0.0f;
	up.m_y = 0.0f;
	up.m_z = -1.0f;

	LegoFloat centerX = (p_position.m_x + m_anchorX) * 0.5f;
	LegoFloat centerY = (p_position.m_y + m_anchorY) * 0.5f;
	LegoFloat centerZ = (p_position.m_z + m_anchorZ) * 0.5f;

	p_position.m_x = 0.0f;
	p_position.m_y = 0.0f;
	p_position.m_z = g_minSoundPan * g_raceDecalTrailOffsetZ;
	centerX -= p_position.m_x;
	centerY -= p_position.m_y;
	centerZ -= p_position.m_z;

	Decal* field = &m_decal;
	field->m_width = m_width;
	field->m_length = distance;
	field->m_center.m_x = centerX;
	field->m_center.m_y = centerY;
	field->m_center.m_z = centerZ;
	field->SetOrientation(&up, &direction);
	m_flags |= c_samplePending;
}

// FUNCTION: LEGORACERS 0x00492180
void RaceDecalManager::Trail::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_flags & c_active) {
		LegoU32 alpha = m_alpha;
		if (alpha < 0xff) {
			p_renderer->SetAlphaOverride(alpha, 2);
		}

		if (m_flags & c_liveSegment) {
			m_decal.Draw(p_renderer);
		}

		LegoU32 count;
		count = (m_flags & c_slotsWrapped) ? sizeOfArray(m_slots) : m_slotIndex;

		if (count) {
			ModelSlot* slot = m_slots;
			do {
				p_renderer->DrawModelEntity(&slot->m_entry.m_entity);
				slot++;
				count--;
			} while (count);
		}

		if (m_alpha < 0xff) {
			p_renderer->ClearAlphaOverride();
		}
	}
}

// FUNCTION: LEGORACERS 0x00492220
void RaceDecalManager::Trail::BakeSegment()
{
	LegoU32 i;

	LegoU32 currentIndex = m_slotIndex;
	GolModelBase* sourceModel = m_decal.GetModel();
	m_slots[currentIndex].m_entry.m_vertexCount = m_decal.GetVertexCount();

	currentIndex = m_slotIndex;
	m_slots[currentIndex].m_entry.m_triangleCount = m_decal.GetTriangleCount();

	GdbVertexArray* sourceVertices;
	sourceModel->GetVertexArray(&sourceVertices);

	GolModelBase* destModel = m_slots[m_slotIndex].m_model;
	GdbVertexArray* destVertices;
	destModel->GetVertexArray(&destVertices);

	ColorRGBA color;
	GolVec2 texCoord;
	GolVec3 normal;
	GolVec3 position;
	for (i = 0; i < m_slots[m_slotIndex].m_entry.m_vertexCount; i++) {
		sourceVertices->GetPosition(i, &position);
		sourceVertices->GetTextureCoordinate(i, &texCoord);
		sourceVertices->GetNormal(i, &normal);
		sourceVertices->GetColor(i, &color);

		destVertices->SetPosition(i, position);
		destVertices->SetTextureCoordinate(i, texCoord);
		destVertices->SetNormal(i, normal);
		destVertices->SetColor(i, color);
	}

	sourceModel->AddFlagsWithBounds(0, FALSE);
	m_slots[m_slotIndex].m_model->AddFlagsWithBounds(1, FALSE);

	GdbModelIndexArrayBase* sourceIndexArrayBase;
	sourceModel->GetIndexArrayInto(&sourceIndexArrayBase);

	GdbModelIndexArrayBase* destIndexArrayBase;
	m_slots[m_slotIndex].m_model->GetIndexArrayInto(&destIndexArrayBase);

	GdbModelIndexArray* sourceIndexArray = static_cast<GdbModelIndexArray*>(sourceIndexArrayBase);
	GdbModelIndexArray* destIndexArray = static_cast<GdbModelIndexArray*>(destIndexArrayBase);
	LegoU32 index = 0;
	while (index < m_slots[m_slotIndex].m_entry.m_triangleCount) {
		LegoU32 offset = index * sizeof(GdbModelIndexArray::Indices);
		LegoU8* sourceIndexBytes = sourceIndexArray->GetIndexBytes() + offset;
		LegoU8* destIndexBytes = destIndexArray->GetIndexBytes() + offset;
		destIndexBytes[0] = sourceIndexBytes[0];
		destIndexBytes[1] = sourceIndexBytes[1];
		destIndexBytes[2] = sourceIndexBytes[2];
		index++;
	}

	sourceModel->AddFlags(0);
	m_slots[m_slotIndex].m_model->AddFlags(1);

	for (i = 0; i < sourceModel->GetGroupCount(); i++) {
		m_slots[m_slotIndex].m_model->GetMutableGroups()[i] = sourceModel->GetGroups()[i];
	}
}

// FUNCTION: LEGORACERS 0x00492470
void RaceDecalManager::Trail::WeldVertices()
{
	LegoU32 currentIndex = m_slotIndex;
	if (currentIndex == 0 && !(m_flags & c_slotsWrapped)) {
		return;
	}

	LegoFloat distanceThreshold = m_width;
	distanceThreshold *= g_raceDecalWeldThresholdScale;
	GolModelBase* sourceModel = m_decal.GetModel();
	LegoU32 updatedCount = 0;

	if (currentIndex > 0) {
		currentIndex--;
	}
	else {
		currentIndex = 2;
	}

	GolModelBase* previousModel = m_slots[currentIndex].m_model;
	GdbVertexArray* sourceVertices;
	GdbVertexArray* previousVertices;
	sourceModel->GetVertexArray(&sourceVertices);
	previousModel->GetVertexArray(&previousVertices);

	for (LegoU32 previousIndex = 0; previousIndex < m_slots[currentIndex].m_entry.m_vertexCount; previousIndex++) {
		GolVec3 previousPosition;
		previousVertices->GetPosition(previousIndex, &previousPosition);

		for (LegoU32 sourceIndex = 0; sourceIndex < m_decal.GetVertexCount(); sourceIndex++) {
			GolVec3 sourcePosition;
			sourceVertices->GetPosition(sourceIndex, &sourcePosition);

			LegoFloat dx = sourcePosition.m_x - previousPosition.m_x;
			LegoFloat dy = sourcePosition.m_y - previousPosition.m_y;
			LegoFloat dz = sourcePosition.m_z - previousPosition.m_z;
			LegoFloat distanceSquared = dx * dx + dy * dy + dz * dz;
			if (distanceSquared < distanceThreshold) {
				sourceVertices->SetPosition(sourceIndex, previousPosition);
				updatedCount++;
			}
		}
	}

	if (updatedCount) {
		sourceModel->AddFlagsWithBounds(1, FALSE);
	}
	else {
		sourceModel->AddFlagsWithBounds(0, FALSE);
	}

	previousModel->AddFlagsWithBounds(0, FALSE);
}

// FUNCTION: LEGORACERS 0x004925e0
RaceDecalManager::RaceDecalManager()
{
	m_items = NULL;
	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00492620
RaceDecalManager::~RaceDecalManager()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00492630
void RaceDecalManager::Destroy()
{
	if (m_items) {
		for (LegoU32 i = 0; i < m_count; i++) {
			m_items[i].Destroy();
		}

		Trail* items = m_items;
		if (items) {
			delete[] items;
		}

		m_items = NULL;
	}

	m_count = 0;
}

// FUNCTION: LEGORACERS 0x00492680
void RaceDecalManager::Initialize(
	GolD3DRenderDevice* p_renderer,
	GolExport* p_golExport,
	GolCollidableEntity* p_params,
	LegoU32 p_count
)
{
	if (m_items) {
		Destroy();
	}

	m_items = new Trail[p_count];
	if (m_items == NULL) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_count = p_count;
	for (LegoU32 i = 0; i < m_count; i++) {
		m_items[i].Initialize(p_renderer, p_golExport, p_params);
	}
}

// FUNCTION: LEGORACERS 0x004927c0
RaceDecalManager::Trail* RaceDecalManager::AcquireTrail(LegoU32 p_durationMs)
{
	LegoU32 i = 0;
	LegoU32 count = m_count;
	while (i < count && m_items[i].IsActive()) {
		i++;
	}

	if (i == count) {
		return NULL;
	}

	m_items[i].Start(p_durationMs);

	return &m_items[i];
}

// FUNCTION: LEGORACERS 0x00492820
void RaceDecalManager::ReleaseTrail(Trail* p_item, LegoU32 p_fadeMs)
{
	p_item->StartFade(p_fadeMs);
}

// FUNCTION: LEGORACERS 0x00492840
void RaceDecalManager::StopAll()
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		m_items[i].Stop();
		result = m_count;
	}
}

// FUNCTION: LEGORACERS 0x00492870
void RaceDecalManager::Update(LegoU32 p_elapsedMs)
{
	LegoU32 result = m_count;

	for (LegoU32 i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].Update(p_elapsedMs);
		}

		result = m_count;
	}
}

// FUNCTION: LEGORACERS 0x004928b0
LegoU32 RaceDecalManager::DrawOpaque(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		LegoU8 flags = m_items[i].GetFlags();
		if (flags & Trail::c_active) {
			m_items[i].DrawOpaque(p_renderer);
		}

		result = m_count;
	}

	return result;
}

// FUNCTION: LEGORACERS 0x004928f0
LegoU32 RaceDecalManager::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	LegoU32 i;
	LegoU32 result = m_count;

	for (i = 0; i < result; i++) {
		if (m_items[i].IsActive()) {
			m_items[i].DrawTransparent(p_renderer);
		}

		result = m_count;
	}

	return result;
}
