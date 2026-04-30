#ifndef MITHRILCHAIN0X8_H
#define MITHRILCHAIN0X8_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;

// SIZE 0x8
class MithrilChain0x8 {
public:
	// SIZE 0x18
	class Entry {
	public:
		enum {
			c_flagActive = 0x01,
			c_flagLooping = 0x02,
			c_flagExpired = 0x04,
		};

		Entry();
		~Entry();

		void Reset();
		void Deactivate();
		void Update(LegoU32 p_elapsedMs);
		void Draw(BronzeFalcon0xc8770* p_renderer);
		LegoBool IsActive() { return m_flags & c_flagActive; }

	private:
		void Clear();

		undefined4 m_unk0x00;   // 0x00
		undefined4 m_unk0x04;   // 0x04
		undefined m_unk0x08[4]; // 0x08
		LegoU32 m_remainingMs;  // 0x0c
		LegoU32 m_durationMs;   // 0x10
		LegoU8 m_flags;         // 0x14
		undefined m_unk0x15[3]; // 0x15
	};

	MithrilChain0x8();
	~MithrilChain0x8();
	void Allocate(LegoU32 p_count);
	void Update(LegoU32 p_elapsedMs);
	void Draw(BronzeFalcon0xc8770* p_renderer);

private:
	void Reset();

	Entry* m_entries; // 0x00
	LegoU32 m_count;  // 0x04
};

#endif // MITHRILCHAIN0X8_H
