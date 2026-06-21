#include "camera/golcamerabase.h"
#include "golfileparser.h"
#include "race/racestate.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x00c::Entry::PathPoint, 0x0c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8::Field0x198, 0x70)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8::CollisionCacheRecord, 0x3c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8::Field0x74c, 0x78)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0x3e8::Field0x74cInstance, 0x78)
DECOMP_SIZE_ASSERT(RaceState::Racer::Field0xc70::Field0x050, 0x78)

// GLOBAL: LEGORACERS 0x004b4bc8
extern const LegoFloat g_unk0x004b4bc8 = 0.001f;

// GLOBAL: LEGORACERS 0x004b4bcc
extern const LegoFloat g_unk0x004b4bcc = 0.00390625f;

// GLOBAL: LEGORACERS 0x004b4bd0
extern const LegoFloat g_unk0x004b4bd0 = 0.0625f;

// GLOBAL: LEGORACERS 0x004b4bd4
extern const LegoFloat g_unk0x004b4bd4 = 0.007874016f;

// GLOBAL: LEGORACERS 0x004b4bd8
extern const LegoFloat g_unk0x004b4bd8 = 0.125f;

// FUNCTION: LEGORACERS 0x004a5170 FOLDED
RaceState::Racer::Field0xc70::Field0x050::Field0x050()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5180 FOLDED
RaceState::Racer::Field0xc70::Field0x050::~Field0x050()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a5170 FOLDED
RaceState::Racer::Field0x3e8Base0x74c::Field0x74cInstance::Field0x74cInstance()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5180 FOLDED
RaceState::Racer::Field0x3e8Base0x74c::Field0x74cInstance::~Field0x74cInstance()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a5190 FOLDED
void RaceState::Racer::Field0xc70::Field0x050::Reset()
{
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_unk0x0c.m_x = 0.0f;
	m_unk0x0c.m_y = 0.0f;
	m_unk0x0c.m_z = 0.0f;
	m_unk0x0c.m_w = 1.0f;
	m_unk0x1c = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 1.0f;
	m_unk0x30 = 0;
	m_unk0x34 = 0xffffffff;
	m_unk0x38 = 0;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48.m_x = 0.0f;
	m_unk0x48.m_y = 0.0f;
	m_unk0x48.m_z = 0.0f;
	m_unk0x54.m_x = 0.0f;
	m_unk0x54.m_y = 0.0f;
	m_unk0x54.m_z = 0.0f;
	m_unk0x54.m_w = 1.0f;
	m_unk0x64.m_x = 0.0f;
	m_unk0x64.m_y = 0.0f;
	m_unk0x64.m_z = 0.0f;
	m_unk0x64.m_w = 1.0f;
	m_unk0x74 = 0;
}

// FUNCTION: LEGORACERS 0x004a5190 FOLDED
void RaceState::Racer::Field0x3e8::Field0x74c::Reset()
{
	m_unk0x00.m_x = 0.0f;
	m_unk0x00.m_y = 0.0f;
	m_unk0x00.m_z = 0.0f;
	m_unk0x0c.m_x = 0.0f;
	m_unk0x0c.m_y = 0.0f;
	m_unk0x0c.m_z = 0.0f;
	m_unk0x0c.m_w = 1.0f;
	m_unk0x1c = 0;
	m_unk0x28 = NULL;
	m_unk0x2c = 1.0f;
	m_unk0x30 = 0;
	m_unk0x34 = 0xffffffff;
	m_unk0x38 = 0;
	m_unk0x3c.m_x = 0.0f;
	m_unk0x3c.m_y = 0.0f;
	m_unk0x3c.m_z = 0.0f;
	m_unk0x48.m_x = 0.0f;
	m_unk0x48.m_y = 0.0f;
	m_unk0x48.m_z = 0.0f;
	m_unk0x54.m_x = 0.0f;
	m_unk0x54.m_y = 0.0f;
	m_unk0x54.m_z = 0.0f;
	m_unk0x54.m_w = 1.0f;
	m_unk0x64.m_x = 0.0f;
	m_unk0x64.m_y = 0.0f;
	m_unk0x64.m_z = 0.0f;
	m_unk0x64.m_w = 1.0f;
	m_unk0x74 = 0;
}

