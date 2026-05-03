#ifndef MENUTOOLCONTEXT0X4BC8_H
#define MENUTOOLCONTEXT0X4BC8_H

#include "aquamarinespirit0x3c.h"
#include "championdefinitionlist.h"
#include "citrinegrove0x1f4c.h"
#include "decomp.h"
#include "garnetflare0x60.h"
#include "lavendervault0x764.h"
#include "legopiecelibrary.h"
#include "legoracers.h"
#include "menuanimationlist.h"
#include "onyxbreeze0x248.h"
#include "racedefinitionlist.h"
#include "racenamelist.h"
#include "sapphirereef0x2030.h"
#include "stackoflegou16.h"
#include "tanzanitewisp0x88.h"
#include "topazburst0x14.h"
#include "turquoiseglow0x80.h"
#include "verdanttide0x38.h"

// SIZE 0x4bc8
class MenuToolContext0x4bc8 {
public:
	LegoRacers::Context* m_context;               // 0x00
	StackOfLegoU16 m_unk0x04;                     // 0x04
	OnyxBreeze0x248 m_inputBindings;              // 0x10
	CitrineGrove0x1f4c m_unk0x258;                // 0x258
	TopazBurst0x14 m_unk0x21a4;                   // 0x21a4
	LegoPieceLibrary m_pieceLibrary;              // 0x21b8
	SapphireReef0x2030 m_unk0x21f4;               // 0x21f4
	VerdantTide0x38 m_unk0x4224;                  // 0x4224
	TurquoiseGlow0x80 m_unk0x425c;                // 0x425c
	AquamarineSpirit0x3c m_unk0x42dc;             // 0x42dc
	ChampionDefinitionList m_championDefinitions; // 0x4318
	RaceDefinitionList m_raceList;                // 0x434c
	RaceNameList m_raceNames;                     // 0x4360
	MenuAnimationList m_menuAnimations;           // 0x4374
	LavenderVault0x764 m_unk0x437c;               // 0x437c
	GarnetFlare0x60 m_unk0x4ae0;                  // 0x4ae0
	TanzaniteWisp0x88 m_unk0x4b40;                // 0x4b40
};

#endif // MENUTOOLCONTEXT0X4BC8_H
