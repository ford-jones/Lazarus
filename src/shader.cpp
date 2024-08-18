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

#include "../include/shader.h"

Shader::Shader()
{
	this->vertReader = nullptr;
	this->fragReader = nullptr;
	this->vertShaderProgram = NULL;
	this->fragShaderProgram = NULL;
	
	this->accepted = 0;
	
	this->vertShader = 0;
	this->fragShader = 0;
	this->shaderProgram = 0;	
};

GLuint Shader::initialiseShader()
{
    this->vertReader = std::make_unique<FileReader>();
    this->fragReader = std::make_unique<FileReader>();

    this->vertShaderProgram   =   vertReader->readFromText("src/shader.vert");                                                      //  Retrieve the vertex shader file contents through stringstream
    this->fragShaderProgram   =   fragReader->readFromText("src/shader.frag");                                                      //  Retrieve the fragment shader file contents through stringstream

    this->vertShader      =   glCreateShader(GL_VERTEX_SHADER);                                                               //   Create a new instance of a vertex shader program in openGL
    this->fragShader      =   glCreateShader(GL_FRAGMENT_SHADER);                                                             //   Create a new instance of a fragment shader program in openGL
    this->shaderProgram   =   glCreateProgram();                                                                              //   Instantiate a new shader program

    glShaderSource      (this->vertShader, 1, &this->vertShaderProgram, NULL);                                                      //   Link the shader.vert file contents to the newly created OpenGL vertex shader instance
    glCompileShader     (this->vertShader);                                                                                   //   Compile the shader
    glGetShaderiv(this->vertShader, GL_COMPILE_STATUS, &this->accepted);                                                            //   Check the compilation status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetShaderInfoLog(this->vertShader, 512, NULL, this->infoLog);                                                             //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << RESET_TEXT << infoLog << std::endl;
    };

    glShaderSource      (this->fragShader, 1, &this->fragShaderProgram, NULL);                                                      //   Link the shader.frag file contents to the newly created OpenGL fragment shader instance
    glCompileShader     (this->fragShader);                                                                                   //   Compile the shader
    glGetShaderiv(this->fragShader, GL_COMPILE_STATUS, &this->accepted);                                                            //   Check the compilation status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetShaderInfoLog(this->fragShader, 512, NULL, this->infoLog);                                                             //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << RESET_TEXT << this->infoLog << std::endl;
    };

    glAttachShader      (this->shaderProgram, this->vertShader);                                                                    //   Attatch the compiled vert shader to the shader program
    glAttachShader      (this->shaderProgram, this->fragShader);                                                                    //   Attatch the compiled frag shader to the shader program
    glLinkProgram       (this->shaderProgram);                                                                                //   Link the shader program to this OpenGL context
    glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &this->accepted);                                                           //   Check the link status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetProgramInfoLog(this->shaderProgram, 512, NULL, this->infoLog);                                                         //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << RESET_TEXT << infoLog << std::endl;
    }

    if(glIsProgram(this->shaderProgram) != GL_TRUE)                                                                           //   Check that the shader program now exists
    {
        std::cout << RED_TEXT << "ERROR::SHADER::PROGRAM::NOT_FOUND" << RESET_TEXT << std::endl;
    }

    return shaderProgram;
};

Shader::~Shader()
{
    glDeleteShader          (this->vertShader);
    glDeleteShader          (this->fragShader);
    glDeleteProgram(this->shaderProgram);
};
