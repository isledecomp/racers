#ifndef FROSTPETAL0X34_H
#define FROSTPETAL0X34_H

#include "decomp.h"
#include "gollist.h"
#include "types.h"

class SoundManager;
class SoundInstance;
class StreamingSoundInstance;

// VTABLE: LEGORACERS 0x004afc08
// SIZE 0x34
class FrostPetal0x34 : public GolListLink {
public:
	FrostPetal0x34();
	~FrostPetal0x34();
	virtual void VTable0x00(LegoChar*);                                                       // vtable+0x00
	virtual void VTable0x04();                                                                // vtable+0x04
	virtual LegoBool32 VTable0x08();                                                          // vtable+0x08
	virtual undefined4 VTable0x0c();                                                          // vtable+0x0c
	virtual void VTable0x10(undefined4, LegoFloat, LegoFloat, LegoFloat, LegoS32, LegoFloat); // vtable+0x10
	virtual void VTable0x14(LegoFloat);                                                       // vtable+0x14
	virtual SoundInstance* VTable0x18(undefined4);                                            // vtable+0x18
	virtual void DestroySoundInstance(SoundInstance*);                                        // vtable+0x1c
	virtual StreamingSoundInstance* VTable0x20(undefined4);                                   // vtable+0x20
	virtual void DestroyStreamingSoundInstance(StreamingSoundInstance*);                      // vtable+0x24
	virtual SoundManager* VTable0x28();                                                       // vtable+0x28

	void SetUnk0x0c(SoundManager* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }

private:
	SoundManager* m_unk0x0c;                   // 0x0c
	undefined4 m_unk0x10;                      // 0x10
	undefined4 m_unk0x14;                      // 0x14
	undefined4 m_unk0x18;                      // 0x18
	GolList<SoundInstance> m_unk0x1c;          // 0x1c
	GolList<StreamingSoundInstance> m_unk0x28; // 0x28
};

#endif // FROSTPETAL0X34_H
