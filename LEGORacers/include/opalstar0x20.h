#ifndef OPALSTAR0X20_H
#define OPALSTAR0X20_H

#include "decomp.h"
#include "gollist.h"
#include "rubyhaze0x08.h"
#include "types.h"

class IndigoStar0x18;

// SIZE 0x20
class OpalStar0x20 : public RubyHaze0x08, public GolListLink {
public:
	OpalStar0x20() {}

	void SetUnk0x10(IndigoStar0x18* p_unk0x10) { m_unk0x10 = p_unk0x10; }

protected:
	IndigoStar0x18* m_unk0x10; // 0x10
	GolListHead m_unk0x14;     // 0x14
};

#endif // OPALSTAR0X20_H
