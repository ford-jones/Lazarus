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
#ifndef LAZARUS_CONSTANTS_H
	#include "../../utils/hdr/constants.h"
#endif
    		
#ifndef LAZARUS_GL_INCLUDES_H
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/meshLoader.h"

MeshLoader::MeshLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'MeshLoader'." << RESET_TEXT << std::endl;
	this->materialIdentifierIndex	=	0;
	this->triangleCount				=	0;

	this->matFinder 				= 	nullptr;
	this->matLoader 				=	nullptr;
};

bool MeshLoader::loadMesh(vector<vec3> &out_vertices, vector<vec2> &out_uvs, vector<vec3> &out_normals, vector<vec3> &out_diffuse, vector<unsigned int> &out_indices, const char* meshPath, const char* materialPath, const char* texturePath) 
{
	this->matFinder = std::make_unique<FileReader>();
	this->matLoader = std::make_unique<MaterialLoader>();
	
    this->materialIdentifierIndex = 0;
    this->triangleCount = 0;

    file.open(meshPath);

    if( !file.is_open() )
    {
        return false;
    }

    while( file.getline(currentLine, 256) )
    {
        if( currentLine[0] == 'm' )                                               //  If the first string of the current line is "mtlib" the line holds the name of a valid wavefront material file
        {
            this->foundMaterial = matFinder->relativePathToAbsolute(materialPath);                                     //  Find the file using the file finder
        }

        else if ( (currentLine[0] == 'v') && (currentLine[1] == ' ') )                                              //  If the first string of the current line is "v" the line holds a set of vertex coordinates
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->vertex.x = stof(data[1]);
            this->vertex.y = stof(data[2]);
            this->vertex.z = stof(data[3]);

            this->temp_vertices.push_back(this->vertex);                                                    //  Push the aforementioned object into the temporary vertices vector
        } 

        else if ( (currentLine[0] == 'v') && currentLine[1] == 't' )                                             //  If the first string of the current line is "vt" the line holds a set of vertex textures (uv) coordinates
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->uv.x = stof(data[1]);
            this->uv.y = stof(data[2]);

            this->temp_uvs.push_back(this->uv);                                                             //  Push the aforementioned object into the temporary uv vector
        }

        else if ( (currentLine[0] == 'v') && currentLine[1] == 'n' )                                             //  If the first string of the current line is "vn" the line holds a set of normal coordinates
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->normal.x = stof(data[1]);
            this->normal.y = stof(data[2]);
            this->normal.z = stof(data[3]);

            this->temp_normals.push_back(this->normal);                                                     //  Push the aforementioned object into the temporary normal vector
        }

        else if ( currentLine[0] == 'f' )                                              //  If the first string of the current line is "f", the data describes which 3 vertexes build a face
        {                                                                                       //  (Each face is triangulated on export and so is comprised of 3 vertexes)
            this->triangleCount += 1;

            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            for(auto i: data) 
            {
                stringstream ssJ(i);
                string tokenJ;

                while(getline(ssJ, tokenJ, '/')) 
                {
                    if (tokenJ != "f") 
                    {
                        attributeIndexes.push_back(tokenJ);
                    }
                }
            }            

            if ( this->attributeIndexes.size() !=  9)                                                                 //  If there arent 10 (9, index 0 is a string / identifier) matches for each face, the mesh likely hasn't been triangulated
            {
                std::cout << RED_TEXT << "ERROR::MESH::MESH_LOADER" << RESET_TEXT << std::endl;
                std::cout << LAZARUS_FILE_UNREADABLE << std::endl;
                return false;
            }

            this->vertexIndices.push_back(stoi(this->attributeIndexes[0]));                                            //  Push each matches index position back to its respective vector's memory location
            this->vertexIndices.push_back(stoi(this->attributeIndexes[3]));                                            //  Each of these vectors contain index positions relative to the output data vectors below
            this->vertexIndices.push_back(stoi(this->attributeIndexes[6]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[1]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[4]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[7]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[2]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[5]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[8]));

            attributeIndexes.clear();
        }
        else if( currentLine[0] == 'u' )                                                          //  If the first string of the current line is "usemtl", the following string identifies the use of a new material for following faces
        {
			this->materialData = {materialIdentifierIndex, triangleCount};
			this->materialBuffer.push_back(this->materialData);
			
            this->materialIdentifierIndex += 1;                                                                       //  Increase the material identification number by 1
            this->triangleCount = 0;                                                                                  //  Reset the triangle count to 0 for the next read
        }
    }

    if (file.eof())                                                                         //  If, the scanner has reached the end of the file
    {
        file.close();
        this->materialData = {materialIdentifierIndex, triangleCount};
		this->materialBuffer.push_back(this->materialData);
        		
        matFinder.reset();
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

    if(texturePath != LAZARUS_MESH_NOTEX)
    {
	    matLoader->loadMaterial(out_diffuse, materialBuffer, foundMaterial, texturePath);
    } 
    else
    {
        matLoader->loadMaterial(out_diffuse, materialBuffer, foundMaterial);
    }

    return true;
};

vector<string> MeshLoader::vectorizeWfProperties(const char *wavefrontData, char delim)
{
    string token;
    string currentString = wavefrontData;
    stringstream ss(currentString);

    vector<string> tokenStore;

    while(getline(ss, token, delim)) 
    {
        tokenStore.push_back(token);
    }

    return tokenStore;
}

MeshLoader::~MeshLoader()
{
    if( file.is_open() )
    {
        file.close();
    }
	std::cout << GREEN_TEXT << "Destroying 'MeshLoader' class." << RESET_TEXT << std::endl;
};
