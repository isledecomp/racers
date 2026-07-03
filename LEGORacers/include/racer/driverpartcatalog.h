#ifndef DRIVERPARTCATALOG_H
#define DRIVERPARTCATALOG_H

#include "decomp.h"
#include "golname.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// SIZE 0x764
class DriverPartCatalog {
public:
	// VTABLE: LEGORACERS 0x004b48b8
	// SIZE 0x1fc
	class PcbTxtParser : public GolTxtParser {
	public:
		// .pcb tokens: one section per Read* handler
		enum {
			e_modelFiles = 0x27,
			e_modelDirectories = 0x28,
			e_hats = 0x29,
			e_faces = 0x2a,
			e_torsos = 0x2b,
			e_legs = 0x2c,
			e_headHats = 0x2d,
			e_bodyModels = 0x2e,
			e_partSlots = 0x2f,
		};
	};

	DriverPartCatalog();
	~DriverPartCatalog();

	void Reset();
	LegoBool32 Destroy();

	LegoBool32 Load(const LegoChar* p_path, LegoBool32 p_binary);

private:
	LegoS32 ReadBracketedCount(GolFileParser& p_parser) const;
	void ReadModelFileNames(GolFileParser& p_parser);
	void ReadModelDirectories(GolFileParser& p_parser);
	void ReadHats(GolFileParser& p_parser);
	void ReadFaces(GolFileParser& p_parser);
	void ReadTorsos(GolFileParser& p_parser);
	void ReadLegs(GolFileParser& p_parser);
	void ReadHeadHats(GolFileParser& p_parser);
	void ReadBodyModelNames(GolFileParser& p_parser);
	void ReadPartSlotNames(GolFileParser& p_parser);
	void ReadFile(GolFileParser& p_parser);

public:
	void CopyHatName(LegoS32 p_index, LegoChar* p_buffer) const;
	void CopyDefaultFaceName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const;
	void CopyTorsoName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const;
	void CopyLegName(LegoS32 p_index, LegoChar* p_directory, LegoChar* p_name) const;
	void CopyBodyModelName(LegoS32 p_index, LegoChar* p_buffer) const;
	void CopyHeadHatName(LegoS32 p_index, LegoChar* p_buffer) const;
	void BuildFaceExpressionName(LegoS32 p_faceIndex, LegoS32 p_expressionIndex, LegoChar* p_buffer) const;
	LegoS32 GetFaceCount() const { return m_faceCount; }
	LegoS32 GetTorsoCount() const { return m_torsoCount; }
	LegoS32 GetLegCount() const { return m_legCount; }
	LegoS32 GetTorsoVariant(LegoS32 p_index) const { return m_torsoVariants[p_index]; }
	LegoS32 GetLegVariant(LegoS32 p_index) const { return m_legVariants[p_index]; }
	LegoS32 GetTorsoLegIndex(LegoS32 p_torsoIndex, LegoS32 p_legIndex) const
	{
		return GetTorsoVariant(p_torsoIndex) + 2 * GetLegVariant(p_legIndex);
	}
	LegoS32 GetHatCount() const { return m_hatCount; }
	LegoU8 GetHatUnlockFlag(LegoS32 p_index) const { return m_hatUnlockFlags[p_index]; }
	LegoU8 GetFaceUnlockFlag(LegoS32 p_index) const { return m_faceUnlockFlags[p_index]; }
	LegoU8 GetTorsoUnlockFlag(LegoS32 p_index) const { return m_torsoUnlockFlags[p_index]; }
	LegoU8 GetLegUnlockFlag(LegoS32 p_index) const { return m_legUnlockFlags[p_index]; }
	const LegoChar* GetHeadModelFileName() const { return m_headModelFileName; }
	const LegoChar* GetHeadModelDirectory() const { return m_modelDirectories[0]; }
	const LegoChar* GetBodyModelFileName(LegoS32 p_index) const { return m_bodyModelFileNames[p_index]; }
	const LegoChar* GetBodyModelDirectory(LegoS32 p_index) const { return m_modelDirectories[p_index]; }

private:
	LegoBool32 m_loaded;                  // 0x000
	LegoS32 m_hatCount;                   // 0x004
	LegoS32 m_faceCount;                  // 0x008
	LegoS32 m_torsoCount;                 // 0x00c
	LegoS32 m_legCount;                   // 0x010
	LegoS32 m_bodyModelNameCount;         // 0x014
	GolName m_hatNames[40];               // 0x018
	undefined m_hatUnlockFlags[40];       // 0x158
	LegoChar m_faceDirectory[8];          // 0x180
	LegoChar m_faceNames[30][4];          // 0x188
	LegoChar m_faceExpressions[6][6];     // 0x200
	undefined m_faceUnlockFlags[30];      // 0x224
	GolName m_torsoVariantDirs[2];        // 0x242
	GolName m_torsoNames[30];             // 0x252
	undefined m_unk0x342[0x344 - 0x342];  // 0x342
	undefined4 m_torsoVariants[30];       // 0x344
	undefined m_torsoUnlockFlags[30];     // 0x3bc
	GolName m_legVariantDirs[2];          // 0x3da
	GolName m_legNames[30];               // 0x3ea
	undefined m_unk0x4da[0x4dc - 0x4da];  // 0x4da
	undefined4 m_legVariants[30];         // 0x4dc
	undefined m_legUnlockFlags[30];       // 0x554
	GolName m_headHatNames[40];           // 0x572
	GolName m_bodyModelNames[5];          // 0x6b2
	LegoChar m_headModelFileName[13];     // 0x6da
	LegoChar m_bodyModelFileNames[2][13]; // 0x6e7
	LegoChar m_modelDirectories[2][32];   // 0x701
	GolName m_partSlotNames[4];           // 0x741
	undefined m_unk0x761[0x763 - 0x761];  // 0x761
};

#endif // DRIVERPARTCATALOG_H
