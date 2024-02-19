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

#include "../hdr/meshLoader.h"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

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
            //  add material count
            const char* filepath;

            vector<vec3> vertices;                                                              //  Buffer to store vertex data
            GLuint modelviewUniformLocation;                                                                        //  The location / index of the modelview matrix inside the vert shader program
            mat4 modelviewMatrix;                                                                                    //  A modelview matrix matrice passed into the shader program as a uniform
        };

        //  Enables a new VAO, binds it to the GLContext, loads vertex data into VBO's and creates a matrice
        TriangulatedMesh createTriangulatedMesh(GLuint shader, string filepath);

        //  Passes the modelview-matrice into the shader program at the appropriate uniform index position
        void instantiateMesh(TriangulatedMesh meshData);
        void drawMesh(TriangulatedMesh meshData);
        virtual ~Mesh();

    private:
        int errorCode;
        vector<vec3> vertices;                                                              //  Buffer to store vertex data
        vector<vec2> uvs;                                                                   //  Buffer to uv data
        vector<vec3> normals;                                                               //  Buffer to store normals data
        vector<vec3> diffuse;                                                               //  Buffer to store diffusion color data

        GLuint VAO;                                                                         //  The OpenGL Vertex Array Object
        GLuint VBO[3];                                                                      //  The OpenGL Vertex Buffer Object

        MeshLoader *finder;
        MeshLoader *loader;
        TriangulatedMesh triangulatedMesh;

};

#endif