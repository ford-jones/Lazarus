#include "main.h"

int main()
{
	fileReader = std::make_unique<FileReader>();
	cursorImage = fileReader->loadImage("assets/images/crosshair.png");
	
    windowBuilder = std::make_unique<WindowManager>(800, 600, "Lazarus::Experimental", nullptr, nullptr);
    windowBuilder->initialise();
	windowBuilder->createCursor(32, 32, 0, 0, cursorImage);
	
    win = glfwGetCurrentContext();

    shaderProgram = shader.initialiseShader();
	
    windowBuilder->loadConfig(shaderProgram);									//  Use the newly created shader program

    lightBuilder = std::make_unique<Light>(shaderProgram);
    light        = std::move(lightBuilder->createAmbientLight(1.0, 1.0, 1.0, 1.0, 1.0, 1.0));
    
    cameraBuilder = std::make_unique<Camera>(shaderProgram);
    camera      = std::move(cameraBuilder->createFixedCamera(800, 600, 1.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

    worldBuilder = std::make_unique<Mesh>(shaderProgram);
    world       = std::move(worldBuilder->createTriangulatedMesh("assets/mesh/world.obj"));

    beachballBuilder = std::make_unique<Mesh>(shaderProgram);
    beachball   = std::move(beachballBuilder->createTriangulatedMesh("assets/mesh/beachball.obj"));

	//printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
	//printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//std::cout << "Version GLFW: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION << std::endl;
	//printf("Version GLEW: %s\n", glewGetString(GLEW_VERSION));
	
    while(!glfwWindowShouldClose(win))
    {
        eventManager.monitorEvents();

		/*Camera*/
        if( camera->projectionLocation >= 0 )
        {
            light = std::move(lightBuilder->initialiseLight(light));
            
            camera = transformer.rotateCameraAsset(camera, turnX, turnY, 0.0);
            camera = transformer.translateCameraAsset(camera, (moveX / 50), 0.0, (moveZ / 50));
            moveCamera(eventManager.keyString);
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
            //	TODO:
            //	Instead of passing a mem handler, pass the entire shared pointer
            //	Move ownership to the loader then return it
            //	Do the same for the draw function
            
            worldBuilder->loadMesh(world);
            worldBuilder->drawMesh(world);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*Beachball*/
        if( beachball->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            beachball = beachballBuilder->initialiseMesh(beachball);
            //beachball = transformer.translateMeshAsset(beachball, (moveX / 50), 0.0, (moveZ / 50));
            //beachball = transformer.rotateMeshAsset(beachball, turnX, turnY, 0.0);
            beachballBuilder->loadMesh(beachball);
            beachballBuilder->drawMesh(beachball);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };
        
		windowBuilder->handleBuffers();
    };
   
    return 0;
};

void moveCamera(string key)
{
		if(key == "up")
		{
			moveZ += 0.5;
		}
		else if(key == "down")
		{
			moveZ += -0.5;
		}
		else if(key == "left")
		{
			moveX += 0.5;
		}
		else if(key == "right")
		{
			moveX += -0.5;
		}
		else if(key == "w")
		{
			turnX += -0.5;
		}
		else if(key == "s")
		{
			turnX += 0.5;
		}
		else if(key == "a")
		{
			turnY += -0.5;
		}
		else if(key == "d")
		{
			turnY += 0.5;
		}
		else 
		{
			moveX = 0.0;
			moveZ = 0.0;
			turnX = 0.0;
			turnY = 0.0;
		};
};
