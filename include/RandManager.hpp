/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#ifndef RANDMANAGER_HPP
#define RANDMANAGER_HPP
#include <array>
#include <random>

#define DEBUG_RAND false

#if DEBUG && DEBUG_RAND
    #define RAND_CALL mainRand(__FILE__,__FUNCTION__,__LINE__)
#else
    #define RAND_CALL mainRand()
#endif // DEBUG && DEBUG_RAND

class RandManager final
{
public:

    enum class IdRand : unsigned int
    {
        MAIN,
        SECO,
        LOAD
    };

RandManager() = delete;
RandManager(const RandManager& right) = delete;
RandManager(RandManager&& right) = delete;
RandManager& operator=(const RandManager& right) = delete;
RandManager& operator=(RandManager&& right) = delete;
~RandManager() = delete;

static void initialize();
static void setMain(bool giveNewSeed, uint_fast32_t newMainSeed = 0); //Set mainSeed
static uint_fast32_t getMainSeed(); //Get mainSeed
static long unsigned int mainRand(const std::string& str2, const std::string& str1, int int1);
//Get a random number from mt
static long unsigned int mainRand(); //Get a random number from mt
static long unsigned int getMainMax();
//Get the max number from mt
static long unsigned int secoRand();
static long unsigned int loadRand();
static long unsigned int genRand(IdRand idRand);
static void update();
static void reset();

protected:

private:
    static constexpr long unsigned int nbGen = 3;

    //static std::array<std::mt19937, 3ul> mt;

    static std::array<std::mersenne_twister_engine<uint_fast32_t,
                                                   32,
                                                   624,
                                                   397,
                                                   31,
                                                   0x9908b0df,
                                                   11,
                                                   0xffffffff,
                                                   7,
                                                   0x9d2c5680,
                                                   15,
                                                   0xefc60000,
                                                   18,
                                                   1812433253>, nbGen> mt;

    static uint_fast32_t mainSeed; //The seed of mt
    //static std::seed_seq* seedSeq;
    static long unsigned int counter;
    static long unsigned int idLog;
    static long unsigned int watch;
};

#endif // RANDMANAGER_HPP
