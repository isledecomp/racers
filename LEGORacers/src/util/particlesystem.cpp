#include "util/particlesystem.h"

#include "cmbmodelpart0x34.h"
#include "core/goldpexport.h"
#include "golerror.h"
#include "mabmaterialanimationitem0x18.h"
#include "mabmaterialanimationitem0x8.h"
#include "menu/widgets/menuselector.h"
#include "mesh/golmodelbase.h"
#include "util/particle.h"

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
	m_unk0x008 = 0;
	m_unk0x00c = 0;
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
	m_unk0x120 = 0;
	m_unk0x134 = 0;
	m_unk0x12c = 0;
	m_unk0x130 = 0;
	m_unk0x124 = 0;
	m_unk0x128 = 0;
	m_unk0x138 = 0;
	m_unk0x13c = 0;
}

// STUB: LEGORACERS 0x00412430
void ParticleSystem::FUN_00412430(
	GolExport* p_golExport,
	GolD3DRenderDevice* p_renderer,
	LegoU32 p_param3,
	LegoU32 p_param4
)
{
	// Most likely matches semantically, but the registers and some other details are still wrong

	if (m_flags & c_flagInitialized) {
		Destroy();
	}

	m_golExport = p_golExport;
	m_unk0x0a0 = 2 * p_param4;
	m_unk0x0a4 = p_param3;
	m_particleCapacity = p_param4;

	m_model = p_golExport->VTable0x14();

	m_model->VTable0x18(
		p_renderer,
		1,
		3 * m_unk0x0a0,
		m_unk0x0a0,
		m_unk0x0a4 + 2 * (m_unk0x0a4 + m_unk0x0a0 / 10) + 1,
		m_unk0x0a4
	);
	// LINE: LEGORACERS 0x004124b5
	m_modelEntity.VTable0x50(m_model, g_maxFloat);
	// LINE: LEGORACERS 0x004124c8
	m_particles = new Particle[m_particleCapacity];

	if (!m_particles) {
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
	m_unk0x120 = 0;
	m_unk0x134 = 0;
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
void ParticleSystem::FUN_00412a50(GolD3DRenderDevice*)
{
	STUB(0x00412a50);
}
