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
private:
    ID3D11Device * m_device;
    ID3D11DeviceContext * m_deviceContext;
    IDXGISwapChain1* m_dxgiSwapChain;
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
    bool Init(HWND hwnd);
    bool Draw();
    void Cleanup();
public:
    ID3D11Device * Device();
    ID3D11DeviceContext * DeviceContext();
};

} //!graphics

#endif //!GRAPHICS_DIRECT3D_H_