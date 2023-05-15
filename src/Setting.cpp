/*
 * The settings manager.
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

#include "OsManager.hpp"
#include "PathManager.hpp"
#include "Setting.hpp"
#include "func.hpp"
#include <fstream>

const std::string Setting::SettingName = "setting";
const std::string Setting::SettingExtension = ".ini";

void Setting::read()
{
    std::string currentLine = "";
    std::string currentKeyWord = "";
    std::ifstream settingFile((PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + SettingName + SettingExtension).c_str());
    while (settingFile)
    {
        std::getline(settingFile, currentLine);
        currentKeyWord = getKeyWordLine(currentLine);
    }
    settingFile.close();
}

void Setting::rewrite()
{
    std::ofstream settingFile((PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + SettingName + SettingExtension).c_str(), std::ios::out | std::ios::trunc);
    settingFile << "[setting]" << "\n";
    settingFile.close();
}

void Setting::initialize()
{
    if (!fileExist(PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + SettingName + SettingExtension))
    {
        rewrite();
        std::cout << "Error: " + PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + SettingName + SettingExtension + " missing. Therefore, the file has been rewritten from scratch." << std::endl;
    }
    read();
}

void Setting::write()
{
    std::ofstream settingFile((PathManager::getPath(PathManager::Dir::DAT) + OsManager::Slash + SettingName + SettingExtension).c_str(), std::ios::out | std::ios::trunc);
    settingFile << "[setting]" << "\n";
    settingFile.close();
}
