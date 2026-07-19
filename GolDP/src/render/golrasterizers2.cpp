#include "render/golrasterizers2.h"

#include "decomp.h"

// GLOBAL: GOLDP 0x10057970
float g_unk0x10057970 = 0.000015258789f;

// GLOBAL: GOLDP 0x10057974
float g_unk0x10057974 = 2.3283064E-10f;

// GLOBAL: GOLDP 0x10057978
float g_unk0x10057978 = 6.7553994E+15f;

// GLOBAL: GOLDP 0x10057980
float g_unk0x10057980 = 103079215104.0f;

// GLOBAL: GOLDP 0x10057990
float g_floatConst1 = 1.0f;

// GLOBAL: GOLDP 0x10057998
float g_unk0x10057998 = 0.000015258789f;

// GLOBAL: GOLDP 0x100579a8
float g_unk0x100579a8 = 25165824.0f;

// GLOBAL: GOLDP 0x100579b0
float g_unk0x100579b0 = 5.1539608E+10f;

// GLOBAL: GOLDP 0x100579b4
float g_unk0x100579b4 = 6.4424509E+9f;

// GLOBAL: GOLDP 0x100579b8
float g_unk0x100579b8 = 8.0530637E+8f;

// GLOBAL: GOLDP 0x100579d8
float g_unk0x100579d8 = 1.3421773E+8f;

#ifdef COMPAT_MODE

void FUN_10041a50(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10041a50);
}

void FUN_10041a60(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10041a60);
}

void FUN_10042020(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10042020);
}

void FUN_10042bd0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10042bd0);
}

void FUN_10043420(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10043420);
}

void FUN_10043c60(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10043c60);
}

void FUN_100444a0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x100444a0);
}

void FUN_10044ce0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10044ce0);
}

void FUN_10045520(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10045520);
}

void FUN_10045d60()
{
	STUB(0x10045d60);
}

void FUN_10045db0()
{
	STUB(0x10045db0);
}

void FUN_10045e00()
{
	STUB(0x10045e00);
}

void FUN_10045e50()
{
	STUB(0x10045e50);
}

void FUN_10045ea0()
{
	STUB(0x10045ea0);
}

void FUN_10045ef0()
{
	STUB(0x10045ef0);
}

void FUN_10045f40()
{
	STUB(0x10045f40);
}

void FUN_10045fa0()
{
	STUB(0x10045fa0);
}

void FUN_10046000()
{
	STUB(0x10046000);
}

void FUN_10046060()
{
	STUB(0x10046060);
}

void FUN_100460c0()
{
	STUB(0x100460c0);
}

void FUN_10046120()
{
	STUB(0x10046120);
}

void FUN_10046180()
{
	STUB(0x10046180);
}

void FUN_100461f0()
{
	STUB(0x100461f0);
}

void FUN_10046260()
{
	STUB(0x10046260);
}

void FUN_100462d0()
{
	STUB(0x100462d0);
}

void FUN_10046340()
{
	STUB(0x10046340);
}

void FUN_100463b0()
{
	STUB(0x100463b0);
}

void FUN_10046420(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10046420);
}

void FUN_10046ba0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10046ba0);
}

void FUN_100473f0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x100473f0);
}

void FUN_10047c40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10047c40);
}

void FUN_10048490(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10048490);
}

void FUN_10048d20(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10048d20);
}

void FUN_100495b0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x100495b0);
}

void FUN_10049e40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x10049e40);
}

void FUN_1004a6d0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	STUB(0x1004a6d0);
}

#else

// STUB: GOLDP 0x10041a50
void FUN_10041a50(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	// empty function; cannot get the folding right
	STUB(0x10041a50);
}

// FUNCTION: GOLDP 0x10041a60
__declspec(naked) void FUN_10041a60(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0x98
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0x88], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0x94], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edi
		mov edi, dword ptr [esp + 0xa8]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10041beb
		cmp edx, ebp
		jle jmp_10041b5d
jmp_10041ae0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, dword ptr [ecx + 0x10]
		shr ebp, 6
		mov edx, dword ptr [ecx + 0x10]
		shr edx, 0xb
		mov eax, dword ptr [ecx + 0x10]
		shr eax, 0x10
		and ebp, 3
		and edx, 0x1c
		and eax, 0xe0
		or edx, ebp
		lea ebp, [esp + 0x84]
		or eax, edx
		mov byte ptr [ebp], al
		mov byte ptr [ebp + 1], al
		mov byte ptr [ebp + 2], al
		mov byte ptr [ebp + 3], al
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10041c5d
jmp_10041b5d:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov ebp, dword ptr [ecx + 0x10]
		shr ebp, 6
		mov edx, dword ptr [ecx + 0x10]
		shr edx, 0xb
		mov eax, dword ptr [ecx + 0x10]
		shr eax, 0x10
		and ebp, 3
		and edx, 0x1c
		and eax, 0xe0
		or edx, ebp
		lea ebp, [esp + 0x84]
		or eax, edx
		mov byte ptr [ebp], al
		mov byte ptr [ebp + 1], al
		mov byte ptr [ebp + 2], al
		mov byte ptr [ebp + 3], al
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10041c5d
jmp_10041beb:
		cmp eax, ebp
		jge jmp_10041ae0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov ebp, dword ptr [ecx + 0x10]
		shr ebp, 6
		mov edx, dword ptr [ecx + 0x10]
		shr edx, 0xb
		mov eax, dword ptr [ecx + 0x10]
		shr eax, 0x10
		and ebp, 3
		and edx, 0x1c
		and eax, 0xe0
		or edx, ebp
		lea ebp, [esp + 0x84]
		or eax, edx
		mov byte ptr [ebp], al
		mov byte ptr [ebp + 1], al
		mov byte ptr [ebp + 2], al
		mov byte ptr [ebp + 3], al
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10041c5d:
		mov ebp, dword ptr [esp + 0x9c]
		lea eax, [esp + 0x24]
		fst dword ptr [esp + 0x50]
		fld dword ptr [esi]
		fsub dword ptr [ecx]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fxch st(1)
		fmulp st(2), st(0)
		fld dword ptr [ecx]
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fldcw word ptr [esp + 4]
		and eax, 0xfffffff8
		mov edx, dword ptr [ebp]
		mov dword ptr [esp + 0x1c], eax
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x70], edx
		mov dword ptr [esp + 0x74], ebx
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10041d4d
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057974]
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10041d4d:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10041eb5
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10041de3
jmp_10041d86:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10041da3
		lea edi, [edi + edx]
		mov eax, dword ptr [esp + 0x84]
jmp_10041d9b:
		mov byte ptr [edi], al
		dec ecx
		lea edi, [edi + 1]
		jns jmp_10041d9b
jmp_10041da3:
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10041d86
jmp_10041de3:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10042008
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10041e50:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10041e6d
		lea edi, [edi + edx]
		mov eax, dword ptr [esp + 0x84]
jmp_10041e65:
		mov byte ptr [edi], al
		dec ecx
		lea edi, [edi + 1]
		jns jmp_10041e65
jmp_10041e6d:
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10041e50
		jmp jmp_10042008
jmp_10041eb5:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10041f38
jmp_10041ed8:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10041ef5
		lea edi, [edi + ecx]
		mov eax, dword ptr [esp + 0x84]
jmp_10041eed:
		mov byte ptr [edi], al
		inc edx
		lea edi, [edi - 1]
		jle jmp_10041eed
jmp_10041ef5:
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10041ed8
jmp_10041f38:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10042008
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10041fab:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10041fc8
		lea edi, [edi + ecx]
		mov eax, dword ptr [esp + 0x84]
jmp_10041fc0:
		mov byte ptr [edi], al
		inc edx
		lea edi, [edi - 1]
		jle jmp_10041fc0
jmp_10041fc8:
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10041fab
jmp_10042008:
		fldcw word ptr [esp]
		add esp, 0x88
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10042020
__declspec(naked) void FUN_10042020(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xc4
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xb4], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xc0], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb8], ebx
		mov dword ptr [esp + 0xbc], edi
		mov edi, dword ptr [esp + 0xd4]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_100422e6
		cmp edx, ebp
		jle jmp_100421bb
jmp_100420a4:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		xor edx, edx
		xor eax, eax
		mov al, byte ptr [ecx + 0x12]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		mov ebp, eax
		shl ebp, 0x17
		mov dl, byte ptr [edi + 0x12]
		add ebp, 0x200000
		sub ebx, eax
		mov dword ptr [esp + 0x84], ebp
		sub edx, eax
		mov dword ptr [esp + 0x90], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		xor eax, eax
		mov al, byte ptr [edi + 0x12]
		mov dword ptr [esp + 0xa8], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0x9c], ebx
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		mov al, byte ptr [ecx + 0x11]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		mov ebp, eax
		shl ebp, 0x14
		mov dl, byte ptr [edi + 0x11]
		add ebp, 0x40000
		sub ebx, eax
		mov dword ptr [esp + 0x88], ebp
		sub edx, eax
		mov dword ptr [esp + 0x94], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		xor eax, eax
		mov al, byte ptr [edi + 0x11]
		mov dword ptr [esp + 0xac], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0xa0], ebx
		mov al, byte ptr [ecx + 0x10]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		mov ebp, eax
		shl ebp, 0x11
		mov dl, byte ptr [edi + 0x10]
		add ebp, 0x8000
		sub ebx, eax
		mov dword ptr [esp + 0x8c], ebp
		sub edx, eax
		mov dword ptr [esp + 0x98], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		xor eax, eax
		mov al, byte ptr [edi + 0x10]
		mov dword ptr [esp + 0xb0], edx
		sub ebx, eax
		mov dword ptr [esp + 0xa4], ebx
		jmp jmp_100423f2
