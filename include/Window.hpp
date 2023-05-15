/*
 * The file that manage the main window.
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

#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <stack>
#include <SFML/Graphics.hpp>

class Window final
{
public:

    enum class IdView : long unsigned int
    {
        MAIN,
        UI,
        SHAKE,
        WHOLE
    };

    Window() = delete;
    Window(const Window& right) = delete;
    Window(Window&& right) = delete;
    Window& operator=(const Window& right) = delete;
    Window& operator=(Window&& right) = delete;
    ~Window() = delete;

    static void getMonitorSize();

    static void create();
    static void initialize();
    static void terminate();

    static void pushStateView(IdView idView);
    static void popStateView();
    static void setViewTarget(sf::RenderTarget& renderTarget);

    static void setUiView(float x, float y, float widthUi, float heightUi);

    static void setOffsetX(float newOffsetX);
    static void setOffsetY(float newOffsetY);

    static void manageEvent();

    static bool isOpen();
    static bool pollEvent(sf::Event& event);
    static bool hasFocus();
    static void close();
    static void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));
    static void draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);
    static void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
    static void display();
    static sf::Vector2<int> getMousePosition();
    static sf::Vector2<float> mapPixelToCoords(const sf::Vector2<int>& point);

    static sf::RenderWindow* getRenderWindow();

    static bool isTextEntered();
    static char32_t getCharEntered();

    static bool isKeyPressed();
    static sf::Keyboard::Key getKeyPressed();

    static bool isAltEntered();
    static bool isControlEntered();
    static bool isShiftEntered();
    static bool isSystemEntered();

    static const long unsigned int Width;
    static const long unsigned int Height;

    //static const float RatioSize;

    static const bool Fullscreen;

protected:

private:
    static sf::RenderWindow* renderWindow;
    static sf::Texture* textureIcon;

    static std::array<sf::View, 4> views;
    static std::stack<IdView> stateView;

    static float mainScale;

    static float uiX;
    static float uiY;
    static float uiWidth;
    static float uiHeight;

    static float offsetX;
    static float offsetY;

    static sf::Vector2<unsigned int> monitorSize;

    static bool textEntered;
    static char32_t charEntered;

    static bool keyPressed;
    static sf::Keyboard::Key codeKeyPressed;

    static bool altEntered;
    static bool controlEntered;
    static bool shiftEntered;
    static bool systemEntered;

    #if DEBUG
        static long unsigned int thickerLock;
        static long unsigned int thickerStep;
        static bool isLock;
        static const long unsigned int DurationThickerLock;
        static const long unsigned int DurationThickerStep;
    #endif // DEBUG
    #if PERF
        static double timeCreation;
    #endif // PERF
};

#endif // WINDOW_HPP
