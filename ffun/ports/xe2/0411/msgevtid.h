enum MSGEVTID {
//KEYCODE
KEY_OK=0x1,
KEY_UP=0x2,
KEY_DOWN=0x3,
KEY_LEFT=0x4,
KEY_RIGHT=0x5,
KEY_POWER=0x6,
KEY_S1=0x7,
KEY_S2=0x8,
KEY_DISP_BACK=0x9,
KEY_FMODE=0xa,
KEY_PLAY=0xb,
KEY_BARRIER_OPEN=0xc,
KEY_BARRIER_CLOSE=0xd,
KEY_ADP_DET=0xe,
KEY_USB=0xf,
KEY_CARD_DET=0x10,
KEY_EXPOSURE=0x11,
KEY_ZOOM_TELE=0x12,
KEY_ZOOM_WIDE=0x13,
KEY_ZOOM_TELE2=0x14,
KEY_ZOOM_WIDE2=0x15,
KEY_AF=0x16,
KEY_DRIVE=0x17,
KEY_VIDEO=0x18,
KEY_HDTV=0x19,
KEY_CONTINUOUS=0x1a,
KEY_FLASH_POPUP=0x1b,
KEY_DIAL_UP=0x1c,
KEY_DIAL_DOWN=0x1d,
KEY_FOCUS_AF=0x1e,
KEY_FOCUS_CAF=0x1f,
KEY_FOCUS_MF=0x20,
KEY_ONEPUSH_AF=0x21,
KEY_ZOOMRING_UP=0x22,
KEY_ZOOMRING_DOWN=0x23,
KEY_AE_LOCK=0x24,
KEY_EVF_LCD=0x25,
KEY_ISO=0x26,
KEY_FUNCTION=0x27,
KEY_EVF_OVF=0x28,
KEY_AF_CSM=0x29,
KEY_CMDL_PUSH=0x2a,
KEY_CMDL_LEFT=0x2b,
KEY_CMDL_RIGHT=0x2c,
KEY_WB=0x2d,
KEY_AE=0x2e,
KEY_RAW=0x2f,
KEY_AF_LOCK=0x30,
KEY_Q=0x31,
KEY_EYE_SENSOR=0x32,
KEY_MOVIE_REC=0x33,
KEY_FLASH_EXT=0x34,
KEY_EXT_MICROPHONE=0x35,
KEY_WLAN=0x36,
KEY_LENS_DET=0x37,
KEY_MA_MENU=0x38,
KEY_CTRLRING_ZOOM_TELE=0x39,
KEY_CTRLRING_ZOOM_TELE2=0x3a,
KEY_CTRLRING_ZOOM_WIDE=0x3b,
KEY_CTRLRING_ZOOM_WIDE2=0x3c,
KEY_FUNCTION3=0x3d,
KEY_ND_FILTER=0x3e,
KEYEVENT_KEY_END=0x3f,
KEY_RING_UP_4=0x101,
KEY_RING_UP_3=0x102,
KEY_RING_UP_2=0x103,
KEY_RING_UP_1=0x104,
KEY_RING_STOP=0x105,
KEY_RING_DOWN_1=0x106,
KEY_RING_DOWN_2=0x107,
KEY_RING_DOWN_3=0x108,
KEY_RING_DOWN_4=0x109,
KEY_LXLENS_END=0x10a,
KEY_HVS_0=0x200,
KEY_HVS_90=0x201,
KEY_HVS_180=0x202,
KEY_HVS_270=0x203,
KEY_RING_OFF=0x204,
KEY_RING_STDBY=0x205,
KEY_RING_ON=0x206,
KEY_WHEELDIAL_CW=0x207,
KEY_WHEELDIAL_CCW=0x208,
KEY_RING_UP=0x209,
KEY_RING_DOWN=0x20a,
KEY_FOCUS_RING_MOVE=0x20b,
KEY_FOCUS_RING_LEFT=0x20c,
KEY_FOCUS_RING_RIGHT=0x20d,
KEY_CTRLRING_CW=0x20e,
KEY_CTRLRING_CCW=0x20f,
KEY_CTRLRING_MF=0x210,
KEY_AEAF_LOCK=0x211,
KEY_R1_S1=0x212,
KEY_R1_S2=0x213,
KEY_R2_S1=0x214,
KEY_R2_S2=0x215,
KEY_STARTFACT_CDW=0x216,
KEY_STARTFACT_POWER=0x217,
KEY_STARTFACT_S1=0x218,
KEY_EXT_TERMINAL_DETECT=0x219,
KEY_METER_SPOT=0x21a,
KEY_METER_MULTI=0x21b,
KEY_METER_AVE=0x21c,
KEY_DOOR=0x21d,
KEY_FACEDETECT=0x21e,
KEY_MACRO=0x21f,
KEY_PS=0x220,
KEY_CRD_DET=0x221,
KEY_CRD_PLAY=0x222,
KEY_CRD_USB=0x223,
KEY_VIEW=0x224,
KEY_EV=0x225,
KEY_FUNCTION2=0x226,
KEY_WIFI=0x227,
KEY_HOME=0x228,
KEY_INFO=0x229,
KEY_METER=0x22a,
KEY_LDISP=0x22b,
KEY_FOCUS=0x22c,
KEY_DELETE=0x22d,
KEY_CMD2_LEFT=0x22e,
KEY_CMD2_RIGHT=0x22f,
KEY_EXTFUNCTION=0x230,
KEY_GRIP_CMDL_LEFT=0x231,
KEY_GRIP_CMDL_RIGHT=0x232,
KEY_GRIP_CMD2_LEFT=0x233,
KEY_GRIP_CMD2_RIGHT=0x234,
KEY_CMD2_PUSH=0x235,
KEY_SP_NIGHTVIEW=0x236,
KEY_SP_NATURALPHOT=0x237,
KEY_SP_BLURREDUCTION=0x238,
KEY_SP_NATURALANDFLASH_MODE=0x239,
KEYEVENT_KEY_UNUSED_END=0x23a,
KEY_PLAY_MODE=0x300,
KEY_REC_MODE=0x301,
KEY_AUTO_MODE=0x302,
KEY_QUICK_MODE=0x303,
KEY_SP_MODE=0x304,
KEY_SP2_MODE=0x305,
KEY_SR_AUTO_MODE=0x306,
KEY_SP_PORTRAIT=0x307,
KEY_SP_LANDSCAPE=0x308,
KEY_SP_SPORTS=0x309,
KEY_PROGRAM_MODE=0x30a,
KEY_SHUTTER_MODE=0x30b,
KEY_APERTURE_MODE=0x30c,
KEY_AS_MODE=0x30d,
KEY_MANUAL_MODE=0x30e,
KEY_VOICE_MODE=0x30f,
KEY_MOVIE_MODE=0x310,
KEY_SETUP_MODE=0x311,
KEY_PSAM_MODE=0x312,
KEY_C1_MODE=0x313,
KEY_C2_MODE=0x314,
KEY_C3_MODE=0x315,
KEY_FSB_MODE=0x316,
KEY_EXR_MODE=0x317,
KEY_ADVANCE_MODE=0x318,
KEY_ADVANCE_FILTER_MODE=0x319,
KEY_PANORAMA_MODE=0x31a,
KEY_SHUTTER_DIAL_A=0x31b,
KEY_SHUTTER_DIAL_1_4000=0x31c,
KEY_SHUTTER_DIAL_1_2000=0x31d,
KEY_SHUTTER_DIAL_1_1000=0x31e,
KEY_SHUTTER_DIAL_1_500=0x31f,
KEY_SHUTTER_DIAL_1_250=0x320,
KEY_SHUTTER_DIAL_1_180=0x321,
KEY_SHUTTER_DIAL_1_125=0x322,
KEY_SHUTTER_DIAL_1_60=0x323,
KEY_SHUTTER_DIAL_1_30=0x324,
KEY_SHUTTER_DIAL_1_15=0x325,
KEY_SHUTTER_DIAL_1_8=0x326,
KEY_SHUTTER_DIAL_1_4=0x327,
KEY_SHUTTER_DIAL_1_2=0x328,
KEY_SHUTTER_DIAL_1_1=0x329,
KEY_SHUTTER_DIAL_T=0x32a,
KEY_SHUTTER_DIAL_B=0x32b,
KEY_EXP_DIAL_P3=0x32c,
KEY_EXP_DIAL_P8_3=0x32d,
KEY_EXP_DIAL_P7_3=0x32e,
KEY_EXP_DIAL_P2=0x32f,
KEY_EXP_DIAL_P5_3=0x330,
KEY_EXP_DIAL_P4_3=0x331,
KEY_EXP_DIAL_P1=0x332,
KEY_EXP_DIAL_P2_3=0x333,
KEY_EXP_DIAL_P1_3=0x334,
KEY_EXP_DIAL_0=0x335,
KEY_EXP_DIAL_M1_3=0x336,
KEY_EXP_DIAL_M2_3=0x337,
KEY_EXP_DIAL_M1=0x338,
KEY_EXP_DIAL_M4_3=0x339,
KEY_EXP_DIAL_M5_3=0x33a,
KEY_EXP_DIAL_M2=0x33b,
KEY_EXP_DIAL_M7_3=0x33c,
KEY_EXP_DIAL_M8_3=0x33d,
KEY_EXP_DIAL_M3=0x33e,
KEY_JIGBOOT=0x33f,
KEYEVENT_MODE_END=0x340,
KEY_M_IRIS_A=0x400,
KEY_M_IRIS_0=0x401,
KEY_M_IRIS_1=0x402,
KEY_M_IRIS_2=0x403,
KEY_M_IRIS_3=0x404,
KEY_M_IRIS_4=0x405,
KEY_M_IRIS_5=0x406,
KEY_M_IRIS_6=0x407,
KEY_M_IRIS_7=0x408,
KEY_M_IRIS_8=0x409,
KEY_M_IRIS_9=0x40a,
KEY_M_IRIS_10=0x40b,
KEY_M_IRIS_11=0x40c,
KEY_M_IRIS_12=0x40d,
KEY_M_IRIS_13=0x40e,
KEY_M_IRIS_14=0x40f,
KEY_M_IRIS_15=0x410,
KEY_M_IRIS_16=0x411,
KEY_M_IRIS_17=0x412,
KEY_M_IRIS_18=0x413,
KEY_M_IRIS_19=0x414,
KEY_M_IRIS_20=0x415,
KEY_M_IRIS_21=0x416,
KEY_M_IRIS_22=0x417,
KEY_M_IRIS_23=0x418,
KEY_M_IRIS_24=0x419,
KEY_M_IRIS_25=0x41a,
KEY_M_IRIS_26=0x41b,
KEY_M_IRIS_27=0x41c,
KEY_M_IRIS_28=0x41d,
KEY_M_IRIS_29=0x41e,
KEY_M_IRIS_30=0x41f,
LENS_POWER_ON=0x420,
LENS_POWER_OFF=0x421,
LENS_MA=0x422,
KEY_OIS=0x423,
KEY_IRIS_RING_MOVE=0x424,
KEY_IRIS_AUTO=0x425,
KEY_FOCUS_DIST=0x426,
KEY_FOCUS_RING_POS=0x427,
KEYEVENT_MODE_LXLENS_END=0x42b,
KEY_M_IRIS_F16=0x500,
KEY_M_IRIS_F14=0x501,
KEY_M_IRIS_F13=0x502,
KEY_M_IRIS_F11=0x503,
KEY_M_IRIS_F10=0x504,
KEY_M_IRIS_F9=0x505,
KEY_M_IRIS_F8=0x506,
KEY_M_IRIS_F7_1=0x507,
KEY_M_IRIS_F6_4=0x508,
KEY_M_IRIS_F5_6=0x509,
KEY_M_IRIS_F5_0=0x50a,
KEY_M_IRIS_F4_5=0x50b,
KEY_M_IRIS_F4_0=0x50c,
KEY_M_IRIS_F3_6=0x50d,
KEY_M_IRIS_F3_2=0x50e,
KEY_M_IRIS_F2_8=0x50f,
KEY_M_IRIS_F2_5=0x510,
KEY_M_IRIS_F2_2=0x511,
KEY_M_IRIS_F2_0=0x512,
KEY_LCD_BACKFACE=0x513,
KEY_LCD_FRONTFACE=0x514,
KEY_LCD_TILT=0x515,
KEY_LCD_OFF=0x516,
KEY_ISO_A=0x517,
KEY_ISO_L=0x518,
KEY_ISO_200=0x519,
KEY_ISO_200_1_3=0x51a,
KEY_ISO_200_2_3=0x51b,
KEY_ISO_400=0x51c,
KEY_ISO_400_1_3=0x51d,
KEY_ISO_400_2_3=0x51e,
KEY_ISO_800=0x51f,
KEY_ISO_800_1_3=0x520,
KEY_ISO_800_2_3=0x521,
KEY_ISO_1600=0x522,
KEY_ISO_1600_1_3=0x523,
KEY_ISO_1600_2_3=0x524,
KEY_ISO_3200=0x525,
KEY_ISO_3200_1_3=0x526,
KEY_ISO_3200_2_3=0x527,
KEY_ISO_6400=0x528,
KEY_ISO_H1=0x529,
KEY_ISO_H2=0x52a,
KEY_DRIVE_PANORAMA=0x52b,
KEY_DRIVE_ADV_FILTER=0x52c,
KEY_DRIVE_MULTIPLAYING=0x52d,
KEY_DRIVE_ONESHOT=0x52e,
KEY_DRIVE_CONT_LOW=0x52f,
KEY_DRIVE_CONT_HIGH=0x530,
KEY_DRIVE_BKT=0x531,
KEY_DRIVE_ADV_FILTER2=0x532,
KEY_DRIVE_BKT2=0x533,
KEY_RECL_AUTO=0x534,
KEY_RECL_MANUAL=0x535,
KEYEVENT_MODE_UNUSED_END=0x536,
BATT_HIGH=0x600,
BATT_HALF=0x601,
BATT_PREEND=0x602,
BATT_END=0x603,
KEYEVENT_BATT_END=0x604,
USB_BUSY=0x700,
USB_UNMOUNT=0x701,
USB_MEDIA_ACCESS_START=0x702,
USB_MEDIA_ACCESS_STOP=0x703,
STRB_READY=0x800,
STRB_NOT_READY=0x801,
STRB_DISABLE=0x802,
DPOF_BUSY=0x803,
DPOF_READY=0x804,
WARN_AE=0x805,
WARN_AE_OFF=0x806,
WARN_AF=0x807,
WARN_AF_OFF=0x808,
WARN_HAND=0x809,
WARN_HAND_OFF=0x80a,
WARN_UNDER=0x80b,
WARN_UNDER_OFF=0x80c,
WARN_OVER=0x80d,
WARN_OVER_OFF=0x80e,
LEVEL_SENS_UPDATE=0x80f,
CMOSTEMP_NORMAL=0x810,
CMOSTEMP_HIGH=0x811,
CMOSTEMP_LIMIT=0x812,
FLASH_EXT_CHARGE_EMPTY=0x813,
FLASH_EXT_CHARGE_HALF=0x814,
FLASH_EXT_CHARGE_FULL=0x815,
COMPLETE=0x816,
DISP_DONE=0x817,
DISP_END=0x818,
REC_DONE=0x819,
REC_HEATING=0x81a,
REC_ABORT=0x81b,
ENABLE_REC=0x81c,
ENABLE_KEY=0x81d,
READ_DONE=0x81e,
PLAY_DONE=0x81f,
PLAY_APP2_DONE=0x820,
FILE_SEARCH_READY=0x821,
WRITING=0x822,
WRITING_COMPLETE=0x823,
OVERCOMPLETE=0x824,
OVER_COMPLETE=0x825,
NOSET_COMPLETE=0x826,
S1_AF_FOCALIZE=0x827,
S1_COMPLETE=0x828,
MULTIPLYING=0x829,
EXPOSURE_DONE=0x82a,
PINP_FRAME_ON=0x82b,
PINP_FRAME_OFF=0x82c,
UPDATE_PB=0x82d,
UPDATE_REC=0x82e,
UPDATE_MEDIA=0x82f,
UPDATE_SYS=0x830,
UPDATE_UPDATE=0x831,
UPDATE_GPS=0x832,
UPDATE_BATT=0x833,
UPDATE_EYEFI=0x834,
UPDATE_USB_CHARGE=0x835,
STARTUP_START=0x836,
REC_DISP_START=0x837,
REC_DISP_STOP=0x838,
ACCEPT=0x839,
REJECT=0x83a,
S2_COUNT_START=0x83b,
S2_SHADE_START=0x83c,
S2_COMPLETE=0x83d,
MOVIE_START=0x83e,
CAMERA_READY=0x83f,
RELEASE_READY=0x840,
PRE_PLAY_READY=0x841,
CHARGE_START=0x842,
CHARGE_STOP=0x843,
VIEW_START=0x844,
VIEW_CHANGE=0x845,
VIEW_READY=0x846,
VIEW_ABORT=0x847,
VIEW_STOP=0x848,
VIEW_AUTO_FACE_REGIST=0x849,
ABORT_RECEIVED=0x84a,
WRITING_START=0x84b,
WRITING_STOP=0x84c,
DUST_REDUCTION_START=0x84d,
DUST_REDUCTION_STOP=0x84e,
HEATING=0x84f,
MOVIE_ABORT=0x850,
OPENING_READY=0x851,
COPY_READY=0x852,
RED_EYE_DETECT_START=0x853,
RED_EYE_CORRECT_START=0x854,
RED_EYE_CORRECT_STOP=0x855,
RED_EYE_VIEW_CHANGE=0x856,
FACE_RECOG_COMPLETE=0x857,
FACE_RECOG_FAILS=0x858,
MICRO_FRAME=0x859,
MULTI_FRAME=0x85a,
SYNTHESIS_START=0x85b,
SYNTHESIS_STOP=0x85c,
AUTO_SHUTTER_ENABLE=0x85d,
MATCHING_FAIL=0x85e,
ERR_MATCHING_ERROR=0x85f,
BEAF_REC_START=0x860,
WRITING_ABORT_READY=0x861,
UPDATE_FILE=0x862,
HOLD_IMAGE=0x863,
START_AFL=0x864,
FOCUS_PRIORITY_REC_ENABLE=0x865,
IMAGE_READY=0x866,
AF_CHASE_OSD_START=0x867,
AF_CHASE_OSD_END=0x868,
EXWIFI_ABORT=0x869,
EXWIFI_APOFF=0x86a,
EXWIFI_COMPLETE=0x86b,
EXWIFI_PICTURE_SAVE_COMPLETE=0x86c,
EXWIFI_AUTO_POWOFF_COMPLETE=0x86d,
UPDATE_DPS_PAPER=0x86e,
UPDATE_DPS_STATUS=0x86f,
UPDATE_DPS_CAPABILITY=0x870,
FILE_ID_BUSY=0x871,
FILE_ID_READY=0x872,
IRDA_UPDATE_PROGRESS=0x873,
PCSH_EV_CAPTURE_IMAGE=0x874,
PCSH_EV_START_LIVE_IMAGE=0x875,
PCSH_EV_STOP_LIVE_IMAGE=0x876,
PCSH_EV_GET_DEV_PROP_DESC=0x877,
PCSH_EV_GET_DEV_PROP_VALUE=0x878,
PCSH_EV_SET_DEV_PROP_VALUE=0x879,
PCSH_EV_RESET_DEV_PROP_VALUE=0x87a,
PCSH_EV_GET_STORAGE_INFO=0x87b,
PCSH_EV_GET_IMAGE_INFO=0x87c,
PCSH_EV_DEL_IMAGE=0x87d,
PCSH_EV_RECEIVE_FIRMWARE=0x87e,
PCSH_EV_UPDATE_FIRMWARE=0x87f,
PCSH_EV_ADD_IMAGE=0x880,
PCSH_EV_CLEAR_IMAGE=0x881,
PCSH_EV_NOTIFY_DEV_PROP_CHG=0x882,
UPDATE_WIFI_STATUS=0x883,
WLAN_PROC_START=0x884,
WLAN_REMOTE_GET_PARAM_ALL=0x885,
WLAN_REMOTE_DEVICE_STATUS_CURRENT=0x886,
WLAN_REMOTE_SETPARAM=0x887,
WLAN_REMOTE_START_LIVE_VIEW=0x888,
WLAN_REMOTE_END_LIVE_VIEW=0x889,
WLAN_REMOTE_STEP_ZOOM=0x88a,
WLAN_REMOTE_START_ZOOM=0x88b,
WLAN_REMOTE_STOP_ZOOM=0x88c,
WLAN_REMOTE_S1_LOCK=0x88d,
WLAN_REMOTE_S1_LOCK_OFF=0x88e,
WLAN_REMOTE_REC_CAPUTURE=0x88f,
WLAN_REMOTE_CANCEL_SELFTIMER=0x890,
WLAN_REMOTE_START_MOVIE=0x891,
WLAN_REMOTE_STOP_MOVIE=0x892,
WLAN_REMOTE_CHANGE_SHUTTERSPEED=0x893,
WLAN_REMOTE_CHANGE_FNUMBER=0x894,
WLAN_REMOTE_CHANGE_EXPOSURE=0x895,
INTERVAL_SHOOT_TRIGGER=0x896,
//ERR EVT
ERR_NO_ERROR=0x900,
ERR_NO_CARD=0x901,
ERR_FILE_NUMBER_FULL=0x902,
ERR_CARD_NOT_INITIAL=0x903,
ERR_CARD_ERROR=0x904,
ERR_CARD_FULL=0x905,
ERR_WRITE_ERROR=0x906,
ERR_FOCUS_ERROR=0x907,
ERR_ZOOMING_ERROR=0x908,
ERR_VOICEMEMO_ERROR=0x909,
ERR_READ_ERROR=0x90a,
ERR_PROTECTED=0x90b,
ERR_DPOF_FILE_ERROR=0x90c,
ERR_WRITE_MOVIE=0x90d,
ERR_CAN_NOT_EXECUTE=0x90e,
ERR_LENS_COVER_ERROR=0x90f,
ERR_DATESORT_FILE_OVER=0x910,
ERR_TRIMMING=0x911,
ERR_IRDA=0x912,
ERR_PARALLAX=0x913,
ERR_PRINTER_FAIL=0x914,
ERR_DPS=0x915,
ERR_UPDATE=0x916,
ERR_WB_OVER=0x917,
ERR_WB_UNDER=0x918,
ERR_FLASH_WRONG=0x919,
ERR_OTHERS=0x91a,
ERR_SYSTEM_HALT=0x91b,
ERR_SPECIFIC=0x91c,
ERR_MIZ_EMERGENCY=0x91d,
ERR_TP_CALIBRATION=0x91e,
ERR_PICTURE_SEARCH_ERROR=0x91f,
ERR_NOT_FOUND=0x920,
ERR_MATCHING_ERROR_SPEED_SLOW=0x921,
ERR_MATCHING_ERROR_GAP=0x922,
ERR_MATCHING_ERROR_SPEED=0x923,
ERR_MATCHING_ERROR_CORRELATION=0x924,
ERR_MATCHING_ERROR_SEAMLESS=0x925,
ERR_RETOUCH_MODE_ERROR=0x926,
ERR_RETOUCH_ERROR=0x927,
ERR_WIFI_CONNECT=0x928,
ERR_WIFI_SEND=0x929,
ERR_WIFI_GPS=0x92a,
ERR_WIFI_FILM=0x92b,
ERR_WIFI_PRINTING=0x92c,
ERR_WIFI_SCAN=0x92d,
ERR_WIFI_PC_SEARCH=0x92e,
ERR_WIFI_PC_REGISTER=0x92f,
ERR_IRIS_ERROR=0x930,
ERR_FOCAL_PLANE_SHUTTER_ERROR=0x931,
ERR_FW_COMPATIBLE_OLD_LENS=0x932,
ERR_FW_COMPATIBLE_OLD_BODY=0x933,
ERR_FW_UNSUPPORTED_LENS=0x934,
ERR_LENS_TIMEOUT_BOOT=0x935,
ERR_LENS_TIMEOUT_INIT=0x936,
ERR_LENS_PRODUCT_ID=0x937,
ERR_LENS_TERMINAL_ERROR=0x938,
ERR_LENS_COMMUNICATION_ERROR=0x939

/* 
USER1=0xa00,
USER2=0xa01,
USER3=0xa02,
USER4=0xa03,
USER5=0xa04,
*/

//UI EVT
UI_EVT_TO_ERROR_INDICATE=0xa00,
UI_EVT_TO_SELFTIMER_INDICATE=0xa01,
UI_EVT_TO_AUTO_POWER_OFF=0xa02,
UI_EVT_TO_AUTO_STANDBY=0xa03,
UI_EVT_TO_ZOOM_W_AUTO_POWER_OFF=0xa04,
UI_EVT_MODECHG=0xa05,
UI_EVT_TO_THUMBNAIL=0xa06,
UI_EVT_TO_AUTOPLAY=0xa07,
UI_EVT_TO_DPOF=0xa08,
UI_EVT_TO_PLAY_GUIDE=0xa09,
UI_EVT_TO_PLAY_SINK=0xa0a,
UI_EVT_TO_BATTERY_END=0xa0b,
UI_EVT_TO_ALLRESET=0xa0c,
UI_EVT_TO_STARTUP=0xa0d,
UI_EVT_TO_KEY_LOCK=0xa0e,
UI_EVT_TO_FUNCTION_MENU=0xa0f,
UI_EVT_TO_QUICK_MENU=0xa10,
UI_EVT_TO_GPS_POWER_SEARCH=0xa11,
UI_EVT_TO_MF_ASSIST=0xa12,
UI_EVT_TO_MANNER=0xa13,
UI_EVT_TO_VISIBILITY=0xa14,
UI_EVT_TO_DISCHARGE=0xa15,
UI_EVT_TO_DISCHARGE_LIMIT=0xa16,
UI_EVT_TO_MACRO=0xa17,
UI_EVT_TO_POSTVIEW=0xa18,
UI_EVT_TO_DPS_NEGO=0xa19,
UI_EVT_TO_CONNECT=0xa1a,
UI_EVT_TO_PINP=0xa1b,
UI_EVT_TO_ECOTIMER=0xa1c,
UI_EVT_TO_MOVIE_ECOTIMER=0xa1d,
UI_EVT_RELEASE_MENU_END=0xa1e,
UI_EVT_TO_PROTECT_FINISH=0xa1f,
UI_EVT_TO_DELETE_ONE=0xa20,
UI_EVT_TO_COPY_COMP=0xa21,
UI_EVT_TO_PLAYINFO_FINISH=0xa22,
UI_EVT_TO_COMMUNICATION_SEARCH=0xa23,
UI_EVT_TO_PRINT_COMPLETE=0xa24,
UI_EVT_AFTERS2_AEL2UNLOCK=0xa25,
UI_EVT_TO_MOVIE_HEAT_ABORT=0xa26,
UI_EVT_MANUALZOOM_AEL_UNLOCK=0xa27,
UI_EVT_ERROR_REDISP=0xa28,
UI_EVT_CHARGE_FLASH=0xa29,
UI_EVT_REQHOLD=0xa2a,
UI_EVT_REC_MODEDIAL_DEL=0xa2b,
UI_EVT_FONTDB_NOT_ACCESS=0xa2c,
UI_EVT_UILIB_ANIMATION_FINISH=0xa2d,
UI_EVT_UILIB_MAIN_LAYER_OFF_FINISH=0xa2e,
UI_EVT_UILIB_MIC_REMOTE_RELEASE_GUIDE_FINISH=0xa2f,
UI_EVT_UILIB_INMEDIA_GUIDE_FINISH=0xa30,
UI_EVT_PLAY_MENU_DISP=0xa31,
UI_EVT_PLAY_CHG_GUIDE=0xa32,
UI_EVT_TO_IRDA_SEND_RECV_COMP=0xa33,
UI_EVT_REC_DISP_THROUGH=0xa34,
UI_EVT_TO_AP_IRSS_SEND_NG_DISP=0xa35,
UI_EVT_ERR_MIZ_EMERGENCY=0xa36,
UI_EVT_REC_LCDBRIGHTNESS=0xa37,
UI_EVT_TO_KEY_ON=0xa38,
UI_EVT_ENDING_START=0xa39,
UI_EVT_TO_ENDING_DISP=0xa3a,
UI_EVT_TO_DIRECT_MENU=0xa3b,
UI_EVT_TO_PLAY_SEARCH_FILE_NOT_EXIST=0xa3c,
UI_EVT_TO_FACE_MV_BTN_DELAY=0xa3d,
UI_EVT_PLAY_AP_PANORAMA_DISP_TIMEOUT=0xa3e,
UI_EVT_PLAY_DELETE_SELECT_TIMEOUT=0xa3f,
UI_EVT_TO_PLAY_UPLOAD_DISP=0xa40,
UI_EVT_MIC_REMOTE_SETTING_CONFIRM_GUIDE_DISP=0xa41,
UI_EVT_MIC_REMOTE_DRIVE_UPDATE=0xa42,
UI_EVT_S1NG_ERASE=0xa43,
UI_EVT_FORMAT_START=0xa44,
UI_EVT_ERASE_FADE_ANIME_COMP=0xa45,
UI_EVT_AUTO_SHUTTER=0xa46,
UI_EVT_TO_SET_MIC_REMOTE=0xa47,
UI_EVT_MENU_BACKGROUND_DATA_SET=0xa48,
UI_EVT_TO_PANORAMA_SAVE_LENS=0xa49,
UI_EVT_PLAY_CONT_SUB_START=0xa4a,
UI_EVT_TO_NO_OPARATION=0xa4b,
UI_EVT_TO_TEMPWORM_POWEROFF=0xa4c,
UI_EVT_TO_TEMPWORM_POWEROFF_MSG=0xa4d,
UI_EVT_PLAY_CONT_ONE_READ=0xa4e,
UI_EVT_UILIB_LOAD_COMPLETE=0xa4f,
UI_EVT_TO_INTERVAL_COUNTDOWN=0xa50,
UI_EVT_TO_PLAY_WLAN_SERACH=0xa51,
UI_EVT_TO_PLAY_WLAN_RETRY=0xa52,
UI_EVT_TO_PLAY_WLAN_NO_OPE=0xa53,
UI_EVT_TO_PLAY_WLAN_END_DISP=0xa54,
UI_EVT_TO_PLAY_WLAN_GET_GPS_END_DISP=0xa55,
UI_EVT_TO_PLAY_WLAN_GET_GPS_DISP=0xa56,
UI_EVT_TO_WLAN_AP_CONNECT=0xa57,
UI_EVT_TO_WLAN_PC_SEARCH=0xa58,
UI_EVT_TO_PCSAVE_NO_OPARATION=0xa59,
UI_EVT_TO_INSTAX_NO_OPARATION=0xa5a,
UI_EVT_PLAY_INSTAX_END_REQ=0xa5b,
UI_EVT_TO_PLAY_9_MULTI_RET=0xa5c,
UI_EVT_TO_PLAY_MULTISELECT_OVER=0xa5d,
UI_EVT_AELOCK_CANCEL=0xa5e,
UI_EVT_ABORT_THROUGH=0xa5f,
UI_EVT_TO_PROCESSING=0xa60,
UI_EVT_REMOTE_REC_END=0xa61,
UI_EVT_TO_MOVIE_BACKLIGHT_SAVE=0xa62,
UI_EVT_OSDOFF_NOERR_REPLY=0xa63,
UI_EVT_OSDDISP_REPLY=0xa64,
UI_EVT_TIMING_START=0xa65,
UI_EVT_TIMING_SETP_COMPLETE=0xa66,
UI_EVT_TIMING_BLOG_IRDADEINIT_REDISP=0xa67,
UI_EVT_TIMING_AP_IRSS_SEND=0xa68,
UI_EVT_TIMING_AP_IRSS_FRAME_SKIP=0xa69,
UI_EVT_TIMING_PLAY_MULTI_STOP_TO_ZOOM=0xa6a,
UI_EVT_TIMING_MICRO_MULTI_EXPAND=0xa6b,
UI_EVT_TIMING_AP_IRSS_SEND_NG_DISP=0xa6c,
UI_EVT_TIMING_PROTECTCARD_ERROR=0xa6d,
UI_EVT_TIMING_PB_INIT_MENUTAB=0xa6e,
UI_EVT_TIMING_PB_INIT_MENU_PICSEARCH=0xa6f,
UI_EVT_TIMING_PB_MENU_DEINIT_COMPLETE=0xa70,
UI_EVT_TIMING_PLAY_DATE_START=0xa71,
UI_EVT_TIMING_SEARCH_TO_PHOTOBOOK=0xa72,
UI_EVT_TIMING_PHOTOBOOK_ASSIST_MENU=0xa73,
UI_EVT_TIMING_PHOTOBOOK_MAKE_MENU=0xa74,
UI_EVT_TIMING_PHOTOBOOK_TO_DATE=0xa75,
UI_EVT_TIMING_TO_INFO=0xa76,
UI_EVT_TIMING_OVF_CHG=0xa77,
UI_EVT_TIMING_LCD_CHG=0xa78,
UI_EVT_TIMING_LCD_EVF_CHG=0xa79,
UI_EVT_TIMING_TO_FULLPLAY=0xa7a,
UI_EVT_TIMING_END=0xa7b,
UI_EVT_SYSTEM_HALT=0xa7c,
UI_EVT_END=0xa7d,

//TOUCH and PEER - not used on XE2
TP_TOUCH_ON=0xb00,
TP_TOUCH_OFF=0xb01,
TP_TOUCH_MOVE=0xb02,
TP_TOUCH_REPEAT=0xb03,
TP_TOUCH_SWEEP=0xb04,
TP_TOUCH_2_ON=0xb05,
TP_TOUCH_2_OFF=0xb06,
TP_TOUCH_2_MOVE=0xb07,
TP_TOUCH_2_REPEAT=0xb08,
TP_TOUCH_2_SWEEP=0xb09,
TP_TOUCH_MULTI_GESTURE=0xb0a,
TP_START_CALIBRATION=0xb0b,
FLASH_UIPEER=0xc00,
FLASH_PLAYERAPP=0xc01,
PLAYPEER_DECOMP=0xc02,
PLAYPEER_ABORT=0xc03,
PLAYPEER_BOOK=0xc04,
PLAYPEER_CURRENT=0xc05,
PLAYPEER_MULTI=0xc06,
PLAYPEER_SEARCH=0xc07

//DEBUG
UI_EVT_DEBUG_START=0xf000,
UI_EVT_DEBUG_TIMER_TIMEOUT=0xf001,
UI_EVT_DEBUG_GCON_CALLBACK=0xf002,
UI_EVT_DEBUG_END=0xf003,
UI_EVT_IGNORE=0xffff
};
