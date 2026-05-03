#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "aquamarinespirit0x3c.h"
#include "audio/soundgroupbinding.h"
#include "bronzefalcon0xc8770.h"
#include "cactusinterface0x4.h"
#include "championdefinitionlist.h"
#include "chromespike0x4.h"
#include "citrinegrove0x1f4c.h"
#include "compat.h"
#include "coppercrest0x40.h"
#include "crimsonsun0xa4.h"
#include "decomp.h"
#include "garnetflare0x60.h"
#include "golfonttable.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "lavendervault0x764.h"
#include "legopiecelibrary.h"
#include "legoracers.h"
#include "menuanimationlist.h"
#include "menutoolcontext0x4bc8.h"
#include "menutoolcreateparams0x30.h"
#include "onyxbreeze0x248.h"
#include "porcelainveil0x50.h"
#include "racedefinitionlist.h"
#include "racenamelist.h"
#include "sapphirereef0x2030.h"
#include "stackoflegou16.h"
#include "tanzanitewisp0x88.h"
#include "topazburst0x14.h"
#include "turquoiseglow0x80.h"
#include "types.h"
#include "verdanttide0x38.h"

class GolExport;
class ImaginaryTool0x368;
class SoundGroup;

// VTABLE: LEGORACERS 0x004b05a4
// SIZE 0x4dd4
class MenuManager : public CactusInterface0x4 {
public:
	MenuManager();
	void VTable0x00() override;                       // vtable+0x00
	void VTable0x1c(undefined4) override;             // vtable+0x1c
	void VTable0x24(undefined4, undefined4) override; // vtable+0x24
	void VTable0x28() override;                       // vtable+0x28
	void VTable0x2c() override;                       // vtable+0x2c
	virtual ~MenuManager();                           // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042c7c0
	// MenuManager::`scalar deleting destructor'

	static void Run(LegoRacers::Context* p_context);

	void Reset();
	LegoS32 Initialize(LegoRacers::Context* p_context);
	LegoS32 Shutdown();
	void FUN_0042cd60();
	void FUN_0042cde0();
	void ReleaseRendererObject();
	void InitializeInputBindings();
	void InitializeAudio();
	void LoadMenuImages();
	void FUN_0042d0e0();
	void LoadMenuData();
	void UnloadMenuData();
	LegoBool32 LoadLocalizedMenuResources(LegoU32 p_languageIndex, LegoBool32 p_forceReload);
	void FUN_0042d3e0(LegoU16 p_menuId);
	void Run();
	void FUN_0042e1f0();
	LegoBool32 FUN_0042e450();
	LegoS32 FUN_0042e490();
	LegoBool32 FUN_0042e680();
	void FUN_0042e720();

private:
	enum {
		c_menuTextRendererObjectName = 0x36,
	};

	void ShutdownInputBindings();
	void ShutdownAudio();
	void FUN_0042d080();
	void FUN_0042d730();

	MenuToolContext0x4bc8 m_unk0x04;        // 0x04
	ChromeSpike0x4 m_unk0x4bcc;             // 0x4bcc
	CrimsonSun0xa4 m_unk0x4bd0;             // 0x4bd0
	CopperCrest0x40 m_unk0x4c74;            // 0x4c74
	undefined4 m_unk0x4cb4;                 // 0x4cb4
	undefined4 m_unk0x4cb8;                 // 0x4cb8
	undefined4 m_unk0x4cbc;                 // 0x4cbc
	undefined4 m_unk0x4cc0;                 // 0x4cc0
	LegoU8 m_unk0x4cc4;                     // 0x4cc4
	undefined m_unk0x4cc5[0x4cc8 - 0x4cc5]; // 0x4cc5
	ImaginaryTool0x368* m_unk0x4cc8;        // 0x4cc8
	undefined m_unk0x4ccc[0x4cd4 - 0x4ccc]; // 0x4ccc
	GolExport* m_unk0x4cd4;                 // 0x4cd4
	BronzeFalcon0xc8770* m_unk0x4cd8;       // 0x4cd8
	AwakeKite0x20* m_imageTable;            // 0x4cdc
	GolFontTable* m_fontTable;              // 0x4ce0
	GolStringTable m_menuNameStrings;       // 0x4ce4
	GolStringTable m_menuTextStrings;       // 0x4cf8
	GolStringTable m_raceStrings;           // 0x4d0c
	SoundGroup* m_soundGroup;               // 0x4d20
	GolString m_unk0x4d24;                  // 0x4d24
	GolString m_unk0x4d30;                  // 0x4d30
	SoundGroupBinding m_soundGroupBinding;  // 0x4d3c
	PorcelainVeil0x50 m_menuStyles;         // 0x4d48
	MenuToolCreateParams0x30 m_unk0x4d98;   // 0x4d98
	ImaginaryTool0x368* m_unk0x4dc8;        // 0x4dc8
	undefined4 m_unk0x4dcc;                 // 0x4dcc
	LegoBool32 m_unk0x4dd0;                 // 0x4dd0
};

#endif // MENUMANAGER_H
