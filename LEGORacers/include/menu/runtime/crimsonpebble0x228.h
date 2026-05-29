#ifndef CRIMSONPEBBLE0X228_H
#define CRIMSONPEBBLE0X228_H

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
#include "util/bluebellfog0x4.h"

class GolD3DRenderDevice;
class CrimsonPebble0x228;
class CrimsonPebbleAnimation0x33c;
class GolExport;
class GolFont0xa0;
class GolFontTable;
class GolFileParser;
class GolWorldEntity;
class MabMaterialAnimation0x14;
class MabMaterialAnimationItem0x18;
class OpalHaven0xf4;
class Particle0x18c;
class GolRenderDevice;
class UtopianPan0xa4;
class SaffronQuartz0x2c;
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
class CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleEvent0x14();
	virtual ~CrimsonPebbleEvent0x14();                                       // vtable+0x00
	virtual void VTable0x04(GolWorldEntity* p_arg);                          // vtable+0x04
	virtual void VTable0x08(GolWorldEntity* p_arg);                          // vtable+0x08
	virtual void VTable0x0c(GolWorldEntity* p_arg);                          // vtable+0x0c
	virtual void VTable0x10(const GolVec3*, const GolVec3*, const GolVec3*); // vtable+0x10
	virtual void VTable0x14();                                               // vtable+0x14
	virtual void VTable0x18();                                               // vtable+0x18

	void Reset();
	void FUN_0049fe30(undefined4 p_param1, GolVec3* p_param2);
	void FUN_0049fec0(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3);
	void ParseCommonToken(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, GolFileParser::ParserTokenType p_token);

	// SYNTHETIC: LEGORACERS 0x0049fd90
	// CrimsonPebbleEvent0x14::`scalar deleting destructor'

protected:
	GolWorldEntity* m_unk0x04; // 0x04
	GolWorldEntity* m_unk0x08; // 0x08
	OpalHaven0xf4* m_unk0x0c;  // 0x0c
	undefined4 m_unk0x10;      // 0x10
};

// SIZE 0x2c
struct CrimsonPebbleEventValueSource0x2c {
	undefined m_unk0x00[0x28]; // 0x00
	GolWorldEntity* m_unk0x28; // 0x28
};

// SIZE 0x24
struct CrimsonPebbleEventValuePayload0x24 {
	undefined m_unk0x00[0x20];                    // 0x00
	CrimsonPebbleEventValueSource0x2c* m_unk0x20; // 0x20
};

// SIZE 0x28
struct CrimsonPebbleEventSelectorPayload0x28 {
	undefined m_unk0x00[0x20]; // 0x00
	undefined4 m_unk0x20;      // 0x20
	GolWorldEntity* m_unk0x24; // 0x24
};

// SIZE 0x44
struct CrimsonPebbleEventVectorPayload0x44 {
	undefined m_unk0x00[0x20]; // 0x00
	GolVec3 m_unk0x20;         // 0x20
	GolVec3 m_unk0x2c;         // 0x2c
	GolVec3 m_unk0x38;         // 0x38
};

// SIZE 0x0c
class CrimsonPebbleEventLink0x0c {
public:
	CrimsonPebbleEventLink0x0c();

	void FUN_004a00c0(undefined4 p_unk0x04, CrimsonPebbleEvent0x14* p_event);
	void FUN_004a00d0();
	void FUN_004a00f0(CrimsonPebbleEventValuePayload0x24* p_payload);
	void FUN_004a0120(CrimsonPebbleEventSelectorPayload0x28* p_payload);
	void FUN_004a0180(CrimsonPebbleEventVectorPayload0x44* p_payload);
	void FUN_004a0200(void*);

	CrimsonPebbleEventLink0x0c* GetNext() const { return m_next; }
	void SetNext(CrimsonPebbleEventLink0x0c* p_next) { m_next = p_next; }

private:
	undefined4 m_unk0x00;               // 0x00
	CrimsonPebbleEvent0x14* m_event;    // 0x04
	CrimsonPebbleEventLink0x0c* m_next; // 0x08
};

// VTABLE: LEGORACERS 0x004b4abc
// SIZE 0x30
class CrimsonPebbleEvent0x30 : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleEvent0x30();

	void VTable0x14() override; // vtable+0x14
	void VTable0x18() override; // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner);
	LegoBool32 ParseToken(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, GolFileParser::ParserTokenType p_token);
	void FUN_004a4050();
	void FUN_004a40f0();

	// SYNTHETIC: LEGORACERS 0x004a1d60
	// CrimsonPebbleEvent0x30::`vector deleting destructor'

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
class CrimsonPebbleEvent0x48 : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleEvent0x48();

	void VTable0x14() override;                      // vtable+0x14
	void VTable0x18() override;                      // vtable+0x18
	void VTable0x08(GolWorldEntity* p_arg) override; // vtable+0x08

	void Reset();
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner);
	void FUN_004a4d10(LegoFloat p_elapsedSeconds);
	void FUN_004a4da0();

	// SYNTHETIC: LEGORACERS 0x004a1ba0
	// CrimsonPebbleEvent0x48::`vector deleting destructor'

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

