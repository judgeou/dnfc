	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 1
	.intel_syntax noprefix
	.def	 _sprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_sprintf
	.globl	_sprintf                # -- Begin function sprintf
_sprintf:                               # @sprintf
# %bb.0:
	push	eax
	mov	eax, dword ptr [esp + 8]
	mov	ecx, dword ptr [esp + 12]
	lea	edx, [esp + 16]
	mov	dword ptr [esp], edx
	push	edx
	push	0
	push	ecx
	push	eax
	call	__vsprintf_l
	add	esp, 16
	pop	ecx
	ret
                                        # -- End function
	.def	 _printErrCode;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	_printErrCode           # -- Begin function printErrCode
_printErrCode:                          # @printErrCode
# %bb.0:
	call	dword ptr [__imp__GetLastError@0]
	push	eax
	push	offset "??_C@_0P@MBPEHPOC@ErrorCode?3?5?$CFd?6?$AA@"
	call	_printf
	pop	ecx
	pop	edx
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
	.def	 _readPointerBuffer;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	_readPointerBuffer      # -- Begin function readPointerBuffer
_readPointerBuffer:                     # @readPointerBuffer
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	push	eax
	mov	ebp, dword ptr [esp + 32]
	mov	ecx, dword ptr [esp + 44]
	mov	eax, dword ptr [esp + 24]
	test	ebp, ebp
	je	LBB3_1
# %bb.2:
	mov	edx, esp
	push	0
	push	4
	push	edx
	push	eax
	push	ecx
	call	dword ptr [__imp__ReadProcessMemory@20]
	mov	edi, dword ptr [__imp__ReadProcessMemory@20]
	lea	ebx, [ebp - 1]
	xor	esi, esi
	jmp	LBB3_3
LBB3_4:                                 #   in Loop: Header=BB3_3 Depth=1
	mov	eax, dword ptr [esp + 28]
	mov	eax, dword ptr [eax + 4*esi]
	add	eax, dword ptr [esp]
	cmp	ebx, esi
	jne	LBB3_6
# %bb.5:                                #   in Loop: Header=BB3_3 Depth=1
	push	0
	push	dword ptr [esp + 40]
	push	dword ptr [esp + 48]
	push	eax
	push	dword ptr [esp + 60]
	jmp	LBB3_7
LBB3_6:                                 #   in Loop: Header=BB3_3 Depth=1
	push	0
	push	4
	lea	ecx, [esp + 8]
	push	ecx
	push	eax
	push	dword ptr [esp + 60]
LBB3_7:                                 #   in Loop: Header=BB3_3 Depth=1
	call	edi
	inc	esi
LBB3_3:                                 # =>This Inner Loop Header: Depth=1
	cmp	esi, ebp
	jl	LBB3_4
# %bb.8:
	xor	eax, eax
	inc	eax
	jmp	LBB3_9
LBB3_1:
	push	0
	push	dword ptr [esp + 40]
	push	dword ptr [esp + 48]
	push	eax
	push	ecx
	call	dword ptr [__imp__ReadProcessMemory@20]
LBB3_9:
	add	esp, 4
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _WriteProcessMemoryForce;
	.scl	2;
	.type	32;
	.endef
	.globl	_WriteProcessMemoryForce # -- Begin function WriteProcessMemoryForce
_WriteProcessMemoryForce:               # @WriteProcessMemoryForce
# %bb.0:
	push	ebx
	push	edi
	push	esi
	sub	esp, 8
	mov	ebx, dword ptr [esp + 36]
	mov	edi, dword ptr [esp + 28]
	mov	esi, dword ptr [esp + 24]
	mov	eax, esp
	push	eax
	push	64
	push	ebx
	push	edi
	push	esi
	call	dword ptr [__imp__VirtualProtectEx@20]
	test	eax, eax
	je	LBB4_1
# %bb.2:
	push	dword ptr [esp + 40]
	push	ebx
	push	dword ptr [esp + 40]
	push	edi
	push	esi
	call	dword ptr [__imp__WriteProcessMemory@20]
	lea	eax, [esp + 4]
	push	eax
	push	dword ptr [esp + 4]
	push	ebx
	push	edi
	push	esi
	call	dword ptr [__imp__VirtualProtectEx@20]
	jmp	LBB4_3
