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

#include "text/Text.hpp"
#include "func.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <stack>

// Add an underline or strikethrough line to the vertex array
void Text::addLine(std::vector<sf::Vertex>& vertices, float lineLength, float lineTop, const sf::Color& color, float offset, float thickness, float outlineThickness)
{
    float top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    float bottom = top + std::floor(thickness + 0.5f);

    vertices.emplace_back(sf::Vector2<float>(-outlineThickness,             top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(lineLength + outlineThickness, top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(-outlineThickness,             bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(-outlineThickness,             bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(lineLength + outlineThickness, top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(lineLength + outlineThickness, bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
}

void Text::addLinePart(std::vector<sf::Vertex>& vertices, float xInit, float xFina, float lineTop, const sf::Color& color, float offset, float thickness, float outlineThickness)
{
    float top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    float bottom = top + std::floor(thickness + 0.5f);

    vertices.emplace_back(sf::Vector2<float>(xInit - outlineThickness, top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina + outlineThickness, top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xInit - outlineThickness, bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xInit - outlineThickness, bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina + outlineThickness, top    - outlineThickness), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina + outlineThickness, bottom + outlineThickness), color, sf::Vector2<float>(1, 1));
}

// Add a glyph quad to the vertex array
void Text::addGlyphQuad(std::vector<sf::Vertex>& vertices, sf::Vector2<float> position, const sf::Color& color, const sf::Glyph& glyph, float italicShear, float outlineThickness)
{
    float padding = 1.0;

    float left   = glyph.bounds.left - padding;
    float top    = glyph.bounds.top - padding;
    float right  = glyph.bounds.left + glyph.bounds.width + padding;
    float bottom = glyph.bounds.top  + glyph.bounds.height + padding;

    float u1 = static_cast<float>(glyph.textureRect.left) - padding;
    float v1 = static_cast<float>(glyph.textureRect.top) - padding;
    float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width) + padding;
    float v2 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height) + padding;

    vertices.emplace_back(sf::Vector2<float>(position.x + left  - italicShear * top    - outlineThickness, position.y + top    - outlineThickness), color, sf::Vector2<float>(u1, v1));
    vertices.emplace_back(sf::Vector2<float>(position.x + right - italicShear * top    - outlineThickness, position.y + top    - outlineThickness), color, sf::Vector2<float>(u2, v1));
    vertices.emplace_back(sf::Vector2<float>(position.x + left  - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2<float>(u1, v2));
    vertices.emplace_back(sf::Vector2<float>(position.x + left  - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2<float>(u1, v2));
    vertices.emplace_back(sf::Vector2<float>(position.x + right - italicShear * top    - outlineThickness, position.y + top    - outlineThickness), color, sf::Vector2<float>(u2, v1));
    vertices.emplace_back(sf::Vector2<float>(position.x + right - italicShear * bottom - outlineThickness, position.y + bottom - outlineThickness), color, sf::Vector2<float>(u2, v2));
}

void Text::addBackPart(std::vector<sf::Vertex>& vertices, float xInit, float xFina, float lineTop, float lineBottom, const sf::Color& color)
{
    vertices.emplace_back(sf::Vector2<float>(xInit, lineTop), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina, lineTop), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xInit, lineBottom), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xInit, lineBottom), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina, lineTop), color, sf::Vector2<float>(1, 1));
    vertices.emplace_back(sf::Vector2<float>(xFina, lineBottom), color, sf::Vector2<float>(1, 1));
}

Text::Text() : sf::Drawable(), sf::Transformable(),
    m_chainText(),
//m_string             (),
    m_infoText(),
    m_fontsSizes( {}),
              m_widthWrap(-1.0f),
              /*
              m_font               (nullptr),
              m_characterSize      (30),
              m_letterSpacingFactor(1.f),
              m_lineSpacingFactor  (1.f),
              m_style              (InfoText::Style::Regular),
              m_fillColor          (255, 255, 255),
              m_outlineColor       (0, 0, 0),
              m_outlineThickness   (0),
              */
              m_vertices           (),
              m_outlineVertices    (),
              m_backVertices       (),
              m_bounds             (),
              m_geometryNeedUpdate (false),
              m_fontTextureId      (0)
{

}

Text::~Text()
{

}
/*
Text::Text(const std::u32string& string, const sf::Font& font, unsigned int characterSize) : sf::Drawable(), sf::Transformable(),
m_chainText({string}),
//m_string             (string),
m_infoText(&font, characterSize),
m_fontsSizes({}),
m_widthWrap(-1.0f),
//m_font               (&font),
//m_characterSize      (characterSize),
//m_letterSpacingFactor(1.f),
//m_lineSpacingFactor  (1.f),
//m_style              (InfoText::Style::Regular),
//m_fillColor          (255, 255, 255),
//m_outlineColor       (0, 0, 0),
//m_outlineThickness   (0),
m_vertices           (),
m_outlineVertices    (),
m_backVertices       (),
m_bounds             (),
m_geometryNeedUpdate (true),
m_fontTextureId      (0)
{

}
*/
Text::Text(const std::vector<const ChainText*>& chainText, const sf::Font& font, unsigned int characterSize) : sf::Drawable(), sf::Transformable(),
    m_chainText(chainText),
//m_string             (string),
    m_infoText(&font, characterSize),
    m_fontsSizes( {}),
m_widthWrap(-1.0f),
/*
m_font               (&font),
m_characterSize      (characterSize),
m_letterSpacingFactor(1.f),
m_lineSpacingFactor  (1.f),
m_style              (InfoText::Style::Regular),
m_fillColor          (255, 255, 255),
m_outlineColor       (0, 0, 0),
m_outlineThickness   (0),
*/
m_vertices           (),
m_outlineVertices    (),
m_backVertices       (),
m_bounds             (),
m_geometryNeedUpdate (true),
m_fontTextureId      (0)
{

}

Text::Text(const Text& right) : sf::Drawable(right), sf::Transformable(right),
    m_chainText(right.m_chainText),
//m_string             (right.m_string),
    m_infoText(right.m_infoText),
    m_fontsSizes(right.m_fontsSizes),
    m_widthWrap(right.m_widthWrap),
    /*
    m_font               (right.m_font),
    m_characterSize      (right.m_characterSize),
    m_letterSpacingFactor(right.m_letterSpacingFactor),
    m_lineSpacingFactor  (right.m_lineSpacingFactor),
    m_style              (right.m_style),
    m_fillColor          (right.m_fillColor),
    m_outlineColor       (right.m_outlineColor),
    m_outlineThickness   (right.m_outlineThickness),
    */
    m_vertices           (right.m_vertices),
    m_outlineVertices    (right.m_outlineVertices),
    m_backVertices       (right.m_backVertices),
    m_bounds             (right.m_bounds),
    m_geometryNeedUpdate (right.m_geometryNeedUpdate),
    m_fontTextureId      (right.m_fontTextureId)
{

}

Text& Text::operator=(const Text& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Drawable::operator=(rhs);
    Transformable::operator=(rhs);
    m_chainText = rhs.m_chainText;
    //m_string              = rhs.m_string;
    m_infoText = rhs.m_infoText;
    m_fontsSizes = rhs.m_fontsSizes;
    m_widthWrap = rhs.m_widthWrap;
    /*
    m_font                = rhs.m_font;
    m_characterSize       = rhs.m_characterSize;
    m_letterSpacingFactor = rhs.m_letterSpacingFactor;
    m_lineSpacingFactor   = rhs.m_lineSpacingFactor;
    m_style               = rhs.m_style;
    m_fillColor           = rhs.m_fillColor;
    m_outlineColor        = rhs.m_outlineColor;
    m_outlineThickness    = rhs.m_outlineThickness;
    */
    m_vertices            = rhs.m_vertices;
    m_outlineVertices     = rhs.m_outlineVertices;
    m_backVertices        = rhs.m_backVertices;
    m_bounds              = rhs.m_bounds;
    m_geometryNeedUpdate  = rhs.m_geometryNeedUpdate;
    m_fontTextureId       = rhs.m_fontTextureId;
    return *this;
}
/*
void Text::setString(const std::u32string& string)
{
    ChainText newChain = string;
    if (newChain != m_chainText)
    {
        m_chainText = newChain;
        m_geometryNeedUpdate = true;
    }
}
*/
void Text::setChainText(const std::vector<const ChainText*>& chainText)
{
    m_chainText = chainText;
    m_geometryNeedUpdate = true;
}

void Text::setFont(const sf::Font& font)
{
    if (m_infoText.getInfo<InfoText::Info::FONT>() != &font)
    {
        m_infoText.setInfo<InfoText::Info::FONT>(&font);
        m_geometryNeedUpdate = true;
    }
}

void Text::setCharacterSize(unsigned int size)
{
    if (m_infoText.getInfo<InfoText::Info::CHAR_SIZE>() != size)
    {
        m_infoText.setInfo<InfoText::Info::CHAR_SIZE>(size);
        m_geometryNeedUpdate = true;
    }
}

void Text::setLetterSpacing(bool spacingFixed, float spacing)
{
    if (spacingFixed != std::get<0>(m_infoText.getInfo<InfoText::Info::LETTER_SPACING>())
            || std::abs(std::get<1>(m_infoText.getInfo<InfoText::Info::LETTER_SPACING>()) - spacing) > m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::LETTER_SPACING>({spacingFixed, spacing});
    }
}

void Text::setLineSpacing(float spacingFactor)
{
    if (std::abs(m_infoText.getInfo<InfoText::Info::LINE_SPACING_FACTOR>() - spacingFactor) > m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::LINE_SPACING_FACTOR>(spacingFactor);
        m_geometryNeedUpdate = true;
    }
}

void Text::setStyle(InfoText::Style style)
{
    if (m_infoText.getInfo<InfoText::Info::STYLE>() != style)
    {
        m_infoText.setInfo<InfoText::Info::STYLE>(style);
        m_geometryNeedUpdate = true;
    }
}

void Text::setFillColor(const sf::Color& color)
{
    if (m_infoText.getInfo<InfoText::Info::FILL_COLOR>() != color)
    {
        m_infoText.setInfo<InfoText::Info::FILL_COLOR>(color);

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_vertices.size(); ++i)
            {
                for (std::size_t j = 0; j < m_vertices[i].size(); ++j)
                {
                    m_vertices[i][j].color = m_infoText.getInfo<InfoText::Info::FILL_COLOR>();
                }
            }
        }
    }
}

