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

#include <iostream>
#include <stdlib.h>
#include <memory>

using std::shared_ptr;
using glm::vec3;
using glm::mat4;

#ifndef LAZARUS_CAMERA_H
#define LAZARUS_CAMERA_H

class Camera
{
    public:
        Camera(GLuint shader);
        struct FixedCamera                                                                     //  Static Camera values represented in key-value pairs
        {
            int id;
			float locationX;
			float locationY;
			float locationZ;
			
            vec3 cameraPosition;                                                                //  The (x,y,z) location of the camera                                                                  
            vec3 targetPosition;                                                                //  The (x,y,z) location of the cameras target
            vec3 direction;                                                                     //  where the camera is looking                             
            vec3 upVector;                                                                      //  The tilt / rotation of the camera                                                                  

            float aspectRatio;                                                                  //  The viewport aspect ratio

            GLuint viewLocation;                                                                //  The location / index of the view matrix inside the vert shader program
            GLuint projectionLocation;                                                          //  The location / index of the projection matrix inside the vert shader program

            mat4 viewMatrix;                                                                    //  A view matrix matrice passed into the shader program as a uniform
            mat4 projectionMatrix;                                                              //  A projection matrix matrice passed into the shader program as a uniform
        };

		//	TODO:
		//	Make creation function for an orthographic camera (projection matrix constructed with glm::ortho rather than glm::perspective)
		//	Rename the existing creation function to createPerspectiveCamera()
		
        shared_ptr<FixedCamera> createFixedCamera(int arX, int arY, double pX, double pY, double pZ, double tX, double tY, double tZ, double uX, double uY, double uZ);
        shared_ptr<FixedCamera> loadCamera(shared_ptr<FixedCamera> cameraData);

    private:
        GLuint shader;
        shared_ptr<FixedCamera> fixedCamera;
};

#endif
