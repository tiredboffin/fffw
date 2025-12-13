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
    int errorStatus;
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
    ERR_07=0x7,
    ARRAY_OVR=0x8,
    ILLEGAL_PRIORITY=0x9,
    ZERO_EVENTS=0xa,
    NOT_ALL_EVENTS=0xb,
    INVALID_OBJ_ID=0xc,
    INVALID_PRM=0xd,
    ERR_0E=0xe,
    ERR_0C=0xf,
    INVALID_MSG_LENGTH=0x11,
    ERR_12=0x12,
    NOT_INITIALIZED=0x13,
    NO_SLOTS=0x14,
    EER_15=0x15,
    ERR_24=0x24,
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
