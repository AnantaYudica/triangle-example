#ifndef INTF_GRAPHICS_SHADER_H_
#define INTF_GRAPHICS_SHADER_H_

#include "../../defn/categ/Shader.h"

#include <string>

namespace intf
{
namespace graphics
{

class Shader
{
public:
    Shader();
public:
    virtual ~Shader() = default;
public:
    virtual bool Attach();
public:
    virtual bool CompileString(defn::categ::Shader categ, 
        std::string str) = 0;
public:
    virtual operator bool() = 0;
};

} //!graphics

} //!intf

#endif //!INTF_GRAPHICS_SHADER_H_