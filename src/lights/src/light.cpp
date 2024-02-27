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

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/light.h"

Light::Light(GLuint shader)
{
	this->shaderProgram = shader;
}

shared_ptr<Light::AmbientLight> Light::createAmbientLight(double x, double y, double z, double r, double g, double b)
{
	ambientLight = std::make_shared<Light::AmbientLight>();
	
    srand(time((0)));                                                                                                             // Seed a random number based on current time

    ambientLight->id             =   1 + (rand() % 2147483647);

    ambientLight->lightPosition  =   vec3(x, y, z);
    ambientLight->lightColor     =   vec3(r, g, b);
    
    ambientLight->lightPositionUniformLocation   =   glGetUniformLocation(shaderProgram, "lightPosition");
    ambientLight->lightColorUniformLocation      =   glGetUniformLocation(shaderProgram, "lightColor");

    return ambientLight;
};

shared_ptr<Light::AmbientLight> Light::initialiseLight(shared_ptr<Light::AmbientLight> lightData)
{
	this->ambientLight = std::move(lightData);
    glUniform3fv        (ambientLight->lightPositionUniformLocation, 1, &ambientLight->lightPosition[0]);
    glUniform3fv        (ambientLight->lightColorUniformLocation, 1, &ambientLight->lightColor[0]);
    
    return ambientLight;
};
