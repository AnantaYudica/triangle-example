#ifndef INTF_GRAPHICS_H_
#define INTF_GRAPHICS_H_

#include "graphics/Shader.h"
#include "graphics/Vertex.h"
#include "../defn/categ/Shader.h"
#include "../defn/Graphics.h"


namespace intf
{

class Graphics
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
public:
    Graphics() = default;
public:
    virtual ~Graphics() = default;
public:
    virtual CategoryType Category() = 0;
public:
    virtual bool BeginDraw() = 0;
    virtual bool EndDraw() = 0;
public:
    virtual void Cleanup() = 0;
public:
    virtual ShaderInterfacePointerType 
        MakeShader(const ShaderCategoryType & categ) = 0;
    virtual VertexInterfacePointerType MakeVertex() = 0;
};

} //!intf

#endif //!INTF_GRAPHICS_H_