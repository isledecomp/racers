#include "golcamerabase.h"
#include "golfileparser.h"
#include "race/racestate.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceState::Racer::Records::Entry::PathPoint, 0x0c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics::Field0x198, 0x70)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics::CollisionCacheRecord, 0x3c)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics::RouteCursor, 0x78)
DECOMP_SIZE_ASSERT(RaceState::Racer::Physics::RouteCursorInstance, 0x78)

// GLOBAL: LEGORACERS 0x004b4bc8
extern const LegoFloat g_pathMinSegmentLengthSquared = 0.001f;

// GLOBAL: LEGORACERS 0x004b4bcc
extern const LegoFloat g_pathPositionXYScale = 0.00390625f;

// GLOBAL: LEGORACERS 0x004b4bd0
extern const LegoFloat g_pathPositionZScale = 0.0625f;

// GLOBAL: LEGORACERS 0x004b4bd4
extern const LegoFloat g_pathRotationScale = 0.007874016f;

// GLOBAL: LEGORACERS 0x004b4bd8
extern const LegoFloat g_pathWidthScale = 0.125f;

// FUNCTION: LEGORACERS 0x004a5170 FOLDED
RaceState::Racer::PhysicsBase0x74c::RouteCursorInstance::RouteCursorInstance()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5180 FOLDED
RaceState::Racer::PhysicsBase0x74c::RouteCursorInstance::~RouteCursorInstance()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a5190 FOLDED
void RaceState::Racer::Physics::RouteCursor::Reset()
{
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = 0.0f;
	m_rotation.m_x = 0.0f;
	m_rotation.m_y = 0.0f;
	m_rotation.m_z = 0.0f;
	m_rotation.m_w = 1.0f;
	m_pointType = 0;
	m_record = NULL;
	m_playbackSpeed = 1.0f;
	m_currentTime = 0;
	m_startIndex = 0xffffffff;
	m_endIndex = 0;
	m_startPosition.m_x = 0.0f;
	m_startPosition.m_y = 0.0f;
	m_startPosition.m_z = 0.0f;
	m_endPosition.m_x = 0.0f;
	m_endPosition.m_y = 0.0f;
	m_endPosition.m_z = 0.0f;
	m_startRotation.m_x = 0.0f;
	m_startRotation.m_y = 0.0f;
	m_startRotation.m_z = 0.0f;
	m_startRotation.m_w = 1.0f;
	m_endRotation.m_x = 0.0f;
	m_endRotation.m_y = 0.0f;
	m_endRotation.m_z = 0.0f;
	m_endRotation.m_w = 1.0f;
	m_segmentStartTime = 0;
}

// FUNCTION: LEGORACERS 0x004a51f0 FOLDED
void RaceState::Racer::Physics::RouteCursor::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5200
void RaceState::Racer::Physics::RouteCursor::Attach(Racer::Records::Entry* p_entry)
{
	m_startIndex = -1;
	m_record = p_entry;
	m_currentTime = 0.0f;
	m_endIndex = 0;
	m_segmentStartTime = 0;
}

// FUNCTION: LEGORACERS 0x004a5220
void RaceState::Racer::Physics::RouteCursor::AttachAtLoop(Racer::Records::Entry* p_entry)
{
	GolVec3* position = &p_entry->m_loopPosition;
	GolVec3* currentPosition = &m_startPosition;
	m_record = p_entry;
	*currentPosition = *position;
	m_position = *position;

	GolQuat* rotation = &p_entry->m_loopRotation;
	GolQuat* currentRotation = &m_startRotation;
	*currentRotation = *rotation;
	m_rotation = *rotation;

	LegoS32 duration = p_entry->m_loopTime;
	m_segmentStartTime = duration;
	m_currentTime = static_cast<LegoFloat>(duration);

	LegoS32 pointIndex = p_entry->m_loopPointIndex;
	m_startIndex = pointIndex;
	m_endIndex = m_startIndex + 1;

	Racer::Records::Entry::PathPoint* point = &p_entry->m_pathPoints[m_startIndex];
	m_pointType = point->GetType();
	m_widthLeft = point->GetWidthLeft();
	m_widthRight = point->GetWidthRight();

	GolVec3 offset;
	point = &m_record->m_pathPoints[m_endIndex];
	point->GetPosition(&offset);

	m_endPosition.m_x = offset.m_x + currentPosition->m_x;
	m_endPosition.m_y = offset.m_y + currentPosition->m_y;
	m_endPosition.m_z = offset.m_z + currentPosition->m_z;
}

