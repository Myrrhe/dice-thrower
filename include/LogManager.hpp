/*
 * This file manage the logs.
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

#ifndef LOGMANAGER_HPP
#define LOGMANAGER_HPP
#include <string>

class LogManager final
{
public:

    LogManager() = delete;
    LogManager(const LogManager& right) = delete;
    LogManager(LogManager&& right) = delete;
    LogManager& operator=(const LogManager& right) = delete;
    LogManager& operator=(LogManager&& right) = delete;
    ~LogManager() = delete;

    static void clean();
    static void append(const std::string& s);

    static const std::string LogName;
    static const std::string LogExtension;

protected:
private:

};

#endif // LOGMANAGER_HPP
