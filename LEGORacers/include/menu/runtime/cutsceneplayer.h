#ifndef CUTSCENEPLAYER_H
#define CUTSCENEPLAYER_H

#include "audio/soundnode.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "goltxtparser.h"
#include "menu/menuanimationlist.h"
#include "menu/runtime/cutsceneanimation.h"
#include "menu/runtime/cutsceneanimationevent.h"
#include "menu/runtime/cutscenecolorevent.h"
#include "menu/runtime/cutsceneevent.h"
#include "menu/runtime/cutsceneeventlink.h"
#include "menu/runtime/cutsceneimagevisual.h"
#include "menu/runtime/cutscenemenuanimationevent.h"
#include "menu/runtime/cutsceneparticleref.h"
#include "menu/runtime/cutscenesoundevent.h"
#include "menu/runtime/cutscenestreamingsoundevent.h"
#include "menu/runtime/cutscenetextvisual.h"
#include "menu/runtime/cutscenevisual.h"
#include "surface/color.h"
#include "types.h"
#include "util/cutsceneeventsink.h"

class GolD3DRenderDevice;
class CutscenePlayer;
class CutsceneAnimation;
class GolExport;
class GolFont;
class GolFontTable;
class GolFileParser;
class GolWorldEntity;
class MabMaterialAnimation;
class MabMaterialTrack;
class GolAnimatedEntity;
class CutsceneParticle;
class GolRenderDevice;
class GolImage;
class CutsceneDefinition;
class SoundManager;
class SoundGroup;
class SoundInstance;
class StreamingSoundInstance;
class MenuAnimationList;
class GolCamera;
class GolImageDefinitionList;
class GolMaterial;
struct Rect;

// VTABLE: LEGORACERS 0x004b4970
// SIZE 0x228
class CutscenePlayer : public CutsceneEventSink {
public:
	// VTABLE: LEGORACERS 0x004b49d4
	// SIZE 0x1fc
	class CebTxtParser : public GolTxtParser {
	public:
		// .ceb section + trigger-channel tokens (event field tokens live in
		// the event classes)
		enum {
			e_animations = 0x27,
			e_stringTables = 0x28,
			e_fontTables = 0x29,
			e_imageLists = 0x2a,
			e_moveEvents = 0x2b,
			e_soundEvents = 0x2f,
			e_streamEvents = 0x36,
			e_animationEvents = 0x3c,
			e_textVisuals = 0x3f,
			e_imageVisuals = 0x4d,
			e_onEventStarted = 0x50,
			e_onEventEnded = 0x51,
			e_onCameraStarted = 0x52,
			e_onCameraEnded = 0x53,
			e_onModelStarted = 0x54,
			e_onModelEnded = 0x55,
			e_onTransformStarted = 0x56,
			e_onTransformEnded = 0x57,
			e_onAmbientStarted = 0x58,
			e_onAmbientEnded = 0x59,
			e_onDirectionalStarted = 0x5a,
			e_onDirectionalEnded = 0x5b,
			e_soundGroups = 0x5c,
			e_jointedEntityName = 0x5d,
			e_modelEntityName = 0x5e,
			e_bspEntityName = 0x5f,
			e_menuAnimationEvents = 0x60,
			e_startX = 0x43,
			e_startY = 0x44,
			e_centerX = 0x45,
			e_centerY = 0x46,
			e_startWidth = 0x47,
			e_startHeight = 0x48,
			e_rateX = 0x49,
			e_rateY = 0x4a,
			e_rateWidth = 0x4b,
			e_rateHeight = 0x4c,
			e_imageAttached = 0x4e,
			e_imageDetached = 0x4f,
			e_visualColor = 0x66,
			e_string = 0x40,
			e_text = 0x41,
			e_font = 0x42,
		};
	};

	CutscenePlayer();

	void OnEventStarted(void*, void*, void*) override;            // vtable+0x00
	void OnEventEnded(void*, void*, void*) override;              // vtable+0x04
	void OnCameraStarted(void*, void*, void*) override;           // vtable+0x08
	void OnCameraEnded(void*, void*, void*) override;             // vtable+0x0c
	void OnModelStarted(void*, void*, void*) override;            // vtable+0x10
	void OnModelEnded(void*, void*, void*) override;              // vtable+0x14
	void OnTransformStarted(void*, void*, void*) override;        // vtable+0x18
	void OnTransformEnded(void*, void*, void*) override;          // vtable+0x1c
	void OnAmbientLightStarted(void*, void*, void*) override;     // vtable+0x20
	void OnAmbientLightEnded(void*, void*, void*) override;       // vtable+0x24
	void OnDirectionalLightStarted(void*, void*, void*) override; // vtable+0x28
	void OnDirectionalLightEnded(void*, void*, void*) override;   // vtable+0x2c
	virtual ~CutscenePlayer();                                    // vtable+0x30