// STUB: LEGORACERS 0x004a5320
void RaceState::Racer::Physics::RouteCursor::Advance(LegoFloat p_elapsedMs)
{
	Racer::Records::Entry* entry = m_record;
	if (entry) {
		Racer::Records::Entry* wrapEntry;
		Racer::Records::Entry::PathPoint* point;
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

		currentTimeFloat = m_playbackSpeed;
		currentTimeFloat *= p_elapsedMs;
		currentTimeFloat += m_currentTime;
		m_currentTime = currentTimeFloat;
		LegoS32 currentTime = static_cast<LegoS32>(currentTimeFloat);
		targetTime = currentTime;

		if (m_startIndex < 0) {
			startValue0x0a = 0.0f;
			startValue0x09 = 0.0f;

			currentPosition = &m_startPosition;
			*currentPosition = entry->m_startPosition;
			m_startRotation = entry->m_startRotation;
			m_segmentStartTime = 0;

			point = &entry->m_pathPoints[m_endIndex];
			point->GetPosition(&offset);
			m_endPosition.m_x = offset.m_x + currentPosition->m_x;
			m_endPosition.m_y = offset.m_y + currentPosition->m_y;
			m_endPosition.m_z = offset.m_z + currentPosition->m_z;
			point->GetRotation(&m_endRotation);
			m_pointType = 4;
		}
		else {
			point = &entry->m_pathPoints[m_startIndex];
			startValue0x0a = point->GetWidthRight();
			startValue0x09 = point->GetWidthLeft();
			point = &m_record->m_pathPoints[m_endIndex];
		}

		endValue0x0a = point->GetWidthRight();
		endValue0x09 = point->GetWidthLeft();
		segmentStartTime = m_segmentStartTime;
		segmentEndTime = segmentStartTime + point->GetLength();

		if (currentTime < segmentStartTime) {
			pointIndex = m_startIndex;
			if (pointIndex) {
				currentPosition = &m_startPosition;
				while (TRUE) {
					segmentEndTime = segmentStartTime;
					m_endIndex = pointIndex;
					m_endPosition = m_startPosition;
					m_endRotation = m_startRotation;
					endValue0x0a = startValue0x0a;
					endValue0x09 = startValue0x09;

					point = &m_record->m_pathPoints[pointIndex];
					point->GetPosition(&offset);
					currentPosition->m_x -= offset.m_x;
					currentPosition->m_y -= offset.m_y;
					currentPosition->m_z -= offset.m_z;

					segmentStartTime = m_segmentStartTime - point->GetLength();
					m_startIndex = pointIndex - 1;
					m_segmentStartTime = segmentStartTime;

					point = &m_record->m_pathPoints[m_startIndex];
					m_pointType = point->GetType();
					startValue0x0a = point->GetWidthRight();
					startValue0x09 = point->GetWidthLeft();
					point->GetRotation(&m_startRotation);

					if (targetTime >= segmentStartTime) {
						break;
					}

					pointIndex = m_startIndex;
					if (!pointIndex) {
						goto ClampStart;
					}
				}
			}
			else {
			ClampStart:
				targetTime = 0;
				m_currentTime = 0.0f;
			}
		}
		else {
			if (currentTime < segmentEndTime) {
				goto Interpolate;
			}

			endPosition = &m_endPosition;
			do {
				m_segmentStartTime = segmentEndTime;
				pointIndex = m_endIndex;
				m_startIndex = pointIndex;
				m_startPosition = *endPosition;
				m_startRotation = m_endRotation;

				startValue0x0a = endValue0x0a;
				startValue0x09 = endValue0x09;
				pointIndex++;
				m_endIndex = pointIndex;

				wrapEntry = m_record;
				if (pointIndex >= wrapEntry->m_pathPointCount) {
					m_startPosition = wrapEntry->m_loopPosition;
					m_endPosition = wrapEntry->m_loopPosition;
					m_startRotation = wrapEntry->m_loopRotation;
					m_endRotation = wrapEntry->m_loopRotation;
					m_segmentStartTime = wrapEntry->m_loopTime;
					m_startIndex = wrapEntry->m_loopPointIndex;
					targetTime += m_segmentStartTime - segmentEndTime;
					m_endIndex = m_startIndex + 1;
					m_currentTime = static_cast<LegoFloat>(targetTime);
				}

				point = &wrapEntry->m_pathPoints[m_endIndex];
				m_pointType = point->GetType();
				endValue0x0a = point->GetWidthRight();
				endValue0x09 = point->GetWidthLeft();

				point->GetPosition(&offset);
				point->GetRotation(&m_endRotation);
				endPosition->m_x += offset.m_x;
				endPosition->m_y += offset.m_y;
				endPosition->m_z += offset.m_z;
				segmentEndTime += point->GetLength();
			} while (targetTime >= segmentEndTime);
		}

	Interpolate:
		amount = static_cast<LegoFloat>(targetTime - m_segmentStartTime) /
				 static_cast<LegoFloat>(segmentEndTime - m_segmentStartTime);
		m_widthLeft = (endValue0x09 - startValue0x09) * amount + startValue0x09;
		m_widthRight = (endValue0x0a - startValue0x0a) * amount + startValue0x0a;

		offset.m_x = m_endPosition.m_x - m_startPosition.m_x;
		offset.m_y = m_endPosition.m_y - m_startPosition.m_y;
		offset.m_z = m_endPosition.m_z - m_startPosition.m_z;
		scaledX = offset.m_x * amount;
		scaledY = offset.m_y * amount;
		scaledZ = offset.m_z * amount;

		m_position.m_x = scaledX + m_startPosition.m_x;
		m_position.m_y = scaledY + m_startPosition.m_y;
		m_position.m_z = scaledZ + m_startPosition.m_z;

		GolMath::FUN_1002f890(m_startRotation, m_endRotation, amount, &m_rotation);
	}
}

