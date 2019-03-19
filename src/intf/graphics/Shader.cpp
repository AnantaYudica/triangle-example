#include "intf/graphics/Shader.h"

using namespace std;
using namespace intf::graphics;

Shader::Shader() :
    m_category(CategoryType::undefined)
{}

Shader::Shader(const CategoryType categ) :
    m_category(categ)
{}

typename Shader::CategoryType Shader::Category() const
{
    return m_category;
}
