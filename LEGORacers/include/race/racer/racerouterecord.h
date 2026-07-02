#ifndef RACEROUTERECORD_H
#define RACEROUTERECORD_H

#include "decomp.h"
#include "goltxtparser.h"
#include "race/racestate.h"
#include "types.h"

class GolFileParser;
class RaceSession;

// SIZE 0x48
class RaceRouteRecord : public RaceState::Racer::Records::Entry {
public:
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

private:
	friend class RaceSession;

	void Load(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror);
	void Reset();
	void ParsePathPoints(GolFileParser* p_parser, LegoBool32 p_mirror);
};

#endif // RACEROUTERECORD_H