struct WoozyTrade {
public:
	enum {
		c_flagBit0 = 1 << 0
	};

	// size unknown, confirmed to be at least 5

	Particle0x18c* m_unk0x00;
	LegoU8 m_unk0x04;
};

// VTABLE: LEGORACERS 0x004b4a94
// SIZE 0x50
class CrimsonPebbleEvent0x50 : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleEvent0x50();

	void VTable0x04(GolWorldEntity* p_arg) override;                                      // vtable+0x04
	void VTable0x0c(GolWorldEntity* p_arg) override;                                      // vtable+0x0c
	void VTable0x10(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void VTable0x14() override;                                                           // vtable+0x14
	void VTable0x18() override;                                                           // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner);
	void FUN_004a3db0();
	void FUN_004a3df0(LegoU32 p_elapsedMs);

	// SYNTHETIC: LEGORACERS 0x004a1f20
	// CrimsonPebbleEvent0x50::`vector deleting destructor'

private:
	CrimsonPebbleAnimation0x33c* m_unk0x14; // 0x14
	WoozyTrade* m_unk0x18;                  // 0x18
	GolName m_unk0x1c;                      // 0x1c
	GolVec3 m_unk0x24;                      // 0x24
	GolVec3 m_unk0x30;                      // 0x30
	GolVec3 m_unk0x3c;                      // 0x3c
	LegoU32 m_unk0x48;                      // 0x48
	LegoU32 m_unk0x4c;                      // 0x4c
};

// VTABLE: LEGORACERS 0x004b4ad8
// SIZE 0x50
class CrimsonPebbleEvent0x50Derived : public CrimsonPebbleEvent0x30 {
public:
	enum Flags {
		c_flagBit3 = 1 << 3,
	};

	CrimsonPebbleEvent0x50Derived();

	void VTable0x04(GolWorldEntity* p_arg) override;                                      // vtable+0x04
	void VTable0x0c(GolWorldEntity* p_arg) override;                                      // vtable+0x0c
	void VTable0x10(const GolVec3* p_a, const GolVec3* p_b, const GolVec3* p_c) override; // vtable+0x10
	void VTable0x14() override;                                                           // vtable+0x14
	void VTable0x18() override;                                                           // vtable+0x18

	void Reset();
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner);
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
class CrimsonPebbleMenuAnimationEvent0x2c : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleMenuAnimationEvent0x2c();

	void VTable0x14() override; // vtable+0x14
	void VTable0x18() override; // vtable+0x18

	void Reset();
	void Parse(
		GolFileParser* p_parser,
		CrimsonPebble0x228* p_owner,
		MenuAnimationList* p_animationList,
		GolD3DRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a22b0
	// CrimsonPebbleMenuAnimationEvent0x2c::`vector deleting destructor'

	// SYNTHETIC: LEGORACERS 0x004a20e0 FOLDED
	// CrimsonPebbleMenuAnimationEvent0x2c::~CrimsonPebbleMenuAnimationEvent0x2c

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
class CrimsonPebbleVisual0x58 : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleVisual0x58();
	~CrimsonPebbleVisual0x58() override; // vtable+0x00

	void VTable0x14() override;                                       // vtable+0x14
	void VTable0x18() override;                                       // vtable+0x18
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
		CrimsonPebble0x228* p_owner,
		GolRenderDevice* p_renderer
	);

	// SYNTHETIC: LEGORACERS 0x004a32d0
	// CrimsonPebbleVisual0x58::`scalar deleting destructor'

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
class CrimsonPebbleVisual0x64 : public CrimsonPebbleVisual0x58 {
public:
	CrimsonPebbleVisual0x64();
	~CrimsonPebbleVisual0x64() override; // vtable+0x00

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
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, GolRenderDevice* p_renderer);
	void FUN_004a3910(GolD3DRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2690
	// CrimsonPebbleVisual0x64::`vector deleting destructor'

private:
	UtopianPan0xa4* m_unk0x58; // 0x58
	GolName m_unk0x5c;         // 0x5c
};

