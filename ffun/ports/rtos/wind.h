typedef unsigned char uchar_t;
typedef unsigned long INSTR;
typedef void (*VOIDFUNCPTR) ();
typedef int (*FUNCPTR) ();
typedef struct obj_class *CLASS_ID;
typedef struct obj_core
    {
    struct obj_class *pObjClass;
    } OBJ_CORE;
typedef struct regindex
    {
    char *regName;
    int regOff;
    int regWidth;
    } REG_INDEX;
typedef struct
    {
    unsigned long sr;
    INSTR *pc;
    unsigned long long lo;
    unsigned long long hi;
    unsigned long long gpreg[32];
    unsigned long cause;
    unsigned long fpcsr;
    } REG_SET;
typedef struct wdb_info
    {
    int wdbState;
    REG_SET * wdbRegisters;
    struct
        {
 void * wdb1;
 void * wdb2;
 } wdbEvtList;
    int bpAddr;
    int taskBpAddr;
    int taskPc;
    int taskFp;
    int taskSp;
    VOIDFUNCPTR wdbExitHook;
  } WDB_INFO;
typedef struct node
    {
    struct node *next;
    struct node *previous;
    } NODE;
typedef struct
    {
    NODE node;
    int count;
    } LIST;
typedef struct
    {
    unsigned int qPriv1;
    unsigned int qPriv2;
    unsigned int qPriv3;
    unsigned int qPriv4;
    } Q_NODE;
typedef struct q_class
    {
    FUNCPTR createRtn;
    FUNCPTR initRtn;
    FUNCPTR deleteRtn;
    FUNCPTR terminateRtn;
    FUNCPTR putRtn;
    FUNCPTR getRtn;
    FUNCPTR removeRtn;
    FUNCPTR resortRtn;
    FUNCPTR advanceRtn;
    FUNCPTR getExpiredRtn;
    FUNCPTR keyRtn;
    FUNCPTR calibrateRtn;
    FUNCPTR infoRtn;
    FUNCPTR eachRtn;
    struct q_class *valid;
    } Q_CLASS;
typedef struct
    {
    Q_NODE *pFirstNode;
    unsigned int qPriv1;
    unsigned int qPriv2;
    Q_CLASS *pQClass;
    } Q_HEAD;
typedef struct dlnode
    {
    void *next;
    void *previous;
    } DL_NODE;
typedef struct
    {
    DL_NODE *head;
    DL_NODE *tail;
    } DL_LIST;
typedef struct obj_core
    {
    struct obj_class *pObjClass;
    } OBJ_CORE;
typedef struct eventsResourceCb
    {
    unsigned registered;
    int taskId;
    unsigned char options;
    unsigned char pad[3];
    } EVENTS_RSRC;
typedef struct semaphore
    {
    OBJ_CORE objCore;
    unsigned char semType;
    unsigned char options;
    unsigned short recurse;
    Q_HEAD qHead;
    union
 {
 unsigned int count;
 struct windTcb *owner;
 } state;
    EVENTS_RSRC events;
    } SEMAPHORE;
typedef enum
    {
    SEM_EMPTY,
    SEM_FULL
    } SEM_B_STATE;
typedef enum {
    BINARY= 0x0,
    MUTEX= 0x1,
    COUNTING= 0x2,
    OLD= 0x3,
} SEM_TYPE;
typedef enum {
    Q_FIFO= 0x00,
    Q_PRIORITY= 0x01,
    DELETE_SAFE= 0x04,
    INVERSION_SAFE= 0x08,
    EVENTSEND_ERR_NOTIFY= 0x10,
} SEM_OPT;
typedef struct semaphore *SEM_ID;
typedef struct mem_part
    {
    OBJ_CORE objCore;
    DL_LIST freeList;
    SEMAPHORE sem;
    unsigned totalWords;
    unsigned minBlockWords;
    unsigned options;
    unsigned curBlocksAllocated;
    unsigned curWordsAllocated;
    unsigned cumBlocksAllocated;
    unsigned cumWordsAllocated;
    } PARTITION;
typedef struct obj_class
    {
    OBJ_CORE objCore;
    struct mem_part *objPartId;
    unsigned objSize;
    unsigned objAllocCnt;
    unsigned objFreeCnt;
    unsigned objInitCnt;
    unsigned objTerminateCnt;
    int coreOffset;
    FUNCPTR createRtn;
    FUNCPTR initRtn;
    FUNCPTR destroyRtn;
    FUNCPTR showRtn;
    FUNCPTR instRtn;
    } OBJ_CLASS;
