

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>

#if defined MUD_GEOM_LIB
#define MUD_GEOM_EXPORT MUD_EXPORT
#else
#define MUD_GEOM_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace glm {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum DrawMode : unsigned int;
    enum class PrimitiveType : unsigned int;
    enum class SymbolDetail : unsigned short;
    
    
    class Shape;
    struct ShapeVar;
    struct Line;
    struct Rect;
    struct Quad;
    struct Grid2;
    struct Triangle;
    struct Circle;
    struct Torus;
    struct Ring;
    struct Ellipsis;
    struct Arc;
    struct Cylinder;
    struct Capsule;
    struct Cube;
    struct Sphere;
    struct SphereRing;
    struct Spheroid;
    struct Aabb;
    struct Plane;
    struct Plane3;
    struct Face3;
    struct Segment;
    struct Ray;
    struct Plane6;
    struct Point8;
    struct VertexAttribute;
    struct Vertex;
    struct Tri;
    struct ShapeVertex;
    struct ShapeTriangle;
    struct MeshData;
    class Geometry;
    struct MeshPacker;
    class Distribution;
    class Poisson;
    class RandomShapePoint;
    struct Polygon;
    struct Box;
    struct Points;
    struct ConvexHull;
    struct Symbol;
    struct Anim;
    class Animator;
    struct ShapeSize;
    struct ProcShape;
    struct CompoundShape;
    struct DispatchDrawProcShape;
    class IcoSphere;
}

namespace mud {
namespace detail {

    
    
}
}

