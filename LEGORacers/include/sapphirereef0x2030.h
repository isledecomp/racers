#ifndef SAPPHIREREEF0X2030_H
#define SAPPHIREREEF0X2030_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;
class GolExport;
class LegoPieceLibrary;
class VerdantTide0x38;

// SIZE 0x2030
class SapphireReef0x2030 {
public:
	SapphireReef0x2030();
	~SapphireReef0x2030();
	LegoBool32 FUN_0049a0e0();
	void FUN_00499fc0(
		GolExport* p_golExport,
		BronzeFalcon0xc8770* p_renderer,
		LegoPieceLibrary* p_pieceLibrary,
		VerdantTide0x38* p_unk0x10
	);
	void FUN_0049ad00();
	void Destroy();

private:
	undefined4 m_unk0x00;               // 0x0000
	undefined m_unk0x04[0x2030 - 0x04]; // 0x0004
};

#endif // SAPPHIREREEF0X2030_H
