#version 330 core

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
    vec3 diffuse = fragColor * lightColor * diff;

    vec4 texColor = texture(texImg, texCoord);

    //  TODO:
    //  This check should be run for r, g, b & a
    //  When r is specified, the bottom right corner of the cube is touched by the tex
    //  Why would it be the alpha value alone anyway? 

    //  Also; all meshes have a texCoord
    //  So its plausible that in some cases, (texColor.x > 0.0) could return true for undesired fragments in other parts of the scene
    //  Hence the fragmentation (bleeding into the other mesh)
    //  The meshloader could possibly perform a check also - and then conditionally load the texcoords into the buffer(s)

    if(texColor.a > 0.0)
    {
        outFragColor = texColor;
    }
    else
    {
        outFragColor = vec4(diffuse, 1.0);
    }
}