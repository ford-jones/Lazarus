#include "../hdr/WindowManager.h"

int WindowManager::Initialise()
{
    if(!glfwInit())
    {
        std::cout << "ERROR::GLFW::NOT_FOUND" << std::endl;
        glfwTerminate();
        return -1;
    };

    window = glfwCreateWindow
    (
        height, 
        width, 
        title, 
        monitor, 
        fullscreen
    );

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    // glClearColor(red, green, blue, alpha);
    glfwSetKeyCallback(window, KeydownHandler);

    return GLFW_NO_ERROR;
};

void WindowManager::KeydownHandler(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    if(action == (GLFW_PRESS || GLFW_REPEAT))
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            std::cout << "up" << std::endl;
            break;
        case GLFW_KEY_DOWN:
            std::cout << "down" << std::endl;
            break;
        case GLFW_KEY_RIGHT:
            std::cout << "right" << std::endl;
            break;
        case GLFW_KEY_LEFT:
            std::cout << "left" << std::endl;
            break;
        default:
            break;
        }
    }
}

WindowManager::WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win)
{
    height = h;
    width = w;
    title = t;
    monitor = m;
    fullscreen = win;
};

WindowManager::~WindowManager() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Destroying window memory" << std::endl;
};
