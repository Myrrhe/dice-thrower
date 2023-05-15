#include "InfoText.hpp"
#include "Global.hpp"
#include "func.hpp"
#include <cassert>

const std::array<std::u32string, 10> InfoText::Keys32 = {{U"font",
                                                          U"cSize",
                                                          U"leSpace",
                                                          U"liSpace",
                                                          U"style",
                                                          U"fColor",
                                                          U"oColor",
                                                          U"bColor",
                                                          U"sBack",
                                                          U"thick"}};

const char32_t InfoText::Separator = U',';

const InfoText InfoText::Default = InfoText();

InfoText::InfoText() :
font(nullptr),
charSize(30),
letterSpacing({true, 1.0f}),
lineSpacingFactor(1.0f),
style(Style::Regular),
fillColor(sf::Color(255, 255, 255, 255)),
outlineColor(sf::Color(0, 0, 0, 255)),
backColor(sf::Color(0, 0, 0, 0)),
sizeBack(0.0f, 0.0f),
thickness(0)
{
    //ctor
}

InfoText::~InfoText()
{
    //dtor
}

InfoText::InfoText(const InfoText& other) :
font(other.font),
charSize(other.charSize),
letterSpacing(other.letterSpacing),
lineSpacingFactor(other.lineSpacingFactor),
style(other.style),
fillColor(other.fillColor),
outlineColor(other.outlineColor),
backColor(other.backColor),
sizeBack(other.sizeBack),
thickness(other.thickness)
{
    //copy ctor
}

InfoText::InfoText(const sf::Font* newFont, long unsigned int newCharSize) :
font(newFont),
charSize(newCharSize),
letterSpacing({true, 1.0f}),
lineSpacingFactor(1.0f),
style(Style::Regular),
fillColor(sf::Color(255, 255, 255, 255)),
outlineColor(sf::Color(0, 0, 0, 255)),
backColor(sf::Color(0, 0, 0, 0)),
sizeBack(0.0f, 0.0f),
thickness(0)
{

}

InfoText::InfoText(const std::u32string& str) :
font(nullptr),
charSize(30),
letterSpacing({true, 1.0f}),
lineSpacingFactor(1.0f),
style(Style::Regular),
fillColor(sf::Color(255, 255, 255, 255)),
outlineColor(sf::Color(0, 0, 0, 255)),
backColor(sf::Color(0, 0, 0, 0)),
sizeBack(0.0f, 0.0f),
thickness(0)
{
    std::vector<std::u32string> vecStr = split(str, Separator);
    for (long unsigned int i = 0; i < vecStr.size(); i++)
    {
        std::pair<std::u32string, std::u32string> keyVal = getKeyValueLine(vecStr[i]);
        //std::cout << "keyVal = " << keyVal.first << ", " << keyVal.second << std::endl;
        if (keyVal.first == U"cSize")
        {
            charSize = str32ToLui(keyVal.second);
        }
        else if (keyVal.first == U"leSpace")
        {
            std::get<0>(letterSpacing) = keyVal.second[0] - U'0';
            std::get<1>(letterSpacing) = str32ToF(keyVal.second.substr(2, std::string::npos));
        }
        else if (keyVal.first == U"leSpaceFix")
        {
            std::get<0>(letterSpacing) = false;
            std::get<1>(letterSpacing) = str32ToF(keyVal.second);
        }
        else if (keyVal.first == U"liSpace")
        {
            lineSpacingFactor = str32ToF(keyVal.second);
        }
        else if (keyVal.first == U"style")
        {
            style = static_cast<Style>(str32ToLui(keyVal.second));
        }
        else if (keyVal.first == U"fColor")
        {
            fillColor = sf::Color(str32HexToLui(keyVal.second));
        }
        else if (keyVal.first == U"oColor")
        {
            outlineColor = sf::Color(str32HexToLui(keyVal.second));
        }
        else if (keyVal.first == U"bColor")
        {
            backColor = sf::Color(str32HexToLui(keyVal.second));
        }
        else if (keyVal.first == U"posBack")
        {
            sizeBack.x = str32ToF(keyVal.second);
        }
        else if (keyVal.first == U"heiBack")
        {
            sizeBack.y = str32ToF(keyVal.second);
        }
        else if (keyVal.first == U"thick")
        {
            thickness = str32ToF(keyVal.second);
        }
    }
}

InfoText& InfoText::operator=(const InfoText& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    font = rhs.font;
    charSize = rhs.charSize;
    letterSpacing = rhs.letterSpacing;
    lineSpacingFactor = rhs.lineSpacingFactor;
    style = rhs.style;
    fillColor = rhs.fillColor;
    outlineColor = rhs.outlineColor;
    backColor = rhs.backColor;
    sizeBack = rhs.sizeBack;
    thickness = rhs.thickness;
    //assignment operator
    return *this;
}

void InfoText::setFont(const sf::Font* newFont)
{
    font = newFont;
}

