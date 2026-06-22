#include "decomp.h"
#include "race/racesession.h"
#include "render/golcommondrawstate.h"
#include "render/gold3drenderdevice.h"

DECOMP_SIZE_ASSERT(RaceSession::Field0x6dc::Field0x270, 0x270)

// GLOBAL: LEGORACERS 0x004b0150
LegoFloat g_unk0x004b0150 = 80.0f;

// GLOBAL: LEGORACERS 0x004b0154
LegoFloat g_unk0x004b0154 = 200.0f;

// GLOBAL: LEGORACERS 0x004b015c
LegoFloat g_unk0x004b015c = 180.0f;

extern const LegoFloat g_violetShoalTwo;

// FUNCTION: LEGORACERS 0x004210b0
RaceSession::Field0x6dc::Field0x270::Field0x270()
{
	m_unk0x204.FUN_004a00b0();
	m_unk0x04 = 0;
	m_unk0x030 = NULL;
	m_unk0x0c4 = NULL;
	m_unk0x200 = NULL;
	m_unk0x210 = NULL;
	m_unk0x214 = NULL;
	m_unk0x218 = NULL;
	m_unk0x21c = 0;
	m_unk0x220 = NULL;
	m_unk0x224 = NULL;
	m_unk0x228 = 0;
	m_unk0x230 = 0;
	m_unk0x234 = 0;
	m_unk0x23c = 0.0f;
	m_unk0x240 = 0.0f;
	m_unk0x238 = 0;
	m_unk0x244 = 100.0f;
	m_unk0x258 = 1.0f;
	m_unk0x25c = 1.0f;
	m_unk0x260 = 1.0f;
	m_unk0x264 = 1.0f;
	m_next = NULL;
	m_unk0x268 = 0;
	m_unk0x22c = 0;
	m_unk0x248 = g_violetShoalTwo;
	m_unk0x24c = 0.0f;
	m_unk0x250 = 0.0f;
	m_unk0x254 = 0.0f;
}

// FUNCTION: LEGORACERS 0x004211e0
RaceSession::Field0x6dc::Field0x270::~Field0x270()
{
	FUN_004214b0();
	m_unk0x204.Destroy();
}

// FUNCTION: LEGORACERS 0x00421250
void RaceSession::Field0x6dc::Field0x270::FUN_00421250(const Params* p_params)
{
	if (m_unk0x04 != 0) {
		FUN_004214b0();
	}

	m_unk0x030 = p_params->m_unk0x00;
	m_unk0x200 = p_params->m_unk0x04;
	m_unk0x210 = p_params->m_unk0x10;
	m_unk0x214 = p_params->m_unk0x14;
	m_unk0x218 = p_params->m_unk0x18;
	m_unk0x224 = p_params->m_unk0x1c;
	m_unk0x228 = p_params->m_unk0x28;
	m_unk0x0e0 = p_params->m_unk0x24;
	m_unk0x230 = p_params->m_unk0x2c;
	m_unk0x234 = p_params->m_unk0x30;
	m_unk0x258 = p_params->m_unk0x34;
	m_unk0x25c = p_params->m_unk0x38;
	m_unk0x260 = p_params->m_unk0x3c;
	m_unk0x264 = p_params->m_unk0x40;
	m_unk0x22c = p_params->m_unk0x44;

	LegoFloat rate = 1.0f / (static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x230)) * 0.001f);
	m_unk0x250 = rate + rate;
	LegoFloat rateDelta = (1.0f - 0.050000001f) - m_unk0x250;
	m_unk0x254 = (rateDelta + rateDelta) * (rate * rate);

	LegoFloat endRate = g_unk0x004b015c / (static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x234)) * 0.001f);
	m_unk0x238 = 0;
	m_unk0x244 = -endRate;

	if (p_params->m_unk0x0c != NULL || p_params->m_unk0x20 != NULL) {
		m_unk0x0c4 = m_unk0x030->CreateBillboard();
	}

	if (p_params->m_unk0x20 != NULL) {
		m_unk0x0c8.FUN_004103c0(*p_params->m_unk0x20);
		m_unk0x0c8.FUN_10025da0(m_unk0x224->GetBillboardMaterialTable(), m_unk0x0e0, FALSE);
		m_unk0x0c8
			.FUN_004104c0(0, m_unk0x224->GetMaterialAnimationItems(), m_unk0x224->GetMaterialAnimationItemCount());
		m_unk0x0c4->FUN_10029e90(m_unk0x224->GetBillboardMaterialTable(), m_unk0x0e0, 0.1f, 0.2f, 250000.0f);
	}
	else if (m_unk0x0c4 != NULL) {
		m_unk0x0c4->VTable0x4c(p_params->m_unk0x0c, 0.1f, 0.2f, 250000.0f);
	}

	if (p_params->m_unk0x08 != NULL) {
		m_unk0x034.VTable0x50(p_params->m_unk0x08->GetModel(0), 250000.0f);
		m_unk0x034.FUN_00411680(p_params->m_unk0x08->FUN_00411640());
		m_unk0x034.FUN_004116b0(p_params->m_unk0x08->FUN_00411660());
		m_unk0x034.FUN_00411700(p_params->m_unk0x08->FUN_004116e0());
		m_unk0x034.FUN_00411730(p_params->m_unk0x08->FUN_004116f0());
	}

	GolD3DRenderDevice* renderer = m_unk0x030->GetDrawState()->m_currentRenderer;
	m_unk0x204.Initialize(renderer, 1);
	m_unk0x0e4.FUN_00414950(m_unk0x030, renderer, 10);
	m_unk0x0e4.GetUnk0x010().SetPrimaryMaterialTable(&m_unk0x204);
	m_unk0x04 = 1;
}

