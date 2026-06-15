#ifndef MENUANIMATIONLIST_H
#define MENUANIMATIONLIST_H

#include "decomp.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"
#include "types.h"

class GolD3DRenderDevice;
class DuskwindBananaRelic0x24;
class GolCameraBase;

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

		// SIZE 0x78
		struct DrawScratch {
			LegoFloat m_topAsFloat;                        // 0x00
			LegoU8 m_alpha;                                // 0x04
			undefined m_unk0x05[0x08 - 0x05];              // 0x05
			Rect m_rect;                                   // 0x08
			GolRenderDevice::TexturedVertex m_topLeft;     // 0x18
			GolRenderDevice::TexturedVertex m_bottomRight; // 0x30
			GolRenderDevice::TexturedVertex m_bottomLeft;  // 0x48
			GolRenderDevice::TexturedVertex m_topRight;    // 0x60
		};

		Entry();
		~Entry();

		void Activate(
			LegoU32 p_durationMs,
			LegoBool32 p_fadeOut,
			DuskwindBananaRelic0x24* p_material,
			const GolCameraBase* p_rectSource
		);
		void Reset();
		void Deactivate();
		void Update(LegoU32 p_elapsedMs);
		void Draw(GolD3DRenderDevice* p_renderer);
		LegoBool IsActive() { return m_flags & c_flagActive; }
		void SetColor(LegoU32 p_colorPacked) { m_colorPacked = p_colorPacked; }

	private:
		void Clear();

		DuskwindBananaRelic0x24* m_material; // 0x00
		const GolCameraBase* m_rectSource;   // 0x04
		union {
			struct {
				LegoU8 m_red;        // 0x08
				LegoU8 m_green;      // 0x09
				LegoU8 m_blue;       // 0x0a
				undefined m_unk0x0b; // 0x0b
			};
			LegoU32 m_colorPacked; // 0x08
		};
		LegoU32 m_remainingMs;  // 0x0c
		LegoU32 m_durationMs;   // 0x10
		LegoU8 m_flags;         // 0x14
		undefined m_unk0x15[3]; // 0x15
	};

	MenuAnimationList();
	~MenuAnimationList();
	void Reset();
	void Allocate(LegoU32 p_count);
	Entry* Activate(
		LegoU32 p_durationMs,
		LegoBool32 p_fadeOut,
		DuskwindBananaRelic0x24* p_material,
		const GolCameraBase* p_rectSource
	);
	void Deactivate(Entry* p_entry);
	LegoBool32 HasActive() const;
	void Update(LegoU32 p_elapsedMs);
	void Draw(GolD3DRenderDevice* p_renderer);
	void FUN_00494fe0();

private:
	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // MENUANIMATIONLIST_H
