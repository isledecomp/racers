#ifndef CUTSCENEEVENT0xE4_H
#define CUTSCENEEVENT0xE4_H

#include "decomp.h"
#include "types.h"

class GolFileParser;
class MabMaterialAnimation0x14;

class CutSceneEvent0xe4 {
	// FIXME: size is unknown

private:
	void FUN_004a0ff0(GolFileParser& p_parser);

	void* m_vftable;                  // 0x00
	undefined m_unk0x04[0x68 - 0x04]; // 0x04
	LegoU32 m_unk0x68;                // 0x68
	undefined m_unk0x6c[0x70 - 0x6c];
	MabMaterialAnimation0x14* m_unk0x70; // 0x70
	undefined m_unk0x74[0xe4 - 0x74];    // 0x04
};

#endif // CUTSCENEEVENT0xE4_H
