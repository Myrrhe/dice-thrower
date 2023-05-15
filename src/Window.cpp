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

#include "LogManager.hpp"
#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "Window.hpp"
#include <iostream>
#include <istream>

sf::RenderWindow* Window::renderWindow;
sf::Texture* Window::textureIcon;

std::array<sf::View, 4> Window::views;
std::stack<Window::IdView> Window::stateView;

float Window::mainScale;

float Window::uiX;
float Window::uiY;
float Window::uiWidth;
float Window::uiHeight;

float Window::offsetX;
float Window::offsetY;

sf::Vector2<unsigned int> Window::monitorSize;

bool Window::textEntered;
char32_t Window::charEntered;

bool Window::keyPressed;
sf::Keyboard::Key Window::codeKeyPressed;

bool Window::altEntered;
bool Window::controlEntered;
bool Window::shiftEntered;
bool Window::systemEntered;

#if DEBUG
long unsigned int Window::thickerLock;
long unsigned int Window::thickerStep;
bool Window::isLock;
const long unsigned int Window::DurationThickerLock = 15;
const long unsigned int Window::DurationThickerStep = 2;
#endif // DEBUG
#if PERF
double Window::timeCreation;
#endif // PERF

const long unsigned int Window::Width = 600;
const long unsigned int Window::Height = 600;

const bool Window::Fullscreen = false;

void Window::getMonitorSize()
{
    //displayVideoModeAvailable();
    monitorSize = OsManager::getMonitorSize();
}

void Window::create()
{
#if PERF
    double ti = OsManager::getCpuTime();
#endif // PERF
    (renderWindow = new sf::RenderWindow)->create(sf::VideoMode(Width, Height, 32u), "", sf::Style::Titlebar | sf::Style::Close,
            sf::ContextSettings(0, 0, 0, 1u, 1u, sf::ContextSettings::Attribute::Default, false));
    //stateView.push(IdView::MAIN);
    stateView.push(IdView::MAIN);
    setViewTarget(*renderWindow);
#if PERF
    timeCreation = OsManager::getCpuTime() - ti;
#endif // PERF
}

void Window::initialize()
{
    textureIcon = new sf::Texture;
    textureIcon->loadFromFile(PathManager::getPath(PathManager::Dir::IMG) + OsManager::Slash + OsManager::StrIcon);
    textureIcon->setSmooth(false);
    textureIcon->setRepeated(false);
    if (textureIcon->getSize().x > 0 && textureIcon->getSize().y > 0)
    {
        renderWindow->setIcon(OsManager::WidthIcon, OsManager::HeightIcon, textureIcon->copyToImage().getPixelsPtr());
    }
    renderWindow->setTitle("Watch");
    renderWindow->setVerticalSyncEnabled(false);
    renderWindow->setMouseCursorVisible(true);
    renderWindow->setMouseCursorGrabbed(false);
    renderWindow->setFramerateLimit(60);

#if PERF
    LogManager::append(std::to_string(timeCreation));
#endif // PERF

    textEntered = false;
    charEntered = 0;

    keyPressed = 0;
    codeKeyPressed = sf::Keyboard::Key::A;

    altEntered = false;
    controlEntered = false;
    shiftEntered = false;
    systemEntered = false;

#if DEBUG
    thickerLock = 0;
    thickerStep = 0;
    isLock = false;
#endif // DEBUG
}

void Window::terminate()
{
    delete renderWindow;
    delete textureIcon;
}

void Window::pushStateView(IdView idView)
{
    stateView.push(idView);
}

void Window::popStateView()
{
    stateView.pop();
}