// FUNCTION: LEGORACERS 0x004214b0
void RaceSession::Field0x6dc::Field0x270::FUN_004214b0()
{
	FUN_004217b0();
	m_unk0x0e4.FUN_004149f0();
	m_unk0x204.Clear();
	m_unk0x034.VTable0x54();

	if (m_unk0x030 != NULL && m_unk0x0c4 != NULL) {
		m_unk0x0c4->VTable0x50();
		m_unk0x030->VTable0x64(m_unk0x0c4);
		m_unk0x0c4 = NULL;
	}

	m_unk0x0c8.Reset();
	m_unk0x04 = 0;
}

// STUB: LEGORACERS 0x00421520
void RaceSession::Field0x6dc::Field0x270::FUN_00421520(
	const GolVec3* p_position,
	undefined4 p_unk0x08,
	RaceState::Racer* p_racer
)
{
	LegoFloat negativeLimit = -2048.0f;
	if (p_position->m_x > 2048.0f || p_position->m_x < negativeLimit || p_position->m_y > 2048.0f ||
		p_position->m_y < negativeLimit || p_position->m_z > 2048.0f || p_position->m_z < negativeLimit) {
		m_unk0x04 = 1;
		return;
	}

	m_unk0x04 = 2;
	m_unk0x238 = m_unk0x230;
	m_unk0x268 = p_unk0x08;
	m_unk0x21c = p_racer;
	m_unk0x23c = 255.0f;
	m_unk0x240 = 0.0f;
	m_unk0x248 = 0.050000001f;
	m_unk0x24c = m_unk0x250;

	m_unk0x008.VTable0x08(*p_position);
	m_unk0x008.FUN_10026fa0(0.1f);

	if (m_unk0x0c4 != NULL) {
		m_unk0x0c4->SetWidth(0.1f);
		m_unk0x0c4->SetHeight(0.2f);
		m_unk0x0c4->VTable0x08(*p_position);
	}

	if (m_unk0x034.HasModel()) {
		m_unk0x034.SetUnk0x58ThenInvalidateRadius(0.050000001f);
		m_unk0x034.VTable0x08(*p_position);
	}

	m_unk0x0e4.m_unk0x0e8.m_x = p_position->m_x;
	m_unk0x0e4.m_unk0x0e8.m_y = p_position->m_y;
	m_unk0x0e4.m_unk0x0e8.m_z = p_position->m_z + 5.0f;

	GolVec3 forward;
	forward.m_x = 0.0f;
	forward.m_y = 0.0f;
	forward.m_z = -1.0f;

	GolVec3 up;
	up.m_x = 1.0f;
	up.m_y = 0.0f;
	up.m_z = 0.0f;
	m_unk0x0e4.FUN_00414c90(&forward, &up);

	if (m_unk0x220 != NULL) {
		m_unk0x220->m_active = 0;
	}

	if (m_unk0x218 != NULL) {
		LegoEventQueue::Callback* callback = this;
		LegoEventQueue::Descriptor descriptor;
		descriptor.m_unk0x00 = 4;
		descriptor.m_unk0x04 = 1;
		descriptor.m_unk0x08 = 0;
		descriptor.m_unk0x0c = 0;
		descriptor.m_data = &m_unk0x008;
		m_unk0x220 = m_unk0x218->FUN_0042fb50(callback, &descriptor);
	}
	else {
		m_unk0x220 = NULL;
	}

	if (m_unk0x0c8.IsConfigured()) {
		m_unk0x0c8.FUN_00410470();
		m_unk0x0c8.FUN_00410480();
		m_unk0x0c8.FUN_10025da0(m_unk0x224->GetBillboardMaterialTable(), m_unk0x0e0, FALSE);
	}

	if (m_unk0x228 != NULL) {
		GolVec3 particlePosition;
		particlePosition.m_x = p_position->m_x;
		particlePosition.m_y = p_position->m_y;
		particlePosition.m_z = p_position->m_z;
		m_unk0x228->FUN_00489d70("explode", &particlePosition, NULL, NULL);
	}
}

