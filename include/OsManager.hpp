/*
 * This file manage the differences between several OS.
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

#ifndef OSMANAGER_HPP
#define OSMANAGER_HPP
#include <string>
#include <SFML/Graphics.hpp>

#ifdef __linux__
#define __GNU__CONST__ [[gnu::const]]
#define __GNU__PURE__ [[gnu::pure]]
#elif _WIN32
#define __GNU__CONST__
#define __GNU__PURE__
#elif _OSX

#endif // __linux__

class OsManager final
{
public:

    OsManager() = delete;
    OsManager(const OsManager& right) = delete;
    OsManager(OsManager&& right) = delete;
    OsManager& operator=(const OsManager& right) = delete;
    OsManager& operator=(OsManager&& right) = delete;
    ~OsManager() = delete;

    static sf::Vector2<unsigned int> getMonitorSize();

    static double getWallTime();
    static double getCpuTime();
    static void createDir(const std::string& str);
    static void sleep(double nbUsec);
    static void initiateCoreFile();

    static const char SlashC;
    static const std::string Slash;

    static const std::string StrIcon;
    static const unsigned int WidthIcon;
    static const unsigned int HeightIcon;

protected:
private:
};

#endif // OSMANAGER_HPP
