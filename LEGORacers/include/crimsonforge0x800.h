#ifndef CRIMSONFORGE0X800_H
#define CRIMSONFORGE0X800_H

#include "decomp.h"
#include "golfile.h"
#include "golfilesource.h"
#include "golhashtable.h"
#include "types.h"

class CactusInterface0x4;
class OpalVault0xf0;

// VTABLE: LEGORACERS 0x004af9a8
// SIZE 0x800
class CrimsonForge0x800 {
public:
	enum {
		c_flagInitialized = 1 << 0,
		c_flagDisplayActive = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
		c_flagBit4 = 1 << 4,
		c_flagBit5 = 1 << 5,
		c_flagBit6 = 1 << 6,
		c_flagBit7 = 1 << 7,
		c_flagBit8 = 1 << 8,
		c_flagBit9 = 1 << 9,
		c_flagBit10 = 1 << 10,
		c_flagBit12 = 1 << 12,
		c_flagBit13 = 1 << 13,
		c_flagBit15 = 1 << 15,
		c_flagBit17 = 1 << 17,
	};

	CrimsonForge0x800();
	virtual LegoU32 VTable0x00(LegoU32) = 0;                 // vtable+0x00
	virtual ~CrimsonForge0x800();                            // vtable+0x04
	virtual void VTable0x08();                               // vtable+0x08
	virtual void Init(const LegoChar*, const LegoChar*) = 0; // vtable+0x0c
	virtual void Destroy() = 0;                              // vtable+0x10
	virtual void LoadGolLibrary() = 0;                       // vtable+0x14
	virtual void UnloadGolLibrary() = 0;                     // vtable+0x18
	virtual void InitInput() = 0;                            // vtable+0x1c
	virtual void VTable0x20() = 0;                           // vtable+0x20
	virtual LegoS32 VTable0x24(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp,
							   LegoU32 p_flags) = 0; // vtable+0x24
	virtual void VTable0x28(
		LegoU32 p_width,
		LegoU32 p_height,
		LegoU32 p_bpp,
		LegoU32 p_flags,
		const LegoChar* p_driverName,
		const LegoChar* p_deviceName
	);                                                        // vtable+0x28
	virtual void VTable0x2c() = 0;                            // vtable+0x2c
	virtual void VTable0x30() = 0;                            // vtable+0x30
	virtual LegoS32 Tick(CactusInterface0x4* p_unk0x81c) = 0; // vtable+0x34
	virtual OpalVault0xf0* VTable0x38() = 0;                  // vtable+0x38

	// SYNTHETIC: LEGORACERS 0x004163b0
	// CrimsonForge0x800::`scalar deleting destructor'

	LegoU32 GetFlags() { return m_flags; }
	GolHashTable& GetHashTable() { return m_hashTable; }

	void Reset();

protected:
	LegoU32 m_flags;                 // 0x04
	GolFile m_files[20];             // 0x08
	GolFileSource m_fileSources[20]; // 0x3c8
	LegoU32 m_fileSourceCount;       // 0x7d8
	GolHashTable m_hashTable;        // 0x7dc
};

#endif // CRIMSONFORGE0X800_H
