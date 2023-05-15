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

#include "RoundedRectangleShape.hpp"
#include "func.hpp"
#include <cmath>

RoundedRectangleShape::RoundedRectangleShape() :
    m_size(),
    m_radius(),
    m_cornerPointCount()
{

}

RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2<float>& size, float radius, unsigned int cornerPointCount) :
    m_size(size),
    m_radius(radius),
    m_cornerPointCount(cornerPointCount)
{
    update();
}

RoundedRectangleShape::RoundedRectangleShape(const RoundedRectangleShape& right) :
    m_size(right.m_size),
    m_radius(right.m_radius),
    m_cornerPointCount(right.m_cornerPointCount)
{

}

RoundedRectangleShape::~RoundedRectangleShape()
{

}

RoundedRectangleShape& RoundedRectangleShape::operator=(const RoundedRectangleShape& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Shape::operator=(rhs);
    m_size = rhs.m_size;
    m_radius = rhs.m_radius;
    m_cornerPointCount = rhs.m_cornerPointCount;
    update();
    return *this;
}

void RoundedRectangleShape::setSize(const sf::Vector2<float>& size)
{
    m_size = size;
    update();
}

const sf::Vector2<float>& RoundedRectangleShape::getSize() const
{
    return m_size;
}

void RoundedRectangleShape::setCornersRadius(float radius)
{
    m_radius = radius;
    update();
}

float RoundedRectangleShape::getCornersRadius() const
{
    return m_radius;
}

void RoundedRectangleShape::setCornerPointCount(unsigned int count)
{
    m_cornerPointCount = count;
    update();
}

std::size_t RoundedRectangleShape::getPointCount() const
{
    return m_cornerPointCount*4;
}

sf::Vector2<float> RoundedRectangleShape::getPoint(std::size_t index) const
{
    if (index >= m_cornerPointCount*4)
    {
        return sf::Vector2<float>(0.0f, 0.0f);
    }
    float deltaAngle = 90.0f/static_cast<float>(m_cornerPointCount - 1);
    sf::Vector2<float> center;
    std::size_t centerIndex = index/m_cornerPointCount;
    switch(centerIndex)
    {
    case 0:
    {
        center.x = m_size.x - m_radius;
        center.y = m_radius;
        break;
    }
    case 1:
    {
        center.x = m_radius;
        center.y = m_radius;
        break;
    }
    case 2:
    {
        center.x = m_radius;
        center.y = m_size.y - m_radius;
        break;
    }
    case 3:
    {
        center.x = m_size.x - m_radius;
        center.y = m_size.y - m_radius;
        break;
    }
    default:
    {
        debugLog("default reached");
        center.x = 0.0f;
        center.y = 0.0f;
        break;
    }
    }
    return sf::Vector2<float>(m_radius*std::cos(deltaAngle*static_cast<float>(index - centerIndex)*m_pi_f/180.0f) + center.x,
                              -m_radius*std::sin(deltaAngle*static_cast<float>(index - centerIndex)*m_pi_f/180.0f) + center.y);
}
