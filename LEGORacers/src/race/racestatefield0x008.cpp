#include "audio/soundnode.h"
#include "audio/streamingsoundinstance.h"
#include "race/racecameracontroller.h"
#include "race/racestate.h"
#include "render/golrenderdevice.h"
#include "scene/golbillboard.h"
#include "world/golworlddatabase.h"

#include <float.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008, 0x199c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::Field0x050::Entry, 0x14)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::ActionSetup, 0x14)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::ActionTarget, 0x1c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::ActionBase, 0x18)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::Action, 0x2c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::MagnetAction, 0x84)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::MissileAction, 0x224)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::BarrelAction, 0x17c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::CannonAction, 0xe8)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::TetherAction, 0x290)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::LightningAction, 0x24c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::Field0x1894Action, 0x190)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::EffectActionBase, 0x2c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::CurseAction, 0x68)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::TurboAction, 0x34)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x008::WarpAction, 0xe4)

extern const LegoFloat g_unk0x004b0958;
extern const LegoFloat g_unk0x004b095c;

// GLOBAL: LEGORACERS 0x004b03f4
extern const LegoFloat g_unk0x004b03f4 = 6.0f;

// GLOBAL: LEGORACERS 0x004b1378
extern const LegoFloat g_unk0x004b1378 = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b14dc
extern const LegoFloat g_unk0x004b14dc = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b1508
extern const LegoFloat g_unk0x004b1508 = 15.0f;

// GLOBAL: LEGORACERS 0x004b165c
extern const LegoFloat g_unk0x004b165c = 30.0f;

// GLOBAL: LEGORACERS 0x004b1660
extern const LegoFloat g_unk0x004b1660 = 300.0f;

// GLOBAL: LEGORACERS 0x004b1840
extern const LegoFloat g_unk0x004b1840 = 100.0f;

// GLOBAL: LEGORACERS 0x004b1844
extern const LegoFloat g_unk0x004b1844 = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1848
extern const LegoFloat g_unk0x004b1848 = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b184c
extern const LegoFloat g_unk0x004b184c = 0.94999999f;

// GLOBAL: LEGORACERS 0x004b1850
extern const LegoFloat g_unk0x004b1850 = 100.0f;

// GLOBAL: LEGORACERS 0x004b1854
extern const LegoFloat g_unk0x004b1854 = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1858
extern const LegoFloat g_unk0x004b1858 = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b185c
extern const LegoFloat g_unk0x004b185c = 100.0f;

// GLOBAL: LEGORACERS 0x004b1860
extern const LegoFloat g_unk0x004b1860 = 62500.0f;

// GLOBAL: LEGORACERS 0x004b1864
extern const LegoFloat g_unk0x004b1864 = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1868
extern const LegoFloat g_unk0x004b1868 = 0.93000001f;

// GLOBAL: LEGORACERS 0x004b186c
extern const LegoFloat g_unk0x004b186c = 0.60000002f;

// GLOBAL: LEGORACERS 0x004b1a6c
extern const LegoFloat g_unk0x004b1a6c = 30.0f;

// FUNCTION: LEGORACERS 0x00451a50
LegoU32 RaceState::Racer::Field0x008::CannonAction::FUN_00451a50(ActionSetup* p_unk0x04)
{
	m_unk0x004 = 2;
	m_racer = p_unk0x04->m_racer;
	m_unk0x028 = p_unk0x04->m_unk0x04;
	m_unk0x02c = p_unk0x04->m_unk0x08;
	m_unk0x008 = p_unk0x04->m_unk0x10;

	ActionTarget* target = p_unk0x04->m_unk0x0c;
	if (target) {
		m_materialName = target->m_materialName;
	}

	GolRenderDevice* renderDevice = m_owner->m_renderDevice;
	const LegoChar* materialName = m_materialName;
	DuskwindBananaRelic0x24* material;
	if (materialName && materialName[0]) {
		material = renderDevice->FindMaterialByName(materialName);
	}
	else {
		material = renderDevice->FindMaterialByName("cannon");
	}

	return m_unk0x0d8->VTable0x4c(material, 5.0f, 5.0f, g_unk0x004b1378);
}

