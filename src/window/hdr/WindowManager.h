#include <iostream>
#include "GL/gl.h"
#include <GLFW/glfw3.h>

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

class WindowManager
{
    public:
        int height, width;
        const char *title;
        GLFWmonitor *monitor;
        GLFWwindow *fullscreen, *window;

        GLclampf red, green, blue, alpha;

        WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win);
        int Initialise();
        static void KeydownHandler(GLFWwindow *win, int key, int scancode, int action, int mods);

        virtual ~WindowManager();

    private:
        int errorCode;
        const char** errorMessage;
};

#endif