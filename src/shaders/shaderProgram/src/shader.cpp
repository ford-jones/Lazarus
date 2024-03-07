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
#ifndef LAZARUS_CONSTANTS_H
	#include "../../../utils/hdr/constants.h"
#endif

#ifndef __GLEW_H__
    #include "../../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/shader.h"

GLuint Shader::initialiseShader()
{
    vertReader = std::make_unique<FileReader>();
    fragReader = std::make_unique<FileReader>();

    vertShaderProgram   =   vertReader->readShader("shader.vert");                                                      //  Retrieve the vertex shader file contents through stringstream
    fragShaderProgram   =   fragReader->readShader("shader.frag");                                                      //  Retrieve the fragment shader file contents through stringstream

    vertShader      =   glCreateShader(GL_VERTEX_SHADER);                                                               //   Create a new instance of a vertex shader program in openGL
    fragShader      =   glCreateShader(GL_FRAGMENT_SHADER);                                                             //   Create a new instance of a fragment shader program in openGL
    shaderProgram   =   glCreateProgram();                                                                              //   Instantiate a new shader program

    glShaderSource      (vertShader, 1, &vertShaderProgram, NULL);                                                      //   Link the shader.vert file contents to the newly created OpenGL vertex shader instance
    glCompileShader     (vertShader);                                                                                   //   Compile the shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &accepted);                                                            //   Check the compilation status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);                                                             //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << RESET_TEXT << infoLog << std::endl;
    };

    glShaderSource      (fragShader, 1, &fragShaderProgram, NULL);                                                      //   Link the shader.frag file contents to the newly created OpenGL fragment shader instance
    glCompileShader     (fragShader);                                                                                   //   Compile the shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &accepted);                                                            //   Check the compilation status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);                                                             //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << RESET_TEXT << infoLog << std::endl;
    };

    glAttachShader      (shaderProgram, vertShader);                                                                    //   Attatch the compiled vert shader to the shader program
    glAttachShader      (shaderProgram, fragShader);                                                                    //   Attatch the compiled frag shader to the shader program
    glLinkProgram       (shaderProgram);                                                                                //   Link the shader program to this OpenGL context
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &accepted);                                                           //   Check the link status
    if(!accepted)                                                                                                       //   If it failed
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);                                                         //   Retrieve the OpenGL shader logs if there are any and print them to the console
        std::cout << RED_TEXT << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << RESET_TEXT << infoLog << std::endl;
    }

    if(glIsProgram(shaderProgram) != GL_TRUE)                                                                           //   Check that the shader program now exists
    {
        std::cout << RED_TEXT << "ERROR::SHADER::PROGRAM::NOT_FOUND" << RESET_TEXT << std::endl;
    }

    return shaderProgram;
};

Shader::~Shader()
{
    glDeleteShader          (vertShader);
    glDeleteShader          (fragShader);
    glDeleteProgram(shaderProgram);
};
