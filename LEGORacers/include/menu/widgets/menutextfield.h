#ifndef MENUTEXTFIELD_H
#define MENUTEXTFIELD_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/widgets/menuicon.h"
#include "render/rectangle.h"

class GolFontBase;
class GolStringTable;

// VTABLE: LEGORACERS 0x004b285c
// SIZE 0x23c
class MenuTextField : public MenuIcon {
public:
#pragma pack(push, 1)
	// The four text-input sound-effect ids (key accepted, value cycled, key
	// removed, input rejected), accessed individually as words but copied from
	// the create params as two 32-bit units.
	// SIZE 0x08
	struct SoundIdSet {
		union {
			LegoU16 m_ids[4];        // 0x00
			undefined4 m_idPairs[2]; // 0x00
		};
	};
#pragma pack(pop)

	// SIZE 0xa0
	class CreateParams : public MenuIcon::CreateParams {
	public:
		GolStringTable* m_stringTable;    // 0x84
		undefined2 m_charsetStringId;     // 0x88
		undefined m_unk0x8a[0x8c - 0x8a]; // 0x8a
		GolFontBase* m_font;              // 0x8c
		GolString* m_initialText;         // 0x90
		undefined2 m_maxLength;           // 0x94
		SoundIdSet m_editSoundIds;        // 0x96
	};

	MenuTextField();

	void Reset() override;                                                           // vtable+0x00
	~MenuTextField() override;                                                       // vtable+0x04
	MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;               // vtable+0x2c
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	void Select(undefined4) override;                                                // vtable+0x4c
	void Deselect(undefined4) override;                                              // vtable+0x50
	virtual LegoBool32 CreateField(CreateParams*, const MenuIcon::CreateState*);     // vtable+0x70
	void HandleEditAction(undefined4 p_action);
	void SetText(GolString* p_string);
	undefined2* GetBuffer() { return m_buffer; }

	// SYNTHETIC: LEGORACERS 0x00470f20
	// MenuTextField::`scalar deleting destructor'

private:
	MenuWidget* HandleCharacterInput(InputEventQueue::Event* p_event);
	MenuWidget* HandleJoystickInput(InputEventQueue::Event* p_event);

protected:
	SoundIdSet m_editSoundIds;                // 0x1a8
	GolStringTable* m_stringTable;            // 0x1b0
	undefined2 m_buffer[(0x1f4 - 0x1b4) / 2]; // 0x1b4
	undefined2 m_charsetIndex;                // 0x1f4
	undefined2 m_unk0x1f6;                    // 0x1f6
	LegoU32 m_inputMode;                      // 0x1f8
	GolString m_charset;                      // 0x1fc
	GolString m_text;                         // 0x208
	GolFontBase* m_font;                      // 0x214
	Rect m_textRect;                          // 0x218
	undefined m_unk0x228[0x238 - 0x228];      // 0x228
	undefined2 m_maxLength;                   // 0x238
	undefined2 m_length;                      // 0x23a
};

#endif // MENUTEXTFIELD_H
