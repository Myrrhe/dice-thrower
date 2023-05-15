/*
 * A non copyable class.
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

#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

/** \class NonCopyable
    \brief A base class that makes any derived class non-copyable.
*/
class NonCopyable
{
public:
    /** Copy constructor
     *  \param other Object to copy from
     */
    NonCopyable(const NonCopyable& other) = delete;
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    NonCopyable& operator=(const NonCopyable& other) = delete;

protected:
    /** Default constructor */
    NonCopyable();
    /** Default destructor */
    ~NonCopyable();
private:
};

#endif // NONCOPYABLE_HPP
