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

#include "../hdr/eventManager.h"


int EventManager::monitorEvents()
{
    glfwPollEvents();
    win = glfwGetCurrentContext();
	
	glfwSetKeyCallback(win, keydownCallback);
    this->updateKeyState();
};

void EventManager::updateKeyState()
{
    up      = glfwGetKey(win, GLFW_KEY_UP);
    down    = glfwGetKey(win, GLFW_KEY_DOWN);
    left    = glfwGetKey(win, GLFW_KEY_LEFT);
    right   = glfwGetKey(win, GLFW_KEY_RIGHT);

    if (up == GLFW_PRESS)
    {
        xangle += 0.0;
        yangle += 0.5;

        return;
    };

    if (down == GLFW_PRESS)
    {
        xangle += 0.0;
        yangle += -0.5;

        return;
    };

    if (left == GLFW_PRESS)
    {
        xangle += 0.5;
        yangle += 0.0;

        return;
    };

    if (right == GLFW_PRESS)
    {
        xangle += -0.5;
        yangle += 0.0;

        return;
    };

    xangle = 0.0;
    yangle = 0.0;
};

void EventManager::keydownCallback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS)
	{
		std::cout << "Key: " << key << std::endl;
	};	
};
