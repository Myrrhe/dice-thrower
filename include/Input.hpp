/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#ifndef INPUT_HPP
#define INPUT_HPP
#include <iostream>
#include <istream>
#include <SFML/Graphics.hpp>

class Input final
{
public:

	enum class InputFl : long unsigned int
	{
	    LEFT  = 1,
	    RIGHT = 1 << 1,
	    UP    = 1 << 2,
	    DOWN  = 1 << 3,
	    SLOW  = 1 << 4,
	    SHOT  = 1 << 5,
	    BOMB  = 1 << 6,
	    NEXT  = 1 << 7,
	    PREV  = 1 << 8,
	    SKIP  = 1 << 9
	};

	enum class TypeInput : long unsigned int
	{
	    KEYBOARD,
	    MOUSE,
	    JOYSTICK_AXIS,
	    JOYSTICK,
	    ERROR_TYPE_INPUT
	};

Input();
~Input();
explicit Input(const sf::Keyboard::Key& newKey);
explicit Input(const sf::Mouse::Button& newButton);
explicit Input(const sf::Joystick::Axis& newAxis,
	           unsigned int newIdJoystick = 0u,
	           bool newSignAxis = true);
explicit Input(unsigned int newButtonJoystick, unsigned int newIdJoystick = 0u);
explicit Input(const std::string& str);
Input(const Input& input) noexcept;
Input& operator=(const Input& input);
std::string to_string() const;
bool operator==(const Input& input) const;
bool operator!=(const Input& input) const;
bool isPressed() const;
TypeInput getTypeInput() const;
sf::Keyboard::Key getKey() const;
sf::Mouse::Button getButton() const;
sf::Joystick::Axis getAxis() const;
bool getSignAxis() const;
unsigned int getButtonJoyStick() const;
unsigned int getIdJoystick() const;

static void initialize();
static long unsigned int getJoystickSensitivity();
static void setJoystickSensitivity(long unsigned int newJoystickSensitivity);

protected:

private:

    TypeInput typeInput;
    sf::Keyboard::Key key;
    sf::Mouse::Button button;
    sf::Joystick::Axis axis;
    unsigned int buttonJoystick;
    unsigned int idJoystick;
    bool signAxis;

    static long unsigned int joystickSensitivity;
};

long unsigned int operator|(const Input::InputFl& inputFl1, const Input::InputFl& inputFl2);
long unsigned int operator|(long unsigned int inputFl1, const Input::InputFl& inputFl2);

#endif // INPUT_HPP
