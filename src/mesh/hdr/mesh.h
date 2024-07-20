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
            int numOfVertices;
            int numOfFaces;
            //	TODO:
            //  add material count
            
            string meshFilepath;
            string materialFilepath;
            string textureFilepath;

            //  TODO:
            //  Order faces into indices array for EBO

            float locationX;
            float locationY;
            float locationZ;

            vector<unsigned int> indices;
            vector<vec3> attributes;
            vector<vec3> vertices;                                                              //  Buffer to store vertex data
            vector<vec2> uvCoords;																//  Buffer to store UV data
            vector<vec3> normals;                                                               //  Buffer to store normals data
            vector<vec3> diffuse;                                                               //  Buffer to store diffusion color data
            GLuint modelviewUniformLocation;                                                                        //  The location / index of the modelview matrix inside the vert shader program
            mat4 modelviewMatrix;                                                                                    //  A modelview matrix matrice passed into the shader program as a uniform
            GLint samplerUniformLocation;
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

        vector<vec3> outAttributes;
        vector<vec3> vertices;                                                              //  Buffer to store vertex data
        vector<vec2> uvs;                                                                   //  Buffer to uv data
        vector<vec3> normals;                                                               //  Buffer to store normals data
        vector<vec3> diffuse;                                                               //  Buffer to store diffusion color data

        vector<unsigned int> indices;
		
		GLuint shaderProgram;
        GLuint VAO;                                                                         //  The OpenGL Vertex Array Object
        // GLuint VBO[4];                                                                      //  The OpenGL Vertex Buffer Object
        GLuint VBO;
        GLuint EBO;

        unique_ptr<FileReader> finder;
        unique_ptr<MeshLoader> loader;
        
        shared_ptr<TriangulatedMesh> triangulatedMesh;

};

#endif
