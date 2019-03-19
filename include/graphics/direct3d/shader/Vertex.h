#ifndef GRAPHICS_DIRECT3D_SHADER_VERTEX_H_
#define GRAPHICS_DIRECT3D_SHADER_VERTEX_H_

#include "../../../intf/graphics/Shader.h"

#include <D3Dcommon.h>
#include <d3d11.h>
#include <string>

namespace graphics
{
namespace direct3d
{
namespace shader
{

class Vertex :
    public intf::graphics::Shader
{
private:
    ID3D10Blob * m_compiled;
    ID3D11VertexShader * m_vertex_shader;
    ID3D11InputLayout * m_input_layout;
public:
    Vertex();
public:
    ~Vertex();
public:
    bool Attach();
public:
    bool CompileString(std::string str);
public:
    void Cleanup();
public:
    operator bool() const;   
};

} //!shader

} //!direct3d

} //!graphics

#endif //!GRAPHICS_DIRECT3D_SHADER_VERTEX_H_
