#include "audio/crimsonray0x20.h"

#include "types.h"

DECOMP_SIZE_ASSERT(OpalStar0x20, 0x20)
DECOMP_SIZE_ASSERT(CrimsonRay0x20, 0x20)

// FUNCTION: LEGORACERS 0x0041a9d0 FOLDED
void CrimsonRay0x20::VTable0x14(AmberLeaf0x10* p_node)
{
	delete p_node;
}

// FUNCTION: LEGORACERS 0x0041a9f0 FOLDED
void* CrimsonRay0x20::VTable0x18()
{
	return m_unk0x10;
}

// FUNCTION: LEGORACERS 0x0041c010
CrimsonRay0x20::CrimsonRay0x20()
{
	m_unk0x10 = NULL;
}

// FUNCTION: LEGORACERS 0x0041c070
CrimsonRay0x20::~CrimsonRay0x20()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0041c0c0
GolListLink* CrimsonRay0x20::VTable0x04(undefined4)
{
	return VTable0x08();
}

// FUNCTION: LEGORACERS 0x0041c0d0
GolListLink* CrimsonRay0x20::VTable0x08()
{
	GolListLink* result;

	while (TRUE) {
		result = m_unk0x14.LastLink();

		if (!m_unk0x14.IsValidLastLink(result)) {
			break;
		}

		VTable0x14(&m_unk0x14.GetItem(*result));
	}

	m_unk0x04 = 0;
	return result;
}

// FUNCTION: LEGORACERS 0x0041c100
AmberLeaf0x10* CrimsonRay0x20::VTable0x10(undefined4)
{
	AmberLeaf0x10* node = new AmberLeaf0x10();

	if (node) {
		node->SetUnk0x0c(this);
		m_unk0x14.Append(node);
	}

	return node;
}

// FUNCTION: LEGORACERS 0x0044a1e0 FOLDED
undefined4 CrimsonRay0x20::VTable0x0c()
{
	return 1;
}