	void Reset();
	LegoBool32 HasFileWithSuffix(const LegoChar* p_fileName, const LegoChar* p_suffix);
	void Load(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		SoundManager* p_soundManager,
		CutsceneDefinition* p_definition,
		const LegoChar* p_fileName,
		undefined4 p_binary
	);
	void ParseAnimationNames(GolFileParser* p_parser);
	void LoadAnimations(undefined4 p_binary);
	void ParseStringTableNames(GolFileParser* p_parser);
	void LoadStringTables();
	void ParseSoundGroupNames(GolFileParser* p_parser);
	void LoadSoundGroups();
	void ParseFontTableNames(GolFileParser* p_parser);
	void LoadFontTables(undefined4 p_binary);
	void ParseImageListNames(GolFileParser* p_parser);
	void LoadImageLists(undefined4 p_binary);
	void ParseMoveEvents(GolFileParser* p_parser);
	void ParseSoundEvents(GolFileParser* p_parser);
	void ParseStreamEvents(GolFileParser* p_parser);
	void ParseAnimationEvents(GolFileParser* p_parser);
	void ParseMenuAnimationEvents(GolFileParser* p_parser);
	void ParseTextVisuals(GolFileParser* p_parser);
	void RefreshTextVisuals();
	void ParseImageVisuals(GolFileParser* p_parser);
	void LoadImageVisuals();
	void ParseTriggerChannel(
		GolFileParser* p_parser,
		LegoU32 p_token,
		undefined4& p_count,
		CutsceneEventLink*& p_links,
		GolNameTable& p_names
	);
	void Update(LegoU32 p_elapsedMs);
	void Draw(GolD3DRenderDevice* p_renderer);
	void UpdateListener(GolCamera* p_lens);
	void DrawTransparent(GolD3DRenderDevice* p_renderer);
	void DrawOverlay(GolD3DRenderDevice* p_renderer);
	void StopAll();
	GolStringTable* GetStringTableByIndex(LegoU32 p_index);

	LegoU32 GetTextVisualCount() const { return m_textVisualCount; }
	LegoU32 GetStringTableCount() const { return m_stringTableCount; }
	SoundManager* GetSoundManager() const { return m_soundManager; }
	void SetStringTable(GolStringTable* p_stringTable) { m_stringTable = p_stringTable; }
	LegoU32 GetAnimationCount() const { return m_animationCount; }
	CutsceneAnimation* GetAnimationByIndex(LegoU32 p_index) const { return &m_animations[p_index]; }
	LegoU32 GetSoundGroupCount() const { return m_soundGroupCount; }
	SoundGroup* GetSoundGroupByIndex(LegoU32 p_index) const { return m_soundGroups[p_index]; }
	GolWorldEntity* FindModelEntity(const LegoChar* p_name);
	GolWorldEntity* FindJointedEntity(const LegoChar* p_name);
	GolWorldEntity* FindBspEntity(const LegoChar* p_name);

	// SYNTHETIC: LEGORACERS 0x004a0390
	// CutscenePlayer::`scalar deleting destructor'