// FUNCTION: LEGORACERS 0x004a51f0 FOLDED
void RaceState::Racer::Field0xc70::Field0x050::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a51f0 FOLDED
void RaceState::Racer::Field0x3e8::Field0x74c::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5200
void RaceState::Racer::Field0x3e8::Field0x74c::FUN_004a5200(Racer::Field0x00c::Entry* p_entry)
{
	m_unk0x34 = -1;
	m_unk0x28 = p_entry;
	m_unk0x30 = 0.0f;
	m_unk0x38 = 0;
	m_unk0x74 = 0;
}

// FUNCTION: LEGORACERS 0x004a5220
void RaceState::Racer::Field0x3e8::Field0x74c::FUN_004a5220(Racer::Field0x00c::Entry* p_entry)
{
	GolVec3* position = &p_entry->m_unk0x024;
	GolVec3* currentPosition = &m_unk0x3c;
	m_unk0x28 = p_entry;
	*currentPosition = *position;
	m_unk0x00 = *position;

	GolQuat* rotation = &p_entry->m_unk0x030;
	GolQuat* currentRotation = &m_unk0x54;
	*currentRotation = *rotation;
	m_unk0x0c = *rotation;

	LegoS32 duration = p_entry->m_unk0x040;
	m_unk0x74 = duration;
	m_unk0x30 = static_cast<LegoFloat>(duration);

	LegoS32 pointIndex = p_entry->m_unk0x044;
	m_unk0x34 = pointIndex;
	m_unk0x38 = m_unk0x34 + 1;

	Racer::Field0x00c::Entry::PathPoint* point = &p_entry->m_unk0x004[m_unk0x34];
	m_unk0x1c = point->GetType();
	m_unk0x20 = point->GetUnk0x09();
	m_unk0x24 = point->GetUnk0x0a();

	GolVec3 offset;
	point = &m_unk0x28->m_unk0x004[m_unk0x38];
	point->GetPosition(&offset);

	m_unk0x48.m_x = offset.m_x + currentPosition->m_x;
	m_unk0x48.m_y = offset.m_y + currentPosition->m_y;
	m_unk0x48.m_z = offset.m_z + currentPosition->m_z;
}

