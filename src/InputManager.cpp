#include "InputManager.hpp"
#include "Window.hpp"
#include <SFML/Graphics.hpp>

bool InputManager::qEntered;
bool InputManager::leftEntered;
bool InputManager::rightEntered;

long unsigned int InputManager::arrowThicker;

bool InputManager::firstInputEntered;

bool InputManager::insertMode;

bool InputManager::mouseClicked;
bool InputManager::firstFrameMouseClicked;
sf::Vector2<int> InputManager::firstPosMouseClicked;

const std::array<std::string, sf::Joystick::AxisCount> InputManager::strAxis = {{"X",
                                                                                 "Y",
                                                                                 "Z",
                                                                                 "R",
                                                                                 "U",
                                                                                 "V",
                                                                                 "PovX",
                                                                                 "PovY"}};

void InputManager::initialize()
{
    qEntered = false;
    leftEntered = false;
    rightEntered = false;

    firstInputEntered = false;

    insertMode = false;

    mouseClicked = false;
    firstFrameMouseClicked = false;
    firstPosMouseClicked = sf::Vector2<int>(0, 0);
}

void InputManager::resetInput()
{
    qEntered = false;
    leftEntered = false;
    rightEntered = false;
}

void InputManager::getInput()
{
    if (leftEntered || rightEntered)
    {
        arrowThicker++;
    }
    else
    {
        arrowThicker = 0;
    }
}

void InputManager::update()
{
    qEntered = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    leftEntered = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    rightEntered = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    if (Window::isKeyPressed())
    {
        if (Window::getKeyPressed() == sf::Keyboard::Key::Insert)
        {
            insertMode = !insertMode;
        }
    }
    if (!mouseClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouseClicked = true;
        firstPosMouseClicked = Window::getMousePosition();
        firstFrameMouseClicked = true;
    }
    else if (mouseClicked && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouseClicked = false;
        firstFrameMouseClicked = false;
    }
    else
    {
        firstFrameMouseClicked = false;
    }
}

bool InputManager::getQEntered()
{
    return qEntered;
}

bool InputManager::getLeftEntered()
{
    return leftEntered;
}

bool InputManager::getRightEntered()
{
    return rightEntered;
}

long unsigned int InputManager::getArrowThicker()
{
    return arrowThicker;
}

bool InputManager::isInsertMode()
{
    return insertMode;
}

bool InputManager::isFirstFrameMouseClicked()
{
    return firstFrameMouseClicked;
}

const sf::Vector2<int>& InputManager::getFirstPosMouseClicked()
{
    return firstPosMouseClicked;
}

