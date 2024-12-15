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
#ifndef LAZARUS_GL_INCLUDES_H
    #include "lz_gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
	#include "lz_constants.h"
#endif

#ifndef LAZARUS_GLOBALS_MANAGER_H
	#include "lz_globals_manager.h"
#endif

#include <iostream>
#include <memory>
#include <string>

#include "lz_texture_loader.h"
#include "lz_file_reader.h"

#ifndef LAZARUS_WORLD_FX_H
#define LAZARUS_WORLD_FX_H

class WorldFX 
{
    public:
        WorldFX();

        struct SkyBox
        {
            int textureId;
            GLuint VAO;
            GLuint VBO;

            //            +x    -x   +y   -y    +z     -z
            std::string right, left, up, down, front, back;

            std::vector<glm::vec3> attributes;
        };

        SkyBox createSkyBox(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath);
        void drawSkyBox(SkyBox sky);

        virtual ~WorldFX();

    private:
        void buildCube();
        void loadSkyMap(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath);

        SkyBox skyBox;

        std::unique_ptr<TextureLoader> textureLoader;
        std::unique_ptr<FileReader> imageLoader;

        FileReader::Image cubeMap[6];
};

#endif