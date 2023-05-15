#ifndef LEAFTEXT_HPP
#define LEAFTEXT_HPP
#include "NodeText.hpp"
#include <string>

class LeafText final : public NodeText
{
public:
    LeafText();
    ~LeafText();
    LeafText(const LeafText& other);
    LeafText(const std::u32string& newStr);
    LeafText(char32_t char32);
    LeafText& operator=(const LeafText& other);

    void release() override;

    void addChar(char32_t char32, long unsigned int posAdd);
    void addChar(char32_t char32);

    void popChar(long unsigned int posPop);
    void popChar();

    void delChar(long unsigned int posInit, long unsigned int posFina);

    void trimRight(long unsigned int posTrim);
    void trimLeft(long unsigned int posTrim);

    void mergeLeaf(const LeafText& leafText);

    Type getType() const override;

    bool isEmpty() const;

    const std::u32string& getStr() const override;

    std::size_t getSize() const;

    bool operator==(const NodeText& right) const override;
    bool operator!=(const NodeText& right) const override;

    std::u32string toStr() const override;

protected:

private:
    std::u32string str;
};

#endif // LEAFTEXT_HPP
