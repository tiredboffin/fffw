enum PSOS_ERR
{
    ERR_TIMEOUT = 0x01,
    ERR_SSFN = 0x03,
    ERR_NODENO = 0x04,
    ERR_OBJDEL = 0x05,
    ERR_OBJID = 0x06,
    ERR_OBJTYPE = 0x07,
    ERR_OBJTFULL = 0x08, // Node’s object table full
    ERR_OBJNF = 0x09,
    ERR_NOTCB = 0x0E,   // Exceeds node's maximum number of tasks
    ERR_NOSTK = 0x0F,   // Insufficient space in Region 0 to create stack
    ERR_TINYSTK = 0x10, // Stack size too small
    ERR_PRIOR = 0x11,   // Priority out of range
    ERR_ACTIVE = 0x12,
    ERR_NACTIVE = 0x13,
    ERR_SUSP = 0x14, // Task was already suspended
    ERR_NOTSUSP = 0x15,
    ERR_SETPRI = 0x16,
    ERR_REGNUM = 0x17,
    ERR_RNADDR = 0x1B,
    ERR_UNITSIZE = 0x1C,
    ERR_TINYUNIT = 0x1D, // Length  too large (for given unit_size)
    ERR_TINYRN = 0x1E,   // Cannot create; region length too small to hold RNCB
    ERR_SEGINUSE = 0x1f, // Cannot delete; one or more seg-ments still in use
    ERR_ZERO = 0x20,
    ERR_TOOBIG = 0x21,
    ERR_NOSEG = 0x22,
    ERR_NOTINRN = 0x23,
    ERR_SEGADDR = 0x24,
    ERR_SEGFREE = 0x25,
    ERR_RNKILLD = 0x26,
    ERR_TATRNDEL = 0x27,
    ERR_PTADDR = 0x28,
    ERR_BUFSIZE = 0x29,
    ERR_TINYPT = 0x2a,
    ERR_BUFINUSE = 0x2B,
    ERR_NOBUF = 0x2C,
    ERR_BUFADDR = 0x2D,
    ERR_BUFFREE = 0x2F,
    ERR_MSGSIZ = 0x31,
    ERR_BUFSIZ = 0x32,
    ERR_NOQCB = 0x33, // Cannot allocate QCB; exceeds node's maximum number of active queues.
    ERR_NOMGB = 0x34, // Cannot allocate private buffers
    ERR_QFULL = 0x35,
    ERR_QKILLD = 0x36,
    ERR_NOMSG = 0x37,
    ERR_TATQDEL = 0x38,
    ERR_MATQDEL = 0x39,
    ERR_VARQ = 0x3A,
    ERR_NOTVARQ = 0x3B,
    ERR_NOEVS = 0x3C,
    ERR_NOTINASR = 0x3E,
    ERR_NOASR = 0x3F,
    ERR_NOSCB = 0x41,
    ERR_NOSEM = 0x42,
    ERR_SKILLD = 0x43,
    ERR_TATSDEL = 0x44,
    ERR_NOTIME = 0x47,
    ERR_ILLDATE = 0x48,
    ERR_ILLTIME = 0x49,
    ERR_ILLTICKS = 0x4A,
    ERR_NOTIMERS = 0x4B,
    ERR_BADTMID = 0x4C,
    ERR_TMNOTSET = 0x4D,
    ERR_TOOLATE = 0x4E,
    ERR_ILLRSC = 0x53,
    ERR_NOAGNT=0x54,
    ERR_STALEID=0x65,
    ERR_NDKLD=0x66,
    ERR_NODR=0x102,
    FAT_ALIGN=0xf00,
    FAT_OVSDA=0xf01, //Region 0 overflow while making system data area
    FAT_OVOBJT=0xf02, //Region 0 overflow while making object table
    FAT_OVDDAT=0xf03, //Region 0 overflow while making device area table
    FAT_OVTCB=0xf04, //Region 0 overflow while making task structures
    FAT_OVQCB=0xf05,
    FAT_OVSMCB=0xf06,
    FAT_OVTM=0xf07,
    FAT_OVPT=0xf08,
    FAT_OVRSC=0xf09,
    FAT_OVRN=0xf0a,
    FAT_ROOT=0xf0c,
    FAT_IDLE=0xf0d,
    FAT_CHKSUM=0xf0e,
    FAT_DEVINIT=0xf1b,
};
    
enum OBJ_TYPE
{
    TASK = 0x01,
    QUEUE = 0x02,
    SEMAPHORE = 0x03,
    REGION = 0x04,
    PART = 0x05,
};
enum SYSCALL
{
    T_CREATE = 0x01,
    T_IDENT = 0x02,
    T_START = 0x03,
    T_RESTART = 0x04,
    T_DELETE = 0x05,
    T_SUSPEND = 0x06,
    T_RESUME = 0x07,
    T_SETPRI = 0x08,
    T_GETREG = 0x0a,
    T_SETREG = 0x0b,
    RN_CREATE = 0x0e,
    RN_RETSEG = 0x12,
    Q_CREATE=0x24,
    Q_IDENT=0x25,
    Q_DELETE=0x26,
    Q_SEND=0x27,
    Q_VSEND=0x28,
    Q_RECEIVE=0x2a,
    SYSC_2C=0x2c,
    EV_RECEIVE=0x2d,
    SM_CREATE=0x33,
    SM_DELETE=0x35,
};

unsigned long t_create(char name[4], unsigned long prio, unsigned long sstack, unsigned long ustack, unsigned long flags, unsigned long *tid);
