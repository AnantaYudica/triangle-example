#include "graphics/direct3d/shader/Pixel.h"
#include "graphics/Direct3d.h"

#include <d3dcompiler.h>

using namespace std;
using namespace graphics;
using namespace graphics::direct3d::shader;

Pixel::Pixel() :
    intf::graphics::Shader(defn::categ::Shader::pixel),
    m_compiled(nullptr),
    m_pixel_shader(nullptr)
{}

Pixel::~Pixel()
{
    Cleanup();
}

bool Pixel::Attach()
{
    if (!m_compiled) return false;
    auto * device_constext = Direct3d::GetInstance().DeviceContext();
    device_constext->PSSetShader(m_pixel_shader, NULL, NULL);
    return true;
}

bool Pixel::CompileString(std::string str)
{
    if (m_compiled) return true;
    auto * device = Direct3d::GetInstance().Device();
    if (m_compiled) 
    {
        m_compiled->Release();
        m_compiled = nullptr;
    }
    auto hr = D3DCompile(str.c_str(), str.size(), 
        NULL, 
        NULL, 
        NULL, 
        "main_ps",
        "ps_4_0",
        NULL,
        NULL,
        &m_compiled,
        NULL);
    if (hr != S_OK) return false;
    hr = device->CreatePixelShader(
        m_compiled->GetBufferPointer(),
        m_compiled->GetBufferSize(),
        NULL,
        &m_pixel_shader);
    return hr == S_OK;
}

void Pixel::Cleanup()
{
    if (m_compiled) 
    {
        m_compiled->Release();
        m_compiled = nullptr;
    }
    if (m_pixel_shader) 
    {
        m_pixel_shader->Release();
        m_pixel_shader = nullptr;
    }
}

Pixel::operator bool() const
{
    return m_compiled;
}