void Text::setOutlineColor(const sf::Color& color)
{
    if (m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>() != color)
    {
        m_infoText.setInfo<InfoText::Info::OUTLINE_COLOR>(color);

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_outlineVertices.size(); ++i)
            {
                for (std::size_t j = 0; j < m_outlineVertices[i].size(); j++)
                {
                    m_outlineVertices[i][j].color = m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>();
                }
            }
        }
    }
}

void Text::setBackColor(const sf::Color& color)
{
    if (m_infoText.getInfo<InfoText::Info::BACK_COLOR>() != color)
    {
        m_infoText.setInfo<InfoText::Info::BACK_COLOR>(color);

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_backVertices.size(); ++i)
            {
                for (std::size_t j = 0; j < m_backVertices[i].size(); j++)
                {
                    m_backVertices[i][j].color = m_infoText.getInfo<InfoText::Info::BACK_COLOR>();
                }
            }
        }
    }
}

void Text::setBackColor(const sf::Color& color, long unsigned int indexInit, long unsigned int indexFina)
{
    long unsigned int k = 0;
    for (std::size_t i = 0; i < m_backVertices.size(); ++i)
    {
        for (std::size_t j = 0; j < m_backVertices[i].size(); j++)
        {
            if (k >= indexInit*6 && k < indexFina*6)
            {
                m_backVertices[i][j].color = color;
            }
            k++;
        }
    }
}

