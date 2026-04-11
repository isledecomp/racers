#ifndef GOLDP_ADAPTER_H
#define GOLDP_ADAPTER_H

#include "gol.h"

extern void SetGolImport(GolImport* p_import);

extern void LockGlobalMutex();

extern void ReleaseGlobalMutex();

extern void DetectCPU();
;

#endif // GOLDP_ADAPTER_H