// STUB: LEGORACERS 0x004a5320
void RaceState::Racer::Field0x3e8::Field0x74c::FUN_004a5320(LegoFloat p_unk0x04)
{
	Racer::Field0x00c::Entry* entry = m_unk0x28;
	if (entry) {
		Racer::Field0x00c::Entry* wrapEntry;
		Racer::Field0x00c::Entry::PathPoint* point;
		GolVec3* currentPosition;
		GolVec3* endPosition;
		GolVec3 offset;
		LegoS32 pointIndex;
		LegoS32 segmentEndTime;
		LegoS32 segmentStartTime;
		LegoS32 targetTime;
		LegoFloat amount;
		LegoFloat currentTimeFloat;
		LegoFloat endValue0x09;
		LegoFloat endValue0x0a;
		LegoFloat scaledX;
		LegoFloat scaledY;
		LegoFloat scaledZ;
		LegoFloat startValue0x09;
		LegoFloat startValue0x0a;

		currentTimeFloat = m_unk0x2c;
		currentTimeFloat *= p_unk0x04;
		currentTimeFloat += m_unk0x30;
		m_unk0x30 = currentTimeFloat;
		LegoS32 currentTime = static_cast<LegoS32>(currentTimeFloat);
		targetTime = currentTime;

		if (m_unk0x34 < 0) {
			startValue0x0a = 0.0f;
			startValue0x09 = 0.0f;

			currentPosition = &m_unk0x3c;
			*currentPosition = entry->m_unk0x008;
			m_unk0x54 = entry->m_unk0x014;
			m_unk0x74 = 0;

			point = &entry->m_unk0x004[m_unk0x38];
			point->GetPosition(&offset);
			m_unk0x48.m_x = offset.m_x + currentPosition->m_x;
			m_unk0x48.m_y = offset.m_y + currentPosition->m_y;
			m_unk0x48.m_z = offset.m_z + currentPosition->m_z;
			point->GetRotation(&m_unk0x64);
			m_unk0x1c = 4;
		}
		else {
			point = &entry->m_unk0x004[m_unk0x34];
			startValue0x0a = point->GetUnk0x0a();
			startValue0x09 = point->GetUnk0x09();
			point = &m_unk0x28->m_unk0x004[m_unk0x38];
		}

		endValue0x0a = point->GetUnk0x0a();
		endValue0x09 = point->GetUnk0x09();
		segmentStartTime = m_unk0x74;
		segmentEndTime = segmentStartTime + point->GetLength();

		if (currentTime < segmentStartTime) {
			pointIndex = m_unk0x34;
			if (pointIndex) {
				currentPosition = &m_unk0x3c;
				while (TRUE) {
					segmentEndTime = segmentStartTime;
					m_unk0x38 = pointIndex;
					m_unk0x48 = m_unk0x3c;
					m_unk0x64 = m_unk0x54;
					endValue0x0a = startValue0x0a;
					endValue0x09 = startValue0x09;

					point = &m_unk0x28->m_unk0x004[pointIndex];
					point->GetPosition(&offset);
					currentPosition->m_x -= offset.m_x;
					currentPosition->m_y -= offset.m_y;
					currentPosition->m_z -= offset.m_z;

					segmentStartTime = m_unk0x74 - point->GetLength();
					m_unk0x34 = pointIndex - 1;
					m_unk0x74 = segmentStartTime;

					point = &m_unk0x28->m_unk0x004[m_unk0x34];
					m_unk0x1c = point->GetType();
					startValue0x0a = point->GetUnk0x0a();
					startValue0x09 = point->GetUnk0x09();
					point->GetRotation(&m_unk0x54);

					if (targetTime >= segmentStartTime) {
						break;
					}

					pointIndex = m_unk0x34;
					if (!pointIndex) {
						goto ClampStart;
					}
				}
			}
			else {
			ClampStart:
				targetTime = 0;
				m_unk0x30 = 0.0f;
			}
		}
		else {
			if (currentTime < segmentEndTime) {
				goto Interpolate;
			}

			endPosition = &m_unk0x48;
			do {
				m_unk0x74 = segmentEndTime;
				pointIndex = m_unk0x38;
				m_unk0x34 = pointIndex;
				m_unk0x3c = *endPosition;
				m_unk0x54 = m_unk0x64;

				startValue0x0a = endValue0x0a;
				startValue0x09 = endValue0x09;
				pointIndex++;
				m_unk0x38 = pointIndex;

				wrapEntry = m_unk0x28;
				if (pointIndex >= wrapEntry->m_unk0x000) {
					m_unk0x3c = wrapEntry->m_unk0x024;
					m_unk0x48 = wrapEntry->m_unk0x024;
					m_unk0x54 = wrapEntry->m_unk0x030;
					m_unk0x64 = wrapEntry->m_unk0x030;
					m_unk0x74 = wrapEntry->m_unk0x040;
					m_unk0x34 = wrapEntry->m_unk0x044;
					targetTime += m_unk0x74 - segmentEndTime;
					m_unk0x38 = m_unk0x34 + 1;
					m_unk0x30 = static_cast<LegoFloat>(targetTime);
				}

				point = &wrapEntry->m_unk0x004[m_unk0x38];
				m_unk0x1c = point->GetType();
				endValue0x0a = point->GetUnk0x0a();
				endValue0x09 = point->GetUnk0x09();

				point->GetPosition(&offset);
				point->GetRotation(&m_unk0x64);
				endPosition->m_x += offset.m_x;
				endPosition->m_y += offset.m_y;
				endPosition->m_z += offset.m_z;
				segmentEndTime += point->GetLength();
			} while (targetTime >= segmentEndTime);
		}

	Interpolate:
		amount = static_cast<LegoFloat>(targetTime - m_unk0x74) / static_cast<LegoFloat>(segmentEndTime - m_unk0x74);
		m_unk0x20 = (endValue0x09 - startValue0x09) * amount + startValue0x09;
		m_unk0x24 = (endValue0x0a - startValue0x0a) * amount + startValue0x0a;

		offset.m_x = m_unk0x48.m_x - m_unk0x3c.m_x;
		offset.m_y = m_unk0x48.m_y - m_unk0x3c.m_y;
		offset.m_z = m_unk0x48.m_z - m_unk0x3c.m_z;
		scaledX = offset.m_x * amount;
		scaledY = offset.m_y * amount;
		scaledZ = offset.m_z * amount;

		m_unk0x00.m_x = scaledX + m_unk0x3c.m_x;
		m_unk0x00.m_y = scaledY + m_unk0x3c.m_y;
		m_unk0x00.m_z = scaledZ + m_unk0x3c.m_z;

		GolMath::FUN_1002f890(m_unk0x54, m_unk0x64, amount, &m_unk0x0c);
	}
}

