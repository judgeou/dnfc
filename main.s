	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 1
	.intel_syntax noprefix
	.def	 _main;
	.scl	2;
	.type	32;
	.endef
	.globl	_main                   # -- Begin function main
_main:                                  # @main
# %bb.0:
	call	_featureInit
	push	0
	push	offset _killAll
	push	123
	call	_bindKey
	add	esp, 12
	call	_startSyncListenKey
	xor	eax, eax
	ret
                                        # -- End function
	.section	.drectve,"yn"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:uuid.lib"
	.ascii	" /DEFAULTLIB:user32.lib"