LBB4_1:
	xor	eax, eax
LBB4_3:
	add	esp, 8
	pop	esi
	pop	edi
	pop	ebx
	ret
                                        # -- End function
	.def	 _writePointerBuffer;
	.scl	2;
	.type	32;
	.endef
	.globl	_writePointerBuffer     # -- Begin function writePointerBuffer
_writePointerBuffer:                    # @writePointerBuffer
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	push	eax
	mov	ebx, dword ptr [esp + 32]
	mov	ecx, dword ptr [esp + 44]
	mov	eax, dword ptr [esp + 24]
	test	ebx, ebx
	je	LBB5_1
# %bb.2:
	mov	edx, esp
	push	0
	push	4
	push	edx
	push	eax
	push	ecx
	call	dword ptr [__imp__ReadProcessMemory@20]
	mov	esi, dword ptr [__imp__ReadProcessMemory@20]
	lea	edi, [ebx - 1]
	xor	ebp, ebp
	jmp	LBB5_3
LBB5_5:                                 #   in Loop: Header=BB5_3 Depth=1
	mov	eax, dword ptr [esp + 28]
	mov	eax, dword ptr [eax + 4*ebp]
	add	eax, dword ptr [esp]
	cmp	edi, ebp
	je	LBB5_7
# %bb.6:                                #   in Loop: Header=BB5_3 Depth=1
	push	0
	push	4
	lea	ecx, [esp + 8]
	push	ecx
	push	eax
	push	dword ptr [esp + 60]
	call	esi
	inc	ebp
LBB5_3:                                 # =>This Inner Loop Header: Depth=1
	cmp	ebp, ebx
	jl	LBB5_5
# %bb.4:
	xor	eax, eax
	inc	eax
	jmp	LBB5_8
LBB5_1:
	push	0
	push	dword ptr [esp + 40]
	push	dword ptr [esp + 48]
	push	eax
	push	ecx
	call	_WriteProcessMemoryForce
	add	esp, 24
	jmp	LBB5_9
LBB5_7:
	push	0
	push	dword ptr [esp + 40]
	push	dword ptr [esp + 48]
	push	eax
	push	dword ptr [esp + 60]
	call	_WriteProcessMemoryForce
	add	esp, 20
LBB5_8:
	add	esp, 4
LBB5_9:
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _getProcessByName;
	.scl	2;
	.type	32;
	.endef
	.globl	_getProcessByName       # -- Begin function getProcessByName
_getProcessByName:                      # @getProcessByName
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	sub	esp, 296
	mov	edi, esp
	mov	dword ptr [edi], 296
	push	0
	push	2
	call	_CreateToolhelp32Snapshot@8
	mov	esi, eax
	push	edi
	push	esi
	call	_Process32First@8
	mov	ecx, eax
	xor	eax, eax
	mov	edx, 0
	mov	ebx, 0
	cmp	ecx, 1
	mov	ecx, 0
	jne	LBB6_6
# %bb.1:
	mov	ebx, dword ptr [esp + 316]
	lea	ebp, [esp + 36]
LBB6_2:                                 # =>This Inner Loop Header: Depth=1
	push	edi
	push	esi
	call	_Process32Next@8
	cmp	eax, 1
	jne	LBB6_3
# %bb.4:                                #   in Loop: Header=BB6_2 Depth=1
	push	ebx
	push	ebp
	call	_strcmp
	pop	ecx
	pop	edx
	test	eax, eax
	jne	LBB6_2
# %bb.5:
	push	dword ptr [esp + 8]
	push	0
	push	2097151
	call	dword ptr [__imp__OpenProcess@12]
	mov	ecx, dword ptr [esp + 8]
	xor	edx, edx
	xor	ebx, ebx
	jmp	LBB6_6
LBB6_3:
	xor	eax, eax
	xor	edx, edx
	xor	ebx, ebx
	xor	ecx, ecx
LBB6_6:
	or	edx, ecx
	or	eax, ebx
	add	esp, 296
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _getModuleBaseAddr;
	.scl	2;
	.type	32;
	.endef
	.globl	_getModuleBaseAddr      # -- Begin function getModuleBaseAddr
