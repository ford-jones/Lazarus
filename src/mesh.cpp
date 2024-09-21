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

#include "../include/mesh.h"

Mesh::Mesh(GLuint shader)
{
	std::cout << GREEN_TEXT << "Constructing class 'Mesh'." << RESET_TEXT << std::endl;
	this->shaderProgram = shader;
	
	this->finder = nullptr;
	this->meshLoader = nullptr;
    this->texLoader = std::make_unique<TextureLoader>();
	triangulatedMesh = nullptr;
    quad = nullptr;

    this->vertexAttributes = {};
    this->diffuseColors = {};
    
    this->xyTextureId = 0;
    this->xyzTextureId = 0;
	
	this->errorCode = GL_NO_ERROR;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::create3DAsset(string meshPath, string materialPath, string texturePath)
{
    this->meshLoader = std::make_unique<MeshLoader>();
    triangulatedMesh = std::make_shared<Mesh::TriangulatedMesh>();

    triangulatedMesh->is3D = 1;

    this->resolveFilepaths(triangulatedMesh, texturePath, materialPath, meshPath);
    
    meshLoader->parseWavefrontObj(
        this->vertexAttributes,
        this->diffuseColors,
        this->xyzTextureId,
        this->texStore,
        triangulatedMesh->meshFilepath.c_str(),
        triangulatedMesh->materialFilepath.c_str(),
        triangulatedMesh->textureFilepath.c_str()
    );

    triangulatedMesh->textureId = this->xyzTextureId;

    this->setInherentProperties(triangulatedMesh);
    this->lookupUniforms(triangulatedMesh);

    return triangulatedMesh;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::createQuad(float width, float height, string texturePath)
{
    quad = std::make_shared<TriangulatedMesh>();

    quad->is3D = 0;

    this->resolveFilepaths(quad, texturePath);

    /* ======================================================================================================
            Vertex positions,           Diffuse colors,             Normals,                    UVs 
    ========================================================================================================= */
    this->vertexAttributes = {
        vec3(0.0f, 0.0f, 0.0f),     vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 0.0f, 0.0f),
        vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 1.0f, 0.0f),

        vec3(width, height, 0.0f),  vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 1.0f, 0.0f),
        vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 1.0f, 0.0f),
    
        vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 1.0f, 0.0f),
        vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 0.0f, 0.0f),
        vec3(width, height, 0.0f),  vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 1.0f, 0.0f),

        vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 1.0f, 0.0f),
        vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(1.0f, 0.0f, 0.0f),
        vec3(0.0f, 0.0f, 0.0f),     vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(0.0f, 0.0f, 0.0f),
    };

    if(quad->textureFilepath != LAZARUS_MESH_NOTEX)
    {
        texLoader->storeTexture(quad->textureFilepath, this->xyTextureId, this->texStore);
    }

    quad->textureId = this->xyTextureId;

    this->setInherentProperties(quad);
    this->lookupUniforms(quad);

    return quad;
}

void Mesh::resolveFilepaths(std::shared_ptr<Mesh::TriangulatedMesh> &asset, string texPath, string mtlPath, string objPath)
{
    this->finder = std::make_unique<FileReader>();
    if(objPath != "") 
    {
        asset->meshFilepath =  finder->relativePathToAbsolute(objPath);
    } 
    else
    {
        asset->meshFilepath = LAZARUS_MESH_NOOBJ;
    };

    if(mtlPath != "") 
    {
        asset->materialFilepath = finder->relativePathToAbsolute(mtlPath);
    }
    else
    {
        asset->materialFilepath = LAZARUS_MESH_NOMTL;
    }
    
    if(texPath != "")
    {
	    asset->textureFilepath = finder->relativePathToAbsolute(texPath);
    }
    else
    {
    	asset->textureFilepath = LAZARUS_MESH_NOTEX;
    };
};

void Mesh::setInherentProperties(std::shared_ptr<Mesh::TriangulatedMesh> &asset)
{
    asset->attributes = this->vertexAttributes;

    asset->textureData.width = this->texStore.width;
    asset->textureData.height = this->texStore.height;
    asset->textureData.pixelData = this->texStore.pixelData;

    asset->locationX = 0;
    asset->locationY = 0;
    asset->locationZ = 0;

    asset->modelviewMatrix = mat4(1.0f);

    asset->numOfVertices = asset->attributes.size() / 4;
    asset->numOfFaces = (asset->numOfVertices) / 3;
}

void Mesh::lookupUniforms(std::shared_ptr<Mesh::TriangulatedMesh> &asset)
{
    asset->modelviewUniformLocation = glGetUniformLocation(this->shaderProgram, "modelMatrix");                                                //  Retrieve the locations of where vert and frag shaders uniforms should be stored
    asset->is3DUniformLocation = glGetUniformLocation(this->shaderProgram, "spriteAsset");

    if(asset->is3D == 1)
    {
        asset->samplerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyzAssetTextures");
        asset->textureLayerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyzTexLayerIndex");    
    }
    else 
    {
        asset->samplerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyAssetTextures");
        asset->textureLayerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyTexLayerIndex");
    }
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::initialiseMesh(std::shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};

	triangulatedMesh = std::move(meshData);
	
    glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, triangulatedMesh->attributes.size() * sizeof(vec3), &triangulatedMesh->attributes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(1 * sizeof(vec3)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(3 * sizeof(vec3)));
    glEnableVertexAttribArray(3);

    this->checkErrors(__PRETTY_FUNCTION__);

    if(triangulatedMesh->textureFilepath != LAZARUS_MESH_NOTEX)
    {
        texLoader->loadTexture(triangulatedMesh->textureData, triangulatedMesh->textureId);
    }
	
    return triangulatedMesh;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::loadMesh(shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);

    glUniformMatrix4fv(triangulatedMesh->modelviewUniformLocation, 1, GL_FALSE, &triangulatedMesh->modelviewMatrix[0][0]);                                    //  Pass the values for each uniform into the shader program
    glUniform1i(triangulatedMesh->is3DUniformLocation, triangulatedMesh->is3D);

    if(triangulatedMesh->textureId != 0)
    {
        glUniform1f(triangulatedMesh->textureLayerUniformLocation, (triangulatedMesh->textureId - 1));
    }

    this->checkErrors(__PRETTY_FUNCTION__);

    return triangulatedMesh;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::drawMesh(shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);
	
    glDrawArrays(GL_TRIANGLES, 0, triangulatedMesh->attributes.size());

    this->checkErrors(__PRETTY_FUNCTION__);

    this->releaseMesh();

    return triangulatedMesh;
};

void Mesh::checkErrors(const char *invoker)
{
    this->errorCode = glGetError();                                                                                       //  Check for errors
    
    if(this->errorCode != 0)                                                                                                  //  If a valid error code is returned from OpenGL
    {
        std::cerr << RED_TEXT << "ERROR::GL_ERROR::CODE " << RESET_TEXT << this->errorCode << std::endl;                      //  Print it to the console
        std::cerr << RED_TEXT << "INVOKED BY: " << RESET_TEXT << invoker << std::endl;                      //  Print it to the console
    };

};

void Mesh::releaseMesh()
{
    glDeleteVertexArrays    (1, &this->VAO);
    glDeleteBuffers         (1, &this->VBO);

    this->checkErrors(__PRETTY_FUNCTION__);
};

Mesh::~Mesh()
{
    this->releaseMesh();
    std::cout << GREEN_TEXT << "Destroying 'Mesh' class." << RESET_TEXT << std::endl;
};