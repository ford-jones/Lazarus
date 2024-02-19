#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/transforms.h"

Mesh::TriangulatedMesh Transform::applyRotation(Mesh::TriangulatedMesh mesh, float x, float y)
{
    mesh.modelviewMatrix = glm::rotate(mesh.modelviewMatrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));                               //  manipulate the model-view matrix's x-axis rotation transform
    mesh.modelviewMatrix = glm::rotate(mesh.modelviewMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));                               //  manipulate the model-view matrix's y-axis rotation transform

    return mesh;
};

Mesh::TriangulatedMesh Transform::applyTranslation(Mesh::TriangulatedMesh mesh, float x, float y, float z)
{
    mesh.modelviewMatrix = glm::translate(mesh.modelviewMatrix, glm::vec3(x, y, z));

    return mesh;
};
