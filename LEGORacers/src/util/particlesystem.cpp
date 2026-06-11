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
	m_unk0x000 = NULL;
	m_unk0x004 = NULL;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x0a0 = 0;
	m_unk0x0a4 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = NULL;
	m_unk0x0b8 = 0;
	m_unk0x0bc.m_x = 0.0f;
	m_unk0x0bc.m_y = 0.0f;
	m_unk0x0bc.m_z = 0.0f;
	m_unk0x0c8 = 0;
	m_unk0x0cc = NULL;
	m_unk0x0d0 = NULL;
	m_unk0x0d4 = NULL;
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

	if (m_unk0x0b8 & c_flagInitialized) {
		Destroy();
	}

	m_unk0x000 = p_golExport;
	m_unk0x0a0 = 2 * p_param4;
	m_unk0x0a4 = p_param3;
	m_unk0x0a8 = p_param4;

	m_unk0x004 = p_golExport->VTable0x14();

	m_unk0x004->VTable0x18(
		p_renderer,
		1,
		3 * m_unk0x0a0,
		m_unk0x0a0,
		m_unk0x0a4 + 2 * (m_unk0x0a4 + m_unk0x0a0 / 10) + 1,
		m_unk0x0a4
	);
	// LINE: LEGORACERS 0x004124b5
	m_unk0x010.VTable0x50(m_unk0x004, g_maxFloat);
	// LINE: LEGORACERS 0x004124c8
	m_unk0x0ac = new Particle[m_unk0x0a8];

	if (!m_unk0x0ac) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	m_unk0x0b8 = c_flagInitialized;

	FUN_00412970();
}

// FUNCTION: LEGORACERS 0x00412560
void ParticleSystem::Destroy()
{
	if (m_unk0x0ac) {
		delete[] m_unk0x0ac;
		m_unk0x0ac = NULL;
	}
	m_unk0x010.VTable0x54();
	if (m_unk0x000) {
		if (m_unk0x004) {
			m_unk0x000->VTable0x48(m_unk0x004);
			m_unk0x004 = NULL;
		}
		m_unk0x000 = NULL;
	}
	Reset();
}

// FUNCTION: LEGORACERS 0x00412760
Particle* ParticleSystem::FUN_00412760(GolVec3* p_param1, GolVec3* p_param2, LegoU32 p_param3)
{
	Particle* entity = FUN_00412a00();

	GolVec3 center, position;

	if (!m_unk0x0e8) {
		m_unk0x010.VTable0x08(*p_param1);
		center.m_x = 0.0f;
		center.m_y = 0.0f;
		center.m_z = 0.0f;
	}
	else {
		m_unk0x010.VTable0x04(&position);
		center.m_x = p_param1->m_x - position.m_x;
		center.m_y = p_param1->m_y - position.m_y;
		center.m_z = p_param1->m_z - position.m_z;
	}

	entity->SetCenter(center);
	entity->SetVelocity(*p_param2);

	entity->m_unk0x28 = 0;
	entity->m_unk0x2c = p_param3;
	entity->m_unk0x30 = NULL;

	m_unk0x0e8++;

	return entity;
}

// FUNCTION: LEGORACERS 0x00412820
void ParticleSystem::FUN_00412820()
{
	if (!m_unk0x0b4) {
		FUN_00412840();
	}
	else {
		m_unk0x0b8 |= c_flagPendingReset;
	}
}

// FUNCTION: LEGORACERS 0x00412840
void ParticleSystem::FUN_00412840()
{
	if (m_unk0x0b8 & c_flagActive) {
		FUN_00412970();
		m_unk0x0d0 = NULL;
		m_unk0x0d4 = NULL;
		m_unk0x0d8 = 0;
		m_unk0x0dc = 0;
		m_unk0x0e0 = 0;
		m_unk0x0e4 = 0;
		m_unk0x0b8 &= ~(c_flagActive | c_flagBit2 | c_flagBit3 | c_flagPendingReset);
	}
}

// FUNCTION: LEGORACERS 0x00412890
void ParticleSystem::FUN_00412890(LegoS32 p_param)
{
	if ((m_unk0x0b8 & c_flagInitialized) && (m_unk0x0b8 & c_flagActive)) {
		m_unk0x0b8 &= ~c_flagBit3;
		if (!m_unk0x0b4) {
			if (m_unk0x0b8 & c_flagPendingReset) {
				FUN_00412840();
			}
		}
		else {
			Particle *next, *other;
			other = NULL;

			for (Particle* current = m_unk0x0b4; current != NULL; current = next) {
				next = current->m_next;
				current->m_unk0x28 += p_param;
				if (current->m_unk0x28 > current->m_unk0x2c) {
					if (!other) {
						m_unk0x0b4 = next;
					}
					else {
						other->m_next = next;
					}
					current->m_next = m_unk0x0b0;
					current->m_unk0x30 = NULL;
					m_unk0x0b0 = current;
				}
				else {
					if (m_unk0x0d0) {
						LegoS32 elapsedMs = current->m_unk0x28;
						current->m_unk0x30 = m_unk0x0d0->FUN_00410560(elapsedMs, m_unk0x0cc, m_unk0x0c8);
					}
					else {
						current->m_unk0x30 = m_unk0x0d4;
					}

					current->FUN_00414600(p_param * 0.001f, &m_unk0x0bc);
					other = current;
				}
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00412970
void ParticleSystem::FUN_00412970()
{
	m_unk0x0b4 = NULL;
	m_unk0x0b0 = m_unk0x0ac;
	for (LegoU32 i = 0; i < m_unk0x0a8 - 1; i++) {
		m_unk0x0ac[i].m_next = &m_unk0x0ac[i + 1];
		m_unk0x0ac[i].m_unk0x30 = NULL;
	}
	m_unk0x0ac[m_unk0x0a8 - 1].m_next = NULL;
	m_unk0x0ac[m_unk0x0a8 - 1].m_unk0x30 = NULL;
}

// FUNCTION: LEGORACERS 0x00412a00
Particle* ParticleSystem::FUN_00412a00()
{
	Particle* maxEntry = m_unk0x0b0;
	Particle* current;

	if (maxEntry) {
		m_unk0x0b0 = maxEntry->m_next;
		maxEntry->m_next = m_unk0x0b4;
		m_unk0x0b4 = maxEntry;
		return maxEntry;
	}
	else {
		maxEntry = m_unk0x0b4;
		LegoU32 maxValue = maxEntry->m_unk0x28;
		for (current = maxEntry->m_next; current != NULL; current = current->m_next) {
			if (current->m_unk0x28 > maxValue) {
				maxEntry = current;
				maxValue = current->m_unk0x28;
			}
		}
		return maxEntry;
	}
}

// STUB: LEGORACERS 0x00412a50
void ParticleSystem::FUN_00412a50(GolD3DRenderDevice*)
{
	STUB(0x00412a50);
}
