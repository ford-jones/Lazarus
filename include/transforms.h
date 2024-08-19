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

#include <memory>

#include "mesh.h"
#include "camera.h"
#include "light.h"

using glm::vec3;
using std::shared_ptr;

#ifndef LAZARUS_TRANSFORMS_H
#define LAZARUS_TRANSFORMS_H

//	TODO:
//	Create scale transformations

class Transform
{
	
    public:
		shared_ptr<Mesh::TriangulatedMesh> translateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> mesh, float x, float y, float z);
        shared_ptr<Mesh::TriangulatedMesh> rotateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> mesh, float x, float y, float z);
        
		shared_ptr<Camera::FixedCamera> translateCameraAsset(shared_ptr<Camera::FixedCamera> camera, float x, float y, float z);
		shared_ptr<Camera::FixedCamera> rotateCameraAsset(shared_ptr<Camera::FixedCamera> camera, float x, float y, float z);
		
		shared_ptr<Light::AmbientLight> translateLightAsset(shared_ptr<Light::AmbientLight> light, float x, float y, float z);
};

#endif
