#include "main.h"

int main()
{
    windowBuilder       =   new WindowManager(800, 600, "Lazarus::Experimental", NULL, NULL);
    eventManager        =   new EventManager;
    lightBuilder        =   new Light;
    cameraBuilder       =   new Camera;
    worldBuilder        =   new Mesh;
    // world               =   new Mesh::TriangulatedMesh;
    beachballBuilder    =   new Mesh;
    // beachball           =   new Mesh::TriangulatedMesh;
    // beachball               =   std::make_shared<Mesh::TriangulatedMesh>();
    transformer         =   new Transform;
    shader              =   new Shader;

    windowBuilder->Initialise();

    win = glfwGetCurrentContext();
    glewExperimental = GL_TRUE;                                                                                         //  Enable GLEW's experimental features
    glewInit();                                                                                                         //  Initialise GLEW graphics library

    printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << "Version GLFW: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
    printf("Version GLEW: %s\n", glewGetString(GLEW_VERSION));

    shaderProgram = shader->initialiseShader();

    glEnable            (GL_CULL_FACE);                                                                                 //  Disable rendering of faces oposite to the viewport
    glEnable            (GL_TEXTURE_2D);                                                                                //  Enable 2 dimensional texture use in this context
    glEnable            (GL_DEPTH_TEST);                                                                                //  Run a depth test on each fragment, render frags in order of perspective rather than order drawn.

    glClearColor        (0.0, 0.0, 0.0, 1.0);                                                                           //  Set the background colour of the scene to black

    glUseProgram        (shaderProgram);                                                                                //  Use the newly created shader program

    light   = lightBuilder->createAmbientLight(shaderProgram, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0);
    camera  = cameraBuilder->createStaticCamera(shaderProgram, 800, 600, 1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    world   = std::move(worldBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/world.obj"));
    beachball   = std::move(beachballBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/beachball.obj"));

    while(!glfwWindowShouldClose(win))
    {
        /*Setup*/
        eventManager->monitorEvents();

        glClear             (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers

        /*Render*/
        if( camera.projectionLocation >= 0 )
        {
            lightBuilder->initialiseLight(light); //  Pass the values for each uniform into the shader program
            cameraBuilder->initialiseCamera(camera);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
        };

        
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

        if( beachball->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            beachball = transformer->applyRotation(beachball, eventManager->xangle, eventManager->yangle);
            beachball = transformer->applyTranslation(beachball, (eventManager->xangle / 50), 0.0, (eventManager->yangle / 50));

            beachball = beachballBuilder->initialiseMesh(beachball);
            beachballBuilder->loadMesh(*beachball);
            beachballBuilder->drawMesh(*beachball);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };


        /*Check errors*/
        errorCode = glfwGetError(errorMessage); 
        if(errorCode != GLFW_NO_ERROR)
        {
            std::cout << "ERROR::GLFW::WINDOW" << std::endl;
            std::cout << "GL_MESSAGE: " << errorMessage << std::endl;

            return errorCode;
        };
        /*Swap Buffers*/
        glfwSwapBuffers(win);
    };

    delete lightBuilder;
    delete cameraBuilder;
    delete worldBuilder;
    // delete world;
    delete beachballBuilder;
    // delete beachball;
    delete transformer;
    delete shader;
    delete windowBuilder;
    delete eventManager;
    
    return 0;
};