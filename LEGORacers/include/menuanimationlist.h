#ifndef MENUANIMATIONLIST_H
#define MENUANIMATIONLIST_H

#include "decomp.h"
#include "types.h"
#include "whitefalcon0x140.h"

class BronzeFalcon0xc8770;

// SIZE 0x8
class MenuAnimationList {
public:
	// SIZE 0x18
	class Entry {
	public:
		enum {
			c_flagActive = 0x01,
			c_flagFadeOut = 0x02,
			c_flagExpired = 0x04,
		};

		struct ScreenRect {
			LegoS32 m_left;   // 0x00
			LegoS32 m_top;    // 0x04
			LegoS32 m_right;  // 0x08
			LegoS32 m_bottom; // 0x0c
		};

		// SIZE 0x120
		struct ScreenRectSource {
			undefined m_unk0x000[0x110 - 0x000]; // 0x000
			ScreenRect m_rect;                   // 0x110

			const ScreenRect* GetRect() const { return &m_rect; }
		};

		// SIZE 0x78
		struct DrawScratch {
			LegoFloat m_topAsFloat;                         // 0x00
			LegoU8 m_alpha;                                 // 0x04
			undefined m_unk0x05[0x08 - 0x05];               // 0x05
			ScreenRect m_rect;                              // 0x08
			WhiteFalcon0x140::TexturedVertex m_topLeft;     // 0x18
			WhiteFalcon0x140::TexturedVertex m_bottomRight; // 0x30
			WhiteFalcon0x140::TexturedVertex m_bottomLeft;  // 0x48
			WhiteFalcon0x140::TexturedVertex m_topRight;    // 0x60
		};

		Entry();
		~Entry();

		void Activate(
			LegoU32 p_durationMs,
			LegoBool32 p_fadeOut,
			undefined4 p_material,
			const ScreenRectSource* p_rectSource
		);
		void Reset();
		void Deactivate();
		void Update(LegoU32 p_elapsedMs);
		void Draw(BronzeFalcon0xc8770* p_renderer);
		LegoBool IsActive() { return m_flags & c_flagActive; }

	private:
		void Clear();

		undefined4 m_material;                // 0x00
		const ScreenRectSource* m_rectSource; // 0x04
		LegoU8 m_red;                         // 0x08
		LegoU8 m_green;                       // 0x09
		LegoU8 m_blue;                        // 0x0a
		undefined m_unk0x0b;                  // 0x0b
		LegoU32 m_remainingMs;                // 0x0c
		LegoU32 m_durationMs;                 // 0x10
		LegoU8 m_flags;                       // 0x14
		undefined m_unk0x15[3];               // 0x15
	};

	MenuAnimationList();
	~MenuAnimationList();
	void Reset();
	void Allocate(LegoU32 p_count);
	void Update(LegoU32 p_elapsedMs);
	void Draw(BronzeFalcon0xc8770* p_renderer);

private:
	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // MENUANIMATIONLIST_H
