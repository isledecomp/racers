#ifndef MENUGAMECONTEXT_H
#define MENUGAMECONTEXT_H

#include "app/legoracers.h"
#include "decomp.h"
#include "menu/menuanimationlist.h"
#include "model/carbuildmodel.h"
#include "model/carpartset.h"
#include "model/legocolortable.h"
#include "model/legopiecelibrary.h"
#include "race/data/championdefinitionlist.h"
#include "race/data/racedefinitionlist.h"
#include "race/data/racenamelist.h"
#include "racer/aquamarinespirit0x3c.h"
#include "racer/drivercosmetictable.h"
#include "racer/lavendervault0x764.h"
#include "save/savesystem.h"
#include "util/garnetflare0x60.h"
#include "util/onyxbreeze0x248.h"
#include "util/stackoflegou16.h"
#include "util/tanzanitewisp0x88.h"

// SIZE 0x4bc8
class MenuGameContext {
public:
	LegoRacers::Context* m_context;               // 0x00
	StackOfLegoU16 m_menuStack;                   // 0x04
	OnyxBreeze0x248 m_inputBindings;              // 0x10
	SaveSystem m_unk0x258;                        // 0x258
	CarPartSet m_unk0x21a4;                       // 0x21a4
	LegoPieceLibrary m_pieceLibrary;              // 0x21b8
	CarBuildModel m_unk0x21f4;                    // 0x21f4
	LegoColorTable m_unk0x4224;                   // 0x4224
	DriverCosmeticTable m_unk0x425c;              // 0x425c
	AquamarineSpirit0x3c m_unk0x42dc;             // 0x42dc
	ChampionDefinitionList m_championDefinitions; // 0x4318
	RaceDefinitionList m_raceList;                // 0x434c
	RaceNameList m_raceNames;                     // 0x4360
	MenuAnimationList m_menuAnimations;           // 0x4374
	LavenderVault0x764 m_unk0x437c;               // 0x437c
	GarnetFlare0x60 m_unk0x4ae0;                  // 0x4ae0
	TanzaniteWisp0x88 m_unk0x4b40;                // 0x4b40
};

#endif // MENUGAMECONTEXT_H
