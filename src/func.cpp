/*
 * A basic function library.
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

#include "func.hpp"
#include <cmath>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <chrono>

std::ostream& operator<<(std::ostream& os, const sf::Color& right)
{
    return os << "(" << static_cast<int>(right.r) << ", " << static_cast<int>(right.g) << ", " << static_cast<int>(right.b) << ", " << static_cast<int>(right.a) << ")";
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2<int>& right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2<float>& right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2<double>& right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Rect<int>& right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width << ", " << right.height << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Rect<float>& right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width << ", " << right.height << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Rect<double>& right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width << ", " << right.height << ')';
}

std::ostream& operator<<(std::ostream& os, const sf::Transform& right)
{
    const float* matrix = right.getMatrix();
    return os << "(" << matrix[0] << " " << matrix[4] << " " << matrix[8]  << " " << matrix[12] << ")" << '\n'
              << "(" << matrix[1] << " " << matrix[5] << " " << matrix[9]  << " " << matrix[13] << ")" << '\n'
              << "(" << matrix[2] << " " << matrix[6] << " " << matrix[10] << " " << matrix[14] << ")" << '\n'
              << "(" << matrix[3] << " " << matrix[7] << " " << matrix[11] << " " << matrix[15] << ")";
}

std::ostream& operator<<(std::ostream& os, const sf::Time& right)
{
    return os << right.asSeconds();
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& right)
{
    std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; i++)
    {
        os << '\"' << right[i] << '\"';
        if (i != sizeV - 1)
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<long unsigned int>& right)
{
    std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; i++)
    {
        os << right[i];
        if (i != sizeV - 1)
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<double>& right)
{
    std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; i++)
    {
        os << right[i];
        if (i != sizeV - 1)
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

sf::Rect<int> operator|(const sf::Rect<int>& left, const sf::Rect<int>& right)
{
    sf::Vector2<int> leftTopCorner = sf::Vector2<int>(std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<int>(leftTopCorner.x,
                         leftTopCorner.y,
                         std::max(left.left + left.width, right.left + right.width) - leftTopCorner.x,
                         std::max(left.top + left.height, right.top + right.height) - leftTopCorner.y);
}

sf::Rect<float> operator|(const sf::Rect<float>& left, const sf::Rect<float>& right)
{
    sf::Vector2<float> leftTopCorner = sf::Vector2<float>(std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<float>(leftTopCorner.x,
                           leftTopCorner.y,
                           std::max(left.left + left.width, right.left + right.width) - leftTopCorner.x,
                           std::max(left.top + left.height, right.top + right.height) - leftTopCorner.y);
}

sf::Rect<double> operator|(const sf::Rect<double>& left, const sf::Rect<double>& right)
{
    sf::Vector2<double> leftTopCorner = sf::Vector2<double>(std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<double>(leftTopCorner.x,
                            leftTopCorner.y,
                            std::max(left.left + left.width, right.left + right.width) - leftTopCorner.x,
                            std::max(left.top + left.height, right.top + right.height) - leftTopCorner.y);
}

sf::Rect<int> operator+(const sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return sf::Rect<int>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<float> operator+(const sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return sf::Rect<float>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<double> operator+(const sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return sf::Rect<double>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<int>& operator+=(sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return left = sf::Rect<int>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<float>& operator+=(sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return left = sf::Rect<float>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<double>& operator+=(sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return left = sf::Rect<double>(left.left + right.x, left.top + right.y, left.width, left.height);
}

sf::Rect<int> operator-(const sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return sf::Rect<int>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<float> operator-(const sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return sf::Rect<float>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<double> operator-(const sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return sf::Rect<double>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<int>& operator-=(sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return left = sf::Rect<int>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<float>& operator-=(sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return left = sf::Rect<float>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<double>& operator-=(sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return left = sf::Rect<double>(left.left - right.x, left.top - right.y, left.width, left.height);
}

sf::Rect<int> operator*(const sf::Rect<int>& left, int right)
{
    return sf::Rect<int>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<float> operator*(const sf::Rect<float>& left, float right)
{
    return sf::Rect<float>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<double> operator*(const sf::Rect<double>& left, double right)
{
    return sf::Rect<double>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<int>& operator*=(sf::Rect<int>& left, int right)
{
    return left = sf::Rect<int>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<float>& operator*=(sf::Rect<float>& left, float right)
{
    return left = sf::Rect<float>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<double>& operator*=(sf::Rect<double>& left, double right)
{
    return left = sf::Rect<double>(left.left, left.top, left.width*right, left.height*right);
}

sf::Rect<int> operator/(const sf::Rect<int>& left, int right)
{
    return sf::Rect<int>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<float> operator/(const sf::Rect<float>& left, float right)
{
    return sf::Rect<float>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<double> operator/(const sf::Rect<double>& left, double right)
{
    return sf::Rect<double>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<int>& operator/=(sf::Rect<int>& left, int right)
{
    return left = sf::Rect<int>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<float>& operator/=(sf::Rect<float>& left, float right)
{
    return left = sf::Rect<float>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<double>& operator/=(sf::Rect<double>& left, double right)
{
    return left = sf::Rect<double>(left.left, left.top, left.width/right, left.height/right);
}

sf::Rect<int> operator*(const sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return sf::Rect<int>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<float> operator*(const sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return sf::Rect<float>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<double> operator*(const sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return sf::Rect<double>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<int>& operator*=(sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return left = sf::Rect<int>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<float>& operator*=(sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return left = sf::Rect<float>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<double>& operator*=(sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return left = sf::Rect<double>(left.left, left.top, left.width*right.x, left.height*right.y);
}

sf::Rect<int> operator/(const sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return sf::Rect<int>(left.left, left.top, left.width/right.x, left.height/right.y);
}

sf::Rect<float> operator/(const sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return sf::Rect<float>(left.left, left.top, left.width/right.x, left.height/right.y);
}

sf::Rect<double> operator/(const sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return sf::Rect<double>(left.left, left.top, left.width/right.x, left.height/right.y);
}

sf::Rect<int>& operator/=(sf::Rect<int>& left, const sf::Vector2<int>& right)
{
    return left = sf::Rect<int>(left.left, left.top, left.width/right.x, left.height/right.y);
}

sf::Rect<float>& operator/=(sf::Rect<float>& left, const sf::Vector2<float>& right)
{
    return left = sf::Rect<float>(left.left, left.top, left.width/right.x, left.height/right.y);
}

sf::Rect<double>& operator/=(sf::Rect<double>& left, const sf::Vector2<double>& right)
{
    return left = sf::Rect<double>(left.left, left.top, left.width/right.x, left.height/right.y);
}

int operator*(const sf::Vector2<int>& left, const sf::Vector2<int>& right)
{
    return left.x*right.x + left.y*right.y;
}

unsigned int operator*(const sf::Vector2<unsigned int>& left, const sf::Vector2<unsigned int>& right)
{
    return left.x*right.x + left.y*right.y;
}

float operator*(const sf::Vector2<float>& left, const sf::Vector2<float>& right)
{
    return left.x*right.x + left.y*right.y;
}

double operator*(const sf::Vector2<double>& left, const sf::Vector2<double>& right)
{
    return left.x*right.x + left.y*right.y;
}

int operator^(const sf::Vector2<int>& left, const sf::Vector2<int>& right)
{
    return left.x*right.y - left.y*right.x;
}

float operator^(const sf::Vector2<float>& left, const sf::Vector2<float>& right)
{
    return left.x*right.y - left.y*right.x;
}

double operator^(const sf::Vector2<double>& left, const sf::Vector2<double>& right)
{
    return left.x*right.y - left.y*right.x;
}

sf::Vector2<float> floor(const sf::Vector2<float>& v)
{
    return sf::Vector2<float>(std::floor(v.x), std::floor(v.y));
}

float getNorm(const sf::Vector2<float>& v)
{
    return std::sqrt(v.x*v.x + v.y*v.y);
}

double getNorm(const sf::Vector2<double>& v)
{
    return std::sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2<int> getInverted(const sf::Vector2<int>& v)
{
    return sf::Vector2<int>(-v.x, -v.y);
}

sf::Vector2<unsigned int> getInverted(const sf::Vector2<unsigned int>& v)
{
    return sf::Vector2<unsigned int>(-v.x, -v.y);
}

sf::Vector2<float> getInverted(const sf::Vector2<float>& v)
{
    return sf::Vector2<float>(-v.x, -v.y);
}

sf::Vector2<double> getInverted(const sf::Vector2<double>& v)
{
    return sf::Vector2<double>(-v.x, -v.y);
}

sf::Vector2<float> getNormalized(const sf::Vector2<float>& v)
{
    float norm = getNorm(v);
    return sf::Vector2<float>(v.x/norm, v.y/norm);
}

sf::Vector2<double> getNormalized(const sf::Vector2<double>& v)
{
    double norm = getNorm(v);
    return sf::Vector2<double>(v.x/norm, v.y/norm);
}

float radToDeg(float radians)
{
    return radians*180.0f/m_pi_f;
}

double radToDeg(double radians)
{
    return radians*180.0/m_pi;
}

float degToRad(float degree)
{
    return degree*m_pi_f/180.0f;
}

double degToRad(double degree)
{
    return degree*m_pi/180.0;
}

float getRotationAngle(const sf::Vector2<float>& v)
{
    sf::Vector2<float> normalizedVec = getNormalized(v);
    float angleXRad = std::acos(normalizedVec.x);
    float angleYRad = std::asin(normalizedVec.y);
    float angleRad;
    if (angleYRad < 0)
    {
        angleRad = m_2pi_f - angleXRad;
    }
    else
    {
        angleRad = angleXRad;
    }
    return angleRad; // Angle in radians
}

double getRotationAngle(const sf::Vector2<double>& v)
{
    sf::Vector2<double> normalizedVec = getNormalized(v);
    double angleXRad = std::acos(normalizedVec.x);
    double angleYRad = std::asin(normalizedVec.y);
    double angleRad;
    if (angleYRad < 0)
    {
        angleRad = m_2pi - angleXRad;
    }
    else
    {
        angleRad = angleXRad;
    }
    return angleRad; // Angle in radians
}

float getAngleBetween(const sf::Vector2<float>& v1, const sf::Vector2<float>& v2)
{
    float angle = std::acos((v1*v2)/(getNorm(v1)*getNorm(v2)));
    return angle; // Angle in radians
}

double getAngleBetween(const sf::Vector2<double>& v1, const sf::Vector2<double>& v2)
{
    double angle = std::acos((v1*v2)/(getNorm(v1)*getNorm(v2)));
    return angle; // Angle in radians
}

sf::Vector2<float> getRotated(const sf::Vector2<float>& vec, float angle)
{
    return sf::Vector2<float>(vec.x*std::cos(angle) + vec.y*std::sin(angle), -vec.x*std::sin(angle) + vec.y*std::cos(angle));
}

sf::Vector2<double> getRotated(const sf::Vector2<double>& vec, double angle)
{
    return sf::Vector2<double>(vec.x*std::cos(angle) + vec.y*std::sin(angle), -vec.x*std::sin(angle) + vec.y*std::cos(angle));
}

double getCoeff(double coeff, Interp interp, bool limiter)
{
    if (limiter && coeff >= 1.0)
    {
        return 1.0;
    }
    if (limiter && coeff <= 0.0)
    {
        return 0.0;
    }
    switch (interp)
    {
        case Interp::LIN:
        {
            return coeff;
            break;
        }
        case Interp::ACC:
        {
            return coeff*coeff;
            break;
        }
        case Interp::BRA:
        {
            return (2.0 - coeff)*coeff;
            break;
        }
        case Interp::SIN:
        {
            return (std::sin((coeff - 0.5)*m_pi) + 1.0)*0.5;
            break;
        }
        case Interp::SFO:
        {
            return 1.0/(1.0 + std::exp(-(2.0*coeff - 1.0)/(coeff*(1.0 - coeff))));
            break;
        }
        case Interp::SIN0:
        {
            return (std::sin((coeff - 0.25)*m_2pi) + 1.0)*0.5;
            break;
        }
        default:
        {
            return 0.0;
            break;
        }
    }
}

double getCoeff(double x, double X, Interp interp, bool limiter)
{
    return getCoeff(x/X, interp, limiter);
}

sf::Color colorBalance(const sf::Color& color1, const sf::Color& color2, double coeff, Interp interp)
{
    double interpCoeff = getCoeff(coeff, interp);
    double oneMinusCoeff = 1.0 - interpCoeff;
    return sf::Color(static_cast<sf::Uint8>(color1.r*interpCoeff + color2.r*oneMinusCoeff),
                     static_cast<sf::Uint8>(color1.g*interpCoeff + color2.g*oneMinusCoeff),
                     static_cast<sf::Uint8>(color1.b*interpCoeff + color2.b*oneMinusCoeff),
                     static_cast<sf::Uint8>(color1.a*interpCoeff + color2.a*oneMinusCoeff));
}

std::string getStringHourPrecise()
{
    std::time_t tt = std::time(nullptr);
    std::string format(8, 0);
    std::strftime(&format[0], 32, "%H:%M:%S", std::localtime(&tt));
    return format;
}

std::string getStringHourVeryPrecise()
{
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    std::string format(12, 0);
    std::chrono::duration<long long int, std::ratio<1, 1000000000> >::rep millis = currentTime.time_since_epoch().count()/1000000 % 1000;
    std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);
    strftime(&format[0], 12 ,"%H:%M:%S", std::localtime(&tt));
    sprintf(&format[0], "%s:%03d", &format[0], static_cast<int>(millis));
    return format;
}

std::array<long unsigned int, 4> getHourVeryPrecise()
{
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    std::chrono::duration<long long int, std::ratio<1, 1000000000> >::rep millis = currentTime.time_since_epoch().count()/1000000 % 1000;
    std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);
    std::tm datetime = *std::localtime(&tt);
    return {{static_cast<long unsigned int>(datetime.tm_hour),
             static_cast<long unsigned int>(datetime.tm_min),
             static_cast<long unsigned int>(datetime.tm_sec),
             static_cast<long unsigned int>(millis)}};
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> res;
    std::back_insert_iterator<std::vector<std::string> > result = std::back_inserter(res);
    std::stringstream ss(s, std::ios_base::in | std::ios_base::out);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

const std::vector<std::string>& split(const std::string& s, const std::string& delim)
{
    static std::vector<std::string> res;
    res.clear();
    std::size_t pos_start = 0;
    std::size_t pos_end;
    std::size_t delim_len = delim.length();
    while ((pos_end = s.find(delim, pos_start)) != std::string::npos)
    {
        res.emplace_back(s.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + delim_len;
    }
    res.emplace_back(s.substr(pos_start, std::string::npos));
    return res;
}

std::vector<std::u32string> split(const std::u32string& s, char32_t delim)
{
    std::vector<std::u32string> res;
    std::back_insert_iterator<std::vector<std::u32string> > result = std::back_inserter(res);
    std::basic_stringstream<char32_t, std::char_traits<char32_t> > ss(s, std::ios_base::in | std::ios_base::out);
    std::u32string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

const std::vector<std::u32string>& split(const std::u32string& s, const std::u32string& delim)
{
    static std::vector<std::u32string> res;
    res.clear();
    std::size_t pos_start = 0;
    std::size_t pos_end;
    std::size_t delim_len = delim.length();
    while ((pos_end = s.find(delim, pos_start)) != std::string::npos)
    {
        res.emplace_back(s.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + delim_len;
    }
    res.emplace_back(s.substr(pos_start, std::string::npos));
    return res;
}

long unsigned int imod(long int i1, long int i2)
{
    while (i1 < 0)
    {
        i1 += i2;
    }
    while (i1 >= i2)
    {
        i1 -= i2;
    }
    return static_cast<long unsigned int>(i1);
}

double dmod(double numer, double denom)
{
    while(numer >= denom)
    {
        numer -= denom;
    }
    while(numer < 0.0)
    {
        numer += denom;
    }
    return numer;
}

float f_mod(float numer, float denom)
{
    while(numer >= denom)
    {
        numer -= denom;
    }
    while(numer < 0.0f)
    {
        numer += denom;
    }
    return numer;
}

long unsigned int power(long unsigned int base, long unsigned int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    else
    {
        long unsigned int res = base;
        for (long unsigned int i = 1; i < exponent; i++)
        {
            res *= base;
        }
        return res;
    }
}

sf::String stringTosfString(const std::string& str)
{   //Can be useful to display accents properly
    std::basic_string<sf::Uint32> utf32str = {};
    sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(utf32str));
    return sf::String(utf32str);
}

sf::String evaluateSpecialChars(const sf::String& str)
{
    sf::String res = "";
    std::size_t i = 0;
    std::size_t sizeStr = str.getSize();
    while(i < sizeStr)
    {
        sf::Uint32 c = str[i];
        if (c == '\\')
        {
            i++;
            sf::Uint32 n = str[i];
            switch (n)
            {
                case '\\':
                {
                    res += n;
                    break;
                }
                case 'n':
                {
                    res += '\n';
                    break;
                }
                case 't':
                {
                    res += '\t';
                    break;
                }
                case '<':
                {
                    res += "\\<";
                    break;
                }
                case '>':
                {
                    res += "\\>";
                    break;
                }
                default:
                {
                    debugLog("default reached");
                    std::cerr << "Error: invalid special char found : " << c << n << std::endl;
                    break;
                }
            }
        }
        else
        {
            res += c;
        }
        i++;
    }
    return res;
}

std::vector<std::string> getDir(const std::string& dir)
{
    std::vector<std::string> res = {};
    DIR *dp;
    dirent *dirp;
    if ((dp = opendir(dir.c_str())) == nullptr)
    {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return {};
    }
    while ((dirp = readdir(dp)) != nullptr)
    {
        res.emplace_back(static_cast<std::string>(dirp->d_name));
    }
    closedir(dp);
    return res;
}

bool fileExist(const std::string& path)
{
    std::ifstream infile(path);
    return infile.good();
}

std::string getKeyWordLine(const std::string& line)
{
    long unsigned int posEq = line.find("=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return "";
    }
    else
    {
        return line.substr(0, posEq);
    }
}

std::string getValueLine(const std::string& line)
{
    long unsigned int posEq = line.find("=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return "";
    }
    else
    {
        return line.substr(posEq + 1, std::string::npos);
    }
}

std::pair<std::string, std::string> getKeyValueLine(const std::string& line)
{
    long unsigned int posEq = line.find("=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return {"", ""};
    }
    else
    {
        return {line.substr(0, posEq), line.substr(posEq + 1, std::string::npos)};
    }
}

std::u32string getKeyWordLine(const std::u32string& line)
{
    long unsigned int posEq = line.find(U"=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return U"";
    }
    else
    {
        return line.substr(0, posEq);
    }
}

std::u32string getValueLine(const std::u32string& line)
{
    long unsigned int posEq = line.find(U"=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return U"";
    }
    else
    {
        return line.substr(posEq + 1, std::string::npos);
    }
}

std::pair<std::u32string, std::u32string> getKeyValueLine(const std::u32string& line)
{
    long unsigned int posEq = line.find(U"=", 0);
    if (posEq == std::string::npos) //std::string::npos = -1;
    {
        return {U"", U""};
    }
    else
    {
        return {line.substr(0, posEq), line.substr(posEq + 1, std::string::npos)};
    }
}

bool isFloat(const std::string& s)
{
    std::basic_istringstream<char, std::char_traits<char>, std::allocator<char> > iss(s);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool isFloat(const std::u32string& s)
{
    std::basic_istringstream<char32_t, std::char_traits<char32_t>, std::allocator<char32_t> > iss(s);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool isPosInt(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool isPosInt(const std::u32string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

long unsigned int str32ToLui(const std::u32string& s)
{
    if (!isPosInt(s))
    {
        return 0;
    }
    long unsigned int res = 0;
    for (long unsigned int i = 0; i < s.size(); i++)
    {
        res += (s[i] - U'0')*power(10, s.size() - 1 - i);
    }
    return res;
}

long unsigned int str32HexToLui(const std::u32string& s)
{
    long unsigned int res = 0;
    for (long unsigned int i = 0; i < s.size(); i++)
    {
        long unsigned int val;
        if (s[i] >= U'0' && s[i] <= U'9')
        {
            val = s[i] - U'0';
        }
        else if (s[i] >= U'a' && s[i] <= U'f')
        {
            val = 10 + s[i] - U'a';
        }
        else if (s[i] >= U'A' && s[i] <= U'F')
        {
            val = 10 + s[i] - U'A';
        }
        else
        {
            return 0;
        }
        res += val*power(16, s.size() - 1 - i);
    }
    return res;
}

float str32ToF(const std::u32string& s)
{
    if (!isFloat(s))
    {
        return 0.0f;
    }
    long unsigned int posInit = s[0] == U'-';
    long unsigned int posPoint = s.find(U'.', 0);
    float res = 0.0f;
    for (long unsigned int i = posInit; i < s.size(); i++)
    {
        if (i != posPoint)
        {
            res += static_cast<float>(s[i] - U'0')*std::pow(10.0f, static_cast<float>(posPoint - 1 - i + (i > posPoint)));
        }
    }
    return res*(posInit == 0 ? 1.0f : -1.0f);
}

std::u32string luiTo32Str(long unsigned int n)
{
    std::u32string res = U"";
    do
    {
        res = std::u32string(1, (static_cast<char32_t>(n % 10) + U'0')) + res;
    } while (n / 10);
    return res;
}

std::u32string luiTo32StrHex(long unsigned int n)
{
    std::u32string res = U"";
    do
    {
        if (n % 16 <= 9)
        {
            res = std::u32string(1, (static_cast<char32_t>(n % 16) + U'0')) + res;
        }
        else
        {
            res = std::u32string(1, (static_cast<char32_t>(n % 16) + U'a')) + res;
        }
    } while (n / 16);
    return res;
}

std::u32string fTo32Str(float n)
{
    std::u32string res = U"";
    do
    {
        res = std::u32string(1, (static_cast<char32_t>(std::fmod(n, 10.0f)) + U'0')) + res;
    } while (n / 10.0f > 1.0f);
    return res;
}

sf::Rect<int> getTextureRect(const sf::Texture* texture)
{
    if (texture == nullptr)
    {
        return sf::Rect<int>(0, 0, 0, 0);
    }
    else
    {
        return sf::Rect<int>(0, 0, static_cast<int>(texture->getSize().x), static_cast<int>(texture->getSize().y));
    }
}

Quaternion getQuatRot(double angle, const sf::Vector3<double>& axe)
{
    double norm = std::sin(angle*0.5)/std::sqrt(axe.x*axe.x + axe.y*axe.y + axe.z*axe.z);
    return Quaternion(std::cos(angle*0.5), axe.x*norm, axe.y*norm, axe.z*norm);
}

Quaternion euler2Quaternion(const sf::Vector3<double>& angle, RotSeq rotSeq)
{
    double c1 = std::cos(angle.x*0.5);
    double c2 = std::cos(angle.y*0.5);
    double c3 = std::cos(angle.z*0.5);
    double s1 = std::sin(angle.x*0.5);
    double s2 = std::sin(angle.y*0.5);
    double s3 = std::sin(angle.z*0.5);
    switch(rotSeq)
    {
        case RotSeq::zyx:
        {
            return Quaternion(c1*c2*c3 + s1*s2*s3,
                              s1*c2*c3 - c1*s2*s3,
                              c1*s2*c3 + s1*c2*s3,
                              c1*c2*s3 - s1*s2*c3);
            break;
        }
        case RotSeq::zyz:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              s1*s2*c3 - c1*s2*s3,
                              c1*s2*c3 + s1*s2*s3,
                              c1*c2*s3 + s1*c2*c3);
            break;
        }
        case RotSeq::zxy:
        {
            return Quaternion(c1*c2*c3 - s1*s2*s3,
                              c1*s2*c3 - s1*c2*s3,
                              c1*s2*s3 + s1*c2*c3,
                              c1*c2*s3 + s1*s2*c3);
            break;
        }
        case RotSeq::zxz:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              c1*s2*c3 + s1*s2*s3,
                              c1*s2*s3 - s1*s2*c3,
                              c1*c2*s3 + s1*c2*c3);
            break;
        }
        case RotSeq::yxz:
        {
            return Quaternion(c1*c2*c3 + s1*s2*s3,
                              c1*s2*c3 + s1*c2*s3,
                              c1*c2*s3 - s1*s2*c3,
                              s1*c2*c3 - c1*s2*s3);
            break;
        }
        case RotSeq::yxy:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              c1*s2*c3 + s1*s2*s3,
                              c1*c2*s3 + s1*c2*c3,
                              s1*s2*c3 - c1*s2*s3);
            break;
        }
        case RotSeq::yzx:
        {
            return Quaternion(c1*c2*c3 - s1*s2*s3,
                              c1*s2*s3 + s1*c2*c3,
                              c1*c2*s3 + s1*s2*c3,
                              c1*s2*c3 - s1*c2*s3);
            break;
        }
        case RotSeq::yzy:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              c1*s2*s3 - s1*s2*c3,
                              c1*c2*s3 + s1*c2*c3,
                              c1*s2*c3 + s1*s2*s3);
            break;
        }
        case RotSeq::xyz:
        {
            return Quaternion(c1*c2*c3 - s1*s2*s3,
                              c1*c2*s3 + s1*s2*c3,
                              c1*s2*c3 - s1*c2*s3,
                              c1*s2*s3 + s1*c2*c3);
            break;
        }
        case RotSeq::xyx:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              c1*c2*s3 + s1*c2*c3,
                              c1*s2*c3 + s1*s2*s3,
                              c1*s2*s3 - s1*s2*c3);
            break;
        }
        case RotSeq::xzy:
        {
            return Quaternion(c1*c2*c3 + s1*s2*s3,
                              c1*c2*s3 - s1*s2*c3,
                              s1*c2*c3 - c1*s2*s3,
                              c1*s2*c3 + s1*c2*s3);
            break;
        }
        case RotSeq::xzx:
        {
            return Quaternion(c1*c2*c3 - s1*c2*s3,
                              c1*c2*s3 + s1*c2*c3,
                              s1*s2*c3 - c1*s2*s3,
                              c1*s2*c3 + s1*s2*s3);
            break;
        }
        default:
        {
            debugLog("default reached");
            return Quaternion(0.0, 0.0, 0.0, 0.0);
            break;
        }
    }
}

sf::Vector3<double> twoaxisrot(double r11, double r12, double r21, double r31, double r32)
{
    return sf::Vector3<double>(std::atan2(r11, r12), std::acos(r21), std::atan2(r31, r32));
}

sf::Vector3<double> threeaxisrot(double r11, double r12, double r21, double r31, double r32)
{
    return sf::Vector3<double>(std::atan2(r31, r32), std::asin(r21), std::atan2(r11, r12));
}

sf::Vector3<double> quaternion2Euler(const Quaternion& q, RotSeq rotSeq)
{
    switch(rotSeq)
    {
        case RotSeq::zyx: //
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.z*q.t + q.x*q.y), q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t),
                         /* -- ajouté*/-std::asin(2.0*(q.y*q.t - q.x*q.z)),
                                       std::atan2(2.0*(q.y*q.z + q.x*q.t), q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t));
            break;
        }
        case RotSeq::zyz:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.z*q.t - q.x*q.y), 2.0*(q.y*q.t + q.x*q.z)),
                                       std::acos(q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t),
                                       std::atan2(2.0*(q.z*q.t + q.x*q.y), -2.0*(q.y*q.t - q.x*q.z)));
            break;
        }
        case RotSeq::zxy:
        {
            return sf::Vector3<double>(std::atan2(-2.0*(q.y*q.t - q.x*q.z), q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t),
                                       std::asin(2.0*(q.z*q.t + q.x*q.y)),
                                       std::atan2(-2.0*(q.y*q.z - q.x*q.t), q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t));
            break;
        }
        case RotSeq::zxz:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.t + q.x*q.z), -2.0*(q.z*q.t - q.x*q.y)),
                                       std::acos(q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t),
                                       std::atan2(2.0*(q.y*q.t - q.x*q.z), 2.0*(q.z*q.t + q.x*q.y)));
            break;
        }
        case RotSeq::yxz:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.z + q.x*q.t), q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t),
                                       std::asin(-2.0*(q.z*q.t - q.x*q.y)),
                                       std::atan2(2.0*(q.y*q.t + q.x*q.z), q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t));
            break;
        }
        case RotSeq::yxy:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.z - q.x*q.t), 2.0*(q.z*q.t + q.x*q.y)),
                                       std::acos(q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t),
                                       std::atan2(2.0*(q.y*q.z + q.x*q.t), -2.0*(q.z*q.t - q.x*q.y)));
            break;
        }
        case RotSeq::yzx:
        {
            return sf::Vector3<double>(std::atan2(-2.0*(q.z*q.t - q.x*q.y), q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t),
                                       std::asin(2.0*(q.y*q.z + q.x*q.t)),
                                       std::atan2(-2.0*(q.y*q.t - q.x*q.z), q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t));
            break;
        }
        case RotSeq::yzy:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.z*q.t + q.x*q.y), -2.0*(q.y*q.z - q.x*q.t)),
                                       std::acos(q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t),
                                       std::atan2(2.0*(q.z*q.t - q.x*q.y), 2.0*(q.y*q.z + q.x*q.t)));
            break;
        }
        case RotSeq::xyz: //
        {
            return sf::Vector3<double>(std::atan2(-2.0*(q.y*q.z - q.x*q.t), q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t),
                         /*  - ajouté*/std::asin(-2.0*(q.y*q.t + q.x*q.z)),
                                       std::atan2(-2.0*(q.z*q.t - q.x*q.y), q.x*q.x - q.y*q.y - q.z*q.z + q.t*q.t));
            break;
        }
        case RotSeq::xyx:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.z + q.x*q.t), -2.0*(q.y*q.t - q.x*q.z)),
                                       std::acos(q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t),
                                       std::atan2(2.0*(q.y*q.z - q.x*q.t), 2.0*(q.y*q.t + q.x*q.z)));
            break;
        }
        case RotSeq::xzy:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.t + q.x*q.z), q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t),
                                       std::asin(-2.0*(q.y*q.z - q.x*q.t)),
                                       std::atan2(2.0*(q.z*q.t + q.x*q.y), q.x*q.x - q.y*q.y + q.z*q.z - q.t*q.t));
            break;
        }
        case RotSeq::xzx:
        {
            return sf::Vector3<double>(std::atan2(2.0*(q.y*q.t - q.x*q.z), 2.0*(q.y*q.z + q.x*q.t)),
                                       std::acos(q.x*q.x + q.y*q.y - q.z*q.z - q.t*q.t),
                                       std::atan2(2.0*(q.y*q.t + q.x*q.z), -2.0*(q.y*q.z - q.x*q.t)));
            break;
        }
        default:
        {
            debugLog("default reached");
            return sf::Vector3<double>(0.0, 0.0, 0.0);
            break;
        }
    }
}

