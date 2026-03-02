enum SEMID {
    SPI_1A = 0x1a,
    SPI_1B = 0x1b,
    SPI_1C = 0x1c,
    SPI_1D = 0x1d,
    SPI_1E = 0x1e,
    SPI_1F = 0x1f,
    I2C_31 = 0x31,
    I2C_32 = 0x32,
    I2C_33 = 0x33,
};

enum DIAG_COUNTER {
   KEY       = 0x00,
   SHUTTER1  = 0x01,
   SHUTTER2  = 0x02,
   FLASH     = 0x03,
   BOOT      = 0x04,
   ZOOM_STEP = 0x05,
   BATT_END  = 0x06,
   USB_ON    = 0x07,
   DUST      = 0x08,
   CNT_9     = 0x09, //not used on xt4
   CMOS_T0   = 0x0a,
   CMOS_T1   = 0x0b,
   CMOS_T2   = 0x0c,
   CNT_D     = 0x0d, //not used on xt4
   EVF_CNT_e = 0x0e,
   SHUTTER11 = 0x11,
};


enum DIAG_COUNTER2 {
   KEY       = 0x00,
   BOOT      = 0x04,
   ZOOM_STEP = 0x05,
   BATT_END  = 0x06,
   USB_ON    = 0x07,
   DUST      = 0x08,
};
