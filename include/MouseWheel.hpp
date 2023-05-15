/*
 * This class check the state of the mouse wheel.
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

#ifndef MOUSEWHEEL_HPP
#define MOUSEWHEEL_HPP

class MouseWheel final
{
public:

    MouseWheel() = delete;
    MouseWheel(const MouseWheel& right) = delete;
    MouseWheel(MouseWheel&& right) = delete;
    MouseWheel& operator=(const MouseWheel& right) = delete;
    MouseWheel& operator=(MouseWheel&& right) = delete;
    ~MouseWheel() = delete;

    static void initialize();

    static void setDeltaWheel(int newDelta);
    static int getDeltaWheel();

protected:

private:
    static int deltaWheel;
};

#endif // MOUSEWHEEL_HPP
