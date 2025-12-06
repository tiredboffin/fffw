enum SEMID {
    RECC1 = 1,
    RECC2 = 2,
    SEM09 = 9,
    RTC = 0x26,
    PACK_MUX = 0x2c,
    DCN = 0x2d,
    GPS = 0x3c,
    BATT = 0x3d,
    FILE_OP = 0x3e,
    HEAP = 0x43,
    PACK = 0x4c,
    D88 = 0x5f,
    JIG = 0x5e,
    IFP = 0x61,
    JPG = 0x6d,
    CPU_BOUND = 0xba, //following id-s bound to cpu1
};

enum IRQ_HARD {
    uITRON_TICKS = 0x20, //pri 0x0c
    IRQ21 = 0x21,
    IRQ22 = 0x22,
    DEV01a = 0x24,
    DEV01b = 0x25,
    DEV01c = 0x26,
    IRQ_PACK = 0x45,
    IRQ_RECC = 0x49,
    IRQ_DMA0 = 0x5B,
    IRQ_DMA1 = 0x5C,
    IRQ_DMA2 = 0x5D,
    IRQ_DMA3 = 0x5E,
    IRQ_UART = 0x6B,
    DISPATCH = 0x78,
    MAX  = 0x7f,
};
enum IRQID {
    DMA0 = 0x0,
    DMA1 = 0x1,
    DMA2 = 0x2,
    DMA3 = 0x3,
    TIMER0 = 5,
    TIMER1 = 6,
    TIMER2 = 7,
    TIMER3 = 8,
    DEV01a = 0x28,
    DEV01b = 0x29,
    DEV01c = 0x2A,
    UNK2F = 0x2F,
    UNK30 = 0x30,
    DEV42 = 0x3c,
    IFP = 0x3f,
    LENS = 0x52,
    UART = 0x5c,
    RECC = 0x5d,
    PACK = 0x64,
    MAX   = 0x81,
    SOFT82 = 0x82,
};

enum BIT63_OP {
    TEST_ONE = 0x2c, //TEST one bit
    ANY = 0x2e, //OR of all 64-bit entries
    SET_BIT = 0x81,
    CLEAR_BIT = 0x82,
    CLEAR_ALL = 0x40,
};

enum KBDH_TYPE {
    RANGE     = 0x0,  // e.g. focus mode switch AF,CAF,MF
    CFGRANGE  = 0x1,  // e.g. shutter dial, iso dial
    DIGITAL   = 0x2,  // e.g. lens detect, SD card detect, some buttonds, etc
    IRQA      = 0x3,  // 
    IRQB      = 0x4,  // e.g. S1, S2
    FUNC      = 0x5,  // e.g. AE lock, Play  
};
