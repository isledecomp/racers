#ifndef DISPLAYDRIVERGUID_H
#define DISPLAYDRIVERGUID_H

#include "types.h"

#include <windows.h>

// SIZE 0x10
union DisplayDriverGuid {
	enum {
		c_wordCount = sizeof(GUID) / sizeof(LegoU32),
	};

	// SIZE 0x04
	struct SerializedWord {
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
	struct Serialized {
		SerializedWord m_words[c_wordCount]; // 0x00
	};

	GUID m_guid;
	LegoU32 m_words[c_wordCount];

	const LegoU32* GetWords() const { return m_words; }
	LegoU32* GetWords() { return m_words; }
};

#endif // DISPLAYDRIVERGUID_H
