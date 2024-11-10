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

#include "../include/camera.h"

Camera::Camera(GLuint shader)
{
    std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
    this->shader = shader;

    this->monitorX = globals.getDisplayWidth();
    this->monitorY = globals.getDisplayHeight();
}

shared_ptr<Camera::FixedCamera> Camera::createPerspectiveCam(double pX, double pY, double pZ, double tX, double tY, double tZ, int arX, int arY)
{
	fixedCamera = std::make_shared<FixedCamera>();
    srand(time((0)));

    fixedCamera->id                   =   1 + (rand() % 2147483647);

    if((arX + arY) > 0)
    {
        fixedCamera->aspectRatio          =   static_cast<float>(arX) / static_cast<float>(arY);                                                                             //  Cast the screens aspect ratio as a float
    }
    else
    {
        fixedCamera->aspectRatio          =   static_cast<float>(monitorX) / static_cast<float>(monitorY);                                                                             //  Cast the screens aspect ratio as a float
    };
    
    fixedCamera->locationX			  =	  pX;
    fixedCamera->locationY			  =	  pY;
    fixedCamera->locationZ            =   pZ;

    fixedCamera->cameraPosition       =   vec3(fixedCamera->locationX, fixedCamera->locationY, fixedCamera->locationZ);                                                                                          //  Define the camera's position
    fixedCamera->targetPosition		  =	  vec3(tX, tY, tZ);
    fixedCamera->direction            =   glm::normalize(fixedCamera->cameraPosition - fixedCamera->targetPosition);
    fixedCamera->upVector             =   vec3(0.0, 1.0, 0.0);                                                                                          //  Define the tilt / rotation of the camera
    
    fixedCamera->viewMatrix           =   glm::lookAt(fixedCamera->cameraPosition, (fixedCamera->cameraPosition + fixedCamera->direction), fixedCamera->upVector);              //  Define the view-matrix through the camera properties
    fixedCamera->projectionMatrix     =   glm::perspective(glm::radians(45.0f), fixedCamera->aspectRatio, 0.1f, 100.0f);                             //  Define the projection matrix, responsible for depth and perspective

    fixedCamera->viewLocation         =   glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    fixedCamera->projectionLocation   =   glGetUniformLocation(shader, "perspectiveProjectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 

    fixedCamera->usesPerspective      =   1;

    return fixedCamera;                                                                                                                             //  Return the newly created camera struct
};

shared_ptr<Camera::FixedCamera> Camera::createOrthoCam(int arX, int arY)
{
	fixedCamera = std::make_shared<FixedCamera>();
    srand(time((0)));

    fixedCamera->id                   =   1 + (rand() % 2147483647);

    if((arX + arY) > 0)
    {
        fixedCamera->aspectRatio          =   static_cast<float>(arX) / static_cast<float>(arY);                                                                             //  Cast the screens aspect ratio as a float
    }
    else
    {
        fixedCamera->aspectRatio          =   static_cast<float>(monitorX) / static_cast<float>(monitorY);                                                                             //  Cast the screens aspect ratio as a float
    };
    
    fixedCamera->locationX			  =	  0.0f;
    fixedCamera->locationY			  =	  0.0f;
    fixedCamera->locationZ            =   -1.0f;

    fixedCamera->cameraPosition       =   vec3(fixedCamera->locationX, fixedCamera->locationY, fixedCamera->locationZ);                                                                                          //  Define the camera's position
    fixedCamera->targetPosition		  =	  vec3(0.0f, 0.0f, 0.0f);
    fixedCamera->direction            =   glm::normalize(fixedCamera->cameraPosition - fixedCamera->targetPosition);
    fixedCamera->upVector             =   vec3(0.0f, 1.0f, 0.0f);                                                                                          //  Define the tilt / rotation of the camera
    
    fixedCamera->viewMatrix           =   glm::lookAt(fixedCamera->cameraPosition, (fixedCamera->cameraPosition + fixedCamera->direction), fixedCamera->upVector);              //  Define the view-matrix through the camera properties
    fixedCamera->projectionMatrix     =   glm::ortho(0.0f, static_cast<float>(arX), 0.0f, static_cast<float>(arY));

    fixedCamera->viewLocation         =   glGetUniformLocation(shader, "viewMatrix");                                                                //  Returns the shader program's view-matrix index position OR -1 upon encountering an error 
    fixedCamera->projectionLocation   =   glGetUniformLocation(shader, "orthoProjectionMatrix");                                                          //  Returns the shader program's projection-matrix index position OR -1 upon encountering an error 

    fixedCamera->usesPerspective      =   0;

    return fixedCamera;                                                                                                                             //  Return the newly created camera struct
};

void Camera::loadCamera(shared_ptr<Camera::FixedCamera> &cameraData)
{
    glUniformMatrix4fv     (cameraData->viewLocation, 1, GL_FALSE, &cameraData->viewMatrix[0][0]);                                                      //  Pass view-uniform data into the shader program
    glUniformMatrix4fv     (cameraData->projectionLocation, 1, GL_FALSE, &cameraData->projectionMatrix[0][0]);                                          //  Pass projection-uniform data into the shader program
    
    glUniform1i(glGetUniformLocation(this->shader, "usesPerspective"), cameraData->usesPerspective);
};

Camera::~Camera()
{
    std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
}