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

#ifndef FUNC_HPP
#define FUNC_HPP
#include "Quaternion.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

#if DEBUG
    #define debugLog(...) {\
        char debugLogStr [100];\
        sprintf(debugLogStr, __VA_ARGS__);\
        std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " <<\
        debugLogStr << std::endl;\
        }
#else
    #define debugLog(...)
#endif // DEBUG

constexpr double m_e =        2.71828182845904523536;
constexpr double m_log2e =    1.44269504088896340736;
constexpr double m_log10e =   0.434294481903251827651;
constexpr double m_ln2 =      0.693147180559945309417;
constexpr double m_ln10 =     2.30258509299404568402;
constexpr double m_pi =       3.14159265358979323846;
constexpr double m_2pi =      6.28318530717958647692;
constexpr double m_pi_2 =     1.57079632679489661923;
constexpr double m_pi_4 =     0.785398163397448309616;
constexpr double m_1_pi =     0.318309886183790671538;
constexpr double m_2_pi =     0.636619772367581343076;
constexpr double m_2_sqrtpi = 1.12837916709551257390;
constexpr double m_sqrt2 =    1.41421356237309504880;
constexpr double m_1_sqrt2 =  0.707106781186547524401;
constexpr double m_epsilon =  0.00000000000000000001;

constexpr double m_1_60s = 1.0/60.0;

constexpr float m_e_f =        2.71828182845904523536f;
constexpr float m_log2e_f =    1.44269504088896340736f;
constexpr float m_log10e_f =   0.434294481903251827651f;
constexpr float m_ln2_f =      0.693147180559945309417f;
constexpr float m_ln10_f =     2.30258509299404568402f;
constexpr float m_pi_f =       3.14159265358979323846f;
constexpr float m_2pi_f =      6.28318530717958647692f;
constexpr float m_pi_2_f =     1.57079632679489661923f;
constexpr float m_pi_4_f =     0.785398163397448309616f;
constexpr float m_1_pi_f =     0.318309886183790671538f;
constexpr float m_2_pi_f =     0.636619772367581343076f;
constexpr float m_2_sqrtpi_f = 1.12837916709551257390f;
constexpr float m_sqrt2_f =    1.41421356237309504880f;
constexpr float m_1_sqrt2_f =  0.707106781186547524401f;
constexpr float m_epsilon_f =  0.00000000000000000001f;

constexpr float m_1_60sf = 1.0f/60.0f;

enum class Interp : long unsigned int
{
    LIN,
    ACC,
    BRA,
    SIN,
    SFO,

    SIN0
};

std::ostream& operator<<(std::ostream& os, const sf::Color& right);

std::ostream& operator<<(std::ostream& os, const sf::Vector2<int>& right);
std::ostream& operator<<(std::ostream& os, const sf::Vector2<float>& right);
std::ostream& operator<<(std::ostream& os, const sf::Vector2<double>& right);

std::ostream& operator<<(std::ostream& os, const sf::Rect<int>& right);
std::ostream& operator<<(std::ostream& os, const sf::Rect<float>& right);
std::ostream& operator<<(std::ostream& os, const sf::Rect<double>& right);

std::ostream& operator<<(std::ostream& os, const sf::Transform& right);

std::ostream& operator<<(std::ostream& os, const sf::Time& right);

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& right);
std::ostream& operator<<(std::ostream& os, const std::vector<long unsigned int>& right);
std::ostream& operator<<(std::ostream& os, const std::vector<double>& right);

sf::Rect<int> operator|(const sf::Rect<int>& left, const sf::Rect<int>& right);
sf::Rect<float> operator|(const sf::Rect<float>& left, const sf::Rect<float>& right);
sf::Rect<double> operator|(const sf::Rect<double>& left, const sf::Rect<double>& right);

