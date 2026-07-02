#ifndef TGBTARGETPOINTLIST_H
#define TGBTARGETPOINTLIST_H

#include "goltxtparser.h"
#include "race/targetpointlist.h"

class RaceSession;

// SIZE 0x08
class TgbTargetPointList : public TargetPointList {
public:
	// VTABLE: LEGORACERS 0x004b1958
	// SIZE 0x1fc
	class TgbTxtParser : public GolTxtParser {
	public:
		// .tgb token meanings
		enum {
			e_target = 0x27,
			e_position = 0x28,
			e_index = 0x29,
		};
	};

	TgbTargetPointList();
	~TgbTargetPointList();

private:
	friend class RaceSession;

	void Reset();
	void Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
};
#endif // TGBTARGETPOINTLIST_H
