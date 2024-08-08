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

        vector<unsigned int> vertexIndices, uvIndices, normalIndices;                                           //  Vector containing matched index positions
        vector<vec3> temp_vertices;                                                                             //  Temporary buffer for storing each set of 3 corresponding vertex indexes
        vector<vec2> temp_uvs;                                                                                  //  Temporary buffer for storing each set of 3 corresponding uv indexes
        vector<vec3> temp_normals;                                                                              //  Temporary buffer for storing each set of 3 corresponding normal indexes
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
        
        vec3 vertex;                                                                                            //  Vertex (singular mesh point) x,y,z vector
        vec2 uv;                                                                                                //  Vertex texture (UV) x,y vector
        vec3 normal;                                                                                            //  Vertex normals (direction) x,y,z vector

		unique_ptr<FileReader> matFinder;
		unique_ptr<MaterialLoader> matLoader;
};

#endif
