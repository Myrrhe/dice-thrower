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

#include "OsManager.hpp"
#include <istream>
#include <iostream>
#ifdef __linux__
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#elif _WIN32
#include <direct.h>
#include <Windows.h>
#include <winnt.h>
#elif _OSX

#endif // __linux__

#ifdef __linux__
const char OsManager::SlashC = '/';
const std::string OsManager::StrIcon = "iconl64.png";
const unsigned int OsManager::WidthIcon = 64;
const unsigned int OsManager::HeightIcon = 64;
#elif _WIN32
const char OsManager::SlashC = '\\';
const std::string OsManager::StrIcon = "iconw128.png";
const unsigned int OsManager::WidthIcon = 128;
const unsigned int OsManager::HeightIcon = 128;
#elif _OSX

#endif // __linux__

const std::string OsManager::Slash = std::string(1, OsManager::SlashC);

sf::Vector2<unsigned int> OsManager::getMonitorSize()
{
#ifdef __linux__
    Display* disp = XOpenDisplay(nullptr);
    Screen*  scrn = DefaultScreenOfDisplay(disp);
    return sf::Vector2<unsigned int>(static_cast<unsigned int>(scrn->width,  static_cast<unsigned int>(scrn->height)));
#elif _WIN32
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return sf::Vector2<unsigned int>(static_cast<unsigned int>(desktop.bottom), static_cast<unsigned int>(desktop.right));
#elif _OSX

#endif // __linux__
}

double OsManager::getWallTime()
{
#ifdef __linux__
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return static_cast<double>(time.tv_sec) + static_cast<double>(time.tv_nsec) * 0.000000001;
#elif _WIN32
    LARGE_INTEGER time, freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time))
    {
        //  Handle error
        return 0;
    }
    return static_cast<double>(time.QuadPart)/static_cast<double>(freq.QuadPart);
#elif _OSX

#endif // __linux__
}

double OsManager::getCpuTime()
{
#ifdef __linux__
    return static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
#elif _WIN32
    FILETIME a;
    FILETIME b;
    FILETIME c;
    FILETIME d;
    if (GetProcessTimes(GetCurrentProcess(),&a,&b,&c,&d) != 0)
    {
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return static_cast<double>(d.dwLowDateTime | (static_cast<uint64_t>(d.dwHighDateTime) << 32)) * 0.0000001;
    }
    else
    {
        //  Handle error
        return 0;
    }
#elif _OSX

#endif // __linux__
}

void OsManager::createDir(const std::string& str)
{
#ifdef __linux__
    mkdir(str.c_str(), 01777);
#elif _WIN32
    _mkdir(str.c_str());
#elif _OSX

#endif // __linux__
}

void OsManager::sleep(double nbUsec)
{
#ifdef __linux__
    usleep(static_cast<__useconds_t>(nbUsec));
#elif _WIN32
    HANDLE timer;
    LARGE_INTEGER ft;
    ft.QuadPart = -(10*static_cast<long int>(nbUsec)); // Convert to 100 nanosecond interval, negative value indicates relative time
    timer = CreateWaitableTimer(nullptr, TRUE, nullptr);
    SetWaitableTimer(timer, &ft, 0, nullptr, nullptr, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
#elif _OSX

#endif // __linux__
}

void OsManager::initiateCoreFile()
{
#ifdef __linux__
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
#elif _WIN32

#elif _OSX

#endif // __linux__
}
