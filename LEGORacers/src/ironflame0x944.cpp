#include "ironflame0x944.h"

#include "../../GolDP/include/gol.h"
#include "gol.h"
#include "golerror.h"
#include "golfsutil.h"

#include <stdio.h>

DECOMP_SIZE_ASSERT(IronFlame0x944, 0x944)

// FUNCTION: LEGORACERS 0x004164d0
IronFlame0x944::IronFlame0x944()
{
	m_golLibrary = NULL;
	m_golExport = NULL;
	m_unk0x924 = 0;
	m_golBackendType = c_golBackendDP;
	m_unk0x92c = 0;
	m_unk0x934 = 0;
	m_unk0x93c = 0;
	m_unk0x940 = 0;
	m_unk0x930 = 0;
	m_unk0x938 = 1;
}

// FUNCTION: LEGORACERS 0x00416580
IronFlame0x944::~IronFlame0x944()
{
	VTable0x10();
}

// STUB: LEGORACERS 0x004165e0
void IronFlame0x944::VTable0x0c(const LegoChar*, const LegoChar*)
{
	// TODO
	STUB(0x4165e0);
}

// STUB: LEGORACERS 0x004167b0
void IronFlame0x944::VTable0x2c()
{
	// TODO
	STUB(0x4167b0);
}

// STUB: LEGORACERS 0x004167e0
void IronFlame0x944::VTable0x10()
{
	// TODO
	STUB(0x4167e0);
}

// FUNCTION: LEGORACERS 0x00416960
void IronFlame0x944::VTable0x14()
{
	LegoChar buffer[100];
	GolImport golImport;

	if (m_golBackendType & c_golBackendGlide) {
		m_golLibrary = LoadLibraryA("GolGlide.DLL");
	}
	else if (m_golBackendType & c_golBackendSoft) {
		m_golLibrary = LoadLibraryA("GolSoft.DLL");
	}
	else if (m_golBackendType & c_golBackendD3D) {
		m_golLibrary = LoadLibraryA("GolD3D.DLL");
	}
	else {
		m_golLibrary = LoadLibraryA("GolDP.DLL");
	}
	if (m_golLibrary == NULL) {
		sprintf(buffer, "Unable to find a valid Gol DLL\nError Code = %d", GetLastError());
		GOL_FATALERROR_MESSAGE(buffer);
	}
	GolEntryCBFN* golEntry = (GolEntryCBFN*) GetProcAddress(m_golLibrary, "GolEntry");
	if (golEntry == NULL) {
		GOL_FATALERROR_MESSAGE("Invalid Gol DLL - cannot call entry procedure");
	}
	CreateGolImport(&golImport);
	golImport.m_fatalErrorMessage = GolFatalErrorMessage;
	m_golExport = golEntry(&golImport);
	m_golDrawState = m_golExport->VTable0x04();
}

// STUB: LEGORACERS 0x00416a30
void IronFlame0x944::VTable0x18()
{
	// TODO
	STUB(0x416a30);
}

// STUB: LEGORACERS 0x00416a90
void IronFlame0x944::VTable0x1c()
{
	// TODO
	STUB(0x416a90);
}

// STUB: LEGORACERS 0x00416ab0
void IronFlame0x944::VTable0x20()
{
	// TODO
	STUB(0x416ab0);
}

// STUB: LEGORACERS 0x00416ac0
void IronFlame0x944::VTable0x28()
{
	// TODO
	STUB(0x416ac0);
}

// STUB: LEGORACERS 0x00416b00
void IronFlame0x944::VTable0x24()
{
	// TODO
	STUB(0x416b00);
}

// STUB: LEGORACERS 0x00416cd0
void IronFlame0x944::VTable0x30()
{
	// TODO
	STUB(0x416cd0);
}

// STUB: LEGORACERS 0x00416ef0
void IronFlame0x944::VTable0x34()
{
	// TODO
	STUB(0x416ef0);
}

// STUB: LEGORACERS 0x00417900
void IronFlame0x944::VTable0x00()
{
	// TODO
	STUB(0x417900);
}
