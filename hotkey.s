	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 1
	.intel_syntax noprefix
	.def	 _bindKey;
	.scl	2;
	.type	32;
	.endef
	.globl	_bindKey                # -- Begin function bindKey
_bindKey:                               # @bindKey
# %bb.0:
	push	ebx
	push	edi
	push	esi
	mov	esi, dword ptr [esp + 24]
	mov	edi, dword ptr [esp + 20]
	mov	ebx, dword ptr [esp + 16]
	push	20
	call	_malloc
	pop	ecx
	mov	ecx, dword ptr [_lastKeyNode]
	mov	dword ptr [eax], ebx
	mov	dword ptr [eax + 4], edi
	mov	dword ptr [eax + 8], esi
	and	dword ptr [eax + 12], 0
	and	dword ptr [eax + 16], 0
	mov	edx, offset _beginKeyNode
	test	ecx, ecx
	lea	ecx, [ecx + 16]
	cmove	ecx, edx
	mov	dword ptr [ecx], eax
	mov	dword ptr [_lastKeyNode], eax
	pop	esi
	pop	edi
	pop	ebx
	ret
                                        # -- End function
	.def	 _startSyncListenKey;
	.scl	2;
	.type	32;
	.endef
	.globl	_startSyncListenKey     # -- Begin function startSyncListenKey
_startSyncListenKey:                    # @startSyncListenKey
# %bb.0:
	push	ebx
	push	edi
	push	esi
	mov	esi, dword ptr [__imp__Sleep@4]
	mov	edi, dword ptr [__imp__GetAsyncKeyState@4]
	mov	ebx, offset _beginKeyNode
LBB1_1:                                 # =>This Inner Loop Header: Depth=1
	mov	ebx, dword ptr [ebx]
	test	ebx, ebx
	je	LBB1_9
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	push	dword ptr [ebx]
	call	edi
                                        # kill: def %ax killed %ax def %eax
	test	al, 1
	je	LBB1_8
# %bb.3:                                #   in Loop: Header=BB1_1 Depth=1
	test	byte ptr [ebx + 12], 1
	je	LBB1_6
# %bb.4:                                #   in Loop: Header=BB1_1 Depth=1
	mov	eax, dword ptr [ebx + 8]
	test	eax, eax
	je	LBB1_6
# %bb.5:                                #   in Loop: Header=BB1_1 Depth=1
	call	eax
	jmp	LBB1_7
LBB1_9:                                 #   in Loop: Header=BB1_1 Depth=1
	push	100
	call	esi
	mov	ebx, offset _beginKeyNode
	jmp	LBB1_1
LBB1_6:                                 #   in Loop: Header=BB1_1 Depth=1
	call	dword ptr [ebx + 4]
LBB1_7:                                 #   in Loop: Header=BB1_1 Depth=1
	inc	dword ptr [ebx + 12]
LBB1_8:                                 #   in Loop: Header=BB1_1 Depth=1
	add	ebx, 16
	jmp	LBB1_1
                                        # -- End function
	.lcomm	_lastKeyNode,4,4        # @lastKeyNode
	.lcomm	_beginKeyNode,4,4       # @beginKeyNode
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:user32.lib"

