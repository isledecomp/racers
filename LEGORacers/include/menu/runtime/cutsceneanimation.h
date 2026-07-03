#ifndef CUTSCENEANIMATION_H
#define CUTSCENEANIMATION_H

#include "golmath.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "menu/runtime/cutsceneparticleref.h"

class CutsceneParticle;
class GolD3DRenderDevice;
class GolExport;
class GolMaterial;
class MabMaterialAnimation;
class MabMaterialTrack;

// VTABLE: LEGORACERS 0x004b403c
// SIZE 0x33c
class CutsceneAnimation : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004b4048
	// SIZE 0x1fc
	class EmbTxtParser : public GolTxtParser {};

	// SIZE 0x08
	class Entry : public CutsceneParticleRef {
	public:
		Entry();
		~Entry();
	};

	// SIZE 0x44
	class Emitter {
	public:
		Emitter();
		~Emitter();

		void Clear();
		void Reset();

		void Parse(
			MabMaterialAnimation* p_materialAnimation,
			GolD3DRenderDevice* p_renderer,
			GolFileParser* p_parser,
			CutsceneAnimation* p_param4
		);
		void GetVectorAt(GolVec3* p_vec, int p_index);
		void GetOrigin(GolVec3* p_vec) const;

		LegoU32 GetPointCount() { return m_pointCount; }
		LegoS32 GetEmitIntervalMs() { return m_emitIntervalMs; }
		LegoU8 GetEmitChance() { return m_emitChance; }
		LegoS32 GetParticleLifeMs() { return m_particleLifeMs; }
		LegoS32 GetDurationMs() { return m_durationMs; }
		LegoU8 GetPriority() const { return m_priority; }
		LegoBool32 IsPersistent() const { return m_durationMs == -1; }
		LegoFloat GetUnk0x1c() const { return m_unk0x1c; }
		LegoFloat GetUnk0x20() const { return m_unk0x20; }
		LegoFloat GetUnk0x24() const { return m_unk0x24; }
		LegoFloat GetUnk0x28() const { return m_unk0x28; }
		LegoFloat GetRadius() const { return m_radius; }
		MabMaterialTrack* GetMaterialAnimationItem() const { return m_materialAnimationItem; }
		MabMaterialAnimation* GetMaterialAnimation() const { return m_materialAnimation; }
		GolMaterial* GetMaterial() const { return m_material; }

	private:
		GolVec3* m_points;                         // 0x00
		LegoU32 m_pointCount;                      // 0x04
		LegoFloat m_originX;                       // 0x08
		LegoFloat m_originY;                       // 0x0c
		LegoFloat m_originZ;                       // 0x10
		LegoS32 m_emitIntervalMs;                  // 0x14
		LegoU8 m_emitChance;                       // 0x18
		LegoU8 m_priority;                         // 0x19
		LegoFloat m_unk0x1c;                       // 0x1c
		LegoFloat m_unk0x20;                       // 0x20
		LegoFloat m_unk0x24;                       // 0x24
		LegoFloat m_unk0x28;                       // 0x28
		LegoFloat m_radius;                        // 0x2c
		LegoS32 m_particleLifeMs;                  // 0x30
		LegoS32 m_durationMs;                      // 0x34
		MabMaterialTrack* m_materialAnimationItem; // 0x38
		MabMaterialAnimation* m_materialAnimation; // 0x3c
		GolMaterial* m_material;                   // 0x40
	};

	CutsceneAnimation();
	~CutsceneAnimation() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	LegoBool32 HasEmitter(const LegoChar* p_param);
	CutsceneParticleRef* SpawnParticle(
		const LegoChar* p_param1,
		GolVec3* p_param2,
		GolVec3* p_param3,
		GolVec3* p_param4
	);
	void ReleaseRef(CutsceneParticleRef* p_param);
	void FinishRef(CutsceneParticleRef* p_param);
	LegoU32 StopAllParticles();
	void Update(LegoU32 p_elapsedMs);
	void Draw(GolD3DRenderDevice* p_renderer);
	void DrawTransparent(GolD3DRenderDevice* p_renderer);
	void Load(
		LegoU32 p_unk0x04,
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		MabMaterialAnimation* p_materialAnimation,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);

	// SYNTHETIC: LEGORACERS 0x004a1180
	// CutsceneAnimation::`vector deleting destructor'

private:
	CutsceneParticle* m_particles; // 0x00c
	Emitter* m_emitters;           // 0x010
	Entry m_refs[100];             // 0x014
	LegoU32 m_emitterCount;        // 0x334
	LegoU32 m_numParticles;        // 0x338
};

#endif // CUTSCENEANIMATION_H
