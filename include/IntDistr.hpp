#ifndef INTDISTR_HPP
#define INTDISTR_HPP
#include "RandManager.hpp"
#include <iostream>
#include <istream>
#include <stack>
#include <vector>

class IntDistr
{
public:
    /** Default constructor */
    IntDistr();
    ~IntDistr();
    IntDistr(const IntDistr& other);
    IntDistr(const std::vector<std::pair<long int, double> >& newValues);
    IntDistr(const std::vector<std::pair<IntDistr, double> >& newIntDistr);
    IntDistr(long int c);
    IntDistr& operator=(const IntDistr& rhs);

    std::size_t size() const;

    std::pair<long int, double>& operator[](std::size_t i);
    const std::pair<long int, double>& operator[](std::size_t i) const;

    IntDistr operator+() const;
    IntDistr operator-() const;
    IntDistr& operator++();
    IntDistr& operator--();
    IntDistr operator++(int) const;
    IntDistr operator--(int) const;
    IntDistr& operator+=(const IntDistr& right);
    IntDistr operator+(const IntDistr& right) const;
    IntDistr& operator-=(const IntDistr& right);
    IntDistr operator-(const IntDistr& right) const;
    IntDistr& operator*=(const IntDistr& right);
    IntDistr operator*(const IntDistr& right) const;
    IntDistr operator==(const IntDistr& right) const;
    IntDistr operator!=(const IntDistr& right) const;
    IntDistr operator>(const IntDistr& right) const;
    IntDistr operator<(const IntDistr& right) const;
    IntDistr operator>=(const IntDistr& right) const;
    IntDistr operator<=(const IntDistr& right) const;
    IntDistr repeat(long unsigned int n) const;
    IntDistr repeat(const IntDistr& n) const;

    double getMean() const;

    long int operator()() const;

    static void pushIdRand(RandManager::IdRand newIdRand);
    static void popIdRand();

protected:

private:
    std::vector<std::pair<long int, double> > values;

    static std::stack<RandManager::IdRand> idRand;
};
std::ostream& operator<<(std::ostream& os, const IntDistr& right);

#endif // INTDISTR_HPP
