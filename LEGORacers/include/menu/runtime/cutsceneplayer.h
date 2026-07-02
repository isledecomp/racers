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
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class GolAnimatedEntity;
class CutsceneParticle;
class GolRenderDevice;
class UtopianPan0xa4;
class CutsceneDefinition;
class SoundManager;
class SoundGroup;
class SoundInstance;
class StreamingSoundInstance;
class MenuAnimationList;
class GolCamera;
class AwakeKite0x20;
class DuskwindBananaRelic0x24;
struct Rect;

// VTABLE: LEGORACERS 0x004b4954
// SIZE 0x14
class CutsceneEvent {
public:
	CutsceneEvent();
	virtual ~CutsceneEvent();                                             // vtable+0x00
	virtual void StartOnJointed(GolWorldEntity* p_arg);                   // vtable+0x04
	virtual void StartOnModel(GolWorldEntity* p_arg);                     // vtable+0x08
	virtual void StartOnBsp(GolWorldEntity* p_arg);                       // vtable+0x0c
	virtual void StartAt(const GolVec3*, const GolVec3*, const GolVec3*); // vtable+0x10
	virtual void Start();                                                 // vtable+0x14
	virtual void Stop();                                                  // vtable+0x18

	void Reset();
	void GetJointPosition(undefined4 p_param1, GolVec3* p_param2);
	void GetJointAxes(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void ParseCommonToken(GolFileParser* p_parser, CutscenePlayer* p_owner, GolFileParser::ParserTokenType p_token);
	void SetDisabled(LegoBool32 p_disabled) { m_disabled = p_disabled; }

	// SYNTHETIC: LEGORACERS 0x0049fd90
	// CutsceneEvent::`scalar deleting destructor'

protected:
	GolWorldEntity* m_parsedEntity;      // 0x04
	GolWorldEntity* m_entity;            // 0x08
	GolAnimatedEntity* m_animatedEntity; // 0x0c
	undefined4 m_disabled;               // 0x10
};

// SIZE 0x2c
struct CutsceneCameraTargetView {
	undefined m_unk0x00[0x28]; // 0x00
	GolWorldEntity* m_entity;  // 0x28
};

// SIZE 0x24
struct CutsceneCameraEventView {
	undefined m_unk0x00[0x20];          // 0x00
	CutsceneCameraTargetView* m_target; // 0x20
};

// SIZE 0x28
struct CutsceneModelEventView {
	undefined m_unk0x00[0x20]; // 0x00
	undefined4 m_modelType;    // 0x20
	GolWorldEntity* m_entity;  // 0x24
};

// SIZE 0x44
struct CutsceneTransformEventView {
	undefined m_unk0x00[0x20]; // 0x00
	GolVec3 m_position;        // 0x20
	GolVec3 m_direction;       // 0x2c
	GolVec3 m_up;              // 0x38
};

// SIZE 0x0c
class CutsceneEventLink {
public:
	CutsceneEventLink();

	void Bind(undefined4 p_unk0x04, CutsceneEvent* p_event);
	void Fire();
	void Fire(CutsceneCameraEventView* p_payload);
	void Fire(CutsceneModelEventView* p_payload);
	void Fire(CutsceneTransformEventView* p_payload);
	void Fire(void*);

	CutsceneEventLink* GetNext() const { return m_next; }
	void SetNext(CutsceneEventLink* p_next) { m_next = p_next; }

private:
	undefined4 m_isStart;      // 0x00
	CutsceneEvent* m_event;    // 0x04
	CutsceneEventLink* m_next; // 0x08
};

// VTABLE: LEGORACERS 0x004b4abc
// SIZE 0x30
class CutsceneSoundEvent : public CutsceneEvent {
public:
	CutsceneSoundEvent();

	void Start() override; // vtable+0x14
	void Stop() override;  // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	LegoBool32 ParseToken(GolFileParser* p_parser, CutscenePlayer* p_owner, GolFileParser::ParserTokenType p_token);
	void FUN_004a4050();
	void FUN_004a40f0();

	// SYNTHETIC: LEGORACERS 0x004a1d60
	// CutsceneSoundEvent::`vector deleting destructor'

protected:
	SoundGroup* m_unk0x14;    // 0x14
	SoundInstance* m_unk0x18; // 0x18
	LegoFloat m_unk0x1c;      // 0x1c
	LegoU32 m_unk0x20;        // 0x20
	LegoFloat m_unk0x24;      // 0x24
	LegoFloat m_unk0x28;      // 0x28
	LegoU16 m_unk0x2c;        // 0x2c
	LegoU16 m_unk0x2e;        // 0x2e
};

// VTABLE: LEGORACERS 0x004b4b34
// SIZE 0x48
class CutsceneMoveEvent : public CutsceneEvent {
public:
	CutsceneMoveEvent();

