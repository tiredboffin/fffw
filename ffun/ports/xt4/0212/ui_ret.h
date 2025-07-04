//UI_RET
enum UI_RET {
IGNORE=0x0,
BUSY=0x1,
EXECUTION=0x2,
INIT_COMPLETE=0x3,
S1_COMPLETE=0x4,
S1OFF_COMPLETE=0x5,
AFON_COMPLETE=0x6,
AFOFF_COMPLETE=0x7,
REC_COMPLETE=0x8,
REC_SINGLE_COMPLETE=0x9,
REC_CONT_COMPLETE=0xa,
REC_VIEW_OFF_START=0xb,
LCDON_ACCEPT=0xc,
LCDOFF_ACCEPT=0xd,
MF_COMPLETE=0xe,
MOVIE_COMPLETE=0xf,
MOVIE_ABORT=0x10,
MF_ABORT=0x11,
EXPO_ABORT=0x12,
CHARGE_ABORT=0x13,
ACCEPT=0x14,
MF_ACCEPT=0x15,
ZOOM_ACCEPT=0x16,
ZOOM_COMPLETE=0x17,
ZOOM_ABORT=0x18,
ZOOM_STOP_ACCEPT=0x19,
MACRO_ACCEPT=0x1a,
MACRO_START_ACCEPT=0x1b,
PINP_ACCEPT=0x1c,
FULLTIME_MF_ACCEPT=0x1d,
MF_ASSIST_ACCEPT=0x1e,
MANUALSETTING_CANCEL_ACCEPT=0x1f,
CWB_ACCEPT=0x20,
S1_ACCEPT=0x21,
S1OFF_ACCEPT=0x22,
AFON_ACCEPT=0x23,
AFOFF_ACCEPT=0x24,
S2_ACCEPT=0x25,
VIEW_ACCEPT=0x26,
PREVIEW_ACCEPT=0x27,
CONTINUOUS_VIEW_ACCEPT=0x28,
AF_AREA_ACCEPT=0x29,
MF_AREA_ACCEPT=0x2a,
PC_AREA_ACCEPT=0x2b,
ONEPUSH_AF_ACCEPT=0x2c,
CAF_CTL_ACCEPT=0x2d,
DEINIT_ACCEPT=0x2e,
MYPOI_RECOG_SINGLE_ACCEPT=0x2f,
MYPOI_RECOG_ACCEPT=0x30,
MYPOI_RECOG_END=0x31,
MYPOI_RECOG_EDIT_ACCEPT=0x32,
MYPOI_RECOG_SHOT_COMPLETE=0x33,
MYPOI_RECOG_SHOT_CANCEL=0x34,
MYPOI_RECOG_SHOT_SUCCESS=0x35,
QUICK_ZOOM_ACCEPT=0x36,
REJECT=0x37,
MODECHG=0x38,
MENUCHG=0x39,
SETPARAM_ACCEPT=0x3a,
MENU_COMMON_START=0x3b,
MENU_COMMON_END=0x3c,
FOCUS_CHG=0x3d,
CWB_START_COMPLETE=0x3e,
CWB_SET_COMPLETE=0x3f,
CWB_CANCEL_COMPLETE=0x40,
CWB_OVER=0x41,
CWB_UNDER=0x42,
BRIGHTNESS_START=0x43,
BRIGHTNESS_END=0x44,
SPEAKER_VOLUME_END=0x45,
RECMENU_CWB=0x46,
MOVIE_ACCEPT=0x47,
SINGLE_ACCEPT=0x48,
CONTINUOUS_ACCEPT=0x49,
LCD_VISIBILITY_COMPLETE=0x4a,
SUPER_RESOLUTION_ZOOM_ACCEPT=0x4b,
RED_EYE_DETECT_ACCEPT=0x4c,
RED_EYE_DETECT_START=0x4d,
RED_EYE_CORRECT_START=0x4e,
RED_EYE_CORRECT_STOP=0x4f,
RED_EYE_ABORT_RECEIVED=0x50,
REC_MODECHG_ACCEPT=0x51,
REC_REMOTE_REC_START_COMPLETE=0x52,
RGB_HISTOGRAM_ACCEPT=0x53,
LEVAL_ACCEPT_3D=0x54,
ERROR_COMPLETE=0x55,
PLAY_MENU_FUNC_EXE=0x56,
PLAY_STAR_RANK_DISP=0x57,
MENU_CTRL_COMPLETE=0x58,
MENU_CTRL_EXECUTION=0x59,
PB_COMP_OSDREQ=0x5a,
PB_COMP_ZOOMWIDE=0x5b,
PB_INIT_COMPLETE=0x5c,
PB_LANG=0x5d,
PB_DATE=0x5e,
PB_LCD=0x5f,
PB_VOL=0x60,
PB_INIT_TO_INFO=0x61,
PB_COMP_YOUTUBE=0x62,
PB_COMP_FACEBOOK=0x63,
PB_COMP_MIXI=0x64,
PB_COMP_MYFINEPIX=0x65,
PB_COMP_CANCEL_ALL=0x66,
PB_COMP_ALL_END=0x67,
PB_COMP_ONE=0x68,
PB_COMP_LAST_ONE=0x69,
PB_COMP_ALL=0x6a,
PB_COMP_ALL_OK=0x6b,
PB_COMP_DD=0x6c,
PB_START_DELETE_SELECT=0x6d,
PB_COMP_DELETE_SELECT=0x6e,
PB_DELETE_SELECT_OVER_WARN=0x6f,
PB_START_MULTI_SELECT=0x70,
PB_COMP_MULTI_SELECT_EXCUTION=0x71,
PB_COMP_MULTI_SELECT=0x72,
PB_MULTI_SELECT_OVER_WARN=0x73,
PB_COMP_ALL_CANCEL=0x74,
PB_COMP_NEXT=0x75,
PB_COMP_BEFORE=0x76,
PB_COMP_REPEAT_NEXT=0x77,
PB_COMP_REPEAT_BEFORE=0x78,
PB_COMP_INFOREQ=0x79,
PB_COMP_ZOOMREQ=0x7a,
PB_COMP_MULTIREQ=0x7b,
PB_COMP_MULTI=0x7c,
PB_COMP_MULTI_FACE_MARKING=0x7d,
PB_COMP_ZOOMING_SELECT=0x7e,
PB_COMP_TRIM=0x7f,
PB_COMP_DATESORT=0x80,
PB_COMP_DATE_DEINIT=0x81,
PB_ABORT_COMP=0x82,
PB_ERRCOMP_DATESORT=0x83,
PB_COMP_MENU=0x84,
PB_COMP_FMENU=0x85,
PB_COMP_ERROREND=0x86,
PB_COMP_TIMERSTOP=0x87,
PB_ERRCOMP_COPY_DISPCOMP=0x88,
PB_ERRCOMP_COPY_NO=0x89,
PB_ERRCOMP_COPY_DEINIT=0x8a,
PB_ERR_PROTECTCARD=0x8b,
PB_ERR_SEARCH_FILE_OVER=0x8c,
PB_ERRCOMP_SEARCH_END=0x8d,
PB_COMP_COPY_DEINIT=0x8e,
PB_COMP_ROTATE=0x8f,
PB_COMP_COPY_GUIDE=0x90,
PB_EXEC_BEEPREQ=0x91,
PB_EXEC_CHG_GUIDE=0x92,
PB_EXEC_ONE=0x93,
PB_EXEC_ALL=0x94,
PB_EXEC_DPOF_SET=0x95,
PB_EXEC_DPOF_RESET=0x96,
PB_EXEC_DPOF_CANCEL=0x97,
PB_COMP_GPSTAG_COPY=0x98,
PB_COMP_ZMODE_ZOOM=0x99,
PB_COMP_ZMODE_MOVE=0x9a,
PB_COMP_LCDEVF_START=0x9b,
PB_COMP_EYESENSOR_START=0x9c,
PB_COMP_AVOUT_START=0x9d,
PB_COMP_AVOUT_STOP=0x9e,
SETUP_RESET_COMPLETE=0x9f,
SETUP_DATESET_COMPLETE=0xa0,
UPDATE_CANCEL=0xa1,
SETUP_INIT_COMPLETE=0xa2,
SETUP_DUST_REDUCTION_COMPLETE=0xa3,
REC_PIXEL_MAPPING_COMPLETE=0xa4,
REC_PIXEL_MAPPING_ACCEPT=0xa5,
REC_PIXEL_MAPPING_REJECT=0xa6,
SETUP_FORMAT_COMPLETE=0xa7,
PB_SEARCH_START=0xa8,
PB_SEARCH_END=0xa9,
PB_SEARCH_STILL=0xaa,
PB_COMP_SEARCH_ITEM_DEL=0xab,
IRDA_SEND_FAILURE=0xac,
IRDA_RECV_FAILURE=0xad,
IRDA_COMP_END=0xae,
PB_COMP_ONE_DEL_DPOFBOOK_CHECK=0xaf,
PB_COMP_ALL_DEL_DPOFBOOK_CHECK=0xb0,
PB_COMP_DD_DEL_DPOFBOOK_CHECK=0xb1,
PB_EXEC_DPOFBOOK_CHECK=0xb2,
MODECHG_PCSTANBY=0xb3,
PCLIVE_STOP_ACCEPT=0xb4,
PCLIVE_START_ACCEPT=0xb5,
PCLIVE_START_COMPLETE=0xb6,
PCLIVE_STOP_COMPLETE=0xb7,
PCCONNECT_SWITCHING_COMPLETE=0xb8,
CONT_SUB_BUSY=0xb9,
CONT_SUB_START_COMPLETE=0xba,
CONT_SUB_STOP_COMPLETE=0xbb,
CONT_SUB_END_COMPLETE=0xbc,
CONT_SELECT_NONE_OFF_COMPLETE=0xbd,
CONT_SELECT_NONE_ON_COMPLETE=0xbe,
CONT_ALL_COMPLETE=0xbf,
FULLPLAY_COMPLETE=0xc0,
PB_UPDATE_END=0xc1,
PB_UPDATE_END_TO_MENU=0xc2,
PB_UPDATE_ONE=0xc3,
BACK_TO_PHOTOBOOK_MAIN=0xc4,
BACK_TO_PHOTOBOOK_SELECT=0xc5,
PB_PHOTOBOOK_FILE_INIT_END=0xc6,
PB_ERR_PHOTOBOOK_FILE_INIT=0xc7,
PB_PHOTOBOOK_END=0xc8,
PB_PHOTOBOOK_DATE_SEARCH_END=0xc9,
PB_PHOTOBOOK_DELETE_END=0xca,
PB_PHOTOBOOK_SELECT_ALL=0xcb,
PB_PHOTOBOOK_SELECT_ALL_WARN=0xcc,
APP2_DONE=0xcd,
PB_COMP_RAW_DEVELOP_DEINIT=0xce,
PB_COMP_RAW_DEVELOP_MENU=0xcf,
PB_COMP_RAW_DEVELOP_CONVERT=0xd0,
PB_COMP_RAW_DEVELOP_CANCEL=0xd1,
RAWMENU_CTRL_COMPLETE=0xd2,
PB_MMICRO9CHG_COMPLETE=0xd3,
PB_RECVOICE_END=0xd4,
PB_PLAYVOICE_END=0xd5,
PB_WLAN_TARGET_ON=0xd6,
PB_WLAN_TARGET_NONE=0xd7,
PB_WLAN_TARGET_OFF=0xd8,
PB_WLAN_CHANGE_MODE_COMP=0xd9,
PB_WLAN_DISCONNECTION=0xda,
PB_WLAN_SUUPEND_COMP=0xdb,
PB_WLAN_RESUME_COMP=0xdc,
WLAN_READ_FAILURE=0xdd,
WLAN_SEND_COMP=0xde,
WLAN_SEND_FAILURE=0xdf,
WLAN_SEND_ABORT=0xe0,
WLAN_VIEWER_START_COMP=0xe1,
WLAN_VIEWER_END_COMP=0xe2,
WLAN_COMP_CONNECT=0xe3,
WLAN_COMP_END=0xe4,
WLAN_GET_GPS_END=0xe5,
WLAN_GET_GPS_COMP=0xe6,
WLAN_GET_GPS_FAILURE=0xe7,
WLAN_GET_GPS_ABORT=0xe8,
AP_SCAN_COMPLETE=0xe9,
PB_WLAN_PCSAVE_CONNECT_COMP=0xea,
PB_PCSAVE_COMP=0xeb,
WLAN_SSID_INPUT=0xec,
WLAN_EASY_SET_START=0xed,
WLAN_INSTAX_END=0xee,
WLAN_INSTAX_PRINT_END=0xef,
CUSTOM_MENU_END=0xf0,
AFC_RESET_COMPLETE=0xf1,
BATT_SEAMLESS=0xf2,
BATT_BLACKOUT=0xf3,
SYNC_DATETIME_COMPLETE=0xf4,
SYNC_DATETIME_ERROR=0xf5,
FOLDER_COMPLETE=0xf6,
UNAVAILABLE=0xf7,
E_VALUE=0xf8,
E_OTHER=0xf9,
SUBSTM_ACCEPT=0xfa,
SUBSTM_COMPLETE=0xfb,
UNKNOWN=-2,
COMPLETE=-1,
};
