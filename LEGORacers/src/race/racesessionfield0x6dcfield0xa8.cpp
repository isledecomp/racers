#include "race/racesessionfield0x6dcfield0xa8.h"

#include "decomp.h"
#include "golconstants.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceSessionField0x6dcField0xa8, 0xa8)

// FUNCTION: LEGORACERS 0x00430ca0
RaceSessionField0x6dcField0xa8::RaceSessionField0x6dcField0xa8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00430cc0
RaceSessionField0x6dcField0xa8* RaceSessionField0x6dcField0xa8::VTable0x10(undefined4 p_flags)
{
	RaceSessionField0x6dcField0xa8* result = this;
	this->~RaceSessionField0x6dcField0xa8();
	if (p_flags & 1) {
		::operator delete(result);
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00430ce0
RaceSessionField0x6dcField0xa8::~RaceSessionField0x6dcField0xa8()
{
	VTable0x14();
}

// FUNCTION: LEGORACERS 0x00430cf0
void RaceSessionField0x6dcField0xa8::Reset()
{
	m_unk0x048 = 5.0f;
	m_unk0x004 = 0;
	m_unk0x008 = 0;
	m_unk0x00c = 0;
	m_unk0x010.m_x = 0.0f;
	m_unk0x010.m_y = 0.0f;
	m_unk0x010.m_z = 0.0f;
	m_unk0x01c.m_x = 0.0f;
	m_unk0x01c.m_y = 0.0f;
	m_unk0x01c.m_z = 0.0f;
	m_unk0x04c = 0;
	m_unk0x034 = 0;
	m_unk0x038 = 0;
	m_unk0x03c = 0;
	m_unk0x040 = 0;
	m_unk0x044 = NULL;
	m_unk0x050 = 0;
	m_unk0x054 = 0;
	m_unk0x058 = 0;
	m_unk0x0a4 = 0;
	m_unk0x09c = 0;
}

// FUNCTION: LEGORACERS 0x00430d40
void RaceSessionField0x6dcField0xa8::FUN_00430d40(Params* p_params)
{
	m_unk0x008 = p_params->m_unk0x00;
	m_unk0x00c = p_params->m_unk0x04;
	m_unk0x040 = p_params->m_unk0x08;
	m_unk0x058 = p_params->m_unk0x20;
	m_unk0x048 = p_params->m_unk0x24;
	m_unk0x050 = 0;
	m_unk0x004 = 1;
	m_unk0x0a4 = NULL;
}

// STUB: LEGORACERS 0x00430d80
void RaceSessionField0x6dcField0xa8::VTable0x0c(
	Params* p_params,
	RaceState::Racer* p_racer,
	RaceState::Racer* p_targetRacer,
	LegoBool32 p_unk0x10,
	LegoBool32 p_unk0x14
)
{
	Params* params = p_params;
	RaceState::Racer* targetRacer = p_targetRacer;
	FUN_00430d40(params);

	LegoFloat speed = params->m_unk0x1c;
	m_unk0x0a0 = targetRacer;
	m_unk0x09c = p_racer;
	if (p_unk0x10) {
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x010);
		m_unk0x010.m_z += m_unk0x048;
		m_unk0x008->VTable0x08(m_unk0x010);
	}
	else {
		m_unk0x008->VTable0x04(&m_unk0x010);
	}

	GolVec3* startPosition = &m_unk0x010;
	GolVec3* target = &m_unk0x01c;
	targetRacer->m_unk0x018.m_unk0x044->VTable0x04(target);
	target->m_z += 5.0f;

	GolVec3 scaledVelocity;
	GolVec3 targetVelocity = targetRacer->m_unk0x3e8.m_unk0x008;
	GolVec3 racerDirection;
	GolVec3 delta;
	delta.m_x = target->m_x - startPosition->m_x;
	delta.m_y = m_unk0x01c.m_y - m_unk0x010.m_y;
	LegoFloat deltaY = delta.m_y;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(deltaY * deltaY + delta.m_x * delta.m_x));
	LegoFloat inverseDistance;
	if (distance == 0.0f) {
		distance = 1.0f;
		inverseDistance = 1.0f;
	}
	else {
		inverseDistance = 1.0f / distance;
	}

	LegoFloat directionX = inverseDistance * delta.m_x;
	RaceState::Racer* racer = p_racer;
	racerDirection = racer->m_unk0x3e8.m_unk0x5f8;
	LegoFloat directionY = inverseDistance * deltaY;
	LegoFloat dot = racerDirection.m_z * 0.0f + racerDirection.m_y * directionY + racerDirection.m_x * directionX;
	if (dot < 0.0f) {
		dot = -dot;
	}

	speed += dot * racer->m_unk0x3e8.m_unk0x604 * g_floatConst1000;
	if (speed <= 0.001f) {
		speed = 0.001f;
	}

	speed = distance / speed;
	LegoFloat durationMs = speed * g_floatConst1000;
	m_unk0x054 = static_cast<LegoS32>(durationMs);
	scaledVelocity.m_x = targetVelocity.m_x * durationMs;
	scaledVelocity.m_y = targetVelocity.m_y * durationMs;
	scaledVelocity.m_z = targetVelocity.m_z * durationMs;

	if (p_unk0x14) {
		GolVec3 predictedTarget;
		predictedTarget.m_x = target->m_x + scaledVelocity.m_x;
		predictedTarget.m_y = target->m_y + scaledVelocity.m_y;
		predictedTarget.m_z = target->m_z + scaledVelocity.m_z;

		GolVec3 racerVector = p_racer->m_unk0x3e8.m_unk0x168;
		GolVec3 predictedDelta;
		predictedDelta.m_x = predictedTarget.m_x - startPosition->m_x;
		predictedDelta.m_y = predictedTarget.m_y - startPosition->m_y;
		predictedDelta.m_z = predictedTarget.m_z - startPosition->m_z;
		LegoFloat predictedDot = racerVector.m_z * predictedDelta.m_z;
		predictedDot += racerVector.m_y * predictedDelta.m_y;
		predictedDot += racerVector.m_x * predictedDelta.m_x;
		if (predictedDot < 0.0f) {
			*target = predictedTarget;
		}
	}
	else {
		target->m_x += scaledVelocity.m_x;
		target->m_y += scaledVelocity.m_y;
		target->m_z += scaledVelocity.m_z;
	}

	target->m_x += params->m_unk0x10.m_x;
	target->m_y += params->m_unk0x10.m_y;
	target->m_z += params->m_unk0x10.m_z;
	FUN_00431450(speed);
	FUN_004314d0(params->m_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00431050
void RaceSessionField0x6dcField0xa8::VTable0x08(
	Params* p_params,
	RaceState::Racer* p_racer,
	GolVec3* p_unk0x0c,
	GolVec3* p_unk0x10,
	LegoBool32 p_unk0x14
)
{
	Params* params = p_params;
	FUN_00430d40(params);

	LegoFloat speed = params->m_unk0x1c;
	m_unk0x01c = *p_unk0x0c;
	m_unk0x0a0 = NULL;
	m_unk0x09c = p_racer;
	if (p_unk0x14) {
		p_racer->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x010);
		m_unk0x010.m_z += m_unk0x048;
		m_unk0x008->VTable0x08(m_unk0x010);
	}
	else {
		m_unk0x008->VTable0x04(&m_unk0x010);
	}

	GolVec3* startPosition = &m_unk0x010;
	GolVec3* target = &m_unk0x01c;
	GolVec3 delta;
	delta.m_x = target->m_x - startPosition->m_x;
	delta.m_y = m_unk0x01c.m_y - m_unk0x010.m_y;
	LegoFloat deltaY = delta.m_y;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(deltaY * deltaY + delta.m_x * delta.m_x));
	LegoFloat inverseDistance;
	if (distance == 0.0f) {
		distance = 1.0f;
		inverseDistance = 1.0f;
	}
	else {
		inverseDistance = 1.0f / distance;
	}

	LegoFloat directionX = inverseDistance * delta.m_x;
	RaceState::Racer* racer = p_racer;
	GolVec3 racerDirection = racer->m_unk0x3e8.m_unk0x5f8;
	GolVec3* racerDirectionPtr = &racerDirection;
	LegoFloat directionY = inverseDistance * deltaY;
	LegoFloat dot = racerDirectionPtr->m_z * 0.0f;
	dot += racerDirectionPtr->m_y * directionY;
	dot += racerDirectionPtr->m_x * directionX;
	if (dot > 0.0f) {
		LegoFloat speedDelta = dot * racer->m_unk0x3e8.m_unk0x604;
		speedDelta *= g_floatConst1000;
		speed += speedDelta;
	}

	LegoFloat durationSeconds = distance / speed;
	LegoFloat scaledDuration = durationSeconds;
	scaledDuration *= g_floatConst1000;
	m_unk0x054 = static_cast<LegoS32>(scaledDuration);
	GolVec3 scaledDelta;
	scaledDelta.m_x = p_unk0x10->m_x * durationSeconds;
	scaledDelta.m_y = p_unk0x10->m_y;
	scaledDelta.m_y *= durationSeconds;
	scaledDelta.m_z = p_unk0x10->m_z;
	scaledDelta.m_z *= durationSeconds;
	target->m_x += scaledDelta.m_x;
	target->m_y += scaledDelta.m_y;
	target->m_z += scaledDelta.m_z;
	target->m_x += params->m_unk0x10.m_x;
	target->m_y += params->m_unk0x10.m_y;
	target->m_z += params->m_unk0x10.m_z;
	FUN_00431450(durationSeconds);
	FUN_004314d0(params->m_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00431220
void RaceSessionField0x6dcField0xa8::VTable0x04(Params* p_params, GolVec3* p_unk0x08)
{
	FUN_00430d40(p_params);

	m_unk0x01c.m_x = p_params->m_unk0x10.m_x + p_unk0x08->m_x;
	m_unk0x01c.m_y = p_params->m_unk0x10.m_y + p_unk0x08->m_y;
	m_unk0x01c.m_z = p_params->m_unk0x10.m_z + p_unk0x08->m_z;
	m_unk0x09c = NULL;
	m_unk0x0a0 = NULL;
	m_unk0x008->VTable0x04(&m_unk0x010);

	GolVec3 delta;
	delta.m_x = m_unk0x01c.m_x - m_unk0x010.m_x;
	delta.m_y = m_unk0x01c.m_y - m_unk0x010.m_y;
	m_unk0x04c = p_params->m_unk0x1c;
	delta.m_z = m_unk0x01c.m_z - m_unk0x010.m_z;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	LegoFloat durationSeconds = p_params->m_unk0x1c;
	durationSeconds = distance / durationSeconds;
	LegoFloat scaledDuration = durationSeconds;
	scaledDuration *= g_floatConst1000;
	m_unk0x054 = static_cast<LegoS32>(scaledDuration);

	LegoFloat inverseDuration = 1.0f;
	inverseDuration /= durationSeconds;
	m_unk0x034 = inverseDuration * delta.m_x;
	m_unk0x038 = inverseDuration * delta.m_y;

	LegoFloat zVelocity = delta.m_z;
	zVelocity /= distance;
	zVelocity *= p_params->m_unk0x1c;
	m_unk0x03c = zVelocity;
	LegoFloat acceleration = m_unk0x040;
	m_unk0x03c = zVelocity - (acceleration * distance) / (p_params->m_unk0x1c + p_params->m_unk0x1c);
	FUN_004314d0(p_params->m_unk0x0c);
}

// STUB: LEGORACERS 0x00431310
void RaceSessionField0x6dcField0xa8::FUN_00431310(RaceState::Racer* p_racer)
{
	GolVec3 velocity;
	velocity.m_x = 0.0f;
	velocity.m_y = 0.0f;
	velocity.m_z = 0.0f;

	m_unk0x050 = 0;
	m_unk0x004 = 1;
	m_unk0x0a0 = m_unk0x09c;
	if (m_unk0x0a0) {
		m_unk0x0a0->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x01c);
		m_unk0x01c.m_z += 5.0f;
		velocity = m_unk0x0a0->m_unk0x3e8.m_unk0x008;
	}
	else {
		m_unk0x01c = m_unk0x010;
	}

	m_unk0x09c = p_racer;
	m_unk0x008->VTable0x04(&m_unk0x010);
	m_unk0x0a4 = NULL;

	GolVec3 delta;
	delta.m_x = m_unk0x01c.m_x - m_unk0x010.m_x;
	delta.m_y = m_unk0x01c.m_y - m_unk0x010.m_y;
	delta.m_z = m_unk0x01c.m_z - m_unk0x010.m_z;
	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	if (distance == 0.0f) {
		distance = 1.0f;
	}

	LegoFloat durationSeconds = distance / m_unk0x04c;
	LegoFloat durationMs = durationSeconds * g_floatConst1000;
	m_unk0x054 = static_cast<LegoS32>(durationMs);

	m_unk0x01c.m_x += velocity.m_x * durationSeconds;
	m_unk0x01c.m_y += velocity.m_y * durationSeconds;
	m_unk0x01c.m_z += velocity.m_z * durationSeconds;
	FUN_00431450(durationSeconds);
}

// FUNCTION: LEGORACERS 0x00431450
void RaceSessionField0x6dcField0xa8::FUN_00431450(LegoFloat p_durationSeconds)
{
	LegoFloat inverseDuration = 1.0f;
	inverseDuration /= p_durationSeconds;

	GolVec3 delta;
	delta.m_x = m_unk0x01c.m_x - m_unk0x010.m_x;
	delta.m_y = m_unk0x01c.m_y - m_unk0x010.m_y;
	delta.m_z = m_unk0x01c.m_z - m_unk0x010.m_z;

	LegoFloat distance = static_cast<LegoFloat>(sqrt(delta.m_y * delta.m_y + delta.m_x * delta.m_x));
	LegoFloat speed = distance * inverseDuration;
	m_unk0x04c = speed;
	m_unk0x034 = delta.m_x * inverseDuration;
	m_unk0x038 = delta.m_y * inverseDuration;

	LegoFloat zVelocity = delta.m_z / distance * speed;
	LegoFloat acceleration = m_unk0x040;
	m_unk0x03c = zVelocity - (acceleration * distance) / (speed + speed);
}

// FUNCTION: LEGORACERS 0x004314d0
void RaceSessionField0x6dcField0xa8::FUN_004314d0(LegoEventQueue* p_eventQueue)
{
	if (m_unk0x044 != NULL) {
		m_unk0x044->m_active = 0;
	}

	if (p_eventQueue != NULL) {
		LegoEventQueue::Callback* callback = this;
		LegoEventQueue::Descriptor descriptor;
		descriptor.m_unk0x08 = 0;
		descriptor.m_unk0x0c = 0;
		descriptor.m_unk0x00 = 4;
		descriptor.m_unk0x04 = 1;
		descriptor.m_data = m_unk0x008;
		m_unk0x044 = p_eventQueue->FUN_0042fb50(callback, &descriptor);
	}
	else {
		m_unk0x044 = NULL;
	}
}

// FUNCTION: LEGORACERS 0x00431530
void RaceSessionField0x6dcField0xa8::VTable0x14()
{
	if (m_unk0x044 != NULL) {
		m_unk0x044->m_active = 0;
		m_unk0x044 = NULL;
	}

	Reset();
}

// FUNCTION: LEGORACERS 0x00431550
LegoS32 RaceSessionField0x6dcField0xa8::VTable0x18(LegoU32 p_elapsedMs)
{
	LegoU32 state = m_unk0x004;
	if (state != 1) {
		return state;
	}

	m_unk0x050 += p_elapsedMs;
	p_elapsedMs = m_unk0x050;
	if (p_elapsedMs >= m_unk0x058) {
		m_unk0x004 = 4;
		m_unk0x008->VTable0x04(&m_unk0x028);
		return 4;
	}

	LegoFloat elapsed = static_cast<LegoS32>(p_elapsedMs) * 0.001f;
	GolVec3 vectors[2];
	vectors[0].m_x = (vectors[1].m_y = m_unk0x038 * elapsed, vectors[1].m_z = m_unk0x03c * elapsed, m_unk0x010.m_x) +
					 elapsed * m_unk0x034;
	vectors[0].m_y = vectors[1].m_y + m_unk0x010.m_y;
	vectors[0].m_z = (vectors[1].m_z + m_unk0x010.m_z) + m_unk0x040 * 0.5f * elapsed * elapsed;
	m_unk0x008->VTable0x04(&vectors[1]);

	GolBoundingVolume::Field0x0c record;
	if (m_unk0x00c->FUN_0041f730(&vectors[1], &vectors[0], &record, &m_unk0x028)) {
		m_unk0x05c.m_x = record.m_unk0x24.m_x;
		m_unk0x05c.m_y = record.m_unk0x24.m_y;
		m_unk0x05c.m_z = record.m_unk0x24.m_z;
		m_unk0x008->VTable0x08(m_unk0x028);
		m_unk0x004 = 3;
		return 3;
	}

	m_unk0x008->VTable0x08(vectors[0]);
	return 1;
}

// FUNCTION: LEGORACERS 0x00431660
void RaceSessionField0x6dcField0xa8::VTable0x00(LegoEventQueue::CallbackData* p_data)
{
	RaceState::Racer* previousContext = m_unk0x09c;
	if (p_data->m_data != previousContext && m_unk0x004 == 1) {
		m_unk0x004 = 2;
		RaceState::Racer* racer = static_cast<RaceState::Racer*>(p_data->m_data);
		m_unk0x0a4 = racer;
		racer->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x028);
	}
}

// FUNCTION: LEGORACERS 0x004316a0
void RaceSessionField0x6dcField0xa8::VTable0x1c(GolVec3* p_unk0x04)
{
	p_unk0x04->m_x = m_unk0x034;
	p_unk0x04->m_y = m_unk0x038;
	LegoFloat z = static_cast<LegoS32>(m_unk0x050) * 0.001f;
	p_unk0x04->m_z = z * m_unk0x040 + m_unk0x03c;
}

// FUNCTION: LEGORACERS 0x004316d0
void RaceSessionField0x6dcField0xa8::FUN_004316d0()
{
	if (m_unk0x044 != NULL) {
		m_unk0x044->m_active = 0;
		m_unk0x044 = NULL;
	}
}