	void Start() override;                             // vtable+0x14
	void Stop() override;                              // vtable+0x18
	void StartOnModel(GolWorldEntity* p_arg) override; // vtable+0x08

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void FUN_004a4d10(LegoFloat p_elapsedSeconds);
	void FUN_004a4da0();

	// SYNTHETIC: LEGORACERS 0x004a1ba0
	// CutsceneMoveEvent::`vector deleting destructor'

private:
	LegoBool32 m_active;      // 0x14
	LegoS32 m_baseX;          // 0x18
	LegoS32 m_baseY;          // 0x1c
	LegoS32 m_baseZ;          // 0x20
	LegoS32 m_offsetStartX;   // 0x24
	LegoS32 m_offsetStartY;   // 0x28
	LegoS32 m_offsetStartZ;   // 0x2c
	LegoFloat m_offsetX;      // 0x30
	LegoFloat m_offsetY;      // 0x34
	LegoFloat m_offsetZ;      // 0x38
	LegoFloat m_offsetDeltaX; // 0x3c
	LegoFloat m_offsetDeltaY; // 0x40
	LegoFloat m_offsetDeltaZ; // 0x44
};

struct CutsceneParticleRef {
public:
	enum {
		c_flagInUse = 1 << 0
	};

	// size unknown, confirmed to be at least 5

	CutsceneParticle* m_particle;
	LegoU8 m_flags;
};

// VTABLE: LEGORACERS 0x004b4a94
// SIZE 0x50
class CutsceneAnimationEvent : public CutsceneEvent {
public:
	CutsceneAnimationEvent();

	void StartOnJointed(GolWorldEntity* p_arg) override;                               // vtable+0x04
	void StartOnBsp(GolWorldEntity* p_arg) override;                                   // vtable+0x0c
	void StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void Start() override;                                                             // vtable+0x14
	void Stop() override;                                                              // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void FUN_004a3db0();
	void FUN_004a3df0(LegoU32 p_elapsedMs);

	// SYNTHETIC: LEGORACERS 0x004a1f20
	// CutsceneAnimationEvent::`vector deleting destructor'

private:
	CutsceneAnimation* m_unk0x14;   // 0x14
	CutsceneParticleRef* m_unk0x18; // 0x18
	GolName m_unk0x1c;              // 0x1c
	GolVec3 m_unk0x24;              // 0x24
	GolVec3 m_unk0x30;              // 0x30
	GolVec3 m_unk0x3c;              // 0x3c
	LegoU32 m_unk0x48;              // 0x48
	LegoU32 m_unk0x4c;              // 0x4c
};

// VTABLE: LEGORACERS 0x004b4ad8
// SIZE 0x50
class CutsceneStreamingSoundEvent : public CutsceneSoundEvent {
public:
	enum Flags {
		c_flagInUse = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit2 = 1 << 2,
		c_flagBit3 = 1 << 3,
	};

	CutsceneStreamingSoundEvent();

	void StartOnJointed(GolWorldEntity* p_arg) override;                               // vtable+0x04
	void StartOnBsp(GolWorldEntity* p_arg) override;                                   // vtable+0x0c
	void StartAt(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void Start() override;                                                             // vtable+0x14
	void Stop() override;                                                              // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner);
	void FUN_004a42a0();
	void FUN_004a43a0(const GolVec3* p_position);
	void FUN_004a44f0();

private:
	StreamingSoundInstance* m_unk0x30; // 0x30
	LegoFloat m_unk0x34;               // 0x34
	LegoFloat m_unk0x38;               // 0x38
	GolVec3 m_unk0x3c;                 // 0x3c
	LegoU32 m_unk0x48;                 // 0x48
	LegoU32 m_unk0x4c;                 // 0x4c
};

// VTABLE: LEGORACERS 0x004b4b18
// SIZE 0x2c
class CutsceneMenuAnimationEvent : public CutsceneEvent {
public:
	CutsceneMenuAnimationEvent();

	void Start() override; // vtable+0x14
	void Stop() override;  // vtable+0x18

