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

#include "../include/lz_transforms.h"

/* =================================================
	TODO: 
	Create scaling translation
==================================================== */
Transform::Transform()
{
	this->up = 0.0f;
	this->localCoordinates = glm::vec3(0.0, 0.0, 0.0);
	this->worldCoordinates = glm::vec4(localCoordinates, 0.0);

	this->temp = vec3(0.0, 0.0, 0.0);
};

void Transform::translateMeshAsset(MeshManager::Mesh &mesh, float x, float y, float z)
{
	this->localCoordinates = glm::vec3(x, y, z);
    mesh.modelviewMatrix = glm::translate(mesh.modelviewMatrix, this->localCoordinates);

	/* ===========================================================================
		Find worldspace coordinates by multiplying object-space coordinates by the 
		entity's modelview matrix.

		See: https://learnopengl.com/img/getting-started/coordinate_systems.png
	=============================================================================== */
	
	this->worldCoordinates = mesh.modelviewMatrix * glm::vec4(this->localCoordinates, 1.0);

    mesh.locationX = this->worldCoordinates.x;
    mesh.locationY = this->worldCoordinates.y;
    mesh.locationZ = this->worldCoordinates.z;

	return;
};

void Transform::rotateMeshAsset(MeshManager::Mesh &mesh, float x, float y, float z)
{	
    mesh.modelviewMatrix = glm::rotate(mesh.modelviewMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    mesh.modelviewMatrix = glm::rotate(mesh.modelviewMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	mesh.modelviewMatrix = glm::rotate(mesh.modelviewMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	
    return;
};

void Transform::translateCameraAsset(CameraManager::Camera &camera, float x, float y, float z, float velocity)
{
	/* =========================================
		TODO:
		Handle camera roll
		Restore orbit / handle both camera cases
		Speed usage here is silly, make it a user input
		glm::lookAt() helper function
	============================================ */
	float speed = 0;

	if(x != 0.0)
	{
		if(x < 0)
		{
			speed = velocity - (velocity * 2);		
		}
		else
		{
			speed = velocity;
		};

		camera.position += (glm::normalize(glm::cross(camera.direction, camera.upVector)) * speed);
	}

	if(z != 0.0)
	{
		if(z < 0)
		{
			speed = velocity - (velocity * 2);		
		}
		else
		{
			speed = velocity;
		};

		camera.position += (speed * camera.direction);
	}

	camera.viewMatrix = glm::lookAt(camera.position, (camera.position + camera.direction), camera.upVector);
	
	return;
};

void Transform::rotateCameraAsset(CameraManager::Camera &camera, float x, float y, float z)
{	
	temp = vec3(0.0, 0.0, 0.0);

	if((x > 360.0f) || (x < -360.0f))
	{
		globals.setExecutionState(LAZARUS_INVALID_RADIANS);
	}
	else
	{
		this->up = this->determineUpVector(x);
		camera.upVector = glm::vec3(0.0f, this->up, 0.0f);

		temp.x = cos(glm::radians(y)) * cos(glm::radians(x));
		temp.y = sin(glm::radians(-x));
		temp.z = sin(glm::radians(y)) * cos(glm::radians(x)); 

		camera.direction = temp;

		camera.viewMatrix = glm::lookAt(camera.position, (camera.position + camera.direction), camera.upVector);              //  Define the view-matrix through the camera properties	
	}
	
	return;
};

void Transform::translateLightAsset(LightManager::Light &light, float x, float y, float z)
{
	light.lightPosition += vec3(x, y, z);
	light.locationX += x;
	light.locationY += y;
	light.locationZ += z;
	
	return;
};

float Transform::determineUpVector(float rotation)
{
	if((rotation >= 90.0f && rotation <= 270.0f) || (rotation <= -90.0f && rotation >= -270.0f))
	{
		return -1.0f;
	}
	else
	{
		return 1.0f;
	};
};