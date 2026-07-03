#ifndef RACESKY_H
#define RACESKY_H

#include "decomp.h"
#include "golmath.h"
#include "golmodelentity.h"
#include "golname.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "surface/color.h"
#include "types.h"

class GolWorldDatabase;
class GolModelBase;
class GdbModelIndexArray;
class GolTextureList;
class GolCamera;
class GolD3DRenderDevice;
class GolFileParser;
class GolExport;
class MabMaterialAnimation;
class MabMaterialTrack;
struct MaterialTable;
class GolMaterial;
class RaceSession;

// Sky/backdrop state for a race (sky model + material animation swaps
// driven by track events).
// VTABLE: LEGORACERS 0x004afd58
// SIZE 0xc8
class RaceSkyState : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004afd64
	// SIZE 0x1fc
	class SkbTxtParser : public GolTxtParser {
	public:
		// .skb tokens
		enum {
			e_state = 0x27,
			e_duration = 0x28,
			e_topColor = 0x29,
			e_middleColor = 0x2a,
			e_bottomColor = 0x2b,
			e_states = 0x2c,
			e_initialState = 0x2d,
			e_heightOffset = 0x2e,
		};
	};

	// SIZE 0x10
	struct Entry {
		// SIZE 0x10
		struct Keyframe {
			LegoU32 m_durationMs;    // 0x00
			ColorRGBA m_topColor;    // 0x04
			ColorRGBA m_middleColor; // 0x08
			ColorRGBA m_bottomColor; // 0x0c
		};

		LegoU32 m_elapsedMs;     // 0x00
		LegoU32 m_keyframeIndex; // 0x04
		Keyframe* m_keyframes;   // 0x08
		LegoU32 m_keyframeCount; // 0x0c
	};

	// SIZE 0x01
	class ModelBuilder {
	public:
		// SIZE 0x38
		struct Params {
			enum {
				c_vertexColored = 1,
				c_vertexLit = 2,
			};

			GolD3DRenderDevice* m_renderer;           // 0x00
			GolModelBase* m_model;                    // 0x04
			GolVec3 m_origin;                         // 0x08
			LegoFloat m_radius;                       // 0x14
			LegoU32 m_segmentCount;                   // 0x18
			LegoU32 m_hemisphere;                     // 0x1c
			LegoU32 m_hasTopCap;                      // 0x20
			LegoU32 m_hasBottomCap;                   // 0x24
			LegoU32 m_reverseWinding;                 // 0x28
			LegoU32 m_useTextureSeam;                 // 0x2c
			LegoU16 m_vertexType;                     // 0x30
			undefined2 m_unk0x32;                     // 0x32
			GdbModelIndexArray* m_absoluteIndexArray; // 0x34
		};

		void Build(Params* p_params);
		void BuildSphere(Params* p_params);
		void BuildSeamedSphere(Params* p_params);
	};

	RaceSkyState();
	~RaceSkyState() override;
	void Clear() override;
	void Load(
		GolD3DRenderDevice* p_renderer,
		GolExport* p_golExport,
		const LegoChar* p_skyName,
		const LegoChar* p_worldName,
		LegoBool32 p_binary
	);
	void Update(LegoU32 p_elapsedMs);
	void SetPosition(GolVec3* p_position);
	void Draw(GolD3DRenderDevice* p_renderer);
	void StartTransition(const LegoChar* p_name, LegoU32 p_durationMs);

	// SYNTHETIC: LEGORACERS 0x0041c490
	// RaceSkyState::`scalar deleting destructor'

public:
	friend class RaceEventTable;

	enum {
		c_hideDome = 1 << 0,
		c_hideSkyWorld = 1 << 1,
	};

	void Reset();
	void EvaluateColors(Entry* p_entry, ColorRGBA* p_topColor, ColorRGBA* p_middleColor, ColorRGBA* p_bottomColor);
	void LerpColor(const ColorRGBA* p_from, const ColorRGBA* p_to, ColorRGBA* p_result, LegoFloat p_amount);
	void ApplyColors(const ColorRGBA* p_topColor, const ColorRGBA* p_middleColor, const ColorRGBA* p_bottomColor);

	GolModelEntity m_domeEntity;      // 0x0c
	GolWorldDatabase* m_skyWorld;     // 0x9c
	GolModelBase* m_domeModel;        // 0xa0
	GolExport* m_golExport;           // 0xa4
	Entry* m_entries;                 // 0xa8
	LegoFloat m_heightOffset;         // 0xac
	LegoU32 m_count;                  // 0xb0
	LegoU32 m_previousStateIndex;     // 0xb4
	LegoU32 m_stateIndex;             // 0xb8
	LegoU32 m_transitionMs;           // 0xbc
	LegoU32 m_transitionElapsedMs;    // 0xc0
	LegoU8 m_hideFlags;               // 0xc4
	ModelBuilder m_modelBuilder;      // 0xc5
	undefined m_unk0xc6[0xc8 - 0xc6]; // 0xc6
};

#endif // RACESKY_H