// FUNCTION: LEGORACERS 0x004217b0
void RaceSession::Field0x6dc::Field0x270::FUN_004217b0()
{
	if (m_unk0x220 != NULL) {
		m_unk0x220->m_active = 0;
		m_unk0x220 = NULL;
	}

	m_unk0x04 = 1;
}

// FUNCTION: LEGORACERS 0x004217d0
void RaceSession::Field0x6dc::Field0x270::FUN_004217d0(LegoU32 p_elapsedMs)
{
	if (m_unk0x04 == 2) {
		FUN_00421850(p_elapsedMs);
	}

	if (m_unk0x04 == 3) {
		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		m_unk0x23c += elapsedSeconds * m_unk0x244;
		if (m_unk0x23c < 0.0f) {
			m_unk0x23c = 0.0f;
		}

		LegoU32 duration = m_unk0x238;
		if (p_elapsedMs >= duration) {
			m_unk0x238 = 0;
			FUN_004217b0();
		}
		else {
			m_unk0x238 = duration - p_elapsedMs;
		}
	}
}

// FUNCTION: LEGORACERS 0x00421850
void RaceSession::Field0x6dc::Field0x270::FUN_00421850(LegoU32 p_elapsedMs)
{
	LegoS32 zero = 0;
	if (m_unk0x04 != zero && m_unk0x04 != 1) {
		LegoU32 duration = m_unk0x238;
		if (p_elapsedMs >= duration) {
			if (m_unk0x214 != NULL && m_unk0x268 != zero) {
				if (m_unk0x220 != NULL) {
					m_unk0x220->m_active = 0;
					m_unk0x220 = NULL;
				}

				LegoU32 finishDuration = m_unk0x234;
				m_unk0x04 = 3;
				LegoFloat width = m_unk0x25c;
				LegoFloat width2 = m_unk0x25c;
				m_unk0x238 = finishDuration;
				m_unk0x23c = g_unk0x004b015c;
				m_unk0x0e4.m_unk0x104 = width;
				m_unk0x0e4.m_unk0x108 = width2;
				m_unk0x0e4.m_unk0x10c = 15.0f;
				m_unk0x0e4.FUN_00414a30(m_unk0x200);
			}
			else {
				FUN_004217b0();
			}

			return;
		}

		m_unk0x238 = duration - p_elapsedMs;

		LegoFloat elapsedSeconds = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs)) * 0.001f;
		LegoFloat acceleration = m_unk0x254;
		m_unk0x24c = acceleration * elapsedSeconds + m_unk0x24c;
		m_unk0x248 = elapsedSeconds * m_unk0x24c + m_unk0x248;

		LegoFloat radius = (m_unk0x264 - 0.1f) * m_unk0x248 + 0.1f;
		m_unk0x008.FUN_10026fa0(radius);

		LegoFloat width = (m_unk0x25c - 0.1f) * m_unk0x248 + 0.1f;
		if (m_unk0x214 != NULL && m_unk0x268 != zero) {
			m_unk0x204.SetPosition(0, m_unk0x214);
			m_unk0x0e4.m_unk0x104 = width;
			m_unk0x0e4.m_unk0x108 = width;
			m_unk0x0e4.m_unk0x10c = 15.0f;
			m_unk0x0e4.FUN_00414a30(m_unk0x200);
		}

		if (m_unk0x0c4 != NULL) {
			m_unk0x0c4->SetWidth(width);
			m_unk0x0c4->SetHeight((m_unk0x260 - 0.2f) * m_unk0x248 + 0.2f);
		}

		LegoFloat value = (m_unk0x258 - 0.050000001f) * m_unk0x248 + 0.050000001f;
		if (value > 1.0f) {
			value = 1.0f;
		}

		if (m_unk0x034.HasModel()) {
			m_unk0x034.SetUnk0x58ThenInvalidateRadius(value);
		}

		m_unk0x23c = (g_violetShoalTwo - (m_unk0x248 + m_unk0x248)) * 255.0f;
		if (m_unk0x23c < 0.0f) {
			m_unk0x23c = 0.0f;
		}
		else if (m_unk0x23c > 255.0f) {
			m_unk0x23c = 255.0f;
		}

		m_unk0x240 = (1.0f - m_unk0x248) * 255.0f;
		if (m_unk0x240 < 0.0f) {
			m_unk0x240 = 0.0f;
		}

		if (m_unk0x0c8.IsConfigured()) {
			m_unk0x0c8.FUN_004104c0(
				p_elapsedMs,
				m_unk0x224->GetMaterialAnimationItems(),
				m_unk0x224->GetMaterialAnimationItemCount()
			);
		}
	}
}