jmp_100421bb:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		xor edx, edx
		xor eax, eax
		mov al, byte ptr [ecx + 0x12]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		mov ebp, eax
		shl ebp, 0x17
		mov dl, byte ptr [edi + 0x12]
		add ebp, 0x200000
		sub ebx, eax
		mov dword ptr [esp + 0x84], ebp
		sub edx, eax
		mov dword ptr [esp + 0x90], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		xor eax, eax
		mov al, byte ptr [edi + 0x12]
		mov dword ptr [esp + 0xa8], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0x9c], ebx
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		mov al, byte ptr [ecx + 0x11]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		mov ebp, eax
		shl ebp, 0x14
		mov dl, byte ptr [edi + 0x11]
		add ebp, 0x40000
		sub ebx, eax
		mov dword ptr [esp + 0x88], ebp
		sub edx, eax
		mov dword ptr [esp + 0x94], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		xor eax, eax
		mov al, byte ptr [edi + 0x11]
		mov dword ptr [esp + 0xac], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0xa0], ebx
		mov al, byte ptr [ecx + 0x10]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		mov ebp, eax
		shl ebp, 0x11
		mov dl, byte ptr [edi + 0x10]
		add ebp, 0x8000
		sub ebx, eax
		mov dword ptr [esp + 0x8c], ebp
		sub edx, eax
		mov dword ptr [esp + 0x98], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		xor eax, eax
		mov al, byte ptr [edi + 0x10]
		mov dword ptr [esp + 0xb0], edx
		sub ebx, eax
		mov dword ptr [esp + 0xa4], ebx
		jmp jmp_100423f2
jmp_100422e6:
		cmp eax, ebp
		jge jmp_100420a4
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		xor edx, edx
		xor eax, eax
		mov al, byte ptr [ecx + 0x12]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		mov ebp, eax
		shl ebp, 0x17
		mov dl, byte ptr [edi + 0x12]
		add ebp, 0x200000
		sub ebx, eax
		mov dword ptr [esp + 0x84], ebp
		sub edx, eax
		mov dword ptr [esp + 0x90], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x12]
		xor eax, eax
		mov al, byte ptr [edi + 0x12]
		mov dword ptr [esp + 0xa8], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0x9c], ebx
		fld1
		fdivrp st(2), st(0)
		mov al, byte ptr [ecx + 0x11]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		mov ebp, eax
		shl ebp, 0x14
		mov dl, byte ptr [edi + 0x11]
		add ebp, 0x40000
		sub ebx, eax
		mov dword ptr [esp + 0x88], ebp
		sub edx, eax
		mov dword ptr [esp + 0x94], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x11]
		xor eax, eax
		mov al, byte ptr [edi + 0x11]
		mov dword ptr [esp + 0xac], edx
		sub ebx, eax
		xor edx, edx
		mov dword ptr [esp + 0xa0], ebx
		mov al, byte ptr [ecx + 0x10]
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		mov ebp, eax
		shl ebp, 0x11
		mov dl, byte ptr [edi + 0x10]
		add ebp, 0x8000
		sub ebx, eax
		mov dword ptr [esp + 0x8c], ebp
		sub edx, eax
		mov dword ptr [esp + 0x98], ebx
		xor ebx, ebx
		mov bl, byte ptr [esi + 0x10]
		xor eax, eax
		mov al, byte ptr [edi + 0x10]
		mov dword ptr [esp + 0xb0], edx
		sub ebx, eax
		mov dword ptr [esp + 0xa4], ebx
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_100423f2:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc8]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp]
		mov ebx, dword ptr [ebp + 4]
		mov dword ptr [esp + 0x70], eax
		mov dword ptr [esp + 0x74], ebx
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		jns jmp_10042476
		mov edx, dword ptr [esp + 0x90]
		mov ebp, dword ptr [esp + 0x94]
		mov dword ptr [esp + 0xa8], edx
		mov ebx, dword ptr [esp + 0x98]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0xb0], ebx
jmp_10042476:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0x90]
		fld dword ptr [esp + 0x44]
		fmulp st(2), st(0)
		fld dword ptr [esp + 0x4c]
		fmulp st(1), st(0)
		fild dword ptr [esp + 0xa8]
		fxch st(2)
		faddp st(1), st(0)
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x5c]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x100579b8]
		fld dword ptr [g_unk0x100579b8]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fild dword ptr [esp + 0xa0]
		fild dword ptr [esp + 0x94]
		fld dword ptr [esp + 0x44]
		fmulp st(2), st(0)
		fld dword ptr [esp + 0x4c]
		fmulp st(1), st(0)
		fild dword ptr [esp + 0xac]
		fxch st(2)
		faddp st(1), st(0)
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x5c]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x100579b4]
		fld dword ptr [g_unk0x100579b4]
		faddp st(2), st(0)
		mov dword ptr [esp + 0xa8], ebx
		mov dword ptr [esp + 0x90], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fild dword ptr [esp + 0xa4]
		fild dword ptr [esp + 0x98]
		fld dword ptr [esp + 0x44]
		fmulp st(2), st(0)
		fld dword ptr [esp + 0x4c]
		fmulp st(1), st(0)
		fild dword ptr [esp + 0xb0]
		fxch st(2)
		faddp st(1), st(0)
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x5c]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x100579b0]
		fld dword ptr [g_unk0x100579b0]
		faddp st(2), st(0)
		mov dword ptr [esp + 0xac], ebx
		mov dword ptr [esp + 0x94], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0x98], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100426c8
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fild dword ptr [esp + 0xa8]
		fild dword ptr [esp + 0x84]
		fld st(2)
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fild dword ptr [esp + 0xac]
		fild dword ptr [esp + 0x88]
		fld st(4)
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fxch st(2)
		faddp st(3), st(0)
		fild dword ptr [esp + 0xb0]
		fild dword ptr [esp + 0x8c]
		fld st(5)
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fxch st(2)
		faddp st(3), st(0)
		fxch st(3)
		fstp qword ptr [eax]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		mov ecx, dword ptr [eax]
		mov edx, dword ptr [eax + 8]
		fstp qword ptr [eax]
		fmul dword ptr [g_unk0x10057970]
		mov dword ptr [esp + 0x84], ecx
		mov esi, dword ptr [eax]
		mov dword ptr [esp + 0x88], edx
		mov dword ptr [esp + 0x8c], esi
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100426c8:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_1004294e
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100427ef
jmp_10042705:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10042766
		lea edi, [edi + edx]
		mov esi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0x88]
		mov ebx, dword ptr [esp + 0x8c]
jmp_10042728:
		mov eax, 0x70000000
		mov edx, 0xe000000
		and eax, esi
		and edx, ebp
		and ebx, 0x1ffffff
		or eax, edx
		mov edx, dword ptr [esp + 0x90]
		or eax, ebx
		shr eax, 0x17
		add esi, edx
		mov byte ptr [edi], al
		mov edx, dword ptr [esp + 0x94]
		mov eax, dword ptr [esp + 0x98]
		add ebp, edx
		add ebx, eax
		dec ecx
		lea edi, [edi + 1]
		jns jmp_10042728
jmp_10042766:
		mov ebx, dword ptr [esp + 0xa8]
		mov edi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0xac]
		add ebx, edi
		mov esi, dword ptr [esp + 0x88]
		mov dword ptr [esp + 0x84], ebx
		mov ebx, dword ptr [esp + 0xb0]
		mov edi, dword ptr [esp + 0x8c]
		add ebp, esi
		add ebx, edi
		mov dword ptr [esp + 0x88], ebp
		mov dword ptr [esp + 0x8c], ebx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10042705
jmp_100427ef:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10042bbf
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_1004285c:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100428bd
		lea edi, [edi + edx]
		mov esi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0x88]
		mov ebx, dword ptr [esp + 0x8c]
jmp_1004287f:
		mov eax, 0x70000000
		mov edx, 0xe000000
		and eax, esi
		and edx, ebp
		and ebx, 0x1ffffff
		or eax, edx
		mov edx, dword ptr [esp + 0x90]
		or eax, ebx
		shr eax, 0x17
		add esi, edx
		mov byte ptr [edi], al
		mov edx, dword ptr [esp + 0x94]
		mov eax, dword ptr [esp + 0x98]
		add ebp, edx
		add ebx, eax
		dec ecx
		lea edi, [edi + 1]
		jns jmp_1004287f
jmp_100428bd:
		mov ebx, dword ptr [esp + 0xa8]
		mov edi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0xac]
		add ebx, edi
		mov esi, dword ptr [esp + 0x88]
		mov dword ptr [esp + 0x84], ebx
		mov ebx, dword ptr [esp + 0xb0]
		mov edi, dword ptr [esp + 0x8c]
		add ebp, esi
		add ebx, edi
		mov dword ptr [esp + 0x88], ebp
		mov dword ptr [esp + 0x8c], ebx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004285c
		jmp jmp_10042bbf
jmp_1004294e:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10042a62
jmp_10042975:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_100429d6
		lea edi, [edi + ecx]
		mov esi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0x88]
		mov ebx, dword ptr [esp + 0x8c]
jmp_10042998:
		mov eax, 0x70000000
		mov ecx, 0xe000000
		and eax, esi
		and ecx, ebp
		and ebx, 0x1ffffff
		or eax, ecx
		mov ecx, dword ptr [esp + 0x90]
		or eax, ebx
		shr eax, 0x17
		sub esi, ecx
		mov byte ptr [edi], al
		mov ecx, dword ptr [esp + 0x94]
		mov eax, dword ptr [esp + 0x98]
		sub ebp, ecx
		sub ebx, eax
		inc edx
		lea edi, [edi - 1]
		jle jmp_10042998
jmp_100429d6:
		mov ebx, dword ptr [esp + 0xa8]
		mov edi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0xac]
		add ebx, edi
		mov esi, dword ptr [esp + 0x88]
		mov dword ptr [esp + 0x84], ebx
		mov ebx, dword ptr [esp + 0xb0]
		mov edi, dword ptr [esp + 0x8c]
		add ebp, esi
		add ebx, edi
		mov dword ptr [esp + 0x88], ebp
		mov dword ptr [esp + 0x8c], ebx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10042975
