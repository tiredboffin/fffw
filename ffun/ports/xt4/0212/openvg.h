typedef enum {
    EGL_OPENGL_ES_API = 0x30A0,
    EGL_OPENVG_API    = 0x30A1,
    EGL_OPENGL_API    = 0x30A2
} EGLBindAPIEnum;

typedef enum {
    EGL_SUCCESS             = 0x3000,
    EGL_NOT_INITIALIZED     = 0x3001,
    EGL_BAD_ACCESS          = 0x3002,
    EGL_BAD_ALLOC           = 0x3003,
    EGL_BAD_ATTRIBUTE       = 0x3004,
    EGL_BAD_CONFIG          = 0x3005,
    EGL_BAD_CONTEXT         = 0x3006,
    EGL_BAD_CURRENT_SURFACE = 0x3007,
    EGL_BAD_DISPLAY         = 0x3008,
    EGL_BAD_MATCH           = 0x3009,
    EGL_BAD_NATIVE_PIXMAP   = 0x300A,
    EGL_BAD_NATIVE_WINDOW   = 0x300B,
    EGL_BAD_PARAMETER       = 0x300C,
    EGL_BAD_SURFACE         = 0x300D,
    EGL_CONTEXT_LOST        = 0x300E
} EGLError;

typedef enum {
    GL_ARRAY_BUFFER              = 0x8892,
    GL_ELEMENT_ARRAY_BUFFER      = 0x8893
} GLBufferTarget;

typedef enum {
    GL_ALPHA_TEST         = 0x0BC0,
    GL_AUTO_NORMAL        = 0x0D80,
    GL_BLEND              = 0x0BE2,
    GL_CLIP_PLANE0        = 0x3000,
    GL_CLIP_PLANE1        = 0x3001,
    GL_CLIP_PLANE2        = 0x3002,
    GL_CLIP_PLANE3        = 0x3003,
    GL_CLIP_PLANE4        = 0x3004,
    GL_CLIP_PLANE5        = 0x3005,
    GL_COLOR_LOGIC_OP     = 0x0BF2,
    GL_COLOR_MATERIAL     = 0x0B57,
    GL_CULL_FACE          = 0x0B44,
    GL_DEPTH_TEST         = 0x0B71,
    GL_DITHER             = 0x0BD0,
    GL_FOG                = 0x0B60,
    GL_INDEX_LOGIC_OP     = 0x0BF1,
    GL_LIGHT0             = 0x4000,
    GL_LIGHT1             = 0x4001,
    GL_LIGHT2             = 0x4002,
    GL_LIGHT3             = 0x4003,
    GL_LIGHT4             = 0x4004,
    GL_LIGHT5             = 0x4005,
    GL_LIGHT6             = 0x4006,
    GL_LIGHT7             = 0x4007,
    GL_LIGHTING           = 0x0B50,
    GL_LINE_SMOOTH        = 0x0B20,
    GL_LINE_STIPPLE       = 0x0B24,
    GL_MAP1_COLOR_4       = 0x0D90,
    GL_MAP1_INDEX         = 0x0D91,
    GL_MAP1_NORMAL        = 0x0D92,
    GL_MAP1_TEXTURE_COORD_1 = 0x0D93,
    GL_MAP1_TEXTURE_COORD_2 = 0x0D94,
    GL_MAP1_TEXTURE_COORD_3 = 0x0D95,
    GL_MAP1_TEXTURE_COORD_4 = 0x0D96,
    GL_MAP1_VERTEX_3      = 0x0D97,
    GL_MAP1_VERTEX_4      = 0x0D98,
    GL_MAP2_COLOR_4       = 0x0DB0,
    GL_MAP2_INDEX         = 0x0DB1,
    GL_MAP2_NORMAL        = 0x0DB2,
    GL_MAP2_TEXTURE_COORD_1 = 0x0DB3,
    GL_MAP2_TEXTURE_COORD_2 = 0x0DB4,
    GL_MAP2_TEXTURE_COORD_3 = 0x0DB5,
    GL_MAP2_TEXTURE_COORD_4 = 0x0DB6,
    GL_MAP2_VERTEX_3      = 0x0DB7,
    GL_MAP2_VERTEX_4      = 0x0DB8,
    GL_MULTISAMPLE        = 0x809D,
    GL_NORMALIZE          = 0x0BA1,
    GL_POINT_SMOOTH       = 0x0B10,
    GL_POINT_SPRITE       = 0x8861,
    GL_POLYGON_OFFSET_FILL  = 0x8037,
    GL_POLYGON_OFFSET_LINE  = 0x2A02,
    GL_POLYGON_OFFSET_POINT = 0x2A01,
    GL_POLYGON_SMOOTH     = 0x0B41,
    GL_POLYGON_STIPPLE    = 0x0B42,
    GL_RESCALE_NORMAL     = 0x803A,
    GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E,
    GL_SAMPLE_ALPHA_TO_ONE      = 0x809F,
    GL_SAMPLE_COVERAGE    = 0x80A0,
    GL_SCISSOR_TEST       = 0x0C11,
    GL_STENCIL_TEST       = 0x0B90,
    GL_TEXTURE_1D         = 0x0DE0,
    GL_TEXTURE_2D         = 0x0DE1,
    GL_TEXTURE_3D         = 0x806F,
    GL_TEXTURE_CUBE_MAP   = 0x8513,
    GL_TEXTURE_GEN_Q      = 0x0C63,
    GL_TEXTURE_GEN_R      = 0x0C62,
    GL_TEXTURE_GEN_S      = 0x0C60,
    GL_TEXTURE_GEN_T      = 0x0C61,
    GL_VERTEX_WEIGHT_ARRAY_EXT = 0x8840,
} GLCapability;

