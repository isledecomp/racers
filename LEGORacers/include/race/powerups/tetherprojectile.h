#ifndef TETHERPROJECTILE_H
#define TETHERPROJECTILE_H

#include "race/powerups/powerupprojectile.h"

class Racer;

// VTABLE: LEGORACERS 0x004b0ca8
// SIZE 0x238
class TetherProjectile : public PowerupProjectile {
public:
	// SIZE 0x20
	struct SetupParams {
		GolExport* m_golExport;     // 0x00
		LegoFloat m_attachHeight;   // 0x04
		LegoFloat m_ropeThickness;  // 0x08
		LegoFloat m_waveAmplitude;  // 0x0c
		ColorRGBA m_baseColor;      // 0x10
		ColorRGBA m_secondaryColor; // 0x14
		ColorRGBA m_tertiaryColor;  // 0x18
		GolMaterial* m_material;    // 0x1c
	};

	TetherProjectile();
	~TetherProjectile();
	PowerupProjectile* Destroy(undefined4) override;
	void Deactivate() override;
	LegoS32 Update(LegoU32 p_elapsedMs) override;
	virtual void Initialize(const SetupParams* p_params); // vtable+0x20
	virtual void Draw(GolD3DRenderDevice* p_renderer);    // vtable+0x24

	void Release(GolVec3* p_position);
	void ResetRope()
	{
		m_tension = 0.0f;
		m_flags = 0;
	}

private:
	enum {
		c_flagSnapped = 1 << 0,
		c_flagReleased = 1 << 1,
	};

	void RebuildBeam(const GolVec3* p_position, LegoFloat p_elapsedMs, LegoFloat p_amount);
	LegoS32 UpdateReleased(LegoU32 p_elapsedMs);
	LegoS32 UpdateAttached(LegoU32 p_elapsedMs);

	BeamMesh m_beam;                  // 0x0a8
	LegoFloat m_attachHeight;         // 0x218
	LegoFloat m_waveAmplitude;        // 0x21c
	LegoFloat m_currentWaveAmplitude; // 0x220
	LegoFloat m_tension;              // 0x224
	GolVec3 m_endPosition;            // 0x228
	LegoU32 m_flags;                  // 0x234
};

#endif // TETHERPROJECTILE_H
