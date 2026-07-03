#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "decomp.h"
#include "save/saverecordlist.h"
#include "types.h"

class GolFile;
class GolStream;
struct PersistentGameState;

// SIZE 0x4a8
class SaveGame : public SaveRecordList {
public:
	SaveGame();
	~SaveGame();

	LegoU8* GetFileImage() { return m_fileImage; }
	void Initialize(undefined4 p_count, undefined4 p_recordSource, undefined4 p_saveIndex);
	LegoS32 LoadFromFile(GolFile& p_file);
	void ReadPersistentGameState(PersistentGameState* p_state);
	void WritePersistentGameState(PersistentGameState* p_state);

	enum {
		c_saveFileMagic0 = 'L',
		c_saveFileMagic1 = 'R',
		c_saveFileHeaderSize = 0x477,
		c_saveFileBlockDataSize = 0x7f,
		c_saveFileBlockSize = 0x80,
		c_saveFileInvalidStatus = 17,
		c_unlockStateOffset = 0x05,
		c_scoreRecordsOffset = 0x09,
		c_scoreRecordCount = 13,
		c_scoreRecordSize = 0x40,
		c_scoreRecordCursorOffset = 0x02,
		c_scoreRecordLapTimeOffset = 0x00,
		c_scoreRecordLapHolderNameOffset = 0x04,
		c_scoreRecordRaceTimeOffset = 0x20,
		c_scoreRecordRaceHolderNameOffset = 0x24,
		c_scoreHolderNameSize = 28,
		c_persistentHeaderOffset = 0x349,
		c_inputBindingHeaderOffset = 0x361,
		c_inputBindingEntryOffset = 0x369,
		c_inputBindingEntrySize = 0x27,
		c_inputBindingHeaderSize = 8,
	};

protected:
	LegoS32 WriteFileImage(GolFile& p_file);

private:
	LegoS32 WriteBlocks(GolStream* p_file, const LegoU8* p_source, LegoU32 p_size);
	LegoS32 ReadBlocks(GolStream& p_file, LegoU8* p_dest, LegoU32 p_size);
	LegoU32 CalculateBlockChecksum(const LegoU8* p_source, LegoU32 p_size);

	LegoU8 m_fileImage[0x4a4 - 0x24]; // 0x24
	LegoU32 m_fileOffset;             // 0x4a4
};

#endif // SAVEGAME_H
