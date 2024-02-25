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
#ifndef __GLEW_H
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/meshLoader.h"

string MeshLoader::findMesh(string filepath) 
{
    this->filenameString      =   fs::absolute(filepath).string();                                              //  Find the absolute path from root (/) to the mesh asset and convert to std::string

    this->fileVec.push_back(this->filenameString);                                                                     //  Push the absolute path into a temporary storage buffer
    return this->filenameString;                                         //  Return the absolute path to the asset, exit the thread
};

bool MeshLoader::loadMesh(const char* path, vector<vec3> &out_vertices, vector<vec2> &out_uvs, vector<vec3> &out_normals, vector<vec3> &out_diffuse) 
{
    this->materialIdentifierIndex = 0;
    this->triangleCount = 0;
    this->file = fopen(path, "r");                                                                    //  Open the file located at `path` with read permissions
    char identifier[128];                                                                       //  Store for the first string of each line from the loaded file

    if( this->file == NULL )
    {                                                                                           //  If, the file has a null value                                 
        return false;                                                                           //  Return from the function, exit the thread
    }

    while( 1 )
    {                                                                                           //  Start loader loop
        this->matFinder   =   new MaterialLoader;
        this->matLoader   =   new MaterialLoader;
        this->res = fscanf(file, "%s", identifier);                                               //  initialise the file scanner

        if (this->res == EOF)                                                                         //  If, the scanner has reached the end of the file
        {
            matLoader->loadMaterial(foundMaterial, out_diffuse, triangleCount, materialIdentifierIndex);      //  Call the material loader once more to pass in the final face / mtl count
            delete[] matFn;                                                                     //  Free allocated memory
            delete matFinder;
            delete matLoader;
            break;                                                                              //  Break out of the loop.
        }

        if( strcmp( identifier, "mtllib" ) == 0 )                                               //  If the first string of the current line is "mtlib" the line holds the name of a valid wavefront material file
        {
            this->matFn       =   new char[20];                                                       //  Create an identifier to store a char[]
            fscanf(this->file, "%s\n", this->matFn);                                                        //  Continue reading the line, the next store the string containing the name of the file
            
            this->foundMaterial = matFinder->findMaterial(this->matFn);                                     //  Find the file using the file finder
        }

        else if ( strcmp( identifier, "v" ) == 0 )                                              //  If the first string of the current line is "v" the line holds a set of vertex coordinates
        {
            fscanf(this->file, "%f %f %f\n", &this->vertex.x, &this->vertex.y, &this->vertex.z );                       //  Continue reading the line, the next 3 strings are mapped to a vertex object in order of x,y,z
            this->temp_vertices.push_back(this->vertex);                                                    //  Push the aforementioned object into the temporary vertices vector
        } 

        else if ( strcmp( identifier, "vt" ) == 0 )                                             //  If the first string of the current line is "vt" the line holds a set of vertex textures (uv) coordinates
        {
            fscanf(this->file, "%f %f\n", &this->uv.x, &this->uv.y );                                             //  Contine reading the line, the next 2 strings are mapped to a uv object in order of x,y
            this->temp_uvs.push_back(this->uv);                                                             //  Push the aforementioned object into the temporary uv vector
        }

        else if ( strcmp( identifier, "vn" ) == 0 )                                             //  If the first string of the current line is "vn" the line holds a set of normal coordinates
        {
            fscanf(this->file, "%f %f %f\n", &this->normal.x, &this->normal.y, &this->normal.z );                       //  Continue reading the line, the next 3 strings are mapped to a normal object in order of x,y,z
            this->temp_normals.push_back(this->normal);                                                     //  Push the aforementioned object into the temporary normal vector
        }

        else if ( strcmp( identifier, "f" ) == 0 )                                              //  If the first string of the current line is "f", the data describes which 3 vertexes build a face
        {                                                                                       //  (Each face is triangulated on export and so is comprised of 3 vertexes)
            this->triangleCount += 1;
            this->matches = fscanf
            (
                this->file, 
                "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                &this->vertexIndex[0], 
                &this->uvIndex[0], 
                &this->normalIndex[0], 
                &this->vertexIndex[1], 
                &this->uvIndex[1], 
                &this->normalIndex[1], 
                &this->vertexIndex[2], 
                &this->uvIndex[2], 
                &this->normalIndex[2] 
            );

            if ( this->matches != 9 )                                                                 //  If there arent 9 matches for each face, the mesh likely hasn't been triangulated
            {
                printf("File can't be read. Try exporting with other options\n");
                return false;
            }

            this->vertexIndices.push_back(this->vertexIndex[0]);                                            //  Push each matches index position back to its respective vector's memory location
            this->vertexIndices.push_back(this->vertexIndex[1]);                                            //  Each of these vectors contain index positions relative to the output data vectors below
            this->vertexIndices.push_back(this->vertexIndex[2]);
            this->uvIndices    .push_back(this->uvIndex[0]);
            this->uvIndices    .push_back(this->uvIndex[1]);
            this->uvIndices    .push_back(this->uvIndex[2]);
            this->normalIndices.push_back(this->normalIndex[0]);
            this->normalIndices.push_back(this->normalIndex[1]);
            this->normalIndices.push_back(this->normalIndex[2]);

        }
        else if( strcmp( identifier, "usemtl" ) == 0 )                                                          //  If the first string of the current line is "usemtl", the following string identifies the use of a new material for following faces
        {
            matLoader->loadMaterial(foundMaterial, out_diffuse, triangleCount, materialIdentifierIndex);        //  Call the material loader function

            this->materialIdentifierIndex += 1;                                                                       //  Increase the material identification number by 1
            this->triangleCount = 0;                                                                                  //  Reset the triangle count to 0 for the next read
        }
    }
    for( unsigned int i = 0; i < this->vertexIndices.size(); i++ )                                //  Loop through the vertex match index position array
    {
        unsigned int vertexIndex    =   vertexIndices[i];                                   //  The index position of each item in the array of matched indexes
        vec3 vertex                 =   temp_vertices[vertexIndex - 1];                     //  Each vertex found at corresponding matched index

        out_vertices.push_back(vertex);                                                     //  Push the found vertex into the output vector
    }

    for( unsigned int i = 0; i < this->uvIndices.size(); i++ )                                    //  Loop through the UV match index position array
    {
        unsigned int uvIndex        =   uvIndices[i];                                       //  The index position of each item in the array of matched indexes
        vec2 uv                     =   temp_uvs[uvIndex - 1];                              //  Each UV found at the corresponding matched index

        out_uvs.push_back(uv);                                                              //  Push the found UV into the output vector
    }

    for( unsigned int i = 0; i < this->normalIndices.size(); i++ )                                //  Loop through the Normal match index position array
    {
        unsigned int normalIndex    =   normalIndices[i];                                   //  The index position of each item in the array of matched indexes
        vec3 normal                 =   temp_normals[normalIndex - 1];                      //  Each Normal found at the corresponding matched index

        out_normals.push_back(normal);                                                      //  Push the found Normal into the output vector
    }

    // this->prepareBufferData(this->vertexIndices, out_vertices, this->temp_vertices);
    // this->prepareBufferData(this->uvIndices, out_uvs, this->temp_uvs);
    // this->prepareBufferData(this->normalIndices, out_normals, this->temp_normals);

    fclose(this->file);                                                                           //  Close the file
};

	
// void MeshLoader::parseWavefrontObj()
// {
	
// };

// void MeshLoader::prepareBufferData(vector<unsigned int> indexVec, vector<vec3> outVec, vector<vec3> tempVec)
// {
// 	for( unsigned int i = 0; i < indexVec.size(); i++ )
// 	{
// 		unsigned int index = indexVec[i];
// 		vec3 vertexData = tempVec[index - 1];
		
// 		outVec.push_back(vertexData);
// 	};
// };