#include "Entity.hpp"
#include "Global.hpp"
#include "func.hpp"

Entity::Entity() : id(0)
{

}

Entity::~Entity()
{

}

Entity::Entity(const Entity& other) : id(other.id)
{

}

Entity& Entity::operator=(const Entity& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    id = rhs.id;
    return *this;
}

bool Entity::operator==(const Entity& entity) const
{
    return id == entity.id;
}

Entity Entity::generate()
{
    return Entity();
}
