#ifndef MENUSCREENID_H
#define MENUSCREENID_H

// Menu IDs dispatched in MenuScreenFactory::CreateScreen (LEGORACERS 0x0047f4e0).
// Names taken verbatim from MENUDATA\MENUNAME.SRF (the game's own screen-name
// string table), looked up at runtime by MenuScreen::LoadStylesAndBindings to
// build each screen's .MIB filename (LEGORacers/src/menu/screens/menuscreen.cpp).
enum {
	c_menuSplash = 0x01,        // MENUNAME[1]  = "splash"
	c_menuMainMenu = 0x02,      // MENUNAME[2]  = "mainmenu"
	c_menuGarage = 0x03,        // MENUNAME[3]  = "garage"
	c_menuPickSet = 0x04,       // MENUNAME[4]  = "pickset", no MenuScreenFactory branch
	c_menuCircuitRace = 0x05,   // MENUNAME[5]  = "circrace"
	c_menuSingleRace = 0x06,    // MENUNAME[6]  = "singrace"
	c_menuTuneUp = 0x07,        // MENUNAME[7]  = "tuneup", no MenuScreenFactory branch
	c_menuOptions = 0x08,       // MENUNAME[8]  = "options"
	c_menuControl = 0x09,       // MENUNAME[9]  = "control", no MenuScreenFactory branch
	c_menuControl1 = 0x0a,      // MENUNAME[10] = "control1"
	c_menuControl2 = 0x0b,      // MENUNAME[11] = "control2"
	c_menuPickMem = 0x0c,       // MENUNAME[12] = "pickmem"
	c_menuPause = 0x0d,         // MENUNAME[13] = "pause", no MenuScreenFactory branch
	c_menuCarBuild = 0x0e,      // MENUNAME[14] = "carbuild"
	c_menuEditDriver = 0x0f,    // MENUNAME[15] = "editdrvr"
	c_menuDriverLicense = 0x10, // MENUNAME[16] = "drvrlice"
	c_menuEditCar = 0x11,       // MENUNAME[17] = "editcar"
	c_menuSelectChassis = 0x12, // MENUNAME[18] = "selchas", no MenuScreenFactory branch
	c_menuPickRacer = 0x13,     // MENUNAME[19] = "pickrcr"
	c_menuPickRacerP1 = 0x14,   // MENUNAME[20] = "pickrcr"
	c_menuPickRacerP2 = 0x15,   // MENUNAME[21] = "pickrcr"
	c_menuChampAward1 = 0x16,   // MENUNAME[22] = "c_award1"
	c_menuChampAward2 = 0x17,   // MENUNAME[23] = "c_award2"
	c_menuChampAward3 = 0x18,   // MENUNAME[24] = "c_award3"
	c_menuChampAward4 = 0x19,   // MENUNAME[25] = "c_award4"
	c_menuWinCar = 0x1a,        // MENUNAME[26] = "wincar"
	c_menuWinRrCar = 0x1b,      // MENUNAME[27] = "winrrcar"
	c_menuWinVvCar = 0x1c,      // MENUNAME[28] = "winvvcar"
	c_menuTimeTrial = 0x1d,     // MENUNAME[29] = "ttrial"
	c_menuMultiPic = 0x1e,      // MENUNAME[30] = "multipic"
	c_menuCircuit1 = 0x1f,      // MENUNAME[31] = "circuit1"
	c_menuCircuit2 = 0x20,      // MENUNAME[32] = "circuit2"
	c_menuCircuit3 = 0x21,      // MENUNAME[33] = "circuit3"
	c_menuCircuit4 = 0x22,      // MENUNAME[34] = "circuit4"
	c_menuCircuit5 = 0x23,      // MENUNAME[35] = "circuit5"
	c_menuCircuit6 = 0x24,      // MENUNAME[36] = "circuit6"
	c_menuCircuit7 = 0x25,      // MENUNAME[37] = "circuit7"
	c_menuMainIntro = 0x26,     // MENUNAME[38] = "mainintr"
	c_menuCredits = 0x27,       // MENUNAME[39] = "credits"
	c_menuLegal = 0x28,         // MENUNAME[40] = "legal"
	c_menuLegoIntro = 0x29,     // MENUNAME[41] = "legointr"
	c_menuN64Start = 0x2a,      // MENUNAME[42] = "n64start"
	c_menuN64Intro = 0x2b,      // MENUNAME[43] = "n64intr" (handled inline by SplashCinematicScreen)
	c_menuPickLanguage = 0x2c,  // MENUNAME[44] = "picklang"
	c_menuLoadAll = 0x2d,       // MENUNAME[45] = "loadall"
	c_menuLoadCard = 0x2e,      // MENUNAME[46] = "loadcard"
	c_menuLcCreate = 0x2f,      // MENUNAME[47] = "lccreate"
	c_menuSaveAll = 0x30,       // MENUNAME[48] = "saveall"
	c_menuSaveCard = 0x31,      // MENUNAME[49] = "savecard"
	c_menuSaveGame = 0x32,      // MENUNAME[50] = "savegame", no MenuScreenFactory branch
	c_menuNewRacer = 0x90       // MENUNAME[144] = "newracer"
};

#endif // MENUSCREENID_H