	void Reset();
	void Parse(
		GolFileParser* p_parser,
		CutscenePlayer* p_owner,
		MenuAnimationList* p_animationList,
		GolD3DRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a22b0
	// CutsceneMenuAnimationEvent::`vector deleting destructor'

	// SYNTHETIC: LEGORACERS 0x004a20e0 FOLDED
	// CutsceneMenuAnimationEvent::~CutsceneMenuAnimationEvent

private:
	MenuAnimationList* m_unk0x14;        // 0x14
	DuskwindBananaRelic0x24* m_unk0x18;  // 0x18
	MenuAnimationList::Entry* m_unk0x1c; // 0x1c
	union {
		struct {
			LegoU8 m_unk0x20; // 0x20
			LegoU8 m_unk0x21; // 0x21
			LegoU8 m_unk0x22; // 0x22
			LegoU8 m_unk0x23; // 0x23
		};
		LegoU32 m_colorPacked; // 0x20
	};
	LegoU32 m_unk0x24;                // 0x24
	LegoU8 m_unk0x28;                 // 0x28
	undefined m_unk0x29[0x2c - 0x29]; // 0x29
};

// VTABLE: LEGORACERS 0x004b4a4c
// SIZE 0x58
class CutsceneVisual : public CutsceneEvent {
public:
	CutsceneVisual();
	~CutsceneVisual() override; // vtable+0x00

	void Start() override;                                            // vtable+0x14
	void Stop() override;                                             // vtable+0x18
	virtual void VTable0x1c(LegoS32* p_width, LegoS32* p_height) = 0; // vtable+0x1c
	virtual void VTable0x20(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4,
		undefined4,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) = 0; // vtable+0x20

	void Reset();
	void Clear();
	void FUN_004a3550(LegoFloat p_elapsedSeconds);
	void FUN_004a35a0(GolD3DRenderDevice* p_renderer);
	void FUN_004a36e0(GolD3DRenderDevice* p_renderer, LegoFloat p_width, LegoFloat p_height);
	void ParseVisualToken(
		GolFileParser* p_parser,
		GolFileParser::ParserTokenType p_token,
		CutscenePlayer* p_owner,
		GolRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a32d0
	// CutsceneVisual::`scalar deleting destructor'

protected:
	enum Flags {
		c_flagPositionX = 1 << 2,
		c_flagPositionY = 1 << 3,
		c_flagWidth = 1 << 4,
		c_flagHeight = 1 << 5,
		c_flagActive = 1 << 6,
		c_flagLayoutPending = 1 << 7
	};

	LegoFloat m_unk0x14;        // 0x14
	LegoFloat m_unk0x18;        // 0x18
	LegoFloat m_unk0x1c;        // 0x1c
	LegoFloat m_unk0x20;        // 0x20
	LegoFloat m_unk0x24;        // 0x24
	LegoFloat m_unk0x28;        // 0x28
	LegoFloat m_unk0x2c;        // 0x2c
	LegoFloat m_unk0x30;        // 0x30
	LegoFloat m_unk0x34;        // 0x34
	LegoFloat m_unk0x38;        // 0x38
	LegoFloat m_unk0x3c;        // 0x3c
	LegoFloat m_unk0x40;        // 0x40
	LegoU32 m_flags;            // 0x44
	GolName m_fontName;         // 0x48
	LegoU32 m_stringTableIndex; // 0x50
	union {
		ColorRGBA m_color;     // 0x54
		LegoU32 m_colorPacked; // 0x54
	};
};

// VTABLE: LEGORACERS 0x004b4a70
// SIZE 0x64
class CutsceneImageVisual : public CutsceneVisual {
public:
	CutsceneImageVisual();
	~CutsceneImageVisual() override; // vtable+0x00

	void VTable0x1c(LegoS32* p_width, LegoS32* p_height) override; // vtable+0x1c
	void VTable0x20(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4 p_width,
		undefined4 p_height,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) override; // vtable+0x20

	void Reset();
	void Clear();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer);
	void FUN_004a3910(GolD3DRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2690
	// CutsceneImageVisual::`vector deleting destructor'

private:
	UtopianPan0xa4* m_unk0x58; // 0x58
	GolName m_unk0x5c;         // 0x5c
};

// VTABLE: LEGORACERS 0x004b4af4
// SIZE 0x70
class CutsceneTextVisual : public CutsceneVisual {
public:
	CutsceneTextVisual();
	~CutsceneTextVisual() override; // vtable+0x00

	void VTable0x1c(LegoS32* p_width, LegoS32* p_height) override; // vtable+0x1c
	void VTable0x20(
		GolRenderDevice* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4,
		undefined4,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) override; // vtable+0x20

