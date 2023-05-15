/*
 * A clickable widget class.
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

#include "ClickableWidget.hpp"
#include <iostream>
#include <istream>

ClickableWidget::ClickableWidget() :
    state(State::MOUSE_NOT_ON_WIDGET),
    newState(State::MOUSE_NOT_ON_WIDGET)
{
    //ctor
}

ClickableWidget::~ClickableWidget()
{
    //dtor
}

ClickableWidget::ClickableWidget(const ClickableWidget& other) : Widget(other),
    state(other.state),
    newState(other.newState)
{
    //copy ctor
}

ClickableWidget& ClickableWidget::operator=(const ClickableWidget& rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    //assignment operator
    Widget::operator=(rhs);
    state = rhs.state;
    newState = rhs.newState;
    return *this;
}

ClickableWidget::State ClickableWidget::getInput()
{
    bool leftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool mouseOnWidget = isMouseOnWidget();
    if (newState == State::MOUSE_NOT_ON_WIDGET) // The mouse is not on the widget
    {
        if (mouseOnWidget)
        {
            newState = State::MOUSE_ON_WIDGET;
        }
        else if (leftButtonPressed)
        {
            newState = State::MOUSE_CLICKED_NOT_ON_WIDGET;
        }
    }
    if (newState == State::MOUSE_CLICKED_NOT_ON_WIDGET) // The mouse is clicked and is not on the widget
    {
        if (mouseOnWidget)
        {
            newState = State::MOUSE_CLICKED_OUT_ON_WIDGET;
        }
        else if (!leftButtonPressed)
        {
            newState = State::MOUSE_NOT_ON_WIDGET;
        }
    }
    if (newState == State::MOUSE_CLICKED_OUT_ON_WIDGET) // The mouse was clicked while out of the widget, and was displaced inside the widget
    {
        if (!mouseOnWidget)
        {
            newState = State::MOUSE_CLICKED_NOT_ON_WIDGET;
        }
        else if (!leftButtonPressed)
        {
            newState = State::MOUSE_ON_WIDGET;
        }
    }
    if (newState == State::MOUSE_ON_WIDGET) // Mouse on widget
    {
        if (!mouseOnWidget)
        {
            newState = State::MOUSE_NOT_ON_WIDGET;
        }
        else if (leftButtonPressed)
        {
            newState = State::MOUSE_CLICKED;
        }
    }
    if (newState == State::MOUSE_CLICKED) // Mouse on button and clicked
    {
        if (!mouseOnWidget)
        {
            newState = State::MOUSE_CLICKED_OUT_OF_WIDGET;
        }
        else if (!leftButtonPressed)
        {
            newState = State::MOUSE_ON_WIDGET;
            return State::CLICKED; // Important note : This state is never a persistent state (i.e), a widget can't have this state
        }
    }
    if (newState == State::MOUSE_CLICKED_OUT_OF_WIDGET) // The mouse was clicked while inside the widget, and was displaced outside the widget
    {
        if (mouseOnWidget)
        {
            newState = State::MOUSE_CLICKED;
        }
        else if (!leftButtonPressed)
        {
            newState = State::MOUSE_NOT_ON_WIDGET;
        }
    }
    return newState;
}

bool ClickableWidget::stateChanged()
{
    bool res = state != newState;
    state = newState;
    return res;
}

std::ostream& operator<<(std::ostream& os, ClickableWidget::State state)
{
    return os << static_cast<long unsigned int>(state);
}
