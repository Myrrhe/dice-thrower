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

#include "LogManager.hpp"
#include "PathManager.hpp"
#include "OsManager.hpp"
#include <fstream>
#include <iostream>
#include <istream>

const std::string LogManager::LogName = "log";
const std::string LogManager::LogExtension = ".txt";

void LogManager::clean()
{
    std::ofstream logFile((PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + LogName + LogExtension).c_str(), std::ios_base::out | std::ios_base::trunc);
    logFile.close();
}

void LogManager::append(const std::string& s)
{
    std::ofstream logFile((PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + LogName + LogExtension).c_str(), std::ios_base::out | std::ios_base::app);
    logFile << s;
#if PERF
    std::cout << s;
#endif // PERF
    logFile.close();
}
