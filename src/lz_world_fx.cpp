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

#include "../include/lz_world_fx.h"

WorldFX::WorldFX(GLuint shaderProgram)
{
    std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
    this->shader = shaderProgram;

    this->meshLoader = std::make_unique<MeshManager>(this->shader);
    this->textureLoader = std::make_unique<TextureLoader>();
    this->imageLoader = nullptr;
    
    this->skyBox = {};
};

WorldFX::SkyBox WorldFX::createSkyBox(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath)
{
    this->skyBox.cube = meshLoader->createCube(10.0f);
    this->skyBox.paths = {rightPath, leftPath, upPath, downPath, frontPath, backPath};

    this->loadSkyMap();

    this->skyBox.cube.textureId = textureLoader->cubeMapTexture;
    this->skyBox.cube.textureFilepath = LAZARUS_MESH_ISSKYBOX;

    /* =================================================
        TODO:
            Do something about this.
    ==================================================== */
    this->skyBox.cube.textureLayer = 1;    
    this->skyBox.cube.textureData = {pixelData: NULL, height: 0, width: 0};

    return this->skyBox;
};

void WorldFX::drawSkyBox(WorldFX::SkyBox sky)
{
    glDepthMask(GL_FALSE);

    meshLoader->loadMesh(sky.cube);
    meshLoader->drawMesh(sky.cube);
    
    glDepthMask(GL_TRUE);
};

void WorldFX::loadSkyMap()
{
    this->imageLoader = std::make_unique<FileReader>();

    for(auto path: this->skyBox.paths)
    {
        std::string absolute = imageLoader->relativePathToAbsolute(path);
        FileReader::Image image = imageLoader->readFromImage(absolute);
        
        /* =======================================================
            Validate that the image inputs for the cubemap are 
            each of the same size.
        ========================================================== */
        if(this->skyBox.cubeMap.size() > 0 && (image.width != image.height || image.width != this->skyBox.cubeMap[0].width))
        {
            globals.setExecutionState(LAZARUS_INVALID_CUBEMAP);
        };
        
        this->skyBox.cubeMap.push_back(image);
    };

    textureLoader->storeCubeMap(this->skyBox.cubeMap[0].width, this->skyBox.cubeMap[0].height);
    textureLoader->loadCubeMap(this->skyBox.cubeMap);
};

WorldFX::~WorldFX()
{
    std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
};