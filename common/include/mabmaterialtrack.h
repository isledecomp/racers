#ifndef MABMATERIALTRACK_H
#define MABMATERIALTRACK_H

#include "decomp.h"
#include "material/materialtable.h"
#include "types.h"

class MabMaterialFrame;
class GolMaterial;

// SIZE 0x18
class MabMaterialTrack {
public:
	enum {
		c_flagConfigured = 0x1 << 0,
		c_flagAssigned = 0x1 << 1,
		c_flagLooping = 0x1 << 2,
	};

	MabMaterialTrack();

	void Configure(undefined2 p_firstFrame, undefined2 p_frameCount, undefined2 p_durationFrames, LegoS32 p_frameRate);
	void Assign(MaterialTable* p_materialTable, LegoU32 p_materialIndex, LegoBool32 p_looping);
	void ConfigureFrom(const MabMaterialTrack& p_other);
	void Reset();
	void Unassign();
	void Rewind();
	void SeekToLastFrame();
	void Update(LegoS32 p_elapsedMs, MabMaterialFrame* p_frames, LegoU32 p_frameCount);
	GolMaterial* SampleMaterial(LegoS32 p_timeMs, MabMaterialFrame* p_frames, LegoU32 p_frameCount);
	MaterialTable* GetMaterialTable() const { return m_materialTable; }
	LegoU16 GetMaterialIndex() const { return m_materialIndex; }
	LegoU16 GetFirstFrame() const { return m_firstFrame; }
	LegoU16 GetFrameCount() const { return m_frameCount; }
	void SetFramesPerMs(LegoFloat p_framesPerMs) { m_framesPerMs = p_framesPerMs; }
	LegoBool32 IsConfigured() const { return m_flags & c_flagConfigured; }
	LegoBool32 IsAssigned() const { return m_flags & c_flagAssigned; }

private:
	MaterialTable* m_materialTable; // 0x00
	LegoU16 m_materialIndex;        // 0x04
	LegoU16 m_firstFrame;           // 0x06
	LegoU16 m_frameCount;           // 0x08
	LegoU16 m_durationFrames;       // 0x0a
	LegoFloat m_framesPerMs;        // 0x0c
	LegoFloat m_frameCursor;        // 0x10
	LegoU32 m_flags;                // 0x14
};

#endif // MABMATERIALTRACK_H