void Text::setSizeBack(const sf::Vector2<float>& sizeBack)
{
    if (std::abs(m_infoText.getInfo<InfoText::Info::SIZE_BACK>().x - sizeBack.x) > m_epsilon_f || std::abs(m_infoText.getInfo<InfoText::Info::SIZE_BACK>().y - sizeBack.y) > m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::SIZE_BACK>(sizeBack);
        m_geometryNeedUpdate = true;
    }
}

void Text::setOutlineThickness(float thickness)
{
    if (std::abs(m_infoText.getInfo<InfoText::Info::THICKNESS>() - thickness) > m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::THICKNESS>(thickness);
        m_geometryNeedUpdate = true;
    }
}

void Text::setWidthWrap(float widthWrap)
{
    if (std::abs(m_widthWrap - widthWrap) > m_epsilon_f)
    {
        m_widthWrap = widthWrap;
        m_geometryNeedUpdate = true;
    }
}

const std::vector<const ChainText*>& Text::getChainText() const
{
    return m_chainText;
}

const sf::Font* Text::getFont() const
{
    return m_infoText.getInfo<InfoText::Info::FONT>();
}

unsigned int Text::getCharacterSize() const
{
    return m_infoText.getInfo<InfoText::Info::CHAR_SIZE>();
}

const std::tuple<bool, float>& Text::getLetterSpacing() const
{
    return m_infoText.getInfo<InfoText::Info::LETTER_SPACING>();
}

float Text::getLineSpacing() const
{
    return m_infoText.getInfo<InfoText::Info::LINE_SPACING_FACTOR>();
}

InfoText::Style Text::getStyle() const
{
    return m_infoText.getInfo<InfoText::Info::STYLE>();
}

const sf::Color& Text::getFillColor() const
{
    return m_infoText.getInfo<InfoText::Info::FILL_COLOR>();
}

const sf::Color& Text::getOutlineColor() const
{
    return m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>();
}

const sf::Color& Text::getBackColor() const
{
    return m_infoText.getInfo<InfoText::Info::BACK_COLOR>();
}

float Text::getOutlineThickness() const
{
    return m_infoText.getInfo<InfoText::Info::THICKNESS>();
}

float Text::getWidthWrap() const
{
    return m_widthWrap;
}

