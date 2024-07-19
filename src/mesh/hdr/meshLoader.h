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
            const char *meshPath,
            const char *materialPath,
            vector<vec3> &out_vertices,                                                                             //  Location of the loaders vertices vector output
            vector<vec2> &out_uvs,                                                                                  //  Location of the loaders uv vector output
            vector<vec3> &out_normals,                                                                               //  Location of the loaders face vector output
            vector<vec3> &out_diffuse
        );
        
        virtual ~MeshLoader();

    private:
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
