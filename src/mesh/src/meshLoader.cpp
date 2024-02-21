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

#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <filesystem>
#include "../hdr/meshLoader.h"

#include "glm/glm.hpp"

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

using std::vector;
using std::string;
using glm::vec3;
using glm::vec2;

namespace fs = std::filesystem;


string MeshLoader::findMesh(string filepath) 
{
    string fns      =   fs::absolute(filepath).string();                                              //  Find the absolute path from root (/) to the mesh asset and convert to std::string

    fileVec.push_back(fns);                                                                     //  Push the absolute path into a temporary storage buffer
    return fns;                                                                                 //  Return the absolute path to the asset, exit the thread
};

bool MeshLoader::loadMesh(const char* path, vector<vec3> &out_vertices, vector<vec2> &out_uvs, vector<vec3> &out_normals, vector<vec3> &out_diffuse) 
{
    int materialIdentifierIndex = 0;
    int triangleCount = 0;
    file = fopen(path, "r");                                                                    //  Open the file located at `path` with read permissions
    char identifier[128];                                                                       //  Store for the first string of each line from the loaded file

    if( file == NULL )
    {                                                                                           //  If, the file has a null value                                 
        return false;                                                                           //  Return from the function, exit the thread
    }

    while( 1 )
    {                                                                                           //  Start loader loop
        matFinder   =   new MaterialLoader;
        matLoader   =   new MaterialLoader;
        int res = fscanf(file, "%s", identifier);                                               //  initialise the file scanner

        if (res == EOF)                                                                         //  If, the scanner has reached the end of the file
        {
            matLoader->loadMaterial(foundMaterial, out_diffuse, triangleCount, materialIdentifierIndex);      //  Call the material loader once more to pass in the final face / mtl count
            delete[] matFn;                                                                     //  Free allocated memory
            delete matFinder;
            delete matLoader;
            break;                                                                              //  Break out of the loop.
        }

        if( strcmp( identifier, "mtllib" ) == 0 )                                               //  If the first string of the current line is "mtlib" the line holds the name of a valid wavefront material file
        {
            matFn       =   new char[20];                                                       //  Create an identifier to store a char[]
            fscanf(file, "%s\n", matFn);                                                        //  Continue reading the line, the next store the string containing the name of the file
            
            foundMaterial = matFinder->findMaterial(matFn);                                     //  Find the file using the file finder
        }

        else if ( strcmp( identifier, "v" ) == 0 )                                              //  If the first string of the current line is "v" the line holds a set of vertex coordinates
        {
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );                       //  Continue reading the line, the next 3 strings are mapped to a vertex object in order of x,y,z
            temp_vertices.push_back(vertex);                                                    //  Push the aforementioned object into the temporary vertices vector
        } 

        else if ( strcmp( identifier, "vt" ) == 0 )                                             //  If the first string of the current line is "vt" the line holds a set of vertex textures (uv) coordinates
        {
            fscanf(file, "%f %f\n", &uv.x, &uv.y );                                             //  Contine reading the line, the next 2 strings are mapped to a uv object in order of x,y
            temp_uvs.push_back(uv);                                                             //  Push the aforementioned object into the temporary uv vector
        }

        else if ( strcmp( identifier, "vn" ) == 0 )                                             //  If the first string of the current line is "vn" the line holds a set of normal coordinates
        {
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );                       //  Continue reading the line, the next 3 strings are mapped to a normal object in order of x,y,z
            temp_normals.push_back(normal);                                                     //  Push the aforementioned object into the temporary normal vector
        }

        else if ( strcmp( identifier, "f" ) == 0 )                                              //  If the first string of the current line is "f", the data describes which 3 vertexes build a face
        {                                                                                       //  (Each face is triangulated on export and so is comprised of 3 vertexes)
            triangleCount += 1;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];                            //  Arrays to store Vertex, UV and normal index positions. Used to match respective v,vt,vn coordinates for each point in the mesh
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

            if ( matches != 9 )                                                                 //  If there arent 9 matches for each face, the mesh likely hasn't been triangulated
            {
                printf("File can't be read. Try exporting with other options\n");
                return false;
            }

            vertexIndices.push_back(vertexIndex[0]);                                            //  Push each matches index position back to its respective vector's memory location
            vertexIndices.push_back(vertexIndex[1]);                                            //  Each of these vectors contain index positions relative to the output data vectors below
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

        }
        else if( strcmp( identifier, "usemtl" ) == 0 )                                                          //  If the first string of the current line is "usemtl", the following string identifies the use of a new material for following faces
        {
            matLoader->loadMaterial(foundMaterial, out_diffuse, triangleCount, materialIdentifierIndex);        //  Call the material loader function

            materialIdentifierIndex += 1;                                                                       //  Increase the material identification number by 1
            triangleCount = 0;                                                                                  //  Reset the triangle count to 0 for the next read
        }
    }
    for( unsigned int i = 0; i < vertexIndices.size(); i++ )                                //  Loop through the vertex match index position array
    {
        unsigned int vertexIndex    =   vertexIndices[i];                                   //  The index position of each item in the array of matched indexes
        vec3 vertex                 =   temp_vertices[vertexIndex - 1];                     //  Each vertex found at corresponding matched index

        out_vertices.push_back(vertex);                                                     //  Push the found vertex into the output vector
    }

    for( unsigned int i = 0; i < uvIndices.size(); i++ )                                    //  Loop through the UV match index position array
    {
        unsigned int uvIndex        =   uvIndices[i];                                       //  The index position of each item in the array of matched indexes
        vec2 uv                     =   temp_uvs[uvIndex - 1];                              //  Each UV found at the corresponding matched index

        out_uvs.push_back(uv);                                                              //  Push the found UV into the output vector
    }

    for( unsigned int i = 0; i < normalIndices.size(); i++ )                                //  Loop through the Normal match index position array
    {
        unsigned int normalIndex    =   normalIndices[i];                                   //  The index position of each item in the array of matched indexes
        vec3 normal                 =   temp_normals[normalIndex - 1];                      //  Each Normal found at the corresponding matched index

        out_normals.push_back(normal);                                                      //  Push the found Normal into the output vector
    }

    fclose(file);                                                                           //  Close the file
}