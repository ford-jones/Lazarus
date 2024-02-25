#ifndef __GLEW_H__
    #include "./src/utils/hdr/gl_includes.h"
#endif

#include <iostream>
#include <memory>

#include "./src/window/hdr/WindowManager.h"
#include "./src/window/hdr/eventManager.h"
#include "./src/mesh/hdr/mesh.h"
#include "./src/transforms/hdr/transforms.h"
#include "./src/shaders/shaderProgram/hdr/shader.h"
#include "./src/lights/hdr/light.h"
#include "./src/cameras/hdr/camera.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

using std::unique_ptr;
using std::shared_ptr;

#ifndef MAIN_H
#define MAIN_H

GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
GLFWwindow *win; 

int errorCode;
const char** errorMessage;

EventManager eventManager;
Shader shader;
Transform transformer;
Light lightBuilder;
Camera cameraBuilder;

Light::AmbientLight light;
Camera::StaticCamera camera;

unique_ptr<WindowManager> windowBuilder;
unique_ptr<Mesh> worldBuilder;
unique_ptr<Mesh> beachballBuilder;
unique_ptr<Mesh> cubeBuilder;

shared_ptr<Mesh::TriangulatedMesh> beachball;
shared_ptr<Mesh::TriangulatedMesh> world;
shared_ptr<Mesh::TriangulatedMesh> cube;

#endif