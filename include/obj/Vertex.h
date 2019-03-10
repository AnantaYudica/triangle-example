#ifndef OBJ_VERTEX_H_
#define OBJ_VERTEX_H_

#include "Color.h"

namespace obj
{

struct Vertex
{
    float X, Y, Z;
    obj::Color Color;
};

} //!obj

#endif //!OBJ_VERTEX_H_