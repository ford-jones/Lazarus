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

#include "../include/lz_camera.h"

CameraManager::CameraManager(GLuint shader)
{
    std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
    this->shader = shader;

    this->monitorX = globals.getDisplayWidth();
    this->monitorY = globals.getDisplayHeight();
}

CameraManager::Camera CameraManager::createPerspectiveCam(double pX, double pY, double pZ, double tX, double tY, double tZ, int arX, int arY)
{
    srand(time((0)));
    camera.id                   = 1 + (rand() % 2147483647);

    if((arX + arY) > 0)
    {
        camera.aspectRatio      = static_cast<float>(arX) / static_cast<float>(arY);                                                                             //  Cast the screens aspect ratio as a float
    }
    else
    {
        camera.aspectRatio      = static_cast<float>(monitorX) / static_cast<float>(monitorY);                                                                             //  Cast the screens aspect ratio as a float
    };
    
    camera.locationX			= pX;
    camera.locationY			= pY;
    camera.locationZ            = pZ;

    camera.cameraPosition       = vec3(camera.locationX, camera.locationY, camera.locationZ);                                                                                          //  Define the camera's position
    camera.targetPosition		= vec3(tX, tY, tZ);
    camera.direction            = glm::normalize(camera.cameraPosition - camera.targetPosition);
    camera.upVector             = vec3(0.0, 1.0, 0.0);                                                                                          //  Define the tilt / rotation of the camera
    
    camera.viewMatrix           = glm::lookAt(camera.cameraPosition, (camera.cameraPosition + camera.direction), camera.upVector);              //  Define the view-matrix through the camera properties
    camera.projectionMatrix     = glm::perspective(glm::radians(45.0f), camera.aspectRatio, 0.1f, 100.0f);                             //  Define the projection matrix, responsible for depth and perspective

    camera.viewLocation         = glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    camera.projectionLocation   = glGetUniformLocation(shader, "perspectiveProjectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 

    camera.usesPerspective      = 1;

    return camera;                                                                                                                             //  Return the newly created camera struct
};

CameraManager::Camera CameraManager::createOrthoCam(int arX, int arY)
{
    srand(time((0)));
    camera.id                   = 1 + (rand() % 2147483647);

    if((arX + arY) > 0)
    {
        camera.aspectRatio      = static_cast<float>(arX) / static_cast<float>(arY);                                                                             //  Cast the screens aspect ratio as a float
    }
    else
    {
        camera.aspectRatio      = static_cast<float>(monitorX) / static_cast<float>(monitorY);                                                                             //  Cast the screens aspect ratio as a float
    };
    
    camera.locationX			= 0.0f;
    camera.locationY			= 0.0f;
    camera.locationZ            = -1.0f;

    camera.cameraPosition       = vec3(camera.locationX, camera.locationY, camera.locationZ);                                                                                          //  Define the camera's position
    camera.targetPosition		= vec3(0.0f, 0.0f, 0.0f);
    camera.direction            = glm::normalize(camera.cameraPosition - camera.targetPosition);
    camera.upVector             = vec3(0.0f, 1.0f, 0.0f);                                                                                          //  Define the tilt / rotation of the camera
    
    camera.viewMatrix           = glm::lookAt(camera.cameraPosition, (camera.cameraPosition + camera.direction), camera.upVector);              //  Define the view-matrix through the camera properties
    camera.projectionMatrix     = glm::ortho(0.0f, static_cast<float>(arX), 0.0f, static_cast<float>(arY));

    camera.viewLocation         = glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    camera.projectionLocation   = glGetUniformLocation(shader, "orthoProjectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 

    camera.usesPerspective      = 0;

    return camera;                                                                                                                             //  Return the newly created camera struct
};

void CameraManager::loadCamera(CameraManager::Camera &cameraData)
{
    if(cameraData.projectionLocation >= 0)
    {
        glUniformMatrix4fv     (cameraData.viewLocation, 1, GL_FALSE, &cameraData.viewMatrix[0][0]);                                                      //  Pass view-uniform data into the shader program
        glUniformMatrix4fv     (cameraData.projectionLocation, 1, GL_FALSE, &cameraData.projectionMatrix[0][0]);                                          //  Pass projection-uniform data into the shader program

        glUniform1i(glGetUniformLocation(this->shader, "usesPerspective"), cameraData.usesPerspective);
    }
    else
    {
        globals.setExecutionState(LAZARUS_MATRIX_LOCATION_ERROR);
    };
};

CameraManager::~CameraManager()
{
    std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
}