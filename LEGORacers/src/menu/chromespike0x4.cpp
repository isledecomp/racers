#include "menu/chromespike0x4.h"

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

DECOMP_SIZE_ASSERT(ChromeSpike0x4, 0x4)

// FUNCTION: LEGORACERS 0x0047f4c0
ChromeSpike0x4::~ChromeSpike0x4()
{
	Shutdown();
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
LegoBool32 ChromeSpike0x4::Shutdown()
{
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047f4d0
LegoBool32 ChromeSpike0x4::Initialize()
{
	Shutdown();
	return TRUE;
}

// FUNCTION: LEGORACERS 0x0047f4e0
ImaginaryTool0x368* ChromeSpike0x4::FUN_0047f4e0(LegoU16 p_menuId)
{
	ImaginaryTool0x368* tool;
	switch (p_menuId) {
	case c_menuSplash:
	case c_menuCredits:
	case c_menuLegal:
	case c_menuLegoIntro:
		tool = new SplashCinematicScreen();
		break;

	case c_menuMainIntro:
		tool = new MainIntroScreen();
		break;

	case c_menuMainMenu:
		tool = new MainMenuScreen();
		break;

	case c_menuCircuitRace:
		tool = new CircuitRaceScreen();
		break;

	case c_menuTimeTrial:
	case c_menuSingleRace:
		tool = new RaceModeSetupScreen();
		break;

	case c_menuGarage:
		tool = new GarageScreen();
		break;

	case c_menuDriverLicense:
		tool = new DriverLicenseScreen();
		break;

	case c_menuEditCar:
		tool = new EditCarScreen();
		break;

	case c_menuEditDriver:
		tool = new EditDriverScreen();
		break;

	case c_menuOptions:
		tool = new OptionsScreen();
		break;

	case c_menuControl1:
	case c_menuControl2:
		tool = new ControlConfigScreen();
		break;

	case c_menuPickMem:
		tool = new PickMemoryCardScreen();
		break;

	case c_menuPickRacer:
	case c_menuPickRacerP1:
	case c_menuPickRacerP2:
		tool = new PickRacerScreen();
		break;

	case c_menuChampAward1:
	case c_menuChampAward2:
	case c_menuChampAward3:
	case c_menuChampAward4:
	case c_menuWinCar:
	case c_menuWinRrCar:
	case c_menuWinVvCar:
	case c_menuCircuit7:
		tool = new AwardCinematicScreen();
		break;

	case c_menuCircuit1:
	case c_menuCircuit2:
	case c_menuCircuit3:
	case c_menuCircuit4:
	case c_menuCircuit5:
	case c_menuCircuit6:
		tool = new CircuitSelectScreen();
		break;

	case c_menuCarBuild:
		tool = new CarBuildScreen();
		break;

	case c_menuMultiPic:
		tool = new MultiplayerPickScreen();
		break;

	case c_menuPickLanguage:
		tool = new PickLanguageScreen();
		break;

	case c_menuLoadAll:
	case c_menuLoadCard:
	case c_menuLcCreate:
	case c_menuSaveAll:
	case c_menuSaveCard:
		tool = new SaveLoadScreen();
		break;

	case c_menuNewRacer:
		tool = new NewRacerScreen();
		break;

	default:
		tool = NULL;
		break;
	}

	if (!tool) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	return tool;
}

// FUNCTION: LEGORACERS 0x0049eb10
ChromeSpike0x4::ChromeSpike0x4()
{
}
