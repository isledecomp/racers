#include "golcamerabase.h"
#include "golfileparser.h"
#include "race/racer/racerouterecord.h"
#include "race/racestate.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceRouteRecord::PathPoint, 0x0c)
DECOMP_SIZE_ASSERT(RacerCarBody::WheelProbe, 0x70)
DECOMP_SIZE_ASSERT(RacerPhysics::CollisionCacheRecord, 0x3c)
DECOMP_SIZE_ASSERT(RacerPhysics::RouteCursor, 0x78)
DECOMP_SIZE_ASSERT(RacerPhysics::RouteCursorInstance, 0x78)

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
RacerCarBody::RouteCursorInstance::RouteCursorInstance()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5180 FOLDED
RacerCarBody::RouteCursorInstance::~RouteCursorInstance()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004a5190 FOLDED
void RacerPhysics::RouteCursor::Reset()
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
void RacerPhysics::RouteCursor::Destroy()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004a5200
void RacerPhysics::RouteCursor::Attach(RaceRouteRecord* p_entry)
{
	m_startIndex = -1;
	m_record = p_entry;
	m_currentTime = 0.0f;
	m_endIndex = 0;
	m_segmentStartTime = 0;
}

// FUNCTION: LEGORACERS 0x004a5220
void RacerPhysics::RouteCursor::AttachAtLoop(RaceRouteRecord* p_entry)
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

	RaceRouteRecord::PathPoint* point = &p_entry->m_pathPoints[m_startIndex];
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

// FUNCTION: LEGORACERS 0x004a5320
void RacerPhysics::RouteCursor::Advance(LegoFloat p_elapsedMs)
{
	RaceRouteRecord* entry = m_record;
	if (entry) {
		RaceRouteRecord::PathPoint* point;
		GolVec3 offset;
		LegoFloat endWidthLeft;
		LegoFloat endWidthRight;
		LegoFloat startWidthLeft;
		LegoFloat startWidthRight;

		LegoFloat currentTime = m_playbackSpeed;
		currentTime *= p_elapsedMs;
		currentTime += m_currentTime;
		m_currentTime = currentTime;
		LegoS32 targetTime = static_cast<LegoS32>(currentTime);

		if (m_startIndex < 0) {
			startWidthRight = 0.0f;
			startWidthLeft = 0.0f;

			GolVec3* currentPosition = &m_startPosition;
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
			startWidthRight = point->GetWidthRight();
			startWidthLeft = point->GetWidthLeft();
			point = &m_record->m_pathPoints[m_endIndex];
		}

		endWidthRight = point->GetWidthRight();
		endWidthLeft = point->GetWidthLeft();
		LegoS32 segmentEndTime = m_segmentStartTime + point->GetLength();

		if (targetTime < m_segmentStartTime) {
			do {
				if (!m_startIndex) {
					targetTime = 0;
					m_currentTime = 0.0f;
					break;
				}

				GolVec3* currentPosition = &m_startPosition;
				segmentEndTime = m_segmentStartTime;
				m_endIndex = m_startIndex;
				m_endPosition = *currentPosition;
				m_endRotation = m_startRotation;
				endWidthRight = startWidthRight;
				endWidthLeft = startWidthLeft;

				RaceRouteRecord::PathPoint* endPoint = &m_record->m_pathPoints[m_endIndex];
				endPoint->GetPosition(&offset);
				currentPosition->m_x -= offset.m_x;
				currentPosition->m_y -= offset.m_y;
				currentPosition->m_z -= offset.m_z;
				m_segmentStartTime -= endPoint->GetLength();
				m_startIndex--;

				RaceRouteRecord::PathPoint* startPoint = &m_record->m_pathPoints[m_startIndex];
				m_pointType = startPoint->GetType();
				startWidthRight = startPoint->GetWidthRight();
				startWidthLeft = startPoint->GetWidthLeft();
				startPoint->GetRotation(&m_startRotation);
			} while (targetTime < m_segmentStartTime);
		}
		else if (targetTime >= segmentEndTime) {
			GolVec3* endPosition = &m_endPosition;
			do {
				m_startIndex = m_endIndex;
				m_startPosition = *endPosition;
				m_segmentStartTime = segmentEndTime;
				m_startRotation = m_endRotation;
				startWidthRight = endWidthRight;
				startWidthLeft = endWidthLeft;
				m_endIndex = m_startIndex + 1;

				RaceRouteRecord* record = m_record;
				if (m_endIndex >= record->m_pathPointCount) {
					m_startPosition = record->m_loopPosition;
					m_endPosition = record->m_loopPosition;
					m_startRotation = record->m_loopRotation;
					m_segmentStartTime = record->m_loopTime;
					m_startIndex = record->m_loopPointIndex;
					targetTime += m_segmentStartTime - segmentEndTime;
					m_currentTime = static_cast<LegoFloat>(targetTime);
					m_endIndex = m_startIndex + 1;
				}

				RaceRouteRecord::PathPoint* endPoint = &record->m_pathPoints[m_endIndex];
				m_pointType = endPoint->GetType();
				endWidthRight = endPoint->GetWidthRight();
				endWidthLeft = endPoint->GetWidthLeft();
				endPoint->GetPosition(&offset);
				endPoint->GetRotation(&m_endRotation);
				endPosition->m_x = offset.m_x + endPosition->m_x;
				endPosition->m_y = offset.m_y + endPosition->m_y;
				endPosition->m_z = offset.m_z + endPosition->m_z;
				segmentEndTime += endPoint->GetLength();
			} while (targetTime >= segmentEndTime);
		}

		LegoFloat elapsed = static_cast<LegoFloat>(targetTime - m_segmentStartTime);
		LegoFloat duration = static_cast<LegoFloat>(segmentEndTime - m_segmentStartTime);
		LegoFloat amount = elapsed / duration;
		m_widthLeft = (endWidthLeft - startWidthLeft) * amount + startWidthLeft;
		m_widthRight = (endWidthRight - startWidthRight) * amount + startWidthRight;

		offset.m_x = m_endPosition.m_x - m_startPosition.m_x;
		offset.m_y = m_endPosition.m_y - m_startPosition.m_y;
		offset.m_z = m_endPosition.m_z - m_startPosition.m_z;

		GolVec3 scaled;
		scaled.m_x = offset.m_x;
		scaled.m_x *= amount;
		scaled.m_y = offset.m_y;
		scaled.m_y *= amount;
		scaled.m_z = offset.m_z;
		scaled.m_z *= amount;

		m_position.m_x = scaled.m_x + m_startPosition.m_x;
		m_position.m_y = scaled.m_y + m_startPosition.m_y;
		m_position.m_z = scaled.m_z + m_startPosition.m_z;

		GolMath::LerpQuat(m_startRotation, m_endRotation, amount, &m_rotation);
	}
}

