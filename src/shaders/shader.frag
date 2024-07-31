#version 460 core

in vec3 fragPosition;
in vec3 diffuseColor;
in vec3 normalCoordinate;
in vec2 textureCoordinate;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform sampler2D texImg;

out vec4 outFragment;

vec3 calculateLambertianDeflection (vec3 colorData) 
{
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normalCoordinate, lightDirection), 0.0);

    vec3 illuminatedFrag = (colorData * lightColor * diff);
    return illuminatedFrag;
}

vec3 interpretTextureData ()
{
    if((diffuseColor.r >= 0.0) &&
       (diffuseColor.g >= 0.0) && 
       (diffuseColor.b >= 0.0))
    {
        vec3 ilumSolidColor = calculateLambertianDeflection(diffuseColor);
        return ilumSolidColor;
    }
    else 
    {
        vec4 tex = texture(texImg, textureCoordinate);
        vec3 texColor = vec3(tex.r, tex.g, tex.b);

        vec3 ilumTexColor = calculateLambertianDeflection(texColor);
        return ilumTexColor;
    }
}

void main ()
{
    vec3 processedFrag = interpretTextureData();

    outFragment = vec4(processedFrag, 1.0);
}