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
#include <stdlib.h>
#include <memory>

#include "fileReader.h"
#include "meshLoader.h"
#include "textureLoader.h"

using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::vector;
using glm::mat4;
using glm::vec3;
using glm::vec2;

#ifndef LAZARUS_MESH_H
#define LAZARUS_MESH_H

class Mesh
{
    public:
        struct TriangulatedMesh
        {
            int textureId;

            int numOfVertices;
            int numOfFaces;
            //	TODO:
            //  add material count
            
            string meshFilepath;
            string materialFilepath;
            string textureFilepath;

            float locationX;
            float locationY;
            float locationZ;

            vector<vec3> attributes;
            vector<vec3> diffuse;                                                               //  Buffer to store diffusion color data

            FileReader::Image textureData;

            mat4 modelviewMatrix;                                                                                    //  A modelview matrix matrice passed into the shader program as a uniform

            GLuint modelviewUniformLocation;                                                                        //  The location / index of the modelview matrix inside the vert shader program
            GLint samplerUniformLocation;
            GLint textureLayerUniformLocation;
            GLint is3DUniformLocation;
            GLint isGlyphUniformLocation;

            int is3D;
            int isGlyph;
        };
		
		Mesh(GLuint shader);
		
        shared_ptr<TriangulatedMesh> create3DAsset(string meshPath, string materialPath, string texturePath = "");
        shared_ptr<TriangulatedMesh> createQuad(float width, float height, string texturePath = "");

        void initialiseMesh(shared_ptr<TriangulatedMesh> &meshData);
        void loadMesh(shared_ptr<TriangulatedMesh> &meshData);
        void drawMesh(shared_ptr<TriangulatedMesh> &meshData);

        virtual ~Mesh();

    private:
        void resolveFilepaths(shared_ptr<TriangulatedMesh> &asset, string texPath = "", string mtlPath = "", string objPath = "");
        void setInherentProperties(shared_ptr<TriangulatedMesh> &asset);
        void lookupUniforms(shared_ptr<TriangulatedMesh> &asset);
        void checkErrors(const char *invoker);
        void releaseMesh();

        int errorCode;

        vector<vec3> vertexAttributes;
        vector<vec3> diffuseColors;                                                               //  Buffer to store diffusion color data

        GLuint xyzTextureId;
        GLuint xyTextureId;

		GLuint shaderProgram;
        GLuint VAO;                                                                         //  The OpenGL Vertex Array Object
        GLuint VBO;

        unique_ptr<FileReader> finder;
        unique_ptr<MeshLoader> meshLoader;
        unique_ptr<TextureLoader> texLoader;
        
        shared_ptr<TriangulatedMesh> triangulatedMesh;
        shared_ptr<TriangulatedMesh> quad;

        GlobalsManager globals;

};

#endif