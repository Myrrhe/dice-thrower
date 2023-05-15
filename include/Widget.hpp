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

#ifndef WIDGET_HPP
#define WIDGET_HPP
#include <SFML/Graphics.hpp>

class Widget : public sf::Transformable, public sf::Drawable
{
public:

    Widget();
    virtual ~Widget();
    Widget(const Widget& other);
    Widget& operator=(const Widget& other);

    void setWindow(const sf::Window* newWindow);

    bool isFocused();
    void setFocus(bool newFocus);
    void flipFocus();

protected:

    virtual sf::Rect<float> getLocalBounds() const = 0;

    bool isMouseOnWidget() const;

    float width;
    float height;

    bool focused;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    const sf::Window* window;
};

#endif // WIDGET_HPP