// STUB: LEGORACERS 0x004a5750
void RaceState::Racer::Physics::RouteCursor::SeekByDelta(GolVec3* p_delta)
{
	LegoS32 endIndex = m_endIndex;
	Racer::Records::Entry::PathPoint* endPoint = &m_record->m_pathPoints[endIndex];
	LegoS32 segmentStartTime = m_segmentStartTime;
	LegoS32 startIndex = m_startIndex;
	LegoS32 segmentEndTime = segmentStartTime + endPoint->GetLength();
	GolVec3 startPosition = m_startPosition;
	GolVec3 endPosition = m_endPosition;

	while (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) < g_pathMinSegmentLengthSquared) {
		startPosition = endPosition;
		segmentStartTime = segmentEndTime;
		startIndex = endIndex;
		endIndex++;

		if (endIndex >= m_record->m_pathPointCount) {
			return;
		}

		endPoint = &m_record->m_pathPoints[endIndex];

		GolVec3 offset;
		endPoint->GetPosition(&offset);
		segmentEndTime += endPoint->GetLength();
		endPosition.m_x += offset.m_x;
		endPosition.m_y += offset.m_y;
		endPosition.m_z += offset.m_z;
	}

	Racer::Records::Entry::PathPoint* startPoint = &m_record->m_pathPoints[startIndex];
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

		if (projectedDelta < 0.0f) {
			LegoFloat backwardDelta = -projectedDelta;
			LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(
				GOL_SQUARED(m_position.m_z - startPosition.m_z) + GOL_SQUARED(m_position.m_y - startPosition.m_y) +
				GOL_SQUARED(m_position.m_x - startPosition.m_x)
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

				do {
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
					startPoint = &m_record->m_pathPoints[startIndex];
				} while (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) < g_pathMinSegmentLengthSquared);

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
			break;
		}

		{
			LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(
				GOL_SQUARED(m_position.m_z - endPosition.m_z) + GOL_SQUARED(m_position.m_y - endPosition.m_y) +
				GOL_SQUARED(m_position.m_x - endPosition.m_x)
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

				do {
					startPosition = endPosition;
					segmentStartTime = segmentEndTime;
					startIndex = endIndex;
					startPoint = endPoint;
					endIndex++;

					if (endIndex >= m_record->m_pathPointCount) {
						return;
					}

					endPoint = &m_record->m_pathPoints[endIndex];
					segmentEndTime += endPoint->GetLength();

					GolVec3 offset;
					endPoint->GetPosition(&offset);
					endPosition.m_x += offset.m_x;
					endPosition.m_y += offset.m_y;
					endPosition.m_z += offset.m_z;
				} while (GOLVECTOR3_DISTANCE_SQUARED(startPosition, endPosition) < g_pathMinSegmentLengthSquared);

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
				projectedDelta =
					unitSegment.m_y * p_delta->m_y + p_delta->m_z * unitSegment.m_z + unitSegment.m_x * p_delta->m_x;

				if (projectedDelta < 0.0f) {
					projectedDelta = 0.0f;
				}
				else if (projectedDelta > segmentLength) {
					remainingDistance = segmentLength;
					continue;
				}

				remainingDistance = static_cast<LegoFloat>(sqrt(
					GOL_SQUARED(m_position.m_z - endPosition.m_z) + GOL_SQUARED(m_position.m_y - endPosition.m_y) +
					GOL_SQUARED(m_position.m_x - endPosition.m_x)
				));
				segmentAmount = projectedDelta + segmentLength - remainingDistance;
				break;
			}
			break;
		}
	}

	m_segmentStartTime = segmentStartTime;
	m_startPosition = startPosition;
	m_endPosition = endPosition;
	m_currentTime = static_cast<LegoFloat>(segmentEndTime - segmentStartTime) * (segmentAmount / segmentLength) +
					static_cast<LegoFloat>(segmentStartTime);
	m_startIndex = startIndex;
	m_endIndex = endIndex;
	startPoint->GetRotation(&m_startRotation);
	endPoint->GetRotation(&m_endRotation);
	Advance(0.0f);
}

