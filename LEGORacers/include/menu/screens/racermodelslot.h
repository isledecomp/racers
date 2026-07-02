#ifndef RACERMODELSLOT_H
#define RACERMODELSLOT_H

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/menusceneelement.h"

class GolWorldEntity;

// VTABLE: LEGORACERS 0x004b3db4
// SIZE 0xa0
class RacerModelSlot : public MenuSceneElement {
public:
	// SIZE 0x48
	class CreateParams : public MenuSceneElement::CreateParams {
	public:
		undefined4 m_unk0x0c[8]; // 0x0c
		GolVec3 m_position;      // 0x2c
		undefined4 m_unk0x38;    // 0x38
		undefined4 m_unk0x3c;    // 0x3c
		LegoFloat m_spinSpeed;   // 0x40
		LegoBool32 m_animate;    // 0x44
	};

	RacerModelSlot();

	void Reset() override;                         // vtable+0x00
	~RacerModelSlot() override;                    // vtable+0x04
	LegoBool32 Draw() override;                    // vtable+0x0c
	LegoBool32 Update(LegoU32 p_elapsed) override; // vtable+0x10

	LegoBool32 Create(CreateParams* p_createParams);
	void SetEntity(GolWorldEntity* p_entity);
	GolWorldEntity* GetEntity() const { return m_entity; }

	// SYNTHETIC: LEGORACERS 0x00487500
	// RacerModelSlot::`scalar deleting destructor'

private:
	LegoBool32 UpdateEntityA(LegoU32 p_elapsed);
	LegoBool32 UpdateEntityB(LegoU32 p_elapsed);
	LegoBool32 UpdateSpin(LegoS32 p_elapsed);

	CreateParams m_createParams; // 0x1c
	GolWorldEntity* m_entityA;   // 0x64
	GolWorldEntity* m_entity;    // 0x68
	GolWorldEntity* m_entityB;   // 0x6c
	GolVec3 m_spinAxis;          // 0x70
	undefined4 m_unk0x7c;        // 0x7c
	undefined4 m_unk0x80;        // 0x80
	undefined4 m_unk0x84;        // 0x84
	undefined4 m_unk0x88[3];     // 0x88
	LegoU32 m_timerAMs;          // 0x94
	LegoU32 m_timerBMs;          // 0x98
	LegoBool32 m_promoteA;       // 0x9c
};

#endif // RACERMODELSLOT_H
