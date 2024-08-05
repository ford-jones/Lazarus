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

#include "../hdr/mesh.h"

Mesh::Mesh(GLuint shader)
{
	std::cout << GREEN_TEXT << "Constructing class 'Mesh'." << RESET_TEXT << std::endl;
	this->shaderProgram = shader;
	
	this->finder = nullptr;
	this->loader = nullptr;
	this->triangulatedMesh = nullptr;

    this->vertexAttributes = {};
    this->diffuseColors = {};
    
    this->textureId = 0;
	
	this->errorCode = GL_NO_ERROR;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::createTriangulatedMesh(string meshPath, string materialPath, string texturePath)
{
    this->finder = std::make_unique<FileReader>();
    this->loader = std::make_unique<MeshLoader>();
    this->triangulatedMesh = std::make_shared<Mesh::TriangulatedMesh>();

    srand(time((0)));
    triangulatedMesh->id = 1 + (rand() % 2147483647);

    triangulatedMesh->meshFilepath =  finder->relativePathToAbsolute(meshPath);
    triangulatedMesh->materialFilepath = finder->relativePathToAbsolute(materialPath);
    
    if(texturePath != "")
    {
	    triangulatedMesh->textureFilepath = finder->relativePathToAbsolute(texturePath);
    }
    else
    {
    	triangulatedMesh->textureFilepath = LAZARUS_MESH_NOTEX;
    };
    
    loader->loadMesh(
        vertexAttributes,
        diffuseColors,
        textureId,
        triangulatedMesh->meshFilepath.c_str(),
        triangulatedMesh->materialFilepath.c_str(),
        triangulatedMesh->textureFilepath.c_str()
    );
    
    triangulatedMesh->locationX = 0;
    triangulatedMesh->locationY = 0;
    triangulatedMesh->locationZ = 0;

    triangulatedMesh->attributes = vertexAttributes;
    triangulatedMesh->textureId = this->textureId;
    triangulatedMesh->modelviewMatrix = mat4(1.0f);                                                                                          //  Define the model-view matrix to default 4x4
    triangulatedMesh->modelviewUniformLocation = glGetUniformLocation(shaderProgram, "modelMatrix");                                                //  Retrieve the locations of where vert and frag shaders uniforms should be stored
    triangulatedMesh->samplerUniformLocation = glGetUniformLocation(shaderProgram, "textures");
    triangulatedMesh->textureLayerUniformLocation = glGetUniformLocation(shaderProgram, "texLayer");

    triangulatedMesh->numOfVertices = vertexAttributes.size() / 4;
    triangulatedMesh->numOfFaces = (triangulatedMesh->numOfVertices) / 3;

    return triangulatedMesh;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::initialiseMesh(std::shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);
	
    glGenVertexArrays(1, &this->VAO);                                                                                                  //  Generate a vertex array object to store the buffers
	glBindVertexArray(this->VAO);                                                                                                      //  Bind the VAO to this openGL context

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
	
    return triangulatedMesh;
};

//	TODO:
//	Ownership is never release from the following two functions
//	Either don't take ownership at all or return the pointer to the function's invocator
//	Update docs

void Mesh::loadMesh(shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);

    glUniformMatrix4fv(triangulatedMesh->modelviewUniformLocation, 1, GL_FALSE, &triangulatedMesh->modelviewMatrix[0][0]);                                    //  Pass the values for each uniform into the shader program
    glUniform1i(triangulatedMesh->samplerUniformLocation, 0);
    
    if(triangulatedMesh->textureId != 0)
    {
        std::cout << "Texture Layer: " << textureId << " - Loaded." << std::endl;
        glUniform1i(triangulatedMesh->textureLayerUniformLocation, triangulatedMesh->textureId);
    }

    this->checkErrors(__PRETTY_FUNCTION__);
};

void Mesh::drawMesh(shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);
	
    glDrawArrays(GL_TRIANGLES, 0, triangulatedMesh->attributes.size());
    this->checkErrors(__PRETTY_FUNCTION__);

    this->releaseMesh();
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
