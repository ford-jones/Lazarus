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

    skullBuilder       = std::make_unique<Mesh>(shaderProgram);
    skull              = std::move(skullBuilder->createTriangulatedMesh("assets/mesh/skull.obj", "assets/material/skull.mtl", "assets/images/skull.png"));

    floorsBuilder        = std::make_unique<Mesh>(shaderProgram);
    floors               = std::move(floorsBuilder->createTriangulatedMesh("assets/mesh/floors.obj", "assets/material/floors.mtl", "assets/images/floors.png"));

    wallsBuilder        = std::make_unique<Mesh>(shaderProgram);
    walls               = std::move(wallsBuilder->createTriangulatedMesh("assets/mesh/walls.obj", "assets/material/walls.mtl", "assets/images/walls.png"));

    swordBuilder        = std::make_unique<Mesh>(shaderProgram);
    sword               = std::move(swordBuilder->createTriangulatedMesh("assets/mesh/sword.obj", "assets/material/sword.mtl"));
    sword = transformer.translateMeshAsset(sword, 0.0, 1.0, 0.0);
    sword = transformer.translateMeshAsset(sword, 0.0, 0.0, 3.0);

    springWaltz = std::move(soundManager->createAudio("assets/sound/springWaltz.mp3", true, 0));
    springWaltz = std::move(soundManager->loadAudio(springWaltz));
    springWaltz = std::move(soundManager->playAudio(springWaltz));

    footstep = std::move(soundManager->createAudio("assets/sound/footsteps.mp3", true, 0));
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

            camera = transformer.translateCameraAsset(camera, (moveX / 10), 0.0, (moveZ / 10));
            camera = transformer.rotateCameraAsset(camera, turnX, turnY, 0.0);

            soundManager->updateListenerLocation(camera->locationX, camera->locationY, camera->locationZ);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
        };

        /*skull*/
        if( skull->modelviewUniformLocation >= 0)
        {
            skull = std::move(skullBuilder->initialiseMesh(skull));

            skull = std::move(skullBuilder->loadMesh(skull));
            skull = std::move(skullBuilder->drawMesh(skull));
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*sword*/
        if( sword->modelviewUniformLocation >= 0)
        {
            sword = std::move(swordBuilder->initialiseMesh(sword));

            sword = std::move(swordBuilder->loadMesh(sword));
            sword = std::move(swordBuilder->drawMesh(sword));

            sword = transformer.translateMeshAsset(sword, (0.5 / 10), 0.0, 0.0);
            // sword = transformer.translateMeshAsset(sword, 0.0, 0.0, 0.0);
            sword = transformer.rotateMeshAsset(sword, 0.0, 1.0, 0.0);

            // soundManager->updateListenerLocation(skull->locationX, skull->locationY, skull->locationZ);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*floors*/
        if( floors->modelviewUniformLocation >= 0)
        {
            floors = std::move(floorsBuilder->initialiseMesh(floors));

            floors = std::move(floorsBuilder->loadMesh(floors));
            floors = std::move(floorsBuilder->drawMesh(floors));

        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        /*walls*/
        if( walls->modelviewUniformLocation >= 0)
        {
            walls = std::move(wallsBuilder->initialiseMesh(walls));

            walls = std::move(wallsBuilder->loadMesh(walls));
            walls = std::move(wallsBuilder->drawMesh(walls));
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
			moveX = -0.5;
		}
		else if(key == "right")
		{
			moveX = 0.5;
		}
		else if(key == "w")
		{
			turnX += -1.0;
		}
		else if(key == "s")
		{
			turnX += 1.0;
		}
		else if(key == "a")
		{
			turnY += -1.0;
		}
		else if(key == "d")
		{
			turnY += 1.0;
		}
		else 
		{
			moveX = 0.0;
			moveZ = 0.0;
			// turnX = 0.0;
			// turnY = 0.0;
		};
};
