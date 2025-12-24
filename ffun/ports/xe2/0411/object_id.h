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
    TRACK = 0x64, // not used
    POS = 0x66,
    JPG = 0x6d,
    CPU_BOUND = 0xba, //following id-s bound to cpu1
};

enum IRQ_HARD {
    uITRON_TICKS = 0x20, //pri 0x0c
    TIMER1 = 0x21, //pri 0x0c
    TIMER2 = 0x22, 
    TIMER3 = 0x23, 
    DEV01a = 0x24,
    DEV01b = 0x25,
    DEV01c = 0x26,
    IRQ_PACK = 0x45,
    IRQ_RECC = 0x49,
    IRQ_SDIO = 0x4F,
    IRQ_DMA0 = 0x5B,
    IRQ_DMA1 = 0x5C,
    IRQ_DMA2 = 0x5D,
    IRQ_DMA3 = 0x5E,
    IRQ_UART = 0x6B,
    DISPATCH = 0x78,
    BOOTROM  = 0x79,
    MAX  = 0x7f,
};
enum IRQID {
    DMA0_PRID  = 0x0,
    DMA1_PRID = 0x1,
    DMA2 = 0x2,
    DMA3 = 0x3,
    TIMER0 = 5,
    TIMER1 = 6,
    TIMER2 = 7,
    TIMER3 = 8,
    UNK09 = 0x09,
    UNK0A = 0x0a,
    UNK0B = 0x0b,
    UNK0C = 0x0c,
    UNK0D = 0x0d,
    UNK0E = 0x0e,
    UNK0F = 0x0f,
    DMA1_PRIA = 0x27,
    DEV01a = 0x28,
    DEV01b = 0x29,
    DEV01c = 0x2A,
    UNK2B = 0x2B,
    UNK2C = 0x2C,
    UNK2F = 0x2F,
    UNK30 = 0x30,
    PFP = 0x35,
    DEV65 = 0x3a,
    GPU = 0x3b,
    DEV42 = 0x3c,
    CMOS = 0x37,
    IFP = 0x3f,
    FACEDT = 0x40,
    USB = 0x47,
    EEP = 0x4b,
    SD0 = 0x4c,
    SATA = 0x4d,
    I2CH0 = 0x4e,
    I2CH1 = 0x4f,
    LENS = 0x51,
    SMP = 0x52,
    HDMI = 0x5b,
    UART = 0x5c,
    RECC = 0x5d,
    PACK = 0x64,
    LENS1 = 0x77
    LENS0 = 0x78
    LENS2 = 0x79
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

enum TM_OP {
    OP0 = 0xc8,
    OP1 = 0xc9,
    OP2 = 0xca,
    OP3 = 0xcb,
};

enum BLINK_KIND {
    NONE  = 0x00,
    LED   = 0x01,
    AFLED = 0x02,
};

enum LCDEVF_CMD {
    TURN_OFF = 0x00,
    TURN_ON  = 0x02,
};