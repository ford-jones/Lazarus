#ifndef LAZARUS_CONSTANTS_H
#define LAZARUS_CONSTANTS_H

#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

static int          LAZARUS_EXECUTION_STATUS        = LAZARUS_NO_INIT;
static bool         LAZARUS_ENFORCE_IMAGE_SANITY    = false;
static int          LAZARUS_MAX_IMAGE_WIDTH         = 0;
static int          LAZARUS_MAX_IMAGE_HEIGHT        = 0;

static int          LAZARUS_LISTENER_KEYCODE        = 0;
static int          LAZARUS_LISTENER_SCANCODE       = 0;

static int          LAZARUS_LISTENER_MOUSECODE      = 0;
static double       LAZARUS_LISTENER_MOUSEX         = 0;
static double       LAZARUS_LISTENER_MOUSEY         = 0;

static double       LAZARUS_LISTENER_SCROLLCODE     = 0;

static const int    LAZARUS_MOUSE_NOCLICK           = 999;

static const char*  LAZARUS_MESH_NOOBJ               = "Non-wavefront mesh.";
static const char*  LAZARUS_MESH_NOMTL               = "Colourless mesh.";
static const char*  LAZARUS_MESH_NOTEX               = "Textureless mesh.";
    
static const int    LAZARUS_NO_INIT                  = -1;
static const int    LAZARUS_OK                       = 0;
static const int    LAZARUS_FILE_NOT_FOUND           = 1;
static const int    LAZARUS_FILE_UNREADABLE          = 2;
static const int    LAZARUS_IMAGE_RESIZE_FAILURE     = 3;
static const int    LAZARUS_FILESTREAM_CLOSED        = 4;
static const int    LAZARUS_AUDIO_ERROR              = 5;


#endif