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

//	TODO: 
//	Make monitor and window optional
//	Rename arguments
//	Update docs

WindowManager::WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win)
{
	this->errorCode = GLFW_NO_ERROR;
	this->errorMessage = NULL;
	
    this->frame.height = h;
    this->frame.width = w;
    this->frame.title = t;
    this->frame.monitor = m;
    this->frame.fullscreen = win;
};

int WindowManager::loadConfig(GLuint shader, bool enableCursor, bool cullFaces, bool testDepth, bool texTwoDimensions)
{	
	if(enableCursor == false)
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	};
	
	if(cullFaces == true)
	{
		glEnable            (GL_CULL_FACE);                                                                                 //  Disable rendering of faces oposite to the viewport
	};
	
	if(testDepth == true)
	{
	    glEnable            (GL_DEPTH_TEST);                                                                                //  Run a depth test on each fragment, render frags in order of perspective rather than order drawn.
	};
	
	if(texTwoDimensions == true)
	{
	    glEnable            (GL_TEXTURE_2D);                                                                                //  Enable 2 dimensional texture use in this context
	};

    glClearColor        (0.0, 0.0, 0.0, 1.0);                                                                           //  Set the background colour of the scene to black
    
	glUseProgram(shader);
	
	this->checkErrors();
	
	return GLFW_NO_ERROR;
};

int WindowManager::createCursor(int sizeX, int sizeY, int hotX, int hotY, unsigned char *cursorImage)
{		
	this->image.width = sizeX;
	this->image.height = sizeY;
	this->image.pixels = cursorImage;
	
	this->cursor = glfwCreateCursor(&this->image, hotX, hotY);
	glfwSetCursor(this->window, this->cursor);
	
	this->checkErrors();
	
	return GLFW_NO_ERROR;
};

int WindowManager::initialise()
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

	this->initialiseGLEW();
	
    this->checkErrors();
    
    return GLFW_NO_ERROR;
};

int WindowManager::handleBuffers()
{
	glfwSwapBuffers(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers
        
    this->checkErrors();

	return GLFW_NO_ERROR;
};

int WindowManager::checkErrors()
{
    errorCode = glfwGetError(errorMessage); 
    if(errorCode != GLFW_NO_ERROR)
    {
        std::cout << "ERROR::GLFW::WINDOW" << std::endl;
        std::cout << "GL_MESSAGE: " << errorMessage << std::endl;

        return errorCode;
    }
    else 
    {
    	return GLFW_NO_ERROR;
    }
};

int WindowManager::initialiseGLEW()
{
    glewExperimental = GL_TRUE;                                                                                         //  Enable GLEW's experimental features
    glewInit();                                                                                                         //  Initialise GLEW graphics library
    
    return GLEW_NO_ERROR;
};

WindowManager::~WindowManager() 
{
    glfwDestroyWindow(this->window);
    glfwDestroyCursor(this->cursor);
    glfwTerminate();

    std::cout << "Destroying window memory" << std::endl;
};