// STUB: LEGORACERS 0x004a5750
void RaceState::Racer::Field0x3e8::Field0x74c::FUN_004a5750(GolVec3* p_delta)
{
	Racer::Field0x00c::Entry* entry = m_unk0x28;
	LegoS32 startIndex = m_unk0x34;
	LegoS32 endIndex = m_unk0x38;
	Racer::Field0x00c::Entry::PathPoint* startPoint = &entry->m_unk0x004[startIndex];
	Racer::Field0x00c::Entry::PathPoint* endPoint = &entry->m_unk0x004[endIndex];
	LegoS32 segmentStartTime = m_unk0x74;
	LegoS32 segmentEndTime = segmentStartTime + endPoint->GetLength();
	GolVec3 startPosition = m_unk0x3c;
	GolVec3 endPosition = m_unk0x48;

	while (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) < g_unk0x004b4bc8) {
		startPosition = endPosition;
		segmentStartTime = segmentEndTime;
		startIndex = endIndex;
		startPoint = endPoint;
		endIndex++;

		if (endIndex >= entry->m_unk0x000) {
			return;
		}

		endPoint = &entry->m_unk0x004[endIndex];
		segmentEndTime += endPoint->GetLength();

		GolVec3 offset;
		endPoint->GetPosition(&offset);
		endPosition.m_x += offset.m_x;
		endPosition.m_y += offset.m_y;
		endPosition.m_z += offset.m_z;
	}

	GolVec3 segment;
	GolVec3 unitSegment;
	LegoFloat segmentLength;
	LegoFloat segmentAmount;

	for (;;) {
		segment.m_x = endPosition.m_x - startPosition.m_x;
		segment.m_y = endPosition.m_y - startPosition.m_y;
		segment.m_z = endPosition.m_z - startPosition.m_z;
		segmentLength = static_cast<LegoFloat>(
			sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
		);

		LegoFloat inverseLength = 1.0f / segmentLength;
		unitSegment.m_x = segment.m_x * inverseLength;
		unitSegment.m_y = segment.m_y * inverseLength;
		unitSegment.m_z = segment.m_z * inverseLength;

		LegoFloat projectedDelta =
			unitSegment.m_y * p_delta->m_y + p_delta->m_z * unitSegment.m_z + unitSegment.m_x * p_delta->m_x;

		if (projectedDelta >= 0.0f) {
			LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(
				GOL_SQUARED(m_unk0x00.m_z - endPosition.m_z) + GOL_SQUARED(m_unk0x00.m_y - endPosition.m_y) +
				GOL_SQUARED(m_unk0x00.m_x - endPosition.m_x)
			));

			if (projectedDelta <= remainingDistance) {
				segmentAmount = projectedDelta + segmentLength - remainingDistance;
				break;
			}

			for (;;) {
				GolVec3 consumed;
				consumed.m_x = unitSegment.m_x * remainingDistance;
				consumed.m_y = unitSegment.m_y * remainingDistance;
				consumed.m_z = unitSegment.m_z * remainingDistance;
				GolCameraBase::FUN_00404580(p_delta, &consumed, p_delta);

				startPosition = endPosition;
				segmentStartTime = segmentEndTime;
				startIndex = endIndex;
				startPoint = endPoint;
				endIndex++;

				if (endIndex >= entry->m_unk0x000) {
					return;
				}

				endPoint = &entry->m_unk0x004[endIndex];
				segmentEndTime += endPoint->GetLength();

				GolVec3 offset;
				endPoint->GetPosition(&offset);
				endPosition.m_x += offset.m_x;
				endPosition.m_y += offset.m_y;
				endPosition.m_z += offset.m_z;

				if (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) >= g_unk0x004b4bc8) {
					segment.m_x = endPosition.m_x - startPosition.m_x;
					segment.m_y = endPosition.m_y - startPosition.m_y;
					segment.m_z = endPosition.m_z - startPosition.m_z;
					segmentLength = static_cast<LegoFloat>(
						sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
					);

					inverseLength = 1.0f / segmentLength;
					unitSegment.m_x = segment.m_x * inverseLength;
					unitSegment.m_y = segment.m_y * inverseLength;
					unitSegment.m_z = segment.m_z * inverseLength;
					projectedDelta = unitSegment.m_y * p_delta->m_y + p_delta->m_z * unitSegment.m_z +
									 unitSegment.m_x * p_delta->m_x;

					if (projectedDelta < 0.0f) {
						projectedDelta = 0.0f;
					}
					else if (projectedDelta > segmentLength) {
						remainingDistance = segmentLength;
						continue;
					}

					remainingDistance = static_cast<LegoFloat>(sqrt(
						GOL_SQUARED(m_unk0x00.m_z - endPosition.m_z) + GOL_SQUARED(m_unk0x00.m_y - endPosition.m_y) +
						GOL_SQUARED(m_unk0x00.m_x - endPosition.m_x)
					));
					segmentAmount = projectedDelta + segmentLength - remainingDistance;
					break;
				}
			}
			break;
		}

		LegoFloat backwardDelta = -projectedDelta;
		LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(
			GOL_SQUARED(m_unk0x00.m_z - startPosition.m_z) + GOL_SQUARED(m_unk0x00.m_y - startPosition.m_y) +
			GOL_SQUARED(m_unk0x00.m_x - startPosition.m_x)
		));

		if (backwardDelta <= remainingDistance) {
			segmentAmount = remainingDistance - backwardDelta;
			break;
		}

		for (;;) {
			GolVec3 consumed;
			LegoFloat negativeDistance = -remainingDistance;
			consumed.m_x = negativeDistance * unitSegment.m_x;
			consumed.m_y = unitSegment.m_y * negativeDistance;
			consumed.m_z = unitSegment.m_z * negativeDistance;
			GolCameraBase::FUN_00404580(p_delta, &consumed, p_delta);

			endPosition = startPosition;
			endIndex = startIndex;
			endPoint = startPoint;
			segmentEndTime = segmentStartTime;
			startIndex--;

			if (startIndex < 0) {
				return;
			}

			segmentStartTime -= endPoint->GetLength();
			GolVec3 offset;
			endPoint->GetPosition(&offset);
			startPosition.m_x -= offset.m_x;
			startPosition.m_y -= offset.m_y;
			startPosition.m_z -= offset.m_z;
			startPoint = &entry->m_unk0x004[startIndex];

			if (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) >= g_unk0x004b4bc8) {
				segment.m_x = endPosition.m_x - startPosition.m_x;
				segment.m_y = endPosition.m_y - startPosition.m_y;
				segment.m_z = endPosition.m_z - startPosition.m_z;
				segmentLength = static_cast<LegoFloat>(
					sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
				);

				LegoFloat inverseLength = 1.0f / segmentLength;
				unitSegment.m_x = segment.m_x * inverseLength;
				unitSegment.m_y = segment.m_y * inverseLength;
				unitSegment.m_z = segment.m_z * inverseLength;
				projectedDelta =
					unitSegment.m_y * p_delta->m_y + p_delta->m_z * unitSegment.m_z + unitSegment.m_x * p_delta->m_x;

				if (projectedDelta > 0.0f) {
					backwardDelta = 0.0f;
					segmentAmount = segmentLength;
					break;
				}

				backwardDelta = -projectedDelta;
				if (backwardDelta > segmentLength) {
					remainingDistance = segmentLength;
					continue;
				}

				segmentAmount = segmentLength - backwardDelta;
				break;
			}
		}
		break;
	}

	m_unk0x74 = segmentStartTime;
	m_unk0x3c = startPosition;
	m_unk0x48 = endPosition;
	m_unk0x30 = static_cast<LegoFloat>(segmentEndTime - segmentStartTime) * (segmentAmount / segmentLength) +
				static_cast<LegoFloat>(segmentStartTime);
	m_unk0x34 = startIndex;
	m_unk0x38 = endIndex;
	startPoint->GetRotation(&m_unk0x54);
	endPoint->GetRotation(&m_unk0x64);
	FUN_004a5320(0.0f);
}

