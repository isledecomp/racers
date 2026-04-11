#ifndef LIST_H
#define LIST_H

#include "types.h"

// SIZE 0x08
struct ListLink {
	ListLink()
	{
		m_prev = this;
		m_next = this;
	}

	ListLink* m_prev; // 0x00
	ListLink* m_next; // 0x04
};

// SIZE 0x0c
struct ListHead {
	struct Sentinel {
		ListLink* m_prev; // 0x00
		ListLink* m_next; // 0x04
	};

	ListHead()
	{
		m_sentinel.m_next = (ListLink*) &m_first;
		m_first = (ListLink*) &m_sentinel;
		m_sentinel.m_prev = NULL;
	}

	ListLink* m_first;   // 0x00
	Sentinel m_sentinel; // 0x04
};

#endif // LIST_H
