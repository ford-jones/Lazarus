#include "main.h"

int main()
{
	fileReader = std::make_unique<FileReader>();
	
   soundManager = std::make_unique<SoundManager>();
   soundManager->initialise();

    windowBuilder = std::make_unique<WindowManager>(800, 600, "Mom's Home!", nullptr, nullptr);
    windowBuilder->initialise();
	
    win = glfwGetCurrentContext();

    shaderProgram = shader.initialiseShader();
	
    windowBuilder->loadConfig(shaderProgram);									//  Use the newly created shader program

    lightBuilder        = std::make_unique<Light>(shaderProgram);
    light               = std::move(lightBuilder->createAmbientLight(0.0, 0.1, 0.0, 1.0, 1.0, 1.0));
    
    cameraBuilder       = std::make_unique<Camera>(shaderProgram);
    camera              = std::move(cameraBuilder->createFixedCamera(800, 600, 0.0, 1.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0));

    hallwayBuilder        = std::make_unique<Mesh>(shaderProgram);
    hallway               = std::move(hallwayBuilder->createTriangulatedMesh("assets/mesh/hallway.obj", "assets/material/hallway.mtl"));

   footstep = std::move(soundManager->createAudio("assets/sound/footsteps.mp3", true, -1));
   footstep = std::move(soundManager->loadAudio(footstep));
   soundManager->positionListener(0.0f, 0.0f, 0.0f);
	
    while(!glfwWindowShouldClose(win))
    {
        eventManager.monitorEvents();
        // keyCapture(eventManager.keyString);

		/*Camera*/
        if( camera->projectionLocation >= 0 )
        {
            light = std::move(lightBuilder->initialiseLight(light));
            
            //  The POSITIVE Z axis of a mesh is determined as the OPPOSITE direction which the camera is facing
            //  In other words; the POSITIVE Z axis scale for a mesh is strictly equal to the NEGATIVE Z axis scale for the camera
            //  OpenGL uses a Right-handed system

            camera = transformer.rotateCameraAsset(camera, -turnX, -turnY, 0.0);
            camera = transformer.translateCameraAsset(camera, (-moveX / 50), 0.0, (-moveZ / 50));

            camera = std::move(cameraBuilder->loadCamera(camera));

            soundManager->positionSource(footstep, camera->locationX, camera->locationY, camera->locationZ);
            // if(footstep->isPaused == true)
            // {
            //     footstep = std::move(soundManager->togglePaused(footstep));
            // }
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::PROJECTION" << RESET_TEXT << std::endl;
        };

        /*hallway*/
        if( hallway->modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
        {
            hallway = hallwayBuilder->initialiseMesh(hallway);
            
            hallwayBuilder->loadMesh(hallway);
            hallwayBuilder->drawMesh(hallway);
        }
        else
        {
            std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
        };

        if(eventManager.keyString == "up")
		{
			moveZ = 1;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "down")
		{
			moveZ = -1;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "left")
		{
			moveX = 1;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "right")
		{
			moveX = -1;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
        else if(eventManager.keyString == "w")
		{
			turnX += -0.5;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "s")
		{
			turnX += 0.5;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "a")
		{
			turnY += -0.5;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else if(eventManager.keyString == "d")
		{
			turnY += 0.5;
            if(footstep->isPaused == true)
            {
                footstep = std::move(soundManager->play(footstep));
            }
		}
		else 
		{
			moveX = 0.0;
			moveZ = 0.0;
			turnX = 0.0;
			turnY = 0.0;
            footstep = std::move(soundManager->pause(footstep));
		};
        
		windowBuilder->handleBuffers();
    };
   
    return 0;
};

void keyCapture(string key)
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
		else 
		{
			moveX = 0.0;
			moveZ = 0.0;
			turnX = 0.0;
			turnY = 0.0;
		};
};
