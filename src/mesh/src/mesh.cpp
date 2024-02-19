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

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/mesh.h"

Mesh::TriangulatedMesh Mesh::createTriangulatedMesh(GLuint shader, string filepath)
{
    finder = new MeshLoader();
    loader = new MeshLoader();

    srand(time((0)));
    triangulatedMesh.id = 1 + (rand() % 2147483647);

    finder->findMesh(filepath);
    triangulatedMesh.filepath = finder->fileVec[0].c_str();
    loader->loadMesh(triangulatedMesh.filepath, vertices, uvs, normals, diffuse);

    triangulatedMesh.numOfVertices = vertices.size();
    triangulatedMesh.numOfFaces = (vertices.size()) / 3;

    glGenVertexArrays           (1, &VAO);                                                                                                  //  Generate a vertex array object to store the buffers
	glBindVertexArray           (VAO);                                                                                                      //  Bind the VAO to this openGL context

	glGenBuffers                (3, &VBO[0]);                                                                                               //  Generate 3 vertex buffer objects
	
    glBindBuffer                (GL_ARRAY_BUFFER, VBO[0]);                                                                                  //  Bind the first VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices[0], GL_STATIC_DRAW);                        //  Pass vertices (vertex-position) data recieved from the loader function to the VBO                                  
	glVertexAttribPointer       (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
	glEnableVertexAttribArray   (0);                                                                                                        //  enable the first VBO in this context

    glBindBuffer                (GL_ARRAY_BUFFER, VBO[1]);                                                                                  //  Bind the second VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, normals.size() * sizeof(normals), &normals[0], GL_STATIC_DRAW);                           //  Pass normals (vertex-direction) data recieved from the loader function to the VBO                                  
    glVertexAttribPointer       (1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
    glEnableVertexAttribArray   (1);                                                                                                        //  enable the second VBO in this context
    
    glBindBuffer                (GL_ARRAY_BUFFER, VBO[2]);                                                                                  //  Bind the third VBO to openGL's array buffer (which the VAO is bound to)
    glBufferData                (GL_ARRAY_BUFFER, diffuse.size() * sizeof(diffuse), &diffuse[0], GL_STATIC_DRAW);                           //  Pass diffuse (diffuse-color) data recieved from the loader function to the VBO                                  
    glVertexAttribPointer       (2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);                                                                     //  Create a pointer to the first generic vertex attribute in the array. 
    glEnableVertexAttribArray   (2);                                                                                                        //  enable the third VBO in this context    

    triangulatedMesh.vertices = vertices;
    triangulatedMesh.modelviewMatrix = mat4(1.0f);                                                                                          //  Define the model-view matrix to default 4x4
    triangulatedMesh.modelviewUniformLocation = glGetUniformLocation(shader, "modelMatrix");                                                //  Retrieve the locations of where vert and frag shaders uniforms should be stored

    return triangulatedMesh;
};

void Mesh::instantiateMesh(TriangulatedMesh meshData)
{
    glUniformMatrix4fv(meshData.modelviewUniformLocation, 1, GL_FALSE, &meshData.modelviewMatrix[0][0]);                                    //  Pass the values for each uniform into the shader program

    errorCode = glGetError();                                                                                       //  Check for errors
    
    if(errorCode != 0)                                                                                                  //  If a valid error code is returned from OpenGL
    {
        std::cout << RED_TEXT << "ERROR::GL_ERROR::CODE " << RESET_TEXT << errorCode << std::endl;                      //  Print it to the console
    };
};

void Mesh::drawMesh(TriangulatedMesh meshData)
{
    glDrawArrays(GL_TRIANGLES, 0, meshData.vertices.size());                                                                                //  Draw the contents of the enabled VAO's stored in this context
};

Mesh::~Mesh()
{
    delete finder;
    delete loader;

    glDeleteVertexArrays    (1, &VAO);
	glDeleteBuffers         (1, &VBO[0]);
    glDeleteBuffers         (1, &VBO[1]);
    glDeleteBuffers         (1, &VBO[2]);
};