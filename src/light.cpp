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

#include "../include/light.h"

Light::Light(GLuint shader)
{
	this->shaderProgram = shader;
}

shared_ptr<Light::AmbientLight> Light::createAmbientLight(double x, double y, double z, double r, double g, double b)
{
	ambientLight = std::make_shared<Light::AmbientLight>();
	
    srand(time((0)));                                                                                                             // Seed a random number based on current time

    ambientLight->id             =   1 + (rand() % 2147483647);
    
    ambientLight->locationX = x;
    ambientLight->locationY = y;
    ambientLight->locationZ = z;

    ambientLight->lightPosition  =   vec3(ambientLight->locationX, ambientLight->locationY, ambientLight->locationZ);
    ambientLight->lightColor     =   vec3(r, g, b);
    
    ambientLight->lightPositionUniformLocation   =   glGetUniformLocation(shaderProgram, "lightPosition");
    ambientLight->lightColorUniformLocation      =   glGetUniformLocation(shaderProgram, "lightColor");

    return ambientLight;
};

void Light::loadLightSource(shared_ptr<Light::AmbientLight> &lightData)
{
    glUniform3fv        (lightData->lightPositionUniformLocation, 1, &lightData->lightPosition[0]);
    glUniform3fv        (lightData->lightColorUniformLocation, 1, &lightData->lightColor[0]);
};