void InfoText::setCharSize(long unsigned int newCharSize)
{
    charSize = newCharSize;
}

void InfoText::setLetterSpacing(const std::tuple<bool, float>& newLetterSpacing)
{
    letterSpacing = newLetterSpacing;
}

void InfoText::setLineSpacingFactor(float newLineSpacingFactor)
{
    lineSpacingFactor = newLineSpacingFactor;
}

void InfoText::setStyle(Style newStyle)
{
    style = newStyle;
}

void InfoText::setFillColor(sf::Color newFillColor)
{
    fillColor = newFillColor;
}

void InfoText::setOutlineColor(sf::Color newOutlineColor)
{
    outlineColor = newOutlineColor;
}

void InfoText::setBackColor(sf::Color newBackColor)
{
    backColor = newBackColor;
}

void InfoText::setSizeBack(const sf::Vector2<float>& newSizeBack)
{
    sizeBack = newSizeBack;
}

void InfoText::setThickness(float newThickness)
{
    thickness = newThickness;
}

const sf::Font* InfoText::getFont() const
{
    return font;
}

long unsigned int InfoText::getCharSize() const
{
    return charSize;
}

const std::tuple<bool, float>& InfoText::getLetterSpacing() const
{
    return letterSpacing;
}

float InfoText::getLineSpacingFactor() const
{
    return lineSpacingFactor;
}

InfoText::Style InfoText::getStyle() const
{
    return style;
}

sf::Color InfoText::getFillColor() const
{
    return fillColor;
}

sf::Color InfoText::getOutlineColor() const
{
    return outlineColor;
}

sf::Color InfoText::getBackColor() const
{
    return backColor;
}

const sf::Vector2<float>& InfoText::getSizeBack() const
{
    return sizeBack;
}

float InfoText::getThickness() const
{
    return thickness;
}
/*
template<class I, InfoText::Info T> const I& InfoText::getInfo() const
{
    return reinterpret_cast<const I&>(0);
}

template<>
const sf::Font*& InfoText::getInfo<const sf::Font*, InfoText::Info::FONT>() const
{
    return font;
}
*/

template<> InfoText::Typer<InfoText::Info::FONT>::Type                InfoText::getInfo<InfoText::Info::FONT>()                const { return font; }
template<> InfoText::Typer<InfoText::Info::CHAR_SIZE>::Type           InfoText::getInfo<InfoText::Info::CHAR_SIZE>()           const { return charSize; }
template<> InfoText::Typer<InfoText::Info::LETTER_SPACING>::Type      InfoText::getInfo<InfoText::Info::LETTER_SPACING>()      const { return letterSpacing; }
template<> InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>::Type InfoText::getInfo<InfoText::Info::LINE_SPACING_FACTOR>() const { return lineSpacingFactor; }
template<> InfoText::Typer<InfoText::Info::STYLE>::Type               InfoText::getInfo<InfoText::Info::STYLE>()               const { return style; }
template<> InfoText::Typer<InfoText::Info::FILL_COLOR>::Type          InfoText::getInfo<InfoText::Info::FILL_COLOR>()          const { return fillColor; }
template<> InfoText::Typer<InfoText::Info::OUTLINE_COLOR>::Type       InfoText::getInfo<InfoText::Info::OUTLINE_COLOR>()       const { return outlineColor; }
template<> InfoText::Typer<InfoText::Info::BACK_COLOR>::Type          InfoText::getInfo<InfoText::Info::BACK_COLOR>()          const { return backColor; }
template<> InfoText::Typer<InfoText::Info::SIZE_BACK>::Type           InfoText::getInfo<InfoText::Info::SIZE_BACK>()           const { return sizeBack; }
template<> InfoText::Typer<InfoText::Info::THICKNESS>::Type           InfoText::getInfo<InfoText::Info::THICKNESS>()           const { return thickness; }

template<> void InfoText::setInfo<InfoText::Info::FONT>(InfoText::Typer<InfoText::Info::FONT>::Type t)                               { font = t; }
template<> void InfoText::setInfo<InfoText::Info::CHAR_SIZE>(InfoText::Typer<InfoText::Info::CHAR_SIZE>::Type t)                     { charSize = t; }
template<> void InfoText::setInfo<InfoText::Info::LETTER_SPACING>(InfoText::Typer<InfoText::Info::LETTER_SPACING>::Type t)           { letterSpacing = t; }
template<> void InfoText::setInfo<InfoText::Info::LINE_SPACING_FACTOR>(InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>::Type t) { lineSpacingFactor = t; }
template<> void InfoText::setInfo<InfoText::Info::STYLE>(InfoText::Typer<InfoText::Info::STYLE>::Type t)                             { style = t; }
template<> void InfoText::setInfo<InfoText::Info::FILL_COLOR>(InfoText::Typer<InfoText::Info::FILL_COLOR>::Type t)                   { fillColor = t; }
template<> void InfoText::setInfo<InfoText::Info::OUTLINE_COLOR>(InfoText::Typer<InfoText::Info::OUTLINE_COLOR>::Type t)             { outlineColor = t; }
template<> void InfoText::setInfo<InfoText::Info::BACK_COLOR>(InfoText::Typer<InfoText::Info::BACK_COLOR>::Type t)                   { backColor = t; }
template<> void InfoText::setInfo<InfoText::Info::SIZE_BACK>(InfoText::Typer<InfoText::Info::SIZE_BACK>::Type t)                     { sizeBack = t; }
template<> void InfoText::setInfo<InfoText::Info::THICKNESS>(InfoText::Typer<InfoText::Info::THICKNESS>::Type t)                     { thickness = t; }

