#ifndef CMBMODELPARTDATA_H
#define CMBMODELPARTDATA_H

#include "decomp.h"
#include "golmath.h"
#include "types.h"

class GolFileParser;

// SIZE 0x28
class CmbModelPartData {
	friend class CmbModelPart;

public:
	CmbModelPartData();
	void Parse(GolFileParser& p_parser);

	LegoFloat GetMsPerFrame() const { return m_msPerFrame; }
	const GolVec3& GetVelocity() const { return m_velocity; }
	const GolVec4& GetBounds() const { return m_bounds; }
	LegoU32 GetTrackIndex() const { return m_unk0x20; }
	LegoU16 GetFrameCount() const { return m_unk0x24; }
	LegoU16 GetLoopFrameCount() const { return m_unk0x26; }
	LegoFloat WrapTime(LegoFloat p_time) const;

private:
	LegoFloat m_msPerFrame; // 0x00
	GolVec3 m_velocity;     // 0x04
	GolVec4 m_bounds;       // 0x10
	LegoU32 m_unk0x20;      // 0x20
	LegoU16 m_unk0x24;      // 0x24
	LegoU16 m_unk0x26;      // 0x26
};

#endif // CMBMODELPARTDATA_H
