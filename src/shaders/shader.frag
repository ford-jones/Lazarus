#version 460 core

in vec3 normal;
in vec3 fragPosition;
in vec3 fragColor;
in vec2 texCoord;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform sampler2D texImg;

out vec4 outFragColor;

void main()
{
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(normal, lightDirection), 0.0);

    if( (fragColor.r >= 0.0) && 
        (fragColor.g >= 0.0) && 
        (fragColor.b >= 0.0) )
    {
        vec3 diffuse = fragColor * lightColor * diff;

        outFragColor = vec4(diffuse, 1.0);
    }
    else
    {
        vec4 texColor = texture(texImg, texCoord);
        vec3 diffuse = vec3(texColor.r, texColor.g, texColor.b) * lightColor * diff;
        
        outFragColor = vec4(diffuse, 1.0);
    }
}