jmp_10042a62:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10042bbf
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10042ad5:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10042b36
		lea edi, [edi + ecx]
		mov esi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0x88]
		mov ebx, dword ptr [esp + 0x8c]
jmp_10042af8:
		mov eax, 0x70000000
		mov ecx, 0xe000000
		and eax, esi
		and ecx, ebp
		and ebx, 0x1ffffff
		or eax, ecx
		mov ecx, dword ptr [esp + 0x90]
		or eax, ebx
		shr eax, 0x17
		sub esi, ecx
		mov byte ptr [edi], al
		mov ecx, dword ptr [esp + 0x94]
		mov eax, dword ptr [esp + 0x98]
		sub ebp, ecx
		sub ebx, eax
		inc edx
		lea edi, [edi - 1]
		jle jmp_10042af8
jmp_10042b36:
		mov ebx, dword ptr [esp + 0xa8]
		mov edi, dword ptr [esp + 0x84]
		mov ebp, dword ptr [esp + 0xac]
		add ebx, edi
		mov esi, dword ptr [esp + 0x88]
		mov dword ptr [esp + 0x84], ebx
		mov ebx, dword ptr [esp + 0xb0]
		mov edi, dword ptr [esp + 0x8c]
		add ebp, esi
		add ebx, edi
		mov dword ptr [esp + 0x88], ebp
		mov dword ptr [esp + 0x8c], ebx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10042ad5
jmp_10042bbf:
		fldcw word ptr [esp]
		add esp, 0xb4
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10042bd0
__declspec(naked) void FUN_10042bd0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10042cf3
		cmp edx, ebp
		jle jmp_10042c99
jmp_10042c50:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10042d31
jmp_10042c99:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10042d31
jmp_10042cf3:
		cmp eax, ebp
		jge jmp_10042c50
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10042d31:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10042d9f
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10042d9f:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10042f97
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10042f97:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_100431d9
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004309c
jmp_10042fd4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004302a
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10042ff8:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x14
		and edx, 0xff00000
		shr edx, 0xc
		and eax, 0xff
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10042ff8
jmp_1004302a:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10042fd4
jmp_1004309c:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10043406
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10043109:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004315f
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_1004312d:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x14
		and edx, 0xff00000
		shr edx, 0xc
		and eax, 0xff
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_1004312d
jmp_1004315f:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043109
		jmp jmp_10043406
jmp_100431d9:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100432cb
jmp_10043200:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10043256
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10043224:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x14
		and ecx, 0xff00000
		shr ecx, 0xc
		and eax, 0xff
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10043224
jmp_10043256:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043200
jmp_100432cb:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10043406
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_1004333e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10043394
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10043362:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x14
		and ecx, 0xff00000
		shr ecx, 0xc
		and eax, 0xff
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10043362
jmp_10043394:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004333e
jmp_10043406:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10043420
__declspec(naked) void FUN_10043420(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10043543
		cmp edx, ebp
		jle jmp_100434e9
jmp_100434a0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10043581
jmp_100434e9:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10043581
jmp_10043543:
		cmp eax, ebp
		jge jmp_100434a0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10043581:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_100435ef
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_100435ef:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100437e7
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100437e7:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10043a25
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100438ea
jmp_10043824:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10043878
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10043848:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x15
		and edx, 0xfe00000
		shr edx, 0xe
		and eax, 0x7f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10043848
jmp_10043878:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043824
jmp_100438ea:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10043c4e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10043957:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100439ab
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_1004397b:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x15
		and edx, 0xfe00000
		shr edx, 0xe
		and eax, 0x7f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_1004397b
jmp_100439ab:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043957
		jmp jmp_10043c4e
jmp_10043a25:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10043b15
jmp_10043a4c:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10043aa0
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10043a70:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x15
		and ecx, 0xfe00000
		shr ecx, 0xe
		and eax, 0x7f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10043a70
jmp_10043aa0:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043a4c
jmp_10043b15:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10043c4e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10043b88:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10043bdc
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10043bac:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x15
		and ecx, 0xfe00000
		shr ecx, 0xe
		and eax, 0x7f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10043bac
jmp_10043bdc:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10043b88
jmp_10043c4e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10043c60
__declspec(naked) void FUN_10043c60(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10043d83
		cmp edx, ebp
		jle jmp_10043d29
jmp_10043ce0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10043dc1
jmp_10043d29:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10043dc1
jmp_10043d83:
		cmp eax, ebp
		jge jmp_10043ce0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10043dc1:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10043e2f
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10043e2f:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10044027
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10044027:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10044265
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004412a
jmp_10044064:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100440b8
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10044088:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x16
		and edx, 0xfc00000
		shr edx, 0x10
		and eax, 0x3f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10044088
jmp_100440b8:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10044064
jmp_1004412a:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004448e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10044197:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100441eb
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_100441bb:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x16
		and edx, 0xfc00000
		shr edx, 0x10
		and eax, 0x3f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_100441bb
jmp_100441eb:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10044197
		jmp jmp_1004448e
jmp_10044265:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10044355
jmp_1004428c:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_100442e0
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_100442b0:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x16
		and ecx, 0xfc00000
		shr ecx, 0x10
		and eax, 0x3f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_100442b0
jmp_100442e0:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004428c
jmp_10044355:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004448e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_100443c8:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004441c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_100443ec:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x16
		and ecx, 0xfc00000
		shr ecx, 0x10
		and eax, 0x3f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_100443ec
jmp_1004441c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100443c8
jmp_1004448e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x100444a0
__declspec(naked) void FUN_100444a0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_100445c3
		cmp edx, ebp
		jle jmp_10044569
jmp_10044520:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10044601
jmp_10044569:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10044601
jmp_100445c3:
		cmp eax, ebp
		jge jmp_10044520
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10044601:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_1004466f
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_1004466f:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10044867
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10044867:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10044aa5
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004496a
jmp_100448a4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100448f8
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_100448c8:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x17
		and edx, 0xf800000
		shr edx, 0x12
		and eax, 0x1f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_100448c8
jmp_100448f8:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100448a4
jmp_1004496a:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10044cce
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_100449d7:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10044a2b
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_100449fb:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x17
		and edx, 0xf800000
		shr edx, 0x12
		and eax, 0x1f
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_100449fb
jmp_10044a2b:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100449d7
		jmp jmp_10044cce
jmp_10044aa5:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10044b95
jmp_10044acc:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10044b20
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10044af0:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x17
		and ecx, 0xf800000
		shr ecx, 0x12
		and eax, 0x1f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10044af0
jmp_10044b20:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10044acc
jmp_10044b95:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10044cce
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10044c08:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10044c5c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10044c2c:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x17
		and ecx, 0xf800000
		shr ecx, 0x12
		and eax, 0x1f
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10044c2c
jmp_10044c5c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10044c08
jmp_10044cce:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10044ce0
__declspec(naked) void FUN_10044ce0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10044e03
		cmp edx, ebp
		jle jmp_10044da9
jmp_10044d60:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10044e41
jmp_10044da9:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10044e41
jmp_10044e03:
		cmp eax, ebp
		jge jmp_10044d60
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10044e41:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10044eaf
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10044eaf:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100450a7
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100450a7:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_100452e5
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100451aa
jmp_100450e4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10045138
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045108:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x18
		and edx, 0xf000000
		shr edx, 0x14
		and eax, 0xf
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10045108
jmp_10045138:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100450e4
jmp_100451aa:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004550e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10045217:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004526b
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_1004523b:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x18
		and edx, 0xf000000
		shr edx, 0x14
		and eax, 0xf
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_1004523b
jmp_1004526b:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045217
		jmp jmp_1004550e
jmp_100452e5:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100453d5
jmp_1004530c:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10045360
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045330:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x18
		and ecx, 0xf000000
		shr ecx, 0x14
		and eax, 0xf
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10045330
jmp_10045360:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004530c
jmp_100453d5:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004550e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10045448:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004549c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_1004546c:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x18
		and ecx, 0xf000000
		shr ecx, 0x14
		and eax, 0xf
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_1004546c
jmp_1004549c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045448
jmp_1004550e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10045520
__declspec(naked) void FUN_10045520(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10045643
		cmp edx, ebp
		jle jmp_100455e9
jmp_100455a0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10045681
jmp_100455e9:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10045681
jmp_10045643:
		cmp eax, ebp
		jge jmp_100455a0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10045681:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_100456ef
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_100456ef:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100458e7
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100458e7:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10045b25
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100459ea
jmp_10045924:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10045978
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045948:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x19
		and edx, 0xe000000
		shr edx, 0x16
		and eax, 7
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10045948
jmp_10045978:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045924
jmp_100459ea:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10045d4e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10045a57:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10045aab
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx - 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045a7b:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x19
		and edx, 0xe000000
		shr edx, 0x16
		and eax, 7
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		inc edi
		add ebp, eax
		mov dl, byte ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov byte ptr [edi], dl
		jns jmp_10045a7b
jmp_10045aab:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045a57
		jmp jmp_10045d4e
jmp_10045b25:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10045c15
jmp_10045b4c:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10045ba0
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045b70:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x19
		and ecx, 0xe000000
		shr ecx, 0x16
		and eax, 7
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10045b70
jmp_10045ba0:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045b4c
jmp_10045c15:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10045d4e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10045c88:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10045cdc
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx + 1]
		mov esi, dword ptr [esp + 0x84]
jmp_10045cac:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x19
		and ecx, 0xe000000
		shr ecx, 0x16
		and eax, 7
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		dec edi
		sub ebp, eax
		mov cl, byte ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov byte ptr [edi], cl
		jle jmp_10045cac
jmp_10045cdc:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10045c88
jmp_10045d4e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10045d60
__declspec(naked) void FUN_10045d60()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045d7e:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x17
		and edx, 0x7000000
		shr edx, 0x14
		and eax, 0xe
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045d7e
		ret
	}
}

