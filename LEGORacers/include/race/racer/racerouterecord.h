#ifndef RACEROUTERECORD_H
#define RACEROUTERECORD_H

#include "decomp.h"
#include "goltxtparser.h"
#include "race/racestate.h"
#include "types.h"

class GolFileParser;
class RaceSession;

// A recorded driving line (.rrb): quantized path samples with start/loop
// state, played back by CarBody::RouteCursor for AI and ghost cars.
// SIZE 0x48
class RaceRouteRecord {
public:
	// Packed 12-byte quantized route sample.
	// SIZE 0x0c
	class PathPoint {
	public:
		LegoU32 GetType() const;
		LegoU32 GetLength() const;
		GolVec3* GetPosition(GolVec3* p_position) const;
		GolQuat* GetRotation(GolQuat* p_rotation) const;
		LegoFloat GetWidthLeft() const;
		LegoFloat GetWidthRight() const;
		void Load(GolFileParser* p_parser, LegoBool32 p_mirror);

		LegoS16 m_positionX;          // 0x00
		LegoS16 m_positionY;          // 0x02
		LegoS8 m_positionZ;           // 0x04
		LegoS8 m_rotationX;           // 0x05
		LegoS8 m_rotationY;           // 0x06
		LegoS8 m_rotationZ;           // 0x07
		LegoS8 m_rotationW;           // 0x08
		LegoS8 m_widthLeft;           // 0x09
		LegoS8 m_widthRight;          // 0x0a
		LegoU8 m_packedTypeAndLength; // 0x0b
	};

	// VTABLE: LEGORACERS 0x004b4b50
	// SIZE 0x1fc
	class RrbTxtParser : public GolTxtParser {
	public:
		// .rrb token meanings
		enum {
			e_pathPoints = 0x27,
			e_startRotation = 0x28,
			e_startPosition = 0x29,
			e_loopPosition = 0x2a,
			e_loopRotation = 0x2b,
			e_loopTime = 0x2c,
			e_loopPointIndex = 0x2d,
		};
	};

	RaceRouteRecord();
	~RaceRouteRecord();
	void Destroy();

	LegoS32 m_pathPointCount; // 0x00
	PathPoint* m_pathPoints;  // 0x04
	GolVec3 m_startPosition;  // 0x08
	GolQuat m_startRotation;  // 0x14
	GolVec3 m_loopPosition;   // 0x24
	GolQuat m_loopRotation;   // 0x30
	LegoS32 m_loopTime;       // 0x40
	LegoS32 m_loopPointIndex; // 0x44

private:
	friend class RaceSession;

	void Load(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror);
	void Reset();
	void ParsePathPoints(GolFileParser* p_parser, LegoBool32 p_mirror);
};

#endif // RACEROUTERECORD_H
