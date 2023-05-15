#ifndef BLOCKINFOTEXT_HPP
#define BLOCKINFOTEXT_HPP
#include "InfoText.hpp"
#include "NodeText.hpp"

class BlockInfoText final : public NodeText
{
public:
    BlockInfoText();
    ~BlockInfoText();
    BlockInfoText(const BlockInfoText& other);
    BlockInfoText(const InfoText& newInfoText);
    BlockInfoText(const std::u32string& str);
    BlockInfoText& operator=(const BlockInfoText& rhs);

    void release() override;

    Type getType() const override;

    const sf::Font* getFont() const;
    long unsigned int getCharSize() const;
    const std::tuple<bool, float>& getLetterSpacing() const;
    float getLineSpacingFactor() const;
    InfoText::Style getStyle() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    sf::Color getBackColor() const;
    const sf::Vector2<float> getSizeBack() const;
    float getThickness() const;

    bool isUsed(long unsigned int i) const;
    bool isUsed(InfoText::Info info) const;
    bool isUseful() const;

    const InfoText& getInfoText() const;

    const std::u32string& getStr() const override;

    bool operator==(const NodeText& right) const override;
    bool operator!=(const NodeText& right) const override;

    BlockInfoText& operator+=(const BlockInfoText& right);
    BlockInfoText operator+(const BlockInfoText& right) const;

    std::u32string toStr() const override;

protected:

private:
    void setUsed(InfoText::Info info, bool newUsed);

    InfoText infoText;
    std::array<bool, 9> useInfo;
};

#endif // BLOCKINFOTEXT_HPP
