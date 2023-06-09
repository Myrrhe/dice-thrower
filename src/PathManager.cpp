/*
 * This file manager the path needed to find the assets of the application.
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
#include "func.hpp"
#include <fstream>

std::string PathManager::path;
std::string PathManager::pathVar;
std::string PathManager::exeName;

const std::string PathManager::PathName = "chrono";
const std::string PathManager::PathExtension = ".ini";

const std::string PathManager::FolderDat = "dat";
const std::string PathManager::FolderImg = "img";
const std::string PathManager::FolderSound = "sound";
const std::string PathManager::FolderFont = "font";
const std::string PathManager::FolderScreenshot = "screenshot";

const std::string PathManager::KeyPath = "path";

std::string PathManager::getPath(Dir dir)
{
    std::string addPath = "";
    switch (dir)
    {
    case Dir::ROOT:
    {
        addPath = "";
        break;
    }
    case Dir::DAT:
    {
        addPath = FolderDat;
        break;
    }
    case Dir::IMG:
    {
        addPath = FolderDat + OsManager::Slash + FolderImg;
        break;
    }
    case Dir::SOUND:
    {
        addPath = FolderDat + OsManager::Slash + FolderSound;
        break;
    }
    case Dir::FONT:
    {
        addPath = FolderDat + OsManager::Slash + FolderFont;
        break;
    }
    case Dir::SCREENSHOT:
    {
        addPath = FolderDat + OsManager::Slash + FolderScreenshot;
        break;
    }
    default:
    {
        addPath = "";
        break;
    }
    }
    return pathVar + path + addPath;
}

void PathManager::setPath(const std::string& argv0)
{
    path = argv0;
    exeName = argv0;
    while (path.back() != OsManager::SlashC && path != "")
    {
        path = path.substr(0, path.size() - 1);
    }
    while (exeName.find(OsManager::SlashC, 0) != std::string::npos && path != "")
    {
        exeName = exeName.substr(1, exeName.size() - 1);
    }
    while (exeName.find('.', 0) != std::string::npos && path != "")
    {
        exeName = exeName.substr(0, exeName.size() - 1);
    }
}

void PathManager::rewrite()
{
    std::ofstream pathFile((path + exeName + PathExtension).c_str(), std::ios::out | std::ios::trunc);
    pathFile << "[path]" << "\n";
    pathFile << KeyPath << "=" << "" << "\n";
    pathFile.close();
}

void PathManager::read()
{
    std::string currentLine = "";
    std::string currentKeyWord = "";
    std::ifstream pathFile((path + exeName + PathExtension).c_str());
    bool keyFound = false;
    while (pathFile)
    {
        std::getline(pathFile, currentLine);
        currentKeyWord = getKeyWordLine(currentLine);
        if (currentKeyWord == KeyPath)
        {
            keyFound = true;
            pathVar = currentLine.substr(currentKeyWord.size() + 1, std::string::npos);
        }
    }
    pathFile.close();
    if (!keyFound)
    {
        std::cout << "Error: " + path + exeName + PathExtension + " exist, but the line \'path=[something]\' was not found. The deletion of the file so it can be rewritten is suggested." << std::endl;
    }
}

void PathManager::initialize()
{
    if (!fileExist(path + exeName + PathExtension))
    {
        std::cout << "Error: " + path + exeName + PathExtension + " missing. Therefore, the file has been rewritten from scratch." << std::endl;
        rewrite();
    }
    read();
}