bool InfoText::operator==(const InfoText& right) const
{
    return font == right.font
        && charSize == right.charSize
        && std::get<0>(letterSpacing) == std::get<0>(right.letterSpacing)
        && std::abs(std::get<1>(letterSpacing) - std::get<1>(right.letterSpacing)) < m_epsilon_f
        && std::abs(lineSpacingFactor - right.lineSpacingFactor) < m_epsilon_f
        && style == right.style
        && fillColor == right.fillColor
        && outlineColor == right.outlineColor
        && backColor == right.backColor
        && std::abs(sizeBack.x - right.sizeBack.x) < m_epsilon_f
        && std::abs(sizeBack.y - right.sizeBack.y) < m_epsilon_f
        && std::abs(thickness - right.thickness) < m_epsilon_f;
}

bool InfoText::operator!=(const InfoText& right) const
{
    return !(*this == right);
}

std::u32string InfoText::getValStr(Info i) const
{
    std::u32string res = U"";
    switch (i)
    {
        case Info::FONT:
        {
            std::basic_stringstream<char32_t, std::char_traits<char32_t> > ss;
            ss << font;
            res = ss.str();
            break;
        }
        case Info::CHAR_SIZE:
        {
            res = luiTo32Str(charSize);
            break;
        }
        case Info::LETTER_SPACING:
        {
            res = luiTo32Str(static_cast<long unsigned int>(std::get<0>(letterSpacing))) + U";" + fTo32Str(std::get<1>(letterSpacing));
            break;
        }
        case Info::LINE_SPACING_FACTOR:
        {
            res = fTo32Str(lineSpacingFactor);
            break;
        }
        case Info::STYLE:
        {
            res = luiTo32Str(static_cast<long unsigned int>(style));
            break;
        }
        case Info::FILL_COLOR:
        {
            res = luiTo32StrHex(fillColor.toInteger());
            break;
        }
        case Info::OUTLINE_COLOR:
        {
            res = luiTo32StrHex(outlineColor.toInteger());
            break;
        }
        case Info::BACK_COLOR:
        {
            res = luiTo32StrHex(backColor.toInteger());
            break;
        }
        case Info::SIZE_BACK:
        {
            res = fTo32Str(sizeBack.x) + U";" + fTo32Str(sizeBack.y);
            break;
        }
        case Info::THICKNESS:
        {
            res = fTo32Str(thickness);
            break;
        }
        default:
        {
            break;
        }
    }
    return res;
}

const std::u32string& InfoText::getKeyStr32(Info i)
{
    switch (i)
    {
        case Info::FONT:                { return Keys32[0]; break; }
        case Info::CHAR_SIZE:           { return Keys32[1]; break; }
        case Info::LETTER_SPACING:      { return Keys32[2]; break; }
        case Info::LINE_SPACING_FACTOR: { return Keys32[3]; break; }
        case Info::STYLE:               { return Keys32[4]; break; }
        case Info::FILL_COLOR:          { return Keys32[5]; break; }
        case Info::OUTLINE_COLOR:       { return Keys32[6]; break; }
        case Info::BACK_COLOR:          { return Keys32[7]; break; }
        case Info::SIZE_BACK:           { return Keys32[8]; break; }
        case Info::THICKNESS:           { return Keys32[9]; break; }
        default:                        { return Global::EmptyStr32; break; }
    }
}

InfoText::Info operator++(InfoText::Info& i, int)
{
    assert(i != InfoText::Info::NB_INFO);
    i = static_cast<InfoText::Info>(static_cast<long unsigned int>(i) + 1);
    return static_cast<InfoText::Info>(static_cast<long unsigned int>(i) - 1);
}

long unsigned int operator|(const InfoText::Style& left, const InfoText::Style& right)
{
    return static_cast<unsigned int>(left) | static_cast<unsigned int>(right);
}

long unsigned int operator|(long unsigned int left, const InfoText::Style& right)
{
    return left | static_cast<unsigned int>(right);
}

long unsigned int operator&(const InfoText::Style& left, const InfoText::Style& right)
{
    return static_cast<unsigned int>(left) & static_cast<unsigned int>(right);
}

std::ostream& operator<<(std::ostream& os, InfoText::Style right)
{
    return os << static_cast<long unsigned int>(right);
}
