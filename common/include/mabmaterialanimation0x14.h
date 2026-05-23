#ifndef MABMATERIALANIMATION0X14_H
#define MABMATERIALANIMATION0X14_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

// VTABLE: GOLDP 0x10057040
// VTABLE: LEGORACERS 0x004af684
// SIZE 0x1fc
class MabTxtParser : public GolTxtParser {};

class MabMaterialAnimationItem0x8;
class MabMaterialAnimationItem0x18;
class WhiteFalcon0x140;

// VTABLE: GOLDP 0x10057034
// VTABLE: LEGORACERS 0x004af678
// SIZE 0x14
class MabMaterialAnimation0x14 {
public:
	MabMaterialAnimation0x14();
	virtual ~MabMaterialAnimation0x14(); // vtable+0x00
	virtual void VTable0x04(
		WhiteFalcon0x140* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);                         // vtable+0x04
	virtual void VTable0x08(); // vtable+0x08

	// SYNTHETIC: GOLDP 0x10017a00
	// SYNTHETIC: LEGORACERS 0x004a11e0
	// MabMaterialAnimation0x14::`vector deleting destructor'

	MabMaterialAnimationItem0x18* GetUnk0x0c() const { return m_unk0x0c; }
	void FUN_00410300(LegoS32 p_elapsedMs);

private:
	void FUN_10025a40(WhiteFalcon0x140* p_renderer, GolFileParser& p_parser);
	void FUN_10025b60(GolFileParser& p_parser);

	MabMaterialAnimationItem0x8* m_unk0x04;
	LegoU32 m_unk0x08;
	MabMaterialAnimationItem0x18* m_unk0x0c;
	LegoU32 m_unk0x10;
};

#endif // MABMATERIALANIMATION0X14_H