// FUNCTION: LEGORACERS 0x00452550
void RaceState::Racer::Field0x008::CurseAction::FUN_00452550(
	Racer* p_racer,
	GolAnimatedEntity* p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10,
	ActionTarget* p_unk0x14
)
{
	m_unk0x030 = m_owner->FUN_0045b9e0();
	if (!m_unk0x030) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x034 = m_owner->FUN_0045b9e0();
	if (!m_unk0x034) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x038 = m_owner->FUN_0045b9e0();
	if (!m_unk0x038) {
		m_unk0x004 = 6;
		return;
	}

	m_racer = p_racer;

	m_unk0x030->FUN_0040d550(
		p_unk0x08->GetModel(0),
		p_unk0x08->VTable0x58(0),
		p_unk0x08->GetModelPart(0),
		p_unk0x08->GetModelDistance(0)
	);
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x08->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x08->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x08->GetModelPart(i);
			m_unk0x030->FUN_10023940(model, p_unk0x08->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x030->SetFlags(m_unk0x030->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x030->FUN_0040dad0(0);

	m_unk0x034->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x0c->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x0c->GetModelPart(i);
			m_unk0x034->FUN_10023940(model, p_unk0x0c->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x034->SetFlags(m_unk0x034->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x034->FUN_0040dad0(0);
	m_unk0x034->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x034->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x034->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x034->FUN_00411730(p_unk0x0c->FUN_004116f0());

	m_unk0x038->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x10->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x10->GetModelPart(i);
			m_unk0x038->FUN_10023940(model, p_unk0x10->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x038->SetFlags(m_unk0x038->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x038->FUN_0040dad0(0);
	m_unk0x038->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x038->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x038->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x038->FUN_00411730(p_unk0x10->FUN_004116f0());

	if (!m_racer) {
		GolVec3 position = p_unk0x14->m_unk0x00;
		GolVec3 direction = p_unk0x14->m_unk0x0c;

		GolWorldEntity* target = &m_unk0x03c;
		target->VTable0x08(position);
		m_unk0x03c.FUN_10026fa0(10.0f);

		m_unk0x034->VTable0x08(position);
		m_unk0x038->VTable0x08(position);

		LegoFloat positionZ = position.m_z;
		positionZ += 13.0f;
		position.m_z = positionZ;
		m_unk0x030->VTable0x08(position);

		direction.m_x = -direction.m_x;
		direction.m_y = -direction.m_y;
		direction.m_z = -direction.m_z;

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = 1.0f;

		GolVec3 forward;
		forward.m_x = -direction.m_y;
		forward.m_y = direction.m_x;
		forward.m_z = 0.0f;
		m_unk0x030->VTable0x40(forward, up);

		m_unk0x034->CopyOrientationFrom(*m_unk0x030);
		m_unk0x038->CopyOrientationFrom(*m_unk0x030);
	}

	m_unk0x004 = 2;
	m_unk0x008 = 0;
}

// FUNCTION: LEGORACERS 0x00452f60
LegoU32 RaceState::Racer::Field0x008::BarrelAction::FUN_00452f60(Racer* p_racer, Racer* p_unk0x08)
{
	m_racer = p_racer;
	LegoU32 result = 0;
	m_unk0x174 = p_unk0x08;
	m_unk0x004 = 2;
	m_unk0x008 = result;
	m_unk0x178 = result;
	return result;
}

// FUNCTION: LEGORACERS 0x00453de0
LegoU32 RaceState::Racer::Field0x008::TetherAction::FUN_00453de0(
	GolModelEntity* p_unk0x04,
	Racer* p_racer,
	Racer* p_unk0x0c,
	Field0x050::Entry* p_unk0x10,
	MabMaterialAnimationItem0x18* p_unk0x14,
	LegoU32 p_unk0x18
)
{
	m_unk0x268 = p_unk0x04;
	m_racer = p_racer;
	m_unk0x028 = p_unk0x0c;
	m_unk0x004 = 2;
	m_unk0x02c = p_unk0x10;
	m_unk0x008 = p_unk0x18;

	m_unk0x274.FUN_004103c0(*p_unk0x14);
	m_unk0x274.FUN_00410470();
	m_unk0x274.FUN_00410480();
	m_unk0x274.FUN_10025da0(&m_owner->m_unk0x008, m_unk0x28c, FALSE);
	m_unk0x274.FUN_004104c0(0, m_owner->m_unk0x018, m_owner->m_unk0x01c);

	return m_unk0x270
		->FUN_10029e90(&m_owner->m_unk0x008, m_unk0x28c, g_unk0x004b1508, g_unk0x004b1508, g_unk0x004b14dc);
}

// FUNCTION: LEGORACERS 0x00454cb0
void RaceState::Racer::Field0x008::LightningAction::FUN_00454cb0(Racer* p_racer, ActionTarget* p_unk0x08)
{
	m_unk0x004 = 2;
	m_unk0x008 = 500;
	m_racer = p_racer;
	m_unk0x028 = 0;

	if (p_racer) {
		m_positionSource = &p_racer->m_unk0xe08;
	}
	else {
		m_positionSource = p_unk0x08->m_positionSource;
	}

	m_unk0x22c = 0;
	if (m_unk0x238) {
		m_unk0x238->VTable0x04(TRUE);
	}
	m_unk0x234 = 0;
}

// FUNCTION: LEGORACERS 0x00455830
void RaceState::Racer::Field0x008::MagnetAction::FUN_00455830(
	Racer* p_racer,
	GolAnimatedEntity* p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10
)
{
	m_unk0x03c = m_owner->FUN_0045b9e0();
	if (!m_unk0x03c) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x040 = m_owner->FUN_0045b9e0();
	if (!m_unk0x040) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x044 = m_owner->FUN_0045b9e0();
	if (!m_unk0x044) {
		m_unk0x004 = 6;
		return;
	}

	m_racer = p_racer;
	m_unk0x004 = 2;
	m_unk0x008 = 20000;

	m_unk0x03c->FUN_0040d550(
		p_unk0x08->GetModel(0),
		p_unk0x08->VTable0x58(0),
		p_unk0x08->GetModelPart(0),
		p_unk0x08->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x08->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x08->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x08->GetModelPart(i);
			m_unk0x03c->FUN_10023940(model, p_unk0x08->VTable0x58(i), modelPart, modelDistance);
		}
	}

	m_unk0x040->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x0c->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x0c->GetModelPart(i);
			m_unk0x040->FUN_10023940(model, p_unk0x0c->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x040->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x040->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x040->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x040->FUN_00411730(p_unk0x0c->FUN_004116f0());

	m_unk0x044->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model) {
			LegoFloat modelDistance = p_unk0x10->GetModelDistance(i);
			CmbModelPart0x34* modelPart = p_unk0x10->GetModelPart(i);
			m_unk0x044->FUN_10023940(model, p_unk0x10->VTable0x58(i), modelPart, modelDistance);
		}
	}
	m_unk0x044->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x044->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x044->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x044->FUN_00411730(p_unk0x10->FUN_004116f0());
}

// FUNCTION: LEGORACERS 0x00456560
void RaceState::Racer::Field0x008::MissileAction::FUN_00456560(
	GolAnimatedEntity* p_unk0x04,
	GolAnimatedEntity* p_unk0x08,
	Racer* p_racer,
	LegoU32 p_unk0x10
)
{
	m_unk0x124 = p_unk0x08;
	m_unk0x004 = 2;
	m_unk0x008 = 3000;
	m_unk0x220 = p_unk0x10;
	m_racer = p_racer;
	m_unk0x028 = 0;

	GolAnimatedEntity* projectile = &m_unk0x128;
	projectile->FUN_0040d550(
		p_unk0x04->GetModel(0),
		p_unk0x04->VTable0x58(0),
		p_unk0x04->GetModelPart(0),
		p_unk0x04->GetModelDistance(0)
	);

	SoundVector position;
	Racer::Field0x018* racerEntities = &m_racer->m_unk0x018;
	racerEntities->m_unk0x044->VTable0x04(&position);
	projectile->VTable0x08(position);

	m_racer->m_unk0x3e8.m_unk0x13c->CopyOrientationTo(&projectile->GetOrientation());
	projectile->SetFlags(projectile->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	projectile->FUN_0040dad0(p_unk0x10);
	projectile->SetFlags(projectile->GetFlags() & ~GolAnimatedEntity::c_flagLoopCurrentPart);

	m_unk0x010->FUN_00443b80(0x33, &position, g_unk0x004b165c, g_unk0x004b1660, 1.0f, 1.0f);
}

// FUNCTION: LEGORACERS 0x00457230
void RaceState::Racer::Field0x008::Field0x1894Action::FUN_00457230(Racer* p_racer)
{
	m_unk0x004 = 2;
	m_racer = p_racer;
	m_unk0x008 = 0;
}

// FUNCTION: LEGORACERS 0x0045a950
void RaceState::Racer::Field0x008::FUN_0045a950(Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
	case 0:
		FUN_0045aa30(p_racer, 0);
		return;
	case 1:
		FUN_0045ab50(p_racer, 1);
		return;
	case 2:
		FUN_0045ac80(p_racer, 2);
		return;
	case 3:
		FUN_0045af80(p_racer, 3);
		return;
	default:
		return;
	}
}

// FUNCTION: LEGORACERS 0x0045a9b0
void RaceState::Racer::Field0x008::FUN_0045a9b0(Racer* p_racer, LegoU32 p_unk0x08)
{
	switch (p_unk0x08) {
	case 0:
		FUN_0045ace0(p_racer, 0);
		break;
	case 1:
		FUN_0045ad30(p_racer, 1);
		break;
	case 2:
		if (25 - m_unk0x187c >= 3) {
			FUN_0045adf0(p_racer, 2);
		}
		break;
	case 3:
		if (25 - m_unk0x187c >= 3) {
			FUN_0045aeb0(p_racer, 3);
		}
		break;
	}
}

// FUNCTION: LEGORACERS 0x0045aa30
LegoU32 RaceState::Racer::Field0x008::FUN_0045aa30(Racer* p_racer, LegoU32 p_unk0x08)
{
	ActionSetup setup;
	setup.m_racer = p_racer;
	setup.m_unk0x08 = NULL;
	setup.m_unk0x04 = NULL;

	if (!m_unk0x1998) {
		GolVec3 position;
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

		GolVec3 direction;
		p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

		if (p_racer->m_unk0xd08 != 2) {
			setup.m_unk0x08 =
				m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}

		if (!setup.m_unk0x08) {
			setup.m_unk0x04 =
				m_unk0x074->FUN_0043ca60(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b1848);
		}
	}

	setup.m_unk0x0c = m_unk0x1998;
	setup.m_unk0x10 = 0;

	CannonAction* action = m_unk0x088;
	if (!action) {
		action = static_cast<CannonAction*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x088 = static_cast<CannonAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	LegoU32 result = action->FUN_00451a50(&setup);
	action->m_unk0x014 = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ab50
LegoU32 RaceState::Racer::Field0x008::FUN_0045ab50(Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x050::Entry* entry = NULL;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);

	Racer* target = m_unk0x074->FUN_0043c910(&position, &direction, g_unk0x004b185c, g_unk0x004b1860, g_unk0x004b1868);
	if (!target) {
		target = m_unk0x074->FUN_0043ca60(&position, &direction, g_unk0x004b185c, g_unk0x004b1864, g_unk0x004b186c);
		if (!target && p_racer->m_unk0xd08 != 2) {
			entry = m_unk0x050->FUN_0045c6a0(&position, &direction, g_unk0x004b1840, g_unk0x004b1844, g_unk0x004b184c);
		}
	}

	TetherAction* action = m_unk0x08c;
	if (!action) {
		action = static_cast<TetherAction*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x08c = static_cast<TetherAction*>(action->m_next);
	}

	ActionBase* next = m_unk0x1880;
	Field0x050::Entry* setupEntry = entry;
	action->m_next = next;
	GolWorldDatabase* worldDatabase = m_unk0x05c;
	m_unk0x1880 = action;
	TetherAction* activeAction = static_cast<TetherAction*>(m_unk0x1880);
	LegoU32 result =
		activeAction->FUN_00453de0(worldDatabase->GetUnk0x9c(), p_racer, target, setupEntry, m_unk0x020, 0);
	action->m_unk0x014 = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045ac80
void RaceState::Racer::Field0x008::FUN_0045ac80(Racer* p_racer, LegoU32 p_unk0x08)
{
	LightningAction* action = m_unk0x090;
	if (!action) {
		action = static_cast<LightningAction*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x090 = static_cast<LightningAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	action->FUN_00454cb0(p_racer, m_unk0x1998);
	action->m_unk0x014 = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ace0
void RaceState::Racer::Field0x008::FUN_0045ace0(Racer* p_racer, LegoU32 p_unk0x08)
{
	Field0x1894Action* action = m_unk0x07c;
	if (!action) {
		action = static_cast<Field0x1894Action*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x07c = static_cast<Field0x1894Action*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;
	action->FUN_00457230(p_racer);
	action->m_unk0x014 = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045ad30
LegoU32 RaceState::Racer::Field0x008::FUN_0045ad30(Racer* p_racer, LegoU32 p_unk0x08)
{
	BarrelAction* action = m_unk0x080;
	if (!action) {
		action = static_cast<BarrelAction*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x080 = static_cast<BarrelAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolVec3 position;
	p_racer->m_unk0x018.m_unk0x044->VTable0x04(&position);

	GolVec3 direction;
	p_racer->m_unk0x018.m_unk0x044->GetOrientationRow0(&direction);
	direction.m_x = -direction.m_x;
	direction.m_y = -direction.m_y;
	direction.m_z = -direction.m_z;

	Racer* target = m_unk0x074->FUN_0043ca60(&position, &direction, g_unk0x004b1850, g_unk0x004b1854, g_unk0x004b1858);
	LegoU32 result = action->FUN_00452f60(p_racer, target);
	action->m_unk0x014 = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045adf0
void RaceState::Racer::Field0x008::FUN_0045adf0(Racer* p_racer, LegoU32 p_unk0x08)
{
	MagnetAction* action = m_unk0x078;
	if (!action) {
		action = static_cast<MagnetAction*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x078 = static_cast<MagnetAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolAnimatedEntity* model0;
	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("magnet");
	}

	GolAnimatedEntity* model1;
	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("magring");
	}

	GolAnimatedEntity* model2;
	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("insd");
	}

	action->FUN_00455830(p_racer, model0, model1, model2);
	action->m_unk0x014 = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x0045aeb0
LegoU32 RaceState::Racer::Field0x008::FUN_0045aeb0(Racer* p_racer, LegoU32 p_unk0x08)
{
	GolAnimatedEntity* model0;
	GolAnimatedEntity* model1;
	GolAnimatedEntity* model2;

	CurseAction* action = m_unk0x084;
	if (!action) {
		action = static_cast<CurseAction*>(FUN_0045b2e0(4, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x084 = static_cast<CurseAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model0 = NULL;
	}
	else {
		model0 = m_unk0x05c->GetUnk0xc0Name("curse");
	}

	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model1 = NULL;
	}
	else {
		model1 = m_unk0x05c->GetUnk0xc0Name("cgreen");
	}

	if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
		model2 = NULL;
	}
	else {
		model2 = m_unk0x05c->GetUnk0xc0Name("cgreen2");
	}

	action->FUN_00452550(p_racer, model0, model1, model2, m_unk0x1998);
	const LegoU32 curseSubtype = 3;
	action->m_unk0x014 = curseSubtype;
	return curseSubtype;
}

// FUNCTION: LEGORACERS 0x0045af80
void RaceState::Racer::Field0x008::FUN_0045af80(Racer* p_racer, LegoU32 p_unk0x08)
{
	for (LegoU32 i = 0; i < 3; i++) {
		MissileAction* action = m_unk0x094;
		if (!action) {
			action = static_cast<MissileAction*>(FUN_0045b2e0(1, p_unk0x08, -1, -1, -1));
		}
		else {
			m_unk0x094 = static_cast<MissileAction*>(action->m_next);
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;

		GolAnimatedEntity* model0;
		if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
			model0 = NULL;
		}
		else {
			model0 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		GolAnimatedEntity* model1;
		if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
			model1 = NULL;
		}
		else {
			model1 = m_unk0x05c->GetUnk0xc0Name("dmissil");
		}

		action->FUN_00456560(model1, model0, p_racer, i);
		action->m_unk0x014 = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b030
void RaceState::Racer::Field0x008::FUN_0045b030(Racer* p_racer, LegoU32 p_unk0x08)
{
	if (25 - m_unk0x187c >= 2) {
		LegoU32 subtype = p_unk0x08;
		Action* action = m_unk0x098;
		if (!action) {
			action = static_cast<Action*>(FUN_0045b2e0(2, 0, 1, 2, 3));
		}
		else {
			m_unk0x098 = static_cast<Action*>(action->m_next);
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;

		GolAnimatedEntity* model;
		GolAnimatedEntity* inputModel;
		switch (subtype) {
		case 0:
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield0");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin0");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 1:
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield1");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin1");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 2:
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield2");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin2");
			}
			else {
				inputModel = NULL;
			}
			break;
		case 3:
			if (!m_unk0x05c->GetUnk0xc0NameEntries()) {
				model = NULL;
			}
			else {
				model = m_unk0x05c->GetUnk0xc0Name("shield3");
			}

			if (m_unk0x05c->GetUnk0xc0NameEntries()) {
				inputModel = m_unk0x05c->GetUnk0xc0Name("shldin3");
			}
			else {
				inputModel = NULL;
			}
			break;
		default:
			model = NULL;
			inputModel = NULL;
			break;
		}

		action->FUN_0045bd30(p_racer, subtype, model, inputModel);
		action->m_unk0x014 = subtype;
	}
}

// FUNCTION: LEGORACERS 0x0045b1e0
void RaceState::Racer::Field0x008::FUN_0045b1e0(Racer* p_racer, LegoU32 p_unk0x08)
{
	if (p_unk0x08 == 3) {
		FUN_0045b260(p_racer, 3);
	}
	else if (25 - m_unk0x187c >= 3) {
		TurboAction* action = m_unk0x09c;
		if (!action) {
			action = static_cast<TurboAction*>(FUN_0045b2e0(3, 0, 1, 2, -1));
		}
		else {
			m_unk0x09c = static_cast<TurboAction*>(action->m_next);
		}

		action->m_next = m_unk0x1880;
		m_unk0x1880 = action;
		action->FUN_0045c8f0(p_racer, p_unk0x08);
		action->m_unk0x014 = p_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x0045b260
LegoU32 RaceState::Racer::Field0x008::FUN_0045b260(Racer* p_racer, LegoU32 p_unk0x08)
{
	WarpAction* action = m_unk0x0a0;
	if (!action) {
		action = static_cast<WarpAction*>(FUN_0045b2e0(3, p_unk0x08, -1, -1, -1));
	}
	else {
		m_unk0x0a0 = static_cast<WarpAction*>(action->m_next);
	}

	action->m_next = m_unk0x1880;
	m_unk0x1880 = action;

	GolModelEntity* model;
	if (!m_unk0x05c->GetUnk0xb4NameEntries()) {
		model = NULL;
	}
	else {
		model = m_unk0x05c->GetUnk0xb4Name("warpprt");
	}

	LegoU32 result = action->FUN_0045d560(p_racer, model, m_unk0x1998);
	action->m_unk0x014 = p_unk0x08;
	return result;
}

// FUNCTION: LEGORACERS 0x0045b2e0
RaceState::Racer::Field0x008::ActionBase* RaceState::Racer::Field0x008::FUN_0045b2e0(
	LegoU32 p_unk0x04,
	LegoU32 p_unk0x08,
	LegoS32 p_unk0x0c,
	LegoS32 p_unk0x10,
	LegoS32 p_unk0x14
)
{
	ActionBase* previous = NULL;
	ActionBase* bestPrevious = NULL;
	ActionBase* best = NULL;
	LegoS32 bestScore = 0;
	LegoU32 bestPriority = 0xffffffff;

	for (ActionBase* action = m_unk0x1880; action; action = action->m_next) {
		if (action->VTable0x18() == p_unk0x04) {
			LegoU32 subtype = action->m_unk0x014;
			if (subtype == p_unk0x08 || subtype == static_cast<LegoU32>(p_unk0x0c) ||
				subtype == static_cast<LegoU32>(p_unk0x10) || subtype == static_cast<LegoU32>(p_unk0x14)) {
				LegoS32 score = action->m_unk0x004;
				if (score > bestScore) {
					bestPriority = action->m_unk0x008;
					bestScore = action->m_unk0x004;
					best = action;
					bestPrevious = previous;
				}
				else if (score == bestScore) {
					LegoU32 priority = action->m_unk0x008;
					if (priority < bestPriority) {
						bestScore = action->m_unk0x004;
						bestPriority = priority;
						best = action;
						bestPrevious = previous;
					}
				}
			}
		}

		previous = action;
	}

	if (!bestPrevious) {
		m_unk0x1880 = best->m_next;
	}
	else {
		bestPrevious->m_next = best->m_next;
	}

	best->m_next = NULL;
	best->VTable0x1c();

	return best;
}

// FUNCTION: LEGORACERS 0x0045b640
void RaceState::Racer::Field0x008::FUN_0045b640(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x188c; i++) {
		Action* action = &m_unk0x18b0[i];
		if (action->m_unk0x004 > 1 && action->m_unk0x020 == p_racer) {
			action->m_unk0x004 = 6;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b690
void RaceState::Racer::Field0x008::FUN_0045b690(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x188d; i++) {
		if (m_unk0x18b4[i].m_unk0x004 > 1 && m_unk0x18b4[i].m_racer == p_racer) {
			m_unk0x18b4[i].m_unk0x004 = 6;
			m_unk0x18b4[i].m_racer = NULL;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b6f0
void RaceState::Racer::Field0x008::FUN_0045b6f0(Racer* p_racer)
{
	for (LegoU32 i = 0; i < m_unk0x1884; i++) {
		MagnetAction* action = &m_unk0x1890[i];
		if (action->m_unk0x004 > 1 && action->m_unk0x078 == p_racer) {
			action->m_unk0x004 = 6;
		}
	}
}

// FUNCTION: LEGORACERS 0x0045b9e0
GolAnimatedEntity* RaceState::Racer::Field0x008::FUN_0045b9e0()
{
	LegoU32 index = 0;
	LegoU32 flags = m_unk0x1878;
	LegoU32 count = m_unk0x187c;

	if (count == sizeOfArray(m_unk0x0a4)) {
		return NULL;
	}

	for (; flags & 1; index++) {
		if (index >= sizeOfArray(m_unk0x0a4)) {
			break;
		}

		flags >>= 1;
	}

	m_unk0x1878 |= 1 << index;
	m_unk0x187c = count + 1;
	return &m_unk0x0a4[index];
}

// FUNCTION: LEGORACERS 0x0045bd30
void RaceState::Racer::Field0x008::Action::FUN_0045bd30(
	Racer* p_racer,
	LegoU32 p_unk0x08,
	GolAnimatedEntity* p_unk0x0c,
	GolAnimatedEntity* p_unk0x10
)
{
	LegoU32 soundId = 0x4c;

	m_unk0x018 = m_unk0x024->FUN_0045b9e0();
	if (!m_unk0x018) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x01c = m_unk0x024->FUN_0045b9e0();
	if (!m_unk0x01c) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x020 = p_racer;
	if (m_unk0x020->m_unk0xd04 & Racer::c_flags0xd04Bit0) {
		m_unk0x024->FUN_0045b640(m_unk0x020);
	}

	switch (p_unk0x08) {
	case 0:
		m_unk0x008 = 4000;
		soundId = 0x4c;
		break;
	case 1:
		m_unk0x008 = 6000;
		soundId = 0x35;
		break;
	case 2:
		m_unk0x008 = 8000;
		soundId = 0x4d;
		break;
	case 3:
		m_unk0x008 = 10000;
		soundId = 0x4e;
		break;
	}

	m_unk0x028 = m_unk0x010->FUN_00443bd0(soundId);
	if (m_unk0x028) {
		m_unk0x028->Play(TRUE);
		m_unk0x028->SetDistanceRange(g_unk0x004b0958, g_unk0x004b095c);
	}

	m_unk0x004 = 3;
	m_unk0x020->FUN_00439770(p_unk0x08);
	if (m_unk0x020->m_unk0xd04 & Racer::c_flags0xd04Bit11) {
		m_unk0x020->FUN_00439b00();
	}
	m_unk0x014 = p_unk0x08;

	m_unk0x018->FUN_0040d550(
		p_unk0x0c->GetModel(0),
		p_unk0x0c->VTable0x58(0),
		p_unk0x0c->GetModelPart(0),
		p_unk0x0c->GetModelDistance(0)
	);

	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x0c->GetModel(i);
		if (model) {
			m_unk0x018->FUN_10023940(
				model,
				p_unk0x0c->VTable0x58(i),
				p_unk0x0c->GetModelPart(i),
				p_unk0x0c->GetModelDistance(i)
			);
		}
	}

	m_unk0x018->FUN_0040dad0(0);
	m_unk0x018->SetFlags(m_unk0x018->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x018->SetUnk0xb8(p_unk0x0c->GetUnk0xb8());
	m_unk0x018->FUN_00411680(p_unk0x0c->FUN_00411640());
	m_unk0x018->FUN_004116b0(p_unk0x0c->FUN_00411660());
	m_unk0x018->FUN_00411700(p_unk0x0c->FUN_004116e0());
	m_unk0x018->FUN_00411730(p_unk0x0c->FUN_004116f0());
	m_unk0x018->CopyPositionFrom(*m_unk0x020->m_unk0x018.m_unk0x044);

	m_unk0x01c->FUN_0040d550(
		p_unk0x10->GetModel(0),
		p_unk0x10->VTable0x58(0),
		p_unk0x10->GetModelPart(0),
		p_unk0x10->GetModelDistance(0)
	);

	for (i = 1; i < 3; i++) {
		GolModelBase* model = p_unk0x10->GetModel(i);
		if (model) {
			m_unk0x01c->FUN_10023940(
				model,
				p_unk0x10->VTable0x58(i),
				p_unk0x10->GetModelPart(i),
				p_unk0x10->GetModelDistance(i)
			);
		}
	}

	m_unk0x01c->FUN_0040dad0(0);
	m_unk0x01c->SetFlags(m_unk0x01c->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x01c->SetUnk0xb8(p_unk0x10->GetUnk0xb8());
	m_unk0x01c->FUN_00411680(p_unk0x10->FUN_00411640());
	m_unk0x01c->FUN_004116b0(p_unk0x10->FUN_00411660());
	m_unk0x01c->FUN_00411700(p_unk0x10->FUN_004116e0());
	m_unk0x01c->FUN_00411730(p_unk0x10->FUN_004116f0());
	m_unk0x01c->CopyPositionFrom(*m_unk0x018);
}

// FUNCTION: LEGORACERS 0x0045c6a0
RaceState::Racer::Field0x008::Field0x050::Entry* RaceState::Racer::Field0x008::Field0x050::FUN_0045c6a0(
	GolVec3* p_unk0x04,
	GolVec3* p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoFloat p_unk0x10,
	LegoFloat p_unk0x14
)
{
	LegoFloat nearestDistanceSquared = FLT_MAX;
	LegoS32 resultIndex = -1;

	for (LegoS32 i = 0; i < m_count; i++) {
		Entry& entry = m_entries[i];

		if (entry.m_flags0x10 & Entry::c_flags0x10Bit1) {
			GolVec3 position = entry.m_unk0x00;
			LegoFloat deltaX = position.m_x - p_unk0x04->m_x;
			GolVec2 deltaYZ;
			deltaYZ.m_x = position.m_y - p_unk0x04->m_y;
			deltaYZ.m_y = position.m_z - p_unk0x04->m_z;
			LegoFloat distanceSquared = deltaYZ.m_y * deltaYZ.m_y + deltaYZ.m_x * deltaYZ.m_x + deltaX * deltaX;

			if (distanceSquared >= p_unk0x0c && distanceSquared <= p_unk0x10) {
				GolVec3 delta;
				delta.m_x = deltaX;
				delta.m_y = deltaYZ.m_x;
				delta.m_z = deltaYZ.m_y;
				GolMath::NormalizeVector3(delta, &delta);

				LegoFloat dotProduct = p_unk0x08->m_z;
				dotProduct *= delta.m_z;
				LegoFloat dotProductY = p_unk0x08->m_y;
				dotProduct += dotProductY * delta.m_y;
				dotProduct += delta.m_x * p_unk0x08->m_x;
				if (dotProduct >= p_unk0x14 && distanceSquared < nearestDistanceSquared) {
					resultIndex = i;
					nearestDistanceSquared = distanceSquared;
				}
			}
		}
	}

	if (resultIndex < 0) {
		return NULL;
	}

	return &m_entries[resultIndex];
}

// FUNCTION: LEGORACERS 0x0045c8f0
void RaceState::Racer::Field0x008::TurboAction::FUN_0045c8f0(Racer* p_racer, LegoU32 p_unk0x08)
{
	GolAnimatedEntity* model = NULL;
	GolAnimatedEntity* effect0 = NULL;
	GolAnimatedEntity* effect1 = NULL;

	m_unk0x020 = m_owner->FUN_0045b9e0();
	if (!m_unk0x020) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x024 = m_owner->FUN_0045b9e0();
	if (!m_unk0x024) {
		m_unk0x004 = 6;
		return;
	}

	m_unk0x028 = m_owner->FUN_0045b9e0();
	if (!m_unk0x028) {
		m_unk0x004 = 6;
		return;
	}

	m_racer = p_racer;
	if (m_racer->m_unk0xc70.m_unk0x014 & Racer::Field0xc70::c_flags0x014Bit0) {
		m_owner->FUN_0045b690(m_racer);
		m_racer->FUN_00439730();
		if (m_racer->m_unk0xd04 & Racer::c_flags0xd04Bit3) {
			m_racer->FUN_004395a0();
		}
	}

	m_unk0x008 = 400;
	m_unk0x014 = p_unk0x08;
	switch (p_unk0x08) {
	case 2:
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_owner->m_unk0x05c->GetUnk0xc0Name("TurboL2");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb2f1");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb2f2");
		}
		break;
	case 1:
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_owner->m_unk0x05c->GetUnk0xc0Name("TurboL1");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb1f1");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb1f2");
		}
		break;
	case 0:
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			model = m_owner->m_unk0x05c->GetUnk0xc0Name("TurboL0");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect0 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb0f1");
		}
		if (m_owner->m_unk0x05c->GetUnk0xc0NameEntries()) {
			effect1 = m_owner->m_unk0x05c->GetUnk0xc0Name("turb0f2");
		}
		break;
	}

	m_unk0x020
		->FUN_0040d550(model->GetModel(0), model->VTable0x58(0), model->GetModelPart(0), model->GetModelDistance(0));
	LegoU32 i;
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = model->GetModel(i);
		if (lodModel) {
			m_unk0x020
				->FUN_10023940(lodModel, model->VTable0x58(i), model->GetModelPart(i), model->GetModelDistance(i));
		}
	}

	m_unk0x024->FUN_0040d550(
		effect0->GetModel(0),
		effect0->VTable0x58(0),
		effect0->GetModelPart(0),
		effect0->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect0->GetModel(i);
		if (lodModel) {
			m_unk0x024->FUN_10023940(
				lodModel,
				effect0->VTable0x58(i),
				effect0->GetModelPart(i),
				effect0->GetModelDistance(i)
			);
		}
	}
	m_unk0x024->FUN_00411680(effect0->FUN_00411640());
	m_unk0x024->FUN_004116b0(effect0->FUN_00411660());
	m_unk0x024->FUN_00411700(effect0->FUN_004116e0());
	m_unk0x024->FUN_00411730(effect0->FUN_004116f0());

	m_unk0x028->FUN_0040d550(
		effect1->GetModel(0),
		effect1->VTable0x58(0),
		effect1->GetModelPart(0),
		effect1->GetModelDistance(0)
	);
	for (i = 1; i < 3; i++) {
		GolModelBase* lodModel = effect1->GetModel(i);
		if (lodModel) {
			m_unk0x028->FUN_10023940(
				lodModel,
				effect1->VTable0x58(i),
				effect1->GetModelPart(i),
				effect1->GetModelDistance(i)
			);
		}
	}
	m_unk0x028->FUN_00411680(effect1->FUN_00411640());
	m_unk0x028->FUN_004116b0(effect1->FUN_00411660());
	m_unk0x028->FUN_00411700(effect1->FUN_004116e0());
	m_unk0x028->FUN_00411730(effect1->FUN_004116f0());

	m_unk0x020->SetFlags(m_unk0x020->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x020->FUN_0040dad0(0);
	m_unk0x024->SetFlags(m_unk0x024->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x024->FUN_0040dad0(0);
	m_unk0x028->SetFlags(m_unk0x028->GetFlags() | GolAnimatedEntity::c_flagPartAnimation);
	m_unk0x028->FUN_0040dad0(0);
	m_unk0x004 = 2;
}

// FUNCTION: LEGORACERS 0x0045d560
LegoU32 RaceState::Racer::Field0x008::WarpAction::FUN_0045d560(
	Racer* p_racer,
	GolModelEntity* p_model,
	ActionTarget* p_unk0x0c
)
{
	LegoU32 flags = p_racer->m_unk0xd04;
	if (!(flags & Racer::c_flags0xd04Bit4)) {
		if (flags & Racer::c_flags0xd04Bit21) {
			m_unk0x004 = 6;
			return flags;
		}

		m_owner->FUN_0045b6f0(p_racer);
		m_racer = p_racer;
		m_unk0x0e0 = p_racer->m_unk0xd08 == 2;
		p_racer->m_unk0xd04 |= Racer::c_flags0xd04Bit21;

		m_unk0x018.VTable0x50(p_model->GetModel(0), p_model->GetModelDistance(0));
		for (LegoU32 i = 1; i < 3; i++) {
			GolModelBase* model = p_model->GetModel(i);
			if (model) {
				m_unk0x018.FUN_10027c50(model, p_model->GetModelDistance(i));
			}
		}

		m_unk0x018.FUN_00411680(p_model->FUN_00411640());
		m_unk0x018.FUN_004116b0(p_model->FUN_00411660());
		m_unk0x018.FUN_00411700(p_model->FUN_004116e0());
		m_unk0x018.FUN_00411730(p_model->FUN_004116f0());

		GolAnimatedEntity* racerEntity = p_racer->m_unk0x018.m_unk0x044;
		GolVec3 position;
		racerEntity->VTable0x04(&position);
		LegoFloat positionZ = position.m_z;
		position.m_z = positionZ + g_unk0x004b03f4;
		m_unk0x018.VTable0x08(position);
		position.m_z -= g_unk0x004b03f4;
		m_unk0x018.CopyOrientationFrom(*racerEntity);

		if (m_racer->m_unk0xdb4) {
			m_racer->m_unk0xdb4->m_unk0x134 = m_unk0x0b0 + g_unk0x004b1a6c;
		}

		if (p_unk0x0c) {
			m_unk0x008 = 0;
			m_unk0x0c0 = p_unk0x0c->m_unk0x00;
			m_unk0x0cc = p_unk0x0c->m_unk0x0c;
			m_unk0x0d8 = TRUE;
		}
		else {
			m_unk0x008 = 500;
			m_unk0x0d8 = FALSE;
		}

		m_unk0x004 = 2;
		return 0;
	}

	m_unk0x004 = 6;
	return flags;
}
