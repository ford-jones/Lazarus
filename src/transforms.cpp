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
//                ((        ...... ...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.      
/*  LAZARUS ENGINE */

#include "../include/transforms.h"

/* =================================================
	TODO: 
	Create scaling translation
==================================================== */

void Transform::translateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> &mesh, float x, float y, float z)
{
    mesh->modelviewMatrix = glm::translate(mesh->modelviewMatrix, glm::vec3(x, y, z));
    mesh->locationX += x;
    mesh->locationY += y;
    mesh->locationZ += z;

	return;
};

void Transform::rotateMeshAsset(shared_ptr<Mesh::TriangulatedMesh> &mesh, float x, float y, float z)
{	
    mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	mesh->modelviewMatrix = glm::rotate(mesh->modelviewMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	
    return;
};

void Transform::translateCameraAsset(shared_ptr<Camera::FixedCamera> &camera, float x, float y, float z)
{
	/* =========================================
		TODO:
		Handle camera roll
		Restore orbit / handle both camera cases
		Speed usage here is silly, make it a user input
		glm::lookAt() helper function
	============================================ */
	camera->locationX += x;
	camera->locationY += y;
	camera->locationZ += z;

	float speed = x + y + z;

	if(x != 0.0)
	{
		camera->cameraPosition += (glm::normalize(glm::cross(camera->direction, camera->upVector)) * speed);
	}

	if(z != 0.0)
	{
		camera->cameraPosition += (speed * camera->direction);
	}

	camera->viewMatrix = glm::lookAt(camera->cameraPosition, (camera->cameraPosition + camera->direction), camera->upVector);
	
	return;
};

void Transform::rotateCameraAsset(shared_ptr<Camera::FixedCamera> &camera, float x, float y, float z)
{	
	if(x >= 90.0f || x <= -90.0f)
	{
		globals.setExecutionState(LAZARUS_INVALID_RADIANS);
	};
	
	glm::vec3 temp;
	temp.x = cos(glm::radians(y)) * cos(glm::radians(x));
	temp.y = sin(glm::radians(-x));
	temp.z = sin(glm::radians(y)) * cos(glm::radians(x)); 

	camera->direction = temp;

	camera->viewMatrix = glm::lookAt(camera->cameraPosition, (camera->cameraPosition + camera->direction), camera->upVector);              //  Define the view-matrix through the camera properties	
	
	return;
};

void Transform::translateLightAsset(shared_ptr<Light::AmbientLight> &light, float x, float y, float z)
{
	light->lightPosition += vec3(x, y, z);
	light->locationX += x;
	light->locationY += y;
	light->locationZ += z;
	
	return;
};
