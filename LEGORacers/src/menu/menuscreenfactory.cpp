#include "menu/menuscreenfactory.h"

#include "golerror.h"
#include "menu/menuscreenid.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/carbuildscreen.h"
#include "menu/screens/circuitracescreen.h"
#include "menu/screens/circuitselectscreen.h"
#include "menu/screens/controlconfigscreen.h"
#include "menu/screens/driverlicensescreen.h"
#include "menu/screens/editcarscreen.h"
#include "menu/screens/editdriverscreen.h"
#include "menu/screens/garagescreen.h"
#include "menu/screens/mainintroscreen.h"
#include "menu/screens/mainmenuscreen.h"
#include "menu/screens/multiplayerpickscreen.h"
#include "menu/screens/newracerscreen.h"
#include "menu/screens/optionsscreen.h"
#include "menu/screens/picklanguagescreen.h"
#include "menu/screens/pickmemorycardscreen.h"
#include "menu/screens/pickracerscreen.h"
#include "menu/screens/racemodesetupscreen.h"
#include "menu/screens/saveloadscreen.h"
#include "menu/screens/splashcinematicscreen.h"

DECOMP_SIZE_ASSERT(MenuScreenFactory, 0x4)

// GLOBAL: LEGORACERS 0x004b3510
static const LegoFloat g_unk0x004b3510 = 6.2831855f;

// GLOBAL: LEGORACERS 0x004c7670
LegoFloat g_unk0x004c7670 = g_unk0x004b3510 * 0.125f;

// FUNCTION: LEGORACERS 0x0047f4c0
MenuScreenFactory::~MenuScreenFactory()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
LegoBool32 MenuScreenFactory::Shutdown()
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047f4d0
LegoBool32 MenuScreenFactory::Initialize()
{
	Shutdown();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047f4e0
MenuGameScreen* MenuScreenFactory::CreateScreen(LegoU16 p_menuId)
{
	MenuGameScreen* screen;
	switch (p_menuId) {
	case c_menuSplash:
	case c_menuCredits:
	case c_menuLegal:
	case c_menuLegoIntro:
		screen = new SplashCinematicScreen();
		break;

	case c_menuMainIntro:
		screen = new MainIntroScreen();
		break;

	case c_menuMainMenu:
		screen = new MainMenuScreen();
		break;

	case c_menuCircuitRace:
		screen = new CircuitRaceScreen();
		break;

	case c_menuTimeTrial:
	case c_menuSingleRace:
		screen = new RaceModeSetupScreen();
		break;

	case c_menuGarage:
		screen = new GarageScreen();
		break;

	case c_menuDriverLicense:
		screen = new DriverLicenseScreen();
		break;

	case c_menuEditCar:
		screen = new EditCarScreen();
		break;

	case c_menuEditDriver:
		screen = new EditDriverScreen();
		break;

	case c_menuOptions:
		screen = new OptionsScreen();
		break;

	case c_menuControl1:
	case c_menuControl2:
		screen = new ControlConfigScreen();
		break;

	case c_menuPickMem:
		screen = new PickMemoryCardScreen();
		break;

	case c_menuPickRacer:
	case c_menuPickRacerP1:
	case c_menuPickRacerP2:
		screen = new PickRacerScreen();
		break;

	case c_menuChampAward1:
	case c_menuChampAward2:
	case c_menuChampAward3:
	case c_menuChampAward4:
	case c_menuWinCar:
	case c_menuWinRrCar:
	case c_menuWinVvCar:
	case c_menuCircuit7:
		screen = new AwardCinematicScreen();
		break;

	case c_menuCircuit1:
	case c_menuCircuit2:
	case c_menuCircuit3:
	case c_menuCircuit4:
	case c_menuCircuit5:
	case c_menuCircuit6:
		screen = new CircuitSelectScreen();
		break;

	case c_menuCarBuild:
		screen = new CarBuildScreen();
		break;

	case c_menuMultiPic:
		screen = new MultiplayerPickScreen();
		break;

	case c_menuPickLanguage:
		screen = new PickLanguageScreen();
		break;

	case c_menuLoadAll:
	case c_menuLoadCard:
	case c_menuLcCreate:
	case c_menuSaveAll:
	case c_menuSaveCard:
		screen = new SaveLoadScreen();
		break;

	case c_menuNewRacer:
		screen = new NewRacerScreen();
		break;

	default:
		screen = NULL;
		break;
	}

	if (!screen) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return screen;
}

// FUNCTION: LEGORACERS 0x0049eb10 FOLDED
MenuScreenFactory::MenuScreenFactory()
{
}