std::back_insert_iterator<std::u32string> utf8ToUtf32(std::string::const_iterator be, std::string::const_iterator en, std::back_insert_iterator<std::u32string> output)
{
    // Some useful precomputed data
    static const std::array<unsigned char, 256> trailing =
    {{
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
    }};
    static const std::array<char32_t, 6> offsets =
    {{
        0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080
    }};
    while (be < en)
    {
        char32_t codepoint = 0;
        // decode the character
        unsigned char trailingBytes = trailing[static_cast<unsigned char>(*be)];
        if (be + trailingBytes < en)
        {
            switch (trailingBytes)
            {
                case 5: (codepoint += static_cast<unsigned char>(*be++)) <<= 6;
                case 4: (codepoint += static_cast<unsigned char>(*be++)) <<= 6;
                case 3: (codepoint += static_cast<unsigned char>(*be++)) <<= 6;
                case 2: (codepoint += static_cast<unsigned char>(*be++)) <<= 6;
                case 1: (codepoint += static_cast<unsigned char>(*be++)) <<= 6;
                case 0:  codepoint += static_cast<unsigned char>(*be++);
                default:;
            }
            codepoint -= offsets[trailingBytes];
        }
        else
        {
            // Incomplete character
            be = en;
        }
        *output++ = codepoint;
    }
    return output;
}

