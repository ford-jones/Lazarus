#version 330 core

in vec3 normal;
in vec3 fragPosition;
in vec3 fragColor;

uniform vec3 lightPosition;
uniform vec3 lightColor;

    out vec4 outFragColor;

    void main()
    {
       vec3 lightDirection = normalize(lightPosition - fragPosition);
       float diff = max(dot(normal, lightDirection), 0.0);
       vec3 diffuse = fragColor * lightColor * diff;

       outFragColor = vec4(diffuse, 1.0);
    }