// FUNCTION: LEGORACERS 0x004a5e10
void RaceState::Racer::Field0x00c::Entry::PathPoint::FUN_004a5e10(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_unk0x00 = static_cast<LegoS16>(p_parser->ReadInteger());
	m_unk0x02 = static_cast<LegoS16>(p_parser->ReadInteger());
	m_unk0x04 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x05 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x06 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x07 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x08 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x09 = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x0a = static_cast<LegoS8>(p_parser->ReadInteger());
	m_unk0x0b = static_cast<LegoU8>(p_parser->ReadInteger());

	if (p_mirror) {
		LegoS8 temp = m_unk0x09;
		m_unk0x09 = m_unk0x0a;
		m_unk0x0a = temp;
		m_unk0x02 = -m_unk0x02;
		m_unk0x06 = -m_unk0x06;
		m_unk0x08 = -m_unk0x08;
	}
}

// FUNCTION: LEGORACERS 0x004a5ec0
LegoU32 RaceState::Racer::Field0x00c::Entry::PathPoint::GetType() const
{
	LegoU32 type = m_unk0x0b >> 6;
	if (type >= 3) {
		type = 4;
	}

	return type;
}

// FUNCTION: LEGORACERS 0x004a5ee0
LegoU32 RaceState::Racer::Field0x00c::Entry::PathPoint::GetLength() const
{
	return (m_unk0x0b & 0x3f) << 5;
}

