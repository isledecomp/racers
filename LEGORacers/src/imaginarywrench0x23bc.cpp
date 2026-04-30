#include "imaginarywrench0x23bc.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ImaginaryWrench0x23bc, 0x23bc)

// GLOBAL: LEGORACERS 0x004c1ff4
const LegoChar* g_cheatNames[] = {
	"NSLWJ",
	"FLYSKYHGH",
	"PGLLRD",
	"PGLLYLL",
	"PGLLGRN",
	"LNFRRRM",
	"RPCRNLY",
	"MXPMX",
	"FSTFRWRD",
	"NWHLS",
	"NCHSSS",
	"NDRVR",
	"NMRCHTS"
};

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryWrench0x23bc::VTable0x44(undefined4)
{
}

// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void ImaginaryWrench0x23bc::VTable0x94(undefined4)
{
}

// STUB: LEGORACERS 0x0047af30
ImaginaryWrench0x23bc::ImaginaryWrench0x23bc()
{
	// TODO
	STUB(0x0047af30);
}

// STUB: LEGORACERS 0x0047b090
ImaginaryWrench0x23bc::~ImaginaryWrench0x23bc()
{
	// TODO
	STUB(0x0047b090);
}

// STUB: LEGORACERS 0x0047b1d0
void ImaginaryWrench0x23bc::VTable0x54()
{
	// TODO
	STUB(0x47b1d0);
}

// STUB: LEGORACERS 0x0047b300
void ImaginaryWrench0x23bc::VTable0x4c(undefined4)
{
	// TODO
	STUB(0x47b300);
}

// STUB: LEGORACERS 0x0047b470
void ImaginaryWrench0x23bc::VTable0x8c(undefined4, undefined4)
{
	// TODO
	STUB(0x47b470);
}

// STUB: LEGORACERS 0x0047b550
void ImaginaryWrench0x23bc::VTable0x74()
{
	// TODO
	STUB(0x47b550);
}

// STUB: LEGORACERS 0x0047b7f0
void ImaginaryWrench0x23bc::VTable0x84()
{
	// TODO
	STUB(0x47b7f0);
}

// STUB: LEGORACERS 0x0047b850
void ImaginaryWrench0x23bc::VTable0x38(undefined4)
{
	// TODO
	STUB(0x47b850);
}

// STUB: LEGORACERS 0x0047b9c0
void ImaginaryWrench0x23bc::VTable0x40(undefined4)
{
	// TODO
	STUB(0x47b9c0);
}

// STUB: LEGORACERS 0x0047b9e0
void ImaginaryWrench0x23bc::VTable0x3c(undefined4)
{
	// TODO
	STUB(0x47b9e0);
}

// FUNCTION: LEGORACERS 0x0047ba00
void ImaginaryWrench0x23bc::FUN_0047ba00()
{
	LegoChar buf[14];
	m_unk0x23a8.CopyToString(buf);
	buf[13] = '\0';

	for (LegoU32 i = 0; i < sizeOfArray(g_cheatNames); ++i) {
		if (strcmp(g_cheatNames[i], buf) == 0) {
			if (i < sizeOfArray(g_cheatNames) - 1) {
				LegoU32 flag = 1 << i;
				LegoU32 current = (*m_unk0x354)->m_unk0x20;

				if (current & flag) {
					(*m_unk0x354)->m_unk0x20 = current & ~flag;
				}
				else {
					(*m_unk0x354)->m_unk0x20 = current | flag;

					switch (flag) {
					case c_pgllrd:
						(*m_unk0x354)->m_unk0x20 &= ~(c_pgllyll | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllyll:
						(*m_unk0x354)->m_unk0x20 &= ~(c_pgllrd | c_pgllgrn | c_rpcrnly);
						break;
					case c_pgllgrn:
						(*m_unk0x354)->m_unk0x20 &= ~(c_pgllrd | c_pgllyll | c_rpcrnly);
						break;
					case c_rpcrnly:
						(*m_unk0x354)->m_unk0x20 &= ~(c_pgllrd | c_pgllyll | c_pgllgrn | c_mxpmx);
						break;
					case c_mxpmx:
						(*m_unk0x354)->m_unk0x20 &= ~c_rpcrnly;
						break;
					case c_nwhls: {
						LegoU32 v = (*m_unk0x354)->m_unk0x20;
						if ((v & c_nchsss) && (v & c_ndrvr)) {
							(*m_unk0x354)->m_unk0x20 = v & ~c_ndrvr;
						}
						break;
					}
					case c_nchsss: {
						LegoU32 v = (*m_unk0x354)->m_unk0x20;
						if ((v & c_nwhls) && (v & c_ndrvr)) {
							(*m_unk0x354)->m_unk0x20 = v & ~c_nwhls;
						}
						break;
					}
					case c_ndrvr: {
						LegoU32 v = (*m_unk0x354)->m_unk0x20;
						if ((v & c_nchsss) && (v & c_nwhls)) {
							(*m_unk0x354)->m_unk0x20 = v & ~c_nchsss;
						}
						break;
					}
					}
				}
			}
			else if (i == sizeOfArray(g_cheatNames) - 1) {
				(*m_unk0x354)->m_unk0x20 = 0;
			}
		}
	}
}

// STUB: LEGORACERS 0x0047bbf0
void ImaginaryWrench0x23bc::VTable0x90(undefined4)
{
	// TODO
	STUB(0x47bbf0);
}
