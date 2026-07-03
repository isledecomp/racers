#ifndef SAVERECORDLIST_H
#define SAVERECORDLIST_H

#include "decomp.h"
#include "golname.h"
#include "types.h"

class GolString;
class SaveGame;
struct DriverCosmetics;

typedef undefined SaveRecordData[0x22d];

// SIZE 0x24
class SaveRecordList {
public:
	// SIZE 0x244
	struct Record {
		Record();
		~Record();

		void Initialize(LegoU32 p_recordSource, LegoU32 p_saveIndex, LegoU32 p_recordId, SaveRecordList* p_owner);
		void Destroy();
		void MarkDirty();
		void GetCosmetics(DriverCosmetics* p_cosmetics) const;
		void CopyCarData(LegoU8* p_dest) const;
		void GetChassisName(GolName p_dest) const;
		void GetName(GolString* p_string) const;
		void GetName(LegoChar* p_dest) const;
		LegoBool32 IsCarSaved() const;
		void MarkCarSaved();
		void MarkCarModified();
		void SetCosmetics(const DriverCosmetics* p_cosmetics);
		void SetChassisName(const GolName p_source);
		void SetName(GolString* p_string);
		void CopyFrom(const Record* p_source);
		void SetRecordId(LegoU32 p_recordId);
		LegoU32 GetTrophy(undefined4 p_raceIndex) const;
		LegoBool32 SetTrophy(LegoU32 p_raceIndex, LegoU32 p_trophy);
		LegoU8* GetCarData() { return &m_data[0x29]; }
		const LegoU8* GetCarData() const { return &m_data[0x29]; }

		SaveRecordList* m_owner;             // 0x00
		Record* m_next;                      // 0x04
		LegoU32 m_recordSource;              // 0x08
		LegoU32 m_saveIndex;                 // 0x0c
		LegoU32 m_recordId;                  // 0x10
		SaveRecordData m_data;               // 0x14
		undefined m_unk0x241[0x244 - 0x241]; // 0x241

	private:
		void Initialize();
	};

	// SIZE 0x241
	struct SerializedRecord {
		undefined m_unk0x00[0x14]; // 0x00
		SaveRecordData m_data;     // 0x14
	};

	SaveRecordList();
	~SaveRecordList();

	Record* AllocateRecord();
	Record* AllocateRecordCopy(Record* p_record);
	void RemoveRecord(Record* p_record);
	Record* GetRecord(LegoU32 p_index);
	Record* FindRecordById(undefined4 p_recordId);
	LegoU32 GetRecordCount() const { return m_recordCount; }
	LegoBool32 HasRecords() const { return m_records != 0; }
	LegoS32 GetAvailableRecordCount() const { return m_recordCapacity - m_recordCount; }
	LegoBool32 IsDirty() const { return m_dirty; }
	void Destroy();

private:
	friend struct Record;
	friend class SaveGame;

	void Initialize();
	void AllocateRecords(LegoU32 p_count, undefined4 p_recordSource, undefined4 p_saveIndex);
	void FreeRecords();
	void RebuildFreeList();

	LegoU32 m_recordCount;     // 0x00
	Record* m_records;         // 0x04
	undefined4 m_recordSource; // 0x08
	LegoU32 m_saveIndex;       // 0x0c
	undefined4 m_unk0x10;      // 0x10
	Record* m_freeRecords;     // 0x14
	Record* m_usedRecords;     // 0x18
	LegoU32 m_recordCapacity;  // 0x1c
	LegoBool32 m_dirty;        // 0x20
};

#endif // SAVERECORDLIST_H
