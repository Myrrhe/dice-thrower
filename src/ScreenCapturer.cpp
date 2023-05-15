/*
 * A class that can capture the window to a .png file.
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

#include "Global.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "ScreenCapturer.hpp"
#include "Window.hpp"
#include "func.hpp"
#include <sys/stat.h>
#include <unistd.h>

bool ScreenCapturer::screenShotEntered;
long unsigned int ScreenCapturer::watchScreenShot;
sf::RenderTexture* ScreenCapturer::renderTexture;
sf::RenderStates ScreenCapturer::renderStatesFlash;
std::array<sf::Vertex, 4> ScreenCapturer::verticesFlash;

const long unsigned int ScreenCapturer::DurationCoolDownScreenShot = 60;
const long unsigned int ScreenCapturer::DurationFlash = 15;

const std::string ScreenCapturer::ShotExtension = ".png";

void ScreenCapturer::initialize()
{
    renderTexture = new sf::RenderTexture;
    renderTexture->create(static_cast<unsigned int>(Window::Width), static_cast<unsigned int>(Window::Height), sf::ContextSettings(0, 0, 0, 1, 1, sf::ContextSettings::Attribute::Default, false));
    if (access(PathManager::getPath(PathManager::Dir::SCREENSHOT).c_str(), 0))
    {
        std::cout << "Error: " + PathManager::getPath(PathManager::Dir::SCREENSHOT) + " missing. Therefore, the directory was recreated" << std::endl;
        OsManager::createDir(PathManager::getPath(PathManager::Dir::SCREENSHOT).c_str());
    }
    resetWatchScreenShot();
    renderStatesFlash.transform = sf::Transform::Identity;
    renderStatesFlash.texture = nullptr;
    renderStatesFlash.shader = nullptr;
    renderStatesFlash.blendMode = sf::BlendMode(sf::BlendMode::Factor::SrcAlpha, sf::BlendMode::Factor::One, sf::BlendMode::Equation::Add,
                                  sf::BlendMode::Factor::One, sf::BlendMode::Factor::One, sf::BlendMode::Equation::Add);
    for (long unsigned int i = 0; i < 4; i++)
    {
        verticesFlash[i].color = sf::Color(255, 255, 255, 0);
    }
    verticesFlash[0].position = sf::Vector2<float>(0.0f, 0.0f);
    verticesFlash[1].position = sf::Vector2<float>(static_cast<float>(Window::Width), 0.0f);
    verticesFlash[2].position = sf::Vector2<float>(0.0f, static_cast<float>(Window::Height));
    verticesFlash[3].position = sf::Vector2<float>(static_cast<float>(Window::Width), static_cast<float>(Window::Height));
}

void ScreenCapturer::saveTexture()
{
    long unsigned int n = 0;
    while (fileExist(PathManager::getPath(PathManager::Dir::SCREENSHOT) + OsManager::Slash + std::to_string(n) + ShotExtension))
    {
        n++;
    }
    renderTexture->display();
    renderTexture->getTexture().copyToImage().saveToFile(PathManager::getPath(PathManager::Dir::SCREENSHOT) + OsManager::Slash + std::to_string(n) + ShotExtension);
    watchScreenShot = DurationCoolDownScreenShot;
}

void ScreenCapturer::resetWatchScreenShot()
{
    watchScreenShot = 0;
}

void ScreenCapturer::getInput()
{
    screenShotEntered = false;
    if (Window::hasFocus())
    {
        screenShotEntered = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C);
    }
}

void ScreenCapturer::update()
{
    for (long unsigned int i = 0; i < 4; i++)
    {
        verticesFlash[i].color.a = static_cast<unsigned char>(255.0*static_cast<double>(watchScreenShot - (DurationCoolDownScreenShot - DurationFlash))/static_cast<double>(DurationFlash));
    }
    if (watchScreenShot)
    {
        watchScreenShot--;
    }
}

void ScreenCapturer::draw(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(verticesFlash.data(), 4, sf::PrimitiveType::TriangleStrip, renderStatesFlash);
}

bool ScreenCapturer::isScreenShot()
{
    return screenShotEntered;
}

long unsigned int ScreenCapturer::getWatchScreenShot()
{
    return watchScreenShot;
}

sf::RenderTexture& ScreenCapturer::getRenderTexture()
{
    return *renderTexture;
}

void ScreenCapturer::terminate()
{
    delete renderTexture;
}
