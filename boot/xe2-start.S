_start:
	b           _boot
	nop
	nop
	nop
	nop
	nop
	nop
	nop
stack_ptr:	.word	0xfff00f00
d88_ofs84:	.word	0xfff88084

_boot:
	msr         CPSR_c,#0xd3 /* Supervisory mode, interrupts disabled.  */
	ldr         sp,stack_ptr
	ldr         r0,d88_ofs84 /* see bootrom */
	mov         r1,#0x1                                 
	str         r1,[r0]     
	mov         r1, pc
	mov         r0, r2
	bl          boot_main
_halt:
	b           _halt
.global nop
nop:
	bx          lr
.global wfi_halt
wfi_halt:
	ldr         r0,d88_ofs84 /* see bootrom */
	mov         r1,#0x0
	str         r1,[r0]
	nop
	nop
	wfi
	b          _halt