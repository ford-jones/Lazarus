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
//                ((        LAZARUS...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.      

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/transforms.h"

shared_ptr<Mesh::TriangulatedMesh> Transform::translateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> mesh, float x, float y, float z)
{
    mesh->modelviewMatrix = glm::translate(mesh->modelviewMatrix, glm::vec3(x, y, z));
    mesh->locationX += x;
    mesh->locationY += y;
    mesh->locationZ += z;

    return mesh;
};

shared_ptr<Mesh::TriangulatedMesh> Transform::rotateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> mesh, float x, float y, float z)
{	
    mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));                               //  manipulate the model-view matrix's x-axis rotation transform
    mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));                               //  manipulate the model-view matrix's y-axis rotation transform
	mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	
    return mesh;
};

shared_ptr<Camera::FixedCamera> Transform::translateCameraAsset(shared_ptr<Camera::FixedCamera> camera, float x, float y, float z)
{
	camera->projectionMatrix = glm::translate(camera->projectionMatrix, glm::vec3(x, y, z));
	camera->viewMatrix = glm::translate(camera->viewMatrix, glm::vec3(x, y, z));
	camera->locationX += x;
	camera->locationY += y;
	camera->locationZ += z;
	
	return camera;
};

shared_ptr<Camera::FixedCamera> Transform::rotateCameraAsset(shared_ptr<Camera::FixedCamera> camera, float x, float y, float z)
{
	camera->projectionMatrix = glm::rotate(camera->projectionMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	camera->projectionMatrix = glm::rotate(camera->projectionMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	camera->projectionMatrix = glm::rotate(camera->projectionMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	return camera;
};