void Window::setViewTarget(sf::RenderTarget& renderTarget)
{
    sf::Vector2<unsigned int> sizeTarget = renderTarget.getSize();
    switch (stateView.top())
    {
    case IdView::MAIN:
    {
        mainScale = std::min(static_cast<float>(sizeTarget.x)/static_cast<float>(Width), static_cast<float>(sizeTarget.y)/static_cast<float>(Height));
        float rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        float rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[0].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[0].setViewport(sf::Rect<float>((rendingSizeX - Width*mainScale)*0.5f/rendingSizeX,
                                             (rendingSizeY - Height*mainScale)*0.5f/rendingSizeY,
                                             1.0f - 2.0f*(rendingSizeX - Width*mainScale)*0.5f/rendingSizeX,
                                             1.0f - 2.0f*(rendingSizeY - Height*mainScale)*0.5f/rendingSizeY));
        renderTarget.setView(views[0]);
        break;
    }
    case IdView::UI:
    {
        float rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        float rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[1].reset(sf::Rect<float>(uiX, uiY, uiWidth, uiHeight));
        views[1].setViewport(sf::Rect<float>(((rendingSizeX - Width*mainScale)*0.5f + uiX*mainScale)/rendingSizeX,
                                             ((rendingSizeY - Height*mainScale)*0.5f + uiY*mainScale)/rendingSizeY,
                                             uiWidth*mainScale/rendingSizeX,
                                             uiHeight*mainScale/rendingSizeY));
        renderTarget.setView(views[1]);
        break;
    }
    case IdView::SHAKE:
    {
        mainScale = std::min(static_cast<float>(sizeTarget.x)/static_cast<float>(Width), static_cast<float>(sizeTarget.y)/static_cast<float>(Height));
        float rendingSizeX = static_cast<float>(Fullscreen ? monitorSize.x : sizeTarget.x);
        float rendingSizeY = static_cast<float>(Fullscreen ? monitorSize.y : sizeTarget.y);
        views[2].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[2].setViewport(sf::Rect<float>((rendingSizeX - (Width + 2.0f*offsetX)*mainScale)*0.5f/rendingSizeX,
                                             (rendingSizeY - (Height + 2.0f*offsetY)*mainScale)*0.5f/rendingSizeY,
                                             1.0f - 2.0f*(rendingSizeX - Width*mainScale)*0.5f/rendingSizeX,
                                             1.0f - 2.0f*(rendingSizeY - Height*mainScale)*0.5f/rendingSizeY));
        renderTarget.setView(views[2]);
        break;
    }
    case IdView::WHOLE:
    {
        views[3].reset(sf::Rect<float>(0.0f, 0.0f, Width, Height));
        views[3].setViewport(sf::Rect<float>(0.0f, 0.0f, 1.0f, 1.0f));
        renderTarget.setView(views[3]);
        break;
    }
    default:
    {
        break;
    }
    }
}

void Window::setUiView(float x, float y, float widthUi, float heightUi)
{
    uiX = x;
    uiY = y;
    uiWidth = widthUi;
    uiHeight = heightUi;
}

void Window::setOffsetX(float newOffsetX)
{
    offsetX = newOffsetX;
}

void Window::setOffsetY(float newOffsetY)
{
    offsetY = newOffsetY;
}

void Window::manageEvent()
{
    MouseWheel::setDeltaWheel(0);
    sf::Event event;
    textEntered = false;
    keyPressed = false;
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            renderWindow->close();
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            MouseWheel::setDeltaWheel(event.mouseWheel.delta);
        }
        else if (event.type == sf::Event::TextEntered)
        {
            textEntered = true;
            charEntered = event.text.unicode;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            keyPressed = true;
            codeKeyPressed = event.key.code;
            altEntered = event.key.alt;
            controlEntered = event.key.control;
            shiftEntered = event.key.shift;
            systemEntered = event.key.system;
        }
    }
}

bool Window::isOpen()
{
    return renderWindow->isOpen();
}

bool Window::pollEvent(sf::Event& event)
{
    return renderWindow->pollEvent(event);
}

bool Window::hasFocus()
{
    return renderWindow->hasFocus();
}

void Window::close()
{
    renderWindow->close();
}

void Window::clear(const sf::Color& color)
{
    renderWindow->clear(color);
}

void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
{
    renderWindow->draw(vertices, vertexCount, type, states);
}

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
    renderWindow->draw(drawable, states);
}

void Window::display()
{
#if DEBUG
    // Enter B to freeze/unfreeze the software, enter N to process one step
    if (isLock)
    {
        while (true)
        {
            OsManager::sleep(1000000/60.0);
            if (thickerLock)
            {
                thickerLock--;
            }
            else if (hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
            {
                thickerLock = 15;
                isLock = false;
                break;
            }
            if (thickerStep)
            {
                thickerStep--;
            }
            else if (hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N))
            {
                thickerStep = 2;
                break;
            }
            manageEvent();
        }
    }
    else if (thickerLock)
    {
        thickerLock--;
    }
    else if (hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
    {
        thickerLock = DurationThickerLock;
        isLock = true;
    }
#endif // DEBUG
    renderWindow->display();
}

sf::Vector2<int> Window::getMousePosition()
{
    return sf::Mouse::getPosition(*renderWindow);
}

sf::Vector2<float> Window::mapPixelToCoords(const sf::Vector2<int>& point)
{
    return renderWindow->mapPixelToCoords(point);
}

sf::RenderWindow* Window::getRenderWindow()
{
    return renderWindow;
}

bool Window::isTextEntered()
{
    return textEntered;
}

char32_t Window::getCharEntered()
{
    return charEntered;
}

bool Window::isKeyPressed()
{
    return keyPressed;
}

sf::Keyboard::Key Window::getKeyPressed()
{
    return codeKeyPressed;
}

bool Window::isAltEntered()
{
    return altEntered;
}

bool Window::isControlEntered()
{
    return controlEntered;
}

bool Window::isShiftEntered()
{
    return shiftEntered;
}

bool Window::isSystemEntered()
{
    return systemEntered;
}
