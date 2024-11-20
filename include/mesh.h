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
            GLuint VAO;                                                                         //  The OpenGL Vertex Array Object
            GLuint VBO;
            GLuint textureId;

            int numOfVertices;
            int numOfFaces;
            /* ===============================
            	TODO | Things to add:
                - Material count
                - VBO & VAO (persisted)
            ================================== */
            
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

            GLint modelviewUniformLocation;                                                                        //  The location / index of the modelview matrix inside the vert shader program
            GLint samplerUniformLocation;
            GLint textureLayerUniformLocation;
            GLint is3DUniformLocation;
            GLint isGlyphUniformLocation;

            int is3D;
            int isGlyph;

            int textureUnit;
        };
		
		Mesh(GLuint shader);
		
        TriangulatedMesh create3DAsset(string meshPath, string materialPath, string texturePath = "");
        TriangulatedMesh createQuad(float width, float height, string texturePath = "", float uvXL = 0.0, float uvXR = 0.0, float uvY = 0.0);

        void loadMesh(TriangulatedMesh &meshData);
        void drawMesh(TriangulatedMesh &meshData);

        virtual ~Mesh();

    private:
        void resolveFilepaths(TriangulatedMesh &asset, string texPath = "", string mtlPath = "", string objPath = "");
        void setInherentProperties(TriangulatedMesh &asset);
        void lookupUniforms(TriangulatedMesh &asset);
        void initialiseMesh(TriangulatedMesh &meshData);
        
        void checkErrors(const char *invoker);

        int errorCode;

        GLuint xyzTextureId;
        GLuint xyTextureId;

		GLuint shaderProgram;

        unique_ptr<FileReader> finder;
        unique_ptr<MeshLoader> meshLoader;
        unique_ptr<TextureLoader> texLoader;
        
        TriangulatedMesh mesh;
        vector<TriangulatedMesh> meshStore;

        GlobalsManager globals;

};

#endif