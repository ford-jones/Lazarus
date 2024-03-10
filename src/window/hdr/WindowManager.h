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

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

class WindowManager
{
    public:
        struct Window
        {
            int height, width;
            const char *title;
            GLFWmonitor *monitor;
            GLFWwindow *fullscreen;
        };

        Window frame;
        GLFWwindow *window;

        int errorCode;
        const char** errorMessage;

		//	TODO:
		//	Make a custom cursor creation function
		//	See https://www.glfw.org/docs/3.3/input_guide.html#cursor_custom
		//	also https://www.glfw.org/docs/3.3/group__input.html#ga556f604f73af156c0db0e97c081373c3
		
        WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win);

		int loadConfig(GLuint shader = 0, bool enableCursor = true, bool cullFaces = true, bool testDepth = true, bool texTwoDimensions = true);
        int initialise();
        int handleBuffers();

        virtual ~WindowManager();
        
	private:
		int initialiseGLEW();
        int checkErrors();
};

#endif
