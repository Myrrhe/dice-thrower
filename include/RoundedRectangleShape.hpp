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

#ifndef ROUNDEDRECTANGLESHAPE_HPP
#define ROUNDEDRECTANGLESHAPE_HPP
#include <SFML/Graphics/Shape.hpp>

/** \class RoundedRectangleShape
    \brief A rectangle with rounded corners.
*/
class RoundedRectangleShape final : public sf::Shape
{
public:

    RoundedRectangleShape();
    explicit RoundedRectangleShape(const sf::Vector2<float>& size,
                                   float radius = 0.0f, unsigned int cornerPointCount = 0u);
    RoundedRectangleShape(const RoundedRectangleShape& right);
    ~RoundedRectangleShape();
    RoundedRectangleShape& operator=(const RoundedRectangleShape& rhs);

    void setSize(const sf::Vector2<float>& size);

    const sf::Vector2<float>& getSize() const;

    void setCornersRadius(float radius);

    float getCornersRadius() const;

    void setCornerPointCount(unsigned int count);

    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2<float> getPoint(std::size_t index) const override;

protected:

private:
    sf::Vector2<float> m_size;
    float m_radius;
    unsigned int m_cornerPointCount;
};

#endif // ROUNDEDRECTANGLESHAPE_HPP
