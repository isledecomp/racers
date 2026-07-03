#ifndef MENURACERCAROUSEL_H
#define MENURACERCAROUSEL_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menumodelcarousel.h"
#include "racer/driverheadbuilder.h"
#include "scene/golbillboard.h"

class MenuGameContext;
class SaveSystem;
class DriverPartCatalog;

// VTABLE: LEGORACERS 0x004b39d4
// SIZE 0x170
class MenuRacerCarousel : public MenuModelCarousel {
public:
	// SIZE 0x80
	class CreateParams : public MenuModelCarousel::CreateParams {
	public:
		MenuGameContext* m_context;       // 0x74
		DriverHeadBuilder* m_headBuilder; // 0x78
		LegoU32 m_partType;               // 0x7c
	};

	MenuRacerCarousel();

	void Reset() override;                   // vtable+0x00
	~MenuRacerCarousel() override;           // vtable+0x04
	LegoBool32 Destroy() override;           // vtable+0x08
	void SetSelection(undefined4) override;  // vtable+0x50
	LegoS32 ScrollNext() override;           // vtable+0x54
	LegoS32 ScrollPrevious() override;       // vtable+0x58
	void RefreshItemModel(LegoS32) override; // vtable+0x60

	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	void SelectValue(LegoS32 p_index);
	LegoS32 GetSelectedValue() const { return m_itemValues[m_selectedIndex]; }
	LegoS32 GetItemCount() const { return m_itemCount; }

	// SYNTHETIC: LEGORACERS 0x004839c0
	// MenuRacerCarousel::`scalar deleting destructor'

protected:
	void CopyModelMaterialTable(GolModelBase* p_model, GolBillboard::ManagedMaterialTable* p_materialTable);
	void CreateMaterialTables(LegoS32);
	void CollectHats(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void CollectFaces(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void CollectTorsos(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void CollectLegs(DriverPartCatalog* p_partCatalog, SaveSystem* p_saveSystem, LegoU32 p_unlockFlags);
	void CollectItems();

	GolBillboard::ManagedMaterialTable* m_materialTables; // 0xc0
	DriverHeadBuilder* m_headBuilder;                     // 0xc4
	MenuGameContext* m_context;                           // 0xc8
	LegoU32 m_partType;                                   // 0xcc
	LegoS32 m_itemValues[(0x170 - 0xd0) / 4];             // 0xd0
};

#endif // MENURACERCAROUSEL_H
