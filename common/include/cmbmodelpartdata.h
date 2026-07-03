#ifndef CMBMODELPARTDATA_H
#define CMBMODELPARTDATA_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolFileParser;

// SIZE 0x28
class CmbModelPartData {
	friend class CmbModelPart;

	enum {
		e_unknown0x2b = 0x2b,
		e_unknown0x2d = 0x2d,
		e_unknown0x2e = 0x2e,
		e_unknown0x2f = 0x2f,
		e_unknown0x30 = 0x30,
		e_unknown0x31 = 0x31,
	};

public:
	CmbModelPartData();
	void Parse(GolFileParser& p_parser);

	LegoFloat GetMsPerFrame() const { return m_msPerFrame; }
	const GolVec3& GetVelocity() const { return m_velocity; }
	const GolVec4& GetBounds() const { return m_bounds; }
	LegoU32 GetTrackIndex() const { return m_trackIndex; }
	LegoU16 GetFrameCount() const { return m_frameCount; }
	LegoU16 GetLoopFrameCount() const { return m_loopFrameCount; }
	LegoFloat WrapTime(LegoFloat p_time) const;

private:
	LegoFloat m_msPerFrame;   // 0x00
	GolVec3 m_velocity;       // 0x04
	GolVec4 m_bounds;         // 0x10
	LegoU32 m_trackIndex;     // 0x20
	LegoU16 m_frameCount;     // 0x24
	LegoU16 m_loopFrameCount; // 0x26
};

#endif // CMBMODELPARTDATA_H
