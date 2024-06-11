extern void nop(void);
#define DELAY 1000000



void p(void) {  
  for (int i = DELAY; i > 0; i--) nop();
}

int boot_main(void) {
    volatile unsigned *ptr = (unsigned *)0xfff893c0; // = FFF89000 + 0x40*0x0F + 0x00

#if 0
    /* This is equivalent to what the fw does to blink red */
    
    *(ptr+1) = 0x00050001; 


    while(1) {
        *ptr = 0x00010001; 
        p();
        *ptr = 0x00010000;   
        p();
    }
#else
    /* Experiments with colors  */
    while(1) {
        *ptr = 0x00050004;         //GREEN OFF, RED ON
        *(ptr + 1) = 0x00050005;
        p();

        *(ptr + 1) = 0x00050000;   //ALL OFF
        p();

        *ptr = 0x50001;         //GREEN ON, RED OFF
        *(ptr + 1) = 0x00050005;   
        p();

        *(ptr + 1) = 0x00050000;   //ALL OFF
        p();

        *ptr = 0x00050000;         //GREEN ON, RED ON  = ORANGE
        *(ptr + 1) = 0x00050005;   
        p();

        *(ptr + 1) = 0x00050000;   //ALL OFF
        p();
    }
#endif
  return 0;
}
