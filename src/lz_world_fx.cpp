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

#include "lz_world_fx.h"

WorldFX::WorldFX()
{
    //  Defaults etc
};

WorldFX::SkyBox WorldFX::createSkyBox(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath)
{
    //  Create and bind vertex objects
    //  Call private members to load / create stuff
    //  Construct this->skyBox
};

void WorldFX::drawSkyBox(WorldFX::SkyBox sky)
{
    //  Set slot / Bind texture
    //  Set uniform values (add uniform stuff to skybox struct too)
    //  Draw arrays
};

void WorldFX::buildCube()
{
    //  Basically hardcode vertex attributes and anything else that might entail
};

void WorldFX::loadSkyMap(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath)
{
    //  Do texture loading (i.e. parse filepaths / allocate tex storage / load to store)
    //  Texture id handover to skybox struct
};

WorldFX::~WorldFX()
{
    //  Cleanup etc
};