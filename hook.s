	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 1
	.intel_syntax noprefix
	.def	 _hook;
	.scl	2;
	.type	32;
	.endef
	.globl	_hook                   # -- Begin function hook
_hook:                                  # @hook
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	sub	esp, 20
	mov	ebp, dword ptr [esp + 44]
	mov	ebx, dword ptr [esp + 52]
	mov	eax, dword ptr [ebp + 8]
	lea	edi, [ebx + eax + 5]
	push	edi
	call	_malloc
	pop	ecx
	mov	esi, eax
	push	ebx
	push	dword ptr [esp + 52]
	push	esi
	call	_memcpy
	add	esp, 12
	mov	eax, dword ptr [ebp + 12]
	mov	dword ptr [esp + 4], edi # 4-byte Spill
	test	eax, eax
	je	LBB0_1
# %bb.2:
	lea	ecx, [esp + 8]
	push	ecx
	push	64
	push	dword ptr [ebp + 16]
	push	eax
	push	dword ptr [esp + 56]
	call	dword ptr [__imp__VirtualProtectEx@20]
	mov	eax, dword ptr [ebp + 12]
	jmp	LBB0_3
LBB0_1:
	push	64
	push	4096
	push	edi
	push	0
	push	dword ptr [esp + 56]
	call	dword ptr [__imp__VirtualAllocEx@20]
	mov	dword ptr [ebp + 12], eax
	mov	dword ptr [ebp + 16], edi
LBB0_3:
	mov	edi, ebp
	test	eax, eax
	mov	dword ptr [esp], eax    # 4-byte Spill
	jne	LBB0_5
# %bb.4:
	call	_printErrCode
LBB0_5:
	mov	ebp, dword ptr [edi + 8]
	mov	eax, esi
	add	eax, ebx
	push	ebp
	push	dword ptr [edi + 4]
	push	eax
	call	_memcpy
	add	esp, 12
	mov	ecx, dword ptr [esp + 4] # 4-byte Reload
	mov	edx, dword ptr [esp]    # 4-byte Reload
	add	ebx, ebp
	mov	byte ptr [esi + ebx], -23
	lea	eax, [edx + ecx]
	sub	ebp, eax
	add	ebp, dword ptr [edi]
	mov	dword ptr [esi + ebx + 1], ebp
	push	0
	push	ecx
	push	esi
	push	edx
	mov	ebp, dword ptr [esp + 56]
	push	ebp
	call	dword ptr [__imp__WriteProcessMemory@20]
	mov	ebx, eax
	push	esi
	call	_free
	pop	eax
	test	ebx, ebx
	je	LBB0_6
# %bb.7:
	lea	eax, [esp + 15]
	mov	esi, dword ptr [esp]    # 4-byte Reload
	mov	byte ptr [eax], -23
	mov	ecx, dword ptr [edi]
	lea	edx, [esi - 5]
	sub	edx, ecx
	mov	dword ptr [eax + 1], edx
	push	0
	push	5
	push	eax
	push	ecx
	push	ebp
	call	_WriteProcessMemoryForce
	add	esp, 20
	test	eax, eax
	cmove	esi, eax
	mov	eax, esi
	jmp	LBB0_8
LBB0_6:
	xor	eax, eax
LBB0_8:
	add	esp, 20
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _hookKeepRegi;
	.scl	2;
	.type	32;
	.endef
	.globl	_hookKeepRegi           # -- Begin function hookKeepRegi
_hookKeepRegi:                          # @hookKeepRegi
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	edi, dword ptr [esp + 32]
	mov	ebp, dword ptr [esp + 28]
	lea	ebx, [edi + 1]
	push	ebx
	call	_malloc
	pop	ecx
	mov	esi, eax
	mov	byte ptr [esi], 96
	lea	eax, [esi + 1]
	push	edi
	push	ebp
	push	eax
	call	_memcpy
	add	esp, 12
	mov	byte ptr [esi + edi], 97
	push	ebx
	push	esi
	push	offset "??_C@_05EPNLOEEB@?$CFx?5?$CFd?$AA@"
	call	_printf
	add	esp, 12
	mov	eax, dword ptr [esp + 24]
	mov	dword ptr [eax + 16], ebx
	push	ebx
	push	esi
	push	eax
	push	dword ptr [esp + 32]
	call	_hook
	add	esp, 16
	mov	edi, eax
	push	esi
	call	_free
	pop	eax
	mov	eax, edi
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_printf
	.globl	_printf                 # -- Begin function printf
_printf:                                # @printf
# %bb.0:
	push	edi
	push	esi
	push	eax
	mov	esi, dword ptr [esp + 16]
	lea	edi, [esp + 20]
	mov	dword ptr [esp], edi
	push	1
	call	___acrt_iob_func
	pop	ecx
	push	edi
	push	0
	push	esi
	push	eax
	call	__vfprintf_l
	add	esp, 20
	pop	esi
	pop	edi
	ret
                                        # -- End function
	.def	 _hookFromFunc;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	_hookFromFunc           # -- Begin function hookFromFunc