_getModuleBaseAddr:                     # @getModuleBaseAddr
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	sub	esp, 548
	mov	eax, dword ptr [esp + 572]
	mov	edi, esp
	mov	dword ptr [edi], 548
	push	eax
	push	24
	call	_CreateToolhelp32Snapshot@8
	mov	esi, eax
	push	edi
	push	esi
	call	_Module32First@8
	cmp	eax, 1
	jne	LBB7_6
# %bb.1:
	mov	ebx, dword ptr [esp + 568]
	lea	ebp, [esp + 32]
LBB7_2:                                 # =>This Inner Loop Header: Depth=1
	push	edi
	push	esi
	call	_Module32Next@8
	test	eax, eax
	je	LBB7_5
# %bb.3:                                #   in Loop: Header=BB7_2 Depth=1
	push	ebx
	push	ebp
	call	_strcmp
	pop	ecx
	pop	edx
	test	eax, eax
	je	LBB7_2
# %bb.4:
	push	esi
	call	dword ptr [__imp__CloseHandle@4]
	mov	eax, dword ptr [esp + 20]
	jmp	LBB7_8
LBB7_6:
	call	_printErrCode
	push	esi
	jmp	LBB7_7
LBB7_5:
	push	esi
LBB7_7:
	call	dword ptr [__imp__CloseHandle@4]
	xor	eax, eax
LBB7_8:
	add	esp, 548
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _toHex;
	.scl	2;
	.type	32;
	.endef
	.globl	_toHex                  # -- Begin function toHex
_toHex:                                 # @toHex
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	push	eax
	mov	eax, dword ptr [esp + 28]
	mov	edi, dword ptr [esp + 32]
	xor	esi, esi
	mov	ebx, esp
	lea	ebp, [eax + 2]
	jmp	LBB8_1
LBB8_3:                                 #   in Loop: Header=BB8_1 Depth=1
	mov	eax, dword ptr [esp + 24]
	movzx	eax, byte ptr [eax + esi]
	push	eax
	push	offset "??_C@_05PCOJHGNM@?$CF?42x?5?$AA@"
	push	ebx
	call	_sprintf
	add	esp, 12
	mov	al, byte ptr [esp]
	inc	esi
	mov	byte ptr [ebp - 2], al
	mov	al, byte ptr [esp + 1]
	mov	byte ptr [ebp - 1], al
	mov	al, byte ptr [esp + 2]
	mov	byte ptr [ebp], al
	add	ebp, 3
LBB8_1:                                 # =>This Inner Loop Header: Depth=1
	cmp	esi, edi
	jl	LBB8_3
# %bb.2:
	mov	ecx, dword ptr [esp + 28]
	lea	eax, [edi + 2*edi]
	mov	byte ptr [ecx + eax], 0
	add	esp, 4
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 _readBytes;
	.scl	2;
	.type	32;
	.endef
	.globl	_readBytes              # -- Begin function readBytes
_readBytes:                             # @readBytes
# %bb.0:
	push	ebx
	push	esi
	mov	ecx, dword ptr [esp + 20]
	mov	edx, dword ptr [esp + 16]
	mov	esi, dword ptr [esp + 12]
	xor	eax, eax
	jmp	LBB9_1
LBB9_3:                                 #   in Loop: Header=BB9_1 Depth=1
	mov	bl, byte ptr [eax + esi]
	mov	byte ptr [edx + eax], bl
	inc	eax
LBB9_1:                                 # =>This Inner Loop Header: Depth=1
	cmp	eax, ecx
	jl	LBB9_3
# %bb.2:
	pop	esi
	pop	ebx
	ret
                                        # -- End function
	.def	 _readBytesBetweenTwoFunc;
	.scl	2;
	.type	32;
	.endef
	.globl	_readBytesBetweenTwoFunc # -- Begin function readBytesBetweenTwoFunc