// FUNCTION: GOLDP 0x10045db0
__declspec(naked) void FUN_10045db0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045dce:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x16
		and edx, 0x7800000
		shr edx, 0x12
		and eax, 0x1e
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045dce
		ret
	}
}

// FUNCTION: GOLDP 0x10045e00
__declspec(naked) void FUN_10045e00()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045e1e:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x15
		and edx, 0x7c00000
		shr edx, 0x10
		and eax, 0x3e
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045e1e
		ret
	}
}

// FUNCTION: GOLDP 0x10045e50
__declspec(naked) void FUN_10045e50()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045e6e:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x14
		and edx, 0x7e00000
		shr edx, 0xe
		and eax, 0x7e
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045e6e
		ret
	}
}

// FUNCTION: GOLDP 0x10045ea0
__declspec(naked) void FUN_10045ea0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045ebe:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x13
		and edx, 0x7f00000
		shr edx, 0xc
		and eax, 0xfe
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045ebe
		ret
	}
}

// FUNCTION: GOLDP 0x10045ef0
__declspec(naked) void FUN_10045ef0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x44]
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045f0e:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x12
		and edx, 0x7f80000
		shr edx, 0xa
		and eax, 0x1fe
		or edx, eax
		mov eax, dword ptr [esp + 0x54]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x5c]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10045f0e
		ret
	}
}

// FUNCTION: GOLDP 0x10045f40
__declspec(naked) void FUN_10045f40()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045f5c:
		shr eax, 0x18
		mov edx, ebx
		and edx, 0x7000000
		and eax, 7
		shr edx, 0x15
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_10045f5c
		ret
	}
}

// FUNCTION: GOLDP 0x10045fa0
__declspec(naked) void FUN_10045fa0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_10045fbc:
		shr eax, 0x17
		mov edx, ebx
		and edx, 0x7800000
		and eax, 0xf
		shr edx, 0x13
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_10045fbc
		ret
	}
}

// FUNCTION: GOLDP 0x10046000
__declspec(naked) void FUN_10046000()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004601c:
		shr eax, 0x16
		mov edx, ebx
		and edx, 0x7c00000
		and eax, 0x1f
		shr edx, 0x11
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004601c
		ret
	}
}

// FUNCTION: GOLDP 0x10046060
__declspec(naked) void FUN_10046060()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004607c:
		shr eax, 0x15
		mov edx, ebx
		and edx, 0x7e00000
		and eax, 0x3f
		shr edx, 0xf
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004607c
		ret
	}
}

// FUNCTION: GOLDP 0x100460c0
__declspec(naked) void FUN_100460c0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_100460dc:
		shr eax, 0x14
		mov edx, ebx
		and edx, 0x7f00000
		and eax, 0x7f
		shr edx, 0xd
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_100460dc
		ret
	}
}

// FUNCTION: GOLDP 0x10046120
__declspec(naked) void FUN_10046120()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004613c:
		shr eax, 0x13
		mov edx, ebx
		and edx, 0x7f80000
		and eax, 0xff
		shr edx, 0xb
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		mov eax, dword ptr [esp + 0x5c]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004613c
		ret
	}
}

// FUNCTION: GOLDP 0x10046180
__declspec(naked) void FUN_10046180()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004619c:
		shr eax, 0x18
		mov edx, ebx
		and edx, 0x7000000
		and eax, 7
		shr edx, 0x15
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_100461dc
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004619c
		ret
jmp_100461dc:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_1004619c
		ret
	}
}

// FUNCTION: GOLDP 0x100461f0
__declspec(naked) void FUN_100461f0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004620c:
		shr eax, 0x17
		mov edx, ebx
		and edx, 0x7800000
		and eax, 0xf
		shr edx, 0x13
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_1004624c
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004620c
		ret
jmp_1004624c:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_1004620c
		ret
	}
}

// FUNCTION: GOLDP 0x10046260
__declspec(naked) void FUN_10046260()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004627c:
		shr eax, 0x16
		mov edx, ebx
		and edx, 0x7c00000
		and eax, 0x1f
		shr edx, 0x11
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_100462bc
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004627c
		ret
jmp_100462bc:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_1004627c
		ret
	}
}

// FUNCTION: GOLDP 0x100462d0
__declspec(naked) void FUN_100462d0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_100462ec:
		shr eax, 0x15
		mov edx, ebx
		and edx, 0x7e00000
		and eax, 0x3f
		shr edx, 0xf
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_1004632c
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_100462ec
		ret
jmp_1004632c:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_100462ec
		ret
	}
}

// FUNCTION: GOLDP 0x10046340
__declspec(naked) void FUN_10046340()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_1004635c:
		shr eax, 0x14
		mov edx, ebx
		and edx, 0x7f00000
		and eax, 0x7f
		shr edx, 0xd
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_1004639c
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004635c
		ret
jmp_1004639c:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_1004635c
		ret
	}
}

// FUNCTION: GOLDP 0x100463b0
__declspec(naked) void FUN_100463b0()
{
	__asm {
		mov ebp, dword ptr [esp + 0x50]
		mov ebx, dword ptr [esp + 0x58]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
		fmul st(0), st(2)
		fxch st(1)
		fmulp st(2), st(0)
		fistp dword ptr [esp + 0x5c]
		fistp dword ptr [esp + 0x54]
jmp_100463cc:
		shr eax, 0x13
		mov edx, ebx
		and edx, 0x7f80000
		and eax, 0xff
		shr edx, 0xb
		mov esi, dword ptr [esp + 0x44]
		or eax, edx
		mov edx, dword ptr [esp + 0x54]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x48]
		add edi, 2
		or edx, edx
		mov eax, dword ptr [esp + 0x5c]
		je jmp_1004640e
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_100463cc
		ret
jmp_1004640e:
		add ebx, eax
		dec ecx
		mov eax, ebp
		jns jmp_100463cc
		ret
	}
}

// FUNCTION: GOLDP 0x10046420
__declspec(naked) void FUN_10046420(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		push esi
		push edi
		push ebx
		push ebp
		sub esp, 0xac
		mov edx, dword ptr [esp + 0xc0]
		mov edi, dword ptr [esp + 0xc4]
		wait
		fnstcw word ptr [esp]
		mov esi, dword ptr [esp + 0xc8]
		mov ecx, dword ptr [edx + 0x28]
		mov eax, dword ptr [edx + 0x34]
		mov ebx, dword ptr [edx + 4]
		mov dword ptr [esp + 0x48], ecx
		mov ecx, dword ptr [edx]
		mov ebp, dword ptr [esp]
		mov dword ptr [esp + 0x28], ebx
		mov dword ptr [esp + 0x24], ecx
		mov ecx, dword ptr [edi + 4]
		mov ebx, dword ptr [eax]
		and ebp, 0xfffffcff
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 4], ebp
		mov edx, dword ptr [esi + 4]
		mov ebp, dword ptr [esp + 0xcc]
		fldcw word ptr [esp + 4]
		cmp ecx, edx
		mov dword ptr [esp + 0x44], eax
		mov dword ptr [esp + 0x40], ebx
		mov eax, dword ptr [ebp + 4]
		mov ebx, dword ptr [g_floatConst1]
		jle jmp_100464aa
		cmp edx, eax
		jle jmp_100464a0
		mov eax, edi
		mov edi, ebp
		mov ebp, esi
		mov esi, eax
		jmp jmp_100464b6
jmp_100464a0:
		mov eax, edi
		mov edi, esi
		mov esi, ebp
		mov ebp, eax
		jmp jmp_100464b6
jmp_100464aa:
		cmp ecx, eax
		jl jmp_100464b6
		mov eax, edi
		mov edi, ebp
		mov ebp, esi
		mov esi, eax
jmp_100464b6:
		fld dword ptr [edi + 4]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [esi + 4]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [ebp + 4]
		fmul dword ptr [g_floatConst65536]
		fxch st(2)
		fistp dword ptr [esp + 0x2c]
		fistp dword ptr [esp + 0x30]
		fistp dword ptr [esp + 0x34]
		fld dword ptr [ebp + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ebp + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(2)
		fst dword ptr [esp + 0x14]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 8], edi
		mov dword ptr [esp + 0xc], esi
		mov dword ptr [esp + 0x10], ebp
		mov ebx, dword ptr [esp + 0x2c]
		mov eax, dword ptr [edi]
		dec ebx
		mov ecx, dword ptr [edi + 0xc]
		xor ebx, 0xffff
		mov dword ptr [esp + 0x64], eax
		and ebx, 0xffff
		mov dword ptr [esp + 0x7c], ecx
		mov dword ptr [esp + 0x38], ebx
		mov dword ptr [esp + 0x8c], eax
		mov dword ptr [esp + 0xa4], ecx
		fstp dword ptr [esp + 0x20]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [esp + 0x20]
		mov ebx, 0x7fffffff
		and ebx, eax
		or eax, eax
		mov dword ptr [esp + 0x20], ebx
		jns jmp_10046566
		mov eax, dword ptr [esp + 0x34]
		mov ebx, dword ptr [esp + 0x30]
		mov dword ptr [esp + 0x30], eax
		mov dword ptr [esp + 0x34], ebx
