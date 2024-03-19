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
        WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win);

		int loadConfig(GLuint shader = 0, bool enableCursor = true, bool cullFaces = true, bool testDepth = true);
		int createCursor(int sizeX, int sizeY, int hotX, int hotY, unsigned char *cursorImage);
        int initialise();
        int handleBuffers();

        virtual ~WindowManager();
        
	private:
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
        
        GLFWwindow *window;
        GLFWcursor *cursor;
        GLFWimage image;
		int initialiseGLEW();
        int checkErrors();
};
#endif
