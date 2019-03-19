#ifndef GRAPHICS_DIRECT3D_VERTEX_BUFFER_H_
#define GRAPHICS_DIRECT3D_VERTEX_BUFFER_H_

#include "../../../intf/graphics/Vertex.h"

#include <d3d11.h>

namespace graphics
{
namespace direct3d
{
namespace vertex
{

class Buffer :
    public intf::graphics::Vertex
{
private:
    ID3D11Buffer * m_vertex_buffer;
    std::size_t m_size;
public:
    Buffer();
public:
    ~Buffer();
public:
    bool Init(utl::Vertex * vertices, const std::size_t & size);
public:
    bool Draw();
public:
    void Cleanup();
public:
    operator bool() const;
};

} //!vertex

} //!direct3d

} //!graphics

#endif //!GRAPHICS_DIRECT3D_VERTEX_BUFFER_H_
