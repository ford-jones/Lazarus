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

#include "../../mesh/hdr/mesh.h"
#include "../../transforms/hdr/transforms.h"
#include "../../shaders/shaderProgram/hdr/shader.h"
#include "../../lights/hdr/light.h"
#include "../../cameras/hdr/camera.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

class OpenGLContext
{
public:
    OpenGLContext();
    void Render(float xangle, float yangle);
    virtual ~OpenGLContext();

private:
    GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL

    // int errorCode;

    Shader *shader;
    Light *lightBuilder;
    Camera *cameraBuilder;
    Mesh *cubeBuilder;
    Mesh *houseBuilder;
    Transform *transformer;

    Light::AmbientLight light;
    Camera::StaticCamera camera;
    Mesh::TriangulatedMesh cube;
    Mesh::TriangulatedMesh house;
};

#endif