enum PSOS_ERR {
    ERR_OBJTFULL=0x08, //Node’s object table full
    ERR_NOTCB=0x0E, //Exceeds node's maximum number of tasks
    ERR_NOSTK=0x0F, //Insufficient space in Region 0 to create stack
    ERR_TINYSTK=0x10, //Stack size too small
    ERR_PRIOR=0x11, //Priority out of range
    ERR_OBJDEL=0x05,
    ERR_OBJID=0x06,
    ERR_OBJTYPE=0x07,
    ERR_SUSP=0x14, // Task was already suspended.
};


enum SYSCALL {
    T_CREATE = 0x01,
    T_START  = 0x03,
};

unsigned long t_create( char name[4], unsigned long prio, unsigned long sstack, unsigned long ustack, unsigned long flags, unsigned long *tid);
