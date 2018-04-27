	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 1
	.intel_syntax noprefix
	.def	 _beginFunc;
	.scl	2;
	.type	32;
	.endef
	.globl	_beginFunc              # -- Begin function beginFunc
_beginFunc:                             # @beginFunc
# %bb.0:
	ret
                                        # -- End function
	.def	 _getValue;
	.scl	2;
	.type	32;
	.endef
	.globl	_getValue               # -- Begin function getValue
_getValue:                              # @getValue
# %bb.0:
	mov	eax, dword ptr [esp + 4]
	mov	eax, dword ptr [eax]
	ret
                                        # -- End function
	.def	 _allobj;
	.scl	2;
	.type	32;
	.endef
	.globl	_allobj                 # -- Begin function allobj
_allobj:                                # @allobj
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	ecx, dword ptr [81790168]
	xor	eax, eax
	test	ecx, ecx
	je	LBB2_8
# %bb.1:
	mov	ebx, dword ptr [ecx + 188]
	test	ebx, ebx
	je	LBB2_8
# %bb.2:
	mov	edi, dword ptr [ebx + 192]
	mov	esi, dword ptr [esp + 24]
	mov	ebx, dword ptr [ebx + 196]
	xor	eax, eax
	jmp	LBB2_3
LBB2_4:                                 #   in Loop: Header=BB2_3 Depth=1
	mov	ebp, dword ptr [edi]
	mov	ecx, dword ptr [ebp + 2088]
	cmp	ecx, dword ptr [esp + 20]
	sete	dl
	cmp	ecx, 101
	sete	cl
	or	cl, dl
	cmp	cl, 1
	jne	LBB2_7
# %bb.5:                                #   in Loop: Header=BB2_3 Depth=1
	mov	ecx, dword ptr [ebp + 152]
	and	ecx, esi
	cmp	ecx, esi
	jne	LBB2_7
# %bb.6:                                #   in Loop: Header=BB2_3 Depth=1
	mov	ecx, dword ptr [esp + 28]
	mov	dword ptr [ecx + 4*eax], ebp
	inc	eax
LBB2_7:                                 #   in Loop: Header=BB2_3 Depth=1
	add	edi, 4
LBB2_3:                                 # =>This Inner Loop Header: Depth=1
	cmp	edi, ebx
	jl	LBB2_4
LBB2_8:
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _getHp;
	.scl	2;
	.type	32;
	.endef
	.globl	_getHp                  # -- Begin function getHp
_getHp:                                 # @getHp
# %bb.0:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	edi
	push	esi
	push	eax
	#APP

	pushal
	mov	ecx, dword ptr [ebp + 8]
	mov	eax, dword ptr [ecx]
	call	dword ptr [eax + 1036]
	mov	dword ptr [ebp - 16], eax
	popal

	#NO_APP
	mov	eax, dword ptr [ebp - 16]
	add	esp, 4
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _getAllHp;
	.scl	2;
	.type	32;
	.endef
	.globl	_getAllHp               # -- Begin function getAllHp
_getAllHp:                              # @getAllHp
# %bb.0:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	edi
	push	esi
	sub	esp, 220
	lea	eax, [ebp - 232]
	xor	esi, esi
	push	eax
	push	17
	push	100
	call	_allobj
	add	esp, 12
	mov	dword ptr [ebp - 16], eax # 4-byte Spill
	xor	eax, eax
	jmp	LBB4_1
LBB4_3:                                 #   in Loop: Header=BB4_1 Depth=1
	mov	dword ptr [ebp - 20], eax # 4-byte Spill
	mov	eax, dword ptr [ebp + 4*esi - 232]
	mov	dword ptr [ebp - 24], esi # 4-byte Spill
	mov	dword ptr [ebp - 32], eax
	#APP

	pushal
	mov	ecx, dword ptr [ebp - 32]
	mov	eax, dword ptr [ecx]
	call	dword ptr [eax + 1036]
	mov	dword ptr [ebp - 28], eax
	popal

	#NO_APP
	mov	eax, dword ptr [ebp - 20] # 4-byte Reload
	mov	esi, dword ptr [ebp - 24] # 4-byte Reload
	add	eax, dword ptr [ebp - 28]
	inc	esi