	void Clear();
	GolNameTable* GetTextVisuals() { return &m_textVisualNames; }

private:
	GolExport* m_golExport;                       // 0x004
	GolD3DRenderDevice* m_renderer;               // 0x008
	SoundManager* m_soundManager;                 // 0x00c
	CutsceneDefinition* m_definition;             // 0x010
	SoundNode m_listener;                         // 0x014
	MenuAnimationList* m_menuAnimations;          // 0x064
	LegoU32 m_animationCount;                     // 0x068
	CutsceneAnimation* m_animations;              // 0x06c
	MabMaterialAnimation* m_materialAnimations;   // 0x070
	LegoChar* m_animationNames;                   // 0x074
	LegoU32 m_stringTableCount;                   // 0x078
	GolStringTable* m_stringTables;               // 0x07c
	LegoChar* m_stringTableNames;                 // 0x080
	LegoU32 m_soundGroupCount;                    // 0x084
	SoundGroup** m_soundGroups;                   // 0x088
	LegoChar* m_soundGroupNames;                  // 0x08c
	LegoU32 m_fontTableCount;                     // 0x090
	GolFontTable** m_fontTables;                  // 0x094
	LegoChar* m_fontTableNames;                   // 0x098
	LegoU32 m_imageListCount;                     // 0x09c
	GolImageDefinitionList** m_imageLists;        // 0x0a0
	LegoChar* m_imageListNames;                   // 0x0a4
	GolNameTable m_moveEventNames;                // 0x0a8
	LegoU32 m_moveEventCount;                     // 0x0b4
	CutsceneColorEvent* m_moveEvents;             // 0x0b8
	GolNameTable m_soundEventNames;               // 0x0bc
	LegoU32 m_soundEventCount;                    // 0x0c8
	CutsceneSoundEvent* m_soundEvents;            // 0x0cc
	GolNameTable m_streamEventNames;              // 0x0d0
	LegoU32 m_streamEventCount;                   // 0x0dc
	CutsceneStreamingSoundEvent* m_streamEvents;  // 0x0e0
	GolNameTable m_animEventNames;                // 0x0e4
	LegoU32 m_animEventCount;                     // 0x0f0
	CutsceneAnimationEvent* m_animEvents;         // 0x0f4
	GolNameTable m_menuAnimEventNames;            // 0x0f8
	LegoU32 m_menuAnimEventCount;                 // 0x104
	CutsceneMenuAnimationEvent* m_menuAnimEvents; // 0x108
	GolNameTable m_textVisualNames;               // 0x10c
	LegoU32 m_textVisualCount;                    // 0x118
	CutsceneTextVisual* m_textVisuals;            // 0x11c
	GolNameTable m_imageVisualNames;              // 0x120
	LegoU32 m_imageVisualCount;                   // 0x12c
	CutsceneImageVisual* m_imageVisuals;          // 0x130
	LegoU32 m_eventStartedCount;                  // 0x134
	CutsceneEventLink* m_eventStartedLinks;       // 0x138
	GolNameTable m_eventStartedNames;             // 0x13c
	LegoU32 m_eventEndedCount;                    // 0x148
	CutsceneEventLink* m_eventEndedLinks;         // 0x14c
	GolNameTable m_eventEndedNames;               // 0x150
	LegoU32 m_cameraStartedCount;                 // 0x15c
	CutsceneEventLink* m_cameraStartedLinks;      // 0x160
	GolNameTable m_cameraStartedNames;            // 0x164
	LegoU32 m_cameraEndedCount;                   // 0x170
	CutsceneEventLink* m_cameraEndedLinks;        // 0x174
	GolNameTable m_cameraEndedNames;              // 0x178
	LegoU32 m_modelStartedCount;                  // 0x184
	CutsceneEventLink* m_modelStartedLinks;       // 0x188
	GolNameTable m_modelStartedNames;             // 0x18c
	LegoU32 m_modelEndedCount;                    // 0x198
	CutsceneEventLink* m_modelEndedLinks;         // 0x19c
	GolNameTable m_modelEndedNames;               // 0x1a0
	LegoU32 m_transformStartedCount;              // 0x1ac
	CutsceneEventLink* m_transformStartedLinks;   // 0x1b0
	GolNameTable m_transformStartedNames;         // 0x1b4
	LegoU32 m_transformEndedCount;                // 0x1c0
	CutsceneEventLink* m_transformEndedLinks;     // 0x1c4
	GolNameTable m_transformEndedNames;           // 0x1c8
	LegoU32 m_ambientStartedCount;                // 0x1d4
	CutsceneEventLink* m_ambientStartedLinks;     // 0x1d8
	GolNameTable m_ambientStartedNames;           // 0x1dc
	LegoU32 m_ambientEndedCount;                  // 0x1e8
	CutsceneEventLink* m_ambientEndedLinks;       // 0x1ec
	GolNameTable m_ambientEndedNames;             // 0x1f0
	LegoU32 m_directionalStartedCount;            // 0x1fc
	CutsceneEventLink* m_directionalStartedLinks; // 0x200
	GolNameTable m_directionalStartedNames;       // 0x204
	LegoU32 m_directionalEndedCount;              // 0x210
	CutsceneEventLink* m_directionalEndedLinks;   // 0x214
	GolNameTable m_directionalEndedNames;         // 0x218
	GolStringTable* m_stringTable;                // 0x224
};

#endif // CUTSCENEPLAYER_H