	void Reset();
	void Clear();
	void Parse(GolFileParser* p_parser, CutscenePlayer* p_owner, GolRenderDevice* p_renderer);
	void RefreshString(CutscenePlayer* p_owner, GolRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2480
	// CutsceneTextVisual::`vector deleting destructor'

private:
	GolString m_string;    // 0x58
	LegoChar* m_rawString; // 0x64
	GolFont* m_font;       // 0x68
	LegoU32 m_stringIndex; // 0x6c
};

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
			MabMaterialAnimation0x14* p_materialAnimation,
			GolD3DRenderDevice* p_renderer,
			GolFileParser* p_parser,
			CutsceneAnimation* p_param4
		);
		void GetVectorAt(GolVec3* p_vec, int p_index);
		void GetOrigin(GolVec3* p_vec) const;

		LegoU32 GetUnk0x04() { return m_unk0x04; }
		LegoS32 GetUnk0x14() { return m_unk0x14; }
		LegoU8 GetUnk0x18() { return m_unk0x18; }
		LegoS32 GetUnk0x30() { return m_unk0x30; }
		LegoS32 GetUnk0x34() { return m_unk0x34; }
		LegoU8 GetPriority() const { return m_unk0x19; }
		LegoBool32 IsOneShot() const { return m_unk0x34 == -1; }
		LegoFloat GetUnk0x1c() const { return m_unk0x1c; }
		LegoFloat GetUnk0x20() const { return m_unk0x20; }
		LegoFloat GetUnk0x24() const { return m_unk0x24; }
		LegoFloat GetUnk0x28() const { return m_unk0x28; }
		LegoFloat GetUnk0x2c() const { return m_unk0x2c; }
		MabMaterialAnimationItem0x18* GetMaterialAnimationItem() const { return m_unk0x38; }
		MabMaterialAnimation0x14* GetMaterialAnimation() const { return m_materialAnimation; }
		DuskwindBananaRelic0x24* GetMaterial() const { return m_unk0x40; }

