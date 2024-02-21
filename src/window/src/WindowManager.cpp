//              .,                                                                                                          .(*      ,*,                
//                ((.     (.    ,                                                                          */*  ,%##%%%%%%%%%%%%%%%#(*           .      
//         .//**/#%%%%%%%%%%%%%%#*   .,                                                             ,**   .(%%%%%%#(******,***,/#%%%%%%%%###(/,         
//             #%%%#*.#%/***,,..,*(%(.    ,,                                                     *     /#%##/*****,,,,,,,,,.,...,,#%,  .#%#.            
//    .,     *%&#/   %#**,,*..,....,.*#,     ..                                               *     ,%#%#/*,,*,*,,,,,.,.,,.,...,...((     /#(//*/**.    
//           (%#    *#*...,.,,..........*/      ,                                          .      *#%(#(**,,,,,,,,..,..,..,,........(.     *#(          
//           *#     *(......,.............(#      ,                                       .     ,((, ##,,,.....,.................. ./       **  .,.     
//            *     ./........ ...........*#*,                                          ,      ,(,  ./*,,,..,,.................  .. *                   
//                   /, ........    ... ../(  *.                                              ,*     /,...,,.,,.....   ............**                   
//                    *... .............  /    ,                                             *,      ,*,,............  ,....     ...                    
//                     *.   ..... .... ..*                                                  .*        *...................   .  ...                     
//               *       ... ......... ,.                                                   ,          ... ..........  ...     ..       ,               
//                ((        .,.,.. ...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.      
/*  LAZARUS ENGINE */

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/WindowManager.h"

int WindowManager::Initialise()
{
    if(!glfwInit())
    {
        std::cout << "ERROR::GLFW::NOT_FOUND" << std::endl;
        glfwTerminate();
        return -1;
    };

    this->window = glfwCreateWindow
    (
        this->frame.height, 
        this->frame.width, 
        this->frame.title, 
        this->frame.monitor, 
        this->frame.fullscreen
    );

    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);

    return GLFW_NO_ERROR;
};


WindowManager::WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win)
{
    this->frame.height = h;
    this->frame.width = w;
    this->frame.title = t;
    this->frame.monitor = m;
    this->frame.fullscreen = win;
};

WindowManager::~WindowManager() 
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    std::cout << "Destroying window memory" << std::endl;
};
