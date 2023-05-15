/*
 * A button class that can be clicked on.
 * Copyright (C) 2020  <copyright holder> <email>
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

#include "Button.hpp"
#include "Window.hpp"
#include <iostream>
#include <istream>

Button::Button() :
texture(nullptr),
vertices(std::array<sf::Vertex, 4>()),
textureRect(sf::Rect<int>(0, 0, 0, 0))
{
    //ctor
}

Button::Button(float newWidth, float newHeight, const sf::Texture* newTexture, const sf::Window* newWindow) :
texture(nullptr),
vertices(std::array<sf::Vertex, 4>()),
textureRect(sf::Rect<int>())
{
    width = newWidth;
    height = newHeight;
    setTexture(newTexture);
    setWindow(newWindow);
}

Button::~Button()
{
    //dtor
}

Button::Button(const Button& other) : ClickableWidget(other),
texture(other.texture),
vertices(other.vertices),
textureRect(other.textureRect)
{
    //copy ctor
}

Button& Button::operator=(const Button& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    ClickableWidget::operator=(rhs);
    texture = rhs.texture;
    vertices = rhs.vertices;
    textureRect = rhs.textureRect;
    return *this;
}

void Button::update()
{
    if (stateChanged())
    {
        updateTexCoords();
    }
}

sf::Rect<float> Button::getLocalBounds() const
{
    return sf::Rect<float>(0.0f, 0.0f, static_cast<float>(std::abs(textureRect.width)), static_cast<float>(std::abs(textureRect.height/4)));
}

sf::Rect<float> Button::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Button::setTexture(const sf::Texture* newTexture)
{
    texture = newTexture;
}

void Button::setTextureRect(int newLeft, int newTop, int newWidth, int newHeight)
{
    textureRect = sf::Rect<int>(newLeft, newTop, newWidth, newHeight);
    updatePositions();
    updateTexCoords();
}

void Button::setColor(const sf::Color& color)
{
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
}

void Button::updatePositions()
{
    sf::Rect<float> bounds = getLocalBounds();
    vertices[0].position = sf::Vector2<float>(0.0f, 0.0f);
    vertices[1].position = sf::Vector2<float>(0.0f, bounds.height);
    vertices[2].position = sf::Vector2<float>(bounds.width, 0.0f);
    vertices[3].position = sf::Vector2<float>(bounds.width, bounds.height);
}

void Button::updateTexCoords()
{
    float left   = static_cast<float>(textureRect.left);
    float right  = left + static_cast<float>(textureRect.width);
    float top    = static_cast<float>(textureRect.top);
    int posTex;
    switch (state)
    {
        case State::MOUSE_NOT_ON_WIDGET:         {posTex = 0; break;}
        case State::MOUSE_CLICKED_NOT_ON_WIDGET: {posTex = 0; break;}
        case State::MOUSE_CLICKED_OUT_ON_WIDGET: {posTex = 1; break;}
        case State::MOUSE_ON_WIDGET:             {posTex = 1; break;}
        case State::MOUSE_CLICKED:               {posTex = 2; break;}
        case State::MOUSE_CLICKED_OUT_OF_WIDGET: {posTex = 3; break;}
        case State::CLICKED:                     {posTex = 0; break;}
        default:                                 {posTex = 0; break;}
    }
    vertices[0].texCoords = sf::Vector2<float>(left, top + static_cast<float>(posTex*textureRect.height/4));
    vertices[1].texCoords = sf::Vector2<float>(left, top + static_cast<float>((posTex + 1)*textureRect.height/4));
    vertices[2].texCoords = sf::Vector2<float>(right, top + static_cast<float>(posTex*textureRect.height/4));
    vertices[3].texCoords = sf::Vector2<float>(right, top + static_cast<float>((posTex + 1)*textureRect.height/4));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = texture;
    target.draw(vertices.data(), 4, sf::PrimitiveType::TriangleStrip, states);
}