_hookFromFunc:                          # @hookFromFunc
# %bb.0:
	push	esi
	mov	edx, dword ptr [esp + 16]
	mov	esi, dword ptr [esp + 20]
	mov	ecx, dword ptr [esp + 12]
	mov	eax, dword ptr [esp + 8]
	sub	esi, edx
	cmp	dword ptr [esp + 24], 0
	je	LBB3_3
# %bb.1:
	push	esi
	push	edx
	push	ecx
	push	eax
	call	_hookKeepRegi
	jmp	LBB3_2
LBB3_3:
	push	esi
	push	edx
	push	ecx
	push	eax
	call	_hook
LBB3_2:
	add	esp, 16
	pop	esi
	ret
                                        # -- End function
	.def	 _hookRecovery;
	.scl	2;
	.type	32;
	.endef
	.globl	_hookRecovery           # -- Begin function hookRecovery
_hookRecovery:                          # @hookRecovery
# %bb.0:
	push	edi
	push	esi
	push	eax
	mov	edi, dword ptr [esp + 20]
	mov	esi, dword ptr [esp + 16]
	push	0
	push	dword ptr [edi + 8]
	push	dword ptr [edi + 4]
	push	dword ptr [edi]
	push	esi
	call	_WriteProcessMemoryForce
	add	esp, 20
	test	eax, eax
	je	LBB4_1
# %bb.2:
	mov	eax, esp
	push	eax
	push	1
	push	dword ptr [edi + 16]
	push	dword ptr [edi + 12]
	push	esi
	call	dword ptr [__imp__VirtualProtectEx@20]
	mov	esi, eax
	test	esi, esi
	jne	LBB4_4
# %bb.3:
	call	_printErrCode
	jmp	LBB4_4
LBB4_1:
	xor	esi, esi
LBB4_4:
	mov	eax, esi
	add	esp, 4
	pop	esi
	pop	edi
	ret
                                        # -- End function
	.def	 _getLoopPoint;
	.scl	2;
	.type	32;
	.endef
	.globl	_getLoopPoint           # -- Begin function getLoopPoint
_getLoopPoint:                          # @getLoopPoint
# %bb.0:
	mov	eax, dword ptr [_loopPoint]
	test	eax, eax
	je	LBB5_1
# %bb.2:
	ret
LBB5_1:
	push	20
	call	_malloc
	pop	ecx
	mov	dword ptr [eax], 36371150
	mov	dword ptr [eax + 4], offset _loopPointOB
	mov	dword ptr [eax + 8], 6
	and	dword ptr [eax + 12], 0
	and	dword ptr [eax + 16], 0
	mov	dword ptr [_loopPoint], eax
	ret
                                        # -- End function
	.def	 _getAllHpDmgPoint;
	.scl	2;
	.type	32;
	.endef
	.globl	_getAllHpDmgPoint       # -- Begin function getAllHpDmgPoint
_getAllHpDmgPoint:                      # @getAllHpDmgPoint
# %bb.0:
	mov	eax, dword ptr [_allHpDmgPoint]
	test	eax, eax
	je	LBB6_1
# %bb.2:
	ret
LBB6_1:
	push	20
	call	_malloc
	pop	ecx
	mov	dword ptr [eax], 47319518
	mov	dword ptr [eax + 4], offset _getAllHpDmgOB
	mov	dword ptr [eax + 8], 5
	and	dword ptr [eax + 12], 0
	and	dword ptr [eax + 16], 0
	mov	dword ptr [_allHpDmgPoint], eax
	ret
                                        # -- End function
	.def	 ___local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,___local_stdio_printf_options
	.globl	___local_stdio_printf_options # -- Begin function __local_stdio_printf_options
___local_stdio_printf_options:          # @__local_stdio_printf_options
# %bb.0:
	mov	eax, offset ___local_stdio_printf_options._OptionsStorage
	ret
                                        # -- End function
	.def	 __vfprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__vfprintf_l
	.globl	__vfprintf_l            # -- Begin function _vfprintf_l
__vfprintf_l:                           # @_vfprintf_l
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	esi, dword ptr [esp + 20]
	mov	edi, dword ptr [esp + 24]
	mov	ebx, dword ptr [esp + 28]
	mov	ebp, dword ptr [esp + 32]
	call	___local_stdio_printf_options
	push	ebp
	push	ebx
	push	edi
	push	esi
	push	dword ptr [eax + 4]
	push	dword ptr [eax]
	call	___stdio_common_vfprintf
	add	esp, 24
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.section	.rdata,"dr",discard,"??_C@_05EPNLOEEB@?$CFx?5?$CFd?$AA@"
	.globl	"??_C@_05EPNLOEEB@?$CFx?5?$CFd?$AA@" # @"\01??_C@_05EPNLOEEB@?$CFx?5?$CFd?$AA@"
"??_C@_05EPNLOEEB@?$CFx?5?$CFd?$AA@":
	.asciz	"%x %d"

	.lcomm	_loopPoint,4,4          # @loopPoint
	.data
_loopPointOB:                           # @loopPointOB
	.asciz	"\213\220\024\006\000"

	.lcomm	_allHpDmgPoint,4,4      # @allHpDmgPoint
_getAllHpDmgOB:                         # @getAllHpDmgOB
	.ascii	"\363\017\021E\b"

	.lcomm	___local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:uuid.lib"

