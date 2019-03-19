#include "graphics/Direct3d.h"
#include "graphics/direct3d/shader/Pixel.h"
#include "graphics/direct3d/shader/Vertex.h"
#include "graphics/direct3d/vertex/Buffer.h"

using namespace std;
using namespace graphics;
using namespace Microsoft::WRL;

Direct3d Direct3d::ms_instance;

Direct3d::Direct3d() :
    m_device(nullptr),
    m_deviceContext(nullptr),
    m_dxgiSwapChain(nullptr),
    m_renderTargetView(nullptr)
{}

Direct3d::~Direct3d()
{
    Cleanup();
}

Direct3d & Direct3d::GetInstance()
{
    return ms_instance;
}

typename Direct3d::CategoryType Direct3d::Category()
{
    return CategoryType::direct3d;
}

bool Direct3d::Init(HWND hwnd)
{
    auto res = D3D11CreateDevice(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        D3D11_CREATE_DEVICE_DEBUG,
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

    RECT rect;
    if (!GetWindowRect(hwnd, &rect)) return false;

    D3D11_VIEWPORT view_port;

    view_port.TopLeftX = 0;
    view_port.TopLeftY = 0;
    view_port.Width = (float)(rect.right - rect.left);
    view_port.Height = (float)(rect.bottom - rect.top);
    view_port.MaxDepth = NULL;
    view_port.MinDepth = NULL;

    m_deviceContext->RSSetViewports(1, &view_port);

    return true;
}

bool Direct3d::BeginDraw()
{
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

    float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);

    return true;
}

bool Direct3d::EndDraw()
{
    m_dxgiSwapChain->Present(1, 0);
    return true;
}

void Direct3d::Cleanup()
{
    if (m_device)
    {   
        m_device->Release();
        m_device = nullptr;
    }
    if (m_deviceContext) 
    {
        m_deviceContext->Release();
        m_deviceContext = nullptr;
    }
    if (m_dxgiSwapChain) 
    {
        m_dxgiSwapChain->Release();
        m_dxgiSwapChain = nullptr;
    }
    if (m_renderTargetView) 
    {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }
}

typename Direct3d::ShaderInterfacePointerType 
Direct3d::MakeShader(const ShaderCategoryType & categ)
{
    if (categ == ShaderCategoryType::vertex)
        return ShaderInterfacePointerType(new direct3d::shader::Vertex());
    else if (categ == ShaderCategoryType::pixel)
        return ShaderInterfacePointerType(new direct3d::shader::Pixel());
    else if (categ == ShaderCategoryType::fragment)
        return ShaderInterfacePointerType(new direct3d::shader::Pixel());
    return ShaderInterfacePointerType(nullptr);
}

typename Direct3d::VertexInterfacePointerType 
Direct3d::MakeVertex()
{
    return VertexInterfacePointerType(new direct3d::vertex::Buffer());
}

ID3D11Device * Direct3d::Device()
{
    return m_device;
}

ID3D11DeviceContext * Direct3d::DeviceContext()
{
    return m_deviceContext;
}

IDXGISwapChain1 * Direct3d::SwapChain()
{
    return m_dxgiSwapChain;
}
