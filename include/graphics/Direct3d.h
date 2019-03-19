#ifndef GRAPHICS_DIRECT3D_H_
#define GRAPHICS_DIRECT3D_H_

#include "../intf/Graphics.h"

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <wrl.h>

namespace graphics
{

class Direct3d final :
    public intf::Graphics
{
public:
    typedef typename intf::Graphics::CategoryType CategoryType;
    typedef typename intf::Graphics::ShaderInterfaceType
        ShaderInterfaceType;
    typedef typename intf::Graphics::VertexInterfaceType
        VertexInterfaceType;
    typedef typename intf::Graphics::ShaderInterfacePointerType
        ShaderInterfacePointerType;
    typedef typename intf::Graphics::VertexInterfacePointerType
        VertexInterfacePointerType;
public:
    typedef typename intf::Graphics::ShaderCategoryType ShaderCategoryType;
private:
    ID3D11Device * m_device;
    ID3D11DeviceContext * m_deviceContext;
    IDXGISwapChain1 * m_dxgiSwapChain;
    ID3D11RenderTargetView * m_renderTargetView;
private:
    static Direct3d ms_instance;
public:
    static Direct3d & GetInstance();
private:
    Direct3d();
public:
    ~Direct3d();
public:
    CategoryType Category();
    bool Init(HWND hwnd);
    bool BeginDraw();
    bool EndDraw();
    void Cleanup();
public:
    ShaderInterfacePointerType 
        MakeShader(const ShaderCategoryType & categ);
    VertexInterfacePointerType MakeVertex();
public:
    ID3D11Device * Device();
    ID3D11DeviceContext * DeviceContext();
    IDXGISwapChain1 * SwapChain();
};

} //!graphics

#endif //!GRAPHICS_DIRECT3D_H_