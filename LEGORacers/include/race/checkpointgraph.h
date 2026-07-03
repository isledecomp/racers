#ifndef CHECKPOINTGRAPH_H
#define CHECKPOINTGRAPH_H

#include "golmath.h"
#include "goltxtparser.h"
#include "types.h"

class GolFileParser;

// SIZE 0x08
class CheckpointGraph {
public:
	// VTABLE: LEGORACERS 0x004afef4
	// SIZE 0x1fc
	class CpbTxtParser : public GolTxtParser {
	public:
		// .cpb token meanings
		enum {
			e_checkpoint = 0x27,
			e_plane = 0x28,
			e_nextIndices = 0x29,
			e_position = 0x2a,
		};
	};

	// SIZE 0x24
	class Entry {
	public:
		// SIZE 0x04
		union NextIndices {
			LegoU32 m_all;     // 0x00
			LegoU8 m_items[4]; // 0x00
		};

		Entry();
		~Entry();

	private:
		friend class CheckpointGraph;

		void Reset();
		void Destroy();
		void Load(GolFileParser* p_parser, LegoBool32 p_mirror);

	public:
		GolVec3 m_planeNormal;     // 0x00
		LegoFloat m_planeDistance; // 0x0c
		GolVec3 m_position;        // 0x10
		LegoFloat m_lapFraction;   // 0x1c
		NextIndices m_next;        // 0x20
	};

	CheckpointGraph();
	~CheckpointGraph();

	void Reset();
	void Load(const LegoChar* p_name, LegoBool32 p_binary, LegoBool32 p_mirror);
	Entry* GetCheckpoint(LegoU32 p_index);
	void ComputeLapFractions();
	LegoU32 CountLapCheckpoints();
	LegoU32 FindNextFractionedCheckpoint(LegoU32 p_startIndex, LegoU32* p_stepCount);
	void AdvanceAlongGraph(GolVec3* p_position, LegoFloat p_distance, Entry* p_entry);

private:
	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // CHECKPOINTGRAPH_H
