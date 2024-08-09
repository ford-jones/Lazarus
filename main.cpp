#include "main.h"

int main()
{
	fileReader = std::make_unique<FileReader>();
	
    soundManager = std::make_unique<SoundManager>();
    soundManager->initialise();

    windowBuilder = std::make_unique<WindowManager>(800, 600, "Lazarus::Experimental", nullptr, nullptr);
    windowBuilder->initialise();

	cursorImage = fileReader->readFromImage("assets/images/crosshair.png");

	windowBuilder->createCursor(32, 32, 0, 0, cursorImage.pixelData);
	
    win = glfwGetCurrentContext();

    shaderProgram = shader.initialiseShader();
	
    windowBuilder->loadConfig(shaderProgram);

    lightBuilder        = std::make_unique<Light>(shaderProgram);
    light               = std::move(lightBuilder->createAmbientLight(1.0, 1.0, 1.0, 1.0, 1.0, 1.0));
    
    cameraBuilder       = std::make_unique<Camera>(shaderProgram);

    camera              = std::move(cameraBuilder->createFixedCamera(800, 600, 0.0, 1.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

    bricksBuilder       = std::make_unique<Mesh>(shaderProgram);
    bricks              = std::move(bricksBuilder->createTriangulatedMesh("assets/mesh/untitled.obj", "assets/material/untitled.mtl", "assets/images/blue.png"));

    tilesBuilder        = std::make_unique<Mesh>(shaderProgram);
    tiles               = std::move(tilesBuilder->createTriangulatedMesh("assets/mesh/tiles.obj", "assets/material/tiles.mtl", "assets/images/white.png"));

    worldBuilder        = std::make_unique<Mesh>(shaderProgram);
    world               = std::move(worldBuilder->createTriangulatedMesh("assets/mesh/world.obj", "assets/material/world.mtl"));

    springWaltz = std::move(soundManager->createAudio("assets/sound/springWaltz.mp3", true, 0));
    springWaltz = std::move(soundManager->loadAudio(springWaltz));
    springWaltz = std::move(soundManager->playAudio(springWaltz));

    footstep = std::move(soundManager->createAudio("assets/sound/footsteps.mp3", true, -1));
    footstep = std::move(soundManager->loadAudio(footstep));
    footstep = std::move(soundManager->playAudio(footstep));

    while(!glfwWindowShouldClose(win))
    {
        fpsCounter.calculateFramesPerSec();
        std::cout << "FPS: " << fpsCounter.framesPerSecond << std::endl;
        
        /*Events*/
        eventManager.monitorEvents();
        keyCapture(eventManager.keyString);

        /*Light*/
        light = std::move(lightBuilder->initialiseLight(light));

		/*Camera*/
        if( camera->projectionLocation >= 0 )
        {
            camera = std::move(cameraBuilder->loadCamera(camera));
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
        };

        /*bricks*/
        if( bricks->modelviewUniformLocation >= 0)
        {
            bricks = std::move(bricksBuilder->initialiseMesh(bricks));

            bricks = std::move(bricksBuilder->loadMesh(bricks));
            bricks = std::move(bricksBuilder->drawMesh(bricks));
            
            bricks = transformer.translateMeshAsset(bricks, (moveX / 50), 0.0, (moveZ / 50));
            bricks = transformer.rotateMeshAsset(bricks, turnX, turnY, 0.0);

            soundManager->updateListenerLocation(bricks->locationX, bricks->locationY, bricks->locationZ);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*tiles*/
        if( tiles->modelviewUniformLocation >= 0)
        {
            tiles = std::move(tilesBuilder->initialiseMesh(tiles));

            tiles = std::move(tilesBuilder->loadMesh(tiles));
            tiles = std::move(tilesBuilder->drawMesh(tiles));

        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*world*/
        if( world->modelviewUniformLocation >= 0)
        {
            world = std::move(worldBuilder->initialiseMesh(world));

            world = std::move(worldBuilder->loadMesh(world));
            world = std::move(worldBuilder->drawMesh(world));
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };
        
		windowBuilder->handleBuffers();
    };
   
    return 0;
};

void keyCapture(string key)
{
		if(key == "up")
		{
			moveZ = 0.5;
		}
		else if(key == "down")
		{
			moveZ = -0.5;
		}
		else if(key == "left")
		{
			moveX = 0.5;
		}
		else if(key == "right")
		{
			moveX = -0.5;
		}
		else if(key == "w")
		{
			turnX = -0.5;
		}
		else if(key == "s")
		{
			turnX = 0.5;
		}
		else if(key == "a")
		{
			turnY = -0.5;
		}
		else if(key == "d")
		{
			turnY = 0.5;
		}
		else 
		{
			moveX = 0.0;
			moveZ = 0.0;
			turnX = 0.0;
			turnY = 0.0;
		};
};
