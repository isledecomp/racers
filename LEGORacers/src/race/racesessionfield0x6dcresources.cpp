#include "audio/soundnode.h"
#include "audio/spatialsoundinstance.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "material/materialtable0x0c.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"

#include <float.h>

// GLOBAL: LEGORACERS 0x004b1484
extern const LegoFloat g_unk0x004b1484 = 3.0f;

// GLOBAL: LEGORACERS 0x004b170c
extern const LegoFloat g_unk0x004b170c = 30.0f;

// GLOBAL: LEGORACERS 0x004b14e8
extern const LegoFloat g_unk0x004b14e8 = 4.0f;

// GLOBAL: LEGORACERS 0x004b1514
extern const LegoFloat g_unk0x004b1514 = 0.60000002f;

// GLOBAL: LEGORACERS 0x004b1548
extern const LegoFloat g_unk0x004b1548 = 30.0f;

// GLOBAL: LEGORACERS 0x004b154c
extern const LegoFloat g_unk0x004b154c = 300.0f;

// GLOBAL: LEGORACERS 0x004b1550
extern const LegoFloat g_unk0x004b1550 = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b1558
extern const LegoFloat g_unk0x004b1558 = 0.85000002f;

// GLOBAL: LEGORACERS 0x004b1568
extern const ColorRGBA g_unk0x004b1568 = {0x19, 0x41, 0xf5, 0xff};

// GLOBAL: LEGORACERS 0x004b156c
extern const ColorRGBA g_unk0x004b156c = {0x19, 0x41, 0xff, 0xff};

// GLOBAL: LEGORACERS 0x004b1570
extern const ColorRGBA g_unk0x004b1570 = {0x19, 0x41, 0xeb, 0xff};

// GLOBAL: LEGORACERS 0x004b1578
extern const LegoFloat g_unk0x004b1578 = 50.0f;

// GLOBAL: LEGORACERS 0x004b15a0
extern const LegoFloat g_unk0x004b15a0 = 8.0f;

// GLOBAL: LEGORACERS 0x004b15a4
extern const LegoFloat g_unk0x004b15a4 = 8.0f;

// GLOBAL: LEGORACERS 0x004b15d4
extern const LegoFloat g_unk0x004b15d4 = 0.00097751711f;

// GLOBAL: LEGORACERS 0x004c1c50
extern ColorRGBA g_unk0x004c1c50 = {0x64, 0x3c, 0x0e, 0xff};

// GLOBAL: LEGORACERS 0x004c1c54
extern ColorRGBA g_unk0x004c1c54 = {0x8f, 0x5a, 0x1c, 0xff};

// GLOBAL: LEGORACERS 0x004c1c58
extern ColorRGBA g_unk0x004c1c58 = {0x14, 0x14, 0x00, 0xff};

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// FUNCTION: LEGORACERS 0x004518f0
RaceSession::Field0x6dc::Field0x18a0::Field0x18a0()
{
	m_unk0x018 = 0;
	m_unk0x018 = &m_unk0x030;
	m_unk0x0d8 = NULL;
	m_unk0x0dc = 0;
	m_unk0x0e0 = 0;
	m_unk0x0e4 = 0;
}

// FUNCTION: LEGORACERS 0x00451970
RaceSession::Field0x6dc::Field0x18a0::~Field0x18a0()
{
	FUN_00451a10();
}

