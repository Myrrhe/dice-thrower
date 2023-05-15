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

#include "../include/RandManager.hpp"
#include "../include/OsManager.hpp"
#include <istream> // Added by Header fixup
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <array>

//std::array<std::mt19937n 3ul> RandManager::mt;

std::array<std::mersenne_twister_engine<uint_fast32_t,
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
                                        1812433253>, RandManager::nbGen> RandManager::mt;

uint_fast32_t RandManager::mainSeed;
//std::seed_seq* RandManager::seedSeq;
long unsigned int RandManager::counter;
long unsigned int RandManager::idLog;
long unsigned int RandManager::watch;

void RandManager::initialize()
{
    mt[1].seed(static_cast<uint_fast32_t>(time(nullptr)));
    mt[2].seed(static_cast<uint_fast32_t>(time(nullptr)));
}

void RandManager::setMain(bool giveNewSeed, uint_fast32_t newMainSeed) //Set mainSeed
{
    //delete seedSeq;
    if (giveNewSeed)
    {
        mainSeed = newMainSeed;
        //seedSeq = new std::seed_seq({newMainSeed});
    }
    else
    {
        //mainSeed = static_cast<int>(time(nullptr));
        mainSeed = static_cast<uint_fast32_t>(time(nullptr));
        //seedSeq = new std::seed_seq({static_cast<unsigned int>(time(nullptr))});
    }
    #if DEBUG
        std::cout << "mainSeed = " << mainSeed << std::endl;
    #endif // DEBUG
    counter = 0;
    //std::srand(mainSeed);
    mt[0].seed(mainSeed);
    //mt[0].seed(*seedSeq);

    idLog = 0;

    #if DEBUG_RAND && DEBUG
        bool fileExist;
        do
        {
            std::ifstream logFile(OsManager::getPath() + "/log/" + static_cast<std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >&>((std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >() << std::dec << idLog)).str() + ".txt");
            if (logFile)
            {
                logFile.close();
                fileExist = true;
                idLog++;
            }
            else
            {
                fileExist = false;
                logFile.close();
                std::ofstream newLogFile(OsManager::getPath() + "/log/" + static_cast<std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >&>((std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >() << std::dec << idLog)).str() + ".txt");
                newLogFile.close();
            }
        }
        while (fileExist);
    #endif // DEBUG_RAND && DEBUG

}

uint_fast32_t RandManager::getMainSeed() //Get mainSeed
{
    return mainSeed;
    /*
    std::vector<uint_fast32_t> v;
    seedSeq->param(std::insert_iterator<std::vector<uint_fast32_t> >(v, v.begin()));
    return v[0];
    */
}

long unsigned int RandManager::mainRand(const std::string&
                                    #if DEBUG_RAND && DEBUG
                                        str1
                                    #endif // DEBUG_RAND && DEBUG
                                    , const std::string&
                                    #if DEBUG_RAND && DEBUG
                                        str2
                                    #endif // DEBUG_RAND && DEBUG
                                    , int
                                    #if DEBUG_RAND && DEBUG
                                        int1
                                    #endif // DEBUG_RAND && DEBUG
                                    ) //Get a random number from mt
{
    uint_fast32_t newRand = mt[0]();
    //std::cout << "FILE = " << str1 << " : LINE = " << int1 << " : newRand : " << counter << " = " << newRand << std::endl;


    #if DEBUG_RAND && DEBUG
        counter++;
        std::ofstream logFile;
        logFile.open(OsManager::getPath() + "/log/" + static_cast<std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >&>((std::basic_ostringstream<char, std::char_traits<char>, std::allocator<char> >() << std::dec << idLog)).str() + ".txt", std::ios::app);
        logFile << "FILE = " << str1 << " : FUNCTION = " << str2 << " : LINE = " << int1 << " : Counter = " << counter << /*" : Watch = " << Stage1::getWatch() << */" : Rand = " << newRand << std::endl;
        logFile.close();
    #endif // DEBUG_RAND && DEBUG



    return newRand;
    //return std::rand();
    //return mt[0]();
}

long unsigned int RandManager::mainRand() //Get a random number from mt
{
    return mt[0]();
}

long unsigned int RandManager::getMainMax() //The max of mt
{
    return mt[0].max();
}

long unsigned int RandManager::secoRand()
{
    return mt[1]();
}

long unsigned int RandManager::loadRand()
{
    return mt[2]();
}

long unsigned int RandManager::genRand(IdRand idRand)
{
    switch (idRand)
    {
        case IdRand::MAIN:
        {
            return mt[0]();
            break;
        }
        case IdRand::SECO:
        {
            return mt[1]();
            break;
        }
        case IdRand::LOAD:
        {
            return mt[2]();
            break;
        }
        default:
        {
            return 0;
            break;
        }
    }
}

void RandManager::update()
{
    watch++;
}

void RandManager::reset()
{
    watch = 0ul;
}
