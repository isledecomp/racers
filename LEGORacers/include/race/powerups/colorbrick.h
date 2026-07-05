#ifndef COLORBRICK_H
#define COLORBRICK_H

#include "race/powerups/pickupbrick.h"

class GolMaterial;

// VTABLE: LEGORACERS 0x004b1710
// SIZE 0x68
class ColorBrick : public PickupBrick {
public:
	enum {
		c_soundRespawn = 0x0e,
		c_soundCollect = 0x31,
		c_soundSwap = 0x48,
	};

	ColorBrick();
	~ColorBrick() override;
	void OnTouched(Racer* p_racer) override;
	void Respawn() override;
	void Draw(GolD3DRenderDevice* p_renderer) override;
	void DrawTransparent(GolD3DRenderDevice* p_renderer) override;

	// SYNTHETIC: LEGORACERS 0x00458e20
	// ColorBrick::`vector deleting destructor'

	void SetColor(LegoU32 p_brickColor);
	void Destroy();
	void Update(LegoU32 p_elapsedMs);
	void SetMaterials(GolMaterial* p_brickMaterial, GolMaterial* p_trailMaterial);
	void SetRespawnMs(LegoU32 p_respawnMs) { m_respawnMs = p_respawnMs; }

private:
	GolMaterial* m_brickMaterial; // 0x54
	GolMaterial* m_trailMaterial; // 0x58
	LegoU32 m_assignedColor;      // 0x5c
	LegoU32 m_currentColor;       // 0x60
	LegoU32 m_nextColor;          // 0x64
};

#endif // COLORBRICK_H