sf::Rect<int> operator+(const sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float> operator+(const sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double> operator+(const sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int>& operator+=(sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float>& operator+=(sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double>& operator+=(sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int> operator-(const sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float> operator-(const sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double> operator-(const sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int>& operator-=(sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float>& operator-=(sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double>& operator-=(sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int> operator*(const sf::Rect<int>& left, int right);
sf::Rect<float> operator*(const sf::Rect<float>& left, float right);
sf::Rect<double> operator*(const sf::Rect<double>& left, double right);

sf::Rect<int>& operator*=(sf::Rect<int>& left, int right);
sf::Rect<float>& operator*=(sf::Rect<float>& left, float right);
sf::Rect<double>& operator*=(sf::Rect<double>& left, double right);

sf::Rect<int> operator/(const sf::Rect<int>& left, int right);
sf::Rect<float> operator/(const sf::Rect<float>& left, float right);
sf::Rect<double> operator/(const sf::Rect<double>& left, double right);

sf::Rect<int>& operator/=(sf::Rect<int>& left, int right);
sf::Rect<float>& operator/=(sf::Rect<float>& left, float right);
sf::Rect<double>& operator/=(sf::Rect<double>& left, double right);

sf::Rect<int> operator*(const sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float> operator*(const sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double> operator*(const sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int>& operator*=(sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float>& operator*=(sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double>& operator*=(sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int> operator/(const sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float> operator/(const sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double> operator/(const sf::Rect<double>& left, const sf::Vector2<double>& right);

sf::Rect<int>& operator/=(sf::Rect<int>& left, const sf::Vector2<int>& right);
sf::Rect<float>& operator/=(sf::Rect<float>& left, const sf::Vector2<float>& right);
sf::Rect<double>& operator/=(sf::Rect<double>& left, const sf::Vector2<double>& right);

int operator*(const sf::Vector2<int>& left, const sf::Vector2<int>& right);
unsigned int operator*(const sf::Vector2<unsigned int>& left, const sf::Vector2<unsigned int>& right);
float operator*(const sf::Vector2<float>& left, const sf::Vector2<float>& right);
double operator*(const sf::Vector2<double>& left, const sf::Vector2<double>& right);

int operator^(const sf::Vector2<int>& left, const sf::Vector2<int>& right);
float operator^(const sf::Vector2<float>& left, const sf::Vector2<float>& right);
double operator^(const sf::Vector2<double>& left, const sf::Vector2<double>& right);

sf::Vector2<float> floor(const sf::Vector2<float>& v);

float getNorm(const sf::Vector2<float>& v);
double getNorm(const sf::Vector2<double>& v);

sf::Vector2<int> getInverted(const sf::Vector2<int>& v);
sf::Vector2<unsigned int> getInverted(const sf::Vector2<unsigned int>& v);
sf::Vector2<float> getInverted(const sf::Vector2<float>& v);
sf::Vector2<double> getInverted(const sf::Vector2<double>& v);

sf::Vector2<float> getNormalized(const sf::Vector2<float>& v);
sf::Vector2<double> getNormalized(const sf::Vector2<double>& v);

float radToDeg(float radians);
double radToDeg(double radians);

float degToRad(float degree);
double degToRad(double degree);

float getRotationAngle(const sf::Vector2<float>& v); // Angle in radians
double getRotationAngle(const sf::Vector2<double>& v); // Angle in radians

float getAngleBetween(const sf::Vector2<float>& v1, const sf::Vector2<float>& v2); // Angle in radians
double getAngleBetween(const sf::Vector2<double>& v1, const sf::Vector2<double>& v2); // Angle in radians

sf::Vector2<float> getRotated(const sf::Vector2<float>& vec, float angle);
sf::Vector2<double> getRotated(const sf::Vector2<double>& vec, double angle);

double getCoeff(double coeff, Interp interp = Interp::LIN, bool limiter = true);
double getCoeff(double x, double X, Interp interp = Interp::LIN, bool limiter = true);

sf::Color colorBalance(const sf::Color& color1, const sf::Color& color2, double coeff, Interp interp = Interp::LIN);

std::string getStringHourPrecise();
std::string getStringHourVeryPrecise();
std::array<long unsigned int, 4> getHourVeryPrecise();

std::vector<std::string> split(const std::string& s, char delim);

const std::vector<std::string>& split(const std::string& s, const std::string& delim);

std::vector<std::u32string> split(const std::u32string& s, char32_t delim);

const std::vector<std::u32string>& split(const std::u32string& s, const std::u32string& delim);

long unsigned int imod(long int i1, long int i2);

double dmod(double numer, double denom);

float f_mod(float numer, float denom);

long unsigned int power(long unsigned int base, long unsigned int exponent);

sf::String stringTosfString(const std::string& str);

sf::String evaluateSpecialChars(const sf::String& str);

std::vector<std::string> getDir(const std::string& dir);

bool fileExist(const std::string& path);

std::string getKeyWordLine(const std::string& line);

std::string getValueLine(const std::string& line);

std::pair<std::string, std::string> getKeyValueLine(const std::string& line);

std::u32string getKeyWordLine(const std::u32string& line);

std::u32string getValueLine(const std::u32string& line);

std::pair<std::u32string, std::u32string> getKeyValueLine(const std::u32string& line);

bool isFloat(const std::string& s);

bool isFloat(const std::u32string& s);

bool isPosInt(const std::string& s);

bool isPosInt(const std::u32string& s);

float str32ToF(const std::u32string& s);

long unsigned int str32ToLui(const std::u32string& s);

long unsigned int str32HexToLui(const std::u32string& s);

std::u32string luiTo32Str(long unsigned int n);

std::u32string luiTo32StrHex(long unsigned int n);

std::u32string fTo32Str(float n);

sf::Rect<int> getTextureRect(const sf::Texture* texture);

enum class RotSeq : long unsigned int {zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xyx, xzy, xzx};

Quaternion getQuatRot(double angle, const sf::Vector3<double>& axe);

Quaternion euler2Quaternion(const sf::Vector3<double>& angle, RotSeq rotSeq);

sf::Vector3<double> twoaxisrot(double r11, double r12, double r21, double r31, double r32);

sf::Vector3<double> threeaxisrot(double r11, double r12, double r21, double r31, double r32);

sf::Vector3<double> quaternion2Euler(const Quaternion& q, RotSeq rotSeq);

std::back_insert_iterator<std::u32string> utf8ToUtf32(std::string::const_iterator be, std::string::const_iterator en, std::back_insert_iterator<std::u32string> output);

std::back_insert_iterator<std::string> utf32ToUtf8(std::u32string::const_iterator be, std::u32string::const_iterator en, std::back_insert_iterator<std::string> output);

std::u32string str8Tostr32(const std::string s);

std::string str32Tostr8(const std::u32string s);

#endif // FUNC_HPP