jmp_10046566:
		fstp dword ptr [esp + 0x1c]
		fld dword ptr [g_unk0x100579d8]
		fmul dword ptr [esi + 0xc]
		fld dword ptr [g_unk0x100579d8]
		fmul dword ptr [edi + 0xc]
		fld dword ptr [g_unk0x100579d8]
		fmul dword ptr [ebp + 0xc]
		fxch st(3)
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [esp + 0x30]
		mov ebx, dword ptr [esp + 0x2c]
		dec eax
		mov edx, dword ptr [esp + 0x38]
		xor eax, 0xffff
		add ebx, edx
		and eax, 0xffff
		mov dword ptr [esp + 0x2c], ebx
		mov dword ptr [esp + 0x3c], eax
		fstp dword ptr [esp + 0x18]
		fld dword ptr [edi + 0x18]
		fmul st(0), st(1)
		fld dword ptr [edi + 0x1c]
		fmulp st(2), st(0)
		fld dword ptr [esi + 0x18]
		fmul st(0), st(3)
		fld dword ptr [esi + 0x1c]
		fmulp st(4), st(0)
		fld dword ptr [ebp + 0x18]
		fmul st(0), st(5)
		fld dword ptr [ebp + 0x1c]
		fmulp st(6), st(0)
		fxch st(2)
		fsub st(1), st(0)
		fsub st(2), st(0)
		fstp dword ptr [esp + 0x6c]
		fmul dword ptr [esp + 0x18]
		fld dword ptr [esp + 0x1c]
		fmulp st(2), st(0)
		fxch st(2)
		fsub st(3), st(0)
		fsub st(4), st(0)
		fstp dword ptr [esp + 0x74]
		fld dword ptr [esp + 0x18]
		fmulp st(3), st(0)
		fld dword ptr [esp + 0x1c]
		fmulp st(4), st(0)
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0x98]
		fstp dword ptr [esp + 0xa0]
		fstp dword ptr [esp + 0x78]
		fild dword ptr [esp + 0x38]
		fld dword ptr [ebp]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fxch st(1)
		fmul dword ptr [esp + 0x1c]
		fld dword ptr [esp + 0x18]
		fmulp st(2), st(0)
		fld st(0)
		fmul dword ptr [g_floatConst65536]
		fld st(2)
		fld dword ptr [g_floatConst65536]
		fmulp st(4), st(0)
		fstp dword ptr [esp + 0x90]
		fistp dword ptr [esp + 0x60]
		fstp dword ptr [esp + 0x68]
		fistp dword ptr [esp + 0x88]
		fmul dword ptr [g_unk0x10057998]
		mov ebx, dword ptr [esp + 0x74]
		mov eax, dword ptr [esp + 0x38]
		mov dword ptr [esp + 0x9c], ebx
		mov ecx, dword ptr [esp + 0x6c]
		fld dword ptr [ebp + 0xc]
		fsub dword ptr [edi + 0xc]
		fld dword ptr [esi + 0xc]
		fsub dword ptr [edi + 0xc]
		fxch st(1)
		fmul dword ptr [esp + 0x1c]
		fld dword ptr [esp + 0x18]
		fmulp st(2), st(0)
		mov dword ptr [esp + 0x94], ecx
		or eax, eax
		fstp dword ptr [esp + 0x80]
		fstp dword ptr [esp + 0xa8]
		je jmp_1004674a
		fld dword ptr [esp + 0x68]
		fmul st(0), st(1)
		fld dword ptr [esp + 0x90]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x80]
		fmul st(0), st(3)
		fld dword ptr [esp + 0xa8]
		fmul st(0), st(4)
		fxch st(3)
		fadd dword ptr [esp + 0x64]
		fxch st(2)
		fadd dword ptr [esp + 0x8c]
		fxch st(1)
		fadd dword ptr [esp + 0x7c]
		fxch st(3)
		fadd dword ptr [esp + 0xa4]
		fxch st(2)
		fstp dword ptr [esp + 0x64]
		fstp dword ptr [esp + 0x8c]
		fstp dword ptr [esp + 0xa4]
		fstp dword ptr [esp + 0x7c]
		fld dword ptr [esp + 0x70]
		fmul st(0), st(1)
		fld dword ptr [esp + 0x98]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x78]
		fmul st(0), st(3)
		fld dword ptr [esp + 0xa0]
		fmul st(0), st(4)
		fxch st(3)
		fadd dword ptr [esp + 0x6c]
		fxch st(2)
		fadd dword ptr [esp + 0x94]
		fxch st(1)
		fadd dword ptr [esp + 0x74]
		fxch st(3)
		fadd dword ptr [esp + 0x9c]
		fxch st(2)
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0x94]
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x74]
jmp_1004674a:
		fstp st(0)
		fld dword ptr [esp + 0x64]
		fmul dword ptr [g_floatConst65536]
		fld dword ptr [esp + 0x8c]
		fmul dword ptr [g_floatConst65536]
		fxch st(1)
		fistp dword ptr [esp + 0x5c]
		mov eax, dword ptr [esp + 0x2c]
		mov ecx, dword ptr [esp + 0x28]
		sar eax, 0x10
		mov edi, dword ptr [esp + 0x24]
		imul ecx
		fistp dword ptr [esp + 0x84]
		mov ebx, dword ptr [esp + 0x2c]
		mov edx, dword ptr [esp + 0x30]
		add edi, eax
		mov ecx, dword ptr [esp + 0x84]
		cmp ebx, edx
		mov dword ptr [esp + 0x24], edi
		mov edx, dword ptr [esp + 0x5c]
		jge jmp_100468d3
jmp_100467a2:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov esi, dword ptr [esp + 0x48]
		sub ecx, edx
		jl jmp_100467ff
		fld dword ptr [esp + 0x8c]
		fsub dword ptr [esp + 0x64]
		fld1
		fdiv dword ptr [esp + 0x7c]
		fld1
		fdiv dword ptr [esp + 0xa4]
		fld dword ptr [esp + 0x6c]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x74]
		fmulp st(3), st(0)
		fld dword ptr [esp + 0x94]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x9c]
		fmulp st(3), st(0)
		fxch st(1)
		fsub st(1), st(0)
		fistp dword ptr [esp + 0x4c]
		fxch st(2)
		fsub st(1), st(0)
		fistp dword ptr [esp + 0x54]
		fld1
		fdivrp st(3), st(0)
		call esi
jmp_100467ff:
		fld dword ptr [esp + 0x64]
		fadd dword ptr [esp + 0x68]
		fld dword ptr [esp + 0x7c]
		fadd dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x5c]
		mov ecx, dword ptr [esp + 0x84]
		fld dword ptr [esp + 0x6c]
		fadd dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x74]
		fadd dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x24]
		fld dword ptr [esp + 0x8c]
		fadd dword ptr [esp + 0x90]
		fld dword ptr [esp + 0xa4]
		fadd dword ptr [esp + 0xa8]
		fld dword ptr [esp + 0x94]
		fadd dword ptr [esp + 0x98]
		fld dword ptr [esp + 0x9c]
		fadd dword ptr [esp + 0xa0]
		add edx, ebp
		mov ebp, dword ptr [esp + 0x88]
		mov esi, dword ptr [esp + 0x28]
		add ecx, ebp
		mov ebx, dword ptr [esp + 0x2c]
		mov eax, dword ptr [esp + 0x30]
		add edi, esi
		add ebx, 0x10000
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x94]
		cmp ebx, eax
		mov dword ptr [esp + 0x24], edi
		fstp dword ptr [esp + 0xa4]
		fstp dword ptr [esp + 0x8c]
		fstp dword ptr [esp + 0x74]
		mov dword ptr [esp + 0x5c], edx
		mov dword ptr [esp + 0x84], ecx
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0x7c]
		fstp dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x2c], ebx
		jl jmp_100467a2
jmp_100468d3:
		fild dword ptr [esp + 0x3c]
		mov eax, dword ptr [esp + 0x34]
		mov esi, dword ptr [esp + 0xc]
		cmp ebx, eax
		mov eax, dword ptr [esp + 0x14]
		jge jmp_10046b90
		or eax, eax
		mov ebp, dword ptr [esp + 0x10]
		fmul dword ptr [g_unk0x10057998]
		fld dword ptr [g_unk0x100579d8]
		fmul dword ptr [esi + 0xc]
		fld dword ptr [g_unk0x100579d8]
		fmul dword ptr [ebp + 0xc]
		fld st(1)
		fmul dword ptr [esi + 0x18]
		fld dword ptr [esi + 0x1c]
		fmulp st(3), st(0)
		fld st(1)
		fmul dword ptr [ebp + 0x18]
		fld dword ptr [ebp + 0x1c]
		fmulp st(3), st(0)
		js jmp_100469c4
		fsub st(0), st(1)
		fxch st(3)
		fsub st(2), st(0)
		fld dword ptr [esp + 0x20]
		fmul st(4), st(0)
		fmulp st(3), st(0)
		fld st(4)
		fmul st(0), st(4)
		fld st(5)
		fmul st(0), st(4)
		fxch st(1)
		faddp st(3), st(0)
		fxch st(4)
		fstp dword ptr [esp + 0x98]
		faddp st(3), st(0)
		fstp dword ptr [esp + 0x94]
		fstp dword ptr [esp + 0xa0]
		fstp dword ptr [esp + 0x9c]
		fld dword ptr [ebp]
		fsub dword ptr [esi]
		fld dword ptr [ebp + 0xc]
		fsub dword ptr [esi + 0xc]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld st(2)
		fmul st(0), st(1)
		fld st(2)
		fmulp st(4), st(0)
		fadd dword ptr [esi]
		fxch st(3)
		fadd dword ptr [esi + 0xc]
		fld dword ptr [g_floatConst65536]
		fmul st(0), st(4)
		fld st(2)
		fld dword ptr [g_floatConst65536]
		fmulp st(4), st(0)
		fstp dword ptr [esp + 0x90]
		fistp dword ptr [esp + 0x84]
		fstp dword ptr [esp + 0xa4]
		fistp dword ptr [esp + 0x88]
		fstp dword ptr [esp + 0xa8]
		fstp dword ptr [esp + 0x8c]
		jmp jmp_10046a46
