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
    #include "lz_gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
    #include "lz_constants.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <memory>

#include "lz_globals_manager.h"

using std::shared_ptr;
using glm::vec3;
using glm::mat4;

#ifndef LAZARUS_CAMERA_H
#define LAZARUS_CAMERA_H

class CameraManager
{
    public:
        CameraManager(GLuint shader);
        struct Camera                                                                     //  Static Camera values represented in key-value pairs
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

            int usesPerspective;
        };
		
        Camera createPerspectiveCam(double pX, double pY, double pZ, double tX, double tY, double tZ, int arX = 0, int arY = 0);
        Camera createOrthoCam(int arX, int arY);
        void loadCamera(Camera &cameraData);

        virtual ~CameraManager();

    private:
        GlobalsManager globals;
        int monitorX;
        int monitorY;

        GLuint shader;
        Camera camera;
};

#endif