// VTABLE: LEGORACERS 0x004b4af4
// SIZE 0x70
class CrimsonPebbleText0x70 : public CrimsonPebbleVisual0x58 {
public:
	CrimsonPebbleText0x70();
	~CrimsonPebbleText0x70() override; // vtable+0x00

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
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, GolRenderDevice* p_renderer);
	void RefreshString(CrimsonPebble0x228* p_owner, GolRenderDevice* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2480
	// CrimsonPebbleText0x70::`vector deleting destructor'

private:
	GolString m_string;    // 0x58
	LegoChar* m_rawString; // 0x64
	GolFont0xa0* m_font;   // 0x68
	LegoU32 m_stringIndex; // 0x6c
};

// VTABLE: LEGORACERS 0x004b403c
// SIZE 0x33c
class CrimsonPebbleAnimation0x33c : public GolNameTable {
public:
	// VTABLE: LEGORACERS 0x004b4048
	// SIZE 0x1fc
	class EmbTxtParser : public GolTxtParser {};

	// SIZE 0x08
	class Entry0x8 {
	public:
		Entry0x8();
		~Entry0x8();

	private:
		undefined4 m_unk0x00;     // 0x00
		LegoU8 m_unk0x04;         // 0x04
		undefined m_unk0x05[0x3]; // 0x05
	};

	// SIZE 0x44
	class Runtime0x44 {
	public:
		struct ListTypeAt0x00 {
			LegoFloat m_unk0x00;
			LegoFloat m_unk0x04;
			LegoFloat m_unk0x08;
		};

		Runtime0x44();
		~Runtime0x44();

		void Clear();
		void Reset();

		void Parse(
			MabMaterialAnimation0x14* p_materialAnimation,
			GolD3DRenderDevice* p_renderer,
			GolFileParser* p_parser,
			CrimsonPebbleAnimation0x33c* p_param4
		);

	private:
		ListTypeAt0x00* m_unk0x00;                     // 0x00
		LegoS32 m_unk0x04;                             // 0x04
		LegoFloat m_unk0x08;                           // 0x08
		LegoFloat m_unk0x0c;                           // 0x0c
		LegoFloat m_unk0x10;                           // 0x10
		LegoS32 m_unk0x14;                             // 0x14
		LegoS8 m_unk0x18;                              // 0x18
		LegoS8 m_unk0x19;                              // 0x19
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

	CrimsonPebbleAnimation0x33c();
	~CrimsonPebbleAnimation0x33c() override; // vtable+0x00

	void Clear() override; // vtable+0x08

	WoozyTrade* FUN_00489d70(const LegoChar* p_param1, GolVec3* p_param2, GolVec3* p_param3, GolVec3* p_param4);
	void FUN_00489f00(WoozyTrade* p_param);
	void FUN_00489fa0(LegoU32 p_elapsedMs);
	void FUN_00489ff0(GolD3DRenderDevice* p_renderer);
	void FUN_0048a040(GolD3DRenderDevice* p_renderer);
	void FUN_00489af0(
		LegoU32 p_unk0x04,
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		MabMaterialAnimation0x14* p_materialAnimation,
		const LegoChar* p_fileName,
		LegoBool32 p_binary
	);

	// SYNTHETIC: LEGORACERS 0x004a1180
	// CrimsonPebbleAnimation0x33c::`vector deleting destructor'

private:
	Particle0x18c* m_particles; // 0x00c
	Runtime0x44* m_unk0x010;    // 0x010
	Entry0x8 m_unk0x014[100];   // 0x014
	LegoU32 m_unk0x334;         // 0x334
	LegoU32 m_numParticles;     // 0x338
};

// VTABLE: LEGORACERS 0x004b4970
// SIZE 0x228
class CrimsonPebble0x228 : public BluebellFog0x4 {
public:
	// VTABLE: LEGORACERS 0x004b49d4
	// SIZE 0x1fc
	class CebTxtParser : public GolTxtParser {};

	CrimsonPebble0x228();

	void VTable0x00(void*, void*, void*) override; // vtable+0x00
	void VTable0x04(void*, void*, void*) override; // vtable+0x04
	void VTable0x08(void*, void*, void*) override; // vtable+0x08
	void VTable0x0c(void*, void*, void*) override; // vtable+0x0c
	void VTable0x10(void*, void*, void*) override; // vtable+0x10
	void VTable0x14(void*, void*, void*) override; // vtable+0x14
	void VTable0x18(void*, void*, void*) override; // vtable+0x18
	void VTable0x1c(void*, void*, void*) override; // vtable+0x1c
	void VTable0x20(void*, void*, void*) override; // vtable+0x20
	void VTable0x24(void*, void*, void*) override; // vtable+0x24
	void VTable0x28(void*, void*, void*) override; // vtable+0x28
	void VTable0x2c(void*, void*, void*) override; // vtable+0x2c
	virtual ~CrimsonPebble0x228();                 // vtable+0x30

