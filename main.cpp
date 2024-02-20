#include "main.h"

int main()
{
    lightBuilder        =   new Light;
    cameraBuilder       =   new Camera;
    houseBuilder        =   new Mesh;
    shader              =   new Shader;
    // transformer         =   new Transform;
    windowBuilder       =   new WindowManager(800, 600, "Lazarus::Experimental", NULL, NULL);

    windowBuilder->Initialise();

    printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    win = glfwGetCurrentContext();
    glewExperimental = GL_TRUE;                                                                                         //  Enable GLEW's experimental features
    glewInit();                                                                                                         //  Initialise GLEW graphics library

    shaderProgram = shader->initialiseShader();

    glEnable            (GL_CULL_FACE);                                                                                 //  Disable rendering of faces oposite to the viewport
    glEnable            (GL_TEXTURE_2D);                                                                                //  Enable 2 dimensional texture use in this context
    glEnable            (GL_DEPTH_TEST);                                                                                //  Run a depth test on each fragment, render frags in order of perspective rather than order drawn.

    glClearColor        (0.0, 0.0, 0.0, 1.0);                                                                           //  Set the background colour of the scene to black

    glClear             (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers

    glUseProgram        (shaderProgram);                                                                                //  Use the newly created shader program

    //  Light + Camera
    light   = lightBuilder->createAmbientLight(shaderProgram, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0);
    camera  = cameraBuilder->createStaticCamera(shaderProgram, 800, 600, 1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    if( camera.projectionLocation >= 0 )
    {
        lightBuilder->initialiseLight(light); //  Pass the values for each uniform into the shader program
        cameraBuilder->initialiseCamera(camera);
    }
    else
    {
        std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
    };

    // //  House
    house = houseBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/house.obj");
    if( house.modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
    {
        // house = transformer->applyTranslation(house, (xangle / 50), 0.0f, (yangle / 50));
        houseBuilder->instantiateMesh(house);
    }
    else
    {
        std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
    };

    while(!glfwWindowShouldClose(win))
    {
        /*Setup*/
        glfwPollEvents();
        glClear             (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers

        /*Render*/
        houseBuilder->drawMesh(house);

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
    delete houseBuilder;
    delete shader;
    delete windowBuilder;
    
    return 0;
};