_readBytesBetweenTwoFunc:               # @readBytesBetweenTwoFunc
# %bb.0:
	push	ebx
	push	esi
	mov	edx, dword ptr [esp + 12]
	mov	eax, dword ptr [esp + 16]
	mov	ecx, dword ptr [esp + 20]
	xor	esi, esi
	sub	eax, edx
	jmp	LBB10_1
LBB10_2:                                #   in Loop: Header=BB10_1 Depth=1
	mov	bl, byte ptr [edx + esi]
	mov	byte ptr [ecx + esi], bl
	inc	esi
LBB10_1:                                # =>This Inner Loop Header: Depth=1
	cmp	esi, eax
	jle	LBB10_2
# %bb.3:
	inc	eax
	pop	esi
	pop	ebx
	ret
                                        # -- End function
	.def	 _readBytesBetweenTwoFunc_alloc;
	.scl	2;
	.type	32;
	.endef
	.globl	_readBytesBetweenTwoFunc_alloc # -- Begin function readBytesBetweenTwoFunc_alloc
_readBytesBetweenTwoFunc_alloc:         # @readBytesBetweenTwoFunc_alloc
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	edi, dword ptr [esp + 20]
	mov	ebx, dword ptr [esp + 24]
	xor	esi, esi
	sub	ebx, edi
	lea	ebp, [ebx + 1]
	push	ebp
	call	_malloc
	pop	ecx
	jmp	LBB11_1
LBB11_2:                                #   in Loop: Header=BB11_1 Depth=1
	mov	cl, byte ptr [edi + esi]
	mov	byte ptr [eax + esi], cl
	inc	esi
LBB11_1:                                # =>This Inner Loop Header: Depth=1
	cmp	esi, ebx
	jle	LBB11_2
# %bb.3:
	mov	ecx, dword ptr [esp + 28]
	mov	dword ptr [ecx], ebp
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
	ret
                                        # -- End function
	.def	 __vsprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__vsprintf_l
	.globl	__vsprintf_l            # -- Begin function _vsprintf_l
__vsprintf_l:                           # @_vsprintf_l
# %bb.0:
	push	dword ptr [esp + 16]
	push	dword ptr [esp + 16]
	push	dword ptr [esp + 16]
	push	-1
	push	dword ptr [esp + 20]
	call	__vsnprintf_l
	add	esp, 20
	ret
                                        # -- End function
	.def	 __vsnprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__vsnprintf_l
	.globl	__vsnprintf_l           # -- Begin function _vsnprintf_l
__vsnprintf_l:                          # @_vsnprintf_l
# %bb.0:
	push	ebp
	push	ebx
	push	edi
	push	esi
	mov	edi, dword ptr [esp + 24]
	mov	ebx, dword ptr [esp + 28]
	mov	ebp, dword ptr [esp + 32]
	mov	esi, dword ptr [esp + 36]
	call	___local_stdio_printf_options
	mov	ecx, dword ptr [eax]
	or	ecx, 1
	push	esi
	push	ebp
	push	ebx
	push	edi
	push	dword ptr [esp + 36]
	push	dword ptr [eax + 4]
	push	ecx
	call	___stdio_common_vsprintf
	add	esp, 28
	xor	ecx, ecx
	dec	ecx
	cmp	eax, -2
	cmovle	eax, ecx
	pop	esi
	pop	edi
	pop	ebx
	pop	ebp
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
	.section	.rdata,"dr",discard,"??_C@_0P@MBPEHPOC@ErrorCode?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0P@MBPEHPOC@ErrorCode?3?5?$CFd?6?$AA@" # @"\01??_C@_0P@MBPEHPOC@ErrorCode?3?5?$CFd?6?$AA@"
"??_C@_0P@MBPEHPOC@ErrorCode?3?5?$CFd?6?$AA@":
	.asciz	"ErrorCode: %d\n"

	.section	.rdata,"dr",discard,"??_C@_05PCOJHGNM@?$CF?42x?5?$AA@"
	.globl	"??_C@_05PCOJHGNM@?$CF?42x?5?$AA@" # @"\01??_C@_05PCOJHGNM@?$CF?42x?5?$AA@"
"??_C@_05PCOJHGNM@?$CF?42x?5?$AA@":
	.asciz	"%.2x "

	.lcomm	___local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:uuid.lib"