typedef struct
    {
    unsigned short valid;
    unsigned short vecNum;
    unsigned short eid;
    unsigned short pad;
    INSTR *epc;
    unsigned long badVa;
    unsigned long statusReg;
    unsigned long causeReg;
    unsigned long fpcsr;
    unsigned long ear;
    } EXC_INFO;
typedef struct eventsCb
    {
    unsigned wanted;
    volatile unsigned received;
    unsigned char options;
    unsigned char sysflags;
    unsigned char pad[2];
    } EVENTS;
typedef struct taskVar
    {
    struct taskVar * next;
    int * address;
    int value;
    } TASK_VAR;
typedef enum
    {
    SELREAD,
    SELWRITE
    } SELECT_TYPE;
typedef struct selWkNode
    {
    NODE linkedListHooks;
    int dontFree;
    int taskId;
    int fd;
    SELECT_TYPE type;
    } SEL_WAKEUP_NODE;
typedef struct
    {
    SEMAPHORE listMutex;
    SEL_WAKEUP_NODE firstNode;
    LIST wakeupList;
    } SEL_WAKEUP_LIST;
typedef long fd_mask;
typedef struct fd_set
{
    fd_mask fd_bits[32];
};
typedef struct selContext
    {
    SEMAPHORE wakeupSem;
    int pendedOnSelect;
    fd_set *pReadFds;
    fd_set *pWriteFds;
    fd_set *pOrigReadFds;
    fd_set *pOrigWriteFds;
    int width;
    } SEL_CONTEXT;
typedef struct windTcb
    {
    Q_NODE qNode;
    Q_NODE tickNode;
    Q_NODE activeNode;
    OBJ_CORE objCore;
    char * name;
    int options;
    unsigned int status;
    unsigned int priority;
    unsigned int priNormal;
    unsigned int priMutexCnt;
    struct semaphore * pPriMutex;
    unsigned int lockCnt;
    unsigned int tslice;
    unsigned short swapInMask;
    unsigned short swapOutMask;
    Q_HEAD * pPendQ;
    unsigned int safeCnt;
    Q_HEAD safetyQHead;
    FUNCPTR entry;
    char * pStackBase;
    char * pStackLimit;
    char * pStackEnd;
    VX_ERR errorStatus;
    int exitCode;
    struct sigtcb * pSignalInfo;
    struct selContext * pSelectContext;
    unsigned int taskTicks;
    unsigned int taskIncTicks;
    struct taskVar * pTaskVar;
    struct rpcModList * pRPCModList;
    struct fpContext * pFpContext;
    struct __sFILE * taskStdFp[3];
    int taskStd[3];
    char ** ppEnviron;
    int envTblSize;
    int nEnvVarEntries;
    struct sm_obj_tcb * pSmObjTcb;
    int windxLock;
    void * pComLocal;
    REG_SET * pExcRegSet;
    EVENTS events;
    WDB_INFO * pWdbInfo;
    void * pPthread;
    int reserved1;
    int reserved2;
    int spare1;
    int spare2;
    int spare3;
    int spare4;
    EXC_INFO excInfo;
    REG_SET regs;
    struct dspContext * pDspContext;
    WDB_INFO wdbInfo;
    } WIND_TCB;
struct __sbuf
    {
    uchar_t * _base;
    int _size;
    };
typedef struct __sFILE
    {
    OBJ_CORE objCore;
    uchar_t * _p;
    int _r;
    int _w;
    short _flags;
    short _file;
    struct __sbuf _bf;
    int _lbfsize;
    struct __sbuf _ub;
    uchar_t * _up;
    int _ur;
    uchar_t _ubuf[3];
    uchar_t _nbuf[1];
    struct __sbuf _lb;
    int _blksize;
    int _offset;
    int taskId;
    } FILE;
typedef struct
    {
    FUNCPTR de_create;
    FUNCPTR de_delete;
    FUNCPTR de_open;
    FUNCPTR de_close;
    FUNCPTR de_read;
    FUNCPTR de_write;
    FUNCPTR de_ioctl;
    int de_inuse;
    } DRV_ENTRY;
typedef struct dlnode
    {
    struct dlnode *next;
    struct dlnode *previous;
    } DL_NODE;
typedef struct
    {
    DL_NODE node;
    short drvNum;
    char * name;
    } DEV_HDR;
