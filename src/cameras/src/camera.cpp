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

#include "../hdr/camera.h"

Camera::StaticCamera Camera::createStaticCamera(GLuint shader, int arX, int arY, double pX, double pY, double pZ, double tX, double tY, double tZ, double uX, double uY, double uZ)
{
    srand(time((0)));

    staticCamera.id                   =   1 + (rand() % 2147483647);
    staticCamera.aspectRatio          =   static_cast<float>(arX) / arY;                                                                             //  Cast the screens aspect ratio as a float

    staticCamera.cameraPosition       =   vec3(pX, pY, pZ);                                                                                          //  Define the camera's position
    staticCamera.targetPosition       =   vec3(tX, tY, tZ);                                                                                          //  Define the camera's target location
    staticCamera.upVector             =   vec3(uX, uY, uZ);                                                                                          //  Define the tilt / rotation of the camera

    staticCamera.viewMatrix           =   glm::lookAt(staticCamera.cameraPosition, staticCamera.targetPosition, staticCamera.upVector);              //  Define the view-matrix through the camera properties
    staticCamera.projectionMatrix     =   glm::perspective(glm::radians(45.0f), staticCamera.aspectRatio, 0.1f, 100.0f);                             //  Define the projection matrix, responsible for depth and perspective

    staticCamera.viewLocation         =   glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    staticCamera.projectionLocation   =   glGetUniformLocation(shader, "projectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 


    return staticCamera;                                                                                                                             //  Return the newly created camera struct
};

void Camera::initialiseCamera(StaticCamera cameraData)
{
    glUniformMatrix4fv     (cameraData.viewLocation, 1, GL_FALSE, &cameraData.viewMatrix[0][0]);                                                      //  Pass view-uniform data into the shader program
    glUniformMatrix4fv     (cameraData.projectionLocation, 1, GL_FALSE, &cameraData.projectionMatrix[0][0]);                                          //  Pass projection-uniform data into the shader program
};