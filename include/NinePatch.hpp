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

#ifndef NINE_PATCH_HPP
#define NINE_PATCH_HPP
#include <SFML/Graphics.hpp>

class NinePatch final : public sf::Transformable, public sf::Drawable
{
public:

    NinePatch();

    explicit NinePatch(const sf::Texture& texture);

    NinePatch(const sf::Texture& texture, const sf::Rect<int>& rectangle);

    ~NinePatch();

    NinePatch(const NinePatch& other);

    NinePatch& operator=(const NinePatch& rhs);

    void setTexture(const sf::Texture& texture, bool resetRect = false);

    void setTextureRect(int newLeft, int newTop, int newWidth, int newHeight);
    void setTextureRect(const sf::Rect<int>& rectangle);

    void setColor(const sf::Color& color);

    void setWidth(float newWidth);
    void setHeight(float newWidth);
    void setSize(const sf::Vector2<float> newSize);
    void setSize(float newWidth, float newHeight);
    void setSize(float newSize);

    void setLeftBorder(float leftBorder);
    void setTopBorder(float topBorder);
    void setRightBorder(float rightBorder);
    void setBottomBorder(float bottomBorder);
    void setBorder(float leftBorder, float topBorder, float rightBorder, float bottomBorder);
    void setBorder(float border);

    const sf::Texture* getTexture() const;

    const sf::Rect<int>& getTextureRect() const;

    const sf::Color& getColor() const;

    sf::Rect<float> getLocalBounds() const;

    sf::Rect<float> getGlobalBounds() const;

    float getWidth() const;
    float getHeight() const;

    float getLeftBorder() const;
    float getTopBorder() const;
    float getRightBorder() const;
    float getBottomBorder() const;

protected:
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updatePositions();

    void updateTexCoords();

    std::array<sf::Vertex, 54> m_vertices;
    const sf::Texture*         m_texture;
    sf::Rect<int>              m_textureRect;
    float                      m_width;
    float                      m_height;
    float                      m_leftBorder;
    float                      m_topBorder;
    float                      m_rightBorder;
    float                      m_bottomBorder;
};

#endif // NINE_PATCH_HPP
