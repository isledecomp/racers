#ifndef PERIDOTTRACE0X4E0_H
#define PERIDOTTRACE0X4E0_H

#include "decomp.h"
#include "displaydriverguid.h"
#include "golfile.h"
#include "peridottraceroot0x108.h"
#include "types.h"

#include <string.h>

class GolFile;
class GolString;
class InputManager;
class PeridotTraceBuffer0x250;
class PeridotTrace0x4e0;

// SIZE 0x28
struct PeridotTraceInputBindingEntry {
	LegoU8 m_deviceType;    // 0x00
	LegoU8 m_deviceSubType; // 0x01
	LegoU8 m_unk0x02;       // 0x02
	LegoU8 m_unk0x03;       // 0x03
	LegoU32 m_events[9];    // 0x04
};

// SIZE 0x04
struct PeridotTraceInputBindingPlayerState {
	LegoU8 m_unk0x00;            // 0x00
	LegoU8 m_unk0x01;            // 0x01
	LegoU8 m_unk0x02;            // 0x02
	LegoU8 m_selectedEntryIndex; // 0x03
};

// SIZE 0xd0
struct PeridotTraceInputBindingState {
	PeridotTraceInputBindingPlayerState m_players[2]; // 0x00
	PeridotTraceInputBindingEntry m_entries[5];       // 0x08

	LegoU8 GetSelectedEntryIndex(LegoU32 p_playerIndex) const { return m_players[p_playerIndex].m_selectedEntryIndex; }

	void SetSelectedEntryIndex(LegoU32 p_playerIndex, LegoU8 p_entryIndex)
	{
		m_players[p_playerIndex].m_selectedEntryIndex = p_entryIndex;
	}
};

// SIZE 0x42c
struct PeridotTracePersistentState {
	void Clear() { ::memset(this, 0, sizeof(*this)); }

	LegoU8 m_unk0x0c;                                  // 0x000
	DisplayDriverGuid::Serialized m_displayDriverGuid; // 0x001
	LegoU8 m_unk0x1d;                                  // 0x011
	LegoU8 m_unk0x1e;                                  // 0x012
	LegoU8 m_unk0x1f;                                  // 0x013
	LegoU8 m_unk0x20;                                  // 0x014
	LegoU8 m_unk0x21;                                  // 0x015
	LegoU8 m_languageIndex;                            // 0x016
	LegoU8 m_unk0x23;                                  // 0x017
	LegoU8 m_unk0x24;                                  // 0x018
	LegoU8 m_unk0x25;                                  // 0x019
	LegoU16 m_unk0x26;                                 // 0x01a
	LegoU32 m_unk0x28[13];                             // 0x01c
	LegoU32 m_unk0x5c[13];                             // 0x050
	LegoU8 m_unk0x90[13][28];                          // 0x084
	LegoU8 m_unk0x1fc[13][28];                         // 0x1f0
	PeridotTraceInputBindingState m_inputBindings;     // 0x35c
};

// SIZE 0x24
class PeridotTraceBase0x24 {
public:
	// SIZE 0x244
	struct Record {
		Record();
		~Record();

		void FUN_0042b2f0(
			undefined4 p_unk0x08,
			undefined4 p_unk0x0c,
			undefined4 p_unk0x10,
			PeridotTraceBase0x24* p_owner
		);
		void Destroy();

		PeridotTraceBase0x24* m_owner; // 0x00
		Record* m_next;                // 0x04
		undefined4 m_unk0x08;          // 0x08
		undefined4 m_unk0x0c;          // 0x0c
		undefined4 m_unk0x10;          // 0x10
		undefined m_data[0x22d];       // 0x14
		undefined m_unk0x241[0x244 - 0x241];

	private:
		void Initialize();
	};

	// SIZE 0x241
	struct SerializedRecord {
		undefined m_unk0x00[0x14]; // 0x00
		undefined m_data[0x22d];   // 0x14
	};

	PeridotTraceBase0x24();
	~PeridotTraceBase0x24();

