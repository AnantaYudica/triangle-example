#ifndef GRAPHICS_DIRECT3D_SHADER_H_
#define GRAPHICS_DIRECT3D_SHADER_H_

#include "../../intf/graphics/Shader.h"

#include <D3Dcommon.h>
#include <d3d11.h>
#include <string>

namespace graphics
{
namespace direct3d
{

class Shader :
    public intf::graphics::Shader
{
private:
    ID3D10Blob * m_vertexCompiled;
    ID3D10Blob * m_pixelCompiled;
    ID3D11VertexShader * m_vertex;
    ID3D11PixelShader* m_pixel;
public:
    Shader();
public:
    ~Shader();
public:
    bool Attach();
public:
    bool CompileString(defn::categ::Shader categ, std::string str);
public:
    operator bool();
};

} //!direct3d

} //!graphics

#endif //!GRAPHICS_DIRECT3D_SHADER_H_