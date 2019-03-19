#include "graphics/direct3d/vertex/Buffer.h"
#include "graphics/Direct3d.h"

using namespace graphics::direct3d::vertex;

Buffer::Buffer() :
    m_vertex_buffer(nullptr),
    m_size(0)
{}

Buffer::~Buffer()
{
    Cleanup();
}

bool Buffer::Init(utl::Vertex * vertices, const std::size_t & size)
{
    if (!vertices) return false;
    auto * device = Direct3d::GetInstance().Device();
    auto * device_constext = Direct3d::GetInstance().DeviceContext();

    m_size = size;

    D3D11_BUFFER_DESC buffer_desc;
    buffer_desc.ByteWidth = (UINT)(sizeof(utl::Vertex) * size);
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = NULL;
    buffer_desc.StructureByteStride = NULL;

    auto hr = device->CreateBuffer(&buffer_desc, NULL, &m_vertex_buffer);
    if (hr != S_OK) return false;

    D3D11_MAPPED_SUBRESOURCE map_subresource;
    map_subresource.pData = NULL;
    map_subresource.DepthPitch = NULL;
    map_subresource.RowPitch = NULL;

    hr = device_constext->Map(
        m_vertex_buffer, 
        NULL, 
        D3D11_MAP_WRITE_DISCARD, 
        NULL, 
        &map_subresource);
    if (hr != S_OK) return false;

    memcpy(map_subresource.pData, vertices, 
        sizeof(utl::Vertex) * size);

    device_constext->Unmap(m_vertex_buffer, NULL);
    return true;
}

bool Buffer::Draw()
{

    if (!m_vertex_buffer) return false;
    auto * device = Direct3d::GetInstance().Device();
    auto * device_constext = Direct3d::GetInstance().DeviceContext();
    auto * swap_chain = Direct3d::GetInstance().SwapChain();

    UINT stride = sizeof(utl::Vertex);
    UINT offset = 0;
    device_constext->IASetVertexBuffers(0, 1, &m_vertex_buffer, 
        &stride, &offset);

    device_constext->IASetPrimitiveTopology(
        D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    device_constext->Draw((UINT)m_size, 0);

    return true;
}

void Buffer::Cleanup()
{
    if (m_vertex_buffer) 
    {
        m_vertex_buffer->Release();
        m_vertex_buffer = nullptr;
    }
}

Buffer::operator bool() const
{
    return m_vertex_buffer;
}
