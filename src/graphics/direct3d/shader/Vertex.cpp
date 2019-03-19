#include "graphics/direct3d/shader/Vertex.h"
#include "graphics/Direct3d.h"

#include <d3dcompiler.h>

using namespace std;
using namespace graphics;
using namespace graphics::direct3d::shader;

Vertex::Vertex() :
    intf::graphics::Shader(defn::categ::Shader::pixel),
    m_compiled(nullptr),
    m_vertex_shader(nullptr)
{}

Vertex::~Vertex()
{
    Cleanup();
}

bool Vertex::Attach()
{
    if (!m_compiled) return false;
    auto * device_constext = Direct3d::GetInstance().DeviceContext();
    device_constext->VSSetShader(m_vertex_shader, NULL, NULL);
    return true;
}

bool Vertex::CompileString(std::string str)
{
    if (m_compiled) return true;
    auto * device = Direct3d::GetInstance().Device();
    auto * device_constext = Direct3d::GetInstance().DeviceContext();
    if (m_compiled) 
    {
        m_compiled->Release();
        m_compiled = nullptr;
    }
    auto hr = D3DCompile(str.c_str(), str.size(), 
        NULL, 
        NULL, 
        NULL, 
        "main_vs",
        "vs_4_0",
        NULL,
        NULL,
        &m_compiled,
        NULL);
    if (hr != S_OK) return false;
    hr = device->CreateVertexShader(
        m_compiled->GetBufferPointer(),
        m_compiled->GetBufferSize(),
        NULL,
        &m_vertex_shader);
    if (hr != S_OK) return false;
    
    D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    hr = device->CreateInputLayout(
        input_element_desc, 
        2, 
        m_compiled->GetBufferPointer(), 
        m_compiled->GetBufferSize(), 
        &m_input_layout);
    if (hr != S_OK) return false;

    device_constext->IASetInputLayout(m_input_layout);
    return true;
}

void Vertex::Cleanup()
{
    if (m_compiled) 
    {
        m_compiled->Release();
        m_compiled = nullptr;
    }
    if (m_vertex_shader) 
    {
        m_vertex_shader->Release();
        m_vertex_shader = nullptr;
    }
}

Vertex::operator bool() const
{
    return m_compiled;
}

