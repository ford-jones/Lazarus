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
#ifndef LAZARUS_GL_INCLUDES_H
    #include "gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
	#include "constants.h"
#endif

#ifndef LAZARUS_GLOBALS_MANAGER_H
    #include "globalsManager.h"
#endif

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

#include "fileReader.h"
#include "materialLoader.h"

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
        vector<vec3> tempVertexPositions;
        vector<vec2> tempUvs;
        vector<vec3> tempNormals;
        vector<vec3> tempDiffuse;

        string foundMaterial;
    	
    	MeshLoader();	
    	    
        bool parseWavefrontObj(
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
        vector<string> splitTokensFromLine(const char *wavefrontData, char delim);
        void interleaveBufferData(vector<vec3> &outAttributes, vector<vec3> &outDiffuse, int numOfAttributes);
        void constructTriangle();

        vector<string> coordinates;

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

        GlobalsManager globals;
};

#endif
