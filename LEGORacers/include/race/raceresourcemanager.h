#ifndef RACERESOURCEMANAGER_H
#define RACERESOURCEMANAGER_H

#include "decomp.h"
#include "types.h"

class SoundManager;

// SIZE 0x04
class RaceResourceManager {
public:
	// SIZE 0x04
	class Resource {
	public:
		virtual void VTable0x00() = 0;          // vtable+0x00
		virtual void VTable0x04(LegoU32) = 0;   // vtable+0x04
		virtual LegoS32 VTable0x08() = 0;       // vtable+0x08
		virtual LegoS32 VTable0x0c() = 0;       // vtable+0x0c
		virtual Resource* VTable0x10() = 0;     // vtable+0x10
		virtual void VTable0x14() = 0;          // vtable+0x14
		virtual void VTable0x18() = 0;          // vtable+0x18
		virtual void VTable0x1c() = 0;          // vtable+0x1c
		virtual void VTable0x20() = 0;          // vtable+0x20
		virtual void VTable0x24(Resource*) = 0; // vtable+0x24
	};

	void FUN_00443c10(Resource* p_resource);

protected:
	SoundManager* m_soundManager; // 0x00
};

#endif // RACERESOURCEMANAGER_H
