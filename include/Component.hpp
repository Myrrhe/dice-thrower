#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include "NonCopyable.hpp"
#include "Entity.hpp"

class Component final : public NonCopyable
{
public:
    Component();
    ~Component();
protected:
private:
    Entity e;
};

#endif // COMPONENT_HPP
