#ifndef NODETEXT_HPP
#define NODETEXT_HPP
#include <string>

class NodeText
{
public:

    enum class Type : long unsigned int
    {
        LEAF,
        BLOCK,
        BLOCKINFO,
        BLOCKCLOSING
    };

    NodeText();
    virtual ~NodeText();
    NodeText(const NodeText& other);
    NodeText& operator=(const NodeText& rhs);

    virtual void release() = 0;

    virtual Type getType() const = 0;

    virtual const std::u32string& getStr() const = 0;

    virtual bool operator==(const NodeText& right) const = 0;
    virtual bool operator!=(const NodeText& right) const = 0;

    virtual std::u32string toStr() const = 0;

protected:

private:
};
std::ostream& operator<<(std::ostream& os, const NodeText::Type& right);

#endif // NODETEXT_HPP
