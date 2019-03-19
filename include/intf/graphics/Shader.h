#ifndef INTF_GRAPHICS_SHADER_H_
#define INTF_GRAPHICS_SHADER_H_

#include "../../defn/categ/Shader.h"

#include <string>
#include <memory>

namespace intf
{
namespace graphics
{

class Shader
{
public:
    typedef std::shared_ptr<Shader> PointerType;
    typedef defn::categ::Shader CategoryType;
private:
    CategoryType m_category;
public:
    Shader();
    Shader(const CategoryType categ);
public:
    virtual ~Shader() = default;
public:
    CategoryType Category() const;
public:
    virtual bool Attach() = 0;
public:
    virtual bool CompileString(std::string str) = 0;
public:
    virtual void Cleanup() = 0;
public:
    virtual operator bool() const = 0;
};

} //!graphics

} //!intf

#endif //!INTF_GRAPHICS_SHADER_H_