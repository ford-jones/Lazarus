#version 460 core

layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec3 inDiffuse;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTexCoord;

out vec3 normal;
out vec3 fragPosition;
out vec3 fragColor;
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
   fragPosition = vec3(modelMatrix * vec4(inVertex, 1.0));
   normal = mat3(transpose(inverse(modelMatrix))) * inNormal;

   vec4 worldPosition = modelMatrix * vec4(inVertex, 1.0);
   gl_Position = projectionMatrix * viewMatrix * worldPosition;
   
   texCoord = vec2(inTexCoord.x, inTexCoord.y);
   fragColor = inDiffuse;
}