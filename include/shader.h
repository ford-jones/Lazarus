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

// #ifndef LAZARUS_GLOBALS_MANAGER_H
    #include "globalsManager.h"
// #endif

#include <iostream>
#include <memory>

#include "fileReader.h"

using std::unique_ptr;

#ifndef LAZARUS_SHADER_H
#define LAZARUS_SHADER_H

class Shader 
{
    public:
    	Shader();
        GLuint initialiseShader();
        virtual ~Shader();

    private: 
        unique_ptr<FileReader> vertReader;                                                             //  Vertex GLSL file reader 
        unique_ptr<FileReader> fragReader;                                                             //  Fragment GLSL file reader

        const char *vertShaderProgram;                                                      //  GLSL Vertex shader program read from stringstream
        const char *fragShaderProgram;                                                      //  GLSL Fragment shader program read from stringstream

        GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
        GLuint vertShader;                                                                  //  Stores the vertex shader
        GLuint fragShader;                                                                  //  Stores the fragment shader

        char infoLog[512];                                                                  //  Handler passed to OpenGL to store any logs
        int accepted;                                                                       //  Handler passed to OpenGL to store the status of an attempt to locate the shader

        // GlobalsManager globals;
        
};

#endif
