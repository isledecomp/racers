#ifndef CARPARTCAROUSEL_H
#define CARPARTCAROUSEL_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menumodelcarousel.h"
#include "model/carpartset.h"
#include "types.h"

class GolModelEntity;
class LegoPieceLibrary;
class MenuIcon;
class CarBuildModel;
class LegoColorTable;

extern const LegoFloat g_twoPi;

// VTABLE: LEGORACERS 0x004b3c10
// SIZE 0x154
class CarPartCarousel : public MenuModelCarousel {
public:
	// SIZE 0x84
	class CreateParams : public MenuModelCarousel::CreateParams {
	public:
		CarPartSet* m_partSet;            // 0x74
		LegoPieceLibrary* m_pieceLibrary; // 0x78
		CarBuildModel* m_buildModel;      // 0x7c
		LegoColorTable* m_colorTable;     // 0x80
	};

	CarPartCarousel();

	void Reset() override;                                 // vtable+0x00
	~CarPartCarousel() override;                           // vtable+0x04
	LegoBool32 Destroy() override;                         // vtable+0x08
	undefined4 OnEvent(undefined4) override;               // vtable+0x3c
	void SetSelection(undefined4) override;                // vtable+0x50
	LegoS32 ScrollNext() override;                         // vtable+0x54
	LegoS32 ScrollPrevious() override;                     // vtable+0x58
	void LayoutItem(undefined4, GolModelEntity*) override; // vtable+0x5c
	void RefreshItemModel(LegoS32) override;               // vtable+0x60

	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	LegoS32 InitializeItemModels();
	void RefreshChoiceIndices();
	void SelectPartByType(LegoS32 p_pieceType);
	void SelectChoice(LegoS32 p_pieceType, LegoS32 p_colorRecordIndex);
	LegoS32 GetChoiceIndex(LegoS32 p_index) const { return m_choiceIndices[p_index]; }

	// SYNTHETIC: LEGORACERS 0x00485250
	// CarPartCarousel::`scalar deleting destructor'

private:
	enum {
		c_vectorZCosineIndex = 114,
		c_vectorXCosineIndex = 882,
	};

	CarPartSet* m_partSet;             // 0xc0
	LegoPieceLibrary* m_pieceLibrary;  // 0xc4
	CarBuildModel* m_buildModel;       // 0xc8
	LegoColorTable* m_colorTable;      // 0xcc
	CarPartSet::Entry* m_currentEntry; // 0xd0
	LegoS32 m_choiceIndices[30];       // 0xd4
	LegoS32 m_currentPieceType;        // 0x14c
	LegoFloat m_rotationAngle;         // 0x150
};

#endif // CARPARTCAROUSEL_H
