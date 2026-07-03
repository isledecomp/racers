#ifndef SAVESLOT_H
#define SAVESLOT_H

#include "save/saveslotbase.h"

class SaveDirectory;

// VTABLE: LEGORACERS 0x004b1308
// SIZE 0x10
class SaveSlot : public SaveSlotBase {
public:
	SaveSlot();
	~SaveSlot() override;                              // vtable+0x00
	LegoS32 EnsureDirectoryExists() override;          // vtable+0x04
	LegoS32 CreateDirectories() override;              // vtable+0x08
	LegoS32 CheckFileExists(const LegoChar*) override; // vtable+0x0c
	LegoS32 RemoveFile(const LegoChar*) override;      // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x004510c0
	// SaveSlot::`scalar deleting destructor'

	void Initialize(SaveDirectory* p_directory, LegoU32 p_index);
	void Reset();

private:
	friend class MemoryCardFileBase;

	LegoS32 BuildFilePath(const LegoChar* p_fileName, LegoChar* p_buffer);
	LegoS32 BuildDirectoryPath(LegoChar* p_buffer);

	SaveDirectory* m_directory; // 0x08
	LegoU32 m_index;            // 0x0c
};

#endif // SAVESLOT_H