	void Reset();
	LegoBool32 HasFileWithSuffix(const LegoChar* p_fileName, const LegoChar* p_suffix);
	void FUN_004a0730(
		GolExport* p_golExport,
		GolD3DRenderDevice* p_renderer,
		SoundManager* p_soundManager,
		SaffronQuartz0x2c* p_unk0x10,
		const LegoChar* p_fileName,
		undefined4 p_binary
	);
	void FUN_004a0ff0(GolFileParser* p_parser);
	void FUN_004a1240(undefined4 p_binary);
	void FUN_004a12e0(GolFileParser* p_unk0x04);
	void FUN_004a14e0();
	void FUN_004a15e0(GolFileParser* p_parser);
	void FUN_004a16f0();
	void FUN_004a1760(GolFileParser* p_parser);
	void FUN_004a1850(undefined4 p_binary);
	void FUN_004a18d0(GolFileParser* p_parser);
	void FUN_004a19c0(undefined4 p_binary);
	void FUN_004a1a40(GolFileParser* p_parser);
	void FUN_004a1c00(GolFileParser* p_parser);
	void FUN_004a1dc0(GolFileParser* p_parser);
	void FUN_004a1f80(GolFileParser* p_parser);
	void FUN_004a20f0(GolFileParser* p_parser);
	void LoadTextEntries(GolFileParser* p_parser);
	void FUN_004a24e0();
	void FUN_004a2520(GolFileParser* p_parser);
	void FUN_004a26f0();
	void FUN_004a2730(
		GolFileParser* p_parser,
		LegoU32 p_token,
		undefined4& p_unk0x08,
		CrimsonPebbleEventLink0x0c*& p_unk0x0c,
		GolNameTable& p_unk0x10
	);
	void FUN_004a2dc0(LegoU32 p_elapsedMs);
	void FUN_004a2f30(GolD3DRenderDevice* p_renderer);
	void FUN_004a2f80(GolCamera* p_lens);
	void FUN_004a3070(GolD3DRenderDevice* p_renderer);
	void FUN_004a30b0(GolD3DRenderDevice* p_renderer);
	void FUN_004a3150();
	GolStringTable* GetStringTableByIndex(LegoU32 p_index);

	LegoU32 GetUnk0x118() const { return m_unk0x118; }
	LegoU32 GetStringTableCount() const { return m_unk0x78; }
	SoundManager* GetSoundManager() const { return m_soundManager; }
	void SetStringTable(GolStringTable* p_stringTable) { m_stringTable = p_stringTable; }
	LegoU32 GetAnimationCount() const { return m_unk0x68; }
	CrimsonPebbleAnimation0x33c* GetAnimationByIndex(LegoU32 p_index) const { return &m_unk0x6c[p_index]; }
	LegoU32 GetSoundGroupCount() const { return m_unk0x84; }
	SoundGroup* GetSoundGroupByIndex(LegoU32 p_index) const { return m_unk0x88[p_index]; }
	GolWorldEntity* FUN_004a3230(const LegoChar* p_name);
	GolWorldEntity* FUN_004a3240(const LegoChar* p_name);
	GolWorldEntity* FUN_004a3250(const LegoChar* p_name);

	// SYNTHETIC: LEGORACERS 0x004a0390
	// CrimsonPebble0x228::`scalar deleting destructor'