sf::Vector2<float> Text::findLocalCharacterPos(std::size_t index) const
{
    // Make sure that we have a valid font
    if (!m_infoText.getInfo<InfoText::Info::FONT>())
    {
        return sf::Vector2<float>();
    }

    long unsigned int nbCharTotal = 0;
    for (long unsigned int i = 0; i < m_chainText.size(); i++)
    {
        nbCharTotal += m_chainText[i]->getNbChar();
    }

    // Adjust the index if it's out of range
    if (index > nbCharTotal)
    {
        index = nbCharTotal;
    }

    // Precompute the variables needed by the algorithm
    /*
    bool  isBold          = m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
    float whitespaceWidth = m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph(' ', m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).advance;
    float letterSpacing   = ( whitespaceWidth / 3.f ) * ( m_infoText.getInfo<InfoText::Info::LETTER_SPACING>() - 1.f );
    whitespaceWidth      += letterSpacing;
    float lineSpacing     = m_infoText.getInfo<InfoText::Info::FONT>()->getLineSpacing(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>()) * m_infoText.getInfo<InfoText::Info::LINE_SPACING>();
    */
    // Compute the position
    sf::Vector2<float> position = sf::Vector2<float>(0.0f, 0.0f);
    char32_t prevChar = 0;
    long unsigned int indexNode = 0;
    std::size_t iInit = 0;
    std::vector<const BlockInfoText*> vecInfo = {};
    BlockInfoText curInfo = m_infoText;
    long unsigned int indexChain = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        bool changeInfo = false;
        while (i - iInit >= m_chainText[indexChain]->getNbChar(indexNode))
        {
            iInit = i;
            if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKINFO)
            {
                vecInfo.emplace_back(dynamic_cast<const BlockInfoText*>((*m_chainText[indexChain])[indexNode]));
            }
            else if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKCLOSING)
            {
                vecInfo.pop_back();
            }
            changeInfo = true;
            indexNode++;
            while (indexNode >= m_chainText[indexChain]->getSize())
            {
                indexChain++;
                indexNode = 0;
            }
        }
        if (changeInfo)
        {
            curInfo = m_infoText;
            for (long unsigned int j = 0; j < vecInfo.size(); j++)
            {
                curInfo += *vecInfo[j];
            }
        }

        char32_t curChar = static_cast<unsigned int>((*m_chainText[indexChain])[indexNode]->getStr()[i - iInit]);

        bool  curBold            = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
        float curWhitespaceWidth = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(' ', curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).advance;
        float curLetterSpacing   = ( curWhitespaceWidth / 3.f ) * ( std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()) - 1.f );
        curWhitespaceWidth      += curLetterSpacing;
        float curLineSpacing     = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getLineSpacing(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()) *
                                   curInfo.getInfoText().getInfo<InfoText::Info::LINE_SPACING_FACTOR>();

        /*
        for (long unsigned int j = 0; j < vecInfo.size(); j++)
        {
            if (vecInfo[vecInfo.size() - 1 - j]->isUsed(InfoText::Info::STYLE))
            {
                curBold = vecInfo[vecInfo.size() - 1 - j]->getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
                break;
            }
        }
        */

        // Apply the kerning offset
        position.x += curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getKerning(prevChar, curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
        case U' ':
            position.x += curWhitespaceWidth;
            continue;
        case U'\t':
            position.x += curWhitespaceWidth * 4;
            continue;
        case U'\n':
            position.y += curLineSpacing;
            position.x = 0;
            continue;
        default:
            break;
        }

        // For regular characters, add the advance offset of the glyph
        if (!std::get<0>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            position.x += std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            position.x += curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).advance + curLetterSpacing;
        }
    }

    return position;
}

sf::Vector2<float> Text::findCharacterPos(std::size_t index) const
{
    return getTransform().transformPoint(findLocalCharacterPos(index)); // Transform the position to global coordinates
}

long unsigned int Text::findIndexCharacter(const sf::Vector2<float>& pos)
{
    // Make sure that we have a valid font
    if (!m_infoText.getInfo<InfoText::Info::FONT>())
    {
        return 0;
    }
    long unsigned int nbCharTotal = 0;
    for (long unsigned int i = 0; i < m_chainText.size(); i++)
    {
        nbCharTotal += m_chainText[i]->getNbChar();
    }
    sf::Vector2<float> position = sf::Vector2<float>(0.0f, 0.0f);
    char32_t prevChar = 0;
    long unsigned int indexNode = 0;
    std::size_t iInit = 0;
    std::vector<const BlockInfoText*> vecInfo = {};
    BlockInfoText curInfo = m_infoText;
    long unsigned int indexChain = 0;
    long unsigned int i = 0;
    //std::cout << "position.x = " << position.x << ", pos.x = " << pos.x << ", position.y = " << position.y << ", pos.y = " << pos.y << ", nbCharTotal = " << nbCharTotal << std::endl;
    while (position.y <= pos.y && position.x < pos.x && i < nbCharTotal)
    {
        //std::cout << "aa" << std::endl;
        bool changeInfo = false;
        while (i - iInit >= m_chainText[indexChain]->getNbChar(indexNode))
        {
            iInit = i;
            if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKINFO)
            {
                vecInfo.emplace_back(dynamic_cast<const BlockInfoText*>((*m_chainText[indexChain])[indexNode]));
            }
            else if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKCLOSING)
            {
                vecInfo.pop_back();
            }
            changeInfo = true;
            indexNode++;
            while (indexNode >= m_chainText[indexChain]->getSize())
            {
                indexChain++;
                indexNode = 0;
            }
        }
        if (changeInfo)
        {
            curInfo = m_infoText;
            for (long unsigned int j = 0; j < vecInfo.size(); j++)
            {
                curInfo += *vecInfo[j];
            }
        }

        char32_t curChar = static_cast<unsigned int>((*m_chainText[indexChain])[indexNode]->getStr()[i - iInit]);

        bool  curBold            = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
        float curWhitespaceWidth = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(' ', curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).advance;
        float curLetterSpacing   = ( curWhitespaceWidth / 3.f ) * ( std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()) - 1.f );
        curWhitespaceWidth      += curLetterSpacing;
        float curLineSpacing     = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getLineSpacing(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()) *
                                   curInfo.getInfoText().getInfo<InfoText::Info::LINE_SPACING_FACTOR>();

        // Apply the kerning offset
        position.x += curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getKerning(prevChar, curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
        case U' ':
            position.x += curWhitespaceWidth;
            continue;
        case U'\t':
            position.x += curWhitespaceWidth * 4;
            continue;
        case U'\n':
            position.y += curLineSpacing;
            position.x = 0;
            continue;
        default:
            break;
        }

        // For regular characters, add the advance offset of the glyph
        if (!std::get<0>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            position.x += std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            position.x += curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).advance + curLetterSpacing;
        }
        i++;
    }
    return i;
}

