#include "graphics/direct3d/Shader.h"
#include "graphics/Direct3d.h"

#include <d3dcompiler.h>

using namespace std;
using namespace graphics;
using namespace graphics::direct3d;
using namespace defn;

Shader::Shader() :
    m_vertexCompiled(nullptr),
    m_pixelCompiled(nullptr),
    m_vertex(nullptr),
    m_pixel(nullptr)
{}

Shader::~Shader()
{
    if (m_vertexCompiled) m_vertexCompiled->Release();
    if (m_pixelCompiled) m_pixelCompiled->Release();
    if (m_vertex) m_vertex->Release();
    if (m_pixel) m_pixel->Release();
}

bool Shader::Attach()
{
    if (!m_vertex || !m_pixel) return false;
    auto & graphics = Direct3d::GetInstance();
    auto * device = graphics.Device();
    auto * device_constext = graphics.DeviceContext();
    device_constext->VSSetShader(m_vertex, NULL, NULL);
    device_constext->PSSetShader(m_pixel, NULL, NULL);
    return true;
}

bool Shader::CompileString(categ::Shader categ, std::string str)
{
    auto & graphics = Direct3d::GetInstance();
    auto * device = graphics.Device();
    auto * device_constext = graphics.DeviceContext();
    if (categ == categ::Shader::vertex)
    {
        if (m_vertexCompiled) m_vertexCompiled->Release();
        m_vertexCompiled = nullptr;
        auto hr = D3DCompile(str.c_str(), str.size(), 
            NULL, 
            NULL, 
            NULL, 
            "main_vs",
            "vs_4_0",
            NULL,
            NULL,
            &m_vertexCompiled,
            NULL);
        if (hr != S_OK) return false;
        hr = device->CreateVertexShader(
            m_vertexCompiled->GetBufferPointer(),
            m_vertexCompiled->GetBufferSize(),
            NULL,
            &m_vertex);
        return hr == S_OK;
    }
    else if (categ == categ::Shader::pixel ||
        categ == categ::Shader::fragment)
    {
        if (m_pixelCompiled) m_pixelCompiled->Release();
        m_pixelCompiled = nullptr;
        auto hr = D3DCompile(str.c_str(), str.size(), 
            NULL, 
            NULL, 
            NULL, 
            "main_ps",
            "fs_4_0",
            NULL,
            NULL,
            &m_pixelCompiled,
            NULL);
        return hr == S_OK;
        hr = device->CreatePixelShader(
            m_pixelCompiled->GetBufferPointer(),
            m_pixelCompiled->GetBufferSize(),
            NULL,
            &m_pixel);
        return hr == S_OK;
    }
    return false;
}

Shader::operator bool()
{
    return m_vertex && m_pixel;
}
