#ifndef __GLEW_H__
    #include "./src/utils/hdr/gl_includes.h"
#endif

#include <iostream>

#include "./src/window/hdr/WindowManager.h"
#include "./src/mesh/hdr/mesh.h"
#include "./src/transforms/hdr/transforms.h"
#include "./src/shaders/shaderProgram/hdr/shader.h"
#include "./src/lights/hdr/light.h"
#include "./src/cameras/hdr/camera.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

#ifndef MAIN_H
#define MAIN_H

GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
GLFWwindow *win; 

int errorCode;
const char** errorMessage;

WindowManager *windowBuilder;
// int errorCode;
Shader *shader;
Light *lightBuilder;
Camera *cameraBuilder;
Mesh *cubeBuilder;
Mesh *houseBuilder;
Transform *transformer;

Light::AmbientLight light;
Camera::StaticCamera camera;
Mesh::TriangulatedMesh cube;
Mesh::TriangulatedMesh house;

#endif