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

shared_ptr<Light::LightSource> Light::createPointLight(double x, double y, double z, double r, double g, double b)
{
	light = std::make_shared<Light::LightSource>();
	
    srand(time((0)));                                                                                                             // Seed a random number based on current time

    light->id             =   1 + (rand() % 2147483647);

    light->lightType      =   LAZARUS_POINT_LIGHT;

    light->lightDirection =   vec3(0.0, 0.0, 0.0);
    light->lightPosition  =   vec3(x, y, z);
    light->lightColor     =   vec3(r, g, b);
    
    this->loadUniforms(light);

    return light;
};

shared_ptr<Light::LightSource> Light::createDirectionalLight(double x, double y, double z, double r, double g, double b)
{
    light = std::make_shared<Light::LightSource>();
	
    srand(time((0)));                                                                                                             // Seed a random number based on current time

    light->id             =   1 + (rand() % 2147483647);

    light->lightType      =   LAZARUS_DIRECTIONAL_LIGHT;

    light->lightDirection =   vec3(x, y, z);
    light->lightPosition  =   vec3(0.0, 0.0, 0.0);
    light->lightColor     =   vec3(r, g, b);
    
    this->loadUniforms(light);

    return light;
};

void Light::loadUniforms(shared_ptr<LightSource> &light)
{
    light->lightDirectionUniformLocation  =   glGetUniformLocation(shaderProgram, "lightDirection");
    light->lightPositionUniformLocation   =   glGetUniformLocation(shaderProgram, "lightPosition");
    light->lightColorUniformLocation      =   glGetUniformLocation(shaderProgram, "lightColor");
    light->lightTypeUniformLocation       =   glGetUniformLocation(shaderProgram, "lightingType");
};

void Light::loadLightSource(shared_ptr<Light::LightSource> &lightData)
{
    glUniform3fv        (lightData->lightPositionUniformLocation, 1, &lightData->lightDirection[0]);
    glUniform3fv        (lightData->lightPositionUniformLocation, 1, &lightData->lightPosition[0]);
    glUniform3fv        (lightData->lightColorUniformLocation, 1, &lightData->lightColor[0]);
    glUniform1i         (lightData->lightTypeUniformLocation, lightData->lightType);
};
