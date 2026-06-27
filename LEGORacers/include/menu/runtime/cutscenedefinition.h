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
class BluebellFog0x4;
class GolD3DRenderDevice;
class GolExport;
class GolFileParser;
class GolWorldEntity;
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004af38c
// SIZE 0x2c
class CutsceneDefinition : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004af398
	// SIZE 0x1fc
	class CdbTxtParser : public GolTxtParser {};

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
			virtual ~Event();                                                 // vtable+0x00
			virtual void VTable0x04(undefined4 p_elapsedMs);                  // vtable+0x04
			virtual void VTable0x08(GolD3DRenderDevice* p_renderer);          // vtable+0x08
			virtual void VTable0x0c(GolD3DRenderDevice* p_renderer);          // vtable+0x0c
			virtual void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event); // vtable+0x10
			virtual void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event); // vtable+0x14

			void Reset();

			// SYNTHETIC: LEGORACERS 0x00405540
			// CutsceneDefinition::Frame::Event::`scalar deleting destructor'

			GolName m_name;    // 0x04
			LegoU32 m_unk0x0c; // 0x0c
			LegoU32 m_unk0x10; // 0x10
			LegoU32 m_unk0x14; // 0x14
			Event* m_unk0x18;  // 0x18
			Event* m_unk0x1c;  // 0x1c
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
				MabMaterialAnimation0x14* m_unk0x00;     // 0x00
				MabMaterialAnimationItem0x18* m_unk0x04; // 0x04
				LegoU32 m_unk0x08;                       // 0x08
				LegoU32 m_unk0x0c;                       // 0x0c
				LegoU32 m_unk0x10;                       // 0x10
				LegoU32 m_unk0x14;                       // 0x14
				LegoU32 m_unk0x18;                       // 0x18
			};

			ModelEvent();
			~ModelEvent() override;                                            // vtable+0x00
			void VTable0x04(undefined4 p_elapsedMs) override;                  // vtable+0x04
			void VTable0x08(GolD3DRenderDevice* p_renderer) override;          // vtable+0x08
			void VTable0x0c(GolD3DRenderDevice* p_renderer) override;          // vtable+0x0c
			void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 Reset();
			LegoU32 FUN_00404a10(CutsceneDefinition* p_parent, GolFileParser* p_parser);
			void FUN_00404c90();
			void FUN_00404e80();
			GolWorldEntity* GetEntity() const { return m_unk0x24; }
			void SetEntity(GolWorldEntity* p_entity) { m_unk0x24 = p_entity; }
			LegoU32 GetAnimationCount() const { return m_unk0x5c; }
			Animation* GetAnimation(LegoU32 p_index) const { return &m_unk0x60[p_index]; }

			// SYNTHETIC: LEGORACERS 0x00405df0
			// CutsceneDefinition::Frame::ModelEvent::`vector deleting destructor'

		private:
			ModelRefType m_modelRefType;   // 0x20
			GolWorldEntity* m_unk0x24;     // 0x24
			CutsceneDefinition* m_unk0x28; // 0x28
			ModelRef m_unk0x2c;            // 0x2c
			GolVec3 m_unk0x34;             // 0x34
			GolVec3 m_unk0x40;             // 0x40
			GolVec3 m_unk0x4c;             // 0x4c
			LegoS32 m_unk0x58;             // 0x58
			LegoU32 m_unk0x5c;             // 0x5c
			Animation* m_unk0x60;          // 0x60
			LegoU32 m_unk0x64;             // 0x64
		};

		// VTABLE: LEGORACERS 0x004af320
		// SIZE 0x34
		class CameraEvent : public Event {
		public:
			CameraEvent();
			void VTable0x04(undefined4 p_elapsedMs) override;                  // vtable+0x04
			void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 FUN_004050a0(CutsceneDefinition* p_parent, GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::CameraEvent::~CameraEvent

			// SYNTHETIC: LEGORACERS 0x00405cb0
			// CutsceneDefinition::Frame::CameraEvent::`vector deleting destructor'

		private:
			GolCamera* m_unk0x20;          // 0x20
			GolName m_unk0x24;             // 0x24
			CutsceneDefinition* m_unk0x2c; // 0x2c
			LegoS32 m_unk0x30;             // 0x30
		};

		// VTABLE: LEGORACERS 0x004af358
		// SIZE 0x38
		class AmbientLightEvent : public Event {
		public:
			AmbientLightEvent();
			void VTable0x04(undefined4 p_elapsedMs) override;                  // vtable+0x04
			void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			void FUN_00405630(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::AmbientLightEvent::~AmbientLightEvent

			// SYNTHETIC: LEGORACERS 0x00406060
			// CutsceneDefinition::Frame::AmbientLightEvent::`vector deleting destructor'

		private:
			GolRenderDevice::MaterialColor m_unk0x20; // 0x20
			LegoU32 m_unk0x24;                        // 0x24
			LegoU32 m_unk0x28;                        // 0x28
			LegoU32 m_unk0x2c;                        // 0x2c
			LegoU8 m_unk0x30;                         // 0x30
			undefined m_unk0x31[0x34 - 0x31];         // 0x31
			Frame* m_unk0x34;                         // 0x34
		};

		// VTABLE: LEGORACERS 0x004af370
		// SIZE 0x44
		class DirectionalLightEvent : public Event {
		public:
			DirectionalLightEvent();
			void VTable0x04(undefined4 p_elapsedMs) override;                  // vtable+0x04
			void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 FUN_00405280(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// CutsceneDefinition::Frame::DirectionalLightEvent::~DirectionalLightEvent

			// SYNTHETIC: LEGORACERS 0x004061e0
			// CutsceneDefinition::Frame::DirectionalLightEvent::`vector deleting destructor'

		private:
			GolRenderDevice::Light m_unk0x20; // 0x20
			LegoU32 m_unk0x30;                // 0x30
			LegoU32 m_unk0x34;                // 0x34
			LegoU32 m_unk0x38;                // 0x38
			LegoU8 m_unk0x3c;                 // 0x3c
			undefined m_unk0x3d[0x40 - 0x3d]; // 0x3d
			Frame* m_unk0x40;                 // 0x40
		};

		// VTABLE: LEGORACERS 0x004af410
		// SIZE 0x44
		class TransformEvent : public Event {
		public:
			TransformEvent();
			~TransformEvent() override;                                        // vtable+0x00
			void VTable0x10(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			void Reset();
			LegoU32 FUN_00407090(GolFileParser* p_parser);
			void FUN_004071a0();

			// SYNTHETIC: LEGORACERS 0x00405f20
			// CutsceneDefinition::Frame::TransformEvent::`vector deleting destructor'

		private:
			GolVec3 m_unk0x20; // 0x20
			GolVec3 m_unk0x2c; // 0x2c
			GolVec3 m_unk0x38; // 0x38
		};

		Frame();
		~Frame();

		void Reset();
		void FUN_00405950(CutsceneDefinition* p_parent, GolFileParser* p_parser);
		void FUN_00405bd0(GolFileParser* p_parser);
		void FUN_00405d10(GolFileParser* p_parser);
		void FUN_00405e50(GolFileParser* p_parser);
		void FUN_00405f80(GolFileParser* p_parser);
		void FUN_00406110(GolFileParser* p_parser);
		void Destroy();
		void FUN_00406310();
		void FUN_00406330();
		void FUN_00406380();
		void FUN_00406390(LegoS32 p_elapsedMs);
		void FUN_00406490(Rect* p_rect);
		void FUN_004064c0(GolD3DRenderDevice* p_renderer, LegoU32 p_lensIndex);
		void FUN_004065a0(undefined4 p_unk0x04);
		LegoU32 FUN_004065d0(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
		void FUN_00406680(Event* p_event);
		void FUN_004066b0(Event* p_event);
		LegoU32 FUN_004066d0(GolCamera* p_lens);
		void FUN_00406710(GolCamera* p_lens);
		void FUN_00406760(const GolRenderDevice::MaterialColor* p_material);
		void FUN_00406770(const GolRenderDevice::MaterialColor* p_material);
		LegoU32 FUN_00406790(const GolRenderDevice::Light* p_light);
		void FUN_004067f0(const GolRenderDevice::Light* p_light);
		void FUN_00406860();
		GolCamera* FUN_00406890();

		LegoU32 GetUnk0x44() const { return m_unk0x44; }
		LegoU32 GetUnk0x48() const { return m_unk0x48; }
		LegoU32 GetUnk0x58() const { return m_unk0x58; }
		LegoU32 GetModelCount() const { return m_unk0x0c; }
		ModelEvent* GetModel(LegoU32 p_index) const { return &m_unk0x10[p_index]; }
		ModelEvent* GetModels() const { return m_unk0x10; }
		void SetFlags(LegoU32 p_flags) { m_unk0x44 |= p_flags; }

	private:
		CutsceneDefinition* m_unk0x00;                   // 0x00
		LegoU32 m_unk0x04;                               // 0x04
		CameraEvent* m_unk0x08;                          // 0x08
		LegoU32 m_unk0x0c;                               // 0x0c
		ModelEvent* m_unk0x10;                           // 0x10
		LegoU32 m_unk0x14;                               // 0x14
		TransformEvent* m_unk0x18;                       // 0x18
		LegoU32 m_unk0x1c;                               // 0x1c
		AmbientLightEvent* m_unk0x20;                    // 0x20
		LegoU32 m_unk0x24;                               // 0x24
		DirectionalLightEvent* m_unk0x28;                // 0x28
		LegoU32 m_unk0x2c;                               // 0x2c
		Event** m_unk0x30;                               // 0x30
		LegoU32 m_unk0x34;                               // 0x34
		Event** m_unk0x38;                               // 0x38
		LegoU32 m_unk0x3c;                               // 0x3c
		Event* m_unk0x40;                                // 0x40
		LegoU32 m_unk0x44;                               // 0x44
		LegoU32 m_unk0x48;                               // 0x48
		LegoU32 m_unk0x4c;                               // 0x4c
		LegoU32 m_unk0x50;                               // 0x50
		LegoU32 m_unk0x54;                               // 0x54
		LegoU32 m_unk0x58;                               // 0x58
		LegoU32 m_unk0x5c;                               // 0x5c
		GolCamera* m_unk0x60[8];                         // 0x60
		const GolRenderDevice::MaterialColor* m_unk0x80; // 0x80
		LegoU32 m_unk0x84;                               // 0x84
		const GolRenderDevice::Light* m_unk0x88[7];      // 0x88
		LegoFloat m_unk0xa4;                             // 0xa4
		Rect m_unk0xa8;                                  // 0xa8
	};

	CutsceneDefinition();
	~CutsceneDefinition() override; // vtable+0x00
	void Clear() override;          // vtable+0x08

	void Reset();
	void FUN_00406980(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);
	void FUN_00406b90(GolFileParser* p_parser);
	void FUN_00406c50(LegoBool32 p_binary);
	void FUN_00406cb0(GolFileParser* p_parser);
	GolCamera* FUN_00406de0(const LegoChar* p_name);
	GolWorldEntity* FUN_00406e30(const LegoChar* p_name);
	GolWorldEntity* FUN_00406e80(const LegoChar* p_name);
	GolWorldEntity* FUN_00406ed0(const LegoChar* p_name);
	GolWorldEntity* FUN_00406f20(LegoU32 p_index, LegoU32 p_modelIndex);
	MabMaterialAnimation0x14* FUN_00406f40(LegoU32 p_index, LegoU32 p_animationIndex);
	MabMaterialAnimationItem0x18* FUN_00406f60(LegoU32 p_index, LegoU32 p_animationIndex, LegoU32 p_itemIndex);
	LegoU32 FUN_00406f90(LegoFloat p_scale);

	void SetUnk0x0c(BluebellFog0x4* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }
	BluebellFog0x4* GetUnk0x0c() const { return m_unk0x0c; }
	LegoU32 GetWorldDatabaseCount() const { return m_unk0x18; }
	GolWorldDatabase* GetWorldDatabase(LegoU32 p_index) const { return m_unk0x1c[p_index]; }
	LegoU32 GetFrameCount() const { return m_frameCount; }
	Frame* GetFrames() const { return m_frames; }

	// SYNTHETIC: LEGORACERS 0x004068f0
	// CutsceneDefinition::`scalar deleting destructor'

private:
	BluebellFog0x4* m_unk0x0c;      // 0x0c
	GolExport* m_golExport;         // 0x10
	GolD3DRenderDevice* m_renderer; // 0x14
	LegoU32 m_unk0x18;              // 0x18
	GolWorldDatabase** m_unk0x1c;   // 0x1c
	LegoChar* m_unk0x20;            // 0x20
	LegoU32 m_frameCount;           // 0x24
	Frame* m_frames;                // 0x28
};

#endif // CUTSCENEDEFINITION_H
