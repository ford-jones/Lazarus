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


void EventManager::monitorEvents()
{
    glfwPollEvents();
    win = glfwGetCurrentContext();
	
	glfwSetKeyCallback(win, keydownCallback);
    this->updateKeyState();
};

int EventManager::updateKeyState()
{
	//	TODO: 
	//	Discern which key is being pressed using glfwGetKeyName()
	this->keyCode = LAZARUS_LISTENER_KEY;
	
	return this->keyCode;
};

void EventManager::keydownCallback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
	//if(action == GLFW_PRESS)
	//{
		//LAZARUS_LISTENER_KEY = key;
		//LAZARUS_LISTENER_SCANCODE = scancode;
	//}
	//else if(action == GLFW)
	
	switch(action)
	{
		case GLFW_PRESS:
			LAZARUS_LISTENER_KEY = key;
			LAZARUS_LISTENER_SCANCODE = scancode;
			break;
		case GLFW_RELEASE:
			LAZARUS_LISTENER_KEY = 0;
			LAZARUS_LISTENER_SCANCODE = 0;
			break;
		default:
			break;
	}
};