// FUNCTION: LEGORACERS 0x004a5e10
void RaceState::Racer::Records::Entry::PathPoint::Load(GolFileParser* p_parser, LegoBool32 p_mirror)
{
	m_positionX = static_cast<LegoS16>(p_parser->ReadInteger());
	m_positionY = static_cast<LegoS16>(p_parser->ReadInteger());
	m_positionZ = static_cast<LegoS8>(p_parser->ReadInteger());
	m_rotationX = static_cast<LegoS8>(p_parser->ReadInteger());
	m_rotationY = static_cast<LegoS8>(p_parser->ReadInteger());
	m_rotationZ = static_cast<LegoS8>(p_parser->ReadInteger());
	m_rotationW = static_cast<LegoS8>(p_parser->ReadInteger());
	m_widthLeft = static_cast<LegoS8>(p_parser->ReadInteger());
	m_widthRight = static_cast<LegoS8>(p_parser->ReadInteger());
	m_packedTypeAndLength = static_cast<LegoU8>(p_parser->ReadInteger());

	if (p_mirror) {
		LegoS8 temp = m_widthLeft;
		m_widthLeft = m_widthRight;
		m_widthRight = temp;
		m_positionY = -m_positionY;
		m_rotationY = -m_rotationY;
		m_rotationW = -m_rotationW;
	}
}

// FUNCTION: LEGORACERS 0x004a5ec0
LegoU32 RaceState::Racer::Records::Entry::PathPoint::GetType() const
{
	LegoU32 type = m_packedTypeAndLength >> 6;
	if (type >= 3) {
		type = 4;
	}

	return type;
}

// FUNCTION: LEGORACERS 0x004a5ee0
LegoU32 RaceState::Racer::Records::Entry::PathPoint::GetLength() const
{
	return (m_packedTypeAndLength & 0x3f) << 5;
}

// FUNCTION: LEGORACERS 0x004a5ef0
GolVec3* RaceState::Racer::Records::Entry::PathPoint::GetPosition(GolVec3* p_position) const
{
	p_position->m_x = static_cast<LegoFloat>(m_positionX) * g_pathPositionXYScale;
	p_position->m_y = static_cast<LegoFloat>(m_positionY) * g_pathPositionXYScale;
	p_position->m_z = static_cast<LegoFloat>(m_positionZ) * g_pathPositionZScale;

	return p_position;
}

// FUNCTION: LEGORACERS 0x004a5f40
GolQuat* RaceState::Racer::Records::Entry::PathPoint::GetRotation(GolQuat* p_rotation) const
{
	p_rotation->m_x = static_cast<LegoFloat>(m_rotationX) * g_pathRotationScale;
	p_rotation->m_y = static_cast<LegoFloat>(m_rotationY) * g_pathRotationScale;
	p_rotation->m_z = static_cast<LegoFloat>(m_rotationZ) * g_pathRotationScale;
	p_rotation->m_w = static_cast<LegoFloat>(m_rotationW) * g_pathRotationScale;

	return p_rotation;
}

// FUNCTION: LEGORACERS 0x004a5fa0
LegoFloat RaceState::Racer::Records::Entry::PathPoint::GetWidthLeft() const
{
	return static_cast<LegoFloat>(m_widthLeft) * g_pathWidthScale;
}

// FUNCTION: LEGORACERS 0x004a5fc0
LegoFloat RaceState::Racer::Records::Entry::PathPoint::GetWidthRight() const
{
	return static_cast<LegoFloat>(m_widthRight) * g_pathWidthScale;
}
