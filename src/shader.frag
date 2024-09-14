#version 460 core

in vec3 fragPosition;
in vec3 diffuseColor;
in vec3 normalCoordinate;
in vec2 textureCoordinate;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform float threeDimesionalTexLayerIndex;
uniform float twoDimesionalTexLayerIndex;

uniform int meshHasThreeDimensions;

layout ( binding = 1 ) uniform sampler2DArray threeDimensionalMeshTextures;
layout ( binding = 2 ) uniform sampler2DArray twoDimensionalMeshTextures;

out vec4 outFragment;

vec3 calculateLambertianDeflection (vec3 colorData) 
{
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normalCoordinate, lightDirection), 0.0);

    vec3 illuminatedFrag = (colorData * lightColor * diff);
    return illuminatedFrag;
}

vec3 interpretColorData ()
{
    if((diffuseColor.r >= 0.0) &&
       (diffuseColor.g >= 0.0) && 
       (diffuseColor.b >= 0.0))
    {
        return diffuseColor;
    }
    else 
    {
        if( meshHasThreeDimensions == 1 )
        {
            vec4 tex = texture(threeDimensionalMeshTextures, vec3(textureCoordinate.xy, threeDimesionalTexLayerIndex));
            vec3 texColor = vec3(tex.r, tex.g, tex.b);
        } 
        else
        {
            vec4 tex = texture(twoDimensionalMeshTextures, vec3(textureCoordinate.xy, twoDimesionalTexLayerIndex));
            vec3 texColor = vec3(tex.r, tex.g, tex.b);
        } 

        return texColor;
    }
}

void main ()
{
    vec3 fragColor = interpretColorData();
    vec3 illumFrag = calculateLambertianDeflection(fragColor);

    outFragment = vec4(illumFrag, 1.0);
}