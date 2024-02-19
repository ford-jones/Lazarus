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
#include "../../../utils/hdr/fileReader.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

#ifndef LAZARUS_SHADER_H
#define LAZARUS_SHADER_H

class Shader 
{
    public:
        GLuint initialiseShader();
        virtual ~Shader();

    private: 
        FileReader *vertReader;                                                             //  Vertex GLSL file reader 
        FileReader *fragReader;                                                             //  Fragment GLSL file reader

        const char *vertShaderProgram;                                                      //  GLSL Vertex shader program read from stringstream
        const char *fragShaderProgram;                                                      //  GLSL Fragment shader program read from stringstream

        GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
        GLuint vertShader;                                                                  //  Stores the vertex shader
        GLuint fragShader;                                                                  //  Stores the fragment shader

        char infoLog[512];                                                                  //  Handler passed to OpenGL to store any logs
        int accepted;                                                                       //  Handler passed to OpenGL to store the status of an attempt to locate the shader
        
};

#endif