long unsigned int Text::findIndexCharacter(float posX)
{
    return findIndexCharacter(sf::Vector2<float>(posX, 0.0f));
}

sf::Rect<float> Text::getLocalBounds() const
{
    ensureGeometryUpdate();

    return m_bounds;
}

sf::Rect<float> Text::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Text::setGeometryNeedUpdate()
{
    m_geometryNeedUpdate = true;
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_infoText.getInfo<InfoText::Info::FONT>())
    {
        ensureGeometryUpdate();

        states.transform *= getTransform();

        // Only draw the outline if there is something to draw
        /*
        if (std::abs(m_infoText.getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
        {
            target.draw(m_outlineVertices.front().data(), m_outlineVertices.size(), sf::PrimitiveType::Triangles, states);
        }
        */
        for (long unsigned int i = 0; i < m_outlineVertices.size(); i++)
        {
            states.texture = nullptr;
            target.draw(m_backVertices[i].data(), m_backVertices[i].size(), sf::PrimitiveType::Triangles, states);
            states.texture = &std::get<0>(m_fontsSizes[i])->getTexture(std::get<1>(m_fontsSizes[i]));
            target.draw(m_outlineVertices[i].data(), m_outlineVertices[i].size(), sf::PrimitiveType::Triangles, states);
            target.draw(m_vertices[i].data(), m_vertices[i].size(), sf::PrimitiveType::Triangles, states);
        }

        if (m_backVertices.size())
        {
            //std::cout << "back vertices size : " << m_backVertices[0].size() << std::endl;
            for (long unsigned int i = 0; i < m_backVertices[0].size(); i++)
            {
                //std::cout << i << " : " << m_backVertices[0][i].position << " " << m_backVertices[0][i].color << std::endl;
            }
        }
        if (m_outlineVertices.size())
        {
            //std::cout << "outline vertices size : " << m_outlineVertices[0].size() << std::endl;
            for (long unsigned int i = 0; i < m_outlineVertices[0].size(); i++)
            {
                //std::cout << i << " : " << m_outlineVertices[0][i].position << " " << m_outlineVertices[0][i].color << std::endl;
            }
        }
    }
}

