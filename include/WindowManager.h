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

#ifndef LAZARUS_GLOBALS_MANAGER_H
    #include "globalsManager.h"
#endif

#include <iostream>
#include <string.h>

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

class WindowManager
{
    public:
        WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win);


		    int loadConfig(GLuint shader = 0, bool enableCursor = true, bool cullFaces = true, bool testDepth = true);
        //  TODO:
        //  Create a class for the cursor
        //	Locate what is being clicked
        //	Call glReadPixels() to retrieve all of the rasterised pixels loaded onto the cpu
		//	I imagine these can then be iterated through and checked for matches against mouseX & mouseY

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

        GlobalsManager globals;
};
#endif
