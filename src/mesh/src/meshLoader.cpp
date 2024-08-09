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

bool MeshLoader::loadMesh(vector<vec3> &outAttributes, vector<vec3> &outDiffuse, GLuint &outTextureId, FileReader::Image &imageData, const char* meshPath, const char* materialPath, const char* texturePath) 
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
        if( currentLine[0] == 'm' )
        {
            this->foundMaterial = matFinder->relativePathToAbsolute(materialPath);
        }

        else if ( (currentLine[0] == 'v') && (currentLine[1] == ' ') )
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->vertex.x = stof(data[1]);
            this->vertex.y = stof(data[2]);
            this->vertex.z = stof(data[3]);

            this->temp_vertices.push_back(this->vertex);
        } 

        else if ( (currentLine[0] == 'v') && currentLine[1] == 't' )
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->uv.x = stof(data[1]);
            this->uv.y = stof(data[2]);

            this->temp_uvs.push_back(this->uv);
        }

        else if ( (currentLine[0] == 'v') && currentLine[1] == 'n' )
        {
            vector<string> data = vectorizeWfProperties(currentLine, ' ');
            
            this->normal.x = stof(data[1]);
            this->normal.y = stof(data[2]);
            this->normal.z = stof(data[3]);

            this->temp_normals.push_back(this->normal);
        }

        else if ( currentLine[0] == 'f' )
        {
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
            /* =======================================================
                In the wavefront file format a literal 'f' preceeds 
                face data containing the line numbers of each points'
                relevant vertex attribute data.

                Lazarus does not yet deal with polygons, only triangles. 
                This means a face should have 3 points, each with 3 
                different vertex attributes. If the face data contains
                any more than 9 vertex attribute indexes we know this 
                mesh hasn't been triangulated and can't be rendered 
                correctly.
            ========================================================== */
            if ( this->attributeIndexes.size() !=  9)
            {
                std::cout << RED_TEXT << "ERROR::MESH::MESH_LOADER" << RESET_TEXT << std::endl;
                std::cout << LAZARUS_FILE_UNREADABLE << std::endl;
                return false;
            }
            
            this->vertexIndices.push_back(stoi(this->attributeIndexes[0]));
            this->vertexIndices.push_back(stoi(this->attributeIndexes[3]));
            this->vertexIndices.push_back(stoi(this->attributeIndexes[6]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[1]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[4]));
            this->uvIndices    .push_back(stoi(this->attributeIndexes[7]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[2]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[5]));
            this->normalIndices.push_back(stoi(this->attributeIndexes[8]));

            attributeIndexes.clear();
        }
        else if( currentLine[0] == 'u' )
        {
			this->materialData = {materialIdentifierIndex, triangleCount};
			this->materialBuffer.push_back(this->materialData);
			
            this->materialIdentifierIndex += 1;
            this->triangleCount = 0;
        }
    }

    if (file.eof())
    {
        file.close();
        this->materialData = {materialIdentifierIndex, triangleCount};
		this->materialBuffer.push_back(this->materialData);
        		
        matFinder.reset();

        if(texturePath != LAZARUS_MESH_NOTEX)
        {
	        matLoader->loadMaterial(outDiffuse, materialBuffer, foundMaterial, outTextureId, imageData, texturePath);
        } 
        else
        {
            matLoader->loadMaterial(outDiffuse, materialBuffer, foundMaterial, outTextureId, imageData);
        }
    }

    for( unsigned int i = 0; i < this->vertexIndices.size(); i++ )
    {

        unsigned int vertexIndex    =   vertexIndices[i];
        unsigned int normalIndex    =   normalIndices[i];
        unsigned int uvIndex        =   uvIndices[i];
        
        vec3 vertex                 =   temp_vertices[vertexIndex - 1];
        vec3 diffuse                =   outDiffuse[i];
        vec3 normal                 =   temp_normals[normalIndex - 1];
        vec3 uv                     =   vec3(temp_uvs[uvIndex - 1].x, temp_uvs[uvIndex - 1].y, 0.0f);

        outAttributes.push_back(vertex);
        outAttributes.push_back(diffuse);
        outAttributes.push_back(normal);
        outAttributes.push_back(uv);
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
