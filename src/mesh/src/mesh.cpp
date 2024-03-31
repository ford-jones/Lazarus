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
	
	this->errorCode = GL_NO_ERROR;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::createTriangulatedMesh(string meshPath, string materialPath)
{
    this->finder = std::make_unique<FileReader>();
    this->loader = std::make_unique<MeshLoader>();
    this->triangulatedMesh = std::make_shared<Mesh::TriangulatedMesh>();

    srand(time((0)));
    triangulatedMesh->id = 1 + (rand() % 2147483647);

    triangulatedMesh->meshFilepath =  finder->relativePathToAbsolute(meshPath);
    triangulatedMesh->materialFilepath = finder->relativePathToAbsolute(materialPath);
    loader->loadMesh(triangulatedMesh->meshFilepath.c_str(), triangulatedMesh->materialFilepath.c_str(), vertices, uvs, normals, diffuse);
    
    triangulatedMesh->locationX = 0;
    triangulatedMesh->locationY = 0;
    triangulatedMesh->locationZ = 0;

    triangulatedMesh->numOfVertices = vertices.size();
    triangulatedMesh->numOfFaces = (vertices.size()) / 3;

    triangulatedMesh->vertices = vertices;
    triangulatedMesh->normals = normals;
    triangulatedMesh->diffuse = diffuse;
    triangulatedMesh->modelviewMatrix = mat4(1.0f);                                                                                          //  Define the model-view matrix to default 4x4
    triangulatedMesh->modelviewUniformLocation = glGetUniformLocation(shaderProgram, "modelMatrix");                                                //  Retrieve the locations of where vert and frag shaders uniforms should be stored

    return triangulatedMesh;
};

std::shared_ptr<Mesh::TriangulatedMesh> Mesh::initialiseMesh(std::shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);
	
    glGenVertexArrays           (1, &this->VAO);                                                                                                  //  Generate a vertex array object to store the buffers
	glBindVertexArray           (this->VAO);                                                                                                      //  Bind the VAO to this openGL context

	glGenBuffers                (3, &this->VBO[0]);                                                                                               //  Generate 3 vertex buffer objects
	
    glBindBuffer                (GL_ARRAY_BUFFER, this->VBO[0]);                                                                                  //  Bind the first VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, triangulatedMesh->vertices.size() * sizeof(vec3), &triangulatedMesh->vertices[0], GL_STATIC_DRAW);                        //  Pass vertices (vertex-position) data recieved from the loader function to the VBO                                  
	glVertexAttribPointer       (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
	glEnableVertexAttribArray   (0);                                                                                                        //  enable the first VBO in this context

    glBindBuffer                (GL_ARRAY_BUFFER, this->VBO[1]);                                                                                  //  Bind the second VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, triangulatedMesh->normals.size() * sizeof(vec3), &triangulatedMesh->normals[0], GL_STATIC_DRAW);                           //  Pass normals (vertex-direction) data recieved from the loader function to the VBO                                  
    glVertexAttribPointer       (1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
    glEnableVertexAttribArray   (1);                                                                                                        //  enable the second VBO in this context
    
    glBindBuffer                (GL_ARRAY_BUFFER, this->VBO[2]);                                                                                  //  Bind the third VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, triangulatedMesh->diffuse.size() * sizeof(vec3), &triangulatedMesh->diffuse[0], GL_STATIC_DRAW);                           //  Pass diffuse (diffuse-color) data recieved from the loader function to the VBO                                  
    glVertexAttribPointer       (2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
    glEnableVertexAttribArray   (2);                                                                                                        //  enable the third VBO in this context    
    
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

    this->checkErrors(__PRETTY_FUNCTION__);
};

void Mesh::drawMesh(shared_ptr<TriangulatedMesh> meshData)
{
	if(triangulatedMesh != nullptr)
	{
		triangulatedMesh.reset();
	};
	
	triangulatedMesh = std::move(meshData);
	
    glDrawArrays(GL_TRIANGLES, 0, triangulatedMesh->vertices.size());                                                                                //  Draw the contents of the enabled VAO's stored in this context

    this->checkErrors(__PRETTY_FUNCTION__);

    this->releaseMesh();
};

void Mesh::checkErrors(const char *invoker)
{
    this->errorCode = glGetError();                                                                                       //  Check for errors
    
    if(this->errorCode != 0)                                                                                                  //  If a valid error code is returned from OpenGL
    {
        std::cout << RED_TEXT << "ERROR::GL_ERROR::CODE " << RESET_TEXT << this->errorCode << std::endl;                      //  Print it to the console
        std::cout << RED_TEXT << "INVOKED BY: " << RESET_TEXT << invoker << std::endl;                      //  Print it to the console
    };
};

void Mesh::releaseMesh()
{
    glDeleteVertexArrays    (1, &this->VAO);
	glDeleteBuffers         (1, &this->VBO[0]);
    glDeleteBuffers         (1, &this->VBO[1]);
    glDeleteBuffers         (1, &this->VBO[2]);

    this->checkErrors(__PRETTY_FUNCTION__);
};

Mesh::~Mesh()
{
    this->releaseMesh();
    std::cout << GREEN_TEXT << "Destroying 'Mesh' class." << RESET_TEXT << std::endl;
};