std::back_insert_iterator<std::string> utf32ToUtf8(std::u32string::const_iterator be, std::u32string::const_iterator en, std::back_insert_iterator<std::string> output)
{
    // Some useful precomputed data
    static const std::array<unsigned char, 7> firstBytes =
    {{
        0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
    }};
    while (be < en)
    {
        // Valid character
        // Get the number of bytes to write
        char32_t input = *be++;
        std::size_t bytestoWrite = 1;
        if      (input <  0x80)       bytestoWrite = 1;
        else if (input <  0x800)      bytestoWrite = 2;
        else if (input <  0x10000)    bytestoWrite = 3;
        else if (input <= 0x0010FFFF) bytestoWrite = 4;

        // Extract the bytes to write
        std::array<unsigned char, 4> bytes;
        switch (bytestoWrite)
        {
            case 4: bytes[3] = static_cast<unsigned char>((input | 0x80) & 0xBF); input >>= 6;
            case 3: bytes[2] = static_cast<unsigned char>((input | 0x80) & 0xBF); input >>= 6;
            case 2: bytes[1] = static_cast<unsigned char>((input | 0x80) & 0xBF); input >>= 6;
            case 1: bytes[0] = static_cast<unsigned char> (input | firstBytes[bytestoWrite]);
            default:;
        }
        // Add them to the output
        output = std::copy(bytes.data(), bytes.data() + bytestoWrite, output);
    }
    return output;
}

std::u32string str8Tostr32(const std::string s)
{
    std::u32string res = U"";
    utf8ToUtf32(s.begin(), s.end(), std::back_inserter(res));
    return res;
}

std::string str32Tostr8(const std::u32string s)
{
    std::string res = "";
    utf32ToUtf8(s.begin(), s.end(), std::back_inserter(res));
    return res;
}
