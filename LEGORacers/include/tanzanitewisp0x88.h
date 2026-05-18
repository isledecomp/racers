#ifndef TANZANITEWISP0X88_H
#define TANZANITEWISP0X88_H

#include "decomp.h"
#include "types.h"

class GolExport;
class AmberHaze0x1c;
class BronzeFalcon0xc8770;
class MagentaRibbon0x20;
class MusicInstance;
class MenuManager;
class MusicGroup;
class GarnetFlare0x60;

// SIZE 0x88
class TanzaniteWisp0x88 {
public:
	// SIZE 0x10
	struct LoadParams {
		GolExport* m_golExport;          // 0x00
		BronzeFalcon0xc8770* m_renderer; // 0x04
		undefined4 m_menuId;             // 0x08
		GarnetFlare0x60* m_unk0x0c;      // 0x0c
	};

	TanzaniteWisp0x88();
	~TanzaniteWisp0x88();

	void ResetMenuState();
	undefined4 FUN_0049d1d0(const LoadParams* p_params);
	LegoBool32 ReleaseMenuResources();
	void RefreshMenuResources();

	void Reset()
	{
		m_unk0x78 = 0;
		m_musicInstance = NULL;
	}

	MusicGroup* GetMusicGroup() { return m_musicGroup; }
	void SetMusicGroup(MusicGroup* p_musicGroup) { m_musicGroup = p_musicGroup; }
	MusicInstance* GetMusicInstance() { return m_musicInstance; }
	void SetMusicInstance(MusicInstance* p_musicInstance) { m_musicInstance = p_musicInstance; }
	LegoBool32 HasMenuResources() const { return m_menuId != 0; }
	undefined4 GetUnk0x78() const { return m_unk0x78; }
	void SetUnk0x78(undefined4 p_unk0x78) { m_unk0x78 = p_unk0x78; }
	LegoS32 GetUnk0x84() const { return m_unk0x84; }

private:
	friend class MenuManager;

	undefined4 m_menuId;                // 0x00
	undefined4 m_unk0x04;               // 0x04
	undefined4 m_unk0x08;               // 0x08
	undefined4 m_unk0x0c;               // 0x0c
	undefined4 m_unk0x10;               // 0x10
	GolExport* m_golExport;             // 0x14
	BronzeFalcon0xc8770* m_renderer;    // 0x18
	MagentaRibbon0x20* m_menuResource0; // 0x1c
	AmberHaze0x1c* m_menuResource1;     // 0x20
	undefined m_unk0x24[0x38 - 0x24];   // 0x24
	undefined4 m_unk0x38;               // 0x38
	undefined m_unk0x3c[0x78 - 0x3c];   // 0x3c
	undefined4 m_unk0x78;               // 0x78
	MusicGroup* m_musicGroup;           // 0x7c
	MusicInstance* m_musicInstance;     // 0x80
	LegoS32 m_unk0x84;                  // 0x84
};

#endif // TANZANITEWISP0X88_H
