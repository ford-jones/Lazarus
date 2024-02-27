#include "main.h"

int main()
{
    windowBuilder = std::make_unique<WindowManager>(800, 600, "Lazarus::Experimental", nullptr, nullptr);
    windowBuilder->initialise();

    win = glfwGetCurrentContext();

    printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << "Version GLFW: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    printf("Version GLEW: %s\n", glewGetString(GLEW_VERSION));

    shaderProgram = shader.initialiseShader();

    windowBuilder->loadConfig(shaderProgram);																				//  Use the newly created shader program

	lightBuilder = std::make_unique<Light>(shaderProgram);
    light        = std::move(lightBuilder->createAmbientLight(1.0, 1.0, 1.0, 1.0, 1.0, 1.0));
    
    cameraBuilder = std::make_unique<Camera>(shaderProgram);
    camera      = std::move(cameraBuilder->createFixedCamera(windowBuilder->frame.height, windowBuilder->frame.width, 1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

    worldBuilder = std::make_unique<Mesh>(shaderProgram);
    world       = std::move(worldBuilder->createTriangulatedMesh("assets/mesh/world.obj"));

    beachballBuilder = std::make_unique<Mesh>(shaderProgram);
    beachball   = std::move(beachballBuilder->createTriangulatedMesh("assets/mesh/beachball.obj"));

    while(!glfwWindowShouldClose(win))
    {
        eventManager.monitorEvents();


		/*Camera*/
        if( camera->projectionLocation >= 0 )
        {
            light = std::move(lightBuilder->initialiseLight(light)); //  Pass the values for each uniform into the shader program
            camera = transformer.translateCameraAsset(camera, (eventManager.xangle / 50), 0.0, (eventManager.yangle / 50));
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

        /*Beachball*/
        if( beachball->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            beachball = beachballBuilder->initialiseMesh(beachball);
            beachballBuilder->loadMesh(*beachball);
            beachballBuilder->drawMesh(*beachball);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

		windowBuilder->handleBuffers();

    };
    
    return 0;
};

