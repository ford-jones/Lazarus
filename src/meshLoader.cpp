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

#include "../include/meshLoader.h"

MeshLoader::MeshLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'MeshLoader'." << RESET_TEXT << std::endl;
	this->materialIdentifierIndex	=	0;
	this->triangleCount				=	0;

	this->matFinder 				= 	nullptr;
	this->matLoader 				=	nullptr;
};

bool MeshLoader::parseWavefrontObj(vector<vec3> &outAttributes, vector<vec3> &outDiffuse, GLuint &outTextureId, FileReader::Image &imageData, const char* meshPath, const char* materialPath, const char* texturePath) 
{
	this->matFinder = std::make_unique<FileReader>();
	this->matLoader = std::make_unique<MaterialLoader>();
	
    this->materialIdentifierIndex = 0;
    this->triangleCount = 0;

    file.open(meshPath);

    if( !file.is_open() )
    {
        // LAZARUS_EXECUTION_STATUS = LAZARUS_FILE_UNREADABLE;
        globals.setExecutionState(LAZARUS_FILE_UNREADABLE);
        
        return false;
    }

    while( file.getline(currentLine, 256) )
    {
        switch (currentLine[0])
        {
        case 'm':
            /* ============================================
                materialPath should be optional.
                The path / filename can be gathered by
                reading the file. The materialPath argument
                should only need to be used as an overide.

                For instance if the filename was changed 
                since export.
            ================================================ */
            this->foundMaterial = matFinder->relativePathToAbsolute(materialPath);
            break;
        
        case 'v':
            if ( currentLine[1] == ' ' )
            {
                coordinates = splitTokensFromLine(currentLine, ' ');

                this->vertex.x = stof(coordinates[1]);
                this->vertex.y = stof(coordinates[2]);
                this->vertex.z = stof(coordinates[3]);

                this->tempVertexPositions.push_back(this->vertex);
            } 

            else if ( currentLine[1] == 't' )
            {
                coordinates = splitTokensFromLine(currentLine, ' ');

                this->uv.x = stof(coordinates[1]);
                this->uv.y = stof(coordinates[2]);

                this->tempUvs.push_back(this->uv);
            }

            else if ( currentLine[1] == 'n' )
            {
                coordinates = splitTokensFromLine(currentLine, ' ');

                this->normal.x = stof(coordinates[1]);
                this->normal.y = stof(coordinates[2]);
                this->normal.z = stof(coordinates[3]);

                this->tempNormals.push_back(this->normal);
            }
            break;

        case 'f':
            this->triangleCount += 1;

            coordinates = splitTokensFromLine(currentLine, ' ');
            for(auto i: coordinates) 
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

            this->constructTriangle();

            break;

        case 'u':
            this->materialData = {materialIdentifierIndex, triangleCount};
			this->materialBuffer.push_back(this->materialData);
			
            this->materialIdentifierIndex += 1;
            this->triangleCount = 0;
            break;

        default:
            break;
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

    this->interleaveBufferData(outAttributes, outDiffuse, this->vertexIndices.size());

    // LAZARUS_EXECUTION_STATUS = LAZARUS_OK;
    globals.setExecutionState(LAZARUS_OK);

    return true;
};

vector<string> MeshLoader::splitTokensFromLine(const char *wavefrontData, char delim)
{
    string token;
    string currentString = wavefrontData;
    stringstream ss(currentString);

    vector<string> tokenStore;

    while(getline(ss, token, delim)) 
    {
        tokenStore.push_back(token);
    }

    // LAZARUS_EXECUTION_STATUS = LAZARUS_OK;
    globals.setExecutionState(LAZARUS_OK);

    return tokenStore;
}

void MeshLoader::interleaveBufferData(vector<vec3> &outAttributes, vector<vec3> &outDiffuse, int numOfAttributes)
{
    for( unsigned int i = 0; i < numOfAttributes; i++ )
    {

        unsigned int vertexIndex    =   vertexIndices[i];
        unsigned int normalIndex    =   normalIndices[i];
        unsigned int uvIndex        =   uvIndices[i];
        
        /* =========================================
            uv is extended from its generic xy components
            to include a z value here to meet the expected
            stride range for attributes in the vertex buffer.
            
            i.e: (4 * sizeof(vec3)) = 12

            Once in the shaders it is disregarded. 
        ============================================ */
        vec3 vertex                 =   tempVertexPositions[vertexIndex - 1];
        vec3 diffuse                =   outDiffuse[i];
        vec3 normal                 =   tempNormals[normalIndex - 1];
        vec3 uv                     =   vec3(tempUvs[uvIndex - 1].x, tempUvs[uvIndex - 1].y, 0.0f);

        outAttributes.push_back(vertex);
        outAttributes.push_back(diffuse);
        outAttributes.push_back(normal);
        outAttributes.push_back(uv);
    }

    // LAZARUS_EXECUTION_STATUS = LAZARUS_OK;
    globals.setExecutionState(LAZARUS_OK);

    return;
}

void MeshLoader::constructTriangle()
{
    /* =======================================================
        A face should have 3 points, each with 3 
        different vertex attributes. If the face data contains
        any more than 9 vertex attribute indexes we know this 
        mesh hasn't been triangulated and can't be rendered 
        correctly.
    ========================================================== */
    if ( this->attributeIndexes.size() !=  9)
    {
        std::cout << RED_TEXT << "ERROR::MESH::MESH_LOADER " << std::endl;
        std::cout << "Status: " << LAZARUS_FILE_UNREADABLE << RESET_TEXT << std::endl;

        // LAZARUS_EXECUTION_STATUS = LAZARUS_FILE_UNREADABLE;
        globals.setExecutionState(LAZARUS_FILE_UNREADABLE);

        return;
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

    // LAZARUS_EXECUTION_STATUS = LAZARUS_OK;
    globals.setExecutionState(LAZARUS_OK);

    return;
}

MeshLoader::~MeshLoader()
{
    if( file.is_open() )
    {
        file.close();
    }
	std::cout << GREEN_TEXT << "Destroying 'MeshLoader' class." << RESET_TEXT << std::endl;
};

