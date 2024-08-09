//                ((.     (.    ,                                                                          */*  ,%##%%%%%%%%%%%%%%%#(*           .      
//              .,                                                                                                          .(*      ,*,                
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
#include <memory>
#include <fstream>
#include <sstream>

#include "../../utils/hdr/fileReader.h"
#include "../../materials/hdr/materialLoader.h"

using std::unique_ptr;
using std::vector;
using std::string;
using glm::vec3;
using glm::vec2;
using std::ifstream;
using std::stringstream;

#ifndef MESH_LOADER_H
#define MESH_LOADER_H

class MeshLoader 
{
    public:
        ifstream file;

        vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        vector<vec3> temp_vertices;
        vector<vec2> temp_uvs;
        vector<vec3> temp_normals;
        vector<vec3> temp_diffuse;

        string foundMaterial;
    	
    	MeshLoader();	
    	    
        bool loadMesh(
            vector<vec3> &outAttributes,
            vector<vec3> &outDiffuse,
            GLuint &outTextureId,
            FileReader::Image &imageData,
            const char *meshPath,
            const char *materialPath,
            const char *texturePath = ""
        );
        
        virtual ~MeshLoader();

    private:
        vector<string> vectorizeWfProperties(const char *wavefrontData, char delim);

        vector<vector<int>> materialBuffer;
        vector<int> materialData;
        int materialIdentifierIndex;
        int triangleCount;
        
        char currentLine[256];
        vector<string> attributeIndexes;
        
        vec3 vertex;
        vec2 uv;
        vec3 normal;

		unique_ptr<FileReader> matFinder;
		unique_ptr<MaterialLoader> matLoader;
};

#endif
