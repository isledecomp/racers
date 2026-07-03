#ifndef CUTSCENEDEFINITION_H
#define CUTSCENEDEFINITION_H

#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "menu/screens/menugamescreen.h"
#include "render/golrenderdevice.h"
#include "render/rectangle.h"
#include "types.h"

class GolCamera;
class CutsceneEventSink;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolWorldEntity;
class MabMaterialAnimation;
class MabMaterialTrack;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004af38c
// SIZE 0x2c
class CutsceneDefinition : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004af398
	// SIZE 0x1fc
	class CdbTxtParser : public GolTxtParser {
	public:
		enum {
			e_frames = 0x27,
			e_worlds = 0x28,
		};
	};

	enum ParserToken {
		c_tokenCameraBlock = 0x29,
		c_tokenCameraName = 0x2a,
		c_tokenStartFrame = 0x2b,
		c_tokenDuration = 0x2c,
		c_tokenAnimationSequence = 0x2d,
		c_tokenModelBlock = 0x2e,
		c_tokenStaticModelName = 0x2f,
		c_tokenJointedModelName = 0x30,
		c_tokenBspModelName = 0x31,
		c_tokenIndexedModelRef = 0x32,
		c_tokenLocation = 0x33,
		c_tokenOrientation = 0x34,
		c_tokenAmbientLightBlock = 0x35,
		c_tokenMaterialAnimationRefs = 0x36,
		c_tokenTransformBlock = 0x37,
		c_tokenLightColor = 0x38,
		c_tokenLightDirection = 0x39,
		c_tokenDirectionalLightBlock = 0x3a,
		c_tokenSpeed = 0x3b,
		c_tokenBlinkTiming = 0x3c,
	};

	// SIZE 0xb8
	class Frame {
	public:
		enum Flags {
			c_flagPlaying = 1 << 0,
			c_flagLoop = 1 << 1,
			c_flagComplete = 1 << 2,
			c_flagLooped = 1 << 3,
			c_flagHasRect = 1 << 4
		};

		// VTABLE: LEGORACERS 0x004af33c
		// SIZE 0x20
		class Event {
		public:
			Event();
			virtual ~Event();                                               // vtable+0x00
			virtual void Update(undefined4 p_elapsedMs);                    // vtable+0x04
			virtual void Draw(GolD3DRenderDevice* p_renderer);              // vtable+0x08
			virtual void DrawTransparent(GolD3DRenderDevice* p_renderer);   // vtable+0x0c
			virtual void Begin(Frame* p_frame, CutsceneEventSink* p_event); // vtable+0x10
			virtual void End(Frame* p_frame, CutsceneEventSink* p_event);   // vtable+0x14

			void Reset();

			// SYNTHETIC: LEGORACERS 0x00405540
			// CutsceneDefinition::Frame::Event::`scalar deleting destructor'

			GolName m_name;       // 0x04
			LegoU32 m_startFrame; // 0x0c
			LegoU32 m_endFrame;   // 0x10
			LegoU32 m_active;     // 0x14
			Event* m_prev;        // 0x18
			Event* m_next;        // 0x1c
		};

		// VTABLE: LEGORACERS 0x004af308
		// SIZE 0x68
		class ModelEvent : public Event {
		public:
			enum ModelRefType {
				c_modelRefNone = 0,
				c_modelRefStaticModel = 1,
				c_modelRefJointedModel = 2,
				c_modelRefBspModel = 3,
				c_modelRefIndexedModel = 4,
			};

			// SIZE 0x08
			struct ModelIndexRef {
				LegoU32 m_resourceIndex; // 0x00
				LegoU32 m_modelIndex;    // 0x04
			};

			// Tagged by m_modelRefType: name refs use m_name, indexed refs use m_indexedRef.
			// SIZE 0x08
			union ModelRef {
				GolName m_name;             // 0x00
				ModelIndexRef m_indexedRef; // 0x00
			};

			// SIZE 0x1c
			struct Animation {
				MabMaterialAnimation* m_materialAnimation; // 0x00
				MabMaterialTrack* m_item;                  // 0x04
				LegoU32 m_resourceIndex;                   // 0x08
				LegoU32 m_animationIndex;                  // 0x0c
				LegoU32 m_itemIndex;                       // 0x10
				LegoU32 m_startParam0x14;                  // 0x14
				LegoU32 m_materialTableIndex;              // 0x18
			};

			ModelEvent();
			~ModelEvent() override;                                          // vtable+0x00
			void Update(undefined4 p_elapsedMs) override;                    // vtable+0x04
			void Draw(GolD3DRenderDevice* p_renderer) override;              // vtable+0x08
			void DrawTransparent(GolD3DRenderDevice* p_renderer) override;   // vtable+0x0c
			void Begin(Frame* p_frame, CutsceneEventSink* p_event) override; // vtable+0x10
			void End(Frame* p_frame, CutsceneEventSink* p_event) override;   // vtable+0x14

			LegoU32 Reset();
			LegoU32 Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser);
			void ResolveEntity();
			void Destroy();
			GolWorldEntity* GetEntity() const { return m_entity; }
			ModelRefType GetModelRefType() const { return m_modelRefType; }
			void SetEntity(GolWorldEntity* p_entity) { m_entity = p_entity; }
			LegoU32 GetAnimationCount() const { return m_animationCount; }
			Animation* GetAnimation(LegoU32 p_index) const { return &m_animations[p_index]; }

			// SYNTHETIC: LEGORACERS 0x00405df0
			// CutsceneDefinition::Frame::ModelEvent::`vector deleting destructor'

		private:
			ModelRefType m_modelRefType;      // 0x20
			GolWorldEntity* m_entity;         // 0x24
			CutsceneDefinition* m_definition; // 0x28
			ModelRef m_modelRef;              // 0x2c
			GolVec3 m_location;               // 0x34
			GolVec3 m_direction;              // 0x40
			GolVec3 m_up;                     // 0x4c
			LegoS32 m_animationIndex;         // 0x58
			LegoU32 m_animationCount;         // 0x5c
			Animation* m_animations;          // 0x60
			LegoU32 m_transparent;            // 0x64
		};

		// VTABLE: LEGORACERS 0x004af320
		// SIZE 0x34
		class CameraEvent : public Event {
		public:
			CameraEvent();
			void Update(undefined4 p_elapsedMs) override;                    // vtable+0x04
			void Begin(Frame* p_frame, CutsceneEventSink* p_event) override; // vtable+0x10
			void End(Frame* p_frame, CutsceneEventSink* p_event) override;   // vtable+0x14

			LegoU32 Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser);
			GolCamera* GetCamera() const { return m_camera; }

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::CameraEvent::~CameraEvent

			// SYNTHETIC: LEGORACERS 0x00405cb0
			// CutsceneDefinition::Frame::CameraEvent::`vector deleting destructor'

		private:
			GolCamera* m_camera;              // 0x20
			GolName m_cameraName;             // 0x24
			CutsceneDefinition* m_definition; // 0x2c
			LegoS32 m_animationIndex;         // 0x30
		};

		// VTABLE: LEGORACERS 0x004af358
		// SIZE 0x38
		class AmbientLightEvent : public Event {
		public:
			AmbientLightEvent();
			void Update(undefined4 p_elapsedMs) override;                    // vtable+0x04
			void Begin(Frame* p_frame, CutsceneEventSink* p_event) override; // vtable+0x10
			void End(Frame* p_frame, CutsceneEventSink* p_event) override;   // vtable+0x14

			void Parse(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::AmbientLightEvent::~AmbientLightEvent

			// SYNTHETIC: LEGORACERS 0x00406060
			// CutsceneDefinition::Frame::AmbientLightEvent::`vector deleting destructor'

		private:
			GolRenderDevice::MaterialColor m_material; // 0x20
			LegoU32 m_blinkOnMs;                       // 0x24
			LegoU32 m_blinkOffMs;                      // 0x28
			LegoU32 m_blinkTimerMs;                    // 0x2c
			LegoU8 m_blinkFlags;                       // 0x30
			undefined m_unk0x31[0x34 - 0x31];          // 0x31
			Frame* m_frame;                            // 0x34
		};

		// VTABLE: LEGORACERS 0x004af370
		// SIZE 0x44
		class DirectionalLightEvent : public Event {
		public:
			DirectionalLightEvent();
			void Update(undefined4 p_elapsedMs) override;                    // vtable+0x04
			void Begin(Frame* p_frame, CutsceneEventSink* p_event) override; // vtable+0x10
			void End(Frame* p_frame, CutsceneEventSink* p_event) override;   // vtable+0x14

			LegoU32 Parse(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::DirectionalLightEvent::~DirectionalLightEvent

			// SYNTHETIC: LEGORACERS 0x004061e0
			// CutsceneDefinition::Frame::DirectionalLightEvent::`vector deleting destructor'

		private:
			GolRenderDevice::Light m_light;   // 0x20
			LegoU32 m_blinkOnMs;              // 0x30
			LegoU32 m_blinkOffMs;             // 0x34
			LegoU32 m_blinkTimerMs;           // 0x38
			LegoU8 m_blinkFlags;              // 0x3c
			undefined m_unk0x3d[0x40 - 0x3d]; // 0x3d
			Frame* m_frame;                   // 0x40
		};

		// VTABLE: LEGORACERS 0x004af410
		// SIZE 0x44
		class TransformEvent : public Event {
		public:
			TransformEvent();
			~TransformEvent() override;                                      // vtable+0x00
			void Begin(Frame* p_frame, CutsceneEventSink* p_event) override; // vtable+0x10
			void End(Frame* p_frame, CutsceneEventSink* p_event) override;   // vtable+0x14

			void Reset();
			LegoU32 Parse(GolFileParser* p_parser);
			const GolVec3& GetPosition() const { return m_position; }
			const GolVec3& GetDirection() const { return m_direction; }
			const GolVec3& GetUp() const { return m_up; }
			void Clear();

			// SYNTHETIC: LEGORACERS 0x00405f20
			// CutsceneDefinition::Frame::TransformEvent::`vector deleting destructor'

		private:
			GolVec3 m_position;  // 0x20
			GolVec3 m_direction; // 0x2c
			GolVec3 m_up;        // 0x38
		};

		Frame();
		~Frame();

		void Reset();
		void Parse(CutsceneDefinition* p_parent, GolFileParser* p_parser);
		void ParseCameraEvents(GolFileParser* p_parser);
		void ParseModelEvents(GolFileParser* p_parser);
		void ParseTransformEvents(GolFileParser* p_parser);
		void ParseAmbientLightEvents(GolFileParser* p_parser);
		void ParseDirectionalLightEvents(GolFileParser* p_parser);
		void Destroy();
		void Play();
		void Rewind();
		void Stop();
		void Update(LegoS32 p_elapsedMs);
		void SetViewportRect(Rect* p_rect);
		void Draw(GolD3DRenderDevice* p_renderer, LegoU32 p_lensIndex);
		void UpdateActiveEvents(undefined4 p_elapsedMs);
		LegoU32 ProcessEvents(LegoU32 p_startFrame, LegoU32 p_endFrame);
		void AddActiveEvent(Event* p_event);
		void RemoveActiveEvent(Event* p_event);
		LegoU32 PushCamera(GolCamera* p_lens);
		void RemoveCamera(GolCamera* p_lens);
		void SetAmbientMaterial(const GolRenderDevice::MaterialColor* p_material);
		void ClearAmbientMaterial(const GolRenderDevice::MaterialColor* p_material);
		LegoU32 AddLight(const GolRenderDevice::Light* p_light);
		void RemoveLight(const GolRenderDevice::Light* p_light);
		void ResolveEntities();
		GolCamera* GetActiveCamera();

		LegoU32 GetFlags() const { return m_flags; }
		LegoU32 GetCurrentFrame() const { return m_currentFrame; }
		LegoU32 GetPlaybackRate() const { return m_playbackRate; }
		LegoU32 GetModelEventCount() const { return m_modelEventCount; }
		ModelEvent* GetModel(LegoU32 p_index) const { return &m_modelEvents[p_index]; }
		ModelEvent* GetModels() const { return m_modelEvents; }
		void SetFlags(LegoU32 p_flags) { m_flags |= p_flags; }

	private:
		CutsceneDefinition* m_definition;                        // 0x00
		LegoU32 m_cameraEventCount;                              // 0x04
		CameraEvent* m_cameraEvents;                             // 0x08
		LegoU32 m_modelEventCount;                               // 0x0c
		ModelEvent* m_modelEvents;                               // 0x10
		LegoU32 m_transformEventCount;                           // 0x14
		TransformEvent* m_transformEvents;                       // 0x18
		LegoU32 m_ambientEventCount;                             // 0x1c
		AmbientLightEvent* m_ambientEvents;                      // 0x20
		LegoU32 m_directionalEventCount;                         // 0x24
		DirectionalLightEvent* m_directionalEvents;              // 0x28
		LegoU32 m_eventCount;                                    // 0x2c
		Event** m_eventsByStart;                                 // 0x30
		LegoU32 m_startCursor;                                   // 0x34
		Event** m_eventsByEnd;                                   // 0x38
		LegoU32 m_endCursor;                                     // 0x3c
		Event* m_activeEvents;                                   // 0x40
		LegoU32 m_flags;                                         // 0x44
		LegoU32 m_currentFrame;                                  // 0x48
		LegoU32 m_frameCount;                                    // 0x4c
		LegoU32 m_elapsedScaled;                                 // 0x50
		LegoU32 m_frameRate;                                     // 0x54
		LegoU32 m_playbackRate;                                  // 0x58
		LegoU32 m_cameraCount;                                   // 0x5c
		GolCamera* m_cameraStack[8];                             // 0x60
		const GolRenderDevice::MaterialColor* m_ambientMaterial; // 0x80
		LegoU32 m_lightCount;                                    // 0x84
		const GolRenderDevice::Light* m_lights[7];               // 0x88
		LegoFloat m_tickAccumulator;                             // 0xa4
		Rect m_viewportRect;                                     // 0xa8
	};

	CutsceneDefinition();
	~CutsceneDefinition() override; // vtable+0x00
	void Clear() override;          // vtable+0x08

	void Reset();
	void Load(GolExport* p_golExport, GolD3DRenderDevice* p_renderer, const LegoChar* p_fileName, LegoBool32 p_binary);
	void ParseWorldNames(GolFileParser* p_parser);
	void LoadWorlds(LegoBool32 p_binary);
	void ParseFrames(GolFileParser* p_parser);
	GolCamera* FindCamera(const LegoChar* p_name);
	GolWorldEntity* FindModelEntity(const LegoChar* p_name);
	GolWorldEntity* FindJointedEntity(const LegoChar* p_name);
	GolWorldEntity* FindBspEntity(const LegoChar* p_name);
	GolWorldEntity* GetIndexedEntity(LegoU32 p_index, LegoU32 p_modelIndex);
	MabMaterialAnimation* GetMaterialAnimation(LegoU32 p_index, LegoU32 p_animationIndex);
	MabMaterialTrack* GetMaterialAnimationItem(LegoU32 p_index, LegoU32 p_animationIndex, LegoU32 p_itemIndex);
	LegoU32 SetCameraAspectRatios(LegoFloat p_scale);

	void SetEventSink(CutsceneEventSink* p_eventSink) { m_eventSink = p_eventSink; }
	CutsceneEventSink* GetEventSink() const { return m_eventSink; }
	LegoU32 GetWorldDatabaseCount() const { return m_worldDatabaseCount; }
	GolWorldDatabase* GetWorldDatabase(LegoU32 p_index) const { return m_worldDatabases[p_index]; }
	LegoU32 GetFrameCount() const { return m_frameCount; }
	Frame* GetFrames() const { return m_frames; }

	// SYNTHETIC: LEGORACERS 0x004068f0
	// CutsceneDefinition::`scalar deleting destructor'

private:
	CutsceneEventSink* m_eventSink;      // 0x0c
	GolExport* m_golExport;              // 0x10
	GolD3DRenderDevice* m_renderer;      // 0x14
	LegoU32 m_worldDatabaseCount;        // 0x18
	GolWorldDatabase** m_worldDatabases; // 0x1c
	LegoChar* m_worldNames;              // 0x20
	LegoU32 m_frameCount;                // 0x24
	Frame* m_frames;                     // 0x28
};

#endif // CUTSCENEDEFINITION_H
