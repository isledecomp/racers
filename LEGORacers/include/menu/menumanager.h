#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "app/golappeventhandler.h"
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
#include "menu/menuinputdispatcher.h"
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
#include "types.h"
#include "util/stackoflegou16.h"

class GolModelRenderState;
class GolExport;
class MenuGameScreen;
class SoundGroup;

// VTABLE: LEGORACERS 0x004b05a4
// SIZE 0x4dd4
class MenuManager : public GolAppEventHandler {
private:
	enum {
		c_menuCursorImageName = 0x36,
		c_maxScreenshotIndex = 9999,
	};

public:
	MenuManager();
	void OnCloseRequested() override;                            // vtable+0x00
	void OnChar(undefined4 p_char) override;                     // vtable+0x1c
	void OnCursorMoved(undefined4 p_x, undefined4 p_y) override; // vtable+0x24
	void OnCursorInside() override;                              // vtable+0x28
	void OnCursorOutside() override;                             // vtable+0x2c
	virtual ~MenuManager();                                      // vtable+0x30

	// SYNTHETIC: LEGORACERS 0x0042c7c0
	// MenuManager::`scalar deleting destructor'

	static void Run(LegoRacers::Context* p_context);

	void Reset();
	LegoS32 Initialize(LegoRacers::Context* p_context);
	LegoS32 Shutdown();
	void InitializeInputDispatcher();
	void SetupCamera();
	void ReleaseRendererObject();
	void InitializeInputBindings();
	void InitializeAudio();
	void LoadMenuImages();
	void InitializeSaveSystem();
	void LoadMenuData();
	void UnloadMenuData();
	LegoBool32 LoadLocalizedMenuResources(LegoU32 p_languageIndex, LegoBool32 p_forceReload);
	void OpenScreen(LegoU16 p_menuId);
	void Run();
	void ApplySettings();
	LegoBool32 HasPendingMemoryCardSaves();
	LegoS32 CommitBestTimes();
	LegoBool32 ProcessRecordBeaten();
	void TakeScreenshot();

private:
	void ShutdownInputBindings();
	void ShutdownAudio();
	void UnloadMenuImages();
	void PrepareRaceContext();
	void BuildPlayerCarModel(
		SaveRecordList::Record* p_record,
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		GolModelRenderState* p_rendererState
	);
	void LoadPartResources(LegoBool32 p_arg);
	void ReleasePartResources();
	void BuildPlayerDriverModel(
		SaveRecordList::Record* p_record,
		LegoRacers::Context::PlayerSetupSlot* p_slot,
		GolModelRenderState* p_rendererState
	);

	MenuGameContext m_gameContext;               // 0x04
	MenuScreenFactory m_screenFactory;           // 0x4bcc
	MenuDialog m_dialog;                         // 0x4bd0
	MenuInputDispatcher m_inputDispatcher;       // 0x4c74
	GolExport* m_golExport;                      // 0x4cd4
	GolD3DRenderDevice* m_renderer;              // 0x4cd8
	GolImageDefinitionList* m_imageTable;        // 0x4cdc
	GolFontTable* m_fontTable;                   // 0x4ce0
	GolStringTable m_menuNameStrings;            // 0x4ce4
	GolStringTable m_menuTextStrings;            // 0x4cf8
	GolStringTable m_raceStrings;                // 0x4d0c
	SoundGroup* m_soundGroup;                    // 0x4d20
	GolString m_cursorImageName;                 // 0x4d24
	GolString m_screenName;                      // 0x4d30
	SoundGroupBinding m_soundGroupBinding;       // 0x4d3c
	SharedMenuStyleTable m_menuStyles;           // 0x4d48
	MenuScreenCreateParams m_screenCreateParams; // 0x4d98
	MenuGameScreen* m_activeScreen;              // 0x4dc8
	undefined4 m_unk0x4dcc;                      // 0x4dcc
	LegoBool32 m_running;                        // 0x4dd0
};

#endif // MENUMANAGER_H
