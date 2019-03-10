#include "Triangle.h"

using namespace obj;

Triangle::Triangle(intf::Graphics * graphics) :
        m_graphics(graphics),
        m_vertices(nullptr),
        m_vertices_size(0)
{}

bool Triangle::Init()
{
    if (!m_graphics) return false;
    if (m_vertices) delete[] m_vertices;
    m_vertices = new Vertex[3];
    m_vertices_size = 3;

    m_vertices[0].X = 0.25f;
    m_vertices[0].Y = 0.75f;
    m_vertices[0].Z = 0.0f;
    m_vertices[0].Color.Red = 1.0f;
    m_vertices[0].Color.Green = 0.0f;
    m_vertices[0].Color.Blue = 0.0f;
    m_vertices[0].Color.Alpha = 1.0f;

    m_vertices[1].X = 0.5;
    m_vertices[1].Y = 0.25;
    m_vertices[1].Z = 0;
    m_vertices[1].Color.Red = 0.0f;
    m_vertices[1].Color.Green = 1.0f;
    m_vertices[1].Color.Blue = 0.0f;
    m_vertices[1].Color.Alpha = 1.0f;

    m_vertices[2].X = 0.75;
    m_vertices[2].Y = 0.75;
    m_vertices[2].Z = 0;
    m_vertices[2].Color.Red = 0.0f;
    m_vertices[2].Color.Green = 0.0f;
    m_vertices[2].Color.Blue = 1.0f;
    m_vertices[2].Color.Alpha = 1.0f;
    
    return false;
}

