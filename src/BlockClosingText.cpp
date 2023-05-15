#include "BlockClosingText.hpp"
#include "Global.hpp"

BlockClosingText::BlockClosingText() : NodeText()
{
    //ctor
}

BlockClosingText::~BlockClosingText()
{
    //dtor
}

BlockClosingText::BlockClosingText(const BlockClosingText& other) : NodeText(other)
{
    //copy ctor
}

BlockClosingText& BlockClosingText::operator=(const BlockClosingText& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    NodeText::operator=(rhs);
    return *this;
}

void BlockClosingText::release()
{

}

NodeText::Type BlockClosingText::getType() const
{
    return Type::BLOCKCLOSING;
}

bool BlockClosingText::operator==(const NodeText& right) const
{
    if (getType() != right.getType())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool BlockClosingText::operator!=(const NodeText& right) const
{
    return !(*this == right);
}

const std::u32string& BlockClosingText::getStr() const
{
    return Global::EmptyStr32;
}

std::u32string BlockClosingText::toStr() const
{
    return U"</>";
}
