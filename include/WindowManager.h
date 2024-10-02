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

#ifndef LAZARUS_WINDOW_MANAGER_H
#define LAZARUS_WINDOW_MANAGER_H

class WindowManager
{
    public:
        WindowManager(int h, int w, const char *t, GLFWmonitor *m = NULL, GLFWwindow *win = NULL);

        int initialise();
		int loadConfig(GLuint shader);
        /* =======================================================================
            TODO:
            1. Fullscreen
            2. Resizing
        	3. Locate what is being clicked (see: glReadPixels())
        ========================================================================== */
        int open();
        int close();

		int createCursor(int sizeX, int sizeY, int hotX, int hotY, unsigned char *cursorImage);
        int handleBuffers();

        bool isOpen;

        virtual ~WindowManager();
        
	private:
		int initialiseGLEW();
        int checkErrors();

        //  Dont know why I made this private
        struct Window
        {
            int height, width;
            const char *title;
            GLFWmonitor *monitor;
            GLFWwindow *fullscreen;
        };

        Window frame;

        bool enableCursor;
        bool cullFaces;
        bool testDepth;

        int errorCode;
        const char** errorMessage;
        
        const GLFWvidmode *videoMode;
        GLFWwindow *window;
        GLFWcursor *cursor;
        GLFWimage image;

        GlobalsManager globals;
};

#endif
