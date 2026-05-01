#ifndef TANZANITEWISP0X88_H
#define TANZANITEWISP0X88_H

#include "decomp.h"
#include "types.h"

class GolExport;
class MusicInstance;
class MenuManager;
class MusicGroup;

// SIZE 0x88
class TanzaniteWisp0x88 {
public:
	TanzaniteWisp0x88();
	~TanzaniteWisp0x88();

	void ResetMenuState();
	LegoBool32 ReleaseMenuResources();

	void Reset()
	{
		m_unk0x78 = 0;
		m_musicInstance = NULL;
	}

	MusicGroup* GetMusicGroup() { return m_musicGroup; }
	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicInstance* GetMusicInstance() { return m_musicInstance; }
	void SetMusicInstance(MusicInstance* p_musicInstance) { m_musicInstance = p_musicInstance; }

private:
	friend class MenuManager;

	undefined4 m_menuId;              // 0x00
	undefined4 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	undefined4 m_unk0x0c;             // 0x0c
	undefined4 m_unk0x10;             // 0x10
	GolExport* m_golExport;           // 0x14
	undefined4 m_unk0x18;             // 0x18
	undefined4* m_menuResource0;      // 0x1c
	undefined4* m_menuResource1;      // 0x20
	undefined m_unk0x24[0x38 - 0x24]; // 0x24
	undefined4 m_unk0x38;             // 0x38
	undefined m_unk0x3c[0x78 - 0x3c]; // 0x3c
	undefined4 m_unk0x78;             // 0x78
	MusicGroup* m_musicGroup;         // 0x7c
	MusicInstance* m_musicInstance;   // 0x80
	undefined m_unk0x84[0x88 - 0x84]; // 0x84
};

#endif // TANZANITEWISP0X88_H
