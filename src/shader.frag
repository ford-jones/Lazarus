#version 460 core

in vec3 fragPosition;
in vec3 diffuseColor;
in vec3 normalCoordinate;
in vec2 textureCoordinate;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform float threeDimensionalTexLayerIndex;
uniform float twoDimensionalTexLayerIndex;

uniform int meshHasThreeDimensions;

layout ( binding = 1 ) uniform sampler2DArray threeDimensionalMeshTextures;
layout ( binding = 2 ) uniform sampler2DArray twoDimensionalMeshTextures;

out vec4 outFragment;

vec3 calculateLambertianDeflection (vec4 colorData) 
{
    vec3 color = vec3(colorData.r, colorData.g, colorData.b);

    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normalCoordinate, lightDirection), 0.0);

    vec3 illuminatedFrag = (color * lightColor * diff);
    
    return illuminatedFrag;
}

vec4 interpretColorData ()
{
    if((diffuseColor.r >= 0.0) &&
       (diffuseColor.g >= 0.0) && 
       (diffuseColor.b >= 0.0))
    {
        return vec4(diffuseColor, 1.0);
    }
    else 
    {
        if( meshHasThreeDimensions == 1 )
        {
            vec4 tex = texture(threeDimensionalMeshTextures, vec3(textureCoordinate.xy, threeDimensionalTexLayerIndex));
            return tex;
        } 
        else
        {
            vec4 tex = texture(twoDimensionalMeshTextures, vec3(textureCoordinate.xy, twoDimensionalTexLayerIndex));

            if(tex.a < 0.1)
            {
                discard;
            }

            return tex;
        } 

    }
}

void main ()
{
    vec4 fragColor = interpretColorData();
            
    vec3 illumFrag = calculateLambertianDeflection(fragColor);

    outFragment = vec4(illumFrag, 1.0);

    return;
}