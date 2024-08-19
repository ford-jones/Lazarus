#ifndef LAZARUS_GL_INCLUDES_H
    #include "gl_includes.h"
#endif

#include "WindowManager.h"
#include "eventManager.h"
#include "mesh.h"
#include "transforms.h"
#include "shader.h"
#include "light.h"
#include "camera.h"
#include "fpsCounter.h"
#include "fileReader.h"
#include "soundManager.h"

#ifndef LAZARUS_H
#define LAZARUS_H

namespace Lazarus
{
    using ::WindowManager;
    using ::EventManager;
    using ::Mesh;
    using ::Transform;
    using ::Shader;
    using ::Light;
    using ::Camera;
    using ::FpsCounter;
    using ::FileReader;
    using ::SoundManager;
}

#endif

// #ifndef LAZARUS_GL_INCLUDES_H
//     #include "./src/utils/hdr/gl_includes.h"
// #endif

// #include <iostream>
// #include <memory>
// #include <string>

// #include "./src/window/hdr/WindowManager.h"
// #include "./src/window/hdr/eventManager.h"
// #include "./src/mesh/hdr/mesh.h"
// #include "./src/transforms/hdr/transforms.h"
// #include "./src/shaders/shaderProgram/hdr/shader.h"
// #include "./src/lights/hdr/light.h"
// #include "./src/cameras/hdr/camera.h"
// #include "./src/utils/hdr/fpsCounter.h"
// #include "./src/utils/hdr/fileReader.h"
// #include "./src/sound/hdr/soundManager.h"

// #define GREEN_TEXT "\x1b[32m"
// #define RESET_TEXT "\x1b[37m"
// #define RED_TEXT  "\x1b[31m"

// using std::string;
// using std::unique_ptr;
// using std::shared_ptr;

// #ifndef MAIN_H
// #define MAIN_H

// GLuint shaderProgram;                                                               //  Stores the shader program being passed to OpenGL
// GLFWwindow *win; 

// int errorCode;
// const char** errorMessage;

// float moveX, moveZ;
// float turnX, turnY;
// FileReader::Image cursorImage;

// void keyCapture(string key);

// EventManager eventManager;
// Shader shader;
// Transform transformer;
// FpsCounter fpsCounter;

// unique_ptr<FileReader> fileReader;
// unique_ptr<SoundManager> soundManager;
// unique_ptr<WindowManager> windowBuilder;
// unique_ptr<Camera> cameraBuilder;
// unique_ptr<Light> lightBuilder;

// unique_ptr<Mesh> wallsBuilder;
// unique_ptr<Mesh> skullBuilder;
// unique_ptr<Mesh> floorsBuilder;
// unique_ptr<Mesh> swordBuilder;

// shared_ptr<SoundManager::Audio> springWaltz;
// shared_ptr<SoundManager::Audio> footstep;
// shared_ptr<Camera::FixedCamera> camera;
// shared_ptr<Light::AmbientLight> light;

// shared_ptr<Mesh::TriangulatedMesh> skull;
// shared_ptr<Mesh::TriangulatedMesh> walls;
// shared_ptr<Mesh::TriangulatedMesh> floors;
// shared_ptr<Mesh::TriangulatedMesh> sword;

// #endif