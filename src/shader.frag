#version 410 core

in vec3 fragPosition;
in vec3 diffuseColor;
in vec3 normalCoordinate;
in vec2 textureCoordinate;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform float xyzTexLayerIndex;
uniform float xyTexLayerIndex;

uniform int spriteAsset;

uniform sampler2DArray xyzAssetTextures;
uniform sampler2DArray xyAssetTextures;

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
        if( spriteAsset == 1 )
        {
            vec4 tex = texture(xyzAssetTextures, vec3(textureCoordinate.xy, xyzTexLayerIndex));
            return tex;
        } 
        else
        {
            vec4 tex = texture(xyAssetTextures, vec3(textureCoordinate.xy, xyTexLayerIndex));

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