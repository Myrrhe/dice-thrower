/*
 * The sound manager.
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

#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP
#include <SFML/Audio.hpp>

class SoundManager final
{
public:

    SoundManager() = delete;
    SoundManager(const SoundManager& right) = delete;
    SoundManager(SoundManager&& right) = delete;
    SoundManager& operator=(const SoundManager& right) = delete;
    SoundManager& operator=(SoundManager&& right) = delete;
    ~SoundManager() = delete;

    static void initialize();
    static void terminate();

protected:

private:
};

#endif // SOUNDMANAGER_HPP
