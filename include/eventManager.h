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
#ifndef LAZARUS_GL_INCLUDES_H
    #include "gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
	#include "constants.h"
#endif

#include <iostream>
#include <string>

using std::string;

#ifndef LAZARUS_EVENT_MANAGER_H
#define LAZARUS_EVENT_MANAGER_H

class EventManager
{
    public:
    	//	TODO:
    	//	Create a constructor / destructor
    	
        void monitorEvents();

        string keyString;
        int keyCode;
		int osCode;

		int mouseCode;
		int mouseX;
		int mouseY;
		
		int scrollCode;
		
    private:
    	static void keydownCallback(GLFWwindow *win, int key, int scancode, int action, int mods);
    	static void mouseDownCallback(GLFWwindow *win, int button, int action, int mods);
    	static void mouseMoveCallback(GLFWwindow *win, double xpos, double ypos);
    	static void scrollCallback(GLFWwindow *win, double xoffset, double yoffset);
    	
        void updateKeyboardState();
        void updateMouseState();

        GLFWwindow *win;
};

#endif