// FUNCTION: LEGORACERS 0x004a5750
void RacerPhysics::RouteCursor::SeekByDelta(GolVec3* p_delta)
{
	LegoFloat inverseLength;
	LegoFloat segmentLength;
	GolVec3 segment;
	GolVec3 endPosition;
	GolVec3 startPosition;
	GolVec3 offset;
	GolVec3 consumed;

	LegoS32 endIndex = m_endIndex;
	RaceRouteRecord::PathPoint* endPoint = &m_record->m_pathPoints[endIndex];
	LegoS32 segmentStartTime = m_segmentStartTime;
	LegoS32 startIndex = m_startIndex;
	LegoS32 segmentEndTime = segmentStartTime + endPoint->GetLength();
	startPosition = m_startPosition;
	endPosition = m_endPosition;

	while (endPosition.DistanceSquaredTo(startPosition) < g_pathMinSegmentLengthSquared) {
		startPosition = endPosition;
		segmentStartTime = segmentEndTime;
		startIndex = endIndex;
		endIndex++;

		if (endIndex >= m_record->m_pathPointCount) {
			return;
		}

		endPoint = &m_record->m_pathPoints[endIndex];

		endPoint->GetPosition(&offset);
		segmentEndTime += endPoint->GetLength();
		endPosition.m_x += offset.m_x;
		endPosition.m_y += offset.m_y;
		endPosition.m_z += offset.m_z;
	}

	RaceRouteRecord::PathPoint* startPoint = &m_record->m_pathPoints[startIndex];

	LegoFloat segmentAmount;

	for (;;) {
		segment.m_x = endPosition.m_x - startPosition.m_x;
		segment.m_y = endPosition.m_y - startPosition.m_y;
		segment.m_z = endPosition.m_z - startPosition.m_z;
		segmentLength = static_cast<LegoFloat>(
			sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
		);

		inverseLength = 1.0f / segmentLength;
		segment.m_x = segment.m_x * inverseLength;
		segment.m_y = segment.m_y * inverseLength;
		segment.m_z = segment.m_z * inverseLength;

		LegoFloat projectedDelta = segment.m_y * p_delta->m_y + p_delta->m_z * segment.m_z + segment.m_x * p_delta->m_x;

		if (projectedDelta < 0.0f) {
			LegoFloat backwardDelta = -projectedDelta;
			LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(startPosition.DistanceSquaredTo(m_position)));

			if (backwardDelta <= remainingDistance) {
				segmentAmount = remainingDistance - backwardDelta;
				break;
			}

			for (;;) {

				LegoFloat negativeDistance = -remainingDistance;
				consumed.m_x = negativeDistance * segment.m_x;
				consumed.m_y = segment.m_y * negativeDistance;
				consumed.m_z = segment.m_z * negativeDistance;
				GolCameraBase::Subtract(p_delta, &consumed, p_delta);

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

					endPoint->GetPosition(&offset);
					startPosition.m_x -= offset.m_x;
					startPosition.m_y -= offset.m_y;
					startPosition.m_z -= offset.m_z;
					startPoint = &m_record->m_pathPoints[startIndex];
				} while (endPosition.DistanceSquaredTo(startPosition) < g_pathMinSegmentLengthSquared);

				segment.m_x = endPosition.m_x - startPosition.m_x;
				segment.m_y = endPosition.m_y - startPosition.m_y;
				segment.m_z = endPosition.m_z - startPosition.m_z;
				segmentLength = static_cast<LegoFloat>(
					sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
				);

				inverseLength = 1.0f / segmentLength;
				segment.m_x = segment.m_x * inverseLength;
				segment.m_y = segment.m_y * inverseLength;
				segment.m_z = segment.m_z * inverseLength;
				projectedDelta = segment.m_y * p_delta->m_y + p_delta->m_z * segment.m_z + segment.m_x * p_delta->m_x;

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
			LegoFloat remainingDistance = static_cast<LegoFloat>(sqrt(endPosition.DistanceSquaredTo(m_position)));

			if (projectedDelta <= remainingDistance) {
				segmentAmount = projectedDelta + segmentLength - remainingDistance;
				break;
			}

			for (;;) {

				consumed.m_x = segment.m_x * remainingDistance;
				consumed.m_y = segment.m_y * remainingDistance;
				consumed.m_z = segment.m_z * remainingDistance;
				GolCameraBase::Subtract(p_delta, &consumed, p_delta);

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

					endPoint->GetPosition(&offset);
					endPosition.m_x += offset.m_x;
					endPosition.m_y += offset.m_y;
					endPosition.m_z += offset.m_z;
				} while (endPosition.DistanceSquaredTo(startPosition) < g_pathMinSegmentLengthSquared);

				segment.m_x = endPosition.m_x - startPosition.m_x;
				segment.m_y = endPosition.m_y - startPosition.m_y;
				segment.m_z = endPosition.m_z - startPosition.m_z;
				segmentLength = static_cast<LegoFloat>(
					sqrt(segment.m_z * segment.m_z + segment.m_y * segment.m_y + segment.m_x * segment.m_x)
				);

				inverseLength = 1.0f / segmentLength;
				segment.m_x = segment.m_x * inverseLength;
				segment.m_y = segment.m_y * inverseLength;
				segment.m_z = segment.m_z * inverseLength;
				projectedDelta = segment.m_y * p_delta->m_y + p_delta->m_z * segment.m_z + segment.m_x * p_delta->m_x;

				if (projectedDelta < 0.0f) {
					projectedDelta = 0.0f;
				}
				else if (projectedDelta > segmentLength) {
					remainingDistance = segmentLength;
					continue;
				}

				remainingDistance = segmentLength;
				segmentAmount = projectedDelta + segmentLength - remainingDistance;
				break;
			}
			break;
		}
	}

	m_segmentStartTime = segmentStartTime;
	m_startPosition = startPosition;
	m_endPosition = endPosition;
	m_currentTime = static_cast<LegoFloat>(segmentEndTime - segmentStartTime) * (segmentAmount * inverseLength) +
					static_cast<LegoFloat>(segmentStartTime);
	m_startIndex = startIndex;
	m_endIndex = endIndex;
	startPoint->GetRotation(&m_startRotation);
	endPoint->GetRotation(&m_endRotation);
	Advance(0.0f);
}

