#ifndef RACEROUTERECORD_H
#define RACEROUTERECORD_H

#include "decomp.h"
#include "goltxtparser.h"
#include "race/racestate.h"
#include "types.h"

class GolFileParser;
class RaceSession;

// SIZE 0x48
class RaceRouteRecord : public RaceState::Racer::Field0x00c::Entry {
public:
	// VTABLE: LEGORACERS 0x004b4b50
	// SIZE 0x1fc
	class RrbTxtParser : public GolTxtParser {};

	RaceRouteRecord();
	~RaceRouteRecord();
	void FUN_004a50a0();

private:
	friend class RaceSession;

	void FUN_004a4e30(const LegoChar* p_fileName, LegoBool32 p_binary, LegoBool32 p_mirror);
	void FUN_004a50c0();
	void FUN_004a5100(GolFileParser* p_parser, LegoBool32 p_mirror);
};

#endif // RACEROUTERECORD_H
