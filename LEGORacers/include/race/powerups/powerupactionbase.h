#ifndef POWERUPACTIONBASE_H
#define POWERUPACTIONBASE_H

#include "race/powerups/powerupaction.h"

// VTABLE: LEGORACERS 0x004b132c
// SIZE 0x18
class PowerupActionBase : public PowerupAction {
public:
	PowerupActionBase();
	~PowerupActionBase();
	void OnEvent(LegoEventQueue::CallbackData* p_param) override; // vtable+0x00
	PowerupAction* Destroy(undefined4 p_flags) override;          // vtable+0x04
	void Update(LegoU32) override;                                // vtable+0x08
	void Draw(GolD3DRenderDevice*) override;                      // vtable+0x0c
	void DrawTransparent(GolD3DRenderDevice*) override;           // vtable+0x10
	void AdvanceState() override = 0;                             // vtable+0x14
	LegoS32 GetBrickColor() override = 0;                         // vtable+0x18
	void Deactivate() override;                                   // vtable+0x1c
};

#endif // POWERUPACTIONBASE_H
