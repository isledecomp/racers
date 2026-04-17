#ifndef CRIMSONFORGE0X800_H
#define CRIMSONFORGE0X800_H

#include "decomp.h"
#include "golfile.h"
#include "golfilesource.h"
#include "golhashtable.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af9a8
// SIZE 0x800
class CrimsonForge0x800 {
public:
	enum {
		c_flagInitialized = 0x01,
	};

	CrimsonForge0x800();
	virtual void VTable0x00() = 0;                           // vtable+0x00
	virtual ~CrimsonForge0x800();                            // vtable+0x04
	virtual void VTable0x08();                               // vtable+0x08
	virtual void Init(const LegoChar*, const LegoChar*) = 0; // vtable+0x0c
	virtual void Destroy() = 0;                              // vtable+0x10
	virtual void LoadGolLibrary() = 0;                       // vtable+0x14
	virtual void UnloadGolLibrary() = 0;                     // vtable+0x18
	virtual void InitInput() = 0;                            // vtable+0x1c
	virtual void VTable0x20() = 0;                           // vtable+0x20
	virtual void VTable0x24() = 0;                           // vtable+0x24
	virtual void VTable0x28();                               // vtable+0x28
	virtual void VTable0x2c() = 0;                           // vtable+0x2c
	virtual void VTable0x30() = 0;                           // vtable+0x30
	virtual void VTable0x34() = 0;                           // vtable+0x34

	// SYNTHETIC: LEGORACERS 0x004163b0
	// CrimsonForge0x800::`scalar deleting destructor'

	undefined4 GetUnk0x04() { return m_unk0x04; }
	GolHashTable& GetHashTable() { return m_hashTable; }

	void Reset();

protected:
	undefined4 m_unk0x04;            // 0x04
	GolFile m_files[20];             // 0x08
	GolFileSource m_fileSources[20]; // 0x3c8
	LegoU32 m_fileSourceCount;       // 0x7d8
	GolHashTable m_hashTable;        // 0x7dc
};

#endif // CRIMSONFORGE0X800_H
