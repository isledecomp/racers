#ifndef OPALSTAR0X20_H
#define OPALSTAR0X20_H

#include "audio/rubyhaze0x08.h"
#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundManager;
class AmberLeaf0x10;

// SIZE 0x20
class OpalStar0x20 : public RubyHaze0x08, public GolListLink {
public:
	OpalStar0x20() {}

	void SetUnk0x10(SoundManager* p_unk0x10) { m_unk0x10 = p_unk0x10; }

protected:
	SoundManager* m_unk0x10;          // 0x10
	GolList<AmberLeaf0x10> m_unk0x14; // 0x14
};

#endif // OPALSTAR0X20_H
