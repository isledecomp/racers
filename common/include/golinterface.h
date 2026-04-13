#ifndef GOLINTERFACE_H
#define GOLINTERFACE_H

#include "gol.h"

#ifdef BUILDING_LEGORACERS
extern void CreateGolImport(GolImport* p_import);
#endif

#ifdef BUILDING_GOL
extern void SetGolImport(GolImport* p_import);
#endif

extern void LockGlobalMutex();

extern void ReleaseGlobalMutex();

#endif // GOLERROR_H
