//driver level flash abstract commands, all translate to 4B mode
enum EEP_CMD {
    EEP_READ_ID = 0x00,
    EEP_WREN    = 0x01,
    EEP_RDSR    = 0x02,
    EEP_WRSR    = 0x03,
    EEP_04      = 0x04,
    EEP_RDSR3   = 0x05,
    EEP_ERASE   = 0x08,
    EEP_ERASE2  = 0x09,
    EEP_PRG     = 0x0a,
    EEP_RDFAST1 = 0x0b,
    EEP_RDFAST2 = 0x0c,
    EEP_READ    = 0x0d,
};