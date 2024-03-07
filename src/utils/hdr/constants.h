#pragma once

#ifndef LAZARUS_CONSTANTS_H
#define LAZARUS_CONSTANTS_H

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

static int LAZARUS_LISTENER_KEYCODE;
static int LAZARUS_LISTENER_SCANCODE;

static int LAZARUS_LISTENER_MOUSECODE;
static double LAZARUS_LISTENER_MOUSEX;
static double LAZARUS_LISTENER_MOUSEY;

static double LAZARUS_LISTENER_SCROLLCODE;

static const int LAZARUS_MOUSE_NOCLICK = 999;

static const char *LAZARUS_FILE_NOT_FOUND = "The requested file can't be found.";
static const char *LAZARUS_FILESTREAM_CLOSED = "The filestream is closed.";

#endif
