#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/light.h"

Light::AmbientLight Light::createAmbientLight(GLuint shader, double x, double y, double z, double r, double g, double b)
{
    srand(time((0)));                                                                                                             // Seed a random number based on current time

    ambientLight.id             =   1 + (rand() % 2147483647);

    ambientLight.lightPosition  =   vec3(x, y, z);
    ambientLight.lightColor     =   vec3(r, g, b);
    
    ambientLight.lightPositionUniformLocation   =   glGetUniformLocation(shader, "lightPosition");
    ambientLight.lightColorUniformLocation      =   glGetUniformLocation(shader, "lightColor");

    return ambientLight;
};

void Light::initialiseLight(AmbientLight lightData)
{
    glUniform3fv        (lightData.lightPositionUniformLocation, 1, &lightData.lightPosition[0]);
    glUniform3fv        (lightData.lightColorUniformLocation, 1, &lightData.lightColor[0]);
};