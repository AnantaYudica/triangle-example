#ifndef INTF_GRAPHICS_H_
#define INTF_GRAPHICS_H_

#include "Vertex.h"


namespace intf
{

class Graphics
{
public:
    Graphics() = default;
public:
    virtual ~Graphics() = default;
public:
    virtual bool InitDraw(Vertex * vertices, int size) = 0;
    virtual bool Draw() = 0;
    virtual void Cleanup() = 0;
};

} //!intf

#endif //!INTF_GRAPHICS_H_