typedef struct
    {
    DEV_HDR * pDevHdr;
    int value;
    char * name;
    int taskId;
    int inuse;
    int obsolete;
    void * auxValue;
    void * reserved;
    } FD_ENTRY;
typedef struct q_class
    {
    FUNCPTR createRtn;
    FUNCPTR initRtn;
    FUNCPTR deleteRtn;
    FUNCPTR terminateRtn;
    FUNCPTR putRtn;
    FUNCPTR getRtn;
    FUNCPTR removeRtn;
    FUNCPTR resortRtn;
    FUNCPTR advanceRtn;
    FUNCPTR getExpiredRtn;
    FUNCPTR keyRtn;
    FUNCPTR calibrateRtn;
    FUNCPTR infoRtn;
    FUNCPTR eachRtn;
    struct q_class *valid;
    } Q_CLASS;
typedef Q_CLASS *Q_CLASS_ID;
typedef struct qJobNode
    {
    struct qJobNode *next;
    } Q_JOB_NODE;
typedef struct
    {
    Q_JOB_NODE *first;
    Q_JOB_NODE *last;
    int count;
    Q_CLASS *pQClass;
    Q_HEAD pendQ;
    } Q_JOB_HEAD;
typedef struct
    {
    Q_JOB_NODE *first;
    Q_JOB_NODE *last;
    int count;
    Q_CLASS *pQClass;
    Q_HEAD pendQ;
    } Q_JOB_HEAD;
typedef struct msg_q
    {
    OBJ_CORE objCore;
    Q_JOB_HEAD msgQ;
    Q_JOB_HEAD freeQ;
    int options;
    int maxMsgs;
    int maxMsgLength;
    int sendTimeouts;
    int recvTimeouts;
    EVENTS_RSRC events;
    } MSG_Q;
typedef struct msg_q *MSG_Q_ID;
typedef struct
    {
    FUNCPTR function;
    int arg1;
    int arg2;
    int arg3;
    } JOB;
typedef struct
    {
    void * pClass;
    char * pBufs;
    int numBufs;
    int bufSize;
    char * pFreeBufs;
    } BUF_POOL;
typedef struct
    {
    char * next;
    int type;
    } BUFFER;
