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

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "RoundedRectangleShape.hpp"
#include "Text.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>

class Engine final
{
public:

    Engine() = delete;
    Engine(const Engine& right) = delete;
    Engine(Engine&& right) = delete;
    Engine& operator=(const Engine& right) = delete;
    Engine& operator=(Engine&& right) = delete;
    ~Engine() = delete;

    static void launch();

protected:
private:
    static void initialize();
    static void terminate();

    static void getInput();
    static void update();
    static void draw(sf::RenderTarget& renderTarget);

    static sf::Font* font;

    static sf::Texture* textureBack;
    static sf::Texture* textureTextBox;
    static sf::Texture* textureCursor;

    static std::array<sf::Vertex, 4> verticesBack;
    static TextBox textBoxProb;

    static bool firstIter;
    static long unsigned int frameCount;
};

#endif // ENGINE_HPP
