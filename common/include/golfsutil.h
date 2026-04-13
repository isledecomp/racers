#ifndef GOLFSUTIL_H
#define GOLFSUTIL_H

struct GolImport;

#ifdef BUILDING_LEGORACERS
extern void CreateGolImport(GolImport* p_import);
#endif

#ifdef BUILDING_GOL
extern void SetGolImport(GolImport* p_import);
#endif

void GolFsLock();
void GolFsUnlock();

#endif // GOLFSUTIL_H
