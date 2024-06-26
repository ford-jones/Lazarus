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

#ifndef LAZARUS_GL_INCLUDES_H
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
	camera->viewMatrix = glm::translate(camera->viewMatrix, glm::vec3(x, y, z));
	camera->locationX += x;
	camera->locationY += y;
	camera->locationZ += z;
	
	return camera;
};

shared_ptr<Camera::FixedCamera> Transform::rotateCameraAsset(shared_ptr<Camera::FixedCamera> camera, float x, float y, float z)
{
	//	TODO:
	//	Rotation in this current manner changes the orientation / location of the camera, as if it were "oribiting" a point.
	//	These rotations should instead be changing the yaw(x) / pitch(y) / roll(z) of the camera, as if it were "turning" or "spinning"
	//	Start the program and apply rotation + translation transforms to a mesh asset to visualise the desired behaviour 
	
	camera->viewMatrix = glm::rotate(camera->viewMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	camera->viewMatrix = glm::rotate(camera->viewMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	camera->viewMatrix = glm::rotate(camera->viewMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	
	return camera;
};

shared_ptr<Light::AmbientLight> Transform::translateLightAsset(shared_ptr<Light::AmbientLight> light, float x, float y, float z)
{
	light->lightPosition += vec3(x, y, z);
	light->locationX += x;
	light->locationY += y;
	light->locationZ += z;
	
	return light;
};