LBB4_1:                                 # =>This Inner Loop Header: Depth=1
	cmp	esi, dword ptr [ebp - 16] # 4-byte Folded Reload
	jl	LBB4_3
# %bb.2:
	add	esp, 220
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _killit_kouxue;
	.scl	2;
	.type	32;
	.endef
	.globl	_killit_kouxue          # -- Begin function killit_kouxue
_killit_kouxue:                         # @killit_kouxue
# %bb.0:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	edi
	push	esi
	#APP

	pushal
	mov	ecx, dword ptr [ebp + 8]
	push	0
	push	0
	push	0
	push	ecx
	push	1
	push	0
	push	0
	mov	eax, 32585568
	call	eax
	popal

	#NO_APP
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _killthemall;
	.scl	2;
	.type	32;
	.endef
	.globl	_killthemall            # -- Begin function killthemall
_killthemall:                           # @killthemall
# %bb.0:
	push	ebp
	mov	ebp, esp
	push	ebx
	push	edi
	push	esi
	sub	esp, 212
	lea	eax, [ebp - 224]
	xor	esi, esi
	push	eax
	push	17
	push	100
	call	_allobj
	add	esp, 12
	mov	dword ptr [ebp - 16], eax # 4-byte Spill
	jmp	LBB6_1
LBB6_3:                                 #   in Loop: Header=BB6_1 Depth=1
	mov	eax, dword ptr [ebp + 4*esi - 224]
	mov	dword ptr [ebp - 20], esi # 4-byte Spill
	mov	dword ptr [ebp - 24], eax
	#APP

	pushal
	mov	ecx, dword ptr [ebp - 24]
	push	0
	push	0
	push	0
	push	ecx
	push	1
	push	0
	push	0
	mov	eax, 32585568
	call	eax
	popal

	#NO_APP
	mov	esi, dword ptr [ebp - 20] # 4-byte Reload
	inc	esi
LBB6_1:                                 # =>This Inner Loop Header: Depth=1
	cmp	esi, dword ptr [ebp - 16] # 4-byte Folded Reload
	jl	LBB6_3
# %bb.2:
	add	esp, 212
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _killthemall_end;
	.scl	2;
	.type	32;
	.endef
	.globl	_killthemall_end        # -- Begin function killthemall_end
_killthemall_end:                       # @killthemall_end
# %bb.0:
	ret
                                        # -- End function
	.def	 _hookcode_allhpdmg;
	.scl	2;
	.type	32;
	.endef
	.globl	_hookcode_allhpdmg      # -- Begin function hookcode_allhpdmg
_hookcode_allhpdmg:                     # @hookcode_allhpdmg
# %bb.0:
	sub	esp, 8
	#APP

	mov	eax, dword ptr [ebp + 12]
	mov	dword ptr [esp + 4], eax

	#NO_APP
	mov	eax, dword ptr [esp + 4]
	mov	ecx, dword ptr [eax + 152]
	and	ecx, 17
	push	17
	pop	edx
	cmp	ecx, edx
	jne	LBB8_5
# %bb.1:
	cmp	dword ptr [eax + 2088], 0
	je	LBB8_2
# %bb.3:
	call	_getAllHp
	jmp	LBB8_4
LBB8_2:
	xor	eax, eax
	inc	eax
LBB8_4:
	mov	dword ptr [esp], eax
	#APP

	cvtsi2ss	xmm0, dword ptr [esp]

	#NO_APP
LBB8_5:
	add	esp, 8
	ret
                                        # -- End function
	.def	 _hookcode_allhpdmg_end;
	.scl	2;
	.type	32;
	.endef
	.globl	_hookcode_allhpdmg_end  # -- Begin function hookcode_allhpdmg_end
