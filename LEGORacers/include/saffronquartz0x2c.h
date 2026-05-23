#ifndef SAFFRONQUARTZ0X2C_H
#define SAFFRONQUARTZ0X2C_H

#include "decomp.h"
#include "golnametable.h"
#include "goltxtparser.h"
#include "imaginarytool0x368.h"
#include "rectangle.h"
#include "types.h"
#include "whitefalcon0x140.h"

class AmberLens0x344;
class BluebellFog0x4;
class BronzeFalcon0xc8770;
class FloatyBoat0x28;
class GolExport;
class GolFileParser;
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class ZoweeBlubberworth0xf0;

// VTABLE: LEGORACERS 0x004af38c
// SIZE 0x2c
class SaffronQuartz0x2c : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004af398
	// SIZE 0x1fc
	class CdbTxtParser : public GolTxtParser {};

	// SIZE 0xb8
	class Frame0xb8 {
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
		class Event0x20 {
		public:
			Event0x20();
			virtual ~Event0x20();                                                 // vtable+0x00
			virtual void VTable0x04(undefined4 p_elapsedMs);                      // vtable+0x04
			virtual void VTable0x08(BronzeFalcon0xc8770* p_renderer);             // vtable+0x08
			virtual void VTable0x0c(BronzeFalcon0xc8770* p_renderer);             // vtable+0x0c
			virtual void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event); // vtable+0x10
			virtual void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event); // vtable+0x14

			void Reset();

			// SYNTHETIC: LEGORACERS 0x00405540
			// SaffronQuartz0x2c::Frame0xb8::Event0x20::`scalar deleting destructor'

			GolName m_name;       // 0x04
			LegoU32 m_unk0x0c;    // 0x0c
			LegoU32 m_unk0x10;    // 0x10
			LegoU32 m_unk0x14;    // 0x14
			Event0x20* m_unk0x18; // 0x18
			Event0x20* m_unk0x1c; // 0x1c
		};

		// VTABLE: LEGORACERS 0x004af308
		// SIZE 0x68
		class Model0x68 : public Event0x20 {
		public:
			// SIZE 0x1c
			struct Animation0x1c {
				MabMaterialAnimation0x14* m_unk0x00;     // 0x00
				MabMaterialAnimationItem0x18* m_unk0x04; // 0x04
				LegoU32 m_unk0x08;                       // 0x08
				LegoU32 m_unk0x0c;                       // 0x0c
				LegoU32 m_unk0x10;                       // 0x10
				LegoU32 m_unk0x14;                       // 0x14
				LegoU32 m_unk0x18;                       // 0x18
			};

			Model0x68();
			~Model0x68() override;                                                 // vtable+0x00
			void VTable0x04(undefined4 p_elapsedMs) override;                      // vtable+0x04
			void VTable0x08(BronzeFalcon0xc8770* p_renderer) override;             // vtable+0x08
			void VTable0x0c(BronzeFalcon0xc8770* p_renderer) override;             // vtable+0x0c
			void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 Reset();
			LegoU32 FUN_00404a10(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser);
			LegoU32 FUN_00404c90();
			void FUN_00404e80();

			// SYNTHETIC: LEGORACERS 0x00405df0
			// SaffronQuartz0x2c::Frame0xb8::Model0x68::`vector deleting destructor'

		private:
			LegoU32 m_unk0x20;            // 0x20
			FloatyBoat0x28* m_unk0x24;    // 0x24
			SaffronQuartz0x2c* m_unk0x28; // 0x28
			GolName m_unk0x2c;            // 0x2c
			GolVec3 m_unk0x34;            // 0x34
			GolVec3 m_unk0x40;            // 0x40
			GolVec3 m_unk0x4c;            // 0x4c
			LegoS32 m_unk0x58;            // 0x58
			LegoU32 m_unk0x5c;            // 0x5c
			Animation0x1c* m_unk0x60;     // 0x60
			LegoU32 m_unk0x64;            // 0x64
		};

		// VTABLE: LEGORACERS 0x004af320
		// SIZE 0x34
		class Camera0x34 : public Event0x20 {
		public:
			Camera0x34();
			void VTable0x04(undefined4 p_elapsedMs) override;                      // vtable+0x04
			void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 FUN_004050a0(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// SaffronQuartz0x2c::Frame0xb8::Camera0x34::~Camera0x34

			// SYNTHETIC: LEGORACERS 0x00405cb0
			// SaffronQuartz0x2c::Frame0xb8::Camera0x34::`vector deleting destructor'

		private:
			AmberLens0x344* m_unk0x20;    // 0x20
			GolName m_unk0x24;            // 0x24
			SaffronQuartz0x2c* m_unk0x2c; // 0x2c
			LegoS32 m_unk0x30;            // 0x30
		};

		// VTABLE: LEGORACERS 0x004af358
		// SIZE 0x38
		class AmbientLight0x38 : public Event0x20 {
		public:
			AmbientLight0x38();
			void VTable0x04(undefined4 p_elapsedMs) override;                      // vtable+0x04
			void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			void FUN_00405630(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::~AmbientLight0x38

			// SYNTHETIC: LEGORACERS 0x00406060
			// SaffronQuartz0x2c::Frame0xb8::AmbientLight0x38::`vector deleting destructor'

		private:
			WhiteFalcon0x140::MaterialColor m_unk0x20; // 0x20
			LegoU32 m_unk0x24;                         // 0x24
			LegoU32 m_unk0x28;                         // 0x28
			LegoU32 m_unk0x2c;                         // 0x2c
			LegoU8 m_unk0x30;                          // 0x30
			undefined m_unk0x31[0x34 - 0x31];          // 0x31
			Frame0xb8* m_unk0x34;                      // 0x34
		};

		// VTABLE: LEGORACERS 0x004af370
		// SIZE 0x44
		class DirectionalLight0x44 : public Event0x20 {
		public:
			DirectionalLight0x44();
			void VTable0x04(undefined4 p_elapsedMs) override;                      // vtable+0x04
			void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			LegoU32 FUN_00405280(GolFileParser* p_parser);

			// SYNTHETIC: LEGORACERS 0x00406290 FOLDED
			// SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::~DirectionalLight0x44

			// SYNTHETIC: LEGORACERS 0x004061e0
			// SaffronQuartz0x2c::Frame0xb8::DirectionalLight0x44::`vector deleting destructor'

		private:
			WhiteFalcon0x140::Light m_unk0x20; // 0x20
			LegoU32 m_unk0x30;                 // 0x30
			LegoU32 m_unk0x34;                 // 0x34
			LegoU32 m_unk0x38;                 // 0x38
			LegoU8 m_unk0x3c;                  // 0x3c
			undefined m_unk0x3d[0x40 - 0x3d];  // 0x3d
			Frame0xb8* m_unk0x40;              // 0x40
		};

		// VTABLE: LEGORACERS 0x004af410
		// SIZE 0x44
		class Event0x44 : public Event0x20 {
		public:
			Event0x44();
			~Event0x44() override;                                                 // vtable+0x00
			void VTable0x10(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x10
			void VTable0x14(Frame0xb8* p_frame, BluebellFog0x4* p_event) override; // vtable+0x14

			void Reset();
			LegoU32 FUN_00407090(GolFileParser* p_parser);
			void FUN_004071a0();

			// SYNTHETIC: LEGORACERS 0x00405f20
			// SaffronQuartz0x2c::Frame0xb8::Event0x44::`vector deleting destructor'

		private:
			GolVec3 m_unk0x20; // 0x20
			GolVec3 m_unk0x2c; // 0x2c
			GolVec3 m_unk0x38; // 0x38
		};

		Frame0xb8();
		~Frame0xb8();

		void Reset();
		void FUN_00405950(SaffronQuartz0x2c* p_parent, GolFileParser* p_parser);
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
		void FUN_004064c0(BronzeFalcon0xc8770* p_renderer, LegoU32 p_lensIndex);
		void FUN_004065a0(undefined4 p_unk0x04);
		LegoU32 FUN_004065d0(LegoU32 p_unk0x04, LegoU32 p_unk0x08);
		void FUN_00406680(Event0x20* p_event);
		void FUN_004066b0(Event0x20* p_event);
		LegoU32 FUN_004066d0(AmberLens0x344* p_lens);
		void FUN_00406710(AmberLens0x344* p_lens);
		void FUN_00406760(const WhiteFalcon0x140::MaterialColor* p_material);
		void FUN_00406770(const WhiteFalcon0x140::MaterialColor* p_material);
		LegoU32 FUN_00406790(const WhiteFalcon0x140::Light* p_light);
		void FUN_004067f0(const WhiteFalcon0x140::Light* p_light);
		void FUN_00406860();
		AmberLens0x344* FUN_00406890();

		LegoU32 GetUnk0x44() const { return m_unk0x44; }
		LegoU32 GetUnk0x48() const { return m_unk0x48; }
		LegoU32 GetUnk0x58() const { return m_unk0x58; }

	private:
		SaffronQuartz0x2c* m_unk0x00;                     // 0x00
		LegoU32 m_unk0x04;                                // 0x04
		Camera0x34* m_unk0x08;                            // 0x08
		LegoU32 m_unk0x0c;                                // 0x0c
		Model0x68* m_unk0x10;                             // 0x10
		LegoU32 m_unk0x14;                                // 0x14
		Event0x44* m_unk0x18;                             // 0x18
		LegoU32 m_unk0x1c;                                // 0x1c
		AmbientLight0x38* m_unk0x20;                      // 0x20
		LegoU32 m_unk0x24;                                // 0x24
		DirectionalLight0x44* m_unk0x28;                  // 0x28
		LegoU32 m_unk0x2c;                                // 0x2c
		Event0x20** m_unk0x30;                            // 0x30
		LegoU32 m_unk0x34;                                // 0x34
		Event0x20** m_unk0x38;                            // 0x38
		LegoU32 m_unk0x3c;                                // 0x3c
		Event0x20* m_unk0x40;                             // 0x40
		LegoU32 m_unk0x44;                                // 0x44
		LegoU32 m_unk0x48;                                // 0x48
		LegoU32 m_unk0x4c;                                // 0x4c
		LegoU32 m_unk0x50;                                // 0x50
		LegoU32 m_unk0x54;                                // 0x54
		LegoU32 m_unk0x58;                                // 0x58
		LegoU32 m_unk0x5c;                                // 0x5c
		AmberLens0x344* m_unk0x60[8];                     // 0x60
		const WhiteFalcon0x140::MaterialColor* m_unk0x80; // 0x80
		LegoU32 m_unk0x84;                                // 0x84
		const WhiteFalcon0x140::Light* m_unk0x88[7];      // 0x88
		LegoFloat m_unk0xa4;                              // 0xa4
		Rect m_unk0xa8;                                   // 0xa8
	};

	SaffronQuartz0x2c();
	~SaffronQuartz0x2c() override; // vtable+0x00
	void Clear() override;         // vtable+0x08

	void Reset();
	void FUN_00406980(
		GolExport* p_golExport,
		BronzeFalcon0xc8770* p_renderer,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);
	void FUN_00406b90(GolFileParser* p_parser);
	void FUN_00406c50(LegoBool32 p_binary);
	void FUN_00406cb0(GolFileParser* p_parser);
	AmberLens0x344* FUN_00406de0(const LegoChar* p_name);
	FloatyBoat0x28* FUN_00406e30(const LegoChar* p_name);
	FloatyBoat0x28* FUN_00406e80(const LegoChar* p_name);
	FloatyBoat0x28* FUN_00406ed0(const LegoChar* p_name);
	FloatyBoat0x28* FUN_00406f20(LegoU32 p_index, LegoU32 p_modelIndex);
	MabMaterialAnimation0x14* FUN_00406f40(LegoU32 p_index, LegoU32 p_animationIndex);
	MabMaterialAnimationItem0x18* FUN_00406f60(LegoU32 p_index, LegoU32 p_animationIndex, LegoU32 p_itemIndex);
	LegoU32 FUN_00406f90(LegoFloat p_scale);

	void SetUnk0x0c(BluebellFog0x4* p_unk0x0c) { m_unk0x0c = p_unk0x0c; }
	BluebellFog0x4* GetUnk0x0c() const { return m_unk0x0c; }
	LegoU32 GetFrameCount() const { return m_frameCount; }
	Frame0xb8* GetFrames() const { return m_frames; }

	// SYNTHETIC: LEGORACERS 0x004068f0
	// SaffronQuartz0x2c::`scalar deleting destructor'

private:
	BluebellFog0x4* m_unk0x0c;         // 0x0c
	GolExport* m_golExport;            // 0x10
	BronzeFalcon0xc8770* m_renderer;   // 0x14
	LegoU32 m_unk0x18;                 // 0x18
	ZoweeBlubberworth0xf0** m_unk0x1c; // 0x1c
	LegoChar* m_unk0x20;               // 0x20
	LegoU32 m_frameCount;              // 0x24
	Frame0xb8* m_frames;               // 0x28
};

#endif // SAFFRONQUARTZ0X2C_H
