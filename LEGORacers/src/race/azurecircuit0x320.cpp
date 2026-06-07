#include "race/azurecircuit0x320.h"

DECOMP_SIZE_ASSERT(AzureCircuit0x320, 0x320)
DECOMP_SIZE_ASSERT(AzureCircuit0x320::Entry0xe34, 0xe34)
DECOMP_SIZE_ASSERT(AzureCircuit0x320::Field0x318, 0xdbc)

// FUNCTION: LEGORACERS 0x0043beb0
void AzureCircuit0x320::FUN_0043beb0(LegoRacers::Context* p_context)
{
	LegoU32 bestScore = c_invalidScore;
	LegoU32 bestSum = c_invalidScore;
	LegoU32 bestIndex = c_invalidScore;
	LegoU32 entryCount = m_unk0x144;

	if (entryCount > 0) {
		LegoU32 entryIndex;

		entryIndex = 0;
		do {
			if (!p_context->m_playerSetupSlots[entryIndex].m_unk0x10) {
				Entry0xe34* entry = &m_unk0x140[entryIndex];
				LegoU32 scoreCount = m_unk0x29c;
				if (scoreCount <= entry->m_unk0xce4) {
					if (scoreCount) {
						LegoU32 remaining = scoreCount;
						LegoU32 sum = 0;
						LegoU32* scores = entry->m_unk0xcec;

						do {
							LegoU32 score = *scores;
							if (score < bestScore) {
								bestScore = score;
								bestIndex = entryIndex;
							}
							sum += score;
							scores++;
						} while (--remaining);

						if (sum < bestSum) {
							bestSum = sum;
						}
					}
					else if (0 < bestSum) {
						bestSum = 0;
					}
				}
			}

			entryIndex++;
		} while (entryIndex < entryCount);
	}

	if (bestScore < c_invalidScore) {
		LegoU32* score = &p_context->m_unk0x98[p_context->m_unk0xd8];
		if (!*score || bestScore <= *score) {
			*score = bestScore;
			p_context->m_unk0xa8[p_context->m_unk0xd8] = bestIndex;
		}
	}

	if (bestSum < c_invalidScore) {
		LegoU32* sum = &p_context->m_unk0xb8[p_context->m_unk0xd8];
		if (!*sum || bestSum <= *sum) {
			*sum = bestSum;
			p_context->m_unk0xc8[p_context->m_unk0xd8] = bestIndex;
		}
	}
}
