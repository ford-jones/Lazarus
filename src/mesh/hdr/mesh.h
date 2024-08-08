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
#include <time.h>
#include <stdlib.h>
#include <memory>

#include "../../utils/hdr/fileReader.h"
#include "../hdr/meshLoader.h"
#include "../../textures/hdr/textureLoader.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

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
            int id;
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
        };
		
		Mesh(GLuint shader);
		
        //  Enables a new VAO, binds it to the GLContext, loads vertex data into VBO's and creates a matrice
        shared_ptr<TriangulatedMesh> createTriangulatedMesh(string meshPath, string materialPath, string texturePath = "");
        //  Passes the modelview-matrice into the shader program at the appropriate uniform index position
        shared_ptr<TriangulatedMesh> initialiseMesh(shared_ptr<TriangulatedMesh> meshData);
        void loadMesh(shared_ptr<TriangulatedMesh> meshData);
        void drawMesh(shared_ptr<TriangulatedMesh> meshData);
        virtual ~Mesh();

    private:
        void checkErrors(const char *invoker);
        void releaseMesh();

        int errorCode;

        vector<vec3> vertexAttributes;
        vector<vec3> diffuseColors;                                                               //  Buffer to store diffusion color data
        GLuint textureId;
		
        FileReader::Image texStore;

		GLuint shaderProgram;
        GLuint VAO;                                                                         //  The OpenGL Vertex Array Object
        GLuint VBO;

        unique_ptr<FileReader> finder;
        unique_ptr<MeshLoader> meshLoader;
        unique_ptr<TextureLoader> texLoader;
        
        shared_ptr<TriangulatedMesh> triangulatedMesh;

};

#endif
