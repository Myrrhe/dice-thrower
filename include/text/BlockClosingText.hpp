#ifndef BLOCKCLOSINGTEXT_HPP
#define BLOCKCLOSINGTEXT_HPP
#include "NodeText.hpp"

class BlockClosingText final : public NodeText
{
public:
    BlockClosingText();
    ~BlockClosingText();
    BlockClosingText(const BlockClosingText& other);
    BlockClosingText& operator=(const BlockClosingText& rhs);

    void release() override;

    Type getType() const override;

    const std::u32string& getStr() const override;

    bool operator==(const NodeText& right) const override;
    bool operator!=(const NodeText& right) const override;

    std::u32string toStr() const override;

protected:

private:
};

#endif // BLOCKCLOSINGTEXT_HPP
