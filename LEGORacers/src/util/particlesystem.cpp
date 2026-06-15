#include "util/particlesystem.h"

#include "camera/golcamera.h"
#include "cmbmodelpart0x34.h"
#include "core/goldpexport.h"
#include "golerror.h"
#include "goltransformbase.h"
#include "mabmaterialanimationitem0x18.h"
#include "mabmaterialanimationitem0x8.h"
#include "material/duskwindbananarelic0x24.h"
#include "menu/widgets/menuselector.h"
#include "mesh/gdbmodelindexarray0xc.h"
#include "mesh/gdbvertexarray0xc.h"
#include "mesh/golmodelbase.h"
#include "render/gold3drenderdevice.h"
#include "util/particle.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ParticleSystem, 0x140)

// GLOBAL: LEGORACERS 0x004af86c
const LegoFloat g_maxFloat = FLT_MAX;

// FUNCTION: LEGORACERS 0x00412360
ParticleSystem::ParticleSystem()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00412380
ParticleSystem::~ParticleSystem()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00412390
void ParticleSystem::Reset()
{
	m_golExport = NULL;
	m_model = NULL;
	m_vertices = NULL;
	m_indices = NULL;
	m_unk0x0a0 = 0;
	m_unk0x0a4 = 0;
	m_particleCapacity = 0;
	m_particles = NULL;
	m_flags = 0;
	m_acceleration.m_x = 0.0f;
	m_acceleration.m_y = 0.0f;
	m_acceleration.m_z = 0.0f;
	m_materialItemCount = 0;
	m_materialItems = NULL;
	m_materialAnimation = NULL;
	m_material = NULL;
	m_unk0x0d8 = 0;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
	m_materialCount = 0;
	m_groupCount = 0;
	m_vertexCount = 0;
	m_triangleCount = 0;
	m_firstBatchVertex = 0;
	m_firstBatchTriangle = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
}

// FUNCTION: LEGORACERS 0x00412430
void ParticleSystem::FUN_00412430(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	LegoU32 p_param3,
	LegoU32 p_param4
)
{
	if (m_flags & c_flagInitialized) {
		Destroy();
	}

	m_golExport = p_golExport;
	m_unk0x0a0 = 2 * p_param4;
	m_unk0x0a4 = p_param3;
	m_particleCapacity = p_param4;

	m_model = p_golExport->VTable0x14();
	LegoU32 vertexCapacity = m_unk0x0a0;
	LegoU32 triangleCapacity = m_unk0x0a4;
	LegoU32 groupCapacity = triangleCapacity + 2 * (triangleCapacity + vertexCapacity / 10) + 1;

	m_model->VTable0x18(p_renderer, 1, 3 * vertexCapacity, vertexCapacity, groupCapacity, triangleCapacity);
	// LINE: LEGORACERS 0x004124b5
	m_modelEntity.VTable0x50(m_model, g_maxFloat);
	// LINE: LEGORACERS 0x004124c8
	Particle* particles = new Particle[m_particleCapacity];
	m_particles = particles;

	if (!particles) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	m_flags = c_flagInitialized;

	ResetParticlePool();
}

// FUNCTION: LEGORACERS 0x00412560
void ParticleSystem::Destroy()
{
	if (m_particles) {
		delete[] m_particles;
		m_particles = NULL;
	}
	m_modelEntity.VTable0x54();
	if (m_golExport) {
		if (m_model) {
			m_golExport->VTable0x48(m_model);
			m_model = NULL;
		}
		m_golExport = NULL;
	}
	Reset();
}

// FUNCTION: LEGORACERS 0x004125c0
void ParticleSystem::ConfigureMaterialAnimation(
	MabMaterialAnimationItem0x18* p_animation,
	MabMaterialAnimationItem0x8* p_items,
	LegoU32 p_itemCount,
	LegoFloat p_unk0x1c,
	LegoFloat p_unk0x20,
	LegoFloat p_unk0x24,
	LegoFloat p_unk0x28,
	LegoFloat p_radius,
	const GolVec3* p_position
)
{
	m_materialAnimation = p_animation;
	m_materialItemCount = p_itemCount;
	m_materialItems = p_items;
	ConfigureCommon(p_unk0x1c, p_unk0x20, p_unk0x24, p_unk0x28, p_radius, p_position);
}