// FUNCTION: LEGORACERS 0x004a5ef0
GolVec3* RaceState::Racer::Field0x00c::Entry::PathPoint::GetPosition(GolVec3* p_position) const
{
	p_position->m_x = static_cast<LegoFloat>(m_unk0x00) * g_unk0x004b4bcc;
	p_position->m_y = static_cast<LegoFloat>(m_unk0x02) * g_unk0x004b4bcc;
	p_position->m_z = static_cast<LegoFloat>(m_unk0x04) * g_unk0x004b4bd0;

	return p_position;
}

// FUNCTION: LEGORACERS 0x004a5f40
GolQuat* RaceState::Racer::Field0x00c::Entry::PathPoint::GetRotation(GolQuat* p_rotation) const
{
	p_rotation->m_x = static_cast<LegoFloat>(m_unk0x05) * g_unk0x004b4bd4;
	p_rotation->m_y = static_cast<LegoFloat>(m_unk0x06) * g_unk0x004b4bd4;
	p_rotation->m_z = static_cast<LegoFloat>(m_unk0x07) * g_unk0x004b4bd4;
	p_rotation->m_w = static_cast<LegoFloat>(m_unk0x08) * g_unk0x004b4bd4;

	return p_rotation;
}

// FUNCTION: LEGORACERS 0x004a5fa0
LegoFloat RaceState::Racer::Field0x00c::Entry::PathPoint::GetUnk0x09() const
{
	return static_cast<LegoFloat>(m_unk0x09) * g_unk0x004b4bd8;
}

// FUNCTION: LEGORACERS 0x004a5fc0
LegoFloat RaceState::Racer::Field0x00c::Entry::PathPoint::GetUnk0x0a() const
{
	return static_cast<LegoFloat>(m_unk0x0a) * g_unk0x004b4bd8;
}
