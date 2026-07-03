#ifndef MABMATERIALANIMATION_H
#define MABMATERIALANIMATION_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class MabMaterialFrame;
class MabMaterialTrack;
class GolRenderDevice;

// VTABLE: GOLDP 0x10057034
// VTABLE: LEGORACERS 0x004af678
// SIZE 0x14
class MabMaterialAnimation {
public:
	// VTABLE: GOLDP 0x10057040
	// VTABLE: LEGORACERS 0x004af684
	// SIZE 0x1fc
	class MabTxtParser : public GolTxtParser {
	public:
		// .maf tokens; section ids double as record/field keywords
		enum {
			e_frames = 0x27,
			e_frameRange = 0x27,
			e_tracks = 0x28,
			e_track = 0x28,
			e_duration = 0x29,
			e_frameRate = 0x2a,
		};
	};

	MabMaterialAnimation();
	virtual ~MabMaterialAnimation(); // vtable+0x00
	virtual void Load(GolRenderDevice* p_renderer, const LegoChar* p_fileName,
					  LegoBool32 p_binary); // vtable+0x04
	virtual void Destroy();                 // vtable+0x08

	// SYNTHETIC: GOLDP 0x10017a00
	// SYNTHETIC: LEGORACERS 0x004a11e0
	// MabMaterialAnimation::`vector deleting destructor'

	MabMaterialTrack* GetTracks() const { return m_tracks; }
	MabMaterialFrame* GetFrames() const { return m_frames; }
	LegoU32 GetFrameCount() const { return m_frameCount; }
	void Update(LegoS32 p_elapsedMs);

private:
	void ParseFrames(GolRenderDevice* p_renderer, GolFileParser& p_parser);
	void ParseTracks(GolFileParser& p_parser);

	MabMaterialFrame* m_frames; // 0x04
	LegoU32 m_frameCount;       // 0x08
	MabMaterialTrack* m_tracks; // 0x0c
	LegoU32 m_trackCount;       // 0x10
};

#endif // MABMATERIALANIMATION_H
