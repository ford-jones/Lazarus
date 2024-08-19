#version 460 core

layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec3 inDiffuse;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTexCoord;

out vec3 fragPosition;
out vec3 diffuseColor;
out vec3 normalCoordinate;
out vec2 textureCoordinate;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main ()
{
   fragPosition = vec3(modelMatrix * vec4(inVertex, 1.0));
   normalCoordinate = mat3(transpose(inverse(modelMatrix))) * inNormal;

   vec4 worldPosition = modelMatrix * vec4(inVertex, 1.0);
   gl_Position = projectionMatrix * viewMatrix * worldPosition;
   
   textureCoordinate = vec2(inTexCoord.x, inTexCoord.y);
   diffuseColor = inDiffuse;
}