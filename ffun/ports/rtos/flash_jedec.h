/* TODO: double check */
enum SPI_NOR_CMD {

    SPI_NOP                = 0x00,

    /* 0x01–0x0F */
    SPI_WRSR               = 0x01,   // JEDEC: Write Status Register #1
    SPI_PAGE_PROGRAM       = 0x02,   // JEDEC: Page Program (3-byte addr)
    SPI_READ               = 0x03,   // JEDEC: Read (3-byte addr)
    SPI_WRDI               = 0x04,   // JEDEC: Write Disable
    SPI_RDSR               = 0x05,   // JEDEC: Read Status Register #1
    SPI_WREN               = 0x06,   // JEDEC: Write Enable
    SPI_FAST_READ          = 0x0B,   // JEDEC: Fast Read
    SPI_FAST_READ_4B       = 0x0C,   // JEDEC: Fast Read (4-byte)

    /* 0x10–0x1F */
    SPI_PP_4B              = 0x12,   // JEDEC: Page Program (4-byte)
    SPI_READ_4B            = 0x13,   // JEDEC: Read (4-byte addr)
    SPI_RDSR3              = 0x15,   // JEDEC: Read Status Register #3
    SPI_BANK_ACCESS        = 0x16,   // Bank Register Access ?

    /* 0x20–0x2F */
    SPI_ERASE              = 0x20,   // JEDEC: Sector Erase (4KB?)
    SPI_ERASE_4K_4B        = 0x21,   // JEDEC: 4KB Erase (4-byte addr)

    /* 0x30–0x3F */
    SPI_QPAGE_PROGRAM      = 0x32,   // JEDEC: Quad Page Program
    SPI_RDSR2              = 0x35,   // JEDEC: Read Status Register #2
    SPI_WRITE_LOCK         = 0x36,   // JEDEC block protection
    SPI_QPI_ENTER_MX       = 0x38,   // Macronix: Enter QPI mode
    SPI_UNLOCK_LOCK        = 0x39,
    SPI_DO_FASTRD          = 0x3B,
    SPI_READ_LOCK          = 0x3D,

    /* 0x40–0x4F */

    SPI_READ_UID           = 0x4B,   // JEDEC: Read Unique ID

    /* 0x50–0x5F */

    SPI_CLEAR_FLAG_MICRON  = 0x50,   // Micron: Clear Flag Status
    SPI_ERASE_32K          = 0x52,   // JEDEC: 32KB erase
    SPI_ERASE_0x5C         = 0x5C,   // JEDEC: erase ?
    SPI_RDSFDP             = 0x5A,   // JEDEC: Read SFDP (Serial Flash Discoverable Parameters)
    SPI_FETCHSFDP          = 0x5B,   // JEDEC: Fetch SFDP

    /* 0x60–0x6F */

    SPI_CHIP_ERASE_2       = 0x60,   // JEDEC: Chip erase
    SPI_ENABLE_RESET       = 0x66,   // JEDEC JESD216: Reset Enable
    SPI_QUAD_READ          = 0x6B,   // Common vendor: Quad Fast Read (1-1-4)

    /* 0x70–0x7F */
    SPI_FLAG_STATUS_MICRON = 0x70,   // Micron: Read Flag Status?

    SPI_READ_STA           = 0x81,   // Micron: Read Flag Status?

    /* 0x90–0x9F */
    SPI_REMS               = 0x90,   // JEDEC legacy ID
    SPI_CMD98              = 0x98,   // Disable protection?
    SPI_RESET_DEVICE       = 0x99,   // JEDEC JESD216: Software Reset Device
    SPI_RDID               = 0x9F,   // JEDEC Read ID

    /* 0xA0–0xAF */

    SPI_RELEASE_POWERDOWN  = 0xAB,   // JEDEC: Wake from Power-Down mode

    /* 0xB0–0xBF */
    SPI_ENTER_4B           = 0xB7,   // JEDEC: Enter 4-byte address mode
    SPI_DEEP_POWERDOWN     = 0xB9,   // JEDEC: Deep Power-Down
    SPI_DIOR               = 0xBB,   // Dual I/O Fast Read

    /* 0xC0–0xCF */
    SPI_CHIP_ERASE_1       = 0xC7,   // JEDEC: Chip erase
    SPI_OCTAL_DDR_READ     = 0xCC,   // Micron/MXIC: Octal DDR Read

    /* 0xD0–0xDF */
    SPI_ERASE_64K          = 0xD8,   // JEDEC: 64KB erase
    SPI_ERASE_256K         = 0xDC,   // JEDEC: 64KB or 256K erase ?


    /* 0xE0–0xEF */

    SPI_ENTER_OCTAL        = 0xE7,   // Macronix, Winbond: Enter Octal mode
    SPI_EXIT_4B            = 0xE9,   // JEDEC: Exit 4-byte address mode
    SPI_QIOR               = 0xEB,   // Quad I/O Read
    SPI_QIOR_4B            = 0xEC,   // Quad I/O Read 4B opcode
    SPI_DDR_QUAD_READ      = 0xEE,   // DDR Quad I/O Read

    /* 0xF0–0xFF */
    SPI_QAUD_READ = 0xFD,            //  Micron MT25Q / MT35XU Double Tranffer Rate Read 4B
    SPI_CMD_0xFF = 0xFF,            // Reset continuous read mode (many vendors)
    //SPI_EXIT_OCTAL         = 0xFF,   // ?
    //SPI_QPI_EXIT_MX        = 0xFF,   // Macronix: Exit QPI mode

};


enum FLASH_ID {
    MicronMT25_512 = 0x20bb20, //1.8V 512Mb
    MicronMT35_512 = 0x2c5b1a, //("mt35xu512a", 0x2c5b1a, 0x104100,  128 * 1024	,  512, USE_FSR | SPI_NOR_4B_OPCODES) 
    MicronMT35_1G  = 0x2c5b1b, //1G
    Maxronix2      = 0xC2803A,
    Macronix1      = 0xC2352A,
};

