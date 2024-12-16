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
#include "lz_mesh.h"

#ifndef LAZARUS_WORLD_FX_H
#define LAZARUS_WORLD_FX_H

class WorldFX 
{
    public:
        WorldFX(GLuint shaderProgram);

        struct SkyBox
        {
            // +x -x +y -y +z -z

            std::vector<std::string> paths;
            std::vector<FileReader::Image> cubeMap;

            MeshManager::Mesh cube;
        };

        SkyBox createSkyBox(std::string rightPath, std::string leftPath, std::string upPath, std::string downPath, std::string frontPath, std::string backPath);
        void drawSkyBox(SkyBox sky);

        virtual ~WorldFX();

    private:
        void loadSkyMap();

        SkyBox skyBox;

        std::unique_ptr<MeshManager> meshLoader;
        std::unique_ptr<FileReader> imageLoader;
        std::unique_ptr<TextureLoader> textureLoader;

        GlobalsManager globals;

        GLuint shader;
};

#endif