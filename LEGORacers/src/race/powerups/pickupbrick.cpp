#include "race/powerups/pickupbrick.h"

#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "decomp.h"
#include "menu/runtime/cutsceneparticle.h"
#include "race/racer/racer.h"
#include "render/gold3drenderdevice.h"

#include <float.h>
#include <math.h>

extern const LegoFloat g_brickScalePercentBase;
extern const LegoFloat g_ghostSampleFractionScale;

extern const LegoFloat g_brickScalePercentBase;

// GLOBAL: LEGORACERS 0x004b0400
extern const LegoFloat g_brickSettleRate = 0.002f;

// GLOBAL: LEGORACERS 0x004b14ac
const LegoFloat g_brickScale = 0.8f;

// GLOBAL: LEGORACERS 0x004c75f4
LegoFloat g_brickScalePercentInverse = 1.0f / g_brickScalePercentBase;

// GLOBAL: LEGORACERS 0x004c75f8
LegoFloat g_brickShrinkPercentPerMs = g_ghostSampleFractionScale * g_brickScalePercentBase;

// FUNCTION: LEGORACERS 0x00453910
PickupBrick::PickupBrick()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453960
PickupBrick::~PickupBrick()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00453970
LegoS32 PickupBrick::Reset()
{
	m_scale = 1.0f;
	m_model = NULL;
	m_blendModel = NULL;
	m_manager = NULL;
	m_soundSource = NULL;
	m_state = c_stateInactive;
	m_nextState = c_stateWait;
	m_stateTimerMs = 0;
	m_respawnMs = 3000;
	m_flags = 0;

	return 0;
}

// FUNCTION: LEGORACERS 0x004539b0
void PickupBrick::Initialize(
	RacePowerupManager* p_owner,
	RacerSoundSource* p_soundResource,
	GolVec3* p_position,
	GolModelEntity* p_model0,
	GolModelEntity* p_model1
)
{
	if (m_manager != NULL) {
		Destroy();
	}

	m_manager = p_owner;
	m_soundSource = p_soundResource;
	m_blendModel = p_model1;
	m_model = p_model0;
	m_worldEntity.SetPosition(*p_position);
	m_state = c_stateWait;
	m_stateTimerMs = 3000;
}

// FUNCTION: LEGORACERS 0x00453a00
void PickupBrick::Respawn()
{
	m_state = c_stateWait;
	m_stateTimerMs = 3000;
}

// FUNCTION: LEGORACERS 0x00453a10
void PickupBrick::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00453a20
void PickupBrick::Update(LegoU32 p_elapsedMs)
{
	if (m_state == c_stateInactive) {
		return;
	}

	LegoU32 elapsedMs = p_elapsedMs + m_stateTimerMs;
	m_stateTimerMs = elapsedMs;

	LegoS32 stateOffset = m_state - c_stateActive;
	if (stateOffset != 0) {
		if (stateOffset == 1 && elapsedMs <= 250) {
			LegoFloat transition = (LegoS32) (250 - elapsedMs) * g_brickShrinkPercentPerMs;
			m_scale = transition * (g_brickScale * g_brickScalePercentInverse);
		}
	}
	else {
		if (elapsedMs < 400) {
			m_scale = (LegoS32) elapsedMs * 0.0024999999f;
		}
		else if (elapsedMs < 500) {
			m_scale = 1.0f - (LegoS32) (elapsedMs - 400) * g_brickSettleRate;
		}
	}

	LegoU8 flags = m_flags;
	if (flags & c_flagTouched) {
		m_flags = (flags & ~(c_flagTouched | c_flagWasTouched)) | c_flagWasTouched;
	}
	else {
		m_flags = flags & ~c_flagWasTouched;
	}
}

// FUNCTION: LEGORACERS 0x00453ad0
void PickupBrick::SetTouchable(LegoBool32 p_touchable)
{
	if (p_touchable) {
		m_scale = g_brickScale;
	}
	else {
		m_scale = 0.0f;
	}
}

// FUNCTION: LEGORACERS 0x00453af0
void PickupBrick::OnEvent(LegoEventQueue::CallbackData* p_data)
{
	m_flags |= c_flagTouched;

	if (m_state == c_stateIdle) {
		Racer* racer = static_cast<Racer*>(p_data->m_data);
		if (!(racer->GetFlags() & c_flagGhost)) {
			if (!(m_flags & c_flagWasTouched) || racer->GetHeldPowerupColor() == 0) {
				OnTouched(racer);
			}
		}
	}
}

// FUNCTION: LEGORACERS 0x00453b30
void PickupBrick::Draw(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateInactive &&
		(m_state == c_stateActive || m_state == c_stateIdle || m_state == c_stateTransition)) {
		GolVec3 position;
		m_worldEntity.GetPosition(&position);
		m_model->SetPosition(position);
		m_model->SetScaleThenInvalidateRadius(m_scale);
		m_model->Draw(*p_renderer);
	}
}

// FUNCTION: LEGORACERS 0x00453b90
void PickupBrick::DrawTransparent(GolD3DRenderDevice* p_renderer)
{
	if (m_state != c_stateInactive &&
		(m_state == c_stateActive || m_state == c_stateIdle || m_state == c_stateTransition)) {
		GolVec3 position;
		m_worldEntity.GetPosition(&position);
		m_blendModel->SetPosition(position);
		m_blendModel->SetScaleThenInvalidateRadius(m_scale);
		m_blendModel->Draw(*p_renderer);
	}
}
