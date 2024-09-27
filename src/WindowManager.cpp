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

#include "../include/WindowManager.h"
/* =======================================
	TODO: 
	- Rename arguments
    - Enable fullscreen 
    - Handle resizing
	- Update docs
========================================== */
WindowManager::WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win)
{
	std::cout << GREEN_TEXT << "Constructing class 'WindowManager'." << RESET_TEXT << std::endl;
	this->errorCode = GLFW_NO_ERROR;
	this->errorMessage = NULL;
	
    this->frame.height = h;
    this->frame.width = w;
    this->frame.title = t;

    this->enableCursor = globals.getCursorHidden();
    this->cullFaces = globals.getBackFaceCulling();
    this->testDepth = globals.getDepthTest();
    /* ==================
        Optional
    ===================== */
    this->frame.monitor = m;
    this->frame.fullscreen = win;

    this->isOpen = false;

    this->cursor = NULL;
};

int WindowManager::loadConfig(GLuint shader)
{	
	if(enableCursor == true)
	{
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	};
	
	if(cullFaces == true)
	{
		glEnable            (GL_CULL_FACE);
        glCullFace          (GL_BACK);
	};
	
	if(testDepth == true)
	{
	    glEnable            (GL_DEPTH_TEST);
	};

    glClearColor        (0.0, 0.0, 0.0, 0.0);    // glfwDestroyWindow(this->window);

    /* ===============================================
        TODO:
        Allow color transparency / overlap 
        e.g.

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
    ================================================== */

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
        std::cout << "ERROR::WINDOW_MANAGER::GLFW_MISSING" << std::endl;

        globals.setExecutionState(LAZARUS_WINDOW_ERROR);
        
        glfwTerminate();
        return -1;
    };

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->checkErrors();

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

    /* ========================================================================== 
        Note that alot of the GL ecosystem uses C-style callbacks. The repercussion
        being that pointers such as "this" cannot be used because of the required
        function signature being a static constant. 

        The solution here is to set the glfw user pointer value to "this" (i.e. 
        this class) and then perform a get on the user pointer inside of the actual 
        callback, which; is declared inline as a non-capturing lambda function.
    ============================================================================= */
    glfwSetWindowUserPointer(this->window, this);

    glfwSetWindowCloseCallback(this->window, [](GLFWwindow *win){
        WindowManager *window = (WindowManager *) glfwGetWindowUserPointer(win);
        window->close();
    });

	this->initialiseGLEW();
    
    return GLFW_NO_ERROR;
};

int WindowManager::open()
{
    glfwSetWindowShouldClose(this->window, GLFW_FALSE);    // glfwDestroyWindow(this->window);
    this->isOpen = true;

    return GLFW_NO_ERROR;
}

int WindowManager::close()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    this->isOpen = false;

    return GLFW_NO_ERROR;
}

int WindowManager::handleBuffers()
{
	glfwSwapBuffers(this->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
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

        globals.setExecutionState(LAZARUS_WINDOW_ERROR);
        return errorCode;
    }
    else 
    {
    	return GLFW_NO_ERROR;
    }
};

int WindowManager::initialiseGLEW()
{
    glewExperimental = GL_TRUE;
    glewInit();

    return GLEW_NO_ERROR;
};

WindowManager::~WindowManager() 
{
    glfwDestroyWindow(this->window);

    if(this->cursor != NULL) 
    {
        glfwDestroyCursor(this->cursor);
    }

    glfwTerminate();

    std::cout << GREEN_TEXT << "Destroying 'WindowManager' class." << RESET_TEXT << std::endl;
};