jmp_100469c4:
		fsub st(1), st(0)
		fxch st(2)
		fsub st(3), st(0)
		fld dword ptr [esp + 0x20]
		fmul st(2), st(0)
		fmulp st(4), st(0)
		fld st(4)
		fmul st(0), st(2)
		fld st(5)
		fmul st(0), st(5)
		fxch st(1)
		faddp st(4), st(0)
		fxch st(4)
		fstp dword ptr [esp + 0x78]
		faddp st(3), st(0)
		fstp dword ptr [esp + 0x70]
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0x74]
		fld dword ptr [esi]
		fsub dword ptr [ebp]
		fld dword ptr [esi + 0xc]
		fsub dword ptr [ebp + 0xc]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld st(2)
		fmul st(0), st(1)
		fld st(2)
		fmulp st(4), st(0)
		fadd dword ptr [ebp]
		fxch st(3)
		fadd dword ptr [ebp + 0xc]
		fld dword ptr [g_floatConst65536]
		fmul st(0), st(4)
		fld st(2)
		fld dword ptr [g_floatConst65536]
		fmulp st(4), st(0)
		fstp dword ptr [esp + 0x68]
		fistp dword ptr [esp + 0x5c]
		fstp dword ptr [esp + 0x7c]
		fistp dword ptr [esp + 0x60]
		fstp dword ptr [esp + 0x80]
		fstp dword ptr [esp + 0x64]
jmp_10046a46:
		mov edx, dword ptr [esp + 0x5c]
		mov ecx, dword ptr [esp + 0x84]
jmp_10046a51:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		mov esi, dword ptr [esp + 0x48]
		sub ecx, edx
		jl jmp_10046aae
		fld dword ptr [esp + 0x8c]
		fsub dword ptr [esp + 0x64]
		fld1
		fdiv dword ptr [esp + 0x7c]
		fld1
		fdiv dword ptr [esp + 0xa4]
		fld dword ptr [esp + 0x6c]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x74]
		fmulp st(3), st(0)
		fld dword ptr [esp + 0x94]
		fmul st(0), st(2)
		fld dword ptr [esp + 0x9c]
		fmulp st(3), st(0)
		fxch st(1)
		fsub st(1), st(0)
		fistp dword ptr [esp + 0x4c]
		fxch st(2)
		fsub st(1), st(0)
		fistp dword ptr [esp + 0x54]
		fld1
		fdivrp st(3), st(0)
		call esi
jmp_10046aae:
		fld dword ptr [esp + 0x64]
		fadd dword ptr [esp + 0x68]
		fld dword ptr [esp + 0x7c]
		fadd dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x5c]
		mov ecx, dword ptr [esp + 0x84]
		fld dword ptr [esp + 0x6c]
		fadd dword ptr [esp + 0x70]
		fld dword ptr [esp + 0x74]
		fadd dword ptr [esp + 0x78]
		mov ebp, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x24]
		fld dword ptr [esp + 0x8c]
		fadd dword ptr [esp + 0x90]
		fld dword ptr [esp + 0xa4]
		fadd dword ptr [esp + 0xa8]
		fld dword ptr [esp + 0x94]
		fadd dword ptr [esp + 0x98]
		fld dword ptr [esp + 0x9c]
		fadd dword ptr [esp + 0xa0]
		add edx, ebp
		mov ebp, dword ptr [esp + 0x88]
		mov esi, dword ptr [esp + 0x28]
		add ecx, ebp
		mov ebx, dword ptr [esp + 0x2c]
		mov eax, dword ptr [esp + 0x34]
		add edi, esi
		add ebx, 0x10000
		fstp dword ptr [esp + 0x9c]
		fstp dword ptr [esp + 0x94]
		cmp ebx, eax
		mov dword ptr [esp + 0x24], edi
		fstp dword ptr [esp + 0xa4]
		fstp dword ptr [esp + 0x8c]
		fstp dword ptr [esp + 0x74]
		mov dword ptr [esp + 0x5c], edx
		mov dword ptr [esp + 0x84], ecx
		fstp dword ptr [esp + 0x6c]
		fstp dword ptr [esp + 0x7c]
		fstp dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x2c], ebx
		jl jmp_10046a51
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
jmp_10046b90:
		fstp st(0)
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10046ba0
__declspec(naked) void FUN_10046ba0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10046cc3
		cmp edx, ebp
		jle jmp_10046c69
jmp_10046c20:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10046d01
jmp_10046c69:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10046d01
jmp_10046cc3:
		cmp eax, ebp
		jge jmp_10046c20
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10046d01:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10046d6f
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10046d6f:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10046f67
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10046f67:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_100471ad
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004706e
jmp_10046fa4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10046ffc
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10046fc8:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x16
		and edx, 0xf800000
		shr edx, 0x11
		and eax, 0x3e
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10046fc8
jmp_10046ffc:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10046fa4
jmp_1004706e:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_100473de
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_100470db:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10047133
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_100470ff:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x16
		and edx, 0xf800000
		shr edx, 0x11
		and eax, 0x3e
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_100470ff
jmp_10047133:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100470db
		jmp jmp_100473de
jmp_100471ad:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100472a1
jmp_100471d4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004722c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_100471f8:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x16
		and ecx, 0xf800000
		shr ecx, 0x11
		and eax, 0x3e
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_100471f8
jmp_1004722c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100471d4
jmp_100472a1:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_100473de
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10047314:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004736c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10047338:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x16
		and ecx, 0xf800000
		shr ecx, 0x11
		and eax, 0x3e
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_10047338
jmp_1004736c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10047314
jmp_100473de:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x100473f0
__declspec(naked) void FUN_100473f0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10047513
		cmp edx, ebp
		jle jmp_100474b9
jmp_10047470:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10047551
jmp_100474b9:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10047551
jmp_10047513:
		cmp eax, ebp
		jge jmp_10047470
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10047551:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_100475bf
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_100475bf:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100477b7
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100477b7:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_100479fd
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_100478be
jmp_100477f4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004784c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10047818:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x17
		and edx, 0xf000000
		shr edx, 0x13
		and eax, 0x1e
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10047818
jmp_1004784c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100477f4
jmp_100478be:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10047c2e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_1004792b:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10047983
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_1004794f:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x17
		and edx, 0xf000000
		shr edx, 0x13
		and eax, 0x1e
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_1004794f
jmp_10047983:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004792b
		jmp jmp_10047c2e
jmp_100479fd:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10047af1
jmp_10047a24:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10047a7c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10047a48:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x17
		and ecx, 0xf000000
		shr ecx, 0x13
		and eax, 0x1e
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_10047a48
jmp_10047a7c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10047a24
jmp_10047af1:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10047c2e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10047b64:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10047bbc
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10047b88:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x17
		and ecx, 0xf000000
		shr ecx, 0x13
		and eax, 0x1e
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_10047b88
jmp_10047bbc:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10047b64
jmp_10047c2e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10047c40
__declspec(naked) void FUN_10047c40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10047d63
		cmp edx, ebp
		jle jmp_10047d09
jmp_10047cc0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10047da1
jmp_10047d09:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10047da1
jmp_10047d63:
		cmp eax, ebp
		jge jmp_10047cc0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10047da1:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov eax, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov dword ptr [esp + 0x84], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10047e0f
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10047e0f:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10048007
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10048007:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_1004824d
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004810e
jmp_10048044:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004809c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10048068:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x18
		and edx, 0xe000000
		shr edx, 0x15
		and eax, 0xe
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_10048068
jmp_1004809c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10048044
jmp_1004810e:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004847e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_1004817b:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100481d3
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov esi, dword ptr [esp + 0x84]
jmp_1004819f:
		mov eax, ebp
		mov edx, ebx
		shr eax, 0x18
		and edx, 0xe000000
		shr edx, 0x15
		and eax, 0xe
		or edx, eax
		mov eax, dword ptr [esp + 0x94]
		add edi, 2
		add ebp, eax
		mov dx, word ptr [esi + edx]
		mov eax, dword ptr [esp + 0x98]
		add ebx, eax
		dec ecx
		mov word ptr [edi], dx
		jns jmp_1004819f
jmp_100481d3:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004817b
		jmp jmp_1004847e
jmp_1004824d:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10048341
jmp_10048274:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_100482cc
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_10048298:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x18
		and ecx, 0xe000000
		shr ecx, 0x15
		and eax, 0xe
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_10048298
jmp_100482cc:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10048274
jmp_10048341:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004847e
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_100483b4:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004840c
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov esi, dword ptr [esp + 0x84]
jmp_100483d8:
		mov eax, ebp
		mov ecx, ebx
		shr eax, 0x18
		and ecx, 0xe000000
		shr ecx, 0x15
		and eax, 0xe
		or ecx, eax
		mov eax, dword ptr [esp + 0x94]
		sub edi, 2
		sub ebp, eax
		mov cx, word ptr [esi + ecx]
		mov eax, dword ptr [esp + 0x98]
		sub ebx, eax
		inc edx
		mov word ptr [edi], cx
		jle jmp_100483d8
jmp_1004840c:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100483b4
jmp_1004847e:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10048490
__declspec(naked) void FUN_10048490(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_100485b3
		cmp edx, ebp
		jle jmp_10048559
jmp_10048510:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_100485f1
jmp_10048559:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_100485f1
jmp_100485b3:
		cmp eax, ebp
		jge jmp_10048510
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_100485f1:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov ebx, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 0x84], ebx
		mov dword ptr [esp + 0x88], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10048669
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10048669:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10048861
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10048861:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10048ac3
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10048976
jmp_1004889e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10048904
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_100488bd:
		shr eax, 0x18
		mov edx, ebx
		and edx, 0xf000000
		and eax, 0xf
		shr edx, 0x14
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_100488bd
jmp_10048904:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004889e
jmp_10048976:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10048d10
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_100489e3:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10048a49
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_10048a02:
		shr eax, 0x18
		mov edx, ebx
		and edx, 0xf000000
		and eax, 0xf
		shr edx, 0x14
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_10048a02
jmp_10048a49:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100489e3
		jmp jmp_10048d10
