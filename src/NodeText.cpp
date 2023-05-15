#include "NodeText.hpp"
#include <iostream>
#include <istream>

NodeText::NodeText()
{
    //ctor
}

NodeText::~NodeText()
{
    //dtor
}

NodeText::NodeText(const NodeText& /*other*/)
{
    //copy ctor
}

NodeText& NodeText::operator=(const NodeText& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    return *this;
}

std::ostream& operator<<(std::ostream& os, const NodeText::Type& right)
{
    return os << static_cast<long unsigned int>(right);
}
