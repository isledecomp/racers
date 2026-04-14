#ifndef GOL_VECTOR_H
#define GOL_VECTOR_H

#include "types.h"

template <typename T>
class GolVector {
	GolVector()
	{
		m_size = 0;
		m_data = NULL;
	}
	~GolVector() { Clear(); }

	void Clear()
	{
		LegoU32 i;

		for (i = 0; i < m_size; i++) {
			m_data[i].Clear();
		}
	}

	LegoU32 m_size;
	T* m_data;
};

#endif // GOL_VECTOR_H
