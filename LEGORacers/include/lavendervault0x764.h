#ifndef LAVENDERVAULT0X764_H
#define LAVENDERVAULT0X764_H

#include "decomp.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// SIZE 0x1fc
// VTABLE: LEGORACERS 0x004b48b8
class PcbTxtParser : public GolTxtParser {};

// SIZE 0x764
class LavenderVault0x764 {
public:
	LavenderVault0x764();
	~LavenderVault0x764();

	void Reset();
	LegoBool32 Destroy();

	LegoBool32 Load(const LegoChar* p_path, LegoBool32 p_binary);

private:
	LegoS32 ReadBracketedCount(GolFileParser& p_parser) const;
	void FUN_004988a0(GolFileParser& p_parser);
	void FUN_00498930(GolFileParser& p_parser);
	void ReadHats(GolFileParser& p_parser);
	void ReadFaces(GolFileParser& p_parser);
	void ReadTorsos(GolFileParser& p_parser);
	void ReadLegs(GolFileParser& p_parser);
	void ReadHeadHats(GolFileParser& p_parser);
	void FUN_00498de0(GolFileParser& p_parser);
	void FUN_00498e40(GolFileParser& p_parser);
	void ReadFile(GolFileParser& p_parser);

public:
	void CopyHatName(LegoS32 p_index, LegoChar* p_buffer) const;
	void FUN_00498f70(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const;
	void FUN_00498fd0(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const;
	void FUN_00499020(LegoS32 p_index, LegoChar* p_buffer1, LegoChar* p_buffer2) const;
	void FUN_00499070(LegoS32 p_index, LegoChar* p_buffer) const;
	void CopyHeadHatName(LegoS32 p_index, LegoChar* p_buffer) const;
	void BuildFaceExpressionName(LegoS32 p_faceIndex, LegoS32 p_expressionIndex, LegoChar* p_buffer) const;

private:
	LegoBool32 m_loaded;                 // 0x000
	LegoS32 m_countHats;                 // 0x004
	LegoS32 m_countFaces;                // 0x008
	LegoS32 m_countTorsos;               // 0x00c
	LegoS32 m_countLegs;                 // 0x010
	LegoS32 m_unk0x014;                  // 0x014
	LegoChar m_hatNames[40][8];          // 0x018
	undefined m_unk0x158[40];            // 0x158
	LegoChar m_unk0x180[0x188 - 0x180];  // 0x180
	LegoChar m_faceNames[30][4];         // 0x188
	LegoChar m_faceExpressions[6][6];    // 0x200
	undefined m_unk0x224[30];            // 0x224
	LegoChar m_unk0x242[2][8];           // 0x242
	LegoChar m_torsoNames[30][8];        // 0x252
	undefined m_unk0x342[0x344 - 0x342]; // 0x342
	undefined4 m_unk0x344[30];           // 0x344
	undefined m_unk0x3bc[30];            // 0x3bc
	LegoChar m_unk0x3da[2][8];           // 0x3da
	LegoChar m_legNames[30][8];          // 0x3ea
	undefined m_unk0x4da[0x4dc - 0x4da]; // 0x4da
	undefined4 m_unk0x4dc[30];           // 0x4dc
	undefined m_unk0x554[30];            // 0x554
	LegoChar m_headHatNames[40][8];      // 0x572
	LegoChar m_unk0x6b2[2][8];           // 0x6b2
	undefined m_unk0x6c2[0x6da - 0x6c2]; // 0x6c2
	LegoChar m_unk0x6da[13];             // 0x6da
	LegoChar m_unk0x6e7[13];             // 0x6e7
	LegoChar m_unk0x6f4[13];             // 0x6f4
	LegoChar m_unk0x701[32];             // 0x701
	LegoChar m_unk0x721[32];             // 0x721
	LegoChar m_unk0x741[4][8];           // 0x741
	undefined m_unk0x761[0x763 - 0x761]; // 0x761
};

#endif // LAVENDERVAULT0X764_H
