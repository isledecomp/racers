#ifndef CRIMSONPEBBLE0X228_H
#define CRIMSONPEBBLE0X228_H

#include "audio/soundnode.h"
#include "bluebellfog0x4.h"
#include "color.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golmath.h"
#include "golname.h"
#include "golnametable.h"
#include "golstring.h"
#include "golstringtable.h"
#include "types.h"

class BronzeFalcon0xc8770;
class CrimsonPebble0x228;
class GolExport;
class GolFont0xa0;
class GolFileParser;
class MabMaterialAnimation0x14;
class WhiteFalcon0x140;
class SaffronQuartz0x2c;
class SoundManager;
class MenuAnimationList;
class AmberLens0x344;
struct Rect;

// SIZE 0x14
class CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleEvent0x14();
	virtual ~CrimsonPebbleEvent0x14();                                       // vtable+0x00
	virtual void VTable0x04(undefined4 p_arg);                               // vtable+0x04
	virtual void VTable0x08(undefined4 p_arg);                               // vtable+0x08
	virtual void VTable0x0c(undefined4 p_arg);                               // vtable+0x0c
	virtual void VTable0x10(const GolVec3*, const GolVec3*, const GolVec3*); // vtable+0x10
	virtual void VTable0x14();                                               // vtable+0x14
	virtual void VTable0x18();                                               // vtable+0x18

	void Reset();

protected:
	undefined4 m_unk0x04; // 0x04
	undefined4 m_unk0x08; // 0x08
	undefined4 m_unk0x0c; // 0x0c
	undefined4 m_unk0x10; // 0x10
};

// SIZE 0x2c
struct CrimsonPebbleEventValueSource0x2c {
	undefined m_unk0x00[0x28]; // 0x00
	undefined4 m_unk0x28;      // 0x28
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
	undefined4 m_unk0x24;      // 0x24
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

private:
	undefined4 m_unk0x00;               // 0x00
	CrimsonPebbleEvent0x14* m_event;    // 0x04
	CrimsonPebbleEventLink0x0c* m_next; // 0x08
};

// SIZE 0x30
class CrimsonPebbleEvent0x30 : public CrimsonPebbleEvent0x14 {
public:
	void FUN_004a40f0();

private:
	undefined m_unk0x14[0x30 - 0x14]; // 0x14
};

// SIZE 0x48
class CrimsonPebbleEvent0x48 : public CrimsonPebbleEvent0x14 {
public:
	void FUN_004a4d10(LegoFloat p_elapsedSeconds);

private:
	undefined m_unk0x14[0x48 - 0x14]; // 0x14
};

// SIZE 0x50
class CrimsonPebbleEvent0x50 : public CrimsonPebbleEvent0x14 {
public:
	void FUN_004a3df0(LegoU32 p_elapsedMs);
	void FUN_004a44f0();

private:
	undefined m_unk0x14[0x50 - 0x14]; // 0x14
};

// SIZE 0x58
class CrimsonPebbleVisual0x58 : public CrimsonPebbleEvent0x14 {
public:
	CrimsonPebbleVisual0x58();
	~CrimsonPebbleVisual0x58() override; // vtable+0x00

