.title "EE308 PIC24F Board"
.sbttl "Initialization Code"
.equ __24FJ256GB110, 1
.include "p24FJ256GB110.inc"

config __CONFIG1, JTAGEN_OFF    
    
.global __reset          ;The label for the first line of code. 
.global __T1Interrupt    ;Declare Timer 1 ISR name global

.bss

.section .const,psv

 .text		  ;Start of Code section
__reset:
    mov	    #__SP_init, W15	; Initalize the Stack Pointer
    mov	    #__SPLIM_init, W0	; Initialize the Stack Pointer Limit Register
    mov	    W0, SPLIM
    nop				; Add NOP to follow SPLIM initialization
    
    mov	    #0x0000, W0
    mov	    W0, TRISB		; all port-B pins output
    mov	    #0xFFFF, W0
    mov	    W0, AD1PCFGL
    
    mov	    #0x0100, W0		; counter start value
    mov	    #0x0060, W1 
    mov	    #0x0000, W2
    mov	    #0x0059, W3
    mov	    #0x0099, W4
    
main_loop:
    
    mov	    W0, LATB
    
    cp	    W0,W2		;if the timer shows 00:00
    bra	    NZ, mm_check	;else check if hh:00
    mov	    #0x2359, W0 
    bra	    main_loop
    
mm_check:
    
    cp.B    W0, W2
    bra	    NZ, dec_mm
    
    add	    W0, W3, W0
    daw.B   W0
    SWAP    W0
    add	    W0, W4, W0
    daw.B   W0
    SWAP    W0
    
    bra	    main_loop
    
dec_mm:
    add	    W0, W4, W0
    daw.B   W0
    bra	    main_loop
    
    
    .end
    