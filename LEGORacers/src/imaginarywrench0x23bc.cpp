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
}

// STUB: LEGORACERS 0x0047b070
void ImaginaryWrench0x23bc::VTable0x68()
{
	// TODO
	STUB(0x47b070);
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
void ImaginaryWrench0x23bc::VTable0x8c()
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
	// TODO
	char buf[12];
	m_unk0x23a8.CopyToString(buf);
	buf[11] = '\0'; // ?

	for (LegoS32 i = 0; i < sizeOfArray(g_cheatNames); i++) {
		if (strcmp(buf, g_cheatNames[i]) == 0) {
			LegoU32 flag = 1 << i;

			if ((*m_unk0x354)->m_unk0x20 & flag) {
				(*m_unk0x354)->m_unk0x20 &= ~flag;
				continue;
			}

			(*m_unk0x354)->m_unk0x20 |= flag;

			switch (flag) {
			case 1:
				break;

			case 2:
				break;

			case 4:
				(*m_unk0x354)->m_unk0x20 &= 0xffffffa7;
				break;

			case 8:
				(*m_unk0x354)->m_unk0x20 &= 0xffffffab;
				break;

			case 16:
				(*m_unk0x354)->m_unk0x20 &= 0xffffffb3;
				break;

			case 32:
				break;

			case 64:
				(*m_unk0x354)->m_unk0x20 &= 0xffffff63;
				break;

			case 128:
				(*m_unk0x354)->m_unk0x20 &= 0xffffffbf;
				break;

			case 256:
				break;

			case 512:
				if (((*m_unk0x354)->m_unk0x20 & 1024)) {
					break;
				}
				if ((*m_unk0x354)->m_unk0x20 & 2048) {
					break;
				}

				(*m_unk0x354)->m_unk0x20 &= 0xfffff7ff;
				break;

			case 1024:
				if (((*m_unk0x354)->m_unk0x20 & 512) == 0 && ((*m_unk0x354)->m_unk0x20 & 2048) == 0) {
					(*m_unk0x354)->m_unk0x20 &= 0xfffffdff;
				}
				break;

			case 2048:
				if (((*m_unk0x354)->m_unk0x20 & 1024) == 0 && ((*m_unk0x354)->m_unk0x20 & 512) == 0) {
					(*m_unk0x354)->m_unk0x20 &= 0xfffffbff;
				}
				break;
			}
		}

		(*m_unk0x354)->m_unk0x20 = 0;
	}
}

// STUB: LEGORACERS 0x0047bbf0
void ImaginaryWrench0x23bc::VTable0x90(undefined4)
{
	// TODO
	STUB(0x47bbf0);
}
