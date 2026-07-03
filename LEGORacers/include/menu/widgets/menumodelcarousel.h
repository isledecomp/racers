#ifndef MENUMODELCAROUSEL_H
#define MENUMODELCAROUSEL_H

#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"
#include "menu/widgets/menucarousel.h"
#include "render/golrenderdevice.h"

class GolCamera;
class GolModelBase;

// VTABLE: LEGORACERS 0x004b2450
// SIZE 0xc0
class MenuModelCarousel : public MenuCarousel {
public:
	// SIZE 0x74
	class CreateParams : public MenuCarousel::CreateParams {
	public:
		LegoS32 m_slotCount;          // 0x38
		Rect* m_slotRects;            // 0x3c
		LegoFloat m_scrollStep;       // 0x40
		LegoS32 m_focusedSlot;        // 0x44
		LegoFloat m_cameraVectors[9]; // 0x48
		LegoU32 m_viewportIndex;      // 0x6c
		LegoFloat m_aspectScale;      // 0x70
	};

	// SIZE 0xd0
	class Item {
	public:
		LegoFloat m_left;                  // 0x00
		LegoFloat m_height;                // 0x04
		LegoFloat m_right;                 // 0x08
		LegoFloat m_unk0x0c;               // 0x0c
		Rect m_rect;                       // 0x10
		LegoFloat m_centerY;               // 0x20
		LegoFloat m_positionZ;             // 0x24
		LegoFloat m_fitSize;               // 0x28
		GolModelBase* m_model;             // 0x2c
		LegoFloat m_modelRadius;           // 0x30
		GolModelEntity m_entity;           // 0x34
		undefined4 m_unk0xc4;              // 0xc4
		VisualStateColor m_primaryColor;   // 0xc8
		VisualStateColor m_secondaryColor; // 0xcc
	};

	MenuModelCarousel();

	void Reset() override;                                                           // vtable+0x00
	~MenuModelCarousel() override;                                                   // vtable+0x04
	LegoBool32 Destroy() override;                                                   // vtable+0x08
	void SetParent(MenuWidget*) override;                                            // vtable+0x0c
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	undefined4 OnEvent(undefined4) override;                                         // vtable+0x3c
	void SnapToSelection() override;                                                 // vtable+0x40
	void StartScroll(undefined4) override;                                           // vtable+0x44
	void SetItemColors(VisualStateColor*, VisualStateColor*) override;               // vtable+0x48
	void SetFocusedItemColors(VisualStateColor*, VisualStateColor*) override;        // vtable+0x4c
	LegoS32 ScrollNext() override;                                                   // vtable+0x54
	LegoS32 ScrollPrevious() override;                                               // vtable+0x58
	virtual void LayoutItem(undefined4, GolModelEntity*);                            // vtable+0x5c
	virtual void RefreshItemModel(LegoS32);                                          // vtable+0x60

	// SYNTHETIC: LEGORACERS 0x0046ca60
	// MenuModelCarousel::`scalar deleting destructor'

protected:
	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	void SetupCamera(CreateParams* p_createParams);
	void InitializeItem(Item* p_item);
	void UpdateViewport();
	void PushCamera();
	void PopCamera();
	void CreateItems(CreateParams* p_createParams);
	void DestroyItems();
	void GetItemPosition(Item* p_item, GolVec3* p_position);
	GolModelEntity* GetItemEntity(LegoS32 p_index);
	GolModelBase* GetItemModel(LegoS32 p_index);

	LegoU32 m_viewportIndex;                        // 0x78
	Item* m_items;                                  // 0x7c
	GolCamera* m_camera;                            // 0x80
	GolCamera* m_savedCamera;                       // 0x84
	GolRenderDevice::MaterialColor m_materialColor; // 0x88
	GolRenderDevice::Light m_light;                 // 0x8c
	undefined4 m_unk0x9c;                           // 0x9c
	undefined4 m_unk0xa0;                           // 0xa0
	LegoFloat m_unk0xa4;                            // 0xa4
	undefined m_unk0xa8[0xb4 - 0xa8];               // 0xa8
	LegoFloat m_cameraDistance;                     // 0xb4
	LegoU32 m_ringBaseIndex;                        // 0xb8
	LegoFloat m_scrollStep;                         // 0xbc
};

#endif // MENUMODELCAROUSEL_H
