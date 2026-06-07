#ifndef MENUSCREENFACTORY_H
#define MENUSCREENFACTORY_H

#include "decomp.h"
#include "menu/screens/menugamescreen.h"
#include "types.h"

// SIZE 0x4
class MenuScreenFactory {
public:
	MenuScreenFactory();
	~MenuScreenFactory();
	LegoBool32 Shutdown();
	LegoBool32 Initialize();
	MenuGameScreen* CreateScreen(LegoU16 p_menuId);

private:
	undefined m_unk0x00[0x4 - 0x00]; // 0x00
};

#endif // MENUSCREENFACTORY_H
