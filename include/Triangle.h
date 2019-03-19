#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "intf/Graphics.h"
#include "intf/graphics/Shader.h"
#include "intf/graphics/Vertex.h"
#include "utl/Vertex.h"

#include <string>
#include <memory>

class Triangle 
{
public:
    typedef typename intf::graphics::Shader::PointerType
        ShaderPointerType;
    typedef typename intf::graphics::Vertex::PointerType
        VertexPointerType;
private:
    intf::Graphics * m_graphics;
    ShaderPointerType m_vertex_shader;
    ShaderPointerType m_fragment_shader;
    VertexPointerType m_vertex;
    utl::Vertex * m_vertices;
    int m_vertices_size;
    std::string m_hl_shader;
public:
    Triangle(intf::Graphics * graphics);
    ~Triangle();
public:
    Triangle(const Triangle & cpy) = delete;
    Triangle(Triangle && mov) = delete;
public:
    Triangle & operator=(const Triangle & cpy) = delete;
    Triangle & operator=(Triangle && mov) = delete;
public:
    bool Init();
public:
    bool Draw();
};

#endif //!TRIANGLE_H_