// FUNCTION: LEGORACERS 0x004a5e10
void RaceRouteRecord::PathPoint::Load(GolFileParser* p_parser, LegoBool32 p_mirror)
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
LegoU32 RaceRouteRecord::PathPoint::GetType() const
{
	LegoU32 type = m_packedTypeAndLength >> 6;
	if (type >= 3) {
		type = 4;
	}

	return type;
}

// FUNCTION: LEGORACERS 0x004a5ee0
LegoU32 RaceRouteRecord::PathPoint::GetLength() const
{
	return (m_packedTypeAndLength & 0x3f) << 5;
}

// FUNCTION: LEGORACERS 0x004a5ef0
GolVec3* RaceRouteRecord::PathPoint::GetPosition(GolVec3* p_position) const
{
	p_position->m_x = static_cast<LegoFloat>(m_positionX) * g_pathPositionXYScale;
	p_position->m_y = static_cast<LegoFloat>(m_positionY) * g_pathPositionXYScale;
	p_position->m_z = static_cast<LegoFloat>(m_positionZ) * g_pathPositionZScale;

	return p_position;
}

// FUNCTION: LEGORACERS 0x004a5f40
GolQuat* RaceRouteRecord::PathPoint::GetRotation(GolQuat* p_rotation) const
{
	p_rotation->m_x = static_cast<LegoFloat>(m_rotationX) * g_pathRotationScale;
	p_rotation->m_y = static_cast<LegoFloat>(m_rotationY) * g_pathRotationScale;
	p_rotation->m_z = static_cast<LegoFloat>(m_rotationZ) * g_pathRotationScale;
	p_rotation->m_w = static_cast<LegoFloat>(m_rotationW) * g_pathRotationScale;

	return p_rotation;
}

// FUNCTION: LEGORACERS 0x004a5fa0
LegoFloat RaceRouteRecord::PathPoint::GetWidthLeft() const
{
	return static_cast<LegoFloat>(m_widthLeft) * g_pathWidthScale;
}

// FUNCTION: LEGORACERS 0x004a5fc0
LegoFloat RaceRouteRecord::PathPoint::GetWidthRight() const
{
	return static_cast<LegoFloat>(m_widthRight) * g_pathWidthScale;
}
