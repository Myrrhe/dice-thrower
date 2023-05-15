#ifndef INFOTEXT_HPP
#define INFOTEXT_HPP
#include <SFML/Graphics.hpp>

class InfoText final
{
public:

    enum class Info : long unsigned int
    {
        INFO_BEGIN = 0,
        FONT = INFO_BEGIN,
        CHAR_SIZE,
        LETTER_SPACING,
        LINE_SPACING_FACTOR,
        STYLE,
        FILL_COLOR,
        OUTLINE_COLOR,
        BACK_COLOR,
        SIZE_BACK,
        THICKNESS,
        NB_INFO = THICKNESS
    };

    enum class Style : long unsigned int
    {
        Regular       = 0,      ///< Regular characters, no style
        Bold          = 1 << 0, ///< Bold characters
        Italic        = 1 << 1, ///< Italic characters
        Underlined    = 1 << 2, ///< Underlined characters
        StrikeThrough = 1 << 3  ///< Strike through characters
    };

    /** Default constructor */
    InfoText();
    /** Default destructor */
    ~InfoText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    InfoText(const InfoText& other);
    InfoText(const sf::Font* newFont, long unsigned int newCharSize);
    InfoText(const std::u32string& str);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    InfoText& operator=(const InfoText& rhs);

    void setFont(const sf::Font* newFont);
    void setCharSize(long unsigned int newCharSize);
    void setLetterSpacing(const std::tuple<bool, float>& newLetterSpacing);
    void setLineSpacingFactor(float newLineSpacingFactor);
    void setStyle(Style newStyle);
    void setFillColor(sf::Color newFillColor);
    void setOutlineColor(sf::Color newOutlineColor);
    void setBackColor(sf::Color newBackColor);
    void setSizeBack(const sf::Vector2<float>& newSizeBack);
    void setThickness(float newThickness);

    const sf::Font* getFont() const;
    long unsigned int getCharSize() const;
    const std::tuple<bool, float>& getLetterSpacing() const;
    float getLineSpacingFactor() const;
    Style getStyle() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    sf::Color getBackColor() const;
    const sf::Vector2<float>& getSizeBack() const;
    float getThickness() const;

    template<Info typeCode> struct Typer;

    template<Info typeCode>
    typename Typer<typeCode>::Type getInfo() const;

    template<Info typeCode>
    void setInfo(typename Typer<typeCode>::Type t);

    bool operator==(const InfoText& right) const;
    bool operator!=(const InfoText& right) const;

    std::u32string getValStr(Info i) const;

    static const std::u32string& getKeyStr32(Info i);

    static const std::array<std::u32string, 10> Keys32;

    static const char32_t Separator;
    static const InfoText Default;

protected:

private:
    const sf::Font* font;
    long unsigned int charSize;
    std::tuple<bool, float> letterSpacing;
    float lineSpacingFactor;
    Style style;
    sf::Color fillColor;
    sf::Color outlineColor;
    sf::Color backColor;
    sf::Vector2<float> sizeBack;
    float thickness;
};

template<InfoText::Info n> struct InfoText::Typer {};

template<> struct InfoText::Typer<InfoText::Info::FONT>
{
    typedef const sf::Font* Type;
};
template<> struct InfoText::Typer<InfoText::Info::CHAR_SIZE>
{
    typedef long unsigned int Type;
};
template<> struct InfoText::Typer<InfoText::Info::LETTER_SPACING>
{
    typedef const std::tuple<bool, float>& Type;
};
template<> struct InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>
{
    typedef float Type;
};
template<> struct InfoText::Typer<InfoText::Info::STYLE>
{
    typedef InfoText::Style Type;
};
template<> struct InfoText::Typer<InfoText::Info::FILL_COLOR>
{
    typedef const sf::Color& Type;
};
template<> struct InfoText::Typer<InfoText::Info::OUTLINE_COLOR>
{
    typedef const sf::Color& Type;
};
template<> struct InfoText::Typer<InfoText::Info::BACK_COLOR>
{
    typedef const sf::Color& Type;
};
template<> struct InfoText::Typer<InfoText::Info::SIZE_BACK>
{
    typedef const sf::Vector2<float>& Type;
};
template<> struct InfoText::Typer<InfoText::Info::THICKNESS>
{
    typedef float Type;
};

InfoText::Info operator++(InfoText::Info& i, int);

long unsigned int operator|(const InfoText::Style& left, const InfoText::Style& right);
long unsigned int operator|(long unsigned int left, const InfoText::Style& right);
long unsigned int operator&(const InfoText::Style& left, const InfoText::Style& right);

std::ostream& operator<<(std::ostream& os, InfoText::Style right);

#endif // INFOTEXT_HPP