enum FF_ERR {
    TIMEOUT=0x1,
    INVALID_ID=0x2,
    OBJ_DELETED=0x3,
    ISR_IVALID_CALL=0x5,
    NOT_ENOUGH_MEMORY=0x6,
    INVALID_TSKID=0x7,
    ARRAY_OVR=0x8,
    ILLEGAL_PRIORITY=0x9,
    ZERO_EVENTS=0xa,
    NOT_ALL_EVENTS=0xb,
    INVALID_OBJ_ID=0xc,
    INVALID_PRM=0xd,
    ERR_0E=0xe,
    INVALID_QID=0xf,
    INVALID_MSG_LENGTH=0x11,
    ERR_12=0x12,
    NOT_INITIALIZED=0x13,
    NO_SLOTS=0x14,
    EER_15=0x15,
    EER_17=0x17,
    TOO_MANY_TASK_ARGS=0x24,
};
enum VX_ERR {
    NAME_NOT_FOUND = ((3 << 16) | 101),
    HOOK_TABLE_FULL = ((3 << 16) | 102),
    TASK_HOOK_NOT_FOUND = ((3 << 16) | 103),
    TASK_SWAP_HOOK_REFERENCED = ((3 << 16) | 104),
    TASK_SWAP_HOOK_SET = ((3 << 16) | 105),
    TASK_SWAP_HOOK_CLEAR= ((3 << 16) | 106),
    TASK_VAR_NOT_FOUND= ((3 << 16) | 107),
    TASK_UNDELAYED= ((3 << 16) | 108),
    ILLEGAL_PRIORITY= ((3 << 16) | 109),
    NOT_ENOUGH_MEMORY= ((17 << 16) | 1),
    INVALID_NBYTES= ((17 << 16) | 2),
    BLOCK_ERROR= ((17 << 16) | 3),
    NO_PARTITION_DESTROY= ((17 << 16) | 4),
    PAGE_SIZE_UNAVAILABLE= ((17 << 16) | 5),
    TIMEOUT= ((134 << 16) | 0x0001),
    NOT_ALL_EVENTS= ((134 << 16) | 0x0002),
    ALREADY_REGISTERED= ((134 << 16) | 0x0003),
    EVENTSEND_FAILED= ((134 << 16) | 0x0004),
    ZERO_EVENTS= ((134 << 16) | 0x0005),
    TASK_NOT_REGISTERED= ((134 << 16) | 0x0006),
    NULL_TASKID_AT_INT_LEVEL= ((134 << 16) | 0x0007),
    NOT_INITIALIZED= ((88 << 16) | 1),
    NOT_A_GLOBAL_ADRS= ((88 << 16) | 2),
    NOT_A_LOCAL_ADRS= ((88 << 16) | 3),
    SHARED_MEM_TOO_SMALL= ((88 << 16) | 4),
    TOO_MANY_CPU= ((88 << 16) | 5),
    LOCK_TIMEOUT= ((88 << 16) | 6),
    NO_OBJECT_DESTROY= ((88 << 16) | 7),
    INVALID_MSG_LENGTH= ((65 << 16) | 1),
    NON_ZERO_TIMEOUT_AT_INT_LEVEL= ((65 << 16) | 2),
    INVALID_QUEUE_TYPE= ((65 << 16) | 3),
    OBJ_ID_ERROR= ((61 << 16) | 1),
    OBJ_UNAVAILABLE= ((61 << 16) | 2),
    OBJ_DELETED= ((61 << 16) | 3),
    OBJ_TIMEOUT= ((61 << 16) | 4),
    OBJ_NO_METHOD= ((61 << 16) | 5),
    NOT_ISR_CALLABLE= ((67 << 16) | 1),
    VEC_TABLE_WP_UNAVAILABLE= ((67 << 16) | 2),
    SEM_INVALID_STATE= ((22 << 16) | 101),
    SEM_INVALID_OPTION= ((22 << 16) | 102),
    SEM_INVALID_QUEUE_TYPE= ((22 << 16) | 103),
    SEM_INVALID_OPERATION= ((22 << 16) | 104),
};
enum MIPS_MEM_HELPERS {
    DCACHE_INV_RANGE = 0,
    CACHE_INV = 1,
    DCACHE_INV_SYNC = 2,
    CODE_CACHE_INV = 3,
    SYNC = 4,
    ALLOC_NCACHED = 5,
    FREE_NCACHED = 6,
    KSEG1_TO_PHYS = 7,
    PHYS_TO_KSEG1 = 8,
};
enum WV_CLASS {
    WV_CLASS_1= 0x00000001,
    WV_CLASS_2= 0x00000003,
    WV_CLASS_3= 0x00000007,
    WV_CLASS_TASKNAMES_PRESERVE= 0x00001000,
    WV_ON= 0x10000000,
    WV_CLASS_1_ON= 0x10000001,
    WV_CLASS_2_ON= 0x10000003,
    WV_CLASS_3_ON= 0x10000007,
    WV_CLASS_TASKNAMES_PRESERVE_ON= 0x10001000,
};
enum TRG_CLASS {
    TRG_CLASS_1= 0x00000001,
    TRG_CLASS_2= 0x00000010,
    TRG_CLASS_3= 0x00000100,
    TRG_CLASS_4= 0x00001000,
    TRG_CLASS_5= 0x00010000,
    TRG_CLASS_6= 0x01111111,
    TRG_ON= 0x10000000,
    TRG_CLASS_1_ON= 0x10000001,
    TRG_CLASS_2_ON= 0x10000010,
    TRG_CLASS_3_ON= 0x10000100,
    TRG_CLASS_4_ON= 0x10001000,
    TRG_CLASS_5_ON= 0x10010000,
    TRG_CLASS_6_ON= 0x11111111,
};
enum WV_EVENT {
    EVENT_TASKSPAWN= (10000 + 0),
    EVENT_TASKDESTROY= (10000 + 1),
    EVENT_TASKDELAY= (10000 + 2),
    EVENT_TASKPRIORITYSET= (10000 + 3),
    EVENT_TASKSUSPEND= (10000 + 4),
 EVENT_TASKRESUME= (10000 + 5),
 EVENT_TASKSAFE= (10000 + 6),
 EVENT_TASKUNSAFE= (10000 + 7),
 EVENT_SEMBCREATE= (10000 + 8),
 EVENT_SEMCCREATE= (10000 + 9),
 EVENT_SEMDELETE= (10000 + 10),
 EVENT_SEMFLUSH= (10000 + 11),
 EVENT_SEMGIVE= (10000 + 12),
 EVENT_SEMMCREATE= (10000 + 13),
 EVENT_SEMMGIVEFORCE= (10000 + 14),
 EVENT_SEMTAKE= (10000 + 15),
 EVENT_WDCREATE= (10000 + 16),
 EVENT_WDDELETE= (10000 + 17),
 EVENT_WDSTART= (10000 + 18),
 EVENT_WDCANCEL= (10000 + 19),
 EVENT_MSGQCREATE= (10000 + 20),
 EVENT_MSGQDELETE= (10000 + 21),
 EVENT_MSGQRECEIVE= (10000 + 22),
 EVENT_MSGQSEND= (10000 + 23),
 EVENT_SIGNAL= (10000 + 24),
 EVENT_SIGSUSPEND= (10000 + 25),
 EVENT_PAUSE= (10000 + 26),
 EVENT_KILL= (10000 + 27),
 EVENT_SAFE_PEND= (10000 + 28),
 EVENT_SIGWRAPPER= (10000 + 29),
 EVENT_MEMALLOC= (10000 + 30),
 EVENT_MEMFREE= (10000 + 31),
 EVENT_MEMPARTCREATE= (10000 + 32),
 EVENT_MEMREALLOC= (10000 + 33),
 EVENT_MEMADDTOPOOL= (10000 + 34),
 EVENT_EVENTSEND= (10000 + 57),
 EVENT_EVENTRECEIVE= (10000 + 58),
 EVENT_WINDSPAWN= (600 + 0),
 EVENT_WINDDELETE= (600 + 1),
 EVENT_WINDSUSPEND= (600 + 2),
 EVENT_WINDRESUME= (600 + 3),
 EVENT_WINDPRIORITYSETRAISE= (600 + 4),
 EVENT_WINDPRIORITYSETLOWER= (600 + 5),
 EVENT_WINDSEMDELETE= (600 + 6),
 EVENT_WINDTICKANNOUNCETMRSLC= (600 + 7),
 EVENT_WINDTICKANNOUNCETMRWD= (600 + 8),
 EVENT_WINDDELAY= (600 + 9),
 EVENT_WINDUNDELAY= (600 + 10),
 EVENT_WINDWDSTART= (600 + 11),
 EVENT_WINDWDCANCEL= (600 + 12),
 EVENT_WINDPENDQGET= (600 + 13),
 EVENT_WINDPENDQFLUSH= (600 + 14),
 EVENT_WINDPENDQPUT= (600 + 15),
 EVENT_WINDPENDQTERMINATE= (600 + 17),
 EVENT_WINDTICKUNDELAY= (600 + 18),
 EVENT_OBJ_TASK= (600 + 19),
 EVENT_OBJ_SEMGIVE= (600 + 20),
 EVENT_OBJ_SEMTAKE= (600 + 21),
 EVENT_OBJ_SEMFLUSH= (600 + 22),
 EVENT_OBJ_MSGSEND= (600 + 23),
 EVENT_OBJ_MSGRECEIVE= (600 + 24),
 EVENT_OBJ_MSGDELETE= (600 + 25),
 EVENT_OBJ_SIGPAUSE= (600 + 26),
 EVENT_OBJ_SIGSUSPEND= (600 + 27),
 EVENT_OBJ_SIGKILL= (600 + 28),
 EVENT_WINDTICKTIMEOUT= (600 + 31),
 EVENT_OBJ_SIGWAIT= (600 + 32),
 EVENT_OBJ_EVENTSEND= (600 + 35),
 EVENT_OBJ_EVENTRECEIVE= (600 + 36),
     EVENT_WIND_EXIT_DISPATCH= (50 + 2),
     EVENT_WIND_EXIT_NODISPATCH= (50 + 3),
     EVENT_WIND_EXIT_DISPATCH_PI= (50 + 4),
     EVENT_WIND_EXIT_NODISPATCH_PI= (50 + 5),
 EVENT_WIND_EXIT_IDLE= (50 + 6),
 EVENT_TASKLOCK= (50 + 7),
 EVENT_TASKUNLOCK= (50 + 8),
 EVENT_TICKANNOUNCE= (50 + 9),
 EVENT_EXCEPTION= (50 + 10),
    EVENT_TASK_STATECHANGE= (50 + 11),
     MIN_PSEUDO_EVENT= (50 + 20),
     EVENT_STATECHANGE= (50 + 20),
     EVENT_NIL= (50 + 21),
     EVENT_VALUE= (50 + 22),
     MAX_PSEUDO_EVENT= (50 + 24),
};
