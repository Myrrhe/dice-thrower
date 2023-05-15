#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity final
{
public:

    Entity();
    ~Entity();
    Entity(const Entity& other);
    Entity& operator=(const Entity& rhs);

    bool operator==(const Entity& entity) const;
    static Entity generate();

protected:
private:
    long unsigned int id;
};

#endif // ENTITY_HPP