// FUNCTION: LEGORACERS 0x00421ae0
void RaceSession::Field0x6dc::Field0x270::FUN_00421ae0(GolD3DRenderDevice* p_renderer)
{
	if (m_unk0x04 == 0 || m_unk0x04 == 1) {
		return;
	}

	if (m_unk0x04 == 2) {
		if (m_unk0x214 != 0 && m_unk0x268 != 0) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(g_unk0x004b015c), 2);
			m_unk0x0e4.FUN_00415a40(p_renderer);
		}

		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x23c), 1);

		if (m_unk0x0c4 != NULL) {
			p_renderer->VTable0xb4(*m_unk0x0c4);
		}

		if (m_unk0x034.HasModel()) {
			p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x240), 1);
			m_unk0x034.VTable0x1c(*p_renderer);
		}

		p_renderer->ClearAlphaOverride();
		return;
	}

	if (m_unk0x04 == 3 && m_unk0x214 != 0 && m_unk0x268 != 0) {
		p_renderer->SetAlphaOverride(static_cast<LegoS32>(m_unk0x23c), 2);
		m_unk0x0e4.FUN_00415a40(p_renderer);
		p_renderer->ClearAlphaOverride();
	}
}

// STUB: LEGORACERS 0x00421c00
void RaceSession::Field0x6dc::Field0x270::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	LegoU32 mode = m_unk0x22c;
	if (!mode) {
		return;
	}

	RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
	if (racer == m_unk0x21c) {
		return;
	}

	LegoU8 racerFlags = static_cast<LegoU8>(racer->m_unk0xd04);
	RaceState::Racer::Field0x3e8* field0x3e8 = &racer->m_unk0x3e8;
	if (racerFlags & c_racerFlags0xd04Bit0) {
		return;
	}

	mode--;
	if (mode) {
		if (--mode) {
			return;
		}

		if ((racer->m_unk0x3e8.m_flags0x6c0 & RaceState::Racer::Field0x3e8::c_flags0x6c0Bit7) &&
			racer->m_unk0xd08 != 2) {
			return;
		}

		GolVec3 direction = field0x3e8->m_unk0x168;
		racer->FUN_004397a0();

		GolVec3 impulse;
		GolVec3* impulseA = &impulse;
		GolVec3* impulseB = &impulse;
		impulseA->m_y = 0.0f;
		impulseA->m_z = 0.0f;
		field0x3e8->m_unk0x008.m_x = 0.0f;
		field0x3e8->m_unk0x008.m_y = impulseA->m_y;
		field0x3e8->m_unk0x008.m_z = impulseA->m_z;

		LegoFloat amount;
		LegoS32 duration = static_cast<LegoS32>(m_unk0x230);
		if (duration) {
			LegoFloat remaining = static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x238));
			LegoFloat durationFloat = static_cast<LegoFloat>(duration);
			amount = remaining / durationFloat;
			amount += amount;

			if (amount > 1.0f) {
				amount = 1.0f;
			}
			else if (amount < 0.0f) {
				amount = 0.0f;
			}
		}
		else {
			amount = 1.0f;
		}

		LegoFloat scale = amount * g_unk0x004b0150;
		impulseA->m_x = direction.m_x * scale;
		impulseA->m_y = direction.m_y * scale;
		impulseA->m_z = direction.m_z * scale;

		GolVec3 offset;
		GolVec3* offsetPtr = &offset;
		offsetPtr->m_x = 0.0f;
		offsetPtr->m_y = 0.0f;
		offsetPtr->m_z = amount * g_unk0x004b0154;
		impulseA->m_x += offsetPtr->m_x;
		impulseA->m_y += offsetPtr->m_y;
		impulseA->m_z += offsetPtr->m_z;

		field0x3e8->VTable0x1c(impulseA, impulseB);
		return;
	}

	if (!(field0x3e8->m_flags0x6c0 & RaceState::Racer::Field0x3e8::c_flags0x6c0Bit1)) {
		field0x3e8->VTable0x24(2.0f, 0.007f, 0);
	}
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void RaceSession::Field0x6dc::Field0x270::FUN_004513d0(GolD3DRenderDevice*)
{
}

// FUNCTION: LEGORACERS 0x004587b0
RaceSession::Field0x6dc::Field0x270* RaceSession::Field0x6dc::Field0x270::VTable0x04(undefined4 p_flags)
{
	Field0x270* result = this;
	if (p_flags & 2) {
		if (p_flags & 1) {
			delete[] this;
		}

		return result;
	}

	this->~Field0x270();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}
