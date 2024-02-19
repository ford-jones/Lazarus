#include "../../mesh/hdr/mesh.h"

#ifndef LAZARUS_TRANSFORMS_H
#define LAZARUS_TRANSFORMS_H

class Transform
{
    public:
        Mesh::TriangulatedMesh applyRotation(Mesh::TriangulatedMesh mesh, float x, float y);
        Mesh::TriangulatedMesh applyTranslation(Mesh::TriangulatedMesh mesh, float x, float y, float z);
};

#endif