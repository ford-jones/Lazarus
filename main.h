#ifndef LAZARUS_GL_INCLUDES_H
    #include "./src/utils/hdr/gl_includes.h"
#endif

#include <iostream>
#include <memory>
#include <string>

#include "./src/window/hdr/WindowManager.h"
#include "./src/window/hdr/eventManager.h"
#include "./src/mesh/hdr/mesh.h"
#include "./src/transforms/hdr/transforms.h"
#include "./src/shaders/shaderProgram/hdr/shader.h"
#include "./src/lights/hdr/light.h"
#include "./src/cameras/hdr/camera.h"
#include "./src/utils/hdr/fpsCounter.h"
#include "./src/utils/hdr/fileReader.h"
#include "./src/sound/hdr/soundManager.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

using std::string;
using std::unique_ptr;
using std::shared_ptr;

#ifndef MAIN_H
#define MAIN_H

GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
GLFWwindow *win; 

int errorCode;
const char** errorMessage;

float moveX, moveZ;
float turnX, turnY;
unsigned char *cursorImage;

void keyCapture(string key);

EventManager eventManager;
Shader shader;
Transform transformer;
FpsCounter fpsCounter;

unique_ptr<FileReader> fileReader;
unique_ptr<SoundManager> soundManager;
unique_ptr<WindowManager> windowBuilder;
unique_ptr<Camera> cameraBuilder;
unique_ptr<Light> lightBuilder;
unique_ptr<Mesh> worldBuilder;
unique_ptr<Mesh> beachballBuilder;

shared_ptr<SoundManager::Audio> springWaltz;
shared_ptr<SoundManager::Audio> footstep;
shared_ptr<Camera::FixedCamera> camera;
shared_ptr<Light::AmbientLight> light;
shared_ptr<Mesh::TriangulatedMesh> beachball;
shared_ptr<Mesh::TriangulatedMesh> world;

#endif
