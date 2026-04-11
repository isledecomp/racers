#ifndef LIST_H
#define LIST_H

// SIZE 0x08
struct ListLink {
	ListLink* m_prev; // 0x00
	ListLink* m_next; // 0x04
};

// SIZE 0x0c
struct ListHead {
	ListLink* m_first;   // 0x00
	ListLink m_sentinel; // 0x04
};

#endif // LIST_H
