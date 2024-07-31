#version 460 core

in vec3 fragPosition;
in vec3 diffuseColor;
in vec3 normalCoordinate;
in vec2 textureCoordinate;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform sampler2D texImg;

out vec4 outFragment;

vec3 applyLambertianLight ()
{
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normalCoordinate, lightDirection), 0.0);

    if((diffuseColor.r >= 0.0) &&
       (diffuseColor.g >= 0.0) && 
       (diffuseColor.b >= 0.0))
    {
        return (diffuseColor * lightColor * diff);
    }
    else 
    {
        vec4 texColor = texture(texImg, textureCoordinate);
        return (vec3(texColor.r, texColor.g, texColor.b) * lightColor * diff);
    }
}

void main()
{
    vec3 illuminatedSurface = applyLambertianLight();

    outFragment = vec4(illuminatedSurface, 1.0);
}