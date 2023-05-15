////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef TEXTCOMP_HPP
#define TEXTCOMP_HPP

#include "ChainText.hpp"

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>

class Text final : public sf::Drawable, public sf::Transformable
{
public:

    Text();

    ~Text();

    //Text(const std::u32string& string, const sf::Font& font, unsigned int characterSize = 30);

    Text(const std::vector<const ChainText*>& chainText, const sf::Font& font, unsigned int characterSize = 30);

    Text(const Text& right);

    Text& operator=(const Text& rhs);

    //void setString(const std::u32string& string);

    void setChainText(const std::vector<const ChainText*>& chainText);

    void setFont(const sf::Font& font);

    void setCharacterSize(unsigned int size);

    void setLineSpacing(float spacingFactor);

    void setLetterSpacing(bool spacingFixed, float spacing);

    void setStyle(InfoText::Style style);

    void setFillColor(const sf::Color& color);

    void setOutlineColor(const sf::Color& color);

    void setBackColor(const sf::Color& color);

    void setBackColor(const sf::Color& color, long unsigned int indexInit, long unsigned int indexFina);

    void setSizeBack(const sf::Vector2<float>& sizeBack);

    void setOutlineThickness(float thickness);

    void setWidthWrap(float widthWrap);

    const std::vector<const ChainText*>& getChainText() const;

    const sf::Font* getFont() const;

    unsigned int getCharacterSize() const;

    const std::tuple<bool, float>& getLetterSpacing() const;

    float getLineSpacing() const;

    InfoText::Style getStyle() const;

    const sf::Color& getFillColor() const;

    const sf::Color& getOutlineColor() const;

    const sf::Color& getBackColor() const;

    float getOutlineThickness() const;

    float getWidthWrap() const;

    sf::Vector2<float> findLocalCharacterPos(std::size_t index) const;

    sf::Vector2<float> findCharacterPos(std::size_t index) const;

    long unsigned int findIndexCharacter(const sf::Vector2<float>& pos);

    long unsigned int findIndexCharacter(float posX);

    sf::Rect<float> getLocalBounds() const;

    sf::Rect<float> getGlobalBounds() const;

    void setGeometryNeedUpdate();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void ensureGeometryUpdate() const;

    static void addLine(std::vector<sf::Vertex>& vertices, float lineLength, float lineTop, const sf::Color& color, float offset, float thickness, float outlineThickness = 0);
    static void addLinePart(std::vector<sf::Vertex>& vertices, float xInit, float xFina, float lineTop, const sf::Color& color, float offset, float thickness, float outlineThickness = 0);
    static void addGlyphQuad(std::vector<sf::Vertex>& vertices, sf::Vector2<float> position, const sf::Color& color, const sf::Glyph& glyph, float italicShear, float outlineThickness = 0);

    static void addBackPart(std::vector<sf::Vertex>& vertices, float xInit, float xFina, float lineTop, float lineBottom, const sf::Color& color);

    std::vector<const ChainText*> m_chainText;

    //sf::String                      m_string;              ///< String to display
    InfoText m_infoText;
    mutable std::vector<std::tuple<const sf::Font*, long unsigned int> > m_fontsSizes;
    float m_widthWrap;
    /*
    const sf::Font*                 m_font;                ///< Font used to display the string
    unsigned int                    m_characterSize;       ///< Base size of characters, in pixels
    float                           m_letterSpacingFactor; ///< Spacing factor between letters
    float                           m_lineSpacingFactor;   ///< Spacing factor between lines
    InfoText::Style                 m_style;               ///< Text style (see Style enum)
    sf::Color                       m_fillColor;           ///< Text fill color
    sf::Color                       m_outlineColor;        ///< Text outline color
    float                           m_outlineThickness;    ///< Thickness of the text's outline
    */

    mutable std::vector<std::vector<sf::Vertex> > m_vertices;            ///< Vertex array containing the fill geometry
    mutable std::vector<std::vector<sf::Vertex> > m_outlineVertices;     ///< Vertex array containing the outline geometry
    mutable std::vector<std::vector<sf::Vertex> > m_backVertices;        ///< Vertex array containing the back
    mutable sf::Rect<float>         m_bounds;              ///< Bounding rectangle of the text (in local coordinates)
    mutable bool                    m_geometryNeedUpdate;  ///< Does the geometry need to be recomputed?
    mutable sf::Uint64              m_fontTextureId;       ///< The font texture id
};

#endif // TEXTCOMP_HPP
