#include "graphics/wgl.h"

using namespace std;
using namespace graphics;

Wgl Wgl::ms_instance;

Wgl & Wgl::GetInstance()
{
    return ms_instance;
}

Wgl::Wgl()
{}

Wgl::~Wgl()
{}

typename Wgl::CategoryType 
Wgl::Category()
{
    return CategoryType::wgl;
}

bool Wgl::Init(HWND hwnd)
{
    HDC device_context = GetDC(hwnd);

    EGLAttrib platform_display_attrib[]
    {
        EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_OPENGL_ANGLE,
        EGL_NONE
    };

    m_display = eglGetPlatformDisplay(EGL_PLATFORM_ANGLE_ANGLE,
        device_context, platform_display_attrib);

    eglInitialize(m_display, NULL, NULL);

    EGLint config_attrib[]{
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };

    eglChooseConfig(m_display, config_attrib, &m_config, 1, &m_numConfig);

    EGLint context_attrib[]{
        EGL_CONTEXT_MAJOR_VERSION, 2,
        EGL_CONTEXT_MINOR_VERSION, 0,
        EGL_NONE
    };

    m_context = eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, context_attrib);

    m_surface = eglCreateWindowSurface(m_display, m_config, hwnd, NULL);

    eglMakeCurrent(m_display, m_surface, m_surface, m_context);

    return true;
}

bool Wgl::BeginDraw()
{
    
    return true;
}

bool Wgl::EndDraw()
{
    return true;
}

void Wgl::Cleanup()
{
    eglDestroySurface(m_display, m_surface);
    eglDestroyContext(m_display, m_context);
}

typename Wgl::ShaderInterfacePointerType
Wgl::MakeShader(const ShaderCategoryType & categ)
{
    return ShaderInterfacePointerType(new wgl::shader::Vertex());
}

typename Wgl::VertexInterfacePointerType Wgl::MakeVertex()
{
    return nullptr;
}