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

#ifndef SCREENCAPTURER_HPP
#define SCREENCAPTURER_HPP
#include <SFML/Graphics.hpp>

class ScreenCapturer final
{
public:

ScreenCapturer() = delete;
ScreenCapturer(const ScreenCapturer& right) = delete;
ScreenCapturer(ScreenCapturer&& right) = delete;
ScreenCapturer& operator=(const ScreenCapturer& right) = delete;
ScreenCapturer& operator=(ScreenCapturer&& right) = delete;
~ScreenCapturer() = delete;

static void initialize();
static void saveTexture();
static void resetWatchScreenShot();
static void getInput();
static void update();
static void draw(sf::RenderTarget& renderTarget);
static bool isScreenShot();
static long unsigned int getWatchScreenShot();
static sf::RenderTexture& getRenderTexture();
static void terminate();

    static const long unsigned int DurationCoolDownScreenShot;
    static const long unsigned int DurationFlash;

    static const std::string ShotExtension;

protected:

private:
    static bool screenShotEntered;
    static long unsigned int watchScreenShot;
    static sf::RenderTexture* renderTexture;

    static sf::RenderStates renderStatesFlash;
    static std::array<sf::Vertex, 4> verticesFlash;
};

#endif // SCREENCAPTURER_HPP
