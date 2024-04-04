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
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/camera.h"

//	TODO: 
//	Make this class's workflow similar to the of the Mesh class
//	i.e. create an initialise function

Camera::Camera(GLuint shader)
{
    this->shader = shader;
}

shared_ptr<Camera::FixedCamera> Camera::createFixedCamera(int arX, int arY, double pX, double pY, double pZ, double tX, double tY, double tZ, double uX, double uY, double uZ)
{
	fixedCamera = std::make_shared<FixedCamera>();
    srand(time((0)));

    fixedCamera->id                   =   1 + (rand() % 2147483647);
    fixedCamera->aspectRatio          =   static_cast<float>(arX) / arY;                                                                             //  Cast the screens aspect ratio as a float
    
    fixedCamera->locationX			  =	  pX;
    fixedCamera->locationY			  =	  pY;
    fixedCamera->locationZ            =   pZ;

    fixedCamera->cameraPosition       =   vec3(fixedCamera->locationX, fixedCamera->locationY, fixedCamera->locationZ);                                                                                          //  Define the camera's position
    fixedCamera->targetPosition		  =	  vec3(tX, tY, tZ);
    fixedCamera->upVector             =   vec3(uX, uY, uZ);                                                                                          //  Define the tilt / rotation of the camera

    
    fixedCamera->viewMatrix           =   glm::lookAt(fixedCamera->cameraPosition, fixedCamera->targetPosition, fixedCamera->upVector);              //  Define the view-matrix through the camera properties
    fixedCamera->projectionMatrix     =   glm::perspective(glm::radians(45.0f), fixedCamera->aspectRatio, 0.1f, 100.0f);                             //  Define the projection matrix, responsible for depth and perspective

    fixedCamera->viewLocation         =   glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    fixedCamera->projectionLocation   =   glGetUniformLocation(shader, "projectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 


    return fixedCamera;                                                                                                                             //  Return the newly created camera struct
};

shared_ptr<Camera::FixedCamera> Camera::loadCamera(shared_ptr<Camera::FixedCamera> cameraData)
{
	this->fixedCamera = std::move(cameraData);
    glUniformMatrix4fv     (fixedCamera->viewLocation, 1, GL_FALSE, &fixedCamera->viewMatrix[0][0]);                                                      //  Pass view-uniform data into the shader program
    glUniformMatrix4fv     (fixedCamera->projectionLocation, 1, GL_FALSE, &fixedCamera->projectionMatrix[0][0]);                                          //  Pass projection-uniform data into the shader program
    
    return fixedCamera;
};
