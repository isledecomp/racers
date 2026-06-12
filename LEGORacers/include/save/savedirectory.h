#ifndef SAVEDIRECTORY_H
#define SAVEDIRECTORY_H

#include "compat.h"
#include "decomp.h"
#include "types.h"

class SaveDirectory;

// VTABLE: LEGORACERS 0x004b0f88
// SIZE 0x08
class SaveSlotBase {
public:
	SaveSlotBase();
	virtual ~SaveSlotBase();                              // vtable+0x00
	virtual LegoS32 EnsureDirectoryExists() = 0;          // vtable+0x04
	virtual LegoS32 CreateDirectories() = 0;              // vtable+0x08
	virtual LegoS32 CheckFileExists(const LegoChar*) = 0; // vtable+0x0c
	virtual LegoS32 VTable0x10(undefined4);               // vtable+0x10
	virtual LegoS32 RemoveFile(const LegoChar*) = 0;      // vtable+0x14
	virtual LegoS32 VTable0x18(undefined4, undefined4);   // vtable+0x18
	virtual LegoS32 VTable0x1c(undefined4);               // vtable+0x1c
	virtual LegoS32 VTable0x20(undefined4, undefined4);   // vtable+0x20

	// SYNTHETIC: LEGORACERS 0x0044e050
	// SaveSlotBase::`scalar deleting destructor'

	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }

protected:
	undefined4 m_unk0x04; // 0x04
};

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
	LegoS32 BuildFilePath(const LegoChar* p_fileName, LegoChar* p_buffer);
	LegoS32 BuildDirectoryPath(LegoChar* p_buffer);

	SaveDirectory* m_directory; // 0x08
	LegoU32 m_index;            // 0x0c
};

// VTABLE: LEGORACERS 0x004b12e4
// SIZE 0x10
class SaveDirectorySlot : public SaveSlot {
public:
	SaveDirectorySlot();

	// SYNTHETIC: LEGORACERS 0x00450f30
	// SaveDirectorySlot::~SaveDirectorySlot

	// SYNTHETIC: LEGORACERS 0x00450f40
	// SaveDirectorySlot::`scalar deleting destructor'
};

// VTABLE: LEGORACERS 0x004b12d8
// SIZE 0x08
class SaveDirectoryBase {
public:
	virtual void Clear() = 0;                // vtable+0x00
	virtual LegoU32 GetEntryCount() = 0;     // vtable+0x04
	virtual SaveSlot* GetEntry(LegoU32) = 0; // vtable+0x08

	const LegoChar* GetDirectoryPath() const { return m_directoryPath; }

protected:
	LegoChar* m_directoryPath; // 0x04
};

// VTABLE: LEGORACERS 0x004b12c8
// SIZE 0x108
class SaveDirectory : public SaveDirectoryBase {
public:
	SaveDirectory();
	void Clear() override;                // vtable+0x00
	LegoU32 GetEntryCount() override;     // vtable+0x04
	SaveSlot* GetEntry(LegoU32) override; // vtable+0x08
	virtual ~SaveDirectory();             // vtable+0x0c
	void Initialize(const LegoChar* p_path);

	// SYNTHETIC: LEGORACERS 0x00450ef0
	// SaveDirectory::`scalar deleting destructor'

private:
	SaveDirectorySlot m_entries[16]; // 0x08
};

#endif // SAVEDIRECTORY_H
