#include "main.h"

int main()
{
    windowBuilder = std::make_unique<WindowManager>(800, 600, "Lazarus::Experimental", nullptr, nullptr);
    windowBuilder->initialise();

    win = glfwGetCurrentContext();
    glewExperimental = GL_TRUE;                                                                                         //  Enable GLEW's experimental features
    glewInit();                                                                                                         //  Initialise GLEW graphics library

    printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << "Version GLFW: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    printf("Version GLEW: %s\n", glewGetString(GLEW_VERSION));

    shaderProgram = shader.initialiseShader();

    glEnable            (GL_CULL_FACE);                                                                                 //  Disable rendering of faces oposite to the viewport
    glEnable            (GL_TEXTURE_2D);                                                                                //  Enable 2 dimensional texture use in this context
    glEnable            (GL_DEPTH_TEST);                                                                                //  Run a depth test on each fragment, render frags in order of perspective rather than order drawn.

    glClearColor        (0.0, 0.0, 0.0, 1.0);                                                                           //  Set the background colour of the scene to black

    glUseProgram        (shaderProgram);                                                                                //  Use the newly created shader program

    light       = lightBuilder.createAmbientLight(shaderProgram, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
    
    cameraBuilder = std::make_unique<Camera>(shaderProgram);
    camera      = std::move(cameraBuilder->createFixedCamera(800, 600, 1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

    worldBuilder = std::make_unique<Mesh>();
    world       = std::move(worldBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/world.obj"));

    beachballBuilder = std::make_unique<Mesh>();
    beachball   = std::move(beachballBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/beachball.obj"));

    cubeBuilder = std::make_unique<Mesh>();
    cube   = std::move(cubeBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/cube.obj"));

    while(!glfwWindowShouldClose(win))
    {
        /*Setup*/
        eventManager.monitorEvents();


        /*Render*/
        if( camera->projectionLocation >= 0 )
        {
            lightBuilder.initialiseLight(light); //  Pass the values for each uniform into the shader program
            camera = std::move(cameraBuilder->loadCamera(camera));
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
        };

        /*World*/
        if( world->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            world = worldBuilder->initialiseMesh(world);
            worldBuilder->loadMesh(*world);
            worldBuilder->drawMesh(*world);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };
        /*Cube*/
        if( cube->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            cube = cubeBuilder->initialiseMesh(cube);
            cubeBuilder->loadMesh(*cube);
            cubeBuilder->drawMesh(*cube);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };
        /*Beachball*/
        if( beachball->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            beachball = transformer.applyRotation(beachball, eventManager.xangle, eventManager.yangle);
            beachball = transformer.applyTranslation(beachball, (eventManager.xangle / 50), 0.0, (eventManager.yangle / 50));

            beachball = beachballBuilder->initialiseMesh(beachball);
            beachballBuilder->loadMesh(*beachball);
            beachballBuilder->drawMesh(*beachball);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

		windowBuilder->handleBuffers();
        /*Check errors*/
        // windowBuilder->checkErrors();

        /*Swap Buffers*/
        // glfwSwapBuffers(win);
        // glClear             (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers
    };
    
    return 0;
};
