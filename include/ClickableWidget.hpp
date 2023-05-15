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

#ifndef CLICKABLEWIDGET_HPP
#define CLICKABLEWIDGET_HPP
#include "Widget.hpp"

class ClickableWidget : public Widget
{
public:

    enum class State : long unsigned int
    {
        MOUSE_NOT_ON_WIDGET,
        MOUSE_CLICKED_NOT_ON_WIDGET,
        MOUSE_CLICKED_OUT_ON_WIDGET,
        MOUSE_ON_WIDGET,
        MOUSE_CLICKED,
        MOUSE_CLICKED_OUT_OF_WIDGET,
        CLICKED
    };

    ClickableWidget();
    virtual ~ClickableWidget();
    ClickableWidget(const ClickableWidget& other);
    ClickableWidget& operator=(const ClickableWidget& other);

    virtual State getInput();

    bool stateChanged();

protected:
    State state;
private:
    State newState;
};
std::ostream& operator<<(std::ostream& os, ClickableWidget::State state);

#endif // CLICKABLEWIDGET_HPP
