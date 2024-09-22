#ifndef LAZARUS_CONSTANTS_H
#define LAZARUS_CONSTANTS_H

#define GREEN_TEXT "\x1b[32m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

static int LAZARUS_LISTENER_KEYCODE = 0;
static int LAZARUS_LISTENER_SCANCODE = 0;

static int LAZARUS_LISTENER_MOUSECODE = 0;
static double LAZARUS_LISTENER_MOUSEX = 0;
static double LAZARUS_LISTENER_MOUSEY = 0;

static double LAZARUS_LISTENER_SCROLLCODE = 0;

static const int LAZARUS_MOUSE_NOCLICK = 999;

static const char *LAZARUS_MESH_NOOBJ = "Non-wavefront mesh.";
static const char *LAZARUS_MESH_NOMTL = "Colourless mesh.";
static const char *LAZARUS_MESH_NOTEX = "Textureless mesh.";

static const char *LAZARUS_FILE_NOT_FOUND = "The requested file cannot be found.";
static const char *LAZARUS_FILE_UNREADABLE = "The requested file cannot be read.";
static const char *LAZARUS_IMAGE_RESIZE_FAILURE = "Image resizing failure.";
static const char *LAZARUS_FILESTREAM_CLOSED = "The filestream is closed.";
static const char *LAZARUS_AUDIO_ERROR = "Lazarus recieved an error from FMOD audio backend.";

#endif