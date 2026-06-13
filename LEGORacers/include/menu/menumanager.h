#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "app/legoracers.h"
#include "audio/soundgroupbinding.h"
#include "compat.h"
#include "decomp.h"
#include "font/golfonttable.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "menu/menuanimationlist.h"
#include "menu/menudialog.h"
#include "menu/menugamecontext.h"
#include "menu/menuinputhandler.h"
#include "menu/menuscreencreateparams.h"
#include "menu/menuscreenfactory.h"
#include "menu/style/sharedmenustyletable.h"
#include "model/carbuildmodel.h"
#include "model/carpartset.h"
#include "model/legocolortable.h"
#include "model/legopiecelibrary.h"
#include "race/data/championdefinitionlist.h"
#include "race/data/circuitdefinitionlist.h"
#include "race/data/racenamelist.h"
#include "racer/chassismodeltable.h"
#include "racer/drivercosmetictable.h"
#include "racer/drivermodelbuilder.h"
#include "racer/driverpartcatalog.h"
#include "racer/driverpartresources.h"
#include "render/gold3drenderdevice.h"
#include "save/savesystem.h"
#include "text/coppercrest0x40.h"
#include "types.h"
#include "util/cactusinterface0x4.h"
#include "util/stackoflegou16.h"

class AmethystBreeze0x104;
class GolExport;
class MenuGameScreen;
class SoundGroup;

// VTABLE: LEGORACERS 0x004b05a4
// SIZE 0x4dd4
class MenuManager : public CactusInterface0x4 {
private:
	enum {
		c_menuTextRendererObjectName = 0x36,
	};

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
	void InitializeTextRenderer();
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
	void ShutdownInputBindings();
	void ShutdownAudio();
	void UnloadMenuImages();
	void FUN_0042d730();
	void FUN_0042dcb0(
		SaveRecordList::Record* p_record,
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		AmethystBreeze0x104* p_rendererState
	);
	void FUN_0042de90(LegoBool32 p_arg);
	void FUN_0042df70();
	void FUN_0042dfa0(
		SaveRecordList::Record* p_record,
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		AmethystBreeze0x104* p_rendererState
	);

	MenuGameContext m_unk0x04;             // 0x04
	MenuScreenFactory m_unk0x4bcc;         // 0x4bcc
	MenuDialog m_unk0x4bd0;                // 0x4bd0
	CopperCrest0x40 m_textRenderer;        // 0x4c74
	GolExport* m_golExport;                // 0x4cd4
	GolD3DRenderDevice* m_renderer;        // 0x4cd8
	AwakeKite0x20* m_imageTable;           // 0x4cdc
	GolFontTable* m_fontTable;             // 0x4ce0
	GolStringTable m_menuNameStrings;      // 0x4ce4
	GolStringTable m_menuTextStrings;      // 0x4cf8
	GolStringTable m_raceStrings;          // 0x4d0c
	SoundGroup* m_soundGroup;              // 0x4d20
	GolString m_unk0x4d24;                 // 0x4d24
	GolString m_unk0x4d30;                 // 0x4d30
	SoundGroupBinding m_soundGroupBinding; // 0x4d3c
	SharedMenuStyleTable m_menuStyles;     // 0x4d48
	MenuScreenCreateParams m_unk0x4d98;    // 0x4d98
	MenuGameScreen* m_unk0x4dc8;           // 0x4dc8
	undefined4 m_unk0x4dcc;                // 0x4dcc
	LegoBool32 m_running;                  // 0x4dd0
};

#endif // MENUMANAGER_H
