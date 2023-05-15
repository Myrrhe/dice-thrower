#include "Visitor.hpp"
#include "Global.hpp"
#include "func.hpp"

Visitor::Visitor()
{

}

Visitor::~Visitor()
{

}

Visitor::Visitor(const Visitor& /*other*/)
{

}

Visitor& Visitor::operator=(const Visitor& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    return *this;
}
