#ifndef DISPLAYDRIVERGUID_H
#define DISPLAYDRIVERGUID_H

#include "types.h"

#include <windows.h>

// SIZE 0x10
union DisplayDriverGuid {
	enum {
		c_wordCount = sizeof(GUID) / sizeof(LegoU32),
	};

	GUID m_guid;
	LegoU32 m_words[c_wordCount];

	const LegoU32* GetWords() const { return m_words; }
	LegoU32* GetWords() { return m_words; }
};

#endif // DISPLAYDRIVERGUID_H