_hookcode_allhpdmg_end:                 # @hookcode_allhpdmg_end
# %bb.0:
	ret
                                        # -- End function
	.def	 _endFunc;
	.scl	2;
	.type	32;
	.endef
	.globl	_endFunc                # -- Begin function endFunc
_endFunc:                               # @endFunc
# %bb.0:
	ret
                                        # -- End function
	.def	 _readyCodeToTarget;
	.scl	2;
	.type	32;
	.endef
	.globl	_readyCodeToTarget      # -- Begin function readyCodeToTarget
_readyCodeToTarget:                     # @readyCodeToTarget
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	edi, dword ptr [esp + 20]
	mov	ebp, offset _beginFunc
	mov	ebx, offset _endFunc
	sub	ebx, ebp
	inc	ebx
	push	16
	push	4096
	push	ebx
	push	0
	push	edi
	call	dword ptr [__imp__VirtualAllocEx@20]
	mov	esi, eax
	test	esi, esi
	je	LBB11_1
# %bb.2:
	push	0
	push	ebx
	push	ebp
	push	esi
	push	edi
	call	_WriteProcessMemoryForce
	add	esp, 20
	mov	edi, eax
	push	esi
	push	ebx
	push	offset "??_C@_0BD@HOOLOPHD@write?5?$CFd?5bytes?5?$CFx?6?$AA@"
	call	_printf
	add	esp, 12
	test	edi, edi
	cmove	esi, edi
	jmp	LBB11_3
LBB11_1:
	xor	esi, esi
LBB11_3:
	mov	eax, esi
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
	.def	 _killAll;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	_killAll                # -- Begin function killAll
_killAll:                               # @killAll
# %bb.0:
	push	edi
	push	esi
	mov	edi, dword ptr [_feature]
	call	_getLoopPoint
	mov	esi, eax
	push	1
	push	offset _killthemall_end
	push	offset _killthemall
	push	esi
	push	edi
	call	_hookFromFunc
	add	esp, 20
	push	50
	call	dword ptr [__imp__Sleep@4]
	push	esi
	push	edi
	call	_hookRecovery
	pop	ecx
	pop	edx
	pop	esi
	pop	edi
	ret
                                        # -- End function
	.def	 _featureInit;
	.scl	2;
	.type	32;
	.endef
	.globl	_featureInit            # -- Begin function featureInit
_featureInit:                           # @featureInit
# %bb.0:
	push	offset "??_C@_07MKFODLIK@DNF?4exe?$AA@"
	call	_getProcessByName
	pop	ecx
	mov	dword ptr [_feature], eax
	mov	dword ptr [_feature+4], edx
	push	eax
	call	_readyCodeToTarget
	pop	ecx
	mov	dword ptr [_feature+8], eax
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
	.section	.rdata,"dr",discard,"??_C@_0BD@HOOLOPHD@write?5?$CFd?5bytes?5?$CFx?6?$AA@"
	.globl	"??_C@_0BD@HOOLOPHD@write?5?$CFd?5bytes?5?$CFx?6?$AA@" # @"\01??_C@_0BD@HOOLOPHD@write?5?$CFd?5bytes?5?$CFx?6?$AA@"
"??_C@_0BD@HOOLOPHD@write?5?$CFd?5bytes?5?$CFx?6?$AA@":
	.asciz	"write %d bytes %x\n"

	.comm	_feature,16,2           # @feature
	.section	.rdata,"dr",discard,"??_C@_07MKFODLIK@DNF?4exe?$AA@"
	.globl	"??_C@_07MKFODLIK@DNF?4exe?$AA@" # @"\01??_C@_07MKFODLIK@DNF?4exe?$AA@"
"??_C@_07MKFODLIK@DNF?4exe?$AA@":
	.asciz	"DNF.exe"

	.lcomm	___local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:uuid.lib"

