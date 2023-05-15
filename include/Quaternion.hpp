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

#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include <complex>
#include <istream>
#include <iostream>
//#include <compare>

class Quaternion final
{
public:
    Quaternion(double newX = 0.0, double newY = 0.0, double newZ = 0.0, double newT = 0.0);
    Quaternion(std::complex<double> newXY,
               std::complex<double> newZT = std::complex<double>(0.0, 0.0));
    Quaternion(const Quaternion& newXYZT);
    ~Quaternion();
    Quaternion& operator=(const Quaternion& right);
    bool operator==(const Quaternion& right) const;
    bool operator!=(const Quaternion& right) const;
    bool operator>(const Quaternion& right) const;
    bool operator<(const Quaternion& right) const;
    bool operator>=(const Quaternion& right) const;
    bool operator<=(const Quaternion& right) const;
    //std::partial_ordering operator<=>(const Quaternion& right) const;
    const double& operator[](long unsigned int i) const;
    double& operator[](long unsigned int i);
    Quaternion operator+() const;
    Quaternion operator-() const;
    Quaternion& operator++();
    Quaternion operator++(int);
    Quaternion& operator--();
    Quaternion operator--(int);
    Quaternion& operator+=(const Quaternion& right);
    Quaternion& operator-=(const Quaternion& right);
    Quaternion& operator*=(const Quaternion& right);
    Quaternion& operator/=(const Quaternion& right);
    Quaternion operator+(const Quaternion& right) const;
    Quaternion operator-(const Quaternion& right) const;
    Quaternion operator*(const Quaternion& right) const;
    Quaternion operator/(const Quaternion& right) const;
    double getNormSquare() const;
    double getNorm() const;
    Quaternion getConjugation() const;
    Quaternion getReciprocal() const;
    Quaternion& setNorm(double newNorm = 1.0);
    Quaternion& conjugate();
    Quaternion& reciproc();
    double getX() const;
    double getY() const;
    double getZ() const;
    double getT() const;
    std::complex<double> getXY() const;
    std::complex<double> getZT() const;
    void setX(double newX = 0.0);
    void setY(double newY = 0.0);
    void setZ(double newZ = 0.0);
    void setT(double newT = 0.0);
    void setXY(double newX = 0.0, double newY = 0.0);
    void setXY(std::complex<double> newXY);
    void setXYZT(double newX = 0.0, double newY = 0.0, double newZ = 0.0, double newT = 0.0);
    void setXYZT(std::complex<double> newXY, std::complex<double> newZT = std::complex<double>(0.0, 0.0));
    void setXYZT(const Quaternion& newXYZT);
    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);

    static const double epsilon;

double x;
double y;
double z;
double t;

protected:

private:

};

#endif // QUATERNION_HPP
