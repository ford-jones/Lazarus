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

#include "../include/lz_mesh.h"

MeshManager::MeshManager(GLuint shader)
{
	std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
	this->shaderProgram = shader;
	
	this->finder = std::make_unique<FileReader>();
    this->texLoader = std::make_unique<TextureLoader>();

	meshLoader = nullptr;

    this->mesh = {};
    this->meshStore = {};
    
    this->xyTextureId = 0;
    this->xyzTextureId = 0;
	
	this->errorCode = GL_NO_ERROR;

};

MeshManager::Mesh MeshManager::create3DAsset(string meshPath, string materialPath, string texturePath)
{
    this->mesh = {};

    this->meshLoader = std::make_unique<MeshLoader>();

    mesh.is3D = 1;
    mesh.isGlyph = 0;

    this->lookupUniforms(mesh);

    glUniform1i(mesh.samplerUniformLocation, 2);

    mesh.textureUnit = GL_TEXTURE2;
    glActiveTexture(mesh.textureUnit);

    this->resolveFilepaths(mesh, texturePath, materialPath, meshPath);
    
    meshLoader->parseWavefrontObj(
        mesh.attributes,
        mesh.diffuse,
        mesh.textureId,
        mesh.textureData,
        mesh.meshFilepath.c_str(),
        mesh.materialFilepath.c_str(),
        mesh.textureFilepath.c_str()
    );

    this->setInherentProperties(mesh);
    this->initialiseMesh(mesh);

    return mesh;
};

/* ========================================================================================
    Note: There is some strange behaviour with this function.
    If a single instance of *this* class is responsible for creating quads as well as 3D
    assets - a texturing artifact will present itself when the user *creates* the quad 
    prior to creating the 3D assets. (i.e. createQuad is called before create3DAsset).

    At the quads origin in worldspace, a "shadow" of the quad will render using texture 
    number 1 off of the xyzTextureStack. Not sure why.

    This is *very* similar to the behaviour seen on MacOS and is possibly related. It might
    just be that the bug doesn't present itself on linux.

    Worth mentioning that this doesn't seem to happen with glyphs - which are wrapped over
    a quad under the hood.
=========================================================================================== */

MeshManager::Mesh MeshManager::createQuad(float width, float height, string texturePath, float uvXL, float uvXR, float uvY)
{
    this->mesh = {};

    mesh.is3D = 0;
    mesh.isGlyph = 0;

    this->lookupUniforms(mesh);

    glUniform1i(mesh.samplerUniformLocation, 3);
    
    mesh.textureUnit = GL_TEXTURE3;
    glActiveTexture(mesh.textureUnit);

    this->resolveFilepaths(mesh, texturePath);

    /* ==========================================================
        If the UV params aren't their default values (0.0) then
        this mesh is being created for a glyph which needs to be 
        looked up in the texture atlas.

        Otherwise it's a generic sprite.
    ============================================================= */

    if((uvXL || uvXR || uvY) > 0.0 )
    {
        float textureIndex = static_cast<float>(mesh.textureId);

        /* ======================================================================================================
                Vertex positions,           Diffuse colors,             Normals,                    UVs 
        ========================================================================================================= */

        mesh.attributes = {                                                                                          
            vec3(0.0f, 0.0f, 0.0f),     vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, 0.0f, textureIndex),
            vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, 0.0f, textureIndex), 
            vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, uvY, textureIndex),

            vec3(width, height, 0.0f),  vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, uvY, textureIndex),
            vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, 0.0f, textureIndex),
            vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, uvY, textureIndex),

            vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, uvY, textureIndex),
            vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, 0.0f, textureIndex),
            vec3(width, height, 0.0f),  vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, uvY, textureIndex),

            vec3(0.0f, height, 0.0f),   vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, uvY, textureIndex),
            vec3(width, 0.0f, 0.0f),    vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXR, 0.0f, textureIndex), 
            vec3(0.0f, 0.0f, 0.0f),     vec3(-0.1f, -0.1f, -0.1f),     vec3(0.0f, 0.0f, 1.0f),     vec3(uvXL, 0.0f, textureIndex),
        };
    }
    else
    {
        mesh.attributes = {
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
    };

    this->setInherentProperties(mesh);
    this->initialiseMesh(mesh);

    return mesh;
}

