#include "Triangle.h"
#include "defn/Graphics.h"

using namespace utl;
using namespace defn;

Triangle::Triangle(intf::Graphics * graphics) :
        m_graphics(graphics),
        m_vertices(nullptr),
        m_vertices_size(0)
{
    m_hl_shader = 
        "struct VOut"
        "{"
        "   float4 position : SV_POSITION;"
        "   float4 color : COLOR;"
        "};"
        "VOut main_vs(float4 position : POSITION, float4 color : COLOR)"
        "{"
        "   VOut output;"
        "   output.position = position;"
        "   output.color = color;"
        "   return output;"
        "}"
        "float4 main_ps(float4 position : SV_POSITION, "
        "   float4 color : COLOR) : SV_TARGET"
        "{"
        "   return color;"
        "}";
}

Triangle::~Triangle() 
{
}

bool Triangle::Init()
{
    if (!m_graphics) return false;
    if (!m_vertex_shader)
        m_vertex_shader = m_graphics->MakeShader(categ::Shader::vertex);
    if (!m_fragment_shader)
        m_fragment_shader = m_graphics->MakeShader(categ::Shader::fragment);
    if (m_graphics->Category() == Graphics::direct3d)
    {
        m_fragment_shader->CompileString(m_hl_shader);
        m_vertex_shader->CompileString(m_hl_shader);
    }

    if (m_vertices) delete[] m_vertices;
    m_vertices = new Vertex[3];
    m_vertices_size = 3;

    m_vertices[1].X = 0.45f;
    m_vertices[1].Y = -0.5f;
    m_vertices[1].Z = 0.0f;
    m_vertices[0].Color.Red = 1.0f;
    m_vertices[0].Color.Green = 0.0f;
    m_vertices[0].Color.Blue = 0.0f;
    m_vertices[0].Color.Alpha = 1.0f;

    m_vertices[0].X = 0.0f;
    m_vertices[0].Y = 0.5f;
    m_vertices[0].Z = 0.0f;
    m_vertices[1].Color.Red = 0.0f;
    m_vertices[1].Color.Green = 1.0f;
    m_vertices[1].Color.Blue = 0.0f;
    m_vertices[1].Color.Alpha = 1.0f;

    m_vertices[2].X = -0.45f;
    m_vertices[2].Y = -0.5f;
    m_vertices[2].Z = 0.0f;
    m_vertices[2].Color.Red = 0.0f;
    m_vertices[2].Color.Green = 0.0f;
    m_vertices[2].Color.Blue = 1.0f;
    m_vertices[2].Color.Alpha = 1.0f;

    if (!m_vertex)
        m_vertex = m_graphics->MakeVertex();
    
    return m_vertex->Init(m_vertices, 3);
}

bool Triangle::Draw()
{
    m_vertex_shader->Attach();
    m_fragment_shader->Attach();
    return m_vertex->Draw();
}