	void Clear();

private:
	GolExport* m_unk0x04;                            // 0x004
	GolD3DRenderDevice* m_unk0x08;                   // 0x008
	SoundManager* m_soundManager;                    // 0x00c
	SaffronQuartz0x2c* m_unk0x10;                    // 0x010
	SoundNode m_unk0x14;                             // 0x014
	MenuAnimationList* m_unk0x64;                    // 0x064
	LegoU32 m_unk0x68;                               // 0x068
	CrimsonPebbleAnimation0x33c* m_unk0x6c;          // 0x06c
	MabMaterialAnimation0x14* m_unk0x70;             // 0x070
	LegoChar* m_unk0x74;                             // 0x074
	LegoU32 m_unk0x78;                               // 0x078
	GolStringTable* m_unk0x7c;                       // 0x07c
	LegoChar* m_unk0x80;                             // 0x080
	LegoU32 m_unk0x84;                               // 0x084
	SoundGroup** m_unk0x88;                          // 0x088
	LegoChar* m_unk0x8c;                             // 0x08c
	LegoU32 m_unk0x90;                               // 0x090
	GolFontTable** m_unk0x94;                        // 0x094
	LegoChar* m_unk0x98;                             // 0x098
	LegoU32 m_unk0x9c;                               // 0x09c
	AwakeKite0x20** m_unk0xa0;                       // 0x0a0
	LegoChar* m_unk0xa4;                             // 0x0a4
	GolNameTable m_unk0xa8;                          // 0x0a8
	LegoU32 m_unk0xb4;                               // 0x0b4
	CrimsonPebbleEvent0x48* m_unk0xb8;               // 0x0b8
	GolNameTable m_unk0xbc;                          // 0x0bc
	LegoU32 m_unk0xc8;                               // 0x0c8
	CrimsonPebbleEvent0x30* m_unk0xcc;               // 0x0cc
	GolNameTable m_unk0xd0;                          // 0x0d0
	LegoU32 m_unk0xdc;                               // 0x0dc
	CrimsonPebbleEvent0x50Derived* m_unk0xe0;        // 0x0e0
	GolNameTable m_unk0xe4;                          // 0x0e4
	LegoU32 m_unk0xf0;                               // 0x0f0
	CrimsonPebbleEvent0x50* m_unk0xf4;               // 0x0f4
	GolNameTable m_unk0xf8;                          // 0x0f8
	undefined4 m_unk0x104;                           // 0x104
	CrimsonPebbleMenuAnimationEvent0x2c* m_unk0x108; // 0x108
	GolNameTable m_unk0x10c;                         // 0x10c
	LegoU32 m_unk0x118;                              // 0x118
	CrimsonPebbleText0x70* m_unk0x11c;               // 0x11c
	GolNameTable m_unk0x120;                         // 0x120
	LegoU32 m_unk0x12c;                              // 0x12c
	CrimsonPebbleVisual0x64* m_unk0x130;             // 0x130
	undefined4 m_unk0x134;                           // 0x134
	CrimsonPebbleEventLink0x0c* m_unk0x138;          // 0x138
	GolNameTable m_unk0x13c;                         // 0x13c
	undefined4 m_unk0x148;                           // 0x148
	CrimsonPebbleEventLink0x0c* m_unk0x14c;          // 0x14c
	GolNameTable m_unk0x150;                         // 0x150
	undefined4 m_unk0x15c;                           // 0x15c
	CrimsonPebbleEventLink0x0c* m_unk0x160;          // 0x160
	GolNameTable m_unk0x164;                         // 0x164
	undefined4 m_unk0x170;                           // 0x170
	CrimsonPebbleEventLink0x0c* m_unk0x174;          // 0x174
	GolNameTable m_unk0x178;                         // 0x178
	undefined4 m_unk0x184;                           // 0x184
	CrimsonPebbleEventLink0x0c* m_unk0x188;          // 0x188
	GolNameTable m_unk0x18c;                         // 0x18c
	undefined4 m_unk0x198;                           // 0x198
	CrimsonPebbleEventLink0x0c* m_unk0x19c;          // 0x19c
	GolNameTable m_unk0x1a0;                         // 0x1a0
	undefined4 m_unk0x1ac;                           // 0x1ac
	CrimsonPebbleEventLink0x0c* m_unk0x1b0;          // 0x1b0
	GolNameTable m_unk0x1b4;                         // 0x1b4
	undefined4 m_unk0x1c0;                           // 0x1c0
	CrimsonPebbleEventLink0x0c* m_unk0x1c4;          // 0x1c4
	GolNameTable m_unk0x1c8;                         // 0x1c8
	undefined4 m_unk0x1d4;                           // 0x1d4
	CrimsonPebbleEventLink0x0c* m_unk0x1d8;          // 0x1d8
	GolNameTable m_unk0x1dc;                         // 0x1dc
	undefined4 m_unk0x1e8;                           // 0x1e8
	CrimsonPebbleEventLink0x0c* m_unk0x1ec;          // 0x1ec
	GolNameTable m_unk0x1f0;                         // 0x1f0
	undefined4 m_unk0x1fc;                           // 0x1fc
	CrimsonPebbleEventLink0x0c* m_unk0x200;          // 0x200
	GolNameTable m_unk0x204;                         // 0x204
	undefined4 m_unk0x210;                           // 0x210
	CrimsonPebbleEventLink0x0c* m_unk0x214;          // 0x214
	GolNameTable m_unk0x218;                         // 0x218
	GolStringTable* m_stringTable;                   // 0x224
};

#endif // CRIMSONPEBBLE0X228_H
