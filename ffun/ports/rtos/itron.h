// Subset of μITRON 4.0 Specification.
enum UTRON_ERR {
    E_SYS   = -5,   // System error
    E_NOSPT = -9,   // Unsupported function
    E_RSFN  = -10,  // Reserved function code
    E_RSATR = -11,  // Reserved attribute
    E_PAR   = -17,  // Parameter error
    E_ID    = -18,  // Invalid ID number
    E_CTX   = -25,  // Context error
    E_MACV  = -26,  // Memory access violation
    E_OACV  = -27,  // Object access violation
    E_ILUSE = -28,  // Illegal service call use
    E_NOMEM = -33,  // Insufficient memory
    E_NOID  = -34,  // No ID number available
    E_OBJ   = -41,  // Object state error
    E_NOEXS = -42,  // Non-existent object
    E_QOVR  = -43,  // Queuing overflow
    E_RLWAI = -49,  // Forced release from waiting
    E_TMOUT = -50,  // Polling failure or timeout
    E_DLT   = -51,  // Waiting object deleted
    E_CLS   = -52,  // Waiting object state changed
    E_WBLK  = -57,  // Non-blocking call accepted
    E_BOVR  = -58   // Buffer overflow
};

enum UTRON_TTS {
    TTS_RUN = 0x01, //RUNNING
    TTS_RDY = 0x02, //READY
    TTS_WAI = 0x04, //WAITING
    TTS_SUS = 0x08, //SUSPENDED
    TTS_WAS = 0x0c, //WAITING-SUSPENDED
    TTS_DMT = 0x10, //DORMANT
};