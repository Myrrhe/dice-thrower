#include "text/LeafText.hpp"

LeafText::LeafText() : NodeText(),
    str(U"")
{
    //ctor
}

LeafText::~LeafText()
{
    //dtor
}

LeafText::LeafText(const LeafText& other) : NodeText(other),
    str(other.str)
{
    //copy ctor
}

LeafText::LeafText(const std::u32string& newStr) : NodeText(),
    str(newStr)
{

}

LeafText::LeafText(char32_t char32) : NodeText(),
    str(std::u32string(1, char32))
{

}

LeafText& LeafText::operator=(const LeafText& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    NodeText::operator=(rhs);
    str = rhs.str;
    return *this;
}

void LeafText::release()
{

}

void LeafText::addChar(char32_t char32, long unsigned int posAdd)
{
    str.insert(str.cbegin() + static_cast<long int>(posAdd), char32);
}

void LeafText::addChar(char32_t char32)
{
    str += char32;
}

void LeafText::popChar(long unsigned int posPop)
{
    str.erase(str.cbegin() + static_cast<long int>(posPop));
}

void LeafText::popChar()
{
    str.pop_back();
}

void LeafText::delChar(long unsigned int posInit, long unsigned int posFina)
{
    str.erase(posInit, posFina - posInit + 1);
}

void LeafText::trimRight(long unsigned int posTrim)
{
    str.erase(posTrim, std::string::npos);
}

void LeafText::trimLeft(long unsigned int posTrim)
{
    str.erase(0, posTrim);
}

void LeafText::mergeLeaf(const LeafText& leafText)
{
    str += leafText.str;
}

NodeText::Type LeafText::getType() const
{
    return Type::LEAF;
}

bool LeafText::isEmpty() const
{
    return str.empty();
}

const std::u32string& LeafText::getStr() const
{
    return str;
}

std::size_t LeafText::getSize() const
{
    return str.size();
}

bool LeafText::operator==(const NodeText& right) const
{
    if (getType() != right.getType())
    {
        return false;
    }
    else
    {
        return str == dynamic_cast<const LeafText*>(&right)->str;
    }
}

bool LeafText::operator!=(const NodeText& right) const
{
    return !(*this == right);
}

std::u32string LeafText::toStr() const
{
    return str;
}