jmp_10048ac3:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10048bc5
jmp_10048aea:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10048b50
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_10048b09:
		shr eax, 0x18
		mov ecx, ebx
		and ecx, 0xf000000
		and eax, 0xf
		shr ecx, 0x14
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_10048b09
jmp_10048b50:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10048aea
jmp_10048bc5:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10048d10
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10048c38:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10048c9e
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_10048c57:
		shr eax, 0x18
		mov ecx, ebx
		and ecx, 0xf000000
		and eax, 0xf
		shr ecx, 0x14
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_10048c57
jmp_10048c9e:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10048c38
jmp_10048d10:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10048d20
__declspec(naked) void FUN_10048d20(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10048e43
		cmp edx, ebp
		jle jmp_10048de9
jmp_10048da0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10048e81
jmp_10048de9:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10048e81
jmp_10048e43:
		cmp eax, ebp
		jge jmp_10048da0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10048e81:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov ebx, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 0x84], ebx
		mov dword ptr [esp + 0x88], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10048ef9
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10048ef9:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_100490f1
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_100490f1:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10049353
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10049206
jmp_1004912e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10049194
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_1004914d:
		shr eax, 0x17
		mov edx, ebx
		and edx, 0xf800000
		and eax, 0x1f
		shr edx, 0x12
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004914d
jmp_10049194:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004912e
jmp_10049206:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_100495a0
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10049273:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_100492d9
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_10049292:
		shr eax, 0x17
		mov edx, ebx
		and edx, 0xf800000
		and eax, 0x1f
		shr edx, 0x12
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_10049292
jmp_100492d9:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10049273
		jmp jmp_100495a0
jmp_10049353:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10049455
jmp_1004937a:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_100493e0
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_10049399:
		shr eax, 0x17
		mov ecx, ebx
		and ecx, 0xf800000
		and eax, 0x1f
		shr ecx, 0x12
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_10049399
jmp_100493e0:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004937a
jmp_10049455:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_100495a0
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_100494c8:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004952e
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_100494e7:
		shr eax, 0x17
		mov ecx, ebx
		and ecx, 0xf800000
		and eax, 0x1f
		shr ecx, 0x12
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_100494e7
jmp_1004952e:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100494c8
jmp_100495a0:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x100495b0
__declspec(naked) void FUN_100495b0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_100496d3
		cmp edx, ebp
		jle jmp_10049679
jmp_10049630:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10049711
jmp_10049679:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10049711
jmp_100496d3:
		cmp eax, ebp
		jge jmp_10049630
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10049711:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov ebx, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 0x84], ebx
		mov dword ptr [esp + 0x88], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_10049789
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_10049789:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_10049981
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_10049981:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_10049be3
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10049a96
jmp_100499be:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10049a24
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_100499dd:
		shr eax, 0x16
		mov edx, ebx
		and edx, 0xfc00000
		and eax, 0x3f
		shr edx, 0x10
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_100499dd
jmp_10049a24:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_100499be
jmp_10049a96:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10049e30
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_10049b03:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_10049b69
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_10049b22:
		shr eax, 0x16
		mov edx, ebx
		and edx, 0xfc00000
		and eax, 0x3f
		shr edx, 0x10
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_10049b22
jmp_10049b69:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10049b03
		jmp jmp_10049e30
jmp_10049be3:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_10049ce5
jmp_10049c0a:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10049c70
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_10049c29:
		shr eax, 0x16
		mov ecx, ebx
		and ecx, 0xfc00000
		and eax, 0x3f
		shr ecx, 0x10
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_10049c29
jmp_10049c70:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10049c0a
jmp_10049ce5:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_10049e30
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_10049d58:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_10049dbe
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_10049d77:
		shr eax, 0x16
		mov ecx, ebx
		and ecx, 0xfc00000
		and eax, 0x3f
		shr ecx, 0x10
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_10049d77
jmp_10049dbe:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_10049d58
jmp_10049e30:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x10049e40
__declspec(naked) void FUN_10049e40(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_10049f63
		cmp edx, ebp
		jle jmp_10049f09
jmp_10049ec0:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10049fa1
jmp_10049f09:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_10049fa1
jmp_10049f63:
		cmp eax, ebp
		jge jmp_10049ec0
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_10049fa1:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov ebx, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 0x84], ebx
		mov dword ptr [esp + 0x88], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_1004a019
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_1004a019:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_1004a211
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_1004a211:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_1004a473
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004a326
jmp_1004a24e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004a2b4
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_1004a26d:
		shr eax, 0x15
		mov edx, ebx
		and edx, 0xfe00000
		and eax, 0x7f
		shr edx, 0xe
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004a26d
jmp_1004a2b4:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004a24e
jmp_1004a326:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004a6c0
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_1004a393:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004a3f9
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_1004a3b2:
		shr eax, 0x15
		mov edx, ebx
		and edx, 0xfe00000
		and eax, 0x7f
		shr edx, 0xe
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004a3b2
jmp_1004a3f9:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004a393
		jmp jmp_1004a6c0
jmp_1004a473:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004a575
jmp_1004a49a:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004a500
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_1004a4b9:
		shr eax, 0x15
		mov ecx, ebx
		and ecx, 0xfe00000
		and eax, 0x7f
		shr ecx, 0xe
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_1004a4b9
jmp_1004a500:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004a49a
jmp_1004a575:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004a6c0
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_1004a5e8:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004a64e
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_1004a607:
		shr eax, 0x15
		mov ecx, ebx
		and ecx, 0xfe00000
		and eax, 0x7f
		shr ecx, 0xe
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_1004a607
jmp_1004a64e:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004a5e8
jmp_1004a6c0:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

// FUNCTION: GOLDP 0x1004a6d0
__declspec(naked) void FUN_1004a6d0(
	GolSoftwareRenderer* p_renderer,
	D3DTLVERTEX* p_vertex0,
	D3DTLVERTEX* p_vertex1,
	D3DTLVERTEX* p_vertex2
)
{
	__asm {
		mov ecx, dword ptr [esp + 8]
		mov edx, dword ptr [esp + 0xc]
		mov eax, dword ptr [g_floatConst1]
		sub esp, 0xbc
		wait
		fnstcw word ptr [esp]
		fld dword ptr [edx + 4]
		fsub dword ptr [ecx + 4]
		mov dword ptr [esp + 0xac], ebp
		mov ebp, dword ptr [esp]
		and ebp, 0xfffffcff
		mov dword ptr [esp + 0xb8], esi
		mov dword ptr [esp + 8], ebp
		fldcw word ptr [esp + 8]
		mov esi, edx
		or ebp, 0x200
		mov dword ptr [esp + 0xb0], ebx
		mov dword ptr [esp + 0xb4], edi
		mov edi, dword ptr [esp + 0xcc]
		mov eax, dword ptr [ecx + 4]
		mov edx, dword ptr [edx + 4]
		fst dword ptr [esp + 0x44]
		fdivr dword ptr [g_floatConst1]
		cmp eax, edx
		mov dword ptr [esp + 4], ebp
		mov ebp, dword ptr [edi + 4]
		mov ebx, dword ptr [esp + 0x44]
		jle jmp_1004a7f3
		cmp edx, ebp
		jle jmp_1004a799
jmp_1004a750:
		fstp dword ptr [esp + 0x58]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0x4c], ebx
		mov ebp, ecx
		mov ecx, edi
		mov edi, esi
		mov esi, ebp
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x54]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_1004a831
jmp_1004a799:
		fstp dword ptr [esp + 0x54]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fsub dword ptr [edi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x44]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		and ebx, 0x7fffffff
		mov ebp, ecx
		mov dword ptr [esp + 0x48], ebx
		mov ebx, dword ptr [esp + 0x54]
		mov ecx, esi
		mov esi, edi
		xor ebx, 0x80000000
		mov edi, ebp
		mov dword ptr [esp + 0x54], ebx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x14], edi
		fstp dword ptr [esp + 0x58]
		fdivr dword ptr [g_floatConst1]
		jmp jmp_1004a831
jmp_1004a7f3:
		cmp eax, ebp
		jge jmp_1004a750
		fld dword ptr [edi + 4]
		fsub dword ptr [ecx + 4]
		fld dword ptr [edi + 4]
		fsub dword ptr [esi + 4]
		fxch st(1)
		fst dword ptr [esp + 0x48]
		fxch st(1)
		fst dword ptr [esp + 0x4c]
		fdivr dword ptr [g_floatConst1]
		mov dword ptr [esp + 0xc], ecx
		mov dword ptr [esp + 0x10], esi
		mov dword ptr [esp + 0x14], edi
		fld1
		fdivrp st(2), st(0)
		fstp dword ptr [esp + 0x58]
		fstp dword ptr [esp + 0x54]
jmp_1004a831:
		fst dword ptr [esp + 0x50]
		fld dword ptr [edi]
		fsub dword ptr [ecx]
		fld dword ptr [ecx]
		fld dword ptr [esi]
		fsub dword ptr [edi]
		fld dword ptr [esi]
		fsub st(0), st(2)
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esp + 0x4c]
		fmul st(0), st(2)
		fxch st(2)
		fmulp st(5), st(0)
		faddp st(1), st(0)
		mov ebp, dword ptr [esp + 0xc0]
		fdivr dword ptr [g_floatConst1]
		mov eax, dword ptr [ebp + 0x34]
		mov ebx, dword ptr [ebp + 4]
		mov ebp, dword ptr [ebp]
		mov dword ptr [esp + 0x74], ebx
		mov ebx, dword ptr [eax]
		mov dword ptr [esp + 0x70], ebp
		mov eax, dword ptr [eax + 0x14]
		mov dword ptr [esp + 0x84], ebx
		mov dword ptr [esp + 0x88], eax
		lea eax, [esp + 0x24]
		mov ebx, dword ptr [esp + 0x4c]
		and eax, 0xfffffff8
		or ebx, ebx
		mov dword ptr [esp + 0x1c], eax
		mov ebp, dword ptr [esp + 0x54]
		mov dword ptr [esp + 0x18], edi
		jns jmp_1004a8a9
		mov ebp, dword ptr [esp + 0x50]
		mov dword ptr [esp + 0x18], esi