// FUNCTION: LEGORACERS 0x00412610
void ParticleSystem::ConfigureMaterial(
	DuskwindBananaRelic0x24* p_material,
	LegoFloat p_unk0x1c,
	LegoFloat p_unk0x20,
	LegoFloat p_unk0x24,
	LegoFloat p_unk0x28,
	LegoFloat p_radius,
	const GolVec3* p_position
)
{
	m_materialAnimation = NULL;
	m_materialItemCount = 0;
	m_materialItems = NULL;
	m_material = p_material;
	ConfigureCommon(p_unk0x1c, p_unk0x20, p_unk0x24, p_unk0x28, p_radius, p_position);
}

// FUNCTION: LEGORACERS 0x00412660
void ParticleSystem::ConfigureCommon(
	LegoFloat p_unk0x1c,
	LegoFloat p_unk0x20,
	LegoFloat p_unk0x24,
	LegoFloat p_unk0x28,
	LegoFloat p_radius,
	const GolVec3* p_position
)
{
	m_unk0x0d8 = p_unk0x1c;
	m_unk0x0dc = p_unk0x20;
	m_unk0x0e0 = p_unk0x24;

	if (m_unk0x0e0 == 0.0f && m_unk0x0e4 == 0.0f) {
		m_flags &= ~c_flagBit2;
	}
	else {
		m_flags |= c_flagBit2;
	}

	m_unk0x0e4 = p_unk0x28;

	if (m_unk0x0e0 == 0.0f && m_unk0x0e4 == 0.0f) {
		m_flags &= ~c_flagBit2;
	}
	else {
		m_flags |= c_flagBit2;
	}

	m_acceleration = *p_position;
	m_spawnedCount = 0;
	m_modelEntity.SetModelDistance(0, p_radius * p_radius);
	m_materialCount = 0;
	m_groupCount = 0;
	m_flags |= c_flagActive | c_flagBit3;
}

// FUNCTION: LEGORACERS 0x00412760
Particle* ParticleSystem::SpawnParticle(GolVec3* p_position, GolVec3* p_velocity, LegoU32 p_lifetimeMs)
{
	Particle* particle = AllocateParticle();

	GolVec3 center, position;

	if (!m_spawnedCount) {
		m_modelEntity.VTable0x08(*p_position);
		center.m_x = 0.0f;
		center.m_y = 0.0f;
		center.m_z = 0.0f;
	}
	else {
		m_modelEntity.VTable0x04(&position);
		center.m_x = p_position->m_x - position.m_x;
		center.m_y = p_position->m_y - position.m_y;
		center.m_z = p_position->m_z - position.m_z;
	}

	particle->SetCenter(center);
	particle->SetVelocity(*p_velocity);

	particle->m_ageMs = 0;
	particle->m_lifetimeMs = p_lifetimeMs;
	particle->m_material = NULL;

	m_spawnedCount++;

	return particle;
}

// FUNCTION: LEGORACERS 0x00412820
void ParticleSystem::RequestDeactivate()
{
	if (!m_activeList) {
		Deactivate();
	}
	else {
		m_flags |= c_flagPendingReset;
	}
}

// FUNCTION: LEGORACERS 0x00412840
void ParticleSystem::Deactivate()
{
	if (m_flags & c_flagActive) {
		ResetParticlePool();
		m_materialAnimation = NULL;
		m_material = NULL;
		m_unk0x0d8 = 0;
		m_unk0x0dc = 0;
		m_unk0x0e0 = 0;
		m_unk0x0e4 = 0;
		m_flags &= ~(c_flagActive | c_flagBit2 | c_flagBit3 | c_flagPendingReset);
	}
}