bool InputManager::isInput(const std::string& str)
{
	bool res = false;
    res = res || str == "A";
    res = res || str == "B";
    res = res || str == "C";
    res = res || str == "D";
    res = res || str == "E";
    res = res || str == "F";
    res = res || str == "G";
    res = res || str == "H";
    res = res || str == "I";
    res = res || str == "J";
    res = res || str == "K";
    res = res || str == "L";
    res = res || str == "M";
    res = res || str == "N";
    res = res || str == "O";
    res = res || str == "P";
    res = res || str == "Q";
    res = res || str == "R";
    res = res || str == "S";
    res = res || str == "T";
    res = res || str == "U";
    res = res || str == "V";
    res = res || str == "W";
    res = res || str == "X";
    res = res || str == "Y";
    res = res || str == "Z";
    res = res || str == "Num0";
    res = res || str == "Num1";
    res = res || str == "Num2";
    res = res || str == "Num3";
    res = res || str == "Num4";
    res = res || str == "Num5";
    res = res || str == "Num6";
    res = res || str == "Num7";
    res = res || str == "Num8";
    res = res || str == "Num9";
    res = res || str == "Escape";
    res = res || str == "LControl";
    res = res || str == "LShift";
    res = res || str == "LAlt";
    res = res || str == "LSystem";
    res = res || str == "RControl";
    res = res || str == "RShift";
    res = res || str == "RAlt";
    res = res || str == "RSystem";
    res = res || str == "Menu";
    res = res || str == "LBracket";
    res = res || str == "RBracket";
    res = res || str == "SemiColon";
    res = res || str == "Comma";
    res = res || str == "Period";
    res = res || str == "Quote";
    res = res || str == "Slash";
    res = res || str == "BackSlash";
    res = res || str == "Tilde";
    res = res || str == "Hyphen";
    res = res || str == "Space";
    res = res || str == "Enter";
    res = res || str == "BackSpace";
    res = res || str == "Tab";
    res = res || str == "PageUp";
    res = res || str == "PageDown";
    res = res || str == "End";
    res = res || str == "Home";
    res = res || str == "Insert";
    res = res || str == "Delete";
    res = res || str == "Add";
    res = res || str == "Substract";
    res = res || str == "Multiply";
    res = res || str == "Divide";
    res = res || str == "Left";
    res = res || str == "Right";
    res = res || str == "Up";
    res = res || str == "Down";
    res = res || str == "Numpad0";
    res = res || str == "Numpad1";
    res = res || str == "Numpad2";
    res = res || str == "Numpad3";
    res = res || str == "Numpad4";
    res = res || str == "Numpad5";
    res = res || str == "Numpad6";
    res = res || str == "Numpad7";
    res = res || str == "Numpad8";
    res = res || str == "Numpad9";
    res = res || str == "F1";
    res = res || str == "F2";
    res = res || str == "F3";
    res = res || str == "F4";
    res = res || str == "F5";
    res = res || str == "F6";
    res = res || str == "F7";
    res = res || str == "F8";
    res = res || str == "F9";
    res = res || str == "F10";
    res = res || str == "F11";
    res = res || str == "F12";
    res = res || str == "F13";
    res = res || str == "F14";
    res = res || str == "F15";
    res = res || str == "Pause";
    res = res || str == "LeftMouse";
    res = res || str == "RightMouse";
    res = res || str == "MiddleMouse";
    res = res || str == "XButton1";
    res = res || str == "XButton2";
    for (unsigned int i = 0u; i < sf::Joystick::Count; i++)
    {
        res = res || str == "XAxis-" + std::to_string(i);
        res = res || str == "XAxis+" + std::to_string(i);
        res = res || str == "YAxis-" + std::to_string(i);
        res = res || str == "YAxis+" + std::to_string(i);
        res = res || str == "ZAxis-" + std::to_string(i);
        res = res || str == "ZAxis+" + std::to_string(i);
        res = res || str == "RAxis-" + std::to_string(i);
        res = res || str == "RAxis+" + std::to_string(i);
        res = res || str == "UAxis-" + std::to_string(i);
        res = res || str == "UAxis+" + std::to_string(i);
        res = res || str == "VAxis-" + std::to_string(i);
        res = res || str == "VAxis+" + std::to_string(i);
        res = res || str == "PovXAxis-" + std::to_string(i);
        res = res || str == "PovXAxis+" + std::to_string(i);
        res = res || str == "PovYAxis-" + std::to_string(i);
        res = res || str == "PovYAxis+" + std::to_string(i);
        for (unsigned int j = 0u; j < sf::Joystick::ButtonCount; j++)
        {
            res = res || str == "JoystickButton" + std::to_string(i) + "-" + std::to_string(j);
        }
    }
    return res;
}

bool InputManager::isInputPressed()
{
    bool res = false;
    for (unsigned int i = 0u; i < sf::Keyboard::KeyCount; i++)
    {
        res = res || sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
    }
    for (unsigned int i = 0u; i < sf::Mouse::ButtonCount; i++)
    {
        res = res || sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i));
    }
    for (unsigned int i = 0u; i < sf::Joystick::Count; i++)
	{
        for (unsigned int j = 0; j < sf::Joystick::AxisCount; j++)
        {
            res = res || (sf::Joystick::isConnected(i)
                       && sf::Joystick::hasAxis(i, static_cast<sf::Joystick::Axis>(j))
                       && (sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity())
                        || sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) < -static_cast<float>(Input::getJoystickSensitivity())));
        }
	    for (unsigned int j = 0u; j < sf::Joystick::ButtonCount; j++)
	    {
            res = res || (sf::Joystick::isConnected(i) && sf::Joystick::isButtonPressed(i, j));
	    }
	}
    return res;
}

