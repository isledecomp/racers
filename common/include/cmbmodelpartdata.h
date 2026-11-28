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
		e_track = 0x2b,
		e_frames = 0x2d,
		e_loopFrames = 0x2e,
		e_frameDuration = 0x2f,
		e_velocity = 0x30,
		e_bounds = 0x31,
	};

public:
	CmbModelPartData();
	void Parse(GolFileParser& p_parser);

	LegoFloat GetMsPerFrame() const { return m_msPerFrame; }
	const GolVec3& GetVelocity() const { return m_velocity; }
	const GolVec3& GetBoundsCenter() const { return m_boundsCenter; }
	LegoFloat GetBoundsRadius() const { return m_boundsRadius; }
	void SetBounds(const GolVec3& p_boundsCenter, LegoFloat p_boundsRadius)
	{
		m_boundsCenter = p_boundsCenter;
		m_boundsRadius = p_boundsRadius;
	}
	LegoU32 GetTrackIndex() const { return m_trackIndex; }
	LegoU16 GetFrameCount() const { return m_frameCount; }
	LegoU32 GetFrameCountWide() const { return m_frameCount; }
	LegoU16 GetLoopFrameCount() const { return m_loopFrameCount; }
	LegoFloat WrapTime(LegoFloat p_time) const;

private:
	LegoFloat m_msPerFrame;   // 0x00
	GolVec3 m_velocity;       // 0x04
	GolVec3 m_boundsCenter;   // 0x10
	LegoFloat m_boundsRadius; // 0x1c
	LegoU32 m_trackIndex;     // 0x20
	LegoU16 m_frameCount;     // 0x24
	LegoU16 m_loopFrameCount; // 0x26
};

#endif // CMBMODELPARTDATA_H