jmp_1004a8a9:
		mov dword ptr [esp + 0x20], ebp
		fstp dword ptr [esp + 0x5c]
		fldcw word ptr [esp + 4]
		mov ebp, dword ptr [esp + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [edi + 0x18]
		fld dword ptr [esi + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x44]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [edi + 0x1c]
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [esi + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fxch st(3)
		fmul dword ptr [esp + 0x44]
		fxch st(1)
		faddp st(2), st(0)
		fxch st(2)
		fmul dword ptr [esp + 0x4c]
		fld dword ptr [ecx + 0x18]
		fadd dword ptr [g_unk0x100579a8]
		fxch st(2)
		fmul dword ptr [esp + 0x5c]
		fxch st(1)
		faddp st(3), st(0)
		fld dword ptr [ecx + 0x1c]
		fld dword ptr [esp + 0x5c]
		fmulp st(4), st(0)
		fadd dword ptr [g_unk0x100579a8]
		fld dword ptr [g_unk0x100579a8]
		fadd st(2), st(0)
		faddp st(4), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fld dword ptr [ebp + 0x1c]
		fsub dword ptr [ecx + 0x1c]
		fld dword ptr [ebp + 0x18]
		fsub dword ptr [ecx + 0x18]
		fxch st(1)
		fmul dword ptr [esp + 0x20]
		fld dword ptr [esp + 0x20]
		fmulp st(2), st(0)
		fld dword ptr [g_unk0x100579a8]
		fadd st(1), st(0)
		faddp st(2), st(0)
		mov dword ptr [esp + 0x90], ebx
		mov dword ptr [esp + 0x94], edx
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x98], edx
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax + 8]
		mov edx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0xa0], ebx
		mov dword ptr [esp + 0x9c], edx
		fld dword ptr [esp + 0x54]
		fmulp st(2), st(0)
		fld dword ptr [edi + 4]
		fld dword ptr [esi + 4]
		fld dword ptr [ecx + 4]
		fld dword ptr [g_unk0x10057980]
		fadd st(1), st(0)
		fadd st(2), st(0)
		fadd st(3), st(0)
		fadd st(4), st(0)
		fadd st(5), st(0)
		faddp st(6), st(0)
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebx, dword ptr [eax]
		mov ebp, dword ptr [eax + 8]
		mov dword ptr [esp + 0x78], ebx
		mov ebx, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x7c], ebp
		mov dword ptr [esp + 0x80], ebx
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov ebp, dword ptr [eax + 8]
		mov ebx, dword ptr [esp + 0x78]
		mov edx, dword ptr [eax]
		mov dword ptr [esp + 0x68], ebp
		xor ebp, ebp
		mov dword ptr [esp + 0x60], edx
		sub ebp, ebx
		mov dword ptr [esp + 0x64], edx
		mov edx, dword ptr [eax + 0x10]
		and ebp, 0xffff
		mov dword ptr [esp + 0x6c], edx
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x20], ebp
		je jmp_1004aaa1
		fild dword ptr [esp + 0x20]
		fld dword ptr [ecx]
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld st(0)
		fild dword ptr [esp + 0x9c]
		fild dword ptr [esp + 0xa0]
		fld st(3)
		fmulp st(2), st(0)
		mov ecx, dword ptr [esp + 0x8c]
		mov edx, dword ptr [esp + 0x90]
		fmulp st(2), st(0)
		fadd dword ptr [g_unk0x10057978]
		fld dword ptr [g_unk0x10057978]
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		fmul dword ptr [g_unk0x10057970]
		mov esi, dword ptr [eax + 8]
		mov edi, dword ptr [eax + 0x10]
		add ecx, esi
		add edx, edi
		mov dword ptr [esp + 0x8c], ecx
		mov dword ptr [esp + 0x90], edx
		fild dword ptr [esp + 0x68]
		fild dword ptr [esp + 0x6c]
		fxch st(2)
		fmul st(1), st(0)
		add ebx, ebp
		fmulp st(2), st(0)
		mov edi, dword ptr [esp + 0x4c]
		mov dword ptr [esp + 0x78], ebx
		fadd st(0), st(2)
		fxch st(1)
		faddp st(2), st(0)
		fstp qword ptr [eax + 8]
		fstp qword ptr [eax + 0x10]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax + 0x10]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ebp
jmp_1004aaa1:
		sar ebx, 0x10
		mov eax, dword ptr [esp + 0x74]
		imul ebx
		or edi, edi
		mov ebx, dword ptr [esp + 0x78]
		mov edi, dword ptr [esp + 0x70]
		js jmp_1004ad07
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x7c]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004abb8
jmp_1004aade:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004ab46
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_1004aafd:
		shr eax, 0x14
		mov edx, ebx
		and edx, 0xff00000
		and eax, 0xff
		shr edx, 0xc
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004aafd
jmp_1004ab46:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004aade
jmp_1004abb8:
		mov ecx, dword ptr [esp + 0x80]
		mov edx, dword ptr [esp + 0x7c]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004af58
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [esi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov edx, dword ptr [esp + 0x60]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		mov ecx, dword ptr [eax + 8]
		mov dword ptr [esp + 0x6c], ebp
		mov dword ptr [esp + 0x64], ecx
jmp_1004ac25:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub ecx, edx
		jl jmp_1004ac8d
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + edx*2 - 2]
		mov eax, ebp
jmp_1004ac44:
		shr eax, 0x14
		mov edx, ebx
		and edx, 0xff00000
		and eax, 0xff
		shr edx, 0xc
		mov esi, dword ptr [esp + 0x84]
		or eax, edx
		mov edx, dword ptr [esp + 0x94]
		add ebp, edx
		xor edx, edx
		mov dl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		add edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov dx, word ptr [esi + edx*2]
		add ebx, eax
		dec ecx
		mov eax, ebp
		mov word ptr [edi], dx
		jns jmp_1004ac44
jmp_1004ac8d:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004ac25
		jmp jmp_1004af58
jmp_1004ad07:
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov eax, dword ptr [esp + 0x80]
		add edx, 0xffff
		cmp ebx, eax
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x70], edi
		jge jmp_1004ae0b
jmp_1004ad2e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004ad96
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_1004ad4d:
		shr eax, 0x14
		mov ecx, ebx
		and ecx, 0xff00000
		and eax, 0xff
		shr ecx, 0xc
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_1004ad4d
jmp_1004ad96:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x80]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004ad2e
jmp_1004ae0b:
		mov ecx, dword ptr [esp + 0x7c]
		mov edx, dword ptr [esp + 0x80]
		cmp ebx, ecx
		mov esi, dword ptr [esp + 0x10]
		mov edi, dword ptr [esp + 0x14]
		jge jmp_1004af58
		sub ebx, edx
		mov eax, dword ptr [esp + 0x1c]
		mov dword ptr [esp + 0x20], ebx
		fild dword ptr [esp + 0x20]
		fld dword ptr [edi]
		fsub dword ptr [esi]
		fxch st(1)
		fmul dword ptr [g_unk0x10057970]
		fld dword ptr [esp + 0x58]
		fmulp st(2), st(0)
		fld dword ptr [edi]
		fadd dword ptr [g_unk0x10057980]
		fld st(2)
		fmulp st(2), st(0)
		fxch st(2)
		fadd dword ptr [g_unk0x10057980]
		fxch st(1)
		faddp st(2), st(0)
		mov ecx, dword ptr [esp + 0x64]
		mov edi, dword ptr [esp + 0x70]
		fstp qword ptr [eax]
		fstp qword ptr [eax + 8]
		mov edx, dword ptr [eax + 8]
		mov ebp, dword ptr [eax]
		add edx, 0xffff
		mov dword ptr [esp + 0x68], ebp
		mov dword ptr [esp + 0x60], edx
jmp_1004ae7e:
		sar edx, 0x10
		dec ecx
		sar ecx, 0x10
		sub edx, ecx
		jg jmp_1004aee6
		mov ebp, dword ptr [esp + 0x8c]
		mov ebx, dword ptr [esp + 0x90]
		lea edi, [edi + ecx*2 + 2]
		mov eax, ebp
jmp_1004ae9d:
		shr eax, 0x14
		mov ecx, ebx
		and ecx, 0xff00000
		and eax, 0xff
		shr ecx, 0xc
		mov esi, dword ptr [esp + 0x84]
		or eax, ecx
		mov ecx, dword ptr [esp + 0x94]
		sub ebp, ecx
		xor ecx, ecx
		mov cl, byte ptr [esi + eax]
		mov esi, dword ptr [esp + 0x88]
		sub edi, 2
		mov eax, dword ptr [esp + 0x98]
		mov cx, word ptr [esi + ecx*2]
		sub ebx, eax
		inc edx
		mov eax, ebp
		mov word ptr [edi], cx
		jle jmp_1004ae9d
jmp_1004aee6:
		mov ebx, dword ptr [esp + 0x8c]
		mov eax, dword ptr [esp + 0x9c]
		mov edx, dword ptr [esp + 0x90]
		mov edi, dword ptr [esp + 0xa0]
		add ebx, eax
		add edx, edi
		mov dword ptr [esp + 0x8c], ebx
		mov dword ptr [esp + 0x90], edx
		mov edi, dword ptr [esp + 0x70]
		mov eax, dword ptr [esp + 0x74]
		mov esi, dword ptr [esp + 0x68]
		mov ebp, dword ptr [esp + 0x6c]
		add edi, eax
		mov edx, dword ptr [esp + 0x60]
		mov ecx, dword ptr [esp + 0x64]
		mov dword ptr [esp + 0x70], edi
		mov ebx, dword ptr [esp + 0x78]
		add edx, esi
		add ebx, 0x10000
		mov eax, dword ptr [esp + 0x7c]
		add ecx, ebp
		cmp ebx, eax
		mov dword ptr [esp + 0x60], edx
		mov dword ptr [esp + 0x64], ecx
		mov dword ptr [esp + 0x78], ebx
		jl jmp_1004ae7e
jmp_1004af58:
		fldcw word ptr [esp]
		add esp, 0xac
		pop ebp
		pop ebx
		pop edi
		pop esi
		ret
	}
}

#endif
