/*
 * A button class that can be clicked on.
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

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "ClickableWidget.hpp"

class Button final : public ClickableWidget
{
public:

    Button();

    Button(float newWidth, float newHeight, const sf::Texture* newTexture, const sf::Window* newWindow);

    ~Button();

    Button(const Button& other);

    Button& operator=(const Button& other);

    void update();

    sf::Rect<float> getLocalBounds() const override;

    sf::Rect<float> getGlobalBounds() const;

    void setTexture(const sf::Texture* newTexture);

    void setTextureRect(int newLeft, int newTop, int newWidth, int newHeight);

    void setColor(const sf::Color& color);

protected:

    void updatePositions();
    void updateTexCoords();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const sf::Texture* texture;
    std::array<sf::Vertex, 4> vertices;
    sf::Rect<int> textureRect;
};

#endif // BUTTON_HPP
