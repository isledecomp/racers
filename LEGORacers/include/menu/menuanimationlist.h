#ifndef MENUANIMATIONLIST_H
#define MENUANIMATIONLIST_H

#include "decomp.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"
#include "surface/color.h"
#include "types.h"

class GolD3DRenderDevice;
class GolMaterial;
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
			GolMaterial* p_material,
			const GolCameraBase* p_rectSource
		);
		void Reset();
		void Deactivate();
		void Update(LegoU32 p_elapsedMs);
		void Draw(GolD3DRenderDevice* p_renderer);
		LegoBool IsActive() { return m_flags & c_flagActive; }
		void SetColor(LegoU32 p_colorPacked) { m_colorPacked = p_colorPacked; }
		void SetColor(ColorRGBA p_color) { m_color = p_color; }

	private:
		void Clear();

		GolMaterial* m_material;           // 0x00
		const GolCameraBase* m_rectSource; // 0x04
		union {
			ColorRGBA m_color;     // 0x08
			LegoU32 m_colorPacked; // 0x08
		};
		LegoU32 m_remainingMs; // 0x0c
		LegoU32 m_durationMs;  // 0x10
		LegoU8 m_flags;        // 0x14
	};

	MenuAnimationList();
	~MenuAnimationList();
	void Reset();
	void Allocate(LegoU32 p_count);
	Entry* Activate(
		LegoU32 p_durationMs,
		LegoBool32 p_fadeOut,
		GolMaterial* p_material,
		const GolCameraBase* p_rectSource
	);
	void Deactivate(Entry* p_entry);
	LegoBool32 HasActive() const;
	void Update(LegoU32 p_elapsedMs);
	void Draw(GolD3DRenderDevice* p_renderer);
	void DeactivateAll();

private:
	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // MENUANIMATIONLIST_H
