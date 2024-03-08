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
#include <filesystem>
#include <cstring>
#include <stdarg.h>
#include <string.h>

#include "../../utils/hdr/fileReader.h"
#include "../../materials/hdr/materialLoader.h"

using std::unique_ptr;
using std::vector;
using std::string;
using glm::vec3;
using glm::vec2;

namespace fs = std::filesystem;

#ifndef MESH_LOADER_H
#define MESH_LOADER_H

class MeshLoader 
{
    public:
        FILE *file;                                                                                             //  A file returned from the absolute path

        vector<unsigned int> vertexIndices, uvIndices, normalIndices;                                           //  Vector containing matched index positions
        vector<vec3> temp_vertices;                                                                             //  Temporary buffer for storing each set of 3 corresponding vertex indexes
        vector<vec2> temp_uvs;                                                                                  //  Temporary buffer for storing each set of 3 corresponding uv indexes
        vector<vec3> temp_normals;                                                                              //  Temporary buffer for storing each set of 3 corresponding normal indexes
        vector<vec3> temp_diffuse;

        string foundMaterial;
    	
    	MeshLoader();	
    	    
        bool loadMesh(
            const char *path,                                                                                       //  The absolute path to the file readers target
            vector<vec3> &out_vertices,                                                                             //  Location of the loaders vertices vector output
            vector<vec2> &out_uvs,                                                                                  //  Location of the loaders uv vector output
            vector<vec3> &out_normals,                                                                               //  Location of the loaders face vector output
            vector<vec3> &out_diffuse
        );

    private:
        //string filenameString;  
        int materialIdentifierIndex;
        int triangleCount;
        int res;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];                            //  Arrays to store Vertex, UV and normal index positions. Used to match respective v,vt,vn coordinates for each point in the mesh
        int matches;
        vec3 vertex;                                                                                            //  Vertex (singular mesh point) x,y,z vector
        vec2 uv;                                                                                                //  Vertex texture (UV) x,y vector
        vec3 normal;                                                                                            //  Vertex normals (direction) x,y,z vector

        char* matFn;
		//MaterialLoader *matFinder;
		unique_ptr<FileReader> matFinder;
		MaterialLoader *matLoader;
};

#endif