	Record* FUN_0042b880();
	undefined4 GetUnk0x00() const { return m_unk0x00; }
	LegoBool32 HasUnk0x04() const { return m_unk0x04 != 0; }
	undefined4 GetUnk0x20() const { return m_unk0x20; }
	void Destroy();

private:
	void Initialize();
	void FUN_0042b720(LegoU32 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	void FUN_0042b7f0();
	void FUN_0042b830();

	friend class PeridotTrace0x4a8;
	friend class PeridotTrace0x4e0;

	LegoU32 m_unk0x00;    // 0x00
	Record* m_unk0x04;    // 0x04
	undefined4 m_unk0x08; // 0x08
	undefined4 m_unk0x0c; // 0x0c
	undefined4 m_unk0x10; // 0x10
	Record* m_unk0x14;    // 0x14
	Record* m_unk0x18;    // 0x18
	LegoU32 m_unk0x1c;    // 0x1c
	undefined4 m_unk0x20; // 0x20
};

// SIZE 0x4a8
class PeridotTrace0x4a8 : public PeridotTraceBase0x24 {
public:
	PeridotTrace0x4a8();
	~PeridotTrace0x4a8();

	LegoU8* GetUnk0x24() { return m_unk0x24; }
	void FUN_004426d0(undefined4, undefined4, undefined4);
	undefined4 FUN_00442770(GolFile& p_file);
	void FUN_00442a00(PeridotTracePersistentState* p_state);
	void FUN_00442c20(PeridotTracePersistentState* p_state);
	undefined4 FUN_004439b0();

private:
	enum {
		c_traceScoreRecordsOffset = 0x09,
		c_traceScoreRecordSize = 0x40,
		c_tracePersistentHeaderOffset = 0x349,
		c_traceInputBindingHeaderOffset = 0x361,
		c_traceInputBindingEntryOffset = 0x369,
		c_traceInputBindingEntrySize = 0x27,
		c_inputBindingHeaderSize = 8,
	};

	LegoU8 m_unk0x24[0x4a4 - 0x24]; // 0x24
	undefined4 m_unk0x4a4;
};

// VTABLE: LEGORACERS 0x004b0fac
// SIZE 0x30
class PeridotTraceActionFile0x30 : public GolFile {
public:
	~PeridotTraceActionFile0x30() override; // vtable+0x18

	enum {
		c_unk0x08Flag0x01 = 1 << 0,
	};

	LegoS32 BufferedOpen(const LegoChar* p_fileName, LegoS32 p_mode, LegoU32 p_bufferSize) override; // vtable+0x1c
	LegoS32 Dispose() override;                                                                      // vtable+0x20

	LegoBool32 HasUnk0x08Flag0x01() const { return m_flags & c_unk0x08Flag0x01; }

	// SYNTHETIC: LEGORACERS 0x0044e110
	// PeridotTraceActionFile0x30::`scalar deleting destructor'
};

// VTABLE: LEGORACERS 0x004b1288
// SIZE 0x34
class PeridotTraceActionBase0x34 : public PeridotTraceActionFile0x30 {
public:
	PeridotTraceActionBase0x34();

	// SYNTHETIC: LEGORACERS 0x00450e70 FOLDED
	// PeridotTraceActionBase0x34::~PeridotTraceActionBase0x34

	// SYNTHETIC: LEGORACERS 0x00450e50 FOLDED
	// PeridotTraceActionBase0x34::`scalar deleting destructor'

private:
	undefined4 m_unk0x30; // 0x30
};

// VTABLE: LEGORACERS 0x004b0ba4
// SIZE 0x34
class PeridotTraceAction0x34 : public PeridotTraceActionBase0x34 {
public:
	// SYNTHETIC: LEGORACERS 0x00450e70 FOLDED
	// PeridotTraceAction0x34::~PeridotTraceAction0x34

	// SYNTHETIC: LEGORACERS 0x00450e50 FOLDED
	// PeridotTraceAction0x34::`scalar deleting destructor'
};

// SIZE 0x4e0
class PeridotTrace0x4e0 : public PeridotTrace0x4a8 {
public:
	PeridotTrace0x4e0();
	~PeridotTrace0x4e0();

	LegoBool32 HasUnk0x4b4Flag0x01() const { return !m_unk0x4a8->HasUnk0x04() && m_unk0x4ac.HasUnk0x08Flag0x01(); }

