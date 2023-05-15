/*
 * A sprite class that can be stretched while keeping the angles of the texture.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "NinePatch.hpp"
#include "func.hpp"
#include <iostream>
#include <istream>

NinePatch::NinePatch() : sf::Transformable(), sf::Drawable(),
m_vertices    (),
m_texture     (nullptr),
m_textureRect (),
m_width       (0.0f),
m_height      (0.0f),
m_leftBorder  (0.0f),
m_topBorder   (0.0f),
m_rightBorder (0.0f),
m_bottomBorder(0.0f)
{

}

NinePatch::NinePatch(const sf::Texture& texture) : sf::Transformable(), sf::Drawable(),
m_vertices    (),
m_texture     (nullptr),
m_textureRect (),
m_width       (0.0f),
m_height      (0.0f),
m_leftBorder  (0.0f),
m_topBorder   (0.0f),
m_rightBorder (0.0f),
m_bottomBorder(0.0f)
{
    setTexture(texture);
}

NinePatch::NinePatch(const sf::Texture& texture, const sf::Rect<int>& rectangle) : sf::Transformable(), sf::Drawable(),
m_vertices    (),
m_texture     (nullptr),
m_textureRect (),
m_width       (0.0f),
m_height      (0.0f),
m_leftBorder  (0.0f),
m_topBorder   (0.0f),
m_rightBorder (0.0f),
m_bottomBorder(0.0f)
{
    setTexture(texture);
    setTextureRect(rectangle);
}

NinePatch::~NinePatch()
{

}

NinePatch::NinePatch(const NinePatch& other) : sf::Transformable(other), sf::Drawable(other),
m_vertices    (other.m_vertices),
m_texture     (other.m_texture),
m_textureRect (other.m_textureRect),
m_width       (other.m_width),
m_height      (other.m_height),
m_leftBorder  (other.m_leftBorder),
m_topBorder   (other.m_topBorder),
m_rightBorder (other.m_rightBorder),
m_bottomBorder(other.m_bottomBorder)
{

}

NinePatch& NinePatch::operator=(const NinePatch& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    sf::Transformable::operator=(rhs);
    sf::Drawable::operator=(rhs);
    m_vertices     = rhs.m_vertices;
    m_texture      = rhs.m_texture;
    m_textureRect  = rhs.m_textureRect;
    m_width        = rhs.m_width;
    m_height       = rhs.m_height;
    m_leftBorder   = rhs.m_leftBorder;
    m_topBorder    = rhs.m_topBorder;
    m_rightBorder  = rhs.m_rightBorder;
    m_bottomBorder = rhs.m_bottomBorder;
    return *this;
}

void NinePatch::setTexture(const sf::Texture& texture, bool resetRect)
{
    // Recompute the texture area if requested, or if there was no valid texture & rect before
    if (resetRect || (!m_texture && (m_textureRect == sf::Rect<int>())))
    {
        setTextureRect(sf::Rect<int>(0, 0, static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)));
    }
    // Assign the new texture
    m_texture = &texture;
}

void NinePatch::setTextureRect(int newLeft, int newTop, int newWidth, int newHeight)
{
    if (newLeft != m_textureRect.left || newTop != m_textureRect.top || newWidth != m_textureRect.width || newHeight != m_textureRect.height)
    {
        m_textureRect = sf::Rect<int>(newLeft, newTop, newWidth, newHeight);
        updatePositions();
        updateTexCoords();
    }
}

void NinePatch::setTextureRect(const sf::Rect<int>& rectangle)
{
    if (rectangle != m_textureRect)
    {
        m_textureRect = rectangle;
        updatePositions();
        updateTexCoords();
    }
}

void NinePatch::setColor(const sf::Color& color)
{
    // Update the vertices' color
    for (std::array<sf::Vertex, 54>::iterator it = m_vertices.begin(); it != m_vertices.end(); it++)
    {
        it[0].color = color;
    }
}

void NinePatch::setWidth(float newWidth)
{
    m_width = newWidth;
    updatePositions();
}

void NinePatch::setHeight(float newHeight)
{
    m_height = newHeight;
    updatePositions();
}

void NinePatch::setSize(const sf::Vector2<float> newSize)
{
    m_width = newSize.x;
    m_height = newSize.y;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setSize(float newWidth, float newHeight)
{
    m_width = newWidth;
    m_height = newHeight;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setSize(float newSize)
{
    m_width = newSize;
    m_height = newSize;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setLeftBorder(float leftBorder)
{
    m_leftBorder = leftBorder;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setTopBorder(float topBorder)
{
    m_topBorder = topBorder;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setRightBorder(float rightBorder)
{
    m_rightBorder = rightBorder;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setBottomBorder(float bottomBorder)
{
    m_bottomBorder = bottomBorder;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setBorder(float leftBorder, float topBorder, float rightBorder, float bottomBorder)
{
    m_leftBorder = leftBorder;
    m_topBorder = topBorder;
    m_rightBorder = rightBorder;
    m_bottomBorder = bottomBorder;
    updatePositions();
    updateTexCoords();
}

void NinePatch::setBorder(float border)
{
    m_leftBorder = border;
    m_topBorder = border;
    m_rightBorder = border;
    m_bottomBorder = border;
    updatePositions();
    updateTexCoords();
}

const sf::Texture* NinePatch::getTexture() const
{
    return m_texture;
}

const sf::Rect<int>& NinePatch::getTextureRect() const
{
    return m_textureRect;
}

const sf::Color& NinePatch::getColor() const
{
    return m_vertices[0].color;
}

sf::Rect<float> NinePatch::getLocalBounds() const
{
    return sf::Rect<float>(0.0f, 0.0f, m_width, m_height);
}

sf::Rect<float> NinePatch::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

float NinePatch::getWidth() const
{
    return m_width;
}

float NinePatch::getHeight() const
{
    return m_height;
}

float NinePatch::getLeftBorder() const
{
    return m_leftBorder;
}

float NinePatch::getTopBorder() const
{
    return m_topBorder;
}

float NinePatch::getRightBorder() const
{
    return m_rightBorder;
}

float NinePatch::getBottomBorder() const
{
    return m_leftBorder;
}

void NinePatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_texture)
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices.data(), 54, sf::PrimitiveType::Triangles, states);
    }
}

void NinePatch::updatePositions()
{
    float borderRight = m_width - m_rightBorder;
    float borderBottom = m_height - m_bottomBorder;

    // Top left area
    m_vertices[0].position = sf::Vector2<float>(0.0f, 0.0f);
    m_vertices[1].position = sf::Vector2<float>(m_leftBorder, 0.0f);
    m_vertices[2].position = sf::Vector2<float>(0.0f, m_topBorder);
    m_vertices[3].position = sf::Vector2<float>(m_leftBorder, m_topBorder);
    m_vertices[4].position = sf::Vector2<float>(0.0f, m_topBorder);
    m_vertices[5].position = sf::Vector2<float>(m_leftBorder, 0.0f);

    // Top middle area
    m_vertices[6].position = sf::Vector2<float>(m_leftBorder, 0.0f);
    m_vertices[7].position = sf::Vector2<float>(borderRight, 0.0f);
    m_vertices[8].position = sf::Vector2<float>(m_leftBorder, m_topBorder);
    m_vertices[9].position = sf::Vector2<float>(borderRight, m_topBorder);
    m_vertices[10].position = sf::Vector2<float>(m_leftBorder, m_topBorder);
    m_vertices[11].position = sf::Vector2<float>(borderRight, 0.0f);

    // Top right area
    m_vertices[12].position = sf::Vector2<float>(borderRight, 0.0f);
    m_vertices[13].position = sf::Vector2<float>(m_width, 0.0f);
    m_vertices[14].position = sf::Vector2<float>(borderRight, m_topBorder);
    m_vertices[15].position = sf::Vector2<float>(m_width, m_topBorder);
    m_vertices[16].position = sf::Vector2<float>(borderRight, m_topBorder);
    m_vertices[17].position = sf::Vector2<float>(m_width, 0.0f);


    // Middle left area
    m_vertices[18].position = sf::Vector2<float>(0.0f, m_topBorder);
    m_vertices[19].position = sf::Vector2<float>(m_leftBorder, m_topBorder);
    m_vertices[20].position = sf::Vector2<float>(0.0f, borderBottom);
    m_vertices[21].position = sf::Vector2<float>(m_leftBorder, borderBottom);
    m_vertices[22].position = sf::Vector2<float>(0.0f, borderBottom);
    m_vertices[23].position = sf::Vector2<float>(m_leftBorder, m_topBorder);

    // Middle area
    m_vertices[24].position = sf::Vector2<float>(m_leftBorder, m_topBorder);
    m_vertices[25].position = sf::Vector2<float>(borderRight, m_topBorder);
    m_vertices[26].position = sf::Vector2<float>(m_leftBorder, borderBottom);
    m_vertices[27].position = sf::Vector2<float>(borderRight, borderBottom);
    m_vertices[28].position = sf::Vector2<float>(m_leftBorder, borderBottom);
    m_vertices[29].position = sf::Vector2<float>(borderRight, m_topBorder);

    // Middle right area
    m_vertices[30].position = sf::Vector2<float>(borderRight, m_topBorder);
    m_vertices[31].position = sf::Vector2<float>(m_width, m_topBorder);
    m_vertices[32].position = sf::Vector2<float>(borderRight, borderBottom);
    m_vertices[33].position = sf::Vector2<float>(m_width, borderBottom);
    m_vertices[34].position = sf::Vector2<float>(borderRight, borderBottom);
    m_vertices[35].position = sf::Vector2<float>(m_width, m_topBorder);


    // Bottom left area
    m_vertices[36].position = sf::Vector2<float>(0.0f, borderBottom);
    m_vertices[37].position = sf::Vector2<float>(m_leftBorder, borderBottom);
    m_vertices[38].position = sf::Vector2<float>(0.0f, m_height);
    m_vertices[39].position = sf::Vector2<float>(m_leftBorder, m_height);
    m_vertices[40].position = sf::Vector2<float>(0.0f, m_height);
    m_vertices[41].position = sf::Vector2<float>(m_leftBorder, borderBottom);

    // Bottom middle area
    m_vertices[42].position = sf::Vector2<float>(m_leftBorder, borderBottom);
    m_vertices[43].position = sf::Vector2<float>(borderRight, borderBottom);
    m_vertices[44].position = sf::Vector2<float>(m_leftBorder, m_height);
    m_vertices[45].position = sf::Vector2<float>(borderRight, m_height);
    m_vertices[46].position = sf::Vector2<float>(m_leftBorder, m_height);
    m_vertices[47].position = sf::Vector2<float>(borderRight, borderBottom);

    // Bottom right area
    m_vertices[48].position = sf::Vector2<float>(borderRight, borderBottom);
    m_vertices[49].position = sf::Vector2<float>(m_width, borderBottom);
    m_vertices[50].position = sf::Vector2<float>(borderRight, m_height);
    m_vertices[51].position = sf::Vector2<float>(m_width, m_height);
    m_vertices[52].position = sf::Vector2<float>(borderRight, m_height);
    m_vertices[53].position = sf::Vector2<float>(m_width, borderBottom);
}

void NinePatch::updateTexCoords()
{
    float left      = static_cast<float>(m_textureRect.left);
    float midLeft   = left + m_leftBorder;
    float midRight  = left + static_cast<float>(m_textureRect.width) - m_rightBorder;
    float right     = left + static_cast<float>(m_textureRect.width);
    float top       = static_cast<float>(m_textureRect.top);
    float midTop    = top + m_topBorder;
    float midBottom = top + static_cast<float>(m_textureRect.height) - m_bottomBorder;
    float bottom    = top + static_cast<float>(m_textureRect.height);

    // Top left area
    m_vertices[0].texCoords = sf::Vector2<float>(left, top);
    m_vertices[1].texCoords = sf::Vector2<float>(midLeft, top);
    m_vertices[2].texCoords = sf::Vector2<float>(left, midTop);
    m_vertices[3].texCoords = sf::Vector2<float>(midLeft, midTop);
    m_vertices[4].texCoords = sf::Vector2<float>(left, midTop);
    m_vertices[5].texCoords = sf::Vector2<float>(midLeft, top);

    // Top middle area
    m_vertices[6].texCoords = sf::Vector2<float>(midLeft, top);
    m_vertices[7].texCoords = sf::Vector2<float>(midRight, top);
    m_vertices[8].texCoords = sf::Vector2<float>(midLeft, midTop);
    m_vertices[9].texCoords = sf::Vector2<float>(midRight, midTop);
    m_vertices[10].texCoords = sf::Vector2<float>(midLeft, midTop);
    m_vertices[11].texCoords = sf::Vector2<float>(midRight, top);

    // Top right area
    m_vertices[12].texCoords = sf::Vector2<float>(midRight, top);
    m_vertices[13].texCoords = sf::Vector2<float>(right, top);
    m_vertices[14].texCoords = sf::Vector2<float>(midRight, midTop);
    m_vertices[15].texCoords = sf::Vector2<float>(right, midTop);
    m_vertices[16].texCoords = sf::Vector2<float>(midRight, midTop);
    m_vertices[17].texCoords = sf::Vector2<float>(right, top);


    // Middle left area
    m_vertices[18].texCoords = sf::Vector2<float>(left, midTop);
    m_vertices[19].texCoords = sf::Vector2<float>(midLeft, midTop);
    m_vertices[20].texCoords = sf::Vector2<float>(left, midBottom);
    m_vertices[21].texCoords = sf::Vector2<float>(midLeft, midBottom);
    m_vertices[22].texCoords = sf::Vector2<float>(left, midBottom);
    m_vertices[23].texCoords = sf::Vector2<float>(midLeft, midTop);

    // Middle middle area
    m_vertices[24].texCoords = sf::Vector2<float>(midLeft, midTop);
    m_vertices[25].texCoords = sf::Vector2<float>(midRight, midTop);
    m_vertices[26].texCoords = sf::Vector2<float>(midLeft, midBottom);
    m_vertices[27].texCoords = sf::Vector2<float>(midRight, midBottom);
    m_vertices[28].texCoords = sf::Vector2<float>(midLeft, midBottom);
    m_vertices[29].texCoords = sf::Vector2<float>(midRight, midTop);

    // Middle right area
    m_vertices[30].texCoords = sf::Vector2<float>(midRight, midTop);
    m_vertices[31].texCoords = sf::Vector2<float>(right, midTop);
    m_vertices[32].texCoords = sf::Vector2<float>(midRight, midBottom);
    m_vertices[33].texCoords = sf::Vector2<float>(right, midBottom);
    m_vertices[34].texCoords = sf::Vector2<float>(midRight, midBottom);
    m_vertices[35].texCoords = sf::Vector2<float>(right, midTop);


    // Bottom left area
    m_vertices[36].texCoords = sf::Vector2<float>(left, midBottom);
    m_vertices[37].texCoords = sf::Vector2<float>(midLeft, midBottom);
    m_vertices[38].texCoords = sf::Vector2<float>(left, bottom);
    m_vertices[39].texCoords = sf::Vector2<float>(midLeft, bottom);
    m_vertices[40].texCoords = sf::Vector2<float>(left, bottom);
    m_vertices[41].texCoords = sf::Vector2<float>(midLeft, midBottom);

    // Bottom middle area
    m_vertices[42].texCoords = sf::Vector2<float>(midLeft, midBottom);
    m_vertices[43].texCoords = sf::Vector2<float>(midRight, midBottom);
    m_vertices[44].texCoords = sf::Vector2<float>(midLeft, bottom);
    m_vertices[45].texCoords = sf::Vector2<float>(midRight, bottom);
    m_vertices[46].texCoords = sf::Vector2<float>(midLeft, bottom);
    m_vertices[47].texCoords = sf::Vector2<float>(midRight, midBottom);

    // Bottom right area
    m_vertices[48].texCoords = sf::Vector2<float>(midRight, midBottom);
    m_vertices[49].texCoords = sf::Vector2<float>(right, midBottom);
    m_vertices[50].texCoords = sf::Vector2<float>(midRight, bottom);
    m_vertices[51].texCoords = sf::Vector2<float>(right, bottom);
    m_vertices[52].texCoords = sf::Vector2<float>(midRight, bottom);
    m_vertices[53].texCoords = sf::Vector2<float>(right, midBottom);
}