void MeshManager::initialiseMesh(MeshManager::Mesh &asset)
{	
    glGenVertexArrays(1, &asset.VAO);
   	glBindVertexArray(asset.VAO);

    if(asset.modelviewUniformLocation >= 0)
    {
        glActiveTexture(asset.textureUnit);

        if((asset.textureFilepath != LAZARUS_MESH_NOTEX))
        {
            // ?
            texLoader->loadImageToTextureStack(asset.textureData, asset.textureId);
        };

        glGenBuffers(1, &asset.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, asset.VBO);

        glBufferData(GL_ARRAY_BUFFER, asset.attributes.size() * sizeof(vec3), &asset.attributes[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(1 * sizeof(vec3)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(2 * sizeof(vec3)));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, (4 * sizeof(vec3)), (void*)(3 * sizeof(vec3)));
        glEnableVertexAttribArray(3);

        this->checkErrors(__PRETTY_FUNCTION__);

        this->meshStore.push_back(asset);
        std::cout << "MeshManager::meshStore size: " << this->meshStore.size() << std::endl;
    }
    else
    {
        globals.setExecutionState(LAZARUS_MATRIX_LOCATION_ERROR);
    };
	
    return;
};

void MeshManager::loadMesh(MeshManager::Mesh &asset)
{
    if(asset.modelviewUniformLocation >= 0)
    {
        glUniformMatrix4fv(asset.modelviewUniformLocation, 1, GL_FALSE, &asset.modelviewMatrix[0][0]);
        glUniform1i(asset.is3DUniformLocation, asset.is3D);
        glUniform1i(asset.isGlyphUniformLocation, asset.isGlyph);
    
        this->checkErrors(__PRETTY_FUNCTION__);
    }
    else
    {
        globals.setExecutionState(LAZARUS_MATRIX_LOCATION_ERROR);
    };

    return;
};

void MeshManager::drawMesh(MeshManager::Mesh &asset)
{
    glBindVertexArray(asset.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, asset.VBO);

    glActiveTexture(asset.textureUnit);

    if((asset.textureFilepath == LAZARUS_MESH_ISTEXT))
    {
        glBindTexture(GL_TEXTURE_2D, asset.textureId);
    }
    else if((asset.textureFilepath != LAZARUS_MESH_NOTEX))
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, asset.textureId);
    };

    glDrawArrays(GL_TRIANGLES, 0, asset.attributes.size());

    this->checkErrors(__PRETTY_FUNCTION__);

    return;
};

void MeshManager::resolveFilepaths(MeshManager::Mesh &asset, string texPath, string mtlPath, string objPath)
{
    if(objPath != "") 
    {
        asset.meshFilepath =  finder->relativePathToAbsolute(objPath);
    } 
    else
    {
        asset.meshFilepath = LAZARUS_MESH_NOOBJ;
    };

    if(mtlPath != "") 
    {
        asset.materialFilepath = finder->relativePathToAbsolute(mtlPath);
    }
    else
    {
        asset.materialFilepath = LAZARUS_MESH_NOMTL;
    }
    
    if(texPath == LAZARUS_MESH_ISTEXT)
    {
        asset.textureFilepath = LAZARUS_MESH_ISTEXT;
    }
    else if(texPath != "")
    {
	    asset.textureFilepath = finder->relativePathToAbsolute(texPath);
        asset.textureData = finder->readFromImage(asset.textureFilepath);
        texLoader->extendTextureStack(asset.textureData.width, asset.textureData.height, asset.textureId);
    }
    else
    {
        /* ========================================
            Layers of the sampler array are aren't 
            zero-indexed. Texture id's of 0 are 
            another indicator that no texture is in
            use.
        =========================================== */
        asset.textureId = 0;
    	asset.textureFilepath = LAZARUS_MESH_NOTEX;
        asset.textureData = {pixelData: NULL, height: 0, width: 0};
    };

    return;
};

void MeshManager::setInherentProperties(MeshManager::Mesh &asset)
{
    asset.locationX = 0;
    asset.locationY = 0;
    asset.locationZ = 0;

    asset.modelviewMatrix = mat4(1.0f);

    asset.numOfVertices = asset.attributes.size() / 4;
    asset.numOfFaces = (asset.numOfVertices) / 3;

   return;
}

void MeshManager::lookupUniforms(MeshManager::Mesh &asset)
{
    asset.modelviewUniformLocation = glGetUniformLocation(this->shaderProgram, "modelMatrix");
    asset.is3DUniformLocation = glGetUniformLocation(this->shaderProgram, "spriteAsset");
    asset.isGlyphUniformLocation = glGetUniformLocation(this->shaderProgram, "glyphAsset");

    if(asset.is3D == 1)
    {
        asset.samplerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyzAssetTextures");
    }
    else 
    {
        asset.samplerUniformLocation = glGetUniformLocation(this->shaderProgram, "xyAssetTextures");
    }

    return;
};

void MeshManager::checkErrors(const char *invoker)
{
    this->errorCode = glGetError();
    
    if(this->errorCode != 0)
    {
        std::cerr << RED_TEXT << "ERROR::GL_ERROR::CODE " << RESET_TEXT << this->errorCode << std::endl;
        std::cerr << RED_TEXT << "INVOKED BY: " << RESET_TEXT << invoker << std::endl;

        globals.setExecutionState(LAZARUS_OPENGL_ERROR);
    }

    return;
};

MeshManager::~MeshManager()
{
    for(auto i: meshStore)
    {
        glDeleteBuffers         (1, &i.VBO);
        glDeleteVertexArrays    (1, &i.VAO);
    };


    this->checkErrors(__PRETTY_FUNCTION__);

    std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
};