Input InputManager::getInputPressed()
{
    Input res = Input(sf::Keyboard::Key::A);
    for (unsigned int i = 0u; i < sf::Keyboard::KeyCount; i++)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        {
            res = Input(static_cast<sf::Keyboard::Key>(i));
        }
    }
    for (unsigned int i = 0u; i < sf::Mouse::ButtonCount; i++)
    {
        if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i)))
        {
            res = Input(static_cast<sf::Mouse::Button>(i));
        }
    }
    for (unsigned int i = 0u; i < sf::Joystick::Count; i++)
	{
        for (unsigned int j = 0; j < sf::Joystick::AxisCount; j++)
        {
            if (sf::Joystick::isConnected(i)
             && sf::Joystick::hasAxis(i, static_cast<sf::Joystick::Axis>(j))
             && (sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity())
              || sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) < -static_cast<float>(Input::getJoystickSensitivity())))
            {
                res = Input(static_cast<sf::Joystick::Axis>(j), i, sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity()));
            }
        }
	    for (unsigned int j = 0; j < sf::Joystick::ButtonCount; j++)
	    {
            if (sf::Joystick::isConnected(i) && sf::Joystick::isButtonPressed(i, j))
			{
				res = Input(j, i);
			}
	    }
	}
    return res;
}

std::vector<Input> InputManager::getAllInputPressed()
{
    std::vector<Input> res;
    for (unsigned int i = 0u; i < sf::Keyboard::KeyCount; i++)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        {
            res.push_back(Input(static_cast<sf::Keyboard::Key>(i)));
        }
    }
    for (unsigned int i = 0u; i < sf::Mouse::ButtonCount; i++)
    {
        if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i)))
        {
            res.push_back(Input(static_cast<sf::Mouse::Button>(i)));
        }
    }
    for (unsigned int i = 0u; i < sf::Joystick::Count; i++)
    {
        for (unsigned int j = 0; j < sf::Joystick::AxisCount; j++)
        {
            if (sf::Joystick::isConnected(i)
             && sf::Joystick::hasAxis(i, static_cast<sf::Joystick::Axis>(j))
             && (sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity())
              || sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) < -static_cast<float>(Input::getJoystickSensitivity())))
            {
                res.push_back(Input(static_cast<sf::Joystick::Axis>(j), i, sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity())));
            }
        }
        for (unsigned int j = 0; j < sf::Joystick::ButtonCount; j++)
        {
            if (sf::Joystick::isConnected(i) && sf::Joystick::isButtonPressed(i, j))
            {
                res.push_back(Input(j, i));
            }
        }
    }
    return res;
}

long unsigned int InputManager::getNumberInputPressed()
{
    long unsigned int res = 0ul;
    for (unsigned int i = 0u; i < sf::Keyboard::KeyCount; i++)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)))
        {
            res++;
        }
    }
    for (unsigned int i = 0u; i < sf::Mouse::ButtonCount; i++)
    {
        if (sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(i)))
        {
            res++;
        }
    }
    for (unsigned int i = 0u; i < sf::Joystick::Count; i++)
    {
        for (unsigned int j = 0; j < sf::Joystick::AxisCount; j++)
        {
            if (sf::Joystick::isConnected(i)
             && sf::Joystick::hasAxis(i, static_cast<sf::Joystick::Axis>(j))
             && (sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) > static_cast<float>(Input::getJoystickSensitivity())
              || sf::Joystick::getAxisPosition(i, static_cast<sf::Joystick::Axis>(j)) < -static_cast<float>(Input::getJoystickSensitivity())))
            {
                res++;
            }
        }
        for (unsigned int j = 0; j < sf::Joystick::ButtonCount; j++)
        {
            if (sf::Joystick::isConnected(i) && sf::Joystick::isButtonPressed(i, j))
            {
                res++;
            }
        }
    }
    return res;
}

bool InputManager::getFirstInputPressed()
{
    return firstInputEntered;
}

void InputManager::setFirstInputPressed()
{
    firstInputEntered = true;
}
