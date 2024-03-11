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
#include <string.h>

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

        int errorCode;
        const char** errorMessage;

        WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win);

		int loadConfig(GLuint shader = 0, bool enableCursor = true, bool cullFaces = true, bool testDepth = true, bool texTwoDimensions = true);
		int createCursor(int sizeX, int sizeY, int hotX, int hotY);
        int initialise();
        int handleBuffers();

        virtual ~WindowManager();
        
	private:
		int initialiseGLEW();
        int checkErrors();
        
        GLFWwindow *window;
        GLFWcursor *cursor;
        GLFWimage image;
};

#endif
