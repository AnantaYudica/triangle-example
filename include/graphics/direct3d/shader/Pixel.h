#ifndef GRAPHICS_DIRECT3D_SHADER_PIXEL_H_
#define GRAPHICS_DIRECT3D_SHADER_PIXEL_H_

#include "../../../intf/graphics/Shader.h"
#include "../../Direct3d.h"

#include <D3Dcommon.h>
#include <d3d11.h>
#include <string>

namespace graphics
{
namespace direct3d
{
namespace shader
{

class Pixel :
    public intf::graphics::Shader
{
private:
    ID3D10Blob * m_compiled;
    ID3D11PixelShader * m_pixel_shader;
public:
    Pixel();
public:
    ~Pixel();
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

#endif //!GRAPHICS_DIRECT3D_SHADER_PIXEL_H_
