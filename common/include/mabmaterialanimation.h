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
	class MabTxtParser : public GolTxtParser {};

	MabMaterialAnimation();
	virtual ~MabMaterialAnimation(); // vtable+0x00
	virtual void VTable0x04(
		GolRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                         // vtable+0x04
	virtual void VTable0x08(); // vtable+0x08

	// SYNTHETIC: GOLDP 0x10017a00
	// SYNTHETIC: LEGORACERS 0x004a11e0
	// MabMaterialAnimation::`vector deleting destructor'

	MabMaterialTrack* GetUnk0x0c() const { return m_unk0x0c; }
	MabMaterialFrame* GetUnk0x04() const { return m_unk0x04; }
	LegoU32 GetUnk0x08() const { return m_unk0x08; }
	void FUN_00410300(LegoS32 p_elapsedMs);

private:
	void FUN_10025a40(GolRenderDevice* p_renderer, GolFileParser& p_parser);
	void FUN_10025b60(GolFileParser& p_parser);

	MabMaterialFrame* m_unk0x04;
	LegoU32 m_unk0x08;
	MabMaterialTrack* m_unk0x0c;
	LegoU32 m_unk0x10;
};

#endif // MABMATERIALANIMATION_H
