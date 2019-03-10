#ifndef INTF_GRAPHICS_H_
#define INTF_GRAPHICS_H_

namespace intf
{

class Graphics
{
public:
    Graphics() = default;
public:
    virtual ~Graphics() = default;
public:
    virtual bool Draw() = 0;
    virtual void Cleanup() = 0;
};

} //!intf

#endif //!INTF_GRAPHICS_H_