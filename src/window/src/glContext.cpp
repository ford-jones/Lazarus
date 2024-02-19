//              .,                                                                                                          .(*      ,*,                
//                ((.     (.    ,                                                                          */*  ,%##%%%%%%%%%%%%%%%#(*           .      
//         .//**/#%%%%%%%%%%%%%%#*   .,                                                             ,**   .(%%%%%%#(******,***,/#%%%%%%%%###(/,         
//             #%%%#*.#%/***,,..,*(%(.    ,,                                                     *     /#%##/*****,,,,,,,,,.,...,,#%,  .#%#.            
//    .,     *%&#/   %#**,,*..,....,.*#,     ..                                               *     ,%#%#/*,,*,*,,,,,.,.,,.,...,...((     /#(//*/**.    
//           (%#    *#*...,.,,..........*/      ,                                          .      *#%(#(**,,,,,,,,..,..,..,,........(.     *#(          
//           *#     *(......,.............(#      ,                                       .     ,((, ##,,,.....,.................. ./       **  .,.     
//            *     ./........ ...........*#*,                                          ,      ,(,  ./*,,,..,,.................  .. *                   
//                   /, ........    ... ../(  *.                                              ,*     /,...,,.,,.....   ............**                   
//                    *... .............  /    ,                                             *,      ,*,,............  ,....     ...                    
//                     *.   ..... .... ..*                                                  .*        *...................   .  ...                     
//               *       ... ......... ,.                                                   ,          ... ..........  ...     ..       ,               
//                ((        .,.,.. ...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.      
/*  LAZARUS ENGINE */

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/glContext.h"

// #if !wxUSE_GLCANVAS
//     #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
// #endif

OpenGLContext::OpenGLContext()
{
    shader          =   new Shader;

    printf("Version OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Version GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    glewExperimental = GL_TRUE;                                                                                         //  Enable GLEW's experimental features
    glewInit();                                                                                                         //  Initialise GLEW graphics library

    shaderProgram = shader->initialiseShader();

    glEnable            (GL_CULL_FACE);                                                                                 //  Disable rendering of faces oposite to the viewport
    glEnable            (GL_TEXTURE_2D);                                                                                //  Enable 2 dimensional texture use in this context
    glEnable            (GL_DEPTH_TEST);                                                                                //  Run a depth test on each fragment, render frags in order of perspective rather than order drawn.

    glClearColor        (0.0, 0.0, 0.0, 1.0);                                                                           //  Set the background colour of the scene to black

    glClear             (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                                    //  Clear the depth and color buffers

    glUseProgram        (shaderProgram);                                                                                //  Use the newly created shader program
}

void OpenGLContext::Render(float xangle, float yangle) // Render loop, controlled by Wx
{
    lightBuilder        =   new Light;
    cameraBuilder       =   new Camera;
    cubeBuilder         =   new Mesh;
    houseBuilder        =   new Mesh;
    transformer         =   new Transform;

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

    //  cube
    cube = cubeBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/cube.obj");
    if( cube.modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
    {
        cubeBuilder->instantiateMesh(cube);
    }
    else
    {
        std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
    };
    cubeBuilder->drawMesh(cube);

    //  House
    house = houseBuilder->createTriangulatedMesh(shaderProgram, "assets/mesh/house.obj");
    if( house.modelviewUniformLocation >= 0)                                                                  //  If the locations are not -1
    {
        house = transformer->applyTranslation(house, (xangle / 50), 0.0f, (yangle / 50));
        houseBuilder->instantiateMesh(house);
    }
    else
    {
        std::cout << RED_TEXT << "ERROR::SHADER::VERT::MATRICE::MODELVIEW" << RESET_TEXT << std::endl;
    };
    houseBuilder->drawMesh(house);
}

OpenGLContext::~OpenGLContext()
{
    delete shader;//  Destroy allocated memory for this iteration of the rener loop and call the corresponding destructors
    // delete lightBuilder;
    // delete cameraBuilder;
    // delete cubeBuilder;
    // // delete houseBuilder;
    // delete transformer;
}

//  The scene used to be dynamic, any two meshes in the ./assets folder could be loaded into the scene at once
//  Deleting both __builder pointers causes segfault on launch
//  World wont load at all
//  Beachball will not load with house