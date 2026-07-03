#ifndef OPTIONSROWBASE_H
#define OPTIONSROWBASE_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"

// VTABLE: LEGORACERS 0x004b2514
// SIZE 0x6e4
class OptionsRowBase : public MenuSelectorBase {
public:
	OptionsRowBase();
	void Reset() override;                                                           // vtable+0x00
	~OptionsRowBase() override;                                                      // vtable+0x04
	void SetColor(VisualStateColor*) override;                                       // vtable+0x14
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
	undefined4 OnEvent(undefined4) override;                                         // vtable+0x3c
	undefined4 TranslateNavigationEvent(undefined4) override;                        // vtable+0x74
	void StepPrevious() override;                                                    // vtable+0x78
	void StepNext() override;                                                        // vtable+0x7c
	virtual void LayoutButtons() = 0;                                                // vtable+0x80
	virtual void LayoutTrack() = 0;                                                  // vtable+0x84
	virtual void LayoutThumb() = 0;                                                  // vtable+0x88
	virtual void SnapThumbToValue() = 0;                                             // vtable+0x8c
	virtual void SetValue(LegoS32) = 0;                                              // vtable+0x90

	LegoS32 GetValue() const { return m_value; }

	// SYNTHETIC: LEGORACERS 0x0046ded0
	// OptionsRowBase::`scalar deleting destructor'

protected:
	friend class MenuScreen;

	LegoBool32 Create(
		MenuInputBindingTable::CompositeBinding* p_createParams,
		MenuStyleTable::CompositeStyle* p_styleEntry
	);

	MenuImage m_thumb;                   // 0x5ec
	MenuImage m_track;                   // 0x648
	undefined m_unk0x6a4[0x6bc - 0x6a4]; // 0x6a4
	LegoS32 m_stepCount;                 // 0x6bc
	LegoS32 m_value;                     // 0x6c0
	LegoS32 m_trackMinX;                 // 0x6c4
	LegoS32 m_trackMaxX;                 // 0x6c8
	LegoFloat m_stepWidth;               // 0x6cc
	Rect m_trackRect;                    // 0x6d0
	MenuIcon::SoundIdPair m_soundIds;    // 0x6e0
};

#endif // OPTIONSROWBASE_H
