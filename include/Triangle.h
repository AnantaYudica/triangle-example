#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "intf/Graphics.h"
#include "Vertex.h"

class Triangle
{
private:
    intf::Graphics * m_graphics;
    Vertex * m_vertices;
    int m_vertices_size;
public:
    Triangle(intf::Graphics * graphics);
    ~Triangle();
public:
    Triangle(const Triangle & cpy) = delete;
    Triangle(Triangle && mov) = delete;
public:
    Triangle & operator=(const Triangle & cpy) = delete;
    Triangle & operator=(Triangle && mov) = delete;
public:
    bool Init();
};

#endif //!TRIANGLE_H_