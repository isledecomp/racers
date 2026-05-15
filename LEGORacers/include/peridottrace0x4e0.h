#ifndef PERIDOTTRACE0X4E0_H
#define PERIDOTTRACE0X4E0_H

#include "decomp.h"
#include "displaydriverguid.h"
#include "types.h"

#include <string.h>

class GolFile;
class GolString;
class InputManager;
class PeridotTraceBuffer0x250;
class PeridotTrace0x4e0;

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

		PeridotTraceBase0x24* m_owner; // 0x00
		Record* m_next;                // 0x04
		undefined4 m_unk0x08;          // 0x08
		undefined4 m_unk0x0c;          // 0x0c
		undefined4 m_unk0x10;          // 0x10
		undefined m_data[0x22d];       // 0x14
		undefined m_unk0x241[0x244 - 0x241];

	private:
		void Initialize();
		void Destroy();
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

private:
	void Initialize();
	void Destroy();
	void FUN_0042b720(LegoU32 p_count, undefined4 p_unk0x08, undefined4 p_unk0x0c);
	void FUN_0042b7f0();
	void FUN_0042b830();

	friend class PeridotTrace0x4a8;

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

	undefined* GetUnk0x24() { return m_unk0x24; }
	void FUN_004426d0(undefined4, undefined4, undefined4);
	undefined4 FUN_00442770(GolFile& p_file);
	void FUN_00442c20(void* p_unk0x04);
	undefined4 FUN_004439b0();

private:
	undefined m_unk0x24[0x4a4 - 0x24]; // 0x24
	undefined4 m_unk0x4a4;
};

// SIZE 0x34
class PeridotTraceActionBase0x34 {
public:
	PeridotTraceActionBase0x34();
	~PeridotTraceActionBase0x34();

	enum {
		c_unk0x08Flag0x01 = 1 << 0,
	};

	LegoBool32 HasUnk0x08Flag0x01() const { return m_unk0x08 & c_unk0x08Flag0x01; }

private:
	undefined4 m_unk0x00;             // 0x00
	undefined4 m_unk0x04;             // 0x04
	LegoU32 m_unk0x08;                // 0x08
	undefined m_unk0x0c[0x34 - 0x0c]; // 0x0c
};

// SIZE 0x34
class PeridotTraceAction0x34 : public PeridotTraceActionBase0x34 {};

// SIZE 0x4e0
class PeridotTrace0x4e0 : public PeridotTrace0x4a8 {
public:
	PeridotTrace0x4e0();
	~PeridotTrace0x4e0();

	LegoBool32 HasUnk0x4b4Flag0x01() const { return !m_unk0x4a8->HasUnk0x04() && m_unk0x4ac.HasUnk0x08Flag0x01(); }

	void FUN_004438e0();
	undefined4 FUN_00443910();
	undefined4 FUN_00443940();
	undefined4 FUN_00443980();

private:
	PeridotTrace0x4a8* m_unk0x4a8;     // 0x4a8
	PeridotTraceAction0x34 m_unk0x4ac; // 0x4ac
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
	undefined4 GetUnk0x00() const { return m_unk0x00; }
	undefined4 GetUnk0x04() const { return m_unk0x04; }
	LegoU8 GetUnk0x0c() const { return m_state.m_unk0x0c; }
	LegoU8 GetUnk0x1f() const { return m_state.m_unk0x1f; }
	LegoU8 GetUnk0x20() const { return m_state.m_unk0x20; }
	LegoU8 GetUnk0x21() const { return m_state.m_unk0x21; }
	LegoU8 GetLanguageIndex() const { return m_state.m_languageIndex; }
	LegoU8 GetUnk0x22() const { return GetLanguageIndex(); }
	LegoU8 GetUnk0x23() const { return m_state.m_unk0x23; }
	LegoU8 FUN_0042f1f0() const;

private:
	// SIZE 0x04
	struct SerializedGuidWord {
		void Set(const LegoU32& p_word)
		{
			m_byte0 = static_cast<LegoU8>(p_word);
			m_byte1 = static_cast<LegoU8>(p_word >> 8);
			m_byte2 = static_cast<LegoU8>(p_word >> 16);
			m_byte3 = static_cast<LegoU8>(p_word >> 24);
		}

		LegoU32 Get() const { return (m_byte3 << 24) + (m_byte2 << 16) + (m_byte1 << 8) + m_byte0; }

		LegoU8 m_byte0; // 0x00
		LegoU8 m_byte1; // 0x01
		LegoU8 m_byte2; // 0x02
		LegoU8 m_byte3; // 0x03
	};

	// SIZE 0x10
	struct SerializedGuid {
		SerializedGuidWord m_words[sizeof(GUID) / sizeof(LegoU32)]; // 0x00
	};

	// SIZE 0x28
	struct InputBindingEntry {
		LegoU8 m_deviceType;    // 0x00
		LegoU8 m_deviceSubType; // 0x01
		LegoU8 m_unk0x02;       // 0x02
		undefined m_unk0x03;    // 0x03
		LegoU32 m_events[9];    // 0x04
	};

	// SIZE 0xd0
	struct InputBindingState {
		LegoU8 m_unk0x00;               // 0x00
		LegoU8 m_unk0x01;               // 0x01
		LegoU8 m_unk0x02;               // 0x02
		LegoU8 m_unk0x03;               // 0x03
		LegoU8 m_unk0x04;               // 0x04
		LegoU8 m_unk0x05;               // 0x05
		LegoU8 m_unk0x06;               // 0x06
		LegoU8 m_unk0x07;               // 0x07
		InputBindingEntry m_entries[5]; // 0x08
	};

	// SIZE 0x42c
	struct PersistentState {
		void Clear() { ::memset(this, 0, sizeof(*this)); }

		LegoU8 m_unk0x0c;                   // 0x000
		SerializedGuid m_displayDriverGuid; // 0x001
		undefined m_unk0x1d;                // 0x011
		undefined m_unk0x1e;                // 0x012
		LegoU8 m_unk0x1f;                   // 0x013
		LegoU8 m_unk0x20;                   // 0x014
		LegoU8 m_unk0x21;                   // 0x015
		LegoU8 m_languageIndex;             // 0x016
		undefined m_unk0x23;                // 0x017
		LegoU8 m_unk0x24;                   // 0x018
		LegoU8 m_unk0x25;                   // 0x019
		LegoU16 m_unk0x26;                  // 0x01a
		LegoU32 m_unk0x28[13];              // 0x01c
		LegoU32 m_unk0x5c[13];              // 0x050
		undefined2 m_unk0x90[13][14];       // 0x084
		undefined2 m_unk0x1fc[13][14];      // 0x1f0
		InputBindingState m_inputBindings;  // 0x35c
	};

	void Initialize();
	LegoU32 GetRegistryLanguageIndex();

	undefined4 m_unk0x00;         // 0x00
	undefined4 m_unk0x04;         // 0x04
	InputManager* m_inputManager; // 0x08
	PersistentState m_state;      // 0x0c
};

// SIZE 0x250
class PeridotTraceBuffer0x250 : public PeridotTraceBase0x24::Record {
public:
	static void CopyStringToBuffer(GolString* p_string, undefined2* p_dest, LegoU32 p_count);

	void Reset() { m_unk0x244 = 0; }

private:
	undefined4 m_unk0x244;               // 0x244
	undefined m_unk0x248[0x250 - 0x248]; // 0x248
};

#endif // PERIDOTTRACE0X4E0_H
