#ifndef LAZARUS_CONSTANTS_H
#define LAZARUS_CONSTANTS_H

#ifdef __APPLE__
    #define LAZARUS_RUNNING_ON_DARWIN true
#else
    #define LAZARUS_RUNNING_ON_DARWIN false
#endif

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

static int LAZARUS_LISTENER_KEYCODE = 0;
static int LAZARUS_LISTENER_SCANCODE = 0;

static int LAZARUS_LISTENER_MOUSECODE = 0;
static double LAZARUS_LISTENER_MOUSEX = 0;
static double LAZARUS_LISTENER_MOUSEY = 0;

static double LAZARUS_LISTENER_SCROLLCODE = 0;

static const int LAZARUS_MOUSE_NOCLICK = 999;

static const char *LAZARUS_FILE_NOT_FOUND = "The requested file can't be found.";
static const char *LAZARUS_FILESTREAM_CLOSED = "The filestream is closed.";

#endif