#ifndef TANZANITEWISP0X88_H
#define TANZANITEWISP0X88_H

#include "decomp.h"

class MusicInstance;
class MenuManager;
class MusicGroup;

// SIZE 0x88
class TanzaniteWisp0x88 {
public:
	TanzaniteWisp0x88();
	~TanzaniteWisp0x88();

	void Reset()
	{
		m_unk0x78 = 0;
		m_musicInstance = 0;
	}

	MusicGroup* GetMusicGroup() { return m_musicGroup; }
	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicInstance* GetMusicInstance() { return m_musicInstance; }
	void SetMusicInstance(MusicInstance* p_musicInstance) { m_musicInstance = p_musicInstance; }

private:
	friend class MenuManager;

	undefined m_unk0x00[0x78 - 0x00]; // 0x00
	undefined4 m_unk0x78;             // 0x78
	MusicGroup* m_musicGroup;         // 0x7c
	MusicInstance* m_musicInstance;   // 0x80
	undefined m_unk0x84[0x88 - 0x84]; // 0x84
};

#endif // TANZANITEWISP0X88_H
