#ifndef INTF_GRAPHICS_VERTEX_H_
#define INTF_GRAPHICS_VERTEX_H_

#include "../../utl/Vertex.h"

#include <memory>

namespace intf
{
namespace graphics
{

class Vertex
{
public:
    typedef std::shared_ptr<Vertex> PointerType;
public:
    Vertex() = default;
public: 
    virtual ~Vertex() = default;
public:
    virtual bool Init(utl::Vertex * vertices, 
        const std::size_t & size) = 0;
public:
    virtual bool Draw() = 0;
public:
    virtual void Cleanup() = 0;
public:
    virtual operator bool() const = 0;
};

} //!graphics

} //!intf

#endif //!INTF_GRAPHICS_VERTEX_H_