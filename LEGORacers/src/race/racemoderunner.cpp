#include "race/racemoderunner.h"

#include "golerror.h"
#include "menu/menumanager.h"

extern RaceModeRunner* g_raceModeRunner;
extern MenuManager* g_menuManager;

// FUNCTION: LEGORACERS 0x0042b130
void RaceModeRunner::Run(LegoRacers::Context* p_context)
{
	g_raceModeRunner = new RaceModeRunner();
	if (!g_raceModeRunner) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_raceModeRunner->Initialize(p_context);
	g_raceModeRunner->Run();
	g_raceModeRunner->Shutdown();

	if (g_raceModeRunner) {
		delete g_raceModeRunner;
	}
}

// FUNCTION: LEGORACERS 0x0042b1e0
void MenuManager::Run(LegoRacers::Context* p_context)
{
	g_menuManager = new MenuManager();
	if (!g_menuManager) {
		GolFatalError(c_golErrorOutOfMemory, NULL, 0);
	}

	g_menuManager->Initialize(p_context);
	g_menuManager->Run();
	g_menuManager->Shutdown();

	if (g_menuManager) {
		delete g_menuManager;
	}
}
