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
#include <stdlib.h>

using glm::vec3;
using glm::mat4;

#ifndef LAZARUS_CAMERA_H
#define LAZARUS_CAMERA_H

class Camera
{
    public:
        struct StaticCamera                                                                     //  Static Camera values represented in key-value pairs
        {
            int id;
            vec3 cameraPosition;                                                                //  The (x,y,z) location of the camera                                                                  
            vec3 targetPosition;                                                                //  The (x,y,z) location of the cameras target, where the camera is looking                             
            vec3 upVector;                                                                      //  The tilt / rotation of the camera                                                                  

            float aspectRatio;                                                                  //  The viewport aspect ratio

            GLuint viewLocation;                                                                //  The location / index of the view matrix inside the vert shader program
            GLuint projectionLocation;                                                          //  The location / index of the projection matrix inside the vert shader program

            mat4 viewMatrix;                                                                    //  A view matrix matrice passed into the shader program as a uniform
            mat4 projectionMatrix;                                                              //  A projection matrix matrice passed into the shader program as a uniform
        };

        StaticCamera createStaticCamera(GLuint shader, int arX, int arY, double pX, double pY, double pZ, double tX, double tY, double tZ, double uX, double uY, double uZ);
        void initialiseCamera(StaticCamera cameraData);

    private:
        StaticCamera staticCamera;
};

#endif