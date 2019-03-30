#ifndef GRAPHICS_WGL_H_
#define GRAPHICS_WGL_H_

#include "../intf/Graphics.h"
#include "wgl/shader/Vertex.h"
#include "wgl/shader/Fragment.h"

#include <Windows.h>
#include "EGL/egl.h"

namespace graphics
{

class Wgl
{
public:
    typedef defn::categ::Shader ShaderCategoryType;
    typedef defn::Graphics CategoryType;
public:
    typedef intf::graphics::Shader ShaderInterfaceType;
    typedef intf::graphics::Vertex VertexInterfaceType;
    typedef typename ShaderInterfaceType::PointerType
        ShaderInterfacePointerType;
    typedef typename VertexInterfaceType::PointerType
        VertexInterfacePointerType;
private:
    EGLDisplay m_display;
    EGLConfig m_config;
    EGLContext m_context;
    EGLSurface m_surface;
    EGLint m_numConfig;
private:
    static Wgl ms_instance;
public:
    static Wgl & GetInstance();
private:
    Wgl();
public:
    ~Wgl();
public:
    CategoryType Category();
public:
    bool Init(HWND hwnd);
public:
    bool BeginDraw();
    bool EndDraw();
public:
    void Cleanup();
public:
    ShaderInterfacePointerType 
        MakeShader(const ShaderCategoryType & categ);
    VertexInterfacePointerType MakeVertex();
};

} //!graphics

#endif //!GRAPHICS_WGL_H_