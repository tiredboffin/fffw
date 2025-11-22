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
    JIG = 0x5e,
    IFP = 0x61,
    JPG = 0x6d,
    CPU_BOUND = 0xba, //following id-s bound to cpu1
};

enum IRQ_HARD {
    DISPATCH = 0x78,
    MAX  = 0x7f,
};
enum IRQID {
    TIMER0 = 5,
    TIMER1 = 6,
    TIMER2 = 7,
    TIMER3 = 8,
    CLOCK = 0x20,
    DEV42 = 0x3c,
    IFP = 0x3f,
    RECC = 0x5d,
    PACK = 0x64,
    MAX  = 0x81,
};

enum BIT63_OP {
    TEST_ONE = 0x2c, //TEST one bit
    ANY = 0x2e, //OR of all 64-bit entries
    SET_BIT = 0x81,
    CLEAR_BIT = 0x82,
    CLEAR_ALL = 0x40,
};