typedef enum {
    GL_VERTEX_ARRAY           = 0x8074,
    GL_NORMAL_ARRAY           = 0x8075,
    GL_COLOR_ARRAY            = 0x8076,
    GL_INDEX_ARRAY            = 0x8077,
    GL_TEXTURE_COORD_ARRAY    = 0x8078,
    GL_EDGE_FLAG_ARRAY        = 0x8079,

    /* ?? */
    GL_FOG_COORD_ARRAY        = 0x8457,
    GL_SECONDARY_COLOR_ARRAY  = 0x845E
    GL_MATRIX_INDEX_ARRAY_OES = 0x8844,  // OES_matrix_palette
    GL_WEIGHT_ARRAY_OES       = 0x86AD   // OES_matrix_palette
    GL_POINT_SIZE_ARRAY_OES   = 0x8B9C,  // OES_point_size_array
} GLClientState;
typedef enum {
    VG_NO_ERROR = 0,
    VG_BAD_HANDLE_ERROR = 0x1000,
    VG_ILLEGAL_ARGUMENT_ERROR = 0x1001,
    VG_OUT_OF_MEMORY_ERROR = 0x1002,
    VG_PATH_CAPABILITY_ERROR = 0x1003,
    VG_UNSUPPORTED_IMAGE_FORMAT_ERROR = 0x1004,
    VG_UNSUPPORTED_PATH_FORMAT_ERROR = 0x1005,
    VG_IMAGE_IN_USE_ERROR = 0x1006
} VGErrorCode;

typedef enum {
    /* Mode settings */
    VG_MATRIX_MODE                    = 0x1100,
    VG_FILL_RULE                      = 0x1101,
    VG_IMAGE_QUALITY                  = 0x1102,
    VG_RENDERING_QUALITY              = 0x1103,
    VG_BLEND_MODE                     = 0x1104,
    VG_IMAGE_MODE                     = 0x1105,

    /* Scissoring rectangles */
    VG_SCISSOR_RECTS                  = 0x1106,

    /* Color transformation */
    VG_COLOR_TRANSFORM                = 0x1170,
    VG_COLOR_TRANSFORM_VALUES         = 0x1171,

    /* Stroke parameters */
    VG_STROKE_LINE_WIDTH              = 0x1110,
    VG_STROKE_CAP_STYLE               = 0x1111,
    VG_STROKE_JOIN_STYLE              = 0x1112,
    VG_STROKE_MITER_LIMIT             = 0x1113,
    VG_STROKE_DASH_PATTERN            = 0x1114,
    VG_STROKE_DASH_PHASE              = 0x1115,
    VG_STROKE_DASH_PHASE_RESET        = 0x1116,

    /* Edge fill color for VG_TILE_FILL tiling mode */
    VG_TILE_FILL_COLOR                = 0x1120,

    /* Color for vgClear */
    VG_CLEAR_COLOR                    = 0x1121,

    /* Glyph origin */
    VG_GLYPH_ORIGIN                   = 0x1122,

    /* Enable/disable alpha masking and scissoring */
    VG_MASKING                        = 0x1130,
    VG_SCISSORING                     = 0x1131,

    /* Pixel layout information */
    VG_PIXEL_LAYOUT                   = 0x1140,
    VG_SCREEN_LAYOUT                  = 0x1141,

    /* Source format selection for image filters */
    VG_FILTER_FORMAT_LINEAR           = 0x1150,
    VG_FILTER_FORMAT_PREMULTIPLIED    = 0x1151,

    /* Destination write enable mask for image filters */
    VG_FILTER_CHANNEL_MASK            = 0x1152,

    /* Implementation limits (read-only) */
    VG_MAX_SCISSOR_RECTS              = 0x1160,
    VG_MAX_DASH_COUNT                 = 0x1161,
    VG_MAX_KERNEL_SIZE                = 0x1162,
    VG_MAX_SEPARABLE_KERNEL_SIZE      = 0x1163,
    VG_MAX_COLOR_RAMP_STOPS           = 0x1164,
    VG_MAX_IMAGE_WIDTH                = 0x1165,
    VG_MAX_IMAGE_HEIGHT               = 0x1166,
    VG_MAX_IMAGE_PIXELS               = 0x1167,
    VG_MAX_IMAGE_BYTES                = 0x1168,
    VG_MAX_FLOAT                      = 0x1169,
    VG_MAX_GAUSSIAN_STD_DEVIATION     = 0x116A

    VG_DMP_PARAM_0xC070 = 0xC070,
    VG_DMP_PARAM_0xC130 = 0xC130,
    VG_DMP_PARAM_0xC131 = 0xC131,
    VG_DMP_PARAM_0xC143 = 0xC143
} VGParamType;

typedef enum {
    VG_RENDERING_QUALITY_NONANTIALIASED = 0x1200,
    VG_RENDERING_QUALITY_FASTER         = 0x1201,
    VG_RENDERING_QUALITY_BETTER         = 0x1202
} VGRenderingQuality;
