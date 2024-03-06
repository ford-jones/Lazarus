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

#include <iostream>
#include <string>
#include "../../utils/hdr/constants.h"

using std::string;

#ifndef LAZARUS_EVENT_MANAGER_H
#define LAZARUS_EVENT_MANAGER_H

class EventManager
{
    public:
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
