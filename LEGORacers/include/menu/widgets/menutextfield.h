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
		GolStringTable* m_unk0x84;        // 0x84
		undefined2 m_unk0x88;             // 0x88
		undefined m_unk0x8a[0x8c - 0x8a]; // 0x8a
		GolFontBase* m_unk0x8c;           // 0x8c
		GolString* m_unk0x90;             // 0x90
		undefined2 m_unk0x94;             // 0x94
		SoundIdSet m_soundIds;            // 0x96
		undefined m_unk0x9e[0xa0 - 0x9e]; // 0x9e
	};

	MenuTextField();

	void Reset() override;                                                            // vtable+0x00
	~MenuTextField() override;                                                        // vtable+0x04
	MenuWidget* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	MenuWidget* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	void VTable0x4c(undefined4) override;                                             // vtable+0x4c
	void VTable0x50(undefined4) override;                                             // vtable+0x50
	virtual LegoBool32 VTable0x70(CreateParams*, const MenuIcon::CreateState*);       // vtable+0x70
	void FUN_00471100(undefined4 p_unk0x04);
	void FUN_004711f0(GolString* p_string);
	undefined2* GetBuffer() { return m_buffer; }

	// SYNTHETIC: LEGORACERS 0x00470f20
	// MenuTextField::`scalar deleting destructor'

private:
	MenuWidget* FUN_004713f0(InputEventQueue::Event* p_event);
	MenuWidget* FUN_00471560(InputEventQueue::Event* p_event);

protected:
	SoundIdSet m_soundIds;                    // 0x1a8
	GolStringTable* m_stringTable;            // 0x1b0
	undefined2 m_buffer[(0x1f4 - 0x1b4) / 2]; // 0x1b4
	undefined2 m_unk0x1f4;                    // 0x1f4
	undefined2 m_unk0x1f6;                    // 0x1f6
	undefined4 m_unk0x1f8;                    // 0x1f8
	GolString m_charset;                      // 0x1fc
	GolString m_text;                         // 0x208
	GolFontBase* m_font;                      // 0x214
	Rect m_unk0x218;                          // 0x218
	undefined m_unk0x228[0x238 - 0x228];      // 0x228
	undefined2 m_maxLength;                   // 0x238
	undefined2 m_length;                      // 0x23a
};

#endif // MENUTEXTFIELD_H
