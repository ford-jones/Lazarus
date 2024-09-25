#ifndef LAZARUS_GL_INCLUDES_H
    #include "gl_includes.h"
#endif

// #ifndef LAZARUS_GLOBALS_MANAGER_H
    #include "globalsManager.h"
// #endif

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
    using ::GlobalsManager;
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