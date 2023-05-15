/*
 * The engine of the watch.
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

#include "Engine.hpp"
#include "Global.hpp"
#include "InputManager.hpp"
#include "LogManager.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "ScreenCapturer.hpp"
#include "Setting.hpp"
#include "Window.hpp"
#include "func.hpp"
#include <cmath>
#include <iostream>
#include <istream>

sf::Font* Engine::font;

sf::Texture* Engine::textureBack;
sf::Texture* Engine::textureTextBox;
sf::Texture* Engine::textureCursor;

std::array<sf::Vertex, 4> Engine::verticesBack;
TextBox Engine::textBoxProb;

bool Engine::firstIter;
long unsigned int Engine::frameCount;

void Engine::initialize()
{
    font = new sf::Font;
    textureBack = new sf::Texture;
    textureTextBox = new sf::Texture;
    textureCursor = new sf::Texture;

    std::vector<std::string> allFont = getDir(PathManager::getPath(PathManager::Dir::FONT));
    long unsigned int nbFile = allFont.size();
    for (long unsigned int i = 0; i < nbFile; i++)
    {
        if (allFont[i].size() < 4)
        {
            continue;
        }
        if (allFont[i].substr(allFont[i].size() - 4, std::string::npos) != ".ttf" && allFont[i].substr(allFont[i].size() - 4, std::string::npos) != ".otf")
        {
            continue;
        }
        font->loadFromFile(PathManager::getPath(PathManager::Dir::FONT) + OsManager::Slash + allFont[i]);
        break;
    }

    textureBack->loadFromFile(PathManager::getPath(PathManager::Dir::IMG) + OsManager::Slash + std::string("back.png"));
    textureBack->setSmooth(false);
    textureBack->setRepeated(false);
    verticesBack[0].position = sf::Vector2<float>(0.0f, 0.0f);
    verticesBack[1].position = sf::Vector2<float>(0.0f, static_cast<float>(Window::Width));
    verticesBack[2].position = sf::Vector2<float>(static_cast<float>(Window::Height), 0.0f);
    verticesBack[3].position = sf::Vector2<float>(static_cast<float>(Window::Height), static_cast<float>(Window::Width));
    for (long unsigned int i = 0; i < 4; i++)
    {
        verticesBack[i].texCoords = verticesBack[i].position;
        verticesBack[i].color = sf::Color(255, 255, 255, 255);
    }

    textureTextBox->loadFromFile(PathManager::getPath(PathManager::Dir::IMG) + OsManager::Slash + std::string("textbox.png"));
    textureTextBox->setSmooth(false);
    textureTextBox->setRepeated(false);
    textureCursor->loadFromFile(PathManager::getPath(PathManager::Dir::IMG) + OsManager::Slash + std::string("cursor.png"));
    textureCursor->setSmooth(false);
    textureCursor->setRepeated(false);
    textBoxProb = TextBox(400.0f, 48.0f, textureTextBox, Window::getRenderWindow());
    textBoxProb.setPointerChainText();
    //textBoxProb.setTexture(*textureTextBox);
    textBoxProb.setTextureRect(sf::Rect<int>(0, 0, 6, 6));
    textBoxProb.setBorder(2, 2, 2, 2);
    //textBoxProb.setSize(sf::Vector2<float>(400.0f, 40.0f));
    textBoxProb.setFont(*font);
    textBoxProb.setCharSize(34);
    //textBoxProb.setLetterSpacingFactor(1.0f);
    textBoxProb.setFillColor(sf::Color(255, 255, 255, 255));
    textBoxProb.setOutlineColor(sf::Color(0, 0, 0, 255));
    textBoxProb.setThickness(1.0f);
    textBoxProb.setRotation(0.0f);
    textBoxProb.setScale(1.0f, 1.0f);
    textBoxProb.setOrigin(0.0f, 0.0f);
    textBoxProb.setPosition(30.0f, 30.0f);
    textBoxProb.setColor(sf::Color(255, 255, 255, 255));
    textBoxProb.setPositionText(3.0f, 2.0f);
    textBoxProb.setTextureCursor(textureCursor);
    textBoxProb.setTextureRectCursor(sf::Rect<int>(0, 0, static_cast<int>(textureCursor->getSize().x), static_cast<int>(textureCursor->getSize().y)));
    textBoxProb.setCursorPositionOffset(5.0f, 5.0f);
    textBoxProb.setCursorPositionMax(395.0f, 2.0f);
    textBoxProb.setSizeBorderSlide(5.0f);

    firstIter = true;
    frameCount = 0;
}

void Engine::terminate()
{
    delete font;
    delete textureBack;
    delete textureTextBox;
    delete textureCursor;
}

void Engine::launch()
{
    initialize();
    while (Window::isOpen())
    {
        getInput();
        update();
        draw(*Window::getRenderWindow());
        if (!ScreenCapturer::getWatchScreenShot() && ScreenCapturer::isScreenShot())
        {
            Engine::draw(ScreenCapturer::getRenderTexture());
            ScreenCapturer::saveTexture();
        }
        Window::display();
    }
    terminate();
}

void Engine::getInput()
{
    InputManager::resetInput();
    if (Window::hasFocus())
    {
        InputManager::getInput();
        textBoxProb.getInput();
        ScreenCapturer::getInput();
    }
}

void Engine::update()
{
    Window::manageEvent();
    InputManager::update();
    textBoxProb.update();
    ScreenCapturer::update();
    ++frameCount;
    if (InputManager::getQEntered())
    {
        Window::close();
    }
    if (firstIter)
    {
        firstIter = false;
    }
}

void Engine::draw(sf::RenderTarget& renderTarget)
{
    renderTarget.clear(sf::Color(0, 0, 0, 255));
    sf::RenderStates statesBack = sf::RenderStates::Default;
    statesBack.texture = textureBack;
    renderTarget.draw(verticesBack.data(), 4, sf::PrimitiveType::TriangleStrip, statesBack);
    renderTarget.draw(textBoxProb, sf::RenderStates::Default);
    ScreenCapturer::draw(renderTarget);
}