// FUNCTION: LEGORACERS 0x00412890
void ParticleSystem::Update(LegoS32 p_elapsedMs)
{
	if ((m_flags & c_flagInitialized) && (m_flags & c_flagActive)) {
		m_flags &= ~c_flagBit3;
		if (!m_activeList) {
			if (m_flags & c_flagPendingReset) {
				Deactivate();
			}
		}
		else {
			Particle *next, *other;
			other = NULL;

			for (Particle* current = m_activeList; current != NULL; current = next) {
				next = current->m_next;
				current->m_ageMs += p_elapsedMs;
				if (current->m_ageMs > current->m_lifetimeMs) {
					if (!other) {
						m_activeList = next;
					}
					else {
						other->m_next = next;
					}
					current->m_next = m_freeList;
					current->m_material = NULL;
					m_freeList = current;
				}
				else {
					if (m_materialAnimation) {
						LegoS32 ageMs = current->m_ageMs;
						current->m_material =
							m_materialAnimation->FUN_00410560(ageMs, m_materialItems, m_materialItemCount);
					}
					else {
						current->m_material = m_material;
					}

					current->Integrate(p_elapsedMs * 0.001f, &m_acceleration);
					other = current;
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00412970
void ParticleSystem::ResetParticlePool()
{
	m_activeList = NULL;
	m_freeList = m_particles;
	for (LegoU32 i = 0; i < m_particleCapacity - 1; i++) {
		m_particles[i].m_next = &m_particles[i + 1];
		m_particles[i].m_material = NULL;
	}
	m_particles[m_particleCapacity - 1].m_next = NULL;
	m_particles[m_particleCapacity - 1].m_material = NULL;
}

// FUNCTION: LEGORACERS 0x00412a00
Particle* ParticleSystem::AllocateParticle()
{
	Particle* particle = m_freeList;
	Particle* current;

	if (particle) {
		m_freeList = particle->m_next;
		particle->m_next = m_activeList;
		m_activeList = particle;
		return particle;
	}
	else {
		particle = m_activeList;
		LegoU32 maxAge = particle->m_ageMs;
		for (current = particle->m_next; current != NULL; current = current->m_next) {
			if (current->m_ageMs > maxAge) {
				particle = current;
				maxAge = current->m_ageMs;
			}
		}
		return particle;
	}
}

// STUB: LEGORACERS 0x00412a50
void ParticleSystem::FUN_00412a50(GolD3DRenderDevice* p_renderer)
{
	LegoU32 flags = m_flags;

	if (flags & c_flagInitialized) {
		if (flags & c_flagActive) {
			if (m_activeList) {
				if (flags & c_flagBit3) {
					Update(0);
				}

				m_flags |= c_flagBit3;

				GolCamera* camera = p_renderer->GetUnk0x0c();
				GolVec3 center;
				GolVec3 cameraPosition;
				m_modelEntity.VTable0x04(&center);
				camera->GetTransform()->GetPosition(&cameraPosition);

				LegoFloat deltaX = cameraPosition.m_x - center.m_x;
				LegoFloat deltaY = cameraPosition.m_y - center.m_y;
				LegoFloat deltaZ = cameraPosition.m_z - center.m_z;
				LegoFloat distanceSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
				if (distanceSquared <= m_modelEntity.GetModelDistance(0)) {
					GolTransformBase* cameraTransform = camera->GetTransform();
					cameraTransform->GetUp(&m_cameraUp);
					cameraTransform->GetForward(&m_cameraForward);

					LegoFloat scale = m_unk0x0d8;
					m_scaledCameraUp.m_x = scale * m_cameraUp.m_x;
					m_scaledCameraUp.m_y = scale * m_cameraUp.m_y;
					m_scaledCameraUp.m_z = scale * m_cameraUp.m_z;

					scale = m_unk0x0dc;
					m_scaledCameraForward.m_x = scale * m_cameraForward.m_x;
					m_scaledCameraForward.m_y = scale * m_cameraForward.m_y;
					m_scaledCameraForward.m_z = scale * m_cameraForward.m_z;

					m_materialCount = 0;
					m_groupCount = 0;
					m_vertexCount = 0;
					m_triangleCount = 0;
					m_firstBatchVertex = 0;
					m_firstBatchTriangle = 0;
					m_batchVertexCount = 0;
					m_batchTriangleCount = 0;

					m_model->VTable0x28(&m_vertices);

					IGdbModelIndexArray0x8* indexArray;
					m_model->VTable0x30(&indexArray);
					m_indices = static_cast<GdbModelIndexArray0xc*>(indexArray)->GetMutableIndices();

					Particle* particle = m_activeList;
					while (particle) {
						DuskwindBananaRelic0x24* material = particle->m_material;
						Particle* next = particle->m_next;
						if (material) {
							FUN_00412c60(material);
							do {
								if (particle->m_material == material) {
									FUN_00412ce0(particle);
									particle->m_material = NULL;
								}

								particle = particle->m_next;
							} while (particle);

							particle = next;
						}
						else {
							particle = next;
						}
					}

					if (m_batchTriangleCount) {
						FUN_00413090();
					}

					m_model->GetMutableGroups()[m_groupCount] = 0xc0000000;
					m_model->SetDirty(TRUE);
					m_model->VTable0x34(0);
					m_model->VTable0x2c(0, FALSE);
					p_renderer->VTable0x94(&m_modelEntity);
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00412c60
void ParticleSystem::FUN_00412c60(DuskwindBananaRelic0x24* p_material)
{
	if (m_batchTriangleCount) {
		FUN_00413090();
	}

	m_model->GetMaterialTable()->SetPosition(m_materialCount, p_material);
	::memcpy(&m_particleColor, &p_material->GetColor0x0c(), sizeof(m_particleColor));

	LegoU32 materialCount = m_materialCount;
	LegoU32 groupCount = m_groupCount++;
	m_materialCount++;

	GolModelBase* model = m_model;
	model->GetMutableGroups()[groupCount] = 0x80000000;
	model->GetMutableGroups()[groupCount] |= materialCount & 0x00ffffff;
	model->SetDirty(TRUE);
}

// FUNCTION: LEGORACERS 0x00412ce0
void ParticleSystem::FUN_00412ce0(Particle* p_particle)
{
	if (m_batchTriangleCount + 1 >= 10) {
		if (m_triangleCount + 1 >= m_unk0x0a0) {
			return;
		}

		FUN_00413090();
	}

	if (m_flags & c_flagBit2) {
		LegoFloat ageMs = static_cast<LegoFloat>((LegoS32) p_particle->m_ageMs);
		LegoFloat lifetimeMs = static_cast<LegoFloat>((LegoS32) p_particle->m_lifetimeMs);
		LegoFloat amount = ageMs / lifetimeMs;
		LegoFloat upScale = m_unk0x0e0 * amount + m_unk0x0d8;
		LegoFloat forwardScale = m_unk0x0e4 * amount + m_unk0x0dc;
		if (upScale <= 0.0f || forwardScale <= 0.0f) {
			return;
		}

		m_scaledCameraUp.m_x = upScale * m_cameraUp.m_x;
		m_scaledCameraUp.m_y = m_cameraUp.m_y * upScale;
		m_scaledCameraUp.m_z = m_cameraUp.m_z * upScale;
		m_scaledCameraForward.m_x = forwardScale * m_cameraForward.m_x;
		m_scaledCameraForward.m_y = m_cameraForward.m_y * forwardScale;
		m_scaledCameraForward.m_z = m_cameraForward.m_z * forwardScale;
	}

	GolVec3 position;
	p_particle->FUN_100286d0(&position);

	position.m_x -= m_scaledCameraUp.m_x * 0.5f + m_scaledCameraForward.m_x * 0.5f;
	position.m_y -= m_scaledCameraUp.m_y * 0.5f + m_scaledCameraForward.m_y * 0.5f;
	position.m_z -= m_scaledCameraUp.m_z * 0.5f + m_scaledCameraForward.m_z * 0.5f;

	GolVec2 texCoord;
	texCoord.m_x = 0.01f;
	texCoord.m_y = 0.01f;
	m_vertices->VTable0x24(m_vertexCount, position);
	m_vertices->VTable0x30(m_vertexCount, m_particleColor);
	m_vertices->VTable0x28(m_vertexCount++, texCoord);

	position.m_x += m_scaledCameraUp.m_x;
	position.m_y += m_scaledCameraUp.m_y;
	position.m_z += m_scaledCameraUp.m_z;
	texCoord.m_x = 0.98f;
	m_vertices->VTable0x24(m_vertexCount, position);
	m_vertices->VTable0x30(m_vertexCount, m_particleColor);
	m_vertices->VTable0x28(m_vertexCount++, texCoord);

	position.m_x += m_scaledCameraForward.m_x;
	position.m_y += m_scaledCameraForward.m_y;
	position.m_z += m_scaledCameraForward.m_z;
	texCoord.m_y = 0.98f;
	m_vertices->VTable0x24(m_vertexCount, position);
	m_vertices->VTable0x30(m_vertexCount, m_particleColor);
	m_vertices->VTable0x28(m_vertexCount++, texCoord);

	position.m_x -= m_scaledCameraUp.m_x;
	position.m_y -= m_scaledCameraUp.m_y;
	position.m_z -= m_scaledCameraUp.m_z;
	texCoord.m_x = 0.01f;
	m_vertices->VTable0x24(m_vertexCount, position);
	m_vertices->VTable0x30(m_vertexCount, m_particleColor);
	m_vertices->VTable0x28(m_vertexCount++, texCoord);

	GdbModelIndexArray0xc::Indices* indices = &m_indices[m_triangleCount++];
	indices->m_c = m_batchVertexCount;
	indices->m_b = m_batchVertexCount + 1;
	indices->m_a = m_batchVertexCount + 2;

	indices = &m_indices[m_triangleCount++];
	indices->m_c = m_batchVertexCount;
	indices->m_b = m_batchVertexCount + 2;
	indices->m_a = m_batchVertexCount + 3;

	m_batchVertexCount += 4;
	m_batchTriangleCount += 2;
}

// FUNCTION: LEGORACERS 0x00413090
LegoU32 ParticleSystem::FUN_00413090()
{
	LegoU32 groupCount = m_groupCount;
	LegoU32 batchVertexCount = m_batchVertexCount;
	LegoU32 firstBatchVertex = m_firstBatchVertex;
	m_groupCount = groupCount + 1;

	GolModelBase* model = m_model;
	model->GetMutableGroups()[groupCount] = 0;
	model->GetMutableGroups()[groupCount] |= ((batchVertexCount + 0xffff) << 16) & 0x003f0000;
	model->GetMutableGroups()[groupCount] |= firstBatchVertex & 0xffff;
	model->SetDirty(TRUE);

	LegoU32 groupCount2 = m_groupCount;
	LegoU32 batchTriangleCount = m_batchTriangleCount;
	LegoU32 firstBatchTriangle = m_firstBatchTriangle;
	m_groupCount = groupCount2 + 1;
	model = m_model;
	model->GetMutableGroups()[groupCount2] = 0x20000000;
	model->GetMutableGroups()[groupCount2] |= (batchTriangleCount & 0x7f) << 16;
	model->GetMutableGroups()[groupCount2] |= firstBatchTriangle & 0xffff;
	model->SetDirty(TRUE);

	LegoU32 triangleCount = m_triangleCount;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
	LegoU32 vertexCount = m_vertexCount;
	m_firstBatchVertex = vertexCount;
	m_firstBatchTriangle = triangleCount;

	return triangleCount;
}
