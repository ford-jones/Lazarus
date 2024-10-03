#ifndef LAZARUS_CONSTANTS_H
#define LAZARUS_CONSTANTS_H

#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

/* Engine Status */

static int          LAZARUS_EXECUTION_STATUS            = 0;

/* User Settings */

static bool         LAZARUS_ENFORCE_IMAGE_SANITY        = false;
static bool         LAZARUS_DISABLE_CURSOR_VISIBILITY   = false;
static bool         LAZARUS_CULL_BACK_FACES             = true;
static bool         LAZARUS_DEPTH_TEST_FRAGS            = true;
static bool         LAZARUS_LAUNCH_IN_FULLSCREEN        = false;
static int          LAZARUS_MAX_IMAGE_WIDTH             = 0;
static int          LAZARUS_MAX_IMAGE_HEIGHT            = 0;

/* Events */

static int          LAZARUS_LISTENER_KEYCODE            = 0;
static int          LAZARUS_LISTENER_SCANCODE           = 0;
static int          LAZARUS_LISTENER_MOUSECODE          = 0;
static double       LAZARUS_LISTENER_MOUSEX             = 0;
static double       LAZARUS_LISTENER_MOUSEY             = 0;
static double       LAZARUS_LISTENER_SCROLLCODE         = 0;
static const int    LAZARUS_MOUSE_NOCLICK               = 999;

/* Entity placeholders */

static const char*  LAZARUS_MESH_NOOBJ                  = "Non-wavefront mesh.";
static const char*  LAZARUS_MESH_NOMTL                  = "Colourless mesh.";
static const char*  LAZARUS_MESH_NOTEX                  = "Textureless mesh.";
    
/* Status Codes */

static const int    LAZARUS_OK                          = 0;
static const int    LAZARUS_FILE_NOT_FOUND              = 101;
static const int    LAZARUS_FILE_UNREADABLE             = 102;
static const int    LAZARUS_FILESTREAM_CLOSED           = 103;
static const int    LAZARUS_IMAGE_LOAD_FAILURE          = 104;
static const int    LAZARUS_IMAGE_RESIZE_FAILURE        = 105;
static const int    LAZARUS_SHADER_ERROR                = 201;
static const int    LAZARUS_VSHADER_COMPILE_FAILURE     = 202;
static const int    LAZARUS_FSHADER_COMPILE_FAILURE     = 203;
static const int    LAZARUS_SHADER_LINKING_FAILURE      = 204;
static const int    LAZARUS_OPENGL_ERROR                = 301;
static const int    LAZARUS_NO_CONTEXT                  = 302;
static const int    LAZARUS_WINDOW_ERROR                = 303;
static const int    LAZARUS_GLFW_NOINIT                 = 304;
static const int    LAZARUS_WIN_EXCEEDS_MAX             = 305;
static const int    LAZARUS_AUDIO_ERROR                 = 401;

#endif