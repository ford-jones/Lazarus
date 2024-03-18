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

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
#include <memory>

#include "../../textures/hdr/textureLoader.h"

using std::unique_ptr;
using std::vector;
using std::string;
using glm::vec3;
using glm::vec2;

#ifndef MATERIAL_LOADER_H
#define MATERIAL_LOADER_H

namespace fs = std::filesystem;

class MaterialLoader
{
    public:        
        MaterialLoader();
        bool loadMaterial(vector<vec3> &out, vector<vector<int>> data, string materialPath, string texturePath = "");
        virtual ~MaterialLoader();

    private:
    	unique_ptr<TextureLoader> textureLoader;
        vec3 diffuse;                                           //  Diffuse colour, the main / dominant colour of a face
        FILE *file;                                             //  The wavefront material file to be opened
        int diffuseTexCount;                                    //  The number of times an instance of `char[]="Kd"`(diffuse color) has appeared since the last invocation
};

#endif