	void FUN_004438a0(
		PeridotTraceRootEntry0x10* p_entry,
		undefined4 p_count,
		undefined4 p_unk0x0c,
		undefined4 p_unk0x10
	);
	void FUN_004438e0();
	undefined4 FUN_00443910();
	undefined4 FUN_00443940();
	undefined4 FUN_00443980();

private:
	PeridotTraceRootEntry0x10* m_unk0x4a8; // 0x4a8
	PeridotTraceAction0x34 m_unk0x4ac;     // 0x4ac
};

// SIZE 0x438
class PeridotTraceState0x438 {
public:
	PeridotTraceState0x438();
	~PeridotTraceState0x438();

	void Initialize(InputManager* p_inputManager);
	void Reset();
	void InitializeInputBindings(InputManager* p_inputManager);
	void FUN_0042eb60(PeridotTrace0x4a8*, undefined4);
	void FUN_0042ef80(PeridotTrace0x4a8*);
	void SetLanguageResourcePath();
	void FUN_0042f020(const DisplayDriverGuid& p_guid);
	void FUN_0042f060(DisplayDriverGuid& p_guid);
	void FUN_0042f200(LegoU8 p_unk0x04);
	LegoBool32 FUN_0042f250(LegoU32 p_unk0x04);
	LegoBool32 FUN_0042f280() const;
	LegoBool32 FUN_0042f310(LegoU32 p_unk0x04, LegoBool32 p_unk0x08, LegoU32 p_unk0x0c, GolString* p_string);

	void SetUnk0x00(undefined4 p_arg1) { m_unk0x00 = p_arg1; }
	void SetLanguageIndex(LegoU8 p_languageIndex) { m_state.m_languageIndex = p_languageIndex; }
	undefined4 GetUnk0x00() const { return m_unk0x00; }
	undefined4 GetUnk0x04() const { return m_unk0x04; }
	LegoU8 GetUnk0x0c() const { return m_state.m_unk0x0c; }
	LegoU8 GetUnk0x1f() const { return m_state.m_unk0x1f; }
	LegoU8 GetUnk0x20() const { return m_state.m_unk0x20; }
	LegoU8 GetUnk0x21() const { return m_state.m_unk0x21; }
	LegoU32 GetLanguageIndex() const { return m_state.m_languageIndex; }
	LegoU8 GetUnk0x22() const { return GetLanguageIndex(); }
	LegoU8 GetUnk0x23() const { return m_state.m_unk0x23; }
	LegoU8 FUN_0042f1f0() const;

private:
	enum {
		c_joystickBindingCount = 2,
		c_keyboardBindingStart = 2,
		c_inputBindingEntryCount = 5,
		c_inputBindingEventCount = 9,
		c_joystickDeviceType = 4,
		c_axisJoystickDeviceSubType = 4,
	};

	void Initialize();
	void FUN_0042ea50(LegoU32 p_playerIndex);
	LegoU32 FUN_0042eac0(LegoU32 p_playerIndex);
	void FUN_0042eb20(LegoU32 p_playerIndex, LegoU32 p_entryIndex);
	LegoBool32 FUN_0042ed10(LegoU32 p_entryIndex, LegoU32 p_event);
	LegoU32 FUN_0042ed80(LegoU32 p_playerIndex, LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	void FUN_0042ee10(LegoU32 p_playerIndex, LegoU32 p_entryIndex, PeridotTraceInputBindingEntry* p_entry);
	void FUN_0042ee70(LegoU32 p_entryIndex, LegoU32 p_eventIndex, LegoU32 p_event);
	LegoU32 FUN_0042ef00(LegoU32 p_entryIndex, LegoU32 p_eventIndex);
	LegoU32 GetRegistryLanguageIndex();

	undefined4 m_unk0x00;                // 0x00
	undefined4 m_unk0x04;                // 0x04
	InputManager* m_inputManager;        // 0x08
	PeridotTracePersistentState m_state; // 0x0c
};

// SIZE 0x250
class PeridotTraceBuffer0x250 : public PeridotTraceBase0x24::Record {
public:
	static void CopyStringToBuffer(GolString* p_string, LegoU8* p_dest, LegoU32 p_count);

	void Reset() { m_unk0x244 = 0; }

private:
	undefined4 m_unk0x244;               // 0x244
	undefined m_unk0x248[0x250 - 0x248]; // 0x248
};

#endif // PERIDOTTRACE0X4E0_H