	private:
		GolVec3* m_unk0x00;                            // 0x00
		LegoU32 m_unk0x04;                             // 0x04
		LegoFloat m_unk0x08;                           // 0x08
		LegoFloat m_unk0x0c;                           // 0x0c
		LegoFloat m_unk0x10;                           // 0x10
		LegoS32 m_unk0x14;                             // 0x14
		LegoU8 m_unk0x18;                              // 0x18
		LegoU8 m_unk0x19;                              // 0x19
		LegoFloat m_unk0x1c;                           // 0x1c
		LegoFloat m_unk0x20;                           // 0x20
		LegoFloat m_unk0x24;                           // 0x24
		LegoFloat m_unk0x28;                           // 0x28
		LegoFloat m_unk0x2c;                           // 0x2c
		LegoS32 m_unk0x30;                             // 0x30
		LegoS32 m_unk0x34;                             // 0x34
		MabMaterialAnimationItem0x18* m_unk0x38;       // 0x38
		MabMaterialAnimation0x14* m_materialAnimation; // 0x3c
		DuskwindBananaRelic0x24* m_unk0x40;            // 0x40
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
		MabMaterialAnimation0x14* p_materialAnimation,
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

// VTABLE: LEGORACERS 0x004b4970
// SIZE 0x228
class CutscenePlayer : public CutsceneEventSink {
public:
	// VTABLE: LEGORACERS 0x004b49d4
	// SIZE 0x1fc
	class CebTxtParser : public GolTxtParser {};

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
		CutsceneDefinition* p_unk0x10,
		const LegoChar* p_fileName,
		undefined4 p_binary
	);
	void ParseAnimationNames(GolFileParser* p_parser);
	void LoadAnimations(undefined4 p_binary);
	void ParseStringTableNames(GolFileParser* p_unk0x04);
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
		undefined4& p_unk0x08,
		CutsceneEventLink*& p_unk0x0c,
		GolNameTable& p_unk0x10
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
	GolExport* m_golExport;                         // 0x004
	GolD3DRenderDevice* m_renderer;                 // 0x008
	SoundManager* m_soundManager;                   // 0x00c
	CutsceneDefinition* m_definition;               // 0x010
	SoundNode m_listener;                           // 0x014
	MenuAnimationList* m_menuAnimations;            // 0x064
	LegoU32 m_animationCount;                       // 0x068
	CutsceneAnimation* m_animations;                // 0x06c
	MabMaterialAnimation0x14* m_materialAnimations; // 0x070
	LegoChar* m_animationNames;                     // 0x074
	LegoU32 m_stringTableCount;                     // 0x078
	GolStringTable* m_stringTables;                 // 0x07c
	LegoChar* m_stringTableNames;                   // 0x080
	LegoU32 m_soundGroupCount;                      // 0x084
	SoundGroup** m_soundGroups;                     // 0x088
	LegoChar* m_soundGroupNames;                    // 0x08c
	LegoU32 m_fontTableCount;                       // 0x090
	GolFontTable** m_fontTables;                    // 0x094
	LegoChar* m_fontTableNames;                     // 0x098
	LegoU32 m_imageListCount;                       // 0x09c
	AwakeKite0x20** m_imageLists;                   // 0x0a0
	LegoChar* m_imageListNames;                     // 0x0a4
	GolNameTable m_moveEventNames;                  // 0x0a8
	LegoU32 m_moveEventCount;                       // 0x0b4
	CutsceneMoveEvent* m_moveEvents;                // 0x0b8
	GolNameTable m_soundEventNames;                 // 0x0bc
	LegoU32 m_soundEventCount;                      // 0x0c8
	CutsceneSoundEvent* m_soundEvents;              // 0x0cc
	GolNameTable m_streamEventNames;                // 0x0d0
	LegoU32 m_streamEventCount;                     // 0x0dc
	CutsceneStreamingSoundEvent* m_streamEvents;    // 0x0e0
	GolNameTable m_animEventNames;                  // 0x0e4
	LegoU32 m_animEventCount;                       // 0x0f0
	CutsceneAnimationEvent* m_animEvents;           // 0x0f4
	GolNameTable m_menuAnimEventNames;              // 0x0f8
	undefined4 m_menuAnimEventCount;                // 0x104
	CutsceneMenuAnimationEvent* m_menuAnimEvents;   // 0x108
	GolNameTable m_textVisualNames;                 // 0x10c
	LegoU32 m_textVisualCount;                      // 0x118
	CutsceneTextVisual* m_textVisuals;              // 0x11c
	GolNameTable m_imageVisualNames;                // 0x120
	LegoU32 m_imageVisualCount;                     // 0x12c
	CutsceneImageVisual* m_imageVisuals;            // 0x130
	undefined4 m_eventStartedCount;                 // 0x134
	CutsceneEventLink* m_eventStartedLinks;         // 0x138
	GolNameTable m_eventStartedNames;               // 0x13c
	undefined4 m_eventEndedCount;                   // 0x148
	CutsceneEventLink* m_eventEndedLinks;           // 0x14c
	GolNameTable m_eventEndedNames;                 // 0x150
	undefined4 m_cameraStartedCount;                // 0x15c
	CutsceneEventLink* m_cameraStartedLinks;        // 0x160
	GolNameTable m_cameraStartedNames;              // 0x164
	undefined4 m_cameraEndedCount;                  // 0x170
	CutsceneEventLink* m_cameraEndedLinks;          // 0x174
	GolNameTable m_cameraEndedNames;                // 0x178
	undefined4 m_modelStartedCount;                 // 0x184
	CutsceneEventLink* m_modelStartedLinks;         // 0x188
	GolNameTable m_modelStartedNames;               // 0x18c
	undefined4 m_modelEndedCount;                   // 0x198
	CutsceneEventLink* m_modelEndedLinks;           // 0x19c
	GolNameTable m_modelEndedNames;                 // 0x1a0
	undefined4 m_transformStartedCount;             // 0x1ac
	CutsceneEventLink* m_transformStartedLinks;     // 0x1b0
	GolNameTable m_transformStartedNames;           // 0x1b4
	undefined4 m_transformEndedCount;               // 0x1c0
	CutsceneEventLink* m_transformEndedLinks;       // 0x1c4
	GolNameTable m_transformEndedNames;             // 0x1c8
	undefined4 m_ambientStartedCount;               // 0x1d4
	CutsceneEventLink* m_ambientStartedLinks;       // 0x1d8
	GolNameTable m_ambientStartedNames;             // 0x1dc
	undefined4 m_ambientEndedCount;                 // 0x1e8
	CutsceneEventLink* m_ambientEndedLinks;         // 0x1ec
	GolNameTable m_ambientEndedNames;               // 0x1f0
	undefined4 m_directionalStartedCount;           // 0x1fc
	CutsceneEventLink* m_directionalStartedLinks;   // 0x200
	GolNameTable m_directionalStartedNames;         // 0x204
	undefined4 m_directionalEndedCount;             // 0x210
	CutsceneEventLink* m_directionalEndedLinks;     // 0x214
	GolNameTable m_directionalEndedNames;           // 0x218
	GolStringTable* m_stringTable;                  // 0x224
};

#endif // CUTSCENEPLAYER_H
