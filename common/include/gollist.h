#ifndef GOLLIST_H
#define GOLLIST_H

#include "types.h"

// SIZE 0x08
struct GolListLink {
	GolListLink()
	{
		m_prev = this;
		m_next = this;
	}

	GolListLink* m_prev; // 0x00
	GolListLink* m_next; // 0x04
};

// SIZE 0x0c
struct GolListHead {
	struct Sentinel {
		GolListLink* m_prev; // 0x00
		GolListLink* m_next; // 0x04
	};

	GolListHead()
	{
		m_sentinel.m_next = (GolListLink*) &m_first;
		m_first = (GolListLink*) &m_sentinel;
		m_sentinel.m_prev = NULL;
	}

	GolListLink* m_first; // 0x00
	Sentinel m_sentinel;  // 0x04
};

#endif // GOLLIST_H
