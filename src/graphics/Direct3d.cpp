#include "graphics/Direct3d.h"

using namespace std;
using namespace graphics;
using namespace Microsoft::WRL;

Direct3d Direct3d::ms_instance;

Direct3d::Direct3d()
{}

Direct3d::~Direct3d()
{}

Direct3d & Direct3d::GetInstance()
{
    return ms_instance;
}

bool Direct3d::Init(HWND hwnd)
{
    auto res = D3D11CreateDevice(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &m_device,
        NULL,
        &m_deviceContext);

    if (res != S_OK) return false;
    ComPtr<ID3D11Device> device{ m_device };

    ComPtr<IDXGIDevice> dxgiDevice;
    device.As(&dxgiDevice);

    ComPtr<IDXGIAdapter> dxgiAdapter;
    dxgiDevice->GetAdapter(&dxgiAdapter);

    ComPtr<IDXGIFactory2> dxgiFactory;
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

    DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc;

    dxgiSwapChainDesc.Width = 0;
    dxgiSwapChainDesc.Height = 0;
    dxgiSwapChainDesc.Stereo = false;
    dxgiSwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    dxgiSwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    dxgiSwapChainDesc.BufferCount = 2;
    dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dxgiSwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    dxgiSwapChainDesc.SampleDesc.Count = 1;
    dxgiSwapChainDesc.SampleDesc.Quality = -1;
    dxgiSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    dxgiSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

    res = dxgiFactory->CreateSwapChainForHwnd(
        m_device,
        hwnd,
        &dxgiSwapChainDesc,
        NULL,
        NULL,
        &m_dxgiSwapChain);

    if (res != S_OK) return false;

    ComPtr<ID3D11Texture2D> backbuffer;
    m_dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backbuffer);

    device->CreateRenderTargetView(backbuffer.Get(), NULL, &m_renderTargetView);

    return true;
}

bool Direct3d::Render()
{
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

    float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

    m_dxgiSwapChain->Present(1, 0);
    return true;
}

bool Direct3d::InitDraw(Vertex * vertices, int size) 
{
    return false;
}

bool Direct3d::Draw()
{
    return false;
}

void Direct3d::Cleanup()
{
    
}