void Text::ensureGeometryUpdate() const
{
    if (!m_infoText.getInfo<InfoText::Info::FONT>())
    {
        return;
    }

    // Do nothing, if geometry has not changed and the font texture has not changed
    if (!m_geometryNeedUpdate/* && m_font->getTexture(m_characterSize).m_cacheId == m_fontTextureId*/)
    {
        return;
    }

    // Save the current fonts texture id
    //m_fontTextureId = m_font->getTexture(m_characterSize).m_cacheId;

    // Mark geometry as updated
    m_geometryNeedUpdate = false;

    // Clear the previous geometry
    m_vertices.clear();
    m_outlineVertices.clear();
    m_backVertices.clear();
    m_fontsSizes.clear();
    m_bounds = sf::Rect<float>();

    // No text: nothing to draw
    if (m_chainText.empty())
    {
        return;
    }

    // Compute values related to the text style
    /*
    bool  isBold             = m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
    bool  isUnderlined       = m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined;
    bool  isStrikeThrough    = m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough;
    float italicShear        = (m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Italic) ? 0.209f : 0.f; // 12 degrees in radians
    float underlineOffset    = m_infoText.getInfo<InfoText::Info::FONT>()->getUnderlinePosition(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float underlineThickness = m_infoText.getInfo<InfoText::Info::FONT>()->getUnderlineThickness(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    */

    // Compute the location of the strike through dynamically
    // We use the center point of the lowercase 'x' glyph as the reference
    // We reuse the underline thickness as the thickness of the strike through as well
    /*
    sf::Rect<float> xBounds = m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph('x', m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).bounds;
    float strikeThroughOffset = xBounds.top + xBounds.height / 2.f;
    */

    // Precompute the variables needed by the algorithm
    /*
    float whitespaceWidth = m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph(' ', m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).advance;
    float letterSpacing   = ( whitespaceWidth / 3.f ) * ( m_infoText.getInfo<InfoText::Info::LETTER_SPACING>() - 1.f );
    whitespaceWidth      += letterSpacing;
    float lineSpacing     = m_infoText.getInfo<InfoText::Info::FONT>()->getLineSpacing(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>()) * m_infoText.getInfo<InfoText::Info::LINE_SPACING>();
    float x               = 0.f;
    float y               = static_cast<float>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    */

    float x               = 0.f;
    float y               = static_cast<float>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float prevX = x;
    float prevY = 0.0f;

    // Create one quad for each character
    float minX = static_cast<float>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float minY = static_cast<float>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float maxX = 0.f;
    float maxY = 0.f;
    char32_t prevChar = 0;
    long unsigned int indexNode = 0;
    std::size_t iInit = 0;
    std::vector<const BlockInfoText*> vecInfo = {};
    BlockInfoText curInfo = m_infoText;
    BlockInfoText prevInfo = curInfo;
    long unsigned int indexArrayVert = 0;
    long unsigned int nbCharTotal = 0;
    for (long unsigned int i = 0; i < m_chainText.size(); i++)
    {
        nbCharTotal += m_chainText[i]->getNbChar();
    }
    long unsigned int indexChain = 0;
    //long unsigned curNbChar = m_chainText.front()->getNbChar();
    const sf::Font* curFont = nullptr;
    long unsigned int curCharSize = 0;
    std::vector<sf::Vertex> curUndelineVertFill = {};
    std::vector<sf::Vertex> curUndelineVertOutline = {};
    std::vector<sf::Vertex> curStrikeThroughVertFill = {};
    std::vector<sf::Vertex> curStrikeThroughVertOutline = {};
    for (std::size_t i = 0; i < /*m_string.getSize()*/nbCharTotal; ++i)
    {
        bool changeInfo = false;
        while (i - iInit >= m_chainText[indexChain]->getNbChar(indexNode))
        {
            iInit = i;
            if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKINFO)
            {
                vecInfo.emplace_back(dynamic_cast<const BlockInfoText*>((*m_chainText[indexChain])[indexNode]));
            }
            else if ((*m_chainText[indexChain])[indexNode]->getType() == NodeText::Type::BLOCKCLOSING)
            {
                vecInfo.pop_back();
            }
            changeInfo = true;
            indexNode++;
            while (indexNode >= m_chainText[indexChain]->getSize())
            {
                indexChain++;
                indexNode = 0;
            }
        }
        if (changeInfo || i == 0)
        {
            curInfo = m_infoText;
            for (long unsigned int j = 0; j < vecInfo.size(); j++)
            {
                curInfo += *vecInfo[j];
            }
            if (curInfo.getInfoText().getInfo<InfoText::Info::FONT>() != curFont || curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>() != curCharSize)
            {
                m_fontsSizes.push_back({curInfo.getInfoText().getInfo<InfoText::Info::FONT>(), curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()});
                curFont = std::get<0>(m_fontsSizes.back());
                curCharSize = std::get<1>(m_fontsSizes.back());
                //std::tie(curFont, curCharSize) = m_fontsSizes.back();
                m_vertices.push_back({});
                m_outlineVertices.push_back({});
                m_backVertices.push_back({});
                indexArrayVert = m_vertices.size() - 1;
            }
            if (i == 0)
            {
                y               = static_cast<float>(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
                prevY = 0.0f;
            }
            if (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined
                    && !(prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined))
            {
                curUndelineVertFill.clear();
                curUndelineVertOutline.clear();
            }
            else if (!(curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined)
                     && prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined)
            {
                m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curUndelineVertFill.begin(), curUndelineVertFill.end());
                m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curUndelineVertOutline.begin(), curUndelineVertOutline.end());
            }
            if (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough
                    && !(prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough))
            {
                curStrikeThroughVertFill.clear();
                curStrikeThroughVertOutline.clear();
            }
            else if (!(curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough)
                     && prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough)
            {
                m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curStrikeThroughVertFill.begin(), curStrikeThroughVertFill.end());
                m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curStrikeThroughVertOutline.begin(), curStrikeThroughVertOutline.end());
            }
        }

        bool  curBold             = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
        bool  curUnderlined       = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined;
        bool  curStrikeThrough    = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough;
        float curItalicShear        = (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Italic) ? 0.209f : 0.f; // 12 degrees in radians
        float curUnderlineOffset    = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlinePosition(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        float curUnderlineThickness = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlineThickness(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());

        sf::Rect<float> curXBounds = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph('x', curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).bounds;
        float curStrikeThroughOffset = curXBounds.top + curXBounds.height / 2.f;

        float curWhitespaceWidth = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(' ', curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).advance;
        float curLetterSpacing   = ( curWhitespaceWidth / 3.f ) * ( std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()) - 1.f );
        curWhitespaceWidth      += curLetterSpacing;
        if (!std::get<0>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            curWhitespaceWidth = std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            curWhitespaceWidth      += curLetterSpacing;
        }
        float curLineSpacing     = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getLineSpacing(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()) *
                                   curInfo.getInfoText().getInfo<InfoText::Info::LINE_SPACING_FACTOR>();

        char32_t curChar = static_cast<unsigned int>((*m_chainText[indexChain])[indexNode]->getStr()[i - iInit])/*m_string[i]*/;

        // Skip the \r char to avoid weird graphical issues
        if (curChar == U'\r')
        {
            continue;
        }

        // Apply the kerning offset
        if (!std::get<0>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            x += 0;
        }
        else
        {
            x += curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getKerning(prevChar, curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        }


        // If we're using the underlined style and there's a new line, draw a line
        /*
        if (curUnderlined && (curChar == '\n' && prevChar != '\n'))
        {
            std::cerr << "Underline added (char = n)" << std::endl;
            TextComp::addLine(m_vertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curUnderlineOffset, curUnderlineThickness);

            if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
            {
                TextComp::addLine(m_outlineVertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curUnderlineOffset, curUnderlineThickness,
                                  curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        */

        // If we're using the strike through style and there's a new line, draw a line across all characters
        /*
        if (curStrikeThrough && (curChar == '\n' && prevChar != '\n'))
        {
            TextComp::addLine(m_vertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curStrikeThroughOffset, curUnderlineThickness);

            if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
            {
                TextComp::addLine(m_outlineVertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curStrikeThroughOffset, curUnderlineThickness,
                                  curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        */

        prevChar = curChar;

        // Handle special characters
        if ((curChar == U' ') || (curChar == U'\n') || (curChar == U'\t'))
        {
            // Update the current bounds (min coordinates)
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (curChar)
            {
            case U' ':
            {
                addBackPart(m_backVertices.back(), prevX, x, y, y + static_cast<float>(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()),
                            curInfo.getInfoText().getInfo<InfoText::Info::BACK_COLOR>());
                if (curUnderlined)
                {
                    addLinePart(curUndelineVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curUnderlineOffset,
                                curUnderlineThickness);
                    if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
                    {
                        addLinePart(curUndelineVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curUnderlineOffset,
                                    curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                if (curStrikeThrough)
                {
                    addLinePart(curStrikeThroughVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curStrikeThroughOffset,
                                curUnderlineThickness);
                    if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
                    {
                        addLinePart(curStrikeThroughVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curStrikeThroughOffset,
                                    curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                x += curWhitespaceWidth;
                if (m_widthWrap >= 0.0f && m_widthWrap < x)
                {
                    prevY = y;
                    y += curLineSpacing;
                    if (curUnderlined)
                    {
                        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curUndelineVertFill.begin(), curUndelineVertFill.end());
                        m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curUndelineVertOutline.begin(), curUndelineVertOutline.end());
                        curUndelineVertFill.clear();
                        curUndelineVertOutline.clear();
                    }
                    if (curStrikeThrough)
                    {
                        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curStrikeThroughVertFill.begin(), curStrikeThroughVertFill.end());
                        m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curStrikeThroughVertOutline.begin(), curStrikeThroughVertOutline.end());
                        curStrikeThroughVertFill.clear();
                        curStrikeThroughVertOutline.clear();
                    }
                    x = 0;
                }
                prevX = x;
                break;
            }
            case U'\t':
            {
                addBackPart(m_backVertices.back(), prevX, x, y, y + static_cast<float>(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()),
                            curInfo.getInfoText().getInfo<InfoText::Info::BACK_COLOR>());
                if (curUnderlined)
                {
                    addLinePart(curUndelineVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curUnderlineOffset,
                                curUnderlineThickness);
                    if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
                    {
                        addLinePart(curUndelineVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curUnderlineOffset,
                                    curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                if (curStrikeThrough)
                {
                    addLinePart(curStrikeThroughVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curStrikeThroughOffset,
                                curUnderlineThickness);
                    if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
                    {
                        addLinePart(curStrikeThroughVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curStrikeThroughOffset,
                                    curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                x += curWhitespaceWidth * 4;
                prevX = x;
                break;
            }
            case U'\n':
            {
                prevY = y;
                y += curLineSpacing;
                if (curUnderlined)
                {
                    m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curUndelineVertFill.begin(), curUndelineVertFill.end());
                    m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curUndelineVertOutline.begin(), curUndelineVertOutline.end());
                    curUndelineVertFill.clear();
                    curUndelineVertOutline.clear();
                }
                if (curStrikeThrough)
                {
                    m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curStrikeThroughVertFill.begin(), curStrikeThroughVertFill.end());
                    m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curStrikeThroughVertOutline.begin(), curStrikeThroughVertOutline.end());
                    curStrikeThroughVertFill.clear();
                    curStrikeThroughVertOutline.clear();
                }
                x = 0;
                prevX = 0;
                break;
            }
            default:
            {
                break;
            }
            }

            // Update the current bounds (max coordinates)
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace
            continue;
        }

        // Apply the outline
        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
        {
            const sf::Glyph& glyph = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold,
                                     curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());

            float left   = glyph.bounds.left;
            float top    = glyph.bounds.top;
            float right  = glyph.bounds.left + glyph.bounds.width;
            float bottom = glyph.bounds.top  + glyph.bounds.height;

            // Add the outline glyph to the vertices
            addGlyphQuad(m_outlineVertices[indexArrayVert], sf::Vector2<float>(x, y), curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), glyph, curItalicShear,
                         curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());

            // Update the current bounds with the outlined glyph bounds
            minX = std::min(minX, x + left   - curItalicShear * bottom - curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            maxX = std::max(maxX, x + right  - curItalicShear * top    - curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            minY = std::min(minY, y + top    - curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            maxY = std::max(maxY, y + bottom - curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }

        /*
        addBackPart(m_backVertices.back(), prevX, x, y, y + static_cast<float>(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()),
                    curInfo.getInfoText().getInfo<InfoText::Info::BACK_COLOR>());
        */

        // Extract the current glyph's description
        const sf::Glyph& glyph = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(curChar, curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold);

        // Add the glyph to the vertices
        addGlyphQuad(m_vertices[indexArrayVert], sf::Vector2<float>(x, y), curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), glyph, curItalicShear);

        // Update the current bounds with the non outlined glyph bounds
        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) <= m_epsilon_f)
        {
            float left   = glyph.bounds.left;
            float top    = glyph.bounds.top;
            float right  = glyph.bounds.left + glyph.bounds.width;
            float bottom = glyph.bounds.top  + glyph.bounds.height;

            minX = std::min(minX, x + left  - curItalicShear * bottom);
            maxX = std::max(maxX, x + right - curItalicShear * top);
            minY = std::min(minY, y + top);
            maxY = std::max(maxY, y + bottom);
        }

        // Advance to the next character
        if (!std::get<0>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            x += std::get<1>(curInfo.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            x += glyph.advance + curLetterSpacing;
        }
        if (curUnderlined)
        {
            addLinePart(curUndelineVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curUnderlineOffset,
                        curUnderlineThickness);
            if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
            {
                addLinePart(curUndelineVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curUnderlineOffset,
                            curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        if (curStrikeThrough)
        {
            addLinePart(curStrikeThroughVertFill, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curStrikeThroughOffset,
                        curUnderlineThickness);
            if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
            {
                addLinePart(curStrikeThroughVertOutline, prevX, x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curStrikeThroughOffset,
                            curUnderlineThickness, curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }

        addBackPart(m_backVertices.back(), prevX, x, /*y, y + static_cast<float>(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>())*/prevY, y,
                    curInfo.getInfoText().getInfo<InfoText::Info::BACK_COLOR>());

        prevX = x;
        prevInfo = curInfo;
    }

    //bool  curBold             = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Bold;
    bool  curUnderlined       = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined;
    bool  curStrikeThrough    = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() & InfoText::Style::StrikeThrough;
    //float curUnderlineOffset    = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlinePosition(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
    //float curUnderlineThickness = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlineThickness(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
    //sf::Rect<float> curXBounds = curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph('x', curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(), curBold).bounds;
    //float curStrikeThroughOffset = curXBounds.top + curXBounds.height / 2.f;
    if (curUnderlined)
    {
        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curUndelineVertFill.begin(), curUndelineVertFill.end());
        m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curUndelineVertOutline.begin(), curUndelineVertOutline.end());
    }
    if (curStrikeThrough)
    {
        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(), curStrikeThroughVertFill.begin(), curStrikeThroughVertFill.end());
        m_outlineVertices[indexArrayVert].insert(m_outlineVertices[indexArrayVert].end(), curStrikeThroughVertOutline.begin(), curStrikeThroughVertOutline.end());
    }
    // If we're using the underlined style, add the last line
    /*
    if (curUnderlined && (x > 0))
    {
        std::cerr << "Underline added (x > 0)" << std::endl;
        TextComp::addLine(m_vertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curUnderlineOffset, curUnderlineThickness);

        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
        {
            TextComp::addLine(m_outlineVertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curUnderlineOffset, curUnderlineThickness,
                              curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }
    }
    */

    // If we're using the strike through style, add the last line across all characters
    /*
    if (curStrikeThrough && (x > 0))
    {
        TextComp::addLine(m_vertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), curStrikeThroughOffset, curUnderlineThickness);

        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) > m_epsilon_f)
        {
            TextComp::addLine(m_outlineVertices[indexArrayVert], x, y, curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(), curStrikeThroughOffset, curUnderlineThickness,
                              curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }
    }
    */

    // Update the bounding rectangle
    m_bounds.left = minX;
    m_bounds.top = minY;
    m_bounds.width = maxX - minX;
    m_bounds.height = maxY - minY;
    /*
    if (m_backVertices.size())
    {
        std::cout << "back vertices size : " << m_backVertices[0].size() << std::endl;
        for (long unsigned int i = 0; i < m_backVertices[0].size(); i++)
        {
            std::cout << i << " : " << m_backVertices[0][i].position << " " << m_backVertices[0][i].color << std::endl;
        }
    }
    */
}
