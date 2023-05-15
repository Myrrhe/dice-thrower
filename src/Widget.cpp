/*
 * A widget class.
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

#include "LogManager.hpp"
#include "Widget.hpp"
#include "func.hpp"
#include <iostream>
#include <istream>

Widget::Widget() :
    width(0.0f),
    height(0.0f),
    focused(false),
    window(nullptr)
{
    //ctor
}

Widget::~Widget()
{
    //dtor
}

Widget::Widget(const Widget& other) : sf::Transformable(other), sf::Drawable(other),
    width(other.width),
    height(other.height),
    focused(other.focused),
    window(nullptr)
{
    //copy ctor
}

Widget& Widget::operator=(const Widget& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    sf::Transformable::operator=(rhs);
    sf::Drawable::operator=(rhs);
    width = rhs.width;
    height = rhs.height;
    focused = rhs.focused;
    window = rhs.window;
    return *this;
}

void Widget::setWindow(const sf::Window* newWindow)
{
    window = newWindow;
}

bool Widget::isMouseOnWidget() const
{
    //sf::Rect<float> rectInput(getLocalBounds().width*0.5f - width*0.5f, getLocalBounds().height*0.5f - height*0.5f, width, height);
    sf::Rect<float> rectInput = getLocalBounds();
#if DEBUG
    if (window == nullptr)
    {
        std::cout << "Warning : No window has been assigned to the widget." << std::endl;
    }
#endif // DEBUG
    sf::Vector2<float> posMouseRel = getInverseTransform().transformPoint(static_cast<sf::Vector2<float> >(sf::Mouse::getPosition(*window)));
    return rectInput.contains(posMouseRel);
}

bool Widget::isFocused()
{
    return focused;
}

void Widget::setFocus(bool newFocus)
{
    focused = newFocus;
}

void Widget::flipFocus()
{
    focused = !focused;
}