	void VTable0x14() override;                                       // vtable+0x14
	void VTable0x18() override;                                       // vtable+0x18
	virtual void VTable0x1c(LegoS32* p_width, LegoS32* p_height) = 0; // vtable+0x1c
	virtual void VTable0x20(
		WhiteFalcon0x140* p_renderer,
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
	void FUN_004a35a0(BronzeFalcon0xc8770* p_renderer);
	void ParseVisualToken(
		GolFileParser* p_parser,
		GolFileParser::ParserTokenType p_token,
		CrimsonPebble0x228* p_owner,
		WhiteFalcon0x140* p_renderer
	);

protected:
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

// SIZE 0x64
class CrimsonPebbleVisual0x64 : public CrimsonPebbleVisual0x58 {
private:
	undefined m_unk0x58[0x64 - 0x58]; // 0x58
};

// VTABLE: LEGORACERS 0x004b4af4
// SIZE 0x70
class CrimsonPebbleText0x70 : public CrimsonPebbleVisual0x58 {
public:
	CrimsonPebbleText0x70();
	~CrimsonPebbleText0x70() override; // vtable+0x00

	void VTable0x1c(LegoS32* p_width, LegoS32* p_height) override; // vtable+0x1c
	void VTable0x20(
		WhiteFalcon0x140* p_renderer,
		LegoS32 p_x,
		LegoS32 p_y,
		undefined4,
		undefined4,
		LegoFloat p_scaleX,
		LegoFloat p_scaleY
	) override; // vtable+0x20

	void Reset();
	void Clear();
	void Parse(GolFileParser* p_parser, CrimsonPebble0x228* p_owner, WhiteFalcon0x140* p_renderer);
	void RefreshString(CrimsonPebble0x228* p_owner, WhiteFalcon0x140* p_renderer);

	// SYNTHETIC: LEGORACERS 0x004a2480
	// CrimsonPebbleText0x70::`vector deleting destructor'

private:
	GolString m_string;    // 0x58
	LegoChar* m_rawString; // 0x64
	GolFont0xa0* m_font;   // 0x68
	LegoU32 m_stringIndex; // 0x6c
};

// SIZE 0x33c
class CrimsonPebbleAnimation0x33c {
public:
	void FUN_00489fa0(LegoU32 p_elapsedMs);
	void FUN_00489ff0(BronzeFalcon0xc8770* p_renderer);
	void FUN_0048a040(BronzeFalcon0xc8770* p_renderer);

private:
	undefined m_unk0x000[0x33c]; // 0x000
};

// VTABLE: LEGORACERS 0x004b4970
// SIZE 0x228
class CrimsonPebble0x228 : public BluebellFog0x4 {
public:
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
		BronzeFalcon0xc8770* p_renderer,
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
		undefined4 p_unk0x04,
		undefined4& p_unk0x08,
		CrimsonPebbleEventLink0x0c*& p_unk0x0c,
		GolNameTable& p_unk0x10
	);
	void FUN_004a2dc0(LegoU32 p_elapsedMs);
	void FUN_004a2f30(BronzeFalcon0xc8770* p_renderer);
	void FUN_004a2f80(AmberLens0x344* p_lens);
	void FUN_004a3070(BronzeFalcon0xc8770* p_renderer);
	void FUN_004a30b0(BronzeFalcon0xc8770* p_renderer);
	void FUN_004a3150();
	GolStringTable* GetStringTableByIndex(LegoU32 p_index);

	LegoU32 GetUnk0x118() const { return m_unk0x118; }
	LegoU32 GetStringTableCount() const { return m_unk0x78; }
	SoundManager* GetSoundManager() const { return m_soundManager; }
	void SetStringTable(GolStringTable* p_stringTable) { m_stringTable = p_stringTable; }

	// SYNTHETIC: LEGORACERS 0x004a0390
	// CrimsonPebble0x228::`scalar deleting destructor'

	void FUN_004a0bf0();

private:
	GolExport* m_unk0x04;                   // 0x004
	BronzeFalcon0xc8770* m_unk0x08;         // 0x008
	SoundManager* m_soundManager;           // 0x00c
	SaffronQuartz0x2c* m_unk0x10;           // 0x010
	SoundNode m_unk0x14;                    // 0x014
	MenuAnimationList* m_unk0x64;           // 0x064
	LegoU32 m_unk0x68;                      // 0x068
	CrimsonPebbleAnimation0x33c* m_unk0x6c; // 0x06c
	MabMaterialAnimation0x14* m_unk0x70;    // 0x070
	undefined4* m_unk0x74;                  // 0x074
	LegoU32 m_unk0x78;                      // 0x078
	GolStringTable* m_unk0x7c;              // 0x07c
	LegoChar* m_unk0x80;                    // 0x080
	undefined4 m_unk0x84;                   // 0x084
	undefined4* m_unk0x88;                  // 0x088
	undefined4* m_unk0x8c;                  // 0x08c
	undefined4 m_unk0x90;                   // 0x090
	undefined4* m_unk0x94;                  // 0x094
	undefined4* m_unk0x98;                  // 0x098
	undefined4 m_unk0x9c;                   // 0x09c
	undefined4* m_unk0xa0;                  // 0x0a0
	undefined4* m_unk0xa4;                  // 0x0a4
	GolNameTable m_unk0xa8;                 // 0x0a8
	LegoU32 m_unk0xb4;                      // 0x0b4
	CrimsonPebbleEvent0x48* m_unk0xb8;      // 0x0b8
	GolNameTable m_unk0xbc;                 // 0x0bc
	LegoU32 m_unk0xc8;                      // 0x0c8
	CrimsonPebbleEvent0x30* m_unk0xcc;      // 0x0cc
	GolNameTable m_unk0xd0;                 // 0x0d0
	LegoU32 m_unk0xdc;                      // 0x0dc
	CrimsonPebbleEvent0x50* m_unk0xe0;      // 0x0e0
	GolNameTable m_unk0xe4;                 // 0x0e4
	LegoU32 m_unk0xf0;                      // 0x0f0
	CrimsonPebbleEvent0x50* m_unk0xf4;      // 0x0f4
	GolNameTable m_unk0xf8;                 // 0x0f8
	undefined4 m_unk0x104;                  // 0x104
	undefined4* m_unk0x108;                 // 0x108
	GolNameTable m_unk0x10c;                // 0x10c
	LegoU32 m_unk0x118;                     // 0x118
	CrimsonPebbleText0x70* m_unk0x11c;      // 0x11c
	GolNameTable m_unk0x120;                // 0x120
	LegoU32 m_unk0x12c;                     // 0x12c
	CrimsonPebbleVisual0x64* m_unk0x130;    // 0x130
	undefined4 m_unk0x134;                  // 0x134
	CrimsonPebbleEventLink0x0c* m_unk0x138; // 0x138
	GolNameTable m_unk0x13c;                // 0x13c
	undefined4 m_unk0x148;                  // 0x148
	CrimsonPebbleEventLink0x0c* m_unk0x14c; // 0x14c
	GolNameTable m_unk0x150;                // 0x150
	undefined4 m_unk0x15c;                  // 0x15c
	CrimsonPebbleEventLink0x0c* m_unk0x160; // 0x160
	GolNameTable m_unk0x164;                // 0x164
	undefined4 m_unk0x170;                  // 0x170
	CrimsonPebbleEventLink0x0c* m_unk0x174; // 0x174
	GolNameTable m_unk0x178;                // 0x178
	undefined4 m_unk0x184;                  // 0x184
	CrimsonPebbleEventLink0x0c* m_unk0x188; // 0x188
	GolNameTable m_unk0x18c;                // 0x18c
	undefined4 m_unk0x198;                  // 0x198
	CrimsonPebbleEventLink0x0c* m_unk0x19c; // 0x19c
	GolNameTable m_unk0x1a0;                // 0x1a0
	undefined4 m_unk0x1ac;                  // 0x1ac
	CrimsonPebbleEventLink0x0c* m_unk0x1b0; // 0x1b0
	GolNameTable m_unk0x1b4;                // 0x1b4
	undefined4 m_unk0x1c0;                  // 0x1c0
	CrimsonPebbleEventLink0x0c* m_unk0x1c4; // 0x1c4
	GolNameTable m_unk0x1c8;                // 0x1c8
	undefined4 m_unk0x1d4;                  // 0x1d4
	CrimsonPebbleEventLink0x0c* m_unk0x1d8; // 0x1d8
	GolNameTable m_unk0x1dc;                // 0x1dc
	undefined4 m_unk0x1e8;                  // 0x1e8
	CrimsonPebbleEventLink0x0c* m_unk0x1ec; // 0x1ec
	GolNameTable m_unk0x1f0;                // 0x1f0
	undefined4 m_unk0x1fc;                  // 0x1fc
	CrimsonPebbleEventLink0x0c* m_unk0x200; // 0x200
	GolNameTable m_unk0x204;                // 0x204
	undefined4 m_unk0x210;                  // 0x210
	CrimsonPebbleEventLink0x0c* m_unk0x214; // 0x214
	GolNameTable m_unk0x218;                // 0x218
	GolStringTable* m_stringTable;          // 0x224
};

#endif // CRIMSONPEBBLE0X228_H