// FUNCTION: LEGORACERS 0x004519d0
void RaceSession::Field0x6dc::Field0x18a0::FUN_004519d0(Field0x64** p_unk0x04, undefined4 p_unk0x08)
{
	if (m_unk0x004 != 0) {
		FUN_00451a10();
	}

	m_unk0x01c = p_unk0x04;
	m_unk0x020 = p_unk0x08;
	m_unk0x0d8 = (*p_unk0x04)->CreateBillboard();
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x00451a10
void RaceSession::Field0x6dc::Field0x18a0::FUN_00451a10()
{
	VTable0x1c();

	if (m_unk0x01c != NULL && m_unk0x0d8 != NULL) {
		(*m_unk0x01c)->VTable0x64(m_unk0x0d8);
		m_unk0x0d8 = NULL;
		m_unk0x01c = NULL;
	}

	m_unk0x004 = 0;
}

// FUNCTION: LEGORACERS 0x00452440
RaceSession::Field0x6dc::Field0x189c::Field0x189c()
{
	FUN_004524f0();
}

// FUNCTION: LEGORACERS 0x004524a0
RaceSession::Field0x6dc::Field0x189c::~Field0x189c()
{
	FUN_00452510();
}

// FUNCTION: LEGORACERS 0x004524f0
void RaceSession::Field0x6dc::Field0x189c::FUN_004524f0()
{
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
	m_unk0x38 = 0;
	m_unk0x018 = 0;
	m_unk0x020 = 0;
	m_unk0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00452510
void RaceSession::Field0x6dc::Field0x189c::FUN_00452510()
{
	VTable0x1c();
	FUN_004524f0();
}

// FUNCTION: LEGORACERS 0x00452530
void RaceSession::Field0x6dc::Field0x189c::FUN_00452530(
	Field0x074* p_unk0x04,
	undefined4 p_unk0x08,
	Field0x6dc* p_unk0x0c
)
{
	m_unk0x018 = p_unk0x04;
	m_unk0x020 = p_unk0x08;
	m_unk0x2c = p_unk0x0c;
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x00452dd0
RaceSession::Field0x6dc::Field0x1898::Field0x1898()
{
	m_unk0x164 = 0;
	m_unk0x168 = 0;
	m_unk0x16c = 0;
	m_unk0x170 = 0;
	m_unk0x174 = 0;
	m_unk0x178 = 0;
}

// FUNCTION: LEGORACERS 0x00452e50
RaceSession::Field0x6dc::Field0x1898::~Field0x1898()
{
	FUN_00452eb0();
}

// FUNCTION: LEGORACERS 0x00452eb0
void RaceSession::Field0x6dc::Field0x1898::FUN_00452eb0()
{
	VTable0x1c();
	m_unk0x02c.VTable0x54();
	m_unk0x164 = 0;
	m_unk0x168 = 0;
	m_unk0x16c = 0;
	m_unk0x170 = 0;
}

// FUNCTION: LEGORACERS 0x00452ee0
void RaceSession::Field0x6dc::Field0x1898::FUN_00452ee0(
	Field0x074* p_unk0x04,
	undefined4 p_unk0x08,
	Field0x6dc* p_unk0x0c,
	undefined4 p_unk0x10,
	GolModelEntity* p_model
)
{
	m_unk0x018 = p_unk0x04;
	m_unk0x020 = p_unk0x08;
	m_unk0x164 = p_unk0x0c;
	m_unk0x168 = p_unk0x10;

	m_unk0x02c.VTable0x50(p_model->GetModel(0), p_model->GetModelDistance(0));

	for (LegoU32 i = 1; i < 3; i++) {
		GolModelBase* model = p_model->GetModel(i);
		if (model != NULL) {
			m_unk0x02c.FUN_10027c50(model, p_model->GetModelDistance(i));
		}
	}

	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x004535a0
RaceSession::Field0x6dc::Field0x68Field0x02c::Field0x68Field0x02c()
{
	m_unk0x60 = 0;
	m_flags0x64 = 0;
}

// FUNCTION: LEGORACERS 0x004535c0
RaceSession::Field0x6dc::Field0x68Field0x02c::~Field0x68Field0x02c()
{
	FUN_00453610();
}

// FUNCTION: LEGORACERS 0x00453610
void RaceSession::Field0x6dc::Field0x68Field0x02c::FUN_00453610()
{
	m_unk0x60 = 0;
	m_flags0x64 = 0;
	FUN_00453a10();
}

// FUNCTION: LEGORACERS 0x00453620
void RaceSession::Field0x6dc::Field0x68Field0x02c::FUN_00453620()
{
	m_unk0x08.VTable0x04(&m_unk0x54);
	m_unk0x3c = c_stateActive;
	m_unk0x60 = 0;
	m_flags0x64 = 0;
}

// FUNCTION: LEGORACERS 0x00453650
void RaceSession::Field0x6dc::Field0x68Field0x02c::VTable0x0c()
{
	Field0x68::VTable0x0c();
	m_unk0x08.VTable0x08(m_unk0x54);
	m_unk0x3c = c_stateActive;
	m_unk0x60 = 0;
	m_flags0x64 = 0;
	m_unk0x4c = 0;
	FUN_00453ad0(FALSE);
}

// FUNCTION: LEGORACERS 0x00453690
void RaceSession::Field0x6dc::Field0x68Field0x02c::FUN_00453690(LegoU32 p_elapsedMs)
{
	if (m_unk0x3c == c_stateInactive) {
		return;
	}

	FUN_00453a20(p_elapsedMs);

	if (m_flags0x64 & c_flags0x64Bit0) {
		m_unk0x60 += p_elapsedMs;
		if (m_unk0x60 > 10000) {
			FUN_004537f0();
		}
	}

	LegoU32 state = m_unk0x3c;
	if (state != c_stateActive) {
		if (state == c_stateTransition && m_unk0x4c > 250) {
			LegoU8 flags = m_flags0x64;
			if (flags & c_flags0x64Bit1) {
				m_flags0x64 = flags & ~c_flags0x64Bit1;
				m_unk0x08.VTable0x08(m_unk0x54);
				m_unk0x3c = c_stateActive;
			}
			else {
				m_unk0x3c = c_stateWait;
			}

			m_unk0x4c = 0;
			FUN_00453ad0(FALSE);
		}
	}
	else if (m_unk0x4c > 500) {
		m_unk0x3c = c_stateIdle;
		m_unk0x4c = 0;
		FUN_00453ad0(TRUE);
	}
}

// STUB: LEGORACERS 0x00453750
void RaceSession::Field0x6dc::Field0x68Field0x02c::VTable0x04(RaceState::Racer*)
{
	STUB(0x00453750);
}

void RaceSession::Field0x6dc::Field0x68Field0x02c::FUN_004537f0()
{
	LegoU8 flags = m_flags0x64;
	LegoU32 state = m_unk0x3c;
	flags &= ~c_flags0x64Bit0;
	m_unk0x60 = 0;
	m_flags0x64 = flags;

	if (state) {
		m_unk0x08.VTable0x08(m_unk0x54);
		m_unk0x3c = c_stateActive;
	}
	else {
		m_unk0x3c = c_stateTransition;
		m_flags0x64 = flags | c_flags0x64Bit1;
	}

	m_unk0x4c = 0;
}

// STUB: LEGORACERS 0x00453910
RaceSession::Field0x6dc::Field0x68::Field0x68()
{
	FUN_00453970();
}

// STUB: LEGORACERS 0x00453960
RaceSession::Field0x6dc::Field0x68::~Field0x68()
{
	FUN_00453a10();
}

// FUNCTION: LEGORACERS 0x00453970
LegoS32 RaceSession::Field0x6dc::Field0x68::FUN_00453970()
{
	m_unk0x30 = 1.0f;
	m_unk0x34 = NULL;
	m_unk0x38 = NULL;
	m_unk0x04 = NULL;
	m_unk0x44 = NULL;
	m_unk0x3c = c_stateInactive;
	m_unk0x40 = c_stateWait;
	m_unk0x4c = 0;
	m_unk0x48 = 3000;
	m_flags0x50 = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x004539b0
void RaceSession::Field0x6dc::Field0x68::FUN_004539b0(
	Field0x6dc* p_owner,
	RaceState::Racer::Field0x004* p_soundResource,
	GolVec3* p_position,
	GolModelEntity* p_model0,
	GolModelEntity* p_model1
)
{
	if (m_unk0x04 != NULL) {
		FUN_00453a10();
	}

	m_unk0x04 = p_owner;
	m_unk0x44 = p_soundResource;
	m_unk0x38 = p_model1;
	m_unk0x34 = p_model0;
	m_unk0x08.VTable0x08(*p_position);
	m_unk0x3c = c_stateWait;
	m_unk0x4c = 3000;
}

// FUNCTION: LEGORACERS 0x00453a00
void RaceSession::Field0x6dc::Field0x68::VTable0x0c()
{
	m_unk0x3c = c_stateWait;
	m_unk0x4c = 3000;
}

// FUNCTION: LEGORACERS 0x00453a10
void RaceSession::Field0x6dc::Field0x68::FUN_00453a10()
{
	FUN_00453970();
}

// STUB: LEGORACERS 0x00453a20
void RaceSession::Field0x6dc::Field0x68::FUN_00453a20(LegoU32 p_elapsedMs)
{
	if (m_unk0x3c == c_stateInactive) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs + m_unk0x4c;
	m_unk0x4c = elapsedMs;

	LegoS32 activeStateOffset = m_unk0x3c - c_stateActive;
	if (activeStateOffset == 0) {
		if (elapsedMs < 400) {
			m_unk0x30 = (LegoS32) elapsedMs * 0.0024999999f;
		}
		else if (elapsedMs < 500) {
			m_unk0x30 = 1.0f - (LegoS32) (elapsedMs - 400) * 0.0020000001f;
		}
	}
	else if (activeStateOffset == 1 && elapsedMs <= 250) {
		m_unk0x30 = (LegoS32) (250 - elapsedMs) * 0.0040000002f * 0.008f;
	}

	LegoU8 flags = m_flags0x50;
	if (flags & c_flags0x50Bit1) {
		m_flags0x50 = (flags & ~(c_flags0x50Bit1 | c_flags0x50Bit2)) | c_flags0x50Bit2;
	}
	else {
		m_flags0x50 = flags & ~c_flags0x50Bit2;
	}
}

// STUB: LEGORACERS 0x00453ad0
void RaceSession::Field0x6dc::Field0x68::FUN_00453ad0(LegoBool32 p_unk0x04)
{
	if (p_unk0x04) {
		m_unk0x30 = 0.80000001f;
	}
	else {
		m_unk0x30 = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x00453af0
void RaceSession::Field0x6dc::Field0x68::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	m_flags0x50 |= c_flags0x50Bit1;

	if (m_unk0x3c == c_stateIdle) {
		RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
		if (!(racer->GetUnk0xd04() & c_racerFlags0xd04Bit4)) {
			if (!(m_flags0x50 & c_flags0x50Bit2) || racer->GetUnk0xccc() == 0) {
				VTable0x04(racer);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00453b30
void RaceSession::Field0x6dc::Field0x68::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x3c != c_stateInactive &&
		(m_unk0x3c == c_stateActive || m_unk0x3c == c_stateIdle || m_unk0x3c == c_stateTransition)) {
		GolVec3 position;
		m_unk0x08.VTable0x04(&position);
		m_unk0x34->VTable0x08(position);
		m_unk0x34->SetUnk0x58ThenInvalidateRadius(m_unk0x30);
		m_unk0x34->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00453b90
void RaceSession::Field0x6dc::Field0x68::VTable0x14(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x3c != c_stateInactive &&
		(m_unk0x3c == c_stateActive || m_unk0x3c == c_stateIdle || m_unk0x3c == c_stateTransition)) {
		GolVec3 position;
		m_unk0x08.VTable0x04(&position);
		m_unk0x38->VTable0x08(position);
		m_unk0x38->SetUnk0x58ThenInvalidateRadius(m_unk0x30);
		m_unk0x38->VTable0x1c(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00453bf0
RaceSession::Field0x6dc::Field0x18a4::Field0x18a4()
{
	m_unk0x018 = 0;
	m_unk0x018 = &m_unk0x030;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x270 = NULL;
	m_unk0x28c = 0;
}

// FUNCTION: LEGORACERS 0x00453c70
RaceSession::Field0x6dc::Field0x18a4::~Field0x18a4()
{
	FUN_00453d90();
}

// FUNCTION: LEGORACERS 0x00453cd0
void RaceSession::Field0x6dc::Field0x18a4::FUN_00453cd0(
	Field0x6dc* p_unk0x04,
	undefined4 p_unk0x08,
	undefined4 p_unk0x0c
)
{
	if (m_unk0x004 != 0) {
		FUN_00453d90();
	}

	m_owner0x01c = p_unk0x04;
	m_unk0x020 = p_unk0x08;
	m_unk0x268 = 0;
	m_unk0x26c = 0;
	m_unk0x28c = p_unk0x0c;

	Field0x238::SetupParams params;
	params.m_unk0x00 = p_unk0x04->m_unk0x000;
	params.m_unk0x08 = g_unk0x004b1514;
	params.m_unk0x0c = g_unk0x004b14e8;
	params.m_unk0x10 = g_unk0x004c1c50;
	params.m_unk0x04 = 3.0f;
	params.m_unk0x14 = g_unk0x004c1c54;
	params.m_unk0x18 = g_unk0x004c1c58;
	params.m_material = p_unk0x04->m_renderer->FindMaterialByName("tether");
	m_unk0x030.VTable0x20(&params);

	m_unk0x004 = 1;
	m_unk0x270 = params.m_unk0x00->CreateBillboard();
}

// FUNCTION: LEGORACERS 0x00453d90
void RaceSession::Field0x6dc::Field0x18a4::FUN_00453d90()
{
	VTable0x1c();

	if (m_owner0x01c != NULL && m_unk0x270 != NULL) {
		m_owner0x01c->m_unk0x000->VTable0x64(m_unk0x270);
		m_unk0x270 = NULL;
		m_owner0x01c = NULL;
	}

	m_unk0x030.VTable0x14();
	m_unk0x004 = 0;
}

// FUNCTION: LEGORACERS 0x00454800
RaceSession::Field0x6dc::Field0x18a8::Field0x18a8()
{
	m_unk0x220 = 0;
	m_unk0x228 = 3;
	m_unk0x230 = g_unk0x004b1578;
	m_unk0x22c = 0;
	m_unk0x238 = NULL;
	m_unk0x244 = 0;
	m_unk0x234 = 0;
	m_unk0x240 = 0;
	m_unk0x23c = 0;
	m_unk0x248 = NULL;
}

// FUNCTION: LEGORACERS 0x00454890
RaceSession::Field0x6dc::Field0x18a8::~Field0x18a8()
{
	FUN_00454ab0();
}

// FUNCTION: LEGORACERS 0x004548f0
void RaceSession::Field0x6dc::Field0x18a8::FUN_004548f0(Field0x0* p_export, Field0x6dc* p_unk0x08)
{
	if (m_unk0x004 != 0) {
		FUN_00454ab0();
	}

	m_owner0x01c = p_unk0x08;
	m_unk0x020 = p_unk0x08->m_unk0x068;
	m_unk0x224 = 0;
	m_unk0x240 = 0;
	m_unk0x23c = 0;

	GolD3DRenderDevice* renderer = p_export->GetDrawState()->m_currentRenderer;

	Field0x170::SetupParams params;
	params.m_material = renderer->FindMaterialByName("lightng");
	params.m_unk0x18[1].m_y = g_unk0x004b1558 * 0.5f;
	params.m_unk0x18[2].m_x = -g_unk0x004b1558;
	params.m_unk0x00 = p_export;
	params.m_renderer = renderer;
	params.m_unk0x0c = 4;
	params.m_unk0x10 = 5;
	params.m_unk0x14 = 2;
	params.m_unk0x18[0].m_x = 0.0f;
	params.m_unk0x18[0].m_y = g_unk0x004b1558;
	params.m_unk0x18[0].m_z = -0.25f;
	params.m_unk0x18[1].m_x = 0.0f;
	params.m_unk0x18[1].m_z = 0.0f;
	params.m_unk0x18[2].m_y = -0.25f;
	params.m_unk0x18[2].m_z = 0.0f;
	params.m_unk0x54 = 0;
	params.m_unk0x58 = 0x3f000000;
	params.m_unk0x5c = 0x3f800000;
	params.m_unk0x68 = 3;
	params.m_modelDistance = 360000.0f;
	params.m_unk0x70 = 1;
	m_unk0x030.FUN_00493c90(&params);
	m_unk0x030.FUN_00494820(&g_unk0x004b1568, &g_unk0x004b156c, &g_unk0x004b1570);

	m_unk0x248 = p_export->CreateBillboard();
	DuskwindBananaRelic0x24* material = renderer->FindMaterialByName("ltflash");
	m_unk0x248->VTable0x4c(material, g_unk0x004b15a0, g_unk0x004b15a4, g_unk0x004b1550);

	m_unk0x004 = 1;
	FUN_00454b90();
}

// FUNCTION: LEGORACERS 0x00454a70
void RaceSession::Field0x6dc::Field0x18a8::FUN_00454a70()
{
	m_unk0x238 = m_unk0x010->FUN_00443bd0(0x44);
	if (m_unk0x238 != NULL) {
		m_unk0x238->SetDistanceRangeWithMinSquared(g_unk0x004b1548 * g_unk0x004b1548, g_unk0x004b154c);
	}
}

// FUNCTION: LEGORACERS 0x00454ab0
void RaceSession::Field0x6dc::Field0x18a8::FUN_00454ab0()
{
	if (m_unk0x238 != NULL) {
		m_unk0x010->FUN_00443c10(m_soundResource0x238);
		m_unk0x238 = NULL;
	}

	VTable0x1c();

	if (m_unk0x248 != NULL) {
		m_unk0x248->VTable0x50();
		m_owner0x01c->m_unk0x000->VTable0x64(m_unk0x248);
		m_unk0x248 = NULL;
	}

	m_unk0x030.FUN_00493e60();
	m_unk0x004 = 0;
	m_unk0x244 = 0;
	m_unk0x23c = 0;
}

// FUNCTION: LEGORACERS 0x00454b20
void RaceSession::Field0x6dc::Field0x18a8::FUN_00454b20()
{
	g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
	m_unk0x1d0[m_unk0x220] = ((LegoS32) g_unk0x004befec[g_unk0x004c6ee4] * g_unk0x004b15d4 - 0.5f) * 5.0f;

	m_unk0x220++;
	if (m_unk0x220 >= 20) {
		m_unk0x220 = 0;
	}
}

// FUNCTION: LEGORACERS 0x00454b90
void RaceSession::Field0x6dc::Field0x18a8::FUN_00454b90()
{
	for (LegoU32 i = 0; i < 20; i++) {
		FUN_00454b20();
	}
}

// FUNCTION: LEGORACERS 0x00455710
RaceSession::Field0x6dc::Field0x1890::Field0x1890()
{
	FUN_004557e0();
}

// FUNCTION: LEGORACERS 0x00455770
RaceSession::Field0x6dc::Field0x1890::~Field0x1890()
{
	FUN_004557c0();
}

// FUNCTION: LEGORACERS 0x004557c0
void RaceSession::Field0x6dc::Field0x1890::FUN_004557c0()
{
	VTable0x1c();
	FUN_004557e0();
}

// FUNCTION: LEGORACERS 0x004557e0
void RaceSession::Field0x6dc::Field0x1890::FUN_004557e0()
{
	m_unk0x3c = 0;
	m_unk0x40 = 0;
	m_unk0x44 = 0;
	m_unk0x38 = 0;
	m_unk0x70 = 0;
	m_unk0x78 = 0;
	m_unk0x7c = 0;
	m_unk0x80 = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
	m_unk0x34 = 0;
}

// FUNCTION: LEGORACERS 0x00455810
void RaceSession::Field0x6dc::Field0x1890::FUN_00455810(
	Field0x6dc* p_unk0x04,
	Field0x074* p_unk0x08,
	undefined4 p_unk0x0c,
	undefined4,
	Field0x0*,
	GolD3DRenderDevice*,
	undefined4
)
{
	m_unk0x38 = p_unk0x04;
	m_unk0x018 = p_unk0x08;
	m_unk0x020 = p_unk0x0c;
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x004562d0
RaceSession::Field0x6dc::ResourceBase0x2c::ResourceBase0x2c()
{
	m_unk0x018 = 0;
	m_unk0x01c = 0;
	m_unk0x020 = 0;
	m_unk0x024 = 0;
	m_unk0x028 = 0;
}

// FUNCTION: LEGORACERS 0x00456430
RaceSession::Field0x6dc::Field0x18ac::Field0x18ac()
{
	m_unk0x018 = 0;
	m_unk0x018 = &m_unk0x030;
	m_unk0x21c = 0;
	m_unk0x030.m_unk0x0f4 = 0;
}

// FUNCTION: LEGORACERS 0x004564b0
RaceSession::Field0x6dc::Field0x18ac::~Field0x18ac()
{
	FUN_00456540();
}

// FUNCTION: LEGORACERS 0x00456510
void RaceSession::Field0x6dc::Field0x18ac::FUN_00456510(Field0x64** p_unk0x04, undefined4 p_unk0x08)
{
	if (m_unk0x004 != 0) {
		FUN_00456540();
	}

	m_unk0x01c = p_unk0x04;
	m_unk0x020 = p_unk0x08;
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x00456540
void RaceSession::Field0x6dc::Field0x18ac::FUN_00456540()
{
	VTable0x1c();
	m_unk0x004 = 0;
	m_unk0x21c = 0;
}

// FUNCTION: LEGORACERS 0x00457080
RaceSession::Field0x6dc::Field0x1894::Field0x1894()
{
	m_unk0x02c = 0;
	m_unk0x058 = 0;
	m_unk0x05c = 0;
	m_unk0x060 = 0;
	m_unk0x18c = 0;
}

// FUNCTION: LEGORACERS 0x00457100
RaceSession::Field0x6dc::Field0x1894::~Field0x1894()
{
	FUN_00457170();
}

// FUNCTION: LEGORACERS 0x00457170
void RaceSession::Field0x6dc::Field0x1894::FUN_00457170()
{
	VTable0x1c();
	m_unk0x064.FUN_004149f0();
	m_unk0x180.Clear();
	m_unk0x02c = 0;
	m_unk0x058 = 0;
	m_unk0x05c = 0;
	m_unk0x060 = 0;
	m_unk0x18c = 0;
}

// FUNCTION: LEGORACERS 0x004571b0
void RaceSession::Field0x6dc::Field0x1894::FUN_004571b0(
	Field0x6dc* p_unk0x04,
	Field0x074* p_unk0x08,
	RaceSessionField0x27d4::Item::Field0x004::Params* p_unk0x0c,
	undefined4 p_unk0x10,
	undefined4 p_unk0x14,
	GolRenderDevice* p_renderer,
	Field0x0* p_export
)
{
	m_unk0x02c = p_unk0x04;
	m_unk0x018 = p_unk0x08;
	m_unk0x020 = p_unk0x10;
	m_unk0x18c = p_unk0x0c;
	m_unk0x05c = p_unk0x14;
	m_unk0x004 = 1;

	m_unk0x180.Initialize(p_renderer, 1);
	m_unk0x180.AssignEntryByName(0, "oilslck");
	m_unk0x064.FUN_00414950(p_export, p_renderer, 0x10);
	m_unk0x064.GetUnk0x010().EnableFlagBit1();
}

// FUNCTION: LEGORACERS 0x00457640
RaceSession::Field0x6dc::Field0x68Field0x028::Field0x68Field0x028()
{
	m_unk0x54 = NULL;
	m_unk0x58 = NULL;
	m_unk0x5c = 3;
	m_unk0x60 = 3;
	m_unk0x64 = 3;
}

// FUNCTION: LEGORACERS 0x00457670
RaceSession::Field0x6dc::Field0x68Field0x028::~Field0x68Field0x028()
{
	FUN_00457700();
}

// FUNCTION: LEGORACERS 0x004576c0
void RaceSession::Field0x6dc::Field0x68Field0x028::FUN_004576c0(LegoU32 p_unk0x04)
{
	m_unk0x5c = p_unk0x04;
	m_unk0x60 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x004576d0
void RaceSession::Field0x6dc::Field0x68Field0x028::VTable0x0c()
{
	Field0x68::VTable0x0c();
	m_unk0x64 = m_unk0x5c;
	m_unk0x60 = m_unk0x5c;
	m_unk0x54 = m_unk0x04->FUN_0045ba90(&m_unk0x60);
	m_unk0x58 = m_unk0x04->FUN_0045bae0(&m_unk0x60);
}

// FUNCTION: LEGORACERS 0x00457700
void RaceSession::Field0x6dc::Field0x68Field0x028::FUN_00457700()
{
	FUN_00453a10();
}

// STUB: LEGORACERS 0x00457710
void RaceSession::Field0x6dc::Field0x68Field0x028::FUN_00457710(LegoU32 p_elapsedMs)
{
	if (m_unk0x3c == c_stateInactive) {
		return;
	}

	FUN_00453a20(p_elapsedMs);

	if (m_unk0x3c == c_stateWait) {
		if (m_unk0x4c >= m_unk0x48) {
			LegoU8 flags = m_flags0x50;
			m_unk0x4c = 0;
			m_unk0x3c = c_stateActive;
			if (flags & c_flags0x50Bit0) {
				goto playSound;
			}
		}
	}
	else if (m_unk0x3c == c_stateActive) {
		if (m_unk0x4c > 500) {
			m_unk0x3c = c_stateIdle;
			m_unk0x4c = 0;
			FUN_00453ad0(TRUE);
		}
	}
	else if (m_unk0x3c == c_stateTransition && m_unk0x4c > 250) {
		m_unk0x3c = m_unk0x40;
		m_unk0x60 = m_unk0x64;
		m_unk0x4c = 0;
		m_unk0x54 = m_unk0x04->FUN_0045ba90(&m_unk0x60);
		m_unk0x58 = m_unk0x04->FUN_0045bae0(&m_unk0x60);
		FUN_00453ad0(FALSE);

		if (m_unk0x3c == c_stateActive && (m_flags0x50 & c_flags0x50Bit0)) {
		playSound:
			SoundVector position;
			m_unk0x08.VTable0x04(&position);
			m_unk0x44->FUN_00443b80(0x0e, &position, g_unk0x004b1484, 150.0f, 1.0f, 1.0f);
		}
	}
}

// STUB: LEGORACERS 0x00457820
void RaceSession::Field0x6dc::Field0x68Field0x028::VTable0x04(RaceState::Racer* p_racer)
{
	if (m_unk0x3c == c_stateIdle) {
		LegoU32 racerState = p_racer->GetUnk0xccc();
		p_racer->FUN_00439210(m_unk0x60);

		SoundVector position;
		m_unk0x08.VTable0x04(&position);

		if (racerState) {
			m_unk0x64 = racerState;
			m_unk0x40 = c_stateActive;
			if (m_flags0x50 & c_flags0x50Bit0) {
				m_unk0x44->FUN_00443b80(0x48, &position, g_unk0x004b170c, 150.0f, 1.0f, 1.0f);
			}
		}
		else {
			m_unk0x64 = m_unk0x5c;
			m_unk0x40 = c_stateWait;
			if (m_flags0x50 & c_flags0x50Bit0) {
				m_unk0x44->FUN_00443b80(0x31, &position, g_unk0x004b170c, 150.0f, 1.0f, 1.0f);
			}
		}

		m_unk0x3c = c_stateTransition;
		m_unk0x4c = 0;
	}
}

// FUNCTION: LEGORACERS 0x004578e0
void RaceSession::Field0x6dc::Field0x68Field0x028::FUN_004578e0(
	DuskwindBananaRelic0x24* p_unk0x04,
	DuskwindBananaRelic0x24* p_unk0x08
)
{
	m_unk0x54 = p_unk0x04;
	m_unk0x58 = p_unk0x08;
}

// FUNCTION: LEGORACERS 0x00457900
void RaceSession::Field0x6dc::Field0x68Field0x028::VTable0x10(GolD3DRenderDevice* p_renderer)
{
	MaterialTable0x0c* materialTable = m_unk0x34->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_unk0x34->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetPosition(0, m_unk0x54);
	Field0x68::VTable0x10(p_renderer);
}

// FUNCTION: LEGORACERS 0x00457930
void RaceSession::Field0x6dc::Field0x68Field0x028::VTable0x14(GolD3DRenderDevice* p_renderer)
{
	MaterialTable0x0c* materialTable = m_unk0x38->GetPrimaryMaterialTable();
	if (materialTable == NULL) {
		materialTable = m_unk0x38->GetModel(0)->GetMaterialTable();
	}
	materialTable->SetPosition(0, m_unk0x58);
	Field0x68::VTable0x14(p_renderer);
}

// FUNCTION: LEGORACERS 0x0045bbe0
RaceSession::Field0x6dc::ResourceBase0x30::ResourceBase0x30()
{
	m_unk0x018 = 0;
	m_unk0x01c = NULL;
	m_unk0x020 = 0;
	m_unk0x024 = 0;
	m_unk0x028 = 0;
	m_unk0x02c = 0;
}

// FUNCTION: LEGORACERS 0x0045bc40
RaceState::Racer* RaceSession::Field0x6dc::Field0x18b0::FUN_0045bc40()
{
	if (m_unk0x18) {
		return m_unk0x18->m_unk0x08;
	}
	else {
		return NULL;
	}
}

// FUNCTION: LEGORACERS 0x0045bc50
RaceSession::Field0x6dc::Field0x18b0::Field0x18b0()
{
	m_unk0x18 = 0;
	m_unk0x1c = 0;
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
}

// FUNCTION: LEGORACERS 0x0045bc80
RaceSession::Field0x6dc::Field0x18b0::~Field0x18b0()
{
	FUN_0045bd10();
}

// FUNCTION: LEGORACERS 0x0045bcd0
void RaceSession::Field0x6dc::Field0x18b0::FUN_0045bcd0(Field0x6dc* p_unk0x04)
{
	if (m_unk0x004 != 0) {
		FUN_0045bd10();
	}

	m_unk0x004 = 1;
	m_unk0x24 = p_unk0x04;
}

// FUNCTION: LEGORACERS 0x0045bd10
void RaceSession::Field0x6dc::Field0x18b0::FUN_0045bd10()
{
	VTable0x1c();
	m_unk0x004 = 0;
}

// FUNCTION: LEGORACERS 0x0045c7e0
RaceSession::Field0x6dc::Field0x18b4::Field0x18b4()
{
	FUN_0045c8d0();
}

// FUNCTION: LEGORACERS 0x0045c830
RaceSession::Field0x6dc::Field0x18b4::~Field0x18b4()
{
	FUN_0045c8b0();
}

// FUNCTION: LEGORACERS 0x0045c880
void RaceSession::Field0x6dc::Field0x18b4::FUN_0045c880(Field0x6dc* p_unk0x04, undefined4 p_unk0x08)
{
	if (m_unk0x004 != 0) {
		FUN_0045c8b0();
	}

	m_unk0x1c = p_unk0x04;
	m_unk0x2c = p_unk0x08;
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x0045c8b0
void RaceSession::Field0x6dc::Field0x18b4::FUN_0045c8b0()
{
	VTable0x1c();
	FUN_0045c8d0();
	m_unk0x004 = 0;
}

// FUNCTION: LEGORACERS 0x0045c8d0
void RaceSession::Field0x6dc::Field0x18b4::FUN_0045c8d0()
{
	m_unk0x20 = 0;
	m_unk0x24 = 0;
	m_unk0x28 = 0;
	m_unk0x018 = 0;
	m_unk0x1c = 0;
	m_unk0x2c = 0;
	m_unk0x30 = 0;
}

// FUNCTION: LEGORACERS 0x0045d400
RaceSession::Field0x6dc::Field0x18b8::Field0x18b8()
{
	FUN_0045d4b0();
}

// FUNCTION: LEGORACERS 0x0045d460
RaceSession::Field0x6dc::Field0x18b8::~Field0x18b8()
{
	FUN_0045d540();
}

// FUNCTION: LEGORACERS 0x0045d4b0
void RaceSession::Field0x6dc::Field0x18b8::FUN_0045d4b0()
{
	m_unk0x004 = 0;
	m_unk0x0e0 = 0;
	m_unk0x0a8 = 0;
	m_unk0x0ac = 0;
	m_unk0x0b0 = 0;
	m_unk0x0b4 = 0;
	m_unk0x0b8 = 0;
	m_unk0x0bc = 0;
	m_unk0x0c0 = 0;
	m_unk0x0c4 = 0;
	m_unk0x0c8 = 0;
	m_unk0x0cc = 0;
	m_unk0x0d0 = 0;
	m_unk0x0d4 = 0;
	m_unk0x0d8 = 0;
	m_unk0x0dc = 0;
}

// FUNCTION: LEGORACERS 0x0045d510
void RaceSession::Field0x6dc::Field0x18b8::FUN_0045d510(const SetupParams* p_params)
{
	if (m_unk0x004 != 0) {
		FUN_0045d540();
	}

	m_unk0x0ac = p_params->m_unk0x00;
	m_unk0x0b0 = p_params->m_unk0x04;
	m_unk0x004 = 1;
}

// FUNCTION: LEGORACERS 0x0045d540
void RaceSession::Field0x6dc::Field0x18b8::FUN_0045d540()
{
	VTable0x1c();
	FUN_0045d4b0();
}
